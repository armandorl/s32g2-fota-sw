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
*   @file       Clock_Ip.c
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
* @section Clock_Ip_c_REF_1
* Violates MISRA 2012 Advisory Rule 20.1, #include directives should only be preceded by preprocessor
* directives or comments. AUTOSAR imposes the specification of the sections in which certain parts
* of the driver must be placed.
*
* @section Clock_Ip_c_REF_2
* Violates MISRA 2012 Advisory Rule 4.8, This file includes the definition
* of types but does not use it. Header is common for all files
*
* @section Clock_Ip_c_REF_3
* Violates MISRA 2012 Advisory Directive 4.9, A function should be used in preference to a function-like macro where they are interchangeable.
* Function like macro are used to reduce code complexity
*
* @section Clock_Ip_c_REF_4
* Violates MISRA 2012 Advisory Rule 12.3, The comma operator should not be used.
* The comma is used  to abstract the trusted call function and to determine when the return into user mode is needed.
*
* @section Clock_Ip_c_REF_5
* Violates MISRA 2012 Advisory Rule 8.7, Functions and objects should not be defined with external linkage if
* they are referenced in only one translation unit.
* These functions represent the API of the driver. External linkage is needed to "export" the API.
*/

#include "Clock_Ip_Private.h"
#include "OsIf.h"
/*******************************************************************************
 * Definitions
 ******************************************************************************/

static void ClockNotificatonsEmptyCallback(Clock_Ip_ClockNotificationType notification, Clock_Ip_NameType clockName);
static void Clock_Ip_Sleep(void);
/* Clock start initialized section data */
#define MCU_START_SEC_VAR_INIT_UNSPECIFIED
/**
* @violates @ref Clock_Ip_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

static const Clock_Ip_ClockConfigType *clockConfig = NULL;                                           /* Reference to the current clock configuration */
static boolean clockTreeIsConsumingPll = FALSE;                                                      /* Clock tree is using a PLL output */
static Clock_Ip_NotificationsCallbackType clockNotificationsCallback = ClockNotificatonsEmptyCallback;   /* Clock Report Error Callback */

/* Clock stop initialized section data */
#define MCU_STOP_SEC_VAR_INIT_UNSPECIFIED
/**
* @violates @ref Clock_Ip_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/* Clock start uninitialized section data */
#define  MCU_START_SEC_VAR_NO_INIT_8
/**
* @violates @ref Clock_Ip_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

static uint8 ClockCalcFreqCallIdx;

/* Clock stop uninitialized section data */
#define  MCU_STOP_SEC_VAR_NO_INIT_8
/**
* @violates @ref Clock_Ip_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"


/* Clock start section code */
#define MCU_START_SEC_CODE
/**
* @violates @ref Clock_Ip_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/*FUNCTION******************************************************************************
 *
 * Function Name : Clock_Ip_Init
 * Description   : This function configures all clocks according to a clock configuration.
 *
 * @implements Clock_Ip_Init_Activity
 * END**********************************************************************************/
/**
* @violates @ref Clock_Ip_c_REF_5 Functions and objects should not be defined with external linkage if
* they are referenced in only one translation unit. These functions represent the API of the driver.
*/
Clock_Ip_StatusType Clock_Ip_Init(Clock_Ip_ClockConfigType const * config)
{
    Clock_Ip_StatusType clockStatus = CLOCK_IP_SUCCESS;
    Clock_Ip_PllStatusType pllStatus;

    (void)consumerClockCallbacks;
    (void)xoscCallbackIndex;
    (void)extOscCallbacks;
    (void)ircoscCallbackIndex;
    (void)intOscCallbacks;
    (void)pcfsCallbackIndex;
    (void)pcfsCallbacks;
    (void)dividerCallbackIndex;
    (void)dividerCallbacks;
    (void)calcFreqCallbacks;

    (void)CLOCK_MODULE_INSTANCE;
    (void)CLOCK_CALLBACK;
    (void)INTERFACE_CLOCK;
    (void)SELECTOR_INDEX;
    (void)PCFS_INSTANCE;
    (void)DIVIDER_INDEX;
    (void)PCTL_INDEX;
    (void)PCC_INDEX;
    (void)PARTITION_INDEX;
    (void)COLLECTION_INDEX;
    (void)PCFS_HW_INDEX;
    (void)ENABLE_REQUEST;
    (void)PCFS_SW_INDEX;
    (void)TRIGGER_FEATURE;


#if (defined(CLOCK_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT))
    /* Set user access allowed for Clock */
    Clock_Ip_SetUserAccessAllowed();
#endif
    Clock_Ip_InitClock(config);

    if (clockTreeIsConsumingPll)
    {
        pllStatus = Clock_Ip_GetPllStatus();
        if (CLOCK_IP_PLL_LOCKED == pllStatus)
        {
            Clock_Ip_DistributePll();
        }
        else
        {
            clockStatus = CLOCK_IP_ERROR;
        }
    }

    return clockStatus;
}

