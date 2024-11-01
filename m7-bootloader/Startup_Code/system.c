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

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Platform_Types.h"
#if defined(S32G2XX)
    #include "S32G274A_MSCM.h"
    #include "S32G274A_FXOSC.h"
    #include "S32G274A_MC_CGM.h"
    #include "S32G274A_MC_CGM_1.h"
    #include "S32G274A_MC_CGM_2.h"
    #include "S32G274A_SCB.h"
    #include "S32G274A_MPU.h"
    #include "S32G274A_MC_ME.h"
    #include "S32G274A_MC_RGM.h"
#elif defined(S32R45)
    #include "S32R45_MSCM.h"
    #include "S32R45_FXOSC.h"
    #include "S32R45_MC_CGM.h"
    #include "S32R45_MC_CGM_1.h"
    #include "S32R45_MC_CGM_2.h"
    #include "S32R45_SCB.h"
    #include "S32R45_MPU.h"
    #include "S32R45_MC_ME.h"
    #include "S32R45_MC_RGM.h"
#endif
#include "Mcal.h"
#if (MCAL_PLATFORM_ARM  == MCAL_ARM_AARCH64)
#include "gic400.h"
#else
#include "nvic.h"
#include "core_specific.h"
#endif
#include "system.h"

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
#define CA53_0_0 (0UL)
#define CA53_0_1 (1UL)
#define CA53_1_0 (2UL)
#define CA53_1_1 (3UL)
#define CM7_0    (4UL)
#define CM7_1    (5UL)
#define CM7_2    (6UL)

#define SVC_GoToSupervisor()      ASM_KEYWORD("svc 0x0")
#define SVC_GoToUser()            ASM_KEYWORD("svc 0x1")

#define S32_SCB_CPACR_CPx_MASK(CpNum)             (0x3U << S32_SCB_CPACR_CPx_SHIFT(CpNum))
#define S32_SCB_CPACR_CPx_SHIFT(CpNum)            (2U*((uint32)CpNum))
#define S32_SCB_CPACR_CPx(CpNum, x)               (((uint32)(((uint32)(x))<<S32_SCB_CPACR_CPx_SHIFT((CpNum))))&S32_SCB_CPACR_CPx_MASK((CpNum)))

/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/
/* Allocate a global variable which will be overwritten by the debugger if attached(in CMM), to catch the core after reset. */
uint32 RESET_CATCH_CORE=0x00U;

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
static void sys_m7_cache_init(void);
/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT  
    extern uint32 startup_getControlRegisterValue(void);
    extern uint32 startup_getAipsRegisterValue(void);
#endif /*MCAL_ENABLE_USER_MODE_SUPPORT*/


/*================================================================================================*/
/**
* @brief    startup_go_to_user_mode
* @details  Function called from startup.s to switch to user mode if MCAL_ENABLE_USER_MODE_SUPPORT
*           is defined
*/
/*================================================================================================*/
void startup_go_to_user_mode(void);
void startup_go_to_user_mode(void)
{
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
    ASM_KEYWORD("svc 0x1");
#endif
}

/*================================================================================================*/
/**
* @brief   Default IRQ handler
* @details Infinite Loop
*/
/*================================================================================================*/
void default_interrupt_routine(void)
{
    while(1);
}

/*================================================================================================*/
/**
* @brief Sys_GoToSupervisor
* @details function used to enter to supervisor mode.
*           check if it's needed to switch to supervisor mode and make the switch.
*           Return 1 if switch was done
*/
/*================================================================================================*/

#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
uint32 Sys_GoToSupervisor(void)
{
    uint32 u32ControlRegValue;
    uint32 u32AipsRegValue;
    uint32 u32SwitchToSupervisor;

    /* if it's 0 then Thread mode is already in supervisor mode */
    u32ControlRegValue = startup_getControlRegisterValue();
    /* if it's 0 the core is in Thread mode, otherwise in Handler mode */
    u32AipsRegValue = startup_getAipsRegisterValue();

    /* if core is already in supervisor mode for Thread mode, or running form Handler mode, there is no need to make the switch */
    if((0UL == (u32ControlRegValue & 1)) || (0 < (u32AipsRegValue & 0xFF)))
    {
        u32SwitchToSupervisor = 0U;
    }
    else
    {
        u32SwitchToSupervisor = 1U;
        SVC_GoToSupervisor();
    }

    return u32SwitchToSupervisor;
}

