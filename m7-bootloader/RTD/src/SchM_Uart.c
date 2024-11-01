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
*   @file
*
*   @addtogroup RTE_MODULE
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"
#include "Mcal.h"
#include "OsIf.h"
#include "SchM_Uart.h"
#ifdef MCAL_TESTING_ENVIRONMENT
#include "EUnit.h" /* EUnit Test Suite */
#endif

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SCHM_UART_AR_RELEASE_MAJOR_VERSION_C     4
#define SCHM_UART_AR_RELEASE_MINOR_VERSION_C     4
#define SCHM_UART_AR_RELEASE_REVISION_VERSION_C  0
#define SCHM_UART_SW_MAJOR_VERSION_C             1
#define SCHM_UART_SW_MINOR_VERSION_C             0
#define SCHM_UART_SW_PATCH_VERSION_C             0

/*==================================================================================================
*                                       LOCAL CONSTANTS
==================================================================================================*/
#ifdef MCAL_PLATFORM_ARM
    #if (MCAL_PLATFORM_ARM == MCAL_ARM_AARCH64)
        #define ISR_STATE_MASK     ((uint32)0x00000002UL)   /**< @brief DAIF bit I and F */
    #elif  (MCAL_PLATFORM_ARM == MCAL_ARM_RARCH)
        #define ISR_STATE_MASK     ((uint32)0x00000080UL)   /**< @brief CPSR bit I */
    #else
        #ifdef MCAL_ENABLE_USER_MODE_SUPPORT
            #define ISR_STATE_MASK     ((uint32)0x000000FFUL)   /**< @brief BASEPRI[7:0] mask */
        #else
            #define ISR_STATE_MASK     ((uint32)0x00000001UL)   /**< @brief PRIMASK bit 0 */
        #endif
    #endif
#else
    #ifdef MCAL_PLATFORM_S12
        #define ISR_STATE_MASK     ((uint32)0x00000010UL)   /**< @brief I bit of CCR */
    #else
        #define ISR_STATE_MASK     ((uint32)0x00008000UL)   /**< @brief EE bit of MSR */
    #endif
#endif
/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#ifdef MCAL_PLATFORM_ARM
    #if (MCAL_PLATFORM_ARM == MCAL_ARM_AARCH64)
        #define ISR_ON(msr)            (uint32)(((uint32)(msr) & (uint32)(ISR_STATE_MASK)) != (uint32)3)
    #elif  (MCAL_PLATFORM_ARM == MCAL_ARM_RARCH)
        #define ISR_ON(msr)            (uint32)(((uint32)(msr) & (uint32)(ISR_STATE_MASK)) != (uint32)(ISR_STATE_MASK))
    #else
        #define ISR_ON(msr)            (uint32)(((uint32)(msr) & (uint32)(ISR_STATE_MASK)) == (uint32)0)
    #endif
#else
    #ifdef MCAL_PLATFORM_S12
        #define ISR_ON(msr)            (uint32)(((uint32)(msr) & (uint32)(ISR_STATE_MASK)) == (uint32)0)
    #else
        #define ISR_ON(msr)            (uint32)((uint32)(msr) & (uint32)(ISR_STATE_MASK))
    #endif
#endif

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/
#define RTE_START_SEC_VAR_NO_INIT_32_NO_CACHEABLE
#include "Rte_MemMap.h"

static uint32 msr_UART_EXCLUSIVE_AREA_00[10];    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_UART_EXCLUSIVE_AREA_01[10];    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_UART_EXCLUSIVE_AREA_02[10];    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_UART_EXCLUSIVE_AREA_03[10];    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_UART_EXCLUSIVE_AREA_04[10];    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_UART_EXCLUSIVE_AREA_05[10];    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_UART_EXCLUSIVE_AREA_06[10];    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_UART_EXCLUSIVE_AREA_07[10];    /**< @brief exclusive area MSR state upon entering*/
static uint32 msr_UART_EXCLUSIVE_AREA_08[10];    /**< @brief exclusive area MSR state upon entering*/