/*FUNCTION******************************************************************************
 *
 * Function Name : Clock_Ip_InitClock
 * Description   : This function configures all clocks according to a clock configuration.
 *
 * @implements Clock_Ip_InitClock_Activity
 * END**********************************************************************************/
/**
* @violates @ref Clock_Ip_c_REF_5 Functions and objects should not be defined with external linkage if
* they are referenced in only one translation unit. These functions represent the API of the driver.
*/
void Clock_Ip_InitClock(Clock_Ip_ClockConfigType const * config)
{
    uint32 i, callbackIndex;

    ClockCalcFreqCallIdx = 0U;
    /* Clear all the settings for CMU0/1/2... */
    /* In case one clock configuration has the CMU disabled, then need to make the transition to
    reset state of CMU modules. */
    if (NULL != clockConfig)
    {
        for (i = 0U; i < config->cmusCount; i++)    /* Reset all clock monitor units from previous configuration. */
        {
                callbackIndex = cmuCallbackIndex[clockFeatures[config->cmus[i].name][CLOCK_CALLBACK]];
                cmuCallbacks[callbackIndex].Reset(&config->cmus[i]);
        }
    }

    /* Save the current clock configuration to be used by "Clock_Ip_DistributePllClock". */
    clockConfig = config;

    /* Platform specific initialization:
     * DFS reset, FIRC_CLK configuration etc. */
    SpecificPlatformInitClock(config);

    /*********************************************************************
     ***  Ramp down to safe configuration. Reset elements from clock tree:
     ***  selectors, fractional dividers, plls and xoscs
     ***********************************************************************/

    for (i = 0U; i < config->selectorsCount; i++)    /* Ramp down all selectors from configuration to SAFE_CLOCK */
    {
        callbackIndex = selectorCallbackIndex[clockFeatures[config->selectors[i].name][CLOCK_CALLBACK]];
        selectorCallbacks[callbackIndex].Reset(&config->selectors[i]);
    }

    for (i = 0U; i < config->fracDivsCount; i++)    /* Put in reset state all fractional dividers from configuration */
    {
        callbackIndex = fractional_dividerCallbackIndex[clockFeatures[config->fracDivs[i].name][CLOCK_CALLBACK]];
        fracDivCallbacks[callbackIndex].Reset(&config->fracDivs[i]);
    }

    for (i = 0U; i < config->pllsCount; i++)       /* Power down all plls from configuration */
    {
        callbackIndex = pllCallbackIndex[clockFeatures[config->plls[i].name][CLOCK_CALLBACK]];
        pllCallbacks[callbackIndex].Reset(&config->plls[i]);
    }

    for (i = 0U; i < config->xoscsCount; i++)     /* Power down all xoscs from configuration */
    {
        callbackIndex = xoscCallbackIndex[clockFeatures[config->xoscs[i].name][CLOCK_CALLBACK]];
        extOscCallbacks[callbackIndex].Reset(&config->xoscs[i]);
    }

    /*******************************************************
     *** Load the new configuration. Selectors that might
     *** be clocked from PLLs/XOCs shouldn't be configured.
     *******************************************************/

    for (i = 0U; i < config->ircoscsCount; i++)   /* Set internal oscillators from configuration */
    {
        callbackIndex = ircoscCallbackIndex[clockFeatures[config->ircoscs[i].name][CLOCK_CALLBACK]];
        intOscCallbacks[callbackIndex].Set(&config->ircoscs[i]);
    }

    for (i = 0U; i < config->xoscsCount; i++)     /* Configure all xoscs from configuration */
    {
        callbackIndex = xoscCallbackIndex[clockFeatures[config->xoscs[i].name][CLOCK_CALLBACK]];
        extOscCallbacks[callbackIndex].Set(&config->xoscs[i]);
    }

    /* Complete the process frequency calculations */
    Clock_Ip_Sleep();

    /* Configure the PCFS  */
    for (i = 0U; i < config->pcfsCount; i++)       /* Configure all progressive frequency switching clocks from configuration */
    {
        callbackIndex = pcfsCallbackIndex[clockFeatures[config->pcfs[i].name][CLOCK_CALLBACK]];
        pcfsCallbacks[callbackIndex].Set(&config->pcfs[i]);
    }

    /* Configure the clock divider triggers that are under MCU control */
    for (i = 0U; i < config->dividerTriggersCount; i++)    /* Set divider triggers from configuration. */
    {
        callbackIndex = dividertriggerCallbackIndex[clockFeatures[config->dividerTriggers[i].name][CLOCK_CALLBACK]];
        dividerTriggerCallbacks[callbackIndex].Configure(&config->dividerTriggers[i]);
    }

    /* Configure the clock dividers that are under MCU control */
    for (i = 0U; i < config->dividersCount; i++)    /* Set dividers from configuration. */
    {
        callbackIndex = dividerCallbackIndex[clockFeatures[config->dividers[i].name][CLOCK_CALLBACK]];
        dividerCallbacks[callbackIndex].Set(&config->dividers[i]);
    }

    /* Trigger update for all divider trigger that are under MCU control */
    for (i = 0U; i < config->dividerTriggersCount; i++)    /* Set divider triggers from configuration. */
    {
        callbackIndex = dividertriggerCallbackIndex[clockFeatures[config->dividerTriggers[i].name][CLOCK_CALLBACK]];
        dividerTriggerCallbacks[callbackIndex].TriggerUpdate(&config->dividerTriggers[i]);
    }

    /* Configure PLL clock generators */
    for (i = 0U; i < config->pllsCount; i++)       /* Configure all plls from configuration asynchronously. Do not wait. */
    {
        callbackIndex = pllCallbackIndex[clockFeatures[config->plls[i].name][CLOCK_CALLBACK]];
        pllCallbacks[callbackIndex].Set(&config->plls[i]);
    }

    /* Configure fractional dividers */
    /* Note: The DFS configuration might actually need to be done after we
     * know that the PLLs are all locked in "Clock_Ip_GetPllStatus". */
    for (i = 0U; i < config->fracDivsCount; i++)    /* Configure all fractional dividers from configuration asynchronously. Do not wait. */
    {
        callbackIndex = fractional_dividerCallbackIndex[clockFeatures[config->fracDivs[i].name][CLOCK_CALLBACK]];
        fracDivCallbacks[callbackIndex].Set(&config->fracDivs[i]);
    }

#ifdef FEATURE_CLOCK_IP_HAS_RAM_WAIT_STATES
    /* The entry point of the flash and RAM controllers configuration. */
    clockNotificationsCallback(CLOCK_IP_RAM_MEMORY_CONFIG_ENTRY_POINT, RESERVED_CLK);

    SetRamWaitStates();

    /* The exit point of the flash and RAM controllers configuration. */
    clockNotificationsCallback(CLOCK_IP_RAM_MEMORY_CONFIG_EXIT_POINT, RESERVED_CLK);
#endif

#ifdef FEATURE_CLOCK_IP_HAS_FLASH_WAIT_STATES
    /* The entry point of the flash and RAM controllers configuration. */
    clockNotificationsCallback(CLOCK_IP_FLASH_MEMORY_CONFIG_ENTRY_POINT, RESERVED_CLK);

    SetFlashWaitStates();

    /* The exit point of the flash and RAM controllers configuration. */
    clockNotificationsCallback(CLOCK_IP_FLASH_MEMORY_CONFIG_EXIT_POINT, RESERVED_CLK);
#endif

    clockTreeIsConsumingPll = FALSE;   /* Check if the clock tree is using a PLL output */

    /* Switch the clock multiplexers under MCU control to the configured source clocks */
    /* Note: if the configured source clock of a ClockMux is the output clock of a PLL/DFS,
     * the configuration will be skipped and the respective ClockMux will be switched in
     * the "Clock_Ip_DistributePllClock" function instead, when the source clock will have
     * stabilized already. */
    for (i = 0U; i < config->selectorsCount; i++)    /* Set only if selected inputs are not clocked from XOSCs or PLLs */
    {
        if ((IRCOSC_TYPE == clockName_sourceType[config->selectors[i].value]))  {

            callbackIndex = selectorCallbackIndex[clockFeatures[config->selectors[i].name][CLOCK_CALLBACK]];
            selectorCallbacks[callbackIndex].Set(&config->selectors[i]);
        }
        else
        {
            /* At least one mux is consuming pll */
            clockTreeIsConsumingPll = TRUE;
        }
    }

    for (i = 0U; i < config->gatesCount; i++)    /* Set clock gates that are under clock control. */
    {
        callbackIndex = gateCallbackIndex[clockFeatures[config->gates[i].name][CLOCK_CALLBACK]];
        gateCallbacks[callbackIndex].Set(&config->gates[i]);
    }

    /* Check if the clock tree is using a PLL output */
    if ( FALSE == clockTreeIsConsumingPll )
    {
#if CLOCK_SPECIFIC_PERIPH_NO > 0U
        /* Configure the specific modules like eMios */
        SpecificPeripheralClockInitialization(&config->specificPeriphalConfiguration);
#endif
        /* Set the Clock Monitoring Units ( CMU0 .. n ). */
        for (i = 0U; i < config->cmusCount; i++)
        {
            callbackIndex = cmuCallbackIndex[clockFeatures[config->cmus[i].name][CLOCK_CALLBACK]];
            cmuCallbacks[callbackIndex].Set(&config->cmus[i]);
        }
    }
    else
    {
        /* The clock tree is using at least one PLL/DFS output clock as source. */
        /* The user must wait until the PLLs and DFSs are locked by polling Clock_Ip_GetPllStatus */
        /* and then call "Clock_Ip_DistributePllClock" */
    }
    /* When mcu clock distribution is updated or power mode is changed, frequencies must be updated. */
    UpdateFrequencies(RUN_MODE);
}

