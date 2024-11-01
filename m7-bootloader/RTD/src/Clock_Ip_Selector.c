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
*   @file       Clock_Ip_Selector.c
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
* @section Clock_Ip_Selector_c_REF_1
* Violates MISRA 2012 Advisory Rule 20.1, #include directives should only be preceded by preprocessor
* directives or comments. AUTOSAR imposes the specification of the sections in which certain parts
* of the driver must be placed.
*
* @section Clock_Ip_Selector_c_REF_2
* Violates MISRA 2012 Advisory Rule 4.8, This file includes the definition
* of types but does not use it. Header is common for all files
*
*/



#include "Clock_Ip_Private.h"

/* Clock start section code */
#define MCU_START_SEC_CODE
/**
* @violates @ref Clock_Ip_Selector_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

static void Callback_SelectorEmpty(Clock_Ip_SelectorConfigType const* config);

#ifdef CGM_X_CSC_CSS_CLK_SW_SWIP
static void ResetCgmXCscCssClkswSwip(Clock_Ip_SelectorConfigType const *config);
static void SetCgmXCscCssClkswSwip(Clock_Ip_SelectorConfigType const *config);
#endif


#ifdef CGM_X_CSC_CSS_CLK_SW_RAMPDOWN_RAMPUP_SWIP
static void ResetCgmXCscCssClkswRampupRampdownSwip(Clock_Ip_SelectorConfigType const *config);
static void SetCgmXCscCssClkswRampupRampdownSwip(Clock_Ip_SelectorConfigType const *config);
#endif

#ifdef CGM_X_CSC_CSS_CS_GRIP
static void SetCgmXCscCssCsGrip(Clock_Ip_SelectorConfigType const *config);
static void ResetCgmXCscCssCsGrip(Clock_Ip_SelectorConfigType const *config);
#endif

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
/**
* @violates @ref Clock_Ip_Selector_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_Selector_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

const selectorCallback selectorCallbacks[SELECTOR_CALLBACKS_COUNT] =
{
    {
        Callback_SelectorEmpty,            /* Reset */
        Callback_SelectorEmpty,            /* Set */
    },
#ifdef CGM_X_CSC_CSS_CLK_SW_SWIP
    {
        ResetCgmXCscCssClkswSwip,          /* Reset */
        SetCgmXCscCssClkswSwip,            /* Set */
    },
#endif

#ifdef CGM_X_CSC_CSS_CLK_SW_RAMPDOWN_RAMPUP_SWIP
    {
        ResetCgmXCscCssClkswRampupRampdownSwip,     /* Reset */
        SetCgmXCscCssClkswRampupRampdownSwip,       /* Set */
    },
#endif

#ifdef CGM_X_CSC_CSS_CS_GRIP
    {
        ResetCgmXCscCssCsGrip,           /* Reset */
        SetCgmXCscCssCsGrip,             /* Set */
    },
#endif
};

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_Selector_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/* Clock start section code */
#define MCU_START_SEC_CODE
/**
* @violates @ref Clock_Ip_Selector_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

static void Callback_SelectorEmpty(Clock_Ip_SelectorConfigType const* config)
{
    (void)config;
    /* No implementation */
}

