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
#include "Hse_Ip.h"
#include "Mu_Ip.h"
#include "SchM_Crypto.h"
#if (STD_ON == HSE_IP_DEV_ERROR_DETECT)
    #include "Devassert.h"
#endif /* (STD_ON == HSE_IP_DEV_ERROR_DETECT) */

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define HSE_IP_VENDOR_ID_C                    43
#define HSE_IP_SW_MAJOR_VERSION_C             1
#define HSE_IP_SW_MINOR_VERSION_C             0
#define HSE_IP_SW_PATCH_VERSION_C             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if Hse_Ip source file and Hse_Ip header file are of the same vendor */
#if (HSE_IP_VENDOR_ID_C != HSE_IP_VENDOR_ID_H)
    #error "Hse_Ip.c and Hse_Ip.h have different vendor ids"
#endif

/* Check if Hse_Ip source file and Hse_Ip header file are of the same Software version */
#if ((HSE_IP_SW_MAJOR_VERSION_C != HSE_IP_SW_MAJOR_VERSION_H) || \
     (HSE_IP_SW_MINOR_VERSION_C != HSE_IP_SW_MINOR_VERSION_H) || \
     (HSE_IP_SW_PATCH_VERSION_C != HSE_IP_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Hse_Ip.c and Hse_Ip.h are different"
#endif


/* Check if Hse_Ip source file and Mu_Ip header file are of the same vendor */
#if (HSE_IP_VENDOR_ID_C != MU_IP_VENDOR_ID_H)
    #error "Hse_Ip.c and Mu_Ip.h have different vendor ids"
#endif

/* Check if Hse_Ip source file and Mu_Ip header file are of the same Software version */
#if ((HSE_IP_SW_MAJOR_VERSION_C != MU_IP_SW_MAJOR_VERSION_H) || \
     (HSE_IP_SW_MINOR_VERSION_C != MU_IP_SW_MINOR_VERSION_H) || \
     (HSE_IP_SW_PATCH_VERSION_C != MU_IP_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Hse_Ip.c and Mu_Ip.h are different"
#endif

/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/
/*! @brief Mask for HSE status bits. */
#define HSE_IP_HSE_STATUS_MASK_U32           (0xFFFF0000UL)
/*! @brief Shift for HSE status bits. */
#define HSE_IP_HSE_STATUS_SHIFT_U8           (16U)
/*! @brief Mask for GSR error flag bits. */
#define HSE_IP_HSE_ALL_ERROR_FLAGS_MASK_U32  (0xFFFFFFFFUL)
/*! @brief Mask for channel busy bits. */
#define HSE_IP_HSE_CHANNEL_BUSY_MASK_U32     (0x0000FFFFUL)

/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/
#define CRYPTO_START_SEC_CONST_UNSPECIFIED
#include "Crypto_MemMap.h"

/*! @brief Array of MU base pointers */
static MU_Type* const Hse_Ip_apMuBase[HSE_NUM_OF_MU_INSTANCES] = MU_HOST_BASE_PTRS;

#define CRYPTO_STOP_SEC_CONST_UNSPECIFIED
#include "Crypto_MemMap.h"

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/

#define CRYPTO_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Crypto_MemMap.h"

/*! @brief Array of state structures per MU instance */
static Hse_Ip_MuStateType* Hse_Ip_apMuState[HSE_NUM_OF_MU_INSTANCES];

#define CRYPTO_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Crypto_MemMap.h"

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

#define CRYPTO_START_SEC_CODE
#include "Crypto_MemMap.h"

/*!
 * @brief       Finds a channel with a HSE response.
 * @details     Searches through channels until finds the first one with a HSE response having the requested type and returns its index.
 *
 * @param[in]   u8MuInstance    MU Instance number
 * @param[in]   eReqType        Request type
 *
 * @return      HSE channel index or HSE_IP_INVALID_MU_CHANNEL_U8
 */
static uint8 Hse_Ip_GetFirstChannelWithResponseReady
(
    uint8              u8MuInstance,
    Hse_Ip_ReqTypeType eReqType
);

/*!
 * @brief       Processes the HSE responses.
 * @details     Processes all the responses found having the specified request type.
 *
 * @param[in]   u8MuInstance    MU Instance number
 * @param[in]   eReqType        Request type
 *
 * @return      void
 */
static void Hse_Ip_ProcessReceivedResponses
(
    uint8              u8MuInstance,
    Hse_Ip_ReqTypeType eReqType
);

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/
static uint8 Hse_Ip_GetFirstChannelWithResponseReady
(
    uint8              u8MuInstance,
    Hse_Ip_ReqTypeType eReqType
)
{
    uint8                 u8MuChannel   = 0U;
    boolean               bChannelFound = (boolean)FALSE;
    uint32                u32ReceiveStatus;
    const Hse_Ip_ReqType* pChannelRequest;

    u32ReceiveStatus = Mu_Ip_GetRxStatusRegister(Hse_Ip_apMuBase[u8MuInstance]);

    while (0U != u32ReceiveStatus)
    {
        pChannelRequest = Hse_Ip_apMuState[u8MuInstance]->apChannelRequest[u8MuChannel];

        if (((uint32)0x01U == (u32ReceiveStatus & (uint32)0x01U)) &&
            ((NULL_PTR != pChannelRequest) && (pChannelRequest->eReqType == eReqType)))
        {
            bChannelFound = (boolean)TRUE;
            break;
        }
        else
        {
            u32ReceiveStatus = u32ReceiveStatus >> 1U;
            u8MuChannel++;
        }
    }

    if((boolean)FALSE == bChannelFound)
    {
        u8MuChannel = HSE_IP_INVALID_MU_CHANNEL_U8;
    }
    return u8MuChannel;
}

static void Hse_Ip_ProcessReceivedResponses
(
    uint8              u8MuInstance,
    Hse_Ip_ReqTypeType eReqType
)
{
    hseSrvResponse_t            HseResponse;
    Hse_Ip_MuStateType*         pHseIpMuState;
    uint8                       u8MuChannel;
    pfHseIpResponseCallbackType pfCallback;
    void*                       pCallbackParam;

    pHseIpMuState = Hse_Ip_apMuState[u8MuInstance];
    u8MuChannel   = Hse_Ip_GetFirstChannelWithResponseReady(u8MuInstance, eReqType);

    while ( HSE_IP_INVALID_MU_CHANNEL_U8 != u8MuChannel )
    {
        /* Disable Rx interrupt for the channel where the message was received */
        if(HSE_IP_REQTYPE_ASYNC_IRQ == pHseIpMuState->apChannelRequest[u8MuChannel]->eReqType)
        {
            Mu_Ip_SetRxIrqEnable(Hse_Ip_apMuBase[u8MuInstance], u8MuChannel, (boolean)FALSE);
        }
        /* Read the response from HSE */
        HseResponse = ((hseSrvResponse_t)Mu_Ip_GetRxRegister(Hse_Ip_apMuBase[u8MuInstance], u8MuChannel));
        /* Mark the channel as not busy processing a request */
        pHseIpMuState->abChannelBusy[u8MuChannel] = (boolean)FALSE;
        /* Prepare the callback and its parameter */
        pfCallback     = pHseIpMuState->apChannelRequest[u8MuChannel]->pfCallback;
        pCallbackParam = pHseIpMuState->apChannelRequest[u8MuChannel]->pCallbackParam;
        /* Release the allocated channel */
        Hse_Ip_ReleaseChannel(u8MuInstance, u8MuChannel);
        /* Check if this channel has an associated callback */
        if(NULL_PTR != pfCallback)
        {
            /* Call the callback provided when the request was made */
            pfCallback(u8MuInstance, u8MuChannel, HseResponse, pCallbackParam);
        }
        /* Check again if new messages have been received from HSE */
        u8MuChannel = Hse_Ip_GetFirstChannelWithResponseReady(u8MuInstance, eReqType);
    }
}

/*==================================================================================================
*                                        GLOBAL FUNCTIONS PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/
/**
* @implements     Hse_Ip_Init_Activity
*/
status_hse_ip_t Hse_Ip_Init
(
    uint8               u8MuInstance,
    Hse_Ip_MuStateType* pHseIpMuState
)
{
    uint8 u8MuChannel;

#if (STD_ON == HSE_IP_DEV_ERROR_DETECT)
    /* Check the validity of the input parameters */
    DevAssert((u8MuInstance  <  HSE_NUM_OF_MU_INSTANCES));
    DevAssert((pHseIpMuState != NULL_PTR));
    /* Check that the driver is not already initialized */
    DevAssert((Hse_Ip_apMuState[u8MuInstance] == NULL_PTR));
#endif /* (STD_ON == HSE_IP_DEV_ERROR_DETECT) */

    /* Fill the state structure with default values */
    pHseIpMuState->pfGenericPurposeCallback = NULL_PTR;

    for (u8MuChannel = 0U; u8MuChannel < HSE_NUM_OF_CHANNELS_PER_MU; u8MuChannel++)
    {
        /* Perform a dummy read of the channel Rx register in order to clear any pending responses not yet processed */
        (void)Mu_Ip_GetRxRegister(Hse_Ip_apMuBase[u8MuInstance], u8MuChannel);
        /* Mark the channel as not busy processing a request */
        pHseIpMuState->abChannelBusy[u8MuChannel] = (boolean)FALSE;
        /* Mark the channel as not allocated */
        pHseIpMuState->abChannelAllocated[u8MuChannel] = (boolean)FALSE;
        /* Initialize the pointer to async request on this channel to NULL */
        pHseIpMuState->apChannelRequest[u8MuChannel] = NULL_PTR;
    }

    /* Save the reference to the state structure allocated by the application */
    Hse_Ip_apMuState[u8MuInstance] = pHseIpMuState;

    return STATUS_HSE_IP_SUCCESS;
}

/**
 * @implements     Hse_Ip_Deinit_Activity
 */
status_hse_ip_t Hse_Ip_Deinit
(
    uint8 u8MuInstance
)
{
#if (STD_ON == HSE_IP_DEV_ERROR_DETECT)
   /* Check the validity of the input parameters */
    DevAssert((u8MuInstance < HSE_NUM_OF_MU_INSTANCES));
    /* Check that the driver is initialized */
    DevAssert((Hse_Ip_apMuState[u8MuInstance] != NULL_PTR));
#endif /* (STD_ON == HSE_IP_DEV_ERROR_DETECT) */

    /* Drop the state structure reference */
    Hse_Ip_apMuState[u8MuInstance] = NULL_PTR;

    return STATUS_HSE_IP_SUCCESS;
}

/**
 * implements    Hse_Ip_GetFreeChannel_Activity
 */
uint8 Hse_Ip_GetFreeChannel
(
    uint8 u8MuInstance
)
{
    uint8  u8RetVal = HSE_IP_INVALID_MU_CHANNEL_U8;
    uint32 u32ChannelBusyBitmap;
    uint32 u32ChannelMask;
    uint8  u8MuChannel;
    uint32 u32RsrReg;
    uint32 u32TsrReg;

#if (STD_ON == HSE_IP_DEV_ERROR_DETECT)
    /* Check the validity of the input parameters */
    DevAssert((u8MuInstance  <  HSE_NUM_OF_MU_INSTANCES));
    /* Check that the driver is initialized */
    DevAssert((Hse_Ip_apMuState[u8MuInstance] != NULL_PTR));
#endif /* (STD_ON == HSE_IP_DEV_ERROR_DETECT) */

    SchM_Enter_Crypto_CRYPTO_EXCLUSIVE_AREA_10();

    u32ChannelBusyBitmap = Mu_Ip_GetFlagStatusRegister(Hse_Ip_apMuBase[u8MuInstance]) & HSE_IP_HSE_CHANNEL_BUSY_MASK_U32;
    u32RsrReg            = Mu_Ip_GetRxStatusRegister(Hse_Ip_apMuBase[u8MuInstance]);
    u32TsrReg            = Mu_Ip_GetTxStatusRegister(Hse_Ip_apMuBase[u8MuInstance]);
    /* Finds the first unallocated channel, channel 0 is reserved for administrative services */
    for (u8MuChannel = 1U; u8MuChannel < HSE_NUM_OF_CHANNELS_PER_MU; u8MuChannel++)
    {
        if (!Hse_Ip_apMuState[u8MuInstance]->abChannelAllocated[u8MuChannel])
        {
            u32ChannelMask = ((uint32)1U << u8MuChannel);
            if ((0U == (u32ChannelBusyBitmap & u32ChannelMask)) &&
                (0U == (u32RsrReg            & u32ChannelMask)) &&
                (0U != (u32TsrReg            & u32ChannelMask))
                )
            {
                Hse_Ip_apMuState[u8MuInstance]->abChannelAllocated[u8MuChannel] = TRUE;
                u8RetVal = u8MuChannel;
                break;
            }
        }
    }

    SchM_Exit_Crypto_CRYPTO_EXCLUSIVE_AREA_10();

    return u8RetVal;
}

/**
 * @implements    Hse_Ip_ReleaseChannel_Activity
 */
void Hse_Ip_ReleaseChannel
(
    uint8 u8MuInstance,
    uint8 u8MuChannel
)
{
#if (STD_ON == HSE_IP_DEV_ERROR_DETECT)
    /* Check the validity of the input parameters */
    DevAssert((u8MuInstance < HSE_NUM_OF_MU_INSTANCES));
    DevAssert((u8MuChannel  < HSE_NUM_OF_CHANNELS_PER_MU));
    /* Check that the channel is not busy */
    DevAssert(((boolean)FALSE == Hse_Ip_apMuState[u8MuInstance]->abChannelBusy[u8MuChannel]));
#endif /* (STD_ON == HSE_IP_DEV_ERROR_DETECT) */

    /* Release the channel */
    Hse_Ip_apMuState[u8MuInstance]->abChannelAllocated[u8MuChannel] = (boolean)FALSE;
    /* Mark the channel as not processing any request */
    Hse_Ip_apMuState[u8MuInstance]->apChannelRequest[u8MuChannel]   = NULL_PTR;
}

/**
 * @implements     Hse_Ip_ServiceRequest_Activity
 */
hseSrvResponse_t Hse_Ip_ServiceRequest
(
    uint8               u8MuInstance,
    uint8               u8MuChannel,
    Hse_Ip_ReqType*     pRequest,
    hseSrvDescriptor_t* pHseSrvDesc
)
{
    hseSrvResponse_t    HseResponse     = HSE_SRV_RSP_OK;
    uint32              u32ElapsedTicks = 0U;
    Hse_Ip_MuStateType* pHseIpMuState;
    uint32              u32TimeoutTicks;
    uint32              u32CurrentTicks;

#if (STD_ON == HSE_IP_DEV_ERROR_DETECT)
    /* Check the validity of the input parameters */
    DevAssert((u8MuInstance < HSE_NUM_OF_MU_INSTANCES));
#endif /* (STD_ON == HSE_IP_DEV_ERROR_DETECT) */

    /* Keep a pointer to MuState to optimize a bit the code for accessing it */
    pHseIpMuState = Hse_Ip_apMuState[u8MuInstance];

#if (STD_ON == HSE_IP_DEV_ERROR_DETECT)
    DevAssert((u8MuChannel  < HSE_NUM_OF_CHANNELS_PER_MU));
    DevAssert((pRequest    != NULL_PTR));
    DevAssert((pHseSrvDesc != NULL_PTR));
    DevAssert(((HSE_IP_REQTYPE_SYNC       == pRequest->eReqType) || \
                     (HSE_IP_REQTYPE_ASYNC_IRQ  == pRequest->eReqType) || \
                     (HSE_IP_REQTYPE_ASYNC_POLL == pRequest->eReqType)));
    /* For HSE_IP_REQTYPE_ASYNC_IRQ and HSE_IP_REQTYPE_ASYNC_POLL requests, there should always be a callback */
    DevAssert(((pRequest->eReqType == HSE_IP_REQTYPE_SYNC) || (NULL_PTR != pRequest->pfCallback)));
    /* Check that the driver is initialized */
    DevAssert((pHseIpMuState != NULL_PTR));
    /* Check that the channel is allocated */
    DevAssert(((0U == u8MuChannel) || (boolean)TRUE == pHseIpMuState->abChannelAllocated[u8MuChannel]));
#endif /* (STD_ON == HSE_IP_DEV_ERROR_DETECT) */

    /* Save the reference to the request. This is used to mark the channel as processing a request and is also used to filter out spurious interrupts */
    pHseIpMuState->apChannelRequest[u8MuChannel] = pRequest;

    if (HSE_IP_REQTYPE_SYNC == pRequest->eReqType)
    {
        /* Mark the channel as busy processing a request */
        pHseIpMuState->abChannelBusy[u8MuChannel] = (boolean)TRUE;
        /* Convert from microseconds to ticks */
        u32TimeoutTicks = OsIf_MicrosToTicks(pRequest->u32Timeout, (OsIf_CounterType)HSE_IP_TIMEOUT_OSIF_COUNTER_TYPE);
        /* Send the service request to HSE */
        Mu_Ip_SetTxRegister(Hse_Ip_apMuBase[u8MuInstance], u8MuChannel, (uint32)pHseSrvDesc);
        /* Read the current value of the counter */
        u32CurrentTicks = OsIf_GetCounter((OsIf_CounterType)HSE_IP_TIMEOUT_OSIF_COUNTER_TYPE);
        /* Wait for the HSE response */
        while (((boolean)FALSE == Mu_Ip_IsResponseReady(Hse_Ip_apMuBase[u8MuInstance], u8MuChannel)) && (u32ElapsedTicks < u32TimeoutTicks))
        {
            /* Update the elapsed ticks, current ticks will be updated too by the OsIf function */
            u32ElapsedTicks += OsIf_GetElapsed(&u32CurrentTicks, (OsIf_CounterType)HSE_IP_TIMEOUT_OSIF_COUNTER_TYPE);
        }
        /* If timeout expired - return timeout error */
        if ( u32ElapsedTicks >= u32TimeoutTicks )
        {
            HseResponse = HSE_SRV_RSP_NO_RESPONSE;
        }
        else
        {
            /* Read the response */
            HseResponse = Mu_Ip_GetRxRegister(Hse_Ip_apMuBase[u8MuInstance], u8MuChannel);
        }
        /* Mark the channel as not busy processing a request */
        pHseIpMuState->abChannelBusy[u8MuChannel] = (boolean)FALSE;
        /* Release the allocated channel */
        Hse_Ip_ReleaseChannel(u8MuInstance, u8MuChannel);
    }
    else
    {
        /* Enable the Rx interruupt if the request is async irq */
        if (HSE_IP_REQTYPE_ASYNC_IRQ == pRequest->eReqType)
        {
            SchM_Enter_Crypto_CRYPTO_EXCLUSIVE_AREA_11();
            Mu_Ip_SetRxIrqEnable(Hse_Ip_apMuBase[u8MuInstance], u8MuChannel, (boolean)TRUE);
            SchM_Exit_Crypto_CRYPTO_EXCLUSIVE_AREA_11();
        }
        /* Mark the channel as busy processing a request */
        pHseIpMuState->abChannelBusy[u8MuChannel] = (boolean)TRUE;
        /* Send the service request to HSE */
        Mu_Ip_SetTxRegister(Hse_Ip_apMuBase[u8MuInstance], u8MuChannel, (uint32)pHseSrvDesc);
    }
    return HseResponse;
}

/**
 * @implements     Hse_Ip_MainFunction_Activity
 */
void Hse_Ip_MainFunction
(
    uint8 u8MuInstance
)
{
#if (STD_ON == HSE_IP_DEV_ERROR_DETECT)
    /* Check the validity of the input parameters */
    DevAssert((u8MuInstance < HSE_NUM_OF_MU_INSTANCES));
#endif /* (STD_ON == HSE_IP_DEV_ERROR_DETECT) */

    Hse_Ip_ProcessReceivedResponses(u8MuInstance, HSE_IP_REQTYPE_ASYNC_POLL);
}

/**
 * @implements     Hse_Ip_GetHseStatus_Activity
 */
hseStatus_t Hse_Ip_GetHseStatus(void)
{
    uint32 u32Status = Mu_Ip_GetFlagStatusRegister(Hse_Ip_apMuBase[0U]);
    return ((hseStatus_t)((u32Status & HSE_IP_HSE_STATUS_MASK_U32) >> HSE_IP_HSE_STATUS_SHIFT_U8));
}

/**
 * @implements     Hse_Ip_RegisterGenericCallback_Activity
 */
void Hse_Ip_RegisterGenericCallback
(
    uint8                             u8MuInstance,
    uint32                            u32NotifEventsMask,
    pfHseIpGenericPurposeCallbackType pfCallback
)
{
#if (STD_ON == HSE_IP_DEV_ERROR_DETECT)
    /* Check the validity of the input parameters */
    DevAssert((u8MuInstance < HSE_NUM_OF_MU_INSTANCES));
    DevAssert((pfCallback  != NULL_PTR));
    /* Check that the driver is initialized */
    DevAssert((Hse_Ip_apMuState[u8MuInstance] != NULL_PTR));
#endif /* (STD_ON == HSE_IP_DEV_ERROR_DETECT) */

    Hse_Ip_apMuState[u8MuInstance]->pfGenericPurposeCallback = pfCallback;
    Mu_Ip_SetGlobalIrqEnable(Hse_Ip_apMuBase[u8MuInstance], u32NotifEventsMask);
}

/**
 * @implements     Hse_Ip_RxIrqHandler_Activity
 */
void Hse_Ip_RxIrqHandler
(
    uint8 u8MuInstance
)
{
    const MU_Type* pMuBase       = Hse_Ip_apMuBase[u8MuInstance];
    uint32         u32ControlReg = Mu_Ip_GetRxControlRegister(pMuBase);
    uint32         u32StatusReg  = Mu_Ip_GetRxStatusRegister(pMuBase);
    uint32         u32SpuriousIrqMask;
    uint8          u8MuChannel;

    /* Check if HseIp layer has been initialized for the current MU instance */
    if (NULL_PTR == Hse_Ip_apMuState[u8MuInstance])
    {
        /* MU instance not initialized. Loop through each of the channels in the MU instance and perform a dummy read on the looped channel.
           This will clear the interrupt flags of every MU channel */
        for (u8MuChannel = 0U; u8MuChannel < HSE_NUM_OF_CHANNELS_PER_MU; u8MuChannel++)
        {
            (void)Mu_Ip_GetRxRegister(pMuBase, u8MuChannel);
        }
    }
    else
    {
        /* The current MU instance is initialized by HseIp. Need to find only those channels having spurious interrupts (Control bit = 0, Status bit = 1)
           The problem is that HseIp layer can be used to execute multiple requests in the same time, some of them can be synchronous, some of them asynchronous, so when
        a interrupt is triggered, we might see channels with Control bit = 0 and Status bit = 1 because they are processing a asynchronous polling request or a synchronous one.
           In the instruction below we consider spurious everything that has Control bit = 0, Status bit = 1, but later on we will clear the status interrupt flag only for those
        channels that do not have an associated request: Hse_Ip_apMuState[u8MuInstance]->apChannelRequest[u8MuChannel] = NULL_PTR */
        u32SpuriousIrqMask = ((u32ControlReg ^ u32StatusReg) & u32StatusReg);

        if (0U != u32SpuriousIrqMask)
        {
            /* Loop through each of the channels in the MU instance */
            for (u8MuChannel = 0U; u8MuChannel < HSE_NUM_OF_CHANNELS_PER_MU; u8MuChannel++)
            {
                /* Check if a spurious interrupt was detected on the currently looped MU channel and more important if the channel does not process any request at this point in time */
                if((0U != (((uint32)(1UL << u8MuChannel)) & u32SpuriousIrqMask)) &&
                   (NULL_PTR == Hse_Ip_apMuState[u8MuInstance]->apChannelRequest[u8MuChannel]))
                {
                    /* Perform a dummy read on the looped channel. This will clear the interrupt flag */
                    (void)Mu_Ip_GetRxRegister(pMuBase, u8MuChannel);
                    /* Clear from the copy of the Status reg the bit of the currently looped channel, for which we considered the interrupt being spurious */
                    u32StatusReg &= ~(1UL << u8MuChannel);
                }
            }
        }
        /* Check if there are still interrupt bits set. If yes, call the function that should handle them */
        if(0U != u32StatusReg)
        {
            Hse_Ip_ProcessReceivedResponses(u8MuInstance, HSE_IP_REQTYPE_ASYNC_IRQ);
        }
    }
}

/**
 * @implements     Hse_Ip_GeneralPurposeIrqHandler_Activity
 */
void Hse_Ip_GeneralPurposeIrqHandler
(
    uint8 u8MuInstance
)
{
    uint32 events = Mu_Ip_GetGlobalIrqFlags(Hse_Ip_apMuBase[u8MuInstance]);

    Mu_Ip_ClearGlobalIrqFlags(Hse_Ip_apMuBase[u8MuInstance], HSE_IP_HSE_ALL_ERROR_FLAGS_MASK_U32);

    if (Hse_Ip_apMuState[u8MuInstance]->pfGenericPurposeCallback != NULL_PTR)
    {
        Hse_Ip_apMuState[u8MuInstance]->pfGenericPurposeCallback(u8MuInstance, events);
    }
}


#define CRYPTO_STOP_SEC_CODE
#include "Crypto_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
