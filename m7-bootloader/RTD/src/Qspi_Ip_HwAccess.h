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

#ifndef QUADSPI_HW_ACCESS_H
#define QUADSPI_HW_ACCESS_H

/**
*   @file Qspi_Ip_HwAccess.h
*
*   @addtogroup IPV_QSPI QSPI IPV Driver
*   @{
*/

/* implements Qspi_Ip_HwAccess.h_Artifact */

#ifdef __cplusplus
extern "C"{
#endif


#include "Qspi_Ip.h"
#include "Qspi_Ip_Common.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define QSPI_IP_HW_ACCESS_VENDOR_ID_H                       43
#define QSPI_IP_HW_ACCESS_AR_RELEASE_MAJOR_VERSION_H        4
#define QSPI_IP_HW_ACCESS_AR_RELEASE_MINOR_VERSION_H        4
#define QSPI_IP_HW_ACCESS_AR_RELEASE_REVISION_VERSION_H     0
#define QSPI_IP_HW_ACCESS_SW_MAJOR_VERSION_H                1
#define QSPI_IP_HW_ACCESS_SW_MINOR_VERSION_H                0
#define QSPI_IP_HW_ACCESS_SW_PATCH_VERSION_H                0
/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Qspi_Ip header file are of the same vendor */
#if (QSPI_IP_HW_ACCESS_VENDOR_ID_H != QSPI_IP_VENDOR_ID_H)
    #error "Qspi_Ip_HwAccess.h and Qspi_Ip.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip header file are of the same Autosar version */
#if ((QSPI_IP_HW_ACCESS_AR_RELEASE_MAJOR_VERSION_H    != QSPI_IP_AR_RELEASE_MAJOR_VERSION_H) || \
     (QSPI_IP_HW_ACCESS_AR_RELEASE_MINOR_VERSION_H    != QSPI_IP_AR_RELEASE_MINOR_VERSION_H) || \
     (QSPI_IP_HW_ACCESS_AR_RELEASE_REVISION_VERSION_H != QSPI_IP_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Qspi_Ip_HwAccess.h and Qspi_Ip.h are different"
#endif
/* Check if current file and Qspi_Ip header file are of the same Software version */
#if ((QSPI_IP_HW_ACCESS_SW_MAJOR_VERSION_H != QSPI_IP_SW_MAJOR_VERSION_H) || \
     (QSPI_IP_HW_ACCESS_SW_MINOR_VERSION_H != QSPI_IP_SW_MINOR_VERSION_H) || \
     (QSPI_IP_HW_ACCESS_SW_PATCH_VERSION_H != QSPI_IP_SW_PATCH_VERSION_H) \
    )
    #error "Software Version Numbers of Qspi_Ip_HwAccess.h and Qspi_Ip.h are different"
#endif

/* Check if current file and Qspi_Ip_Common header file are of the same vendor */
#if (QSPI_IP_HW_ACCESS_VENDOR_ID_H != QSPI_IP_COMMON_VENDOR_ID_H)
    #error "Qspi_Ip_HwAccess.h and Qspi_Ip_Common.h have different vendor ids"
#endif
/* Check if current file and Qspi_Ip_Common header file are of the same Autosar version */
#if ((QSPI_IP_HW_ACCESS_AR_RELEASE_MAJOR_VERSION_H    != QSPI_IP_COMMON_AR_RELEASE_MAJOR_VERSION_H) || \
     (QSPI_IP_HW_ACCESS_AR_RELEASE_MINOR_VERSION_H    != QSPI_IP_COMMON_AR_RELEASE_MINOR_VERSION_H) || \
     (QSPI_IP_HW_ACCESS_AR_RELEASE_REVISION_VERSION_H != QSPI_IP_COMMON_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Qspi_Ip_HwAccess.h and Qspi_Ip_Common.h are different"
#endif
/* Check if current file and Qspi_Ip_Common header file are of the same Software version */
#if ((QSPI_IP_HW_ACCESS_SW_MAJOR_VERSION_H != QSPI_IP_COMMON_SW_MAJOR_VERSION_H) || \
     (QSPI_IP_HW_ACCESS_SW_MINOR_VERSION_H != QSPI_IP_COMMON_SW_MINOR_VERSION_H) || \
     (QSPI_IP_HW_ACCESS_SW_PATCH_VERSION_H != QSPI_IP_COMMON_SW_PATCH_VERSION_H) \
    )
    #error "Software Version Numbers of Qspi_Ip_HwAccess.h and Qspi_Ip_Common.h are different"
#endif
/*******************************************************************************
 * Definitions
 ******************************************************************************/

#define QSPI_IP_RX_READOUT_IP   1U        /* RX Buffer content is read using the AHB Bus registers QSPI_ARDBn */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif


/*
 * Set all hardware registers to their reset value
 */
static inline void Qspi_Ip_ResetAllRegisters(QuadSPI_Type *baseAddr)
{
    uint8 cnt;

    /* reset MCR register */
    baseAddr->MCR      = (uint32)0x000F404CUL;
    /* reset IPCR register */
    baseAddr->IPCR     = (uint32)0x00000000UL;
    /* reset FLSHCR register */
    baseAddr->FLSHCR   = (uint32)0x00000303UL;
    /* reset BUF0CR register */
    baseAddr->BUF0CR   = (uint32)0x0000000BUL;
    /* reset BUF1CR register */
    baseAddr->BUF1CR   = (uint32)0x00000001UL;
    /* reset BUF2CR register */
    baseAddr->BUF2CR   = (uint32)0x00000002UL;
    /* reset BUF3CR register */
    baseAddr->BUF3CR   = (uint32)0x80000003UL;
    /* reset BFGENCR register */
    baseAddr->BFGENCR  = (uint32)0x00000000UL;
    /* reset BUF0IND register */
    baseAddr->BUF0IND  = (uint32)0x00000000UL;
    /* reset BUF1IND register */
    baseAddr->BUF1IND  = (uint32)0x00000000UL;
    /* reset BUF2IND register */
    baseAddr->BUF2IND  = (uint32)0x00000000UL;
    /* reset AWRCR register */
    baseAddr->AWRCR    = (uint32)0x00000000UL;
    /* reset DLLCRA register */
    baseAddr->DLLCRA   = (uint32)0x01200000UL;
    /* reset DLLCRB register */
    baseAddr->DLLCRB   = (uint32)0x01200000UL;
    /* reset PARITYCR register */
    baseAddr->PARITYCR = (uint32)0x00000000UL;
    /* reset SFAR register */
    baseAddr->SFAR     = (uint32)0x00000000UL;
    /* reset SFACR register */
    baseAddr->SFACR    = (uint32)0x00000800UL;
    /* reset SMPR register */
    baseAddr->SMPR     = (uint32)0x00000000UL;
    /* reset RBCT register */
    baseAddr->RBCT     = (uint32)0x00000000UL;
    /* reset DLCR register */
    baseAddr->DLCR     = (uint32)0x40FF40FFUL;
    /* reset TBDR register */
    baseAddr->TBDR     = (uint32)0x00000000UL;
    /* reset TBCT register */
    baseAddr->TBCT     = (uint32)0x00000000UL;
    /* reset FR register, Write 1 to clear */
    baseAddr->FR       = (uint32)0x9D83DFC1UL;
    /* reset RSER register */
    baseAddr->RSER     = (uint32)0x00000000UL;
    /* reset SPTRCLR register */
    baseAddr->SPTRCLR  = (uint32)0x00000000UL;
    /* reset SFA1AD register */
    baseAddr->SFA1AD   = (uint32)0x00000000UL;
    /* reset SFA2AD register */
    baseAddr->SFA2AD   = (uint32)0x00000000UL;
    /* reset SFB1AD register */
    baseAddr->SFB1AD   = (uint32)0x00000000UL;
    /* reset SFB2AD register */
    baseAddr->SFB2AD   = (uint32)0x00000000UL;
    /* reset DLPR register */
    baseAddr->DLPR     = (uint32)0xAA553443UL;
    /* reset LUTKEY register */
    baseAddr->LUTKEY   = (uint32)0x5AF05AF0UL;
    /* reset LCKCR register */
    baseAddr->LCKCR    = (uint32)0x00000002UL;
    /* reset LUT0 register */
    baseAddr->LUT[0]   = (uint32)0x08180403UL;
    /* reset LUT1 register */
    baseAddr->LUT[1]   = (uint32)0x24001C08UL;
    for (cnt = 2U; cnt < QuadSPI_LUT_COUNT; cnt++)
    {
        baseAddr->LUT[cnt] = (uint32)0x00000000UL;
    }
}


/*
 * Triggers an IP transaction
 */
static inline void Qspi_Ip_IpTrigger(QuadSPI_Type *baseAddr, 
                                      uint8 seqID,
                                      uint16 dataSize)
{
    baseAddr->IPCR =  QuadSPI_IPCR_SEQID(seqID)
                    | QuadSPI_IPCR_IDATSZ(dataSize);
}


/*
 * Clear Rx buffer
 */
static inline void Qspi_Ip_ClearRxBuf(QuadSPI_Type *baseAddr)
{
    baseAddr->MCR |= QuadSPI_MCR_CLR_RXF_MASK;

}


/*
 * Clear Tx buffer
 */
static inline void Qspi_Ip_ClearTxBuf(QuadSPI_Type *baseAddr)
{
    baseAddr->MCR |= QuadSPI_MCR_CLR_TXF_MASK;

}


/*
 * Checks the Tx buffer clear flag
 * Returns TRUE if the Tx buffer content is invalidated.
 */
static inline boolean Qspi_Ip_GetClrTxStatus(const QuadSPI_Type *baseAddr)
{
    uint32 regValue = (uint32)baseAddr->MCR;
    regValue = (regValue & QuadSPI_MCR_CLR_TXF_MASK) >> QuadSPI_MCR_CLR_TXF_SHIFT;
    return (regValue == 0U)? TRUE : FALSE;
}


/*
 * Enable QuadSPI device
 */
static inline void Qspi_Ip_Enable(QuadSPI_Type *baseAddr)
{
    baseAddr->MCR &= ~QuadSPI_MCR_MDIS_MASK;

}


/*
 * Disable QuadSPI device
 */
static inline void Qspi_Ip_Disable(QuadSPI_Type *baseAddr)
{
    baseAddr->MCR |= QuadSPI_MCR_MDIS_MASK;

}

#if (FEATURE_QSPI_DDR == 1)
/*
 * Enable DDR mode
 */
static inline void QSPI_DDR_Enable(QuadSPI_Type *baseAddr)
{
    baseAddr->MCR |= QuadSPI_MCR_DDR_EN_MASK;

}


/*
 * Disable DDR mode
 */
static inline void QSPI_DDR_Disable(QuadSPI_Type *baseAddr)
{
    baseAddr->MCR &= ~QuadSPI_MCR_DDR_EN_MASK;

}


/*
 * Enable or disable DQS Latency
 */
static inline void QSPI_DQS_LatEnable(QuadSPI_Type *baseAddr, boolean enable)
{
    uint32 regValue = (uint32)baseAddr->MCR;
    regValue &= (uint32)(~((uint32)QuadSPI_MCR_DQS_LAT_EN_MASK));
    regValue |= QuadSPI_MCR_DQS_LAT_EN(enable? 1U : 0U);

    baseAddr->MCR = (uint32)regValue;
}
#endif /* FEATURE_QSPI_DDR == 1 */


/*
 * Enable DQS
 */
static inline void QSPI_DQS_Enable(QuadSPI_Type *baseAddr)
{
    (void)baseAddr;
#ifdef QuadSPI_MCR_DQS_EN_MASK
    baseAddr->MCR |= QuadSPI_MCR_DQS_EN_MASK;
#endif
}

/*
 * Disable DQS
 */
static inline void QSPI_DQS_Disable(QuadSPI_Type *baseAddr)
{
    (void)baseAddr;
#ifdef QuadSPI_MCR_DQS_EN_MASK
    baseAddr->MCR &= ~QuadSPI_MCR_DQS_EN_MASK;
#endif
}


/*
 * Assert QuadSPI sw reset bits
 */
static inline void Qspi_Ip_SwResetOn(QuadSPI_Type *baseAddr)
{
    baseAddr->MCR |= QuadSPI_MCR_SWRSTHD_MASK | QuadSPI_MCR_SWRSTSD_MASK;

}


/*
 * Deassert QuadSPI sw reset bits
 */
static inline void Qspi_Ip_SwResetOff(QuadSPI_Type *baseAddr)
{
    baseAddr->MCR &= ~(QuadSPI_MCR_SWRSTHD_MASK | QuadSPI_MCR_SWRSTSD_MASK);

}


#if (FEATURE_QSPI_CONFIGURABLE_ISD == 1)
/*
 * Configure idle values for data lines 2:3
 */
#if (FEATURE_QSPI_HAS_SIDE_B == 1)
static inline void Qspi_Ip_SetIdleLineValues(QuadSPI_Type *baseAddr, 
                                              uint8 iofa2IdleValue, 
                                              uint8 iofa3IdleValue, 
                                              uint8 iofb2IdleValue, 
                                              uint8 iofb3IdleValue)
{
    /* get value MCR register */
    uint32 regValue = (uint32)baseAddr->MCR;
    /* set mask for ISD3FA,ISD2FA,ISD2FB,ISD3FB */
    regValue &= (uint32)(~(QuadSPI_MCR_ISD2FA_MASK | QuadSPI_MCR_ISD3FA_MASK | QuadSPI_MCR_ISD2FB_MASK | QuadSPI_MCR_ISD3FB_MASK));
    regValue |= (QuadSPI_MCR_ISD2FA(iofa2IdleValue) |
                 QuadSPI_MCR_ISD3FA(iofa3IdleValue) | 
                 QuadSPI_MCR_ISD2FB(iofb2IdleValue) | 
                 QuadSPI_MCR_ISD3FB(iofb3IdleValue));
    /* set again the MCR register */
    baseAddr->MCR = (uint32)regValue;
}
#else
static inline void Qspi_Ip_SetIdleLineValues(QuadSPI_Type *baseAddr, 
                                              uint8 iofa2IdleValue, 
                                              uint8 iofa3IdleValue)
{
    /* get value MCR register */
    uint32 regValue = (uint32)baseAddr->MCR;
    /* set mask for ISD3FA,ISD2FA,ISD2FB,ISD3FB */
    regValue &= (uint32)(~(QuadSPI_MCR_ISD2FA_MASK | QuadSPI_MCR_ISD3FA_MASK | QuadSPI_MCR_ISD2FB_MASK | QuadSPI_MCR_ISD3FB_MASK));
    regValue |= (QuadSPI_MCR_ISD2FA(iofa2IdleValue) 
                 | QuadSPI_MCR_ISD3FA(iofa3IdleValue));
    /* set again the MCR register */
    baseAddr->MCR = (uint32)regValue;
}
#endif  /* FEATURE_QSPI_HAS_SIDE_B == 1 */
#endif  /* FEATURE_QSPI_CONFIGURABLE_ISD == 1 */


/*
 * Enable/Disable DQS slave delay chain
 */
static inline void Qspi_Ip_DLLSlaveEnA(QuadSPI_Type *baseAddr, boolean enable)
{
    uint32 regValue = (uint32)baseAddr->DLLCRA;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRA_SLV_EN_MASK));
    regValue |= QuadSPI_DLLCRA_SLV_EN(enable? 1U : 0U);
    baseAddr->DLLCRA = (uint32)regValue;
}