#ifdef CGM_X_CSC_CSS_CLK_SW_SWIP
static void ResetCgmXCscCssClkswSwip(Clock_Ip_SelectorConfigType const *config)
{

    uint32 instance      = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    uint32 selectorIndex = clockFeatures[config->name][SELECTOR_INDEX];

    cgm[instance][selectorIndex]->CSC |= MC_CGM_MUX_CSC_SAFE_SW_MASK;


    UpdateClockState(config->name, SELECTOR_ENTRY_1);
}
static void SetCgmXCscCssClkswSwip(Clock_Ip_SelectorConfigType const *config)
{

    uint32 instance      = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    uint32 selectorIndex = clockFeatures[config->name][SELECTOR_INDEX];
    uint32 selectorValue = selectorEntry_hardwareValue[config->value];    /* Hw value corresponding to selector entry. Translate input clock source to hardware value. */

    uint32 regValue;
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;

    ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
    do
    {
        TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
    }
    while(((cgm[instance][selectorIndex]->CSS & MC_CGM_MUX_CSS_SWIP_MASK) == MC_CGM_MUX_CSS_SWIP_IN_PROGRESS) && (FALSE == TimeoutOccurred));

    if (FALSE == TimeoutOccurred)
    {
        regValue = cgm[instance][selectorIndex]->CSC;
        regValue &= ~MC_CGM_MUX_CSC_SELCTL_MASK;
        regValue |= MC_CGM_MUX_CSC_SELCTL(selectorValue);
        regValue |= (MC_CGM_MUX_CSC_CLK_SW_MASK);  /* Clock switch operation is requested */
        cgm[instance][selectorIndex]->CSC = regValue;

        ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
        /* Wait for CLK_SW to auto-clear */
        do
        {
            TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }                                                          /* No safe clock switch operation was requested. */
        while(((cgm[instance][selectorIndex]->CSS & MC_CGM_MUX_CSS_CLK_SW_MASK) == MC_CGM_MUX_CSS_CLK_SW_NOT_REQUESTED) && (FALSE == TimeoutOccurred));

        if (FALSE == TimeoutOccurred)
        {
            ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
            /* Wait for acknowledge to be cleared. */
            do
            {
                TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
            }
            while(((cgm[instance][selectorIndex]->CSS & MC_CGM_MUX_CSS_SWIP_MASK) == MC_CGM_MUX_CSS_SWIP_IN_PROGRESS) && (FALSE == TimeoutOccurred) );

            if (FALSE == TimeoutOccurred)
            {
                /* Check the switch status. */
                if (MC_CGM_MUX_CSS_SWTRG_SUCCEEDED != ((cgm[instance][selectorIndex]->CSS & MC_CGM_MUX_CSS_SWTRG_MASK) >> MC_CGM_MUX_0_CSS_SWTRG_SHIFT))
                {
                    ReportClockErrors(CLOCK_IP_REPORT_CLOCK_MUX_SWITCH_ERROR, config->name);
                }
                else
                {
                    UpdateClockState(config->name,
                                    selectorEntryIndex[(cgm[instance][selectorIndex]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT]);
                }
            }
            else
            {
                /* Report timeout error */
                ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, config->name);
            }
        }
        else
        {
            /* Report timeout error */
            ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, config->name);
        }
    }
    else {

        /* Report timeout error */
        ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, config->name);
    }
}
#endif


#ifdef CGM_X_CSC_CSS_CLK_SW_RAMPDOWN_RAMPUP_SWIP
static void ResetCgmXCscCssClkswRampupRampdownSwip(Clock_Ip_SelectorConfigType const *config)
{

    uint32 instance      = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    uint32 selectorIndex = clockFeatures[config->name][SELECTOR_INDEX];

    cgm[instance][selectorIndex]->CSC |= MC_CGM_MUX_CSC_SAFE_SW_MASK;


    UpdateClockState(config->name, SELECTOR_ENTRY_1);
}
static void SetCgmXCscCssClkswRampupRampdownSwip(Clock_Ip_SelectorConfigType const *config)
{

    uint32 instance      = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    uint32 selectorIndex = clockFeatures[config->name][SELECTOR_INDEX];
    uint32 selectorValue = selectorEntry_hardwareValue[config->value];    /* Hw value corresponding to selector entry. Translate input clock source to hardware value. */

    uint32 regValue;
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;

    ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
    do
    {
        TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
    }
    while (((cgm[instance][selectorIndex]->CSS & MC_CGM_MUX_CSS_SWIP_MASK) == MC_CGM_MUX_CSS_SWIP_IN_PROGRESS) && (FALSE == TimeoutOccurred));

    if (FALSE == TimeoutOccurred)
    {
        regValue = cgm[instance][selectorIndex]->CSC;
        regValue &= ~MC_CGM_MUX_CSC_SELCTL_MASK;
        regValue |= MC_CGM_MUX_CSC_SELCTL(selectorValue);
        /* All the PCFS commands should be atomic in nature (i.e. a single register write should provide a complete PCFS sequence
         * to be executed, that is ramp-down, clock switch, and ramp-up. It is necessary to set both RAMPUP and RAMPDOWN bits
         * together even if you want to trigger either RAMPUP or RAMPDOWN process, otherwise the PCFS effect will not manifest. */
        regValue |= (MC_CGM_MUX_CSC_CLK_SW_MASK | MC_CGM_MUX_CSC_RAMPUP_MASK | MC_CGM_MUX_CSC_RAMPDOWN_MASK);
        cgm[instance][selectorIndex]->CSC = regValue;

        ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
        /* Wait for CLK_SW to auto-clear */
        do
        {
            TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }                                                          /* No safe clock switch operation was requested. */
        while(((cgm[instance][selectorIndex]->CSS & MC_CGM_MUX_CSS_CLK_SW_MASK) == MC_CGM_MUX_CSS_CLK_SW_NOT_REQUESTED) && (FALSE == TimeoutOccurred));

        if (FALSE == TimeoutOccurred)
        {
            ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
            /* Wait for acknowledge to be cleared. */
            do
            {
                TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
            }
            while (((cgm[instance][selectorIndex]->CSS & MC_CGM_MUX_CSS_SWIP_MASK) == MC_CGM_MUX_CSS_SWIP_IN_PROGRESS) && (FALSE == TimeoutOccurred) );

            if (FALSE == TimeoutOccurred)
            {
                /* Check the switch status. */
                if (MC_CGM_MUX_CSS_SWTRG_SUCCEEDED != ((cgm[instance][selectorIndex]->CSS & MC_CGM_MUX_CSS_SWTRG_MASK) >> MC_CGM_MUX_CSS_SWTRG_SHIFT))
                {
                    ReportClockErrors(CLOCK_IP_REPORT_CLOCK_MUX_SWITCH_ERROR, config->name);
                }
                else
                {
                    UpdateClockState(config->name,
                                    selectorEntryIndex[(cgm[instance][selectorIndex]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT]);
                }
            }
            else
            {
                /* Report timeout error */
                ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, config->name);
            }
        }
        else
        {
            /* Report timeout error */
            ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, config->name);
        }
    }
    else
    {
        /* Report timeout error */
        ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, config->name);
    }
}
#endif