static volatile uint32 reentry_guard_UART_EXCLUSIVE_AREA_00[10]; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_UART_EXCLUSIVE_AREA_01[10]; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_UART_EXCLUSIVE_AREA_02[10]; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_UART_EXCLUSIVE_AREA_03[10]; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_UART_EXCLUSIVE_AREA_04[10]; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_UART_EXCLUSIVE_AREA_05[10]; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_UART_EXCLUSIVE_AREA_06[10]; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_UART_EXCLUSIVE_AREA_07[10]; /**< @brief guard for the msr variable against overwrite*/
static volatile uint32 reentry_guard_UART_EXCLUSIVE_AREA_08[10]; /**< @brief guard for the msr variable against overwrite*/

#define RTE_STOP_SEC_VAR_NO_INIT_32_NO_CACHEABLE
#include "Rte_MemMap.h"
/*==================================================================================================
*                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

#ifndef _COSMIC_C_S32XX_
/*================================================================================================*/
/**
* @brief   This function returns the MSR register value (32 bits).
* @details This function returns the MSR register value (32 bits).
*
* @param[in]     void        No input parameters
* @return        uint32 msr  This function returns the MSR register value (32 bits).
*
* @pre  None
* @post None
*
*/
uint32 Uart_schm_read_msr(void);
#endif /*ifndef _COSMIC_C_S32XX_*/
/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
#define RTE_START_SEC_CODE
#include "Rte_MemMap.h"

#if (defined(_GREENHILLS_C_S32XX_) || defined(_CODEWARRIOR_C_S32XX_))
/*================================================================================================*/
/**
* @brief   This macro returns the MSR register value (32 bits).
* @details This macro function implementation returns the MSR register value in r3 (32 bits).
*
* @pre  None
* @post None
*
*/
#ifdef MCAL_PLATFORM_ARM
#if (MCAL_PLATFORM_ARM == MCAL_ARM_AARCH64)
ASM_KEYWORD uint32 Uart_schm_read_msr(void)
{
    mrs x0, S3_3_c4_c2_1
}
#elif  (MCAL_PLATFORM_ARM == MCAL_ARM_RARCH)
ASM_KEYWORD uint32 Uart_schm_read_msr(void)
{
    mrs r0, CPSR
}
#else
ASM_KEYWORD uint32 Uart_schm_read_msr(void)
{
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
    mrs r0, BASEPRI
#else
    mrs r0, PRIMASK
#endif
}
#endif
#else
#ifdef MCAL_PLATFORM_S12
ASM_KEYWORD uint32 Uart_schm_read_msr(void)
{
   tfr ccr, d6
}
#else
ASM_KEYWORD uint32 Uart_schm_read_msr(void)
{
    mfmsr r3
}
#endif
#endif
#endif /*#ifdef GHS||CW*/

#ifdef _DIABDATA_C_S32XX_
/**
* @brief   This function returns the MSR register value (32 bits).
* @details This function returns the MSR register value (32 bits).
*
* @param[in]     void        No input parameters
* @return        uint32 msr  This function returns the MSR register value (32 bits).
*
* @pre  None
* @post None
*
*/
#ifdef MCAL_PLATFORM_ARM
FUNC(uint32, RTE_CODE) Uart_schm_read_msr(void)
{
    register uint32 reg_tmp;
    #if (MCAL_PLATFORM_ARM == MCAL_ARM_AARCH64)
        __asm volatile( " mrs %x0, DAIF " : "=r" (reg_tmp) );
    #elif  (MCAL_PLATFORM_ARM == MCAL_ARM_RARCH)
        __asm volatile( " mrs %0, CPSR " : "=r" (reg_tmp) );
    #else
        #ifdef MCAL_ENABLE_USER_MODE_SUPPORT
        __asm volatile( " mrs %0, basepri " : "=r" (reg_tmp) );
        #else
        __asm volatile( " mrs %0, primask " : "=r" (reg_tmp) );
        #endif
    #endif
    return (uint32)reg_tmp;
}
#else
ASM_KEYWORD uint32 Uart_schm_read_msr(void)
{
    mfmsr r3
}
#endif  /* MCAL_PLATFORM_ARM */

#endif   /* _DIABDATA_C_S32XX_*/

#ifdef _COSMIC_C_S32XX_
/*================================================================================================*/
/**
* @brief   This function returns the MSR register value (32 bits).
* @details This function returns the MSR register value (32 bits).
*
* @param[in]     void        No input parameters
* @return        uint32 msr  This function returns the MSR register value (32 bits).
*
* @pre  None
* @post None
*
*/

