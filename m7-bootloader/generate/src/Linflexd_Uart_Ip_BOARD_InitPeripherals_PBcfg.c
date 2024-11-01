
/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : LINFLEXD
*   Dependencies         : 
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
*   @file Linflexd_Uart_Ip_PBcfg.c
*   @defgroup linflexd_uart_ip Linflexd UART IPL
*   @addtogroup  linflexd_uart_ip Linflexd UART IPL
*   @{
*/


#ifdef __cplusplus
extern "C"
{
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Linflexd_Uart_Ip_Types.h"
#include "Linflexd_Uart_Ip_Cfg.h"
#include "StandardTypes.h"
#if (LINFLEXD_UART_HAS_DMA_ENABLED == STD_ON)
#include "Dma_Ip.h"
#endif
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define LINFLEXD_UART_IP_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID_C                     43
#define LINFLEXD_UART_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C      4
#define LINFLEXD_UART_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C      4
#define LINFLEXD_UART_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION_C   0
#define LINFLEXD_UART_IP_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION_C              1
#define LINFLEXD_UART_IP_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION_C              0
#define LINFLEXD_UART_IP_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION_C              0


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

/* Checks against linflexd_Uart_Ip_Types.h */
#if (LINFLEXD_UART_IP_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID_C != LINFLEXD_UART_IP_TYPES_VENDOR_ID)
    #error "linflexd_Uart_Ip_BOARD_InitPeripherals_PBcfg.c and linflexd_Uart_Ip_Types.h have different vendor ids"
#endif
#if ((LINFLEXD_UART_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C    != LINFLEXD_UART_IP_TYPES_AR_RELEASE_MAJOR_VERSION)|| \
     (LINFLEXD_UART_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C    != LINFLEXD_UART_IP_TYPES_AR_RELEASE_MINOR_VERSION)|| \
     (LINFLEXD_UART_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION_C != LINFLEXD_UART_IP_TYPES_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of linflexd_Uart_Ip_BOARD_InitPeripherals_PBcfg.c and linflexd_Uart_Ip_Types.h are different"
#endif
#if ((LINFLEXD_UART_IP_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION_C != LINFLEXD_UART_IP_TYPES_SW_MAJOR_VERSION)|| \
     (LINFLEXD_UART_IP_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION_C != LINFLEXD_UART_IP_TYPES_SW_MINOR_VERSION)|| \
     (LINFLEXD_UART_IP_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION_C != LINFLEXD_UART_IP_TYPES_SW_PATCH_VERSION))
    #error "Software Version Numbers of linflexd_Uart_Ip_BOARD_InitPeripherals_PBcfg.c and linflexd_Uart_Ip_Types.h are different"
#endif

/* Checks against linflexd_Uart_Ip_Cfg.h */
#if (LINFLEXD_UART_IP_PBCFG_BOARD_INITPERIPHERALS_VENDOR_ID_C != LINFLEXD_UART_IP_CFG_VENDOR_ID)
    #error "linflexd_Uart_Ip_BOARD_InitPeripherals_PBcfg.c and linflexd_Uart_Ip_Cfg.h have different vendor ids"
#endif
#if ((LINFLEXD_UART_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MAJOR_VERSION_C    != LINFLEXD_UART_IP_CFG_AR_RELEASE_MAJOR_VERSION)|| \
     (LINFLEXD_UART_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_MINOR_VERSION_C    != LINFLEXD_UART_IP_CFG_AR_RELEASE_MINOR_VERSION)|| \
     (LINFLEXD_UART_IP_PBCFG_BOARD_INITPERIPHERALS_AR_RELEASE_REVISION_VERSION_C != LINFLEXD_UART_IP_CFG_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of linflexd_Uart_Ip_BOARD_InitPeripherals_PBcfg.c and linflexd_Uart_Ip_Cfg.h are different"
#endif
#if ((LINFLEXD_UART_IP_PBCFG_BOARD_INITPERIPHERALS_SW_MAJOR_VERSION_C != LINFLEXD_UART_IP_CFG_SW_MAJOR_VERSION)|| \
     (LINFLEXD_UART_IP_PBCFG_BOARD_INITPERIPHERALS_SW_MINOR_VERSION_C != LINFLEXD_UART_IP_CFG_SW_MINOR_VERSION)|| \
     (LINFLEXD_UART_IP_PBCFG_BOARD_INITPERIPHERALS_SW_PATCH_VERSION_C != LINFLEXD_UART_IP_CFG_SW_PATCH_VERSION))
    #error "Software Version Numbers of linflexd_Uart_Ip_BOARD_InitPeripherals_PBcfg.c and linflexd_Uart_Ip_Cfg.h are different"
#endif
/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/

#define UART_START_SEC_VAR_NO_INIT_UNSPECIFIED_NO_CACHEABLE
#include "Uart_MemMap.h"
extern Linflexd_Uart_Ip_StateStructureType Linflexd_Uart_Ip_apStateStructure[LINFLEXD_INSTANCE_COUNT];

#define UART_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_NO_CACHEABLE
#include "Uart_MemMap.h"

#define UART_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Uart_MemMap.h"

/**
* @brief          Hardware configuration for Linflexd Uart Hardware - Configuration:
*
* @api
*/
const Linflexd_Uart_Ip_UserConfigType Linflexd_Uart_Ip_pHwConfigPB_1_BOARD_INITPERIPHERALS =
{
    /* Actual baudrate */
    115200,
    /* Baudrate mantissa*/
    67U,
    /* Baudrate Divisor*/
    13U,
    /* Parity control */
    FALSE,
    /* Parity type */
    LINFLEXD_UART_IP_PARITY_EVEN,
    /* Number of stop bits, 1 stop bit (default) or 2 stop bits */
    LINFLEXD_UART_IP_ONE_STOP_BIT,
    /* Number of bits per transmitted/received word */
    LINFLEXD_UART_IP_8_BITS,
    /* Type of UART transfer (interrupt/dma based) */
    LINFLEXD_UART_IP_USING_INTERRUPTS,
    /* Callback to invoke for data receive.*/
    NULL_PTR,
    /* Receive callback parameter pointer.*/
    NULL_PTR,
    /* Callback to invoke for data send */
    NULL_PTR,
    /* Transmit callback parameter pointer.*/
    NULL_PTR,
    /* Callback to invoke on error conditions */
    NULL_PTR,
    /* Error callback parameter pointer */
    NULL_PTR,
#if (LINFLEXD_UART_HAS_DMA_ENABLED == STD_ON)
    /* DMA channel number for DMA-based rx. */
    255,
    /* DMA channel number for DMA-based tx. */
    255,
#endif
    /* Runtime state structure refference */
    &Linflexd_Uart_Ip_apStateStructure[1U]
};



#define UART_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Uart_MemMap.h"

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

