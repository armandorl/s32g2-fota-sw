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
#ifndef SWT_43_INSTANCESwt_Ip_IP_BOARD_INITPERIPHERALS_PBCFG_H
#define SWT_43_INSTANCESwt_Ip_IP_BOARD_INITPERIPHERALS_PBCFG_H

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
#include "Swt_Ip_Cfg_Defines.h"
#include "Swt_Ip_Types.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SWT_43_INSTANCESwt_Ip_IP_VENDOR_ID_BOARD_INITPERIPHERALS_PBCFG                    43
#define SWT_43_INSTANCESwt_Ip_IP_AR_RELEASE_MAJOR_VERSION_BOARD_INITPERIPHERALS_PBCFG     4
#define SWT_43_INSTANCESwt_Ip_IP_AR_RELEASE_MINOR_VERSION_BOARD_INITPERIPHERALS_PBCFG     4
#define SWT_43_INSTANCESwt_Ip_IP_AR_RELEASE_REVISION_VERSION_BOARD_INITPERIPHERALS_PBCFG  0
#define SWT_43_INSTANCESwt_Ip_IP_SW_MAJOR_VERSION_BOARD_INITPERIPHERALS_PBCFG             1
#define SWT_43_INSTANCESwt_Ip_IP_SW_MINOR_VERSION_BOARD_INITPERIPHERALS_PBCFG             0
#define SWT_43_INSTANCESwt_Ip_IP_SW_PATCH_VERSION_BOARD_INITPERIPHERALS_PBCFG             0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/* Check if current file and Swt_Ip_Cfg_Defines header file are of the same vendor */
#if (SWT_43_INSTANCESwt_Ip_IP_VENDOR_ID_BOARD_INITPERIPHERALS_PBCFG != SWT_IP_CFG_DEFINES_VENDOR_ID)
#error "SWT_43_INSTANCESwt_Ip_IP_BOARD_INITPERIPHERALS_PBcfg.h and Swt_Ip_Cfg_Defines.h have different vendor ids"
#endif

/* Check if current file and Swt_Ip_Cfg_Defines header file are of the same Autosar version */
#if ((SWT_43_INSTANCESwt_Ip_IP_AR_RELEASE_MAJOR_VERSION_BOARD_INITPERIPHERALS_PBCFG    != SWT_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION) || \
     (SWT_43_INSTANCESwt_Ip_IP_AR_RELEASE_MINOR_VERSION_BOARD_INITPERIPHERALS_PBCFG    != SWT_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION) || \
     (SWT_43_INSTANCESwt_Ip_IP_AR_RELEASE_REVISION_VERSION_BOARD_INITPERIPHERALS_PBCFG != SWT_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION))
#error "AutoSar Version Numbers of SWT_43_INSTANCESwt_Ip_IP_BOARD_INITPERIPHERALS_PBcfg.h and Swt_Ip_Cfg_Defines.h are different"
#endif

/* Check if current file and Swt_Ip_Cfg_Defines header file are of the same software version */
#if ((SWT_43_INSTANCESwt_Ip_IP_SW_MAJOR_VERSION_BOARD_INITPERIPHERALS_PBCFG != SWT_IP_CFG_DEFINES_SW_MAJOR_VERSION) || \
     (SWT_43_INSTANCESwt_Ip_IP_SW_MINOR_VERSION_BOARD_INITPERIPHERALS_PBCFG != SWT_IP_CFG_DEFINES_SW_MINOR_VERSION) || \
     (SWT_43_INSTANCESwt_Ip_IP_SW_PATCH_VERSION_BOARD_INITPERIPHERALS_PBCFG != SWT_IP_CFG_DEFINES_SW_PATCH_VERSION))
#error "Software Version Numbers of SWT_43_INSTANCESwt_Ip_IP_BOARD_INITPERIPHERALS_PBcfg.h and Swt_Ip_Cfg_Defines.h are different"
#endif

/* Check if current file and Swt_Ip_Types.h header file are of the same vendor */
#if (SWT_43_INSTANCESwt_Ip_IP_VENDOR_ID_BOARD_INITPERIPHERALS_PBCFG != SWT_IP_TYPES_VENDOR_ID)
#error "SWT_43_INSTANCESwt_Ip_IP_BOARD_INITPERIPHERALS_PBcfg.h and Swt_Ip_Types.h have different vendor ids"
#endif

#if ((SWT_43_INSTANCESwt_Ip_IP_AR_RELEASE_MAJOR_VERSION_BOARD_INITPERIPHERALS_PBCFG    != SWT_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (SWT_43_INSTANCESwt_Ip_IP_AR_RELEASE_MINOR_VERSION_BOARD_INITPERIPHERALS_PBCFG    != SWT_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (SWT_43_INSTANCESwt_Ip_IP_AR_RELEASE_REVISION_VERSION_BOARD_INITPERIPHERALS_PBCFG != SWT_IP_TYPES_AR_RELEASE_REVISION_VERSION))
#error "AutoSar Version Numbers of SWT_43_INSTANCESwt_Ip_IP_BOARD_INITPERIPHERALS_PBcfg.h and Swt_Ip_Types.h are different"
#endif

#if ((SWT_43_INSTANCESwt_Ip_IP_SW_MAJOR_VERSION_BOARD_INITPERIPHERALS_PBCFG != SWT_IP_TYPES_SW_MAJOR_VERSION) || \
     (SWT_43_INSTANCESwt_Ip_IP_SW_MINOR_VERSION_BOARD_INITPERIPHERALS_PBCFG != SWT_IP_TYPES_SW_MINOR_VERSION) || \
     (SWT_43_INSTANCESwt_Ip_IP_SW_PATCH_VERSION_BOARD_INITPERIPHERALS_PBCFG != SWT_IP_TYPES_SW_PATCH_VERSION))
#error "Software Version Numbers of SWT_43_INSTANCESwt_Ip_IP_BOARD_INITPERIPHERALS_PBcfg.h and Swt_Ip_Types.h are different"
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                            ENUMS
==================================================================================================*/

/*==================================================================================================
*                               STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

#define WDG_START_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @brief Include Memory mapping specification
*/
#include "Wdg_MemMap.h"

extern const Swt_Ip_ConfigType Swt_Ip_1_Cfg0;

#define WDG_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Wdg_MemMap.h"

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* SWT_43_INSTANCESwt_Ip_IP_BOARD_INITPERIPHERALS_PBCFG_H */



