/**
*   @file       Clock_Ip_Cfg_Defines.h
*   @implements Clock_Ip_Cfg_Defines.h_Artifact
*   @version    0.9.0
*
*   @brief   AUTOSAR Mcu - Post-Build(PB) configuration file code template.
*   @details Code template for Post-Build(PB) configuration file generation.
*
*   @addtogroup CLOCK_DRIVER_CONFIGURATION Clock Driver
*   @{
*/


#ifndef CLOCK_IP_CFG_DEFINES_H
#define CLOCK_IP_CFG_DEFINES_H


#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/


/*==================================================================================================
                                           DEFINES AND MACROS
==================================================================================================*/

/**
* @brief            Max number of internal oscillators
*/
#define FEATURE_CLOCK_IRCOSCS_COUNT       (2U)

/**
* @brief            Max number of external oscillators
*/
#define FEATURE_CLOCK_XOSCS_COUNT       (1U)

/**
* @brief            Max number of pll devices
*/
#define FEATURE_CLOCK_PLLS_COUNT       (4U)

/**
* @brief            Max number of selectors
*/
#define FEATURE_CLOCK_SELECTORS_COUNT       (28U)

/**
* @brief            Max number of dividers
*/
#define FEATURE_CLOCK_DIVIDERS_COUNT       (33U)

/**
* @brief            Max number of divider triggers
*/
#define FEATURE_CLOCK_DIVIDER_TRIGGERS_COUNT       (7U)

/**
* @brief            Max number of fractional dividers
*/
#define FEATURE_CLOCK_FRACTIONAL_DIVIDERS_COUNT       (12U)

/**
* @brief            Max number of external clocks
*/
#define FEATURE_CLOCK_EXT_CLKS_COUNT       (23U)

/**
* @brief            Max number of pcfs
*/
#define FEATURE_CLOCK_PCFS_COUNT       (3U)

/**
* @brief            Max number of clock gates
*/
#define FEATURE_CLOCK_GATES_COUNT       (9U)

/**
* @brief            Max number of clock monitoring units
*/
#define FEATURE_CLOCK_CMUS_COUNT       (27U)

/**
* @brief             Max number of consumer clocks
*/
#define FEATURE_CLOCK_CONSUMER_COUNT     (100U)

/**
* @brief            Max number of specific peripheral (eMIOS) units
*/
#define FEATURE_CLOCK_SPECIFIC_PERIPH_COUNT       (0U)

/**
* @brief            Supported power mode.
*/
#define FEATURE_CLOCK_IP_HAS_RUN_MODE                0U

