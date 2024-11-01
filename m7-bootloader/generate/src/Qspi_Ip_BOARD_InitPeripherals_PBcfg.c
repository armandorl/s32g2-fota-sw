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
*   @file Qspi_Ip_BOARD_InitPeripherals_PBcfg.c
*
*   @addtogroup FLS
*   @{
*/

/* implements Qspi_Ip_PBcfg.c_Artifact */

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Qspi_Ip_Types.h"
#include "Qspi_Ip_Features.h"
#include "Qspi_Ip_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FLS_QSPI_IP_VENDOR_ID_CFG_C                      43
#define FLS_QSPI_IP_AR_RELEASE_MAJOR_VERSION_CFG_C       4
#define FLS_QSPI_IP_AR_RELEASE_MINOR_VERSION_CFG_C       4
#define FLS_QSPI_IP_AR_RELEASE_REVISION_VERSION_CFG_C    0
#define FLS_QSPI_IP_SW_MAJOR_VERSION_CFG_C               1
#define FLS_QSPI_IP_SW_MINOR_VERSION_CFG_C               0
#define FLS_QSPI_IP_SW_PATCH_VERSION_CFG_C               0

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Qspi_Ip_Types header file are of the same vendor */
#if (FLS_QSPI_IP_VENDOR_ID_CFG_C != FLS_QSPI_TYPES_VENDOR_ID)
    #error "Qspi_Ip_PBcfg.c and Qspi_Ip_Types.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_Types header file are of the same Autosar version */
#if ((FLS_QSPI_IP_AR_RELEASE_MAJOR_VERSION_CFG_C    != FLS_QSPI_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (FLS_QSPI_IP_AR_RELEASE_MINOR_VERSION_CFG_C    != FLS_QSPI_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (FLS_QSPI_IP_AR_RELEASE_REVISION_VERSION_CFG_C != FLS_QSPI_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Qspi_Ip_PBcfg.c and Qspi_Ip_Types.h are different"
#endif
/* Check if current file and Qspi_Ip_Types header file are of the same Software version */
#if ((FLS_QSPI_IP_SW_MAJOR_VERSION_CFG_C != FLS_QSPI_TYPES_SW_MAJOR_VERSION) || \
     (FLS_QSPI_IP_SW_MINOR_VERSION_CFG_C != FLS_QSPI_TYPES_SW_MINOR_VERSION) || \
     (FLS_QSPI_IP_SW_PATCH_VERSION_CFG_C != FLS_QSPI_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Qspi_Ip_PBcfg.c and Qspi_Ip_Types.h are different"
#endif

/* Check if current file and Qspi_Ip_Features header file are of the same vendor */
#if (FLS_QSPI_IP_VENDOR_ID_CFG_C != QSPI_IP_FEATURES_VENDOR_ID_CFG)
    #error "Qspi_Ip_PBcfg.c and Qspi_Ip_Features.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_Features header file are of the same Autosar version */
#if ((FLS_QSPI_IP_AR_RELEASE_MAJOR_VERSION_CFG_C    != QSPI_IP_FEATURES_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (FLS_QSPI_IP_AR_RELEASE_MINOR_VERSION_CFG_C    != QSPI_IP_FEATURES_AR_RELEASE_MINOR_VERSION_CFG) || \
     (FLS_QSPI_IP_AR_RELEASE_REVISION_VERSION_CFG_C != QSPI_IP_FEATURES_AR_RELEASE_REVISION_VERSION_CFG) \
    )
    #error "AutoSar Version Numbers of Qspi_Ip_PBcfg.c and Qspi_Ip_Features.h are different"
#endif
/* Check if current file and Qspi_Ip_Features header file are of the same Software version */
#if ((FLS_QSPI_IP_SW_MAJOR_VERSION_CFG_C != QSPI_IP_FEATURES_SW_MAJOR_VERSION_CFG) || \
     (FLS_QSPI_IP_SW_MINOR_VERSION_CFG_C != QSPI_IP_FEATURES_SW_MINOR_VERSION_CFG) || \
     (FLS_QSPI_IP_SW_PATCH_VERSION_CFG_C != QSPI_IP_FEATURES_SW_PATCH_VERSION_CFG) \
    )
    #error "Software Version Numbers of Qspi_Ip_PBcfg.c and Qspi_Ip_Features.h are different"
#endif

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/



#define FLS_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Fls_MemMap.h"

