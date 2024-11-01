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

/**
*   @file Qspi_Ip_Controller.c
*
*   @addtogroup IPV_QSPI QSPI IPV Driver
*   @{
*/

/* implements Qspi_Ip_Controller.c_Artifact */

#ifdef __cplusplus
extern "C"{
#endif


#include "Qspi_Ip_Cfg.h"
#include "Qspi_Ip_Controller.h"
#include "Qspi_Ip_HwAccess.h"
#include "Mcal.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define QSPI_IP_CONTROLLER_VENDOR_ID_C                       43
#define QSPI_IP_CONTROLLER_AR_RELEASE_MAJOR_VERSION_C        4
#define QSPI_IP_CONTROLLER_AR_RELEASE_MINOR_VERSION_C        4
#define QSPI_IP_CONTROLLER_AR_RELEASE_REVISION_VERSION_C     0
#define QSPI_IP_CONTROLLER_SW_MAJOR_VERSION_C                1
#define QSPI_IP_CONTROLLER_SW_MINOR_VERSION_C                0
#define QSPI_IP_CONTROLLER_SW_PATCH_VERSION_C                0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Qspi_Ip_Cfg header file are of the same vendor */
#if (QSPI_IP_CONTROLLER_VENDOR_ID_C != QSPI_IP_VENDOR_ID_CFG)
    #error "Qspi_Ip_Controller.c and Qspi_Ip_Cfg.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_Cfg header file are of the same Autosar version */
#if ((QSPI_IP_CONTROLLER_AR_RELEASE_MAJOR_VERSION_C    != QSPI_IP_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (QSPI_IP_CONTROLLER_AR_RELEASE_MINOR_VERSION_C    != QSPI_IP_AR_RELEASE_MINOR_VERSION_CFG) || \
     (QSPI_IP_CONTROLLER_AR_RELEASE_REVISION_VERSION_C != QSPI_IP_AR_RELEASE_REVISION_VERSION_CFG) \
    )
    #error "AutoSar Version Numbers of Qspi_Ip_Controller.c and Qspi_Ip_Cfg.h are different"
#endif
/* Check if current file and Qspi_Ip_Cfg header file are of the same Software version */
#if ((QSPI_IP_CONTROLLER_SW_MAJOR_VERSION_C != QSPI_IP_SW_MAJOR_VERSION_CFG) || \
     (QSPI_IP_CONTROLLER_SW_MINOR_VERSION_C != QSPI_IP_SW_MINOR_VERSION_CFG) || \
     (QSPI_IP_CONTROLLER_SW_PATCH_VERSION_C != QSPI_IP_SW_PATCH_VERSION_CFG) \
    )
    #error "Software Version Numbers of Qspi_Ip_Controller.c and Qspi_Ip_Cfg.h are different"
#endif

/* Check if current file and Qspi_Ip_Controller header file are of the same vendor */
#if (QSPI_IP_CONTROLLER_VENDOR_ID_C != QSPI_IP_CONTROLLER_VENDOR_ID_H)
    #error "Qspi_Ip_Controller.c and Qspi_Ip_Controller.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_Controller header file are of the same Autosar version */
#if ((QSPI_IP_CONTROLLER_AR_RELEASE_MAJOR_VERSION_C    != QSPI_IP_CONTROLLER_AR_RELEASE_MAJOR_VERSION_H) || \
     (QSPI_IP_CONTROLLER_AR_RELEASE_MINOR_VERSION_C    != QSPI_IP_CONTROLLER_AR_RELEASE_MINOR_VERSION_H) || \
     (QSPI_IP_CONTROLLER_AR_RELEASE_REVISION_VERSION_C != QSPI_IP_CONTROLLER_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Qspi_Ip_Controller.c and Qspi_Ip_Controller.h are different"
#endif
/* Check if current file and Qspi_Ip_Controller header file are of the same Software version */
#if ((QSPI_IP_CONTROLLER_SW_MAJOR_VERSION_C != QSPI_IP_CONTROLLER_SW_MAJOR_VERSION_H) || \
     (QSPI_IP_CONTROLLER_SW_MINOR_VERSION_C != QSPI_IP_CONTROLLER_SW_MINOR_VERSION_H) || \
     (QSPI_IP_CONTROLLER_SW_PATCH_VERSION_C != QSPI_IP_CONTROLLER_SW_PATCH_VERSION_H) \
    )
    #error "Software Version Numbers of Qspi_Ip_Controller.c and Qspi_Ip_Controller.h are different"
#endif

/* Check if current file and Qspi_Ip_HwAccess header file are of the same vendor */
#if (QSPI_IP_CONTROLLER_VENDOR_ID_C != QSPI_IP_HW_ACCESS_VENDOR_ID_H)
    #error "Qspi_Ip_Controller.c and Qspi_Ip_HwAccess.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_HwAccess header file are of the same Autosar version */
#if ((QSPI_IP_CONTROLLER_AR_RELEASE_MAJOR_VERSION_C    != QSPI_IP_HW_ACCESS_AR_RELEASE_MAJOR_VERSION_H) || \
     (QSPI_IP_CONTROLLER_AR_RELEASE_MINOR_VERSION_C    != QSPI_IP_HW_ACCESS_AR_RELEASE_MINOR_VERSION_H) || \
     (QSPI_IP_CONTROLLER_AR_RELEASE_REVISION_VERSION_C != QSPI_IP_HW_ACCESS_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Qspi_Ip_Controller.c and Qspi_Ip_HwAccess.h are different"
#endif
/* Check if current file and Qspi_Ip_HwAccess header file are of the same Software version */
#if ((QSPI_IP_CONTROLLER_SW_MAJOR_VERSION_C != QSPI_IP_HW_ACCESS_SW_MAJOR_VERSION_H) || \
     (QSPI_IP_CONTROLLER_SW_MINOR_VERSION_C != QSPI_IP_HW_ACCESS_SW_MINOR_VERSION_H) || \
     (QSPI_IP_CONTROLLER_SW_PATCH_VERSION_C != QSPI_IP_HW_ACCESS_SW_PATCH_VERSION_H) \
    )
    #error "Software Version Numbers of Qspi_Ip_Controller.c and Qspi_Ip_HwAccess.h are different"
