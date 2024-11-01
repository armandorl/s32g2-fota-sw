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
*   @file     Linflexd_Uart_Ip.c
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

#include "Linflexd_Uart_Ip.h"
#if (LINFLEXD_UART_HAS_DMA_ENABLED == STD_ON)
    #include "Dma_Ip.h"
#endif

#ifdef LINFLEXD_UART_DEV_ERROR_DETECT
    #if (LINFLEXD_UART_DEV_ERROR_DETECT == STD_ON)
        #include "Devassert.h"
    #endif /* (STD_ON == LINFLEXD_UART_DEV_ERROR_DETECT) */
#endif /* idfef LINFLEXD_UART_DEV_ERROR_DETECT */

#if (STD_ON == LINFLEXD_SET_USER_ACCESS_ALLOWED_AVAILABLE)
    #define USER_MODE_REG_PROT_ENABLED      (STD_ON)
    #include "RegLockMacros.h"
#endif
/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define LINFLEXD_UART_IP_VENDOR_ID_C                      43
#define LINFLEXD_UART_IP_AR_RELEASE_MAJOR_VERSION_C       4
#define LINFLEXD_UART_IP_AR_RELEASE_MINOR_VERSION_C       4
#define LINFLEXD_UART_IP_AR_RELEASE_REVISION_VERSION_C    0
#define LINFLEXD_UART_IP_SW_MAJOR_VERSION_C               1
#define LINFLEXD_UART_IP_SW_MINOR_VERSION_C               0
#define LINFLEXD_UART_IP_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Linflexd_Uart_Ip.h */
#if (LINFLEXD_UART_IP_VENDOR_ID_C != LINFLEXD_UART_IP_VENDOR_ID)
    #error "Linflexd_Uart_Ip.c and Linflexd_Uart_Ip.h have different vendor ids"
#endif
#if ((LINFLEXD_UART_IP_AR_RELEASE_MAJOR_VERSION_C    != LINFLEXD_UART_IP_AR_RELEASE_MAJOR_VERSION) || \
     (LINFLEXD_UART_IP_AR_RELEASE_MINOR_VERSION_C    != LINFLEXD_UART_IP_AR_RELEASE_MINOR_VERSION) || \
     (LINFLEXD_UART_IP_AR_RELEASE_REVISION_VERSION_C != LINFLEXD_UART_IP_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Linflexd_Uart_Ip.c and Linflexd_Uart_Ip.h are different"
#endif
#if ((LINFLEXD_UART_IP_SW_MAJOR_VERSION_C != LINFLEXD_UART_IP_SW_MAJOR_VERSION) || \
     (LINFLEXD_UART_IP_SW_MINOR_VERSION_C != LINFLEXD_UART_IP_SW_MINOR_VERSION) || \
     (LINFLEXD_UART_IP_SW_PATCH_VERSION_C != LINFLEXD_UART_IP_SW_PATCH_VERSION))
    #error "Software Version Numbers of Linflexd_Uart_Ip.c and Linflexd_Uart_Ip.h are different"
#endif
/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/

#ifdef LINFLEXD_UART_DEV_ERROR_DETECT
    #if (LINFLEXD_UART_DEV_ERROR_DETECT == STD_ON)
        #define LINFLEXD_UART_DEV_ASSERT(x)      DevAssert(x)
    #else
    	#define LINFLEXD_UART_DEV_ASSERT(x)      (void)(x)
	#endif
#endif

/* @brief Address of the least significant byte or word in a 32-bit register (depends on endianness) */
#define LINFLEXD_UART_LSBW_ADDR(reg)  ((uint32)(&(reg)))

/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

#if (LINFLEXD_UART_HAS_DMA_ENABLED == STD_ON)
    #define LINFLEXD_UART_DMA_CONFIG_LIST_DIMENSION             (10U)
    #define LINFLEXD_UART_DMA_LEAST_CONFIG_LIST_DIMENSION       (2U)
#endif

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/
#define UART_START_SEC_VAR_NO_INIT_UNSPECIFIED_NO_CACHEABLE
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

/** @brief Array of UART driver runtime state structures */
Linflexd_Uart_Ip_StateStructureType Linflexd_Uart_Ip_apStateStructure[LINFLEXD_INSTANCE_COUNT];

#define UART_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_NO_CACHEABLE
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

#define UART_START_SEC_VAR_NO_INIT_UNSPECIFIED
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

/** @brief User config structure. */
static const Linflexd_Uart_Ip_UserConfigType* Linflexd_Uart_Ip_apUserConfig[LINFLEXD_INSTANCE_COUNT] = UART_CONFIGURATION_PTRS_FOR_INIT;

#define UART_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

#define UART_START_SEC_VAR_NO_INIT_UNSPECIFIED
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

/** @brief Array of pointers to UART driver runtime state structures */
static Linflexd_Uart_Ip_StateStructureType* Linflexd_Uart_Ip_apStateStructuresArray[LINFLEXD_INSTANCE_COUNT] = UART_STATE_STRUCTURE_PTRS_FOR_INIT;

#define UART_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

#define UART_START_SEC_CONST_UNSPECIFIED
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

/** @brief Table of base addresses for LINFLEXD instances. */
static LINFLEXD_Type* const Linflexd_Uart_Ip_apBases[LINFLEXD_INSTANCE_COUNT] = FEATURE_LINFLEXD_IP_SPECIFIC_BASE_PTR;

#define UART_STOP_SEC_CONST_UNSPECIFIED
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

#if (LINFLEXD_UART_HAS_DMA_ENABLED == STD_ON)
#define UART_START_SEC_CONST_BOOLEAN
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

/** @brief Table storing DMA capabilities for LINFLEXD instances. */
static const boolean s_LINFLEXDInstHasDma[LINFLEXD_INSTANCE_COUNT] = FEATURE_LINFLEXD_IP_INST_HAS_DMA;

#define UART_STOP_SEC_CONST_BOOLEAN
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"
#endif

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/
#define UART_START_SEC_CODE
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

static Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_StartSendUsingInterrupts(uint32 u32Instance,
                                                                             const uint8 * pTxBuff,
                                                                             uint32 u32TxSize);
static Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_StartReceiveUsingInterrupts(uint32 u32Instance,
                                                                                uint8 * pRxBuff,
                                                                                uint32 u32RxSize);
static void Linflexd_Uart_Ip_CompleteSendUsingInterrupts(uint32 u32Instance);
static void Linflexd_Uart_Ip_CompleteReceiveUsingInterrupts(uint32 u32Instance);
#if (LINFLEXD_UART_HAS_DMA_ENABLED == STD_ON)
static Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_StartSendUsingDma(uint32 u32Instance,
                                                                      const uint8 * pTxBuff,
                                                                      uint32 u32TxSize);
static Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_StartReceiveUsingDma(uint32 u32Instance,
                                                                         uint8 * pRxBuff,
                                                                         uint32 u32RxSize);
static void Linflexd_Uart_Ip_FlushRxFifo(const LINFLEXD_Type *pBase, Linflexd_Uart_Ip_WordLengthType eWordLength);
#endif
static void Linflexd_Uart_Ip_PutData(uint32 u32Instance);
static void Linflexd_Uart_Ip_GetData(uint32 u32Instance);
#if (STD_ON == LINFLEXD_SET_USER_ACCESS_ALLOWED_AVAILABLE)
static void Linflexd_Uart_Ip_SetUserAccess(uint32 u32Instance);
#endif /* LINFLEXD_SET_USER_ACCESS_ALLOWED_AVAILABLE */

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/

/* implements     Linflexd_Uart_Ip_SetBaudrate_Activity*/
Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_SetBaudrate_Privileged(uint32 u32Instance,
                                                                    Linflexd_Uart_Ip_BaudrateType desiredBaudRate,
                                                                    uint32 clockFrequency)
{

    LINFLEXD_UART_DEV_ASSERT(u32Instance < LINFLEXD_INSTANCE_COUNT);

    LINFLEXD_Type * pBase;
    float32 prescaler;
    float32 fraction;
    uint32 mantissa;
    uint32 fractionDenominator;
    uint8 fractionNumerator;
    float32 float32Numerator;
    boolean resetIdle = FALSE;
    Linflexd_Uart_Ip_StateStructureType * pUartState;
    uint32 u32StartTime;
    Linflexd_Uart_Ip_StatusType status = LINFLEXD_UART_IP_STATUS_ERROR;

    pBase = Linflexd_Uart_Ip_apBases[u32Instance];
    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];

    LINFLEXD_UART_DEV_ASSERT(pUartState != NULL_PTR);

    if ((pUartState->bIsTxBusy == TRUE) || (pUartState->bIsRxBusy == TRUE))
    {
        status = LINFLEXD_UART_IP_STATUS_BUSY;
    }
    else
    {
        /* Compute the values for baud rate divider mantissa and fraction */
        prescaler = (float32)clockFrequency / ((float32)desiredBaudRate * (float32)DEFAULT_OSR);
        mantissa = (uint32)prescaler;
        fraction = prescaler - (float32)mantissa;
        fractionDenominator = ((uint32)1U << (uint32)BAUDRATE_FRACTION_WIDTH);
        float32Numerator = ((float32)fraction * (float32)fractionDenominator) + (float32)0.5F;
        fractionNumerator = (uint8)(float32Numerator);

        if (fractionNumerator == fractionDenominator)
        {
            fractionNumerator = 0;
            mantissa++;
        }

        if (LINFLEXD_GetLinState(pBase) != LINFLEXD_STATE_INIT_MODE)
        {
            /* Request init mode and wait until the mode entry is complete */
            LINFLEXD_EnterInitMode(pBase);

            u32StartTime = OsIf_GetCounter(LINFLEXD_UART_IP_TIMEOUT_TYPE);

            while (!LINFLEXD_CheckTimeout(u32StartTime, (uint32)LINFLEXD_UART_TIMEOUT_VALUE_US) &&
                    (LINFLEXD_GetLinState(pBase) != LINFLEXD_STATE_INIT_MODE)) {}

            /* Init mode error */
            if (LINFLEXD_GetLinState(pBase) != LINFLEXD_STATE_INIT_MODE)
            {
                return LINFLEXD_UART_IP_STATUS_ERROR;
            }
            else
            {
                resetIdle = TRUE;
            }
        }

        /* Write the computed values to registers */
        LINFLEXD_SetIntegerBaudRate(pBase, mantissa);
        LINFLEXD_SetFractionalBaudRate(pBase, fractionNumerator);

        if (resetIdle == TRUE)
        {
            /* Enter normal mode */
            LINFLEXD_EnterNormalMode(pBase);
        }
        /* Save current baudrate value */
        pUartState->u32Baudrate = (uint32)desiredBaudRate;
        status = LINFLEXD_UART_IP_STATUS_SUCCESS;
    }
    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_GetBaudRate
 * Description   : This function retrieves the baud rate for UART communication.
 *
