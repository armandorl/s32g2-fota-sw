/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : IPV_QSPI
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

#ifndef QSPI_IP_COMMON_H
#define QSPI_IP_COMMON_H

/**
*   @file Qspi_Ip_Common.h
*
*   @addtogroup IPV_QSPI QSPI IPV Driver
*   @{
*/

/* implements Qspi_Ip_Common.h_Artifact */

#ifdef __cplusplus
extern "C"{
#endif

#include "Qspi_Ip_Features.h"
#include "Devassert.h"
#include "Qspi_Ip.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define QSPI_IP_COMMON_VENDOR_ID_H                       43
#define QSPI_IP_COMMON_AR_RELEASE_MAJOR_VERSION_H        4
#define QSPI_IP_COMMON_AR_RELEASE_MINOR_VERSION_H        4
#define QSPI_IP_COMMON_AR_RELEASE_REVISION_VERSION_H     0
#define QSPI_IP_COMMON_SW_MAJOR_VERSION_H                1
#define QSPI_IP_COMMON_SW_MINOR_VERSION_H                0
#define QSPI_IP_COMMON_SW_PATCH_VERSION_H                0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Qspi_Ip_Features header file are of the same vendor */
#if (QSPI_IP_COMMON_VENDOR_ID_H != QSPI_IP_FEATURES_VENDOR_ID_CFG)
    #error "Qspi_Ip_Common.h and Qspi_Ip_Features.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_Features header file are of the same Autosar version */
#if ((QSPI_IP_COMMON_AR_RELEASE_MAJOR_VERSION_H    != QSPI_IP_FEATURES_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (QSPI_IP_COMMON_AR_RELEASE_MINOR_VERSION_H    != QSPI_IP_FEATURES_AR_RELEASE_MINOR_VERSION_CFG) || \
     (QSPI_IP_COMMON_AR_RELEASE_REVISION_VERSION_H != QSPI_IP_FEATURES_AR_RELEASE_REVISION_VERSION_CFG) \
    )
    #error "AutoSar Version Numbers of Qspi_Ip_Common.h and Qspi_Ip_Features.h are different"
#endif
/* Check if current file and Qspi_Ip_Features header file are of the same Software version */
#if ((QSPI_IP_COMMON_SW_MAJOR_VERSION_H != QSPI_IP_FEATURES_SW_MAJOR_VERSION_CFG) || \
     (QSPI_IP_COMMON_SW_MINOR_VERSION_H != QSPI_IP_FEATURES_SW_MINOR_VERSION_CFG) || \
     (QSPI_IP_COMMON_SW_PATCH_VERSION_H != QSPI_IP_FEATURES_SW_PATCH_VERSION_CFG) \
    )
    #error "Software Version Numbers of Qspi_Ip_Common.h and Qspi_Ip_Features.h are different"
#endif

/* Check if current file and Qspi_Ip header file are of the same vendor */
#if (QSPI_IP_COMMON_VENDOR_ID_H != QSPI_IP_VENDOR_ID_H)
    #error "Qspi_Ip_Common.h and Qspi_Ip.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip header file are of the same Autosar version */
#if ((QSPI_IP_COMMON_AR_RELEASE_MAJOR_VERSION_H    != QSPI_IP_AR_RELEASE_MAJOR_VERSION_H) || \
     (QSPI_IP_COMMON_AR_RELEASE_MINOR_VERSION_H    != QSPI_IP_AR_RELEASE_MINOR_VERSION_H) || \
     (QSPI_IP_COMMON_AR_RELEASE_REVISION_VERSION_H != QSPI_IP_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Qspi_Ip_Common.h and Qspi_Ip.h are different"
#endif
/* Check if current file and Qspi_Ip header file are of the same Software version */
#if ((QSPI_IP_COMMON_SW_MAJOR_VERSION_H != QSPI_IP_SW_MAJOR_VERSION_H) || \
     (QSPI_IP_COMMON_SW_MINOR_VERSION_H != QSPI_IP_SW_MINOR_VERSION_H) || \
     (QSPI_IP_COMMON_SW_PATCH_VERSION_H != QSPI_IP_SW_PATCH_VERSION_H) \
    )
    #error "Software Version Numbers of Qspi_Ip_Common.h and Qspi_Ip.h are different"
#endif

/*******************************************************************************
 * Enumerations.
 ******************************************************************************/
/*! DEV_ASSERT_QSPI definition */
#if (QSPI_IP_DEV_ERROR_DETECT == STD_ON)
#define     DEV_ASSERT_QSPI(x)   DevAssert((x))
#else
#define     DEV_ASSERT_QSPI(x)
#endif
/*******************************************************************************
 * External variable declarations.
 ******************************************************************************/

#define FLS_START_SEC_CONST_UNSPECIFIED
#include "Fls_MemMap.h"

/* Table of AHB addresses for QuadSPI instances. */
extern const uint32 Qspi_Ip_AhbAddress[QuadSPI_INSTANCE_COUNT];

#define FLS_STOP_SEC_CONST_UNSPECIFIED
#include "Fls_MemMap.h"


/*******************************************************************************
* Definitions
******************************************************************************/


/*!
 * @brief Driver configuration structure
 *
 * This structure is used to provide configuration parameters for the external flash driver
 * at initialization time.
 */
typedef struct
{
    const Qspi_Ip_MemoryConfigType *configuration;      /*!< Serial flash device configuration                */
    const Qspi_Ip_MemoryConnectionType *connection;     /*!< Connection to a QSPI device                      */
    uint32 baseAddress;                                 /*!< Base address of serial flash device              */
    uint32 lastCommand;                                 /*!< Last command sent to the flash device            */
    uint16 activeReadLut;                               /*!< LUT number for currently active read mode        */
} Qspi_Ip_StateType;

/*******************************************************************************
 * API
 ******************************************************************************/




#ifdef __cplusplus
}
#endif

/** @} */

#endif /* QSPI_IP_COMMON_H */
