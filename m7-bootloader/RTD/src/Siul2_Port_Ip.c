/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : SIUL2
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
*   @file    Siul2_Port_Ip.c
*
*   @addtogroup Port_IPL
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
#include "Siul2_Port_Ip.h"

#ifdef PORT_ENABLE_USER_MODE_SUPPORT
   #define USER_MODE_REG_PROT_ENABLED   (PORT_ENABLE_USER_MODE_SUPPORT)
   #include "RegLockMacros.h"
   #include "OsIf_Internal.h"
#endif

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/*
* @brief Parameters that shall be published within the driver header file and also in the
* module's description file
*/
#define SIUL2_PORT_IP_VENDOR_ID_C                     43
#define SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_C      4
#define SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_C      4
#define SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_C   0
#define SIUL2_PORT_IP_SW_MAJOR_VERSION_C              1
#define SIUL2_PORT_IP_SW_MINOR_VERSION_C              0
#define SIUL2_PORT_IP_SW_PATCH_VERSION_C              0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if the files Siul2_Port_Ip.c and Siul2_Port_Ip.h are of the same version */
#if (SIUL2_PORT_IP_VENDOR_ID_C != SIUL2_PORT_IP_VENDOR_ID_H)
    #error "Siul2_Port_Ip.c and Siul2_Port_Ip.h have different vendor ids"
#endif

/* Check if Siul2_Port_Ip.c and Siul2_Port_Ip.h are of the same Autosar version */
#if ((SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_C    != SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_H) || \
     (SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_C    != SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_H) || \
     (SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_C != SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Siul2_Port_Ip.c and Siul2_Port_Ip.h are different"
#endif

/* Check if Siul2_Port_Ip.c and Siul2_Port_Ip.h are of the same Software version */
#if ((SIUL2_PORT_IP_SW_MAJOR_VERSION_C != SIUL2_PORT_IP_SW_MAJOR_VERSION_H) || \
     (SIUL2_PORT_IP_SW_MINOR_VERSION_C != SIUL2_PORT_IP_SW_MINOR_VERSION_H) || \
     (SIUL2_PORT_IP_SW_PATCH_VERSION_C != SIUL2_PORT_IP_SW_PATCH_VERSION_H)    \
    )
    #error "Software Version Numbers of Siul2_Port_Ip.c and Siul2_Port_Ip.h are different"
#endif

/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
#define SIUL2_NUM_OF_PIN_PORT           16u
#define SIUL2_MAX_NUM_OF_IMCR_REG       512u

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/
#define PORT_START_SEC_CONST_32
#include "Port_MemMap.h"

/**
* @brief Base address array for Siul2 instances
*/
static const uint32 Port_au32Siul2BaseAddr[] =
{
#ifdef SIUL2_BASE
    SIUL2_BASE
#endif
#ifdef SIUL2_0_BASE
    SIUL2_0_BASE
#endif
#ifdef SIUL2_1_BASE
    ,SIUL2_1_BASE
#endif
#ifdef SIUL2_AE_BASE
    ,SIUL2_AE_BASE
#endif
};

#define PORT_STOP_SEC_CONST_32
#include "Port_MemMap.h"

#define PORT_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Port_MemMap.h"

static const Siul2_Port_Ip_PinSettingsConfig * pPort_Setting;

#define PORT_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Port_MemMap.h"

#define PORT_START_SEC_VAR_NO_INIT_32
#include "Port_MemMap.h"

static uint32 u32MaxPinConfigured;

#define PORT_STOP_SEC_VAR_NO_INIT_32
#include "Port_MemMap.h"
/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
#define PORT_START_SEC_CODE
#include "Port_MemMap.h"
/*!
 * @brief Initializes the pins with the given configuration structure
 *
 * This function configures the pins with the options provided in the
 * given structure.
 *
 * @param[in] pinNumber the number of configured pins in structure
 * @param[in] config the configuration structure
  */
static void Siul2_Port_Ip_PinInit(const Siul2_Port_Ip_PinSettingsConfig * config);
/*!
 * @brief Get the MSCR configuration from the MSCR register
 *
 * @param[in] pinNumber the number of configured pins in structure
 * @param[in] config the configuration structure
  */
