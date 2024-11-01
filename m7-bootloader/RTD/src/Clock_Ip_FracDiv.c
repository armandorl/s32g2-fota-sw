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
*   @file       Clock_Ip_FracDiv.c
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
* @section Clock_Ip_FracDiv_c_REF_1
* Violates MISRA 2012 Advisory Rule 20.1, #include directives should only be preceded by preprocessor
* directives or comments. AUTOSAR imposes the specification of the sections in which certain parts
* of the driver must be placed.
*
* @section Clock_Ip_FracDiv_c_REF_2
* Violates MISRA 2012 Advisory Rule 4.8, This file includes the definition
* of types but does not use it. Header is common for all files
*
*/


#include "Clock_Ip_Private.h"

/* Clock start section code */
#define MCU_START_SEC_CODE
/**
* @violates @ref Clock_Ip_FracDiv_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

static void Callback_FracDivEmpty(Clock_Ip_FracDivConfigType const* config);
static clock_dfs_status_t Callback_FracDivEmptyComplete(Clock_Ip_FracDivConfigType const *config);
#ifdef DFS_MFI_MFN
static void ResetDfsMfiMfn(Clock_Ip_FracDivConfigType const *config);
static void SetDfsMfiMfn(Clock_Ip_FracDivConfigType const *config);
static clock_dfs_status_t CompleteDfsMfiMfn(Clock_Ip_FracDivConfigType const *config);
#endif

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
/**
* @violates @ref Clock_Ip_FracDiv_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_FracDiv_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

const fracDivCallback fracDivCallbacks[FRACTIONAL_DIVIDER_CALLBACKS_COUNT] =
{
    {
        Callback_FracDivEmpty,            /* Reset */
        Callback_FracDivEmpty,            /* Set */
        Callback_FracDivEmptyComplete,    /* Complete */
    },
#ifdef DFS_MFI_MFN
    {
        ResetDfsMfiMfn,                   /* Reset */
        SetDfsMfiMfn,                     /* Set */
        CompleteDfsMfiMfn,                /* Complete */
    },
#endif
};

static void Callback_FracDivEmpty(Clock_Ip_FracDivConfigType const* config)
{
    (void)config;
    /* No implementation */
}

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_FracDiv_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/* Clock start section code */
#define MCU_START_SEC_CODE
/**
* @violates @ref Clock_Ip_FracDiv_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

static clock_dfs_status_t Callback_FracDivEmptyComplete(Clock_Ip_FracDivConfigType const *config)
{
    (void)config;
    /* No implementation */
    return STATUS_DFS_NOT_ENABLED;
}

#ifdef DFS_MFI_MFN
static void ResetDfsMfiMfn(Clock_Ip_FracDivConfigType const *config)
{

    uint32 instance      = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    uint32 dividerIndex  = clockFeatures[config->name][DIVIDER_INDEX];

    /* Put this fractional divider in reset state */
    dfs[instance]->PORTRESET |= (1UL << dividerIndex);

    UpdateClockState(config->name, DISABLED_CLOCK);
}
static void SetDfsMfiMfn(Clock_Ip_FracDivConfigType const *config)
{

    uint32 instance      = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    uint32 dividerIndex  = clockFeatures[config->name][DIVIDER_INDEX];

    uint32 integerPart     = config->value[0U];          /* Integer part. */
    uint32 fractionalPart  = config->value[1U];          /* Fractional part. */

    uint32 value = 0U;

    /* Check whether fractional divider is enabled */
    if ((integerPart != 0U) || (fractionalPart != 0U))
    {
        /* Write the value by which input signal is divided */
        value |= DFS_DVPORT_MFN(fractionalPart);
        value |= DFS_DVPORT_MFI(integerPart);
        dfs[instance]->DVPORT[dividerIndex] = value;

        /* Get corresponding port out of reset state */
        dfs[instance]->PORTRESET &= ~(1UL << dividerIndex);
    }
}
static clock_dfs_status_t CompleteDfsMfiMfn(Clock_Ip_FracDivConfigType const *config)
{
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 DfsPortStatus;

    clock_dfs_status_t status = STATUS_DFS_LOCKED;

    uint32 instance      = clockFeatures[config->name][CLOCK_MODULE_INSTANCE];
    uint32 dividerIndex  = clockFeatures[config->name][DIVIDER_INDEX];

    /* Check whether fractional divider is enabled */
    if ((dfs[instance]->PORTRESET & (1UL << dividerIndex)) == 0U)
    {
        ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
        /* Wait until this port is locked */
        do
        {
            Clock_Ip_TimeDelay();
            DfsPortStatus = (((dfs[instance]->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & (1UL << dividerIndex));
            TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while ((DfsPortStatus == 0U) && (FALSE == TimeoutOccurred));

        if (FALSE == TimeoutOccurred)
        {
            UpdateClockState(config->name, ENABLED_CLOCK);
        }
        else
        {
            status = STATUS_DFS_UNLOCKED;
            /* Report timeout error */
            ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, config->name);
        }
    }
    else
    {
        status = STATUS_DFS_NOT_ENABLED;
    }

    return status;
}


#endif

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
/**
* @violates @ref Clock_Ip_FracDiv_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/*! @}*/

/*******************************************************************************
 * EOF
 ******************************************************************************/

