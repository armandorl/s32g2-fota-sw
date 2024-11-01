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
*   @file       Clock_Ip_Monitor.c
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
* @section Clock_Ip_Monitor_c_REF_1
* Violates MISRA 2012 Advisory Rule 20.1, #include directives should only be preceded by preprocessor
* directives or comments. AUTOSAR imposes the specification of the sections in which certain parts
* of the driver must be placed.
*
* @section Clock_Ip_Monitor_c_REF_2
* Violates MISRA 2012 Advisory Rule 4.8, This file includes the definition
* of types but does not use it. Header is common for all files
*
*/


#include "Clock_Ip_Private.h"

/* Clock start section code */
#define MCU_START_SEC_CODE
/**
* @violates @ref Clock_Ip_Monitor_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/*  TODO ARTD-738  Implement CMU in Clock_Ip driver    */

static void ClockMonitorEmpty(Clock_Ip_CmuConfigType const* config);
static void ClockMonitorEmpty_Disable(Clock_Ip_NameType name);
static void ClockMonitorEmpty_ClearStatus(Clock_Ip_NameType name);
static Clock_Ip_CmuStatusType ClockMonitorEmpty_GetStatus(Clock_Ip_NameType name);

#ifdef CMU_FC_FCE_REF_CNT_LFREF_HFREF
static void ResetCmuFcFceRefCntLfrefHfref(Clock_Ip_CmuConfigType const* config);
static void SetCmuFcFceRefCntLfrefHfref(Clock_Ip_CmuConfigType const* config);
static void DisableCmuFcFceRefCntLfrefHfref(Clock_Ip_NameType name);
static void ClearStatusCmuFcFceRefCntLfrefHfref(Clock_Ip_NameType name);
static Clock_Ip_CmuStatusType GetStatusCmuFcFceRefCntLfrefHfref(Clock_Ip_NameType name);
#endif
static void Mcu_CMU_ClockFailInt(void);


/* Clock stop section code */
#define MCU_STOP_SEC_CODE
/**
* @violates @ref Clock_Ip_Monitor_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_Monitor_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

const clockMonitorCallback cmuCallbacks[CMU_CALLBACKS_COUNT] =
{
	{
		ClockMonitorEmpty,                /* Reset */
		ClockMonitorEmpty,                /* Set */
		ClockMonitorEmpty_Disable,        /* Disable */
		ClockMonitorEmpty_ClearStatus,    /* Clear */
		ClockMonitorEmpty_GetStatus,      /* Get status */
	},
#ifdef CMU_FC_FCE_REF_CNT_LFREF_HFREF
	{
		ResetCmuFcFceRefCntLfrefHfref,          /* Reset */
		SetCmuFcFceRefCntLfrefHfref,            /* Set */
		DisableCmuFcFceRefCntLfrefHfref,        /* Disable */
		ClearStatusCmuFcFceRefCntLfrefHfref,    /* Clear */
		GetStatusCmuFcFceRefCntLfrefHfref,      /* Get status */
	},
#endif
};

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_Monitor_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"


/* Clock start section code */
#define MCU_START_SEC_CODE
/**
* @violates @ref Clock_Ip_Monitor_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

static void ClockMonitorEmpty(Clock_Ip_CmuConfigType const* config)
{
	(void)config;
	/* No implementation */
}

static void ClockMonitorEmpty_Disable(Clock_Ip_NameType name)
{
	(void)name;
	/* No implementation */
}

static void ClockMonitorEmpty_ClearStatus(Clock_Ip_NameType name)
{
	(void)name;
	/* No implementation */
}

static Clock_Ip_CmuStatusType ClockMonitorEmpty_GetStatus(Clock_Ip_NameType name)
{
	(void)name;
	/* No implementation */
	return CLOCK_IP_CMU_STATUS_UNDEFINED;
}


#ifdef CMU_FC_FCE_REF_CNT_LFREF_HFREF
static void DisableCmuFcFceRefCntLfrefHfref(Clock_Ip_NameType name)
{
    uint32 instance      = clockFeatures[name][CMU_INSTANCE];

    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 FrequencyCheckStatus;

    /* Only disable frequency check if it is enabled */
    if ((cmu[instance]->GCR & CMU_FC_GCR_FCE_MASK) == CMU_FREQUENCY_CHECK_ENABLED)
    {
        ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
        /* Wait for frequency check to be running. */
        do
        {
            FrequencyCheckStatus = (cmu[instance]->SR & CMU_FC_SR_RS_MASK);
            TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while((FrequencyCheckStatus == CMU_FREQUENCY_CHECK_STOPPED) && (!TimeoutOccurred));

        /* timeout notification */
        if (TimeoutOccurred)
		{
			/* Report timeout error */
			ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, name);
		}
        else
        {
            /* Disable frequency check */
            cmu[instance]->GCR &= ~CMU_FC_GCR_FCE_MASK;
        }
    }

    /* Disable interupts */
    cmu[instance]->IER &= ~(CMU_FC_IER_FLLIE_MASK | CMU_FC_IER_FHHIE_MASK | CMU_FC_IER_FLLAIE_MASK | CMU_FC_IER_FHHAIE_MASK);

    /* Reset reference counter */
    cmu[instance]->RCCR = CMU_RESET_COUNTER_VALUE;

    /* Reset high limit */
    cmu[instance]->HTCR = CMU_RESET_HIGH_LIMIT;

    /* Reset high limit */
    cmu[instance]->LTCR = CMU_RESET_LOW_LIMIT;

    /* Clear flags */
    cmu[instance]->SR |= (CMU_FC_SR_FLL_MASK | CMU_FC_SR_FHH_MASK | CMU_FC_SR_RS_MASK);
}