static inline void Siul2_Port_Ip_GetMSCRConfiguration(Siul2_Port_Ip_PinSettingsConfig * config,
                                                      const Siul2_Port_Ip_PortType * const base,
                                                      uint16 pin);
/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/
/*FUNCTION**********************************************************************
 *
 * Function Name : PINS_Init
 * Description   : This function configures the pin feature with the options
 * provided in the given structure.
 *
 *END**************************************************************************/
static void Siul2_Port_Ip_PinInit(const Siul2_Port_Ip_PinSettingsConfig * config)
{
    uint32 pinsValues = 0U;
    uint8 inputMuxIterator;
    uint32 imcrRegIdx;
    uint8 siulInstance;
#ifdef SIUL2_0_BASE
    SIUL2_Type * imcrBase = (SIUL2_Type *)SIUL2_0_BASE;
#endif /* SIUL2_0_BASE */
#ifdef SIUL2_BASE
    SIUL2_Type * imcrBase = (SIUL2_Type *)SIUL2_BASE;
#endif /* SIUL2_BASE */
    SIUL2_PORT_DEV_ASSERT((boolean)(config != NULL));
    SIUL2_PORT_DEV_ASSERT((boolean)(config->pinPortIdx < SIUL2_MSCR_COUNT));

#ifdef SIUL2
    if (config->base == SIUL2)
    {
        siulInstance = 0;
    }
#endif /* SIUL2 */
#ifdef SIUL2_0
    if (config->base == SIUL2_0)
    {
        siulInstance = 0;
    }
#endif /* SIUL2_0 */
#ifdef SIUL2_1
    else
    {
        siulInstance = 1;
    }
#endif /* SIUL2_1 */

    if (config->pullConfig != PORT_INTERNAL_PULL_NOT_ENABLED)
    {
        pinsValues |= SIUL2_MSCR_PUE(1);
        pinsValues |= SIUL2_MSCR_PUS(config->pullConfig);
    }

    pinsValues |= SIUL2_MSCR_OBE(config->outputBuffer);
#ifdef FEATURE_SIUL2_PORT_IP_HAS_INVERT_DATA
    pinsValues |= SIUL2_MSCR_INV(config->invert);
#endif /* FEATURE_SIUL2_PORT_IP_HAS_INVERT_DATA */
#ifdef FEATURE_SIUL2_PORT_IP_HAS_PULL_KEEPER
    pinsValues |= SIUL2_MSCR_PKE(config->pullKeep);
#endif /* FEATURE_SIUL2_PORT_IP_HAS_PULL_KEEPER */
#ifdef FEATURE_SIUL2_PORT_IP_HAS_RECEIVER_SELECT
    pinsValues |= SIUL2_MSCR_RCVR(config->receiverSel);
#endif /* FEATURE_SIUL2_PORT_IP_HAS_RECEIVER_SELECT*/
#ifdef FEATURE_SIUL2_PORT_IP_HAS_OPEN_DRAIN
    pinsValues |= SIUL2_MSCR_ODE(config->openDrain);
#endif /* FEATURE_SIUL2_PORT_IP_HAS_OPEN_DRAIN */
    pinsValues |= SIUL2_MSCR_IBE(config->inputBuffer);
    pinsValues |= SIUL2_MSCR_SRE(config->slewRateCtrlSel);
    pinsValues |= SIUL2_MSCR_SMC(config->safeMode);
    pinsValues |= SIUL2_MSCR_SSS(config->mux);

    /* Configure initial value for GPIO pin in GPIO mux */
    if ((PORT_MUX_AS_GPIO == config->mux) && (PORT_OUTPUT_BUFFER_ENABLED == config->outputBuffer))
    {
        Siul2_Port_Ip_SetGPDO(siulInstance,(uint16)config->pinPortIdx,config->initValue);
    }

    /* Write to Multiplexed Signal Configuration Register */
    config->base->MSCR[config->pinPortIdx] = pinsValues;

    /* Write to Input Multiplexed Signal Configuration Register */
    if (PORT_INPUT_BUFFER_ENABLED == config->inputBuffer)
    {
        for (inputMuxIterator = 0U; inputMuxIterator < FEATURE_SIUL2_MAX_NUMBER_OF_INPUT; inputMuxIterator++)
        {
            /* Check if input mux information needs to be configured */
            if (PORT_INPUT_MUX_NO_INIT != config->inputMux[inputMuxIterator])
            {
                /* Write to Input Mux register */
                imcrRegIdx = config->inputMuxReg[inputMuxIterator];
                /* If the IMCR number is higher than 512 then the IMCR register is on siul2_1 */
                if(imcrRegIdx<SIUL2_MAX_NUM_OF_IMCR_REG)
                {
                    /*use the base address of siul2_0*/
                    #ifdef SIUL2_0_BASE
                        imcrBase = (SIUL2_Type *)SIUL2_0_BASE;
                    #endif /* SIUL2_0_BASE */
                    #ifdef SIUL2_BASE
                        imcrBase = (SIUL2_Type *)SIUL2_BASE;
                    #endif /* SIUL2_BASE */
                }
#ifdef SIUL2_1_BASE
                else
                {
                    /*use the base address of siul2_1*/
                    imcrBase = (SIUL2_Type *)SIUL2_1_BASE;
                    imcrRegIdx = imcrRegIdx - SIUL2_MAX_NUM_OF_IMCR_REG;
                }
#endif /* SIUL2_1_BASE */
                /* Config input signal */
                imcrBase->IMCR[imcrRegIdx % SIUL2_MAX_NUM_OF_IMCR_REG] = SIUL2_IMCR_SSS(config->inputMux[inputMuxIterator]);
            }
        }
    }
}

