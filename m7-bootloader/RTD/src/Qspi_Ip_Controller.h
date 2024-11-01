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

#ifndef QSPI_IP_CONTROLLER_H
#define QSPI_IP_CONTROLLER_H

/**
*   @file Qspi_Ip_Controller.h
*
*   @addtogroup IPV_QSPI QSPI IPV Driver
*   @{
*/

/* implements Qspi_Ip_Controller.h_Artifact */

#ifdef __cplusplus
extern "C"{
#endif

#include "Qspi_Ip_Features.h"
#include "Qspi_Ip_Common.h"
#include "Qspi_Ip.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define QSPI_IP_CONTROLLER_VENDOR_ID_H                       43
#define QSPI_IP_CONTROLLER_AR_RELEASE_MAJOR_VERSION_H        4
#define QSPI_IP_CONTROLLER_AR_RELEASE_MINOR_VERSION_H        4
#define QSPI_IP_CONTROLLER_AR_RELEASE_REVISION_VERSION_H     0
#define QSPI_IP_CONTROLLER_SW_MAJOR_VERSION_H                1
#define QSPI_IP_CONTROLLER_SW_MINOR_VERSION_H                0
#define QSPI_IP_CONTROLLER_SW_PATCH_VERSION_H                0
/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Qspi_Ip_Features header file are of the same vendor */
#if (QSPI_IP_CONTROLLER_VENDOR_ID_H != QSPI_IP_FEATURES_VENDOR_ID_CFG)
    #error "Qspi_Ip_Controller.h and Qspi_Ip_Features.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_Features header file are of the same Autosar version */
#if ((QSPI_IP_CONTROLLER_AR_RELEASE_MAJOR_VERSION_H    != QSPI_IP_FEATURES_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (QSPI_IP_CONTROLLER_AR_RELEASE_MINOR_VERSION_H    != QSPI_IP_FEATURES_AR_RELEASE_MINOR_VERSION_CFG) || \
     (QSPI_IP_CONTROLLER_AR_RELEASE_REVISION_VERSION_H != QSPI_IP_FEATURES_AR_RELEASE_REVISION_VERSION_CFG) \
    )
    #error "AutoSar Version Numbers of Qspi_Ip_Controller.h and Qspi_Ip_Features.h are different"
#endif
/* Check if current file and Qspi_Ip_Features header file are of the same Software version */
#if ((QSPI_IP_CONTROLLER_SW_MAJOR_VERSION_H != QSPI_IP_FEATURES_SW_MAJOR_VERSION_CFG) || \
     (QSPI_IP_CONTROLLER_SW_MINOR_VERSION_H != QSPI_IP_FEATURES_SW_MINOR_VERSION_CFG) || \
     (QSPI_IP_CONTROLLER_SW_PATCH_VERSION_H != QSPI_IP_FEATURES_SW_PATCH_VERSION_CFG) \
    )
    #error "Software Version Numbers of Qspi_Ip_Controller.h and Qspi_Ip_Features.h are different"
#endif

/* Check if current file and Qspi_Ip_Common header file are of the same vendor */
#if (QSPI_IP_CONTROLLER_VENDOR_ID_H != QSPI_IP_COMMON_VENDOR_ID_H)
    #error "Qspi_Ip_Controller.h and Qspi_Ip_Common.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_Common header file are of the same Autosar version */
#if ((QSPI_IP_CONTROLLER_AR_RELEASE_MAJOR_VERSION_H    != QSPI_IP_COMMON_AR_RELEASE_MAJOR_VERSION_H) || \
     (QSPI_IP_CONTROLLER_AR_RELEASE_MINOR_VERSION_H    != QSPI_IP_COMMON_AR_RELEASE_MINOR_VERSION_H) || \
     (QSPI_IP_CONTROLLER_AR_RELEASE_REVISION_VERSION_H != QSPI_IP_COMMON_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Qspi_Ip_Controller.h and Qspi_Ip_Common.h are different"
#endif
/* Check if current file and Qspi_Ip_Common header file are of the same Software version */
#if ((QSPI_IP_CONTROLLER_SW_MAJOR_VERSION_H != QSPI_IP_COMMON_SW_MAJOR_VERSION_H) || \
     (QSPI_IP_CONTROLLER_SW_MINOR_VERSION_H != QSPI_IP_COMMON_SW_MINOR_VERSION_H) || \
     (QSPI_IP_CONTROLLER_SW_PATCH_VERSION_H != QSPI_IP_COMMON_SW_PATCH_VERSION_H) \
    )
    #error "Software Version Numbers of Qspi_Ip_Controller.h and Qspi_Ip_Common.h are different"