*END**************************************************************************/
/* implements     Linflexd_Uart_Ip_GetBaudRate_Activity*/
void Linflexd_Uart_Ip_GetBaudRate(uint32 u32Instance, uint32 * configuredBaudRate)
{
    LINFLEXD_UART_DEV_ASSERT(u32Instance < LINFLEXD_INSTANCE_COUNT);
    LINFLEXD_UART_DEV_ASSERT(configuredBaudRate != NULL_PTR);

    Linflexd_Uart_Ip_StateStructureType *pUartStatePtr;
    pUartStatePtr = Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];

    LINFLEXD_UART_DEV_ASSERT(pUartStatePtr != NULL_PTR);

    *configuredBaudRate = pUartStatePtr->u32Baudrate;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_Init
 * Description   : This function initializes a LINFLEXD instance for UART
 * operation.
 * This function will initialize the run-time state structure to keep track of
 * the on-going transfers, initialize the module to user defined settings and
 * default settings, enable the module-level interrupt to the core, and enable
 * the UART module transmitter and receiver.
 *
 *END**************************************************************************/
/* implements     Linflexd_Uart_Ip_Init_Activity*/
void Linflexd_Uart_Ip_Init_Privileged(uint32 u32Instance, const Linflexd_Uart_Ip_UserConfigType * userConfig)
{
    LINFLEXD_UART_DEV_ASSERT(u32Instance < LINFLEXD_INSTANCE_COUNT);
    LINFLEXD_UART_DEV_ASSERT(Linflexd_Uart_Ip_apStateStructuresArray[u32Instance] == NULL_PTR);
    LINFLEXD_UART_DEV_ASSERT(userConfig != NULL_PTR);
#if (LINFLEXD_UART_HAS_DMA_ENABLED == STD_ON)
    /* Check if an instance with no DMA support is configured in DMA mode */
    LINFLEXD_UART_DEV_ASSERT((userConfig->eTransferType != LINFLEXD_UART_IP_USING_DMA) || s_LINFLEXDInstHasDma[u32Instance]);
#endif
    LINFLEXD_Type * pBase = Linflexd_Uart_Ip_apBases[u32Instance];
    Linflexd_Uart_Ip_apStateStructuresArray[u32Instance] = userConfig->pStateStruct;

	Linflexd_Uart_Ip_StateStructureType *pUartStatePtr = Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];
    Linflexd_Uart_Ip_apUserConfig[u32Instance] = userConfig;

    uint32 u32Index;
    uint32 u32StartTime;

    /* Clear the state struct for this u32Instance. */
    uint8 *pClearStructPtr = (uint8 *)pUartStatePtr;
    for (u32Index = 0; u32Index < sizeof(Linflexd_Uart_Ip_StateStructureType); u32Index++)
    {
        pClearStructPtr[u32Index] = 0U;
    }

    /* Request init mode and wait until the mode entry is complete */
    LINFLEXD_EnterInitMode(pBase);

    pUartStatePtr->bIsDriverInitialized = FALSE;

    u32StartTime = OsIf_GetCounter(LINFLEXD_UART_IP_TIMEOUT_TYPE);
    while (!LINFLEXD_CheckTimeout(u32StartTime, (uint32)LINFLEXD_UART_TIMEOUT_VALUE_US) &&
            (LINFLEXD_GetLinState(pBase) != LINFLEXD_STATE_INIT_MODE)) {}

    if (LINFLEXD_GetLinState(pBase) == LINFLEXD_STATE_INIT_MODE)
    {
        pUartStatePtr->bIsDriverInitialized = TRUE;
    }

    /* Set UART mode */
    LINFLEXD_SetMode(pBase, LINFLEXD_UART_MODE);

    /* Set the baud rate */
    LINFLEXD_SetIntegerBaudRate(pBase, userConfig->u32BaudRateMantissa);
    LINFLEXD_SetFractionalBaudRate(pBase, userConfig->u8BaudRateFractionalDivisor);

    pUartStatePtr->u32Baudrate = userConfig->u32BaudRate;

    /* Set word length */
    LINFLEXD_SetUartWordLength(pBase, userConfig->eWordLength);
    LINFLEXD_SetTxDataFieldLength(pBase, (uint8)((uint8)userConfig->eWordLength >> 1U));
    LINFLEXD_SetRxDataFieldLength(pBase, (uint8)((uint8)userConfig->eWordLength >> 1U));

    /* Set parity */
    if (userConfig->bParityCheck)
    {
        LINFLEXD_SetParityControl(pBase, TRUE);
        LINFLEXD_SetParityType(pBase, userConfig->eParityType);
    }
    else
    {
        LINFLEXD_SetParityControl(pBase, FALSE);
    }

    /* Set stop bits count */
    LINFLEXD_SetRxStopBitsCount(pBase, userConfig->eStopBitsCount);
    LINFLEXD_SetTxStopBitsCount(pBase, userConfig->eStopBitsCount, TRUE);

    /* Enable FIFO for DMA based communication, or buffer mode for interrupt based communication */
    if (userConfig->eTransferType == LINFLEXD_UART_IP_USING_DMA)
    {
        LINFLEXD_SetTxMode(pBase, LINFLEXD_UART_RXTX_FIFO_MODE);
        LINFLEXD_SetRxMode(pBase, LINFLEXD_UART_RXTX_FIFO_MODE);
    }
    else
    {
        LINFLEXD_SetTxMode(pBase, LINFLEXD_UART_RXTX_BUFFER_MODE);
        LINFLEXD_SetRxMode(pBase, LINFLEXD_UART_RXTX_BUFFER_MODE);
    }

    /* Enter normal mode */
    LINFLEXD_EnterNormalMode(pBase);

    /* initialize last driver operation status */
    pUartStatePtr->eTransmitStatus = LINFLEXD_UART_IP_STATUS_SUCCESS;
    pUartStatePtr->eReceiveStatus = LINFLEXD_UART_IP_STATUS_SUCCESS;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_Deinit
 * Description   : This function shuts down the UART by disabling interrupts and
 *                 transmitter/receiver.
 *
*END**************************************************************************/
/* implements     Linflexd_Uart_Ip_Deinit_Activity */
void Linflexd_Uart_Ip_Deinit(uint32 u32Instance)
{
    LINFLEXD_UART_DEV_ASSERT(u32Instance < LINFLEXD_INSTANCE_COUNT);

    LINFLEXD_Type * pBase;

    pBase = Linflexd_Uart_Ip_apBases[u32Instance];
    /* Clear the saved pointer to the state structure */
    Linflexd_Uart_Ip_apStateStructuresArray[u32Instance] = NULL_PTR;
    
    /* Calling Linflexd_Uart_Ip_Deinit shall disable the transmitter and reciever. */
    /* Disable transmission complete interrupt */
    LINFLEXD_SetInterruptMode(pBase, LINFLEXD_DATA_TRANSMITTED_INT, FALSE);
    /* Disable receive data full interrupt. */
    LINFLEXD_SetInterruptMode(pBase, LINFLEXD_DATA_RECEPTION_COMPLETE_INT, FALSE);

    /*Calling Linflexd_Uart_Ip_Deinit shall disable error interrupts (rx overrun and framing error).*/
    /* Disable error interrupts */
    LINFLEXD_SetInterruptMode(pBase, LINFLEXD_FRAME_ERROR_INT, FALSE);
    LINFLEXD_SetInterruptMode(pBase, LINFLEXD_BUFFER_OVERRUN_INT, FALSE);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_SetTxBuffer
 * Description   : Sets the driver internal reference to the tx buffer.
 *                 Can be called from the tx callback to provide a different
 *                 buffer for continuous transmission.
 *
*END**************************************************************************/
/* implements     Linflexd_Uart_Ip_SetTxBuffer_Activity */
Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_SetTxBuffer(uint32 u32Instance,
                                                         const uint8 * pTxBuff,
                                                         uint32 u32TxSize)
{
    LINFLEXD_UART_DEV_ASSERT(u32Instance < LINFLEXD_INSTANCE_COUNT);
    LINFLEXD_UART_DEV_ASSERT(pTxBuff != NULL_PTR);
    LINFLEXD_UART_DEV_ASSERT(u32TxSize > 0U);

    Linflexd_Uart_Ip_StateStructureType * pUartState;

    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];

    LINFLEXD_UART_DEV_ASSERT(pUartState != NULL_PTR);

    pUartState->pTxBuff = pTxBuff;
    pUartState->u32TxSize = u32TxSize;

    return LINFLEXD_UART_IP_STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_SetRxBuffer
 * Description   : Sets the driver internal reference to the rx buffer.
 *                 Can be called from the rx callback to provide a different
 *                 buffer for continuous reception.
 *
*END**************************************************************************/
/* implements     Linflexd_Uart_Ip_SetRxBuffer_Activity */
Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_SetRxBuffer(uint32 u32Instance,
                                                         uint8 * pRxBuff,
                                                         uint32 u32RxSize)
{
    LINFLEXD_UART_DEV_ASSERT(u32Instance < LINFLEXD_INSTANCE_COUNT);
    LINFLEXD_UART_DEV_ASSERT(pRxBuff != NULL_PTR);
    LINFLEXD_UART_DEV_ASSERT(u32RxSize > 0U);

    Linflexd_Uart_Ip_StateStructureType * pUartState;

    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];

    LINFLEXD_UART_DEV_ASSERT(pUartState != NULL_PTR);

    pUartState->pRxBuff = pRxBuff;
    pUartState->u32RxSize = u32RxSize;

    return LINFLEXD_UART_IP_STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_PutData
 * Description   : Write data to the buffer register, according to configured
 * word length.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void Linflexd_Uart_Ip_PutData(uint32 u32Instance)
{
    Linflexd_Uart_Ip_StateStructureType * pUartState;
    LINFLEXD_Type * pBase;
    const Linflexd_Uart_Ip_UserConfigType *pUartUserCfg = (Linflexd_Uart_Ip_UserConfigType*) Linflexd_Uart_Ip_apUserConfig[u32Instance];
    pBase = Linflexd_Uart_Ip_apBases[u32Instance];
    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];

    if((pUartUserCfg->eWordLength == LINFLEXD_UART_IP_7_BITS) || (pUartUserCfg->eWordLength == LINFLEXD_UART_IP_8_BITS))
    {
        uint8 data = *(pUartState->pTxBuff);
        /* Update the state structure */
        ++pUartState->pTxBuff;
        --pUartState->u32TxSize;
        /* Transmit the data */
        LINFLEXD_SetTxDataBuffer1Byte(pBase, data);
    }
    else
    {
        /* Transmit the data and update state structure */
        if(pUartState->u32TxSize == 1U)
        {
            uint16 data = (uint16)(*pUartState->pTxBuff);
            ++pUartState->pTxBuff;
            --pUartState->u32TxSize;
            LINFLEXD_SetTxDataBuffer2Bytes(pBase, data);
        }
        else
        {
            uint16 data = *((const uint16*)pUartState->pTxBuff);
            /* Move the pointer twice */
            ++pUartState->pTxBuff;
            ++pUartState->pTxBuff;
            pUartState->u32TxSize -= 2U;
            LINFLEXD_SetTxDataBuffer2Bytes(pBase, data);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_CompleteSendUsingInterrupts
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void Linflexd_Uart_Ip_CompleteSendUsingInterrupts(uint32 u32Instance)
{
    Linflexd_Uart_Ip_StateStructureType * pUartState;
    LINFLEXD_Type * pBase;

    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];
    pBase = Linflexd_Uart_Ip_apBases[u32Instance];

    /* Disable transmission complete interrupt */
    LINFLEXD_SetInterruptMode(pBase, LINFLEXD_DATA_TRANSMITTED_INT, FALSE);

    /* Disable the transmitter */
    LINFLEXD_SetTransmitterState(pBase, FALSE);

    /* Update the information of the module driver state */
    pUartState->bIsTxBusy = FALSE;

    /* If the current transmission hasn't been aborted, update the status */
    if (pUartState->eTransmitStatus == LINFLEXD_UART_IP_STATUS_BUSY)
    {
        pUartState->eTransmitStatus = LINFLEXD_UART_IP_STATUS_SUCCESS;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_CompleteReceiveUsingInterrupts
 * Description   : Finish up a receive by completing the process of receiving data
 * and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void Linflexd_Uart_Ip_CompleteReceiveUsingInterrupts(uint32 u32Instance)
{
    Linflexd_Uart_Ip_StateStructureType * pUartState;
    LINFLEXD_Type * pBase;

    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];
    pBase = Linflexd_Uart_Ip_apBases[u32Instance];

    /* Disable receive data full interrupt. */
    LINFLEXD_SetInterruptMode(pBase, LINFLEXD_DATA_RECEPTION_COMPLETE_INT, FALSE);
    
    /* Disable error interrupts */
    LINFLEXD_SetInterruptMode(pBase, LINFLEXD_FRAME_ERROR_INT, FALSE);
    LINFLEXD_SetInterruptMode(pBase, LINFLEXD_BUFFER_OVERRUN_INT, FALSE);
    
    /* Disable the receiver */
    LINFLEXD_SetReceiverState(pBase, FALSE);

    /* Update the information of the module driver state */
    pUartState->bIsRxBusy = FALSE;

    /* If the current reception hasn't been aborted and no error occurred, update the status */
    if (pUartState->eReceiveStatus == LINFLEXD_UART_IP_STATUS_BUSY)
    {
        pUartState->eReceiveStatus = LINFLEXD_UART_IP_STATUS_SUCCESS;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_SyncSend_Privileged
 * Description   : Send out multiple bytes of data using polling method.
 *
 *END**************************************************************************/
 /* implements    Linflexd_Uart_Ip_SyncSend_Activity */
Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_SyncSend_Privileged(uint32 u32Instance,
                                                                 const uint8 *pTxBuff,
                                                                 uint32 u32TxSize)
{

    /* Check the validity of the parameters */
    LINFLEXD_UART_DEV_ASSERT(u32TxSize > 0U);
    LINFLEXD_UART_DEV_ASSERT(pTxBuff != NULL_PTR);
    LINFLEXD_UART_DEV_ASSERT(u32Instance < LINFLEXD_INSTANCE_COUNT);

    Linflexd_Uart_Ip_StateStructureType * pUartState;
    LINFLEXD_Type * pBase;
    uint32 u32StartTime;

    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];
    pBase = Linflexd_Uart_Ip_apBases[u32Instance];

    LINFLEXD_UART_DEV_ASSERT(pUartState != NULL_PTR);

    SchM_Enter_Uart_UART_EXCLUSIVE_AREA_03();
    /* Check driver is not busy transmitting data from a previous asynchronous call */
    if (pUartState->bIsTxBusy)
    {
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_03();
        return LINFLEXD_UART_IP_STATUS_BUSY;
    }

     /* Initialize the module driver state structure */
    pUartState->bIsTxBusy = TRUE;
    SchM_Exit_Uart_UART_EXCLUSIVE_AREA_03();
    pUartState->pTxBuff = pTxBuff;
    pUartState->u32TxSize = u32TxSize;

    pUartState->eTransmitStatus = LINFLEXD_UART_IP_STATUS_BUSY;
    
    /* The interrupts shall be disabled when the Linflexd_Uart_Ip_SyncReceive and Linflexd_Uart_Ip_SyncSend are called. */
    /* Disble transmission complete interrupt */
    LINFLEXD_SetInterruptMode(pBase, LINFLEXD_DATA_TRANSMITTED_INT, FALSE);
    /* Disable receive data full interrupt. */
    LINFLEXD_SetInterruptMode(pBase, LINFLEXD_DATA_RECEPTION_COMPLETE_INT, FALSE);
        
    /* Disable error interrupts */
    LINFLEXD_SetInterruptMode(pBase, LINFLEXD_FRAME_ERROR_INT, FALSE);
    LINFLEXD_SetInterruptMode(pBase, LINFLEXD_BUFFER_OVERRUN_INT, FALSE);

    /* Enable the transmitter */
    LINFLEXD_SetTransmitterState(pBase, TRUE);

    u32StartTime = OsIf_GetCounter(LINFLEXD_UART_IP_TIMEOUT_TYPE);

    while ((pUartState->u32TxSize > 0U) && !LINFLEXD_CheckTimeout(u32StartTime, (uint32)LINFLEXD_UART_TIMEOUT_VALUE_US))
    {
        LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_DATA_TRANSMITTED_FLAG);
        Linflexd_Uart_Ip_PutData(u32Instance);
        /* Wait until data transmited flag is set or timeout occurs if there is an error during transmission */
        while (!LINFLEXD_GetStatusFlag(pBase, LINFLEXD_UART_DATA_TRANSMITTED_FLAG) && \
               !LINFLEXD_CheckTimeout(u32StartTime, (uint32)LINFLEXD_UART_TIMEOUT_VALUE_US))
        {}
    }
    LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_DATA_TRANSMITTED_FLAG);

    /* Disable the transmitter */
    LINFLEXD_SetTransmitterState(pBase, FALSE);

    /* Check if Timeout occur */
    if(pUartState->u32TxSize > 0U)
    {
        pUartState->eTransmitStatus = LINFLEXD_UART_IP_STATUS_TIMEOUT;
    }else /* The transmit process is complete */
    {
        pUartState->eTransmitStatus = LINFLEXD_UART_IP_STATUS_SUCCESS;
    }
    pUartState->bIsTxBusy = FALSE;
    return pUartState->eTransmitStatus;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_GetData
 * Description   : Read data from the buffer register, according to configured
 * word length.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void Linflexd_Uart_Ip_GetData(uint32 u32Instance)
{
    const Linflexd_Uart_Ip_UserConfigType *pUartUserCfg = (Linflexd_Uart_Ip_UserConfigType*) Linflexd_Uart_Ip_apUserConfig[u32Instance];
    Linflexd_Uart_Ip_StateStructureType * pUartState;
    LINFLEXD_Type * pBase;

    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];
    pBase = Linflexd_Uart_Ip_apBases[u32Instance];


    if((pUartUserCfg->eWordLength == LINFLEXD_UART_IP_7_BITS) || (pUartUserCfg->eWordLength == LINFLEXD_UART_IP_8_BITS))
    {
        /* Get the data */
        *(pUartState->pRxBuff) = LINFLEXD_GetRxDataBuffer1Byte(pBase);
        /* Update the state structure */
        ++pUartState->pRxBuff;
        --pUartState->u32RxSize;
    }
    else
    {
        /* Get the data and update state structure */
        if(pUartState->u32RxSize == 1U)
        {
            *(pUartState->pRxBuff) = (uint8)(LINFLEXD_GetRxDataBuffer2Bytes(pBase));
            ++pUartState->pRxBuff;
            --pUartState->u32RxSize;
        }
        else
        {
            *((uint16*)(pUartState->pRxBuff)) = LINFLEXD_GetRxDataBuffer2Bytes(pBase);
            /* Move the pointer twice */
            ++pUartState->pRxBuff;
            ++pUartState->pRxBuff;
            pUartState->u32RxSize -= 2U;
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_SyncReceive_Privileged
 * Description   : Retrieves data from the LINFLEXD module in UART mode with
 * polling method.
 *
*END**************************************************************************/
/* implements     Linflexd_Uart_Ip_SyncReceive_Activity*/
Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_SyncReceive_Privileged(uint32 u32Instance,
                                                                    uint8 * pRxBuff,
                                                                    uint32 u32RxSize)
{
    /* Check the validity of the parameters */
    LINFLEXD_UART_DEV_ASSERT(u32RxSize > 0U);
    LINFLEXD_UART_DEV_ASSERT(pRxBuff != NULL_PTR);
    LINFLEXD_UART_DEV_ASSERT(u32Instance < LINFLEXD_INSTANCE_COUNT);

    Linflexd_Uart_Ip_StateStructureType * pUartState;
    boolean bIsError = FALSE;
    LINFLEXD_Type * pBase;
    uint32 u32StartTime;
    uint32 u32ElapsedTime;
    uint32 u32TimeoutTicks;

    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];
    pBase = Linflexd_Uart_Ip_apBases[u32Instance];

    LINFLEXD_UART_DEV_ASSERT(pUartState != NULL_PTR);

    SchM_Enter_Uart_UART_EXCLUSIVE_AREA_06();
    /* Check driver is not busy transmitting data from a previous asynchronous call */
    if (pUartState->bIsRxBusy)
    {
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_06();
        return LINFLEXD_UART_IP_STATUS_BUSY;
    }

     /* Initialize the module driver state structure */
    pUartState->bIsRxBusy = TRUE;
    SchM_Exit_Uart_UART_EXCLUSIVE_AREA_06();
    pUartState->pRxBuff = pRxBuff;
    pUartState->u32RxSize = u32RxSize;
    pUartState->eReceiveStatus = LINFLEXD_UART_IP_STATUS_BUSY;
    
    /*The interrupts shall be disabled when the Linflexd_Uart_Ip_SyncReceive and Linflexd_Uart_Ip_SyncSend are called.*/
    /* Disble transmission complete interrupt */
    LINFLEXD_SetInterruptMode(pBase, LINFLEXD_DATA_TRANSMITTED_INT, FALSE);
    /* Disable receive data full interrupt. */
    LINFLEXD_SetInterruptMode(pBase, LINFLEXD_DATA_RECEPTION_COMPLETE_INT, FALSE);
    /* Disable error interrupts */
    LINFLEXD_SetInterruptMode(pBase, LINFLEXD_FRAME_ERROR_INT, FALSE);
    LINFLEXD_SetInterruptMode(pBase, LINFLEXD_BUFFER_OVERRUN_INT, FALSE);

    /* Enable the receiver */
    LINFLEXD_SetReceiverState(pBase, TRUE);

    u32StartTime = OsIf_GetCounter(LINFLEXD_UART_IP_TIMEOUT_TYPE);

    /* To be updated with timeout when aProach is defined*/
    while ((pUartState->u32RxSize > 0U) && !LINFLEXD_CheckTimeout(u32StartTime, (uint32)LINFLEXD_UART_TIMEOUT_VALUE_US))
    {
        /* Wait until data reception flag is set or timeout occurs if there is an error during reception */
        while (!LINFLEXD_GetStatusFlag(pBase, LINFLEXD_UART_DATA_RECEPTION_COMPLETE_FLAG) && \
               !LINFLEXD_CheckTimeout(u32StartTime, (uint32)LINFLEXD_UART_TIMEOUT_VALUE_US))
        {}

        /* Update the receive status according to the error occurred */
        if (LINFLEXD_GetStatusFlag(pBase, LINFLEXD_UART_BUFFER_OVERRUN_FLAG))
        {
            /* Update the status */
            pUartState->eReceiveStatus = LINFLEXD_UART_IP_STATUS_RX_OVERRUN;
            /* Clear the flag */
            LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_BUFFER_OVERRUN_FLAG);
            bIsError = TRUE;
        }
        if (LINFLEXD_GetStatusFlag(pBase, LINFLEXD_UART_FRAME_ERROR_FLAG))
        {
            /* Update the status */
            pUartState->eReceiveStatus = LINFLEXD_UART_IP_STATUS_FRAMING_ERROR;
            /* Clear the flag */
            LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_FRAME_ERROR_FLAG);
            bIsError = TRUE;
        }
        if (LINFLEXD_GetStatusFlag(pBase, LINFLEXD_UART_PARITY_ERROR_FLAG))
        {
            /* Update the status */
            pUartState->eReceiveStatus = LINFLEXD_UART_IP_STATUS_PARITY_ERROR;
            /* Clear the flag */
            LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_PARITY_ERROR_FLAG);
            bIsError = TRUE;
        }
        if (LINFLEXD_GetStatusFlag(pBase, LINFLEXD_UART_NOISE_FLAG))
        {
            /* Update the status */
            pUartState->eReceiveStatus = LINFLEXD_UART_IP_STATUS_NOISE_ERROR;
            /* Clear the flag */
            LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_NOISE_FLAG);
            bIsError = TRUE;
        }

        if (!bIsError)
        {
            /* Retrieve the data */
            Linflexd_Uart_Ip_GetData(u32Instance);

            /* Clear the flags */
            LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_DATA_RECEPTION_COMPLETE_FLAG);
            LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_MESSAGE_BUFFER_FULL_FLAG);
        }
        else
        {
            break;
        }
    }

    u32ElapsedTime  = OsIf_GetElapsed(&u32StartTime, LINFLEXD_UART_IP_TIMEOUT_TYPE);
    u32TimeoutTicks = OsIf_MicrosToTicks((uint32)LINFLEXD_UART_TIMEOUT_VALUE_US, LINFLEXD_UART_IP_TIMEOUT_TYPE);

    /* Check if Timeout occur */
    if (u32ElapsedTime >= u32TimeoutTicks)
    {
        pUartState->eReceiveStatus = LINFLEXD_UART_IP_STATUS_TIMEOUT;
    }

    if (pUartState->eReceiveStatus == LINFLEXD_UART_IP_STATUS_BUSY)
    {
        pUartState->eReceiveStatus = LINFLEXD_UART_IP_STATUS_SUCCESS;
    }

    /* Disable the receiver */
    LINFLEXD_SetReceiverState(pBase, FALSE);
    pUartState->bIsRxBusy = FALSE;

    return pUartState->eReceiveStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_AbortReceivingData_Privileged
 * Description   : Terminates a non-blocking receive early.
 *
 *END**************************************************************************/