/*!
 * @brief Initializes the pins with the given configuration structure
 *
 * This function configures the pins with the options provided in the
 * given structure.
 *
 * @param[in] pinNumber the number of configured pins in structure
 * @param[in] config the configuration structure
  */
static inline void Siul2_Port_Ip_GetMSCRConfiguration(Siul2_Port_Ip_PinSettingsConfig * config,
                                                      const Siul2_Port_Ip_PortType * const base,
                                                      uint16 pin)
{
    uint32 u32RegVal = 0xFFFFFFFFUL;
    Siul2_Port_Ip_PortPullConfig pullValue;

    u32RegVal = base->MSCR[pin];
    config->mux = (Siul2_Port_Ip_PortMux)((u32RegVal & SIUL2_MSCR_SSS_MASK) >> SIUL2_MSCR_SSS_SHIFT);
    config->safeMode = (Siul2_Port_Ip_PortSafeMode)((u32RegVal & SIUL2_MSCR_SMC_MASK) >> SIUL2_MSCR_SMC_SHIFT);

    if (0U == ((u32RegVal & SIUL2_MSCR_PUE_MASK) >> SIUL2_MSCR_PUE_SHIFT))
    {
        pullValue = PORT_INTERNAL_PULL_NOT_ENABLED;
    }
    else
    {
        pullValue = (Siul2_Port_Ip_PortPullConfig)((u32RegVal & SIUL2_MSCR_PUS_MASK) >> SIUL2_MSCR_PUS_SHIFT);
    }

    config->pullConfig = pullValue;
    config->slewRateCtrlSel = (Siul2_Port_Ip_PortSlewRateControl)((u32RegVal & SIUL2_MSCR_SRE_MASK) >> SIUL2_MSCR_SRE_SHIFT);
#ifdef FEATURE_SIUL2_PORT_IP_HAS_RECEIVER_SELECT
    config->receiverSel = (Siul2_Port_Ip_PortReceiverSelect)((u32RegVal & SIUL2_MSCR_RCVR_MASK) >> SIUL2_MSCR_RCVR_SHIFT);
#endif /* FEATURE_SIUL2_PORT_IP_HAS_RECEIVER_SELECT */
#ifdef FEATURE_SIUL2_PORT_IP_HAS_OPEN_DRAIN
    config->openDrain = (Siul2_Port_Ip_PortOpenDrain)((u32RegVal & SIUL2_MSCR_ODE_MASK) >> SIUL2_MSCR_ODE_SHIFT);
#endif /* FEATURE_SIUL2_PORT_IP_HAS_OPEN_DRAIN */
#ifdef FEATURE_SIUL2_PORT_IP_HAS_DRIVE_STRENGTH
    config->driveStrength = (Siul2_Port_Ip_PortDriveStrength)((u32RegVal & SIUL2_MSCR_DSE_MASK) >> SIUL2_MSCR_DSE_SHIFT);
#endif /* FEATURE_SIUL2_PORT_IP_HAS_DRIVE_STRENGTH */
#ifdef FEATURE_SIUL2_PORT_IP_HAS_INPUT_FILTER
    config->inputFilter = (Siul2_Port_Ip_PortInputFilter)((u32RegVal & SIUL2_MSCR_IFE_MASK) >> SIUL2_MSCR_IFE_SHIFT);
#endif /* FEATURE_SIUL2_PORT_IP_HAS_INPUT_FILTER */
#ifdef FEATURE_SIUL2_PORT_IP_HAS_INVERT_DATA
    config->invert = (Siul2_Port_Ip_PortInvert)((u32RegVal & SIUL2_MSCR_INV_MASK) >> SIUL2_MSCR_INV_SHIFT);
#endif /* FEATURE_SIUL2_PORT_IP_HAS_INVERT_DATA */
#ifdef FEATURE_SIUL2_PORT_IP_HAS_PULL_KEEPER
            config->pullKeep = (Siul2_Port_Ip_PortPullKeep)((u32RegVal & SIUL2_MSCR_PKE_MASK) >> SIUL2_MSCR_PKE_SHIFT);
#endif /* FEATURE_SIUL2_PORT_IP_HAS_PULL_KEEPER */
    config->inputBuffer = (Siul2_Port_Ip_PortInputBuffer)((u32RegVal & SIUL2_MSCR_IBE_MASK) >> SIUL2_MSCR_IBE_SHIFT);
    config->outputBuffer = (Siul2_Port_Ip_PortOutputBuffer)((u32RegVal & SIUL2_MSCR_OBE_MASK) >> SIUL2_MSCR_OBE_SHIFT);
}

