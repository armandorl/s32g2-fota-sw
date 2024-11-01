/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!GlobalInfo
product: Clocks v7.0
processor: S32G274A_Rev2
package_id: S32G274A_Rev2_525bga
mcu_data: PlatformSDK_S32G_2020_12
processor_version: 0.0.0
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

#ifdef __cplusplus
extern "C"{
#endif



/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Clock_Ip_PBcfg.h"
#include "StandardTypes.h"
#include "Clock_Ip.h"

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

#define MCU_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "Mcu_MemMap.h"


/* TEXT BELOW IS USED AS SETTING FOR TOOLS *************************************
!!Configuration
name: BOARD_BootClockRUN
called_from_default_init: true
outputs:
- {id: A53_CORE_CLK.outFreq, value: 1 GHz}
- {id: A53_CORE_DIV10_CLK.outFreq, value: 100 MHz}
- {id: A53_CORE_DIV2_CLK.outFreq, value: 500 MHz}
- {id: ACCEL_PLL_PHI0.outFreq, value: 600 MHz}
- {id: ACCEL_PLL_PHI1.outFreq, value: 600 MHz}
- {id: ADC0_CLK.outFreq, value: 48 MHz}
- {id: ADC1_CLK.outFreq, value: 48 MHz}
- {id: CLKOUT0_CLK.outFreq, value: 40/13 MHz}
- {id: CLKOUT1_CLK.outFreq, value: 40 MHz}
- {id: CORE_PLL_DFS1.outFreq, value: 800 MHz}
- {id: CORE_PLL_DFS2.outFreq, value: 800 MHz}
- {id: CORE_PLL_DFS3.outFreq, value: 500 MHz}
- {id: CORE_PLL_DFS4.outFreq, value: 300 MHz}
- {id: CORE_PLL_DFS5.outFreq, value: 600 MHz}
- {id: CORE_PLL_DFS6.outFreq, value: 600 MHz}
- {id: CORE_PLL_PHI0.outFreq, value: 1 GHz}
- {id: CORE_PLL_PHI1.outFreq, value: 500 MHz}
- {id: CRC0_CLK.outFreq, value: 400/3 MHz}
- {id: CTU0_CLK.outFreq, value: 48 MHz}
- {id: CTU1_CLK.outFreq, value: 48 MHz}
- {id: DAPB_CLK.outFreq, value: 200 MHz}
- {id: DDR_CLK.outFreq, value: 48 MHz}
- {id: DMA0_CLK.outFreq, value: 400 MHz}
- {id: DMA1_CLK.outFreq, value: 400 MHz}
- {id: DMAMUX0_CLK.outFreq, value: 400/3 MHz}
- {id: DMAMUX1_CLK.outFreq, value: 400/3 MHz}
- {id: DMAMUX2_CLK.outFreq, value: 400/3 MHz}
- {id: DMAMUX3_CLK.outFreq, value: 400/3 MHz}
- {id: DMA_CRC0_CLK.outFreq, value: 400 MHz}
- {id: DMA_CRC1_CLK.outFreq, value: 400 MHz}
- {id: EIM0_CLK.outFreq, value: 100 MHz}
- {id: EIM1_CLK.outFreq, value: 200/3 MHz}
- {id: EIM2_CLK.outFreq, value: 200/3 MHz}
- {id: EIM3_CLK.outFreq, value: 200/3 MHz}
- {id: EIM_CLK.outFreq, value: 200/3 MHz}
- {id: ERM0_CLK.outFreq, value: 200/3 MHz}
- {id: FIRCOUT.outFreq, value: 48 MHz}
- {id: FLEXCAN0_CLK.outFreq, value: 48 MHz}
- {id: FLEXCAN1_CLK.outFreq, value: 48 MHz}
- {id: FLEXCAN2_CLK.outFreq, value: 48 MHz}
- {id: FLEXCAN3_CLK.outFreq, value: 48 MHz}
- {id: FLEXCAN_CLK.outFreq, value: 48 MHz}
- {id: FLEXRAY_CLK.outFreq, value: 48 MHz}
- {id: FLEXTIMERA_CLK.outFreq, value: 48 MHz}
- {id: FLEXTIMERB_CLK.outFreq, value: 48 MHz}
- {id: FRAY0_CLK.outFreq, value: 48 MHz}
- {id: FTIMER0_CLK.outFreq, value: 48 MHz}
- {id: FTIMER1_CLK.outFreq, value: 48 MHz}
- {id: FXOSCOUT.outFreq, value: 40 MHz}
- {id: GMAC0_TS_CLK.outFreq, value: 200 MHz}
- {id: GMAC0_TX_CLK.outFreq, value: 125 MHz}
- {id: GMAC_TS_CLK.outFreq, value: 200 MHz}
- {id: IIC0_CLK.outFreq, value: 400/3 MHz}
- {id: IIC1_CLK.outFreq, value: 400/3 MHz}
- {id: IIC2_CLK.outFreq, value: 400/3 MHz}
- {id: IIC3_CLK.outFreq, value: 400/3 MHz}
- {id: IIC4_CLK.outFreq, value: 400/3 MHz}
- {id: LBIST0_CLK.outFreq, value: 50 MHz}
- {id: LBIST1_CLK.outFreq, value: 50 MHz}
- {id: LBIST2_CLK.outFreq, value: 50 MHz}
- {id: LBIST3_CLK.outFreq, value: 50 MHz}
- {id: LBIST4_CLK.outFreq, value: 50 MHz}
- {id: LBIST5_CLK.outFreq, value: 50 MHz}
- {id: LBIST6_CLK.outFreq, value: 50 MHz}
- {id: LBIST7_CLK.outFreq, value: 50 MHz}
- {id: LBIST_CLK.outFreq, value: 50 MHz}
- {id: LIN0_CLK.outFreq, value: 125 MHz}
- {id: LIN1_CLK.outFreq, value: 125 MHz}
- {id: LIN2_CLK.outFreq, value: 125 MHz}
- {id: LIN_CLK.outFreq, value: 125 MHz}
- {id: OCOTP0_CLK.outFreq, value: 48 MHz}
- {id: PERIPH_PLL_DFS1.outFreq, value: 800 MHz}
- {id: PERIPH_PLL_DFS2.outFreq, value: 12000/19 MHz}
- {id: PERIPH_PLL_DFS3.outFreq, value: 800 MHz}
- {id: PERIPH_PLL_DFS4.outFreq, value: 500 MHz}
- {id: PERIPH_PLL_DFS5.outFreq, value: 500 MHz}
- {id: PERIPH_PLL_DFS6.outFreq, value: 500 MHz}
- {id: PERIPH_PLL_PHI0.outFreq, value: 100 MHz}
- {id: PERIPH_PLL_PHI1.outFreq, value: 80 MHz}
- {id: PERIPH_PLL_PHI2.outFreq, value: 80 MHz}
- {id: PERIPH_PLL_PHI3.outFreq, value: 125 MHz}
- {id: PERIPH_PLL_PHI4.outFreq, value: 200 MHz}
- {id: PERIPH_PLL_PHI5.outFreq, value: 125 MHz}
- {id: PERIPH_PLL_PHI6.outFreq, value: 100 MHz}
- {id: PERIPH_PLL_PHI7.outFreq, value: 100 MHz}
- {id: PER_CLK.outFreq, value: 48 MHz}
- {id: PFEMAC0_RX_CLK.outFreq, value: 48 MHz}
- {id: PFEMAC0_TX_CLK.outFreq, value: 48 MHz}
- {id: PFEMAC1_RX_CLK.outFreq, value: 48 MHz}
- {id: PFEMAC1_TX_CLK.outFreq, value: 48 MHz}
- {id: PFEMAC2_RX_CLK.outFreq, value: 48 MHz}
- {id: PFEMAC2_TX_CLK.outFreq, value: 48 MHz}
- {id: PFE_PE_CLK.outFreq, value: 48 MHz}
- {id: PIT0_CLK.outFreq, value: 400/3 MHz}
- {id: PIT1_CLK.outFreq, value: 400/3 MHz}
- {id: QSPI0_CLK.outFreq, value: 160 MHz, locked: true, accuracy: '0.001'}
- {id: QSPI_CLK.outFreq, value: 160 MHz}
- {id: RTC0_CLK.outFreq, value: 200/3 MHz}
- {id: SERDES_0_LANE_0_CDR.outFreq, value: 100 MHz}
- {id: SERDES_0_LANE_0_TX.outFreq, value: 100 MHz}
- {id: SERDES_0_LANE_1_CDR.outFreq, value: 100 MHz}
- {id: SERDES_0_LANE_1_TX.outFreq, value: 100 MHz}
- {id: SERDES_1_LANE_0_CDR.outFreq, value: 125 MHz}
- {id: SERDES_1_LANE_0_TX.outFreq, value: 125 MHz}
- {id: SERDES_1_LANE_1_CDR.outFreq, value: 125 MHz}
- {id: SERDES_1_LANE_1_TX.outFreq, value: 125 MHz}
- {id: SIRCOUT.outFreq, value: 32 kHz}
- {id: SIUL0_CLK.outFreq, value: 48 MHz}
- {id: SIUL1_CLK.outFreq, value: 48 MHz}
- {id: SPI0_CLK.outFreq, value: 48 MHz}
- {id: SPI1_CLK.outFreq, value: 48 MHz}
- {id: SPI2_CLK.outFreq, value: 48 MHz}
- {id: SPI3_CLK.outFreq, value: 48 MHz}
- {id: SPI4_CLK.outFreq, value: 48 MHz}
- {id: SPI5_CLK.outFreq, value: 48 MHz}
- {id: SPI_CLK.outFreq, value: 48 MHz}
- {id: STM0_CLK.outFreq, value: 400/3 MHz}
- {id: STM1_CLK.outFreq, value: 400/3 MHz}
- {id: STM2_CLK.outFreq, value: 400/3 MHz}
- {id: STM3_CLK.outFreq, value: 400/3 MHz}
- {id: STM4_CLK.outFreq, value: 400/3 MHz}
- {id: STM5_CLK.outFreq, value: 400/3 MHz}
- {id: STM6_CLK.outFreq, value: 400/3 MHz}
- {id: STM7_CLK.outFreq, value: 400/3 MHz}
- {id: SWT0_CLK.outFreq, value: 48 MHz}
- {id: SWT1_CLK.outFreq, value: 48 MHz}
- {id: SWT2_CLK.outFreq, value: 48 MHz}
- {id: SWT3_CLK.outFreq, value: 48 MHz}
- {id: SWT4_CLK.outFreq, value: 48 MHz}
- {id: SWT5_CLK.outFreq, value: 48 MHz}
- {id: SWT6_CLK.outFreq, value: 48 MHz}
- {id: USDHC0_CLK.outFreq, value: 48 MHz}
- {id: USDHC_CLK.outFreq, value: 48 MHz}
- {id: WKPU0_CLK.outFreq, value: 200/3 MHz}
- {id: XBAR_2X_CLK.outFreq, value: 800 MHz}
- {id: XBAR_CLK.outFreq, value: 400 MHz}
- {id: XBAR_DIV2_CLK.outFreq, value: 200 MHz}
- {id: XBAR_DIV3_CLK.outFreq, value: 400/3 MHz}
- {id: XBAR_DIV4_CLK.outFreq, value: 100 MHz}
- {id: XBAR_DIV6_CLK.outFreq, value: 200/3 MHz}
settings:
- {id: ACCELPLL_PHI0.scale, value: '4', locked: true}
- {id: ACCELPLL_PHI1.scale, value: '4', locked: true}
- {id: ACCELPLL_PLLCLKMUX.sel, value: FXOSC_CLK.FXOSCOUT}
- {id: ACCELPLL_PREDIV.scale, value: '1', locked: true}
- {id: ACCEL_MFD.scale, value: '60', locked: true}
- {id: ACCEL_PLLODIV_0_DE, value: Enabled}
- {id: ACCEL_PLLODIV_1_DE, value: Enabled}
- {id: ACCEL_PLL_PD, value: Power_up}
- {id: COREPLL_DFS1.scale, value: '2.5', locked: true}
- {id: COREPLL_DFS2.scale, value: '2.5', locked: true}
- {id: COREPLL_DFS3.scale, value: '4', locked: true}
- {id: COREPLL_DFS4.scale, value: 20/3, locked: true}
- {id: COREPLL_DFS5.scale, value: 10/3, locked: true}
- {id: COREPLL_DFS6.scale, value: 10/3, locked: true}
- {id: COREPLL_PHI0.scale, value: '2', locked: true}
- {id: COREPLL_PHI1.scale, value: '4', locked: true}
- {id: COREPLL_PLLCLKMUX.sel, value: FXOSC_CLK.FXOSCOUT}
- {id: COREPLL_PREDIV.scale, value: '1', locked: true}
- {id: CORE_DFS1_PD, value: Power_up}
- {id: CORE_DFS2_PD, value: Power_up}
- {id: CORE_DFS3_PD, value: Power_up}
- {id: CORE_DFS4_PD, value: Power_up}
- {id: CORE_DFS5_PD, value: Power_up}
- {id: CORE_DFS6_PD, value: Power_up}
- {id: CORE_MFD.scale, value: '50', locked: true}
- {id: CORE_PLLODIV_0_DE, value: Enabled}
- {id: CORE_PLLODIV_1_DE, value: Enabled}
- {id: CORE_PLL_PD, value: Power_up}
- {id: DDRPLL_PHI0.scale, value: '4', locked: true}
- {id: DDRPLL_PLLCLKMUX.sel, value: FXOSC_CLK.FXOSCOUT}
- {id: DDR_MFD.scale, value: '40'}
- {id: DDR_PLLODIV_0_DE, value: Enabled}
- {id: DIV_0_DE, value: Enabled}
- {id: DIV_3_DE, value: Enabled}
- {id: FXOSC_PM, value: Crystal_mode}
- {id: MC_CGM_0_MUX_0.sel, value: COREPLL_DFS1}
- {id: MC_CGM_0_MUX_15_DIV0.scale, value: '1', locked: true}
- {id: MC_CGM_1_MUX_0.sel, value: COREPLL_PHI0}
- {id: MC_CGM_2_MUX_0_DIV0.scale, value: '1', locked: true}
- {id: MODULE_CLOCKS.MC_CGM_0_AUX0_DIV0.scale, value: '16', locked: true}
- {id: MODULE_CLOCKS.MC_CGM_0_AUX0_DIV1.scale, value: '4', locked: true}
- {id: MODULE_CLOCKS.MC_CGM_0_AUX0_MUX.sel, value: COREPLL_DFS1}
- {id: MODULE_CLOCKS.MC_CGM_0_AUX10_MUX.sel, value: PERIPHPLL_PHI5}
- {id: MODULE_CLOCKS.MC_CGM_0_AUX11_MUX.sel, value: external_clocks.GMACEXTRXREFOUT}
- {id: MODULE_CLOCKS.MC_CGM_0_AUX12_DIV0.scale, value: '5'}
- {id: MODULE_CLOCKS.MC_CGM_0_AUX12_MUX.sel, value: PERIPHPLL_DFS1}
- {id: MODULE_CLOCKS.MC_CGM_0_AUX1_DIV0.scale, value: '13', locked: true}
- {id: MODULE_CLOCKS.MC_CGM_0_AUX8_MUX.sel, value: PERIPHPLL_PHI3}
- {id: MODULE_CLOCKS.MC_CGM_0_AUX9_MUX.sel, value: PERIPHPLL_PHI4}
- {id: PERIPHPLL_DFS1.scale, value: '2.5', locked: true}
- {id: PERIPHPLL_DFS2.scale, value: 19/6, locked: true}
- {id: PERIPHPLL_DFS3.scale, value: '2.5', locked: true}
- {id: PERIPHPLL_DFS4.scale, value: '4', locked: true}
- {id: PERIPHPLL_DFS5.scale, value: '4', locked: true}
- {id: PERIPHPLL_DFS6.scale, value: '4', locked: true}
- {id: PERIPHPLL_MFD.scale, value: '50', locked: true}
- {id: PERIPHPLL_PHI0.scale, value: '20', locked: true}
- {id: PERIPHPLL_PHI1.scale, value: '25', locked: true}
- {id: PERIPHPLL_PHI2.scale, value: '25', locked: true}
- {id: PERIPHPLL_PHI3.scale, value: '16', locked: true}
- {id: PERIPHPLL_PHI4.scale, value: '10', locked: true}
- {id: PERIPHPLL_PHI5.scale, value: '16', locked: true}
- {id: PERIPHPLL_PHI6.scale, value: '20', locked: true}
- {id: PERIPHPLL_PHI7.scale, value: '20', locked: true}
- {id: PERIPHPLL_PLLCLKMUX.sel, value: FXOSC_CLK.FXOSCOUT}
- {id: PERIPH_DFS1_PD, value: Power_up}
- {id: PERIPH_DFS2_PD, value: Power_up}
- {id: PERIPH_DFS3_PD, value: Power_up}
- {id: PERIPH_DFS4_PD, value: Power_up}
- {id: PERIPH_DFS5_PD, value: Power_up}
- {id: PERIPH_DFS6_PD, value: Power_up}
- {id: PERIPH_PLL_PD, value: Power_up}
- {id: PLLODIV0_DE, value: Enabled}
- {id: PLLODIV1_DE, value: Enabled}
- {id: PLLODIV2_DE, value: Enabled}
- {id: PLLODIV3_DE, value: Enabled}
- {id: PLLODIV4_DE, value: Enabled}
- {id: PLLODIV5_DE, value: Enabled}
- {id: PLLODIV6_DE, value: Enabled}
- {id: PLLODIV7_DE, value: Enabled}
- {id: PREDIV.scale, value: '1', locked: true}
sources:
- {id: FXOSC_CLK.FXOSC_CLK.outFreq, value: 40 MHz, enabled: true}
- {id: external_clocks.ftm_0_ext_ref.outFreq, value: 20 MHz}
- {id: external_clocks.ftm_1_ext_ref.outFreq, value: 20 MHz}
- {id: external_clocks.gmac_ext_ref.outFreq, value: 40 MHz}
- {id: external_clocks.gmac_ext_rx_ref.outFreq, value: 125 MHz}
- {id: external_clocks.gmac_ext_ts_ref.outFreq, value: 200 MHz}
- {id: external_clocks.gmac_ext_tx_ref.outFreq, value: 125 MHz}
- {id: external_clocks.pfemac0_ext_ref.outFreq, value: 40 MHz}
- {id: external_clocks.pfemac0_ext_rx.outFreq, value: 125 MHz}
- {id: external_clocks.pfemac0_ext_tx.outFreq, value: 125 MHz}
- {id: external_clocks.pfemac1_ext_ref.outFreq, value: 40 MHz}
- {id: external_clocks.pfemac1_ext_rx.outFreq, value: 125 MHz}
- {id: external_clocks.pfemac1_ext_tx.outFreq, value: 125 MHz}
- {id: external_clocks.pfemac2_ext_ref.outFreq, value: 40 MHz}
- {id: external_clocks.pfemac2_ext_rx.outFreq, value: 125 MHz}
- {id: external_clocks.pfemac2_ext_tx.outFreq, value: 125 MHz}
 * BE CAREFUL MODIFYING THIS COMMENT - IT IS YAML SETTINGS FOR TOOLS **********/

/* *************************************************************************
 * Configuration structure for Clock Configuration 0
 * ************************************************************************* */
 /*! @brief User Configuration structure clock_Cfg_0 */
const Clock_Ip_ClockConfigType Mcu_aClockConfigPB[1] = {
    {
        0U,                          /* clkConfigId */

        0U,                       /* ircoscsCount */
        1U,                       /* xoscsCount */
        4U,                       /* pllsCount */
        28U,                       /* selectorsCount */
        33U,                       /* dividersCount */
        7U,                       /* dividerTriggersCount */
        12U,                       /* fracDivsCount */
        23U,                       /* extClksCount */
        0U,                       /* gatesCount */
        3U,                       /* pcfsCount */
        0U,                       /* cmusCount */


        /* IRCOSC initialization. */
        {
            #if CLOCK_IRCOSCS_NO > 0U
            {
                RESERVED_CLK,           /* name */
                0U,                     /* enable */
            },
            #endif

            #if CLOCK_IRCOSCS_NO > 0U
            {
                RESERVED_CLK,           /* name */
                0U,                     /* enable */
            },
            #endif

        },

        /* XOSC initialization. */
        {
            #if CLOCK_XOSCS_NO > 0U
            {
                FXOSC_CLK,              /* Clock name associated to xosc */
                40000000U,              /* External oscillator frequency. */ 
                1U,                     /* Enable xosc. */
                157U,                   /* Startup stabilization time. */
                0U,                     /* bypassOption: Xosc use crystal */ 
                1U,                     /* Comparator is enabled */ 
                12U,                    /* TransConductance */
            },
            #endif
        },


        /* PLL initialization. */
        {
            #if CLOCK_PLLS_NO > 0U
            {
                COREPLL_CLK,                /* name */
                1U,                     /* enable */
                FXOSC_CLK,                     /* inputReference */
                0U,                     /* Bypass */
                1,                      /* predivider */
                0U,                     /* numeratorFracLoopDiv */
                50U,                   /* mulFactorDiv */
                0U,                     /* modulation */
                1U,                     /* Modulaton type: Spread spectrum modulation bypassed */ 
                0U,                     /* modulationPeriod */
                0U,                     /* incrementStep */
                0U,                     /* sigmaDelta */
                0U,                     /* ditherControl */
                0U,                     /* ditherControlValue */
            },
            #endif

            #if CLOCK_PLLS_NO > 1U
            {
                PERIPHPLL_CLK,                /* name */
                1U,                     /* enable */
                FXOSC_CLK,                     /* inputReference */
                0U,                     /* Bypass */
                1,                      /* predivider */
                0U,                     /* numeratorFracLoopDiv */
                50U,                   /* mulFactorDiv */
                0U,                     /* modulation */
                0U,                     /* Modulaton type */
                0U,                     /* modulationPeriod */
                0U,                     /* incrementStep */
                0U,                     /* sigmaDelta */
                0U,                     /* ditherControl */
                0U,                     /* ditherControlValue */
            },
            #endif

            #if CLOCK_PLLS_NO > 2U
            {
                DDRPLL_CLK,                /* name */
                0U,                     /* enable */
                FXOSC_CLK,                     /* inputReference */
                0U,                     /* Bypass */
                1,                      /* predivider */
                0U,                     /* numeratorFracLoopDiv */
                40U,                   /* mulFactorDiv */
                0U,                     /* modulation */
                1U,                     /* Modulaton type: Spread spectrum modulation bypassed */ 
                0U,                     /* modulationPeriod */
                0U,                     /* incrementStep */
                0U,                     /* sigmaDelta */
                0U,                     /* ditherControl */
                0U,                     /* ditherControlValue */
            },
            #endif

            #if CLOCK_PLLS_NO > 3U
            {
                ACCELPLL_CLK,                /* name */
                1U,                     /* enable */
                FXOSC_CLK,                     /* inputReference */
                0U,                     /* Bypass */
                1,                      /* predivider */
                0U,                     /* numeratorFracLoopDiv */
                60U,                   /* mulFactorDiv */
                0U,                     /* modulation */
                1U,                     /* Modulaton type: Spread spectrum modulation bypassed */ 
                0U,                     /* modulationPeriod */
                0U,                     /* incrementStep */
                0U,                     /* sigmaDelta */
                0U,                     /* ditherControl */
                0U,                     /* ditherControlValue */
            },
            #endif

        },



        /* SELECTOR initialization. */
        {

            #if CLOCK_SELECTORS_NO > 0U
            {
                XBAR_2X_CLK,                    /* name */
                CORE_PLL_DFS1_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 1U
            {
                CLKOUT0_CLK,                    /* name */
                FXOSC_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 2U
            {
                CLKOUT1_CLK,                    /* name */
                FXOSC_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 3U
            {
                PER_CLK,                    /* name */
                FIRC_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 4U
            {
                FLEXTIMERA_CLK,                    /* name */
                FIRC_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 5U
            {
                FLEXTIMERB_CLK,                    /* name */
                FIRC_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 6U
            {
                FLEXRAY_CLK,                    /* name */
                FIRC_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 7U
            {
                FLEXCAN_CLK,                    /* name */
                FIRC_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 8U
            {
                LIN_CLK,                    /* name */
                PERIPH_PLL_PHI3_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 9U
            {
                GMAC_TS_CLK,                    /* name */
                PERIPH_PLL_PHI4_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 10U
            {
                GMAC0_TX_CLK,                    /* name */
                PERIPH_PLL_PHI5_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 11U
            {
                GMAC0_RX_CLK,                    /* name */
                GMAC_0_EXT_RX_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 12U
            {
                QSPI_CLK,                    /* name */
                PERIPH_PLL_DFS1_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 13U
            {
                USDHC_CLK,                    /* name */
                FIRC_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 14U
            {
                GMAC_REF_DIV_CLK,                    /* name */
                FIRC_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 15U
            {
                SPI_CLK,                    /* name */
                FIRC_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 16U
            {
                A53_CORE_CLK,                    /* name */
                CORE_PLL_PHI0_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 17U
            {
                PFE_PE_CLK,                    /* name */
                FIRC_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 18U
            {
                PFEMAC0_TX_CLK,                    /* name */
                FIRC_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 19U
            {
                PFEMAC1_TX_CLK,                    /* name */
                FIRC_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 20U
            {
                PFEMAC2_TX_CLK,                    /* name */
                FIRC_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 21U
            {
                PFEMAC0_RX_CLK,                    /* name */
                FIRC_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 22U
            {
                PFEMAC1_RX_CLK,                    /* name */
                FIRC_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 23U
            {
                PFEMAC2_RX_CLK,                    /* name */
                FIRC_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 24U
            {
                PFEMAC0_REF_DIV_CLK,                    /* name */
                FIRC_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 25U
            {
                PFEMAC1_REF_DIV_CLK,                    /* name */
                FIRC_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 26U
            {
                PFEMAC2_REF_DIV_CLK,                    /* name */
                FIRC_CLK,                    /* value */
            },
            #endif

            #if CLOCK_SELECTORS_NO > 27U
            {
                DDR_CLK,                    /* name */
                FIRC_CLK,                    /* value */
            },
            #endif
        },


        /* DIVIDER initialization. */
        {

            #if CLOCK_DIVIDERS_NO > 0U
            {
                CORE_PLL_PHI0_CLK,                    /* name */
                2U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 1U
            {
                CORE_PLL_PHI1_CLK,                    /* name */
                4U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 2U
            {
                PERIPH_PLL_PHI0_CLK,                    /* name */
                20U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 3U
            {
                PERIPH_PLL_PHI1_CLK,                    /* name */
                25U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 4U
            {
                PERIPH_PLL_PHI2_CLK,                    /* name */
                25U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 5U
            {
                PERIPH_PLL_PHI3_CLK,                    /* name */
                16U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 6U
            {
                PERIPH_PLL_PHI4_CLK,                    /* name */
                10U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 7U
            {
                PERIPH_PLL_PHI5_CLK,                    /* name */
                16U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 8U
            {
                PERIPH_PLL_PHI6_CLK,                    /* name */
                20U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 9U
            {
                PERIPH_PLL_PHI7_CLK,                    /* name */
                20U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 10U
            {
                DDR_PLL_PHI0_CLK,                    /* name */
                4U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 11U
            {
                ACCEL_PLL_PHI0_CLK,                    /* name */
                4U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 12U
            {
                ACCEL_PLL_PHI1_CLK,                    /* name */
                4U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 13U
            {
                LBIST_CLK,                    /* name */
                16U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 14U
            {
                DAPB_CLK,                    /* name */
                4U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 15U
            {
                GMAC_REF_DIV_CLK,                    /* name */
                0U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 16U
            {
                CLKOUT0_CLK,                    /* name */
                13U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 17U
            {
                CLKOUT1_CLK,                    /* name */
                1U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 18U
            {
                PER_CLK,                    /* name */
                1U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 19U
            {
                FLEXTIMERA_CLK,                    /* name */
                1U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 20U
            {
                FLEXTIMERB_CLK,                    /* name */
                1U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 21U
            {
                FLEXRAY_CLK,                    /* name */
                1U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 22U
            {
                GMAC_TS_CLK,                    /* name */
                1U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 23U
            {
                GMAC0_TX_CLK,                    /* name */
                1U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 24U
            {
                QSPI_CLK,                    /* name */
                5U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 25U
            {
                USDHC_CLK,                    /* name */
                1U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 26U
            {
                PFE_PE_CLK,                    /* name */
                1U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 27U
            {
                PFEMAC0_TX_CLK,                    /* name */
                1U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 28U
            {
                PFEMAC1_TX_CLK,                    /* name */
                1U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 29U
            {
                PFEMAC2_TX_CLK,                    /* name */
                1U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 30U
            {
                PFEMAC0_REF_DIV_CLK,                    /* name */
                0U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 31U
            {
                PFEMAC1_REF_DIV_CLK,                    /* name */
                0U,                              /* value */
                {
                    0U,
                }
            },
            #endif

            #if CLOCK_DIVIDERS_NO > 32U
            {
                PFEMAC2_REF_DIV_CLK,                    /* name */
                0U,                              /* value */
                {
                    0U,
                }
            },
            #endif
        },


        /* TRIGGER DIVIDER Initialization. */
        {
            #if CLOCK_DIVIDER_TRIGGERS_NO > 0U
            {
                PFE_PE_CLK,          /* divider name */
                IMMEDIATE_DIVIDER_UPDATE,          /* trigger value */
                PFE_PE_CLK,          /* input source name */
            },
            #endif
            #if CLOCK_DIVIDER_TRIGGERS_NO > 1U
            {
                PFEMAC0_TX_CLK,          /* divider name */
                IMMEDIATE_DIVIDER_UPDATE,          /* trigger value */
                PFEMAC0_TX_CLK,          /* input source name */
            },
            #endif
            #if CLOCK_DIVIDER_TRIGGERS_NO > 2U
            {
                PFEMAC1_TX_CLK,          /* divider name */
                IMMEDIATE_DIVIDER_UPDATE,          /* trigger value */
                PFEMAC1_TX_CLK,          /* input source name */
            },
            #endif
            #if CLOCK_DIVIDER_TRIGGERS_NO > 3U
            {
                PFEMAC2_TX_CLK,          /* divider name */
                IMMEDIATE_DIVIDER_UPDATE,          /* trigger value */
                PFEMAC2_TX_CLK,          /* input source name */
            },
            #endif
            #if CLOCK_DIVIDER_TRIGGERS_NO > 4U
            {
                PFEMAC0_REF_DIV_CLK,          /* divider name */
                IMMEDIATE_DIVIDER_UPDATE,          /* trigger value */
                PFEMAC0_REF_DIV_CLK,          /* input source name */
            },
            #endif
            #if CLOCK_DIVIDER_TRIGGERS_NO > 5U
            {
                PFEMAC1_REF_DIV_CLK,          /* divider name */
                IMMEDIATE_DIVIDER_UPDATE,          /* trigger value */
                PFEMAC1_REF_DIV_CLK,          /* input source name */
            },
            #endif
            #if CLOCK_DIVIDER_TRIGGERS_NO > 6U
            {
                PFEMAC2_REF_DIV_CLK,          /* divider name */
                IMMEDIATE_DIVIDER_UPDATE,          /* trigger value */
                PFEMAC2_REF_DIV_CLK,          /* input source name */
            },
            #endif
        },



        /* FRACTIONAL DIVIDER initialization. */
        {

            #if CLOCK_FRACTIONAL_DIVIDERS_NO > 0U
            {
                CORE_PLL_DFS1_CLK,                    /* name */
                {
                    1U,          /* integer part */
                    9U,          /* fractional part */
                },
            },
            #endif

            #if CLOCK_FRACTIONAL_DIVIDERS_NO > 1U
            {
                CORE_PLL_DFS2_CLK,                    /* name */
                {
                    1U,          /* integer part */
                    9U,          /* fractional part */
                },
            },
            #endif

            #if CLOCK_FRACTIONAL_DIVIDERS_NO > 2U
            {
                CORE_PLL_DFS3_CLK,                    /* name */
                {
                    2U,          /* integer part */
                    0U,          /* fractional part */
                },
            },
            #endif

            #if CLOCK_FRACTIONAL_DIVIDERS_NO > 3U
            {
                CORE_PLL_DFS4_CLK,                    /* name */
                {
                    3U,          /* integer part */
                    12U,          /* fractional part */
                },
            },
            #endif

            #if CLOCK_FRACTIONAL_DIVIDERS_NO > 4U
            {
                CORE_PLL_DFS5_CLK,                    /* name */
                {
                    1U,          /* integer part */
                    24U,          /* fractional part */
                },
            },
            #endif

            #if CLOCK_FRACTIONAL_DIVIDERS_NO > 5U
            {
                CORE_PLL_DFS6_CLK,                    /* name */
                {
                    1U,          /* integer part */
                    24U,          /* fractional part */
                },
            },
            #endif

            #if CLOCK_FRACTIONAL_DIVIDERS_NO > 6U
            {
                PERIPH_PLL_DFS1_CLK,                    /* name */
                {
                    1U,          /* integer part */
                    9U,          /* fractional part */
                },
            },
            #endif

            #if CLOCK_FRACTIONAL_DIVIDERS_NO > 7U
            {
                PERIPH_PLL_DFS2_CLK,                    /* name */
                {
                    1U,          /* integer part */
                    21U,          /* fractional part */
                },
            },
            #endif

            #if CLOCK_FRACTIONAL_DIVIDERS_NO > 8U
            {
                PERIPH_PLL_DFS3_CLK,                    /* name */
                {
                    1U,          /* integer part */
                    9U,          /* fractional part */
                },
            },
            #endif

            #if CLOCK_FRACTIONAL_DIVIDERS_NO > 9U
            {
                PERIPH_PLL_DFS4_CLK,                    /* name */
                {
                    2U,          /* integer part */
                    0U,          /* fractional part */
                },
            },
            #endif

            #if CLOCK_FRACTIONAL_DIVIDERS_NO > 10U
            {
                PERIPH_PLL_DFS5_CLK,                    /* name */
                {
                    2U,          /* integer part */
                    0U,          /* fractional part */
                },
            },
            #endif

            #if CLOCK_FRACTIONAL_DIVIDERS_NO > 11U
            {
                PERIPH_PLL_DFS6_CLK,                    /* name */
                {
                    2U,          /* integer part */
                    0U,          /* fractional part */
                },
            },
            #endif
        },



        /* EXTERNAL CLOCKS initialization. */
        {

            #if CLOCK_EXT_CLKS_NO > 0U
            {
                FTM_0_EXT_REF_CLK,                    /* name */
                0U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 1U
            {
                FTM_1_EXT_REF_CLK,                    /* name */
                0U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 2U
            {
                GMAC_0_EXT_REF_CLK,                    /* name */
                0U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 3U
            {
                GMAC_0_EXT_RX_CLK,                    /* name */
                0U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 4U
            {
                GMAC_0_EXT_TX_CLK,                    /* name */
                0U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 5U
            {
                GMAC_EXT_TS_CLK,                    /* name */
                0U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 6U
            {
                PFE_MAC_0_EXT_REF_CLK,                    /* name */
                0U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 7U
            {
                PFE_MAC_0_EXT_RX_CLK,                    /* name */
                0U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 8U
            {
                PFE_MAC_0_EXT_TX_CLK,                    /* name */
                0U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 9U
            {
                PFE_MAC_1_EXT_REF_CLK,                    /* name */
                0U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 10U
            {
                PFE_MAC_1_EXT_RX_CLK,                    /* name */
                0U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 11U
            {
                PFE_MAC_1_EXT_TX_CLK,                    /* name */
                0U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 12U
            {
                PFE_MAC_2_EXT_REF_CLK,                    /* name */
                0U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 13U
            {
                PFE_MAC_2_EXT_RX_CLK,                    /* name */
                0U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 14U
            {
                PFE_MAC_2_EXT_TX_CLK,                    /* name */
                0U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 15U
            {
                SERDES_0_LANE_0_TX,                    /* name */
                100000000U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 16U
            {
                SERDES_0_LANE_0_CDR,                    /* name */
                100000000U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 17U
            {
                SERDES_0_LANE_1_TX,                    /* name */
                100000000U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 18U
            {
                SERDES_0_LANE_1_CDR,                    /* name */
                100000000U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 19U
            {
                SERDES_1_LANE_0_TX,                    /* name */
                125000000U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 20U
            {
                SERDES_1_LANE_0_CDR,                    /* name */
                125000000U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 21U
            {
                SERDES_1_LANE_1_TX,                    /* name */
                125000000U,                              /* value */
            },
            #endif

            #if CLOCK_EXT_CLKS_NO > 22U
            {
                SERDES_1_LANE_1_CDR,                    /* name */
                125000000U,                              /* value */
            },
            #endif
        },



        /* CLOCK GATES initialization. */
        {

            #if CLOCK_GATES_NO > 0U
            {
                DDR_CLK,                    /* name */
                0U,                           /* enable */
            },
            #endif

            #if CLOCK_GATES_NO > 1U
            {
                GMAC0_TS_CLK,                    /* name */
                0U,                           /* enable */
            },
            #endif

            #if CLOCK_GATES_NO > 2U
            {
                PFEMAC0_TX_CLK,                    /* name */
                0U,                           /* enable */
            },
            #endif

            #if CLOCK_GATES_NO > 3U
            {
                PFEMAC0_RX_CLK,                    /* name */
                0U,                           /* enable */
            },
            #endif

            #if CLOCK_GATES_NO > 4U
            {
                PFEMAC1_TX_CLK,                    /* name */
                0U,                           /* enable */
            },
            #endif

            #if CLOCK_GATES_NO > 5U
            {
                PFEMAC1_RX_CLK,                    /* name */
                0U,                           /* enable */
            },
            #endif

            #if CLOCK_GATES_NO > 6U
            {
                PFEMAC2_TX_CLK,                    /* name */
                0U,                           /* enable */
            },
            #endif

            #if CLOCK_GATES_NO > 7U
            {
                PFEMAC2_RX_CLK,                    /* name */
                0U,                           /* enable */
            },
            #endif

            #if CLOCK_GATES_NO > 8U
            {
                USDHC0_CLK,                    /* name */
                0U,                           /* enable */
            },
            #endif
        },
        /* PCFS initialization. */ 
        {
            {
                RESERVED_CLK,
                0U,
                0U,
                RESERVED_CLK,
            },
        },
        /* Clock monitor */ 
        {
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
            {
                RESERVED_CLK,
                0,
                0,
            },
        },
        /* Specific peripheral initialization. */
        {
            0U,
            {
                {
                    RESERVED_VALUE,
                    0U,
                }
            }
        }
    },
};
