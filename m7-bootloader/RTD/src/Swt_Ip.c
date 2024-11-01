/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : Swt
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
*   @file
*
*   @addtogroup Swt
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif


/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/
#include "Swt_Ip.h"
#include "Devassert.h"
#include "SchM_Wdg.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SWT_IP_VENDOR_ID_C                      43
#define SWT_IP_AR_RELEASE_MAJOR_VERSION_C       4
#define SWT_IP_AR_RELEASE_MINOR_VERSION_C       4
#define SWT_IP_AR_RELEASE_REVISION_VERSION_C    0
#define SWT_IP_SW_MAJOR_VERSION_C               1
#define SWT_IP_SW_MINOR_VERSION_C               0
#define SWT_IP_SW_PATCH_VERSION_C               0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/

/* Check if current file and Swt_Ip header file are of the same vendor */
#if (SWT_IP_VENDOR_ID_C != SWT_IP_VENDOR_ID)
#error "Swt_Ip.c and Swt_Ip.h have different vendor ids"
#endif

/* Check if current file and Swt_Ip header file are of the same Autosar version */
#if ((SWT_IP_AR_RELEASE_MAJOR_VERSION_C     != SWT_IP_AR_RELEASE_MAJOR_VERSION) || \
     (SWT_IP_AR_RELEASE_MINOR_VERSION_C     != SWT_IP_AR_RELEASE_MINOR_VERSION) || \
     (SWT_IP_AR_RELEASE_REVISION_VERSION_C  != SWT_IP_AR_RELEASE_REVISION_VERSION))
#error "AutoSar Version Numbers of Swt_Ip.c and Swt_Ip.h are different"
#endif

/* Check if current file and Swt_Ip header file are of the same software version */
#if ((SWT_IP_SW_MAJOR_VERSION_C != SWT_IP_SW_MAJOR_VERSION) || \
     (SWT_IP_SW_MINOR_VERSION_C != SWT_IP_SW_MINOR_VERSION) || \
     (SWT_IP_SW_PATCH_VERSION_C != SWT_IP_SW_PATCH_VERSION))
