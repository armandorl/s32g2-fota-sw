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
#ifndef LINFLEXD_UART_IP_H
#define LINFLEXD_UART_IP_H

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
#include "Linflexd_Uart_Ip_Types.h"
#include "Linflexd_Uart_Ip_Cfg.h"
#include "Mcal.h"
#include "Linflexd_Uart_Ip_Wrapper.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define LINFLEXD_UART_IP_VENDOR_ID                    43
#define LINFLEXD_UART_IP_MODULE_ID                    255
#define LINFLEXD_UART_IP_AR_RELEASE_MAJOR_VERSION     4
#define LINFLEXD_UART_IP_AR_RELEASE_MINOR_VERSION     4
#define LINFLEXD_UART_IP_AR_RELEASE_REVISION_VERSION  0
#define LINFLEXD_UART_IP_SW_MAJOR_VERSION             1
#define LINFLEXD_UART_IP_SW_MINOR_VERSION             0
#define LINFLEXD_UART_IP_SW_PATCH_VERSION             0
/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Linflexd_Uart_Ip_Types.h */
#if (LINFLEXD_UART_IP_VENDOR_ID != LINFLEXD_UART_IP_TYPES_VENDOR_ID)
    #error "Linflexd_Uart_Ip.h and Linflexd_Uart_Ip_Types.h have different vendor ids"
#endif
#if ((LINFLEXD_UART_IP_AR_RELEASE_MAJOR_VERSION    != LINFLEXD_UART_IP_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (LINFLEXD_UART_IP_AR_RELEASE_MINOR_VERSION    != LINFLEXD_UART_IP_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (LINFLEXD_UART_IP_AR_RELEASE_REVISION_VERSION != LINFLEXD_UART_IP_TYPES_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Linflexd_Uart_Ip.h and Linflexd_Uart_Ip_Types.h are different"
#endif
#if ((LINFLEXD_UART_IP_SW_MAJOR_VERSION != LINFLEXD_UART_IP_TYPES_SW_MAJOR_VERSION) || \
     (LINFLEXD_UART_IP_SW_MINOR_VERSION != LINFLEXD_UART_IP_TYPES_SW_MINOR_VERSION) || \
     (LINFLEXD_UART_IP_SW_PATCH_VERSION != LINFLEXD_UART_IP_TYPES_SW_PATCH_VERSION))
    #error "Software Version Numbers of Linflexd_Uart_Ip.h and Linflexd_Uart_Ip_Types.h are different"
#endif

/* Checks against Linflexd_Uart_Ip_Cfg.h */
#if (LINFLEXD_UART_IP_VENDOR_ID != LINFLEXD_UART_IP_CFG_VENDOR_ID)
    #error "Linflexd_Uart_Ip.h and Linflexd_Uart_Ip_Cfg.h have different vendor ids"
#endif
#if ((LINFLEXD_UART_IP_AR_RELEASE_MAJOR_VERSION    != LINFLEXD_UART_IP_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (LINFLEXD_UART_IP_AR_RELEASE_MINOR_VERSION    != LINFLEXD_UART_IP_CFG_AR_RELEASE_MINOR_VERSION) || \
     (LINFLEXD_UART_IP_AR_RELEASE_REVISION_VERSION != LINFLEXD_UART_IP_CFG_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Linflexd_Uart_Ip.h and Linflexd_Uart_Ip_Cfg.h are different"
#endif
#if ((LINFLEXD_UART_IP_SW_MAJOR_VERSION != LINFLEXD_UART_IP_CFG_SW_MAJOR_VERSION) || \
     (LINFLEXD_UART_IP_SW_MINOR_VERSION != LINFLEXD_UART_IP_CFG_SW_MINOR_VERSION) || \
     (LINFLEXD_UART_IP_SW_PATCH_VERSION != LINFLEXD_UART_IP_CFG_SW_PATCH_VERSION))
    #error "Software Version Numbers of Linflexd_Uart_Ip.h and Linflexd_Uart_Ip_Cfg.h are different"
#endif
/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/
#define UART_START_SEC_CONFIG_DATA_UNSPECIFIED
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"
/* Calling the external Configuration symbols defined by Linflexd_Uart_Ip_Cfg.h */
LINFLEXD_UART_IP_CONFIG_EXT
#define UART_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"
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

