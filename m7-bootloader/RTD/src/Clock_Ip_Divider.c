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
*   @file       Clock_Ip_Divider.c
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
* @section Clock_Ip_Divider_c_REF_1
* Violates MISRA 2012 Advisory Rule 20.1, #include directives should only be preceded by preprocessor
* directives or comments. AUTOSAR imposes the specification of the sections in which certain parts
* of the driver must be placed.
*
* @section Clock_Ip_Divider_c_REF_2
* Violates MISRA 2012 Advisory Rule 4.8, This file includes the definition
* of types but does not use it. Header is common for all files
*
*/

#include "Clock_Ip_Private.h"

/* Clock start section code */
#define MCU_START_SEC_CODE
/**
* @violates @ref Clock_Ip_Divider_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"


static void Callback_DividerEmpty(Clock_Ip_DividerConfigType const* config);
#ifdef CGM_X_DE_DIV_STAT_WITHOUT_PHASE
static void SetCgmXDeDivStatWithoutPhase(Clock_Ip_DividerConfigType const* config);
#endif
#ifdef CGM_X_DE_DIV_WITHOUT_PHASE
static void SetCgmXDeDivWithoutPhase(Clock_Ip_DividerConfigType const* config);
#endif
#ifdef CGM_X_DE_DIV_STAT_WITH_PHASE
static void SetCgmXDeDivStatWithPhase(Clock_Ip_DividerConfigType const* config);
#endif
#ifdef PLLDIG_PLL0DIV_DE_DIV_OUTPUT
static void SetPlldigPll0divDeDivOutput(Clock_Ip_DividerConfigType const* config);
#endif
#ifdef PLL_PLL0DIV_DE_DIV_OUTPUT
static void SetPllPll0divDeDivOutput(Clock_Ip_DividerConfigType const* config);
#endif
#ifdef PLL_PLLDV_ODIV2_OUTPUT
static void SetPllPlldvOdiv2Output(Clock_Ip_DividerConfigType const* config);
#endif

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
/**
* @violates @ref Clock_Ip_Divider_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_Divider_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

const dividerCallback dividerCallbacks[DIVIDER_CALLBACKS_COUNT] =
{
    {
        Callback_DividerEmpty,                  /* Set */
    },
#ifdef CGM_X_DE_DIV_STAT_WITHOUT_PHASE
    {
        SetCgmXDeDivStatWithoutPhase,           /* Set */
    },
#endif
#ifdef CGM_X_DE_DIV_WITHOUT_PHASE
    {
        SetCgmXDeDivWithoutPhase,               /* Set */
    },
#endif
#ifdef CGM_X_DE_DIV_STAT_WITH_PHASE
    {
        SetCgmXDeDivStatWithPhase,              /* Set */
    },
#endif
#ifdef PLLDIG_PLL0DIV_DE_DIV_OUTPUT
    {
        SetPlldigPll0divDeDivOutput,            /* Set */
    },
#endif
#ifdef PLL_PLL0DIV_DE_DIV_OUTPUT
    {
        SetPllPll0divDeDivOutput,               /* Set */
    },
#endif
#ifdef PLL_PLLDV_ODIV2_OUTPUT
    {
        SetPllPlldvOdiv2Output,                /* Set */
    },
#endif
};

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_Divider_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
/* Clock start section code */
/**
* @violates @ref Clock_Ip_Divider_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

static void Callback_DividerEmpty(Clock_Ip_DividerConfigType const* config)
{
    (void)config;
    /* No implementation */
}