#ifdef CGM_X_CSC_CSS_CS_GRIP
static void ResetCgmXCscCssCsGrip(Clock_Ip_SelectorConfigType const *config)
{
    (void)config;

    /* Software muxes can't be reset. They don't have SAFE_CLK as selector entry. */
}
static void SetCgmXCscCssCsGrip(Clock_Ip_SelectorConfigType const *config)
{

    uint32 instance      = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    uint32 selectorIndex = clockFeatures[config->name][SELECTOR_INDEX];
    uint32 selectorValue = selectorEntry_hardwareValue[config->value];    /* Hw value corresponding to selector entry. Translate input clock source to hardware value. */

    uint32 regValue;
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;

    /* Check that a different clock source must be set */
    if (selectorValue != ((cgm[instance][selectorIndex]->CSC & MC_CGM_MUX_CSC_SELCTL_MASK) >> MC_CGM_MUX_CSC_SELCTL_SHIFT))
    {
        cgm[instance][selectorIndex]->CSC |= (MC_CGM_MUX_CSC_CG_MASK | MC_CGM_MUX_CSC_FCG_MASK);

        ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
        do
        {
            TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while (((cgm[instance][selectorIndex]->CSS & MC_CGM_MUX_CSS_CS_MASK) == MC_CGM_MUX_CSS_CS_TRANSPARENT) && (FALSE == TimeoutOccurred));

        if (FALSE == TimeoutOccurred)
        {
            /* Configure clock source. */
            regValue = cgm[instance][selectorIndex]->CSC;
            regValue &= ~MC_CGM_MUX_CSC_SELCTL_MASK;
            regValue |= MC_CGM_MUX_CSC_SELCTL(selectorValue);
            cgm[instance][selectorIndex]->CSC = regValue;
            /* Clear CG and FCG bit after set the SELCTL bit */
            cgm[instance][selectorIndex]->CSC &= ~(MC_CGM_MUX_CSC_FCG_MASK | MC_CGM_MUX_CSC_CG_MASK);

            ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
            /* Wait until the output clock is ungated. */
            do
            {
                TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
            }
            while (((cgm[instance][selectorIndex]->CSS & MC_CGM_MUX_CSS_CS_MASK) != MC_CGM_MUX_CSS_CS_TRANSPARENT) && (FALSE == TimeoutOccurred));

            if (TRUE == TimeoutOccurred)
            {
                ReportClockErrors(CLOCK_IP_REPORT_CLOCK_MUX_SWITCH_ERROR, config->name);
            }
            else
            {
                UpdateClockState(config->name,
                                selectorEntryIndex[(cgm[instance][selectorIndex]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT]);
            }
        }
        else
        {
            /* Report timeout error */
            ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, config->name);
        }

    }
}
#endif

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
/**
* @violates @ref Clock_Ip_Selector_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/*! @}*/

/*******************************************************************************
 * EOF
 ******************************************************************************/
