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
*   @file       Clock_Ip_Pll.c
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
* @section Clock_Ip_Pll_c_REF_1
* Violates MISRA 2012 Advisory Rule 20.1, #include directives should only be preceded by preprocessor
* directives or comments. AUTOSAR imposes the specification of the sections in which certain parts
* of the driver must be placed.
*
* @section Clock_Ip_Pll_c_REF_2
* Violates MISRA 2012 Advisory Rule 4.8, This file includes the definition
* of types but does not use it. Header is common for all files
*
*/


#include "Clock_Ip_Private.h"

/* Clock start section code */
#define MCU_START_SEC_CODE
/**
* @violates @ref Clock_Ip_Pll_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

static void Callback_PllEmpty(Clock_Ip_PllConfigType const* config);
static clock_pll_status_t Callback_PllEmptyComplete(Clock_Ip_PllConfigType const* config);
#ifdef PLLDIG_RDIV_MFI_MFN_SDMEN_SSCGBYP_SPREADCTL_STEPNO_STEPSIZE
static void ResetPlldigRdivMfiMfnSdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* config);
static void SetPlldigRdivMfiMfnSdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* config);
static clock_pll_status_t CompletePlldigRdivMfiMfnSdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* config);
#endif
#ifdef PLLDIG_RDIV_MFI_MFN_SDMEN
static void ResetPlldigRdivMfiMfnSdmen(Clock_Ip_PllConfigType const* config);
static void SetPlldigRdivMfiMfnSdmen(Clock_Ip_PllConfigType const* config);
static clock_pll_status_t CompletePlldigRdivMfiMfnSdmen(Clock_Ip_PllConfigType const* config);
#endif
#ifdef PLL_RDIV_MFI_MFN_ODIV2_SDMEN_SSCGBYP_SPREADCTL_STEPNO_STEPSIZE
static void ResetPllRdivMfiMfnOdiv2SdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* config);
static void SetPllRdivMfiMfnOdiv2SdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* config);
static clock_pll_status_t CompletePllRdivMfiMfnOdiv2SdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* config);
#endif

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
/**
* @violates @ref Clock_Ip_Pll_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_Pll_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

const pllCallback pllCallbacks[PLL_CALLBACKS_COUNT] =
{
    {
        Callback_PllEmpty,            /* Reset */
        Callback_PllEmpty,            /* Set */
        Callback_PllEmptyComplete,    /* Complete */
    },
    /* Pll with frequency modulation */
#ifdef PLLDIG_RDIV_MFI_MFN_SDMEN_SSCGBYP_SPREADCTL_STEPNO_STEPSIZE
    {
        ResetPlldigRdivMfiMfnSdmenSsscgbypSpreadctlStepnoStepsize,              /* Reset */
        SetPlldigRdivMfiMfnSdmenSsscgbypSpreadctlStepnoStepsize,                /* Set */
        CompletePlldigRdivMfiMfnSdmenSsscgbypSpreadctlStepnoStepsize,           /* Complete */
    },
#endif
    /* Pll without frequency modulation */
#ifdef PLLDIG_RDIV_MFI_MFN_SDMEN
    {
        ResetPlldigRdivMfiMfnSdmen,          /* Reset */
        SetPlldigRdivMfiMfnSdmen,            /* Set */
        CompletePlldigRdivMfiMfnSdmen,       /* Complete */
    },
#endif
    /* Pll with frequency modulation and VCO clock post divider for driving the PHI output clocks */
#ifdef PLL_RDIV_MFI_MFN_ODIV2_SDMEN_SSCGBYP_SPREADCTL_STEPNO_STEPSIZE
	{
			ResetPllRdivMfiMfnOdiv2SdmenSsscgbypSpreadctlStepnoStepsize,              /* Reset */
			SetPllRdivMfiMfnOdiv2SdmenSsscgbypSpreadctlStepnoStepsize,                /* Set */
			CompletePllRdivMfiMfnOdiv2SdmenSsscgbypSpreadctlStepnoStepsize,           /* Complete */
	},
#endif
};


/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_Pll_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

#define MCU_START_SEC_CODE
/* Clock start section code */
/**
* @violates @ref Clock_Ip_Pll_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"


static void Callback_PllEmpty(Clock_Ip_PllConfigType const* config)
{
    (void)config;
    /* No implementation */
}
static clock_pll_status_t Callback_PllEmptyComplete(Clock_Ip_PllConfigType const* config)
{
    (void)config;
    /* No implementation */
    return STATUS_PLL_NOT_ENABLED;
}

