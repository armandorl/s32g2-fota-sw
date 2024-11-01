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
*   @file       Clock_Ip_Gate.c
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
* @section Clock_Ip_Gate_c_REF_1
* Violates MISRA 2012 Advisory Rule 20.1, #include directives should only be preceded by preprocessor
* directives or comments. AUTOSAR imposes the specification of the sections in which certain parts
* of the driver must be placed.
*
* @section Clock_Ip_Gate_c_REF_2
* Violates MISRA 2012 Advisory Rule 4.8, This file includes the definition
* of types but does not use it. Header is common for all files
*
*/


#include "Clock_Ip_Private.h"

/* Clock start section code */
#define MCU_START_SEC_CODE
/**
* @violates @ref Clock_Ip_Gate_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"


static void ClockSetGateEmpty(Clock_Ip_GateConfigType const* config);
static void ClockUpdateGateEmpty(Clock_Ip_NameType clockName, boolean gate);
#ifdef MC_ME_PARTITION_COFB_ENABLE_REQUEST
static void ClockSetGateMcMePartitionCollectionClockRequest(Clock_Ip_GateConfigType const* config);
static void ClockUpdateGateMcMePartitionCollectionClockRequest(Clock_Ip_NameType clockName, boolean gate);
#endif

/* Clock stop section code */
#define MCU_STOP_SEC_CODE
/**
* @violates @ref Clock_Ip_Gate_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_Gate_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

const gateCallback gateCallbacks[GATE_CALLBACKS_COUNT] =
{
    {
        ClockSetGateEmpty,     /* Set */
        ClockUpdateGateEmpty,  /* Update */
    },
#ifdef MC_ME_PARTITION_COFB_ENABLE_REQUEST
    {
            ClockSetGateMcMePartitionCollectionClockRequest,      /* Set */
            ClockUpdateGateMcMePartitionCollectionClockRequest,   /* Update */
    },
#endif
};


/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_Gate_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"


/* Clock start section code */
#define MCU_START_SEC_CODE
/**
* @violates @ref Clock_Ip_Gate_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

static void ClockSetGateEmpty(Clock_Ip_GateConfigType const* config)
{
    (void)config;
    /* No implementation */
}
static void ClockUpdateGateEmpty(Clock_Ip_NameType clockName, boolean gate)
{
    (void)clockName;
    (void)gate;
    /* No implementation */
}

#ifdef MC_ME_PARTITION_COFB_ENABLE_REQUEST
static void ClockSetGateMcMePartitionCollectionClockRequest(Clock_Ip_GateConfigType const* config)
{
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;
    uint32 partition      = clockFeatures[config->name][PARTITION_INDEX];
    uint32 collection     = clockFeatures[config->name][COLLECTION_INDEX];
    uint32 enableRequest  = clockFeatures[config->name][ENABLE_REQUEST];

    if (config->enable != 0U)
    {
        if ((mcmeGetPartitions[partition]->PRTN_COFB_STAT[collection] & (1UL << enableRequest)) == 0U)
        {

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
    else
    {
        if ((mcmeGetPartitions[partition]->PRTN_COFB_STAT[collection] & (1UL << enableRequest)) != 0U)
        {

            mcmeSetPartitions[partition]->PRTN_COFB_CLKEN[collection] &= (~(1UL << enableRequest));
            mcmeTriggerPartitions[partition]->PRTN_PCONF  |= MC_ME_PRTN1_PCONF_PCE_MASK;
            mcmeTriggerPartitions[partition]->PRTN_PUPD   |= MC_ME_PRTN1_PUPD_PCUD_MASK;
            McMeEnterKey();

            /* Wait until clock gate is updated */
            ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
            do
            {
                TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
            }
            while (((mcmeGetPartitions[partition]->PRTN_COFB_STAT[collection] & (1UL << enableRequest)) != 0U) && (FALSE == TimeoutOccurred));
            /* timeout notification */
            if (TRUE == TimeoutOccurred)
            {
                /* Report timeout error */
                ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, config->name);
            }
        }
    }
}
static void ClockUpdateGateMcMePartitionCollectionClockRequest(Clock_Ip_NameType clockName, boolean gate)
{
    Clock_Ip_GateConfigType config;
    config.name = clockName;
    if (gate == TRUE)
    {
        config.enable = 0U;
    }
    else
    {
        config.enable = 1U;
    }
    ClockSetGateMcMePartitionCollectionClockRequest(&config);
}
#endif



/* Clock stop section code */
#define MCU_STOP_SEC_CODE
/**
* @violates @ref Clock_Ip_Gate_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/*! @}*/

/*******************************************************************************
 * EOF
 ******************************************************************************/