/* External QSPI flash parameters. */
/* paFlashConnectionCfg */
const Qspi_Ip_MemoryConnectionType QspiConfigSet_BOARD_InitPeripherals_paFlashConnectionCfg[1U] =
{
    {
        0U,  /* qspiInstance */
        QSPI_IP_SIDE_A1  /* connectionType */
    }
};


/* paQspiUnitCfg */
const Qspi_Ip_ControllerConfigType QspiConfigSet_BOARD_InitPeripherals_paQspiUnitCfg[1U] =
{
    /* ControllerCfg_0 */
    {
        QSPI_IP_DATA_RATE_SDR,  /* dataRate */
        67108864U,  /* memSizeA1 */
        0U,  /* memSizeA2 */
        0U,  /* memSizeB1 */
        0U,  /* memSizeB2 */
        4U,  /* csHoldTime */
        4U,  /* csSetupTime */
        0U,  /* columnAddr */
        (boolean)FALSE,  /* wordAddresable */
        QSPI_IP_READ_MODE_LOOPBACK,  /* readModeA */
        QSPI_IP_READ_MODE_LOOPBACK,  /* readModeB */
        QSPI_IP_SAMPLE_DELAY_SAME_DQS,  /* sampleDelay */
        QSPI_IP_SAMPLE_PHASE_NON_INVERTED,  /* samplePhase */
        {
            /* (dllSettingsA) */
            QSPI_IP_DLL_BYPASSED,  /* dllMode */
            (boolean)FALSE,  /* freqEnable */
            1U,  /* referenceCounter */
            2U,  /* resolution */
            5U,  /* coarseDelay */
            15U,  /* fineDelay */
            4U   /* tapSelect */
        },
        {
            /* (dllSettingsB) */
            QSPI_IP_DLL_BYPASSED,  /* dllMode */
            (boolean)FALSE,  /* freqEnable */
            1U,  /* referenceCounter */
            2U,  /* resolution */
            0U,  /* coarseDelay */
            0U,  /* fineDelay */
            0U   /* tapSelect */
        },
        (boolean)FALSE,  /* centerAlignedStrobeA */
        (boolean)FALSE,  /* centerAlignedStrobeB */
        (boolean)FALSE,  /* differentialClockA */
        (boolean)FALSE,  /* differentialClockB */
        (boolean)FALSE,  /* dqsLatency */
        QSPI_IP_FLASH_DATA_ALIGN_REFCLK,  /* dataAlign */
        1U,  /* io2IdleValueA */
        1U,  /* io3IdleValueA */
        1U,  /* io2IdleValueB */
        1U,  /* io3IdleValueB */
        (boolean)FALSE,  /* byteSwap */
        {
            /* AHBConfig */
            {
                /* masters */
                0U,  /* buffer 0 master ID */
                1U,  /* buffer 1 master ID */
                2U,  /* buffer 2 master ID */
                3U  /* buffer 3 master ID */
            },
            {
                /* sizes */
                256U,  /* buffer 0 size */
                256U,  /* buffer 1 size */
                256U,  /* buffer 2 size */
                256U  /* buffer 3 size */
            },
            (boolean)TRUE  /* allMasters */
        }
    }
};


/* paInitOperations[] (MemCfg_0) */
static const Qspi_Ip_InitOperationType MemCfg_0_BOARD_InitPeripherals_paInitOperations_0[2U] =
{
    {
        QSPI_IP_OP_TYPE_RMW_REG,  /* opType */
        39U,  /* command1Lut */
        43U,  /* command2Lut */
        19U,  /* weLut */
        0U,  /* addr */
        1U,  /* size */
        0U,  /* shift */
        2U,  /* width */
        0U,  /* value */
        NULL_PTR  /* ctrlCfgPtr */
    },
    {
        QSPI_IP_OP_TYPE_READ_REG,  /* opType */
        39U,  /* command1Lut */
        QSPI_IP_LUT_INVALID,  /* command2Lut */
        QSPI_IP_LUT_INVALID,  /* weLut */
        0U,  /* addr */
        1U,  /* size */
        0U,  /* shift */
        2U,  /* width */
        0U,  /* value */
        NULL_PTR  /* ctrlCfgPtr */
    }
};


