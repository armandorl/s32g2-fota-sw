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

#ifndef HSE_IP_H
#define HSE_IP_H

/**
*   @file
*
*   @addtogroup HSE_IP
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
#include "hse_interface.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define HSE_IP_VENDOR_ID_H                       43
#define HSE_IP_SW_MAJOR_VERSION_H                1
#define HSE_IP_SW_MINOR_VERSION_H                0
#define HSE_IP_SW_PATCH_VERSION_H                0
#define HSE_IP_AR_RELEASE_MAJOR_VERSION_H        4
#define HSE_IP_AR_RELEASE_MINOR_VERSION_H        4


/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if the files Hse_Ip.h and StandardTypes.h are of the same AutoSar version */
#if ((HSE_IP_AR_RELEASE_MAJOR_VERSION_H != STD_AR_RELEASE_MAJOR_VERSION) || \
     (HSE_IP_AR_RELEASE_MINOR_VERSION_H != STD_AR_RELEASE_MINOR_VERSION)    \
    )
    #error "AutoSar Version Numbers of Hse_Ip.h and StandardTypes.h are different"
#endif
#endif

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/** @brief Macro returned when no MU channel is available */
#define HSE_IP_INVALID_MU_CHANNEL_U8        ((uint8)0xFFU)

/** @brief Extension to the list of responses returned by HSE */
#define HSE_SRV_RSP_NO_RESPONSE             ((hseSrvResponse_t)0xBB55BB55UL)

/** @brief   Type defining HseSrv callback type for notifications that will be sent to the caller when
            a response is received from HSE, as a result of an asynchronous request */
typedef void (*pfHseIpResponseCallbackType)(uint8 u8MuInstance, uint8 u8MuChannel, hseSrvResponse_t HseResponse, void* pCallbackParam);

/** @brief   Type defining HseSrv callback type for notifications that will be sent to the caller when
            HSE triggers an interrupt signaling certain intern events */
typedef void (*pfHseIpGenericPurposeCallbackType)(uint8 u8MuInstance, uint32 u32HseNotifEvents);

/** @brief   Enum defining the possible return type values for the HSE IP API */
typedef enum
{
    STATUS_HSE_IP_SUCCESS = 0x00U,  /*!< Operation success status */
    STATUS_HSE_IP_ERROR             /*!< Operation error status */
} status_hse_ip_t;

/** @brief       Enum defining the possible types of service requests that can be sent to HSE
* @implements    Hse_Ip_ReqTypeType_typedef
*/
typedef enum
{
    HSE_IP_REQTYPE_SYNC = 0UL,  /*!< Synchronous - the service request function does not return until the HSE completes
                                     the request, or the timeout expires */
    HSE_IP_REQTYPE_ASYNC_IRQ,   /*!< Asynchronous using interrupts - the service request function returns right after
                                     sending the request to HSE; an interrupt is triggered when HSE completes the request
                                     (application can be notified through the channel callback) */
    HSE_IP_REQTYPE_ASYNC_POLL   /*!< Asynchronous polling - the service request function returns right after sending the
                                     request to HSE; application must poll the driver by calling Hse_Ip_MainFunction */
}Hse_Ip_ReqTypeType;

/** @brief   Structure defining how a request sent from the upper layer to Hse_Ip should look like */
typedef struct
{
    Hse_Ip_ReqTypeType                  eReqType;       /*!< Selects the request type (SYNC/ASYNC) */
    pfHseIpResponseCallbackType         pfCallback;     /*!< The callback for asynchronous request */
    void*                               pCallbackParam; /*!< Parameter used to call the asynchronous callback(can be NULL) */
    uint32                              u32Timeout;     /*!< Timeout for the synchronous requests (in us or ticks depending on selected counter) */
} Hse_Ip_ReqType;

/** @brief   Structure defining the internal state machine of the Hse_Ip layer for a given MU instance */
typedef struct
{
    Hse_Ip_ReqType*                     apChannelRequest[HSE_NUM_OF_CHANNELS_PER_MU];    /*!< Reference to channel request */
    volatile boolean                    abChannelAllocated[HSE_NUM_OF_CHANNELS_PER_MU];  /*!< Channel allocated flag */
    volatile boolean                    abChannelBusy[HSE_NUM_OF_CHANNELS_PER_MU];       /*!< Channel busy processing a request flag */
    pfHseIpGenericPurposeCallbackType   pfGenericPurposeCallback;                        /*!< General purpose callback */
} Hse_Ip_MuStateType;

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/
#define CRYPTO_START_SEC_CODE
#include "Crypto_MemMap.h"

/*!
 * @brief       Initializes the HSE Host driver.
 * @details     This function initializes the HSE host driver over an MU instance. It initializes the state
 *              structure with default values.
 *
 * @param[in]   u8MuInstance    MU Instance number
 * @param[in]   pHseIpMuState   Pointer to the state structure which will be used for holding
 *                              the internal state of the driver.
 *
 * @return      An error code or STATUS_HSE_IP_SUCCESS
 */
