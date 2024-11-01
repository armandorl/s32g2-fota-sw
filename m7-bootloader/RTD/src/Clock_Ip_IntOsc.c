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
*   @file       Clock_Ip_IntOsc.c
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
* @section Clock_Ip_IntOsc_c_REF_1
* Violates MISRA 2012 Advisory Rule 20.1, #include directives should only be preceded by preprocessor
* directives or comments. AUTOSAR imposes the specification of the sections in which certain parts
* of the driver must be placed.
*
* @section Clock_Ip_IntOsc_c_REF_2
* Violates MISRA 2012 Advisory Rule 4.8, This file includes the definition 
* of types but does not use it. Header is common for all files
*
*/


#include "Clock_Ip_Private.h"

/* Clock start section code */
#define MCU_START_SEC_CODE
/**
* @violates @ref Clock_Ip_IntOsc_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"


static void InternalOscillatorEmpty(Clock_Ip_IrcoscConfigType const* config);
#ifdef FIRC_STDBY_ENABLE
static void FircStdbyEnable(Clock_Ip_IrcoscConfigType const* config);
#endif
#ifdef SIRC_STDBY_ENABLE
static void SircStdbyEnable(Clock_Ip_IrcoscConfigType const* config);
#endif

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
/**
* @violates @ref Clock_Ip_IntOsc_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_IntOsc_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

const intOscCallback intOscCallbacks[IRCOSC_CALLBACKS_COUNT] =
{
	{
		InternalOscillatorEmpty,        /* Set */
	},
#ifdef FIRC_STDBY_ENABLE
	{
		FircStdbyEnable,         	 	/* Set */
	},
#endif
#ifdef SIRC_STDBY_ENABLE
	{
		SircStdbyEnable,            	/* Set */
	},
#endif
};


/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_IntOsc_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"


/* Clock start section code */
#define MCU_START_SEC_CODE
/**
* @violates @ref Clock_Ip_IntOsc_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

static void InternalOscillatorEmpty(Clock_Ip_IrcoscConfigType const* config)
{
	(void)config;
	/* No implementation */
}

#ifdef FIRC_STDBY_ENABLE
static void FircStdbyEnable(Clock_Ip_IrcoscConfigType const* config)
{
    if (config->enable != 0U)
    {
    	FIRC->STDBY_ENABLE |= FIRC_STDBY_ENABLE_STDBY_EN_MASK;
    }
    else
    {
    	FIRC->STDBY_ENABLE &= ~FIRC_STDBY_ENABLE_STDBY_EN_MASK;
    }

}
#endif
#ifdef SIRC_STDBY_ENABLE
static void SircStdbyEnable(Clock_Ip_IrcoscConfigType const* config)
{
    if (config->enable != 0U)
    {
    	SIRC->MISCELLANEOUS_IN |= SIRC_MISCELLANEOUS_IN_STANDBY_ENABLE_MASK;
    }
    else
    {
    	SIRC->MISCELLANEOUS_IN &= ~SIRC_MISCELLANEOUS_IN_STANDBY_ENABLE_MASK;
    }

}
#endif


/* Clock stop section code */
#define MCU_STOP_SEC_CODE
/**
* @violates @ref Clock_Ip_IntOsc_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/*! @}*/

/*******************************************************************************
 * EOF
 ******************************************************************************/