#ifdef CGM_X_DE_DIV_STAT_WITHOUT_PHASE
static void SetCgmXDeDivStatWithoutPhase(Clock_Ip_DividerConfigType const* config)
{
    uint32 instance      = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    uint32 selectorIndex = clockFeatures[config->name][SELECTOR_INDEX];
    uint32 dividerIndex  = clockFeatures[config->name][DIVIDER_INDEX];
    uint32 triggerFeat   = clockFeatures[config->name][TRIGGER_FEATURE];
    uint32 regValue;
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 DividerStatus;

    boolean immediateTriggerIsUpdated = TRUE;

    /* Program divider value */
    if (config->value != 0U)  {
        regValue = cgm[instance][selectorIndex]->divider[dividerIndex];
        regValue &= ~MC_CGM_MUX_DC_DIV_MASK;
        regValue |= MC_CGM_MUX_DC_DIV(config->value-1U);
        cgm[instance][selectorIndex]->divider[dividerIndex] = regValue;
    }

#if defined(MC_CGM_MUX_DIV_TRIG_CTRL_COMMON_TRIGGER_DIVIDER_UPDATE)
    if (triggerFeat == TRIGGER)
    {
        /* Common update is triggered. */
        if ((cgm[instance][selectorIndex]->MUX_DIV_TRIG_CTRL & MC_CGM_MUX_DIV_TRIG_CTRL_TCTL_MASK) == MC_CGM_MUX_DIV_TRIG_CTRL_COMMON_TRIGGER_DIVIDER_UPDATE)
        {
            immediateTriggerIsUpdated = FALSE;
        }
    }
#endif

    /* Immediate update is triggered. */
    if (TRUE == immediateTriggerIsUpdated)
    {
        ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
        /* Wait for acknowledge to be cleared. */
        do
        {
            DividerStatus = (cgm[instance][selectorIndex]->MUX_DIV_UPD_STAT & MC_CGM_MUX_DIV_UPD_STAT_DIV_STAT_MASK);
            TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while ((DividerStatus == MC_CGM_MUX_DIV_UPD_STAT_DIV_STAT_PENDING) && (FALSE == TimeoutOccurred));
    }

    if (FALSE == TimeoutOccurred)
    {
        /* Enable or Disable the Clock Divider */
        if (config->value != 0U)
        {
            /* Enable divider */
            cgm[instance][selectorIndex]->divider[dividerIndex] |= MC_CGM_MUX_DC_DE_MASK;

            if (DISABLED_CLOCK == GetClockState(config->name))
            {
                UpdateClockState(config->name, ENABLED_CLOCK);
            }
        }
        else
        {
            cgm[instance][selectorIndex]->divider[dividerIndex] &= ~MC_CGM_MUX_DC_DE_MASK;
            UpdateClockState(config->name, DISABLED_CLOCK);
        }
    }
    else
    {
        /* Report timeout error */
        ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, config->name);
    }
}
#endif


#ifdef CGM_X_DE_DIV_WITHOUT_PHASE
static void SetCgmXDeDivWithoutPhase(Clock_Ip_DividerConfigType const* config)
{


    uint32 instance      = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    uint32 selectorIndex = clockFeatures[config->name][SELECTOR_INDEX];
    uint32 dividerIndex  = clockFeatures[config->name][DIVIDER_INDEX];

    uint32 regValue;

    /* Program divider value */
    if (config->value != 0U)  {
        regValue = cgm[instance][selectorIndex]->divider[dividerIndex];
        regValue &= ~MC_CGM_MUX_DC_DIV_MASK;
        regValue |= MC_CGM_MUX_DC_DIV(config->value-1U);
        cgm[instance][selectorIndex]->divider[dividerIndex] = regValue;
    }

    /* Enable or Disable the Clock Divider */
    if (config->value != 0U)
    {
        /* Enable divider */
        cgm[instance][selectorIndex]->divider[dividerIndex] |= MC_CGM_MUX_DC_DE_MASK;

        if (DISABLED_CLOCK == GetClockState(config->name))
        {
            UpdateClockState(config->name, ENABLED_CLOCK);
        }
    }
    else
    {
        cgm[instance][selectorIndex]->divider[dividerIndex] &= ~MC_CGM_MUX_DC_DE_MASK;
        UpdateClockState(config->name, DISABLED_CLOCK);
    }
}
#endif


#ifdef CGM_X_DE_DIV_STAT_WITH_PHASE
static void SetCgmXDeDivStatWithPhase(Clock_Ip_DividerConfigType const* config)
{


    uint32 instance      = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    uint32 selectorIndex = clockFeatures[config->name][SELECTOR_INDEX];
    uint32 dividerIndex  = clockFeatures[config->name][DIVIDER_INDEX];
    uint32 triggerFeat   = clockFeatures[config->name][TRIGGER_FEATURE];
    uint32 regValue;
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 DividerStatus;

    boolean immediateTriggerIsUpdated = TRUE;

    /* Program divider value */
    if (config->value != 0U)  {
        regValue = cgm[instance][selectorIndex]->divider[dividerIndex];
        regValue &= ~MC_CGM_MUX_DC_DIV_MASK;
        regValue |= MC_CGM_MUX_DC_DIV(config->value-1U);
        cgm[instance][selectorIndex]->divider[dividerIndex] = regValue;
    }

#if defined(MC_CGM_MUX_DIV_TRIG_CTRL_COMMON_TRIGGER_DIVIDER_UPDATE)
    if (triggerFeat == TRIGGER)
    {
        /* Common update is triggered. */
        if ((cgm[instance][selectorIndex]->MUX_DIV_TRIG_CTRL & MC_CGM_MUX_DIV_TRIG_CTRL_TCTL_MASK) == MC_CGM_MUX_DIV_TRIG_CTRL_COMMON_TRIGGER_DIVIDER_UPDATE)
        {
            immediateTriggerIsUpdated = FALSE;
        }
    }
#endif

    /* Immediate update is triggered. */
    if (TRUE == immediateTriggerIsUpdated)
    {
        ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
        /* Wait for acknowledge to be cleared. */
        do
        {
            DividerStatus = (cgm[instance][selectorIndex]->MUX_DIV_UPD_STAT & MC_CGM_MUX_DIV_UPD_STAT_DIV_STAT_MASK);
            TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while ((DividerStatus == MC_CGM_MUX_DIV_UPD_STAT_DIV_STAT_PENDING) && (FALSE == TimeoutOccurred));
    }

    if (FALSE == TimeoutOccurred)
    {
        /* Update phase value */

        /* Disable clock to update phase */
        cgm[instance][selectorIndex]->divider[dividerIndex] &= ~MC_CGM_MUX_DC_DE_MASK;
        UpdateClockState(config->name, DISABLED_CLOCK);

        ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
        /* Wait for the divider update to complete. */
        do
        {
            DividerStatus = (cgm[instance][selectorIndex]->MUX_DIV_UPD_STAT & MC_CGM_MUX_DIV_UPD_STAT_DIV_STAT_MASK);
            TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while ((DividerStatus == MC_CGM_MUX_DIV_UPD_STAT_DIV_STAT_PENDING) && (FALSE == TimeoutOccurred));

        if (FALSE == TimeoutOccurred)
        {
            /* We should now wait for at least one division cycle as per the existing programmed DIV value. */
            /* However, a register write sequence operation will take MUCH longer than one division cycle. */
            /* Therefore, there is no need to perform an explicit wait. */
            regValue = cgm[instance][selectorIndex]->divider[dividerIndex];
            regValue &= ~MC_CGM_MUX_DC_PHASE_MASK;
            regValue |= MC_CGM_MUX_DC_PHASE(config->options[0U]);
            cgm[instance][selectorIndex]->divider[dividerIndex] = regValue;
        }
        else
        {
            /* Report timeout error */
            ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, config->name);
        }

        /* Enable Clock Divider */
        if (config->value != 0U)
        {
            cgm[instance][selectorIndex]->divider[dividerIndex] |= MC_CGM_MUX_DC_DE_MASK;
            if (DISABLED_CLOCK == GetClockState(config->name))
            {
                UpdateClockState(config->name, ENABLED_CLOCK);
            }
        }
    }
    else
    {
        /* Report timeout error */
        ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, config->name);
    }
}
#endif


#ifdef PLLDIG_PLL0DIV_DE_DIV_OUTPUT
static void SetPlldigPll0divDeDivOutput(Clock_Ip_DividerConfigType const* config)
{

    uint32 instance      = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    uint32 dividerIndex  = clockFeatures[config->name][DIVIDER_INDEX];
    uint32 regValue;

    /* Disable divider */
    pll[instance]->PLLODIV[dividerIndex] &= ~PLLDIG_PLLODIV_DE_MASK;
    /* Check if divider is enabled */
    if (config->value != 0U)
    {
        regValue = pll[instance]->PLLODIV[dividerIndex];
        regValue |= PLLDIG_PLLODIV_DE_MASK;
        regValue &= ~PLLDIG_PLLODIV_DIV_MASK;
        regValue |= PLLDIG_PLLODIV_DIV(config->value - 1U);
        pll[instance]->PLLODIV[dividerIndex] = regValue;

        if (DISABLED_CLOCK == GetClockState(config->name))
        {
            UpdateClockState(config->name, ENABLED_CLOCK);
        }
    }
    else
    {
        UpdateClockState(config->name, DISABLED_CLOCK);
    }
}
#endif