/*================================================================================================*/
/**
* @brief Sys_GoToUser_Return
* @details function used to switch back to user mode for Thread mode, return a uint32 value passed as parameter
*/
/*================================================================================================*/
uint32 Sys_GoToUser_Return(uint32 u32SwitchToSupervisor, uint32 u32returnValue)
{
    if (1UL == u32SwitchToSupervisor)
    {
        SVC_GoToUser();
    }

    return u32returnValue;
}

uint32 Sys_GoToUser(void)
{
    SVC_GoToUser();
    return 0UL;
}
#endif


/*================================================================================================*/
/**
* @brief Sys_GetCoreID
* @details Function used to get the ID of the currently executing thread
*/
/*================================================================================================*/
#if !defined(USING_OS_AUTOSAROS)
uint8 Sys_GetCoreID(void)
{
    return ((uint8)(MSCM->CPXNUM & MSCM_CPXNUM_CPN_MASK));
}
#endif

/*================================================================================================*/
/**
* @brief Sys_StartSecondaryCores
* @details Function used to start the secondary cores
*/
/*================================================================================================*/
#if (defined(CORE0) && defined(MULTIPLE_IMAGE))
#ifdef __ICCARM__
    #pragma default_function_attributes = @ ".systeminit"
#else
    __attribute__ ((section (".systeminit")))
#endif
static void Sys_StartSecondaryCores(void)
{
#ifdef START_CM7_1
    extern const uint32 __CORE1_START_ADDRESS;

    MC_ME->PRTN0_CORE1_ADDR = (uint32)&__CORE1_START_ADDRESS;
    MC_ME->PRTN0_CORE1_PCONF = 1;
    MC_ME->PRTN0_CORE1_PUPD = 1;
    MC_ME->CTL_KEY = 0x5AF0;
    MC_ME->CTL_KEY = 0xA50F;
    while (!(MC_ME->PRTN0_CORE1_STAT & MC_ME_PRTN0_CORE1_STAT_CCS_MASK)) {};
    MC_RGM->PRST_0[0].PRST_0 &= ~MC_RGM_PRST_0_PERIPH_1_RST(1);
    while(MC_RGM->PSTAT_0[0].PSTAT_0 & MC_RGM_PSTAT_0_PERIPH_1_STAT_MASK);
#endif
#ifdef START_CM7_2
    extern const uint32 __CORE2_START_ADDRESS;

    MC_ME->PRTN0_CORE2_ADDR = (uint32)&__CORE2_START_ADDRESS;
    MC_ME->PRTN0_CORE2_PCONF = 1;
    MC_ME->PRTN0_CORE2_PUPD = 1;
    MC_ME->CTL_KEY = 0x5AF0;
    MC_ME->CTL_KEY = 0xA50F;
    while (!(MC_ME->PRTN0_CORE2_STAT & MC_ME_PRTN0_CORE2_STAT_CCS_MASK)) {};
    MC_RGM->PRST_0[0].PRST_0 &= ~MC_RGM_PRST_0_PERIPH_2_RST(1);
    while(MC_RGM->PSTAT_0[0].PSTAT_0 & MC_RGM_PSTAT_0_PERIPH_2_STAT_MASK);
#endif
}
#endif

/*================================================================================================*/
/*
 * system initialization : system clock, interrupt router ...
 */
#ifdef __ICCARM__ 
    #pragma default_function_attributes = @ ".systeminit"
#else
    __attribute__ ((section (".systeminit")))
#endif 

