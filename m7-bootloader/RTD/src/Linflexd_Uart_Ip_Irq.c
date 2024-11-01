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
#include "Linflexd_Uart_Ip.h"
#include "Linflexd_Uart_Ip_Irq.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define LINFLEXD_UART_IP_IRQ_VENDOR_ID_C                      43
#define LINFLEXD_UART_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C       4
#define LINFLEXD_UART_IP_IRQ_AR_RELEASE_MINOR_VERSION_C       4
#define LINFLEXD_UART_IP_IRQ_AR_RELEASE_REVISION_VERSION_C    0
#define LINFLEXD_UART_IP_IRQ_SW_MAJOR_VERSION_C               1
#define LINFLEXD_UART_IP_IRQ_SW_MINOR_VERSION_C               0
#define LINFLEXD_UART_IP_IRQ_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Linflexd_Uart_Ip.h */
#if (LINFLEXD_UART_IP_IRQ_VENDOR_ID_C != LINFLEXD_UART_IP_VENDOR_ID)
    #error "Linflexd_Uart_Ip_Irq.c and Linflexd_Uart_Ip.h have different vendor ids"
#endif
#if ((LINFLEXD_UART_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C    != LINFLEXD_UART_IP_AR_RELEASE_MAJOR_VERSION) || \
     (LINFLEXD_UART_IP_IRQ_AR_RELEASE_MINOR_VERSION_C    != LINFLEXD_UART_IP_AR_RELEASE_MINOR_VERSION) || \
     (LINFLEXD_UART_IP_IRQ_AR_RELEASE_REVISION_VERSION_C != LINFLEXD_UART_IP_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Linflexd_Uart_Ip_Irq.c and Linflexd_Uart_Ip.h are different"
#endif
#if ((LINFLEXD_UART_IP_IRQ_SW_MAJOR_VERSION_C != LINFLEXD_UART_IP_SW_MAJOR_VERSION) || \
     (LINFLEXD_UART_IP_IRQ_SW_MINOR_VERSION_C != LINFLEXD_UART_IP_SW_MINOR_VERSION) || \
     (LINFLEXD_UART_IP_IRQ_SW_PATCH_VERSION_C != LINFLEXD_UART_IP_SW_PATCH_VERSION))
    #error "Software Version Numbers of Linflexd_Uart_Ip_Irq.c and Linflexd_Uart_Ip.h are different"
#endif
/* Checks against Linflexd_Uart_Ip_Irq.h */
#if (LINFLEXD_UART_IP_IRQ_VENDOR_ID_C != LINFLEXD_UART_IP_IRQ_VENDOR_ID)
    #error "Linflexd_Uart_Ip_Irq.c and Linflexd_Uart_Ip_Irq.h have different vendor ids"
#endif
#if ((LINFLEXD_UART_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C    != LINFLEXD_UART_IP_IRQ_AR_RELEASE_MAJOR_VERSION) || \
     (LINFLEXD_UART_IP_IRQ_AR_RELEASE_MINOR_VERSION_C    != LINFLEXD_UART_IP_IRQ_AR_RELEASE_MINOR_VERSION) || \
     (LINFLEXD_UART_IP_IRQ_AR_RELEASE_REVISION_VERSION_C != LINFLEXD_UART_IP_IRQ_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Linflexd_Uart_Ip_Irq.c and Linflexd_Uart_Ip_Irq.h are different"
#endif
#if ((LINFLEXD_UART_IP_IRQ_SW_MAJOR_VERSION_C != LINFLEXD_UART_IP_IRQ_SW_MAJOR_VERSION) || \
     (LINFLEXD_UART_IP_IRQ_SW_MINOR_VERSION_C != LINFLEXD_UART_IP_IRQ_SW_MINOR_VERSION) || \
     (LINFLEXD_UART_IP_IRQ_SW_PATCH_VERSION_C != LINFLEXD_UART_IP_IRQ_SW_PATCH_VERSION))
    #error "Software Version Numbers of Linflexd_Uart_Ip_Irq.c and Linflexd_Uart_Ip_Irq.h are different"
#endif
/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/
#define UART_START_SEC_CODE
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

#if (LINFLEXD_INSTANCE_COUNT > 0U)
#ifdef LinflexD_0
/* Implementation of LINFLEXD0 handler named in startup code. */
ISR(LINFLEXD0_UART_IRQHandler)
{
    Linflexd_Uart_Ip_IRQHandler(0U);
}
#endif
#endif
#if (LINFLEXD_INSTANCE_COUNT > 1U)
#ifdef LinflexD_1
/* Implementation of LINFLEXD1 handler named in startup code. */
ISR(LINFLEXD1_UART_IRQHandler)
{
    Linflexd_Uart_Ip_IRQHandler(1U);
}
#endif
#endif
#if (LINFLEXD_INSTANCE_COUNT > 2U)
#ifdef LinflexD_2
/* Implementation of LINFLEXD2 handler named in startup code. */
ISR(LINFLEXD2_UART_IRQHandler)
{
    Linflexd_Uart_Ip_IRQHandler(2U);
}
#endif
#endif

#if (LINFLEXD_UART_HAS_DMA_ENABLED == STD_ON)
#if (LINFLEXD_INSTANCE_COUNT > 0U)
#ifdef LinflexD_0
/* Implementation of LINFlexD0 Tx callback function for Dma interrupt. */
void Linflexd_0_Uart_Ip_DmaTxCompleteCallback(void)
{
    Linflexd_Uart_Ip_CompleteSendUsingDma(LinflexD_0);
}
/* Implementation of LINFlexD0 Rx callback function for Dma interrupt. */
void Linflexd_0_Uart_Ip_DmaRxCompleteCallback(void)
{
    Linflexd_Uart_Ip_CompleteReceiveUsingDma(LinflexD_0);
}
#endif
#endif
#if (LINFLEXD_INSTANCE_COUNT > 1U)
#ifdef LinflexD_1
/* Implementation of LINFlexD1 Tx callback function for Dma interrupt. */
void Linflexd_1_Uart_Ip_DmaTxCompleteCallback(void)
{
    Linflexd_Uart_Ip_CompleteSendUsingDma(LinflexD_1);
}
/* Implementation of LINFlexD1 Rx callback function for Dma interrupt. */
void Linflexd_1_Uart_Ip_DmaRxCompleteCallback(void)
{
    Linflexd_Uart_Ip_CompleteReceiveUsingDma(LinflexD_1);
}
#endif
#endif
#if (LINFLEXD_INSTANCE_COUNT > 2U)
#ifdef LinflexD_2
/* Implementation of LINFlexD2 Tx callback function for Dma interrupt. */
void Linflexd_2_Uart_Ip_DmaTxCompleteCallback(void)
{
    Linflexd_Uart_Ip_CompleteSendUsingDma(LinflexD_2);
}
/* Implementation of LINFlexD2 Rx callback function for Dma interrupt. */
void Linflexd_2_Uart_Ip_DmaRxCompleteCallback(void)
{
    Linflexd_Uart_Ip_CompleteReceiveUsingDma(LinflexD_2);
}
#endif
#endif
#endif

#define UART_STOP_SEC_CODE
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
