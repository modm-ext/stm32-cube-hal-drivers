#!/usr/bin/env python3
import shutil
import logging
import os, re, sys
import subprocess

from pathlib import Path
from multiprocessing.pool import ThreadPool

stm32_families = [
    "c0xx",
    "f0xx", "f1xx", "f2xx", "f3xx", "f4xx", "f7xx",
    "g0xx", "g4xx",
    "h5xx", "h7xx", "h7rsxx",
    "l0xx", "l1xx", "l4xx", "l5xx",
    "u0xx", "u5xx",
    "wbxx", "wb0x", "wbaxx", "wlxx", "wl3x",
]

def get_header_version(release_notes):
    vmatch = re.search(r">V([0-9]+\.[0-9]+\.[0-9]+)", release_notes)
    return vmatch.group(1) if vmatch else None

def get_header_date(release_notes):
    vmatch = re.search(r">V.+?/.*?(\d{2}-[A-Z][a-z]+?-20\d{2}).*?<", release_notes, flags=re.DOTALL | re.MULTILINE)
    return vmatch.group(1) if vmatch else None

logging.basicConfig(level=logging.DEBUG if "-vv" in sys.argv else logging.INFO)

def get_header_files(family):
    LOGGER = logging.getLogger(family)

    remote_path = Path(f"raw/stm32{family}").absolute()
    repo_url = f"https://github.com/STMicroelectronics/stm32{family}-hal-driver.git"
    subprocess.run(f"git clone --depth=1 {repo_url} {remote_path}", shell=True)

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
    LOGGER.info("Header v{} -> v{}".format(header_local_version, header_remote_version))

    if header_local_version == header_remote_version:
        LOGGER.info("Skipping update...")
        return (header_remote_version, header_remote_date)

    shutil.rmtree(destination_path, ignore_errors=True)
    destination_path.mkdir(parents=True)
    shutil.copy(remote_readme, destination_path / "Release_Notes.html")
    for glob in ("Inc/*.h", "Src/*.c"):
        for path in remote_path.glob(glob):
            if not path.is_file(): continue
            dest = destination_path / path.relative_to(remote_path)
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
with ThreadPool(len(stm32_families)) as pool:
    family_versions = pool.map(get_header_files, stm32_families)


def update_readme(readme, family, new_version, new_date):
    family = family.rstrip('x').upper()
    match = rf"{family}: v.+? created .+?]"
    replace = f"{family}: v{new_version} created {new_date}]"
    return re.sub(match, replace, readme)

for family, versions in zip(stm32_families, family_versions):
    if versions is None or versions[0] is None: continue;
    readme = Path("README.md").read_text()
    readme = update_readme(readme, family, versions[0], versions[1])
    Path("README.md").write_text(readme)
    subprocess.run(f"git add README.md stm32{family}", shell=True)
    if subprocess.call("git diff-index --quiet HEAD --", shell=True):
        subprocess.run(f'git commit -m "Update STM32{family.rstrip('x').upper()} CubeHal drivers to v{versions[0]}"', shell=True)

exit(family_versions.count(None))
