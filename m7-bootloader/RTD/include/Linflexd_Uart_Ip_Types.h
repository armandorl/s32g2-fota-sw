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

#ifndef LINFLEXD_UART_IP_TYPES_H
#define LINFLEXD_UART_IP_TYPES_H

/**
*   @file
*   @defgroup linflexd_uart_ip Linflexd UART IPL
*   @addtogroup  linflexd_uart_ip Linflexd UART IPL
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
#include "Linflexd_Uart_Ip_HwAccess.h"
/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define LINFLEXD_UART_IP_TYPES_VENDOR_ID                    43
#define LINFLEXD_UART_IP_TYPES_MODULE_ID                    255
#define LINFLEXD_UART_IP_TYPES_AR_RELEASE_MAJOR_VERSION     4
#define LINFLEXD_UART_IP_TYPES_AR_RELEASE_MINOR_VERSION     4
#define LINFLEXD_UART_IP_TYPES_AR_RELEASE_REVISION_VERSION  0
#define LINFLEXD_UART_IP_TYPES_SW_MAJOR_VERSION             1
#define LINFLEXD_UART_IP_TYPES_SW_MINOR_VERSION             0
#define LINFLEXD_UART_IP_TYPES_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Linflexd_Uart_Ip_Types.h */
#if (LINFLEXD_UART_IP_HWACCESS_VENDOR_ID != LINFLEXD_UART_IP_TYPES_VENDOR_ID)
    #error "Linflexd_Uart_Ip_HwAccess.h and Linflexd_Uart_Ip_Types.h have different vendor ids"
#endif
#if ((LINFLEXD_UART_IP_HWACCESS_AR_RELEASE_MAJOR_VERSION    != LINFLEXD_UART_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (LINFLEXD_UART_IP_HWACCESS_AR_RELEASE_MINOR_VERSION    != LINFLEXD_UART_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (LINFLEXD_UART_IP_HWACCESS_AR_RELEASE_REVISION_VERSION != LINFLEXD_UART_IP_TYPES_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Linflexd_Uart_Ip_HwAccess.h and Linflexd_Uart_Ip_Types.h are different"
#endif
#if ((LINFLEXD_UART_IP_HWACCESS_SW_MAJOR_VERSION != LINFLEXD_UART_IP_TYPES_SW_MAJOR_VERSION) || \
     (LINFLEXD_UART_IP_HWACCESS_SW_MINOR_VERSION != LINFLEXD_UART_IP_TYPES_SW_MINOR_VERSION) || \
     (LINFLEXD_UART_IP_HWACCESS_SW_PATCH_VERSION != LINFLEXD_UART_IP_TYPES_SW_PATCH_VERSION))
    #error "Software Version Numbers of Linflexd_Uart_Ip_HwAccess.h and Linflexd_Uart_Ip_Types.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if current file and StandardTypes.h header file are of the same Autosar version */
    #if ((LINFLEXD_UART_IP_TYPES_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
            (LINFLEXD_UART_IP_TYPES_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION))
        #error "Linflexd_Uart_Ip_Types.h and StandardTypes.h are different"
    #endif
#endif
/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       TYPES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/**
 * @brief Type of UART a-sync transfer (based on interrupts or DMA).
 *
 *
 */
typedef enum
{
    LINFLEXD_UART_IP_USING_DMA         = 0U,    /**< @brief The driver will use DMA to perform UART transfer */
    LINFLEXD_UART_IP_USING_INTERRUPTS  = 1U     /**< @brief The driver will use interrupts to perform UART transfer */
} Linflexd_Uart_Ip_TransferType;

/**
 * @brief Driver status type.
 *
 *
 * */
typedef enum
{
    LINFLEXD_UART_IP_STATUS_SUCCESS                    = 0x00U,  /**< @brief Generic operation success status */
    LINFLEXD_UART_IP_STATUS_ERROR                      = 0x01U,  /**< @brief Generic operation failure status */
    LINFLEXD_UART_IP_STATUS_BUSY                       = 0x02U,  /**< @brief Generic operation busy status */
    LINFLEXD_UART_IP_STATUS_TIMEOUT                    = 0x03U,  /**< @brief Generic operation timeout status */
    LINFLEXD_UART_IP_STATUS_TX_UNDERRUN                = 0x04U,  /**< @brief TX underrun error */
    LINFLEXD_UART_IP_STATUS_RX_OVERRUN                 = 0x05U,  /**< @brief RX overrun error */
    LINFLEXD_UART_IP_STATUS_ABORTED                    = 0x06U,  /**< @brief* A transfer was aborted */
    LINFLEXD_UART_IP_STATUS_FRAMING_ERROR              = 0x07U,  /**< @brief Framing error */
    LINFLEXD_UART_IP_STATUS_PARITY_ERROR               = 0x08U,  /**< @brief Parity error */
    LINFLEXD_UART_IP_STATUS_NOISE_ERROR                = 0x09U,  /**< @brief Noise error */

} Linflexd_Uart_Ip_StatusType;

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
 * @brief Define the enum of the events which can trigger UART callback
 *
 * @details This enum should include the events for all platforms.
 *
 *
 */
