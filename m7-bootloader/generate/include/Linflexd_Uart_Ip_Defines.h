/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : LINFLEXD
*   Dependencies         : 
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 1.0.0
*   Build Version        : S32_RTD_1_0_0_D2012_ASR_REL_4_4_REV_0000_20201222
*
*   (c) Copyright 2020 NXP Semiconductors
*   All Rights Reserved.
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef LINFLEXD_UART_IP_DEFINES_H
#define LINFLEXD_UART_IP_DEFINES_H

/**
*   @file
*   @defgroup linflexd_uart_ip Linflexd UART IPL
*   @addtogroup  linflexd_uart_ip Linflexd UART IPL
*   @{
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
* 4) user callback header files
==================================================================================================*/
#include "S32G274A_LINFLEXD.h"
#include "Mcal.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define LINFLEXD_UART_IP_DEFINES_VENDOR_ID                     43
#define LINFLEXD_UART_IP_DEFINES_AR_RELEASE_MAJOR_VERSION      4
#define LINFLEXD_UART_IP_DEFINES_AR_RELEASE_MINOR_VERSION      4
#define LINFLEXD_UART_IP_DEFINES_AR_RELEASE_REVISION_VERSION   0
#define LINFLEXD_UART_IP_DEFINES_SW_MAJOR_VERSION              1
#define LINFLEXD_UART_IP_DEFINES_SW_MINOR_VERSION              0
#define LINFLEXD_UART_IP_DEFINES_SW_PATCH_VERSION              0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
 *                                     DEFINES AND MACROS
==================================================================================================*/
/* @brief Development error detection */
#define LINFLEXD_UART_DEV_ERROR_DETECT          (STD_OFF)

/* @brief Number of available hardware instances */
#define LINFLEXD_UART_IP_NUMBER_OF_INSTANCES    (1U)

/* @brief Uart Osif source counter. This parameter is used to select between different OsIf counter implementation */
#define LINFLEXD_UART_IP_TIMEOUT_TYPE           (OSIF_COUNTER_DUMMY)

/* @brief Number of loops before returning STATUS_TIMEOUT.*/
#define LINFLEXD_UART_TIMEOUT_VALUE_US          (0)

/* @brief LINFLEXD rx/tx/error interrupt lines ored toghether. */
#define FEATURE_LINFLEXD_ORED_INT_LINES         (1U)

/* @brief Address of the least significant byte in a 32-bit register (depends on endianness) */
#define FEATURE_LINFLEXD_LSB_ADDR(reg)          ((uint32)(&(reg)))

/* @brief Address of the least significant word in a 32-bit register (depends on endianness) */
#define FEATURE_LINFLEXD_LSW_ADDR(reg)          ((uint32)(&(reg)))

/* @brief LINFlexD DMA support */
#define LINFLEXD_UART_HAS_DMA_ENABLED           (STD_OFF)

/* @brief LINFLEXD UART instances configuration initialize value */
#define UART_CONFIGURATION_PTRS_FOR_INIT        {NULL_PTR,NULL_PTR,NULL_PTR}

/* @brief LINFLEXD UART configured instances configuration initialize value */
#define UART_INST_CONFIGURED_PTRS_FOR_INIT		{NULL_PTR}

/* @brief LINFLEXD UART instances state structure initialize value */
#define UART_STATE_STRUCTURE_PTRS_FOR_INIT		{NULL_PTR,NULL_PTR,NULL_PTR}

/* @brief LINFLEXD UART Hardware instances count initialize value */
#define UART_HW_CHANNELS_MAPPING_FOR_INIT       {-1,-1,-1}

/* @brief LINFlexD Usermode support */
#define LINFLEXD_UART_ENABLE_USER_MODE_SUPPORT  (STD_OFF)

/* @brief LINFLEXD DMA enabled instances */
#define FEATURE_LINFLEXD_IP_INST_HAS_DMA        {TRUE,TRUE,TRUE}

/* @brief LINFLEXD Base instance list */
#define FEATURE_LINFLEXD_IP_SPECIFIC_BASE_PTR	{LINFLEXD_0,LINFLEXD_1,LINFLEXD_2}

#if ((STD_ON == LINFLEXD_UART_ENABLE_USER_MODE_SUPPORT) && defined(MCAL_LINFLEX_REG_PROT_AVAILABLE) && (STD_ON == MCAL_LINFLEX_REG_PROT_AVAILABLE))
    #define LINFLEXD_SET_USER_ACCESS_ALLOWED_AVAILABLE      (STD_ON)
#else
    #define LINFLEXD_SET_USER_ACCESS_ALLOWED_AVAILABLE      (STD_OFF)
#endif
/*==================================================================================================
*                                            ENUMS
==================================================================================================*/

/*==================================================================================================
*                               STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/



#ifdef __cplusplus
}
#endif

/** @} */

#endif /* LINFLEXD_UART_IP_DEFINES_H */