/*
 * Activates/Deactivates DQS slave delay chain update
 */
static inline void Qspi_Ip_DLLSlaveUpdateA(QuadSPI_Type *baseAddr, boolean enable)
{
    uint32 regValue = (uint32)baseAddr->DLLCRA;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRA_SLV_UPD_MASK));
    regValue |= QuadSPI_DLLCRA_SLV_UPD(enable? 1U : 0U);
    baseAddr->DLLCRA = (uint32)regValue;
}

#if (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1)
/*
 * Activates/Deactivates DQS slave delay chain update
 */
static inline void Qspi_Ip_DLLEnableA(QuadSPI_Type *baseAddr, boolean enable)
{
    uint32 regValue = (uint32)baseAddr->DLLCRA;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRA_DLLEN_MASK));
    regValue |= QuadSPI_DLLCRA_DLLEN(enable? 1U : 0U);
    baseAddr->DLLCRA = (uint32)regValue;
}
#endif /* (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1) */

/*
 * Activates/Deactivates slave DLL bypass
 */
static inline void Qspi_Ip_DLLSlaveBypassA(QuadSPI_Type *baseAddr, boolean enable)
{
    uint32 regValue = (uint32)baseAddr->DLLCRA;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRA_SLV_DLL_BYPASS_MASK));
    regValue |= QuadSPI_DLLCRA_SLV_DLL_BYPASS(enable? 1U : 0U);
    baseAddr->DLLCRA = (uint32)regValue;
}

