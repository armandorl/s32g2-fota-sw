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
*   @file Qspi_Ip.c
*
*   @addtogroup IPV_QSPI QSPI IPV Driver
*   @{
*/

/* implements Qspi_Ip.c_Artifact */

#ifdef __cplusplus
extern "C"{
#endif

#include "Qspi_Ip_Cfg.h"
#include "Qspi_Ip_Controller.h"
#include "Qspi_Ip_Common.h"
#include "Qspi_Ip.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define QSPI_IP_VENDOR_ID_C                    43
#define QSPI_IP_AR_RELEASE_MAJOR_VERSION_C     4
#define QSPI_IP_AR_RELEASE_MINOR_VERSION_C     4
#define QSPI_IP_AR_RELEASE_REVISION_VERSION_C  0
#define QSPI_IP_SW_MAJOR_VERSION_C             1
#define QSPI_IP_SW_MINOR_VERSION_C             0
#define QSPI_IP_SW_PATCH_VERSION_C             0
/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Qspi_Ip_Cfg header file are of the same vendor */
#if (QSPI_IP_VENDOR_ID_C != QSPI_IP_VENDOR_ID_CFG)
    #error "Qspi_Ip.c and Qspi_Ip_Cfg.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_Cfg header file are of the same Autosar version */
#if ((QSPI_IP_AR_RELEASE_MAJOR_VERSION_C    != QSPI_IP_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (QSPI_IP_AR_RELEASE_MINOR_VERSION_C    != QSPI_IP_AR_RELEASE_MINOR_VERSION_CFG) || \
     (QSPI_IP_AR_RELEASE_REVISION_VERSION_C != QSPI_IP_AR_RELEASE_REVISION_VERSION_CFG) \
    )
    #error "AutoSar Version Numbers of Qspi_Ip.c and Qspi_Ip_Cfg.h are different"
#endif
/* Check if current file and Qspi_Ip_Cfg header file are of the same Software version */
#if ((QSPI_IP_SW_MAJOR_VERSION_C != QSPI_IP_SW_MAJOR_VERSION_CFG) || \
     (QSPI_IP_SW_MINOR_VERSION_C != QSPI_IP_SW_MINOR_VERSION_CFG) || \
     (QSPI_IP_SW_PATCH_VERSION_C != QSPI_IP_SW_PATCH_VERSION_CFG) \
    )
    #error "Software Version Numbers of Qspi_Ip.c and Qspi_Ip_Cfg.h are different"
#endif

/* Check if current file and Qspi_Ip_Controller header file are of the same vendor */
#if (QSPI_IP_VENDOR_ID_C != QSPI_IP_CONTROLLER_VENDOR_ID_H)
    #error "Qspi_Ip.c and Qspi_Ip_Controller.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_Controller header file are of the same Autosar version */
#if ((QSPI_IP_AR_RELEASE_MAJOR_VERSION_C    != QSPI_IP_CONTROLLER_AR_RELEASE_MAJOR_VERSION_H) || \
     (QSPI_IP_AR_RELEASE_MINOR_VERSION_C    != QSPI_IP_CONTROLLER_AR_RELEASE_MINOR_VERSION_H) || \
     (QSPI_IP_AR_RELEASE_REVISION_VERSION_C != QSPI_IP_CONTROLLER_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Qspi_Ip.c and Qspi_Ip_Controller.h are different"
#endif
/* Check if current file and Qspi_Ip_Controller header file are of the same Software version */
#if ((QSPI_IP_SW_MAJOR_VERSION_C != QSPI_IP_CONTROLLER_SW_MAJOR_VERSION_H) || \
     (QSPI_IP_SW_MINOR_VERSION_C != QSPI_IP_CONTROLLER_SW_MINOR_VERSION_H) || \
     (QSPI_IP_SW_PATCH_VERSION_C != QSPI_IP_CONTROLLER_SW_PATCH_VERSION_H) \
    )
    #error "Software Version Numbers of Qspi_Ip.c and Qspi_Ip_Controller.h are different"
#endif

/* Check if current file and Qspi_Ip_Common header file are of the same vendor */
#if (QSPI_IP_VENDOR_ID_C != QSPI_IP_COMMON_VENDOR_ID_H)
    #error "Qspi_Ip.c and Qspi_Ip_Common.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_Common header file are of the same Autosar version */
#if ((QSPI_IP_AR_RELEASE_MAJOR_VERSION_C    != QSPI_IP_COMMON_AR_RELEASE_MAJOR_VERSION_H) || \
     (QSPI_IP_AR_RELEASE_MINOR_VERSION_C    != QSPI_IP_COMMON_AR_RELEASE_MINOR_VERSION_H) || \
     (QSPI_IP_AR_RELEASE_REVISION_VERSION_C != QSPI_IP_COMMON_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Qspi_Ip.c and Qspi_Ip_Common.h are different"
#endif
/* Check if current file and Qspi_Ip_Common header file are of the same Software version */
#if ((QSPI_IP_SW_MAJOR_VERSION_C != QSPI_IP_COMMON_SW_MAJOR_VERSION_H) || \
     (QSPI_IP_SW_MINOR_VERSION_C != QSPI_IP_COMMON_SW_MINOR_VERSION_H) || \
     (QSPI_IP_SW_PATCH_VERSION_C != QSPI_IP_COMMON_SW_PATCH_VERSION_H) \
    )
    #error "Software Version Numbers of Qspi_Ip.c and Qspi_Ip_Common.h are different"
#endif

/* Check if current file and Qspi_Ip header file are of the same vendor */
#if (QSPI_IP_VENDOR_ID_C != QSPI_IP_VENDOR_ID_H)
    #error "Qspi_Ip.c and Qspi_Ip.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip header file are of the same Autosar version */