/**
 * @brief Sets the baud rate for UART communication.
 *
 * @details This function computes the fractional and integer parts of the baud rate divisor
 *          to obtain the desired baud rate using the current protocol clock.
 *
 * @param[in] u32Instance     - LINFLEXD instance number.
 * @param[in] desiredBaudRate - Desired baud rate.
 * @param[in] clockFrequency  - Uart source clock.
 * @return Linflexd_Uart_Ip_StatusType
 * @retval LINFLEXD_UART_IP_STATUS_BUSY    - A trasfer is ongoing, therefore a baurate value change can't be possible.
 * @retval LINFLEXD_UART_IP_STATUS_ERROR   - Error in changing the baudrate.
 * @retval LINFLEXD_UART_IP_STATUS_SUCCESS - Baudrate value changed successfully.
 */
#define Linflexd_Uart_Ip_SetBaudrate(u32Instance, desiredBaudRate, clockFrequency) \
                Call_Linflexd_Uart_Ip_SetBaudrate(u32Instance, desiredBaudRate, clockFrequency)

#define UART_START_SEC_CODE
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

/**
 * @brief Gets the baud rate for UART communication.
 *
 * @details This function returns the current UART baud rate, according to register values
 * and the protocol clock frequency.
 *
 * @param[in] u32Instance         - LINFLEXD instance number.
 * @param[out] configuredBaudRate - Pointer to a valid memory location where the current baudrate value will be provided.
 * @return void
 */
void Linflexd_Uart_Ip_GetBaudRate(uint32 u32Instance, uint32 * configuredBaudRate);

#define UART_STOP_SEC_CODE
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

/**
 * @brief Initializes a LINFLEXD instance for UART operations.
 *
 *
 * @param u32Instance[in] - LINFLEXD instance number.
 * @param userConfig[in]  - User configuration structure.
 * @return void
 */
#define Linflexd_Uart_Ip_Init(u32Instance, userConfig) \
                Call_Linflexd_Uart_Ip_Init(u32Instance, userConfig)
#define UART_START_SEC_CODE
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"
/**
 * @brief Shuts down the UART functionality of the LINFLEXD module
 * by disabling interrupts and transmitter/receiver.
 *
 * @param u32Instance[in] - LINFLEXD instance number.
 * @return void
 */
void Linflexd_Uart_Ip_Deinit(uint32 u32Instance);

/**
 * @brief Sets the internal driver reference to the tx buffer.
 *
 * @details This function can be called from the tx callback to provide the driver
 * with a new buffer, for continuous transmission.
 *
 * @param u32Instance[in] - LINFLEXD instance number.
 * @param pTxBuff[in]     - Source buffer containing 8-bit data chars to send.
 * @param u32TxSize[in]   - The number of bytes to send.
 * @return Linflexd_Uart_Ip_StatusType
 * @retval LINFLEXD_UART_IP_STATUS_SUCCESS - Buffer set successfully.
 */
Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_SetTxBuffer(uint32 u32Instance,
                                                         const uint8 * pTxBuff,
                                                         uint32 u32TxSize);
/**
 * @brief Sets the internal driver reference to the rx buffer.
 *
 * @details This function can be called from the rx callback to provide the driver
 * with a new buffer, for continuous reception.
 *
 * @param u32Instance[in] - LINFLEXD instance number.
 * @param pTxBuff[in]     - Source buffer containing 8-bit data chars to receive.
 * @param u32TxSize[in]   - The number of bytes to receive.
 * @return Linflexd_Uart_Ip_StatusType
 * @retval LINFLEXD_UART_IP_STATUS_SUCCESS - Buffer set successfully.
*/
Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_SetRxBuffer(uint32 u32Instance,
                                                         uint8 * pRxBuff,
                                                         uint32 u32RxSize);

#define UART_STOP_SEC_CODE
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

/**
 * @brief Terminates a non-blocking receive early.
 *
 * @param u32Instance[in] - LINFLEXD instance number
 *
 * @return Linflexd_Uart_Ip_StatusType
 * @retval LINFLEXD_UART_IP_STATUS_SUCCESS - Operation has been successfully ended or no operation was on-going.
 */
#define Linflexd_Uart_Ip_AbortReceivingData(u32Instance) \
                Call_Linflexd_Uart_Ip_AbortReceivingData(u32Instance)