/*
 * Activates/Deactivates slave auto update
 */
static inline void Qspi_Ip_DLLSlaveAutoUpdateA(QuadSPI_Type *baseAddr, boolean enable)
{
    (void)baseAddr;
    (void)enable;
#if (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1)
    uint32 regValue = (uint32)baseAddr->DLLCRA;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRA_SLAVE_AUTO_UPDT_MASK));
    regValue |= QuadSPI_DLLCRA_SLAVE_AUTO_UPDT(enable? 1U : 0U);
    baseAddr->DLLCRA = (uint32)regValue;
#endif /* (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1) */
}

/*
 * Activates/Deactivates delay-chain for high frequency of operation
 */
static inline void Qspi_Ip_DLLFreqEnA(QuadSPI_Type *baseAddr, boolean enable)
{
    uint32 regValue = (uint32)baseAddr->DLLCRA;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRA_FREQEN_MASK));
    regValue |= QuadSPI_DLLCRA_FREQEN(enable? 1U : 0U);
    baseAddr->DLLCRA = (uint32)regValue;
}

/*
 * Sets slave delay chain coarse delay for DLL bypass mode
 */
static inline void Qspi_Ip_DLLSetCoarseDelayA(QuadSPI_Type *baseAddr, uint8 coarseDelay)
{
    uint32 regValue = (uint32)baseAddr->DLLCRA;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRA_SLV_DLY_COARSE_MASK));
    regValue |= QuadSPI_DLLCRA_SLV_DLY_COARSE(coarseDelay);
    baseAddr->DLLCRA = (uint32)regValue;
}

#ifdef QuadSPI_DLLCRA_SLV_DLY_FINE_MASK
/*
 * Sets slave delay chain fine delay for DLL bypass mode
 */