#endif

#if (QSPI_IP_MEM_INSTANCE_COUNT > 0)

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @cond DRIVER_INTERNAL_USE_ONLY */

/* Mask of QuadSPI IP-related error flags */
#define QSPI_ERR_FLAGS_MASK    (QuadSPI_FR_TBUF_MASK | \
                                QuadSPI_FR_ILLINE_MASK | \
                                QuadSPI_FR_RBOF_MASK | \
                                QuadSPI_FR_IPAEF_MASK | \
                                QuadSPI_FR_IPIEF_MASK)


#define FLS_START_SEC_CONST_UNSPECIFIED
#include "Fls_MemMap.h"

/* Table of base addresses for QuadSPI instances. */
QuadSPI_Type * const Qspi_Ip_BaseAddress[QuadSPI_INSTANCE_COUNT] = QuadSPI_BASE_PTRS;
/* Table of AHB addresses for QuadSPI instances. */
const uint32 Qspi_Ip_AhbAddress[QuadSPI_INSTANCE_COUNT] = QuadSPI_AHB_PTRS;

#define FLS_STOP_SEC_CONST_UNSPECIFIED
#include "Fls_MemMap.h"


/*******************************************************************************
 * Private Functions
 ******************************************************************************/

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_ProcessDataRead
 * Description   : Processes read data
 * @implements     Qspi_Ip_ProcessDataRead_Activity */
