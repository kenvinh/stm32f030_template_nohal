/**
  ******************************************************************************
  * File Name          : rcc.h
  * Description        : This file contains all the functions prototypes for 
  *                      the system clock
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GPIO_H
#define __GPIO_H

/*******************************************************************************
 * Includes
*******************************************************************************/
#include "stm32f0xx.h"
#include "driver_config.h"

/*******************************************************************************
 * Macro definition
*******************************************************************************/

/*
 * GPIOx_MODER
*/
#define GPIO_MODER_MODE_INPUT           (uint32_t)(0x00000000U)
#define GPIO_MODER_MODE_OUTPUT          (uint32_t)(0x00000001U)
#define GPIO_MODER_MODE_ALTERNATE       (uint32_t)(0x00000002U)
#define GPIO_MODER_MODE_ANALOG          (uint32_t)(0x00000003U)        

#define GPIO_INT_MODER_MASK_INPUT       (uint32_t)(0x00000000U)
#define GPIO_INT_MODER_MASK_OUTPUT      (uint32_t)(0x55555555U)
#define GPIO_INT_MODER_MASK_ALTERNATE   (uint32_t)(0xAAAAAAAAU)
#define GPIO_INT_MODER_MASK_ANALOG      (uint32_t)(0xFFFFFFFFU)

/*
 * GPIOx_OTYPER
*/
#define GPIO_OTYPER_OUTPUT_PUSHPULL     (uint32_t)(0x00000000U)
#define GPIO_OTYPER_OUTPUT_OPENDRAIN    (uint32_t)(0x00000001U)        

#define GPIO_INT_OTYPER_MASK_PUSHPULL   (uint32_t)(0x00000000U)
#define GPIO_INT_OTYPER_MASK_OPENDRAIN  (uint32_t)(0x0000FFFFU)
/*
 * GPIOx_OSPEEDR
*/
#define GPIO_OSPEER_SPEED_LOW           (uint32_t)(0x00000000U)
#define GPIO_OSPEER_SPEED_MEDIUM        (uint32_t)(0x00000001U)
#define GPIO_OSPEER_SPEED_HIGH          (uint32_t)(0x00000003U)  

#define GPIO_INT_OSPEEDR_MASK_LOW       (uint32_t)(0x00000000U)
#define GPIO_INT_OSPEEDR_MASK_MEDIUM    (uint32_t)(0x55555555U)
#define GPIO_INT_OSPEEDR_MASK_HIGH      (uint32_t)(0xFFFFFFFFU)

/*
 * GPIOx_PUPDR
*/
#define GPIO_PUPDR_PULL_NONE            (uint32_t)(0x00000000U)
#define GPIO_PUPDR_PULL_UP              (uint32_t)(0x00000001U)
#define GPIO_PUPDR_PULL_DOWN            (uint32_t)(0x00000002U)

#define GPIO_INT_PUPDR_MASK_NONE        (uint32_t)(0x00000000U)
#define GPIO_INT_PUPDR_MASK_PULL_UP     (uint32_t)(0x55555555U)
#define GPIO_INT_PUPDR_MASK_PULL_DOWN   (uint32_t)(0xAAAAAAAAU)

/*
 * GPIOx_AFRx
*/
#define GPIO_AFR_ALTERNATE_FUNC0        (uint32_t)(0x00000000U)
#define GPIO_AFR_ALTERNATE_FUNC1        (uint32_t)(0x00000001U)
#define GPIO_AFR_ALTERNATE_FUNC2        (uint32_t)(0x00000002U)
#define GPIO_AFR_ALTERNATE_FUNC3        (uint32_t)(0x00000003U)
#define GPIO_AFR_ALTERNATE_FUNC4        (uint32_t)(0x00000004U)
#define GPIO_AFR_ALTERNATE_FUNC5        (uint32_t)(0x00000005U)
#define GPIO_AFR_ALTERNATE_FUNC6        (uint32_t)(0x00000006U)
#define GPIO_AFR_ALTERNATE_FUNC7        (uint32_t)(0x00000007U)