typedef enum
{
    LINFLEXD_UART_IP_EVENT_RX_FULL      = 0x00U,    /**< @brief Rx buffer is full */
    LINFLEXD_UART_IP_EVENT_TX_EMPTY     = 0x01U,    /**< @brief Tx buffer is empty */
    LINFLEXD_UART_IP_EVENT_END_TRANSFER = 0x02U,    /**< @brief The current transfer is ending */
    LINFLEXD_UART_IP_EVENT_ERROR        = 0x03U,    /**< @brief An error occured during transfer */
} Linflexd_Uart_Ip_EventType;

/**
 * @brief Callback for all peripherals which support UART features
 *
 *
 */
typedef void (*Linflexd_Uart_Ip_CallbackType)(uint8 hwInstance,
                                            void *driverState,
                                            Linflexd_Uart_Ip_EventType event,
                                            void *userData);


/**
 * @brief Runtime State of the UART driver.
 *
 *
 */
typedef struct
{
    uint32 u32Baudrate;                                     /**< @brief Variable that indicates if structure belongs to an instance already initialized.*/
    const uint8 * pTxBuff;                                  /**< @brief The buffer of data being sent.*/
    uint8 * pRxBuff;                                        /**< @brief The buffer of received data.*/
    volatile uint32 u32TxSize;                              /**< @brief The remaining number of bytes to be transmitted. */
    volatile uint32 u32RxSize;                              /**< @brief The remaining number of bytes to be received. */
    volatile boolean bIsTxBusy;                             /**< @brief True if there is an active transmit.*/
    volatile boolean bIsRxBusy;                             /**< @brief True if there is an active receive.*/
    volatile Linflexd_Uart_Ip_StatusType eTransmitStatus;   /**< @brief Status of last driver transmit operation */
    volatile Linflexd_Uart_Ip_StatusType eReceiveStatus;    /**< @brief Status of last driver receive operation */
    boolean bIsDriverInitialized;                           /**< @brief Variable that indicates if driver is initialized or not */

} Linflexd_Uart_Ip_StateStructureType;

/**
 *  @brief LINFLEXD configuration structure
 *
 *
 */
typedef struct
{
    uint32 u32BaudRate;                                 /**< @brief Baudrate value*/
    uint32 u32BaudRateMantissa;                         /**< @brief Baudrate mantissa*/
    uint8 u8BaudRateFractionalDivisor;                  /**< @brief Baudrate Divisor*/
    /**
     *
     * @brief    Parity control - enabled/disabled
     * @details: This parameter is valid only for 8/16 bits words;
     *           for 7/15 word length parity is always enabled
     */
    boolean bParityCheck;

    Linflexd_Uart_Ip_ParityType eParityType;            /**< @brief always 0/always 1/even/odd */
    Linflexd_Uart_Ip_StopBitsCountType eStopBitsCount;  /**< @brief number of stop bits, 1 stop bit (default) or 2 stop bits */
    Linflexd_Uart_Ip_WordLengthType eWordLength;        /**< @brief number of bits per transmitted/received word */
    Linflexd_Uart_Ip_TransferType eTransferType;        /**< @brief Type of UART transfer (interrupt/dma based) */
    Linflexd_Uart_Ip_CallbackType pfRxCallback;         /**< @brief Callback to invoke for data receive */
    void * pRxCallbackParam;                            /**< @brief Receive callback parameter pointer.*/
    Linflexd_Uart_Ip_CallbackType pfTxCallback;         /**< @brief Callback to invoke for data send */
    void * pTxCallbackParam;                            /**< @brief Transmit callback parameter pointer.*/
    Linflexd_Uart_Ip_CallbackType pfErrorCallback;      /**< @brief Callback to invoke on error conditions */
    void * pErrorCallbackParam;                         /**< @brief Error callback parameter pointer */
#if (LINFLEXD_UART_HAS_DMA_ENABLED == STD_ON)
    uint8 u8RxDMAChannel;                               /**< @brief DMA channel number for DMA-based rx.
                                                                    If DMA mode is not used this field will be ignored. */
    uint8 u8TxDMAChannel;                               /**< @brief DMA channel number for DMA-based tx.
                                                                    If DMA mode is not used this field will be ignored. */
#endif
    Linflexd_Uart_Ip_StateStructureType* pStateStruct;  /**< @brief Runtime state structure refference */

} Linflexd_Uart_Ip_UserConfigType;

 /**
*
* @brief   Baudrate values supported by the driver
*/
typedef enum
{
    UART_BAUDRATE_1200   = 1200,
 	UART_BAUDRATE_2400   = 2400,
	UART_BAUDRATE_4800   = 4800,
	UART_BAUDRATE_7200   = 7200,
	UART_BAUDRATE_9600   = 9600,
	UART_BAUDRATE_14400  = 14400,
	UART_BAUDRATE_19200  = 19200,
	UART_BAUDRATE_28800  = 28800,
	UART_BAUDRATE_38400  = 38400,
	UART_BAUDRATE_57600  = 57600,
	UART_BAUDRATE_115200 = 115200,
	UART_BAUDRATE_230400 = 230400,

}
Linflexd_Uart_Ip_BaudrateType;
/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/**  @} */

#endif /* LINFLEXD_UART_IP_TYPES_H */


