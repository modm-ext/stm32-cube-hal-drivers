/**
  ******************************************************************************
  * @file    stm32wbaxx_ll_utils.h
  * @author  MCD Application Team
  * @brief   Header file of UTILS LL module.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  @verbatim
  ==============================================================================
                     ##### How to use this driver #####
  ==============================================================================
    [..]
    The LL UTILS driver contains a set of generic APIs that can be
    used by user:
      (+) Device electronic signature
      (+) Timing functions
      (+) PLL configuration functions

  @endverbatim
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32WBAxx_LL_UTILS_H
#define __STM32WBAxx_LL_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx.h"

/** @addtogroup STM32WBAxx_LL_Driver
  * @{
  */

/** @defgroup UTILS_LL UTILS
  * @{
  */

/* Private types -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private constants ---------------------------------------------------------*/
/** @defgroup UTILS_LL_Private_Constants UTILS Private Constants
  * @{
  */

/* Max delay can be used in LL_mDelay */
#define LL_MAX_DELAY                  0xFFFFFFFFU

/**
  * @brief Unique device ID register base address
  */
#define UID_BASE_ADDRESS              UID_BASE

/**
  * @brief Flash size data register base address
  */
#define FLASHSIZE_BASE_ADDRESS        FLASHSIZE_BASE

/**
  * @brief Package data register base address
  */