#define GPIO_INT_AFR_MASK_FUNC0         (uint32_t)(0x00000000U)
#define GPIO_INT_AFR_MASK_FUNC1         (uint32_t)(0x11111111U)
#define GPIO_INT_AFR_MASK_FUNC2         (uint32_t)(0x22222222U)
#define GPIO_INT_AFR_MASK_FUNC3         (uint32_t)(0x33333333U)
#define GPIO_INT_AFR_MASK_FUNC4         (uint32_t)(0x44444444U)
#define GPIO_INT_AFR_MASK_FUNC5         (uint32_t)(0x55555555U)
#define GPIO_INT_AFR_MASK_FUNC6         (uint32_t)(0x66666666U)
#define GPIO_INT_AFR_MASK_FUNC7         (uint32_t)(0x77777777U)

/*
 * Pin definition
*/
#define GPIO_PIN_00                    (uint16_t)(0x0001U)
#define GPIO_PIN_01                    (uint16_t)(0x0002U)
#define GPIO_PIN_02                    (uint16_t)(0x0004U)
#define GPIO_PIN_03                    (uint16_t)(0x0008U)
#define GPIO_PIN_04                    (uint16_t)(0x0010U)
#define GPIO_PIN_05                    (uint16_t)(0x0020U)
#define GPIO_PIN_06                    (uint16_t)(0x0040U)
#define GPIO_PIN_07                    (uint16_t)(0x0080U)
#define GPIO_PIN_08                    (uint16_t)(0x0100U)
#define GPIO_PIN_09                    (uint16_t)(0x0200U)
#define GPIO_PIN_10                    (uint16_t)(0x0400U)
#define GPIO_PIN_11                    (uint16_t)(0x0800U)
#define GPIO_PIN_12                    (uint16_t)(0x1000U)
#define GPIO_PIN_13                    (uint16_t)(0x2000U)
#define GPIO_PIN_14                    (uint16_t)(0x4000U)
#define GPIO_PIN_15                    (uint16_t)(0x8000U)

/*******************************************************************************
 * Type definition
*******************************************************************************/

/*******************************************************************************
 * Export variables
*******************************************************************************/

/*******************************************************************************
 * Macro function
*******************************************************************************/
#define GPIO_GET_2BIT_REGISTER_MASK(pins)           (\
                                                        (((pins) & GPIO_PIN_00) ? 0x00000003U : 0) | \
                                                        (((pins) & GPIO_PIN_01) ? 0x0000000CU : 0) | \
                                                        (((pins) & GPIO_PIN_02) ? 0x00000030U : 0) | \
                                                        (((pins) & GPIO_PIN_03) ? 0x000000C0U : 0) | \
                                                        (((pins) & GPIO_PIN_04) ? 0x00000300U : 0) | \
                                                        (((pins) & GPIO_PIN_05) ? 0x00000C00U : 0) | \
                                                        (((pins) & GPIO_PIN_06) ? 0x00003000U : 0) | \
                                                        (((pins) & GPIO_PIN_07) ? 0x0000C000U : 0) | \
                                                        (((pins) & GPIO_PIN_08) ? 0x00030000U : 0) | \
                                                        (((pins) & GPIO_PIN_09) ? 0x000C0000U : 0) | \
                                                        (((pins) & GPIO_PIN_10) ? 0x00300000U : 0) | \
                                                        (((pins) & GPIO_PIN_11) ? 0x00C00000U : 0) | \
                                                        (((pins) & GPIO_PIN_12) ? 0x03000000U : 0) | \
                                                        (((pins) & GPIO_PIN_13) ? 0x0C000000U : 0) | \
                                                        (((pins) & GPIO_PIN_14) ? 0x30000000U : 0) | \
                                                        (((pins) & GPIO_PIN_15) ? 0xC0000000U : 0) )