static inline void Qspi_Ip_DLLSetFineDelayA(QuadSPI_Type *baseAddr, uint8 fineDelay)
{
    uint32 regValue = (uint32)baseAddr->DLLCRA;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRA_SLV_DLY_FINE_MASK));
    regValue |= QuadSPI_DLLCRA_SLV_DLY_FINE(fineDelay);
    baseAddr->DLLCRA = (uint32)regValue;
}
#endif  /* QuadSPI_DLLCRA_SLV_DLY_FINE_MASK */

/*
 * Sets reference counter
 */
static inline void Qspi_Ip_DLLSetReferenceCounterA(QuadSPI_Type *baseAddr, uint8 referenceCounter)
{
    uint32 regValue = (uint32)baseAddr->DLLCRA;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRA_DLL_REFCNTR_MASK));
    regValue |= QuadSPI_DLLCRA_DLL_REFCNTR(referenceCounter);
    baseAddr->DLLCRA = (uint32)regValue;
}

/*
 * Sets resolution
 */
static inline void Qspi_Ip_DLLSetResolutionA(QuadSPI_Type *baseAddr, uint8 resolution)
{
    uint32 regValue = (uint32)baseAddr->DLLCRA;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRA_DLLRES_MASK));
    regValue |= QuadSPI_DLLCRA_DLLRES(resolution);
    baseAddr->DLLCRA = (uint32)regValue;
}

/*
 * Sets slave delay chain coarse offset
 */
static inline void Qspi_Ip_DLLSetCoarseOffsetA(QuadSPI_Type *baseAddr, uint8 coarseDelay)
{
    uint32 regValue = (uint32)baseAddr->DLLCRA;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRA_SLV_DLY_OFFSET_MASK));
    regValue |= QuadSPI_DLLCRA_SLV_DLY_OFFSET(coarseDelay);
    baseAddr->DLLCRA = (uint32)regValue;
}

/*
 * Sets slave delay chain fine offset
 */
static inline void Qspi_Ip_DLLSetFineOffsetA(QuadSPI_Type *baseAddr, uint8 fineDelay)
{
    uint32 regValue = (uint32)baseAddr->DLLCRA;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRA_SLV_FINE_OFFSET_MASK));
    regValue |= QuadSPI_DLLCRA_SLV_FINE_OFFSET(fineDelay);
    baseAddr->DLLCRA = (uint32)regValue;
}


#if (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1)
/*
 * Checks high frequency slave delay chain lock status
 */
static inline boolean Qspi_Ip_DLLGetSlaveLockStatusA(const QuadSPI_Type *baseAddr)
{
    uint32 regValue = (uint32)baseAddr->DLLSR;
    regValue = (regValue & QuadSPI_DLLSR_SLVA_LOCK_MASK) >> QuadSPI_DLLSR_SLVA_LOCK_SHIFT;
    return (regValue != 0U)? TRUE : FALSE;
}

/*
 * Checks DLL lock status
 */
static inline boolean Qspi_Ip_DLLGetLockStatusA(const QuadSPI_Type *baseAddr)
{
    uint32 regValue = (uint32)baseAddr->DLLSR;
    regValue = (regValue & QuadSPI_DLLSR_DLLA_LOCK_MASK) >> QuadSPI_DLLSR_DLLA_LOCK_SHIFT;
    return (regValue != 0U)? TRUE : FALSE;
}

/*
 * Checks high frequency slave delay chain error status
 */
static inline boolean Qspi_Ip_DLLGetErrorStatusA(const QuadSPI_Type *baseAddr)
{
    uint32 regValue = (uint32)baseAddr->DLLSR;
    regValue = regValue & (QuadSPI_DLLSR_DLLA_RANGE_ERR_MASK | QuadSPI_DLLSR_DLLA_FINE_UNDERFLOW_MASK);
    return (regValue != 0U)? TRUE : FALSE;
}
#endif /* (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1) */

#if (FEATURE_QSPI_HAS_SIDE_B == 1)
/*
 * Enable/Disable DQS slave delay chain
 */
static inline void Qspi_Ip_DLLSlaveEnB(QuadSPI_Type *baseAddr, boolean enable)
{
    uint32 regValue = (uint32)baseAddr->DLLCRB;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRB_SLV_EN_MASK));
    regValue |= QuadSPI_DLLCRB_SLV_EN(enable? 1U : 0U);
    baseAddr->DLLCRB = (uint32)regValue;
}

/*
 * Activates/Deactivates DQS slave delay chain update
 */
static inline void Qspi_Ip_DLLSlaveUpdateB(QuadSPI_Type *baseAddr, boolean enable)
{
    uint32 regValue = (uint32)baseAddr->DLLCRB;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRB_SLV_UPD_MASK));
    regValue |= QuadSPI_DLLCRB_SLV_UPD(enable? 1U : 0U);
    baseAddr->DLLCRB = (uint32)regValue;
}

#if (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1)
/*
 * Activates/Deactivates DQS slave delay chain update
 */
static inline void Qspi_Ip_DLLEnableB(QuadSPI_Type *baseAddr, boolean enable)
{
    uint32 regValue = (uint32)baseAddr->DLLCRB;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRB_DLLEN_MASK));
    regValue |= QuadSPI_DLLCRB_DLLEN(enable? 1U : 0U);
    baseAddr->DLLCRB = (uint32)regValue;
}
#endif /* (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1) */

/*
 * Activates/Deactivates slave DLL bypass
 */
static inline void Qspi_Ip_DLLSlaveBypassB(QuadSPI_Type *baseAddr, boolean enable)
{
    uint32 regValue = (uint32)baseAddr->DLLCRB;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRB_SLV_DLL_BYPASS_MASK));
    regValue |= QuadSPI_DLLCRB_SLV_DLL_BYPASS(enable? 1U : 0U);
    baseAddr->DLLCRB = (uint32)regValue;
}

/*
 * Activates/Deactivates slave auto update
 */
static inline void Qspi_Ip_DLLSlaveAutoUpdateB(QuadSPI_Type *baseAddr, boolean enable)
{
    (void)baseAddr;
    (void)enable;
#if (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1)
    uint32 regValue = (uint32)baseAddr->DLLCRB;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRB_SLAVE_AUTO_UPDT_MASK));
    regValue |= QuadSPI_DLLCRB_SLAVE_AUTO_UPDT(enable? 1U : 0U);
    baseAddr->DLLCRB = (uint32)regValue;
#endif /* (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1) */
}

/*
 * Activates/Deactivates delay-chain for high frequency of operation
 */
