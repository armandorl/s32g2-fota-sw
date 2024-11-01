/**************************************************************************************************
 *
 * Copyright 2021 NXP
 *
 **************************************************************************************************
 *
 * NXP Confidential Proprietary. This software is owned or controlled by NXP and may only be used
 * strictly in accordance with the applicable terms. By expressly accepting such terms or by
 * downloading, installing, activating and/or otherwise using the software, you are agreeing that
 * you have read, and that you agree to comply with and are bound by, such license terms.
 * If you do not agree to be bound by the applicable license terms, then you may not retain,
 * install, activate or otherwise use the software.
 *
 * THIS SOFTWARE IS PROVIDED BY NXP "AS IS" AND ANY EXPRESSED OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL NXP OR ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
**************************************************************************************************/


/**
 * @page misra_violations MISRA-C:2012 violations
 *
 */
#include <stdio.h>
#include "S32G274A.h"
//#include "Pit_Ip.h"
#include "IntCtrl_Ip.h"
#include "device.h"
#include "Mcal.h"
#include "Clock_Ip.h"
#include "Siul2_Port_Ip.h"

#include "ext_flash.h"

#include "Hse_Ip.h"

#include "Swt_Ip_BOARD_InitPeripherals_PBcfg.h"
#include "Swt_Ip.h"

#ifdef LINFLEXD_1_LIN_UART_MODE
#include "Linflexd_Uart_Ip.h"
#endif

#include "OsIf.h"

#ifdef SJA1105_CONFIG
#include "Spi.h"
#include "switch_init.h"
#endif /* SJA1105_CONFIG */

extern ISR(PIT_0_ISR);
extern ISR(LINFLEXD1_UART_IRQHandler);

/* PIT instance used */
#define PIT_INST                (0U)
/* PIT timeout period */
#define PIT_PERIOD              (133333U)

#define CFG_PHY_CTRL_IDX        (0U)
#define CFG_PHY_SPEED           (GMAC_SPEED_1G)
#define ENABLE_PHY_LOOPBACK     (0U)   /* Set to 1 to enable PHY loop-back */
#define ENABLE_PHY_FULL_DUPLEX  (1U)   /* Set to 0 to enable PHY Half-duplex mode */

#define PHY_ID1                 (0x0022U)
#define PHY_ID2                 (0x1622U)

#define PHY_LED_ON              (1U)

/*==================================================================================================
*                                    HSE  GLOBAL VARIABLES
==================================================================================================*/

/* Array of variables used to store the descriptors containing the service request for HSE firmware. This example uses both synchronous and
asynchronous calls to Hse Ip, made only on MU0 instance. For this reason, we need to have a descriptor variable available for each of the channels in the MU0.
   The descriptors should be placed in the shared memory, in a non-cacheable area */
hseSrvDescriptor_t   Hse_aSrvDescriptor[HSE_NUM_OF_CHANNELS_PER_MU] __attribute__((section(".non_cacheable")));


/* Variable that will store the internal state machine of the Hse Ip layer. As this application uses only MU0 to communicate
   with HSE, there is no need for an array of such variables.
   The address of the variable storing the internal state machine should be provided as parameter when the Hse Ip layer
is initialized on one MU instance. */
static Hse_Ip_MuStateType HseIp_MuState;
/* List of identifiers for the MU instances */
#define MU0_INSTANCE_U8                     ((uint8)0U)
#define MU1_INSTANCE_U8                     ((uint8)1U)

/* Identifier for the only MU instance used in this example */
#define APP_MU_INSTANCE_U8                  (MU0_INSTANCE_U8)
/**
* @brief        MU0 Ored Rx Interrupt handler
* @details      Defined in Mu_Ip_Irq.c and used by Hse_Ip layer to process the interrupts triggered when
                responses are received from HSE for requests made on MU0 instance
*/
extern void Mu_Ip_Mu0_OredRx_Isr(void);

#define TIMEOUT_TICKS_U32                   ((uint32)10000000U)
/* Table containing NVM key catalog entries */
const hseKeyGroupCfgEntry_t Hse_aNvmKeyCatalog[] =
{
    /* NvmKeyGroup_MASTER_ECU_KEY__BOOT_MAC_KEY__Key1_To_Key10 */
    {(HSE_MU0_MASK), HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_SHE, 12U, 128U, {0U, 0U}},
	/* CUST keys */    \
	{ HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES,           3U,         128U, {0U,0U} },
	 /* HMAC key */ \
	{ HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_HMAC,          1U,         512U, {0U,0U} },
	/* ECC keys */ \
	{ HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_ECC_PAIR,      1U,         256U, {0U,0U} },
    { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_ECC_PUB,       1U,         256U, {0U,0U} },
	 /* RSA keys */ \
	 { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_RSA_PAIR,      2U,         2048U, {0U,0U} },
	 { HSE_ALL_MU_MASK, HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_RSA_PUB,       2U,         2048U, {0U,0U} },

    /* Marker to end the key catalog */
    {0U, 0U, 0U, 0U, 0U, {0U, 0U}}
};