/*FUNCTION******************************************************************************
 *
 * Function Name : Clock_Ip_GetPllStatus
 * Description   : This function configures all clocks according to a clock configuration.
 * If no configuration is received, no change will be processed in HW and clock driver
 * will calculate frequencies only.
 *
 * @implements Clock_Ip_GetPllStatus_Activity
 * END**********************************************************************************/
 /**
* @violates @ref Clock_Ip_c_REF_5 Functions and objects should not be defined with external linkage if
* they are referenced in only one translation unit. These functions represent the API of the driver.
*/
Clock_Ip_PllStatusType Clock_Ip_GetPllStatus(void)
{

    Clock_Ip_PllStatusType retValue = CLOCK_IP_PLL_STATUS_UNDEFINED;
    clock_pll_status_t pllStatus;
    clock_dfs_status_t dfsStatus;
    uint32 i, callbackIndex;

    /* 'clockConfig' is set by Clock_Ip_InitClock().
     *  It doesn't make sense to call PLL status without clock initialization. */
    if (NULL != clockConfig)
    {
        for (i = 0U; i < clockConfig->pllsCount; i++)       /* Wait for all PLL clock generators that are under clock control. */
        {
        	if (!clockConfig->plls[i].enable)
				continue;
			
            callbackIndex = pllCallbackIndex[clockFeatures[clockConfig->plls[i].name][CLOCK_CALLBACK]];
            pllStatus = pllCallbacks[callbackIndex].Complete(&clockConfig->plls[i]);
            if (STATUS_PLL_UNLOCKED == pllStatus)
            {
                retValue = CLOCK_IP_PLL_UNLOCKED;
                break;
            }
            else
            {
                if (STATUS_PLL_LOCKED == pllStatus)
                {
                    retValue = CLOCK_IP_PLL_LOCKED;
                }
            }
        }
        if (CLOCK_IP_PLL_LOCKED == retValue)
        {
            for (i = 0U; i < clockConfig->fracDivsCount; i++)    /* Wait for all fractional dividers that are under clock control. */
            {
                callbackIndex = fractional_dividerCallbackIndex[clockFeatures[clockConfig->fracDivs[i].name][CLOCK_CALLBACK]];
                dfsStatus = fracDivCallbacks[callbackIndex].Complete(&clockConfig->fracDivs[i]);
                if (STATUS_DFS_UNLOCKED == dfsStatus)
                {
                    retValue = CLOCK_IP_PLL_UNLOCKED;
                    break;
                }
            }
        }
    }

    return retValue;
}