#ifdef PLL_PLL0DIV_DE_DIV_OUTPUT
static void SetPllPll0divDeDivOutput(Clock_Ip_DividerConfigType const* config)
{
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 instance      = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    uint32 dividerIndex  = clockFeatures[config->name][DIVIDER_INDEX];
    uint32 regValue;

    /* Check clock status for PLL device */
    if ((MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK56_MASK) == 0U)
    {
        /* Enable clock for PLL device */
        MC_ME->PRTN1_COFB1_CLKEN |= MC_ME_PRTN1_COFB1_CLKEN_REQ56(1U);   /* REQ56: Frequency Modulated Phase-Locked Loop */
        MC_ME->PRTN1_PCONF       |= MC_ME_PRTN1_PCONF_PCE_MASK;          /* PCE=1: Enable the clock to Partition #1 */
        MC_ME->PRTN1_PUPD        |= MC_ME_PRTN1_PUPD_PCUD_MASK;          /* PCUD=1: Trigger the hardware process */
        MC_ME->CTL_KEY = 0x5AF0;                                         /* Enter key */
        MC_ME->CTL_KEY = 0xA50F;                                         /* Enter inverted key */
        /* Wait until PLL clock is running */
        ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
        do
        {
            TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while (((MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK56_MASK) == 0U) && (FALSE == TimeoutOccurred));
        /* timeout notification */
        if (TRUE == TimeoutOccurred)
        {
            /* Report timeout error */
            ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, config->name);
        }
    }

    /* Disable divider */
    pll[instance]->PLLODIV[dividerIndex] &= ~PLL_PLLODIV_DE_MASK;
    /* Check if divider is enabled */
    if (config->value != 0U)
    {
        regValue = pll[instance]->PLLODIV[dividerIndex];
        regValue |= PLL_PLLODIV_DE_MASK;
        regValue &= ~PLL_PLLODIV_DIV_MASK;
        regValue |= PLL_PLLODIV_DIV(config->value - 1U);
        pll[instance]->PLLODIV[dividerIndex] = regValue;

        if (DISABLED_CLOCK == GetClockState(config->name))
        {
            UpdateClockState(config->name, ENABLED_CLOCK);
        }
    }
    else
    {
        UpdateClockState(config->name, DISABLED_CLOCK);
    }
}
#endif

#ifdef PLL_PLLDV_ODIV2_OUTPUT
static void SetPllPlldvOdiv2Output(Clock_Ip_DividerConfigType const* config)
{
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 instance      = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    uint32 regValue, dividerValue;

    /* Check clock status for PLL device */
    if ((MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK56_MASK) == 0U)
    {
        /* Enable clock for PLL device */
        MC_ME->PRTN1_COFB1_CLKEN |= MC_ME_PRTN1_COFB1_CLKEN_REQ56(1U);   /* REQ56: Frequency Modulated Phase-Locked Loop */
        MC_ME->PRTN1_PCONF       |= MC_ME_PRTN1_PCONF_PCE_MASK;          /* PCE=1: Enable the clock to Partition #1 */
        MC_ME->PRTN1_PUPD        |= MC_ME_PRTN1_PUPD_PCUD_MASK;          /* PCUD=1: Trigger the hardware process */
        MC_ME->CTL_KEY = 0x5AF0;                                         /* Enter key */
        MC_ME->CTL_KEY = 0xA50F;                                         /* Enter inverted key */
        /* Wait until PLL clock is running */
        ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
        do
        {
            TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while(((MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK56_MASK) == 0U) && (!TimeoutOccurred));
        /* timeout notification */
        if (TimeoutOccurred)
        {
            /* Report timeout error */
            ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, config->name);
        }
    }

    dividerValue = (config->value != 0U) ? config->value : 1U;

    regValue = pll[instance]->PLLDV;
    regValue &= ~PLL_PLLDV_ODIV2_MASK;
    regValue |= PLL_PLLDV_ODIV2(dividerValue);
    pll[instance]->PLLDV = regValue;

    UpdateClockState(config->name, ENABLED_CLOCK);
}
#endif



/* Clock stop section code */
#define MCU_STOP_SEC_CODE
/**
* @violates @ref Clock_Ip_Divider_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/*! @}*/

/*******************************************************************************
 * EOF
 ******************************************************************************/
