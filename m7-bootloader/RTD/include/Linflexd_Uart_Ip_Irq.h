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

#ifndef LINFLEXD_UART_IP_IRQ_H
#define LINFLEXD_UART_IP_IRQ_H

/**
*   @file
*   @defgroup linflexd_uart_ip Linflexd UART IPL
*   @addtogroup  linflexd_uart_ip Linflexd UART IPL
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Linflexd_Uart_Ip_Defines.h"
#include "Linflexd_Uart_Ip_Cfg.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define LINFLEXD_UART_IP_IRQ_VENDOR_ID                    43
#define LINFLEXD_UART_IP_IRQ_MODULE_ID                    255
#define LINFLEXD_UART_IP_IRQ_AR_RELEASE_MAJOR_VERSION     4
#define LINFLEXD_UART_IP_IRQ_AR_RELEASE_MINOR_VERSION     4
#define LINFLEXD_UART_IP_IRQ_AR_RELEASE_REVISION_VERSION  0
#define LINFLEXD_UART_IP_IRQ_SW_MAJOR_VERSION             1
#define LINFLEXD_UART_IP_IRQ_SW_MINOR_VERSION             0
#define LINFLEXD_UART_IP_IRQ_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/
#define UART_START_SEC_CODE
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

#if (LINFLEXD_INSTANCE_COUNT > 0U)
#ifdef LinflexD_0
/* Implementation of LINFLEXD0 handler named in startup code. */
ISR(LINFLEXD0_UART_IRQHandler);
#endif
#endif

#if (LINFLEXD_INSTANCE_COUNT > 1U)
#ifdef LinflexD_1
/* Implementation of LINFLEXD1 handler named in startup code. */
ISR(LINFLEXD1_UART_IRQHandler);
#endif
#endif

#if (LINFLEXD_INSTANCE_COUNT > 2U)
#ifdef LinflexD_2
/* Implementation of LINFLEXD2 handler named in startup code. */
ISR(LINFLEXD2_UART_IRQHandler);
#endif
#endif
#if (LINFLEXD_UART_HAS_DMA_ENABLED == STD_ON)
#ifdef LinflexD_0
#if (LINFLEXD_INSTANCE_COUNT > 0U)
void Linflexd_0_Uart_Ip_DmaRxCompleteCallback(void);
void Linflexd_0_Uart_Ip_DmaTxCompleteCallback(void);
#endif
#endif
#if (LINFLEXD_INSTANCE_COUNT > 1U)
#ifdef LinflexD_1
void Linflexd_1_Uart_Ip_DmaRxCompleteCallback(void);
void Linflexd_1_Uart_Ip_DmaTxCompleteCallback(void);
#endif
#endif
#if (LINFLEXD_INSTANCE_COUNT > 2U)
#ifdef LinflexD_2
void Linflexd_2_Uart_Ip_DmaRxCompleteCallback(void);
void Linflexd_2_Uart_Ip_DmaTxCompleteCallback(void);
#endif
#endif
#endif
#ifdef __cplusplus
}
#endif

#define UART_STOP_SEC_CODE
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

/** @} */

#endif /* LINFLEXD_UART_IP_IRQ_H */
