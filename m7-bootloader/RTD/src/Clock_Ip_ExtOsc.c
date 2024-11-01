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
*   @file       Clock_Ip_ExtOsc.c
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
* @section Clock_Ip_ExtOsc_c_REF_1
* Violates MISRA 2012 Advisory Rule 20.1, #include directives should only be preceded by preprocessor
* directives or comments. AUTOSAR imposes the specification of the sections in which certain parts
* of the driver must be placed.
*
* @section Clock_Ip_ExtOsc_c_REF_2
* Violates MISRA 2012 Advisory Rule 4.8, This file includes the definition
* of types but does not use it. Header is common for all files
*
*/

#include "Clock_Ip_Private.h"

/* Clock start section code */
#define MCU_START_SEC_CODE
/**
* @violates @ref Clock_Ip_ExtOsc_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"


static void ExternalOscillatorEmpty(Clock_Ip_XoscConfigType const* config);
#ifdef FXOSC_OSCON_BYP_EOCV_GM_SEL
static void ResetFxoscOsconBypEocvGmSel(Clock_Ip_XoscConfigType const* config);
static void SetFxoscOsconBypEocvGmSel(Clock_Ip_XoscConfigType const* config);
#endif
static void ExternalOscillatorEmpty(Clock_Ip_XoscConfigType const* config);
#ifdef SXOSC_OSCON_EOCV
static void ResetSxoscOsconEocv(Clock_Ip_XoscConfigType const* config);
static void SetSxoscOsconEocv(Clock_Ip_XoscConfigType const* config);
#endif

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
/**
* @violates @ref Clock_Ip_ExtOsc_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_ExtOsc_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

const extOscCallback extOscCallbacks[XOSC_CALLBACKS_COUNT] =
{
    {
        ExternalOscillatorEmpty,        /* Reset */
        ExternalOscillatorEmpty,        /* Set */
    },
#ifdef FXOSC_OSCON_BYP_EOCV_GM_SEL
    {
        ResetFxoscOsconBypEocvGmSel,        /* Reset */
        SetFxoscOsconBypEocvGmSel,          /* Set */
    },
#endif
#ifdef SXOSC_OSCON_EOCV
    {
        ResetSxoscOsconEocv,           /* Reset */
        SetSxoscOsconEocv,             /* Set */
    },
#endif
};

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_ExtOsc_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/* Clock start section code */
#define MCU_START_SEC_CODE
/**
* @violates @ref Clock_Ip_ExtOsc_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

static void ExternalOscillatorEmpty(Clock_Ip_XoscConfigType const* config)
{
    (void)config;
    /* No implementation */
}

#ifdef FXOSC_OSCON_BYP_EOCV_GM_SEL
static void ResetFxoscOsconBypEocvGmSel(Clock_Ip_XoscConfigType const* config)
{
    uint32 instance = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];

    uint32 partition      = clockFeatures[config->name][PARTITION_INDEX];
    uint32 collection     = clockFeatures[config->name][COLLECTION_INDEX];
    uint32 enableRequest  = clockFeatures[config->name][ENABLE_REQUEST];

    bool isGatedInMcMe = TRUE;

    (void)partition;
    (void)collection;
    (void)enableRequest;

    /* FXOSC supports clock gate in MC_ME */
    if ((partition != INV_VAL) && (collection != INV_VAL) && (enableRequest != INV_VAL))
    {
        /* Check clock status for FXOSC */
        if ((mcmeGetPartitions[partition]->PRTN_COFB_STAT[collection] & (1UL << enableRequest)) != 0U)
        {
            isGatedInMcMe = FALSE;
        }
    }
    else
    {
        /* FXOSC doesn't support clock gate in MC_ME, so is not gated. */
        isGatedInMcMe = FALSE;
    }

    if (isGatedInMcMe == FALSE)
    {
        /* Disable FXOSC */
        xosc[instance]->CTRL &= ~FXOSC_CTRL_OSCON_MASK;
    }

    UpdateClockState(config->name, DISABLED_CLOCK);
}
static void SetFxoscOsconBypEocvGmSel(Clock_Ip_XoscConfigType const* config)
{
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 FxoscStatus;
    uint32 instance = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];

    uint32 partition      = clockFeatures[config->name][PARTITION_INDEX];
    uint32 collection     = clockFeatures[config->name][COLLECTION_INDEX];
    uint32 enableRequest  = clockFeatures[config->name][ENABLE_REQUEST];


    (void)partition;
    (void)collection;
    (void)enableRequest;

    if (config->enable != 0U)
    {
        /* FXOSC supports clock gate in MC_ME */
        if ((partition != INV_VAL) && (collection != INV_VAL) && (enableRequest != INV_VAL))
        {
            /* Check clock status for FXOSC */
            if ((mcmeGetPartitions[partition]->PRTN_COFB_STAT[collection] & (1UL << enableRequest)) == 0U)
            {
                /* Enable clock for FXOSC device */
                mcmeSetPartitions[partition]->PRTN_COFB_CLKEN[collection] |= (1UL << enableRequest);
                mcmeTriggerPartitions[partition]->PRTN_PCONF  |= MC_ME_PRTN1_PCONF_PCE_MASK;
                mcmeTriggerPartitions[partition]->PRTN_PUPD   |= MC_ME_PRTN1_PUPD_PCUD_MASK;
                McMeEnterKey();
                /* Wait until clock gate is updated */
                ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
                do
                {
                    TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
                }
                while (((mcmeGetPartitions[partition]->PRTN_COFB_STAT[collection] & (1UL << enableRequest)) == 0U) && (FALSE == TimeoutOccurred));
                /* timeout notification */
                if (TRUE == TimeoutOccurred)
                {
                    /* Report timeout error */
                    ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, config->name);
                }
            }
        }

        xosc[instance]->CTRL =
           (
            FXOSC_CTRL_OSCON(1U)                                                |
            FXOSC_CTRL_OSC_BYP(config->bypassOption)                            |
            FXOSC_CTRL_EOCV(config->startupDelay)                               |
            FXOSC_CTRL_GM_SEL(config->transConductance)                         |
            FXOSC_CTRL_COMP_EN(config->compEn)
           );

        /* This assumes that FXOSC_CTRL[COMP_EN] = 1 and FXOSC_CTRL[OSC_BYP] = 0 (i.e. crystal clock/oscillator output). */
        /* In bypass mode (i.e. EXTAL output), FXOSC_CTRL[COMP_EN] = 0 and FXOSC_CTRL[OSC_BYP] = 1, which means that
           we cannot check for stabilization. This shifts the responsibility of waiting for a stable clock to the
           upper layers. */
        if (config->compEn != 0U)
        {
            if (config->bypassOption == 0U)
            {
                ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
                /* Wait until xosc is locked */
                do
                {
                    Clock_Ip_TimeDelay();
                    FxoscStatus = ((xosc[instance]->STAT & FXOSC_STAT_OSC_STAT_MASK) >> FXOSC_STAT_OSC_STAT_SHIFT);
                    TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
                }
                while ((FxoscStatus == 0U) && (FALSE == TimeoutOccurred));

                if (FALSE == TimeoutOccurred)
                {
                    UpdateClockState(config->name, ENABLED_CLOCK);
                }
                else
                {
                    /* Report timeout error */
                    ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, config->name);
                }
            }
            else
            {
                /* Invalid FXOSC configuration: FXOSC_CTRL[COMP_EN] = 1 enforces FXOSC_CTRL[OSC_BYP] = 0. */
                /* Report timeout error */
                ReportClockErrors(CLOCK_IP_REPORT_FXOSC_CONFIGURATION_ERROR, config->name);
            }
        }
    }
}
#endif