/**
* @brief            Supported clocks.
*/
#define FEATURE_CLOCK_IP_HAS_FIRC_CLK         0U
#define FEATURE_CLOCK_IP_HAS_FXOSC_CLK         1U
#define FEATURE_CLOCK_IP_HAS_SIRC_CLK         2U
#define FEATURE_CLOCK_IP_HAS_COREPLL_CLK         3U
#define FEATURE_CLOCK_IP_HAS_PERIPHPLL_CLK         4U
#define FEATURE_CLOCK_IP_HAS_DDRPLL_CLK         5U
#define FEATURE_CLOCK_IP_HAS_ACCELPLL_CLK         6U
#define FEATURE_CLOCK_IP_HAS_CORE_PLL_PHI0_CLK         7U
#define FEATURE_CLOCK_IP_HAS_CORE_PLL_PHI1_CLK         8U
#define FEATURE_CLOCK_IP_HAS_CORE_PLL_DFS1_CLK         9U
#define FEATURE_CLOCK_IP_HAS_CORE_PLL_DFS2_CLK         10U
#define FEATURE_CLOCK_IP_HAS_CORE_PLL_DFS3_CLK         11U
#define FEATURE_CLOCK_IP_HAS_CORE_PLL_DFS4_CLK         12U
#define FEATURE_CLOCK_IP_HAS_CORE_PLL_DFS5_CLK         13U
#define FEATURE_CLOCK_IP_HAS_CORE_PLL_DFS6_CLK         14U
#define FEATURE_CLOCK_IP_HAS_PERIPH_PLL_PHI0_CLK         15U
#define FEATURE_CLOCK_IP_HAS_PERIPH_PLL_PHI1_CLK         16U
#define FEATURE_CLOCK_IP_HAS_PERIPH_PLL_PHI2_CLK         17U
#define FEATURE_CLOCK_IP_HAS_PERIPH_PLL_PHI3_CLK         18U
#define FEATURE_CLOCK_IP_HAS_PERIPH_PLL_PHI4_CLK         19U
#define FEATURE_CLOCK_IP_HAS_PERIPH_PLL_PHI5_CLK         20U
#define FEATURE_CLOCK_IP_HAS_PERIPH_PLL_PHI6_CLK         21U
#define FEATURE_CLOCK_IP_HAS_PERIPH_PLL_PHI7_CLK         22U
#define FEATURE_CLOCK_IP_HAS_PERIPH_PLL_DFS1_CLK         23U
#define FEATURE_CLOCK_IP_HAS_PERIPH_PLL_DFS2_CLK         24U
#define FEATURE_CLOCK_IP_HAS_PERIPH_PLL_DFS3_CLK         25U
#define FEATURE_CLOCK_IP_HAS_PERIPH_PLL_DFS4_CLK         26U
#define FEATURE_CLOCK_IP_HAS_PERIPH_PLL_DFS5_CLK         27U
#define FEATURE_CLOCK_IP_HAS_PERIPH_PLL_DFS6_CLK         28U
#define FEATURE_CLOCK_IP_HAS_DDR_PLL_PHI0_CLK         29U
#define FEATURE_CLOCK_IP_HAS_ACCEL_PLL_PHI0_CLK         30U
#define FEATURE_CLOCK_IP_HAS_ACCEL_PLL_PHI1_CLK         31U
#define FEATURE_CLOCK_IP_HAS_FTM_0_EXT_REF_CLK         32U
#define FEATURE_CLOCK_IP_HAS_FTM_1_EXT_REF_CLK         33U
#define FEATURE_CLOCK_IP_HAS_GMAC_0_EXT_REF_CLK         34U
#define FEATURE_CLOCK_IP_HAS_GMAC_0_EXT_RX_CLK         35U
#define FEATURE_CLOCK_IP_HAS_GMAC_0_EXT_TX_CLK         36U
#define FEATURE_CLOCK_IP_HAS_GMAC_EXT_TS_CLK         37U
#define FEATURE_CLOCK_IP_HAS_PFE_MAC_0_EXT_REF_CLK         38U
#define FEATURE_CLOCK_IP_HAS_PFE_MAC_0_EXT_RX_CLK         39U
#define FEATURE_CLOCK_IP_HAS_PFE_MAC_0_EXT_TX_CLK         40U
#define FEATURE_CLOCK_IP_HAS_PFE_MAC_1_EXT_REF_CLK         41U
#define FEATURE_CLOCK_IP_HAS_PFE_MAC_1_EXT_RX_CLK         42U
#define FEATURE_CLOCK_IP_HAS_PFE_MAC_1_EXT_TX_CLK         43U
#define FEATURE_CLOCK_IP_HAS_PFE_MAC_2_EXT_REF_CLK         44U
#define FEATURE_CLOCK_IP_HAS_PFE_MAC_2_EXT_RX_CLK         45U
#define FEATURE_CLOCK_IP_HAS_PFE_MAC_2_EXT_TX_CLK         46U
#define FEATURE_CLOCK_IP_HAS_SERDES_0_LANE_0_TX         47U
#define FEATURE_CLOCK_IP_HAS_SERDES_0_LANE_0_CDR         48U
#define FEATURE_CLOCK_IP_HAS_SERDES_0_LANE_1_TX         49U
#define FEATURE_CLOCK_IP_HAS_SERDES_0_LANE_1_CDR         50U
#define FEATURE_CLOCK_IP_HAS_SERDES_1_LANE_0_TX         51U
#define FEATURE_CLOCK_IP_HAS_SERDES_1_LANE_0_CDR         52U
#define FEATURE_CLOCK_IP_HAS_SERDES_1_LANE_1_TX         53U
#define FEATURE_CLOCK_IP_HAS_SERDES_1_LANE_1_CDR         54U
#define FEATURE_CLOCK_IP_HAS_XBAR_2X_CLK         55U
#define FEATURE_CLOCK_IP_HAS_XBAR_CLK         56U
#define FEATURE_CLOCK_IP_HAS_XBAR_DIV2_CLK         57U
#define FEATURE_CLOCK_IP_HAS_XBAR_DIV3_CLK         58U
#define FEATURE_CLOCK_IP_HAS_XBAR_DIV4_CLK         59U
#define FEATURE_CLOCK_IP_HAS_XBAR_DIV6_CLK         60U
#define FEATURE_CLOCK_IP_HAS_A53_CORE_CLK         61U
#define FEATURE_CLOCK_IP_HAS_A53_CORE_DIV2_CLK         62U
#define FEATURE_CLOCK_IP_HAS_A53_CORE_DIV10_CLK         63U
#define FEATURE_CLOCK_IP_HAS_DDR_CLK         64U
#define FEATURE_CLOCK_IP_HAS_PFE_PE_CLK         65U
#define FEATURE_CLOCK_IP_HAS_PER_CLK         66U
#define FEATURE_CLOCK_IP_HAS_GMAC_REF_DIV_CLK         67U
#define FEATURE_CLOCK_IP_HAS_PFEMAC0_REF_DIV_CLK         68U
#define FEATURE_CLOCK_IP_HAS_PFEMAC1_REF_DIV_CLK         69U
#define FEATURE_CLOCK_IP_HAS_PFEMAC2_REF_DIV_CLK         70U
#define FEATURE_CLOCK_IP_HAS_SERDES_REF_CLK         71U
#define FEATURE_CLOCK_PRODUCERS_NO         72U
#define FEATURE_CLOCK_IP_HAS_ADC0_CLK         73U
#define FEATURE_CLOCK_IP_HAS_ADC1_CLK         74U
#define FEATURE_CLOCK_IP_HAS_CLKOUT0_CLK         75U
#define FEATURE_CLOCK_IP_HAS_CLKOUT1_CLK         76U
#define FEATURE_CLOCK_IP_HAS_CORE_A53_CLUSTER_0_CLK         77U
#define FEATURE_CLOCK_IP_HAS_CORE_A53_CLUSTER_1_CLK         78U
#define FEATURE_CLOCK_IP_HAS_CORE_M7_0_CLK         79U
#define FEATURE_CLOCK_IP_HAS_CORE_M7_1_CLK         80U
#define FEATURE_CLOCK_IP_HAS_CORE_M7_2_CLK         81U
#define FEATURE_CLOCK_IP_HAS_CRC0_CLK         82U
#define FEATURE_CLOCK_IP_HAS_CTU0_CLK         83U
#define FEATURE_CLOCK_IP_HAS_CTU1_CLK         84U
#define FEATURE_CLOCK_IP_HAS_DAPB_CLK         85U
#define FEATURE_CLOCK_IP_HAS_DMA0_CLK         86U
#define FEATURE_CLOCK_IP_HAS_DMA1_CLK         87U
#define FEATURE_CLOCK_IP_HAS_DMAMUX0_CLK         88U
#define FEATURE_CLOCK_IP_HAS_DMAMUX1_CLK         89U
#define FEATURE_CLOCK_IP_HAS_DMAMUX2_CLK         90U
#define FEATURE_CLOCK_IP_HAS_DMAMUX3_CLK         91U
#define FEATURE_CLOCK_IP_HAS_DMA_CRC0_CLK         92U
#define FEATURE_CLOCK_IP_HAS_DMA_CRC1_CLK         93U
#define FEATURE_CLOCK_IP_HAS_EIM0_CLK         94U
#define FEATURE_CLOCK_IP_HAS_EIM1_CLK         95U
#define FEATURE_CLOCK_IP_HAS_EIM2_CLK         96U
#define FEATURE_CLOCK_IP_HAS_EIM3_CLK         97U
#define FEATURE_CLOCK_IP_HAS_EIM_CLK         98U
#define FEATURE_CLOCK_IP_HAS_ERM0_CLK         99U
#define FEATURE_CLOCK_IP_HAS_FLEXCAN_CLK         100U
#define FEATURE_CLOCK_IP_HAS_FLEXCAN0_CLK         101U
#define FEATURE_CLOCK_IP_HAS_FLEXCAN1_CLK         102U
#define FEATURE_CLOCK_IP_HAS_FLEXCAN2_CLK         103U
#define FEATURE_CLOCK_IP_HAS_FLEXCAN3_CLK         104U
#define FEATURE_CLOCK_IP_HAS_FLEXRAY_CLK         105U
#define FEATURE_CLOCK_IP_HAS_FRAY0_CLK         106U
#define FEATURE_CLOCK_IP_HAS_FLEXTIMERA_CLK         107U
#define FEATURE_CLOCK_IP_HAS_FTIMER0_CLK         108U
#define FEATURE_CLOCK_IP_HAS_FLEXTIMERB_CLK         109U
#define FEATURE_CLOCK_IP_HAS_FTIMER1_CLK         110U
#define FEATURE_CLOCK_IP_HAS_GMAC_TS_CLK         111U
#define FEATURE_CLOCK_IP_HAS_GMAC0_RX_CLK         112U
#define FEATURE_CLOCK_IP_HAS_GMAC0_TX_CLK         113U
#define FEATURE_CLOCK_IP_HAS_GMAC0_TS_CLK         114U
#define FEATURE_CLOCK_IP_HAS_IIC0_CLK         115U
#define FEATURE_CLOCK_IP_HAS_IIC1_CLK         116U
#define FEATURE_CLOCK_IP_HAS_IIC2_CLK         117U
#define FEATURE_CLOCK_IP_HAS_IIC3_CLK         118U
#define FEATURE_CLOCK_IP_HAS_IIC4_CLK         119U
#define FEATURE_CLOCK_IP_HAS_LBIST_CLK         120U
#define FEATURE_CLOCK_IP_HAS_LBIST0_CLK         121U
#define FEATURE_CLOCK_IP_HAS_LBIST1_CLK         122U
#define FEATURE_CLOCK_IP_HAS_LBIST2_CLK         123U
#define FEATURE_CLOCK_IP_HAS_LBIST3_CLK         124U
#define FEATURE_CLOCK_IP_HAS_LBIST4_CLK         125U
#define FEATURE_CLOCK_IP_HAS_LBIST5_CLK         126U
#define FEATURE_CLOCK_IP_HAS_LBIST6_CLK         127U
#define FEATURE_CLOCK_IP_HAS_LBIST7_CLK         128U
#define FEATURE_CLOCK_IP_HAS_LIN_CLK         129U
#define FEATURE_CLOCK_IP_HAS_LIN0_CLK         130U
#define FEATURE_CLOCK_IP_HAS_LIN1_CLK         131U
#define FEATURE_CLOCK_IP_HAS_LIN2_CLK         132U
#define FEATURE_CLOCK_IP_HAS_OCOTP0_CLK         133U
#define FEATURE_CLOCK_IP_HAS_PFEMAC0_RX_CLK         134U
#define FEATURE_CLOCK_IP_HAS_PFEMAC0_TX_CLK         135U
#define FEATURE_CLOCK_IP_HAS_PFEMAC1_RX_CLK         136U
#define FEATURE_CLOCK_IP_HAS_PFEMAC1_TX_CLK         137U
#define FEATURE_CLOCK_IP_HAS_PFEMAC2_RX_CLK         138U
#define FEATURE_CLOCK_IP_HAS_PFEMAC2_TX_CLK         139U
#define FEATURE_CLOCK_IP_HAS_PIT0_CLK         140U
#define FEATURE_CLOCK_IP_HAS_PIT1_CLK         141U
#define FEATURE_CLOCK_IP_HAS_QSPI_CLK         142U
#define FEATURE_CLOCK_IP_HAS_QSPI0_CLK         143U
#define FEATURE_CLOCK_IP_HAS_RTC0_CLK         144U
#define FEATURE_CLOCK_IP_HAS_SIUL0_CLK         145U
#define FEATURE_CLOCK_IP_HAS_SIUL1_CLK         146U
#define FEATURE_CLOCK_IP_HAS_SPI_CLK         147U
#define FEATURE_CLOCK_IP_HAS_SPI0_CLK         148U
#define FEATURE_CLOCK_IP_HAS_SPI1_CLK         149U
#define FEATURE_CLOCK_IP_HAS_SPI2_CLK         150U
#define FEATURE_CLOCK_IP_HAS_SPI3_CLK         151U
#define FEATURE_CLOCK_IP_HAS_SPI4_CLK         152U
#define FEATURE_CLOCK_IP_HAS_SPI5_CLK         153U
#define FEATURE_CLOCK_IP_HAS_STM0_CLK         154U
#define FEATURE_CLOCK_IP_HAS_STM1_CLK         155U
#define FEATURE_CLOCK_IP_HAS_STM2_CLK         156U
#define FEATURE_CLOCK_IP_HAS_STM3_CLK         157U
#define FEATURE_CLOCK_IP_HAS_STM4_CLK         158U
#define FEATURE_CLOCK_IP_HAS_STM5_CLK         159U
#define FEATURE_CLOCK_IP_HAS_STM6_CLK         160U
#define FEATURE_CLOCK_IP_HAS_STM7_CLK         161U
#define FEATURE_CLOCK_IP_HAS_SWT0_CLK         162U
#define FEATURE_CLOCK_IP_HAS_SWT1_CLK         163U
#define FEATURE_CLOCK_IP_HAS_SWT2_CLK         164U
#define FEATURE_CLOCK_IP_HAS_SWT3_CLK         165U
#define FEATURE_CLOCK_IP_HAS_SWT4_CLK         166U
#define FEATURE_CLOCK_IP_HAS_SWT5_CLK         167U
#define FEATURE_CLOCK_IP_HAS_SWT6_CLK         168U
#define FEATURE_CLOCK_IP_HAS_USDHC_CLK         169U
#define FEATURE_CLOCK_IP_HAS_USDHC0_CLK         170U
#define FEATURE_CLOCK_IP_HAS_WKPU0_CLK         171U
#define FEATURE_CLOCK_IP_HAS_XBAR_DIV3_FAIL_CLK         172U
#define FEATURE_CLOCKS_NO         173U

/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/



#ifdef __cplusplus
}
#endif

#endif /* #ifndef CLOCK_IP_CFG_DEFINES_H */

/** @} */
