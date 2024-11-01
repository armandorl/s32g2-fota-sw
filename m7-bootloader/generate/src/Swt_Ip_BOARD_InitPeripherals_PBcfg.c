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

#include "Swt_Ip_BOARD_INITPERIPHERALS_PBcfg.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SWT_43_INSTANCE$instanceId$_Ip_$variantName$_PBCFG_VENDOR_ID_C                      43
#define SWT_43_INSTANCE$instanceId$_Ip_$variantName$_PBCFG_AR_RELEASE_MAJOR_VERSION_C       4
#define SWT_43_INSTANCE$instanceId$_Ip_$variantName$_PBCFG_AR_RELEASE_MINOR_VERSION_C       4
#define SWT_43_INSTANCE$instanceId$_Ip_$variantName$_PBCFG_AR_RELEASE_REVISION_VERSION_C    0
#define SWT_43_INSTANCE$instanceId$_Ip_$variantName$_PBCFG_SW_MAJOR_VERSION_C               1
#define SWT_43_INSTANCE$instanceId$_Ip_$variantName$_PBCFG_SW_MINOR_VERSION_C               0
#define SWT_43_INSTANCE$instanceId$_Ip_$variantName$_PBCFG_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/

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

#define WDG_START_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @brief Include Memory mapping specification
*/
#include "Wdg_MemMap.h"


/* Swt Callback Notification 0*/
extern void Swt_CallbackNotification0(void);

const Swt_Ip_ConfigType Swt_Ip_1_Cfg0 = 
{
    (uint8)SWT_IP_ALL_MAP_DISABLE | SWT_IP_MAP0_ENABLE | SWT_IP_MAP1_ENABLE | SWT_IP_MAP2_ENABLE | SWT_IP_MAP3_ENABLE | SWT_IP_MAP4_ENABLE | SWT_IP_MAP5_ENABLE | SWT_IP_MAP6_ENABLE | SWT_IP_MAP7_ENABLE,
    (boolean)FALSE,
    FALSE,
    FALSE,
    FALSE,
    FALSE,
    FALSE,
    0xe4e1c00,
    0x0,
    0,
    SWT_IP_UNLOCK,
    (Swt_CallbackPtrType) &Swt_CallbackNotification0
};


#define WDG_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @brief Include Memory mapping specification
*/
#include "Wdg_MemMap.h"

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