#ifdef SXOSC_OSCON_EOCV
static void ResetSxoscOsconEocv(Clock_Ip_XoscConfigType const* config)
{
    uint32 instance = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];

    uint32 partition      = clockFeatures[config->name][PARTITION_INDEX];
    uint32 collection     = clockFeatures[config->name][COLLECTION_INDEX];
    uint32 enableRequest  = clockFeatures[config->name][ENABLE_REQUEST];

    (void)mcmeSetPartitions;
    (void)mcmeGetPartitions;
    (void)mcmeTriggerPartitions;
    (void)partition;
    (void)collection;
    (void)enableRequest;

    if ((partition != INV_VAL) && (collection != INV_VAL) && (enableRequest != INV_VAL))
    {
        /* Check clock status for SXOSC */
        if ((mcmeGetPartitions[partition]->PRTN_COFB_STAT[collection] & (1UL << enableRequest)) != 0U)
        {
            /* Disable SXOSC */
            xosc[instance]->CTRL &= ~FXOSC_CTRL_OSCON_MASK;
        }
    }

    UpdateClockState(config->name, DISABLED_CLOCK);
}
static void SetSxoscOsconEocv(Clock_Ip_XoscConfigType const* config)
{
    uint32 instance = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 SxoscStatus;

    uint32 partition      = clockFeatures[config->name][PARTITION_INDEX];
    uint32 collection     = clockFeatures[config->name][COLLECTION_INDEX];
    uint32 enableRequest  = clockFeatures[config->name][ENABLE_REQUEST];

    (void)partition;
    (void)collection;
    (void)enableRequest;

    if (config->enable != 0U)
    {
        if ((partition != INV_VAL) && (collection != INV_VAL) && (enableRequest != INV_VAL))
        {
            /* Check clock status for SXOSC */
            if ((mcmeGetPartitions[partition]->PRTN_COFB_STAT[collection] & (1UL << enableRequest)) == 0U)
            {
                /* Enable clock for SXOSC device */
                mcmeSetPartitions[partition]->PRTN_COFB_CLKEN[collection] |= (1UL << enableRequest);
                mcmeTriggerPartitions[partition]->PRTN_PCONF  |= MC_ME_PRTN1_PCONF_PCE_MASK;
                mcmeTriggerPartitions[partition]->PRTN_PUPD   |= MC_ME_PRTN1_PUPD_PCUD_MASK;
                McMeEnterKey();
                /* Wait until clock gate is updated */
                ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
                do
                {
                    TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
                }
                while (((mcmeGetPartitions[partition]->PRTN_COFB_STAT[collection] & (1UL << enableRequest)) == 0U) && (FALSE == TimeoutOccurred));
                /* timeout notification */
                if (TRUE == TimeoutOccurred)
                {
                    /* Report timeout error */
                    ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, config->name);
                }
            }
        }

        xosc[instance]->CTRL =
           (SXOSC_SXOSC_CTRL_OSCON(1U)                                                |
            SXOSC_SXOSC_CTRL_EOCV(config->startupDelay)
           );

        ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
        /* Wait until xosc is locked */
        do
        {
            Clock_Ip_TimeDelay();
            SxoscStatus = ((xosc[instance]->STAT & SXOSC_SXOSC_STAT_OSC_STAT_MASK) >> SXOSC_SXOSC_STAT_OSC_STAT_SHIFT);
            TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while ((SxoscStatus == 0U) && (FALSE == TimeoutOccurred));

        if (FALSE == TimeoutOccurred)
        {
            UpdateClockState(config->name, ENABLED_CLOCK);
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
* @violates @ref Clock_Ip_ExtOsc_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/*! @}*/

/*******************************************************************************
 * EOF
 ******************************************************************************/
