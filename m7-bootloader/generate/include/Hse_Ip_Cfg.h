/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : Crypto
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

#ifndef HSE_IP_CFG_H
#define HSE_IP_CFG_H

/**
*   @file
*
*   @addtogroup CRYPTO
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
#include "S32G274A_MU.h"
#include "OsIf.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define HSE_IP_CFG_VENDOR_ID_H                       43
#define HSE_IP_CFG_SW_MAJOR_VERSION_H                1
#define HSE_IP_CFG_SW_MINOR_VERSION_H                0
#define HSE_IP_CFG_SW_PATCH_VERSION_H                0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/* Pre-processor switch to enable/disable development error detection for Hse Ip API */
#define HSE_IP_DEV_ERROR_DETECT                  (STD_OFF)

/* Check if the chosen counter type is enabled */
#if (STD_OFF == OSIF_USE_SYSTEM_TIMER)
    #error "OSIF System counter is disabled"
#endif

/* OsIf counter type used in timeout detection for HSE IP service request */
#define HSE_IP_TIMEOUT_OSIF_COUNTER_TYPE         (OSIF_COUNTER_SYSTEM)

/* Initializer for the MU Host base addresses */
#define MU_HOST_BASE_PTRS                        { MU0__MUB, MU1__MUB, MU2__MUB, MU3__MUB }

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

#endif /* HSE_IP_CFG_H */