/* Pll with frequency modulation */
#ifdef PLLDIG_RDIV_MFI_MFN_SDMEN_SSCGBYP_SPREADCTL_STEPNO_STEPSIZE
static void ResetPlldigRdivMfiMfnSdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* config)
{

    uint32 instance = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];

    /* Power down PLL */
    pll[instance]->PLLCR |= PLLDIG_PLLCR_PLLPD_MASK;
    UpdateClockState(config->name, DISABLED_CLOCK);
}
static void SetPlldigRdivMfiMfnSdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* config)
{
    uint32 instance = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    uint32 value;

    if (config->enable != 0U)
    {
        /* Select input reference. */
        pll[instance]->PLLCLKMUX = PLLDIG_PLLCLKMUX_REFCLKSEL(config->inputReference);

        /* Configure PLL: predivider and multiplier */
        value = (uint32) (PLLDIG_PLLDV_RDIV(config->predivider)   |
                            PLLDIG_PLLDV_MFI(config->mulFactorDiv));
        pll[instance]->PLLDV = value;

        /* Set numerator fractional loop divider and sigma delta modulation */
        value = pll[instance]->PLLFD;
        value &= ~(PLLDIG_PLLFD_MFN_MASK | PLLDIG_PLLFD_SDMEN_MASK);
        value |=  PLLDIG_PLLFD_MFN(config->numeratorFracLoopDiv);
        value |= PLLDIG_PLLFD_SDMEN(config->sigmaDelta);
        pll[instance]->PLLFD = value;

        /* Configure modulation */
        value = (uint32) (PLLDIG_PLLFM_SSCGBYP((config->modulationFrequency != 0U) ? 0UL : 1UL)  |
                            PLLDIG_PLLFM_SPREADCTL(config->modulationType)                |
                            PLLDIG_PLLFM_STEPNO(config->incrementStep)                    |
                            PLLDIG_PLLFM_STEPSIZE(config->modulationPeriod));
        pll[instance]->PLLFM = value;

        /* Send command to enable PLL device. */
        pll[instance]->PLLCR &= ~PLLDIG_PLLCR_PLLPD_MASK;
        UpdateClockState(config->name, ENABLED_CLOCK);
    }
}

static clock_pll_status_t CompletePlldigRdivMfiMfnSdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* config)
{
    clock_pll_status_t pllStatus = STATUS_PLL_LOCKED;

    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 PllLockStatus;
    uint32 instance = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];

    if ((pll[instance]->PLLCR & PLLDIG_PLLCR_PLLPD_MASK) == 0U)
    {
        ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
        /* Wait until this pll is locked */
        do
        {
            Clock_Ip_TimeDelay();
            PllLockStatus = ((pll[instance]->PLLSR & PLLDIG_PLLSR_LOCK_MASK) >> PLLDIG_PLLSR_LOCK_SHIFT);
            TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while ((PllLockStatus == 0U) && (FALSE == TimeoutOccurred));

        if (TRUE == TimeoutOccurred)
        {
            UpdateClockState(config->name, DISABLED_CLOCK);
            pllStatus = STATUS_PLL_UNLOCKED;
        }
    }
    else
    {
        pllStatus = STATUS_PLL_UNLOCKED;
    }
    return pllStatus;
}
#endif

/* Pll with frequency modulation and VCO clock post divider for driving the PHI output clocks */
#ifdef PLL_RDIV_MFI_MFN_ODIV2_SDMEN_SSCGBYP_SPREADCTL_STEPNO_STEPSIZE
static void ResetPllRdivMfiMfnOdiv2SdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* config)
{
    uint32 instance = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];

    /* Check clock status for PLL */
    if ((MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK56_MASK) != 0U)
    {
        /* Power down PLL */
        pll[instance]->PLLCR |= PLL_PLLCR_PLLPD_MASK;
    }
    UpdateClockState(config->name, DISABLED_CLOCK);

}
static void SetPllRdivMfiMfnOdiv2SdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* config)
{
    uint32 instance = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    uint32 value;
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;

    if (config->enable != 0U)
    {
        /* Check clock status for PLL */
        if (((MC_ME->PRTN1_COFB1_STAT & MC_ME_PRTN1_COFB1_STAT_BLOCK56_MASK) == 0U))
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

        /* Configure PLL: predivider and multiplier */
        value = (uint32) (PLL_PLLDV_RDIV(config->predivider)   |
                            PLL_PLLDV_MFI(config->mulFactorDiv));
        pll[instance]->PLLDV = value;

        /* Set numerator fractional loop divider and sigma delta modulation */
        value = pll[instance]->PLLFD;
        value &= ~(PLL_PLLFD_MFN_MASK | PLL_PLLFD_SDMEN_MASK);
        value |=  PLL_PLLFD_MFN(config->numeratorFracLoopDiv);
        value |= PLL_PLLFD_SDMEN(config->sigmaDelta);
        pll[instance]->PLLFD = value;

        /* Configure modulation */
        value = (uint32) (PLL_PLLFM_SSCGBYP((config->modulationFrequency != 0U) ? 0UL : 1UL)  |
                            PLL_PLLFM_SPREADCTL(config->modulationType)                |
                            PLL_PLLFM_STEPNO(config->incrementStep)                    |
                            PLL_PLLFM_STEPSIZE(config->modulationPeriod));
        pll[instance]->PLLFM = value;

        /* Send command to enable PLL device. */
        pll[instance]->PLLCR &= ~PLL_PLLCR_PLLPD_MASK;
        UpdateClockState(config->name, ENABLED_CLOCK);
    }
}