/* implements     Linflexd_Uart_Ip_AbortReceivingData_Activity*/
Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_AbortReceivingData_Privileged(uint32 u32Instance)
{
    LINFLEXD_UART_DEV_ASSERT(u32Instance < LINFLEXD_INSTANCE_COUNT);

    Linflexd_Uart_Ip_StateStructureType * pUartState;
    const Linflexd_Uart_Ip_UserConfigType *pUartUserCfg = (Linflexd_Uart_Ip_UserConfigType*) Linflexd_Uart_Ip_apUserConfig[u32Instance];

    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];
    Linflexd_Uart_Ip_StatusType status = LINFLEXD_UART_IP_STATUS_ERROR;

    LINFLEXD_UART_DEV_ASSERT(pUartState != NULL_PTR);
    LINFLEXD_UART_DEV_ASSERT(pUartUserCfg != NULL_PTR);

    /* Check if a transfer is running. */
    if (!pUartState->bIsRxBusy)
    {
        status = LINFLEXD_UART_IP_STATUS_SUCCESS;
    }
    else
    {
        /* Update the rx status */
        pUartState->eReceiveStatus = LINFLEXD_UART_IP_STATUS_ABORTED;

        /* Stop the running transfer. */
        if (pUartUserCfg->eTransferType == LINFLEXD_UART_IP_USING_INTERRUPTS)
        {
            Linflexd_Uart_Ip_CompleteReceiveUsingInterrupts(u32Instance);
        }
        #if (LINFLEXD_UART_HAS_DMA_ENABLED == STD_ON)
            else
            {
                /* Release the DMA channel */
                (void)Dma_Ip_SetLogicChannelCommand(pUartUserCfg->u8RxDMAChannel, DMA_IP_CH_CLEAR_HARDWARE_REQUEST);
                Linflexd_Uart_Ip_CompleteReceiveUsingDma(u32Instance);
            }
        #endif
        status = LINFLEXD_UART_IP_STATUS_SUCCESS;
    }
    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_AbortSendingData_Privileged
 * Description   : This function terminates an non-blocking UART transmission
 * early. During a non-blocking UART transmission, the user has the option to
 * terminate the transmission early if the transmission is still in progress.
 *
 *END**************************************************************************/
/* implements     Linflexd_Uart_Ip_AbortSendingData_Activity */
Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_AbortSendingData_Privileged(uint32 u32Instance)
{
    LINFLEXD_UART_DEV_ASSERT(u32Instance < LINFLEXD_INSTANCE_COUNT);

    Linflexd_Uart_Ip_StateStructureType * pUartState;
    const Linflexd_Uart_Ip_UserConfigType *pUartUserCfg = (Linflexd_Uart_Ip_UserConfigType*) Linflexd_Uart_Ip_apUserConfig[u32Instance];

    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];
    Linflexd_Uart_Ip_StatusType status = LINFLEXD_UART_IP_STATUS_ERROR;

    LINFLEXD_UART_DEV_ASSERT(pUartState != NULL_PTR);
    LINFLEXD_UART_DEV_ASSERT(pUartUserCfg != NULL_PTR);

    /* Check if a transfer is running. */
    if (!pUartState->bIsTxBusy)
    {
        status = LINFLEXD_UART_IP_STATUS_SUCCESS;
    }
    else
    {
        /* Update the tx status */
        pUartState->eTransmitStatus = LINFLEXD_UART_IP_STATUS_ABORTED;

        /* Stop the running transfer. */
        if (pUartUserCfg->eTransferType == LINFLEXD_UART_IP_USING_INTERRUPTS)
        {
            Linflexd_Uart_Ip_CompleteSendUsingInterrupts(u32Instance);
        }
        #if (LINFLEXD_UART_HAS_DMA_ENABLED == STD_ON)
            else
            {
                /* Release the DMA channel */
                (void)Dma_Ip_SetLogicChannelCommand(pUartUserCfg->u8TxDMAChannel, DMA_IP_CH_CLEAR_HARDWARE_REQUEST);
                Linflexd_Uart_Ip_CompleteSendUsingDma(u32Instance);
            }
        #endif
        status = LINFLEXD_UART_IP_STATUS_SUCCESS;
    }
    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_StartReceiveUsingInterrupts
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_StartReceiveUsingInterrupts(uint32 u32Instance,
                                                                                uint8 * pRxBuff,
                                                                                uint32 u32RxSize)
{
    LINFLEXD_UART_DEV_ASSERT(u32Instance < LINFLEXD_INSTANCE_COUNT);
    LINFLEXD_UART_DEV_ASSERT(pRxBuff != NULL_PTR);

    Linflexd_Uart_Ip_StateStructureType * pUartState;
    const Linflexd_Uart_Ip_UserConfigType *pUartUserCfg = (Linflexd_Uart_Ip_UserConfigType*) Linflexd_Uart_Ip_apUserConfig[u32Instance];
    LINFLEXD_Type * pBase;

    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];
    pBase = Linflexd_Uart_Ip_apBases[u32Instance];
    Linflexd_Uart_Ip_StatusType status = LINFLEXD_UART_IP_STATUS_ERROR;

    SchM_Enter_Uart_UART_EXCLUSIVE_AREA_07();
    /* Check it's not busy receiving data from a previous function call */
    if ((pUartState->bIsRxBusy) && (pUartUserCfg->pfRxCallback != NULL_PTR))
    {
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_07();
        status = LINFLEXD_UART_IP_STATUS_BUSY;
    }
    else
    {
        /* Initialize the module driver state struct to indicate transfer in progress
         * and with the buffer and byte count data. */
        pUartState->bIsRxBusy = TRUE;
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_07();
        pUartState->pRxBuff = pRxBuff;
        LINFLEXD_UART_DEV_ASSERT(u32RxSize > 0U);
        pUartState->u32RxSize = u32RxSize;
        pUartState->eReceiveStatus = LINFLEXD_UART_IP_STATUS_BUSY;

        /* Clear the flag */
        LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_DATA_RECEPTION_COMPLETE_FLAG);
        LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_MESSAGE_BUFFER_FULL_FLAG);

        /* Enable the receiver */
        LINFLEXD_SetReceiverState(pBase, TRUE);

        /* Enable receive data full interrupt */
        LINFLEXD_SetInterruptMode(pBase, LINFLEXD_DATA_RECEPTION_COMPLETE_INT, TRUE);
        status = LINFLEXD_UART_IP_STATUS_SUCCESS;
    }
    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_GetReceiveStatus
 * Description   : This function returns whether the previous UART receive is
 * complete. When performing a non-blocking receive, the user can call this
 * function to ascertain the state of the current receive progress: in progress
 * or complete. In addition, if the receive is still in progress, the user can
 * obtain the number of words that have not yet been received.
 *
 *END**************************************************************************/