/**
 * @brief Terminates a non-blocking transfer(send) early.
 *
 * @param u32Instance[in] - LINFLEXD instance number
 *
 * @return Linflexd_Uart_Ip_StatusType
 * @retval LINFLEXD_UART_IP_STATUS_SUCCESS - Operation has been successfully ended or no operation was on-going.
 */

#define Linflexd_Uart_Ip_AbortSendingData(u32Instance) \
                Call_Linflexd_Uart_Ip_AbortSendingData(u32Instance)

/**
 * @brief Sends data using LINFLEXD module in UART mode with polling method.
 *
 * @details Blocking means that the function does not return until the transmission is complete.
 *
 * @param u32Instance[in] - LINFLEXD instance number.
 * @param pTxBuff[in]     - Source buffer containing 8-bit data chars to send.
 * @param u32TxSize[in]   - pTxBuff size.
 * @return Linflexd_Uart_Ip_StatusType
 * @retval LINFLEXD_UART_IP_STATUS_BUSY    - A trasfer is ongoing, therefore a new transfer can't begin.
 * @retval LINFLEXD_UART_IP_STATUS_ERROR   - Error in transmission.
 * @retval LINFLEXD_UART_IP_STATUS_SUCCESS - Operation ended successfully.
 * @retval LINFLEXD_UART_IP_STATUS_TIMEOUT - Operation has timeout.
 */
#define Linflexd_Uart_Ip_SyncSend(u32Instance, pTxBuff, u32TxSize) \
                Call_Linflexd_Uart_Ip_SyncSend(u32Instance, pTxBuff, u32TxSize)
/**
 * @brief Sends data using LINFLEXD module in UART mode with polling method.
 *
 * @details Blocking means that the function does not return until the transmission is complete.
 *
 * @param u32Instance[in] - LINFLEXD instance number.
 * @param pRxBuff[in]     - Source buffer containing 8-bit data chars to receive.
 * @param u32RxSize[in]   - pRxBuff size.
 * @return Linflexd_Uart_Ip_StatusType
 * @retval LINFLEXD_UART_IP_STATUS_BUSY    - A trasfer is ongoing, therefore a new transfer can't begin.
 * @retval LINFLEXD_UART_IP_STATUS_ERROR   - Error in reception.
 * @retval LINFLEXD_UART_IP_STATUS_SUCCESS - Operation ended successfully.
 * @retval LINFLEXD_UART_IP_STATUS_TIMEOUT - Operation has timeout.
 */
#define Linflexd_Uart_Ip_SyncReceive(u32Instance, pRxBuff, u32RxSize) \
                Call_Linflexd_Uart_Ip_SyncReceive(u32Instance, pRxBuff, u32RxSize)

/**
 * @brief Starts data reception from the LINFLEXD module in UART mode with non-blocking method.
 * @details This enables an a-sync method for receiving data. When used with
 * a non-blocking transmission, the UART driver can perform a full duplex operation.
 * Non-blocking means that the function returns immediately.
 * The application has to get the receive status to know when the receive is complete.
 *
 * @param u32Instance[in] - LINFLEXD instance number.
 * @param pRxBuff[in]     - Buffer containing 8-bit read data chars to be received.
 * @param u32RxSize[in]   - Size of pRxBuff.
 * @return Linflexd_Uart_Ip_StatusType
 * @retval LINFLEXD_UART_IP_STATUS_BUSY    - A trasfer is ongoing, therefore a new transfer can't begin.
 * @retval LINFLEXD_UART_IP_STATUS_SUCCESS - Operation started successfully.
 */
#define Linflexd_Uart_Ip_AsyncReceive(u32Instance, pRxBuff, u32RxSize) \
                Call_Linflexd_Uart_Ip_AsyncReceive(u32Instance, pRxBuff, u32RxSize)

/**
 * @brief Sends data using LINFLEXD module in UART mode with non-blocking method.
 *
 * @details This enables an a-sync method for transmitting data. When used with
 * a non-blocking receive, the UART driver can perform a full duplex operation.
 * Non-blocking  means that the function returns immediately.
 * The application has to get the transmit status to know when the transmission is complete.
 *
 * @param u32Instance[in] - LINFLEXD instance number.
 * @param pTxBuff[in]     - Buffer containing 8-bit read data chars to send.
 * @param u32TxSize[in]   - Size of pTxBuff.
 * @return Linflexd_Uart_Ip_StatusType
 * @retval LINFLEXD_UART_IP_STATUS_BUSY    - A trasfer is ongoing, therefore a new transfer can't begin.
 * @retval LINFLEXD_UART_IP_STATUS_SUCCESS - Operation started successfully.
 */
