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

#ifndef SWT_DEVICE_REGISTERS_H
#define SWT_DEVICE_REGISTERS_H

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
#include "Swt_Ip_FeatureDefines.h"

#if defined(S32G2XX)

    #include "S32G274A_SWT.h"

#elif defined(S32R45)

    #include "S32R45_SWT.h"

#elif defined(S32K3XX)

    #include "S32K344_SWT.h"
#endif

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SWT_IP_DEVICE_REGISTERS_VENDOR_ID                    43
#define SWT_IP_DEVICE_REGISTERS_MODULE_ID                    102
#define SWT_IP_DEVICE_REGISTERS_AR_RELEASE_MAJOR_VERSION     4
#define SWT_IP_DEVICE_REGISTERS_AR_RELEASE_MINOR_VERSION     4
#define SWT_IP_DEVICE_REGISTERS_AR_RELEASE_REVISION_VERSION  0
#define SWT_IP_DEVICE_REGISTERS_SW_MAJOR_VERSION             1
#define SWT_IP_DEVICE_REGISTERS_SW_MINOR_VERSION             0
#define SWT_IP_DEVICE_REGISTERS_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/

/* Check if current file and Swt_Ip_Cfg_Defines configuration header file are of the same vendor */
#if (SWT_IP_DEVICE_REGISTERS_VENDOR_ID != SWT_IP_FEATURE_DEFINES_VENDOR_ID)
#error "Swt_Ip_DeviceRegisters.h and Swt_Ip_FeatureDefines.h have different vendor ids"
#endif

#if ((SWT_IP_DEVICE_REGISTERS_AR_RELEASE_MAJOR_VERSION    != SWT_IP_FEATURE_DEFINES_AR_RELEASE_MAJOR_VERSION) || \
     (SWT_IP_DEVICE_REGISTERS_AR_RELEASE_MINOR_VERSION    != SWT_IP_FEATURE_DEFINES_AR_RELEASE_MINOR_VERSION) || \
     (SWT_IP_DEVICE_REGISTERS_AR_RELEASE_REVISION_VERSION != SWT_IP_FEATURE_DEFINES_AR_RELEASE_REVISION_VERSION))
#error "AutoSar Version Numbers of Swt_Ip_DeviceRegisters.h and Swt_Ip_FeatureDefines.h are different"
#endif

#if ((SWT_IP_DEVICE_REGISTERS_SW_MAJOR_VERSION != SWT_IP_FEATURE_DEFINES_SW_MAJOR_VERSION) || \
     (SWT_IP_DEVICE_REGISTERS_SW_MINOR_VERSION != SWT_IP_FEATURE_DEFINES_SW_MINOR_VERSION) || \
     (SWT_IP_DEVICE_REGISTERS_SW_PATCH_VERSION != SWT_IP_FEATURE_DEFINES_SW_PATCH_VERSION))
#error "Software Version Numbers of Swt_Ip_DeviceRegisters.h and Swt_Ip_FeatureDefines.h are different"
#endif

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

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

#endif /*SWT_DEVICE_REGISTERS_H */
