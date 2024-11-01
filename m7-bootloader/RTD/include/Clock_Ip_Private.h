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
*   @file    Clock_Ip_Private.h
*   @version    1.0.0
*
*   @brief   CLOCK IP driver private header file.
*   @details CLOCK IP driver private header file.

*   @addtogroup CLOCK_DRIVER Clock Driver
*   @{
*/

#if !defined(CLOCK_IP_PRIVATE_H)
#define CLOCK_IP_PRIVATE_H

#include "Clock_Ip.h"
#include <stdbool.h>
#include <stddef.h>

#if defined(S32G2XX)
    #include "Clock_Ip_S32G2XX.h"
#elif defined(S32R45)
    #include "Clock_Ip_S32R45.h"
#elif defined(S32K3XX)
    #include "Clock_Ip_S32K3XX.h"
#else
    #error "Unknown platform!"
#endif

#ifdef CLOCK_IP_DEV_ERROR_DETECT
#if (STD_ON == CLOCK_IP_DEV_ERROR_DETECT)
    #include "Devassert.h"
#endif /* (STD_ON == CLOCK_IP_DEV_ERROR_DETECT) */
#endif /* #ifdef CLOCK_IP_DEV_ERROR_DETECT */

 /**
 * @file Clock.h
 *
 * @page misra_violations MISRA-C:2012 violations
 *
 */

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/



/* Total number of clocks */
#define CLOCK_NAMES_NO                    FEATURE_CLOCKS_NO
/* Total number of producer clocks */
#define CLOCK_PRODUCERS_NO                FEATURE_CLOCK_PRODUCERS_NO

/* Define clock features */
#define CLOCK_MODULE_INSTANCE       0U              /* Instance of the module where clock element is implemented. */
#define CLOCK_CALLBACK              1U              /* Actions to be done for different implementations of a clock element. */
#define INTERFACE_CLOCK             2U              /* Name of the interface clock. Without interface clock, peripheral instance is not working. */
#define SELECTOR_INDEX              2U              /* Selector index. */
#define PCFS_INSTANCE               2U              /* Index of device where pcfs is implemented */
#define DIVIDER_INDEX               3U              /* Divider index. */
#define PCTL_INDEX                  3U              /* Index in peripheral configurations. Implemented on some platforms. */
#define PCC_INDEX                   3U              /* Index in peripheral clock control array. Implemented on some platforms. */
#define PARTITION_INDEX             3U              /* Index of partition where clock enable request is implemented. Implemented on some platforms. */
#define COLLECTION_INDEX            4U              /* Index of collection where clock enable request is implemented. Implemented on some platforms. */
#define PCFS_HW_INDEX               4U              /* Hardware index for progressive clock switching (register index) */
#define ENABLE_REQUEST              5U              /* Index of clock enable request. Implemented on some platforms. */
#define PCFS_SW_INDEX               5U              /* Software index for progressive clock switching (driver's cache index) */
#define TRIGGER_FEATURE             5U              /* Divider trigger feature is supported by feature or not */
#define CMU_INSTANCE                6U              /* Cmu instance */
#define CMU_SW_INDEX                7U              /* Cmu software index */


/* Maximum number of clock features for each clock name */
#define CLOCK_FEATURES_NO           8U

#define INV_VAL                     255U            /* Invalid value */
#define NO_TRIGGER                  0U              /* No trigger is supported by divider. */
#define TRIGGER                     1U              /* Trigger is supported by divider. */
#define TRIGGER_VALUE               0xFFFFFFFFU     /* Trigger value. */

#ifdef CLOCK_IP_DEV_ERROR_DETECT
#if (CLOCK_IP_DEV_ERROR_DETECT == STD_ON)
    #define CLOCK_DEV_ASSERT(x)      DevAssert(x)
#endif
#endif

/*! @brief Clock ip source type.
 */
typedef enum
{
    /* Generic error codes */
    UKNOWN_TYPE                                    = 0x00U,    /*!< Clock path from source to this clock name has at least one selector. */
    IRCOSC_TYPE                                    = 0x01U,    /*!< Source is an internal oscillator. */
    XOSC_TYPE                                      = 0x02U,    /*!< Source is an external oscillator. */
    PLL_TYPE                                       = 0x03U,    /*!< Source is a pll. */
	EXT_CLK_TYPE                                   = 0x04U,    /*!< Source is an external clock. */
	SERDES_TYPE                                    = 0x04U,    /*!< Source is a SERDES. */

} clock_name_source_type_t;

/*! @brief Clock pll status return codes.
 */
typedef enum
{
    STATUS_PLL_NOT_ENABLED                         = 0x00U,    /*!< Not enabled */
    STATUS_PLL_UNLOCKED                            = 0x01U,    /*!< Unlocked */
    STATUS_PLL_LOCKED                              = 0x02U,    /*!< Locked */

} clock_pll_status_t;

/*! @brief Clock dfs status return codes.
 */
typedef enum
{
    STATUS_DFS_NOT_ENABLED                         = 0x00U,    /*!< Not enabled */
    STATUS_DFS_UNLOCKED                            = 0x01U,    /*!< Unlocked */
    STATUS_DFS_LOCKED                              = 0x02U,    /*!< Locked */

} clock_dfs_status_t;

/*! @brief Clock cmu status return codes.
 */
typedef enum
{
	STATUS_CMU_NOT_ENABLED                         = 0x00U,    /*!< Not enabled */
	STATUS_CMU_IN_RANGE                            = 0x01U,    /*!< In range */
	STATUS_CMU_FREQ_HIGHER                         = 0x02U,    /*!< Frequency higher than high reference event status */
	STATUS_CMU_FREQ_LOWER                          = 0x03U,    /*!< Frequency lower than high reference event status */

} clock_cmu_status_t;


/*! @brief Clock state - selector entry index for selector elements, on/off state for the other clock elements
 */
typedef enum
{
	DISABLED_CLOCK                                 = 0x00U,     /*!< Clock is disabled. */
	SELECTOR_ENTRY_1                               = 0x01U,    /*!< 1st selector entry. */
	SELECTOR_ENTRY_2                               = 0x02U,    /*!< 2nd selector entry. */
	SELECTOR_ENTRY_3                               = 0x03U,    /*!< 3rd selector entry. */
	SELECTOR_ENTRY_4                               = 0x04U,    /*!< 4th selector entry. */
	SELECTOR_ENTRY_5                               = 0x05U,    /*!< 5th selector entry. */
	SELECTOR_ENTRY_6                               = 0x06U,    /*!< 6th selector entry. */
	SELECTOR_ENTRY_7                               = 0x07U,    /*!< 7th selector entry. */
	SELECTOR_ENTRY_8                               = 0x08U,    /*!< 8th selector entry. */
	SELECTOR_ENTRY_9                               = 0x09U,    /*!< 9th selector entry. */
	SELECTOR_ENTRY_10                              = 0xAU,     /*!< 10th selector entry. */
	SELECTOR_ENTRY_11                              = 0xBU,     /*!< 11th selector entry. */
	SELECTOR_ENTRY_12                              = 0xCU,     /*!< 12th selector entry. */
	SELECTOR_ENTRY_13                              = 0xDU,     /*!< 13th selector entry. */
	SELECTOR_ENTRY_14                              = 0xEU,     /*!< 14th selector entry. */
	SELECTOR_ENTRY_15                              = 0xFU,     /*!< 15th selector entry. */
	SELECTOR_ENTRY_16                              = 0x10U,    /*!< 16th selector entry. */
	SELECTOR_ENTRY_17                              = 0x11U,    /*!< 17th selector entry. */
	SELECTOR_ENTRY_18                              = 0x12U,    /*!< 18th selector entry. */
	SELECTOR_ENTRY_19                              = 0x13U,    /*!< 19th selector entry. */
	ENABLED_CLOCK                                  = 0xFFU,     /*!< Clock is disabled. */

} clock_element_state_t;



typedef void (*intOscSetCallback)(Clock_Ip_IrcoscConfigType const * config);
typedef struct
{
	intOscSetCallback Set;

}intOscCallback;

typedef void (*extOscSetCallback)(Clock_Ip_XoscConfigType const * config);
typedef void (*extOscResetCallback)(Clock_Ip_XoscConfigType const * config);
typedef struct
{
	extOscResetCallback Reset;
	extOscSetCallback Set;

}extOscCallback;


typedef void (*dividerSetCallback)(Clock_Ip_DividerConfigType const * config);
typedef struct
{
	dividerSetCallback Set;

}dividerCallback;

typedef void (*dividerConfigureCallback)(Clock_Ip_DividerTriggerConfigType const * config);
typedef void (*dividerTriggerUpdateCallback)(Clock_Ip_DividerTriggerConfigType const * config);
typedef struct
{
	dividerConfigureCallback Configure;
	dividerTriggerUpdateCallback TriggerUpdate;

}dividerTriggerCallback;


typedef void (*fracDivSetCallback)(Clock_Ip_FracDivConfigType const * config);
typedef void (*fracDivResetCallback)(Clock_Ip_FracDivConfigType const * config);
typedef clock_dfs_status_t (*fracDivCompleteCallback)(Clock_Ip_FracDivConfigType const * config);
typedef struct
{
    fracDivResetCallback Reset;
	fracDivSetCallback Set;
	fracDivCompleteCallback Complete;

}fracDivCallback;

typedef void (*pllSetCallback)(Clock_Ip_PllConfigType const * config);
typedef void (*pllResetCallback)(Clock_Ip_PllConfigType const * config);
typedef clock_pll_status_t (*pllCompleteCallback)(Clock_Ip_PllConfigType const * config);
typedef struct
{
	pllResetCallback Reset;
	pllSetCallback Set;
	pllCompleteCallback Complete;

}pllCallback;

typedef void (*selectorSetCallback)(Clock_Ip_SelectorConfigType const * config);
typedef void (*selectorResetCallback)(Clock_Ip_SelectorConfigType const * config);
typedef struct
{
	selectorResetCallback Reset;
	selectorSetCallback Set;

}selectorCallback;

typedef void (*gateSetCallback)(Clock_Ip_GateConfigType const * config);
typedef void (*gateUpdateCallback)(Clock_Ip_NameType clockName, boolean gate);
typedef struct
{
	gateSetCallback Set;
	gateUpdateCallback Update;

}gateCallback;

typedef void (*clockMonitorSetCallback)(Clock_Ip_CmuConfigType const * config);
typedef void (*clockMonitorResetCallback)(Clock_Ip_CmuConfigType const * config);
typedef void (*clockMonitorClearStatusCallback)(Clock_Ip_NameType name);
typedef void (*clockMonitorDisableCallback)(Clock_Ip_NameType name);
typedef Clock_Ip_CmuStatusType (*clockMonitorGetMonitorStatusCallback)(Clock_Ip_NameType name);
typedef struct
{
	clockMonitorResetCallback Reset;
	clockMonitorSetCallback Set;
	clockMonitorDisableCallback Disable;
	clockMonitorClearStatusCallback Clear;
	clockMonitorGetMonitorStatusCallback GetStatus;

}clockMonitorCallback;


typedef void (*pcfsSetCallback)(Clock_Ip_PcfsConfigType const * config);
typedef struct
{
	pcfsSetCallback Set;

}pcfsCallback;

typedef uint32 (*consumerClockCallback)(void);
typedef void (*CalcFreqCallback)(void);


/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED

#include "Mcu_MemMap.h"

extern const uint8 xoscCallbackIndex[ALL_CALLBACKS_COUNT];
extern const extOscCallback extOscCallbacks[XOSC_CALLBACKS_COUNT];

extern const uint8 dividerCallbackIndex[ALL_CALLBACKS_COUNT];
extern const dividerCallback dividerCallbacks[DIVIDER_CALLBACKS_COUNT];

extern const uint8 dividertriggerCallbackIndex[ALL_CALLBACKS_COUNT];
extern const dividerTriggerCallback dividerTriggerCallbacks[DIVIDERTRIGGER_CALLBACKS_COUNT];

extern const uint8 fractional_dividerCallbackIndex[ALL_CALLBACKS_COUNT];
extern const fracDivCallback fracDivCallbacks[FRACTIONAL_DIVIDER_CALLBACKS_COUNT];

extern const uint8 pllCallbackIndex[ALL_CALLBACKS_COUNT];
extern const pllCallback pllCallbacks[PLL_CALLBACKS_COUNT];

extern const uint8 selectorCallbackIndex[ALL_CALLBACKS_COUNT];
extern const selectorCallback selectorCallbacks[SELECTOR_CALLBACKS_COUNT];

extern const uint8 ircoscCallbackIndex[ALL_CALLBACKS_COUNT];
extern const intOscCallback intOscCallbacks[IRCOSC_CALLBACKS_COUNT];

extern const uint8 cmuCallbackIndex[ALL_CALLBACKS_COUNT];
extern const clockMonitorCallback cmuCallbacks[CMU_CALLBACKS_COUNT];

extern const uint8 gateCallbackIndex[ALL_CALLBACKS_COUNT];
extern const gateCallback gateCallbacks[GATE_CALLBACKS_COUNT];

extern const uint8 pcfsCallbackIndex[ALL_CALLBACKS_COUNT];
extern const pcfsCallback pcfsCallbacks[PCFS_CALLBACKS_COUNT];

extern const consumerClockCallback consumerClockCallbacks[CONSUMER_CALLBACKS_COUNT];

extern const clock_name_source_type_t clockName_sourceType[CLOCK_PRODUCERS_NO];

extern const CalcFreqCallback calcFreqCallbacks[CALC_FREQ_CALLBACKS_NO];

extern const uint8 clockFeatures[CLOCK_NAMES_NO][CLOCK_FEATURES_NO];

extern const uint16 selectorEntry_hardwareValue[CLOCK_PRODUCERS_NO];
extern const clock_element_state_t selectorEntryIndex[SELECTOR_HARDWARE_VALUES_NO];

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED

#include "Mcu_MemMap.h"

/* Clock start section code */
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"

void ReportClockErrors(Clock_Ip_ClockNotificationType error, Clock_Ip_NameType clockName);
void UpdateClockState(Clock_Ip_NameType name, clock_element_state_t state);
clock_element_state_t GetClockState(Clock_Ip_NameType name);

void SpecificPeripheralClockInitialization(Clock_IP_SpecificPeriphConfigType const * config);
void SpecificPlatformInitClock(Clock_Ip_ClockConfigType const * config);
uint32 GetProducerClockFreq(Clock_Ip_NameType clockName);
void Clock_Ip_TimeDelay(void);
void UpdateFrequencies(power_modes_t powerMode);
ISR(Mcu_Cmu_ClockFailIsr);
#ifdef FEATURE_CLOCK_IP_HAS_RAM_WAIT_STATES
    void SetRamWaitStates(void);
#endif
#ifdef FEATURE_CLOCK_IP_HAS_FLASH_WAIT_STATES
    void SetFlashWaitStates(void);
#endif
/*!
 * @brief Initializes a starting reference point for timeout
 *
 * @param[out] startTimeOut    The starting time from which elapsed time is measured
 * @param[out] elapsedTimeOut  The elapsed time to be passed to ClockTimeoutExpired
 * @param[out] timeoutTicksOut The timeout value (in ticks) to be passed to ClockTimeoutExpired
 * @param[in]  timeoutUs       The timeout value (in microseconds)
 */
void ClockStartTimeout(uint32 *startTimeOut,
                       uint32 *elapsedTimeOut,
                       uint32 *timeoutTicksOut,
                       uint32 timeoutUs);
/*!
 * @brief Checks for timeout condition.
 *
 * @param[in,out] startTimeInOut    The starting time from which elapsed time is measured
 * @param[in,out] elapsedTimeInOut  The accumulated elapsed time from the starting time reference
 * @param[in]     TimeoutTicks      The timeout limit (in ticks)
 */
boolean ClockTimeoutExpired(uint32 *startTimeInOut,
                            uint32 *elapsedTimeInOut,
                            uint32 TimeoutTicks);

/* Clock stop section code */
#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*! @}*/

#endif /* CLOCK_IP_PRIVATE_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