#ifdef MCAL_PLATFORM_S12
    #define Uart_schm_read_msr()  ASM_KEYWORD("tfr ccr, d6")
#else
    #define Uart_schm_read_msr() ASM_KEYWORD("mfmsr r3")
#endif

#endif  /*Cosmic compiler only*/


#ifdef _HITECH_C_S32XX_
/*================================================================================================*/
/**
* @brief   This function returns the MSR register value (32 bits).
* @details This function returns the MSR register value (32 bits).
*
* @param[in]     void        No input parameters
* @return        uint32 msr  This function returns the MSR register value (32 bits).
*
* @pre  None
* @post None
*
*/
uint32 Uart_schm_read_msr(void)
{
    uint32 result;
    __asm volatile("mfmsr %0" : "=r" (result) :);
    return result;
}

#endif  /*HighTec compiler only*/
 /*================================================================================================*/
#ifdef _LINARO_C_S32XX_
/**
* @brief   This function returns the MSR register value (32 bits).
* @details This function returns the MSR register value (32 bits).
*
* @param[in]     void        No input parameters
* @return        uint32 msr  This function returns the MSR register value (32 bits).
*
* @pre  None
* @post None
*
*/
FUNC(uint32, RTE_CODE) Uart_schm_read_msr(void)
{
    register uint32 reg_tmp;
    #if (MCAL_PLATFORM_ARM == MCAL_ARM_AARCH64)
        __asm volatile( " mrs %x0, DAIF " : "=r" (reg_tmp) );
    #elif  (MCAL_PLATFORM_ARM == MCAL_ARM_RARCH)
        __asm volatile( " mrs %0, CPSR " : "=r" (reg_tmp) );
    #else
        #ifdef MCAL_ENABLE_USER_MODE_SUPPORT
        __asm volatile( " mrs %0, basepri " : "=r" (reg_tmp) );
        #else
        __asm volatile( " mrs %0, primask " : "=r" (reg_tmp) );
        #endif
    #endif
    return (uint32)reg_tmp;
}
#endif   /* _LINARO_C_S32XX_*/
/*================================================================================================*/

#ifdef _ARM_DS5_C_S32XX_
/**
* @brief   This function returns the MSR register value (32 bits).
* @details This function returns the MSR register value (32 bits).
*
* @param[in]     void        No input parameters
* @return        uint32 msr  This function returns the MSR register value (32 bits).
*
* @pre  None
* @post None
*
*/
uint32 Uart_schm_read_msr(void)
{
    register uint32 reg_tmp;
    #if (MCAL_PLATFORM_ARM == MCAL_ARM_AARCH64)
        __asm volatile( " mrs %x0, DAIF " : "=r" (reg_tmp) );
    #elif  (MCAL_PLATFORM_ARM == MCAL_ARM_RARCH)
        __asm volatile( " mrs %0, CPSR " : "=r" (reg_tmp) );
    #else
        #ifdef MCAL_ENABLE_USER_MODE_SUPPORT
        __asm volatile( " mrs %0, basepri " : "=r" (reg_tmp) );
        #else
        __asm volatile( " mrs %0, primask " : "=r" (reg_tmp) );
        #endif
    #endif
    return (uint32)reg_tmp;
}
#endif   /* _ARM_DS5_C_S32XX_ */

#ifdef _IAR_C_S32XX_
/**
* @brief   This function returns the MSR register value (32 bits).
* @details This function returns the MSR register value (32 bits).
*
* @param[in]     void        No input parameters
* @return        uint32 msr  This function returns the MSR register value (32 bits).
*
* @pre  None
* @post None
*
*/
uint32 Uart_schm_read_msr(void)
{
    register uint32 reg_tmp;

#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
   __asm volatile( " mrs %0, basepri " : "=r" (reg_tmp) );
#else
   __asm volatile( " mrs %0, primask " : "=r" (reg_tmp) );
#endif

    return (uint32)reg_tmp;
}
#endif   /* _IAR_C_S32XX_ */

#define RTE_STOP_SEC_CODE
#include "Rte_MemMap.h"

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/
#define RTE_START_SEC_CODE
#include "Rte_MemMap.h"