status_hse_ip_t Hse_Ip_Init
(
    uint8               u8MuInstance,
    Hse_Ip_MuStateType* pHseIpMuState
);

/*!
 * @brief       Deinitializes the HSE Host driver.
 * @details     This function clears the reference to the previous state structure.
 *
 * @param[in]   u8MuInstance: MU Instance number
 *
 * @return      An error code or STATUS_HSE_IP_SUCCESS
 */
status_hse_ip_t Hse_Ip_Deinit
(
    uint8 u8MuInstance
);

/*!
 * @brief       Retrieves the next free channel to be used by the application.
 * @details     This function finds the next available channel and locks it for the use of the current task.
 *              If all channels are allocated, the function returns HSE_IP_INVALID_MU_CHANNEL_U8.
 *
 * @param[in]   u8MuInstance    MU Instance number
 *
 * @return      HSE channel number or HSE_IP_INVALID_MU_CHANNEL_U8
 */
uint8 Hse_Ip_GetFreeChannel
(
    uint8 u8MuInstance
);

/*!
 * @brief       Releases a channel previously obtained.
 * @details     This releases the lock on an MU channel, making it available for other tasks.
 *
 * @param[in]   u8MuInstance    MU Instance number
 * @param[in]   u8MuChannel     MU channel to be released
 *
 * @return      void
 */
void Hse_Ip_ReleaseChannel
(
    uint8 u8MuInstance,
    uint8 u8MuChannel
);

/*!
 * @brief       Sends a service request to HSE.
 * @details     This function sends a service request to HSE on the specified channel.
 *              If the request type is synchronous, this function will not return until either the request has been services,
 *              or the timeout expires.
 *              If the request type is asynchronous, the function returns right after launching the service request to HSE.
 *              The application then either needs to poll the result of the request (calling Hse_Ip_MainFunction()) or wait
 *              to be notified by the interrupt when the service is done.
 *
 * @param[in]   u8MuInstance    MU Instance number
 * @param[in]   u8MuChannel     MU channel number
 * @param[in]   pReqType        Structure that describes the request parameters:
 *                              type (sync/interrupts/polling), callback, timeout
 * @param[in]   pHseSrvDesc     Requested service descriptor
 *
 * @return      HSE service response
 */
hseSrvResponse_t Hse_Ip_ServiceRequest
(
    uint8               u8MuInstance,
    uint8               u8MuChannel,
    Hse_Ip_ReqType*     pRequest,
    hseSrvDescriptor_t* pHseSrvDesc
);

/*!
 * @brief       Function that should be called cyclically to process the requests sent using asynchronous poll method .
 * @details     After an asynchronous poll request is sent using Hse_Ip_ServiceRequest() service, the layer on top of the Hse_Ip
 *              should call periodically the Hse_Ip_MainFunction() in order to retrieve message processing status from HSE
 *              and when a response is received, call the callback sent at request time.
 *
 * @param[in]   u8MuInstance    MU Instance number
 *
 * @return      void
 */
void Hse_Ip_MainFunction
(
    uint8 u8MuInstance
);

/*!
 * @brief       Returns the HSE firmware status.
 * @details     This function retrieves the global status of the HSE firmware, read from MU_FSR register.
 *
 * @param[in]   none
 *
 * @return      void
 */
hseStatus_t Hse_Ip_GetHseStatus(void);

/*!
 * @brief       Registers a general purpose callback.
 * @details     This function saves the reference to a generic callback to be called whenever an error is reported by HSE.
 *              The signature of the callback should be:
 *              void callback(uint8 u8MuInstance, uint32 u32HseNotifEvents)
 *
 * @param[in]   u8MuInstance    MU Instance number
 * @param[in]   notifEventsMask HSE Errors to be enabled (see definition of hseError_t).
 * @param[in]   callback        Pointer to the callback function.
 *
 * @return      void
 */
void Hse_Ip_RegisterGenericCallback
(
    uint8                             u8MuInstance,
    uint32                            u32NotifEventsMask,
    pfHseIpGenericPurposeCallbackType pfCallback
);

/*!
 * @brief       Rx interrupt handler.
 * @details     This function processes the RX related interrupts from MU Ip layer
 *
 * @param[in]   u8MuInstance    MU Instance number
 *
 * @return      void
 */
void Hse_Ip_RxIrqHandler
(
    uint8 u8MuInstance
);

/*!
 * @brief       General Purpose interrupt handler.
 * @details     This function processes the General Purpose related interrupts from MU Ip layer
 *
 * @param[in]   u8MuInstance    MU Instance number
 *
 * @return      void
 */
void Hse_Ip_GeneralPurposeIrqHandler
(
    uint8 u8MuInstance
);


#define CRYPTO_STOP_SEC_CODE
#include "Crypto_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* HSE_IP_H */
