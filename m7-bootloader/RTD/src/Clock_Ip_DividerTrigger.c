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
*   @file       Clock_Ip_DividerTrigger.c
*   @version    1.0.0
*
*   @brief   CLOCK driver implementations.
*   @details CLOCK driver implementations.
*
*   @addtogroup CLOCK_DRIVER_TRIGGER Clock Driver
*   @{
*/


/**
* @page misra_violations MISRA-C:2012 violations
*
* @section Clock_Ip_DividerTrigger_c_REF_1
* Violates MISRA 2012 Advisory Rule 20.1, #include directives should only be preceded by preprocessor
* directives or comments. AUTOSAR imposes the specification of the sections in which certain parts
* of the driver must be placed.
*
* @section Clock_Ip_DividerTrigger_c_REF_2
* Violates MISRA 2012 Advisory Rule 4.8, This file includes the definition
* of types but does not use it. Header is common for all files
*
*/


#include "Clock_Ip_Private.h"

/* Clock start section code */
#define MCU_START_SEC_CODE
/**
* @violates @ref Clock_Ip_DividerTrigger_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"


static void Callback_DividerTriggerEmpty(Clock_Ip_DividerTriggerConfigType const* config);
#ifdef CGM_X_DIV_TRIG_CTRL_TCTL_HHEN_UPD_STAT
static void ConfigureCgmXDivTrigCtrlTctlHhenUpdStat(Clock_Ip_DividerTriggerConfigType const* config);
static void TriggerUpdateCgmXDivTrigCtrlTctlHhenUpdStat(Clock_Ip_DividerTriggerConfigType const* config);
#endif

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
/**
* @violates @ref Clock_Ip_DividerTrigger_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_DividerTrigger_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

const dividerTriggerCallback dividerTriggerCallbacks[DIVIDERTRIGGER_CALLBACKS_COUNT] =
{
    {
        Callback_DividerTriggerEmpty,                  /* Configure */
        Callback_DividerTriggerEmpty,                  /* Trigger Update */
    },
#ifdef CGM_X_DIV_TRIG_CTRL_TCTL_HHEN_UPD_STAT
    {
        ConfigureCgmXDivTrigCtrlTctlHhenUpdStat,           /* Configure */
        TriggerUpdateCgmXDivTrigCtrlTctlHhenUpdStat,       /* Trigger Update */
    },
#endif
};

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_DividerTrigger_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/* Clock start section code */
#define MCU_START_SEC_CODE
/**
* @violates @ref Clock_Ip_DividerTrigger_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

static void Callback_DividerTriggerEmpty(Clock_Ip_DividerTriggerConfigType const* config)
{
    (void)config;
    /* No implementation */
}


#ifdef CGM_X_DIV_TRIG_CTRL_TCTL_HHEN_UPD_STAT
static void ConfigureCgmXDivTrigCtrlTctlHhenUpdStat(Clock_Ip_DividerTriggerConfigType const* config)
{
    uint32 instance      = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    uint32 selectorIndex = clockFeatures[config->name][SELECTOR_INDEX];

    /* Check whether trigger is enabled */
    if (config->triggerType != IMMEDIATE_DIVIDER_UPDATE)
    {
        cgm[instance][selectorIndex]->MUX_DIV_TRIG_CTRL = (MC_CGM_MUX_DIV_TRIG_CTRL_TCTL_MASK);
    }
    else
    {
        cgm[instance][selectorIndex]->MUX_DIV_TRIG_CTRL &= ~(MC_CGM_MUX_DIV_TRIG_CTRL_TCTL_MASK);
    }
}

static void TriggerUpdateCgmXDivTrigCtrlTctlHhenUpdStat(Clock_Ip_DividerTriggerConfigType const* config)
{
    uint32 instance      = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    uint32 selectorIndex = clockFeatures[config->name][SELECTOR_INDEX];

    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 DividerStatus;

    /* Check whether trigger is enabled */
    if (config->triggerType != IMMEDIATE_DIVIDER_UPDATE)
    {
        cgm[instance][selectorIndex]->MUX_DIV_TRIG = MC_CGM_MUX_DIV_TRIG_TRIGGER(TRIGGER_VALUE);

        ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
        /* Wait for acknowledge to be cleared. */
        do
        {
            DividerStatus = (cgm[instance][selectorIndex]->MUX_DIV_UPD_STAT & MC_CGM_MUX_DIV_UPD_STAT_DIV_STAT_MASK);
            TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while ((DividerStatus == MC_CGM_MUX_DIV_UPD_STAT_DIV_STAT_PENDING) && (FALSE == TimeoutOccurred));

        /* timeout notification */
        if (TRUE == TimeoutOccurred)
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
* @violates @ref Clock_Ip_DividerTrigger_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"


/*! @}*/

/*******************************************************************************
 * EOF
 ******************************************************************************/