static inline void Qspi_Ip_DLLFreqEnB(QuadSPI_Type *baseAddr, boolean enable)
{
    uint32 regValue = (uint32)baseAddr->DLLCRB;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRB_FREQEN_MASK));
    regValue |= QuadSPI_DLLCRB_FREQEN(enable? 1U : 0U);
    baseAddr->DLLCRB = (uint32)regValue;
}

/*
 * Sets slave delay chain coarse delay for DLL bypass mode
 */
static inline void Qspi_Ip_DLLSetCoarseDelayB(QuadSPI_Type *baseAddr, uint8 coarseDelay)
{
    uint32 regValue = (uint32)baseAddr->DLLCRB;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRB_SLV_DLY_COARSE_MASK));
    regValue |= QuadSPI_DLLCRB_SLV_DLY_COARSE(coarseDelay);
    baseAddr->DLLCRB = (uint32)regValue;
}

#ifdef QuadSPI_DLLCRB_SLV_DLY_FINE_MASK
/*
 * Sets slave delay chain fine delay for DLL bypass mode
 */
static inline void Qspi_Ip_DLLSetFineDelayB(QuadSPI_Type *baseAddr, uint8 fineDelay)
{
#ifdef QuadSPI_DLLCRB_SLV_DLY_FINE_MASK
    uint32 regValue = (uint32)baseAddr->DLLCRB;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRB_SLV_DLY_FINE_MASK));
    regValue |= QuadSPI_DLLCRB_SLV_DLY_FINE(fineDelay);
    baseAddr->DLLCRB = (uint32)regValue;
#endif  /* QuadSPI_DLLCRB_SLV_DLY_FINE_MASK */
}
#endif /* ifdef QuadSPI_DLLCRB_SLV_DLY_FINE_MASK */

/*
 * Sets reference counter
 */
static inline void Qspi_Ip_DLLSetReferenceCounterB(QuadSPI_Type *baseAddr, uint8 referenceCounter)
{
    uint32 regValue = (uint32)baseAddr->DLLCRB;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRB_DLL_REFCNTR_MASK));
    regValue |= QuadSPI_DLLCRB_DLL_REFCNTR(referenceCounter);
    baseAddr->DLLCRB = (uint32)regValue;
}

/*
 * Sets resolution
 */
static inline void Qspi_Ip_DLLSetResolutionB(QuadSPI_Type *baseAddr, uint8 resolution)
{
    uint32 regValue = (uint32)baseAddr->DLLCRB;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRB_DLLRES_MASK));
    regValue |= QuadSPI_DLLCRB_DLLRES(resolution);
    baseAddr->DLLCRB = (uint32)regValue;
}

/*
 * Sets slave delay chain coarse offset
 */
static inline void Qspi_Ip_DLLSetCoarseOffsetB(QuadSPI_Type *baseAddr, uint8 coarseDelay)
{
    uint32 regValue = (uint32)baseAddr->DLLCRB;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRB_SLV_DLY_OFFSET_MASK));
    regValue |= QuadSPI_DLLCRB_SLV_DLY_OFFSET(coarseDelay);
    baseAddr->DLLCRB = (uint32)regValue;
}

/*
 * Sets slave delay chain fine offset
 */
static inline void Qspi_Ip_DLLSetFineOffsetB(QuadSPI_Type *baseAddr, uint8 fineDelay)
{
    uint32 regValue = (uint32)baseAddr->DLLCRB;
    regValue &= (uint32)(~((uint32)QuadSPI_DLLCRB_SLV_FINE_OFFSET_MASK));
    regValue |= QuadSPI_DLLCRB_SLV_FINE_OFFSET(fineDelay);
    baseAddr->DLLCRB = (uint32)regValue;
}

#if (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1)
/*
 * Checks high frequency slave delay chain lock status
 */
static inline boolean Qspi_Ip_DLLGetSlaveLockStatusB(const QuadSPI_Type *baseAddr)
{
    uint32 regValue = (uint32)baseAddr->DLLSR;
    regValue = (regValue & QuadSPI_DLLSR_SLVB_LOCK_MASK) >> QuadSPI_DLLSR_SLVB_LOCK_SHIFT;
    return (regValue != 0U)? TRUE : FALSE;
}

/*
 * Checks DLL lock status
 */
static inline boolean Qspi_Ip_DLLGetLockStatusB(const QuadSPI_Type *baseAddr)
{
    uint32 regValue = (uint32)baseAddr->DLLSR;
    regValue = (regValue & QuadSPI_DLLSR_DLLB_LOCK_MASK) >> QuadSPI_DLLSR_DLLB_LOCK_SHIFT;
    return (regValue != 0U)? TRUE : FALSE;
}

/*
 * Checks high frequency slave delay chain error status
 */
static inline boolean Qspi_Ip_DLLGetErrorStatusB(const QuadSPI_Type *baseAddr)
{
    uint32 regValue = (uint32)baseAddr->DLLSR;
    regValue = regValue & (QuadSPI_DLLSR_DLLB_RANGE_ERR_MASK | QuadSPI_DLLSR_DLLB_FINE_UNDERFLOW_MASK);
    return (regValue != 0U)? TRUE : FALSE;
}
#endif /* (FEATURE_QSPI_EXTERNAL_DLL_FULL == 1) */

#endif  /* FEATURE_QSPI_HAS_SIDE_B == 1 */


/*
 * Configure external flash memory map
 */
static inline void Qspi_Ip_SetMemMap(uint32 instance, QuadSPI_Type *baseAddr, uint32 sizeA1, uint32 sizeA2
#if (FEATURE_QSPI_HAS_SIDE_B == 1)
                   , uint32 sizeB1, uint32 sizeB2
#endif
                   )
{
    baseAddr->SFA1AD = Qspi_Ip_AhbAddress[instance] + sizeA1;
    baseAddr->SFA2AD = Qspi_Ip_AhbAddress[instance] + sizeA1 + sizeA2;
#if (FEATURE_QSPI_HAS_SIDE_B == 1)
    baseAddr->SFB1AD = Qspi_Ip_AhbAddress[instance] + sizeA1 + sizeA2 + sizeB1;
    baseAddr->SFB2AD = Qspi_Ip_AhbAddress[instance] + sizeA1 + sizeA2 + sizeB1 + sizeB2;
#endif
}