/*FUNCTION******************************************************************************
 *
 * Function Name : Clock_Ip_DistributePll
 * Description   : Function completes the PLL configuration and then activates the PLL clock to Mcu
 * The function will not distribute the PLL clock if the driver state does not allow it, or the PLL is not stable.
 *
 * @implements Clock_Ip_DistributePll_Activity
 * END**********************************************************************************/
/**
* @violates @ref Clock_Ip_c_REF_5 Functions and objects should not be defined with external linkage if
* they are referenced in only one translation unit. These functions represent the API of the driver.
*/
void Clock_Ip_DistributePll(void)
{

    uint32 i, callbackIndex;

    /* 'clockConfig' is set by Clock_Ip_InitClock().
     *  It doesn't make sense to call PLL distribution without clock initialization. */
    if (NULL != clockConfig)
    {
        for (i = 0U; i < clockConfig->selectorsCount; i++)    /* Set only if selected inputs are clocked from XOSCs or PLLs */
        {
            if (IRCOSC_TYPE != clockName_sourceType[clockConfig->selectors[i].value])  {

                callbackIndex = selectorCallbackIndex[clockFeatures[clockConfig->selectors[i].name][CLOCK_CALLBACK]];
                selectorCallbacks[callbackIndex].Set(&clockConfig->selectors[i]);
            }
        }

        /* In the case of PLL is enabled but PLL clock source is not used by any clock Mux.
           So, no need to re-configure for CMUs, because they are configured by Clock_Ip_InitClock */
        /* Check if the clock tree is using a PLL output */
        if ( clockTreeIsConsumingPll )
        {
#if CLOCK_SPECIFIC_PERIPH_NO > 0U
            SpecificPeripheralClockInitialization(&clockConfig->specificPeriphalConfiguration);
#endif
            /* Enable CMU if used */
            for (i = 0U; i < clockConfig->cmusCount; i++)
            {
                    callbackIndex = cmuCallbackIndex[clockFeatures[clockConfig->cmus[i].name][CLOCK_CALLBACK]];
                    cmuCallbacks[callbackIndex].Set(&clockConfig->cmus[i]);
            }
        }
    }

    /* When mcu clock distribution is updated or
     * power mode is changed, frequencies must be updated.
     */
    UpdateFrequencies(RUN_MODE);
}