/* Table containing RAM key catalog entries */
const hseKeyGroupCfgEntry_t Hse_aRamKeyCatalog[] =
{
    /* RamKeyGroup_RamKey */
    {(HSE_MU0_MASK), HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_SHE, 1U, 128U, {0U, 0U}},
    /* Symmetric key */
    { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_AES,            1U,        128U, {0U,0U} },
    /* Usable only on MU0 */
    { HSE_MU0_MASK,    HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_AES,            2U,        256U, {0U,0U} },
    /* HMAC key */
    { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_HMAC,           1U,        512U, {0U,0U} },
    /* ECC keys*/
    { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_ECC_PAIR,       1U,        256U, {0U,0U} },
    { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_ECC_PUB,        1U,        256U, {0U,0U} },
    /* Temporary secrets */
    { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_SHARED_SECRET,  1U,        638U, {0U,0U} },
    { HSE_ALL_MU_MASK, HSE_KEY_OWNER_ANY,   HSE_KEY_TYPE_SHARED_SECRET,  1U,        4096U, {0U,0U} },
    /* Marker to end the key catalog */
    {0U, 0U, 0U, 0U, 0U, {0U, 0U}}
};


static Hse_Ip_ReqType HseIp_aRequest[HSE_NUM_OF_CHANNELS_PER_MU];
static hseSrvResponse_t App_FormatHseKeyCatalogs(void)
{
    hseSrvDescriptor_t* pHseSrvDescriptor;
    hseSrvResponse_t    RetVal      = HSE_SRV_RSP_GENERAL_ERROR;
    uint8               u8MuChannel = Hse_Ip_GetFreeChannel(APP_MU_INSTANCE_U8);

    if(HSE_IP_INVALID_MU_CHANNEL_U8 != u8MuChannel)
    {
        /* Optimize a bit the code by storing the address of the channel's descriptor in a pointer */
        pHseSrvDescriptor = &Hse_aSrvDescriptor[u8MuChannel];

        /* Create the service request for HSE by setting the descriptor's members */
        pHseSrvDescriptor->srvId                                         = HSE_SRV_ID_FORMAT_KEY_CATALOGS;
        pHseSrvDescriptor->hseSrv.formatKeyCatalogsReq.pNvmKeyCatalogCfg = HSE_PTR_TO_HOST_ADDR(Hse_aNvmKeyCatalog);
        pHseSrvDescriptor->hseSrv.formatKeyCatalogsReq.pRamKeyCatalogCfg = HSE_PTR_TO_HOST_ADDR(Hse_aRamKeyCatalog);

        /* Build the request to be sent to Hse Ip layer */
        HseIp_aRequest[u8MuChannel].eReqType   = HSE_IP_REQTYPE_SYNC;
        HseIp_aRequest[u8MuChannel].u32Timeout = TIMEOUT_TICKS_U32;

        /* Send the request to Hse Ip layer */
        RetVal = Hse_Ip_ServiceRequest(APP_MU_INSTANCE_U8, u8MuChannel, &HseIp_aRequest[u8MuChannel], pHseSrvDescriptor);
    }

    return RetVal;
}

