/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : Crypto
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
*   @addtogroup CRYPTO
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Mcal.h"
#include "Hse_Ip.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MU_IP_IRQ_VENDOR_ID_C                    43
#define MU_IP_IRQ_SW_MAJOR_VERSION_C             1
#define MU_IP_IRQ_SW_MINOR_VERSION_C             0
#define MU_IP_IRQ_SW_PATCH_VERSION_C             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if Mu_Ip_Irq source file and Mcal.h header file are of the same vendor */
#if (MU_IP_IRQ_VENDOR_ID_C != MCAL_VENDOR_ID )
    #error "Mu_Ip_Irq.c and Mcal.h have different vendor ids"
#endif

/* Check if Mu_Ip_Irq source file and Mcal.h header file are of the same Software version */
#if ((MU_IP_IRQ_SW_MAJOR_VERSION_C != MCAL_SW_MAJOR_VERSION) || \
     (MU_IP_IRQ_SW_MINOR_VERSION_C != MCAL_SW_MINOR_VERSION) || \
     (MU_IP_IRQ_SW_PATCH_VERSION_C != MCAL_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Mu_Ip_Irq.c and Mcal.h are different"
#endif

/* Check if Mu_Ip_Irq source file and Hse_Ip.h header file are of the same vendor */
#if (MU_IP_IRQ_VENDOR_ID_C != HSE_IP_VENDOR_ID_H )
    #error "Mu_Ip_Irq.c and Hse_Ip.h have different vendor ids"
#endif

/* Check if Mu_Ip_Irq source file and Hse_Ip.h header file are of the same Software version */
#if ((MU_IP_IRQ_SW_MAJOR_VERSION_C != HSE_IP_SW_MAJOR_VERSION_H) || \
     (MU_IP_IRQ_SW_MINOR_VERSION_C != HSE_IP_SW_MINOR_VERSION_H) || \
     (MU_IP_IRQ_SW_PATCH_VERSION_C != HSE_IP_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Mu_Ip_Irq.c and Hse_Ip.h are different"
#endif

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

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL FUNCTIONS PROTOTYPES
==================================================================================================*/
ISR(Mu_Ip_Mu0_OredRx_Isr);
ISR(Mu_Ip_Mu0_OredGP_Isr);
ISR(Mu_Ip_Mu1_OredRx_Isr);
ISR(Mu_Ip_Mu1_OredGP_Isr);
ISR(Mu_Ip_Mu2_OredRx_Isr);
ISR(Mu_Ip_Mu2_OredGP_Isr);
ISR(Mu_Ip_Mu3_OredRx_Isr);
ISR(Mu_Ip_Mu3_OredGP_Isr);

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/
#define CRYPTO_START_SEC_CODE
#include "Crypto_MemMap.h"

/**
* @brief   Crypto handler for a MU instance RX interrupt.
* @details This function implements the ISR occurring on an Rx event on the MU instance 0.
*
* @isr
*
*/
ISR(Mu_Ip_Mu0_OredRx_Isr)
{
    Hse_Ip_RxIrqHandler(0U);
}

/**
* @brief   Crypto handler for a MU instance General Purpose interrupt.
* @details This function implements the ISR occurring on an General Purpose event on the MU instance 0.
*
* @isr
*
*/
ISR(Mu_Ip_Mu0_OredGP_Isr)
{
    Hse_Ip_GeneralPurposeIrqHandler(0U);
}


/**
* @brief   Crypto handler for a MU instance RX interrupt.
* @details This function implements the ISR occurring on an Rx event on the MU instance 1.
*
* @isr
*
*/
ISR(Mu_Ip_Mu1_OredRx_Isr)
{
    Hse_Ip_RxIrqHandler(1U);
}

/**
* @brief   Crypto handler for a MU instance General Purpose interrupt.
* @details This function implements the ISR occurring on an General Purpose event on the MU instance 1.
*
* @isr
*
*/
ISR(Mu_Ip_Mu1_OredGP_Isr)
{
    Hse_Ip_GeneralPurposeIrqHandler(1U);
}


/**
* @brief   Crypto handler for a MU instance RX interrupt.
* @details This function implements the ISR occurring on an Rx event on the MU instance 2.
*
* @isr
*
*/
ISR(Mu_Ip_Mu2_OredRx_Isr)
{
    Hse_Ip_RxIrqHandler(2U);
}

/**
* @brief   Crypto handler for a MU instance General Purpose interrupt.
* @details This function implements the ISR occurring on an General Purpose event on the MU instance 2.
*
* @isr
*
*/
ISR(Mu_Ip_Mu2_OredGP_Isr)
{
    Hse_Ip_GeneralPurposeIrqHandler(2U);
}


/**
* @brief   Crypto handler for a MU instance RX interrupt.
* @details This function implements the ISR occurring on an Rx event on the MU instance 3.
*
* @isr
*
*/
ISR(Mu_Ip_Mu3_OredRx_Isr)
{
    Hse_Ip_RxIrqHandler(3U);
}

/**
* @brief   Crypto handler for a MU instance General Purpose interrupt.
* @details This function implements the ISR occurring on an General Purpose event on the MU instance 3.
*
* @isr
*
*/
ISR(Mu_Ip_Mu3_OredGP_Isr)
{
    Hse_Ip_GeneralPurposeIrqHandler(3U);
}

#define CRYPTO_STOP_SEC_CODE
#include "Crypto_MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */
