/**
  ******************************************************************************
  * @file    stm32wbaxx_hal_sai_ex.h
  * @author  MCD Application Team
  * @brief   Header file of SAI HAL extended module.
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
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef STM32WBAxx_HAL_SAI_EX_H
#define STM32WBAxx_HAL_SAI_EX_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx_hal_def.h"

/** @addtogroup STM32WBAxx_HAL_Driver
  * @{
  */
#if defined (SAI1)
/** @addtogroup SAIEx
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup SAIEx_Exported_Types SAIEx Exported Types
  * @{
  */

/**
  * @brief  PDM microphone delay structure definition
  */
typedef struct
{
#if defined(STM32WBA62xx) || defined(STM32WBA63xx) || defined(STM32WBA64xx) || defined(STM32WBA65xx) || defined (STM32WBA6Mxx)
  uint32_t MicPair;     /*!< Specifies which pair of microphones is selected.
                             This parameter must be a number between Min_Data = 1 and
                             Max_Data = 3 for STM32WBA6xxx devices, Max_Data = 2 for other devices. */
#else /* defined(STM32WBA62xx) || defined(STM32WBA63xx) || defined(STM32WBA64xx) || defined(STM32WBA65xx) || defined (STM32WBA6Mxx) */
  uint32_t MicPair;     /*!< Specifies which pair of microphones is selected.
                             This parameter must be a number between Min_Data = 1 and Max_Data = 2. */
#endif /* defined(STM32WBA62xx) || defined(STM32WBA63xx) || defined(STM32WBA64xx) || defined(STM32WBA65xx) || defined (STM32WBA6Mxx) */

  uint32_t LeftDelay;   /*!< Specifies the delay in PDM clock unit to apply on left microphone.
                             This parameter must be a number between Min_Data = 0 and Max_Data = 7. */

  uint32_t RightDelay;  /*!< Specifies the delay in PDM clock unit to apply on right microphone.
                             This parameter must be a number between Min_Data = 0 and Max_Data = 7. */
} SAIEx_PdmMicDelayParamTypeDef;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/** @addtogroup SAIEx_Exported_Functions SAIEx Extended Exported Functions
  * @{
  */

/** @addtogroup SAIEx_Exported_Functions_Group1 Peripheral Control functions
  * @{
  */
HAL_StatusTypeDef HAL_SAIEx_ConfigPdmMicDelay(const SAI_HandleTypeDef *hsai,
                                              const SAIEx_PdmMicDelayParamTypeDef *pdmMicDelay);
/**
  * @}
  */

/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @addtogroup SAIEx_Private_Macros SAIEx Extended Private Macros
  * @{
  */
#define IS_SAI_PDM_MIC_DELAY(VALUE)   ((VALUE) <= 7U)
/**
  * @}
  */

/**
  * @}
  */
#endif /* SAI1 */
/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* STM32WBAxx_HAL_SAI_EX_H */