#define GPIO_GET_4BIT_REGISTER_MASK(pins)           (\
                                                        (((pins) & GPIO_PIN_00) ? 0x0000000FU : 0) | \
                                                        (((pins) & GPIO_PIN_01) ? 0x000000F0U : 0) | \
                                                        (((pins) & GPIO_PIN_02) ? 0x00000F00U : 0) | \
                                                        (((pins) & GPIO_PIN_03) ? 0x0000F000U : 0) | \
                                                        (((pins) & GPIO_PIN_04) ? 0x000F0000U : 0) | \
                                                        (((pins) & GPIO_PIN_05) ? 0x00F00000U : 0) | \
                                                        (((pins) & GPIO_PIN_06) ? 0x0F000000U : 0) | \
                                                        (((pins) & GPIO_PIN_07) ? 0xF0000000U : 0) | \
                                                        (((pins) & GPIO_PIN_08) ? 0x0000000FU : 0) | \
                                                        (((pins) & GPIO_PIN_09) ? 0x000000F0U : 0) | \
                                                        (((pins) & GPIO_PIN_10) ? 0x00000F00U : 0) | \
                                                        (((pins) & GPIO_PIN_11) ? 0x0000F000U : 0) | \
                                                        (((pins) & GPIO_PIN_12) ? 0x000F0000U : 0) | \
                                                        (((pins) & GPIO_PIN_13) ? 0x00F00000U : 0) | \
                                                        (((pins) & GPIO_PIN_14) ? 0x0F000000U : 0) | \
                                                        (((pins) & GPIO_PIN_15) ? 0xF0000000U : 0) )


#define GPIO_MODER_SET_VALUE(gpio, pins, value)     {\
                                                        uint32_t mask;\
                                                        uint32_t set_value;\
                                                        mask = GPIO_GET_2BIT_REGISTER_MASK(pins);\
                                                        gpio->MODER &= ~mask;\
                                                        set_value = mask & \
                                                                 (\
                                                                    (value == GPIO_MODER_MODE_INPUT)    ? GPIO_INT_MODER_MASK_INPUT : (\
                                                                    (value == GPIO_MODER_MODE_OUTPUT)   ? GPIO_INT_MODER_MASK_OUTPUT : (\
                                                                    (value == GPIO_MODER_MODE_ALTERNATE)? GPIO_INT_MODER_MASK_ALTERNATE : (\
                                                                    (value == GPIO_MODER_MODE_ANALOG)   ? GPIO_INT_MODER_MASK_ANALOG : 0 \
                                                                 ))));\
                                                        gpio->MODER |= set_value;\
                                                    }

#define GPIO_OTYPER_SET_VALUE(gpio, pins, value)    {\
                                                        uint32_t mask;\
                                                        uint32_t set_value;\
                                                        mask = (uint32_t)(pins);\
                                                        gpio->OTYPER &= ~mask;\
                                                        set_value = mask & \
                                                                 (\
                                                                    (value == GPIO_OTYPER_OUTPUT_PUSHPULL)    ? GPIO_INT_OTYPER_MASK_PUSHPULL : (\
                                                                    (value == GPIO_OTYPER_OUTPUT_OPENDRAIN)   ? GPIO_INT_OTYPER_MASK_OPENDRAIN : 0\
                                                                 ));\
                                                        gpio->OTYPER |= set_value;\
                                                    }

#define GPIO_OSPEEDR_SET_VALUE(gpio, pins, value)   {\
                                                        uint32_t mask;\
                                                        uint32_t set_value;\
                                                        mask = GPIO_GET_2BIT_REGISTER_MASK(pins);\
                                                        gpio->OSPEEDR &= ~mask;\
                                                        set_value = mask & \
                                                                 (\
                                                                    (value == GPIO_OSPEER_SPEED_LOW)        ? GPIO_INT_OSPEEDR_MASK_LOW : (\
                                                                    (value == GPIO_OSPEER_SPEED_MEDIUM)     ? GPIO_INT_OSPEEDR_MASK_MEDIUM : (\
                                                                    (value == GPIO_OSPEER_SPEED_HIGH)       ? GPIO_INT_OSPEEDR_MASK_HIGH : 0 \
                                                                 )));\
                                                        gpio->OSPEEDR |= set_value;\
                                                    }