static inline Qspi_Ip_StatusType Qspi_Ip_ProcessDataRead(uint8 * dataRead, uint32 size, const QuadSPI_Type *baseAddr)
{
    uint8 * data = dataRead;
    uint32 cnt = 0U;
    uint32 recvData;
    uint32 sizeRemaining;
    uint32 wordSize;
    uint8 byteCnt;

    sizeRemaining = size;
    /* Check user buffer alignment */
    if (((uint32)dataRead & 0x3U) == 0U)
    {
        /* Process 4 bytes at a time to speed up read */
        for (cnt = 0U; cnt < (sizeRemaining >> 2U); cnt++)
        {
            *((uint32 *)(data)) = baseAddr->RBDR[cnt];
            data = &(data[4U]);
        }
        sizeRemaining -= cnt * 4U;
    }
    /* Process remaining bytes one by one */
    while (sizeRemaining > 0U)
    {
        /* Get next received word */
        recvData = baseAddr->RBDR[cnt];
        /* get wordSize for the loop */
        wordSize = (sizeRemaining > 4U)?4U:sizeRemaining;
        for (byteCnt = 0U; byteCnt < wordSize; byteCnt++)
        {
#if (defined(CORE_BIG_ENDIAN))
            *data = (uint8)(recvData >> 24U);
            recvData <<= 8U;
#else
            *data = (uint8)(recvData & 0xFFU);
            recvData >>= 8U;
#endif
            data++;
            sizeRemaining--;
        }
        cnt++;
    }
    return STATUS_QSPI_IP_SUCCESS;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_ProcessDataVerify
 * Description   : Processes program verify data
 * @implements     Qspi_Ip_ProcessDataVerify_Activity */
static inline Qspi_Ip_StatusType Qspi_Ip_ProcessDataVerify(const uint8 * dataCmp, uint32 size, const QuadSPI_Type *baseAddr)
{
    const uint8 * roData = dataCmp;
    uint32 cnt = 0U;
    uint32 recvData;
    uint8 recvByte;
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_SUCCESS;
    uint32 byteCnt;
    uint32 wordSize;
    uint32 sizeRemaining;



    sizeRemaining = size;
    /* Check user buffer alignment */
    if (((uint32)dataCmp & 0x3U) == 0U)
    {
        for (cnt = 0U; cnt < (size >> 2U); cnt++)
        {
            /* Process 4 bytes at a time to speed up read */
            if (*((const uint32 *)(roData)) != baseAddr->RBDR[cnt])
            {
                /* return STATUS_QSPI_IP_ERROR_PROGRAM_VERIFY if the data is not match */
                status = STATUS_QSPI_IP_ERROR_PROGRAM_VERIFY;
                break;
            }
            /* update the roData */
            roData = &(roData[4U]);
        }
        /* update the sizeRemaining */
        sizeRemaining -= cnt * 4U;
    }
    /* Process remaining bytes one by one */
    while ((status == STATUS_QSPI_IP_SUCCESS) && (sizeRemaining > 0U))
    {
        /* Get next received word */
        recvData = baseAddr->RBDR[cnt];
        /* get wordSize for the loop */
        wordSize = (sizeRemaining > 4U)?4U:sizeRemaining;
        for (byteCnt = 0U; byteCnt < wordSize; byteCnt++)
        {
#if (defined(CORE_BIG_ENDIAN))
            recvByte = (uint8)(recvData >> 24U);
            recvData <<= 8U;
#else
            recvByte = (uint8)(recvData & 0xFFU);
            recvData >>= 8U;
#endif
            /* return STATUS_QSPI_IP_ERROR_PROGRAM_VERIFY if the data is not match */
            if (*roData != recvByte)
            {
                status = STATUS_QSPI_IP_ERROR_PROGRAM_VERIFY;
                break;
            }
            /* update the roData, sizeRemaining */
            roData++;
            sizeRemaining--;
        }
        cnt++;
    }
    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_ProcessDataBlankCheck
 * Description   : Processes blank check data
 * @implements     Qspi_Ip_ProcessDataBlankCheck_Activity */
static inline Qspi_Ip_StatusType Qspi_Ip_ProcessDataBlankCheck(uint32 size, const QuadSPI_Type *baseAddr)
{
    uint32 cnt = 0U;
    uint32 recvData = 0U;
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_SUCCESS;
    uint32 dataSize;

    /* Blank check */
    for (cnt = 0U; cnt < (size >> 2U); cnt++)
    {
        if (baseAddr->RBDR[cnt] != 0xFFFFFFFFU)
        {
            status = STATUS_QSPI_IP_ERROR;
            break;
        }
    }
    dataSize = size & 3U;
    if ((status == STATUS_QSPI_IP_SUCCESS) && (dataSize != 0U))
    {
        /* Process last few bytes */
        recvData = baseAddr->RBDR[size >> 2U];
#if (defined(CORE_BIG_ENDIAN))
        if ((~recvData & ~(((uint32)1U << (((uint32)4U - dataSize) * 8U)) - 1U)) != 0U)
#else
        if ((~recvData & (((uint32)1U << (dataSize * 8U)) - 1U)) != 0U)
#endif
        {
            status = STATUS_QSPI_IP_ERROR;
        }
    }
    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_FillTxBuf
 * Description   : Fill Tx buffer with the specified number of 4-byte entries
* @implements      Qspi_Ip_FillTxBuf_Activity */
static void Qspi_Ip_FillTxBuf(QuadSPI_Type *baseAddr, const uint8 * roData, uint32 size)
{
    uint32 sizeLeft = size;
    uint32 wordSize;
    uint32 data;
    uint8 byteCnt;
    const uint8 * roDataPtr = roData;

    /* Check user buffer alignment */
    if (((uint32)roData & 0x3U) == 0U)
    {
        /* Process 4 bytes at a time to speed things up */
        while (sizeLeft >= 4U)
        {
            data = *(const uint32 *)roDataPtr;
            sizeLeft -= 4U;
            roDataPtr = &(roDataPtr[4U]);
            Qspi_Ip_WriteTxData(baseAddr, data);
        }
    }
    /* Process remaining bytes one by one */
    while (sizeLeft > 0U)
    {
        /* Processes last few data bytes (less than 4) */
        data = 0U;
        wordSize = (sizeLeft > 4U)?4U:sizeLeft;
        for (byteCnt = 0U; byteCnt < wordSize; byteCnt++)
        {
#if (defined(CORE_BIG_ENDIAN))
            data += ((uint32)(*roDataPtr) << (8U * (3U - byteCnt)));
#else
            data += ((uint32)(*roDataPtr) << (8U * byteCnt));
#endif
            roDataPtr++;
        }
        Qspi_Ip_WriteTxData(baseAddr, data);
        sizeLeft -= wordSize;
    }

    return;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_ErrorCheck
 * Description   : Checks if there were errors during IP command execution
* @implements      Qspi_Ip_ErrorCheck_Activity */
static inline Qspi_Ip_StatusType Qspi_Ip_ErrorCheck(QuadSPI_Type *baseAddr)
{
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_SUCCESS;

    if ((baseAddr->FR & QSPI_ERR_FLAGS_MASK) != 0U)
    {
        /* clear error flags */
        baseAddr->FR = QSPI_ERR_FLAGS_MASK;
        status = STATUS_QSPI_IP_ERROR;
    }
    else
    {
        /* Empty clause added to fulfill MISRA. */
    }

    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_SwReset
 * Description   : Resets the QuadSPI device
* @implements      Qspi_Ip_SwReset_Activity */
static void Qspi_Ip_SwReset(QuadSPI_Type *baseAddr)
{
    /* Software reset AHB domain and Serial Flash domain at the same time. */
    Qspi_Ip_SwResetOn(baseAddr);
    /* Disable QuadSPI module before de-asserting the reset bits. */
    Qspi_Ip_Disable(baseAddr);
    /* De-asset Software reset AHB domain and Serial Flash domain bits. */
    Qspi_Ip_SwResetOff(baseAddr);
    /* Re-enable QuadSPI module after reset. */
    Qspi_Ip_Enable(baseAddr);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_ConfigureDLLA
 * Description   : Configures DLL - Side A
* @implements      Qspi_Ip_ConfigureDLLA_Activity */
static Qspi_Ip_StatusType Qspi_Ip_ConfigureDLLA(uint32 instance, QuadSPI_Type *baseAddr, const Qspi_Ip_ControllerConfigType * userConfigPtr)
{
#if (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1)
    uint32  u32ElapsedTicks = 0U;
    uint32  u32TimeoutTicks;
    uint32  u32CurrentTicks;
#endif

    (void)instance;
    /* Ensure DLL and slave chain update are off */
    Qspi_Ip_DLLSlaveUpdateA(baseAddr, FALSE);
#if (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1)
    Qspi_Ip_DLLEnableA(baseAddr, FALSE);
    /* Prepare timeout counter */
    u32TimeoutTicks = OsIf_MicrosToTicks(QSPI_IP_DLL_LOCK_TIMEOUT, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    u32CurrentTicks = OsIf_GetCounter((OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
#endif

    if (userConfigPtr->dllSettingsA.dllMode == QSPI_IP_DLL_BYPASSED)
    {
        /* Set DLL in bypass mode and configure coarse and fine delays */
        Qspi_Ip_DLLSlaveEnA(baseAddr, TRUE);
        Qspi_Ip_DLLSlaveBypassA(baseAddr, TRUE);
        Qspi_Ip_DLLSlaveAutoUpdateA(baseAddr, FALSE);
        Qspi_Ip_DLLSetCoarseDelayA(baseAddr, userConfigPtr->dllSettingsA.coarseDelay);
#ifdef QuadSPI_DLLCRA_SLV_DLY_FINE_MASK
        Qspi_Ip_DLLSetFineDelayA(baseAddr, userConfigPtr->dllSettingsA.fineDelay);
#endif  /* QuadSPI_DLLCRA_SLV_DLY_FINE_MASK */
        Qspi_Ip_DLLFreqEnA(baseAddr, userConfigPtr->dllSettingsA.freqEnable);
        /* Trigger slave chain update */
        Qspi_Ip_DLLSlaveUpdateA(baseAddr, TRUE);
#if (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1)
        /* Wait for slave delay chain update */
        while (!Qspi_Ip_DLLGetSlaveLockStatusA(baseAddr))
        {
            /* Check for errors reported by DLL */
            if (Qspi_Ip_DLLGetErrorStatusA(baseAddr))
            {
                return STATUS_QSPI_IP_ERROR;
            }
            /* Check for timeout */
            u32ElapsedTicks += OsIf_GetElapsed(&u32CurrentTicks, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
            if ( u32ElapsedTicks >= u32TimeoutTicks )
            {
                return STATUS_QSPI_IP_TIMEOUT;
            }
        }
        /* Disable slave chain update */
        Qspi_Ip_DLLSlaveUpdateA(baseAddr, FALSE);
#endif /* (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1) */
    }
#if (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1)
    else /* QSPI_DLL_MANUAL_UPDATE or QSPI_DLL_AUTO_UPDATE */
    {
        Qspi_Ip_DLLSlaveEnA(baseAddr, TRUE);
        Qspi_Ip_DLLSlaveBypassA(baseAddr, FALSE);
        Qspi_Ip_DLLSlaveAutoUpdateA(baseAddr, (userConfigPtr->dllSettingsA.dllMode == QSPI_IP_DLL_AUTO_UPDATE));
        Qspi_Ip_DLLSetReferenceCounterA(baseAddr, userConfigPtr->dllSettingsA.referenceCounter);
        Qspi_Ip_DLLSetResolutionA(baseAddr, userConfigPtr->dllSettingsA.resolution);
        Qspi_Ip_DLLSetCoarseOffsetA(baseAddr, userConfigPtr->dllSettingsA.coarseDelay);
        Qspi_Ip_DLLSetFineOffsetA(baseAddr, userConfigPtr->dllSettingsA.fineDelay);
        Qspi_Ip_DLLFreqEnA(baseAddr, userConfigPtr->dllSettingsA.freqEnable);
        if (userConfigPtr->dllSettingsA.dllMode == QSPI_IP_DLL_AUTO_UPDATE)
        {
            /* For auto update mode, trigger slave chain update */
            Qspi_Ip_DLLSlaveUpdateA(baseAddr, TRUE);
        }
        /* Enable DLL */
        Qspi_Ip_DLLEnableA(baseAddr, TRUE);

        if (userConfigPtr->dllSettingsA.dllMode == QSPI_IP_DLL_MANUAL_UPDATE)
        {
            /* For manual update mode, wait for DLL lock before triggering slave chain update */
            while (!Qspi_Ip_DLLGetLockStatusA(baseAddr))
            {
                /* Check for errors reported by DLL */
                if (Qspi_Ip_DLLGetErrorStatusA(baseAddr))
                {
                    return STATUS_QSPI_IP_ERROR;
                }
                /* Check for timeout */
                u32ElapsedTicks += OsIf_GetElapsed(&u32CurrentTicks, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
                if ( u32ElapsedTicks >= u32TimeoutTicks )
                {
                    return STATUS_QSPI_IP_TIMEOUT;
                }
            }
            Qspi_Ip_DLLSlaveUpdateA(baseAddr, TRUE);
        }
        /* Wait for slave delay chain update */
        while (!Qspi_Ip_DLLGetSlaveLockStatusA(baseAddr))
        {
            /* Check for errors reported by DLL */
            if (Qspi_Ip_DLLGetErrorStatusA(baseAddr))
            {
                return STATUS_QSPI_IP_ERROR;
            }
            /* Check for timeout */
            u32ElapsedTicks += OsIf_GetElapsed(&u32CurrentTicks, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
            if ( u32ElapsedTicks >= u32TimeoutTicks )
            {
                return STATUS_QSPI_IP_TIMEOUT;
            }
        }
        /* Disable slave chain update */
        Qspi_Ip_DLLSlaveUpdateA(baseAddr, FALSE);

    }
#endif /* (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1) */
    return STATUS_QSPI_IP_SUCCESS;
}

#if (FEATURE_QSPI_HAS_SIDE_B == 1)
/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_ConfigureDLLB
 * Description   : Configures DLL - Side B
* @implements      Qspi_Ip_ConfigureDLLB_Activity */
static Qspi_Ip_StatusType Qspi_Ip_ConfigureDLLB(uint32 instance, QuadSPI_Type *baseAddr, const Qspi_Ip_ControllerConfigType * userConfigPtr)
{
    uint32  u32ElapsedTicks = 0U;
    uint32  u32TimeoutTicks;
    uint32  u32CurrentTicks;

    (void)instance;
    /* Ensure DLL and slave chain update are off */
    Qspi_Ip_DLLSlaveUpdateB(baseAddr, FALSE);
#if (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1)
    Qspi_Ip_DLLEnableB(baseAddr, FALSE);
#endif
    /* Prepare timeout counter */
    u32TimeoutTicks = OsIf_MicrosToTicks(QSPI_IP_DLL_LOCK_TIMEOUT, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    u32CurrentTicks = OsIf_GetCounter((OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    if (userConfigPtr->dllSettingsB.dllMode == QSPI_IP_DLL_BYPASSED)
    {
        /* Set DLL in bypass mode and configure coarse and fine delays */
        Qspi_Ip_DLLSlaveEnB(baseAddr, TRUE);
        Qspi_Ip_DLLSlaveBypassB(baseAddr, TRUE);
        Qspi_Ip_DLLSlaveAutoUpdateB(baseAddr, FALSE);
        Qspi_Ip_DLLSetCoarseDelayB(baseAddr, userConfigPtr->dllSettingsB.coarseDelay);
#ifdef QuadSPI_DLLCRB_SLV_DLY_FINE_MASK
        Qspi_Ip_DLLSetFineDelayB(baseAddr, userConfigPtr->dllSettingsB.fineDelay);
#endif /* ifdef QuadSPI_DLLCRB_SLV_DLY_FINE_MASK */
        Qspi_Ip_DLLFreqEnB(baseAddr, userConfigPtr->dllSettingsB.freqEnable);
        /* Trigger slave chain update */
        Qspi_Ip_DLLSlaveUpdateB(baseAddr, TRUE);

#if (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1)
        /* Wait for slave delay chain update */
        while (!Qspi_Ip_DLLGetSlaveLockStatusB(baseAddr))
        {
            /* Check for errors reported by DLL */
            if (Qspi_Ip_DLLGetErrorStatusB(baseAddr))
            {
                return STATUS_QSPI_IP_ERROR;
            }
            /* Check for timeout */
            u32ElapsedTicks += OsIf_GetElapsed(&u32CurrentTicks, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
            if ( u32ElapsedTicks >= u32TimeoutTicks )
            {
                return STATUS_QSPI_IP_TIMEOUT;
            }
        }
        /* Disable slave chain update */
        Qspi_Ip_DLLSlaveUpdateB(baseAddr, FALSE);
#endif /* (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1) */
    }
#if (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1)
    else /* QSPI_DLL_MANUAL_UPDATE or QSPI_DLL_AUTO_UPDATE */
    {
        Qspi_Ip_DLLSlaveEnB(baseAddr, TRUE);
        Qspi_Ip_DLLSlaveBypassB(baseAddr, FALSE);
        Qspi_Ip_DLLSlaveAutoUpdateB(baseAddr, (userConfigPtr->dllSettingsB.dllMode == QSPI_IP_DLL_AUTO_UPDATE));
        Qspi_Ip_DLLSetReferenceCounterB(baseAddr, userConfigPtr->dllSettingsB.referenceCounter);
        Qspi_Ip_DLLSetResolutionB(baseAddr, userConfigPtr->dllSettingsB.resolution);
        Qspi_Ip_DLLSetCoarseOffsetB(baseAddr, userConfigPtr->dllSettingsB.coarseDelay);
        Qspi_Ip_DLLSetFineOffsetB(baseAddr, userConfigPtr->dllSettingsB.fineDelay);
        Qspi_Ip_DLLFreqEnB(baseAddr, userConfigPtr->dllSettingsB.freqEnable);
        if (userConfigPtr->dllSettingsB.dllMode == QSPI_IP_DLL_AUTO_UPDATE)
        {
            /* For auto update mode, trigger slave chain update */
            Qspi_Ip_DLLSlaveUpdateB(baseAddr, TRUE);
        }
        /* Enable DLL */
        Qspi_Ip_DLLEnableB(baseAddr, TRUE);

        if (userConfigPtr->dllSettingsB.dllMode == QSPI_IP_DLL_MANUAL_UPDATE)
        {
            /* For manual update mode, wait for DLL lock before triggering slave chain update */
            while (!Qspi_Ip_DLLGetLockStatusB(baseAddr))
            {
                /* Check for errors reported by DLL */
                if (Qspi_Ip_DLLGetErrorStatusB(baseAddr))
                {
                    return STATUS_QSPI_IP_ERROR;
                }
                /* Check for timeout */
                u32ElapsedTicks += OsIf_GetElapsed(&u32CurrentTicks, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
                if ( u32ElapsedTicks >= u32TimeoutTicks )
                {
                    return STATUS_QSPI_IP_TIMEOUT;
                }
            }
            Qspi_Ip_DLLSlaveUpdateB(baseAddr, TRUE);
        }
        /* Wait for slave delay chain update */
        while (!Qspi_Ip_DLLGetSlaveLockStatusB(baseAddr))
        {
            /* Check for errors reported by DLL */
            if (Qspi_Ip_DLLGetErrorStatusB(baseAddr))
            {
                return STATUS_QSPI_IP_ERROR;
            }
            /* Check for timeout */
            u32ElapsedTicks += OsIf_GetElapsed(&u32CurrentTicks, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
            if ( u32ElapsedTicks >= u32TimeoutTicks )
            {
                return STATUS_QSPI_IP_TIMEOUT;
            }
        }
        /* Disable slave chain update */
        Qspi_Ip_DLLSlaveUpdateB(baseAddr, FALSE);

    }
#endif /* (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1) */
    return STATUS_QSPI_IP_SUCCESS;
}
#endif  /* FEATURE_QSPI_HAS_SIDE_B == 1 */


#if defined(FEATURE_QSPI_CHIP_OPTIONS_S32K3)
/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_ConfigureChipOptions
 * Description   : Configures chip-specific settings, e.g. SOCCR
 ***********************************************************************/
static void Qspi_Ip_ConfigureChipOptions(QuadSPI_Type *baseAddr, const Qspi_Ip_ControllerConfigType * userConfigPtr)
{
    (void)userConfigPtr;
    baseAddr->SOCCR = 0x0000000E;   /* set ibe=1, obe=1, dse=1 and sre=0 */
}
#else
/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_ConfigureChipOptions
 * Description   : Configures chip-specific settings, e.g. SOCCR
 ***********************************************************************/
static void Qspi_Ip_ConfigureChipOptions(const QuadSPI_Type *baseAddr, const Qspi_Ip_ControllerConfigType * userConfigPtr)
{
    (void)userConfigPtr;
    (void)baseAddr;
}
#endif


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_ConfigureReadOptions
 * Description   : Configures data read settings
* @implements      Qspi_Ip_ConfigureReadOptions_Activity */
static void Qspi_Ip_ConfigureReadOptions(QuadSPI_Type *baseAddr, const Qspi_Ip_ControllerConfigType * userConfigPtr)
{
    /* Always enable DQS */
    QSPI_DQS_Enable(baseAddr);
#if (FEATURE_QSPI_DDR == 1)
    QSPI_DQS_LatEnable(baseAddr, userConfigPtr->dqsLatency);
    if (userConfigPtr->dataRate == QSPI_IP_DATA_RATE_SDR)
    {
        QSPI_DDR_Disable(baseAddr);
        /* Ignore output data align setting in SDR mode */
        Qspi_Ip_SetDataInHoldTime(baseAddr, QSPI_IP_FLASH_DATA_ALIGN_REFCLK);
    }
    else  /* QSPI_IP_DATA_RATE_DDR */
    {
        QSPI_DDR_Enable(baseAddr);
        Qspi_Ip_SetDataInHoldTime(baseAddr, userConfigPtr->dataAlign);
    }
#endif /* FEATURE_QSPI_DDR == 1 */
    /* select DQS source (internal/loopback/external) */
    Qspi_Ip_SetDQSSource(baseAddr, userConfigPtr->readModeA
#if (FEATURE_QSPI_HAS_SIDE_B == 1)
                        , userConfigPtr->readModeB
#endif
                        );
    
    /* Select DLL tap in SMPR register */
    Qspi_Ip_SetRxDLLTapA(baseAddr, userConfigPtr->dllSettingsA.tapSelect);
#if (FEATURE_QSPI_HAS_SIDE_B == 1)
    Qspi_Ip_SetRxDLLTapB(baseAddr, userConfigPtr->dllSettingsB.tapSelect);
#endif
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_AhbSetup
 * Description   : Sets up AHB accesses to the serial flash
* @implements      Qspi_Ip_AhbSetup_Activity */
static Qspi_Ip_StatusType Qspi_Ip_AhbSetup(uint32 instance, const Qspi_Ip_ControllerAhbConfigType *config)
{
    QuadSPI_Type *baseAddr;

    DEV_ASSERT_QSPI(instance < QuadSPI_INSTANCE_COUNT);
    DEV_ASSERT_QSPI((config->sizes[0U] & 7U) == 0U);
    DEV_ASSERT_QSPI(((uint32)config->sizes[0U] +
               (uint32)config->sizes[1U] +
               (uint32)config->sizes[2U] +
               (uint32)config->sizes[3U]) <= FEATURE_QSPI_AHB_BUF_SIZE);
    /* Get base address of instance */
    baseAddr = Qspi_Ip_BaseAddress[instance];

    /* configure AHB transfer sizes to match the buffer sizes */
    /* Set AHB buffer 0 */
    Qspi_Ip_SetAhbBuf0(baseAddr, config->sizes[0U], config->masters[0U]);
    /* Set AHB buffer 1 */
    Qspi_Ip_SetAhbBuf1(baseAddr, config->sizes[1U], config->masters[1U]);
    /* Set AHB buffer 2 */
    Qspi_Ip_SetAhbBuf2(baseAddr, config->sizes[2U], config->masters[2U]);
    /* Set AHB buffer 3 */
    Qspi_Ip_SetAhbBuf3(baseAddr, config->sizes[3U], config->masters[3U], config->allMasters);
    /* Set AHB buffer index 0 */
    Qspi_Ip_SetAhbBuf0Ind(baseAddr, (uint32)config->sizes[0U]);
    /* Set AHB buffer index 1 */
    Qspi_Ip_SetAhbBuf1Ind(baseAddr, (uint32)config->sizes[0U] + (uint32)config->sizes[1U]);
    /* Set AHB buffer index 2 */
    Qspi_Ip_SetAhbBuf2Ind(baseAddr, (uint32)config->sizes[0U] + (uint32)config->sizes[1U] + (uint32)config->sizes[2U]);

    return STATUS_QSPI_IP_SUCCESS;
}


/*! @endcond */

/*******************************************************************************
 * Code
 ******************************************************************************/


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_ControllerInit
 * Description   : Initializes the qspi controller
 * @implements     Qspi_Ip_ControllerInit_Activity */
Qspi_Ip_StatusType Qspi_Ip_ControllerInit(uint32 instance, const Qspi_Ip_ControllerConfigType * userConfigPtr)
{
    QuadSPI_Type *baseAddr;
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_SUCCESS;

    DEV_ASSERT_QSPI(instance < QuadSPI_INSTANCE_COUNT);
    /* Initialize driver status structure */

    baseAddr = Qspi_Ip_BaseAddress[instance];

    /* Ensure module is disabled */
    Qspi_Ip_Disable(baseAddr);

    /* Ensure all registers contain their reset value */
    Qspi_Ip_ResetAllRegisters(baseAddr);

    /* Apply configuration settings */
    Qspi_Ip_SetMemMap(instance, baseAddr, userConfigPtr->memSizeA1, userConfigPtr->memSizeA2
#if (FEATURE_QSPI_HAS_SIDE_B == 1)
                                , userConfigPtr->memSizeB1, userConfigPtr->memSizeB2
#endif  /* FEATURE_QSPI_HAS_SIDE_B */
                                );

#if (FEATURE_QSPI_ADDR_CFG == 1)
    Qspi_Ip_SetAddrOptions(baseAddr, userConfigPtr->columnAddr, userConfigPtr->wordAddresable);
#endif
    Qspi_Ip_SetRxCfg(baseAddr, userConfigPtr->sampleDelay, userConfigPtr->samplePhase);
    Qspi_Ip_SetCsHoldTime(baseAddr, userConfigPtr->csHoldTime);
    Qspi_Ip_SetCsSetupTime(baseAddr, userConfigPtr->csSetupTime);
#if (FEATURE_QSPI_CONFIGURABLE_ISD == 1)
    /* Unused side lines are "no matter" so just repeat idle settings on both sides */
    Qspi_Ip_SetIdleLineValues(baseAddr, userConfigPtr->io2IdleValueA, userConfigPtr->io3IdleValueA,
                                         userConfigPtr->io2IdleValueB, userConfigPtr->io3IdleValueB);
#endif
    /* Read Rx buffer through RBDR registers */
    Qspi_Ip_SetRxBufReadout(baseAddr, QSPI_IP_RX_READOUT_IP);
    /* Set watermarks */
    Qspi_Ip_SetTxWatermark(baseAddr, 1U);
    Qspi_Ip_SetRxWatermark(baseAddr, 1U);

#if (FEATURE_QSPI_CENTER_ALIGNED_READ_STROBE == 1)
    Qspi_Ip_SetCenterAlignedStrobeA(baseAddr, userConfigPtr->centerAlignedStrobeA);
#if (FEATURE_QSPI_HAS_SIDE_B == 1)
    Qspi_Ip_SetCenterAlignedStrobeB(baseAddr, userConfigPtr->centerAlignedStrobeB);
#endif
#endif
#if (FEATURE_QSPI_DIFFERENTIAL_CLOCK == 1)
    Qspi_Ip_SetDifferentialClockA(baseAddr, userConfigPtr->differentialClockA);
#if (FEATURE_QSPI_HAS_SIDE_B == 1)
    Qspi_Ip_SetDifferentialClockB(baseAddr, userConfigPtr->differentialClockB);
#endif
#endif
#if (FEATURE_QSPI_ADDR_CFG == 1)
    Qspi_Ip_SetByteSwap(baseAddr, userConfigPtr->byteSwap);
#endif

    /* Configure read options */
    Qspi_Ip_ConfigureReadOptions(baseAddr, userConfigPtr);
    /* Configure chip-specific options */
    Qspi_Ip_ConfigureChipOptions(baseAddr, userConfigPtr);
    /* Configure AHB settings */
    (void)Qspi_Ip_AhbSetup(instance, &(userConfigPtr->ahbConfig));
    /* Enable QuadSPI module */
    Qspi_Ip_Enable(baseAddr);

    /* Configure DLL */
    if ((userConfigPtr->memSizeA1 + userConfigPtr->memSizeA2) > 0U)
    {
        status = Qspi_Ip_ConfigureDLLA(instance, baseAddr, userConfigPtr);
    }
#if (FEATURE_QSPI_HAS_SIDE_B == 1)
    if ((userConfigPtr->memSizeB1 + userConfigPtr->memSizeB2) > 0U)
    {
        if (status == STATUS_QSPI_IP_SUCCESS)
        {
            status = Qspi_Ip_ConfigureDLLB(instance, baseAddr, userConfigPtr);
        }
    }
#endif

    if (status == STATUS_QSPI_IP_SUCCESS)
    {
        /* Reset serial flash and AHB domains */
        Qspi_Ip_SwReset(baseAddr);
    }

    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_ControllerDeinit
 * Description   : De-initialize the qspi driver
 * @implements     Qspi_Ip_ControllerDeinit_Activity */
Qspi_Ip_StatusType Qspi_Ip_ControllerDeinit(uint32 instance)
{
    QuadSPI_Type *baseAddr;

    DEV_ASSERT_QSPI(instance < QuadSPI_INSTANCE_COUNT);
    baseAddr = Qspi_Ip_BaseAddress[instance];

    /* Disable QuadSPI module */
    Qspi_Ip_Disable(baseAddr);

    return STATUS_QSPI_IP_SUCCESS;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_GetBaseAdress
 * Description   : Returns the physical base address of a flash device on the AHB bus.
 *                 The controller must be initialized prior to calling this function.
 * @implements     Qspi_Ip_GetBaseAdress_Activity */
uint32 Qspi_Ip_GetBaseAdress(uint32 instance, Qspi_Ip_ConnectionType connectionType)
{
    const QuadSPI_Type *baseAddr;
    uint32 address = 0U;

    DEV_ASSERT_QSPI(instance < QuadSPI_INSTANCE_COUNT);
    /* get the base address base on the instance */
    baseAddr = Qspi_Ip_BaseAddress[instance];

    switch (connectionType)
    {
        case QSPI_IP_SIDE_A1:
            /* get base address of side A1 */
            address = Qspi_Ip_AhbAddress[instance];
            break;
        case QSPI_IP_SIDE_A2:
            /* get base address of side A2 */
            address = baseAddr->SFA1AD;
            break;
#if (FEATURE_QSPI_HAS_SIDE_B == 1)
        case QSPI_IP_SIDE_B1:
            /* get base address of side B1 */
            address = baseAddr->SFA2AD;
            break;
        case QSPI_IP_SIDE_B2:
            /* get base address of side B2 */
            address = baseAddr->SFB1AD;
            break;
#endif
        default:
            ; /* Not possible */
            break;
    }

    return address;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_IpCommand
 * Description   : Launches a simple IP command
 * @implements     Qspi_Ip_IpCommand_Activity */
Qspi_Ip_StatusType Qspi_Ip_IpCommand(uint32 instance, uint8 lut, uint32 addr)
{
    QuadSPI_Type *baseAddr;
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_SUCCESS;
    uint32  u32ElapsedTicks = 0U;
    uint32  u32TimeoutTicks;
    uint32  u32CurrentTicks;

    DEV_ASSERT_QSPI(instance < QuadSPI_INSTANCE_COUNT);
    baseAddr = Qspi_Ip_BaseAddress[instance];
    /* Set address */
    Qspi_Ip_SetIpAddr(baseAddr, addr);
    /* Trigger IP command with specified sequence and dummy size */
    Qspi_Ip_IpTrigger(baseAddr, lut, 1U);
    /* Prepare timeout counter */
    u32TimeoutTicks = OsIf_MicrosToTicks(QSPI_IP_CMD_COMPLETE_TIMEOUT, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    u32CurrentTicks = OsIf_GetCounter((OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    do
    {
        u32ElapsedTicks += OsIf_GetElapsed(&u32CurrentTicks, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
        status = Qspi_Ip_ControllerGetStatus(instance);
    }
    while ((u32ElapsedTicks < u32TimeoutTicks) && (status == STATUS_QSPI_IP_BUSY));
    if (status == STATUS_QSPI_IP_BUSY)
    {
        status = STATUS_QSPI_IP_TIMEOUT;
    }
    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_IpRead
 * Description   : Launches an IP read command
 * @implements     Qspi_Ip_IpRead_Activity */
Qspi_Ip_StatusType Qspi_Ip_IpRead(uint32 instance,
                         uint8 lut,
                         uint32 addr,
                         uint8 * dataRead,
                         const uint8 * dataCmp,
                         uint32 size)
{
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_SUCCESS;
    QuadSPI_Type *baseAddr;
    uint32  u32ElapsedTicks = 0U;
    uint32  u32TimeoutTicks;
    uint32  u32CurrentTicks;

    DEV_ASSERT_QSPI(instance < QuadSPI_INSTANCE_COUNT);
    baseAddr = Qspi_Ip_BaseAddress[instance];

    /* Make sure there is no garbage in Rx fifo */
    Qspi_Ip_ClearRxBuf(baseAddr);
    /* Set read address */
    Qspi_Ip_SetIpAddr(baseAddr, addr);
    /* Trigger IP command with specified sequence and size */
    Qspi_Ip_IpTrigger(baseAddr, lut, (uint16)size);
    /* Prepare timeout counter */
    u32TimeoutTicks = OsIf_MicrosToTicks(QSPI_IP_CMD_COMPLETE_TIMEOUT, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    u32CurrentTicks = OsIf_GetCounter((OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    /* Wait for command to be completed */
    while (Qspi_Ip_GetBusyStatus(baseAddr))
    {
        u32ElapsedTicks += OsIf_GetElapsed(&u32CurrentTicks, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
        if (u32ElapsedTicks >= u32TimeoutTicks)
        {
            status = STATUS_QSPI_IP_TIMEOUT;
            break;
        }
    }
    if (status == STATUS_QSPI_IP_SUCCESS)
    {
        /* Check for errors reported by the QuadSPI */
        status = Qspi_Ip_ErrorCheck(baseAddr);
    }
    if (status == STATUS_QSPI_IP_SUCCESS)
    {
        /* Process received data */
        if (dataRead != NULL_PTR)
        {
            /* Normal read */
            status = Qspi_Ip_ProcessDataRead(dataRead, size, baseAddr);
        }
        else if (dataCmp != NULL_PTR)
        {
            /* Verify */
            status = Qspi_Ip_ProcessDataVerify(dataCmp, size, baseAddr);
        }
        else
        {
            /* Blank check */
            status = Qspi_Ip_ProcessDataBlankCheck(size, baseAddr);
        }
    }   /* (status = STATUS_QSPI_IP_SUCCESS) */

    /* Reset Rx fifo */
    Qspi_Ip_ClearRxBuf(baseAddr);

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_InvalidateTxBuf
 * Description   : Invalidates the TX buffer content and wait until it is completed or timed out
 * @implements     Qspi_Ip_InvalidateTxBuf_Activity */
static inline Qspi_Ip_StatusType Qspi_Ip_InvalidateTxBuf(uint32 instance)
{
    QuadSPI_Type *baseAddr;
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_SUCCESS;
    uint32  u32ElapsedTicks = 0U;
    uint32  u32TimeoutTicks;
    uint32  u32CurrentTicks;

    baseAddr = Qspi_Ip_BaseAddress[instance];

    Qspi_Ip_ClearTxBuf(baseAddr);

    /* Prepare timeout counter */
    u32TimeoutTicks = OsIf_MicrosToTicks(QSPI_IP_CMD_COMPLETE_TIMEOUT, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    u32CurrentTicks = OsIf_GetCounter((OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    /* Wait for the CLR_TXF clears itself */
    while (!Qspi_Ip_GetClrTxStatus(baseAddr))
    {
        u32ElapsedTicks += OsIf_GetElapsed(&u32CurrentTicks, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
        if (u32ElapsedTicks >= u32TimeoutTicks)
        {
            status = STATUS_QSPI_IP_TIMEOUT;
            break;
        }
    }

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_IpWrite
 * Description   : Launches an IP write command
 * @implements     Qspi_Ip_IpWrite_Activity */
Qspi_Ip_StatusType Qspi_Ip_IpWrite(uint32 instance,
                          uint8 lut,
                          uint32 addr,
                          const uint8 * data,
                          uint32 size)
{
    QuadSPI_Type *baseAddr;
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_SUCCESS;
    Qspi_Ip_StatusType errors = STATUS_QSPI_IP_SUCCESS;
    uint32  u32ElapsedTicks = 0U;
    uint32  u32TimeoutTicks;
    uint32  u32CurrentTicks;

    baseAddr = Qspi_Ip_BaseAddress[instance];
    DEV_ASSERT_QSPI(instance < QuadSPI_INSTANCE_COUNT);
    DEV_ASSERT_QSPI(size <= (uint16)FEATURE_QSPI_TX_BUF_SIZE);
    /* Reset AHB buffers to force re-read from memory after write operation */
    Qspi_Ip_SwReset(baseAddr);

    /* Set write address */
    Qspi_Ip_SetIpAddr(baseAddr, addr);

    /* Ensure there is no garbage in Tx FIFO */
    status = Qspi_Ip_InvalidateTxBuf(instance);
    if (STATUS_QSPI_IP_SUCCESS != status)
    {
        return status;
    }

    /* Fill Tx buffer */
    Qspi_Ip_FillTxBuf(baseAddr, data, size);

    /* Trigger IP command with specified sequence and size */
    Qspi_Ip_IpTrigger(baseAddr, lut, (uint16)size);

    /* Add Fault Injection point for FR_TBUF flag */
    MCAL_FAULT_INJECTION_POINT(FLS_FIP_FR_ERROR_IPWRITE);

    /* Prepare timeout counter */
    u32TimeoutTicks = OsIf_MicrosToTicks(QSPI_IP_CMD_COMPLETE_TIMEOUT, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    u32CurrentTicks = OsIf_GetCounter((OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    /* Wait for command to be completed */
    while (Qspi_Ip_GetBusyStatus(baseAddr))
    {
        u32ElapsedTicks += OsIf_GetElapsed(&u32CurrentTicks, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
        if (u32ElapsedTicks >= u32TimeoutTicks)
        {
            status = STATUS_QSPI_IP_TIMEOUT;
            break;
        }
    }
    /* Check for errors reported by the QuadSPI */
    errors = Qspi_Ip_ErrorCheck(baseAddr);
    if (status == STATUS_QSPI_IP_SUCCESS)
    {
        status = errors;
    }

    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_ControllerGetStatus
 * Description   : Checks the status of the currently running IP command
 * @implements     Qspi_Ip_ControllerGetStatus_Activity */
Qspi_Ip_StatusType Qspi_Ip_ControllerGetStatus(uint32 instance)
{
    QuadSPI_Type *baseAddr;
    Qspi_Ip_StatusType status;

    DEV_ASSERT_QSPI((instance < QuadSPI_INSTANCE_COUNT));
    baseAddr = Qspi_Ip_BaseAddress[instance];

    /* Check device for busy status */
    if (Qspi_Ip_GetBusyStatus(baseAddr))
    {
        status = STATUS_QSPI_IP_BUSY;
    }
    else
    {
        /* Check for errors reported by the QuadSPI */
        status = Qspi_Ip_ErrorCheck(baseAddr);
    }
    return status;
}

#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

#endif /* (QSPI_IP_MEM_INSTANCE_COUNT > 0) */


#ifdef __cplusplus
}
#endif

/** @} */
