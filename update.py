#!/usr/bin/env python3

import urllib.request
import shutil
import logging
import os
import re
import sys
import subprocess
import json
import urllib.request

from pathlib import Path
from multiprocessing.pool import ThreadPool

def replace(text, key, content):
    return re.sub(r"<!--{0}-->.*?<!--/{0}-->".format(key), "<!--{0}-->\n{1}\n<!--/{0}-->".format(key, content), text, flags=re.DOTALL | re.MULTILINE)

def get_header_version(release_notes):
    vmatch = re.search(r">V([0-9]+\.[0-9]+\.[0-9]+)", release_notes) or \
             re.search(r">([0-9]+\.[0-9]+\.[0-9]+) */", release_notes)
    return vmatch.group(1) if vmatch else None

def get_header_date(release_notes):
    vmatch = re.search(r">V.+?/.*?(\d{2}-[A-Z][a-z]+?-20\d{2}).*?<", release_notes, flags=re.DOTALL | re.MULTILINE) or \
             re.search(r">[0-9]+\.[0-9]+\.[0-9]+ */.*?(\d{2}-[A-Z][a-z]+?-20\d{2}).*?<", release_notes, flags=re.DOTALL)
    return vmatch.group(1) if vmatch else None

def repo_name(family):
    return f"stm32{family}-drivers" if family in stm32_hal2 else f"stm32{family}-hal-driver"

logging.basicConfig(level=logging.DEBUG if "-vv" in sys.argv else logging.INFO)

def get_header_files(family):
    LOGGER = logging.getLogger(family)

    remote_path = Path(f"raw/stm32{family}").absolute()
    repo = f"STMicroelectronics/{repo_name(family)}"
    repo_url = f"https://github.com/{repo}.git"

    with urllib.request.urlopen(f"https://api.github.com/repos/{repo}/tags") as response:
        tag = json.loads(response.read())[0]["name"]

    subprocess.run(f"git clone --depth=1 --branch {tag} {repo_url} {remote_path}", shell=True)

    remote_readme = (remote_path / "Release_Notes.html")
    remote_readme_content = remote_readme.read_text(errors="replace")
    header_remote_version = get_header_version(remote_readme_content)
    header_remote_date = get_header_date(remote_readme_content)

    destination_path = Path(f"stm32{family}")
    header_local_version = (destination_path / "Release_Notes.html")
    if header_local_version.exists():
        header_local_version = get_header_version(header_local_version.read_text(errors="replace"))
    else:
        header_local_version = None
    LOGGER.info(f"STM32{family.upper()} -> {tag}")

    shutil.rmtree(destination_path, ignore_errors=True)
    destination_path.mkdir(parents=True)
    shutil.copy(remote_readme, destination_path / "Release_Notes.html")
    # HAL2 mixes headers and sources in hal/ and ll/, flatten them into Inc/ and Src/
    globs = {"hal/*.h": "Inc", "ll/*.h": "Inc", "hal/*.c": "Src", "ll/*.c": "Src"} if family in stm32_hal2 else \
            {"Inc/*.h": None, "Inc/*/*.h": None, "Src/*.c": None}
    for glob, folder in globs.items():
        for path in remote_path.glob(glob):
            if not path.is_file(): continue
            dest = destination_path / (Path(folder, path.name) if folder else path.relative_to(remote_path))
            if dest.exists():
                LOGGER.critical(f"{dest} already exists!")
                return None
            dest.parent.mkdir(parents=True, exist_ok=True)
            # Copy, normalize newline and remove trailing whitespace
            with path.open("r", newline=None, encoding="utf-8", errors="ignore") as rfile, \
                            dest.open("w", encoding="utf-8") as wfile:
                wfile.writelines(l.rstrip()+"\n" for l in rfile.readlines())

    for patch in Path('patches').glob(f"{family}*.patch"):
        LOGGER.info(f"Applying {patch}...")
        if os.system(f"git apply -v --ignore-whitespace {patch}") != 0:
            LOGGER.critical(f"Applying {patch} FAILED...")
            return None

    LOGGER.info("Successful update")
    return (header_remote_version, header_remote_date)


shutil.rmtree("raw", ignore_errors=True)
Path("raw").mkdir()
subprocess.run("git clone --depth=1 https://github.com/STMicroelectronics/STM32Cube_MCU_Overall_Offer.git raw/STM32Cube_MCU_Overall_Offer", shell=True)
readme = "".join(p.read_text() for p in Path("raw/STM32Cube_MCU_Overall_Offer").glob("*.md"))
stm32_hal2 = [f.lower() for f in re.findall(r"\(https://github.com/STMicroelectronics/stm32(\w+?)-drivers\)", readme, flags=re.IGNORECASE)]
stm32_families = re.findall(r"\(https://github.com/STMicroelectronics/stm32(\w+?)-hal-driver\)", readme)
stm32_families = sorted(set(stm32_families + stm32_hal2), key=lambda f: f.rstrip('x'))

with ThreadPool(len(stm32_families)) as pool:
    family_versions = pool.map(get_header_files, stm32_families)
# family_versions = [get_header_files(f) for f in stm32_families]

readme = Path("README.md").read_text()
rows = {f.lower(): row for row, f in re.findall(r"^(- \[STM32(\w+?):.*)$", readme, flags=re.MULTILINE)}

for family, versions in zip(stm32_families, family_versions):
    if versions is None or versions[0] is None: continue;
    # Update only this family's row, so that each commit contains only its own README change
    name = family.rstrip('x')
    rows[name] = f"- [STM32{name.upper()}: v{versions[0]} created {versions[1]}](https://github.com/STMicroelectronics/{repo_name(family)})"
    readme = replace(readme, "table", "\n".join(rows[f.rstrip('x')] for f in stm32_families if f.rstrip('x') in rows))
    Path("README.md").write_text(readme)
    subprocess.run(f"git add README.md stm32{family}", shell=True)
    if subprocess.call("git diff-index --quiet HEAD --", shell=True):
        subprocess.run(f'git commit -m "Update STM32{family.rstrip('x').upper()} CubeHal drivers to v{versions[0]}"', shell=True)

exit(family_versions.count(None))