#if (defined(MCAL_ENABLE_USER_MODE_SUPPORT) && defined(PORT_ENABLE_USER_MODE_SUPPORT) && (STD_ON == PORT_ENABLE_USER_MODE_SUPPORT))
#if (defined(MCAL_SIUL2_REG_PROT_AVAILABLE) && (STD_ON == MCAL_SIUL2_REG_PROT_AVAILABLE))
/*FUNCTION**********************************************************************
 *
 * Function Name : Siul2_Port_Ip_SetUserAccessAllowed
 * Description   : Enables SIUL2 registers writing in User Mode by configuring REG_PROT
 *                 Sets the UAA (User Access Allowed) bit of the SIUL2 IP allowing SIUL2 registers writing in User Mode
 *
 *END**************************************************************************/

static void Siul2_Port_Ip_SetUserAccessAllowed(void)
{
#ifdef SIUL2_BASE
    SET_USER_ACCESS_ALLOWED(SIUL2_BASE, SIUL2_PROT_MEM_U32);
#endif /* SIUL2_BASE */
#ifdef SIUL2_0_BASE
    SET_USER_ACCESS_ALLOWED(SIUL2_0_BASE, SIUL2_PROT_MEM_U32);
#endif /* SIUL2_0_BASE */
#ifdef SIUL2_1_BASE
    SET_USER_ACCESS_ALLOWED(SIUL2_1_BASE, SIUL2_PROT_MEM_U32);
#endif /* SIUL2_1_BASE */
#ifdef SIUL2_AE_BASE
#if(STD_ON == PORT_SIUL2_AE_ENABLED)
    SET_USER_ACCESS_ALLOWED(SIUL2_AE_BASE, SIUL2_AE_PROT_MEM_U32);
#endif /* (STD_ON == PORT_SIUL2_AE_ENABLED) */
#endif /* SIUL2_AE_BASE */
}
#endif /* (defined(MCAL_SIUL2_REG_PROT_AVAILABLE) && (STD_ON == MCAL_SIUL2_REG_PROT_AVAILABLE)) */
#endif /* (defined(MCAL_ENABLE_USER_MODE_SUPPORT) && defined(PORT_ENABLE_USER_MODE_SUPPORT) && (STD_ON == PORT_ENABLE_USER_MODE_SUPPORT)) */

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/
void Siul2_Port_Ip_SetMSCR(uint8 SiulInstance, uint16 MscrInstance, uint32 value)
{
    PORT_WRITE32(SIUL2_MSCR_ADDR32(SiulInstance,(uint32)MscrInstance),value);
}

