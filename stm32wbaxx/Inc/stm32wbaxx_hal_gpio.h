/**
  ******************************************************************************
  * @file    stm32wbaxx_hal_gpio.h
  * @author  MCD Application Team
  * @brief   Header file of GPIO HAL module.
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
#ifndef STM32WBAxx_HAL_GPIO_H
#define STM32WBAxx_HAL_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32wbaxx_hal_def.h"

/** @addtogroup STM32WBAxx_HAL_Driver
  * @{
  */

/** @defgroup GPIO GPIO
  * @brief GPIO HAL module driver
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup GPIO_Exported_Types GPIO Exported Types
  * @{
  */
/**
  * @brief   GPIO Init structure definition
  */
typedef struct
{
  uint32_t Pin;        /*!< Specifies the GPIO pins to be configured.
                            This parameter can be any value of @ref GPIO_pins */

  uint32_t Mode;       /*!< Specifies the operating mode for the selected pins.
                            This parameter can be a value of @ref GPIO_mode */

  uint32_t Pull;       /*!< Specifies the Pull-up or Pull-Down activation for the selected pins.
                            This parameter can be a value of @ref GPIO_pull */

  uint32_t Speed;      /*!< Specifies the speed for the selected pins.
                            This parameter can be a value of @ref GPIO_speed */

  uint32_t Alternate;  /*!< Peripheral to be connected to the selected pins
                            This parameter can be a value of @ref GPIOEx_Alternate_function_selection */
} GPIO_InitTypeDef;

/**
  * @brief  GPIO Bit SET and Bit RESET enumeration
  */