/* implements     Linflexd_Uart_Ip_GetReceiveStatus_Activity */
Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_GetReceiveStatus(uint32 u32Instance, uint32 * pBytesRemaining)
{
    LINFLEXD_UART_DEV_ASSERT(u32Instance < LINFLEXD_INSTANCE_COUNT);

    Linflexd_Uart_Ip_StateStructureType * pUartState;
    const Linflexd_Uart_Ip_UserConfigType *pUartUserCfg = (Linflexd_Uart_Ip_UserConfigType*) Linflexd_Uart_Ip_apUserConfig[u32Instance];
#if (LINFLEXD_UART_HAS_DMA_ENABLED == STD_ON)
    const Dma_Ip_LogicChannelInfoParamType eDmaLogicChnParam = DMA_IP_CH_GET_CURRENT_ITER_COUNT;
#endif
    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];

    LINFLEXD_UART_DEV_ASSERT(pUartState != NULL_PTR);
    LINFLEXD_UART_DEV_ASSERT(pUartUserCfg != NULL_PTR);

    if (pBytesRemaining != NULL_PTR)
    {
        if (pUartState->bIsRxBusy)
        {
            /* Fill in the number of bytes yet to be received and update the return value if needed */
            if (pUartUserCfg->eTransferType == LINFLEXD_UART_IP_USING_INTERRUPTS)
            {
                /* In interrupt-based communication, the remaining bytes are retrieved
                 * from the state structure
                 */
                *pBytesRemaining = pUartState->u32RxSize;
            }
#if (LINFLEXD_UART_HAS_DMA_ENABLED == STD_ON)
            else
            {
                /* In DMA-based communication, the remaining bytes are retrieved
                 * from the current DMA major loop count
                 */
                Dma_Ip_GetLogicChannelParam(pUartUserCfg->u8RxDMAChannel, eDmaLogicChnParam, pBytesRemaining);
            }
#endif
        }
        else
        {
            *pBytesRemaining = 0;
        }
    }

    return pUartState->eReceiveStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_GetTransmitStatus
 * Description   : This function returns whether the previous UART transmit has
 * finished. When performing non-blocking transmit, the user can call this
 * function to ascertain the state of the current transmission:
 * in progress (or busy) or complete (success). In addition, if the transmission
 * is still in progress, the user can obtain the number of words that have been
 * currently transferred.
 *
 *END**************************************************************************/
 /* implements     Linflexd_Uart_Ip_GetTransmitStatus_Activity */

Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_GetTransmitStatus(uint32 u32Instance, uint32 * pBytesRemaining)
{
    LINFLEXD_UART_DEV_ASSERT(u32Instance < LINFLEXD_INSTANCE_COUNT);

    Linflexd_Uart_Ip_StateStructureType * pUartState;
    const Linflexd_Uart_Ip_UserConfigType *pUartUserCfg = (Linflexd_Uart_Ip_UserConfigType*) Linflexd_Uart_Ip_apUserConfig[u32Instance];
#if (LINFLEXD_UART_HAS_DMA_ENABLED == STD_ON)
    const Dma_Ip_LogicChannelInfoParamType eDmaLogicChnParam = DMA_IP_CH_GET_CURRENT_ITER_COUNT;
#endif
    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];

    LINFLEXD_UART_DEV_ASSERT(pUartState != NULL_PTR);
    LINFLEXD_UART_DEV_ASSERT(pUartUserCfg != NULL_PTR);

    if (pBytesRemaining != NULL_PTR)
    {
        /* Fill in the number of bytes yet to be transferred and update the return value if needed */
        if (pUartState->bIsTxBusy)
        {
            /* Fill in the bytes not transferred yet. */
            if (pUartUserCfg->eTransferType == LINFLEXD_UART_IP_USING_INTERRUPTS)
            {
                /* In interrupt-based communication, the remaining bytes are retrieved
                 * from the state structure
                 */
                *pBytesRemaining = pUartState->u32TxSize;
            }
#if (LINFLEXD_UART_HAS_DMA_ENABLED == STD_ON)
            else
            {
                /* In DMA-based communication, the remaining bytes are retrieved
                 * from the current DMA major loop count
                 */
                Dma_Ip_GetLogicChannelParam(pUartUserCfg->u8TxDMAChannel, eDmaLogicChnParam, pBytesRemaining);
            }
#endif
        }
        else
        {
            *pBytesRemaining = 0;
        }
    }
    return pUartState->eTransmitStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_AsyncReceive_Privileged
 * Description   : Retrieves data from the LINFLEXD module in UART mode with
 * non-blocking method.
 *
 *END**************************************************************************/
 /* implements     Linflexd_Uart_Ip_AsyncReceive_Activity*/
Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_AsyncReceive_Privileged(uint32 u32Instance,
                                                                     uint8 * pRxBuff,
                                                                     uint32 u32RxSize)
{
    LINFLEXD_UART_DEV_ASSERT(pRxBuff != NULL_PTR);
    LINFLEXD_UART_DEV_ASSERT(u32Instance < LINFLEXD_INSTANCE_COUNT);
    LINFLEXD_Type * pBase;
    Linflexd_Uart_Ip_StatusType retVal = LINFLEXD_UART_IP_STATUS_ERROR;
    const Linflexd_Uart_Ip_UserConfigType *pUartUserCfg = (Linflexd_Uart_Ip_UserConfigType*) Linflexd_Uart_Ip_apUserConfig[u32Instance];

    LINFLEXD_UART_DEV_ASSERT(pUartUserCfg != NULL_PTR);

    pBase = Linflexd_Uart_Ip_apBases[u32Instance];

    /* Enable error interrupts */
    LINFLEXD_SetInterruptMode(pBase, LINFLEXD_FRAME_ERROR_INT, TRUE);
    LINFLEXD_SetInterruptMode(pBase, LINFLEXD_BUFFER_OVERRUN_INT, TRUE);

    if (pUartUserCfg->eTransferType == LINFLEXD_UART_IP_USING_INTERRUPTS)
    {
        /* Start the transmission process using interrupts */
        retVal = Linflexd_Uart_Ip_StartReceiveUsingInterrupts(u32Instance, pRxBuff, u32RxSize);
    }
#if (LINFLEXD_UART_HAS_DMA_ENABLED == STD_ON)
    else
    {
        /* Start the transmission process using DMA */
        retVal = Linflexd_Uart_Ip_StartReceiveUsingDma(u32Instance, pRxBuff, u32RxSize);
    }
#endif
    return retVal;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_StartSendUsingInterrupts
 * Description   : Initiate (start) a transmit by beginning the process of
 * sending data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_StartSendUsingInterrupts(uint32 u32Instance,
                                                                             const uint8 * pTxBuff,
                                                                             uint32 u32TxSize)
{
    LINFLEXD_Type * pBase;
    Linflexd_Uart_Ip_StateStructureType * pUartState;
    Linflexd_Uart_Ip_StatusType status = LINFLEXD_UART_IP_STATUS_ERROR;
    pBase = Linflexd_Uart_Ip_apBases[u32Instance];
    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];

    SchM_Enter_Uart_UART_EXCLUSIVE_AREA_04();
    /* Check it's not busy transmitting data from a previous function call */
    if (pUartState->bIsTxBusy)
    {
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_04();
        status = LINFLEXD_UART_IP_STATUS_BUSY;
    }
    else
    {
        /* Initialize the module driver state structure */
        pUartState->bIsTxBusy = TRUE;
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_04();
        pUartState->pTxBuff = pTxBuff;

        LINFLEXD_UART_DEV_ASSERT(u32TxSize > 0U);
        pUartState->u32TxSize = u32TxSize;

        pUartState->eTransmitStatus = LINFLEXD_UART_IP_STATUS_BUSY;

        /* Enable the transmitter */
        LINFLEXD_SetTransmitterState(pBase, TRUE);

        /* Clear the tx empty flag to make sure the transmission of the first byte
         * doesn't occur right after enabling the tx interrupt
         */
        LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_DATA_TRANSMITTED_FLAG);

        /* Enable transmission complete interrupt */
        LINFLEXD_SetInterruptMode(pBase, LINFLEXD_DATA_TRANSMITTED_INT, TRUE);

        /* Transmit the first word */
        Linflexd_Uart_Ip_PutData(u32Instance);
        status = LINFLEXD_UART_IP_STATUS_SUCCESS;
    }
    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_AsyncSend_Privileged
 * Description   : This function sends data using LINFLEXD module in UART mode
 * with non-blocking method.
 *
 *END**************************************************************************/
 /* implements     Linflexd_Uart_Ip_AsyncSend_Activity */
Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_AsyncSend_Privileged(uint32 u32Instance,
                                                                  const uint8 * pTxBuff,
                                                                  uint32 u32TxSize)
{
    LINFLEXD_UART_DEV_ASSERT(pTxBuff != NULL_PTR);
    LINFLEXD_UART_DEV_ASSERT(u32Instance < LINFLEXD_INSTANCE_COUNT);

    Linflexd_Uart_Ip_StatusType retVal = LINFLEXD_UART_IP_STATUS_SUCCESS;
    const Linflexd_Uart_Ip_UserConfigType *pUartUserCfg;

    pUartUserCfg = (Linflexd_Uart_Ip_UserConfigType*) Linflexd_Uart_Ip_apUserConfig[u32Instance];

    LINFLEXD_UART_DEV_ASSERT(pUartUserCfg != NULL_PTR);
    LINFLEXD_UART_DEV_ASSERT((pUartUserCfg->eTransferType == LINFLEXD_UART_IP_USING_INTERRUPTS) ||
                                (pUartUserCfg->eTransferType == LINFLEXD_UART_IP_USING_DMA));

    if (pUartUserCfg->eTransferType == LINFLEXD_UART_IP_USING_INTERRUPTS)
    {
        /* Start the transmission process using interrupts */
        retVal = Linflexd_Uart_Ip_StartSendUsingInterrupts(u32Instance, pTxBuff, u32TxSize);
    }
#if (LINFLEXD_UART_HAS_DMA_ENABLED == STD_ON)
    else
    {
        /* Start the transmission process using DMA */
        retVal = Linflexd_Uart_Ip_StartSendUsingDma(u32Instance, pTxBuff, u32TxSize);
    }
#endif
    /* Start the transmission process */
    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_RxIRQHandler
 * Description   : Rx interrupt handler for UART.
 * This handler uses the rx buffer stored in the state structure to receive
 * data. This is not a public API as it is called by IRQ whenever an interrupt
 * occurs.
 *
 *END**************************************************************************/
static void Linflexd_Uart_Ip_RxIRQHandler(uint32 u32Instance)
{
    Linflexd_Uart_Ip_StateStructureType * pUartState;
    const Linflexd_Uart_Ip_UserConfigType *pUartUserCfg = (Linflexd_Uart_Ip_UserConfigType*) Linflexd_Uart_Ip_apUserConfig[u32Instance];
    LINFLEXD_Type * pBase;

    pBase = Linflexd_Uart_Ip_apBases[u32Instance];
    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];

    if (pUartState != NULL_PTR)
    {
        if (pUartState->bIsDriverInitialized)
        {
            /* Exit if there is no reception in progress */
            if (!pUartState->bIsRxBusy)
            {
                /* Clear the flag */
                LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_DATA_RECEPTION_COMPLETE_FLAG);
                return;
            }

            /* Retrieve the data */
            Linflexd_Uart_Ip_GetData(u32Instance);

            /* Clear the flags */
            LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_DATA_RECEPTION_COMPLETE_FLAG);
            LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_MESSAGE_BUFFER_FULL_FLAG);

            /* Check if this was the last byte in the current buffer */
            if (pUartState->u32RxSize == 0U)
            {
                /* Invoke the callback when the buffer is finished;
                * Application can provide another buffer inside the callback by calling Linflexd_Uart_Ip_SetRxBuffer */
                if (pUartUserCfg->pfRxCallback != NULL_PTR)
                {
                    pUartUserCfg->pfRxCallback(u32Instance, pUartState, LINFLEXD_UART_IP_EVENT_RX_FULL, pUartUserCfg->pRxCallbackParam);
                }
            }

            /* Finish reception if this was the last byte received */
            if (pUartState->u32RxSize == 0U)
            {
                /* Complete transfer (disable rx logic) */
                Linflexd_Uart_Ip_CompleteReceiveUsingInterrupts(u32Instance);

                /* Invoke callback if there is one */
                if (pUartUserCfg->pfRxCallback != NULL_PTR)
                {
                    pUartUserCfg->pfRxCallback(u32Instance, pUartState, LINFLEXD_UART_IP_EVENT_END_TRANSFER, pUartUserCfg->pRxCallbackParam);
                }
            }
        }
        /* Case of spurious interrupt when driver had an error in initialization */
        else
        {
            /* Clear the flags */
            LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_DATA_RECEPTION_COMPLETE_FLAG);
            LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_MESSAGE_BUFFER_FULL_FLAG);
        }
    }
    /* Case of spurious interrupt when driver is not at all initialized*/
    else
    {
        /* Clear the flags */
        LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_DATA_RECEPTION_COMPLETE_FLAG);
        LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_MESSAGE_BUFFER_FULL_FLAG);
    }

}