#if ((QSPI_IP_AR_RELEASE_MAJOR_VERSION_C    != QSPI_IP_AR_RELEASE_MAJOR_VERSION_H) || \
     (QSPI_IP_AR_RELEASE_MINOR_VERSION_C    != QSPI_IP_AR_RELEASE_MINOR_VERSION_H) || \
     (QSPI_IP_AR_RELEASE_REVISION_VERSION_C != QSPI_IP_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Qspi_Ip.c and Qspi_Ip.h are different"
#endif
/* Check if current file and Qspi_Ip header file are of the same Software version */
#if ((QSPI_IP_SW_MAJOR_VERSION_C != QSPI_IP_SW_MAJOR_VERSION_H) || \
     (QSPI_IP_SW_MINOR_VERSION_C != QSPI_IP_SW_MINOR_VERSION_H) || \
     (QSPI_IP_SW_PATCH_VERSION_C != QSPI_IP_SW_PATCH_VERSION_H) \
    )
    #error "Software Version Numbers of Qspi_Ip.c and Qspi_Ip.h are different"
#endif
/*******************************************************************************
 * Variables
 ******************************************************************************/
#if (QSPI_IP_MEM_INSTANCE_COUNT > 0)

 /* Phisical LUT seq to use for all flash commands */
#define QSPI_IP_COMMAND_LUT 0U
 /* Phisical LUT seq to use for AHB reads */
#define QSPI_IP_AHB_LUT 1U

 /* Last command sent to the flash device */
#define QSPI_IP_LAST_COMMAND_NONE     0U
#define QSPI_IP_LAST_COMMAND_WRITE    1U
#define QSPI_IP_LAST_COMMAND_ERASE    2U

#define FLS_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Fls_MemMap.h"

/* Pointer to runtime state structures */
static Qspi_Ip_StateType Qspi_Ip_MemoryStateStructure[QSPI_IP_MEM_INSTANCE_COUNT];

#define FLS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Fls_MemMap.h"


/*******************************************************************************
 * Private Functions
 ******************************************************************************/

#define FLS_START_SEC_CODE
#include "Fls_MemMap.h"

static Qspi_Ip_StatusType Qspi_Ip_WriteEnable(uint32 instance);
static Qspi_Ip_StatusType Qspi_Ip_InitReset(uint32 instance, uint16 resetCmdLut, uint8 resetCmdCount, const Qspi_Ip_StateType * state);
static Qspi_Ip_StatusType Qspi_Ip_InitWriteReg(uint32 instance, const Qspi_Ip_InitOperationType * operation);
static Qspi_Ip_StatusType Qspi_Ip_InitRMWReg(uint32 instance, const Qspi_Ip_InitOperationType * operation);
static Qspi_Ip_StatusType Qspi_Ip_InitReadReg(uint32 instance, const Qspi_Ip_InitOperationType * operation);
static Qspi_Ip_StatusType Qspi_Ip_InitProtection(uint32 instance, const Qspi_Ip_StateType * state);

/*!
 * @brief Configures LUT commands
 *
 * This function configures a pair of LUT commands in the specified LUT register.
 * LUT sequences start at index multiple of 4 and can have up to 8 commands
 *
 * @param instance     QuadSPI peripheral instance number
 * @param instr0       First instruction
 * @param instr1       Second instruction
 * Implements      Qspi_Ip_SetLut_Activity
 */
static inline void Qspi_Ip_SetLut(uint32 instance,
                                   uint8 lut,
                                   Qspi_Ip_InstrOpType operation0,
                                   Qspi_Ip_InstrOpType operation1)
{
    QuadSPI_Type *baseAddr;

    baseAddr = Qspi_Ip_BaseAddress[instance];
    baseAddr->LUT[lut] = (uint32)operation0 + ((uint32)operation1 << 16U);
}


/*!
 * @brief Sets sequence ID for AHB operations
 *
 * @param instance     QuadSPI peripheral instance number
 * @param seqID        Sequence ID in LUT for read operation
 * Implements   Qspi_Ip_SetAhbSeqId_Activity
 */
static inline void Qspi_Ip_SetAhbSeqId(uint32 instance, 
                                        uint8 seqID)
{
    QuadSPI_Type *baseAddr;

    DEV_ASSERT_QSPI(instance < QuadSPI_INSTANCE_COUNT);
    baseAddr = Qspi_Ip_BaseAddress[instance];
    baseAddr->BFGENCR =  QuadSPI_BFGENCR_SEQID(seqID);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_InitLutSeq
 * Description   : Initializes one sequence in the LUT table from a virtual table sequence. Returns start index of next sequence.
* @implements      Qspi_Ip_InitLutSeq_Activity */
static uint16 Qspi_Ip_InitLutSeq(uint32 instance, uint16 virtualLutIdx, uint8 lutIndex)
{
    const Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);
    const Qspi_Ip_InstrOpType *virtualLutTable = state->configuration->lutSequences.lutOps;
    Qspi_Ip_InstrOpType operation1, operation2;
    uint16 vLutIdx = virtualLutIdx;         /* Index in virtual LUT  */
    uint8 lutIdx = 0U;                      /* Index in phisical LUT */

    do
    {
        DEV_ASSERT_QSPI(vLutIdx < state->configuration->lutSequences.opCount);
        operation1 = virtualLutTable[vLutIdx];
        vLutIdx++;
        operation2 = QSPI_IP_LUT_SEQ_END;
        if (operation1 != QSPI_IP_LUT_SEQ_END)
        {
            DEV_ASSERT_QSPI(vLutIdx < state->configuration->lutSequences.opCount);
            operation2 = virtualLutTable[vLutIdx];
            vLutIdx++;
        }
        /* Add two operations to lut sequence */
        DEV_ASSERT_QSPI(lutIdx < FEATURE_QSPI_LUT_SEQUENCE_SIZE);
        Qspi_Ip_SetLut(instance, (FEATURE_QSPI_LUT_SEQUENCE_SIZE * lutIndex) + lutIdx, operation1, operation2);
        lutIdx++;
    }
    while (operation2 != QSPI_IP_LUT_SEQ_END);

    return vLutIdx;
}



/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_SetValue
 * Description   : Converts a long value in data to be sent to flash
