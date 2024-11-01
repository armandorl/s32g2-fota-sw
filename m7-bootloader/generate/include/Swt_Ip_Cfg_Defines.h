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

#ifndef SWT_IP_CFG_DEFINES_H
#define SWT_IP_CFG_DEFINES_H

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
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "StandardTypes.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define SWT_IP_CFG_DEFINES_VENDOR_ID                    43
#define SWT_IP_CFG_DEFINES_MODULE_ID                    102
#define SWT_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION     4
#define SWT_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION     4
#define SWT_IP_CFG_DEFINES_AR_RELEASE_REVISION_VERSION  0
#define SWT_IP_CFG_DEFINES_SW_MAJOR_VERSION             1
#define SWT_IP_CFG_DEFINES_SW_MINOR_VERSION             0
#define SWT_IP_CFG_DEFINES_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if current file and SchM_Wdg header file are of the same Autosar version */
    #if ((SWT_IP_CFG_DEFINES_AR_RELEASE_MAJOR_VERSION    != STD_AR_RELEASE_MAJOR_VERSION) || \
        (SWT_IP_CFG_DEFINES_AR_RELEASE_MINOR_VERSION     != STD_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Swt_Ip_Cfg_Defines.h and StandardTypes.h are different"
    #endif
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/**
* @brief  Enable available Swt instances on platform
*/
#define SWT_IP_ENABLE_INSTANCE0 (STD_ON)
#define SWT_IP_ENABLE_INSTANCE1 (STD_ON)
#define SWT_IP_ENABLE_INSTANCE2 (STD_ON)
#define SWT_IP_ENABLE_INSTANCE3 (STD_ON)
#define SWT_IP_ENABLE_INSTANCE4 (STD_ON)
#define SWT_IP_ENABLE_INSTANCE5 (STD_ON)
#define SWT_IP_ENABLE_INSTANCE6 (STD_ON)

/**
* @brief  Compile switch to enable development error detection
*/
#define SWT_IP_DEV_ERROR_DETECT (STD_ON)

/**
* @brief  Compile switch to allow/forbid disabling the Swt during runtime
*/
#define SWT_IP_DEINIT (STD_ON)

/**
* @brief  Define indicating for which Swt instances the Clear Reset Request feature is supported
*/
#define SWT_IP_CLEAR_RESET_REQUEST (STD_ON)

/*==================================================================================================
*                                              ENUMS
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


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* SWT_IP_CFG_DEFINES_H */