typedef enum
{
  GPIO_PIN_RESET = 0U,
  GPIO_PIN_SET
} GPIO_PinState;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup GPIO_Exported_Constants GPIO Exported Constants
  * @{
  */
/** @defgroup GPIO_pins GPIO pins
  * @{
  */
#define GPIO_PIN_0                      ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                      ((uint16_t)0x0002)  /* Pin 1 selected    */
#define GPIO_PIN_2                      ((uint16_t)0x0004)  /* Pin 2 selected    */
#define GPIO_PIN_3                      ((uint16_t)0x0008)  /* Pin 3 selected    */
#define GPIO_PIN_4                      ((uint16_t)0x0010)  /* Pin 4 selected    */
#define GPIO_PIN_5                      ((uint16_t)0x0020)  /* Pin 5 selected    */
#define GPIO_PIN_6                      ((uint16_t)0x0040)  /* Pin 6 selected    */
#define GPIO_PIN_7                      ((uint16_t)0x0080)  /* Pin 7 selected    */
#define GPIO_PIN_8                      ((uint16_t)0x0100)  /* Pin 8 selected    */
#define GPIO_PIN_9                      ((uint16_t)0x0200)  /* Pin 9 selected    */
#define GPIO_PIN_10                     ((uint16_t)0x0400)  /* Pin 10 selected   */
#define GPIO_PIN_11                     ((uint16_t)0x0800)  /* Pin 11 selected   */
#define GPIO_PIN_12                     ((uint16_t)0x1000)  /* Pin 12 selected   */
#define GPIO_PIN_13                     ((uint16_t)0x2000)  /* Pin 13 selected   */
#define GPIO_PIN_14                     ((uint16_t)0x4000)  /* Pin 14 selected   */
#define GPIO_PIN_15                     ((uint16_t)0x8000)  /* Pin 15 selected   */
#define GPIO_PIN_All                    ((uint16_t)0xFFFF)  /* All pins selected */

#define GPIO_PIN_MASK                   (0x0000FFFFu) /* PIN mask for assert test */
/**
  * @}
  */

/** @defgroup GPIO_mode GPIO mode
  * @brief GPIO Configuration Mode
  *        Elements values convention: 0x00WX00YZ
  *           - W  : EXTI trigger detection on 3 bits
  *           - X  : EXTI mode (IT or Event) on 2 bits
  *           - Y  : Output type (Push Pull or Open Drain) on 1 bit
  *           - Z  : GPIO mode (Input, Output, Alternate or Analog) on 2 bits
  * @{
  */
#define GPIO_MODE_INPUT                 MODE_INPUT                                                  /*!< Input Floating Mode                                                */
#define GPIO_MODE_OUTPUT_PP             (MODE_OUTPUT | OUTPUT_PP)                                   /*!< Output Push Pull Mode                                              */
#define GPIO_MODE_OUTPUT_OD             (MODE_OUTPUT | OUTPUT_OD)                                   /*!< Output Open Drain Mode                                             */
#define GPIO_MODE_AF_PP                 (MODE_AF | OUTPUT_PP)                                       /*!< Alternate Function Push Pull Mode                                  */
#define GPIO_MODE_AF_OD                 (MODE_AF | OUTPUT_OD)                                       /*!< Alternate Function Open Drain Mode                                 */
#define GPIO_MODE_ANALOG                MODE_ANALOG                                                 /*!< Analog Mode                                                        */
#define GPIO_MODE_IT_RISING             (MODE_INPUT | EXTI_IT | TRIGGER_RISING)                     /*!< External Interrupt Mode with Rising edge trigger detection         */
#define GPIO_MODE_IT_FALLING            (MODE_INPUT | EXTI_IT | TRIGGER_FALLING)                    /*!< External Interrupt Mode with Falling edge trigger detection        */
#define GPIO_MODE_IT_RISING_FALLING     (MODE_INPUT | EXTI_IT | TRIGGER_RISING | TRIGGER_FALLING)   /*!< External Interrupt Mode with Rising/Falling edge trigger detection */
#define GPIO_MODE_EVT_RISING            (MODE_INPUT | EXTI_EVT | TRIGGER_RISING)                    /*!< External Event Mode with Rising edge trigger detection             */
#define GPIO_MODE_EVT_FALLING           (MODE_INPUT | EXTI_EVT | TRIGGER_FALLING)                   /*!< External Event Mode with Falling edge trigger detection            */
#define GPIO_MODE_EVT_RISING_FALLING    (MODE_INPUT | EXTI_EVT | TRIGGER_RISING | TRIGGER_FALLING)  /*!< External Event Mode with Rising/Falling edge trigger detection     */
/**
  * @}
  */

/** @defgroup GPIO_speed GPIO speed
  * @brief GPIO Output Maximum frequency
  * @{
  */
#define GPIO_SPEED_FREQ_LOW             0x00000000u  /*!< Low speed       */
#define GPIO_SPEED_FREQ_MEDIUM          0x00000001u  /*!< Medium speed    */
#define GPIO_SPEED_FREQ_HIGH            0x00000002u  /*!< High speed      */
/**
  * @}
  */

/** @defgroup GPIO_pull GPIO pull
  * @brief GPIO Pull-Up or Pull-Down Activation
  * @{
  */
#define GPIO_NOPULL                     0x00000000u   /*!< No Pull-up or Pull-down activation  */
#define GPIO_PULLUP                     0x00000001u   /*!< Pull-up activation                  */
#define GPIO_PULLDOWN                   0x00000002u   /*!< Pull-down activation                */
/**
  * @}
  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

/** @defgroup GPIO_attributes GPIO attributes
  * @brief GPIO pin secure or non-secure attributes
  * @{
  */
#define  GPIO_PIN_SEC       (0x00000001U)   /*!< Secure pin attribute      */
#define  GPIO_PIN_NSEC      (0x00000000U)   /*!< Non-secure pin attribute  */
/**
  * @}
  */

#endif /* __ARM_FEATURE_CMSE */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup GPIO_Exported_Macros GPIO Exported Macros
  * @{
  */

/**
  * @brief  Check whether the specified EXTI line is rising edge asserted or not.
  * @param  __EXTI_LINE__ specifies the EXTI line to check.
  *          This parameter can be GPIO_PIN_x where x can be(0..15)
  * @retval The new state of __EXTI_LINE__ (SET or RESET).
  */
#define __HAL_GPIO_EXTI_GET_RISING_IT(__EXTI_LINE__)         (EXTI->RPR1 & (__EXTI_LINE__))

/**
  * @brief  Clear the EXTI line rising pending bits.
  * @param  __EXTI_LINE__ specifies the EXTI lines to clear.
  *          This parameter can be any combination of GPIO_PIN_x where x can be (0..15)
  * @retval None
  */
#define __HAL_GPIO_EXTI_CLEAR_RISING_IT(__EXTI_LINE__)       (EXTI->RPR1 = (__EXTI_LINE__))

/**
  * @brief  Check whether the specified EXTI line is falling edge asserted or not.
  * @param  __EXTI_LINE__ specifies the EXTI line to check.
  *          This parameter can be GPIO_PIN_x where x can be(0..15)
  * @retval The new state of __EXTI_LINE__ (SET or RESET).
  */
#define __HAL_GPIO_EXTI_GET_FALLING_IT(__EXTI_LINE__)        (EXTI->FPR1 & (__EXTI_LINE__))

/**
  * @brief  Clear the EXTI line falling pending bits.
  * @param  __EXTI_LINE__ specifies the EXTI lines to clear.
  *          This parameter can be any combination of GPIO_PIN_x where x can be (0..15)
  * @retval None
  */
#define __HAL_GPIO_EXTI_CLEAR_FALLING_IT(__EXTI_LINE__)      (EXTI->FPR1 = (__EXTI_LINE__))

/**
  * @brief  Check whether the specified EXTI line is asserted or not.
  * @param __EXTI_LINE__ specifies the EXTI line to check.
  *          This parameter can be GPIO_PIN_x where x can be(0..15)
  * @retval The new state of __EXTI_LINE__ (SET or RESET).
  */
#define __HAL_GPIO_EXTI_GET_IT(__EXTI_LINE__)         (__HAL_GPIO_EXTI_GET_RISING_IT(__EXTI_LINE__) || \
                                                       __HAL_GPIO_EXTI_GET_FALLING_IT(__EXTI_LINE__))

/**
  * @brief  Clear the EXTI's line pending bits.
  * @param  __EXTI_LINE__ specifies the EXTI lines to clear.
  *          This parameter can be any combination of GPIO_PIN_x where x can be (0..15)
  * @retval None
  */
#define __HAL_GPIO_EXTI_CLEAR_IT(__EXTI_LINE__)         \
  do {                                                  \
    __HAL_GPIO_EXTI_CLEAR_RISING_IT(__EXTI_LINE__);     \
    __HAL_GPIO_EXTI_CLEAR_FALLING_IT(__EXTI_LINE__);    \
  } while(0)


/**
  * @brief  Generate a Software interrupt on selected EXTI line(s).
  * @param  __EXTI_LINE__ specifies the EXTI line to be set.
  *          This parameter can be any combination of GPIO_PIN_x where x can be (0..15)
  * @retval None
  */
#define __HAL_GPIO_EXTI_GENERATE_SWIT(__EXTI_LINE__)  (EXTI->SWIER1 = (__EXTI_LINE__))
/**
  * @}
  */

/* Private macros ------------------------------------------------------------*/
/** @defgroup GPIO_Private_Constants GPIO Private Constants
  * @{
  */
#define GPIO_MODE_Pos                           0u
#define GPIO_MODE                               (0x3uL << GPIO_MODE_Pos)
#define MODE_INPUT                              (0x0uL << GPIO_MODE_Pos)
#define MODE_OUTPUT                             (0x1uL << GPIO_MODE_Pos)
#define MODE_AF                                 (0x2uL << GPIO_MODE_Pos)
#define MODE_ANALOG                             (0x3uL << GPIO_MODE_Pos)
#define OUTPUT_TYPE_Pos                         4u
#define OUTPUT_TYPE                             (0x1uL << OUTPUT_TYPE_Pos)
#define OUTPUT_PP                               (0x0uL << OUTPUT_TYPE_Pos)
#define OUTPUT_OD                               (0x1uL << OUTPUT_TYPE_Pos)
#define EXTI_MODE_Pos                           16u
#define EXTI_MODE                               (0x3uL << EXTI_MODE_Pos)
#define EXTI_IT                                 (0x1uL << EXTI_MODE_Pos)
#define EXTI_EVT                                (0x2uL << EXTI_MODE_Pos)
#define TRIGGER_MODE_Pos                         20u
#define TRIGGER_MODE                            (0x7uL << TRIGGER_MODE_Pos)
#define TRIGGER_RISING                          (0x1uL << TRIGGER_MODE_Pos)
#define TRIGGER_FALLING                         (0x2uL << TRIGGER_MODE_Pos)
/**
  * @}
  */

/** @defgroup GPIO_Private_Macros GPIO Private Macros
  * @{
  */
#define IS_GPIO_PIN_ACTION(ACTION)  (((ACTION) == GPIO_PIN_RESET) || ((ACTION) == GPIO_PIN_SET))

#define IS_GPIO_PIN(__PIN__)        ((((uint32_t)(__PIN__) & GPIO_PIN_MASK) != 0x00u) &&\
                                     (((uint32_t)(__PIN__) & ~GPIO_PIN_MASK) == 0x00u))