* @implements      Qspi_Ip_SetValue_Activity */
static inline void Qspi_Ip_SetValue(uint8 *data, uint8 size, uint32 value)
{
    uint8 cnt;
    uint32 temp = value;

    /* Put value in the data buffer */
    for (cnt = 0U; cnt < size; cnt++)
    {
        data[cnt] = (uint8)(temp & 0xFFU);
        temp >>= 8U;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_SetBitfield
 * Description   : Sets a new value in a register bitfield
* @implements      Qspi_Ip_SetBitfield_Activity */
static void Qspi_Ip_SetBitfield(uint8 *data, uint8 size, uint8 shift, uint8 width, uint32 value)
{
    uint8 cnt;
    uint32 longData = 0U;
    uint32 mask;

    /* Pack data in a long value */
    for (cnt = 0U; cnt < size; cnt++)
    {
        longData = (longData << 8U) + data[cnt];
    }
    /* Apply change */
    mask = ((1UL << (uint32)width) - 1UL) << (uint32)shift;
    longData &= ~mask;
    longData |= (value << shift) & mask;
    /* Put data back in the data buffer */
    for (cnt = 0U; cnt < size; cnt++)
    {
        data[cnt] = (uint8)(longData & 0xFFU);
        longData >>= 8U;
    }
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_GetBitfield
 * Description   : Extracts the value of a register bitfield
 * @implements     Qspi_Ip_GetBitfield_Activity */
static uint32 Qspi_Ip_GetBitfield(const uint8 *data, uint8 size, uint8 shift, uint8 width)
{
    uint8 cnt;
    uint32 longData = 0U;
    uint32 mask;
    uint32 value;

    /* Pack data in a long value */
    for (cnt = 0U; cnt < size; cnt++)
    {
        longData = (longData << 8U) + data[cnt];
    }
    /* Extract field */
    mask = (1UL << (uint32)width) - 1UL;
    value = (longData >> shift) & mask;
    return value;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_UpdateStatusReg
 * Description   : Updates a bitfield in the status register
* @implements      Qspi_Ip_UpdateStatusReg_Activity */
static Qspi_Ip_StatusType Qspi_Ip_UpdateStatusReg(uint32 instance, uint8 offset, uint8 width, uint8 value)
{
    const Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);
    const Qspi_Ip_StatusConfigType *statusConfig = &(state->configuration->statusConfig);
    uint8 data[4U];
    Qspi_Ip_StatusType status;

    /* Read status register */
    status = Qspi_Ip_RunReadCommand(instance, statusConfig->statusRegReadLut, 0U, data, NULL_PTR, statusConfig->regSize);

    if (status == STATUS_QSPI_IP_SUCCESS)
    {
        /* Check existing value, write status register only if needed */
        if (value != Qspi_Ip_GetBitfield(data, statusConfig->regSize, offset, width))
        {
            Qspi_Ip_SetBitfield(data, statusConfig->regSize, offset, width, value);
        }
        /* send WREN command for status register */
        if (statusConfig->writeEnableSRLut != QSPI_IP_LUT_INVALID)
        {
            status = Qspi_Ip_RunCommand(instance, statusConfig->writeEnableSRLut, 0U);
        }
        if (status == STATUS_QSPI_IP_SUCCESS)
        {
            /* send write status register command */
            status = Qspi_Ip_RunWriteCommand(instance, statusConfig->statusRegWriteLut, 0U, data, statusConfig->regSize);
        }
    }

    return status;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_CheckStatusReg
 * Description   : Checks a bitfield in the status register
* @implements      Qspi_Ip_CheckStatusReg_Activity */
static Qspi_Ip_StatusType Qspi_Ip_CheckStatusReg(uint32 instance, uint8 offset, uint8 width, uint8 *value)
{
    const Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);
    const Qspi_Ip_StatusConfigType *statusConfig = &(state->configuration->statusConfig);
    uint8 data[4];
    Qspi_Ip_StatusType status;

    /* Read status register */
    status = Qspi_Ip_RunReadCommand(instance, statusConfig->statusRegReadLut, 0U, data, NULL_PTR, statusConfig->regSize);
    if (status == STATUS_QSPI_IP_SUCCESS)
    {
        /* Extract bit-field */
        *value = (uint8)Qspi_Ip_GetBitfield(data, statusConfig->regSize, offset, width);
    }

    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_WriteEnable
 * Description   : Enables the serial flash memory for a program or erase operation
* @implements      Qspi_Ip_WriteEnable_Activity */
static Qspi_Ip_StatusType Qspi_Ip_WriteEnable(uint32 instance)
{
    const Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);
    const Qspi_Ip_StatusConfigType *statusConfig = &(state->configuration->statusConfig);

    uint32 retries = QSPI_IP_MAX_RETRY + 1U;
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_TIMEOUT;
    Qspi_Ip_StatusType cmdStatus;
    uint8 welValue = 0U;

    while (retries > 0U)
    {
        /* send WREN command */
        cmdStatus = Qspi_Ip_RunCommand(instance, statusConfig->writeEnableLut, 0U);
        if (cmdStatus != STATUS_QSPI_IP_SUCCESS)
        {
            status = cmdStatus;
        }
        /* check WEL bit */
        cmdStatus = Qspi_Ip_CheckStatusReg(instance, statusConfig->writeEnableOffset, 1U, &welValue);
        if (cmdStatus == STATUS_QSPI_IP_SUCCESS)
        {
            /* check WEL == 1 */
            if (welValue == 1U)
            {
                status = STATUS_QSPI_IP_SUCCESS;
                break;
            }
        }
        else
        {
            /* record error */
            status = cmdStatus;
        }
        retries--;
    }

    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_BasicErase
 * Description   : Perform one of the supported erase types in the serial flash. 
 * @implements      Qspi_Ip_BasicErase_Activity */
static Qspi_Ip_StatusType Qspi_Ip_BasicErase(uint32 instance, uint32 address, uint16 eraseLut)
{
    Qspi_Ip_StatusType status;

    /* enable write before erasing */
    status = Qspi_Ip_WriteEnable(instance);
    if (status == STATUS_QSPI_IP_SUCCESS)
    {
        /* launch erase command and return */
        status = Qspi_Ip_RunCommand(instance, eraseLut, address);
    }
    else
    {
        /* Empty clause added to fulfill MISRA. */
    }

    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_CheckCommandComplete
 * Description   : Wait until external memory is not busy
* @implements      Qspi_Ip_CheckCommandComplete_Activity */
static Qspi_Ip_StatusType Qspi_Ip_CheckCommandComplete(uint32 instance)
{
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_SUCCESS;
    uint32  u32ElapsedTicks = 0U;
    uint32  u32TimeoutTicks;
    uint32  u32CurrentTicks;

    /* Prepare timeout counter */
    u32TimeoutTicks = OsIf_MicrosToTicks(QSPI_IP_FLS_INIT_TIMEOUT, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    u32CurrentTicks = OsIf_GetCounter((OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    /* Wait for the command to complete */
    do
    {
        /* Get memory status */
        status = Qspi_Ip_GetMemoryStatus(instance);
        u32ElapsedTicks += OsIf_GetElapsed(&u32CurrentTicks, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
        /* Check timeout */
        if (u32ElapsedTicks >= u32TimeoutTicks)
        {
            status = STATUS_QSPI_IP_TIMEOUT;
            break;
        }
    }
    while (STATUS_QSPI_IP_BUSY == status);
    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_CheckResetComplete
 * Description   : Wait until external memory is available for operation after a reset
* @implements      Qspi_Ip_CheckResetComplete_Activity */
static void Qspi_Ip_CheckResetComplete(void)
{
    uint32  u32ElapsedTicks = 0U;
    uint32  u32TimeoutTicks;
    uint32  u32CurrentTicks;

    /* Prepare timeout counter */
    u32TimeoutTicks = OsIf_MicrosToTicks(QSPI_IP_RESET_TIMEOUT, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    u32CurrentTicks = OsIf_GetCounter((OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    /* Wait for the specified time */
    do
    {
        u32ElapsedTicks += OsIf_GetElapsed(&u32CurrentTicks, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    }
    while (u32ElapsedTicks < u32TimeoutTicks);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_InitWriteReg
 * Description   : Write the configured value into a register of external flash device
* @implements      Qspi_Ip_InitWriteReg_Activity */
static Qspi_Ip_StatusType Qspi_Ip_InitWriteReg(uint32 instance, const Qspi_Ip_InitOperationType * operation)
{
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_SUCCESS;
    uint8 value[4U];

    /* write a value in a register */
    if (QSPI_IP_LUT_INVALID != operation->weLut)
    {
        /* send WREN command */
        status = Qspi_Ip_RunCommand(instance, operation->weLut, operation->addr);
        if (STATUS_QSPI_IP_SUCCESS == status)
        {
            Qspi_Ip_SetValue(value, operation->size, operation->value);
            status = Qspi_Ip_RunWriteCommand(instance, operation->command1Lut, operation->addr, value, operation->size);
        }
    }

    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_InitRMWReg
 * Description   : Change a bitfield in a register of external flash device
* @implements      Qspi_Ip_InitRMWReg_Activity */
static Qspi_Ip_StatusType Qspi_Ip_InitRMWReg(uint32 instance, const Qspi_Ip_InitOperationType * operation)
{
    Qspi_Ip_StatusType status;
    uint32 fieldVal;
    uint8 value[4U];

    /* Read current register value */
    status = Qspi_Ip_RunReadCommand(instance, operation->command1Lut, operation->addr, value, NULL_PTR, operation->size);
    if (STATUS_QSPI_IP_SUCCESS == status)
    {
        /* Retrieve target bitfield */
        fieldVal = Qspi_Ip_GetBitfield(value, operation->size, operation->shift, operation->width);
        if (fieldVal != operation->value)
        {
            /* Modify target bitfield */
            Qspi_Ip_SetBitfield(value, operation->size, operation->shift, operation->width, operation->value);
            if (QSPI_IP_LUT_INVALID != operation->weLut)
            {
                /* Send WREN command */
                status = Qspi_Ip_RunCommand(instance, operation->weLut, operation->addr);
            }
            if (STATUS_QSPI_IP_SUCCESS == status)
            {
                /* Write back register value; use second LUT command */
                status = Qspi_Ip_RunWriteCommand(instance, operation->command2Lut, operation->addr, (uint8 *)&value, operation->size);
            }
        }
    }

    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_InitReadReg
 * Description   : Read the register's value of external flash device and loop until matching the configured one
* @implements      Qspi_Ip_InitReadReg_Activity */
static Qspi_Ip_StatusType Qspi_Ip_InitReadReg(uint32 instance, const Qspi_Ip_InitOperationType * operation)
{
    Qspi_Ip_StatusType status;
    uint32 fieldVal = 0U;
    uint8 value[4U];
    uint32 u32ElapsedTicks = 0U;
    uint32 u32TimeoutTicks;
    uint32 u32CurrentTicks;

    /* Prepare timeout counter */
    u32TimeoutTicks = OsIf_MicrosToTicks(QSPI_IP_FLS_INIT_TIMEOUT, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    u32CurrentTicks = OsIf_GetCounter((OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    do
    {
        /* read current register value */
        status = Qspi_Ip_RunReadCommand(instance, operation->command1Lut, operation->addr, value, NULL_PTR, operation->size);
        if (STATUS_QSPI_IP_SUCCESS == status)
        {
            /* retrieve target bitfield */
            fieldVal = Qspi_Ip_GetBitfield(value, operation->size, operation->shift, operation->width);
        }
        u32ElapsedTicks += OsIf_GetElapsed(&u32CurrentTicks, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
        if (u32ElapsedTicks >= u32TimeoutTicks)
        {
            status = STATUS_QSPI_IP_TIMEOUT;
            break;
        }
    }
    while (fieldVal != operation->value);

    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_InitDevice
 * Description   : Execute initialization sequence to get the serial flash memory in the target state for operation
* @implements      Qspi_Ip_InitDevice_Activity */
static Qspi_Ip_StatusType Qspi_Ip_InitDevice(uint32 instance, uint16 resetCmdLut, uint8 resetCmdCount, const Qspi_Ip_StateType * state)
{
    const Qspi_Ip_InitOperationType *initOperations;
    Qspi_Ip_StatusType status;
    uint8 initOpCount;
    uint8 initOp;

   /* Perform initial reset */
    status = Qspi_Ip_InitReset(instance, resetCmdLut, resetCmdCount, state);

    if (status == STATUS_QSPI_IP_SUCCESS)
    {
        /* Perform operations in initialization list */
        initOpCount = state->configuration->initConfiguration.opCount;
        if (initOpCount > 0U)
        {
            initOperations = state->configuration->initConfiguration.operations;
            for (initOp = 0; initOp < initOpCount; initOp++)
            {
                switch (initOperations[initOp].opType)
                {
                    case QSPI_IP_OP_TYPE_CMD:
                        /* Execute a simple command */
                        status = Qspi_Ip_RunCommand(instance, initOperations[initOp].command1Lut, initOperations[initOp].addr);
                        break;

                    case QSPI_IP_OP_TYPE_WRITE_REG:
                        /* Write value into the register */
                        status = Qspi_Ip_InitWriteReg(instance, &initOperations[initOp]);
                        break;

                    case QSPI_IP_OP_TYPE_RMW_REG:
                        /* Change a bitfield in the register */
                        status = Qspi_Ip_InitRMWReg(instance, &initOperations[initOp]);
                        break;

                    case QSPI_IP_OP_TYPE_READ_REG:
                        /* Check a bitfield in the register */
                        status = Qspi_Ip_InitReadReg(instance, &initOperations[initOp]);
                        break;

                    case QSPI_IP_OP_TYPE_QSPI_CFG:
                        /* Re-initialize QSPI controller with the given configuration */
                        (void)Qspi_Ip_ControllerDeinit(state->connection->qspiInstance);
                        status = Qspi_Ip_ControllerInit(state->connection->qspiInstance, initOperations[initOp].ctrlCfgPtr);
                        break;

                    default:
                        ; /* unknown operation */
                        break;
                }   /* switch */

                if (STATUS_QSPI_IP_SUCCESS != status)
                {
                    break;
                }
            }   /* for */
        }  /* if (initOpCount > 0U) */
    }   /* if (status == STATUS_QSPI_IP_SUCCESS) */

    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_InitProtection
 * Description   : Update the protection configuration value if needed
* @implements      Qspi_Ip_InitProtection_Activity */
static Qspi_Ip_StatusType Qspi_Ip_InitProtection(uint32 instance, const Qspi_Ip_StateType * state)
{
    Qspi_Ip_StatusType status;
    uint8 configProtection = state->configuration->statusConfig.blockProtectionValue;
    uint8 getProtection = 0U;

    /* Ensure the previous command is completed */
    status = Qspi_Ip_CheckCommandComplete(instance);
    if (STATUS_QSPI_IP_SUCCESS == status)
    {
        /* Read and check the current setting */
        status = Qspi_Ip_GetProtection(instance, &getProtection);
        if ((STATUS_QSPI_IP_SUCCESS == status) && (getProtection != configProtection))
        {
            /* Set new setting */
            status = Qspi_Ip_SetProtection(instance, configProtection);
            if (STATUS_QSPI_IP_SUCCESS == status)
            {
                /* Ensure the write is completed  */
                status = Qspi_Ip_CheckCommandComplete(instance);
            }
        }
    }

    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_InitReset
 * Description   : Perform the software reset sequence
* @implements      Qspi_Ip_InitReset_Activity */
static Qspi_Ip_StatusType Qspi_Ip_InitReset(uint32 instance, uint16 resetCmdLut, uint8 resetCmdCount, const Qspi_Ip_StateType * state)
{
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_SUCCESS;
    uint16 crtLut = resetCmdLut;
    uint8 cnt;

    if (QSPI_IP_LUT_INVALID != resetCmdLut)
    {
        for (cnt = 0U; cnt < resetCmdCount; cnt++)
        {
            /* Copy sequence in LUT registers */
            crtLut = Qspi_Ip_InitLutSeq(instance, crtLut, QSPI_IP_COMMAND_LUT);

            /* Run QSPI command */
            status = Qspi_Ip_IpCommand(state->connection->qspiInstance, QSPI_IP_COMMAND_LUT, state->baseAddress);
            if (status != STATUS_QSPI_IP_SUCCESS)
            {
                return status;
            }
        }
        /* Ensure flash is ready after reset */
        Qspi_Ip_CheckResetComplete();
    }

    return status;
}


/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_RunCommand
 * Description   : Launches a simple command for the serial flash
* @implements      Qspi_Ip_RunCommand_Activity */
Qspi_Ip_StatusType Qspi_Ip_RunCommand(uint32 instance,
                                       uint16 lut,
                                       uint32 addr)
{
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_SUCCESS;
    const Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);

    if (lut == QSPI_IP_LUT_INVALID)
    {
        status = STATUS_QSPI_IP_ERROR;
    }
    else
    {
        /* Copy sequence in LUT registers */
        (void)Qspi_Ip_InitLutSeq(instance, lut, QSPI_IP_COMMAND_LUT);

        /* Run QSPI command */
        status = Qspi_Ip_IpCommand(state->connection->qspiInstance, QSPI_IP_COMMAND_LUT, state->baseAddress + addr);
    }

    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_RunReadCommand
 * Description   : Launches a read command for the serial flash
* @implements      Qspi_Ip_RunReadCommand_Activity */
Qspi_Ip_StatusType Qspi_Ip_RunReadCommand(uint32 instance, 
                                           uint16 lut, 
                                           uint32 addr, 
                                           uint8 * dataRead,
                                           const uint8 * dataCmp,
                                           uint32 size)
{
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_SUCCESS;
    const Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);

    if (lut == QSPI_IP_LUT_INVALID)
    {
        status = STATUS_QSPI_IP_ERROR;
    }
    else
    {
        /* Copy sequence in LUT registers */
        (void)Qspi_Ip_InitLutSeq(instance, lut, QSPI_IP_COMMAND_LUT);

        /* Run QSPI command */
        status = Qspi_Ip_IpRead(state->connection->qspiInstance, QSPI_IP_COMMAND_LUT, state->baseAddress + addr, dataRead, dataCmp, size);
    }

    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_RunWriteCommand
 * Description   : Launches a write command for the serial flash
 * @implements     Qspi_Ip_RunWriteCommand_Activity */
Qspi_Ip_StatusType Qspi_Ip_RunWriteCommand(uint32 instance, 
                                            uint16 lut, 
                                            uint32 addr, 
                                            const uint8 * data, 
                                            uint32 size)
{
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_SUCCESS;
    const Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);

    if (lut == QSPI_IP_LUT_INVALID)
    {
        status = STATUS_QSPI_IP_ERROR;
    }
    else
    {
        /* Copy sequence in LUT registers */
        (void)Qspi_Ip_InitLutSeq(instance, lut, QSPI_IP_COMMAND_LUT);

        /* Run QSPI command */
        status = Qspi_Ip_IpWrite(state->connection->qspiInstance, QSPI_IP_COMMAND_LUT, state->baseAddress + addr, data, size);
    }

    return status;
}



/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_EraseBlock
 * Description   : Erase a sector in the serial flash. 
 *                 The size must match one of the device's erase types.
 * @implements     Qspi_Ip_EraseBlock_Activity */
Qspi_Ip_StatusType Qspi_Ip_EraseBlock(uint32 instance, uint32 address, uint32 size)
{
    Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_ERROR;
    uint8 eraseType;

    /* Check address range */
    if (address < state->configuration->memSize)
    {
        /* find the suited erase type */
        for (eraseType = 0U; eraseType < QSPI_IP_ERASE_TYPES; eraseType++)
        {
            if ((state->configuration->eraseSettings.eraseTypes[eraseType].eraseLut != QSPI_IP_LUT_INVALID) && 
                (size == (uint32)((uint32)1U << (state->configuration->eraseSettings.eraseTypes[eraseType].size))))
            {
                break;
            }
            else
            {
                /* Empty clause added to fulfill MISRA. */
            }
        }
        /* if erase type was found, launch the erase */
        if (eraseType < QSPI_IP_ERASE_TYPES)
        {
            status = Qspi_Ip_BasicErase(instance, address, state->configuration->eraseSettings.eraseTypes[eraseType].eraseLut);
            if (status == STATUS_QSPI_IP_SUCCESS)
            {
                state->lastCommand = QSPI_IP_LAST_COMMAND_ERASE;
            }
        }
        else
        {
            /* Empty clause added to fulfill MISRA. */
        }
    }
    else
    {
        /* Empty clause added to fulfill MISRA. */
    }
    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_EraseChip
 * Description   : Erase the entire serial flash
 * @implements     Qspi_Ip_EraseChip_Activity */
Qspi_Ip_StatusType Qspi_Ip_EraseChip(uint32 instance)
{
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_ERROR;
    const Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);

    if (state->configuration->eraseSettings.chipEraseLut != QSPI_IP_LUT_INVALID)
    {
        /* enable write before erasing */
        status = Qspi_Ip_WriteEnable(instance);
        if (status == STATUS_QSPI_IP_SUCCESS)
        {
            /* launch erase command */
            status = Qspi_Ip_RunCommand(instance, state->configuration->eraseSettings.chipEraseLut, 0U);
        }
        else
        {
            /* Empty clause added to fulfill MISRA. */
        }
    }
    else
    {
        /* Empty clause added to fulfill MISRA. */
    }
    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_ProgramSuspend
 * Description   : Suspends a program operation
 * @implements     Qspi_Ip_ProgramSuspend_Activity */
Qspi_Ip_StatusType Qspi_Ip_ProgramSuspend(uint32 instance)
{
    const Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);

    return Qspi_Ip_RunCommand(instance, state->configuration->suspendSettings.programSuspendLut, 0U);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_ProgramResume
 * Description   : Resumes a program operation
 * @implements     Qspi_Ip_ProgramResume_Activity */
Qspi_Ip_StatusType Qspi_Ip_ProgramResume(uint32 instance)
{
    const Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);

    return Qspi_Ip_RunCommand(instance, state->configuration->suspendSettings.programResumeLut, 0U);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_EraseSuspend
 * Description   : Suspends an erase operation
 * @implements     Qspi_Ip_EraseSuspend_Activity */
Qspi_Ip_StatusType Qspi_Ip_EraseSuspend(uint32 instance)
{
    const Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);

    return Qspi_Ip_RunCommand(instance, state->configuration->suspendSettings.eraseSuspendLut, 0U);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_EraseResume
 * Description   : Resumes an erase operation
 * @implements     Qspi_Ip_EraseResume_Activity */
Qspi_Ip_StatusType Qspi_Ip_EraseResume(uint32 instance)
{
    const Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);

    return Qspi_Ip_RunCommand(instance, state->configuration->suspendSettings.eraseResumeLut, 0U);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_Reset
 * Description   : Issues a software reset command
 * @implements     Qspi_Ip_Reset_Activity */
Qspi_Ip_StatusType Qspi_Ip_Reset(uint32 instance)
{
    uint16 resetCmdLut;        /*!< First command in reset sequence            */
    uint8 resetCmdCount;       /*!< Number of commands in reset sequence       */
    const Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_ERROR;

    resetCmdCount = state->configuration->resetSettings.resetCmdCount;
    if (resetCmdCount > 0U)
    {
        resetCmdLut = state->configuration->resetSettings.resetCmdLut;
        /* Execute reset and initial setup of external device */
        status = Qspi_Ip_InitDevice(instance, resetCmdLut, resetCmdCount, state);
    }

    /* If enabled, call the reset callout. */
    if (NULL_PTR != state->configuration->resetCallout)
    {
        status = state->configuration->resetCallout(instance);
    }

    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_GetMemoryStatus
 * Description   : Get the status of the last operation
 * @implements     Qspi_Ip_GetMemoryStatus_Activity */
Qspi_Ip_StatusType Qspi_Ip_GetMemoryStatus(uint32 instance)
{
    Qspi_Ip_StatusType status;
    uint8 busyValue;
    Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);
    const Qspi_Ip_StatusConfigType *statusConfig = &(state->configuration->statusConfig);

    /* Check if the QuadSPI command is complete */
    status = Qspi_Ip_ControllerGetStatus(state->connection->qspiInstance);
    if (status == STATUS_QSPI_IP_SUCCESS)
    {
        /* Check if the operation has finished in the serial flash */
        status = Qspi_Ip_CheckStatusReg(instance, statusConfig->busyOffset, 1U, &busyValue);
        if (status == STATUS_QSPI_IP_SUCCESS)
        {
            /* Check BUSY value */
            if (busyValue == statusConfig->busyValue)
            {
                /* Write/erase in progress */
                status = STATUS_QSPI_IP_BUSY;
            }
            else
            {
                /* Call user callout, if available, to check operation result */
                if ((state->lastCommand != QSPI_IP_LAST_COMMAND_NONE) && (NULL_PTR != state->configuration->errorCheckCallout))
                {
                    status = state->configuration->errorCheckCallout(instance);
                }
                state->lastCommand = QSPI_IP_LAST_COMMAND_NONE;
            }
        }
        else
        {
            /* Empty clause added to fulfill MISRA. */
        }
    }
    else
    {
        /* Empty clause added to fulfill MISRA. */
    }

    return status;
}



/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_Read
 * Description   : Read data from serial flash
 * @implements     Qspi_Ip_Read_Activity */
Qspi_Ip_StatusType Qspi_Ip_Read(uint32 instance, 
                                   uint32 address,
                                   uint8 * data,
                                   uint32 size)
{
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_SUCCESS;
    const Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);
    uint32 crtAddress = address;
    uint8 * crtData = data;
    uint32 crtSize = size;
    uint32 chunkSize = QSPI_IP_MAX_READ_SIZE;
    uint32  u32ElapsedTicks = 0U;
    uint32  u32TimeoutTicks;
    uint32  u32CurrentTicks;

    /* Prepare timeout counter */
    u32TimeoutTicks = OsIf_MicrosToTicks(QSPI_IP_READ_TIMEOUT, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    u32CurrentTicks = OsIf_GetCounter((OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    while ((crtSize > 0U) && (status == STATUS_QSPI_IP_SUCCESS))
    {
        if (chunkSize > crtSize)
        {
            /* Adjust size for last chunk */
            chunkSize = crtSize;
        }
        /* Check timeout */
        u32ElapsedTicks += OsIf_GetElapsed(&u32CurrentTicks, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
        if (u32ElapsedTicks >= u32TimeoutTicks)
        {
            status = STATUS_QSPI_IP_TIMEOUT;
            break;
        }
        status = Qspi_Ip_RunReadCommand(instance, state->activeReadLut, crtAddress, crtData, NULL_PTR, chunkSize);
        /* Move to next chunk */
        crtSize -= chunkSize;
        crtAddress += chunkSize;
        crtData = &(crtData[chunkSize]);
    }
    return status;
}



/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_ReadId
 * Description   : Read manufacturer ID from serial flash
 * @implements     Qspi_Ip_ReadId_Activity */
Qspi_Ip_StatusType Qspi_Ip_ReadId(uint32 instance, 
                                  uint8 * data)
{
    const Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);

    return Qspi_Ip_RunReadCommand(instance, 
                                  state->configuration->readIdSettings.readIdLut, 
                                  0U, 
                                  data, 
                                  NULL_PTR, 
                                  state->configuration->readIdSettings.readIdSize);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_ProgramVerify
 * Description   : Verifies data written in serial flash
 * @implements     Qspi_Ip_ProgramVerify_Activity */
Qspi_Ip_StatusType Qspi_Ip_ProgramVerify(uint32 instance, 
                                            uint32 address,
                                            const uint8 * data,
                                            uint32 size)
{
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_SUCCESS;
    const Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);
    uint32 crtAddress = address;
    const uint8 * crtData = data;
    uint32 crtSize = size;
    uint32 chunkSize = QSPI_IP_MAX_READ_SIZE;
    uint32  u32ElapsedTicks = 0U;
    uint32  u32TimeoutTicks;
    uint32  u32CurrentTicks;

    /* Prepare timeout counter */
    u32TimeoutTicks = OsIf_MicrosToTicks(QSPI_IP_READ_TIMEOUT, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    u32CurrentTicks = OsIf_GetCounter((OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    while ((crtSize > 0U) && (STATUS_QSPI_IP_SUCCESS == status))
    {
        if (chunkSize > crtSize)
        {
            /* Adjust size for last chunk */
            chunkSize = crtSize;
        }
        /* Check timeout */
        u32ElapsedTicks += OsIf_GetElapsed(&u32CurrentTicks, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
        if (u32ElapsedTicks >= u32TimeoutTicks)
        {
            status = STATUS_QSPI_IP_TIMEOUT;
            break;
        }
        status = Qspi_Ip_RunReadCommand(instance, state->activeReadLut, crtAddress, NULL_PTR, crtData, chunkSize);
        /* Move to next chunk */
        crtSize -= chunkSize;
        crtAddress += chunkSize;
        crtData = &(crtData[chunkSize]);
    }
    return status;
}



/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_EraseVerify
 * Description   : Verifies that an area in serial flash is in erased state
 * @implements     Qspi_Ip_EraseVerify_Activity */
Qspi_Ip_StatusType Qspi_Ip_EraseVerify(uint32 instance, 
                                          uint32 address,
                                          uint32 size)
{
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_SUCCESS;
    const Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);
    uint32 crtAddress = address;
    uint32 crtSize = size;
    uint32 chunkSize = QSPI_IP_MAX_READ_SIZE;
    uint32  u32ElapsedTicks = 0U;
    uint32  u32TimeoutTicks;
    uint32  u32CurrentTicks;

    /* Prepare timeout counter */
    u32TimeoutTicks = OsIf_MicrosToTicks(QSPI_IP_READ_TIMEOUT, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    u32CurrentTicks = OsIf_GetCounter((OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
    while ((crtSize > 0U) && (STATUS_QSPI_IP_SUCCESS == status))
    {
        if (chunkSize > crtSize)
        {
            /* Adjust size for last chunk */
            chunkSize = crtSize;
        }
        /* Check timeout */
        u32ElapsedTicks += OsIf_GetElapsed(&u32CurrentTicks, (OsIf_CounterType)QSPI_IP_TIMEOUT_TYPE);
        if (u32ElapsedTicks >= u32TimeoutTicks)
        {
            status = STATUS_QSPI_IP_TIMEOUT;
            break;
        }
        status = Qspi_Ip_RunReadCommand(instance, state->activeReadLut, crtAddress, NULL_PTR, NULL_PTR, chunkSize);
        /* Move to next chunk */
        crtSize -= chunkSize;
        crtAddress += chunkSize;
    }
    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_Program
 * Description   : Writes data in serial flash
 * @implements     Qspi_Ip_Program_Activity */
Qspi_Ip_StatusType Qspi_Ip_Program(uint32 instance,
                                      uint32 address,
                                      const uint8 * data,
                                      uint32 size)
{
    Qspi_Ip_StatusType status;
    Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);

    /* Check address range and page size */
    if ((address >= state->configuration->memSize) || ((size > state->configuration->pageSize)))
    {
        status = STATUS_QSPI_IP_ERROR;
    }
    else
    {
        /* enable write before programming */
        status = Qspi_Ip_WriteEnable(instance);
        if (status == STATUS_QSPI_IP_SUCCESS)
        {
            status = Qspi_Ip_RunWriteCommand(instance, state->configuration->writeLut, address, data, size);
            if (status == STATUS_QSPI_IP_SUCCESS)
            {
                state->lastCommand = QSPI_IP_LAST_COMMAND_WRITE;
            }
        }
        else
        {
            /* Empty clause added to fulfill MISRA. */
        }
    }
    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_Enter0XX
 * Description   : Enters 0-X-X mode (no command for read instructions)
 * @implements     Qspi_Ip_Enter0XX_Activity */
Qspi_Ip_StatusType Qspi_Ip_Enter0XX(uint32 instance)
{
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_ERROR;
    Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);
    uint8 dummyData;

    if (state->configuration->read0xxLut != QSPI_IP_LUT_INVALID)
    {
        state->activeReadLut = state->configuration->read0xxLut;
        /* Perform a dummy read to activate 0-X-X mode */
        status = Qspi_Ip_RunReadCommand(instance, state->activeReadLut, 0U, &dummyData, NULL_PTR, 1U);
    }
    else
    {
        /* Empty clause added to fulfill MISRA. */
    }
    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_Exit0XX
 * Description   : Exits 0-X-X mode (no command for read instructions)
 * @implements     Qspi_Ip_Exit0XX_Activity */
Qspi_Ip_StatusType Qspi_Ip_Exit0XX(uint32 instance)
{
    Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_ERROR;
    uint8 dummyData;

    if (state->configuration->read0xxLut != QSPI_IP_LUT_INVALID)
    {
        state->activeReadLut = state->configuration->readLut;
        /* Perform a dummy read to disable 0-X-X mode */
        status = Qspi_Ip_RunReadCommand(instance, state->activeReadLut, 0U, &dummyData, NULL_PTR, 1U);
    }
    else
    {
        /* Empty clause added to fulfill MISRA. */
    }

    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_SetProtection
 * Description   : Sets the protection bits of the device
 * @implements     Qspi_Ip_SetProtection_Activity */
Qspi_Ip_StatusType Qspi_Ip_SetProtection(uint32 instance, uint8 value)
{
    const Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);
    const Qspi_Ip_StatusConfigType *statusConfig = &(state->configuration->statusConfig);
   
    return Qspi_Ip_UpdateStatusReg(instance, statusConfig->blockProtectionOffset, statusConfig->blockProtectionWidth, value);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_GetProtection
 * Description   : Returns the current protection bits of the device
 * @implements     Qspi_Ip_GetProtection_Activity */
Qspi_Ip_StatusType Qspi_Ip_GetProtection(uint32 instance, uint8 *value)
{
    const Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);
    const Qspi_Ip_StatusConfigType *statusConfig = &(state->configuration->statusConfig);
   
    return Qspi_Ip_CheckStatusReg(instance, statusConfig->blockProtectionOffset, statusConfig->blockProtectionWidth, value);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_AhbReadEnable
 * Description   : Enables AHB reads for the current flash device
 * @implements     Qspi_Ip_AhbReadEnable_Activity */
Qspi_Ip_StatusType Qspi_Ip_AhbReadEnable(uint32 instance)
{
    const Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);
    Qspi_Ip_StatusType status = STATUS_QSPI_IP_ERROR;

    if (state->activeReadLut != QSPI_IP_LUT_INVALID)
    {
        /* Copy sequence in LUT registers */
        (void)Qspi_Ip_InitLutSeq(instance, state->activeReadLut, QSPI_IP_AHB_LUT);
        /* Set sequence number */
        Qspi_Ip_SetAhbSeqId(instance, QSPI_IP_AHB_LUT);
        status = STATUS_QSPI_IP_SUCCESS;
    }
    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_Init
 * Description   : Initialize the serial flash memory driver
 *
 * @implements     Qspi_Ip_Init_Activity */
Qspi_Ip_StatusType Qspi_Ip_Init(uint32 instance, const Qspi_Ip_MemoryConfigType * pConfig, const Qspi_Ip_MemoryConnectionType * pConnect)
{
    Qspi_Ip_StatusType status;
    Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);

    DEV_ASSERT_QSPI(instance < QuadSPI_INSTANCE_COUNT);
    /* Copy configuration information to state structure */
    DEV_ASSERT_QSPI(state->configuration == NULL_PTR);
    state->configuration = pConfig;
    state->connection = pConnect;
    state->activeReadLut = pConfig->readLut;    /* 0-X-X mode disabled by default */
    state->lastCommand = QSPI_IP_LAST_COMMAND_NONE;
    state->baseAddress = Qspi_Ip_GetBaseAdress(pConnect->qspiInstance, pConnect->connectionType);

    /* Execute initial setup of external device */
    status = Qspi_Ip_InitDevice(instance, pConfig->initResetSettings.resetCmdLut, pConfig->initResetSettings.resetCmdCount, state);

    /* If enabled, call the init callout, for additional QSPI IP or external memory settings. */
    if ((status == STATUS_QSPI_IP_SUCCESS) && (NULL_PTR != pConfig->initCallout))
    {
        status = pConfig->initCallout(instance);
    }

    /* Perform protection configuration */
    if (STATUS_QSPI_IP_SUCCESS == status)
    {
        status = Qspi_Ip_InitProtection(instance, state);
    }

    return status;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : Qspi_Ip_Deinit
 * Description   : De-initialize the serial flash memory driver
 * @implements     Qspi_Ip_Deinit_Activity */
Qspi_Ip_StatusType Qspi_Ip_Deinit(uint32 instance)
{
    Qspi_Ip_StateType * state = &(Qspi_Ip_MemoryStateStructure[instance]);

    DEV_ASSERT_QSPI(instance < QuadSPI_INSTANCE_COUNT);
    DEV_ASSERT_QSPI(state->configuration != NULL_PTR);
    state->configuration = NULL_PTR;
    return STATUS_QSPI_IP_SUCCESS;
}

#define FLS_STOP_SEC_CODE
#include "Fls_MemMap.h"

#endif /* (QSPI_IP_MEM_INSTANCE_COUNT > 0) */


#ifdef __cplusplus
}
#endif

/** @} */