/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_TxIRQHandler
 * Description   : Tx interrupt handler for UART.
 * This handler uses the tx buffer stored in the state structure to transmit
 * data. This is not a public API as it is called by IRQ whenever an interrupt
 * occurs.
 *
 *END**************************************************************************/
static void Linflexd_Uart_Ip_TxIRQHandler(uint32 u32Instance)
{
    Linflexd_Uart_Ip_StateStructureType * pUartState;
    const Linflexd_Uart_Ip_UserConfigType *pUartUserCfg = (Linflexd_Uart_Ip_UserConfigType*) Linflexd_Uart_Ip_apUserConfig[u32Instance];
    LINFLEXD_Type * pBase;

    pBase = Linflexd_Uart_Ip_apBases[u32Instance];
    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];

    if (pUartState != NULL_PTR)
    {
        if (pUartState->bIsDriverInitialized)
        {
            /* Exit if there is no transmission in progress */
            if (!pUartState->bIsTxBusy)
            {
                /* Clear the flag */
                LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_DATA_TRANSMITTED_FLAG);
                return;
            }

            /* Check if there are any more bytes to send */
            if (pUartState->u32TxSize > 0U)
            {
                /* Clear the flag */
                LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_DATA_TRANSMITTED_FLAG);

                /* Send data */
                Linflexd_Uart_Ip_PutData(u32Instance);
            }
            else
            {
                /* Invoke the callback when the buffer is finished;
                * Application can provide another buffer inside the callback by calling Linflexd_Uart_Ip_SetTxBuffer */
                if (pUartUserCfg->pfTxCallback != NULL_PTR)
                {
                    pUartUserCfg->pfTxCallback(u32Instance, pUartState, LINFLEXD_UART_IP_EVENT_TX_EMPTY, pUartUserCfg->pTxCallbackParam);
                }

                /* If there is no more data to send, complete the transmission */
                if (pUartState->u32TxSize == 0U)
                {
                    Linflexd_Uart_Ip_CompleteSendUsingInterrupts(u32Instance);

                    /* Call the callback to notify application that the transfer is complete */
                    if (pUartUserCfg->pfTxCallback != NULL_PTR)
                    {
                        pUartUserCfg->pfTxCallback(u32Instance, pUartState, LINFLEXD_UART_IP_EVENT_END_TRANSFER, pUartUserCfg->pTxCallbackParam);
                    }

                    /* Clear the flag */
                    LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_DATA_TRANSMITTED_FLAG);
                }
            }
        }
        /* Case of spurious interrupt when driver had an error in initialization */
        else
        {
            LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_DATA_TRANSMITTED_FLAG);
        }
    }
    /* Case of spurious interrupt when driver is not at all initialized*/
    else
    {
        LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_DATA_TRANSMITTED_FLAG);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_ErrIRQHandler
 * Description   : Error interrupt handler for UART.
 * This handler calls the user callback to treat error conditions.
 *
 *END**************************************************************************/
static void Linflexd_Uart_Ip_ErrIRQHandler(uint32 u32Instance)
{
    Linflexd_Uart_Ip_StateStructureType * pUartState;
    const Linflexd_Uart_Ip_UserConfigType *pUartUserCfg = (Linflexd_Uart_Ip_UserConfigType*) Linflexd_Uart_Ip_apUserConfig[u32Instance];
    LINFLEXD_Type * pBase;

    pBase = Linflexd_Uart_Ip_apBases[u32Instance];
    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];

    if (pUartState != NULL_PTR)
    {
        if (pUartState->bIsDriverInitialized)
        {
            /* Update the receive status according to the error occurred */
            if (LINFLEXD_GetStatusFlag(pBase, LINFLEXD_UART_BUFFER_OVERRUN_FLAG))
            {
                /* Update the status */
                pUartState->eReceiveStatus = LINFLEXD_UART_IP_STATUS_RX_OVERRUN;
                /* Clear the flag */
                LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_BUFFER_OVERRUN_FLAG);
            }
            else if (LINFLEXD_GetStatusFlag(pBase, LINFLEXD_UART_FRAME_ERROR_FLAG))
            {
                /* Update the status */
                pUartState->eReceiveStatus = LINFLEXD_UART_IP_STATUS_FRAMING_ERROR;
                /* Clear the flag */
                LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_FRAME_ERROR_FLAG);
            }
            else
            {
                /* This branch should never be reached - avoid MISRA violations */
                pUartState->eReceiveStatus = LINFLEXD_UART_IP_STATUS_ERROR;
            }

            /* Terminate the current reception */
            if (pUartUserCfg->eTransferType == LINFLEXD_UART_IP_USING_INTERRUPTS)
            {
                Linflexd_Uart_Ip_CompleteReceiveUsingInterrupts(u32Instance);
            }
#if (LINFLEXD_UART_HAS_DMA_ENABLED == STD_ON)
            else
            {
                /* Release the DMA channel */
                (void)Dma_Ip_SetLogicChannelCommand(pUartUserCfg->u8RxDMAChannel, DMA_IP_CH_CLEAR_HARDWARE_REQUEST);
                Linflexd_Uart_Ip_CompleteReceiveUsingDma(u32Instance);
            }
#endif
            /* Invoke the callback, if any */
            if (pUartUserCfg->pfErrorCallback != NULL_PTR)
            {
                pUartUserCfg->pfErrorCallback(u32Instance, pUartState, LINFLEXD_UART_IP_EVENT_ERROR, pUartUserCfg->pErrorCallbackParam);
            }
        }
        /* Case of spurious interrupt when driver had an error in initialization */
        else
        {
            LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_BUFFER_OVERRUN_FLAG);
            LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_FRAME_ERROR_FLAG);
        }
    }
    /* Case of spurious interrupt when driver is not at all initialized*/
    else
    {
        LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_BUFFER_OVERRUN_FLAG);
        LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_FRAME_ERROR_FLAG);
    }

}

#if defined (FEATURE_LINFLEXD_ORED_INT_LINES)
/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_IRQHandler
 * Description   : Interrupt handler for UART.
 * This handler uses the buffers stored in the state structure to transfer
 * data. This is not a public API as it is called by IRQ whenever an interrupt
 * occurs.
 *
 *END**************************************************************************/
void Linflexd_Uart_Ip_IRQHandler(uint32 u32Instance)
{
    LINFLEXD_Type * pBase;

    pBase = Linflexd_Uart_Ip_apBases[u32Instance];

    /* Handle receive data full interrupt */
    if (LINFLEXD_GetStatusFlag(pBase, LINFLEXD_UART_DATA_RECEPTION_COMPLETE_FLAG))
    {
        if (LINFLEXD_IsInterruptEnabled(pBase, LINFLEXD_DATA_RECEPTION_COMPLETE_INT))
        {
            Linflexd_Uart_Ip_RxIRQHandler(u32Instance);
        }
        else
        {
            /* CPR_RTD_00028.uart Spurious interrupt*/
            /* Clear Interrupt status flags */
            LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_DATA_RECEPTION_COMPLETE_FLAG);
            LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_MESSAGE_BUFFER_FULL_FLAG);
        }
    }

    /* Handle transmitter data register empty interrupt */
    if (LINFLEXD_GetStatusFlag(pBase, LINFLEXD_UART_DATA_TRANSMITTED_FLAG))
    {
        if (LINFLEXD_IsInterruptEnabled(pBase, LINFLEXD_DATA_TRANSMITTED_INT))
        {
            Linflexd_Uart_Ip_TxIRQHandler(u32Instance);
        }
        else
        {
            /* CPR_RTD_00028.uart Spurious interrupt*/
            /* Clear Interrupt status flags */
            LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_DATA_TRANSMITTED_FLAG);
        }
    }

    /* Handle the error interrupts if no rx/tx interrupt was triggered */
    if (LINFLEXD_GetStatusFlag(pBase, LINFLEXD_UART_FRAME_ERROR_FLAG))
    {
        if (LINFLEXD_IsInterruptEnabled(pBase, LINFLEXD_FRAME_ERROR_INT))
        {
            Linflexd_Uart_Ip_ErrIRQHandler(u32Instance);
        }
        else
        {
            /* CPR_RTD_00028.uart Spurious interrupt*/
            /* Clear Interrupt status flags */
            LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_FRAME_ERROR_FLAG);
        }
    }

    if (LINFLEXD_GetStatusFlag(pBase, LINFLEXD_UART_BUFFER_OVERRUN_FLAG))
    {
        if (LINFLEXD_IsInterruptEnabled(pBase, LINFLEXD_BUFFER_OVERRUN_INT))
        {
            Linflexd_Uart_Ip_ErrIRQHandler(u32Instance);
        }
        else
        {
            /* CPR_RTD_00028.uart Spurious interrupt*/
            /* Clear Interrupt status flags */
            LINFLEXD_ClearStatusFlag(pBase, LINFLEXD_UART_BUFFER_OVERRUN_FLAG);
        }
    }
}
#endif /*FEATURE_LINFLEXD_ORED_INT_LINES*/