static void ResetCmuFcFceRefCntLfrefHfref(Clock_Ip_CmuConfigType const* config)
{
    DisableCmuFcFceRefCntLfrefHfref(config->name);
}

static void SetCmuFcFceRefCntLfrefHfref(Clock_Ip_CmuConfigType const* config)
{
    uint32 instance      = clockFeatures[config->name][CMU_INSTANCE];
    uint32 swIndex       = clockFeatures[config->name][CMU_SW_INDEX];

    /* Set reference counter */
    cmu[instance]->RCCR = cmuEntries[swIndex].refCount;

    /* Set high limit */
    cmu[instance]->HTCR = cmuEntries[swIndex].hfRef;

    /* Set high limit */
    cmu[instance]->LTCR = cmuEntries[swIndex].lfRef;

    /* Enable/disable interrupts */
    if (config->interrupt != 0U)
    {
        cmu[instance]->IER |= (CMU_FC_IER_FLLIE_MASK | CMU_FC_IER_FHHIE_MASK);
    }
    else
    {
        cmu[instance]->IER &= ~(CMU_FC_IER_FLLIE_MASK | CMU_FC_IER_FHHIE_MASK);
    }

    /* Enable cmu */
    if (config->enable != 0U)
    {
        cmu[instance]->GCR |= CMU_FC_GCR_FCE_MASK;
    }
}

static void ClearStatusCmuFcFceRefCntLfrefHfref(Clock_Ip_NameType name)
{
    uint32 instance      = clockFeatures[name][CMU_INSTANCE];

    uint32 cmuIsrValue;

    /* Read flags */
    cmuIsrValue = cmu[instance]->SR & CMU_ISR_MASK;

    /* Clear flags */
    cmu[instance]->SR = cmuIsrValue;
}

static Clock_Ip_CmuStatusType GetStatusCmuFcFceRefCntLfrefHfref(Clock_Ip_NameType name)
{
    uint32 cmuIerValue, cmuIsrValue;
    Clock_Ip_CmuStatusType status = CLOCK_IP_CMU_STATUS_UNDEFINED;

    uint32 instance      = clockFeatures[name][CMU_INSTANCE];

    /* Read flags */
    cmuIsrValue = cmu[instance]->SR & CMU_ISR_MASK;

    /* Read interrupt enable */
    cmuIerValue = cmu[instance]->IER & CMU_ISR_MASK;

    cmuIsrValue = cmuIsrValue & cmuIerValue;


    /* Gheck flash if frequency check is enabled */
    if ((cmu[instance]->GCR & CMU_FC_GCR_FCE_MASK) == CMU_FREQUENCY_CHECK_ENABLED)
    {
        if ( ( CMU_FC_SR_FHH_MASK == (cmuIsrValue & CMU_FC_SR_FHH_MASK) ) )
        {
            status = CLOCK_IP_CMU_HIGH_FREQ;
        }
        else if ( CMU_FC_SR_FLL_MASK == (cmuIsrValue & CMU_FC_SR_FLL_MASK) )
        {
            status = CLOCK_IP_CMU_LOW_FREQ;
        }
        else
        {
            status = CLOCK_IP_CMU_IN_RANGE;
        }
    }

    return status;

}
#define CMU_IS_NOT_UNDER_MCU_CONTROL 0U

/**
* @brief        This function clear the CMU interrupt flag from CMU module.
* @details      Called by RGM ISR routine when a user notification for CMU FCCU events is configured
*
* @return       void
*
* @implements Mcu_CMU_ClockFailInt_Activity
*
*/
static void Mcu_CMU_ClockFailInt(void)
{
    uint32 cmuIerValue, cmuIsrValue, instance, indexCmuEntry;
    const Clock_Ip_ClockConfigType* const clockCfg = GetClockConfig();
    const Clock_Ip_CmuConfigType *cmuConfig;

    for (indexCmuEntry = 0U; indexCmuEntry < CMU_ENTRIES_NO; indexCmuEntry++)
    {
        if (cmuEntries[indexCmuEntry].configIndex != CMU_IS_NOT_UNDER_MCU_CONTROL)
        {
            cmuConfig = &clockCfg->cmus[cmuEntries[indexCmuEntry].configIndex - 1U];
            instance      = clockFeatures[cmuConfig->name][CMU_INSTANCE];

            /* Read flags */
            cmuIsrValue = cmu[instance]->SR & CMU_ISR_MASK;

            /* Clear status flag */
            cmu[instance]->SR = cmuIsrValue;

            /* Read interrupt enable */
            cmuIerValue = cmu[instance]->IER & CMU_ISR_MASK;

            /* Filter all interrupts that are not enabled from cmuIsrValue */
            cmuIsrValue = cmuIsrValue & cmuIerValue;

            /* If at least one interrupt has been triggered */
            if (cmuIsrValue != 0U)
            {
                ReportClockErrors(CLOCK_IP_CMU_NOTIFICATION, cmuConfig->name);
            }
        }
    }
}

/**
* @brief        This function clear the CMU interrupt flag from CMU module.
* @details      Called by RGM ISR routine when a user notification for CMU FCCU events is configured
*
* @return       void
*
*/
ISR(Mcu_Cmu_ClockFailIsr)
{
    Mcu_CMU_ClockFailInt();
}

#endif

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
/**
* @violates @ref Clock_Ip_Monitor_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/*! @}*/

/*******************************************************************************
 * EOF
 ******************************************************************************/