/*FUNCTION******************************************************************************
 *
 * Function Name : Clock_Ip_DisableClockMonitor
 * Description   : Disables a clock monitor.
 *
 * @implements Clock_Ip_DisableClockMonitor_Activity
 * END**********************************************************************************/
/**
* @violates @ref Clock_Ip_c_REF_5 Functions and objects should not be defined with external linkage if
* they are referenced in only one translation unit. These functions represent the API of the driver.
*/
void Clock_Ip_DisableClockMonitor(Clock_Ip_NameType clockName)
{

    uint32 callbackIndex;

    callbackIndex = cmuCallbackIndex[clockFeatures[clockName][CLOCK_CALLBACK]];
    cmuCallbacks[callbackIndex].Disable(clockName);
}

/*FUNCTION******************************************************************************
 *
 * Function Name : Clock_Ip_GetClockMonitorStatus
 * Description   : Returns the clock monitor status.
 *
 * @implements Clock_Ip_GetClockMonitorStatus_Activity
 * END**********************************************************************************/
/**
* @violates @ref Clock_Ip_c_REF_5 Functions and objects should not be defined with external linkage if
* they are referenced in only one translation unit. These functions represent the API of the driver.
*/
Clock_Ip_CmuStatusType Clock_Ip_GetClockMonitorStatus(Clock_Ip_NameType clockName)
{
    uint32 callbackIndex;

    callbackIndex = cmuCallbackIndex[clockFeatures[clockName][CLOCK_CALLBACK]];
    return cmuCallbacks[callbackIndex].GetStatus(clockName);
}

/*FUNCTION******************************************************************************
 *
 * Function Name : Clock_Ip_ClearClockMonitorStatus
 * Description   : Clears status flags for a monitor clock.
 *
 * @implements Clock_Ip_ClearClockMonitorStatus_Activity
 * END**********************************************************************************/