#error "Software Version Numbers of Swt_Ip.c and Swt_Ip.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if current file and Devassert header file are of the same Autosar version */
    #if ((SWT_IP_AR_RELEASE_MAJOR_VERSION_C    != DEVASSERT_AR_RELEASE_MAJOR_VERSION) || \
        (SWT_IP_AR_RELEASE_MINOR_VERSION_C     != DEVASSERT_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Swt_Ip_Irq.c and Osif.h are different"
    #endif
    
    /* Check if current file and StandardTypes header file are of the same Autosar version */
    #if ((SWT_IP_AR_RELEASE_MAJOR_VERSION_C    != STD_AR_RELEASE_MAJOR_VERSION) || \
        (SWT_IP_AR_RELEASE_MINOR_VERSION_C     != STD_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Swt_Ip_Irq.c and StandardTypes.h are different"
    #endif

    /* Check if current file and StandardTypes header file are of the same Autosar version */
    #if ((SWT_IP_AR_RELEASE_MAJOR_VERSION_C    != SCHM_WDG_AR_RELEASE_MAJOR_VERSION) || \
        (SWT_IP_AR_RELEASE_MINOR_VERSION_C     != SCHM_WDG_AR_RELEASE_MINOR_VERSION))
    #error "AutoSar Version Numbers of Swt_Ip_Irq.c and StandardTypes.h are different"
    #endif
#endif /* DISABLE_MCAL_INTERMODULE_ASR_CHECK */

/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/

#define WDG_START_SEC_CONST_UNSPECIFIED
/**
* @brief Include Memory mapping specification
*/
#include "Wdg_MemMap.h"

static SWT_Type * const s_swtBase[SWT_INSTANCE_COUNT] = SWT_BASE_PTRS;

#define WDG_STOP_SEC_CONST_UNSPECIFIED
/**
* @brief Include Memory mapping specification
*/
#include "Wdg_MemMap.h"

#define WDG_START_SEC_VAR_NO_INIT_UNSPECIFIED
/**
* @brief Include Memory mapping specification
*/
#include "Wdg_MemMap.h"

static Swt_CallbackPtrType Swt_Ip_apCallbackPtr[SWT_INSTANCE_COUNT];

#define WDG_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/**
* @brief Include Memory mapping specification
*/
#include "Wdg_MemMap.h"

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

#ifdef WDG_ROM
    #if (WDG_ROM == 1U)
        #define WDG_START_SEC_CODE
    #endif
#else
    #if (WDG_RAM == 0U)
        #define WDG_START_SEC_RAMCODE
    #endif
#endif
/**
* @brief Include Memory mapping specification
*/
#include "Wdg_MemMap.h"

static inline boolean Swt_Ip_IsEnable(const SWT_Type * const base)
{
    /* Checks whether the SWT is enabled */
    return ((base->CR & SWT_CR_WEN_MASK) != 0U);
}

static inline void Swt_Ip_Enable(SWT_Type * const base)
{
    /* Enables the SWT */
    base->CR |= SWT_CR_WEN_MASK;
}

static inline void Swt_Ip_Disable(SWT_Type * const base)
{
    /* Enables the SWT */
    base->CR &= ~SWT_CR_WEN_MASK;
}

static Swt_Ip_LockType Swt_Ip_GetLock(const SWT_Type * const base)
{
    Swt_Ip_LockType lockMode = SWT_IP_UNLOCK;

    switch ((base->CR & (SWT_CR_SLK_MASK | SWT_CR_HLK_MASK)) >> SWT_CR_SLK_SHIFT)
    {
        case 0U:
            lockMode = SWT_IP_UNLOCK;
            break;
        case 1U:
            lockMode = SWT_IP_SOFTLOCK;
            break;
        case 2U:
            lockMode = SWT_IP_HARDLOCK;
            break;
        default:
            lockMode = SWT_IP_HARDLOCK;
            break;
    }

    return lockMode;
}

static void Swt_Ip_Lock(SWT_Type * const base,
                 Swt_Ip_LockType lockConfig)
{
    /* Configures lock bits */
    switch (lockConfig)
    {
        /* Hard lock */
        case SWT_IP_HARDLOCK:
            base->CR |= SWT_CR_HLK(1U);
            break;
        /* Soft lock */
        case SWT_IP_SOFTLOCK:
            base->CR |= SWT_CR_SLK(1U);
            break;
        /* Unlock */
        default:
            /* Do nothing */
            break;
    }
}

static Swt_Ip_StatusType Swt_Ip_Unlock(SWT_Type * const base)
{
    Swt_Ip_StatusType ret = SWT_IP_STATUS_SUCCESS;
    uint8 timeout = SWT_IP_UNLOCK_TIMEOUT;

    /* Hard lock */
    if ((base->CR & SWT_CR_HLK_MASK) != 0U)
    {
        ret = SWT_IP_STATUS_ERROR;
    }
    else
    {
        /* Soft lock */
        if ((base->CR & SWT_CR_SLK_MASK) != 0U)
        {
            /* Unlocks sequence */
            base->SR = SWT_SR_WSC(SWT_IP_UNLOCK_VALUE1);
            base->SR = SWT_SR_WSC(SWT_IP_UNLOCK_VALUE2);

            /* Waits unlock complete */
            while (((base->CR & SWT_CR_SLK_MASK) != 0U) && (timeout-- > 0))
            {
                /* Do nothing */
            }
            if(timeout == 0U)
            {
                ret = SWT_IP_STATUS_ERROR;
            }
        }
        /* Unlock */
        else
        {
            /* Do nothing */
        }
    }

    return ret;
}

static void Swt_Ip_RegisterConfig(SWT_Type * const base,
                                     const Swt_Ip_ConfigType * const Swt_Ip_pConfig)
{
    /* Temporary storage for control register value */
    uint32 cr = 0x00UL;

    /* Sets control configuration */
    cr = (SWT_IP_MAP(Swt_Ip_pConfig->u8MapEnBitmask)
        | SWT_CR_SMD(Swt_Ip_pConfig->bEnKeyedService ? 1UL : 0UL)
        | SWT_CR_RIA(Swt_Ip_pConfig->bEnResetOnInvalidAccess ? 1UL : 0UL)
        | SWT_CR_WND(Swt_Ip_pConfig->bEnWindow ? 1UL : 0UL)
        | SWT_CR_ITR(Swt_Ip_pConfig->bEnInterrupt ? 1UL : 0UL)
        | SWT_CR_STP(Swt_Ip_pConfig->bEnRunInStopMode? 0UL : 1UL)
        | SWT_CR_FRZ(Swt_Ip_pConfig->bEnRunInDebugMode ? 0UL : 1UL));

    /* Write configuration to the SWT CR register*/
    base->CR = cr;

    /* Clears interrupt flags */

    base->IR = SWT_IR_TIF_MASK;

    /* Sets timeout value */
    base->TO = Swt_Ip_pConfig->u32TimeoutValue;

    /* Sets window value */
    if (Swt_Ip_pConfig->bEnWindow)
    {
        base->WN = Swt_Ip_pConfig->u32WindowValue;
    }

    /* Sets initial service key value */
    if (Swt_Ip_pConfig->bEnKeyedService)
    {
        base->SK = SWT_SK_SK(Swt_Ip_pConfig->u16InitialKey);
    }
}

static Swt_Ip_StatusType Swt_Ip_CheckTimeout(uint32 u32TimeoutValue, uint32 u32WindowValue)
{
    Swt_Ip_StatusType ret = SWT_IP_STATUS_SUCCESS;

    if (u32TimeoutValue < SWT_IP_TO_MINIMUM_VALUE)
    {
        ret = SWT_IP_STATUS_ERROR;
    }

    if ((u32WindowValue != 0) && (u32TimeoutValue <= u32WindowValue))
    {
        ret = SWT_IP_STATUS_ERROR;
    }

    return ret;
}

static inline void Swt_Ip_ServiceCmd(SWT_Type * const base,
                                        uint16 u16ServiceKey)
{
    base->SR = (base->SR & ~SWT_SR_WSC_MASK) | SWT_SR_WSC(u16ServiceKey);
}

static inline boolean Swt_Ip_IsKeyedServiceMode(const SWT_Type * const base)
{
    /* Is Keyed Service Mode used? */
    return (((base->CR & SWT_CR_SMD_MASK) >> SWT_CR_SMD_SHIFT) == 1U);
}

static inline uint16 Swt_Ip_ServiceKeyGen(const SWT_Type * const base)
{
    /* Generates the next key used to service the SWT */
    return ((uint16)((((base->SK & SWT_SK_SK_MASK) >> SWT_SK_SK_SHIFT) * 17U) + 3U));
}

#if (SWT_IP_DEINIT == STD_ON)
    #if (SWT_IP_CLEAR_RESET_REQUEST == STD_ON)
        static inline boolean Swt_Ip_RequestedReset(const SWT_Type * const base)
        {
            return (((base->RRR & SWT_RRR_RRF_MASK)>> SWT_RRR_RRF_SHIFT) == 1U);
        }
    #endif
#endif

#if (SWT_IP_DEINIT == STD_ON)
static inline void Swt_Ip_ClearRequest(SWT_Type * const base)
{
    base->RRR = SWT_RRR_RRF(1U);
}
#endif

static inline boolean Swt_Ip_GetIntFlag(const SWT_Type * const base)
{
    return ((base->IR & SWT_IR_TIF_MASK) != 0U);
}

static inline boolean Swt_Ip_IsIntEnabled(const SWT_Type * const base)
{
    return ((base->CR & SWT_CR_ITR_MASK ) != 0U);
}

static inline void Swt_Ip_ClearIntFlag(SWT_Type * const base)
{
    base->IR &= SWT_IR_TIF_MASK;
}


/*==================================================================================================
*                                 GLOBAL FUNCTIONS PROTOTYPES
==================================================================================================*/

void Swt_Ip_IrqHandler(uint32 u32Instance);

/*==================================================================================================
*                                      GLOBAL FUNCTIONS
==================================================================================================*/

/**
* @Description    This function initializes SWT instance.
*
* @implements     Swt_Ip_Init_Activity
*/
Swt_Ip_StatusType Swt_Ip_Init(const uint32 u32Instance,
                            const Swt_Ip_ConfigType * const Swt_Ip_pConfig)
{
    SWT_Type * const base = s_swtBase[u32Instance];
    Swt_Ip_StatusType ret = SWT_IP_STATUS_SUCCESS;

#if (SWT_IP_DEV_ERROR_DETECT == STD_ON)
    DevAssert(u32Instance < SWT_INSTANCE_COUNT);
    DevAssert(Swt_Ip_pConfig != NULL);
#endif

    if ((Swt_Ip_IsEnable(base)) || ((boolean)(Swt_Ip_Unlock(base) == SWT_IP_STATUS_ERROR)))
    {
        ret = SWT_IP_STATUS_ERROR;
    }
    else
    {
        /* Verify if the timeout and window values are within accepted range */
        ret = Swt_Ip_CheckTimeout(Swt_Ip_pConfig->u32TimeoutValue, Swt_Ip_pConfig->u32WindowValue);

        if (ret == SWT_IP_STATUS_SUCCESS)
        {
            /* Configures the SWT instance */
            Swt_Ip_RegisterConfig(base, Swt_Ip_pConfig);

            if(Swt_Ip_pConfig->bEnInterrupt)
            {
                Swt_Ip_apCallbackPtr[u32Instance] = Swt_Ip_pConfig->pfSwtCallback;
            }

            /* Enable the SWT timer */
            Swt_Ip_Enable(base);

            /* Lock the SWT */
            Swt_Ip_Lock(base, Swt_Ip_pConfig->lockConfig);
        }
    }

    return ret;
}

#if (SWT_IP_DEINIT == STD_ON)
/**
* @Description    This function de-initializes SWT instance.
*
* @implements     Swt_Ip_Deinit_Activity
*/
    Swt_Ip_StatusType Swt_Ip_Deinit(const uint32 u32Instance)
    {
        SWT_Type * const base = s_swtBase[u32Instance];
        Swt_Ip_StatusType ret;

    #if (SWT_IP_DEV_ERROR_DETECT == STD_ON)
        DevAssert(u32Instance < SWT_INSTANCE_COUNT);
    #endif

        /* Unlocks SWT instance */
        ret = Swt_Ip_Unlock(base);

        if (ret == SWT_IP_STATUS_SUCCESS)
        {
            /* Disable SWT timer */
            Swt_Ip_Disable(base);

            /* Clears interrupt flag */
            base->IR = SWT_IR_TIF_MASK;
            /* Resets timeout value */
            base->TO = SWT_IP_TO_RESET_VALUE;
            /* Resets window value */
            base->WN = SWT_IP_WN_RESET_VALUE;
            /* Resets service key value */
            base->SK = SWT_IP_SK_RESET_VALUE;
            /* Resets control register */
            base->CR = SWT_IP_CR_RESET_VALUE;
            /* Clear RRF bit in RRR register */
            Swt_Ip_ClearRequest(base);
        }

        return ret;
    }
#endif

/**
* @Description    This function services SWT instance.
*
* @implements     Swt_Ip_Service_Activity
*/
void Swt_Ip_Service(const uint32 u32Instance)
{
    SWT_Type * const base = s_swtBase[u32Instance];
    boolean bUnlockSequence = FALSE;

#if (SWT_IP_DEV_ERROR_DETECT == STD_ON)
    DevAssert(u32Instance < SWT_INSTANCE_COUNT);
#endif

    SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_09();
    if (Swt_Ip_IsKeyedServiceMode(base))
    {
        /* Keyed Service Sequence Mode */
        bUnlockSequence = (Swt_Ip_ServiceKeyGen(base) == SWT_IP_UNLOCK_VALUE1) ? TRUE : bUnlockSequence;
        Swt_Ip_ServiceCmd(base, Swt_Ip_ServiceKeyGen(base));
        bUnlockSequence = (Swt_Ip_ServiceKeyGen(base) == SWT_IP_UNLOCK_VALUE1) ? TRUE : bUnlockSequence;
        Swt_Ip_ServiceCmd(base, Swt_Ip_ServiceKeyGen(base));

        if ((Swt_Ip_GetLock(base) == SWT_IP_SOFTLOCK) && (bUnlockSequence == TRUE))
        {
            /* Unlock key generated. Complete the unlock sequence and lock it again. */
            Swt_Ip_ServiceCmd(base, SWT_IP_UNLOCK_VALUE2);
            Swt_Ip_Lock(base, SWT_IP_SOFTLOCK);
        }
    }
    else
    {
        /* Fixed Service Sequence Mode */
        Swt_Ip_ServiceCmd(base, SWT_IP_FIXED_SERVICE_VALUE1);
        Swt_Ip_ServiceCmd(base, SWT_IP_FIXED_SERVICE_VALUE2);
    }
    SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_09();
}


/**
* @Description    This function configure SWT instance.
*
* @implements     Swt_Ip_Config_Activity
*/
Swt_Ip_StatusType Swt_Ip_Config(const uint32 u32Instance,
                              const Swt_Ip_ConfigType * const Swt_Ip_pConfig)
{
    SWT_Type * const base = s_swtBase[u32Instance];
    Swt_Ip_StatusType ret;

#if (SWT_IP_DEV_ERROR_DETECT == STD_ON)
    DevAssert(u32Instance < SWT_INSTANCE_COUNT);
    DevAssert(Swt_Ip_pConfig != NULL);
#endif

    ret = Swt_Ip_CheckTimeout(Swt_Ip_pConfig->u32TimeoutValue, Swt_Ip_pConfig->u32WindowValue);

    if (ret == SWT_IP_STATUS_SUCCESS)
    {
        if(Swt_Ip_Unlock(base) == SWT_IP_STATUS_ERROR)
        {
            ret = SWT_IP_STATUS_ERROR;
        }
        else
        {
            boolean bSwtEnabled = Swt_Ip_IsEnable(base);

            if (bSwtEnabled)
            {
                Swt_Ip_Disable(base);
            }

            /* Configures the SWT instance */
            Swt_Ip_RegisterConfig(base, Swt_Ip_pConfig);

            /* If the timer was enebled, enable it after configuration is done */
            if (bSwtEnabled)
            {
                Swt_Ip_Enable(base);
            }
            /* Lock the SWT */
            Swt_Ip_Lock(base, Swt_Ip_pConfig->lockConfig);
        }
    }

    return ret;
}

/**
* @Description    This function sets the timeout value for the SWT instance.
*
* @implements     Swt_Ip_SetTimeout_Activity
*/
Swt_Ip_StatusType Swt_Ip_SetTimeout(const uint32 u32Instance,
                                    const uint32 u32TimeoutValue, const uint32 u32WindowValue)
{
    SWT_Type * const base = s_swtBase[u32Instance];
    Swt_Ip_LockType lockConfig;
    Swt_Ip_StatusType ret;

#if (SWT_IP_DEV_ERROR_DETECT == STD_ON)
    DevAssert(u32Instance < SWT_INSTANCE_COUNT);
#endif

    lockConfig = Swt_Ip_GetLock(base);
    ret = Swt_Ip_CheckTimeout(u32TimeoutValue, u32WindowValue);

    if (ret == SWT_IP_STATUS_SUCCESS)
    {
        if(Swt_Ip_Unlock(base) == SWT_IP_STATUS_ERROR)
        {
            ret = SWT_IP_STATUS_ERROR;
        }
        else
        {
            /* Stop the SWT timer */
            Swt_Ip_Disable(base);

            /* Sets timeout value */
            base->TO = u32TimeoutValue;

            /* Sets window value */
            if (u32WindowValue > 0)
            {
                base->WN = u32WindowValue;
                /* Enable Windowed Mode */
                base->CR |= SWT_CR_WND_MASK;
            }
            else
            {
                base->CR &= ~SWT_CR_WND_MASK;
            }

            /* Start the SWT timer */
            Swt_Ip_Enable(base);

            /* Lock the SWT */
            Swt_Ip_Lock(base, lockConfig);
        }
    }

    return ret;
}

/**
* @Description    This function starts the timer for the SWT instance.
*
* @implements     Swt_Ip_StartTimer_Activity
*/
Swt_Ip_StatusType Swt_Ip_StartTimer(const uint32 u32Instance)
{
    SWT_Type * const base = s_swtBase[u32Instance];
    Swt_Ip_LockType lockConfig;
    Swt_Ip_StatusType ret;

#if (SWT_IP_DEV_ERROR_DETECT == STD_ON)
    DevAssert(u32Instance < SWT_INSTANCE_COUNT);
#endif

    lockConfig = Swt_Ip_GetLock(base);
    /* Unlocks the SWT */
    SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_10();
    ret = Swt_Ip_Unlock(base);

    if (ret == SWT_IP_STATUS_SUCCESS)
    {
        /* Start the SWT timer */
        Swt_Ip_Enable(base);

        Swt_Ip_Lock(base, lockConfig);
    }
    SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_10();

    return ret;
}

/**
* @Description    This function stops the timer for the SWT instance.
*
* @implements     Swt_Ip_StopTimer_Activity
*/
Swt_Ip_StatusType Swt_Ip_StopTimer(const uint32 u32Instance)
{
    SWT_Type * const base = s_swtBase[u32Instance];
    Swt_Ip_LockType lockConfig;
    Swt_Ip_StatusType ret;

#if (SWT_IP_DEV_ERROR_DETECT == STD_ON)
    DevAssert(u32Instance < SWT_INSTANCE_COUNT);
#endif

    lockConfig = Swt_Ip_GetLock(base);
    /* Unlocks the SWT */
    SchM_Enter_Wdg_WDG_EXCLUSIVE_AREA_11();
    ret = Swt_Ip_Unlock(base);

    if (ret == SWT_IP_STATUS_SUCCESS)
    {
        /* Start the SWT timer */
        Swt_Ip_Disable(base);

        Swt_Ip_Lock(base, lockConfig);
    }
    SchM_Exit_Wdg_WDG_EXCLUSIVE_AREA_11();

    return ret;
}

#if (SWT_IP_DEINIT == STD_ON)
#if (SWT_IP_CLEAR_RESET_REQUEST == STD_ON)
/**
* @Description    This function clears reset request.
*
* @implements     Swt_Ip_ClearResetRequest_Activity
*/
    Swt_Ip_StatusType Swt_Ip_ClearResetRequest(const uint32 u32Instance)
    {
        SWT_Type * const base = s_swtBase[u32Instance];
        Swt_Ip_StatusType ret = SWT_IP_STATUS_SUCCESS;

    #if (SWT_IP_DEV_ERROR_DETECT == STD_ON)
        DevAssert(u32Instance < SWT_INSTANCE_COUNT);
    #endif

        /* Can the SWT instance be reset without system reset */
        ret = ((SWT_IP_RRR_SUPPORT & (1UL << u32Instance)) != 0UL) ? SWT_IP_STATUS_SUCCESS : SWT_IP_STATUS_ERROR;

        if (Swt_Ip_RequestedReset(base) && (ret == SWT_IP_STATUS_SUCCESS))
        {   /* Reset the SWT instance */
            Swt_Ip_ClearRequest(base);
        }
        else
        {   /* SWT has not requested a reset */
            ret = SWT_IP_STATUS_ERROR;
        }
        /* Wait for the SWT instance to finish reseting */
        while (Swt_Ip_RequestedReset(base) && (ret == SWT_IP_STATUS_SUCCESS)) { }

        return ret;
    }
#endif
#endif
/**
* @Description    This function handles the swt interrupt request.
*
* @implements     Swt_Ip_IrqHandler_Activity
*/
void Swt_Ip_IrqHandler(uint32 u32Instance)
{
    SWT_Type * const base = s_swtBase[u32Instance];

#if (SWT_IP_DEV_ERROR_DETECT == STD_ON)
    DevAssert(u32Instance < SWT_INSTANCE_COUNT);
#endif

    if  (Swt_Ip_GetIntFlag(base))
    {
        Swt_Ip_ClearIntFlag(base);

        if((Swt_Ip_apCallbackPtr[u32Instance] != ((void *)0)) && (Swt_Ip_IsIntEnabled(base)))
        {
            Swt_Ip_apCallbackPtr[u32Instance]();
        }
    }
}

#ifdef WDG_ROM
    #if (WDG_ROM == 1U)
        #define WDG_STOP_SEC_CODE
    #endif
#else
    #if (WDG_RAM == 0U)
        #define WDG_STOP_SEC_RAMCODE
    #endif
#endif
/**
* @brief Include Memory mapping specification
*/
#include "Wdg_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