/*
 * Set CS hold time in serial clock cycles
 */
static inline void Qspi_Ip_SetCsHoldTime(QuadSPI_Type *baseAddr, uint8 cycles)
{
    uint32 regValue = (uint32)baseAddr->FLSHCR;
    regValue &= (uint32)(~((uint32)QuadSPI_FLSHCR_TCSH_MASK));
    regValue |= QuadSPI_FLSHCR_TCSH(cycles);
    baseAddr->FLSHCR = (uint32)regValue;
}


/*
 * Set CS setup time
 */
static inline void Qspi_Ip_SetCsSetupTime(QuadSPI_Type *baseAddr, uint8 cycles)
{
    uint32 regValue = (uint32)baseAddr->FLSHCR;
    regValue &= (uint32)(~((uint32)QuadSPI_FLSHCR_TCSS_MASK));
    regValue |= QuadSPI_FLSHCR_TCSS(cycles);
    baseAddr->FLSHCR = (uint32)regValue;
}


#if (FEATURE_QSPI_DDR == 1)
/*
 * Set data in hold time
 */
static inline void Qspi_Ip_SetDataInHoldTime(QuadSPI_Type *baseAddr, Qspi_Ip_FlashDataAlignType enable)
{
    uint32 regValue = (uint32)baseAddr->FLSHCR;
    regValue &= (uint32)(~(QuadSPI_FLSHCR_TDH_MASK));
    regValue |= QuadSPI_FLSHCR_TDH(enable);
    baseAddr->FLSHCR = (uint32)regValue;
}
#endif 


/*
 * Sets AHB buffer 0 configuration
 */
static inline void Qspi_Ip_SetAhbBuf0(QuadSPI_Type *baseAddr, 
                                       uint16 size,
                                       uint8 master)
{
    baseAddr->BUF0CR =  QuadSPI_BUF0CR_ADATSZ((uint32)size >> 3U)
                      | QuadSPI_BUF0CR_MSTRID(master);
}


/*
 * Sets AHB buffer 1 configuration
 */
static inline void Qspi_Ip_SetAhbBuf1(QuadSPI_Type *baseAddr, 
                                       uint16 size,
                                       uint8 master)
{
    baseAddr->BUF1CR =  QuadSPI_BUF1CR_ADATSZ((uint32)size >> 3U)
                      | QuadSPI_BUF1CR_MSTRID(master);
}


/*
 * Sets AHB buffer 2 configuration
 */
static inline void Qspi_Ip_SetAhbBuf2(QuadSPI_Type *baseAddr, 
                                       uint16 size,
                                       uint8 master)
{
    baseAddr->BUF2CR =  QuadSPI_BUF2CR_ADATSZ((uint32)size >> 3U)
                      | QuadSPI_BUF2CR_MSTRID(master);
}


/*
 * Sets AHB buffer 3 configuration
 */
static inline void Qspi_Ip_SetAhbBuf3(QuadSPI_Type *baseAddr, 
                                       uint16 size,
                                       uint8 master,
                                       boolean allMasters)
{
    baseAddr->BUF3CR =  QuadSPI_BUF3CR_ADATSZ((uint32)size >> 3U)
                      | QuadSPI_BUF3CR_MSTRID(master)
                      | QuadSPI_BUF3CR_ALLMST(allMasters? 1U : 0U);
}


/*
 * Sets AHB buffer 0 index. Parameter represents desired end index of the buffer.
 */
static inline void Qspi_Ip_SetAhbBuf0Ind(QuadSPI_Type *baseAddr, 
                                          uint32 index)
{
    baseAddr->BUF0IND =  index;
}


/*
 * Sets AHB buffer 1 index. Parameter represents desired end index of the buffer.
 */
static inline void Qspi_Ip_SetAhbBuf1Ind(QuadSPI_Type *baseAddr, 
                                          uint32 index)
{
    baseAddr->BUF1IND =  index;
}


/*
 * Sets AHB buffer 2 index. Parameter represents desired end index of the buffer.
 */
static inline void Qspi_Ip_SetAhbBuf2Ind(QuadSPI_Type *baseAddr, 
                                          uint32 index)
{
    baseAddr->BUF2IND =  index;
}


/*
 * Sets address for IP transactions
 */
static inline void Qspi_Ip_SetIpAddr(QuadSPI_Type *baseAddr, 
                                     uint32 addr)
{
    baseAddr->SFAR = addr;
}


#if (FEATURE_QSPI_ADDR_CFG == 1)
/*
 * Sets flash address options
 */
static inline void Qspi_Ip_SetAddrOptions(QuadSPI_Type *baseAddr, 
                                           uint32 columnAddr,
                                           boolean wordAdressable)
{
    baseAddr->SFACR = QuadSPI_SFACR_CAS(columnAddr)
                    | QuadSPI_SFACR_WA(wordAdressable? 1U : 0U);
}
#endif


/*
 * Configures parameters related to sampling Rx data
 */
static inline void Qspi_Ip_SetRxCfg(QuadSPI_Type *baseAddr, 
                                     Qspi_Ip_SampleDelayType delay,
                                     Qspi_Ip_SamplePhaseType clockPhase)
{
    baseAddr->SMPR = QuadSPI_SMPR_FSPHS(clockPhase)
                   | QuadSPI_SMPR_FSDLY(delay);
}


/*
 * Configures parameters related to sampling Rx data
 */
static inline void Qspi_Ip_SetRxDLLTapA(QuadSPI_Type *baseAddr, uint8 taps)
{
    uint32 regValue = baseAddr->SMPR;
    regValue &= ~QuadSPI_SMPR_DLLFSMPFA_MASK;
    regValue |= QuadSPI_SMPR_DLLFSMPFA(taps);
    baseAddr->SMPR = regValue;
}


#if (FEATURE_QSPI_HAS_SIDE_B == 1)
/*
 * Configures parameters related to sampling Rx data
 */
static inline void Qspi_Ip_SetRxDLLTapB(QuadSPI_Type *baseAddr, uint8 taps)
{
    uint32 regValue = baseAddr->SMPR;
    regValue &= ~QuadSPI_SMPR_DLLFSMPFB_MASK;
    regValue |= QuadSPI_SMPR_DLLFSMPFB(taps);
    baseAddr->SMPR = regValue;
}
#endif

/*
 * Checks if module is busy with a transaction
 */