#if (LINFLEXD_UART_HAS_DMA_ENABLED == STD_ON)
/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_StartSendUsingDma
 * Description   : Initiate (start) a transmit by beginning the process of
 * sending data using DMA transfers.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_StartSendUsingDma(uint32 u32Instance,
                                                                      const uint8 * pTxBuff,
                                                                      uint32 u32TxSize)
{
    LINFLEXD_Type * pBase;
    Linflexd_Uart_Ip_StateStructureType * pUartState;
    const Linflexd_Uart_Ip_UserConfigType *pUartUserCfg;
    Dma_Ip_LogicChannelTransferListType dmaTransferList[LINFLEXD_UART_DMA_CONFIG_LIST_DIMENSION];
    Dma_Ip_ReturnType eDmaReturnStatus;

    pBase = Linflexd_Uart_Ip_apBases[u32Instance];
    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];
    pUartUserCfg = (Linflexd_Uart_Ip_UserConfigType*) Linflexd_Uart_Ip_apUserConfig[u32Instance];

    SchM_Enter_Uart_UART_EXCLUSIVE_AREA_05();
    /* Check it's not busy transmitting data from a previous function call */
    if (pUartState->bIsTxBusy)
    {
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_05();
        return LINFLEXD_UART_IP_STATUS_BUSY;
    }

    /* Update state structure */
    pUartState->bIsTxBusy = TRUE;
    SchM_Exit_Uart_UART_EXCLUSIVE_AREA_05();
    pUartState->pTxBuff = pTxBuff;

    /* Check the validity of the parameters */
    LINFLEXD_UART_DEV_ASSERT(u32TxSize > 0U);
    if(!((pUartUserCfg->eWordLength == LINFLEXD_UART_IP_7_BITS) || (pUartUserCfg->eWordLength == LINFLEXD_UART_IP_8_BITS)))
    {
        /* The size of the buffer should be an even number for DMA transfers with 15/16 bits word length */
        LINFLEXD_UART_DEV_ASSERT((u32TxSize & 1U) == 0U);
    }
    pUartState->u32TxSize = 0U;
    pUartState->eTransmitStatus = LINFLEXD_UART_IP_STATUS_BUSY;

    /* Set up parameters for Dma_Ip_LogicChannelTransferListType */
    dmaTransferList[0].Param = DMA_IP_CH_SET_SOURCE_ADDRESS;
    dmaTransferList[0].Value = (uint32)pTxBuff;
    dmaTransferList[1].Param = DMA_IP_CH_SET_DESTINATION_ADDRESS;
    dmaTransferList[1].Value = LINFLEXD_UART_LSBW_ADDR(pBase->BDRL);
    dmaTransferList[2].Param = DMA_IP_CH_SET_SOURCE_SIGNED_OFFSET;
    dmaTransferList[3].Param = DMA_IP_CH_SET_DESTINATION_SIGNED_OFFSET;
    dmaTransferList[3].Value = 0;
    dmaTransferList[4].Param = DMA_IP_CH_SET_MAJORLOOP_COUNT;
    dmaTransferList[5].Param = DMA_IP_CH_SET_MINORLOOP_SIZE;
    dmaTransferList[6].Param = DMA_IP_CH_SET_DESTINATION_TRANSFER_SIZE;
    dmaTransferList[7].Param = DMA_IP_CH_SET_SOURCE_TRANSFER_SIZE;
    if((pUartUserCfg->eWordLength == LINFLEXD_UART_IP_7_BITS) || (pUartUserCfg->eWordLength == LINFLEXD_UART_IP_8_BITS))
    {
        dmaTransferList[2].Value = 1;
        dmaTransferList[4].Value = u32TxSize;
        dmaTransferList[5].Value = 1;
        dmaTransferList[6].Value = DMA_IP_TRANSFER_SIZE_1_BYTE;
        dmaTransferList[7].Value = DMA_IP_TRANSFER_SIZE_1_BYTE;
    }
    else
    {
        dmaTransferList[2].Value = 2;
        dmaTransferList[4].Value = u32TxSize/2;
        dmaTransferList[5].Value = 2;
        dmaTransferList[6].Value = DMA_IP_TRANSFER_SIZE_2_BYTE;
        dmaTransferList[7].Value = DMA_IP_TRANSFER_SIZE_2_BYTE;
    }

    dmaTransferList[8].Param = DMA_IP_CH_SET_CONTROL_EN_MAJOR_INTERRUPT;
    dmaTransferList[8].Value = 1;
    dmaTransferList[9].Param = DMA_IP_CH_SET_CONTROL_DIS_AUTO_REQUEST;
    dmaTransferList[9].Value = 1;

    /* Configure the transfer control descriptor for the DMA channel */
    eDmaReturnStatus = Dma_Ip_SetLogicChannelTransferList(pUartUserCfg->u8TxDMAChannel, dmaTransferList, LINFLEXD_UART_DMA_CONFIG_LIST_DIMENSION);
    LINFLEXD_UART_DEV_ASSERT(eDmaReturnStatus == DMA_IP_STATUS_SUCCESS);

    /* Start the DMA channel */
    eDmaReturnStatus = Dma_Ip_SetLogicChannelCommand(pUartUserCfg->u8TxDMAChannel, DMA_IP_CH_SET_HARDWARE_REQUEST);
    LINFLEXD_UART_DEV_ASSERT(eDmaReturnStatus == DMA_IP_STATUS_SUCCESS);
    /* Enable the transmitter */
    LINFLEXD_SetTransmitterState(pBase, TRUE);

    /* Enable tx DMA requests for the current instance */
    LINFLEXD_SetDmaTxEnable(pBase, TRUE);

    return LINFLEXD_UART_IP_STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_StartReceiveUsingDma
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data using DMA transfers.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static Linflexd_Uart_Ip_StatusType Linflexd_Uart_Ip_StartReceiveUsingDma(uint32 u32Instance,
                                                                         uint8 * pRxBuff,
                                                                         uint32 u32RxSize)
{
    LINFLEXD_Type * pBase;
    Linflexd_Uart_Ip_StateStructureType * pUartState;
    const Linflexd_Uart_Ip_UserConfigType *pUartUserCfg;
    Dma_Ip_LogicChannelTransferListType dmaTransferList[LINFLEXD_UART_DMA_CONFIG_LIST_DIMENSION];
    Dma_Ip_ReturnType eDmaReturnStatus;

    pBase = Linflexd_Uart_Ip_apBases[u32Instance];
    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];
    pUartUserCfg = (Linflexd_Uart_Ip_UserConfigType*) Linflexd_Uart_Ip_apUserConfig[u32Instance];


    SchM_Enter_Uart_UART_EXCLUSIVE_AREA_08();
    /* Check it's not busy transmitting data from a previous function call */
    if (pUartState->bIsRxBusy)
    {
        SchM_Exit_Uart_UART_EXCLUSIVE_AREA_08();
        return LINFLEXD_UART_IP_STATUS_BUSY;
    }

    /* Update the state structure */
    pUartState->bIsRxBusy = TRUE;
    SchM_Exit_Uart_UART_EXCLUSIVE_AREA_08();

    LINFLEXD_UART_DEV_ASSERT(u32RxSize > 0U);
    if(!((pUartUserCfg->eWordLength == LINFLEXD_UART_IP_7_BITS) || (pUartUserCfg->eWordLength == LINFLEXD_UART_IP_8_BITS)))
    {
        /* The size of the buffer should be an even number for DMA transfers with 15/16 bits word length */
        LINFLEXD_UART_DEV_ASSERT((u32RxSize & 1U) == 0U);
    }
    pUartState->pRxBuff = pRxBuff;
    pUartState->u32RxSize = 0U;
    pUartState->eReceiveStatus = LINFLEXD_UART_IP_STATUS_BUSY;

    /* Set up parameters for Dma_Ip_LogicChannelTransferListType */
    dmaTransferList[0].Param = DMA_IP_CH_SET_SOURCE_ADDRESS;
    dmaTransferList[0].Value = LINFLEXD_UART_LSBW_ADDR(pBase->BDRM);
    dmaTransferList[1].Param = DMA_IP_CH_SET_DESTINATION_ADDRESS;
    dmaTransferList[1].Value = (uint32)pRxBuff;
    dmaTransferList[2].Param = DMA_IP_CH_SET_SOURCE_SIGNED_OFFSET;
    dmaTransferList[2].Value = 0;
    dmaTransferList[3].Param = DMA_IP_CH_SET_DESTINATION_SIGNED_OFFSET;
    dmaTransferList[4].Param = DMA_IP_CH_SET_MAJORLOOP_COUNT;
    dmaTransferList[5].Param = DMA_IP_CH_SET_MINORLOOP_SIZE;
    dmaTransferList[6].Param = DMA_IP_CH_SET_DESTINATION_TRANSFER_SIZE;
    dmaTransferList[7].Param = DMA_IP_CH_SET_SOURCE_TRANSFER_SIZE;
    if((pUartUserCfg->eWordLength == LINFLEXD_UART_IP_7_BITS) || (pUartUserCfg->eWordLength == LINFLEXD_UART_IP_8_BITS))
    {
        dmaTransferList[3].Value = 1;
        dmaTransferList[4].Value = u32RxSize;
        dmaTransferList[5].Value = 1;
        dmaTransferList[6].Value = DMA_IP_TRANSFER_SIZE_1_BYTE;
        dmaTransferList[7].Value = DMA_IP_TRANSFER_SIZE_1_BYTE;
    }
    else
    {
        dmaTransferList[3].Value = 2;
        dmaTransferList[4].Value = u32RxSize/2;
        dmaTransferList[5].Value = 2;
        dmaTransferList[6].Value = DMA_IP_TRANSFER_SIZE_2_BYTE;
        dmaTransferList[7].Value = DMA_IP_TRANSFER_SIZE_2_BYTE;
    }
    dmaTransferList[8].Param = DMA_IP_CH_SET_CONTROL_EN_MAJOR_INTERRUPT;
    dmaTransferList[8].Value = 1;
    dmaTransferList[9].Param = DMA_IP_CH_SET_CONTROL_DIS_AUTO_REQUEST;
    dmaTransferList[9].Value = 1;

    /* Configure the transfer control descriptor for the DMA channel */
    eDmaReturnStatus = Dma_Ip_SetLogicChannelTransferList(pUartUserCfg->u8RxDMAChannel, dmaTransferList, LINFLEXD_UART_DMA_CONFIG_LIST_DIMENSION);
    LINFLEXD_UART_DEV_ASSERT(eDmaReturnStatus == DMA_IP_STATUS_SUCCESS);

    /* Start the DMA channel */
    eDmaReturnStatus = Dma_Ip_SetLogicChannelCommand(pUartUserCfg->u8RxDMAChannel, DMA_IP_CH_SET_HARDWARE_REQUEST);

    LINFLEXD_UART_DEV_ASSERT(eDmaReturnStatus == DMA_IP_STATUS_SUCCESS);
    /* Flush the rx FIFO to discard any junk data received while the driver was idle */
    Linflexd_Uart_Ip_FlushRxFifo(pBase, pUartUserCfg->eWordLength);

    /* Enable the receiver */
    LINFLEXD_SetReceiverState(pBase, TRUE);

    /* Enable rx DMA requests for the current instance */
    LINFLEXD_SetDmaRxEnable(pBase, TRUE);

    return LINFLEXD_UART_IP_STATUS_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LINFLEXD_UART_DRV_CompleteSendDataUsingDma
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the DMA requests. This is a callback for DMA major loop
 * completion, so it must match the DMA callback signature.
 *
 *END**************************************************************************/
