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

#ifndef QSPI_IP_CFG_H
#define QSPI_IP_CFG_H

/**
*   @file Qspi_Ip_Cfg.h
*
*   @addtogroup FLS
*   @{
*/

/* implements Qspi_Ip_Cfg.h_Artifact */

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
#include "Qspi_Ip_Types.h"
#include "OsIf.h"


/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define QSPI_IP_VENDOR_ID_CFG                    43
#define QSPI_IP_AR_RELEASE_MAJOR_VERSION_CFG     4
#define QSPI_IP_AR_RELEASE_MINOR_VERSION_CFG     4
#define QSPI_IP_AR_RELEASE_REVISION_VERSION_CFG  0
#define QSPI_IP_SW_MAJOR_VERSION_CFG             1
#define QSPI_IP_SW_MINOR_VERSION_CFG             0
#define QSPI_IP_SW_PATCH_VERSION_CFG             0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if Qspi_Ip_Cfg header file and StandardTypes.h header file are of the same Autosar version */
    #if ((QSPI_IP_AR_RELEASE_MAJOR_VERSION_CFG != STD_AR_RELEASE_MAJOR_VERSION) || \
         (QSPI_IP_AR_RELEASE_MINOR_VERSION_CFG != STD_AR_RELEASE_MINOR_VERSION) \
        )
        #error "Autosar Version Numbers of Qspi_Ip_Cfg.h and StandardTypes.h are different"
    #endif
    /* Check if Qspi_Ip_Cfg header file and OsIf.h header file are of the same Autosar version */
    #if ((QSPI_IP_AR_RELEASE_MAJOR_VERSION_CFG != OSIF_AR_RELEASE_MAJOR_VERSION) || \
         (QSPI_IP_AR_RELEASE_MINOR_VERSION_CFG != OSIF_AR_RELEASE_MINOR_VERSION) \
        )
        #error "Autosar Version Numbers of Qspi_Ip_Cfg.h and OsIf.h are different"
    #endif
#endif

/* Check if current file and Qspi_Ip_Types header file are of the same vendor */
#if (QSPI_IP_VENDOR_ID_CFG != FLS_QSPI_TYPES_VENDOR_ID)
    #error "Qspi_Ip_Cfg.h and Qspi_Ip_Types.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_Types header file are of the same Autosar version */
#if ((QSPI_IP_AR_RELEASE_MAJOR_VERSION_CFG    != FLS_QSPI_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (QSPI_IP_AR_RELEASE_MINOR_VERSION_CFG    != FLS_QSPI_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (QSPI_IP_AR_RELEASE_REVISION_VERSION_CFG != FLS_QSPI_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Qspi_Ip_Cfg.h and Qspi_Ip_Types.h are different"
#endif
/* Check if current file and Qspi_Ip_Types header file are of the same Software version */
#if ((QSPI_IP_SW_MAJOR_VERSION_CFG != FLS_QSPI_TYPES_SW_MAJOR_VERSION) || \
     (QSPI_IP_SW_MINOR_VERSION_CFG != FLS_QSPI_TYPES_SW_MINOR_VERSION) || \
     (QSPI_IP_SW_PATCH_VERSION_CFG != FLS_QSPI_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Qspi_Ip_Cfg.h and Qspi_Ip_Types.h are different"
#endif

/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/* Maximum number of retries for Write Enable command */
#define QSPI_IP_MAX_RETRY                 (3U)

/* Pre-processor switch to enable/disable development error detection for QSPI Ip API */
#define QSPI_IP_DEV_ERROR_DETECT          (STD_OFF)

/* Number of serial flash devices */
#define QSPI_IP_MEM_INSTANCE_COUNT        (1U)

/* Timeout for DLL lock sequence */
#define QSPI_IP_DLL_LOCK_TIMEOUT          (2147483647U)

/* Timeout for QSPI command completion */
#define QSPI_IP_CMD_COMPLETE_TIMEOUT      (2000000U)

/* Timeout for external flash software reset completion */
#define QSPI_IP_RESET_TIMEOUT             (2000000U)

/* Timeout for external flash startup initialization sequence completion */
#define QSPI_IP_FLS_INIT_TIMEOUT          (2000000U)

/* Timeout for a complete read operation */
#define QSPI_IP_READ_TIMEOUT              (2147483647U)


/* OsIf counter type used in timeout detection for QSPI IP operations  */
#define QSPI_IP_TIMEOUT_TYPE              (OSIF_COUNTER_DUMMY)

/*==================================================================================================
                                 GLOBAL CONSTANT DECLARATIONS
==================================================================================================*/
#define FLS_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Fls_MemMap.h"

/* Controller connections */
extern const Qspi_Ip_ControllerConfigType QspiConfigSet_BOARD_InitPeripherals_paQspiUnitCfg[1];
/* Memory configurations */
extern const Qspi_Ip_MemoryConfigType QspiConfigSet_BOARD_InitPeripherals_paFlashCfg[1];
/* Memory-controller connections */
extern const Qspi_Ip_MemoryConnectionType QspiConfigSet_BOARD_InitPeripherals_paFlashConnectionCfg[1];

#define FLS_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Fls_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* QSPI_IP_CFG_H */

