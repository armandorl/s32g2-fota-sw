/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : 
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
*   @file       Clock_Ip_ProgFreqSwitch.c
*   @version    1.0.0
*
*   @brief   CLOCK driver implementations.
*   @details CLOCK driver implementations.
*
*   @addtogroup CLOCK_DRIVER Clock Driver
*   @{
*/

/**
* @page misra_violations MISRA-C:2012 violations
*
* @section Clock_Ip_ProgFreqSwitch_c_REF_1
* Violates MISRA 2012 Advisory Rule 20.1, #include directives should only be preceded by preprocessor
* directives or comments. AUTOSAR imposes the specification of the sections in which certain parts
* of the driver must be placed.
*
* @section Clock_Ip_ProgFreqSwitch_c_REF_2
* Violates MISRA 2012 Advisory Rule 4.8, This file includes the definition 
* of types but does not use it. Header is common for all files
*
*/



#include "Clock_Ip_Private.h"

/* Clock start section code */
#define MCU_START_SEC_CODE
/**
* @violates @ref Clock_Ip_ProgFreqSwitch_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"


static void ProgressiveFrequencyClockSwitchEmpty(Clock_Ip_PcfsConfigType const* config);
#ifdef CGM_X_PCFS_SDUR_SDUR
static void CgmXPcfsSdurSdur(Clock_Ip_PcfsConfigType const *config);
#endif
#ifdef CGM_X_PCFS_SDUR_DIVC_DIVE_DIVS
static void CgmXPcfsSdurDivcDiveDivs(Clock_Ip_PcfsConfigType const *config);
#endif

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
/**
* @violates @ref Clock_Ip_ProgFreqSwitch_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_ProgFreqSwitch_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

const pcfsCallback pcfsCallbacks[PCFS_CALLBACKS_COUNT] =
{
	{
		ProgressiveFrequencyClockSwitchEmpty,     /* Set */

	},
#ifdef CGM_X_PCFS_SDUR_SDUR
	{
		CgmXPcfsSdurSdur,    					  /* Set */
	},
#endif
#ifdef CGM_X_PCFS_SDUR_DIVC_DIVE_DIVS
	{
			CgmXPcfsSdurDivcDiveDivs,    		  /* Set */
	},
#endif
};

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_ProgFreqSwitch_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"


/* Clock start section code */
#define MCU_START_SEC_CODE
/**
* @violates @ref Clock_Ip_ProgFreqSwitch_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

static void ProgressiveFrequencyClockSwitchEmpty(Clock_Ip_PcfsConfigType const* config)
{
	(void)config;
	/* No implementation */
}


#ifdef CGM_X_PCFS_SDUR_SDUR
static void CgmXPcfsSdurSdur(Clock_Ip_PcfsConfigType const *config)
{
    uint32 instance      = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    uint32 hwIndex       = clockFeatures[config->name][PCFS_HW_INDEX];
    uint32 swIndex       = clockFeatures[config->name][PCFS_SW_INDEX];


    cgmPcfs[instance]->PCFS_SDUR = MC_CGM_PCFS_SDUR_SDUR(pcfsEntries[swIndex].sdur);
    (void)hwIndex;    /* hw index is not used because divc_init, divc_rate, divc_rate, div_startValue, div_endValue registers are not implemented */

	/* No implementation */
}
#endif


#ifdef CGM_X_PCFS_SDUR_DIVC_DIVE_DIVS
static void CgmXPcfsSdurDivcDiveDivs(Clock_Ip_PcfsConfigType const *config)
{
    uint32 instance      = clockFeatures[config->name][PCFS_INSTANCE];
    uint32 hwIndex       = clockFeatures[config->name][PCFS_HW_INDEX];
    uint32 swIndex       = clockFeatures[config->name][PCFS_SW_INDEX];

    cgmPcfs[instance]->PCFS_SDUR = MC_CGM_PCFS_SDUR_SDUR(pcfsEntries[swIndex].sdur);
    cgmPcfs[instance]->PCFS[hwIndex].DIVC = MC_CGM_PCFS_DIVC_RATE(pcfsEntries[swIndex].divc_rate) | MC_CGM_PCFS_DIVC_INIT(pcfsEntries[swIndex].divc_init);
    cgmPcfs[instance]->PCFS[hwIndex].DIVE = MC_CGM_PCFS_DIVE_DIVE(pcfsEntries[swIndex].div_endValue);
    cgmPcfs[instance]->PCFS[hwIndex].DIVS = MC_CGM_PCFS_DIVS_DIVS(pcfsEntries[swIndex].div_startValue);
}
#endif


/* Clock stop section code */
#define MCU_STOP_SEC_CODE
/**
* @violates @ref Clock_Ip_ProgFreqSwitch_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/*! @}*/

/*******************************************************************************
 * EOF
 ******************************************************************************/