#define PACKAGE_BASE_ADDRESS          PACKAGE_BASE

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup UTILS_LL_Private_Macros UTILS Private Macros
  * @{
  */
/**
  * @}
  */
/* Exported types ------------------------------------------------------------*/
/** @defgroup UTILS_LL_ES_INIT UTILS Exported structures
  * @{
  */

/**
  * @brief  UTILS PLL structure definition
  */
typedef struct
{
  uint32_t PLLM;   /*!< Division factor for PLL VCO input clock.
                        This parameter can be a number between Min_Data = 1 and Max_Data = 16

                        This feature can be modified afterwards using one of these functions
                        @ref LL_RCC_PLL1_ConfigDomain_PLL1P(), @ref LL_RCC_PLL1_ConfigDomain_PLL1R(), @ref LL_RCC_PLL1_ConfigDomain_PLL1Q(). */

  uint32_t PLLN;   /*!< Multiplication factor for PLL VCO output clock.
                        This parameter must be a number between Min_Data = 4 and Max_Data = 512

                        This feature can be modified afterwards using one of these functions
                        @ref LL_RCC_PLL1_ConfigDomain_PLL1P(), @ref LL_RCC_PLL1_ConfigDomain_PLL1R(), @ref LL_RCC_PLL1_ConfigDomain_PLL1Q(). */

  uint32_t PLLR;   /*!< Division for the main system clock.
                        This parameter can be a number between Min_Data = 1 and Max_Data = 128

                        This feature can be modified afterwards using unitary function
                        @ref LL_RCC_PLL1_ConfigDomain_PLL1R(). */
} LL_UTILS_PLLInitTypeDef;

/**
  * @brief  UTILS System, AHB and APB buses clock configuration structure definition
  */
typedef struct
{
  uint32_t AHBCLKDivider;         /*!< The AHB clock (HCLK) divider. This clock is derived from the system clock (SYSCLK).
                                       This parameter can be a value of @ref RCC_LL_EC_SYSCLK_DIV

                                       This feature can be modified afterwards using unitary function
                                       @ref LL_RCC_SetAHBPrescaler(). */

  uint32_t APB1CLKDivider;        /*!< The APB1 clock (PCLK1) divider. This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_LL_EC_APB1_DIV

                                       This feature can be modified afterwards using unitary function
                                       @ref LL_RCC_SetAPB1Prescaler(). */

  uint32_t APB2CLKDivider;        /*!< The APB2 clock (PCLK2) divider. This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_LL_EC_APB2_DIV

                                       This feature can be modified afterwards using unitary function
                                       @ref LL_RCC_SetAPB2Prescaler(). */

  uint32_t APB7CLKDivider;        /*!< The APB7 clock (PCLK7) divider. This clock is derived from the AHB clock (HCLK).
                                       This parameter can be a value of @ref RCC_LL_EC_APB7_DIV

                                       This feature can be modified afterwards using unitary function
                                       @ref LL_RCC_SetAPB7Prescaler(). */

} LL_UTILS_ClkInitTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup UTILS_LL_Exported_Constants UTILS Exported Constants
  * @{
  */

/** @defgroup UTILS_EC_PACKAGETYPE PACKAGE TYPE
  * @{
  */
#if defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx) || defined(STM32WBA5Mxx)
#define LL_UTILS_PACKAGETYPE_UFQFPN32           0x00000000U /*!< UFQFPN32 package type                               */
#define LL_UTILS_PACKAGETYPE_UFQFPN48           0x00000002U /*!< UFQFPN48 package type                               */
#define LL_UTILS_PACKAGETYPE_WLCSP41_SMPS       0x00000009U /*!< WLCSP41 with internal SMPS package type             */
#define LL_UTILS_PACKAGETYPE_UFQFPN48_SMPS      0x0000000AU /*!< UFQFPN48 with internal SMPS package type            */
#define LL_UTILS_PACKAGETYPE_UFBGA59            0x0000000BU /*!< UFBGA59 package type                                */
#elif defined(STM32WBA62xx) || defined(STM32WBA63xx) || defined(STM32WBA64xx) || defined(STM32WBA65xx) || defined (STM32WBA6Mxx)
#define LL_UTILS_PACKAGETYPE_UFQFPN48_USB       0x00000003U /*!< UFQFPN48 with USB package type                      */
#define LL_UTILS_PACKAGETYPE_WLCSP88_USB        0x00000005U /*!< WLSCP88 with USB package type                       */
#define LL_UTILS_PACKAGETYPE_UFBGA121_USB       0x00000007U /*!< UFBGA121 with USB package type                      */
#define LL_UTILS_PACKAGETYPE_UFQFPN48_SMPS      0x0000000AU /*!< UFQFPN48 with internal SMPS package type            */
#define LL_UTILS_PACKAGETYPE_UFQFPN48_SMPS_USB  0x0000000BU /*!< UFQFPN48 with internal SMPS and USB package type    */
#define LL_UTILS_PACKAGETYPE_VFQFPN68_SMPS_USB  0x0000000CU /*!< VFQFPN68 with internal SMPS and USB package type    */
#define LL_UTILS_PACKAGETYPE_WLCSP88_SMPS_USB   0x0000000DU /*!< WLCSP88 with internal SMPS and USB package type     */
#define LL_UTILS_PACKAGETYPE_UFBGA121_SMPS_USB  0x0000000FU /*!< UFBGA121 with internal SMPS and USB package type    */
#endif /* defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx) || defined(STM32WBA5Mxx) */
/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/

/* Exported functions --------------------------------------------------------*/
/** @defgroup UTILS_LL_Exported_Functions UTILS Exported Functions
  * @{
  */

/** @defgroup UTILS_EF_DEVICE_ELECTRONIC_SIGNATURE DEVICE ELECTRONIC SIGNATURE
  * @{
  */

/**
  * @brief  Get Word0 of the unique device identifier (UID based on 96 bits)
  * @retval UID[31:0]: X and Y coordinates on the wafer expressed in BCD format
  */
__STATIC_INLINE uint32_t LL_GetUID_Word0(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)UID_BASE_ADDRESS)));
}

/**
  * @brief  Get Word1 of the unique device identifier (UID based on 96 bits)
  * @retval UID[63:32]: Wafer number (UID[39:32]) & LOT_NUM[23:0] (UID[63:40])
  */
__STATIC_INLINE uint32_t LL_GetUID_Word1(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)(UID_BASE_ADDRESS + 4U))));
}

/**
  * @brief  Get Word2 of the unique device identifier (UID based on 96 bits)
  * @retval UID[95:64]: Lot number (ASCII encoded) - LOT_NUM[55:24]
  */
__STATIC_INLINE uint32_t LL_GetUID_Word2(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)(UID_BASE_ADDRESS + 8U))));
}

/**
  * @brief  Get Flash memory size
  * @note   This bitfield indicates the size of the device Flash memory expressed in
  *         Kbytes. As an example, 0x040 corresponds to 64 Kbytes.
  * @retval FLASH_SIZE[15:0]: Flash memory size in Kbytes
  */
