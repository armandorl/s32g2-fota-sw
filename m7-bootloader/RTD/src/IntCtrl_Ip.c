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
*   @addtogroup IntCtrl_Ip
*   @{
*/

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/

#include "IntCtrl_Ip.h"
#include "Mcal.h"

/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/
extern uint32 __INT_SRAM_START[];
/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
#if ((STD_ON == INTCTRL_PLATFORM_ENABLE_USER_MODE_SUPPORT) && (defined (MCAL_ENABLE_USER_MODE_SUPPORT)))
    #define Call_IntCtrl_Ip_InstallHandlerPrivileged(eIrqNumber,pfNewHandler,pfOldHandler)  \
                OsIf_Trusted_Call3params(IntCtrl_Ip_InstallHandlerPrivileged,(eIrqNumber),(pfNewHandler),(pfOldHandler))
    #define Call_IntCtrl_Ip_EnableIrqPrivileged(eIrqNumber)  \
                OsIf_Trusted_Call1param(IntCtrl_Ip_EnableIrqPrivileged,(eIrqNumber))
    #define Call_IntCtrl_Ip_DisableIrqPrivileged(eIrqNumber)  \
                OsIf_Trusted_Call1param(IntCtrl_Ip_DisableIrqPrivileged,(eIrqNumber))
    #define Call_IntCtrl_Ip_SetPriorityPrivileged(eIrqNumber,u8Priority)  \
                OsIf_Trusted_Call2params(IntCtrl_Ip_SetPriorityPrivileged,(eIrqNumber),(u8Priority))
    #define Call_IntCtrl_Ip_GetPriorityPrivileged(eIrqNumber)  \
                OsIf_Trusted_Call_Return1param(IntCtrl_Ip_GetPriorityPrivileged,(eIrqNumber))
    #define Call_IntCtrl_Ip_ClearPendingPrivileged(eIrqNumber)  \
                OsIf_Trusted_Call1param(IntCtrl_Ip_ClearPendingPrivileged,(eIrqNumber))
    #define Call_IntCtrl_Ip_SetPendingPrivileged(eIrqNumber)  \
                OsIf_Trusted_Call1param(IntCtrl_Ip_SetPendingPrivileged,(eIrqNumber))
    #define Call_IntCtrl_Ip_GetPendingPrivileged(eIrqNumber)  \
                OsIf_Trusted_Call_Return1param(IntCtrl_Ip_GetPendingPrivileged,(eIrqNumber))
    #define Call_IntCtrl_Ip_GetActivePrivileged(eIrqNumber)  \
                OsIf_Trusted_Call_Return1param(IntCtrl_Ip_GetActivePrivileged,(eIrqNumber))
#if (INT_CTRL_IP_MSCM_SYSTEM_INTERRUPT_ROUTER == STD_ON)
    #define Call_IntCtrl_Ip_SetTargetCoresPrivileged(eIrqNumber,u8TargetCores)  \
                OsIf_Trusted_Call2params(IntCtrl_Ip_SetTargetCoresPrivileged,(eIrqNumber),(u8TargetCores))
#endif
#if (INT_CTRL_IP_MSI_AVAILABLE == STD_ON)
    #define Call_IntCtrl_Ip_GenerateDirectedCpuInterruptPrivileged(eIrqNumber,eCpuTarget)  \
                OsIf_Trusted_Call2params(IntCtrl_Ip_GenerateDirectedCpuInterruptPrivileged,(eIrqNumber),(eCpuTarget))
#endif
#else /*STD_ON == INTCTRL_PLATFORM_ENABLE_USER_MODE_SUPPORT*/
    #define Call_IntCtrl_Ip_InstallHandlerPrivileged(eIrqNumber,pfNewHandler,pfOldHandler)  \
                IntCtrl_Ip_InstallHandlerPrivileged((eIrqNumber),(pfNewHandler),(pfOldHandler))
    #define Call_IntCtrl_Ip_EnableIrqPrivileged(eIrqNumber)  \
                IntCtrl_Ip_EnableIrqPrivileged((eIrqNumber))
    #define Call_IntCtrl_Ip_DisableIrqPrivileged(eIrqNumber)  \
                IntCtrl_Ip_DisableIrqPrivileged((eIrqNumber))
    #define Call_IntCtrl_Ip_SetPriorityPrivileged(eIrqNumber,u8Priority)  \
                IntCtrl_Ip_SetPriorityPrivileged((eIrqNumber),(u8Priority))
    #define Call_IntCtrl_Ip_GetPriorityPrivileged(eIrqNumber)  \
                IntCtrl_Ip_GetPriorityPrivileged((eIrqNumber))
    #define Call_IntCtrl_Ip_ClearPendingPrivileged(eIrqNumber)  \
                IntCtrl_Ip_ClearPendingPrivileged((eIrqNumber))
    #define Call_IntCtrl_Ip_SetPendingPrivileged(eIrqNumber)  \
                IntCtrl_Ip_SetPendingPrivileged((eIrqNumber))
    #define Call_IntCtrl_Ip_GetPendingPrivileged(eIrqNumber)  \
                IntCtrl_Ip_GetPendingPrivileged((eIrqNumber))
    #define Call_IntCtrl_Ip_GetActivePrivileged(eIrqNumber)  \
                IntCtrl_Ip_GetActivePrivileged((eIrqNumber))
#if (INT_CTRL_IP_MSCM_SYSTEM_INTERRUPT_ROUTER == STD_ON)
    #define Call_IntCtrl_Ip_SetTargetCoresPrivileged(eIrqNumber,u8TargetCores)  \
                IntCtrl_Ip_SetTargetCoresPrivileged((eIrqNumber),(u8TargetCores))
#endif
#if (INT_CTRL_IP_MSI_AVAILABLE == STD_ON)
    #define Call_IntCtrl_Ip_GenerateDirectedCpuInterruptPrivileged(eIrqNumber,eCpuTarget)  \
                IntCtrl_Ip_GenerateDirectedCpuInterruptPrivileged((eIrqNumber),(eCpuTarget))
#endif
#endif /*STD_ON == INTCTRL_PLATFORM_ENABLE_USER_MODE_SUPPORT*/

#define PLATFORM_START_SEC_CODE
#include "Platform_MemMap.h"
static inline void IntCtrl_Ip_InstallHandlerPrivileged(IRQn_Type eIrqNumber,
                               const IntCtrl_Ip_IrqHandlerType pfNewHandler,
                               IntCtrl_Ip_IrqHandlerType* const pfOldHandler);
static inline void IntCtrl_Ip_EnableIrqPrivileged(IRQn_Type eIrqNumber);
static inline void IntCtrl_Ip_DisableIrqPrivileged(IRQn_Type eIrqNumber);
static inline void IntCtrl_Ip_SetPriorityPrivileged(IRQn_Type eIrqNumber, uint8 u8Priority);
static inline uint8 IntCtrl_Ip_GetPriorityPrivileged(IRQn_Type eIrqNumber);
static inline void IntCtrl_Ip_ClearPendingPrivileged(IRQn_Type eIrqNumber);
static inline void IntCtrl_Ip_SetPendingPrivileged(IRQn_Type eIrqNumber);
static inline boolean IntCtrl_Ip_GetPendingPrivileged(IRQn_Type eIrqNumber);
static inline boolean IntCtrl_Ip_GetActivePrivileged(IRQn_Type eIrqNumber);
#if (INT_CTRL_IP_MSCM_SYSTEM_INTERRUPT_ROUTER == STD_ON)
static inline void IntCtrl_Ip_SetTargetCoresPrivileged(IRQn_Type eIrqNumber, uint8 u8TargetCores);
#endif
#if (INT_CTRL_IP_MSI_AVAILABLE == STD_ON)
static inline void IntCtrl_Ip_GenerateDirectedCpuInterruptPrivileged(IRQn_Type eIrqNumber, IntCtrl_Ip_IrqTargetType eCpuTarget);
#endif

#define M7_CCR 0xE000ED14
#define M7_DCCMVAU 0xE000EF64
#define DCACHE_ENABLE() (REG_READ32(M7_CCR) & (1<<16))

static inline void IntCtrl_Ip_InstallHandlerPrivileged(IRQn_Type eIrqNumber,
                               const IntCtrl_Ip_IrqHandlerType pfNewHandler,
                               IntCtrl_Ip_IrqHandlerType* const pfOldHandler)
{
#if (INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON)

    /* Check IRQ number - dev_irqNumber is used to avoid compiler warning */
    sint32 dev_irqNumber = (sint32)eIrqNumber;
    DevAssert(INT_CTRL_IP_IRQ_MIN <= dev_irqNumber);
    DevAssert(dev_irqNumber <= (sint32)INT_CTRL_IP_IRQ_MAX);
    DevAssert(S32_SCB->VTOR >= (uint32)__INT_SRAM_START);

#endif /*(INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON) */

    uint32 * pVectorRam = (uint32 *)S32_SCB->VTOR;

    /* Save the former handler pointer */
    if (pfOldHandler != NULL_PTR)
    {
        *pfOldHandler = (IntCtrl_Ip_IrqHandlerType)pVectorRam[((sint32)eIrqNumber) + 16];
    }

    /* Set handler into vector table */
    pVectorRam[((sint32)eIrqNumber) + 16] = (uint32)pfNewHandler;
	if (DCACHE_ENABLE())
		REG_WRITE32(M7_DCCMVAU, &pVectorRam[((sint32)eIrqNumber) + 16]);

    /* Invalidate ICache */
    S32_SCB->ICIALLU = 0UL;
    ASM_KEYWORD("dsb");
    ASM_KEYWORD("isb");
}

static inline void IntCtrl_Ip_EnableIrqPrivileged(IRQn_Type eIrqNumber)
{
#if (INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON)
    /* Check IRQ number - dev_irqNumber is used to avoid compiler warning */
    DevAssert(0 <= (sint32)eIrqNumber);
    DevAssert((sint32)eIrqNumber <= (sint32)INT_CTRL_IP_IRQ_MAX);
#endif /*(INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON) */
    /* Enable interrupt */
    S32_NVIC->ISER[(uint32)(eIrqNumber) >> 5U] = (uint32)(1UL << ((uint32)(eIrqNumber) & (uint32)0x1FU));
}

static inline void IntCtrl_Ip_DisableIrqPrivileged(IRQn_Type eIrqNumber)
{
#if (INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON)
    /* Check IRQ number - dev_irqNumber is used to avoid compiler warning */
    DevAssert(0 <= (sint32)eIrqNumber);
    DevAssert((sint32)eIrqNumber <= (sint32)INT_CTRL_IP_IRQ_MAX);
#endif /*(INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON) */
    /* Disable interrupt */
    S32_NVIC->ICER[((uint32)(eIrqNumber) >> 5U)] = (uint32)(1UL << ((uint32)(eIrqNumber) & (uint32)0x1FU));
}

static inline void IntCtrl_Ip_SetPriorityPrivileged(IRQn_Type eIrqNumber, uint8 u8Priority)
{
#if (INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON)

    /* Check IRQ number and priority - dev_irqNumber is used to avoid compiler warning */
    DevAssert(INT_CTRL_IP_IRQ_MIN <= (sint32)eIrqNumber);
    DevAssert((sint32)eIrqNumber <= (sint32)INT_CTRL_IP_IRQ_MAX);
    DevAssert(u8Priority < (uint8)(1U << INT_CTRL_IP_NVIC_PRIO_BITS));

#endif /* (INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON) */

    uint8 shift = (uint8) (8U - INT_CTRL_IP_NVIC_PRIO_BITS);

    if ((sint32)eIrqNumber < 0)
    {
        uint32 intVectorId = ((uint32)(eIrqNumber) & 0xFU);
        uint32 shprRegId = intVectorId >> 2U;

        /* Compute pointer to SHPR register - avoid MISRA violation. */
        volatile uint8 * shprRegPtr = ((shprRegId == 1U) ? (volatile uint8 *)&S32_SCB->SHPR1 : ((shprRegId == 2U) ? (volatile uint8 *)&S32_SCB->SHPR2 : (volatile uint8 *)&S32_SCB->SHPR3));

        /* Set Priority for Cortex-M System Interrupts */
        shprRegPtr[intVectorId & 3U] = (uint8)((((uint32)u8Priority) << shift) & 0xFFUL);
    }
    else
    {
        /* Set Priority for device specific Interrupts */
        S32_NVIC->IP[(uint32)(eIrqNumber)] = (uint8)((((uint32)u8Priority) << shift) & 0xFFUL);
    }
}

static inline uint8 IntCtrl_Ip_GetPriorityPrivileged(IRQn_Type eIrqNumber)
{
#if (INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON)

    /* Check IRQ number */
    DevAssert(INT_CTRL_IP_IRQ_MIN <= eIrqNumber);
    DevAssert((sint32)eIrqNumber <= (sint32)INT_CTRL_IP_IRQ_MAX);

#endif /*(INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON) */

    uint8 priority;
    uint8 shift = (uint8) (8U - INT_CTRL_IP_NVIC_PRIO_BITS);

    if ((sint32)eIrqNumber < 0)
    {
        uint32 intVectorId = ((uint32)(eIrqNumber) & 0xFU);
        uint32 shprRegId = intVectorId >> 2U;

        /* Compute pointer to SHPR register - avoid MISRA violation. */
        volatile const uint8 * shprRegPtr = ((shprRegId == 1U) ? (volatile uint8 *)&S32_SCB->SHPR1 : ((shprRegId == 2U) ? (volatile uint8 *)&S32_SCB->SHPR2 : (volatile uint8 *)&S32_SCB->SHPR3));

        /* Get Priority from Cortex-M  System Interrupts */
        priority = (uint8)(shprRegPtr[intVectorId & 3U] >> (shift));
    }
    else
    {
        /* Get Priority for device specific Interrupts  */
        priority = (uint8)(S32_NVIC->IP[(uint32)(eIrqNumber)] >> shift);
    }

    return priority;
}

static inline void IntCtrl_Ip_ClearPendingPrivileged(IRQn_Type eIrqNumber)
{
#if (INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON)
    /* Check IRQ number */
    DevAssert(0 <= (sint32)eIrqNumber);
    DevAssert((sint32)eIrqNumber <= (sint32)INT_CTRL_IP_IRQ_MAX);
#endif /* (INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON) */

#if (INT_CTRL_IP_MSI_AVAILABLE == STD_ON)
    uint32 currentCpu;
    uint32 irqId;

    if ((INTCTRL_IP_DIRECTED_CPU_INT_MIN <= eIrqNumber) && (eIrqNumber <= INTCTRL_IP_DIRECTED_CPU_INT_MAX))
    {
        currentCpu = MSCM_CPXNUM_CPN_MASK & (MSCM->CPXNUM);
        irqId = (uint32)eIrqNumber - (uint32)INTCTRL_IP_DIRECTED_CPU_INT_MIN;

        /* Clear Directed CPU Pending Interrupt */
        MSCM_IRCPnIRx->IRCPnIRx[currentCpu][irqId].IntStatusR = 0x7FU;

        return;
    }
#endif /* (INT_CTRL_IP_MSI_AVAILABLE == STD_ON) */

    /* Clear Pending Interrupt */
    S32_NVIC->ICPR[(uint32)(eIrqNumber) >> 5U] = (uint32)(1UL << ((uint32)(eIrqNumber) & (uint32)0x1FU));
}

static inline void IntCtrl_Ip_SetPendingPrivileged(IRQn_Type eIrqNumber)
{
#if (INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON)
    /* Check IRQ number - dev_irqNumber is used to avoid compiler warning */
    DevAssert(0 <= (sint32)eIrqNumber);
    DevAssert(((sint32)eIrqNumber) <= (sint32)INT_CTRL_IP_IRQ_MAX);
#endif /*(INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON) */
    /* Set Pending Interrupt */
    S32_NVIC->ISPR[(uint32)(eIrqNumber) >> 5U] = (uint32)(1UL << ((uint32)(eIrqNumber) & (uint32)0x1FU));

}

static inline boolean IntCtrl_Ip_GetPendingPrivileged(IRQn_Type eIrqNumber)
{
#if (INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON)
    /* Check IRQ number */
    DevAssert(0 <= (sint32)eIrqNumber);
    DevAssert(((sint32)eIrqNumber) <= (sint32)INT_CTRL_IP_IRQ_MAX);
#endif /*(INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON) */

#if (INT_CTRL_IP_MSI_AVAILABLE == STD_ON)
    uint32 currentCpu;
    uint32 irqId;

    /* Get Directed CPU Pending Interrupt */
    if ((INTCTRL_IP_DIRECTED_CPU_INT_MIN <= eIrqNumber) && (eIrqNumber <= INTCTRL_IP_DIRECTED_CPU_INT_MAX))
    {
        currentCpu = MSCM_CPXNUM_CPN_MASK & (MSCM->CPXNUM);
        irqId = (uint32)eIrqNumber - (uint32)INTCTRL_IP_DIRECTED_CPU_INT_MIN;

        return ((MSCM_IRCPnIRx->IRCPnIRx[currentCpu][irqId].IntStatusR != 0U) ? TRUE : FALSE);
    }
#endif /* (INT_CTRL_IP_MSI_AVAILABLE == STD_ON) */

    /* Get Pending Interrupt */
    return ((((S32_NVIC->ISPR[(((uint32)eIrqNumber) >> 5UL)] & (1UL << (((uint32)eIrqNumber) & 0x1FUL))) != 0UL) ? TRUE : FALSE));
}

static inline boolean IntCtrl_Ip_GetActivePrivileged(IRQn_Type eIrqNumber)
{
#if (INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON)
    /* Check IRQ number */
    DevAssert(0 <= (sint32)eIrqNumber);
    DevAssert(((sint32)eIrqNumber) <= (sint32)INT_CTRL_IP_IRQ_MAX);
#endif /*(INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON) */
    /* Get Active Interrupt */
    return ((((S32_NVIC->IABR[(((uint32)eIrqNumber) >> 5UL)] & (1UL << (((uint32)eIrqNumber) & 0x1FUL))) != 0UL) ? TRUE : FALSE));
}


#if (INT_CTRL_IP_MSCM_SYSTEM_INTERRUPT_ROUTER == STD_ON)
/**
 * @internal
 * @brief         Sets the target cores for an interrupt request.
 * @implements    IntCtrl_Ip_SetTargetCores_Activity
 */
static inline void IntCtrl_Ip_SetTargetCoresPrivileged(IRQn_Type eIrqNumber, uint8 u8TargetCores)
{
#if (INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON)
    /* Check IRQ number */
    DevAssert(0 <= (sint32)eIrqNumber);
    DevAssert(((sint32)eIrqNumber) <= (sint32)INT_CTRL_IP_IRQ_MAX);
    /* Check interrupt routing is not locked for this IRQ */
    DevAssert((MSCM->IRSPRC[eIrqNumber] & (uint16)(MSCM_IRSPRC_LOCK_MASK)) == (uint16)MSCM_IRSPRC_LOCK(0));
#endif /*(INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON) */
    MSCM->IRSPRC[eIrqNumber] = (uint16)u8TargetCores;
}
#endif

#if (INT_CTRL_IP_MSI_AVAILABLE == STD_ON)
static inline void IntCtrl_Ip_GenerateDirectedCpuInterruptPrivileged(IRQn_Type eIrqNumber, IntCtrl_Ip_IrqTargetType eCpuTarget)
{
#if (INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON)
    /* Check IRQ number */
    DevAssert(INTCTRL_IP_DIRECTED_CPU_INT_MIN <= (sint32)eIrqNumber);
    DevAssert((sint32)eIrqNumber <= INTCTRL_IP_DIRECTED_CPU_INT_MAX);
#endif

    uint32 irqId = (uint32)eIrqNumber - (uint32)INTCTRL_IP_DIRECTED_CPU_INT_MIN;
    uint32 core;
    uint32 target;

    if (eCpuTarget == INTCTRL_IP_TARGET_OTHERS)
    {
        for (core = 0U; core < INTCTRL_IP_MSI_CORE_CNT; core++)
        {
            /* Generate a Directed CPU Interrupt to every other core */
            if (core != (MSCM_CPXNUM_CPN_MASK & (MSCM->CPXNUM)))
            {
                MSCM_IRCPnIRx->IRCPnIRx[core][irqId].IGR = 0x1U;
            }
        }
    }
    else
    {
        if (eCpuTarget == INTCTRL_IP_TARGET_SELF)
        {
            target = MSCM_CPXNUM_CPN_MASK & (MSCM->CPXNUM);
        }
        else
        {
            target = (uint32)eCpuTarget;
        }

        /* Generate Directed CPU Interrupt to target core */
        MSCM_IRCPnIRx->IRCPnIRx[target][irqId].IGR = 0x1U;
    }
}
#endif /* INT_CTRL_IP_MSI_AVAILABLE == STD_ON */

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/





/**
 * @internal
 * @brief         Initializes the configured interrupts at interrupt controller level.
 * @implements    IntCtrl_Ip_Init_Activity
 */
IntCtrl_Ip_StatusType IntCtrl_Ip_Init(const IntCtrl_Ip_CtrlConfigType *pIntCtrlCtrlConfig)
{
#if (INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON)
    DevAssert(pIntCtrlCtrlConfig != NULL_PTR);
    DevAssert(pIntCtrlCtrlConfig->u32ConfigIrqCount < INT_CTRL_IP_IRQ_MAX);
#endif
    uint32 irqIdx;
    for (irqIdx = 0; irqIdx < pIntCtrlCtrlConfig->u32ConfigIrqCount; irqIdx++)
    {
        IntCtrl_Ip_SetPriority(pIntCtrlCtrlConfig->aIrqConfig[irqIdx].eIrqNumber,
                               pIntCtrlCtrlConfig->aIrqConfig[irqIdx].u8IrqPriority);

        if (pIntCtrlCtrlConfig->aIrqConfig[irqIdx].bIrqEnabled)
        {
            IntCtrl_Ip_EnableIrq(pIntCtrlCtrlConfig->aIrqConfig[irqIdx].eIrqNumber);
        }
        else
        {
            IntCtrl_Ip_DisableIrq(pIntCtrlCtrlConfig->aIrqConfig[irqIdx].eIrqNumber);
        }
    }

    return INTCTRL_IP_STATUS_SUCCESS;
}

#if (INT_CTRL_IP_MSCM_SYSTEM_INTERRUPT_ROUTER == STD_ON)
/**
 * @internal
 * @brief         Initializes the configured routing interrupts.
 * @implements    IntCtrl_Ip_ConfigIrqRouting_Activity
 */
IntCtrl_Ip_StatusType IntCtrl_Ip_ConfigIrqRouting(const IntCtrl_Ip_GlobalRouteConfigType *routeConfig)
{
#if (INT_CTRL_IP_DEV_ERROR_DETECT == STD_ON)
    DevAssert(routeConfig != NULL_PTR);
    DevAssert(routeConfig->u32ConfigIrqCount < INT_CTRL_IP_IRQ_MAX);
#endif
    uint32 irqIdx;
    for (irqIdx = 0; irqIdx < routeConfig->u32ConfigIrqCount; irqIdx++)
    {
        /* Configure routing */
        IntCtrl_Ip_SetTargetCores(routeConfig->aIrqConfig[irqIdx].eIrqNumber,
                                  routeConfig->aIrqConfig[irqIdx].u8TargetCores);
        /* Install the configured handler */
        IntCtrl_Ip_InstallHandler(routeConfig->aIrqConfig[irqIdx].eIrqNumber,
                                  routeConfig->aIrqConfig[irqIdx].pfHandler,
                                  NULL_PTR);
    }
    return INTCTRL_IP_STATUS_SUCCESS;
}
#endif

/**
 * @internal
 * @brief         Installs a handler for an IRQ.
 * @implements    IntCtrl_Ip_InstallHandler_Activity
 */
void IntCtrl_Ip_InstallHandler(IRQn_Type eIrqNumber,
                               const IntCtrl_Ip_IrqHandlerType pfNewHandler,
                               IntCtrl_Ip_IrqHandlerType* const pfOldHandler)
{
    Call_IntCtrl_Ip_InstallHandlerPrivileged(eIrqNumber,pfNewHandler,pfOldHandler);
}

/**
 * @internal
 * @brief         Enables an interrupt request.
 * @implements    IntCtrl_Ip_EnableIrq_Activity
 */
void IntCtrl_Ip_EnableIrq(IRQn_Type eIrqNumber)
{
    Call_IntCtrl_Ip_EnableIrqPrivileged(eIrqNumber);
}

/**
 * @internal
 * @brief         Disables an interrupt request.
 * @implements    IntCtrl_Ip_DisableIrq_Activity
 */
void IntCtrl_Ip_DisableIrq(IRQn_Type eIrqNumber)
{
    Call_IntCtrl_Ip_DisableIrqPrivileged(eIrqNumber);
}

/**
 * @internal
 * @brief         Sets the priority for an interrupt request.
 * @implements    IntCtrl_Ip_SetPriority_Activity
 */
void IntCtrl_Ip_SetPriority(IRQn_Type eIrqNumber, uint8 u8Priority)
{
    Call_IntCtrl_Ip_SetPriorityPrivileged(eIrqNumber,u8Priority);
}

/**
 * @internal
 * @brief         Gets the priority for an interrupt request.
 * @implements    IntCtrl_Ip_GetPriority_Activity
 */
uint8 IntCtrl_Ip_GetPriority(IRQn_Type eIrqNumber)
{
    return Call_IntCtrl_Ip_GetPriorityPrivileged(eIrqNumber);
}

/**
 * @internal
 * @brief         Clears the pending flag for an interrupt request.
 * @implements    IntCtrl_Ip_ClearPending_Activity
 */
void IntCtrl_Ip_ClearPending(IRQn_Type eIrqNumber)
{
    Call_IntCtrl_Ip_ClearPendingPrivileged(eIrqNumber);
}

/**
 * @internal
 * @brief         Sets the pending flag for an interrupt request.
 * @implements    IntCtrl_Ip_SetPending_Activity
 */
void IntCtrl_Ip_SetPending(IRQn_Type eIrqNumber)
{
    Call_IntCtrl_Ip_SetPendingPrivileged(eIrqNumber);
}

/**
 * @internal
 * @brief         Gets the pending flag for an interrupt request.
 * @implements    IntCtrl_Ip_GetPending_Activity
 */
boolean IntCtrl_Ip_GetPending(IRQn_Type eIrqNumber)
{
    return Call_IntCtrl_Ip_GetPendingPrivileged(eIrqNumber);
}

/**
 * @internal
 * @brief         Gets the active flag for an interrupt request.
 * @implements    IntCtrl_Ip_GetActive_Activity
 */
boolean IntCtrl_Ip_GetActive(IRQn_Type eIrqNumber)
{
    return Call_IntCtrl_Ip_GetActivePrivileged(eIrqNumber);
}

#if (INT_CTRL_IP_MSCM_SYSTEM_INTERRUPT_ROUTER == STD_ON)
/**
 * @internal
 * @brief         Sets the target cores for an interrupt request.
 * @implements    IntCtrl_Ip_SetTargetCores_Activity
 */
void IntCtrl_Ip_SetTargetCores(IRQn_Type eIrqNumber, uint8 u8TargetCores)
{
    Call_IntCtrl_Ip_SetTargetCoresPrivileged(eIrqNumber,u8TargetCores);
}
#endif

#if (INT_CTRL_IP_MSI_AVAILABLE == STD_ON)
/**
 * @internal
 * @brief         Generates an interrupt request to a CPU target.
 * @implements    IntCtrl_Ip_GenerateDirectedCpuInterrupt_Activity
 */
void IntCtrl_Ip_GenerateDirectedCpuInterrupt(IRQn_Type eIrqNumber, IntCtrl_Ip_IrqTargetType eCpuTarget)
{
    Call_IntCtrl_Ip_GenerateDirectedCpuInterruptPrivileged(eIrqNumber,eCpuTarget);
}
#endif /* INT_CTRL_IP_MSI_AVAILABLE == STD_ON */

#define PLATFORM_STOP_SEC_CODE
#include "Platform_MemMap.h"

/** @} */
