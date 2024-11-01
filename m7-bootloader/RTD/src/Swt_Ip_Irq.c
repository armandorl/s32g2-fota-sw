/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : Swt
*   Dependencies         : none
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
*
*   @addtogroup Swt
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "StandardTypes.h"
#include "Swt_Ip_Cfg_Defines.h"
#include "OsIf.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SWT_IP_IRQ_VENDOR_ID_C                      43
#define SWT_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C       4
#define SWT_IP_IRQ_AR_RELEASE_MINOR_VERSION_C       4
#define SWT_IP_IRQ_AR_RELEASE_REVISION_VERSION_C    0
#define SWT_IP_IRQ_SW_MAJOR_VERSION_C               1
#define SWT_IP_IRQ_SW_MINOR_VERSION_C               0
#define SWT_IP_IRQ_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/

/* Check if current file and Swt_Ip_Cfg_Defines configuration header file are of the same vendor */
#if (SWT_IP_IRQ_VENDOR_ID_C != SWT_IP_CFG_DEFINES_VENDOR_ID)
#error "Swt_Ip_Irq.c and Swt_Ip_Cfg_Defines.h have different vendor ids"
#endif

#if ((SWT_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C    != SWT_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION) || \
     (SWT_IP_IRQ_AR_RELEASE_MINOR_VERSION_C    != SWT_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION) || \
     (SWT_IP_IRQ_AR_RELEASE_REVISION_VERSION_C != SWT_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION))
#error "AutoSar Version Numbers of Swt_Ip_Irq.c and Swt_Ip_Cfg_Defines.h are different"
#endif

#if ((SWT_IP_IRQ_SW_MAJOR_VERSION_C != SWT_IP_CFG_DEFINES_SW_MAJOR_VERSION) || \
     (SWT_IP_IRQ_SW_MINOR_VERSION_C != SWT_IP_CFG_DEFINES_SW_MINOR_VERSION) || \
     (SWT_IP_IRQ_SW_PATCH_VERSION_C != SWT_IP_CFG_DEFINES_SW_PATCH_VERSION))
#error "Software Version Numbers of Swt_Ip_Irq.c and Swt_Ip_Cfg_Defines.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if current file and Osif header file are of the same Autosar version */
    #if ((SWT_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C    != OSIF_AR_RELEASE_MAJOR_VERSION) || \
        (SWT_IP_IRQ_AR_RELEASE_MINOR_VERSION_C     != OSIF_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Swt_Ip_Irq.c and Osif.h are different"
    #endif
    
    /* Check if current file and StandardTypes header file are of the same Autosar version */
    #if ((SWT_IP_IRQ_AR_RELEASE_MAJOR_VERSION_C    != STD_AR_RELEASE_MAJOR_VERSION) || \
        (SWT_IP_IRQ_AR_RELEASE_MINOR_VERSION_C     != STD_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Swt_Ip_Irq.c and StandardTypes.h are different"
    #endif
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                 GLOBAL FUNCTIONS PROTOTYPES
==================================================================================================*/

#ifdef WDG_ROM
    #if (WDG_ROM == 1U)
        #define WDG_START_SEC_CODE
    #endif
#else
    #if (WDG_RAM == 0U)
        #define WDG_START_SEC_RAMCODE
    #endif
#endif
/**
* @brief Include Memory mapping specification
*/
#include "Wdg_MemMap.h"

extern void Swt_Ip_IrqHandler(uint32 u32Instance);

#ifdef SWT_IP_ENABLE_INSTANCE0
#if (SWT_IP_ENABLE_INSTANCE0 == STD_ON)
    ISR(Swt_Ip_Swt0_Isr);
#endif
#endif

#ifdef SWT_IP_ENABLE_INSTANCE1
#if (SWT_IP_ENABLE_INSTANCE1 == STD_ON)
    ISR(Swt_Ip_Swt1_Isr);
#endif
#endif

#ifdef SWT_IP_ENABLE_INSTANCE2
#if (SWT_IP_ENABLE_INSTANCE2 == STD_ON)
    ISR(Swt_Ip_Swt2_Isr);
#endif
#endif

#ifdef SWT_IP_ENABLE_INSTANCE3
#if (SWT_IP_ENABLE_INSTANCE3 == STD_ON)
    ISR(Swt_Ip_Swt3_Isr);
#endif
#endif

#ifdef SWT_IP_ENABLE_INSTANCE4
#if (SWT_IP_ENABLE_INSTANCE4 == STD_ON)
    ISR(Swt_Ip_Swt4_Isr);
#endif
#endif

#ifdef SWT_IP_ENABLE_INSTANCE5
#if (SWT_IP_ENABLE_INSTANCE5 == STD_ON)
    ISR(Swt_Ip_Swt5_Isr);
#endif
#endif

#ifdef SWT_IP_ENABLE_INSTANCE6
#if (SWT_IP_ENABLE_INSTANCE6 == STD_ON)
    ISR(Swt_Ip_Swt6_Isr);
#endif
#endif

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/



/**
* @brief   Swt handler for initial timeout interrupt.
* @details This function implements the ISR occurring on the first SWT timeout.
*
* @isr
*
*/
#ifdef SWT_IP_ENABLE_INSTANCE0
#if (SWT_IP_ENABLE_INSTANCE0 == STD_ON)
    ISR(Swt_Ip_Swt0_Isr)
    {
        Swt_Ip_IrqHandler(0U);
    }
#endif
#endif

#ifdef SWT_IP_ENABLE_INSTANCE1
#if (SWT_IP_ENABLE_INSTANCE1 == STD_ON)
    ISR(Swt_Ip_Swt1_Isr)
    {
        Swt_Ip_IrqHandler(1U);
    }
#endif
#endif

#ifdef SWT_IP_ENABLE_INSTANCE2
#if (SWT_IP_ENABLE_INSTANCE2 == STD_ON)
    ISR(Swt_Ip_Swt2_Isr)
    {
        Swt_Ip_IrqHandler(2U);
    }
#endif
#endif

#ifdef SWT_IP_ENABLE_INSTANCE3
#if (SWT_IP_ENABLE_INSTANCE3 == STD_ON)
    ISR(Swt_Ip_Swt3_Isr)
    {
        Swt_Ip_IrqHandler(3U);
    }
#endif
#endif

#ifdef SWT_IP_ENABLE_INSTANCE4
#if (SWT_IP_ENABLE_INSTANCE4 == STD_ON)
    ISR(Swt_Ip_Swt4_Isr)
    {
        Swt_Ip_IrqHandler(4U);
    }
#endif
#endif

#ifdef SWT_IP_ENABLE_INSTANCE5
#if (SWT_IP_ENABLE_INSTANCE5 == STD_ON)
    ISR(Swt_Ip_Swt5_Isr)
    {
        Swt_Ip_IrqHandler(5U);
    }
#endif
#endif

#ifdef SWT_IP_ENABLE_INSTANCE6
#if (SWT_IP_ENABLE_INSTANCE6 == STD_ON)
    ISR(Swt_Ip_Swt6_Isr)
    {
        Swt_Ip_IrqHandler(6U);
    }
#endif
#endif

#ifdef WDG_ROM
    #if (WDG_ROM == 1U)
        #define WDG_STOP_SEC_CODE
    #endif
#else
    #if (WDG_RAM == 0U)
        #define WDG_STOP_SEC_RAMCODE
    #endif
#endif
/**
* @brief Include Memory mapping specification
*/
#include "Wdg_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
