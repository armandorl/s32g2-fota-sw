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
*   @file
*   @internal
*   @addtogroup UART_IPW_DRIVER
*   @{
*/
#ifndef LINFLEXD_UART_IP_WRAPPER_H_
#define LINFLEXD_UART_IP_WRAPPER_H_

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define UART_START_SEC_CODE
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"
#if (STD_ON == LINFLEXD_SET_USER_ACCESS_ALLOWED_AVAILABLE)
        #define Call_Linflexd_Uart_Ip_Init(u32Instance, userConfig) \
                OsIf_Trusted_Call2params(Linflexd_Uart_Ip_Init_Privileged, u32Instance, userConfig)

        #define Call_Linflexd_Uart_Ip_SetBaudrate(u32Instance, desiredBaudRate, clockFrequency) \
                OsIf_Trusted_Call_Return3param(Linflexd_Uart_Ip_SetBaudrate_Privileged, u32Instance, desiredBaudRate, clockFrequency)

        #define Call_Linflexd_Uart_Ip_SyncReceive(u32Instance, pRxBuff, u32RxSize) \
                OsIf_Trusted_Call_Return3param(Linflexd_Uart_Ip_SyncReceive_Privileged, u32Instance, pRxBuff, u32RxSize)

        #define Call_Linflexd_Uart_Ip_AsyncReceive(u32Instance, pRxBuff, u32RxSize) \
                OsIf_Trusted_Call_Return3param(Linflexd_Uart_Ip_AsyncReceive_Privileged, u32Instance, pRxBuff, u32RxSize)

        #define Call_Linflexd_Uart_Ip_SyncSend(u32Instance, pTxBuff, u32TxSize) \
                OsIf_Trusted_Call_Return3param(Linflexd_Uart_Ip_SyncSend_Privileged, u32Instance, pTxBuff, u32TxSize)

        #define Call_Linflexd_Uart_Ip_AsyncSend(u32Instance, pTxBuff, u32TxSize) \
                OsIf_Trusted_Call_Return3param(Linflexd_Uart_Ip_AsyncSend_Privileged, u32Instance, pTxBuff, u32TxSize)

        #define Call_Linflexd_Uart_Ip_AbortReceivingData(u32Instance) \
                OsIf_Trusted_Call_Return1param(Linflexd_Uart_Ip_AbortReceivingData_Privileged, u32Instance)

        #define Call_Linflexd_Uart_Ip_AbortSendingData(u32Instance) \
                OsIf_Trusted_Call_Return1param(Linflexd_Uart_Ip_AbortSendingData_Privileged, u32Instance)
#else
        #define Call_Linflexd_Uart_Ip_Init(u32Instance, userConfig) \
                Linflexd_Uart_Ip_Init_Privileged(u32Instance, userConfig)

        #define Call_Linflexd_Uart_Ip_SetBaudrate(u32Instance, desiredBaudRate, clockFrequency) \
                Linflexd_Uart_Ip_SetBaudrate_Privileged(u32Instance, desiredBaudRate, clockFrequency)

        #define Call_Linflexd_Uart_Ip_SyncReceive(u32Instance, pRxBuff, u32RxSize) \
                Linflexd_Uart_Ip_SyncReceive_Privileged(u32Instance, pRxBuff, u32RxSize)

        #define Call_Linflexd_Uart_Ip_AsyncReceive(u32Instance, pRxBuff, u32RxSize) \
                Linflexd_Uart_Ip_AsyncReceive_Privileged(u32Instance, pRxBuff, u32RxSize)

        #define Call_Linflexd_Uart_Ip_SyncSend(u32Instance, pTxBuff, u32TxSize) \
                Linflexd_Uart_Ip_SyncSend_Privileged(u32Instance, pTxBuff, u32TxSize)

        #define Call_Linflexd_Uart_Ip_AsyncSend(u32Instance, pTxBuff, u32TxSize) \
                Linflexd_Uart_Ip_AsyncSend_Privileged(u32Instance, pTxBuff, u32TxSize)

        #define Call_Linflexd_Uart_Ip_AbortReceivingData(u32Instance) \
                Linflexd_Uart_Ip_AbortReceivingData_Privileged(u32Instance)

        #define Call_Linflexd_Uart_Ip_AbortSendingData(u32Instance) \
                Linflexd_Uart_Ip_AbortSendingData_Privileged(u32Instance)

#endif
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

/**
 * @internal
 * @brief Initializes a LINFLEXD instance for UART operation.
 *
 * The caller provides memory for the driver state structures during initialization.
 * The user must enable the LINFLEXD clock source in the application to initialize the module.
 *
 * @param u32Instance LINFLEXD instance number
 * @param userConfig user configuration structure
 * @return void
 */
void Linflexd_Uart_Ip_Init_Privileged(uint32 u32Instance, const Linflexd_Uart_Ip_UserConfigType * userConfig);

/**
 * @internal
 * @brief Sets the baud rate for UART communication.
 *
 * This function computes the fractional and integer parts of the baud rate divisor
 * to obtain the desired baud rate using the current protocol clock.
 *
 * @param u32Instance LINFLEXD instance number
 * @param desiredBaudRate desired baud rate
 * @param clockFrequency Uart source clock
 * @return An error code or STATUS_UART_SUCCESS
 */
Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_SetBaudrate_Privileged(uint32 u32Instance,
                                                                    Linflexd_Uart_Ip_BaudrateType desiredBaudRate,
                                                                    uint32 clockFrequency);

/**
 * @internal
 * @brief Retrieves data from the LINFLEXD module in UART mode with polling method.
 *
 * Blocking means that the function does not return until the receive is complete.
 *
 * @param u32Instance LINFLEXD instance number
 * @param pRxBuff buffer containing 8-bit read data chars received
 * @param u32RxSize the number of bytes to receive
 * @return An error code orLINFLEXD_UART_IP_STATUS_SUCCESS
 */
Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_SyncReceive_Privileged(uint32 u32Instance,
                                                                    uint8 * pRxBuff,
                                                                    uint32 u32RxSize);

/**
 * @internal
 * @brief Retrieves data from the LINFLEXD module in UART mode with non-blocking method.
 * This enables an a-sync method for receiving data. When used with
 * a non-blocking transmission, the UART driver can perform a full duplex operation.
 * Non-blocking means that the function returns immediately.
 * The application has to get the receive status to know when the receive is complete.
 *
 * @param u32Instance LINFLEXD instance number
 * @param pRxBuff buffer containing 8-bit read data chars received
 * @param u32RxSize the number of bytes to receive
 * @return An error code orLINFLEXD_UART_IP_STATUS_SUCCESS
 */
Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_AsyncReceive_Privileged(uint32 u32Instance,
                                                                     uint8 * pRxBuff,
                                                                     uint32 u32RxSize);

/**
 * @internal
 * @brief Sends data using LINFLEXD module in UART mode with polling method.
 *
 * Blocking means that the function does not return until the transmission is complete.
 *
 * @param u32Instance LINFLEXD instance number
 * @param pTxBuff source buffer containing 8-bit data chars to send
 * @param u32TxSize the number of bytes to send
 * @return An error code orLINFLEXD_UART_IP_STATUS_SUCCESS
 */

Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_SyncSend_Privileged(uint32 u32Instance,
                                                                 const uint8 *pTxBuff,
                                                                 uint32 u32TxSize);

/**
 * @internal
 * @brief Sends data using LINFLEXD module in UART mode with non-blocking method.
 *
 * This enables an a-sync method for transmitting data. When used with
 * a non-blocking receive, the UART driver can perform a full duplex operation.
 * Non-blocking  means that the function returns immediately.
 * The application has to get the transmit status to know when the transmission is complete.
 *
 * @param u32Instance LINFLEXD instance number
 * @param pTxBuff source buffer containing 8-bit data chars to send
 * @param u32TxSize the number of bytes to send
 * @return An error code orLINFLEXD_UART_IP_STATUS_SUCCESS
 */
Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_AsyncSend_Privileged(uint32 u32Instance,
                                                                  const uint8 * pTxBuff,
                                                                  uint32 u32TxSize);

/**
 * @internal
 * @brief Terminates a non-blocking receive early.
 *
 * @param u32Instance LINFLEXD instance number
 *
 * @returnLINFLEXD_UART_IP_STATUS_SUCCESS
 */
Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_AbortReceivingData_Privileged(uint32 u32Instance);
/**
 * @internal
 * @brief Terminates a non-blocking transmission early.
 *
 * @param u32Instance LINFLEXD instance number
 * @returnLINFLEXD_UART_IP_STATUS_SUCCESS
 */

Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_AbortSendingData_Privileged(uint32 u32Instance);

#define UART_STOP_SEC_CODE
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* LINFLEXD_UART_IP_WRAPPER_H_ */

/** @} */