#define GPIO_PUPDR_SET_VALUE(gpio, pins, value)     {\
                                                        uint32_t mask;\
                                                        uint32_t set_value;\
                                                        mask = GPIO_GET_2BIT_REGISTER_MASK(pins);\
                                                        gpio->PUPDR &= ~mask;\
                                                        set_value = mask & \
                                                                 (\
                                                                    (value == GPIO_PUPDR_PULL_NONE)         ? GPIO_INT_PUPDR_MASK_NONE : (\
                                                                    (value == GPIO_PUPDR_PULL_UP)           ? GPIO_INT_PUPDR_MASK_PULL_UP : (\
                                                                    (value == GPIO_PUPDR_PULL_DOWN)         ? GPIO_INT_PUPDR_MASK_PULL_DOWN : 0 \
                                                                 )));\
                                                        gpio->PUPDR |= set_value;\
                                                    }

#define GPIO_AFR_SET_VALUE(gpio, pins, value)       {\
                                                        uint32_t mask;\
                                                        uint32_t set_value;\
                                                        mask = GPIO_GET_4BIT_REGISTER_MASK(((pins)&0x00FF));\
                                                        gpio->AFR[0] &= ~mask;\
                                                        set_value = mask & \
                                                                 (\
                                                                    (value == GPIO_AFR_ALTERNATE_FUNC0)     ? GPIO_INT_AFR_MASK_FUNC0 : (\
                                                                    (value == GPIO_AFR_ALTERNATE_FUNC1)     ? GPIO_INT_AFR_MASK_FUNC1 : (\
                                                                    (value == GPIO_AFR_ALTERNATE_FUNC2)     ? GPIO_INT_AFR_MASK_FUNC2 : (\
                                                                    (value == GPIO_AFR_ALTERNATE_FUNC3)     ? GPIO_INT_AFR_MASK_FUNC3 : (\
                                                                    (value == GPIO_AFR_ALTERNATE_FUNC4)     ? GPIO_INT_AFR_MASK_FUNC4 : (\
                                                                    (value == GPIO_AFR_ALTERNATE_FUNC5)     ? GPIO_INT_AFR_MASK_FUNC5 : (\
                                                                    (value == GPIO_AFR_ALTERNATE_FUNC6)     ? GPIO_INT_AFR_MASK_FUNC6 : (\
                                                                    (value == GPIO_AFR_ALTERNATE_FUNC7)     ? GPIO_INT_AFR_MASK_FUNC7 : 0 \
                                                                 ))))))));\
                                                        gpio->AFR[0] |= set_value;\
                                                        mask = GPIO_GET_4BIT_REGISTER_MASK((((pins)&0xFF00)>>8));\
                                                        gpio->AFR[1] &= ~mask;\
                                                        set_value = mask & \
                                                                 (\
                                                                    (value == GPIO_AFR_ALTERNATE_FUNC0)     ? GPIO_INT_AFR_MASK_FUNC0 : (\
                                                                    (value == GPIO_AFR_ALTERNATE_FUNC1)     ? GPIO_INT_AFR_MASK_FUNC1 : (\
                                                                    (value == GPIO_AFR_ALTERNATE_FUNC2)     ? GPIO_INT_AFR_MASK_FUNC2 : (\
                                                                    (value == GPIO_AFR_ALTERNATE_FUNC3)     ? GPIO_INT_AFR_MASK_FUNC3 : (\
                                                                    (value == GPIO_AFR_ALTERNATE_FUNC4)     ? GPIO_INT_AFR_MASK_FUNC4 : (\
                                                                    (value == GPIO_AFR_ALTERNATE_FUNC5)     ? GPIO_INT_AFR_MASK_FUNC5 : (\
                                                                    (value == GPIO_AFR_ALTERNATE_FUNC6)     ? GPIO_INT_AFR_MASK_FUNC6 : (\
                                                                    (value == GPIO_AFR_ALTERNATE_FUNC7)     ? GPIO_INT_AFR_MASK_FUNC7 : 0 \
                                                                 ))))))));\
                                                        gpio->AFR[1] |= set_value;\
                                                    }

#define GPIO_DIRECT_OUTPUT_HIGH(gpio, pins)         (gpio->BSRR = pins)    
#define GPIO_DIRECT_OUTPUT_LOW(gpio, pins)          (gpio->BRR = pins)


/*******************************************************************************
 * Function Prototypes
*******************************************************************************/
uint8_t GPIO_Init(void);

#endif /* __GPIO_H */