static inline boolean Qspi_Ip_GetBusyStatus(const QuadSPI_Type *baseAddr)
{
    uint32 regValue = (uint32)baseAddr->SR;
    regValue = (regValue & QuadSPI_SR_BUSY_MASK) >> QuadSPI_SR_BUSY_SHIFT;
    return (regValue != 0U)? TRUE : FALSE;
}


/*
 * Returns the current fill level of the Rx buffer
 */
static inline uint32 Qspi_Ip_GetRxBufFill(const QuadSPI_Type *baseAddr)
{
    uint32 regValue = (uint32)baseAddr->RBSR;
    regValue = (regValue & QuadSPI_RBSR_RDBFL_MASK) >> QuadSPI_RBSR_RDBFL_SHIFT;
    return regValue;
}


/*
 * Checks if enough Rx data is available, according to the watermark setting
 */
static inline boolean Qspi_Ip_GetRxDataEvent(const QuadSPI_Type *baseAddr)
{
    uint32 regValue = (uint32)baseAddr->SR;
    regValue = (regValue & QuadSPI_SR_RXWE_MASK) >> QuadSPI_SR_RXWE_SHIFT;
    return (regValue != 0U)? TRUE : FALSE;
}


/*
 * Returns Tx buffer fill level expressed in 4-byte entries
 */
static inline uint32 Qspi_Ip_GetTxBufFill(const QuadSPI_Type *baseAddr)
{
    uint32 regValue = (uint32)baseAddr->TBSR;
    regValue = (regValue & QuadSPI_TBSR_TRBFL_MASK) >> QuadSPI_TBSR_TRBFL_SHIFT;
    return regValue;
}


/*
 * Checks the Tx buffer watermark. 
 * Returns TRUE if number of buffer entries specified by the watermark is available.
 */
static inline boolean Qspi_Ip_GetTxWatermarkAvailable(const QuadSPI_Type *baseAddr)
{
    uint32 regValue = (uint32)baseAddr->SR;
    regValue = (regValue & QuadSPI_SR_TXWA_MASK) >> QuadSPI_SR_TXWA_SHIFT;
    return (regValue != 0U)? TRUE : FALSE;
}


/*
 * Writes data in the Tx buffer
 */
static inline void Qspi_Ip_WriteTxData(QuadSPI_Type *baseAddr, uint32 data)
{
    baseAddr->TBDR = data;
}


/*
 * Returns the address of the Tx data register
 */
static inline uint32 Qspi_Ip_GetTxDataAddr(const QuadSPI_Type *baseAddr)
{
    return (uint32)&(baseAddr->TBDR);
}


/*
 * Returns the address of the first Rx data register
 */
static inline uint32 Qspi_Ip_GetRxDataAddr(const QuadSPI_Type *baseAddr)
{
    return (uint32)&(baseAddr->RBDR[0U]);
}


/*
 * Enables Tx DMA request (when Tx buffer has room for more data)
 */
static inline void Qspi_Ip_EnableTxDmaReq(QuadSPI_Type *baseAddr)
{
    baseAddr->RSER |= QuadSPI_RSER_TBFDE_MASK;
}


/*
 * Enables Rx DMA request (when Rx buffer has room for more data)
 */
static inline void Qspi_Ip_EnableRxDmaReq(QuadSPI_Type *baseAddr)
{
    baseAddr->RSER |= QuadSPI_RSER_RBDDE_MASK;
}


/*
 * Disables both Rx and Tx DMA requests
 */
static inline void Qspi_Ip_DisableDmaReq(QuadSPI_Type *baseAddr)
{
    baseAddr->RSER &= ~(QuadSPI_RSER_TBFDE_MASK | QuadSPI_RSER_RBDDE_MASK);
}


/*
 * Perform a POP operation on the Rx buffer, removing Rx_watermark entries
 */
static inline void Qspi_Ip_RxPop(QuadSPI_Type *baseAddr)
{
    baseAddr->FR = QuadSPI_FR_RBDF_MASK;
}


/*
 * Configures the watermark for the Rx buffer, expressed in number of 4-byte entries
 */
static inline void Qspi_Ip_SetRxWatermark(QuadSPI_Type *baseAddr,
                                           uint8 watermark)
{
    uint32 regValue = (uint32)baseAddr->RBCT;
    regValue &= (uint32)(~((uint32)QuadSPI_RBCT_WMRK_MASK));
    regValue |= QuadSPI_RBCT_WMRK((uint32)watermark - 1U);
    baseAddr->RBCT = (uint32)regValue;
}


/*
 * Configures the rx for the Rx buffer, expressed in number of 4-byte entries
 */
static inline void Qspi_Ip_SetRxBufReadout(QuadSPI_Type *baseAddr,
                                            uint8 readout)
{
    uint32 regValue = (uint32)baseAddr->RBCT;
    regValue &= (uint32)(~((uint32)QuadSPI_RBCT_RXBRD_MASK));
    regValue |= QuadSPI_RBCT_RXBRD(readout);
    baseAddr->RBCT = (uint32)regValue;
}


/*
 * Configures the watermark for the Tx buffer, expressed in number of 4-byte entries
 */
static inline void Qspi_Ip_SetTxWatermark(QuadSPI_Type *baseAddr,
                                           uint8 watermark)
{
    uint32 regValue = (uint32)baseAddr->TBCT;
    regValue &= (uint32)(~((uint32)QuadSPI_TBCT_WMRK_MASK));
    regValue |= QuadSPI_TBCT_WMRK(watermark);
    baseAddr->TBCT = (uint32)regValue;
}


/*
 * Enables interrupts specified by the mask parameter
 */
static inline void Qspi_Ip_EnableInt(QuadSPI_Type *baseAddr,
                                      uint32 mask)
{
    baseAddr->RSER |= mask;
}


/*
 * Disables interrupts specified by the mask parameter
 */
static inline void Qspi_Ip_DisableInt(QuadSPI_Type *baseAddr,
                                       uint32 mask)
{
    baseAddr->RSER &= ~mask;
}


/*
 * Clears interrupt flags specified by the mask parameter
 */
static inline void Qspi_Ip_ClearIntFlag(QuadSPI_Type *baseAddr,
                                         uint32 mask)
{
    baseAddr->FR = mask;
}


/*
 * Configure DQS clock for sampling read data
 */
