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

#ifndef SWT_IP_FEATUREDEFINES_H
#define SWT_IP_FEATUREDEFINES_H

/**
*   @file
*
*   @addtogroup Wdg
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
#define SWT_IP_FEATURE_DEFINES_VENDOR_ID                    43
#define SWT_IP_FEATURE_DEFINES_MODULE_ID                    102
#define SWT_IP_FEATURE_DEFINES_AR_RELEASE_MAJOR_VERSION     4
#define SWT_IP_FEATURE_DEFINES_AR_RELEASE_MINOR_VERSION     4
#define SWT_IP_FEATURE_DEFINES_AR_RELEASE_REVISION_VERSION  0
#define SWT_IP_FEATURE_DEFINES_SW_MAJOR_VERSION             1
#define SWT_IP_FEATURE_DEFINES_SW_MINOR_VERSION             0
#define SWT_IP_FEATURE_DEFINES_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if current file and StandardTypes header file are of the same Autosar version */
    #if ((SWT_IP_FEATURE_DEFINES_AR_RELEASE_MAJOR_VERSION    != STD_AR_RELEASE_MAJOR_VERSION) || \
        (SWT_IP_FEATURE_DEFINES_AR_RELEASE_MINOR_VERSION     != STD_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Swt_Ip_Cfg_Defines.h and StandardTypes.h are different"
    #endif
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/* @brief Support service mode watch-point input */
#define SWT_IP_SUPPORT_WATCHPOINT      (0U)
/* @brief Support for clock selection */
#define SWT_IP_HAS_CLOCK_SELECT        (0U)
/* @brief Support for running in stop mode */
#define SWT_IP_HAS_STOP_MODE           (1U)
/* @brief Support for Self Reset
 * Only SWT instances 1-6 can support this feature
 * SWT_0 instance reset request is tied to system reset
 * bits set are for instances that support this feature
 */
#define SWT_IP_RRR_SUPPORT             (0x0000007EUL)
/* @brief The key values to clear Soft Lock bit */
#define SWT_IP_UNLOCK_VALUE1           (0xC520U)
#define SWT_IP_UNLOCK_VALUE2           (0xD928U)
/* @brief The key values used for resetting the SWT counter in Fixed Service Sequence Mode */
#define SWT_IP_FIXED_SERVICE_VALUE1    (0xA602U)
#define SWT_IP_FIXED_SERVICE_VALUE2    (0xB480U)
/* @brief The reset value of the control register */
#define SWT_IP_CR_RESET_VALUE          (0xFF00010AU)
/* @brief The reset value of the timeout register */
#define SWT_IP_TO_RESET_VALUE          (0x0073FDE0U)
/* @brief The reset value of the window register */
#define SWT_IP_WN_RESET_VALUE          (0x0U)
/* @brief The reset value of the service key register */
#define SWT_IP_SK_RESET_VALUE          (0x0U)
/* @brief The minimum timeout value */
#define SWT_IP_TO_MINIMUM_VALUE        (0x100U)
/* @brief Sets the master access protection field */
#define SWT_IP_MAP_MASK                (0xFF000000U)
#define SWT_IP_MAP_SHIFT               (24U)
#define SWT_IP_MAP(x)                  (((uint32)(((uint32)(x)) << SWT_IP_MAP_SHIFT)) & SWT_IP_MAP_MASK)

/* @brief Timeout to wait for SWT unlock */
#define SWT_IP_UNLOCK_TIMEOUT           (15U)

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

#endif /* SWT_IP_FEATUREDEFINES_H */