#define IS_GPIO_SINGLE_PIN(__PIN__) (((__PIN__) == GPIO_PIN_0)   ||\
                                     ((__PIN__) == GPIO_PIN_1)   ||\
                                     ((__PIN__) == GPIO_PIN_2)   ||\
                                     ((__PIN__) == GPIO_PIN_3)   ||\
                                     ((__PIN__) == GPIO_PIN_4)   ||\
                                     ((__PIN__) == GPIO_PIN_5)   ||\
                                     ((__PIN__) == GPIO_PIN_6)   ||\
                                     ((__PIN__) == GPIO_PIN_7)   ||\
                                     ((__PIN__) == GPIO_PIN_8)   ||\
                                     ((__PIN__) == GPIO_PIN_9)   ||\
                                     ((__PIN__) == GPIO_PIN_10)  ||\
                                     ((__PIN__) == GPIO_PIN_11)  ||\
                                     ((__PIN__) == GPIO_PIN_12)  ||\
                                     ((__PIN__) == GPIO_PIN_13)  ||\
                                     ((__PIN__) == GPIO_PIN_14)  ||\
                                     ((__PIN__) == GPIO_PIN_15))

#define IS_GPIO_COMMON_PIN(__RESETMASK__, __SETMASK__)   \
  (((uint32_t)(__RESETMASK__) & (uint32_t)(__SETMASK__)) == 0x00u)