uint32 Siul2_Port_Ip_ReadMSCR(uint8 SiulInstance, uint16 MscrInstance)
{
    /* Return the value from MSCR register with MscrInstance */
    return PORT_READ32(SIUL2_MSCR_ADDR32(SiulInstance,(uint32)MscrInstance));
}

void Siul2_Port_Ip_SetIMCR(uint8 SiulInstance, uint16 ImcrInstance, uint32 value)
{
    /* Write the value into IMCR register */
    PORT_WRITE32(SIUL2_IMCR_ADDR32(SiulInstance,(uint32)ImcrInstance),value);
}

void Siul2_Port_Ip_SetGPDO(uint8 SiulInstance, uint16 GpdoInstance, uint8 value)
{
    /* If the value is low or high */
    if (value != PORT_PIN_LEVEL_NOTCHANGED_U8)
    {
        /* Write the value into GPDO register */
        PORT_WRITE8(SIUL2_GPDO_ADDR8(SiulInstance,GpdoInstance),value);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Siul2_Port_Ip_Init
 * Description   : This function configures the pins with the options provided
 * in the given structure.
 *
 * @implements Siul2_Port_Ip_Init_Activity
 *END**************************************************************************/
Siul2_Port_Ip_PortStatusType Siul2_Port_Ip_Init(uint32 pinCount,
                                       const Siul2_Port_Ip_PinSettingsConfig config[])
{
    uint32 i;

#if (defined(MCAL_ENABLE_USER_MODE_SUPPORT) && defined(PORT_ENABLE_USER_MODE_SUPPORT) && (STD_ON == PORT_ENABLE_USER_MODE_SUPPORT))
#if (defined(MCAL_SIUL2_REG_PROT_AVAILABLE) && (STD_ON == MCAL_SIUL2_REG_PROT_AVAILABLE))
    /* Enable register access from user mode, if enabled from configuration file */
    OsIf_Trusted_Call(Siul2_Port_Ip_SetUserAccessAllowed);
#endif /* (defined(MCAL_SIUL2_REG_PROT_AVAILABLE) && (STD_ON == MCAL_SIUL2_REG_PROT_AVAILABLE)) */
#endif /* (defined(MCAL_ENABLE_USER_MODE_SUPPORT) && defined(PORT_ENABLE_USER_MODE_SUPPORT) && (STD_ON == PORT_ENABLE_USER_MODE_SUPPORT)) */

    /* Store the configuration pointer */
    pPort_Setting = config;

    /* Store the number of configured pins */
    u32MaxPinConfigured = pinCount;
    for (i = 0U; i < pinCount; i++)
    {
        Siul2_Port_Ip_PinInit(&config[i]);
    }

    return SIUL2_PORT_SUCCESS;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Siul2_Port_Ip_SetPullSel
 * Description   : This function configures the internal resistor.
 *
 * @implements Siul2_Port_Ip_SetPullSel_Activity
 *END**************************************************************************/
void Siul2_Port_Ip_SetPullSel(Siul2_Port_Ip_PortType * const base,
                              uint16 pin,
                              Siul2_Port_Ip_PortPullConfig pullConfig)
{
    uint32 regVal;
    uint32 pueVal;
    uint32 pusVal;

    SIUL2_PORT_DEV_ASSERT((boolean)(base != NULL));
    SIUL2_PORT_DEV_ASSERT((boolean)(pin < SIUL2_NUM_OF_PIN_PORT));

    /* If that pin belong to SIUL2_AE*/
#ifdef FEATURE_SIUL2_HAS_AE_INSTANCE
    if ((uint32)base > (uint32)SIUL2_AE)
    {
        pueVal = SIUL2_AE_MSCR_PUE_MASK;
        pusVal = SIUL2_AE_MSCR_PUS_MASK;
    }
    else
#endif /* FEATURE_SIUL2_HAS_AE_INSTANCE */
    {
        pueVal = SIUL2_MSCR_PUE_MASK;
        pusVal = SIUL2_MSCR_PUS_MASK;
    }

    switch (pullConfig)
    {
        case PORT_INTERNAL_PULL_NOT_ENABLED:
        {
            /* Clear the Pull Enable bit field */
            base->MSCR[pin] &= ~pueVal;
            break;
        }
        case PORT_INTERNAL_PULL_DOWN_ENABLED:
        {
            regVal = base->MSCR[pin];
            /* Set the Pull Enable bit field */
            regVal |= pueVal;
            /* Clear the Pull Select bit field */
            regVal &= ~pusVal;
            base->MSCR[pin] = regVal;
            break;
        }
        case PORT_INTERNAL_PULL_UP_ENABLED:
        {
            regVal = base->MSCR[pin];
            /* Set the Pull Enable bit field */
            regVal |= pueVal;
            /* Set the Pull Select bit field */
            regVal |= pusVal;
            base->MSCR[pin] = regVal;
            break;
        }
        default:
            /* Invalid command */
            SIUL2_PORT_DEV_ASSERT(FALSE);
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Siul2_Port_Ip_SetOutputBuffer
 * Description   : This function configures the output buffer.
 *
 * @implements Siul2_Port_Ip_SetOutputBuffer_Activity
 *END**************************************************************************/
void Siul2_Port_Ip_SetOutputBuffer(Siul2_Port_Ip_PortType * const base,
                                   uint16 pin,
                                   boolean enable,
                                   Siul2_Port_Ip_PortMux mux)
{
    SIUL2_PORT_DEV_ASSERT((boolean)(base != NULL));
    SIUL2_PORT_DEV_ASSERT((boolean)(pin < SIUL2_NUM_OF_PIN_PORT));

    {
        /* Clear the OBE bit field */
        base->MSCR[pin] &= ~SIUL2_MSCR_OBE_MASK;
        /* Write the OBE bit field with enable */
        base->MSCR[pin] |= SIUL2_MSCR_OBE(enable ? 1UL : 0UL);
    }

    /* Clear the SSS bit field */
    base->MSCR[pin] &= ~SIUL2_MSCR_SSS_MASK;
    /* Write the SSS bit field with mux */
    base->MSCR[pin] |= SIUL2_MSCR_SSS(mux);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Siul2_Port_Ip_SetInputBuffer
 * Description   : This function configures the input buffer.
 *
 * @implements Siul2_Port_Ip_SetInputBuffer_Activity
 *END**************************************************************************/
void Siul2_Port_Ip_SetInputBuffer(Siul2_Port_Ip_PortType * const base,
                                  uint16 pin,
                                  boolean enable,
                                  uint32 inputMuxReg,
                                  Siul2_Port_Ip_PortInputMux inputMux)
{
    SIUL2_Type * siul2Base;
    uint32 imcrRegIdx = inputMuxReg;
    uint32 imcrVal;
    SIUL2_PORT_DEV_ASSERT((boolean)(pin < SIUL2_NUM_OF_PIN_PORT));

    if (base != NULL)
    {
        /* Enable/disable input buffer for input signal */
        base->MSCR[pin] &= ~SIUL2_MSCR_IBE_MASK;
        base->MSCR[pin] |= SIUL2_MSCR_IBE(enable ? 1UL : 0UL);
    }

    /* Check input mux to configure input signal */
    if (inputMux != PORT_INPUT_MUX_NO_INIT)
    {
        if (imcrRegIdx < SIUL2_MAX_NUM_OF_IMCR_REG)
        {
#ifdef SIUL2_0_BASE
            siul2Base = (SIUL2_Type *)SIUL2_0_BASE;
#endif /* SIUL2_0_BASE */
#ifdef SIUL2_BASE
            siul2Base = (SIUL2_Type *)SIUL2_BASE;
#endif /* SIUL2_BASE */
        }
#ifdef SIUL2_1_BASE
        else
        {
            siul2Base = (SIUL2_Type *)SIUL2_1_BASE;
        }
#endif /* SIUL2_1_BASE */
        /* Configure input mux */
        imcrVal  = siul2Base->IMCR[imcrRegIdx % SIUL2_MAX_NUM_OF_IMCR_REG];
        imcrVal &= ~SIUL2_IMCR_SSS_MASK;
        imcrVal |= SIUL2_IMCR_SSS(inputMux);
        siul2Base->IMCR[imcrRegIdx % SIUL2_MAX_NUM_OF_IMCR_REG] = imcrVal;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Siul2_Port_Ip_SetPinDirection
 * Description   : This function configures the pin direction
 *
 * @implements Siul2_Port_Ip_SetPinDirection_Activity
 *END**************************************************************************/
void Siul2_Port_Ip_SetPinDirection(Siul2_Port_Ip_PortType * const base,
                                   uint16 pin,
                                   Siul2_Port_Ip_PortDirectionType direction)
{
    SIUL2_PORT_DEV_ASSERT((boolean)(base != NULL));
    SIUL2_PORT_DEV_ASSERT((boolean)(pin < SIUL2_NUM_OF_PIN_PORT));

    switch (direction)
    {
    /* direction pin in */
    case SIUL2_PORT_IN:
        base->MSCR[pin] &= ~SIUL2_MSCR_OBE_MASK;
        base->MSCR[pin] |= SIUL2_MSCR_IBE(1UL);
        break;
    /* direction pin out */
    case SIUL2_PORT_OUT:
        base->MSCR[pin] &= ~SIUL2_MSCR_IBE_MASK;
        base->MSCR[pin] |= SIUL2_MSCR_OBE(1UL);
        break;
    /* direction in out */
    case SIUL2_PORT_IN_OUT:
        base->MSCR[pin] |= (SIUL2_MSCR_IBE_MASK | SIUL2_MSCR_OBE_MASK);
        break;
    /* direction hi_z */
    case SIUL2_PORT_HI_Z:
        base->MSCR[pin] &= ~(SIUL2_MSCR_IBE_MASK | SIUL2_MSCR_OBE_MASK);
        break;
    default:
        /* Do nothing */
        break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Siul2_Port_Ip_RevertPinConfiguration
 * Description   : This function configures the pin configuration with the values from the configuration structure
 *
 * @implements Siul2_Port_Ip_RevertPinConfiguration_Activity
 *END**************************************************************************/
uint32 Siul2_Port_Ip_RevertPinConfiguration(const Siul2_Port_Ip_PortType * const base,
                                           uint16 pin)
{
    uint16 u16PinIdx;
    uint32 u32RegVal = 0xFFFFFFFFUL;
    const Siul2_Port_Ip_PinSettingsConfig * ConfigPtr = pPort_Setting;
    uint32 MaxPinConfigured = u32MaxPinConfigured;
    uint32 portNumber;
    uint32 u32MscrId;

    SIUL2_PORT_DEV_ASSERT((boolean)(base != NULL));
    SIUL2_PORT_DEV_ASSERT((boolean)(pin < SIUL2_NUM_OF_PIN_PORT));

    /* Get the PortID:  Subtract the address of the first mscr from the base parameter then divide to 4 and 16 because there are 16 ports but each MSCR has 4 bytes */
#if (2 == SIUL2_NUM_SIUL2_INSTANCES_U8)
    /* Check if that pin is belong to SIUL2_1 or SIUL2_0 */
    if(base > (Siul2_Port_Ip_PortType *)SIUL2_1_BASE)
    {
        portNumber = (uint32)((uint32)((uint32)((uint32)base - (uint32)SIUL2_1_MSCR_BASE) >> 2U) >> 4U);
    }
    else
    {
        portNumber = (uint32)((uint32)((uint32)((uint32)base - (uint32)SIUL2_0_MSCR_BASE) >> 2U) >> 4U);
    }
#else
    portNumber = (uint32)((uint32)((uint32)((uint32)base - (uint32)SIUL2_MSCR_BASE) >> 2U) >> 4U);
#endif

    /* Get the MscrID: 16 is the maximum number of pins per port so the portNumber need to multiply 16 */
    u32MscrId = (portNumber << 4U) + (uint32)pin;

    /* The loop to find the Mscr Id in pin configuration's structure */
    for(u16PinIdx = 0U; u16PinIdx < MaxPinConfigured; u16PinIdx++)
    {
        /* If we found that pin */
        if(ConfigPtr[u16PinIdx].pinPortIdx == u32MscrId)
        {
            Siul2_Port_Ip_PinInit(&ConfigPtr[u16PinIdx]);
            u32RegVal = base->MSCR[pin];
            /* Break the loop. Do not need to search in all pin configuration's structure */
            break;
        }
    }
    /* Return the MSCR value */
    return u32RegVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : Siul2_Port_Ip_GetPinConfiguration
 * Description   : This function returns the value of the pin configuration register.
 *
 * @implements Siul2_Port_Ip_GetPinConfiguration_Activity
 *END**************************************************************************/
void Siul2_Port_Ip_GetPinConfiguration(const Siul2_Port_Ip_PortType * const base,
                                       Siul2_Port_Ip_PinSettingsConfig * config,
                                       uint16 pin)
{
    const Siul2_Port_Ip_PinSettingsConfig * ConfigPtr = pPort_Setting;
    uint32 MaxPinConfigured = u32MaxPinConfigured;
    uint32 portNumber;
    uint32 u32MscrId;
    uint32 u32MscrBase;
    uint16 u16PinIdx;
    uint8 inputMuxIterator;

    SIUL2_PORT_DEV_ASSERT((boolean)(base != NULL));
    SIUL2_PORT_DEV_ASSERT((boolean)(pin < SIUL2_NUM_OF_PIN_PORT));

    /* Choose the MSCR base address for the pin */
#if (2 == SIUL2_NUM_SIUL2_INSTANCES_U8)
    if(base > (Siul2_Port_Ip_PortType *)SIUL2_1_BASE)
    {
        u32MscrBase = (uint32)SIUL2_1_MSCR_BASE;
    }
    else
    {
        u32MscrBase = (uint32)SIUL2_0_MSCR_BASE;
    }
#else
    u32MscrBase = (uint32)SIUL2_MSCR_BASE;
#endif

    /* Get the PortID:  Subtract the address of the first mscr from the base parameter then divide to 4 and 16 because there are 16 ports and each MSCR has 4 bytes */
    portNumber = (uint32)((uint32)base - u32MscrBase) / 64UL;
    /* Get the MscrID: 16 is the maximum number of pins per port so the portNumber need to multiply 16 */
    u32MscrId = (portNumber << 4U) + (uint32)pin;

    for(u16PinIdx = 0U; u16PinIdx < MaxPinConfigured; u16PinIdx++)
    {
        /* If that pin was found */
        if(ConfigPtr[u16PinIdx].pinPortIdx == u32MscrId)
        {
            config->base = ConfigPtr[u16PinIdx].base;
            config->pinSiul2Instance = ConfigPtr[u16PinIdx].pinSiul2Instance;
            config->pinPortIdx = ConfigPtr[u16PinIdx].pinPortIdx;
            config->initValue = ConfigPtr[u16PinIdx].initValue;

            for (inputMuxIterator = 0U; inputMuxIterator < FEATURE_SIUL2_MAX_NUMBER_OF_INPUT; inputMuxIterator++)
            {
                config->inputMuxReg[inputMuxIterator] = ConfigPtr[u16PinIdx].inputMuxReg[inputMuxIterator];
                config->inputMux[inputMuxIterator] = ConfigPtr[u16PinIdx].inputMux[inputMuxIterator];
            }

            /* Get the MSCR configuration from register */
            Siul2_Port_Ip_GetMSCRConfiguration(config, base, pin);
            break;
        }
    }
}

#define PORT_STOP_SEC_CODE
#include "Port_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