void SchM_Enter_Uart_UART_EXCLUSIVE_AREA_00(void)
{
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    if(0UL == reentry_guard_UART_EXCLUSIVE_AREA_00[u32CoreId])
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
        msr_UART_EXCLUSIVE_AREA_00[u32CoreId] = OsIf_Trusted_Call_Return(Uart_schm_read_msr);
#else
        msr_UART_EXCLUSIVE_AREA_00[u32CoreId] = Uart_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
        if (ISR_ON(msr_UART_EXCLUSIVE_AREA_00[u32CoreId])) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
        {
            OsIf_SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32XX_
            ASM_KEYWORD(" nop ");    /* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
        }
    }
    reentry_guard_UART_EXCLUSIVE_AREA_00[u32CoreId]++;
}

void SchM_Exit_Uart_UART_EXCLUSIVE_AREA_00(void)
{
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    reentry_guard_UART_EXCLUSIVE_AREA_00[u32CoreId]--;
    if ((ISR_ON(msr_UART_EXCLUSIVE_AREA_00[u32CoreId])) && (0UL == reentry_guard_UART_EXCLUSIVE_AREA_00[u32CoreId]))         /* If interrupts were enabled */
    {
        OsIf_ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32XX_
        ASM_KEYWORD(" nop ");    /* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}

void SchM_Enter_Uart_UART_EXCLUSIVE_AREA_01(void)
{
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    if(0UL == reentry_guard_UART_EXCLUSIVE_AREA_01[u32CoreId])
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
        msr_UART_EXCLUSIVE_AREA_01[u32CoreId] = OsIf_Trusted_Call_Return(Uart_schm_read_msr);
#else
        msr_UART_EXCLUSIVE_AREA_01[u32CoreId] = Uart_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
        if (ISR_ON(msr_UART_EXCLUSIVE_AREA_01[u32CoreId])) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
        {
            OsIf_SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32XX_
            ASM_KEYWORD(" nop ");    /* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
        }
    }
    reentry_guard_UART_EXCLUSIVE_AREA_01[u32CoreId]++;
}

void SchM_Exit_Uart_UART_EXCLUSIVE_AREA_01(void)
{
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    reentry_guard_UART_EXCLUSIVE_AREA_01[u32CoreId]--;
    if ((ISR_ON(msr_UART_EXCLUSIVE_AREA_01[u32CoreId])) && (0UL == reentry_guard_UART_EXCLUSIVE_AREA_01[u32CoreId]))         /* If interrupts were enabled */
    {
        OsIf_ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32XX_
        ASM_KEYWORD(" nop ");    /* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}

void SchM_Enter_Uart_UART_EXCLUSIVE_AREA_02(void)
{
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    if(0UL == reentry_guard_UART_EXCLUSIVE_AREA_02[u32CoreId])
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
        msr_UART_EXCLUSIVE_AREA_02[u32CoreId] = OsIf_Trusted_Call_Return(Uart_schm_read_msr);
#else
        msr_UART_EXCLUSIVE_AREA_02[u32CoreId] = Uart_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
        if (ISR_ON(msr_UART_EXCLUSIVE_AREA_02[u32CoreId])) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
        {
            OsIf_SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32XX_
            ASM_KEYWORD(" nop ");    /* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
        }
    }
    reentry_guard_UART_EXCLUSIVE_AREA_02[u32CoreId]++;
}

void SchM_Exit_Uart_UART_EXCLUSIVE_AREA_02(void)
{
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    reentry_guard_UART_EXCLUSIVE_AREA_02[u32CoreId]--;
    if ((ISR_ON(msr_UART_EXCLUSIVE_AREA_02[u32CoreId])) && (0UL == reentry_guard_UART_EXCLUSIVE_AREA_02[u32CoreId]))         /* If interrupts were enabled */
    {
        OsIf_ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32XX_
        ASM_KEYWORD(" nop ");    /* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}

void SchM_Enter_Uart_UART_EXCLUSIVE_AREA_03(void)
{
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    if(0UL == reentry_guard_UART_EXCLUSIVE_AREA_03[u32CoreId])
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
        msr_UART_EXCLUSIVE_AREA_03[u32CoreId] = OsIf_Trusted_Call_Return(Uart_schm_read_msr);
#else
        msr_UART_EXCLUSIVE_AREA_03[u32CoreId] = Uart_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
        if (ISR_ON(msr_UART_EXCLUSIVE_AREA_03[u32CoreId])) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
        {
            OsIf_SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32XX_
            ASM_KEYWORD(" nop ");    /* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
        }
    }
    reentry_guard_UART_EXCLUSIVE_AREA_03[u32CoreId]++;
}

void SchM_Exit_Uart_UART_EXCLUSIVE_AREA_03(void)
{
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    reentry_guard_UART_EXCLUSIVE_AREA_03[u32CoreId]--;
    if ((ISR_ON(msr_UART_EXCLUSIVE_AREA_03[u32CoreId])) && (0UL == reentry_guard_UART_EXCLUSIVE_AREA_03[u32CoreId]))         /* If interrupts were enabled */
    {
        OsIf_ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32XX_
        ASM_KEYWORD(" nop ");    /* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}

void SchM_Enter_Uart_UART_EXCLUSIVE_AREA_04(void)
{
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    if(0UL == reentry_guard_UART_EXCLUSIVE_AREA_04[u32CoreId])
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
        msr_UART_EXCLUSIVE_AREA_04[u32CoreId] = OsIf_Trusted_Call_Return(Uart_schm_read_msr);
#else
        msr_UART_EXCLUSIVE_AREA_04[u32CoreId] = Uart_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
        if (ISR_ON(msr_UART_EXCLUSIVE_AREA_04[u32CoreId])) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
        {
            OsIf_SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32XX_
            ASM_KEYWORD(" nop ");    /* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
        }
    }
    reentry_guard_UART_EXCLUSIVE_AREA_04[u32CoreId]++;
}

void SchM_Exit_Uart_UART_EXCLUSIVE_AREA_04(void)
{
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    reentry_guard_UART_EXCLUSIVE_AREA_04[u32CoreId]--;
    if ((ISR_ON(msr_UART_EXCLUSIVE_AREA_04[u32CoreId])) && (0UL == reentry_guard_UART_EXCLUSIVE_AREA_04[u32CoreId]))         /* If interrupts were enabled */
    {
        OsIf_ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32XX_
        ASM_KEYWORD(" nop ");    /* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}

void SchM_Enter_Uart_UART_EXCLUSIVE_AREA_05(void)
{
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    if(0UL == reentry_guard_UART_EXCLUSIVE_AREA_05[u32CoreId])
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
        msr_UART_EXCLUSIVE_AREA_05[u32CoreId] = OsIf_Trusted_Call_Return(Uart_schm_read_msr);
#else
        msr_UART_EXCLUSIVE_AREA_05[u32CoreId] = Uart_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
        if (ISR_ON(msr_UART_EXCLUSIVE_AREA_05[u32CoreId])) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
        {
            OsIf_SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32XX_
            ASM_KEYWORD(" nop ");    /* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
        }
    }
    reentry_guard_UART_EXCLUSIVE_AREA_05[u32CoreId]++;
}

void SchM_Exit_Uart_UART_EXCLUSIVE_AREA_05(void)
{
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    reentry_guard_UART_EXCLUSIVE_AREA_05[u32CoreId]--;
    if ((ISR_ON(msr_UART_EXCLUSIVE_AREA_05[u32CoreId])) && (0UL == reentry_guard_UART_EXCLUSIVE_AREA_05[u32CoreId]))         /* If interrupts were enabled */
    {
        OsIf_ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32XX_
        ASM_KEYWORD(" nop ");    /* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}


void SchM_Enter_Uart_UART_EXCLUSIVE_AREA_06(void)
{
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    if(0UL == reentry_guard_UART_EXCLUSIVE_AREA_06[u32CoreId])
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
        msr_UART_EXCLUSIVE_AREA_06[u32CoreId] = OsIf_Trusted_Call_Return(Uart_schm_read_msr);
#else
        msr_UART_EXCLUSIVE_AREA_06[u32CoreId] = Uart_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
        if (ISR_ON(msr_UART_EXCLUSIVE_AREA_06[u32CoreId])) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
        {
            OsIf_SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32XX_
            ASM_KEYWORD(" nop ");    /* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
        }
    }
    reentry_guard_UART_EXCLUSIVE_AREA_06[u32CoreId]++;
}

void SchM_Exit_Uart_UART_EXCLUSIVE_AREA_06(void)
{
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    reentry_guard_UART_EXCLUSIVE_AREA_06[u32CoreId]--;
    if ((ISR_ON(msr_UART_EXCLUSIVE_AREA_06[u32CoreId])) && (0UL == reentry_guard_UART_EXCLUSIVE_AREA_06[u32CoreId]))         /* If interrupts were enabled */
    {
        OsIf_ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32XX_
        ASM_KEYWORD(" nop ");    /* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}


void SchM_Enter_Uart_UART_EXCLUSIVE_AREA_07(void)
{
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    if(0UL == reentry_guard_UART_EXCLUSIVE_AREA_07[u32CoreId])
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
        msr_UART_EXCLUSIVE_AREA_07[u32CoreId] = OsIf_Trusted_Call_Return(Uart_schm_read_msr);
#else
        msr_UART_EXCLUSIVE_AREA_07[u32CoreId] = Uart_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
        if (ISR_ON(msr_UART_EXCLUSIVE_AREA_07[u32CoreId])) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
        {
            OsIf_SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32XX_
            ASM_KEYWORD(" nop ");    /* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
        }
    }
    reentry_guard_UART_EXCLUSIVE_AREA_07[u32CoreId]++;
}

void SchM_Exit_Uart_UART_EXCLUSIVE_AREA_07(void)
{
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    reentry_guard_UART_EXCLUSIVE_AREA_07[u32CoreId]--;
    if ((ISR_ON(msr_UART_EXCLUSIVE_AREA_07[u32CoreId])) && (0UL == reentry_guard_UART_EXCLUSIVE_AREA_07[u32CoreId]))         /* If interrupts were enabled */
    {
        OsIf_ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32XX_
        ASM_KEYWORD(" nop ");    /* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}


void SchM_Enter_Uart_UART_EXCLUSIVE_AREA_08(void)
{
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    if(0UL == reentry_guard_UART_EXCLUSIVE_AREA_08[u32CoreId])
    {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
        msr_UART_EXCLUSIVE_AREA_08[u32CoreId] = OsIf_Trusted_Call_Return(Uart_schm_read_msr);
#else
        msr_UART_EXCLUSIVE_AREA_08[u32CoreId] = Uart_schm_read_msr();  /*read MSR (to store interrupts state)*/
#endif /* MCAL_ENABLE_USER_MODE_SUPPORT */
        if (ISR_ON(msr_UART_EXCLUSIVE_AREA_08[u32CoreId])) /*if MSR[EE] = 0, skip calling Suspend/Resume AllInterrupts*/
        {
            OsIf_SuspendAllInterrupts();
#ifdef _ARM_DS5_C_S32XX_
            ASM_KEYWORD(" nop ");    /* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
        }
    }
    reentry_guard_UART_EXCLUSIVE_AREA_08[u32CoreId]++;
}

void SchM_Exit_Uart_UART_EXCLUSIVE_AREA_08(void)
{
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();

    reentry_guard_UART_EXCLUSIVE_AREA_08[u32CoreId]--;
    if ((ISR_ON(msr_UART_EXCLUSIVE_AREA_08[u32CoreId])) && (0UL == reentry_guard_UART_EXCLUSIVE_AREA_08[u32CoreId]))         /* If interrupts were enabled */
    {
        OsIf_ResumeAllInterrupts();
#ifdef _ARM_DS5_C_S32XX_
        ASM_KEYWORD(" nop ");    /* Compiler fix - forces the CSPID instruction to be generated with -02, -Ospace are selected*/
#endif
    }
}

#ifdef MCAL_TESTING_ENVIRONMENT
/**
@brief   This function checks that all entered exclusive areas were also exited.
@details This function checks that all entered exclusive areas were also exited. The check
         is done by verifying that all reentry_guard_* static variables are back to the
         zero value.

@param[in]     void       No input parameters
@return        void       This function does not return a value. Test asserts are used instead.

@pre  None
@post None

@remarks Covers
@remarks Implements
*/
void SchM_Check_uart(void)
{
    uint32 u32CoreId = (uint32)OsIf_GetCoreID();


}
#endif /*MCAL_TESTING_ENVIRONMENT*/

#define RTE_STOP_SEC_CODE
#include "Rte_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