void Eth_T_EnableIRQs(void)
{
    unsigned int instance, channel;

#ifdef FEATURE_ETH_COMMON_IRQS
    /*! @brief ETH common IRQ number for each instance. */
    const IRQn_Type ethCommonIrqId[FEATURE_ETH_NUM_INSTANCES] = FEATURE_ETH_COMMON_IRQS;
    /*! @brief ETH common IRQ handler for each instance. */
    void (*ethCommonIrqHandler[FEATURE_ETH_NUM_INSTANCES])(void) = FEATURE_GMAC_COMMON_IRQ_HDLRS;
#endif /* FEATURE_ETH_COMMON_IRQS */

#ifdef FEATURE_ETH_SAFETY_IRQS
    /*! @brief ETH safety IRQ number for each instance. */
    const IRQn_Type ethSafetyIrqId[FEATURE_ETH_NUM_INSTANCES] = FEATURE_ETH_SAFETY_IRQS;
    /*! @brief ETH safety IRQ handler for each instance. */
    void (*ethSafetyIrqHandler[FEATURE_ETH_NUM_INSTANCES])(void) = FEATURE_GMAC_SAFETY_IRQ_HDLRS;
#endif /* FEATURE_ETH_COMMON_IRQS */

#ifdef FEATURE_ETH_TX_IRQS
    /*! @brief ETH transmit IRQ number for each channel and each instance. */
    const IRQn_Type ethTxIrqId[FEATURE_ETH_NUM_INSTANCES][FEATURE_ETH_NUM_CHANNELS] = FEATURE_ETH_TX_IRQS;
    /*! @brief ETH transmit IRQ handler for each channel and each instance. */
    void (*ethTxIrqHandler[FEATURE_ETH_NUM_INSTANCES][FEATURE_ETH_NUM_CHANNELS])(void) = FEATURE_ETH_TX_IRQ_HDLRS;
#endif /* FEATURE_ETH_TX_IRQS */

#ifdef FEATURE_ETH_RX_IRQS
    /*! @brief ETH receive IRQ number for each channel and each instance. */
    const IRQn_Type ethRxIrqId[FEATURE_ETH_NUM_INSTANCES][FEATURE_ETH_NUM_CHANNELS] = FEATURE_ETH_RX_IRQS;
    /*! @brief ETH receive IRQ handler for each channel and each instance. */
    void (*ethRxIrqHandler[FEATURE_ETH_NUM_INSTANCES][FEATURE_ETH_NUM_CHANNELS])(void) = FEATURE_ETH_RX_IRQ_HLDRS;
#endif /* FEATURE_GMAC_RX_IRQS */

    /* Enable IRQs in a platform-specific way */
//    for (instance = 0U; instance < FEATURE_GMAC_NUM_INSTANCES; ++instance)
    {
    #ifdef FEATURE_ETH_COMMON_IRQS
        ((volatile uint32*)S32_SCB->VTOR)[ethCommonIrqId[instance] + 16] = (uint32)ethCommonIrqHandler[instance];
        S32_NVIC->ISER[(uint32)(ethCommonIrqId[instance]) >> 5U] = (uint32)(1UL << ((uint32)(ethCommonIrqId[instance]) & (uint32)0x1FU));
    #endif /* FEATURE_ETH_COMMON_IRQS */

    #ifdef FEATURE_ETH_SAFETY_IRQS
        ((volatile uint32*)S32_SCB->VTOR)[ethSafetyIrqId[instance] + 16] = (uint32)ethSafetyIrqHandler[instance];
        S32_NVIC->ISER[(uint32)(ethSafetyIrqId[instance]) >> 5U] = (uint32)(1UL << ((uint32)(ethSafetyIrqId[instance]) & (uint32)0x1FU));
    #endif /* FEATURE_ETH_COMMON_IRQS */

    #ifdef FEATURE_ETH_RX_IRQS
        for (channel = 0U; channel < FEATURE_ETH_NUM_CHANNELS; ++channel)
        {
            ((volatile uint32*)S32_SCB->VTOR)[ethRxIrqId[instance][channel] + 16] = (uint32)ethRxIrqHandler[instance][channel];
            S32_NVIC->ISER[(uint32)(ethRxIrqId[instance][channel]) >> 5U] = (uint32)(1UL << ((uint32)(ethRxIrqId[instance][channel]) & (uint32)0x1FU));
        }
    #endif /* FEATURE_ETH_RX_IRQS */

    #ifdef FEATURE_ETH_TX_IRQS
        for (channel = 0U; channel < FEATURE_ETH_NUM_CHANNELS; ++channel)
        {
            ((volatile uint32*)S32_SCB->VTOR)[ethTxIrqId[instance][channel] + 16] = (uint32)ethTxIrqHandler[instance][channel];
            S32_NVIC->ISER[(uint32)(ethTxIrqId[instance][channel]) >> 5U] = (uint32)(1UL << ((uint32)(ethTxIrqId[instance][channel]) & (uint32)0x1FU));
        }
    #endif /* FEATURE_ETH_TX_IRQS */
    }
}