#define IS_GPIO_MODE(__MODE__)      (((__MODE__) == GPIO_MODE_INPUT)              ||\
                                     ((__MODE__) == GPIO_MODE_OUTPUT_PP)          ||\
                                     ((__MODE__) == GPIO_MODE_OUTPUT_OD)          ||\
                                     ((__MODE__) == GPIO_MODE_AF_PP)              ||\
                                     ((__MODE__) == GPIO_MODE_AF_OD)              ||\
                                     ((__MODE__) == GPIO_MODE_IT_RISING)          ||\
                                     ((__MODE__) == GPIO_MODE_IT_FALLING)         ||\
                                     ((__MODE__) == GPIO_MODE_IT_RISING_FALLING)  ||\
                                     ((__MODE__) == GPIO_MODE_EVT_RISING)         ||\
                                     ((__MODE__) == GPIO_MODE_EVT_FALLING)        ||\
                                     ((__MODE__) == GPIO_MODE_EVT_RISING_FALLING) ||\
                                     ((__MODE__) == GPIO_MODE_ANALOG))

#define IS_GPIO_SPEED(__SPEED__)    (((__SPEED__) == GPIO_SPEED_FREQ_LOW)    ||\
                                     ((__SPEED__) == GPIO_SPEED_FREQ_MEDIUM) ||\
                                     ((__SPEED__) == GPIO_SPEED_FREQ_HIGH))

#define IS_GPIO_PULL(__PULL__)      (((__PULL__) == GPIO_NOPULL)   ||\
                                     ((__PULL__) == GPIO_PULLUP)   || \
                                     ((__PULL__) == GPIO_PULLDOWN))

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

#define IS_GPIO_PIN_ATTRIBUTES(__ATTRIBUTES__)  (((__ATTRIBUTES__) == GPIO_PIN_SEC)  ||\
                                                 ((__ATTRIBUTES__) == GPIO_PIN_NSEC))

#endif /* __ARM_FEATURE_CMSE */

/* Include GPIO HAL Extended module */
#include "stm32wbaxx_hal_gpio_ex.h"

/* Exported functions --------------------------------------------------------*/
/** @defgroup GPIO_Exported_Functions GPIO Exported Functions
  *  @brief    GPIO Exported Functions
  * @{
  */

/** @defgroup GPIO_Exported_Functions_Group1 Initialization/de-initialization functions
  *  @brief    Initialization and Configuration functions
  * @{
  */

/* Initialization and de-initialization functions *****************************/
void              HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, const GPIO_InitTypeDef *GPIO_Init);
void              HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin);

/**
  * @}
  */

/** @defgroup GPIO_Exported_Functions_Group2 IO operation functions
  *  @brief    IO operation functions
  * @{
  */

/* IO operation functions *****************************************************/
GPIO_PinState     HAL_GPIO_ReadPin(const GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void              HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void              HAL_GPIO_WriteMultipleStatePin(GPIO_TypeDef *GPIOx, uint16_t PinReset, uint16_t PinSet);
void              HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
#if defined (STM32WBA62xx) || defined (STM32WBA63xx) || defined (STM32WBA64xx) || defined (STM32WBA65xx) || defined (STM32WBA6Mxx)
void              HAL_GPIO_EnableHighSPeedLowVoltage(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void              HAL_GPIO_DisableHighSPeedLowVoltage(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
#endif  /* defined (STM32WBA62xx) || defined (STM32WBA63xx) || defined (STM32WBA64xx) || defined (STM32WBA65xx) || defined (STM32WBA6Mxx) */
HAL_StatusTypeDef HAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin);
void              HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin);
void              HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin);
void              HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin);

/**
  * @}
  */

#if defined (__ARM_FEATURE_CMSE) && (__ARM_FEATURE_CMSE == 3U)

/** @defgroup GPIO_Exported_Functions_Group3 IO attributes management functions
  * @{
  */

/* IO attributes management functions *****************************************/
void              HAL_GPIO_ConfigPinAttributes(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t PinAttributes);
HAL_StatusTypeDef HAL_GPIO_GetConfigPinAttributes(const GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t *pPinAttributes);

/**
  * @}
  */

#endif /* __ARM_FEATURE_CMSE */

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

#endif /* STM32WBAxx_HAL_GPIO_H */