static clock_pll_status_t CompletePllRdivMfiMfnOdiv2SdmenSsscgbypSpreadctlStepnoStepsize(Clock_Ip_PllConfigType const* config)
{
    clock_pll_status_t pllStatus = STATUS_PLL_LOCKED;

    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 PllLockStatus;
    uint32 instance = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];

    if ((pll[instance]->PLLCR & PLL_PLLCR_PLLPD_MASK) == 0U)
    {
        ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
        /* Wait until this pll is locked */
        do
        {
            Clock_Ip_TimeDelay();
            PllLockStatus = ((pll[instance]->PLLSR & PLL_PLLSR_LOCK_MASK) >> PLL_PLLSR_LOCK_SHIFT);
            TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while ((PllLockStatus == 0U) && (FALSE == TimeoutOccurred));

        if (TRUE == TimeoutOccurred)
        {
            UpdateClockState(config->name, DISABLED_CLOCK);
            pllStatus = STATUS_PLL_UNLOCKED;
        }
    }
    else
    {
        pllStatus = STATUS_PLL_UNLOCKED;
    }
    return pllStatus;
}
#endif



/* Pll without frequency modulation */
#ifdef PLLDIG_RDIV_MFI_MFN_SDMEN
static void ResetPlldigRdivMfiMfnSdmen(Clock_Ip_PllConfigType const* config)
{
    uint32 instance = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];

    /* Power down PLL */
    pll[instance]->PLLCR |= PLLDIG_PLLCR_PLLPD_MASK;
    UpdateClockState(config->name, DISABLED_CLOCK);
}
static void SetPlldigRdivMfiMfnSdmen(Clock_Ip_PllConfigType const* config)
{
    uint32 instance = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    uint32 value;

    if (config->enable != 0U)
    {
        /* Select input reference. */
        pll[instance]->PLLCLKMUX = PLLDIG_PLLCLKMUX_REFCLKSEL(config->inputReference);

        /* Configure PLL: predivider and multiplier */
        value = (uint32) (PLLDIG_PLLDV_RDIV(config->predivider)   |
                            PLLDIG_PLLDV_MFI(config->mulFactorDiv));
        pll[instance]->PLLDV = value;

        /* Set numerator fractional loop divider and sigma delta modulation */
        value = pll[instance]->PLLFD;
        value &= ~(PLLDIG_PLLFD_MFN_MASK | PLLDIG_PLLFD_SDMEN_MASK);
        value |=  PLLDIG_PLLFD_MFN(config->numeratorFracLoopDiv);
        value |= PLLDIG_PLLFD_SDMEN(config->sigmaDelta);
        pll[instance]->PLLFD = value;

        /* Send command to enable PLL device. */
        pll[instance]->PLLCR &= ~PLLDIG_PLLCR_PLLPD_MASK;
        UpdateClockState(config->name, ENABLED_CLOCK);
    }
}
static clock_pll_status_t CompletePlldigRdivMfiMfnSdmen(Clock_Ip_PllConfigType const* config)
{

    uint32 instance = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    clock_pll_status_t pllStatus = STATUS_PLL_LOCKED;
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 PllLockStatus;

    if ((pll[instance]->PLLCR & PLLDIG_PLLCR_PLLPD_MASK) == 0U)
    {
        ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
        /* Wait until this pll is locked */
        do
        {
            Clock_Ip_TimeDelay();
            PllLockStatus = ((pll[instance]->PLLSR & PLLDIG_PLLSR_LOCK_MASK) >> PLLDIG_PLLSR_LOCK_SHIFT);
            TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while ((PllLockStatus == 0U) && (FALSE == TimeoutOccurred));

        if(TRUE == TimeoutOccurred)
        {
            UpdateClockState(config->name, DISABLED_CLOCK);
            pllStatus = STATUS_PLL_UNLOCKED;
        }
    }
    else
    {
        pllStatus = STATUS_PLL_UNLOCKED;
    }
    return pllStatus;
}
#endif

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
/**
* @violates @ref Clock_Ip_Pll_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/*! @}*/

/*******************************************************************************
 * EOF
 ******************************************************************************/

