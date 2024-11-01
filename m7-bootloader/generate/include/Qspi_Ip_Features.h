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

#if !defined(QSPI_IP_FEATURES_H)
#define QSPI_IP_FEATURES_H

/**
*   @file Qspi_Ip_Features.h
*
*   @addtogroup FLS
*   @{
*/

/* implements Qspi_Ip_Features.h_Artifact */

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define QSPI_IP_FEATURES_VENDOR_ID_CFG                      43
#define QSPI_IP_FEATURES_AR_RELEASE_MAJOR_VERSION_CFG       4
#define QSPI_IP_FEATURES_AR_RELEASE_MINOR_VERSION_CFG       4
#define QSPI_IP_FEATURES_AR_RELEASE_REVISION_VERSION_CFG    0
#define QSPI_IP_FEATURES_SW_MAJOR_VERSION_CFG               1
#define QSPI_IP_FEATURES_SW_MINOR_VERSION_CFG               0
#define QSPI_IP_FEATURES_SW_PATCH_VERSION_CFG               0

#if defined(S32K3XX)
    #include "S32K344_QUADSPI.h"
#endif
#if defined(S32G2XX)
    #include "S32G274A_QUADSPI.h"
#endif

/* QuadSPI module features */

/*! @brief First address of the serial flash device on the AHB bus. */
#define FEATURE_QSPI_AMBA_BASE                        0x00000000U
/*! @brief Size of AHB buffer. */
#define FEATURE_QSPI_AHB_BUF_SIZE                     1024U
/*! @brief Size of Tx FIFO. */
#define FEATURE_QSPI_TX_BUF_SIZE                      1024U
/*! @brief Size of Rx FIFO. */
#define FEATURE_QSPI_RX_BUF_SIZE                      256U
/*! @brief Number of LUT registers that make up a LUT sequence */
#define FEATURE_QSPI_LUT_SEQUENCE_SIZE                5U

/*! @brief Supports Double Data Rate operation */
#define FEATURE_QSPI_DDR                              1
/*! @brief QSPI side B is available */
#define FEATURE_QSPI_HAS_SIDE_B                       1
/*! @brief Configurable Idle Signal Drive */
#define FEATURE_QSPI_CONFIGURABLE_ISD                 1
/*! @brief Supports addr. config options (byte swap, column address, word addressable) */
#define FEATURE_QSPI_ADDR_CFG                         1
/*! @brief Supports center-aligned read strobe */
#define FEATURE_QSPI_CENTER_ALIGNED_READ_STROBE       1
/*! @brief Supports differential clock */
#define FEATURE_QSPI_DIFFERENTIAL_CLOCK               1
/*! @brief Supports internal DQS sampling mode */
#define FEATURE_QSPI_INTERNAL_DQS                     1
/*! @brief Supports loopback sampling mode */
#define FEATURE_QSPI_LOOPBACK                         1
/*! @brief Supports DQS loopback sampling mode */
#define FEATURE_QSPI_LOOPBACK_DQS                     1
/*! @brief Supports external DQS sampling mode */
#define FEATURE_QSPI_EXTERNAL_DQS                     1
/*! @brief Supports full DLL features (as opposed to bypass mode only) */
#define FEATURE_QSPI_EXTERNAL_DLL_FULL                1
/*! @brief Supports column address */
#define FEATURE_QSPI_COL_ADDR                         1
/*! @brief Supports word addressing */
#define FEATURE_QSPI_WORD_ADDR                        1
/*! @brief Supports data align */
#define FEATURE_QSPI_DATA_ALIGN                       1
#if defined(S32K3XX)
/*! @brief Needs S32K3 chip-specific initialization (SOCCR) */
#define FEATURE_QSPI_CHIP_OPTIONS_S32K3
#endif

/*! @brief AHB base pointers initializer for all QSPI units */
#define QuadSPI_AHB_PTRS    { FEATURE_QSPI_AMBA_BASE }


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* QSPI_IP_FEATURES_H */