void SystemInit(void)
{
    uint32 i;
    uint32 coreMask;
	uint8 regionNum = 0U;

    uint32 coreId = OsIf_GetCoreID();

    switch(coreId)
    {
        case CA53_0_0:
            /* There is only one bitfield for all Cortex A53 interrupt steering. Fall trough */
        case CA53_0_1:
            /* There is only one bitfield for all Cortex A53 interrupt steering. Fall trough */
        case CA53_1_0:
            /* There is only one bitfield for all Cortex A53 interrupt steering. Fall trough */
        case CA53_1_1:
            coreMask = (1UL << MSCM_IRSPRC_GIC500_SHIFT);
            break;
        case CM7_0:
            coreMask = (1UL << MSCM_IRSPRC_M7_0_SHIFT);
            break;
        case CM7_1:
            coreMask = (1UL << MSCM_IRSPRC_M7_1_SHIFT);
            break;
        case CM7_2:
            coreMask = (1UL << MSCM_IRSPRC_M7_2_SHIFT);
            break;
        default:
            coreMask = 0UL;
            break;
    }

    /* Configure MSCM to enable/disable interrupts routing to Core processor */
    for (i = 0; i < MSCM_IRSPRC_COUNT; i++) 
    {
        MSCM->IRSPRC[i] |= coreMask;
    }

#if (defined(CORE0) && defined(MULTIPLE_IMAGE))
    Sys_StartSecondaryCores();
#endif

#if (MCAL_PLATFORM_ARM  == MCAL_ARM_AARCH64)
    
   /* Configure Addresses for GIC_Distributor and Core(Redistributor) */  
    gic400_setGICAddr((void*)0x50800000, (void*)0x50880000);

    /* Configure interrupt controller (GICv2 assumed) */
    gic400_disableGIC();
    gic400_disableCPUInterface();
    gic400_enableGIC();
    gic400_enableCPUInterface();
    gic400_enableNonSecureCPUInterface();
    /* Configure priority mask to lowest value - enables all priorities */
  
    gic400_setPriorityMask(0xFF);
  
    /* fill the interrupts_vector with the default interrupt rutine */
    for (i=0; i<INT_NUM_SOURCES; i++)
    {
        g_INT_vectors[i] = (int_function_t)default_interrupt_routine; 
    }

#else

  NVIC_SetPriorityGrouping(0); /* 0 means 7 bits for prio, 1 for sub-prio */
  S32_SCB->CCR |=  1;          /* processor can enter Thread mode from any level under the
                                   control of an EXC_RETURN value, PendSV priority set to 0 */
  S32_SCB->SHPR3 = 0;

/**************************************************************************/
                      /* FPU ENABLE*/
/**************************************************************************/
#ifdef ENABLE_FPU
    /* Enable CP10 and CP11 coprocessors */
    S32_SCB->CPACR |= (S32_SCB_CPACR_CPx(10U, 3U) | S32_SCB_CPACR_CPx(11U, 3U)); 

    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
#endif /* ENABLE_FPU */

/**************************************************************************/
                      /* DEFAULT MEMORY ENABLE*/
/**************************************************************************/
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");

    /* Set default memory regions */
    for (regionNum = 0U; regionNum < CPU_MPU_MEMORY_COUNT; regionNum++)
    {
        S32_MPU->RNR  = regionNum;
        S32_MPU->RBAR = rbar[regionNum];
        S32_MPU->RASR = rasr[regionNum];
    }

    /* Enable MPU */
    S32_MPU->CTRL |= S32_MPU_CTRL_ENABLE_MASK;

    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
    
/**************************************************************************/
            /* ENABLE CACHE */
/**************************************************************************/
    sys_m7_cache_init();
#endif
}

__attribute__ ((section (".systeminit")))

static void sys_m7_cache_init(void)
{        
    uint32 ccsidr = 0U;
    uint32 sets = 0U;
    uint32 ways = 0U;

#ifdef D_CACHE_ENABLE    
    /*init Data caches*/
    S32_SCB->CSSELR = 0U;                       /* select Level 1 data cache */
    ASM_KEYWORD("dsb");
    ccsidr = S32_SCB->CCSIDR;
    sets = (uint32)(CCSIDR_SETS(ccsidr));
    do {
      ways = (uint32)(CCSIDR_WAYS(ccsidr));
      do {
        S32_SCB->DCISW = (((sets << SCB_DCISW_SET_Pos) & SCB_DCISW_SET_Msk) |
                      ((ways << SCB_DCISW_WAY_Pos) & SCB_DCISW_WAY_Msk)  );  
        ASM_KEYWORD("dsb");
      } while (ways-- != 0U);
    } while(sets-- != 0U);
    ASM_KEYWORD("dsb");
    S32_SCB->CCR |=  (uint32)SCB_CCR_DC_Msk;  /* enable D-Cache */
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
#endif

#ifdef I_CACHE_ENABLE  
    /*init Code caches*/
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
    S32_SCB->ICIALLU = 0UL;                     /* invalidate I-Cache */
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
    S32_SCB->CCR |=  (uint32)SCB_CCR_IC_Msk;  /* enable I-Cache */
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
#endif
}

#ifdef __ICCARM__ 
    #pragma default_function_attributes =
#endif

#ifdef __cplusplus
}
#endif