void Linflexd_Uart_Ip_CompleteSendUsingDma(uint32 u32Instance)
{
    LINFLEXD_Type * pBase;
    Linflexd_Uart_Ip_StateStructureType * pUartState;
    const Linflexd_Uart_Ip_UserConfigType *pUartUserCfg;
    Dma_Ip_LogicChannelTransferListType dmaTransferList[LINFLEXD_UART_DMA_LEAST_CONFIG_LIST_DIMENSION];
    Dma_Ip_ReturnType eDmaReturnStatus;

    pBase = Linflexd_Uart_Ip_apBases[u32Instance];
    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];
    pUartUserCfg = (Linflexd_Uart_Ip_UserConfigType*) Linflexd_Uart_Ip_apUserConfig[u32Instance];


    /* Invoke the callback when the buffer is finished;
     * Application can provide another buffer inside the callback by calling LINFLEXD_UART_DRV_SetTxBuffer */
    if (pUartState->eTransmitStatus == LINFLEXD_UART_IP_STATUS_BUSY)
    {
        if (pUartUserCfg->pfTxCallback != NULL_PTR)
        {
            /* Pass the state structure as parameter for internal information retrieval */
            pUartUserCfg->pfTxCallback(u32Instance, pUartState, LINFLEXD_UART_IP_EVENT_TX_EMPTY, pUartUserCfg->pTxCallbackParam);
        }
    }

    /* If the callback has updated the tx buffer, update the DMA descriptor to continue the transfer;
     * otherwise, stop the current transfer.
     */
    if (pUartState->u32TxSize > 0U)
    {
        /* Set up parameters for Dma_Ip_LogicChannelTransferListType */
        dmaTransferList[0].Param = DMA_IP_CH_SET_SOURCE_ADDRESS;
        dmaTransferList[1].Param = DMA_IP_CH_SET_MAJORLOOP_COUNT;
        /* Update tx size and major loop count parameters for Dma_Ip_LogicChannelTransferListType */
        dmaTransferList[0].Value = (uint32)(pUartState->pTxBuff);
        if(!((pUartUserCfg->eWordLength == LINFLEXD_UART_IP_7_BITS) || (pUartUserCfg->eWordLength == LINFLEXD_UART_IP_8_BITS)))
        {
            /* The size of the buffer should be an even number for DMA transfers with 15/16 bits word length */
            LINFLEXD_UART_DEV_ASSERT((pUartState->u32TxSize & 1U) == 0U);
        }
        if((pUartUserCfg->eWordLength == LINFLEXD_UART_IP_7_BITS) || (pUartUserCfg->eWordLength == LINFLEXD_UART_IP_8_BITS))
        {
            dmaTransferList[1].Value = pUartState->u32TxSize;
        }
        else
        {
            dmaTransferList[1].Value = (pUartState->u32TxSize)/2;
        }

        /* Re-configure the transfer control descriptor for the DMA channel */
        eDmaReturnStatus = Dma_Ip_SetLogicChannelTransferList(pUartUserCfg->u8TxDMAChannel, dmaTransferList, LINFLEXD_UART_DMA_LEAST_CONFIG_LIST_DIMENSION);
        LINFLEXD_UART_DEV_ASSERT(eDmaReturnStatus == DMA_IP_STATUS_SUCCESS);

        /* Now that this tx is set up, clear remaining bytes count */
        pUartState->u32TxSize = 0U;

        /* Re-start the channel */
        eDmaReturnStatus = Dma_Ip_SetLogicChannelCommand(pUartUserCfg->u8TxDMAChannel, DMA_IP_CH_SET_HARDWARE_REQUEST);
        LINFLEXD_UART_DEV_ASSERT(eDmaReturnStatus == DMA_IP_STATUS_SUCCESS);
    }
    else
    {
        /* Disable tx DMA requests for the current instance */
        LINFLEXD_SetDmaTxEnable(pBase, FALSE);

        /* Disable the transmitter */
        LINFLEXD_SetTransmitterState(pBase, FALSE);

        /* Call the callback to notify application that the transfer is complete */
        if (pUartUserCfg->pfTxCallback != NULL_PTR)
        {
            pUartUserCfg->pfTxCallback(u32Instance, pUartState, LINFLEXD_UART_IP_EVENT_END_TRANSFER, pUartUserCfg->pTxCallbackParam);
        }

        /* Update the busy flag */
        pUartState->bIsTxBusy = FALSE;

        /* If the current reception hasn't been aborted, update the status */
        if (pUartState->eTransmitStatus == LINFLEXD_UART_IP_STATUS_BUSY)
        {
            pUartState->eTransmitStatus = LINFLEXD_UART_IP_STATUS_SUCCESS;
        }
    }
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_CompleteReceiveUsingDma
 * Description   : Finish up a receive by completing the process of receiving data
 * and disabling the DMA requests. This is a callback for DMA major loop
 * completion, so it must match the DMA callback signature.
 *
 *END**************************************************************************/
void Linflexd_Uart_Ip_CompleteReceiveUsingDma(uint32 u32Instance)
{
    LINFLEXD_Type * pBase;
    Linflexd_Uart_Ip_StateStructureType * pUartState;
    const Linflexd_Uart_Ip_UserConfigType *pUartUserCfg;
    Dma_Ip_LogicChannelTransferListType dmaTransferList[LINFLEXD_UART_DMA_LEAST_CONFIG_LIST_DIMENSION];
    Dma_Ip_ReturnType eDmaReturnStatus;

    pBase = Linflexd_Uart_Ip_apBases[u32Instance];
    pUartState = (Linflexd_Uart_Ip_StateStructureType *)Linflexd_Uart_Ip_apStateStructuresArray[u32Instance];
    pUartUserCfg = (Linflexd_Uart_Ip_UserConfigType*) Linflexd_Uart_Ip_apUserConfig[u32Instance];

    /* Invoke the callback when the buffer is finished */
    if (pUartState->eReceiveStatus == LINFLEXD_UART_IP_STATUS_BUSY)
    {
        /* Application can provide another buffer inside the callback by calling LINFLEXD_UART_DRV_SetRxBuffer */
        if (pUartUserCfg->pfRxCallback != NULL_PTR)
        {
            pUartUserCfg->pfRxCallback(u32Instance, pUartState, LINFLEXD_UART_IP_EVENT_RX_FULL, pUartUserCfg->pRxCallbackParam);
        }
    }

    /* If the callback has updated the rx buffer, update the DMA descriptor to continue the transfer;
     * otherwise, stop the current transfer.
     */
    if (pUartState->u32RxSize > 0U)
    {
        /* Set up parameters for Dma_Ip_LogicChannelTransferListType */
        dmaTransferList[0].Param = DMA_IP_CH_SET_DESTINATION_ADDRESS;
        dmaTransferList[1].Param = DMA_IP_CH_SET_MAJORLOOP_COUNT;
        dmaTransferList[0].Value = (uint32)(pUartState->pRxBuff);
        if((pUartUserCfg->eWordLength == LINFLEXD_UART_IP_7_BITS) || (pUartUserCfg->eWordLength == LINFLEXD_UART_IP_8_BITS))
        {
            dmaTransferList[1].Value = pUartState->u32RxSize;
        }
        else
        {
            dmaTransferList[1].Value = (pUartState->u32RxSize)/2;
        }
        /* Re-configure the transfer control descriptor for the DMA channel */
        eDmaReturnStatus = Dma_Ip_SetLogicChannelTransferList(pUartUserCfg->u8RxDMAChannel, dmaTransferList, LINFLEXD_UART_DMA_LEAST_CONFIG_LIST_DIMENSION);
        LINFLEXD_UART_DEV_ASSERT(eDmaReturnStatus == DMA_IP_STATUS_SUCCESS);

        /* Now that this rx is set up, clear remaining bytes count */
        pUartState->u32RxSize = 0U;

        /* Re-start the channel */
        eDmaReturnStatus = Dma_Ip_SetLogicChannelCommand(pUartUserCfg->u8RxDMAChannel, DMA_IP_CH_SET_HARDWARE_REQUEST);
        LINFLEXD_UART_DEV_ASSERT(eDmaReturnStatus == DMA_IP_STATUS_SUCCESS);
    }
    else
    {
        /* Disable rx DMA requests for the current instance */
        LINFLEXD_SetDmaRxEnable(pBase, FALSE);

        /* Disable the receiver */
        LINFLEXD_SetReceiverState(pBase, FALSE);

        /* Update the information of the module driver state */
        pUartState->bIsRxBusy = FALSE;

        /* If the current reception hasn't been aborted, update the status and call the callback */
        if (pUartState->eReceiveStatus == LINFLEXD_UART_IP_STATUS_BUSY)
        {
            pUartState->eReceiveStatus = LINFLEXD_UART_IP_STATUS_SUCCESS;

            /* Call the callback to notify application that the transfer is complete */
            if (pUartUserCfg->pfRxCallback != NULL_PTR)
            {
                pUartUserCfg->pfRxCallback(u32Instance, pUartState, LINFLEXD_UART_IP_EVENT_END_TRANSFER, pUartUserCfg->pRxCallbackParam);
            }
        }
        /* Disable error interrupts */
        LINFLEXD_SetInterruptMode(pBase, LINFLEXD_FRAME_ERROR_INT, FALSE);
        LINFLEXD_SetInterruptMode(pBase, LINFLEXD_BUFFER_OVERRUN_INT, FALSE);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Linflexd_Uart_Ip_FlushRxFifo
 * Description   : Flushes the rx FIFO.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void Linflexd_Uart_Ip_FlushRxFifo(const LINFLEXD_Type *pBase, Linflexd_Uart_Ip_WordLengthType eWordLength)
{
    uint16 u16dummy;

    if((eWordLength == LINFLEXD_UART_IP_7_BITS) || (eWordLength == LINFLEXD_UART_IP_8_BITS))
    {
        volatile const uint8 *u8FifoBase;

        /* Get the address of the FIFO */
        u8FifoBase = (volatile const uint8 *)(&(pBase->BDRM));
#ifdef CORE_BIG_ENDIAN
        u8FifoBase = &u8FifoBase[3];
#endif

        /* Four dummy reads, to flush the FIFO contents */
        u16dummy = (uint16)(*u8FifoBase);
        u16dummy = (uint16)(*u8FifoBase);
        u16dummy = (uint16)(*u8FifoBase);
        u16dummy = (uint16)(*u8FifoBase);
        (void)u16dummy;
    }
    else
    {
        volatile const uint16 *u16FifoBase;

        /* Get the address of the FIFO */
        u16FifoBase = (volatile const uint16 *)(&(pBase->BDRM));
#ifdef CORE_BIG_ENDIAN
        u16FifoBase = &u16FifoBase[1];
#endif

        /* Four dummy reads, to flush the FIFO contents */
        u16dummy = *u16FifoBase;
        u16dummy = *u16FifoBase;
        u16dummy = *u16FifoBase;
        u16dummy = *u16FifoBase;
        (void)u16dummy;
    }
}
#endif


#if (STD_ON == LINFLEXD_SET_USER_ACCESS_ALLOWED_AVAILABLE)
/**
* @brief This function will set UAA bit in REG_PROT for UART unit
*/
static void Linflexd_Uart_Ip_SetUserAccess(uint32 u32Instance)
{
    LINFLEXD_Type * pBase;
    pBase = Linflexd_Uart_Ip_apBases[u32Instance];

    SET_USER_ACCESS_ALLOWED((uint32)pBase, LINFLEX_PROT_MEM_U32);
}

/**
* @brief This function will enable writing all UART registers under protection in User mode by configuring REG_PROT
*/
void Linflexd_Uart_Ip_SetUserAccessAllowed(uint32 u32Instance)
{
    OsIf_Trusted_Call1param(Linflexd_Uart_Ip_SetUserAccess, u32Instance);
}
#endif /* LINFLEXD_SET_USER_ACCESS_ALLOWED_AVAILABLE */

#define UART_STOP_SEC_CODE
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