/* paLutOperations */
static const Qspi_Ip_InstrOpType MemCfg_0_BOARD_InitPeripherals_paLutOperations_0[47U] =
{
    /* 0: READ_SPI_MODE */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)3U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_ADDR | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)24U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_READ | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)128U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 1: WRITE_SPI_MODE */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)2U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_ADDR | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)24U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_WRITE | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)128U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 2: ERASE_SECTOR_SPI_MODE */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)32U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_ADDR | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)24U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 3: READ_SR_SPI_MODE */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)5U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_READ | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)2U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_STOP | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)0U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 4: WRITE_SR_SPI_MODE */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)1U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_WRITE | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)2U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_STOP | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)0U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 5: WRITE_ENABLE_SPI_MODE */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)6U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 6: RESET_ENABLE */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)102U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 7: RESET */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)153U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 8: FastRead */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)235U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_ADDR | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_4 | (Qspi_Ip_InstrOpType)24U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_MODE | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_4 | (Qspi_Ip_InstrOpType)0U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_DUMMY | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_4 | (Qspi_Ip_InstrOpType)4U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_READ | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_4 | (Qspi_Ip_InstrOpType)16U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 9: FastWrite */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)56U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_ADDR | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_4 | (Qspi_Ip_InstrOpType)24U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_WRITE | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_4 | (Qspi_Ip_InstrOpType)16U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)0U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 10: Read_Device_ID */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)159U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_READ | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)3U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 11: READ_CR2_SPI_MODE */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)113U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_ADDR | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)32U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_READ | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)1U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP),
    /* 12: WRITE_CR2_SPI_MODE */
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_CMD | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)114U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_ADDR | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)32U),
    (Qspi_Ip_InstrOpType)((Qspi_Ip_InstrOpType)QSPI_IP_LUT_INSTR_WRITE | (Qspi_Ip_InstrOpType)QSPI_IP_LUT_PADS_1 | (Qspi_Ip_InstrOpType)1U),
    (Qspi_Ip_InstrOpType)(QSPI_IP_LUT_INSTR_STOP)
};


/* paFlashCfg */
const Qspi_Ip_MemoryConfigType QspiConfigSet_BOARD_InitPeripherals_paFlashCfg[1U] =
{
    {
        /* MemCfg_0 */
        67108864U,  /* memSize */
        256U,  /* pageSize */
        0U,  /* readLut */
        4U,  /* writeLut */
        QSPI_IP_LUT_INVALID,  /* read0xxLut */
        QSPI_IP_LUT_INVALID,  /* read0xxLutAHB */
        /* readIdSettings */
        {
            36U,  /* readIdLut */
            3U,  /* readIdSize */
            3834306U  /* readIdExpected */
        },
        {
            /* eraseSettings */
            {
                {
                    /* eraseTypes[0] */
                    8U,  /* eraseLut */
                    12U  /* size */
                },
                {
                    /* eraseTypes[1] */
                    QSPI_IP_LUT_INVALID,  /* eraseLut */
                    1U  /* size */
                },
                {
                    /* eraseTypes[2] */
                    QSPI_IP_LUT_INVALID,  /* eraseLut */
                    1U  /* size */
                },
                {
                    /* eraseTypes[3] */
                    QSPI_IP_LUT_INVALID,  /* eraseLut */
                    1U  /* size */
                }
            },
            QSPI_IP_LUT_INVALID  /* chipEraseLut */
        },
        {
            /* statusConfig */
            11U,  /* statusRegReadLut */
            15U,  /* statusRegWriteLut */
            19U,  /* writeEnableSRLut */
            19U,  /* writeEnableLut */
            1U,  /* regSize */
            0U,  /* busyOffset */
            1U,  /* busyValue */
            1U,  /* writeEnableOffset */
            2U,  /* blockProtectionOffset */
            4U,  /* blockProtectionWidth */
            0U  /* blockProtectionValue */
        },
        {
            /* suspendSettings */
            QSPI_IP_LUT_INVALID,  /* eraseSuspendLut */
            QSPI_IP_LUT_INVALID,  /* eraseResumeLut */
            QSPI_IP_LUT_INVALID,  /* programSuspendLut */
            QSPI_IP_LUT_INVALID  /* programResumeLut */
        },
        {
            /* resetSettings */
            23U,  /* resetCmdLut */
            2U  /* resetCmdCount */
        },
        {
            /* initResetSettings */
            21U,  /* resetCmdLut */
            2U  /* resetCmdCount */
        },
        {
            /* initConfiguration */
            2U,  /* opCount */
            MemCfg_0_BOARD_InitPeripherals_paInitOperations_0  /* operations */
        },
        {
            /* lutSequences */
            47U,  /* opCount */
            MemCfg_0_BOARD_InitPeripherals_paLutOperations_0  /* lutOps */
        },
        NULL_PTR,  /* FlsQspiInitCallout */
        NULL_PTR,  /* FlsQspiResetCallout */
        NULL_PTR,  /* FlsQspiErrorCheckCallout */
    }
};

#define FLS_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "Fls_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @}*/

