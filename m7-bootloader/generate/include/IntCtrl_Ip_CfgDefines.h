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

#ifndef INTCTRL_IP_CFG_DEFINES_H_
#define INTCTRL_IP_CFG_DEFINES_H_

/*==================================================================================================
                                         INCLUDE FILES
==================================================================================================*/
#include "IntCtrl_Ip_DeviceRegisters.h"

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
/* Development error detection */
#define INT_CTRL_IP_DEV_ERROR_DETECT              (STD_ON)

/* CPU to CPU interrupt (MSI) routing through MSCM */
#define INT_CTRL_IP_MSI_AVAILABLE                 (STD_ON)

/* MSI target core count */
#define INTCTRL_IP_MSI_CORE_CNT                   (7U)

/* MSI vector min */
#define INTCTRL_IP_DIRECTED_CPU_INT_MIN           (INT0_IRQn)

/* MSI vector max */
#define INTCTRL_IP_DIRECTED_CPU_INT_MAX           (INT2_IRQn)

/* System interrupt routing through MSCM */
#define INT_CTRL_IP_MSCM_SYSTEM_INTERRUPT_ROUTER  (STD_ON)

/* First implemented interrupt vector */
#define INT_CTRL_IP_IRQ_MIN                       (Pcie_1_MSI_IRQn)

/* Last implemented interrupt vector */
#define INT_CTRL_IP_IRQ_MAX                       (PCIE1_TLP_IRQn)

/* Number of priority bits implemented */
#define INT_CTRL_IP_NVIC_PRIO_BITS                (4U)

/* User mode support */
#define INTCTRL_PLATFORM_ENABLE_USER_MODE_SUPPORT (STD_OFF)

#endif /* INTCTRL_IP_CFG_DEFINES_H_ */