#endif

/* Check if current file and Qspi_Ip header file are of the same vendor */
#if (QSPI_IP_CONTROLLER_VENDOR_ID_H != QSPI_IP_VENDOR_ID_H)
    #error "Qspi_Ip_Controller.h and Qspi_Ip.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip header file are of the same Autosar version */
#if ((QSPI_IP_CONTROLLER_AR_RELEASE_MAJOR_VERSION_H    != QSPI_IP_AR_RELEASE_MAJOR_VERSION_H) || \
     (QSPI_IP_CONTROLLER_AR_RELEASE_MINOR_VERSION_H    != QSPI_IP_AR_RELEASE_MINOR_VERSION_H) || \
     (QSPI_IP_CONTROLLER_AR_RELEASE_REVISION_VERSION_H != QSPI_IP_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Qspi_Ip_Controller.h and Qspi_Ip.h are different"
#endif
/* Check if current file and Qspi_Ip header file are of the same Software version */
#if ((QSPI_IP_CONTROLLER_SW_MAJOR_VERSION_H != QSPI_IP_SW_MAJOR_VERSION_H) || \
     (QSPI_IP_CONTROLLER_SW_MINOR_VERSION_H != QSPI_IP_SW_MINOR_VERSION_H) || \
     (QSPI_IP_CONTROLLER_SW_PATCH_VERSION_H != QSPI_IP_SW_PATCH_VERSION_H) \
    )
    #error "Software Version Numbers of Qspi_Ip_Controller.h and Qspi_Ip.h are different"
#endif
/*******************************************************************************
 * Enumerations.
 ******************************************************************************/

/*******************************************************************************
* Definitions
******************************************************************************/

#define FLS_START_SEC_CONST_UNSPECIFIED
#include "Fls_MemMap.h"

extern QuadSPI_Type * const Qspi_Ip_BaseAddress[];

#define FLS_STOP_SEC_CONST_UNSPECIFIED
#include "Fls_MemMap.h"


/*******************************************************************************
 * API
 ******************************************************************************/
/*!
 * @name QuadSPI Driver
 * @{
 */

#if defined(__cplusplus)
extern "C" {
#endif

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"

/*!
 * @brief Returns the physical base address of a flash device
 *
 * This function returns the physical base address of a flash device, depending on the QSPI connection.
 * The controller must be initialized prior to calling this function.
 *
 * @param instance        QuadSPI peripheral instance number
 * @param connectionType  Connection of the flash device to QSPI
 */
uint32 Qspi_Ip_GetBaseAdress(uint32 instance, Qspi_Ip_ConnectionType connectionType);

/*!
 * @brief Launches a simple IP command
 *
 * @param instance     QuadSPI peripheral instance number
 * @param lut          Index of LUT register
 * @param addr         Address of the target serial flash
 * @return    Error or success status returned by API
 */
Qspi_Ip_StatusType Qspi_Ip_IpCommand(uint32 instance, uint8 lut, uint32 addr);


/*!
 * @brief Launches an IP read command
 *
 * This function can launch a read command in 3 modes:
 * - normal read (dataRead != NULL_PTR): Data is read from serial flash and placed in the buffer
 * - verify (dataRead == NULL_PTR, dataCmp != NULL_PTR): Data is read from serial flash and compared to the reference buffer
 * - blank check (dataRead == NULL_PTR, dataCmp == NULL_PTR): Data is read from serial flash and compared to 0xFF
 * Only normal read mode can use DMA.
 *
 * @param instance       QuadSPI peripheral instance number
 * @param lut            Index of LUT register
 * @param addr           Start address for read operation in serial flash
 * @param dataRead       Buffer where to store read data
 * @param dataCmp        Buffer to be compared to read data
 * @param size           Size of data buffer
 * @return    Error or success status returned by API
 */
Qspi_Ip_StatusType Qspi_Ip_IpRead(uint32 instance, 
                         uint8 lut, 
                         uint32 addr, 
                         uint8 * dataRead,
                         const uint8 * dataCmp,
                         uint32 size);


/*!
 * @brief Launches an IP write command
 *
 * @param instance       QuadSPI peripheral instance number
 * @param lut            Index of LUT register
 * @param addr           Start address for write operation in serial flash
 * @param data           Data to be programmed in flash
 * @param size           Size of data buffer
 * @return    Error or success status returned by API
 */
Qspi_Ip_StatusType Qspi_Ip_IpWrite(uint32 instance, 
                          uint8 lut, 
                          uint32 addr, 
                          const uint8 * data, 
                          uint32 size);


#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */

#endif /* QSPI_IP_CONTROLLER_H */