static inline void Qspi_Ip_SetDQSSource(QuadSPI_Type *baseAddr, 
                                        Qspi_Ip_ReadModeType readModeA
#if (FEATURE_QSPI_HAS_SIDE_B == 1)
                                        , Qspi_Ip_ReadModeType readModeB
#endif
                                        )
{
    /* get the value of MCR register */
    uint32 regValue = (uint32)baseAddr->MCR;
    regValue &= (uint32)(~QuadSPI_MCR_DQS_FA_SEL_MASK);
    /* switch for modes */
    switch(readModeA)
    {
#if (FEATURE_QSPI_INTERNAL_DQS == 1)
        case QSPI_IP_READ_MODE_INTERNAL_DQS:
                /* if it is DQS internal */
                regValue |= QuadSPI_MCR_DQS_FA_SEL(0U);
                break;
#endif
#if (FEATURE_QSPI_LOOPBACK == 1)
        case QSPI_IP_READ_MODE_LOOPBACK:
                /* if it is Pad loopback */
                regValue |= QuadSPI_MCR_DQS_FA_SEL(1U);
                break;
#endif
#if (FEATURE_QSPI_LOOPBACK_DQS == 1)
        case QSPI_IP_READ_MODE_LOOPBACK_DQS:
                /* if it is DQS pad loopback */
                regValue |= QuadSPI_MCR_DQS_FA_SEL(2U);
                break;
#endif
#if (FEATURE_QSPI_EXTERNAL_DQS == 1)
        case QSPI_IP_READ_MODE_EXTERNAL_DQS:
                /* if it is DQS external */
                regValue |= QuadSPI_MCR_DQS_FA_SEL(3U);
                break;
#endif
        default:
                ; /* Not possible */
                break;
    }
#if (FEATURE_QSPI_HAS_SIDE_B == 1)
    switch(readModeB)
    {
#if (FEATURE_QSPI_INTERNAL_DQS == 1)
        case QSPI_IP_READ_MODE_INTERNAL_DQS:
                /* if it is DQS internal */
                regValue |= QuadSPI_MCR_DQS_FB_SEL(0U);
                break;
#endif
#if (FEATURE_QSPI_LOOPBACK == 1)
        case QSPI_IP_READ_MODE_LOOPBACK:
                /* if it is Pad loopback */
                regValue |= QuadSPI_MCR_DQS_FB_SEL(1U);
                break;
#endif
#if (FEATURE_QSPI_LOOPBACK_DQS == 1)
        case QSPI_IP_READ_MODE_LOOPBACK_DQS:
                /* if it is DQS pad loopback */
                regValue |= QuadSPI_MCR_DQS_FB_SEL(2U);
                break;
#endif
#if (FEATURE_QSPI_EXTERNAL_DQS == 1)
        case QSPI_IP_READ_MODE_EXTERNAL_DQS:
                /* if it is DQS external */
                regValue |= QuadSPI_MCR_DQS_FB_SEL(3U);
                break;
#endif
        default:
                ; /* Not possible */
                break;
    }
#endif /* (FEATURE_QSPI_HAS_SIDE_B == 1) */
    baseAddr->MCR = (uint32)regValue;
}

#if (FEATURE_QSPI_CENTER_ALIGNED_READ_STROBE == 1)
static inline void Qspi_Ip_SetCenterAlignedStrobeA(QuadSPI_Type *baseAddr, boolean centerAlignedStrobe)
{
    /* Get the value of MCR register */
    uint32 regValue = (uint32)baseAddr->MCR;
    /* Set mask */
    regValue &= (uint32)(~QuadSPI_MCR_CK2_DCARS_FA_MASK);
    regValue |= QuadSPI_MCR_CK2_DCARS_FA(centerAlignedStrobe? 1U : 0U);
    /* Update again the MCR register */
    baseAddr->MCR = (uint32)regValue;
}
#if (FEATURE_QSPI_HAS_SIDE_B == 1)
static inline void Qspi_Ip_SetCenterAlignedStrobeB(QuadSPI_Type *baseAddr, boolean centerAlignedStrobe)
{
    /* Get the value of MCR register */
    uint32 regValue = (uint32)baseAddr->MCR;
    /* Set mask */
    regValue &= (uint32)(~QuadSPI_MCR_CK2_DCARS_FB_MASK);
    regValue |= QuadSPI_MCR_CK2_DCARS_FB(centerAlignedStrobe? 1U : 0U);
    /* Update again the MCR register */
    baseAddr->MCR = (uint32)regValue;
}
#endif
#endif
#if (FEATURE_QSPI_DIFFERENTIAL_CLOCK == 1)
static inline void Qspi_Ip_SetDifferentialClockB(QuadSPI_Type *baseAddr, boolean differentialClock)
{
    /* Get the value of MCR register */
    uint32 regValue = (uint32)baseAddr->MCR;
    /* Set mask */
    regValue &= (uint32)(~QuadSPI_MCR_CKN_FB_EN_MASK);
    regValue |= QuadSPI_MCR_CKN_FB_EN(differentialClock? 1U : 0U);
    /* Update again the MCR register */
    baseAddr->MCR = (uint32)regValue;
}
#if (FEATURE_QSPI_HAS_SIDE_B == 1)
static inline void Qspi_Ip_SetDifferentialClockA(QuadSPI_Type *baseAddr, boolean differentialClock)
{
    /* Get the value of MCR register */
    uint32 regValue = (uint32)baseAddr->MCR;
    /* Set mask */
    regValue &= (uint32)(~QuadSPI_MCR_CKN_FA_EN_MASK);
    regValue |= QuadSPI_MCR_CKN_FA_EN(differentialClock? 1U : 0U);
    /* update again the MCR register */
    baseAddr->MCR = (uint32)regValue;
}
#endif
#endif


#if (FEATURE_QSPI_ADDR_CFG == 1)
static inline void Qspi_Ip_SetByteSwap(QuadSPI_Type *baseAddr, boolean byteSwap)
{
    /* Get the value of SFACR register */
    uint32 regValue = (uint32)baseAddr->SFACR;
    /* Set mask */
    regValue &= (uint32)(~QuadSPI_SFACR_BYTE_SWAP_MASK);
    regValue |= QuadSPI_SFACR_BYTE_SWAP(byteSwap? 1U : 0U);
    /* Update again the SFACR register */
    baseAddr->SFACR = (uint32)regValue;
}
#endif

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* QUADSPI_HW_ACCESS_H */