#define Linflexd_Uart_Ip_AsyncSend(u32Instance, pTxBuff, u32TxSize) \
                Call_Linflexd_Uart_Ip_AsyncSend(u32Instance, pTxBuff, u32TxSize)

#define UART_START_SEC_CODE
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"
/**
 * @brief Returns whether the status of the previous transmission.
 *
 * @param u32Instance[in]      - LINFLEXD instance number.
 * @param pBytesRemaining[out] - Pointer to value that is populated with the number of bytes that
 *                               have been sent in the active transfer.
 *        @note In DMA mode, this parameter may not be accurate, in case the transfer completes
 *              right after calling this function; in this edge-case, the parameter will reflect
 *              the initial transfer size, due to automatic reloading of the major loop count
 *              in the DMA transfer descriptor.
 * @return Linflexd_Uart_Ip_StatusType
 * @retval LINFLEXD_UART_IP_STATUS_BUSY    - A trasfer is ongoing.
 * @retval LINFLEXD_UART_IP_STATUS_SUCCESS - Previous operation ended successfully.
 * @retval LINFLEXD_UART_IP_STATUS_ERROR   - Previous operation had a DMA error.
 */

Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_GetTransmitStatus(uint32 u32Instance, uint32 * pBytesRemaining);


/**
 * @brief Returns whether the status of the previous reception.
 *
 * @param u32Instance[in]      - LINFLEXD instance number
 * @param pBytesRemaining[out] - Pointer to value that is filled  with the number of bytes that
 *                               still need to be received in the active transfer.
 *        @note The parameter pBytesRemaining may not be accurate, in case the transfer completes
 *              right after calling this function; in this edge-case, this parameter will
 *              have the wrong value.
 * @return Linflexd_Uart_Ip_StatusType
 * @retval LINFLEXD_UART_IP_STATUS_BUSY          - A trasfer is ongoing.
 * @retval LINFLEXD_UART_IP_STATUS_SUCCESS       - Previous operation ended successfully.
 * @retval LINFLEXD_UART_IP_STATUS_RX_OVERRUN    - Previous operation had an overrun error.
 * @retval LINFLEXD_UART_IP_STATUS_FRAMING_ERROR - Previous operation had a framing  error.
 */
Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_GetReceiveStatus(uint32 u32Instance, uint32 * pBytesRemaining);

void Linflexd_Uart_Ip_IRQHandler(uint32 u32Instance);

#if (LINFLEXD_UART_HAS_DMA_ENABLED == STD_ON)
/**
 * @internal
 * @brief   : Finish up a transmit by completing the process of sending
 * data and disabling the DMA requests. This is a part of callback for DMA major loop
 * completion, so it must match the DMA callback signature.
 * @param u32Instance LINFLEXD instance number
 * @return void
 */
void Linflexd_Uart_Ip_CompleteSendUsingDma(uint32 u32Instance);

/**
 * @internal
 * @brief   : Finish up a receive by completing the process of receiving data
 * and disabling the DMA requests. This is a part of callback for DMA major loop
 * completion, so it must match the DMA callback signature.
 * @param u32Instance LINFLEXD instance number
 * @return void
 */
void Linflexd_Uart_Ip_CompleteReceiveUsingDma(uint32 u32Instance);
#endif

#if (STD_ON == LINFLEXD_SET_USER_ACCESS_ALLOWED_AVAILABLE)
/**
* @brief   This function configure REG_PROT for UART unit so all registers under protection UART can be accessed from user mode.
* @details This function will setting UAA bit in REG_PROT_GCR to 1.
*
* @param[in]     u32Instance            Instance of the hardware unit.
*
*/
void Linflexd_Uart_Ip_SetUserAccessAllowed(uint32 u32Instance);
#endif /* if (STD_ON == LINFLEXD_SET_USER_ACCESS_ALLOWED_AVAILABLE) */

#define UART_STOP_SEC_CODE
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* LINFLEXD_UART_IP_DRIVER_H */