__STATIC_INLINE uint32_t LL_GetFlashSize(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)FLASHSIZE_BASE_ADDRESS)) & 0xFFFFU);
}

/**
  * @brief  Get Package type
  * @retval Returned value can be one of the following values:
#if defined(STM32WBA52xx) || defined(STM32WBA54xx) || defined(STM32WBA55xx) || defined(STM32WBA5Mxx)
  *         @arg @ref LL_UTILS_PACKAGETYPE_UFQFPN32
  *         @arg @ref LL_UTILS_PACKAGETYPE_UFQFPN48
  *         @arg @ref LL_UTILS_PACKAGETYPE_WLCSP41_SMPS
  *         @arg @ref LL_UTILS_PACKAGETYPE_UFQFPN48_SMPS
  *         @arg @ref LL_UTILS_PACKAGETYPE_UFBGA59
#elif defined(STM32WBA62xx) || defined(STM32WBA63xx) || defined(STM32WBA64xx) || defined(STM32WBA65xx) || defined (STM32WBA6Mxx)
  *         @arg @ref LL_UTILS_PACKAGETYPE_UFQFPN48_USB
  *         @arg @ref LL_UTILS_PACKAGETYPE_WLCSP88_USB
  *         @arg @ref LL_UTILS_PACKAGETYPE_UFBGA121_USB
  *         @arg @ref LL_UTILS_PACKAGETYPE_UFQFPN48_SMPS
  *         @arg @ref LL_UTILS_PACKAGETYPE_UFQFPN48_SMPS_USB
  *         @arg @ref LL_UTILS_PACKAGETYPE_VFQFPN68_SMPS_USB
  *         @arg @ref LL_UTILS_PACKAGETYPE_WLCSP88_SMPS_USB
  *         @arg @ref LL_UTILS_PACKAGETYPE_UFBGA121_SMPS_USB
#endif
  */
__STATIC_INLINE uint32_t LL_GetPackageType(void)
{
  return (uint32_t)(READ_REG(*((uint32_t *)PACKAGE_BASE_ADDRESS)) & 0x1FU);
}

/**
  * @}
  */

/** @defgroup UTILS_LL_EF_DELAY DELAY
  * @{
  */

/**
  * @brief  This function configures the Cortex-M SysTick source of the time base.
  * @param  HCLKFrequency HCLK frequency in Hz (can be calculated thanks to RCC helper macro)
  * @note   When a RTOS is used, it is recommended to avoid changing the SysTick
  *         configuration by calling this function, for a delay use rather osDelay RTOS service.
  * @param  Ticks Number of ticks
  * @retval None
  */
__STATIC_INLINE void LL_InitTick(uint32_t HCLKFrequency, uint32_t Ticks)
{
  /* Configure the SysTick to have interrupt in 1ms time base */
  SysTick->LOAD  = (uint32_t)((HCLKFrequency / Ticks) - 1UL);  /* set reload register */
  SysTick->VAL   = 0UL;                                       /* Load the SysTick Counter Value */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                   SysTick_CTRL_ENABLE_Msk;                   /* Enable the Systick Timer */
}

void        LL_Init1msTick(uint32_t HCLKFrequency);
void        LL_Init1msTick_HCLK_Div8(uint32_t HCLKFrequency);
void        LL_Init1msTick_LSE(void);
void        LL_Init1msTick_LSI(void);
void        LL_mDelay(uint32_t Delay);

/**
  * @}
  */

/** @defgroup UTILS_EF_SYSTEM SYSTEM
  * @{
  */

void        LL_SetSystemCoreClock(uint32_t HCLKFrequency);
ErrorStatus LL_PLL1_ConfigSystemClock_HSI(LL_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct,
                                          LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct);
ErrorStatus LL_PLL1_ConfigSystemClock_HSE(uint32_t HSEFrequency,
                                          LL_UTILS_PLLInitTypeDef *UTILS_PLLInitStruct,
                                          LL_UTILS_ClkInitTypeDef *UTILS_ClkInitStruct);
ErrorStatus LL_SetFlashLatency(uint32_t HCLK_Frequency);
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __STM32WBAxx_LL_UTILS_H */