/**
* @violates @ref Clock_Ip_c_REF_5 Functions and objects should not be defined with external linkage if
* they are referenced in only one translation unit. These functions represent the API of the driver.
*/
void Clock_Ip_ClearClockMonitorStatus(Clock_Ip_NameType clockName)
{

    uint32 callbackIndex;

    callbackIndex = cmuCallbackIndex[clockFeatures[clockName][CLOCK_CALLBACK]];
    cmuCallbacks[callbackIndex].Clear(clockName);
}

/*FUNCTION******************************************************************************
 *
 * Function Name : Clock_Ip_PowerModeChangeNotification
 * Description   : Notifies clock driver when a power mode is changed.
 *
 * @implements Clock_Ip_PowerModeChangeNotification_Activity
 * END**********************************************************************************/
/**
* @violates @ref Clock_Ip_c_REF_5 Functions and objects should not be defined with external linkage if
* they are referenced in only one translation unit. These functions represent the API of the driver.
*/
void Clock_Ip_PowerModeChangeNotification(power_modes_t powerMode,power_notification_t notification)
{
    switch(notification)
    {
        case BEFORE_POWER_MODE_CHANGE:
        {
            UpdateFrequencies(powerMode);
        }
        break;
        case POWER_MODE_CHANGE_IN_PROGRESS:
        {
            UpdateFrequencies(powerMode);
        }
        break;
        case POWER_MODE_CHANGED:
        {
            UpdateFrequencies(powerMode);
        }
        break;
        default:
        {
            /*  Other option is not implemented */
        }
        break;
    }
}

/*FUNCTION******************************************************************************
 *
 * Function Name : Clock_Ip_DisableModuleClock
 * Description   : This function installs a callback for clock notifications. 
 *
 * @implements Clock_Ip_InstallNotificationsCallback_Activity
 * END**********************************************************************************/
/**
* @violates @ref Clock_Ip_c_REF_5 Functions and objects should not be defined with external linkage if
* they are referenced in only one translation unit. These functions represent the API of the driver.
*/
void Clock_Ip_InstallNotificationsCallback(Clock_Ip_NotificationsCallbackType callback)
{
    clockNotificationsCallback = callback;
}

/*FUNCTION******************************************************************************
 *
 * Function Name : Clock_Ip_DisableModuleClock
 * Description   : Disables clock for a peripheral. 
 *
 * @implements Clock_Ip_DisableModuleClock_Activity
 * END**********************************************************************************/
/**
* @violates @ref Clock_Ip_c_REF_5 Functions and objects should not be defined with external linkage if
* they are referenced in only one translation unit. These functions represent the API of the driver.
*/
void Clock_Ip_DisableModuleClock(Clock_Ip_NameType clockName)
{

    uint32 callbackIndex;

    callbackIndex = gateCallbackIndex[clockFeatures[clockName][CLOCK_CALLBACK]];
    gateCallbacks[callbackIndex].Update(clockName,TRUE);
}

/*FUNCTION******************************************************************************
 *
 * Function Name : Clock_Ip_EnableModuleClock
 * Description   : Enable clock for a peripheral. 
 *
 * @implements Clock_Ip_EnableModuleClock_Activity
 * END**********************************************************************************/
/**
* @violates @ref Clock_Ip_c_REF_5 Functions and objects should not be defined with external linkage if
* they are referenced in only one translation unit. These functions represent the API of the driver.
*/
void Clock_Ip_EnableModuleClock(Clock_Ip_NameType clockName)
{

    uint32 callbackIndex;

    callbackIndex = gateCallbackIndex[clockFeatures[clockName][CLOCK_CALLBACK]];
    gateCallbacks[callbackIndex].Update(clockName,FALSE);
}