int32_t hse_init_keyslots(void)
{
	static volatile hseStatus_t            HseStatus;
    status_hse_ip_t        HseIpStatus = 0;
    static volatile hseSrvResponse_t       HseResponse;

    /* =============================================================================================================================== */
    /*    Initialize OsIf component. It will be used to measure timeouts while waiting for HSE to respond to synchronous requests      */
    /* =============================================================================================================================== */
    OsIf_Init(NULL_PTR);

    /* =============================================================================================================================== */
    /*    Check that HSE is initialized (along with RNG module) by reading the status bits in FSR                                      */
    /* =============================================================================================================================== */
    do {
    	HseStatus = Hse_Ip_GetHseStatus();
    	if ((HseStatus & (HSE_STATUS_INIT_OK | HSE_STATUS_RNG_INIT_OK)) ==
    			(HSE_STATUS_INIT_OK | HSE_STATUS_RNG_INIT_OK))
    		break;
    } while(1);

    /* =============================================================================================================================== */
    /*    Initialize Hse Ip layer for MU0 instance                                                                                     */
    /* =============================================================================================================================== */
    HseIpStatus = Hse_Ip_Init(APP_MU_INSTANCE_U8, &HseIp_MuState);

    printf("\r\nHSE was initializaed OK\r\n");
    /* =============================================================================================================================== */
    /*    Format HSE Nvm and Ram key catalogs                                                                                          */
    /* =============================================================================================================================== */
    HseResponse = App_FormatHseKeyCatalogs();
    if(HSE_SRV_RSP_OK != HseResponse)
    {
    	 return -1;
    }

    printf("HSE key slots was formated OK\r\n");

    return 0;
}

/**
* @brief        SWT0 Interrupt handler
* @details      Be used for calling Swt_Ip_IrqHandler defined in Swt_Ip.c
*/
extern void Swt_Ip_Swt0_Isr(void);

int32_t device_init(void)
{
    /* Init mode for PHY node and PHY interface with RGMII mode, speed 1G */
    //SRC->GMAC_0_CTRL_STS |= SRC_GMAC_0_CTRL_STS_PHY_MODE(0U) | SRC_GMAC_0_CTRL_STS_PHY_INTF_SEL(1U);

	#ifdef NUM_OF_CONFIGURED_PINS0
    /* Initialize all pins using the Port driver */
    Siul2_Port_Ip_Init(NUM_OF_CONFIGURED_PINS0, g_pin_mux_InitConfigArr0);
	#endif
	
    /* Initialize Clocks */
    Clock_Ip_Init(&Mcu_aClockConfigPB[0U]);

	IntCtrl_Ip_Init(&IntCtrlConfig_0);

    /*Enable the SWT0 interrupt vector */
    IntCtrl_Ip_InstallHandler(SWT0_IRQn, Swt_Ip_Swt0_Isr, NULL_PTR);

    /*Initialize SWT */
    Swt_Ip_Init(0, &Swt_Ip_1_Cfg0);

	#ifdef LINFLEXD_1_LIN_UART_MODE
	IntCtrl_Ip_EnableIrq(LINFLEXD1_IRQn);
	IntCtrl_Ip_InstallHandler(LINFLEXD1_IRQn, LINFLEXD1_UART_IRQHandler, NULL_PTR);
	#endif
    /* Install interrupt handlers for PIT and EMAC */
//    IntCtrl_Ip_InstallHandler(PIT0_IRQn, PIT_0_ISR, NULL_PTR);
//    IntCtrl_Ip_EnableIrq(PIT0_IRQn);
#if 0
	Eth_T_EnableIRQs();

    /* Initialize Os Interface */
    OsIf_Init(NULL_PTR);

    /* Initialize PIT driver and start the timer */
    Pit_Ip_Init(PIT_INST, &PIT_0_InitConfig_PB);
    Pit_Ip_InitChannel(PIT_INST, PitChannel_0);
    Pit_Ip_EnableChannelInterrupt(PIT_INST, CH_0);
    Pit_Ip_StartChannel(PIT_INST, CH_0, PIT_PERIOD);
#endif

	#ifdef LINFLEXD_1_LIN_UART_MODE
	/* Initialize LINFlexD module for UART usage */
	Linflexd_Uart_Ip_Init(1, &Linflexd_Uart_Ip_pHwConfigPB_1_BOARD_INITPERIPHERALS);
	#endif
	
#if 1
	if (hse_init_keyslots() < 0)
	{
		return -1;
	}
#endif

    /* Initialize and enable the GMAC module */
    //Gmac_Ip_Init(INST_GMAC_0, &Gmac_0_ConfigPB_BOARD_INITPERIPHERALS);
	if (qspi_init() < 0)
		return -2;

    return qspi_read_test();

#ifdef SJA1105_CONFIG
    Spi_Init()
    Switch_Init();
#endif /* SJA1105_CONFIG */
}