/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_GetClockFrequency
 * Description   : This function returns the frequency of a given clock
 *
 * @implements Clock_Ip_GetClockFrequency_Activity
 * END**************************************************************************/
 /**
* @violates @ref Clock_Ip_c_REF_5 Functions and objects should not be defined with external linkage if
* they are referenced in only one translation unit. These functions represent the API of the driver.
*/
uint32 Clock_Ip_GetClockFrequency(Clock_Ip_NameType clockName)
{
    uint32 frequency;
#if (defined(CLOCK_IP_DEV_ERROR_DETECT) && (CLOCK_IP_DEV_ERROR_DETECT == STD_ON))
    CLOCK_DEV_ASSERT((((uint32)clockName) < ((uint32)CLOCK_NAMES_NO)) && (THE_LAST_PRODUCER_CLK != clockName));
#endif

    if(((uint32)clockName) > ((uint32)THE_LAST_PRODUCER_CLK))
    {
        frequency = consumerClockCallbacks[((uint32)clockName) - ((uint32)THE_LAST_PRODUCER_CLK) - (uint32)1U]();
    }
    else
    {
        frequency = GetProducerClockFreq(clockName);
    }
    return frequency;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_Sleep.
 * Description   : Complete the process frequency calculations
 *
 *END**************************************************************************/
static void Clock_Ip_Sleep(void)
{
    while(ClockCalcFreqCallIdx < (CALC_FREQ_CALLBACKS_NO-1U))
    {
        calcFreqCallbacks[ClockCalcFreqCallIdx]();
        ClockCalcFreqCallIdx++;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_TimeDelay.
 * Description   : TimeDelay. Process frequency calculations on behalf of TimeDelay function.
 *
 *END**************************************************************************/
void Clock_Ip_TimeDelay(void)
{
    calcFreqCallbacks[ClockCalcFreqCallIdx]();

    if (ClockCalcFreqCallIdx < (CALC_FREQ_CALLBACKS_NO-1U))
    {
        ClockCalcFreqCallIdx++;
    }
}

#if (defined(CLOCK_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT))
/*FUNCTION**********************************************************************
 *
 * Function Name : Clock_Ip_SetUserAccessAllowed.
 * Description   : Set user access allowed.
 *
 *END**************************************************************************/
/**
* @violates @ref Clock_Ip_c_REF_5 Functions and objects should not be defined with external linkage if
* they are referenced in only one translation unit. These functions represent the API of the driver.
*/
void Clock_Ip_SetUserAccessAllowed(void)
{
    /**
    * @violates @ref Clock_Ip_c_REF_3 A function should be used in preference to a function-like macro where they are interchangeable.
    */
    /**
    * @violates @ref Clock_Ip_c_REF_4 The comma is used  to abstract the trusted call function and to determine when the return into user mode is needed.
    */
    OsIf_Trusted_Call(SpecificSetUserAccessAllowed);
}
#endif /* (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT) */

/*FUNCTION**********************************************************************
 *
 * Function Name : ClockNotificatonsEmptyCallback.
 * Description   : Notification clock call back.
 *
 *END**************************************************************************/
static void ClockNotificatonsEmptyCallback(Clock_Ip_ClockNotificationType notification, Clock_Ip_NameType clockName)
{
    /* No implementation */
    (void)notification;
    (void)clockName;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ReportClockErrors
 * Description   : Report clock error
 *
 *END**************************************************************************/
void ReportClockErrors(Clock_Ip_ClockNotificationType error, Clock_Ip_NameType clockName)
{
    clockNotificationsCallback(error,clockName);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ClockStartTimeout
 * Description   : Checks for timeout condition
 *
 *END**************************************************************************/
void ClockStartTimeout(uint32 *startTimeOut,
                       uint32 *elapsedTimeOut,
                       uint32 *timeoutTicksOut,
                       uint32 timeoutUs)
{
    *startTimeOut    = OsIf_GetCounter(CLOCK_TIMEOUT_TYPE);
    *elapsedTimeOut  = 0U;
    *timeoutTicksOut = OsIf_MicrosToTicks(timeoutUs, CLOCK_TIMEOUT_TYPE);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : ClockTimeoutExpired
 * Description   : Checks for timeout expiration condition
 *
 *END**************************************************************************/
boolean ClockTimeoutExpired(uint32 *startTimeInOut,
                            uint32 *elapsedTimeInOut,
                            uint32 TimeoutTicks)
{
    *elapsedTimeInOut += OsIf_GetElapsed(startTimeInOut, CLOCK_TIMEOUT_TYPE);

    return ((*elapsedTimeInOut >= TimeoutTicks)? TRUE : FALSE);
}


/* Clock stop section code */
#define MCU_STOP_SEC_CODE
/**
* @violates @ref Clock_Ip_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/*! @}*/

/*******************************************************************************
 * EOF
 ******************************************************************************/
