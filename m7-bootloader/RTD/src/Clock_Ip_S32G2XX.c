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
*   @file       Clock_Ip_S32G274A.c
*   @version    1.0.0
*
*   @brief   CLOCK driver implementations.
*   @details CLOCK driver implementations.
*
*   @addtogroup CLOCK_DRIVER Clock Driver
*   @{
*/

/**
* @page misra_violations MISRA-C:2012 violations
*
* @section Clock_Ip_S32G2XX_c_REF_1
* Violates MISRA 2012 Advisory Rule 20.1, #include directives should only be preceded by preprocessor
* directives or comments. AUTOSAR imposes the specification of the sections in which certain parts
* of the driver must be placed.
*
* @section Clock_Ip_S32G2XX_c_REF_2
* Violates MISRA 2012 Advisory Rule 4.8, This file includes the definition
* of types but does not use it. Header is common for all files
*
* @section Clock_Ip_S32G2XX_c_REF_3
* Violates MISRA 2012 Advisory Rule 11.4, A conversion should not be performed between a pointer to object
* and an integer type.
* The cast is used to access memory mapped registers.
*
* @section Clock_Ip_S32G2XX_c_REF_4
* Violates MISRA 2012 Advisory Directive 4.9, A function should be used in preference to a function-like macro where they are interchangeable.
* Function like macro are used to reduce code complexity
*
* @section Clock_Ip_S32G2XX_c_REF_5
* Violates MISRA 2012 Advisory Rule 12.3, The comma operator should not be used.
* The comma is used  to abstract the trusted call function and to determine when the return into user mode is needed.
*
*
* @section Clock_Ip_S32G2XX_c_REF_6
* Violates MISRA 2012 Advisory Rule 8.7, Functions and objects should not be defined with external linkage if
* they are referenced in only one translation unit.
* This error shouldn't be reported for static objects.
*
* @section Clock_Ip_S32G2XX_c_REF_7
* Violates MISRA 2012 Required Rule 13.1, Initializer lists shall not contain persisten side effects.
* The initializer lists is used to access memory mapped registers.
*/

#include <stdbool.h>
#include <stddef.h>

#if defined(S32G2XX)

#include "Clock_Ip_Private.h"

#if (defined(CLOCK_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT))
    #define USER_MODE_REG_PROT_ENABLED      (STD_ON)
    #include "RegLockMacros.h"
#endif /* CLOCK_IP_ENABLE_USER_MODE_SUPPORT */

#define CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL    0U

#define    BUFFER_NO_CLK                                     0U
#define    BUFFER_FIRC                                       1U
#define    BUFFER_FXOSC                                      2U
#define    BUFFER_SIRC                                       3U
#define    BUFFER_COREPLL                                    4U
#define    BUFFER_PERIPHPLL                                  5U
#define    BUFFER_DDRPLL                                     6U
#define    BUFFER_ACCELPLL                                   7U
#define    BUFFER_ftm0extref                                 8U
#define    BUFFER_ftm1extref                                 9U
#define    BUFFER_gmac0extref                                10U
#define    BUFFER_gmac0extrx                                 11U
#define    BUFFER_gmac0exttx                                 12U
#define    BUFFER_gmacextts                                  13U
#define    BUFFER_pfemac0extref                              14U
#define    BUFFER_pfemac0extrx                               15U
#define    BUFFER_pfemac0exttx                               16U
#define    BUFFER_pfemac1extref                              17U
#define    BUFFER_pfemac1extrx                               18U
#define    BUFFER_pfemac1exttx                               19U
#define    BUFFER_pfemac2extref                              20U
#define    BUFFER_pfemac2extrx                               21U
#define    BUFFER_pfemac2exttx                               22U
#define    BUFFER_SERDES0LANE0TX                             23U
#define    BUFFER_SERDES0LANE0CDR                            24U
#define    BUFFER_SERDES0LANE1TX                             25U
#define    BUFFER_SERDES0LANE1CDR                            26U
#define    BUFFER_SERDES1LANE0TX                             27U
#define    BUFFER_SERDES1LANE0CDR                            28U
#define    BUFFER_SERDES1LANE1TX                             29U
#define    BUFFER_SERDES1LANE1CDR                            30U
#define    BUFFER_XBAR_FIRC                                  31U
#define    BUFFER_XBARDIV2_FIRC                              32U
#define    BUFFER_XBARDIV3_FIRC                              33U
#define    BUFFER_XBARDIV4_FIRC                              34U
#define    BUFFER_XBARDIV6_FIRC                              35U
#define    BUFFER_A53COREDIV2_FIRC                           36U
#define    BUFFER_A53COREDIV10_FIRC                          37U
#define    BUFFER_PFEPE_FIRC                                 38U
#define    BUFFER_PER_FIRC                                   39U
#define    BUFFER_GMACREFDIV_FIRC                            40U
#define    BUFFER_GMACREFDIV_gmac0extref                     41U
#define    BUFFER_PFEMAC0REFDIV_FIRC                         42U
#define    BUFFER_PFEMAC0REFDIV_pfemac0extref                43U
#define    BUFFER_PFEMAC1REFDIV_FIRC                         44U
#define    BUFFER_PFEMAC1REFDIV_pfemac1extref                45U
#define    BUFFER_PFEMAC2REFDIV_FIRC                         46U
#define    BUFFER_PFEMAC2REFDIV_pfemac2extref                47U
#define    BUFFER_COREPLLPHI0_COREPLL                        48U
#define    BUFFER_COREPLLPHI1_COREPLL                        49U
#define    BUFFER_COREPLLDFS1_COREPLL                        50U
#define    BUFFER_COREPLLDFS2_COREPLL                        51U
#define    BUFFER_COREPLLDFS3_COREPLL                        52U
#define    BUFFER_COREPLLDFS4_COREPLL                        53U
#define    BUFFER_COREPLLDFS5_COREPLL                        54U
#define    BUFFER_COREPLLDFS6_COREPLL                        55U
#define    BUFFER_PERIPHPLLPHI0_PERIPHPLL                    56U
#define    BUFFER_PERIPHPLLPHI1_PERIPHPLL                    57U
#define    BUFFER_PERIPHPLLPHI2_PERIPHPLL                    58U
#define    BUFFER_PERIPHPLLPHI3_PERIPHPLL                    59U
#define    BUFFER_PERIPHPLLPHI4_PERIPHPLL                    60U
#define    BUFFER_PERIPHPLLPHI5_PERIPHPLL                    61U
#define    BUFFER_PERIPHPLLPHI6_PERIPHPLL                    62U
#define    BUFFER_PERIPHPLLPHI7_PERIPHPLL                    63U
#define    BUFFER_PERIPHPLLDFS1_PERIPHPLL                    64U
#define    BUFFER_PERIPHPLLDFS2_PERIPHPLL                    65U
#define    BUFFER_PERIPHPLLDFS3_PERIPHPLL                    66U
#define    BUFFER_PERIPHPLLDFS4_PERIPHPLL                    67U
#define    BUFFER_PERIPHPLLDFS5_PERIPHPLL                    68U
#define    BUFFER_PERIPHPLLDFS6_PERIPHPLL                    69U
#define    BUFFER_DDRPLLPHI0_DDRPLL                          70U
#define    BUFFER_ACCELPLLPHI0_ACCELPLL                      71U
#define    BUFFER_ACCELPLLPHI1_ACCELPLL                      72U
#define    BUFFER_XBAR_COREPLLDFS1_COREPLL                   73U
#define    BUFFER_XBARDIV2_COREPLLDFS1_COREPLL               74U
#define    BUFFER_XBARDIV3_COREPLLDFS1_COREPLL               75U
#define    BUFFER_XBARDIV4_COREPLLDFS1_COREPLL               76U
#define    BUFFER_XBARDIV6_COREPLLDFS1_COREPLL               77U
#define    BUFFER_A53COREDIV2_COREPLLPHI0_COREPLL            78U
#define    BUFFER_A53COREDIV2_COREPLLDFS2_COREPLL            79U
#define    BUFFER_A53COREDIV10_COREPLLPHI0_COREPLL           80U
#define    BUFFER_A53COREDIV10_COREPLLDFS2_COREPLL           81U
#define    BUFFER_PFEPE_ACCELPLLPHI1_ACCELPLL                82U
#define    BUFFER_PER_PERIPHPLLPHI1_PERIPHPLL                83U
#define    BUFFER_FREQS_NO                                   84U

/* Pcfs settings that are dependent on device */
#define A_MAX_SIZE 6U
#define DEFAULT_MAX_ALLOWABLE_IDD_CHANGE 50

typedef struct {

    uint32 input1, input2, input3, input4, input5;
    uint32 aux1, aux2, aux3, aux4, aux5;
    uint32 output;

} tCalcFreqDataType;

/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_S32G2XX_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

cgmMux_Type* const cgm[MC_CGM_instances_count][MC_CGM_muxs_count] =
{
    {(cgmMux_Type*)(&MC_CGM_0->MUX_0_CSC), (cgmMux_Type*)(&MC_CGM_0->MUX_1_CSC), (cgmMux_Type*)(&MC_CGM_0->MUX_2_CSC), (cgmMux_Type*)(&MC_CGM_0->MUX_3_CSC), (cgmMux_Type*)(&MC_CGM_0->MUX_4_CSC), (cgmMux_Type*)(&MC_CGM_0->MUX_5_CSC), (cgmMux_Type*)(&MC_CGM_0->MUX_6_CSC), (cgmMux_Type*)(&MC_CGM_0->MUX_7_CSC), (cgmMux_Type*)(&MC_CGM_0->MUX_8_CSC), (cgmMux_Type*)(&MC_CGM_0->MUX_9_CSC), (cgmMux_Type*)(&MC_CGM_0->MUX_10_CSC), (cgmMux_Type*)(&MC_CGM_0->MUX_11_CSC), (cgmMux_Type*)(&MC_CGM_0->MUX_12_CSC), NULL, (cgmMux_Type*)(&MC_CGM_0->MUX_14_CSC), (cgmMux_Type*)(&MC_CGM_0->MUX_15_CSC), (cgmMux_Type*)(&MC_CGM_0->MUX_16_CSC)},
    {(cgmMux_Type*)(&MC_CGM_1->MUX_0_CSC),NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {(cgmMux_Type*)(&MC_CGM_2->MUX_0_CSC), (cgmMux_Type*)(&MC_CGM_2->MUX_1_CSC), (cgmMux_Type*)(&MC_CGM_2->MUX_2_CSC), (cgmMux_Type*)(&MC_CGM_2->MUX_3_CSC), (cgmMux_Type*)(&MC_CGM_2->MUX_4_CSC), (cgmMux_Type*)(&MC_CGM_2->MUX_5_CSC), (cgmMux_Type*)(&MC_CGM_2->MUX_6_CSC), (cgmMux_Type*)(&MC_CGM_2->MUX_7_CSC), (cgmMux_Type*)(&MC_CGM_2->MUX_8_CSC), (cgmMux_Type*)(&MC_CGM_2->MUX_9_CSC),NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
    {(cgmMux_Type*)(&MC_CGM_5->MUX_0_CSC),NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},
};
cgmPcfs_Type* const cgmPcfs[MC_CGM_instances_count] =
{
    (cgmPcfs_Type*)(&MC_CGM_0->PCFS_SDUR),(cgmPcfs_Type*)(&MC_CGM_1->PCFS_SDUR),(cgmPcfs_Type*)(&MC_CGM_2->PCFS_SDUR),NULL,NULL,NULL
};
ExtOSC_Type* const xosc[XOSC_INSTANCES_ARRAY_SIZE] = {(ExtOSC_Type*)FXOSC};
PLLDIG_Type* const pll[PLL_INSTANCES_ARRAY_SIZE] = {CORE_PLL, PERIPH_PLL, DDR_PLL, ACCEL_PLL};
DFS_Type* const dfs[DFS_INSTANCES_ARRAY_SIZE] = {CORE_DFS,PERIPH_DFS};
volatile ClockMonitor_Type* const cmu[CMU_INSTANCES_ARRAY_SIZE] =
{

    (volatile ClockMonitor_Type*)CMU_FC_0,
    (volatile ClockMonitor_Type*)CMU_FC_5,
    (volatile ClockMonitor_Type*)CMU_FC_6,
    (volatile ClockMonitor_Type*)CMU_FC_7,
    (volatile ClockMonitor_Type*)CMU_FC_8,
    (volatile ClockMonitor_Type*)CMU_FC_9,
    (volatile ClockMonitor_Type*)CMU_FC_10,
    (volatile ClockMonitor_Type*)CMU_FC_11,
    (volatile ClockMonitor_Type*)CMU_FC_12,
    (volatile ClockMonitor_Type*)CMU_FC_13,
    (volatile ClockMonitor_Type*)CMU_FC_14,
    (volatile ClockMonitor_Type*)CMU_FC_15,
    (volatile ClockMonitor_Type*)CMU_FC_16,
    (volatile ClockMonitor_Type*)CMU_FC_17,
    (volatile ClockMonitor_Type*)CMU_FC_18,
    (volatile ClockMonitor_Type*)CMU_FC_20,
    (volatile ClockMonitor_Type*)CMU_FC_21,
    (volatile ClockMonitor_Type*)CMU_FC_22,
    (volatile ClockMonitor_Type*)CMU_FC_27,
    (volatile ClockMonitor_Type*)CMU_FC_28,
    (volatile ClockMonitor_Type*)CMU_FC_39,
    (volatile ClockMonitor_Type*)CMU_FC_46,
    (volatile ClockMonitor_Type*)CMU_FC_47,
    (volatile ClockMonitor_Type*)CMU_FC_48,
    (volatile ClockMonitor_Type*)CMU_FC_49,
    (volatile ClockMonitor_Type*)CMU_FC_50,
    (volatile ClockMonitor_Type*)CMU_FC_51,
};
volatile mcmePartitionSet_Type* const mcmeSetPartitions[MC_ME_partitions_count] =
{
    (volatile mcmePartitionSet_Type*)((volatile uint8*)&MC_ME->PRTN0_COFB0_CLKEN),
    NULL,
    (volatile mcmePartitionSet_Type*)((volatile uint8*)&MC_ME->PRTN2_COFB0_CLKEN),
    (volatile mcmePartitionSet_Type*)((volatile uint8*)&MC_ME->PRTN3_COFB0_CLKEN),
};
volatile const mcmePartitionGet_Type* const mcmeGetPartitions[MC_ME_partitions_count] =
{
    (volatile const mcmePartitionGet_Type*)((volatile const uint8*)&MC_ME->PRTN0_COFB0_STAT),
    NULL,
    (volatile const mcmePartitionGet_Type*)((volatile const uint8*)&MC_ME->PRTN2_COFB0_STAT),
    (volatile const mcmePartitionGet_Type*)((volatile const uint8*)&MC_ME->PRTN3_COFB0_STAT),
};
volatile mcmePartitionTrigger_Type* const mcmeTriggerPartitions[MC_ME_partitions_count] =
{
    (volatile mcmePartitionTrigger_Type*)((volatile uint8*)&MC_ME->PRTN0_PCONF),
    NULL,
    (volatile mcmePartitionTrigger_Type*)((volatile uint8*)&MC_ME->PRTN2_PCONF),
    (volatile mcmePartitionTrigger_Type*)((volatile uint8*)&MC_ME->PRTN3_PCONF),
};

cmuEntry cmuEntries[CMU_ENTRIES_NO] =  {
    /* CMU FXOSC_CLK */
    {
        FXOSC_CLK,                                       /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU XBAR_DIV3_FAIL_CLK */
    {
        XBAR_DIV3_FAIL_CLK,                              /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU CORE_M7_0_CLK */
    {
        CORE_M7_0_CLK,                                   /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU XBAR_DIV3_CLK */
    {
        XBAR_DIV3_CLK,                                   /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU CORE_M7_1_CLK */
    {
        CORE_M7_1_CLK,                                   /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU CORE_M7_2_CLK */
    {
        CORE_M7_2_CLK,                                   /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU PER_CLK */
    {
        PER_CLK,                                         /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU SERDES_REF_CLK */
    {
        SERDES_REF_CLK,                                  /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU FLEXRAY_CLK */
    {
        FLEXRAY_CLK,                                     /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU FLEXCAN_CLK */
    {
        FLEXCAN_CLK,                                    /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU GMAC0_TX_CLK */
    {
        GMAC0_TX_CLK,                                    /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU GMAC_TS_CLK */
    {
        GMAC_TS_CLK,                                     /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU LIN_CLK */
    {
        LIN_CLK,                                         /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU QSPI_CLK */
    {
        QSPI_CLK,                                        /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU USDHC_CLK */
    {
        USDHC_CLK,                                       /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU DDR_CLK */
    {
        DDR_CLK,                                         /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU GMAC0_RX_CLK */
    {
        GMAC0_RX_CLK,                                    /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU SPI_CLK */
    {
        SPI_CLK,                                         /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU CORE_A53_CLUSTER_0_CLK */
    {
        CORE_A53_CLUSTER_0_CLK,                          /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU CORE_A53_CLUSTER_1_CLK */
    {
        CORE_A53_CLUSTER_1_CLK,                          /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU PFE_PE_CLK */
    {
        PFE_PE_CLK,                                       /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU PFEMAC0_TX_CLK */
    {
        PFEMAC0_TX_CLK,                                  /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU PFEMAC0_RX_CLK */
    {
        PFEMAC0_RX_CLK,                                  /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU PFEMAC1_TX_CLK */
    {
        PFEMAC1_TX_CLK,                                  /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU PFEMAC1_RX_CLK */
    {
        PFEMAC1_RX_CLK,                                  /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU PFEMAC2_TX_CLK */
    {
        PFEMAC2_TX_CLK,                                  /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
    /* CMU PFEMAC2_RX_CLK */
    {
        PFEMAC2_RX_CLK,                                  /* Name of the clock that supports cmu (clock monitor) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,          /* Pointer to cmu configuration structure - by default is not under mcu control */
        0U,                                              /* enable */
        0U,                                              /* refCount */
        0x00FFFFFCU,                                     /* hfRef */
        3U,                                              /* lfRef */
    },
};

static const uint32 enableDisableMask[2U] = {0U,0xFFFFFFFFU};

static const uint32 aMax[A_MAX_SIZE] = {0U,5U,10U,15U,20U,100U};
static const uint32 pcfsRate[A_MAX_SIZE] = {0U,12U,48U,112U,184U,1000U};

/* microA per MHz */
#define DYNAMIC_IDD_CHANGE 2360U

#define NO_CALLBACK                   0U
#define HWMUX_PCFS_DIV_TRIGGER_CMU    1U
#define PCFS_DFS                      1U
#define PLL_MOD                       1U
#define GATE                          1U
#define HWMUX_DIV_CMU                 2U
#define PLL                           2U
#define DFS                           2U
#define HWMUX_DIV_PHASE_CMU           3U
#define HWMUX_CMU                     4U
#define PCFS_PLL_OUT                  4U
#define HWMUX_DIV                     5U
#define FAST_XOSC_CMU                 5U
#define HWMUX_DIV_TRIGGER             6U
#define CMU                           6U
#define SWMUX_DIV_CLKOUT              7U
#define HWMUX_DIV_PHASE               8U
#define HWMUX_DIV_PHASE_TRIGGER_CMU   9U
#define HWMUX_PCFS                    10U
#define PLL_OUT                       10U

const uint8 dividerCallbackIndex[ALL_CALLBACKS_COUNT] = {
    NO_CALLBACK,                                       /* No callback */
    CGM_X_DE_DIV_STAT_WITHOUT_PHASE,                   /* HWMUX_PCFS_DIV_TRIGGER_CMU */
    CGM_X_DE_DIV_STAT_WITHOUT_PHASE,                   /* HWMUX_DIV_CMU */
    CGM_X_DE_DIV_STAT_WITH_PHASE,                      /* HWMUX_DIV_PHASE_CMU */
    PLLDIG_PLL0DIV_DE_DIV_OUTPUT,                      /* PCFS_PLL_OUT */
    CGM_X_DE_DIV_STAT_WITHOUT_PHASE,                   /* HWMUX_DIV */
    CGM_X_DE_DIV_STAT_WITHOUT_PHASE,                   /* HWMUX_DIV_TRIGGER */
    CGM_X_DE_DIV_WITHOUT_PHASE,                        /* SWMUX_DIV_CLKOUT */
    CGM_X_DE_DIV_STAT_WITH_PHASE,                      /* HWMUX_DIV_PHASE */
    CGM_X_DE_DIV_STAT_WITH_PHASE,                      /* HWMUX_DIV_PHASE_TRIGGER_CMU */
    PLLDIG_PLL0DIV_DE_DIV_OUTPUT,                      /* PLL_OUT */
    NO_CALLBACK,                                       /* No callback */
};
const uint8 dividertriggerCallbackIndex[ALL_CALLBACKS_COUNT] = {
    NO_CALLBACK,                                       /* No callback */
    CGM_X_DIV_TRIG_CTRL_TCTL_HHEN_UPD_STAT,            /* HWMUX_PCFS_DIV_TRIGGER_CMU */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    CGM_X_DIV_TRIG_CTRL_TCTL_HHEN_UPD_STAT,            /* HWMUX_DIV_TRIGGER */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    CGM_X_DIV_TRIG_CTRL_TCTL_HHEN_UPD_STAT,            /* HWMUX_DIV_PHASE_TRIGGER_CMU */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
};
const uint8 xoscCallbackIndex[ALL_CALLBACKS_COUNT] = {
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    FXOSC_OSCON_BYP_EOCV_GM_SEL,                       /* FAST_XOSC_CMU */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
};
const uint8 ircoscCallbackIndex[ALL_CALLBACKS_COUNT] = {
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
};
const uint8 gateCallbackIndex[ALL_CALLBACKS_COUNT] = {
    NO_CALLBACK,                                       /* No callback */
    MC_ME_PARTITION_COFB_ENABLE_REQUEST,               /* GATE */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
};
const uint8 fractional_dividerCallbackIndex[ALL_CALLBACKS_COUNT] = {
    NO_CALLBACK,                                       /* No callback */
    DFS_MFI_MFN,                                       /* PCFS_DFS */
    DFS_MFI_MFN,                                       /* DFS */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
};
const uint8 pllCallbackIndex[ALL_CALLBACKS_COUNT] = {
    NO_CALLBACK,                                       /* No callback */
    PLLDIG_RDIV_MFI_MFN_SDMEN_SSCGBYP_SPREADCTL_STEPNO_STEPSIZE,/* PLL_MOD */
    PLLDIG_RDIV_MFI_MFN_SDMEN,                         /* PLL */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
};
const uint8 selectorCallbackIndex[ALL_CALLBACKS_COUNT] = {
    NO_CALLBACK,                                       /* No callback */
    CGM_X_CSC_CSS_CLK_SW_RAMPDOWN_RAMPUP_SWIP,         /* HWMUX_PCFS_DIV_TRIGGER_CMU */
    CGM_X_CSC_CSS_CLK_SW_SWIP,                         /* HWMUX_DIV_CMU */
    CGM_X_CSC_CSS_CLK_SW_SWIP,                         /* HWMUX_DIV_PHASE_CMU */
    CGM_X_CSC_CSS_CLK_SW_SWIP,                         /* HWMUX_CMU */
    CGM_X_CSC_CSS_CLK_SW_SWIP,                         /* HWMUX_DIV */
    CGM_X_CSC_CSS_CLK_SW_SWIP,                         /* HWMUX_DIV_TRIGGER */
    CGM_X_CSC_CSS_CS_GRIP,                             /* SWMUX_DIV_CLKOUT */
    CGM_X_CSC_CSS_CLK_SW_SWIP,                         /* HWMUX_DIV_PHASE */
    CGM_X_CSC_CSS_CLK_SW_SWIP,                         /* HWMUX_DIV_PHASE_TRIGGER_CMU */
    CGM_X_CSC_CSS_CLK_SW_RAMPDOWN_RAMPUP_SWIP,         /* HWMUX_PCFS */
    CGM_X_CSC_CSS_CLK_SW_SWIP,                         /* HWMUX */
};
const uint8 pcfsCallbackIndex[ALL_CALLBACKS_COUNT] = {
    NO_CALLBACK,                                       /* No callback */
    CGM_X_PCFS_SDUR_DIVC_DIVE_DIVS,                    /* PCFS_DFS */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    CGM_X_PCFS_SDUR_DIVC_DIVE_DIVS,                    /* PCFS_PLL_OUT */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
};
const uint8 cmuCallbackIndex[ALL_CALLBACKS_COUNT] = {
    NO_CALLBACK,                                       /* No callback */
    CMU_FC_FCE_REF_CNT_LFREF_HFREF,                    /* HWMUX_PCFS_DIV_TRIGGER_CMU */
    CMU_FC_FCE_REF_CNT_LFREF_HFREF,                    /* HWMUX_DIV_CMU */
    CMU_FC_FCE_REF_CNT_LFREF_HFREF,                    /* HWMUX_DIV_PHASE_CMU */
    CMU_FC_FCE_REF_CNT_LFREF_HFREF,                    /* HWMUX_CMU */
    CMU_FC_FCE_REF_CNT_LFREF_HFREF,                    /* FAST_XOSC_CMU */
    CMU_FC_FCE_REF_CNT_LFREF_HFREF,                    /* CMU */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
    CMU_FC_FCE_REF_CNT_LFREF_HFREF,                    /* HWMUX_DIV_PHASE_TRIGGER_CMU */
    NO_CALLBACK,                                       /* No callback */
    NO_CALLBACK,                                       /* No callback */
};






const clock_name_source_type_t clockName_sourceType[CLOCK_PRODUCERS_NO] = {
    IRCOSC_TYPE,                               /*!< FIRC_CLK                                */
    XOSC_TYPE,                                 /*!< FXOSC_CLK                               */
    IRCOSC_TYPE,                               /*!< SIRC_CLK                                */
    PLL_TYPE,                                  /*!< COREPLL_CLK                             */
    PLL_TYPE,                                  /*!< PERIPHPLL_CLK                           */
    PLL_TYPE,                                  /*!< DDRPLL_CLK                              */
    PLL_TYPE,                                  /*!< ACCELPLL_CLK                            */
    PLL_TYPE,                                  /*!< CORE_PLL_PHI0_CLK                       */
    PLL_TYPE,                                  /*!< CORE_PLL_PHI1_CLK                       */
    PLL_TYPE,                                  /*!< CORE_PLL_DFS1_CLK                       */
    PLL_TYPE,                                  /*!< CORE_PLL_DFS2_CLK                       */
    PLL_TYPE,                                  /*!< CORE_PLL_DFS3_CLK                       */
    PLL_TYPE,                                  /*!< CORE_PLL_DFS4_CLK                       */
    PLL_TYPE,                                  /*!< CORE_PLL_DFS5_CLK                       */
    PLL_TYPE,                                  /*!< CORE_PLL_DFS6_CLK                       */
    PLL_TYPE,                                  /*!< PERIPH_PLL_PHI0_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_PHI1_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_PHI2_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_PHI3_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_PHI4_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_PHI5_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_PHI6_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_PHI7_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_DFS1_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_DFS2_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_DFS3_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_DFS4_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_DFS5_CLK                     */
    PLL_TYPE,                                  /*!< PERIPH_PLL_DFS6_CLK                     */
    PLL_TYPE,                                  /*!< DDR_PLL_PHI0_CLK                        */
    PLL_TYPE,                                  /*!< ACCEL_PLL_PHI0_CLK                      */
    PLL_TYPE,                                  /*!< ACCEL_PLL_PHI1_CLK                      */
    EXT_CLK_TYPE,                              /*!< FTM_0_EXT_REF_CLK                       */
    EXT_CLK_TYPE,                              /*!< FTM_1_EXT_REF_CLK                       */
    EXT_CLK_TYPE,                              /*!< GMAC_0_EXT_REF_CLK                      */
    EXT_CLK_TYPE,                              /*!< GMAC_0_EXT_RX_CLK                       */
    EXT_CLK_TYPE,                              /*!< GMAC_0_EXT_TX_CLK                       */
    EXT_CLK_TYPE,                              /*!< GMAC_EXT_TS_CLK                         */
    EXT_CLK_TYPE,                              /*!< PFE_MAC_0_EXT_REF_CLK                   */
    EXT_CLK_TYPE,                              /*!< PFE_MAC_0_EXT_RX_CLK                    */
    EXT_CLK_TYPE,                              /*!< PFE_MAC_0_EXT_TX_CLK                    */
    EXT_CLK_TYPE,                              /*!< PFE_MAC_1_EXT_REF_CLK                   */
    EXT_CLK_TYPE,                              /*!< PFE_MAC_1_EXT_RX_CLK                    */
    EXT_CLK_TYPE,                              /*!< PFE_MAC_1_EXT_TX_CLK                    */
    EXT_CLK_TYPE,                              /*!< PFE_MAC_2_EXT_REF_CLK                   */
    EXT_CLK_TYPE,                              /*!< PFE_MAC_2_EXT_RX_CLK                    */
    EXT_CLK_TYPE,                              /*!< PFE_MAC_2_EXT_TX_CLK                    */
    SERDES_TYPE,                              /*!< SERDES_0_LANE_0_TX                      */
    SERDES_TYPE,                              /*!< SERDES_0_LANE_0_CDR                     */
    SERDES_TYPE,                              /*!< SERDES_0_LANE_1_TX                      */
    SERDES_TYPE,                              /*!< SERDES_0_LANE_1_CDR                     */
    SERDES_TYPE,                              /*!< SERDES_1_LANE_0_TX                      */
    SERDES_TYPE,                              /*!< SERDES_1_LANE_0_CDR                     */
    SERDES_TYPE,                              /*!< SERDES_1_LANE_1_TX                      */
    SERDES_TYPE,                              /*!< SERDES_1_LANE_1_CDR                     */
    UKNOWN_TYPE,                               /*!< XBAR_2X_CLK                             */
    UKNOWN_TYPE,                               /*!< XBAR_CLK                                */
    UKNOWN_TYPE,                               /*!< XBAR_DIV2_CLK                           */
    UKNOWN_TYPE,                               /*!< XBAR_DIV3_CLK                           */
    UKNOWN_TYPE,                               /*!< XBAR_DIV4_CLK                           */
    UKNOWN_TYPE,                               /*!< XBAR_DIV6_CLK                           */
    UKNOWN_TYPE,                               /*!< A53_CORE_CLK                            */
    UKNOWN_TYPE,                               /*!< A53_CORE_DIV2_CLK                       */
    UKNOWN_TYPE,                               /*!< A53_CORE_DIV10_CLK                      */
    UKNOWN_TYPE,                               /*!< DDR_CLK                                 */
    UKNOWN_TYPE,                               /*!< PFE_PE_CLK                              */
    UKNOWN_TYPE,                               /*!< PER_CLK                                 */
    UKNOWN_TYPE,                               /*!< GMAC_REF_DIV_CLK                        */
    UKNOWN_TYPE,                               /*!< PFEMAC0_REF_DIV_CLK                     */
    UKNOWN_TYPE,                               /*!< PFEMAC1_REF_DIV_CLK                     */
    UKNOWN_TYPE,                               /*!< PFEMAC2_REF_DIV_CLK                     */
    UKNOWN_TYPE,                               /*!< SERDES_REF_CLK                          */
};



/* Clock features mapping */
const uint8 clockFeatures[CLOCK_NAMES_NO][CLOCK_FEATURES_NO] =
/*   \
*****************************************************************************************************************************************************************************  \
*********************************     ********       *************               *********  DIVIDER   **** C P ******        ***********************************   *   ******  \
*********************************     ********   C   *************  INTERFACE    *********  INDEX     **** O C ******        *********************************** C * C ******  \
*********************************  I  ********   A   *************  CLOCK        *********            **** L F ******        *********************************** M * M ******  \
*********************************  N  ********   L   *************               *********  or        **** L S ****** CLK    *********************************** U * U ******  \
*********************************  S  ********   L   *************  or           *********            **** E   ****** ENABLE ***********************************   *   ******  \
*********************************  T  ********   B   *************               *********  PCTL      **** C H ****** REQ    *********************************** I * S ******  \
*********************************  A  ********   A   *************  SELECTOR     *********  INDEX     **** T W ******        *********************************** N * W ******  \
*********************************  N  ********   C   *************  INDEX        *********            **** I   ****** PCFS   *********************************** S *   ******  \
*********************************  C  ********   K   *************               *********  or        **** O I ****** SW     *********************************** T * I ******  \
*********************************  E  ********       *************  or           *********            **** N N ****** INDEX  *********************************** A * N ******  \
*********************************     ********       *************               *********  PCC       ****   D ******        *********************************** N * D ******  \
*********************************     ********       *************  PCFS         *********  INDEX     **** I E ******        *********************************** C * E ******  \
*********************************     ********       *************  INSTANCE     *********            **** D X ******        *********************************** E * X ******  \
*********************************     ********       *************               *********  PARTITION ****     ******        ***********************************   *   ******  \
*********************************     ********       *************               *********  INDEX     ****     ******        ***********************************   *   ******  \
******************************************************************************************************************************************************************************/\
{                                                                           \
/*   FIRC_CLK clock            */ {0U,       NO_CALLBACK,             0U,                      INV_VAL,    INV_VAL,     INV_VAL,                                0U,  0U},           /*   FIRC_CLK clock            */ \
/*   FXOSC_CLK clock           */ {0U,       FAST_XOSC_CMU,           0U,                      INV_VAL,    INV_VAL,     INV_VAL,                                0U,  0U},           /*   FXOSC_CLK clock           */ \
/*   SIRC_CLK clock            */ {0U,       NO_CALLBACK,             0U,                      INV_VAL,    INV_VAL,     INV_VAL,                                0U,  0U},           /*   SIRC_CLK clock            */ \
/*   COREPLL_CLK clock         */ {0U,       PLL_MOD,                 0U,                      INV_VAL,    INV_VAL,     INV_VAL,                                0U,  0U},           /*   COREPLL_CLK clock         */ \
/*   PERIPHPLL_CLK clock       */ {1U,       PLL,                     0U,                      INV_VAL,    INV_VAL,     INV_VAL,                                0U,  0U},           /*   PERIPHPLL_CLK clock       */ \
/*   DDRPLL_CLK clock          */ {2U,       PLL_MOD,                 0U,                      INV_VAL,    INV_VAL,     INV_VAL,                                0U,  0U},           /*   DDRPLL_CLK clock          */ \
/*   ACCELPLL_CLK clock        */ {3U,       PLL_MOD,                 0U,                      INV_VAL,    INV_VAL,     INV_VAL,                                0U,  0U},           /*   ACCELPLL_CLK clock        */ \
/*   COREPLL_PHI0 clock        */ {0U,       PCFS_PLL_OUT,            1U,                      0U,         3U,          PCFS_COREPLLPHI0,                       0U,  0U},           /*   COREPLL_PHI0 clock        */ \
/*   COREPLL_PHI1 clock        */ {0U,       PLL_OUT,                 0U,                      1U,         0U,          0U,                                     0U,  0U},           /*   COREPLL_PHI1 clock        */ \
/*   COREPLL_DFS1 clock        */ {0U,       PCFS_DFS,                0U,                      0U,         11U,         PCFS_COREPLLDFS1,                       0U,  0U},           /*   COREPLL_DFS1 clock        */ \
/*   COREPLL_DFS2 clock        */ {0U,       DFS,                     0U,                      1U,         0U,          0U,                                     0U,  0U},           /*   COREPLL_DFS2 clock        */ \
/*   COREPLL_DFS3 clock        */ {0U,       DFS,                     0U,                      2U,         0U,          0U,                                     0U,  0U},           /*   COREPLL_DFS3 clock        */ \
/*   COREPLL_DFS4 clock        */ {0U,       DFS,                     0U,                      3U,         0U,          0U,                                     0U,  0U},           /*   COREPLL_DFS4 clock        */ \
/*   COREPLL_DFS5 clock        */ {0U,       DFS,                     0U,                      4U,         0U,          0U,                                     0U,  0U},           /*   COREPLL_DFS5 clock        */ \
/*   COREPLL_DFS6 clock        */ {0U,       DFS,                     0U,                      5U,         0U,          0U,                                     0U,  0U},           /*   COREPLL_DFS6 clock        */ \
/*   PERIPHPLL_PHI0 clock      */ {1U,       PLL_OUT,                 0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   PERIPHPLL_PHI0 clock      */ \
/*   PERIPHPLL_PHI1 clock      */ {1U,       PLL_OUT,                 0U,                      1U,         0U,          0U,                                     0U,  0U},           /*   PERIPHPLL_PHI1 clock      */ \
/*   PERIPHPLL_PHI2 clock      */ {1U,       PLL_OUT,                 0U,                      2U,         0U,          0U,                                     0U,  0U},           /*   PERIPHPLL_PHI2 clock      */ \
/*   PERIPHPLL_PHI3 clock      */ {1U,       PLL_OUT,                 0U,                      3U,         0U,          0U,                                     0U,  0U},           /*   PERIPHPLL_PHI3 clock      */ \
/*   PERIPHPLL_PHI4 clock      */ {1U,       PLL_OUT,                 0U,                      4U,         0U,          0U,                                     0U,  0U},           /*   PERIPHPLL_PHI4 clock      */ \
/*   PERIPHPLL_PHI5 clock      */ {1U,       PLL_OUT,                 0U,                      5U,         0U,          0U,                                     0U,  0U},           /*   PERIPHPLL_PHI5 clock      */ \
/*   PERIPHPLL_PHI6 clock      */ {1U,       PLL_OUT,                 0U,                      6U,         0U,          0U,                                     0U,  0U},           /*   PERIPHPLL_PHI6 clock      */ \
/*   PERIPHPLL_PHI7 clock      */ {1U,       PLL_OUT,                 0U,                      7U,         0U,          0U,                                     0U,  0U},           /*   PERIPHPLL_PHI7 clock      */ \
/*   PERIPHPLL_DFS1 clock      */ {1U,       DFS,                     0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   PERIPHPLL_DFS1 clock      */ \
/*   PERIPHPLL_DFS2 clock      */ {1U,       DFS,                     0U,                      1U,         0U,          0U,                                     0U,  0U},           /*   PERIPHPLL_DFS2 clock      */ \
/*   PERIPHPLL_DFS3 clock      */ {1U,       DFS,                     0U,                      2U,         0U,          0U,                                     0U,  0U},           /*   PERIPHPLL_DFS3 clock      */ \
/*   PERIPHPLL_DFS4 clock      */ {1U,       DFS,                     0U,                      3U,         0U,          0U,                                     0U,  0U},           /*   PERIPHPLL_DFS4 clock      */ \
/*   PERIPHPLL_DFS5 clock      */ {1U,       DFS,                     0U,                      4U,         0U,          0U,                                     0U,  0U},           /*   PERIPHPLL_DFS5 clock      */ \
/*   PERIPHPLL_DFS6 clock      */ {1U,       DFS,                     0U,                      5U,         0U,          0U,                                     0U,  0U},           /*   PERIPHPLL_DFS6 clock      */ \
/*   DDRPLL_PHI0 clock         */ {2U,       PLL_OUT,                 0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   DDRPLL_PHI0 clock         */ \
/*   ACCELPLL_PHI0 clock       */ {3U,       PLL_OUT,                 0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   ACCELPLL_PHI0 clock       */ \
/*   ACCELPLL_PHI1 clock       */ {3U,       PCFS_PLL_OUT,            2U,                      1U,         32U,         PCFS_ACCELPLLPHI1,                      0U,  0U},           /*   ACCELPLL_PHI1 clock       */ \
/*   ftm_0_ext_ref clock       */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   ftm_0_ext_ref clock       */ \
/*   ftm_1_ext_ref clock       */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   ftm_1_ext_ref clock       */ \
/*   gmac_0_ext_ref clock      */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   gmac_0_ext_ref clock      */ \
/*   gmac_0_ext_rx clock       */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   gmac_0_ext_rx clock       */ \
/*   gmac_0_ext_tx clock       */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   gmac_0_ext_tx clock       */ \
/*   gmac_ext_ts clock         */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   gmac_ext_ts clock         */ \
/*   pfe_mac_0_ext_ref clock   */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   pfe_mac_0_ext_ref clock   */ \
/*   pfe_mac_0_ext_rx clock    */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   pfe_mac_0_ext_rx clock    */ \
/*   pfe_mac_0_ext_tx clock    */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   pfe_mac_0_ext_tx clock    */ \
/*   pfe_mac_1_ext_ref clock   */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   pfe_mac_1_ext_ref clock   */ \
/*   pfe_mac_1_ext_rx clock    */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   pfe_mac_1_ext_rx clock    */ \
/*   pfe_mac_1_ext_tx clock    */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   pfe_mac_1_ext_tx clock    */ \
/*   pfe_mac_2_ext_ref clock   */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   pfe_mac_2_ext_ref clock   */ \
/*   pfe_mac_2_ext_rx clock    */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   pfe_mac_2_ext_rx clock    */ \
/*   pfe_mac_2_ext_tx clock    */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   pfe_mac_2_ext_tx clock    */ \
/*   SERDES_0_LANE_0_TX clock  */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   SERDES_0_LANE_0_TX clock  */ \
/*   SERDES_0_LANE_0_CDR clock */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   SERDES_0_LANE_0_CDR clock */ \
/*   SERDES_0_LANE_1_TX clock  */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   SERDES_0_LANE_1_TX clock  */ \
/*   SERDES_0_LANE_1_CDR clock */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   SERDES_0_LANE_1_CDR clock */ \
/*   SERDES_1_LANE_0_TX clock  */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   SERDES_1_LANE_0_TX clock  */ \
/*   SERDES_1_LANE_0_CDR clock */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   SERDES_1_LANE_0_CDR clock */ \
/*   SERDES_1_LANE_1_TX clock  */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   SERDES_1_LANE_1_TX clock  */ \
/*   SERDES_1_LANE_1_CDR clock */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   SERDES_1_LANE_1_CDR clock */ \
/*   XBAR_2X_CLK clock         */ {0U,       HWMUX_PCFS,              0U,                      0U,         0U,          NO_TRIGGER,                             0U,  0U},           /*   XBAR_2X_CLK clock         */ \
/*   XBAR_CLK clock            */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          NO_TRIGGER,                             0U,  0U},           /*   XBAR_CLK clock            */ \
/*   XBAR_DIV2_CLK clock       */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          NO_TRIGGER,                             0U,  0U},           /*   XBAR_DIV2_CLK clock       */ \
/*   XBAR_DIV3_CLK clock       */ {0U,       CMU,                     0U,                      0U,         0U,          NO_TRIGGER,                             3U,  3U},           /*   XBAR_DIV3_CLK clock       */ \
/*   XBAR_DIV4_CLK clock       */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          NO_TRIGGER,                             0U,  0U},           /*   XBAR_DIV4_CLK clock       */ \
/*   XBAR_DIV6_CLK clock       */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          NO_TRIGGER,                             0U,  0U},           /*   XBAR_DIV6_CLK clock       */ \
/*   A53_CORE_CLK clock        */ {1U,       HWMUX_PCFS,              0U,                      0U,         0U,          NO_TRIGGER,                             0U,  0U},           /*   A53_CORE_CLK clock        */ \
/*   A53_CORE_DIV2_CLK clock   */ {1U,       NO_CALLBACK,             0U,                      0U,         0U,          NO_TRIGGER,                             0U,  0U},           /*   A53_CORE_DIV2_CLK clock   */ \
/*   A53_CORE_DIV10_CLK clock  */ {1U,       NO_CALLBACK,             0U,                      0U,         0U,          NO_TRIGGER,                             0U,  0U},           /*   A53_CORE_DIV10_CLK clock  */ \
/*   DDR_CLK clock             */ {5U,       HWMUX_CMU,               0U,                      0U,         0U,          NO_TRIGGER,                             15U, 15U},          /*   DDR_CLK clock             */ \
/*   PFE_PE_CLK clock          */ {2U,       HWMUX_PCFS_DIV_TRIGGER_CMU,0U,                    0U,         0U,          TRIGGER,                                20U, 20U},          /*   PFE_PE_CLK clock          */ \
/*   PER_CLK clock             */ {0U,       HWMUX_DIV_CMU,           3U,                      0U,         0U,          NO_TRIGGER,                             6U,  6U},           /*   PER_CLK clock             */ \
/*   GMAC_REF_DIV_CLK clock    */ {0U,       HWMUX_DIV,               15U,                     0U,         0U,          NO_TRIGGER,                             0U,  0U},           /*   GMAC_REF_DIV_CLK clock    */ \
/*   PFEMAC0_REF_DIV_CLK clock */ {2U,       HWMUX_DIV_TRIGGER,       7U,                      0U,         0U,          TRIGGER,                                0U,  0U},           /*   PFEMAC0_REF_DIV_CLK clock */ \
/*   PFEMAC1_REF_DIV_CLK clock */ {2U,       HWMUX_DIV_TRIGGER,       8U,                      0U,         0U,          TRIGGER,                                0U,  0U},           /*   PFEMAC1_REF_DIV_CLK clock */ \
/*   PFEMAC2_REF_DIV_CLK clock */ {2U,       HWMUX_DIV_TRIGGER,       9U,                      0U,         0U,          TRIGGER,                                0U,  0U},           /*   PFEMAC2_REF_DIV_CLK clock */ \
/*   SERDES_REF_CLK clock      */ {0U,       CMU,                     0U,                      0U,         0U,          NO_TRIGGER,                             7U,  7U},           /*   SERDES_REF_CLK clock      */ \
/*   THE_LAST_PRODUCER_CLK     */ {0U,       NO_CALLBACK,             0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   THE_LAST_PRODUCER_CLK     */ \
/*   ADC0_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)PER_CLK,          0U,         0U,          0U,                                     0U,  0U},           /*   ADC0_CLK clock            */ \
/*   ADC1_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)PER_CLK,          0U,         0U,          0U,                                     0U,  0U},           /*   ADC1_CLK clock            */ \
/*   CLKOUT0_CLK clock         */ {0U,       SWMUX_DIV_CLKOUT,        1U,                      0U,         0U,          NO_TRIGGER,                             0U,  0U},           /*   CLKOUT0_CLK clock         */ \
/*   CLKOUT1_CLK clock         */ {0U,       SWMUX_DIV_CLKOUT,        2U,                      0U,         0U,          NO_TRIGGER,                             0U,  0U},           /*   CLKOUT1_CLK clock         */ \
/*   CORE_A53_CLUSTER_0_CLK clock */ {0U,    CMU,                     (uint8)A53_CORE_CLK,     0U,         0U,          0U,                                     18U, 18U},          /*   CORE_A53_CLUSTER_0_CLK clock */ \
/*   CORE_A53_CLUSTER_1_CLK clock */ {0U,    CMU,                     (uint8)A53_CORE_CLK,     0U,         0U,          0U,                                     19U, 19U},          /*   CORE_A53_CLUSTER_1_CLK clock */ \
/*   CORE_M7_0_CLK clock       */ {0U,       CMU,                     (uint8)XBAR_CLK,         0U,         0U,          0U,                                     2U,  2U},           /*   CORE_M7_0_CLK clock       */ \
/*   CORE_M7_1_CLK clock       */ {0U,       CMU,                     (uint8)XBAR_CLK,         0U,         0U,          0U,                                     4U,  4U},           /*   CORE_M7_1_CLK clock       */ \
/*   CORE_M7_2_CLK clock       */ {0U,       CMU,                     (uint8)XBAR_CLK,         0U,         0U,          0U,                                     5U,  5U},           /*   CORE_M7_2_CLK clock       */ \
/*   CRC0_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   CRC0_CLK clock            */ \
/*   CTU0_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   CTU0_CLK clock            */ \
/*   CTU1_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   CTU1_CLK clock            */ \
/*   DAPB_CLK clock            */ {0U,       HWMUX_DIV,               0U,                      1U,       0U,            NO_TRIGGER,                             0U,  0U},           /*   DAPB_CLK clock            */ \
/*   DMA0_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_CLK,         0U,         0U,          0U,                                     0U,  0U},           /*   DMA0_CLK clock            */ \
/*   DMA1_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_CLK,         0U,         0U,          0U,                                     0U,  0U},           /*   DMA1_CLK clock            */ \
/*   DMAMUX0_CLK clock         */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   DMAMUX0_CLK clock         */ \
/*   DMAMUX1_CLK clock         */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   DMAMUX1_CLK clock         */ \
/*   DMAMUX2_CLK clock         */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   DMAMUX2_CLK clock         */ \
/*   DMAMUX3_CLK clock         */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   DMAMUX3_CLK clock         */ \
/*   DMA_CRC0_CLK clock        */ {0U,       NO_CALLBACK,             (uint8)XBAR_CLK,         0U,         0U,          0U,                                     0U,  0U},           /*   DMA_CRC0_CLK clock        */ \
/*   DMA_CRC1_CLK clock        */ {0U,       NO_CALLBACK,             (uint8)XBAR_CLK,         0U,         0U,          0U,                                     0U,  0U},           /*   DMA_CRC1_CLK clock        */ \
/*   EIM0_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)A53_CORE_DIV10_CLK,0U,        0U,          0U,                                     0U,  0U},           /*   EIM0_CLK clock            */ \
/*   EIM1_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV6_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   EIM1_CLK clock            */ \
/*   EIM2_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV6_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   EIM2_CLK clock            */ \
/*   EIM3_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV6_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   EIM3_CLK clock            */ \
/*   EIM_CLK clock             */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV6_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   EIM_CLK clock             */ \
/*   ERM0_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV6_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   ERM0_CLK clock            */ \
/*   FLEXCAN_CLK clock         */ {0U,       HWMUX_CMU,               7U,                      0U,         0U,          0U,                                     9U,  9U},           /*   FLEXCAN_CLK clock         */ \
/*   FLEXCAN0_CLK clock        */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   FLEXCAN0_CLK clock        */ \
/*   FLEXCAN1_CLK clock        */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   FLEXCAN1_CLK clock        */ \
/*   FLEXCAN2_CLK clock        */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   FLEXCAN2_CLK clock        */ \
/*   FLEXCAN3_CLK clock        */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   FLEXCAN3_CLK clock        */ \
/*   FLEXRAY_CLK clock         */ {0U,       HWMUX_DIV_CMU,           6U,                      0U,         0U,          0U,                                     8U,  8U},           /*   FLEXRAY_CLK clock         */ \
/*   FRAY0_CLK clock           */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   FRAY0_CLK clock           */ \
/*   FLEXTIMERA_CLK clock      */ {0U,       HWMUX_DIV,               4U,                      0U,         0U,          0U,                                     0U,  0U},           /*   FLEXTIMERA_CLK clock      */ \
/*   FTIMER0_CLK clock         */ {0U,       NO_CALLBACK,             (uint8)PER_CLK,          0U,         0U,          0U,                                     0U,  0U},           /*   FTIMER0_CLK clock         */ \
/*   FLEXTIMERB_CLK clock      */ {0U,       HWMUX_DIV,               5U,                      0U,         0U,          0U,                                     0U,  0U},           /*   FLEXTIMERB_CLK clock      */ \
/*   FTIMER1_CLK clock         */ {0U,       NO_CALLBACK,             (uint8)PER_CLK,          0U,         0U,          0U,                                     0U,  0U},           /*   FTIMER1_CLK clock         */ \
/*   GMAC_TS_CLK clock         */ {0U,       HWMUX_DIV_CMU,           9U,                      0U,         0U,          0U,                                     11U, 11U},          /*   GMAC_TS_CLK clock         */ \
/*   GMAC0_RX_CLK clock        */ {0U,       HWMUX_CMU,               11U,                     0U,         0U,          NO_TRIGGER,                             16U, 16U},          /*   GMAC0_RX_CLK clock        */ \
/*   GMAC0_TX_CLK clock        */ {0U,       HWMUX_DIV_PHASE_CMU,     10U,                     0U,         0U,          NO_TRIGGER,                             10U, 10U},          /*   GMAC0_TX_CLK clock        */ \
/*   GMAC0_TS_CLK clock        */ {0U,       GATE,                    (uint8)XBAR_CLK,         2U,       0U,            MC_ME_PRTN2_COFB0_CLKEN_REQ3_SHIFT,     0U,  0U},           /*   GMAC0_TS_CLK clock        */ \
/*   IIC0_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   IIC0_CLK clock            */ \
/*   IIC1_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   IIC1_CLK clock            */ \
/*   IIC2_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   IIC2_CLK clock            */ \
/*   IIC3_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   IIC3_CLK clock            */ \
/*   IIC4_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   IIC4_CLK clock            */ \
/*   LBIST_CLK clock           */ {0U,       HWMUX_DIV_PHASE,         0U,                      0U,         0U,          0U,                                     0U,  0U},           /*   LBIST_CLK clock           */ \
/*   LBIST0_CLK clock          */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   LBIST0_CLK clock          */ \
/*   LBIST1_CLK clock          */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   LBIST1_CLK clock          */ \
/*   LBIST2_CLK clock          */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   LBIST2_CLK clock          */ \
/*   LBIST3_CLK clock          */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   LBIST3_CLK clock          */ \
/*   LBIST4_CLK clock          */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   LBIST4_CLK clock          */ \
/*   LBIST5_CLK clock          */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   LBIST5_CLK clock          */ \
/*   LBIST6_CLK clock          */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   LBIST6_CLK clock          */ \
/*   LBIST7_CLK clock          */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   LBIST7_CLK clock          */ \
/*   LIN_CLK clock             */ {0U,       HWMUX_CMU,               8U,                      0U,         0U,          0U,                                     12U, 12U},          /*  LIN_CLK clock             */ \
/*   LIN0_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)LIN_CLK,          0U,         0U,          0U,                                     0U,  0U},           /*   LIN0_CLK clock            */ \
/*   LIN1_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)LIN_CLK,          0U,         0U,          0U,                                     0U,  0U},           /*   LIN1_CLK clock            */ \
/*   LIN2_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)LIN_CLK,          0U,         0U,          0U,                                     0U,  0U},           /*   LIN2_CLK clock            */ \
/*   OCOTP0_CLK clock          */ {0U,       NO_CALLBACK,             (uint8)FIRC_CLK,         0U,         0U,          0U,                                     0U,  0U},           /*   OCOTP0_CLK clock          */ \
/*   PFEMAC0_RX_CLK clock      */ {2U,       HWMUX_CMU,               4U,                      0U,         0U,          NO_TRIGGER,                             22U, 22U},          /*   PFEMAC0_RX_CLK clock      */ \
/*   PFEMAC0_TX_CLK clock      */ {2U,       HWMUX_DIV_PHASE_TRIGGER_CMU, 1U,                      0U,         0U,          TRIGGER,                                21U, 21U},          /*   PFEMAC0_TX_CLK clock      */ \
/*   PFEMAC1_RX_CLK clock      */ {2U,       HWMUX_CMU,               5U,                      0U,         0U,          NO_TRIGGER,                             24U, 24U},          /*   PFEMAC1_RX_CLK clock      */ \
/*   PFEMAC1_TX_CLK clock      */ {2U,       HWMUX_DIV_PHASE_TRIGGER_CMU, 2U,                      0U,         0U,          TRIGGER,                                23U, 23U},          /*   PFEMAC1_TX_CLK clock      */ \
/*   PFEMAC2_RX_CLK clock      */ {2U,       HWMUX_CMU,               6U,                      0U,         0U,          NO_TRIGGER,                             26U, 26U},          /*   PFEMAC2_RX_CLK clock      */ \
/*   PFEMAC2_TX_CLK clock      */ {2U,       HWMUX_DIV_PHASE_TRIGGER_CMU, 3U,                      0U,         0U,          TRIGGER,                                25U, 25U},          /*   PFEMAC2_TX_CLK clock      */ \
/*   PIT0_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   PIT0_CLK clock            */ \
/*   PIT1_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   PIT1_CLK clock            */ \
/*   QSPI_CLK clock            */ {0U,       HWMUX_DIV_CMU,           12U,                     0U,         0U,          0U,                                     13U, 13U},          /*   QSPI_CLK clock            */ \
/*   QSPI0_CLK clock           */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   QSPI0_CLK clock           */ \
/*   RTC0_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV6_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   RTC0_CLK clock            */ \
/*   SIUL0_CLK clock           */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   SIUL0_CLK clock           */ \
/*   SIUL1_CLK clock           */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   SIUL1_CLK clock           */ \
/*   SPI_CLK clock             */ {0U,       HWMUX_CMU,               16U,                     0U,         0U,          0U,                                     17U, 17U},          /*   SPI_CLK clock             */ \
/*   SPI0_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)SPI_CLK,          0U,         0U,          0U,                                     0U,  0U},           /*   SPI0_CLK clock            */ \
/*   SPI1_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)SPI_CLK,          0U,         0U,          0U,                                     0U,  0U},           /*   SPI1_CLK clock            */ \
/*   SPI2_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)SPI_CLK,          0U,         0U,          0U,                                     0U,  0U},           /*   SPI2_CLK clock            */ \
/*   SPI3_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)SPI_CLK,          0U,         0U,          0U,                                     0U,  0U},           /*   SPI3_CLK clock            */ \
/*   SPI4_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)SPI_CLK,          0U,         0U,          0U,                                     0U,  0U},           /*   SPI4_CLK clock            */ \
/*   SPI5_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)SPI_CLK,          0U,         0U,          0U,                                     0U,  0U},           /*   SPI5_CLK clock            */ \
/*   STM0_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   STM0_CLK clock            */ \
/*   STM1_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   STM1_CLK clock            */ \
/*   STM2_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   STM2_CLK clock            */ \
/*   STM3_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   STM3_CLK clock            */ \
/*   STM4_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   STM4_CLK clock            */ \
/*   STM5_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   STM5_CLK clock            */ \
/*   STM6_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   STM6_CLK clock            */ \
/*   STM7_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   STM7_CLK clock            */ \
/*   SWT0_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   SWT0_CLK clock            */ \
/*   SWT1_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   SWT1_CLK clock            */ \
/*   SWT2_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   SWT2_CLK clock            */ \
/*   SWT3_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   SWT3_CLK clock            */ \
/*   SWT4_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   SWT4_CLK clock            */ \
/*   SWT5_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   SWT5_CLK clock            */ \
/*   SWT6_CLK clock            */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   SWT6_CLK clock            */ \
/*   USDHC_CLK clock           */ {0U,       HWMUX_DIV_CMU,           14U,                     0U,         0U,          0U,                                     14U, 14U},          /*   USDHC_CLK clock           */ \
/*   USDHC0_CLK clock          */ {0U,       GATE,                    (uint8)XBAR_DIV3_CLK,    0U,         0U,          MC_ME_PRTN0_COFB0_CLKEN_REQ0_SHIFT,     0U,  0U},           /*   USDHC0_CLK clock          */ \
/*   WKPU0_CLK clock           */ {0U,       NO_CALLBACK,             (uint8)XBAR_DIV6_CLK,    0U,         0U,          0U,                                     0U,  0U},           /*   WKPU0_CLK clock           */ \
/*   XBAR_DIV3_FAIL_CLK clock  */ {0U,       CMU,                     (uint8)XBAR_DIV3_CLK,    0U,         0U,          0U,                                     1U,  1U},           /*   XBAR_DIV3_FAIL_CLK clock  */ \
};


/*!
 * @brief Converts a clock name to a selector entry hardware value
 */
const uint16 selectorEntry_hardwareValue[CLOCK_PRODUCERS_NO] = {
    0U,                                       /*!< FIRC_CLK                                */
    2U,                                       /*!< FXOSC_CLK                               */
    1U,                                       /*!< SIRC_CLK                                */
    0U,                                       /*!< COREPLL_CLK                             */
    0U,                                       /*!< PERIPHPLL_CLK                           */
    0U,                                       /*!< DDRPLL_CLK                              */
    0U,                                       /*!< ACCELPLL_CLK                            */
    4U,                                       /*!< CORE_PLL_PHI0_CLK                       */
    5U,                                       /*!< CORE_PLL_PHI1_CLK                       */
    12U,                                      /*!< CORE_PLL_DFS1_CLK                       */
    13U,                                      /*!< CORE_PLL_DFS2_CLK                       */
    14U,                                      /*!< CORE_PLL_DFS3_CLK                       */
    15U,                                      /*!< CORE_PLL_DFS4_CLK                       */
    16U,                                      /*!< CORE_PLL_DFS5_CLK                       */
    17U,                                      /*!< CORE_PLL_DFS6_CLK                       */
    18U,                                      /*!< PERIPH_PLL_PHI0_CLK                     */
    19U,                                      /*!< PERIPH_PLL_PHI1_CLK                     */
    20U,                                      /*!< PERIPH_PLL_PHI2_CLK                     */
    21U,                                      /*!< PERIPH_PLL_PHI3_CLK                     */
    22U,                                      /*!< PERIPH_PLL_PHI4_CLK                     */
    23U,                                      /*!< PERIPH_PLL_PHI5_CLK                     */
    24U,                                      /*!< PERIPH_PLL_PHI6_CLK                     */
    25U,                                      /*!< PERIPH_PLL_PHI7_CLK                     */
    26U,                                      /*!< PERIPH_PLL_DFS1_CLK                     */
    27U,                                      /*!< PERIPH_PLL_DFS2_CLK                     */
    28U,                                      /*!< PERIPH_PLL_DFS3_CLK                     */
    29U,                                      /*!< PERIPH_PLL_DFS4_CLK                     */
    30U,                                      /*!< PERIPH_PLL_DFS5_CLK                     */
    31U,                                      /*!< PERIPH_PLL_DFS6_CLK                     */
    36U,                                      /*!< DDR_PLL_PHI0_CLK                        */
    32U,                                      /*!< ACCEL_PLL_PHI0_CLK                      */
    33U,                                      /*!< ACCEL_PLL_PHI1_CLK                      */
    34U,                                      /*!< FTM_0_EXT_REF_CLK                       */
    35U,                                      /*!< FTM_1_EXT_REF_CLK                       */
    39U,                                      /*!< GMAC_0_EXT_REF_CLK                      */
    38U,                                      /*!< GMAC_0_EXT_RX_CLK                       */
    37U,                                      /*!< GMAC_0_EXT_TX_CLK                       */
    44U,                                      /*!< GMAC_EXT_TS_CLK                         */
    50U,                                      /*!< PFE_MAC_0_EXT_REF_CLK                   */
    49U,                                      /*!< PFE_MAC_0_EXT_RX_CLK                    */
    48U,                                      /*!< PFE_MAC_0_EXT_TX_CLK                    */
    53U,                                      /*!< PFE_MAC_1_EXT_REF_CLK                   */
    52U,                                      /*!< PFE_MAC_1_EXT_RX_CLK                    */
    51U,                                      /*!< PFE_MAC_1_EXT_TX_CLK                    */
    56U,                                      /*!< PFE_MAC_2_EXT_REF_CLK                   */
    55U,                                      /*!< PFE_MAC_2_EXT_RX_CLK                    */
    54U,                                      /*!< PFE_MAC_2_EXT_TX_CLK                    */
    40U,                                      /*!< SERDES_0_LANE_0_TX                      */
    41U,                                      /*!< SERDES_0_LANE_0_CDR                     */
    46U,                                      /*!< SERDES_0_LANE_1_TX                      */
    47U,                                      /*!< SERDES_0_LANE_1_CDR                     */
    57U,                                      /*!< SERDES_1_LANE_0_TX                      */
    58U,                                      /*!< SERDES_1_LANE_0_CDR                     */
    62U,                                      /*!< SERDES_1_LANE_1_TX                      */
    63U,                                      /*!< SERDES_1_LANE_1_CDR                     */
    0U,                                       /*!< XBAR_2X_CLK                             */
    0U,                                       /*!< XBAR_CLK                                */
    0U,                                       /*!< XBAR_DIV2_CLK                           */
    0U,                                       /*!< XBAR_DIV3_CLK                           */
    0U,                                       /*!< XBAR_DIV4_CLK                           */
    0U,                                       /*!< XBAR_DIV6_CLK                           */
    0U,                                       /*!< A53_CORE_CLK                            */
    0U,                                       /*!< A53_CORE_DIV2_CLK                       */
    0U,                                       /*!< A53_CORE_DIV10_CLK                      */
    0U,                                       /*!< DDR_CLK                                 */
    0U,                                       /*!< PFE_PE_CLK                              */
    0U,                                       /*!< PER_CLK                                 */
    45U,                                      /*!< GMAC_REF_DIV_CLK                        */
    59U,                                      /*!< PFEMAC0_REF_DIV_CLK                     */
    60U,                                      /*!< PFEMAC1_REF_DIV_CLK                     */
    61U,                                      /*!< PFEMAC2_REF_DIV_CLK                     */
    0U,                                       /*!< SERDES_REF_CLK                          */
};


/*!
 * @brief Converts hardware value of a selector entry to clock name
 */
static const Clock_Ip_NameType hardwareValue_selectorEntry[SELECTOR_HARDWARE_VALUES_NO]   = {

        FIRC_CLK,                      /* clock name for 0  hardware value */
        SIRC_CLK,                      /* clock name for 1  hardware value */
        FXOSC_CLK,                     /* clock name for 2  hardware value */
        RESERVED_CLK,                  /* clock name for 3  hardware value */
        CORE_PLL_PHI0_CLK,             /* clock name for 4  hardware value */
        CORE_PLL_PHI1_CLK,             /* clock name for 5  hardware value */
        RESERVED_CLK,                  /* clock name for 6  hardware value */
        RESERVED_CLK,                  /* clock name for 7  hardware value */
        RESERVED_CLK,                  /* clock name for 8  hardware value */
        RESERVED_CLK,                  /* clock name for 9  hardware value */
        RESERVED_CLK,                  /* clock name for 10 hardware value */
        RESERVED_CLK,                  /* clock name for 11 hardware value */
        CORE_PLL_DFS1_CLK,             /* clock name for 12 hardware value */
        CORE_PLL_DFS2_CLK,             /* clock name for 13 hardware value */
        CORE_PLL_DFS3_CLK,             /* clock name for 14 hardware value */
        CORE_PLL_DFS4_CLK,             /* clock name for 15 hardware value */
        CORE_PLL_DFS5_CLK,             /* clock name for 16 hardware value */
        CORE_PLL_DFS6_CLK,             /* clock name for 17 hardware value */
        PERIPH_PLL_PHI0_CLK,           /* clock name for 18 hardware value */
        PERIPH_PLL_PHI1_CLK,           /* clock name for 19 hardware value */
        PERIPH_PLL_PHI2_CLK,           /* clock name for 20 hardware value */
        PERIPH_PLL_PHI3_CLK,           /* clock name for 21 hardware value */
        PERIPH_PLL_PHI4_CLK,           /* clock name for 22 hardware value */
        PERIPH_PLL_PHI5_CLK,           /* clock name for 23 hardware value */
        PERIPH_PLL_PHI6_CLK,           /* clock name for 24 hardware value */
        PERIPH_PLL_PHI7_CLK,           /* clock name for 25 hardware value */
        PERIPH_PLL_DFS1_CLK,           /* clock name for 26 hardware value */
        PERIPH_PLL_DFS2_CLK,           /* clock name for 27 hardware value */
        PERIPH_PLL_DFS3_CLK,           /* clock name for 28 hardware value */
        PERIPH_PLL_DFS4_CLK,           /* clock name for 29 hardware value */
        PERIPH_PLL_DFS5_CLK,           /* clock name for 30 hardware value */
        PERIPH_PLL_DFS6_CLK,           /* clock name for 31 hardware value */
        ACCEL_PLL_PHI0_CLK,            /* clock name for 32 hardware value */
        ACCEL_PLL_PHI1_CLK,            /* clock name for 33 hardware value */
        FTM_0_EXT_REF_CLK,             /* clock name for 34 hardware value */
        FTM_1_EXT_REF_CLK,             /* clock name for 35 hardware value */
        DDR_PLL_PHI0_CLK,              /* clock name for 36 hardware value */
        GMAC_0_EXT_TX_CLK,           /* clock name for 37 hardware value */
        GMAC_0_EXT_RX_CLK,           /* clock name for 38 hardware value */
        GMAC_0_EXT_REF_CLK,              /* clock name for 39 hardware value */
        SERDES_0_LANE_0_TX,            /* clock name for 40 hardware value */
        SERDES_0_LANE_0_CDR,           /* clock name for 41 hardware value */
        RESERVED_CLK,                  /* clock name for 42 hardware value */
        RESERVED_CLK,                  /* clock name for 43 hardware value */
        GMAC_EXT_TS_CLK,           /* clock name for 44 hardware value */
        GMAC_REF_DIV_CLK,              /* clock name for 45 hardware value */
        SERDES_0_LANE_1_TX,            /* clock name for 46 hardware value */
        SERDES_0_LANE_1_CDR,           /* clock name for 47 hardware value */
        PFE_MAC_0_EXT_TX_CLK,        /* clock name for 48 hardware value */
        PFE_MAC_0_EXT_RX_CLK,        /* clock name for 49 hardware value */
        PFE_MAC_0_EXT_REF_CLK,           /* clock name for 50 hardware value */
        PFE_MAC_1_EXT_TX_CLK,        /* clock name for 51 hardware value */
        PFE_MAC_1_EXT_RX_CLK,        /* clock name for 52 hardware value */
        PFE_MAC_1_EXT_REF_CLK,           /* clock name for 53 hardware value */
        PFE_MAC_2_EXT_TX_CLK,        /* clock name for 54 hardware value */
        PFE_MAC_2_EXT_RX_CLK,        /* clock name for 55 hardware value */
        PFE_MAC_2_EXT_REF_CLK,           /* clock name for 56 hardware value */
        SERDES_1_LANE_0_TX,            /* clock name for 57 hardware value */
        SERDES_1_LANE_0_CDR,           /* clock name for 58 hardware value */
        PFEMAC0_REF_DIV_CLK,           /* clock name for 59 hardware value */
        PFEMAC1_REF_DIV_CLK,           /* clock name for 60 hardware value */
        PFEMAC2_REF_DIV_CLK,           /* clock name for 61 hardware value */
        SERDES_1_LANE_1_TX,            /* clock name for 62 hardware value */
        SERDES_1_LANE_1_CDR,           /* clock name for 63 hardware value */

};

const clock_element_state_t selectorEntryIndex[SELECTOR_HARDWARE_VALUES_NO] =
{
SELECTOR_ENTRY_1,           /* FIRC_CLK -  0  hardware value */
DISABLED_CLOCK,             /* SIRC_CLK -  1  hardware value */
DISABLED_CLOCK,             /* FXOSC_CLK -  2  hardware value */
DISABLED_CLOCK,             /* RESERVED_CLK -  3  hardware value */
SELECTOR_ENTRY_2,           /* CORE_PLL_PHI0_CLK -  4  hardware value */
DISABLED_CLOCK,             /* CORE_PLL_PHI1_CLK -  5  hardware value */
DISABLED_CLOCK,             /* RESERVED_CLK -  6  hardware value */
DISABLED_CLOCK,             /* RESERVED_CLK -  7  hardware value */
DISABLED_CLOCK,             /* RESERVED_CLK -  8  hardware value */
DISABLED_CLOCK,             /* RESERVED_CLK -  9  hardware value */
DISABLED_CLOCK,             /* RESERVED_CLK -  10 hardware value */
DISABLED_CLOCK,             /* RESERVED_CLK -  11 hardware value */
SELECTOR_ENTRY_2,           /* CORE_PLL_DFS1_CLK -  12 hardware value */
SELECTOR_ENTRY_3,           /* CORE_PLL_DFS2_CLK -  13 hardware value */
DISABLED_CLOCK,             /* CORE_PLL_DFS3_CLK -  14 hardware value */
DISABLED_CLOCK,             /* CORE_PLL_DFS4_CLK -  15 hardware value */
DISABLED_CLOCK,             /* CORE_PLL_DFS5_CLK -  16 hardware value */
DISABLED_CLOCK,             /* CORE_PLL_DFS6_CLK -  17 hardware value */
DISABLED_CLOCK,             /* PERIPH_PLL_PHI0_CLK -  18 hardware value */
SELECTOR_ENTRY_2,           /* PERIPH_PLL_PHI1_CLK -  19 hardware value */
DISABLED_CLOCK,             /* PERIPH_PLL_PHI2_CLK -  20 hardware value */
DISABLED_CLOCK,             /* PERIPH_PLL_PHI3_CLK -  21 hardware value */
DISABLED_CLOCK,             /* PERIPH_PLL_PHI4_CLK -  22 hardware value */
DISABLED_CLOCK,             /* PERIPH_PLL_PHI5_CLK -  23 hardware value */
DISABLED_CLOCK,             /* PERIPH_PLL_PHI6_CLK -  24 hardware value */
DISABLED_CLOCK,             /* PERIPH_PLL_PHI7_CLK -  25 hardware value */
DISABLED_CLOCK,             /* PERIPH_PLL_DFS1_CLK -  26 hardware value */
DISABLED_CLOCK,             /* PERIPH_PLL_DFS2_CLK -  27 hardware value */
DISABLED_CLOCK,             /* PERIPH_PLL_DFS3_CLK -  28 hardware value */
DISABLED_CLOCK,             /* PERIPH_PLL_DFS4_CLK -  29 hardware value */
DISABLED_CLOCK,             /* PERIPH_PLL_DFS5_CLK -  30 hardware value */
DISABLED_CLOCK,             /* PERIPH_PLL_DFS6_CLK -  31 hardware value */
DISABLED_CLOCK,             /* ACCEL_PLL_PHI0_CLK -  32 hardware value */
SELECTOR_ENTRY_2,           /* ACCEL_PLL_PHI1_CLK -  33 hardware value */
DISABLED_CLOCK,             /* FTM_0_EXT_REF_CLK -  34 hardware value */
DISABLED_CLOCK,             /* FTM_1_EXT_REF_CLK -  35 hardware value */
SELECTOR_ENTRY_2,           /* DDR_PLL_PHI0_CLK -  36 hardware value */
DISABLED_CLOCK,             /* GMAC_0_EXT_TX_CLK -  37 hardware value */
DISABLED_CLOCK,             /* GMAC_0_EXT_RX_CLK -  38 hardware value */
DISABLED_CLOCK,             /* GMAC_0_EXT_REF_CLK -  39 hardware value */
DISABLED_CLOCK,             /* SERDES_0_LANE_0_TX -  40 hardware value */
DISABLED_CLOCK,             /* SERDES_0_LANE_0_CDR -  41 hardware value */
DISABLED_CLOCK,             /* RESERVED_CLK -  42 hardware value */
DISABLED_CLOCK,             /* RESERVED_CLK -  43 hardware value */
DISABLED_CLOCK,             /* GMAC_EXT_TS_CLK -  44 hardware value */
DISABLED_CLOCK,             /* GMAC_REF_DIV_CLK -  45 hardware value */
DISABLED_CLOCK,             /* SERDES_0_LANE_1_TX -  46 hardware value */
DISABLED_CLOCK,             /* SERDES_0_LANE_1_CDR -  47 hardware value */
DISABLED_CLOCK,             /* PFE_MAC_0_EXT_TX_CLK -  48 hardware value */
DISABLED_CLOCK,             /* PFE_MAC_0_EXT_RX_CLK -  49 hardware value */
SELECTOR_ENTRY_2,           /* PFE_MAC_0_EXT_REF_CLK -  50 hardware value */
DISABLED_CLOCK,             /* PFE_MAC_1_EXT_TX_CLK -  51 hardware value */
DISABLED_CLOCK,             /* PFE_MAC_1_EXT_RX_CLK -  52 hardware value */
SELECTOR_ENTRY_2,           /* PFE_MAC_1_EXT_REF_CLK -  53 hardware value */
DISABLED_CLOCK,             /* PFE_MAC_2_EXT_TX_CLK -  54 hardware value */
DISABLED_CLOCK,             /* PFE_MAC_2_EXT_RX_CLK -  55 hardware value */
SELECTOR_ENTRY_2,           /* PFE_MAC_2_EXT_REF_CLK -  56 hardware value */
DISABLED_CLOCK,             /* SERDES_1_LANE_0_TX -  57 hardware value */
DISABLED_CLOCK,             /* SERDES_1_LANE_0_CDR -  58 hardware value */
DISABLED_CLOCK,             /* PFEMAC0_REF_DIV_CLK -  59 hardware value */
DISABLED_CLOCK,             /* PFEMAC1_REF_DIV_CLK -  60 hardware value */
DISABLED_CLOCK,             /* PFEMAC2_REF_DIV_CLK -  61 hardware value */
DISABLED_CLOCK,             /* SERDES_1_LANE_1_TX -  62 hardware value */
DISABLED_CLOCK,             /* SERDES_1_LANE_1_CDR -  63 hardware value */
};

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Clock_Ip_S32G2XX_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/* Clock start uninitialized shared section data */
#define MCU_START_SEC_VAR_NO_INIT_UNSPECIFIED_NO_CACHEABLE
/**
* @violates @ref Clock_Ip_S32G2XX_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

static uint32 bufferFreqs[BUFFER_FREQS_NO];
static uint8 freqPointers[CLOCK_PRODUCERS_NO + 1U];
static clock_element_state_t clkState[CLOCK_PRODUCERS_NO + 1U];

/* Clock stop uninitialized shared section data */
#define MCU_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_NO_CACHEABLE
/**
* @violates @ref Clock_Ip_S32G2XX_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/* Clock start initialized section data */
#define MCU_START_SEC_VAR_INIT_UNSPECIFIED
/**
* @violates @ref Clock_Ip_S32G2XX_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

static tCalcFreqDataType tmpData;
static const Clock_Ip_ClockConfigType *clock_config = NULL;
static uint32 configuredCoreClock = 0U;           /* Frequency of the core clock. */
static uint32 configuredPerClock = 0U;           /* Frequency of the PER clock. */
static uint32 configuredFlexRayClk = 0U;           /* Frequency of the FLEXRAY clock. */
static uint32 configuredFlexCanClk = 0U;           /* Frequency of the FLEXCAN clock. */
static uint32 configuredGmacTxClk = 0U;           /* Frequency of the GMAC0_TX clock. */
static uint32 configuredGmacTsClk = 0U;           /* Frequency of the GMAC_TS clock. */
static uint32 configuredLinClk = 0U;           /* Frequency of the LIN clock. */
static uint32 configuredQspiClk = 0U;           /* Frequency of the QSPI clock. */
static uint32 configuredUsdhcClk = 0U;           /* Frequency of the USDHC clock. */
static uint32 configuredDdrClk = 0U;           /* Frequency of the DDR_clk clock. */
static uint32 configuredGmacRxClk = 0U;           /* Frequency of the GMAC0_RX clock. */
static uint32 configuredSpiClk = 0U;           /* Frequency of the SPI clock. */
static uint32 configuredA53coreClk = 0U;           /* Frequency of the A53_CORE clock. */
static uint32 configuredPfepeClk = 0U;           /* Frequency of the PFE_PE clock. */
static uint32 configuredPfemac0txClk = 0U;           /* Frequency of the PFEMAC0_TX clock. */
static uint32 configuredPfemac0rxClk = 0U;           /* Frequency of the PFEMAC0_RX clock. */
static uint32 configuredPfemac1txClk = 0U;           /* Frequency of the PFEMAC1_TX clock. */
static uint32 configuredPfemac1rxClk = 0U;           /* Frequency of the PFEMAC1_RX clock. */
static uint32 configuredPfemac2txClk = 0U;           /* Frequency of the PFEMAC2_TX clock. */
static uint32 configuredPfemac2rxClk = 0U;           /* Frequency of the PFEMAC2_RX clock. */
static uint32 configuredGmacRefDiv = 0U;           /* Frequency of the GMAC_REF_DIV clock. */
static uint32 configuredPfemac0RefDiv = 0U;          /* Frequency of the PFEMAC0_REF_DIV clock */
static uint32 configuredPfemac1RefDiv = 0U;          /* Frequency of the PFEMAC1_REF_DIV clock */
static uint32 configuredPfemac2RefDiv = 0U;          /* Frequency of the PFEMAC2_REF_DIV clock */
pcfsEntry pcfsEntries[PCFS_ENTRIES_NO] =  {

    /* PCFS_COREPLLDFS1 */
    {
        CORE_PLL_DFS1_CLK,                        /* Name of the clock that supports pcfs (rampup-rampdown) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,   /* Pointer to pcfs configuration structure - by default is not under mcu control */
        0u,                                       /* SDUR */
        0u,                                       /* DIVC_INIT */
        0u,                                       /* DIV_RATE */
        0u,                                       /* DIV_START_VALUE */
        0u,                                       /* DIV_END_VALUE */
    },

    /* PCFS_COREPLLPHI0 */
    {
        CORE_PLL_PHI0_CLK,                        /* Name of the clock that supports pcfs (rampup-rampdown) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,   /* Pointer to pcfs configuration structure - by default is not under mcu control */
        0u,                                       /* SDUR */
        0u,                                       /* DIVC_INIT */
        0u,                                       /* DIV_RATE */
        0u,                                       /* DIV_START_VALUE */
        0u,                                       /* DIV_END_VALUE */
    },

    /* PCFS_ACCELPLLPHI1 */
    {
        ACCEL_PLL_PHI1_CLK,                       /* Name of the clock that supports pcfs (rampup-rampdown) */
        CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL,   /* Pointer to pcfs configuration structure - by default is not under mcu control */
        0u,                                       /* SDUR */
        0u,                                       /* DIVC_INIT */
        0u,                                       /* DIV_RATE */
        0u,                                       /* DIV_START_VALUE */
        0u,                                       /* DIV_END_VALUE */
    },
};

/* RECORD_CALLBACK_TIMESTAMPS must be defined when timestamp are measured. */
#ifdef RECORD_CALLBACK_TIMESTAMPS
    #define SYSTICK_MAX (0xFFFFFFu)
    uint32 timestampCallback[CALC_FREQ_CALLBACKS_NO];
    uint32 systickCounter = 0U;
    uint32 timestampIndexEntry = 0U;
#endif

/* Clock stop initialized section data */
#define MCU_STOP_SEC_VAR_INIT_UNSPECIFIED
/**
* @violates @ref Clock_Ip_S32G2XX_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"


/* Clock start section code */
#define MCU_START_SEC_CODE
/**
* @violates @ref Clock_Ip_S32G2XX_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

#ifdef FEATURE_CLOCK_IP_HAS_RAM_WAIT_STATES

static void SRAMC_SetRamIWS(void);

void SetRamWaitStates(void)
{
#ifdef CLOCK_IP_ENABLE_USER_MODE_SUPPORT
  #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_4 A function should be used in preference to a function-like macro where they are interchangeable.
    */
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_5 The comma is used  to abstract the trusted call function and to determine when the return into user mode is needed.
    */
    OsIf_Trusted_Call(SRAMC_SetRamIWS);
  #else
    SRAMC_SetRamIWS();
  #endif
#else
  SRAMC_SetRamIWS();
#endif
}
#endif

#ifdef FEATURE_CLOCK_IP_HAS_FLASH_WAIT_STATES
void SetFlashWaitStates(void)
{
    FLASH_SetFlashIWS();
}
#endif


void UpdateClockState(Clock_Ip_NameType name, clock_element_state_t state)
{
    if ( ((uint32)name) < ((uint32)THE_LAST_PRODUCER_CLK))
    {
        clkState[name] = state;
    }
}

clock_element_state_t GetClockState(Clock_Ip_NameType name)
{
    clock_element_state_t retValue;

    if ( ((uint32)name) < ((uint32)THE_LAST_PRODUCER_CLK))
    {
        retValue = clkState[name];
    }
    else
    {
        retValue = clkState[THE_LAST_PRODUCER_CLK];
    }

    return retValue;
}
void SpecificPeripheralClockInitialization(Clock_IP_SpecificPeriphConfigType const * config)
{
    (void)config;
}
void SpecificPlatformInitClock(Clock_Ip_ClockConfigType const * config)
{
    clock_config = config;
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;

    if ((dfs[0U]->CTL & DFS_CTL_DFS_RESET_MASK) != 0U)  /* if master dfs is in reset */
    {
        if ((pll[0U]->PLLCR & PLLDIG_PLLCR_PLLPD_MASK) != 0U)   /* if CORE_PLL is not enabled */
        {
            pll[0U]->PLLCLKMUX = 0U;                                                   /* FIRC input reference 48 MHz */
            pll[0U]->PLLDV = (PLLDIG_PLLDV_RDIV(1U) | PLLDIG_PLLDV_MFI(30U));          /* /1 * 30 */
            pll[0U]->PLLCR &= ~PLLDIG_PLLCR_PLLPD_MASK;                                /* Start PERIPH_PLL */
            pll[0U]->PLLFD &= ~(PLLDIG_PLLFD_MFN_MASK | PLLDIG_PLLFD_SDMEN_MASK);      /* Disable modulation */
            ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
            /* Wait until the update has finished. */
            do
            {
                TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
            }
            while((((pll[0U]->PLLSR & PLLDIG_PLLSR_LOCK_MASK) >> PLLDIG_PLLSR_LOCK_SHIFT) == 0U) && (FALSE == TimeoutOccurred));
            /* timeout notification */
            if (TRUE == TimeoutOccurred)
            {
                /* Report timeout error */
                ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, config->plls[0U].name);
            }
        }

        dfs[0U]->PORTRESET |= (DFS_PORTRESET_RESET0_MASK | DFS_PORTRESET_RESET1_MASK | DFS_PORTRESET_RESET2_MASK | DFS_PORTRESET_RESET3_MASK | DFS_PORTRESET_RESET4_MASK | DFS_PORTRESET_RESET5_MASK);
        dfs[0U]->CTL |= DFS_CTL_DFS_RESET_MASK;

        dfs[0U]->DVPORT[0U] = (DFS_DVPORT_MFN(0u) | DFS_DVPORT_MFI(1U));
        dfs[0U]->DVPORT[1U] = (DFS_DVPORT_MFN(0u) | DFS_DVPORT_MFI(1U));
        dfs[0U]->DVPORT[2U] = (DFS_DVPORT_MFN(0u) | DFS_DVPORT_MFI(1U));
        dfs[0U]->DVPORT[3U] = (DFS_DVPORT_MFN(0u) | DFS_DVPORT_MFI(1U));
        dfs[0U]->DVPORT[4U] = (DFS_DVPORT_MFN(0u) | DFS_DVPORT_MFI(1U));
        dfs[0U]->DVPORT[5U] = (DFS_DVPORT_MFN(0u) | DFS_DVPORT_MFI(1U));

        dfs[0U]->CTL &= ~DFS_CTL_DFS_RESET_MASK;
        dfs[0U]->PORTRESET &= ~((DFS_PORTRESET_RESET0_MASK | DFS_PORTRESET_RESET1_MASK | DFS_PORTRESET_RESET2_MASK | DFS_PORTRESET_RESET3_MASK | DFS_PORTRESET_RESET4_MASK | DFS_PORTRESET_RESET5_MASK));

        ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
        do
        {
            TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while((DFS_PORTSR_PORTSTAT(dfs[0U]->PORTSR) == 0U) && (FALSE == TimeoutOccurred));
        /* timeout notification */
        if (TRUE == TimeoutOccurred)
        {
            /* Report timeout error */
            ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, config->fracDivs[0U].name);
        }
    }

    if ((dfs[1U]->CTL & DFS_CTL_DFS_RESET_MASK) != 0U)  /* if master dfs is in reset */
    {
        if ((pll[1U]->PLLCR & PLLDIG_PLLCR_PLLPD_MASK) != 0U)   /* if PERIPH_PLL is not enabled */
        {
            pll[1U]->PLLCLKMUX = 0U;                                                   /* FIRC input reference 48 MHz */
            pll[1U]->PLLDV = (PLLDIG_PLLDV_RDIV(1U) | PLLDIG_PLLDV_MFI(30U));          /* /1 * 30 */
            pll[1U]->PLLCR &= ~PLLDIG_PLLCR_PLLPD_MASK;                                /* Start PERIPH_PLL */
            pll[1U]->PLLFD &= ~(PLLDIG_PLLFD_MFN_MASK | PLLDIG_PLLFD_SDMEN_MASK);      /* Disable modulation */

            ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
            do
            {
                TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
            }
            while((((pll[1U]->PLLSR & PLLDIG_PLLSR_LOCK_MASK) >> PLLDIG_PLLSR_LOCK_SHIFT) == 0U) && (FALSE == TimeoutOccurred));
            /* timeout notification */
            if (TRUE == TimeoutOccurred)
            {
                /* Report timeout error */
                ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, config->plls[1U].name);
            }
        }

        dfs[1U]->PORTRESET |= (DFS_PORTRESET_RESET0_MASK | DFS_PORTRESET_RESET1_MASK | DFS_PORTRESET_RESET2_MASK | DFS_PORTRESET_RESET3_MASK | DFS_PORTRESET_RESET4_MASK | DFS_PORTRESET_RESET5_MASK);

        dfs[1U]->DVPORT[0U] = (DFS_DVPORT_MFN(0u) | DFS_DVPORT_MFI(1U));
        dfs[1U]->DVPORT[1U] = (DFS_DVPORT_MFN(0u) | DFS_DVPORT_MFI(1U));
        dfs[1U]->DVPORT[2U] = (DFS_DVPORT_MFN(0u) | DFS_DVPORT_MFI(1U));
        dfs[1U]->DVPORT[3U] = (DFS_DVPORT_MFN(0u) | DFS_DVPORT_MFI(1U));
        dfs[1U]->DVPORT[4U] = (DFS_DVPORT_MFN(0u) | DFS_DVPORT_MFI(1U));
        dfs[1U]->DVPORT[5U] = (DFS_DVPORT_MFN(0u) | DFS_DVPORT_MFI(1U));

        dfs[1U]->CTL &= ~DFS_CTL_DFS_RESET_MASK;
        dfs[1U]->PORTRESET &= ~((DFS_PORTRESET_RESET0_MASK | DFS_PORTRESET_RESET1_MASK | DFS_PORTRESET_RESET2_MASK | DFS_PORTRESET_RESET3_MASK | DFS_PORTRESET_RESET4_MASK | DFS_PORTRESET_RESET5_MASK));

        ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, CLOCK_TIMEOUT_VALUE_US);
        do
        {
            TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
        }
        while ((DFS_PORTSR_PORTSTAT(dfs[1U]->PORTSR) == 0U) && (FALSE == TimeoutOccurred));
        /* timeout notification */
        if (TRUE == TimeoutOccurred)
        {
            /* Report timeout error */
            ReportClockErrors(CLOCK_IP_REPORT_TIMEOUT_ERROR, config->fracDivs[1U].name);
        }
    }
}

uint32 GetProducerClockFreq(Clock_Ip_NameType clockName)
{
    return bufferFreqs[freqPointers[clockName]];
}












void UpdateFrequencies(power_modes_t powerMode)
{
    static const Clock_Ip_NameType selectorEntriesXBAR_2X_CLK[3U]         = {THE_LAST_PRODUCER_CLK,FIRC_CLK,CORE_PLL_DFS1_CLK};
    static const uint8 bufferFreqEntriesXBAR_2X_CLK[3U]             = {BUFFER_NO_CLK,BUFFER_FIRC,BUFFER_COREPLLDFS1_COREPLL};
    static const uint8 bufferFreqEntriesXBAR_CLK[3U]                = {BUFFER_NO_CLK,BUFFER_XBAR_FIRC,BUFFER_XBAR_COREPLLDFS1_COREPLL};
    static const uint8 bufferFreqEntriesXBAR_DIV2_CLK[3U]           = {BUFFER_NO_CLK,BUFFER_XBARDIV2_FIRC,BUFFER_XBARDIV2_COREPLLDFS1_COREPLL};
    static const uint8 bufferFreqEntriesXBAR_DIV3_CLK[3U]           = {BUFFER_NO_CLK,BUFFER_XBARDIV3_FIRC,BUFFER_XBARDIV3_COREPLLDFS1_COREPLL};
    static const uint8 bufferFreqEntriesXBAR_DIV4_CLK[3U]           = {BUFFER_NO_CLK,BUFFER_XBARDIV4_FIRC,BUFFER_XBARDIV4_COREPLLDFS1_COREPLL};
    static const uint8 bufferFreqEntriesXBAR_DIV6_CLK[3U]           = {BUFFER_NO_CLK,BUFFER_XBARDIV6_FIRC,BUFFER_XBARDIV6_COREPLLDFS1_COREPLL};

    static const Clock_Ip_NameType selectorEntriesA53_CORE_CLK[4U]        = {THE_LAST_PRODUCER_CLK,FIRC_CLK,CORE_PLL_PHI0_CLK,CORE_PLL_DFS2_CLK};
    static const uint8 bufferFreqEntriesA53_CORE_CLK[4U]            = {BUFFER_NO_CLK,BUFFER_FIRC,BUFFER_COREPLLPHI0_COREPLL,BUFFER_COREPLLDFS2_COREPLL};
    static const uint8 bufferFreqEntriesA53_CORE_DIV2_CLK[4U]       = {BUFFER_NO_CLK,BUFFER_A53COREDIV2_FIRC,BUFFER_A53COREDIV2_COREPLLPHI0_COREPLL,BUFFER_A53COREDIV2_COREPLLDFS2_COREPLL};
    static const uint8 bufferFreqEntriesA53_CORE_DIV10_CLK[4U]      = {BUFFER_NO_CLK,BUFFER_A53COREDIV10_FIRC,BUFFER_A53COREDIV10_COREPLLPHI0_COREPLL,BUFFER_A53COREDIV10_COREPLLDFS2_COREPLL};

    static const Clock_Ip_NameType selectorEntriesDDR_CLK[3U]             = {THE_LAST_PRODUCER_CLK,FIRC_CLK,DDR_PLL_PHI0_CLK};
    static const uint8 bufferFreqEntriesDDR_CLK[3U]                 = {BUFFER_NO_CLK,BUFFER_FIRC,BUFFER_DDRPLLPHI0_DDRPLL};

    static const Clock_Ip_NameType selectorEntriesPFE_PE_CLK[3U]         = {THE_LAST_PRODUCER_CLK,FIRC_CLK, ACCEL_PLL_PHI1_CLK};
    static const uint8 bufferFreqEntriesPFE_PE_CLK[3U]             = {BUFFER_NO_CLK,BUFFER_PFEPE_FIRC, BUFFER_PFEPE_ACCELPLLPHI1_ACCELPLL};

    static const Clock_Ip_NameType selectorEntriesPER_CLK[3U]             = {THE_LAST_PRODUCER_CLK,FIRC_CLK, PERIPH_PLL_PHI1_CLK};
    static const uint8 bufferFreqEntriesPER_CLK[3U]                 = {BUFFER_NO_CLK,BUFFER_PER_FIRC, BUFFER_PER_PERIPHPLLPHI1_PERIPHPLL};

    static const Clock_Ip_NameType selectorEntriesGMAC_REF_DIV_CLK[3U]    = {THE_LAST_PRODUCER_CLK,FIRC_CLK, GMAC_0_EXT_REF_CLK};
    static const uint8 bufferFreqEntriesGMAC_REF_DIV_CLK[3U]        = {BUFFER_NO_CLK,BUFFER_GMACREFDIV_FIRC, BUFFER_GMACREFDIV_gmac0extref};

    static const Clock_Ip_NameType selectorEntriesPFEMAC0_REF_DIV_CLK[3U] = {THE_LAST_PRODUCER_CLK,FIRC_CLK, PFE_MAC_0_EXT_REF_CLK};
    static const uint8 bufferFreqEntriesPFEMAC0_REF_DIV_CLK[3U]     = {BUFFER_NO_CLK,BUFFER_PFEMAC0REFDIV_FIRC, BUFFER_PFEMAC0REFDIV_pfemac0extref};

    static const Clock_Ip_NameType selectorEntriesPFEMAC1_REF_DIV_CLK[3U] = {THE_LAST_PRODUCER_CLK,FIRC_CLK, PFE_MAC_1_EXT_REF_CLK};
    static const uint8 bufferFreqEntriesPFEMAC1_REF_DIV_CLK[3U]     = {BUFFER_NO_CLK,BUFFER_PFEMAC1REFDIV_FIRC, BUFFER_PFEMAC1REFDIV_pfemac1extref};

    static const Clock_Ip_NameType selectorEntriesPFEMAC2_REF_DIV_CLK[3U] = {THE_LAST_PRODUCER_CLK,FIRC_CLK, PFE_MAC_2_EXT_REF_CLK};
    static const uint8 bufferFreqEntriesPFEMAC2_REF_DIV_CLK[3U]     = {BUFFER_NO_CLK,BUFFER_PFEMAC2REFDIV_FIRC, BUFFER_PFEMAC2REFDIV_pfemac2extref};

    static const clock_element_state_t convertValueToClockState[256U] =
    {DISABLED_CLOCK,SELECTOR_ENTRY_1,SELECTOR_ENTRY_2,SELECTOR_ENTRY_3,SELECTOR_ENTRY_4,SELECTOR_ENTRY_5,SELECTOR_ENTRY_6,SELECTOR_ENTRY_7,SELECTOR_ENTRY_8,SELECTOR_ENTRY_9,SELECTOR_ENTRY_10,SELECTOR_ENTRY_11,SELECTOR_ENTRY_12,SELECTOR_ENTRY_13,SELECTOR_ENTRY_14,SELECTOR_ENTRY_15,SELECTOR_ENTRY_16,SELECTOR_ENTRY_17,SELECTOR_ENTRY_18,SELECTOR_ENTRY_19,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,
    DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,
    DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,
    DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,
    DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,
    DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,
    DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,
    DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,DISABLED_CLOCK,ENABLED_CLOCK};

    (void)powerMode;

    uint8 corepll    = ((uint8)clkState[COREPLL_CLK]);
    uint8 periphpll  = ((uint8)clkState[PERIPHPLL_CLK]);
    uint8 ddrpll     = ((uint8)clkState[DDRPLL_CLK]);
    uint8 accelpll   = ((uint8)clkState[ACCELPLL_CLK]);

    freqPointers[FXOSC_CLK]         = ((uint8)clkState[FXOSC_CLK]) & BUFFER_FXOSC;
    freqPointers[COREPLL_CLK]       = corepll   & BUFFER_COREPLL;
    freqPointers[PERIPHPLL_CLK]     = periphpll & BUFFER_PERIPHPLL;
    freqPointers[DDRPLL_CLK]        = ddrpll    & BUFFER_DDRPLL;
    freqPointers[ACCELPLL_CLK]      = accelpll  & BUFFER_ACCELPLL;

    clkState[CORE_PLL_PHI0_CLK]    = convertValueToClockState[((uint8)clkState[CORE_PLL_PHI0_CLK]) & corepll];
    clkState[CORE_PLL_PHI1_CLK]    = convertValueToClockState[((uint8)clkState[CORE_PLL_PHI1_CLK]) & corepll];
    clkState[PERIPH_PLL_PHI0_CLK]  = convertValueToClockState[((uint8)clkState[PERIPH_PLL_PHI0_CLK]) & periphpll];
    clkState[SERDES_REF_CLK]       = clkState[PERIPH_PLL_PHI0_CLK];
    clkState[PERIPH_PLL_PHI1_CLK]  = convertValueToClockState[((uint8)clkState[PERIPH_PLL_PHI1_CLK]) & periphpll];
    clkState[PERIPH_PLL_PHI2_CLK]  = convertValueToClockState[((uint8)clkState[PERIPH_PLL_PHI2_CLK]) & periphpll];
    clkState[PERIPH_PLL_PHI3_CLK]  = convertValueToClockState[((uint8)clkState[PERIPH_PLL_PHI3_CLK]) & periphpll];
    clkState[PERIPH_PLL_PHI4_CLK]  = convertValueToClockState[((uint8)clkState[PERIPH_PLL_PHI4_CLK]) & periphpll];
    clkState[PERIPH_PLL_PHI5_CLK]  = convertValueToClockState[((uint8)clkState[PERIPH_PLL_PHI5_CLK]) & periphpll];
    clkState[PERIPH_PLL_PHI6_CLK]  = convertValueToClockState[((uint8)clkState[PERIPH_PLL_PHI6_CLK]) & periphpll];
    clkState[PERIPH_PLL_PHI7_CLK]  = convertValueToClockState[((uint8)clkState[PERIPH_PLL_PHI7_CLK]) & periphpll];
    clkState[DDR_PLL_PHI0_CLK]     = convertValueToClockState[((uint8)clkState[DDR_PLL_PHI0_CLK]) & ddrpll];
    clkState[ACCEL_PLL_PHI0_CLK]   = convertValueToClockState[((uint8)clkState[ACCEL_PLL_PHI0_CLK]) & accelpll];
    clkState[ACCEL_PLL_PHI1_CLK]   = convertValueToClockState[((uint8)clkState[ACCEL_PLL_PHI1_CLK]) & accelpll];

    freqPointers[CORE_PLL_DFS1_CLK]  = ((uint8)clkState[CORE_PLL_DFS1_CLK]) & BUFFER_COREPLLDFS1_COREPLL;
    freqPointers[CORE_PLL_DFS2_CLK]  = ((uint8)clkState[CORE_PLL_DFS2_CLK]) & BUFFER_COREPLLDFS2_COREPLL;
    freqPointers[CORE_PLL_DFS3_CLK]  = ((uint8)clkState[CORE_PLL_DFS3_CLK]) & BUFFER_COREPLLDFS3_COREPLL;
    freqPointers[CORE_PLL_DFS4_CLK]  = ((uint8)clkState[CORE_PLL_DFS4_CLK]) & BUFFER_COREPLLDFS4_COREPLL;
    freqPointers[CORE_PLL_DFS5_CLK]  = ((uint8)clkState[CORE_PLL_DFS5_CLK]) & BUFFER_COREPLLDFS5_COREPLL;
    freqPointers[CORE_PLL_DFS6_CLK]  = ((uint8)clkState[CORE_PLL_DFS6_CLK]) & BUFFER_COREPLLDFS6_COREPLL;

    freqPointers[PERIPH_PLL_DFS1_CLK]  = ((uint8)clkState[PERIPH_PLL_DFS1_CLK]) & BUFFER_PERIPHPLLDFS1_PERIPHPLL;
    freqPointers[PERIPH_PLL_DFS2_CLK]  = ((uint8)clkState[PERIPH_PLL_DFS2_CLK]) & BUFFER_PERIPHPLLDFS2_PERIPHPLL;
    freqPointers[PERIPH_PLL_DFS3_CLK]  = ((uint8)clkState[PERIPH_PLL_DFS3_CLK]) & BUFFER_PERIPHPLLDFS3_PERIPHPLL;
    freqPointers[PERIPH_PLL_DFS4_CLK]  = ((uint8)clkState[PERIPH_PLL_DFS4_CLK]) & BUFFER_PERIPHPLLDFS4_PERIPHPLL;
    freqPointers[PERIPH_PLL_DFS5_CLK]  = ((uint8)clkState[PERIPH_PLL_DFS5_CLK]) & BUFFER_PERIPHPLLDFS5_PERIPHPLL;
    freqPointers[PERIPH_PLL_DFS6_CLK]  = ((uint8)clkState[PERIPH_PLL_DFS6_CLK]) & BUFFER_PERIPHPLLDFS6_PERIPHPLL;

    freqPointers[CORE_PLL_PHI0_CLK]    = ((uint8)clkState[CORE_PLL_PHI0_CLK]) & BUFFER_COREPLLPHI0_COREPLL;
    freqPointers[CORE_PLL_PHI1_CLK]    = ((uint8)clkState[CORE_PLL_PHI1_CLK]) & BUFFER_COREPLLPHI1_COREPLL;

    freqPointers[PERIPH_PLL_PHI0_CLK]  = ((uint8)clkState[PERIPH_PLL_PHI0_CLK]) & BUFFER_PERIPHPLLPHI0_PERIPHPLL;
    freqPointers[PERIPH_PLL_PHI1_CLK]  = ((uint8)clkState[PERIPH_PLL_PHI1_CLK]) & BUFFER_PERIPHPLLPHI1_PERIPHPLL;
    freqPointers[PERIPH_PLL_PHI2_CLK]  = ((uint8)clkState[PERIPH_PLL_PHI2_CLK]) & BUFFER_PERIPHPLLPHI2_PERIPHPLL;
    freqPointers[PERIPH_PLL_PHI3_CLK]  = ((uint8)clkState[PERIPH_PLL_PHI3_CLK]) & BUFFER_PERIPHPLLPHI3_PERIPHPLL;
    freqPointers[PERIPH_PLL_PHI4_CLK]  = ((uint8)clkState[PERIPH_PLL_PHI4_CLK]) & BUFFER_PERIPHPLLPHI4_PERIPHPLL;
    freqPointers[PERIPH_PLL_PHI5_CLK]  = ((uint8)clkState[PERIPH_PLL_PHI5_CLK]) & BUFFER_PERIPHPLLPHI5_PERIPHPLL;
    freqPointers[PERIPH_PLL_PHI6_CLK]  = ((uint8)clkState[PERIPH_PLL_PHI6_CLK]) & BUFFER_PERIPHPLLPHI6_PERIPHPLL;
    freqPointers[PERIPH_PLL_PHI7_CLK]  = ((uint8)clkState[PERIPH_PLL_PHI7_CLK]) & BUFFER_PERIPHPLLPHI7_PERIPHPLL;

    freqPointers[DDR_PLL_PHI0_CLK]     = ((uint8)clkState[DDR_PLL_PHI0_CLK]) & BUFFER_DDRPLLPHI0_DDRPLL;

    freqPointers[ACCEL_PLL_PHI0_CLK]   = ((uint8)clkState[ACCEL_PLL_PHI0_CLK]) & BUFFER_ACCELPLLPHI0_ACCELPLL;
    freqPointers[ACCEL_PLL_PHI1_CLK]   = ((uint8)clkState[ACCEL_PLL_PHI1_CLK]) & BUFFER_ACCELPLLPHI1_ACCELPLL;

    freqPointers[XBAR_2X_CLK]          = ((uint8)clkState[selectorEntriesXBAR_2X_CLK[clkState[XBAR_2X_CLK]]]) & bufferFreqEntriesXBAR_2X_CLK[clkState[XBAR_2X_CLK]];
    freqPointers[XBAR_CLK]             = ((uint8)clkState[selectorEntriesXBAR_2X_CLK[clkState[XBAR_2X_CLK]]]) & bufferFreqEntriesXBAR_CLK[clkState[XBAR_2X_CLK]];
    freqPointers[XBAR_DIV2_CLK]        = ((uint8)clkState[selectorEntriesXBAR_2X_CLK[clkState[XBAR_2X_CLK]]]) & bufferFreqEntriesXBAR_DIV2_CLK[clkState[XBAR_2X_CLK]];
    freqPointers[XBAR_DIV3_CLK]        = ((uint8)clkState[selectorEntriesXBAR_2X_CLK[clkState[XBAR_2X_CLK]]]) & bufferFreqEntriesXBAR_DIV3_CLK[clkState[XBAR_2X_CLK]];
    freqPointers[XBAR_DIV4_CLK]        = ((uint8)clkState[selectorEntriesXBAR_2X_CLK[clkState[XBAR_2X_CLK]]]) & bufferFreqEntriesXBAR_DIV4_CLK[clkState[XBAR_2X_CLK]];
    freqPointers[XBAR_DIV6_CLK]        = ((uint8)clkState[selectorEntriesXBAR_2X_CLK[clkState[XBAR_2X_CLK]]]) & bufferFreqEntriesXBAR_DIV6_CLK[clkState[XBAR_2X_CLK]];
    freqPointers[A53_CORE_CLK]         = ((uint8)clkState[selectorEntriesA53_CORE_CLK[clkState[A53_CORE_CLK]]]) & bufferFreqEntriesA53_CORE_CLK[clkState[A53_CORE_CLK]];
    freqPointers[A53_CORE_DIV2_CLK]    = ((uint8)clkState[selectorEntriesA53_CORE_CLK[clkState[A53_CORE_CLK]]]) & bufferFreqEntriesA53_CORE_DIV2_CLK[clkState[A53_CORE_CLK]];
    freqPointers[A53_CORE_DIV10_CLK]   = ((uint8)clkState[selectorEntriesA53_CORE_CLK[clkState[A53_CORE_CLK]]]) & bufferFreqEntriesA53_CORE_DIV10_CLK[clkState[A53_CORE_CLK]];
    freqPointers[DDR_CLK]              = ((uint8)clkState[selectorEntriesDDR_CLK[clkState[DDR_CLK]]]) & bufferFreqEntriesDDR_CLK[clkState[DDR_CLK]];
    freqPointers[PFE_PE_CLK]          = ((uint8)clkState[selectorEntriesPFE_PE_CLK[clkState[PFE_PE_CLK]]]) & bufferFreqEntriesPFE_PE_CLK[clkState[PFE_PE_CLK]];
    freqPointers[PER_CLK]              = ((uint8)clkState[selectorEntriesPER_CLK[clkState[PER_CLK]]]) & bufferFreqEntriesPER_CLK[clkState[PER_CLK]];
    freqPointers[GMAC_REF_DIV_CLK]     = ((uint8)clkState[selectorEntriesGMAC_REF_DIV_CLK[clkState[GMAC_REF_DIV_CLK]]]) & bufferFreqEntriesGMAC_REF_DIV_CLK[clkState[GMAC_REF_DIV_CLK]];
    freqPointers[PFEMAC0_REF_DIV_CLK]  = ((uint8)clkState[selectorEntriesPFEMAC0_REF_DIV_CLK[clkState[PFEMAC0_REF_DIV_CLK]]]) & bufferFreqEntriesPFEMAC0_REF_DIV_CLK[clkState[PFEMAC0_REF_DIV_CLK]];
    freqPointers[PFEMAC1_REF_DIV_CLK]  = ((uint8)clkState[selectorEntriesPFEMAC1_REF_DIV_CLK[clkState[PFEMAC1_REF_DIV_CLK]]]) & bufferFreqEntriesPFEMAC1_REF_DIV_CLK[clkState[PFEMAC1_REF_DIV_CLK]];
    freqPointers[PFEMAC2_REF_DIV_CLK]  = ((uint8)clkState[selectorEntriesPFEMAC2_REF_DIV_CLK[clkState[PFEMAC2_REF_DIV_CLK]]]) & bufferFreqEntriesPFEMAC2_REF_DIV_CLK[clkState[PFEMAC2_REF_DIV_CLK]];
}



static uint32 get_ADC0_CLK_Frequency(void);
static uint32 get_ADC1_CLK_Frequency(void);
static uint32 get_CLKOUT0_CLK_Frequency(void);
static uint32 get_CLKOUT1_CLK_Frequency(void);
static uint32 get_CORE_A53_CLUSTER_0_CLK_Frequency(void);
static uint32 get_CORE_A53_CLUSTER_1_CLK_Frequency(void);
static uint32 get_CORE_M7_0_CLK_Frequency(void);
static uint32 get_CORE_M7_1_CLK_Frequency(void);
static uint32 get_CORE_M7_2_CLK_Frequency(void);
static uint32 get_CRC0_CLK_Frequency(void);
static uint32 get_CTU0_CLK_Frequency(void);
static uint32 get_CTU1_CLK_Frequency(void);
static uint32 get_DAPB_CLK_Frequency(void);
static uint32 get_DMA0_CLK_Frequency(void);
static uint32 get_DMA1_CLK_Frequency(void);
static uint32 get_DMAMUX0_CLK_Frequency(void);
static uint32 get_DMAMUX1_CLK_Frequency(void);
static uint32 get_DMAMUX2_CLK_Frequency(void);
static uint32 get_DMAMUX3_CLK_Frequency(void);
static uint32 get_DMA_CRC0_CLK_Frequency(void);
static uint32 get_DMA_CRC1_CLK_Frequency(void);
static uint32 get_EIM0_CLK_Frequency(void);
static uint32 get_EIM1_CLK_Frequency(void);
static uint32 get_EIM2_CLK_Frequency(void);
static uint32 get_EIM3_CLK_Frequency(void);
static uint32 get_EIM_CLK_Frequency(void);
static uint32 get_ERM0_CLK_Frequency(void);
static uint32 get_FLEXCAN_CLK_Frequency(void);
static uint32 get_FLEXCAN0_CLK_Frequency(void);
static uint32 get_FLEXCAN1_CLK_Frequency(void);
static uint32 get_FLEXCAN2_CLK_Frequency(void);
static uint32 get_FLEXCAN3_CLK_Frequency(void);
static uint32 get_FLEXRAY_CLK_Frequency(void);
static uint32 get_FRAY0_CLK_Frequency(void);
static uint32 get_FLEXTIMERA_CLK_Frequency(void);
static uint32 get_FTIMER0_CLK_Frequency(void);
static uint32 get_FLEXTIMERB_CLK_Frequency(void);
static uint32 get_FTIMER1_CLK_Frequency(void);
static uint32 get_GMAC0_RX_CLK_Frequency(void);
static uint32 get_GMAC_TS_CLK_Frequency(void);
static uint32 get_GMAC0_TS_CLK_Frequency(void);
static uint32 get_GMAC0_TX_CLK_Frequency(void);
static uint32 get_IIC0_CLK_Frequency(void);
static uint32 get_IIC1_CLK_Frequency(void);
static uint32 get_IIC2_CLK_Frequency(void);
static uint32 get_IIC3_CLK_Frequency(void);
static uint32 get_IIC4_CLK_Frequency(void);
static uint32 get_LBIST_CLK_Frequency(void);
static uint32 get_LBIST0_CLK_Frequency(void);
static uint32 get_LBIST1_CLK_Frequency(void);
static uint32 get_LBIST2_CLK_Frequency(void);
static uint32 get_LBIST3_CLK_Frequency(void);
static uint32 get_LBIST4_CLK_Frequency(void);
static uint32 get_LBIST5_CLK_Frequency(void);
static uint32 get_LBIST6_CLK_Frequency(void);
static uint32 get_LBIST7_CLK_Frequency(void);
static uint32 get_LIN_CLK_Frequency(void);
static uint32 get_LIN0_CLK_Frequency(void);
static uint32 get_LIN1_CLK_Frequency(void);
static uint32 get_LIN2_CLK_Frequency(void);
static uint32 get_OCOTP0_CLK_Frequency(void);
static uint32 get_PFEMAC0_RX_CLK_Frequency(void);
static uint32 get_PFEMAC0_TX_CLK_Frequency(void);
static uint32 get_PFEMAC1_RX_CLK_Frequency(void);
static uint32 get_PFEMAC1_TX_CLK_Frequency(void);
static uint32 get_PFEMAC2_RX_CLK_Frequency(void);
static uint32 get_PFEMAC2_TX_CLK_Frequency(void);
static uint32 get_PIT0_CLK_Frequency(void);
static uint32 get_PIT1_CLK_Frequency(void);
static uint32 get_QSPI_CLK_Frequency(void);
static uint32 get_QSPI0_CLK_Frequency(void);
static uint32 get_RTC0_CLK_Frequency(void);
static uint32 get_SIUL0_CLK_Frequency(void);
static uint32 get_SIUL1_CLK_Frequency(void);
static uint32 get_SPI_CLK_Frequency(void);
static uint32 get_SPI0_CLK_Frequency(void);
static uint32 get_SPI1_CLK_Frequency(void);
static uint32 get_SPI2_CLK_Frequency(void);
static uint32 get_SPI3_CLK_Frequency(void);
static uint32 get_SPI4_CLK_Frequency(void);
static uint32 get_SPI5_CLK_Frequency(void);
static uint32 get_STM0_CLK_Frequency(void);
static uint32 get_STM1_CLK_Frequency(void);
static uint32 get_STM2_CLK_Frequency(void);
static uint32 get_STM3_CLK_Frequency(void);
static uint32 get_STM4_CLK_Frequency(void);
static uint32 get_STM5_CLK_Frequency(void);
static uint32 get_STM6_CLK_Frequency(void);
static uint32 get_STM7_CLK_Frequency(void);
static uint32 get_SWT0_CLK_Frequency(void);
static uint32 get_SWT1_CLK_Frequency(void);
static uint32 get_SWT2_CLK_Frequency(void);
static uint32 get_SWT3_CLK_Frequency(void);
static uint32 get_SWT4_CLK_Frequency(void);
static uint32 get_SWT5_CLK_Frequency(void);
static uint32 get_SWT6_CLK_Frequency(void);
static uint32 get_USDHC_CLK_Frequency(void);
static uint32 get_USDHC0_CLK_Frequency(void);
static uint32 get_WKPU0_CLK_Frequency(void);
static uint32 get_XBAR_DIV3_FAIL_CLK_Frequency(void);

static void CONFIG_ELEMENTS_MAPPINGS_01(void)
{
    uint8 i;

#ifdef RECORD_CALLBACK_TIMESTAMPS
    S32_SysTick->CSR = S32_SysTick_CSR_ENABLE(0u);
    S32_SysTick->RVR = S32_SysTick_RVR_RELOAD(SYSTICK_MAX);
    S32_SysTick->CVR = S32_SysTick_CVR_CURRENT(0U);
    S32_SysTick->CSR = S32_SysTick_CSR_ENABLE(1u) | S32_SysTick_CSR_TICKINT(0u) | S32_SysTick_CSR_CLKSOURCE(1u);
#endif

    for (i = 0U; i <= ((uint8)THE_LAST_PRODUCER_CLK); i++)
    {
        freqPointers[i] = CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL;
    }

    for (i = 0U; i < clock_config->ircoscsCount; i++)
    {
        freqPointers[clock_config->ircoscs[i].name] = i+1U;
    }

    for (i = 0U; i < clock_config->xoscsCount; i++)
    {
        freqPointers[clock_config->xoscs[i].name] = i+1U;
    }

    for (i = 0U; i < clock_config->pllsCount; i++)
    {
        freqPointers[clock_config->plls[i].name] = i+1U;
    }

    for (i = 0U; i < clock_config->extClksCount; i++)
    {
        freqPointers[clock_config->extClks[i].name] = i+1U;
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void CONFIG_ELEMENTS_MAPPINGS_02(void)
{
    uint8 i,j;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (((uint8)clock_config->selectors[i].name) < ((uint8)THE_LAST_PRODUCER_CLK))
        {
            freqPointers[clock_config->selectors[i].name] = i+1U;
        }
    }

    for (i = 0U; i < clock_config->dividersCount; i++)
    {
        if (((uint8)clock_config->dividers[i].name) < ((uint8)THE_LAST_PRODUCER_CLK))
        {
            freqPointers[clock_config->dividers[i].name] = i+1U;
        }
    }

    for (i = 0U; i < clock_config->fracDivsCount; i++)
    {
        if (((uint8)clock_config->fracDivs[i].name) < ((uint8)THE_LAST_PRODUCER_CLK))
        {
            freqPointers[clock_config->fracDivs[i].name] = i+1U;
        }
    }

    for (i = 0U; i < clock_config->pcfsCount; i++)
    {
        for (j = 0U; j < PCFS_ENTRIES_NO; j++)
        {
            if (pcfsEntries[j].name == clock_config->pcfs[i].name)
            {
                pcfsEntries[j].configIndex = i+1U;
            }
        }
    }

    for (i = 0U; i < clock_config->cmusCount; i++)
    {
        for (j = 0U; j < CMU_ENTRIES_NO; j++)
        {
            if (cmuEntries[j].name == clock_config->cmus[i].name)
            {
                cmuEntries[j].configIndex = i+1U;
            }
        }
    }
}

static void NOT_UNDER_MCU_CONTROL_A(void)
{
        clkState[FIRC_CLK]                  = ENABLED_CLOCK;
    if (freqPointers[FXOSC_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[FXOSC_CLK]                 = (((xosc[0U]->STAT & FXOSC_STAT_OSC_STAT_MASK) >> FXOSC_STAT_OSC_STAT_SHIFT) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
        clkState[SIRC_CLK]                  = ENABLED_CLOCK;
    if (freqPointers[COREPLL_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[COREPLL_CLK]               = (((pll[0U]->PLLSR & PLLDIG_PLLSR_LOCK_MASK) >> PLLDIG_PLLSR_LOCK_SHIFT) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[PERIPHPLL_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[PERIPHPLL_CLK]             = (((pll[1U]->PLLSR & PLLDIG_PLLSR_LOCK_MASK) >> PLLDIG_PLLSR_LOCK_SHIFT) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[DDRPLL_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[DDRPLL_CLK]                = (((pll[2U]->PLLSR & PLLDIG_PLLSR_LOCK_MASK) >> PLLDIG_PLLSR_LOCK_SHIFT) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[ACCELPLL_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[ACCELPLL_CLK]              = (((pll[3U]->PLLSR & PLLDIG_PLLSR_LOCK_MASK) >> PLLDIG_PLLSR_LOCK_SHIFT) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[CORE_PLL_PHI0_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[CORE_PLL_PHI0_CLK]         = (((pll[0U]->PLLODIV[0U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[CORE_PLL_PHI1_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[CORE_PLL_PHI1_CLK]         = (((pll[0U]->PLLODIV[1U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[CORE_PLL_DFS1_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[CORE_PLL_DFS1_CLK]         = ((((dfs[0U]->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & 1U) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[CORE_PLL_DFS2_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[CORE_PLL_DFS2_CLK]         = ((((dfs[0U]->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & 2U) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
}

static void NOT_UNDER_MCU_CONTROL_B(void)
{
    if (freqPointers[CORE_PLL_DFS3_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[CORE_PLL_DFS3_CLK]         = ((((dfs[0U]->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & 4U) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[CORE_PLL_DFS4_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[CORE_PLL_DFS4_CLK]         = ((((dfs[0U]->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & 8U) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[CORE_PLL_DFS5_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[CORE_PLL_DFS5_CLK]         = ((((dfs[0U]->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & 16U) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[CORE_PLL_DFS6_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[CORE_PLL_DFS6_CLK]         = ((((dfs[0U]->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & 32U) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[PERIPH_PLL_PHI0_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[PERIPH_PLL_PHI0_CLK]       = (((pll[1U]->PLLODIV[0U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
}
static void NOT_UNDER_MCU_CONTROL_C(void)
{
    if (freqPointers[PERIPH_PLL_PHI1_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[PERIPH_PLL_PHI1_CLK]       = (((pll[1U]->PLLODIV[1U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[PERIPH_PLL_PHI2_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[PERIPH_PLL_PHI2_CLK]       = (((pll[1U]->PLLODIV[2U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[PERIPH_PLL_PHI3_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[PERIPH_PLL_PHI3_CLK]       = (((pll[1U]->PLLODIV[3U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[PERIPH_PLL_PHI4_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[PERIPH_PLL_PHI4_CLK]       = (((pll[1U]->PLLODIV[4U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[PERIPH_PLL_PHI5_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[PERIPH_PLL_PHI5_CLK]       = (((pll[1U]->PLLODIV[5U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
}
static void NOT_UNDER_MCU_CONTROL_D(void)
{
    if (freqPointers[PERIPH_PLL_PHI6_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[PERIPH_PLL_PHI6_CLK]       = (((pll[1U]->PLLODIV[6U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[PERIPH_PLL_PHI7_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[PERIPH_PLL_PHI7_CLK]       = (((pll[1U]->PLLODIV[7U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[PERIPH_PLL_DFS1_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[PERIPH_PLL_DFS1_CLK]       = ((((dfs[1U]->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & 1U) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[PERIPH_PLL_DFS2_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[PERIPH_PLL_DFS2_CLK]       = ((((dfs[1U]->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & 2U) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[PERIPH_PLL_DFS3_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[PERIPH_PLL_DFS3_CLK]       = ((((dfs[1U]->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & 4U) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[PERIPH_PLL_DFS4_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[PERIPH_PLL_DFS4_CLK]       = ((((dfs[1U]->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & 8U) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
}
static void NOT_UNDER_MCU_CONTROL_E(void)
{
    if (freqPointers[PERIPH_PLL_DFS5_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[PERIPH_PLL_DFS5_CLK]       = ((((dfs[1U]->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & 16U) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[PERIPH_PLL_DFS6_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[PERIPH_PLL_DFS6_CLK]       = ((((dfs[1U]->PORTSR >> DFS_PORTSR_PORTSTAT_SHIFT) & DFS_PORTSR_PORTSTAT_MASK) & 32U) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[DDR_PLL_PHI0_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[DDR_PLL_PHI0_CLK]          = (((pll[2U]->PLLODIV[0U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[ACCEL_PLL_PHI0_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[ACCEL_PLL_PHI0_CLK]        = (((pll[3U]->PLLODIV[0U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
    if (freqPointers[ACCEL_PLL_PHI1_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[ACCEL_PLL_PHI1_CLK]        = (((pll[3U]->PLLODIV[1U] & PLLDIG_PLLODIV_DE_MASK) >> PLLDIG_PLLODIV_DE_SHIFT) == 0U) ? DISABLED_CLOCK : ENABLED_CLOCK;
    }
}

static void NOT_UNDER_MCU_CONTROL_F(void)
{
    clkState[SERDES_0_LANE_0_TX]        = ENABLED_CLOCK;
    clkState[SERDES_0_LANE_0_CDR]       = ENABLED_CLOCK;
    clkState[SERDES_0_LANE_1_TX]        = ENABLED_CLOCK;
    clkState[SERDES_0_LANE_1_CDR]       = ENABLED_CLOCK;
    clkState[SERDES_1_LANE_0_TX]        = ENABLED_CLOCK;
    clkState[SERDES_1_LANE_0_CDR]       = ENABLED_CLOCK;
    clkState[SERDES_1_LANE_1_TX]        = ENABLED_CLOCK;
    clkState[SERDES_1_LANE_1_CDR]       = ENABLED_CLOCK;
    clkState[FTM_0_EXT_REF_CLK]         = ENABLED_CLOCK;
    clkState[FTM_1_EXT_REF_CLK]         = ENABLED_CLOCK;
    clkState[GMAC_0_EXT_REF_CLK]          = ENABLED_CLOCK;
    clkState[GMAC_0_EXT_RX_CLK]       = ENABLED_CLOCK;
    clkState[GMAC_0_EXT_TX_CLK]       = ENABLED_CLOCK;
    clkState[GMAC_EXT_TS_CLK]       = ENABLED_CLOCK;
    clkState[PFE_MAC_0_EXT_REF_CLK]       = ENABLED_CLOCK;
    clkState[PFE_MAC_0_EXT_RX_CLK]    = ENABLED_CLOCK;
    clkState[PFE_MAC_0_EXT_TX_CLK]    = ENABLED_CLOCK;
    clkState[PFE_MAC_1_EXT_REF_CLK]       = ENABLED_CLOCK;
    clkState[PFE_MAC_1_EXT_RX_CLK]    = ENABLED_CLOCK;
    clkState[PFE_MAC_1_EXT_TX_CLK]    = ENABLED_CLOCK;
    clkState[PFE_MAC_2_EXT_REF_CLK]       = ENABLED_CLOCK;
    clkState[PFE_MAC_2_EXT_RX_CLK]    = ENABLED_CLOCK;
    clkState[PFE_MAC_2_EXT_TX_CLK]    = ENABLED_CLOCK;
    if (freqPointers[XBAR_2X_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[XBAR_2X_CLK]               = selectorEntryIndex[(cgm[0U][0U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT];
        clkState[XBAR_CLK]                  = clkState[XBAR_2X_CLK];
        clkState[XBAR_DIV2_CLK]             = clkState[XBAR_2X_CLK];
        clkState[XBAR_DIV3_CLK]             = clkState[XBAR_2X_CLK];
        clkState[XBAR_DIV4_CLK]             = clkState[XBAR_2X_CLK];
        clkState[XBAR_DIV6_CLK]             = clkState[XBAR_2X_CLK];
    }
    if (freqPointers[A53_CORE_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[A53_CORE_CLK]              = selectorEntryIndex[(cgm[1U][0U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT];
        clkState[A53_CORE_DIV2_CLK]         = clkState[A53_CORE_CLK];
        clkState[A53_CORE_DIV10_CLK]        = clkState[A53_CORE_CLK];
    }
    if (freqPointers[DDR_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        clkState[DDR_CLK]                   = selectorEntryIndex[(cgm[1U][0U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT];
    }
}

static void NOT_UNDER_MCU_CONTROL_G(void)
{
    if (freqPointers[PFE_PE_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        if ((cgm[1U][0U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) == 0U)
        {
            clkState[PFE_PE_CLK] = DISABLED_CLOCK;
        }
        else
        {
            clkState[PFE_PE_CLK]               = selectorEntryIndex[(cgm[2U][0U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT];
        }
    }
    if (freqPointers[PER_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        if ((cgm[0U][3U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) == 0U)
        {
            clkState[PER_CLK] = DISABLED_CLOCK;
        }
        else
        {
            clkState[PER_CLK]               = selectorEntryIndex[(cgm[0U][3U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT];
        }
    }
    if (freqPointers[GMAC_REF_DIV_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        if ((cgm[0U][15U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) == 0U)
        {
            clkState[GMAC_REF_DIV_CLK] = DISABLED_CLOCK;
        }
        else
        {
            clkState[GMAC_REF_DIV_CLK]               = selectorEntryIndex[(cgm[0U][15U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT];
        }
    }
    if (freqPointers[PFEMAC0_REF_DIV_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        if ((cgm[2U][7U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) == 0U)
        {
            clkState[PFEMAC0_REF_DIV_CLK] = DISABLED_CLOCK;
        }
        else
        {
            clkState[PFEMAC0_REF_DIV_CLK]               = selectorEntryIndex[(cgm[2U][7U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT];
        }
    }
    if (freqPointers[PFEMAC1_REF_DIV_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        if ((cgm[2U][8U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) == 0U)
        {
            clkState[PFEMAC1_REF_DIV_CLK] = DISABLED_CLOCK;
        }
        else
        {
            clkState[PFEMAC0_REF_DIV_CLK]               = selectorEntryIndex[(cgm[2U][8U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT];
        }
    }
    if (freqPointers[PFEMAC2_REF_DIV_CLK] == CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        if ((cgm[2U][9U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) == 0U)
        {
            clkState[PFEMAC2_REF_DIV_CLK] = DISABLED_CLOCK;
        }
        else
        {
            clkState[PFEMAC0_REF_DIV_CLK]               = selectorEntryIndex[(cgm[2U][9U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT];
        }
    }
    clkState[THE_LAST_PRODUCER_CLK]    = DISABLED_CLOCK;
}



static void IRCOSCS_XOSCS_SERDES_CLOCKS(void)
{
    const Clock_Ip_XoscConfigType *xoscConfig;
    if (freqPointers[FXOSC_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        xoscConfig = &clock_config->xoscs[freqPointers[FXOSC_CLK] - 1U];
        bufferFreqs[BUFFER_FXOSC]           = xoscConfig->freq;
    }
    else
    {
        bufferFreqs[BUFFER_FXOSC] = 40000000U;
    }

    bufferFreqs[BUFFER_SIRC]                = 32000U;
    bufferFreqs[BUFFER_FIRC]                = 48000000U;

    freqPointers[FIRC_CLK]                      = BUFFER_FIRC;
    freqPointers[SIRC_CLK]                      = BUFFER_SIRC;

    bufferFreqs[BUFFER_SERDES0LANE0TX]      = (freqPointers[SERDES_0_LANE_0_TX] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[SERDES_0_LANE_0_TX] - 1U].value : 0U;
    freqPointers[SERDES_0_LANE_0_TX]            = BUFFER_SERDES0LANE0TX;
    bufferFreqs[BUFFER_SERDES0LANE0CDR]     = (freqPointers[SERDES_0_LANE_0_CDR] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[SERDES_0_LANE_0_CDR] - 1U].value : 0U;
    freqPointers[SERDES_0_LANE_0_CDR]           = BUFFER_SERDES0LANE0CDR;
    bufferFreqs[BUFFER_SERDES0LANE1TX]      = (freqPointers[SERDES_0_LANE_1_TX] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[SERDES_0_LANE_1_TX] - 1U].value : 0U;
    freqPointers[SERDES_0_LANE_1_TX]            = BUFFER_SERDES0LANE1TX;
    bufferFreqs[BUFFER_SERDES0LANE1CDR]     = (freqPointers[SERDES_0_LANE_1_CDR] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[SERDES_0_LANE_1_CDR] - 1U].value : 0U;
    freqPointers[SERDES_0_LANE_1_CDR]           = BUFFER_SERDES0LANE1CDR;
    bufferFreqs[BUFFER_SERDES1LANE0TX]      = (freqPointers[SERDES_1_LANE_0_TX] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[SERDES_1_LANE_0_TX] - 1U].value : 0U;
    freqPointers[SERDES_1_LANE_0_TX]            = BUFFER_SERDES1LANE0TX;
    bufferFreqs[BUFFER_SERDES1LANE0CDR]     = (freqPointers[SERDES_1_LANE_0_CDR] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[SERDES_1_LANE_0_CDR] - 1U].value : 0U;
    freqPointers[SERDES_1_LANE_0_CDR]           = BUFFER_SERDES1LANE0CDR;
    bufferFreqs[BUFFER_SERDES1LANE1TX]      = (freqPointers[SERDES_1_LANE_1_TX] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[SERDES_1_LANE_1_TX] - 1U].value : 0U;
    freqPointers[SERDES_1_LANE_1_TX]            = BUFFER_SERDES1LANE1TX;
    bufferFreqs[BUFFER_SERDES1LANE1CDR]     = (freqPointers[SERDES_1_LANE_1_CDR] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[SERDES_1_LANE_1_CDR] - 1U].value : 0U;
    freqPointers[SERDES_1_LANE_1_CDR]           = BUFFER_SERDES1LANE1CDR;

}

static void EXTERNAL_CLOCKS(void)
{
    bufferFreqs[BUFFER_ftm0extref]       = (freqPointers[FTM_0_EXT_REF_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[FTM_0_EXT_REF_CLK] - 1U].value : 0U;
    freqPointers[FTM_0_EXT_REF_CLK]             = BUFFER_ftm0extref;
    bufferFreqs[BUFFER_ftm1extref]       = (freqPointers[FTM_1_EXT_REF_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[FTM_1_EXT_REF_CLK] - 1U].value : 0U;
    freqPointers[FTM_1_EXT_REF_CLK]             = BUFFER_ftm1extref;
    bufferFreqs[BUFFER_gmac0extref]        = (freqPointers[GMAC_0_EXT_REF_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[GMAC_0_EXT_REF_CLK] - 1U].value : 0U;
    freqPointers[GMAC_0_EXT_REF_CLK]              = BUFFER_gmac0extref;
    bufferFreqs[BUFFER_gmac0extrx]     = (freqPointers[GMAC_0_EXT_RX_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[GMAC_0_EXT_RX_CLK] - 1U].value : 0U;
    freqPointers[GMAC_0_EXT_RX_CLK]           = BUFFER_gmac0extrx;
    bufferFreqs[BUFFER_gmac0exttx]     = (freqPointers[GMAC_0_EXT_TX_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[GMAC_0_EXT_TX_CLK] - 1U].value : 0U;
    freqPointers[GMAC_0_EXT_TX_CLK]           = BUFFER_gmac0exttx;
    bufferFreqs[BUFFER_gmacextts]     = (freqPointers[GMAC_EXT_TS_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[GMAC_EXT_TS_CLK] - 1U].value : 0U;
    freqPointers[GMAC_EXT_TS_CLK]           = BUFFER_gmacextts;
    bufferFreqs[BUFFER_pfemac0extref]     = (freqPointers[PFE_MAC_0_EXT_REF_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[PFE_MAC_0_EXT_REF_CLK] - 1U].value : 0U;
    freqPointers[PFE_MAC_0_EXT_REF_CLK]           = BUFFER_pfemac0extref;
    bufferFreqs[BUFFER_pfemac0extrx]  = (freqPointers[PFE_MAC_0_EXT_RX_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[PFE_MAC_0_EXT_RX_CLK] - 1U].value : 0U;
    freqPointers[PFE_MAC_0_EXT_RX_CLK]        = BUFFER_pfemac0extrx;
    bufferFreqs[BUFFER_pfemac0exttx]  = (freqPointers[PFE_MAC_0_EXT_TX_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[PFE_MAC_0_EXT_TX_CLK] - 1U].value : 0U;
    freqPointers[PFE_MAC_0_EXT_TX_CLK]        = BUFFER_pfemac0exttx;
    bufferFreqs[BUFFER_pfemac1extref]     = (freqPointers[PFE_MAC_1_EXT_REF_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[PFE_MAC_1_EXT_REF_CLK] - 1U].value : 0U;
    freqPointers[PFE_MAC_1_EXT_REF_CLK]           = BUFFER_pfemac1extref;
    bufferFreqs[BUFFER_pfemac1extrx]  = (freqPointers[PFE_MAC_1_EXT_RX_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[PFE_MAC_1_EXT_RX_CLK] - 1U].value : 0U;
    freqPointers[PFE_MAC_1_EXT_RX_CLK]        = BUFFER_pfemac1extrx;
    bufferFreqs[BUFFER_pfemac1exttx]  = (freqPointers[PFE_MAC_1_EXT_TX_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[PFE_MAC_1_EXT_TX_CLK] - 1U].value : 0U;
    freqPointers[PFE_MAC_1_EXT_TX_CLK]        = BUFFER_pfemac1exttx;
    bufferFreqs[BUFFER_pfemac2extref]     = (freqPointers[PFE_MAC_2_EXT_REF_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[PFE_MAC_2_EXT_REF_CLK] - 1U].value : 0U;
    freqPointers[PFE_MAC_2_EXT_REF_CLK]           = BUFFER_pfemac2extref;
    bufferFreqs[BUFFER_pfemac2extrx]  = (freqPointers[PFE_MAC_2_EXT_RX_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[PFE_MAC_2_EXT_RX_CLK] - 1U].value : 0U;
    freqPointers[PFE_MAC_2_EXT_RX_CLK]        = BUFFER_pfemac2extrx;
    bufferFreqs[BUFFER_pfemac2exttx]  = (freqPointers[PFE_MAC_2_EXT_TX_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL) ? clock_config->extClks[freqPointers[PFE_MAC_2_EXT_TX_CLK] - 1U].value : 0U;
    freqPointers[PFE_MAC_2_EXT_TX_CLK]        = BUFFER_pfemac2exttx;
}

static void COREPLL_A(void)
{
    const Clock_Ip_PllConfigType *pllConfig;
    if (freqPointers[COREPLL_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        pllConfig = &clock_config->plls[freqPointers[COREPLL_CLK] - 1U];
        switch(pllConfig->inputReference)
        {
            case FIRC_CLK:
                tmpData.input1 = bufferFreqs[BUFFER_FIRC];                   /* fin */
                break;
            case FXOSC_CLK:
                tmpData.input1 = bufferFreqs[BUFFER_FXOSC];                  /* fin */
                break;
            default:
                tmpData.input1 = 0U;
                break;
        }
        tmpData.input2 = pllConfig->predivider;              /* rdiv */
        tmpData.input3 = pllConfig->mulFactorDiv;            /* mfi */
        tmpData.input4 = pllConfig->numeratorFracLoopDiv;    /* mfn */
    }
    else
    {
        switch((pll[0U]->PLLCLKMUX & PLLDIG_PLLCLKMUX_REFCLKSEL_MASK) >> PLLDIG_PLLCLKMUX_REFCLKSEL_SHIFT)
        {
            case 0U:
                tmpData.input1 = bufferFreqs[BUFFER_FIRC];                   /* fin */
                break;
            case 1U:
                tmpData.input1 = bufferFreqs[BUFFER_FXOSC];                  /* fin */
                break;
            default:
                tmpData.input1 = 0U;
                break;
        }
        tmpData.input2 = ((pll[0U]->PLLDV & PLLDIG_PLLDV_RDIV_MASK) >> PLLDIG_PLLDV_RDIV_SHIFT);              /* rdiv */
        tmpData.input3 = ((pll[0U]->PLLDV & PLLDIG_PLLDV_MFI_MASK) >> PLLDIG_PLLDV_MFI_SHIFT);                /* mfi */
        tmpData.input4 = ((pll[0U]->PLLFD & PLLDIG_PLLFD_MFN_MASK) >> PLLDIG_PLLFD_MFN_SHIFT);                /* mfn */
    }

    tmpData.aux1 = tmpData.input3 / tmpData.input2;                              /* mfi divided by rdiv */
    tmpData.aux2 = tmpData.input3 - (tmpData.aux1 * tmpData.input2);             /* mfi minus aux1 multiplied by rdiv */
}

static void COREPLL_B(void)
{
    tmpData.aux3 = (tmpData.input2 << 14U) + (tmpData.input2 << 11U);            /* rdiv multiplied by 18432 */
    tmpData.aux4 = tmpData.input1 / tmpData.aux3;                                /* fin divide by (rdiv multiplied by 18432) */
    tmpData.aux5 = tmpData.input1 - (tmpData.aux4 * tmpData.aux3);               /* fin minus aux4 multiplied by (rdiv mul 18432) */
    tmpData.output = tmpData.aux1 * tmpData.input1;                              /* aux1 multipied by fin */
}

static void COREPLL_C(void)
{
    tmpData.output += tmpData.input1 / tmpData.input2 * tmpData.aux2;            /* fin divided by rdiv and multiplied by aux2 */
    tmpData.output += tmpData.aux4 * tmpData.input4;                             /* mfn multiplied by aux4 */
    tmpData.output += tmpData.aux5 * tmpData.input4 / tmpData.aux3;              /* aux5 multiplied by mfn and divide by (rdiv mul 18432) */
    bufferFreqs[BUFFER_COREPLL] = tmpData.output;

}

static void PERIPHPLL_A(void)
{
    const Clock_Ip_PllConfigType *pllConfig;
    if (freqPointers[PERIPHPLL_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        pllConfig = &clock_config->plls[freqPointers[PERIPHPLL_CLK] - 1U];
        switch(pllConfig->inputReference)
        {
            case FIRC_CLK:
                tmpData.input1 = bufferFreqs[BUFFER_FIRC];                   /* fin */
                break;
            case FXOSC_CLK:
                tmpData.input1 = bufferFreqs[BUFFER_FXOSC];                  /* fin */
                break;
            default:
                tmpData.input1 = 0U;
                break;
        }
        tmpData.input2 = pllConfig->predivider;              /* rdiv */
        tmpData.input3 = pllConfig->mulFactorDiv;            /* mfi */
        tmpData.input4 = pllConfig->numeratorFracLoopDiv;    /* mfn */
    }
    else
    {
        switch((pll[1U]->PLLCLKMUX & PLLDIG_PLLCLKMUX_REFCLKSEL_MASK) >> PLLDIG_PLLCLKMUX_REFCLKSEL_SHIFT)
        {
            case 0U:
                tmpData.input1 = bufferFreqs[BUFFER_FIRC];                   /* fin */
                break;
            case 1U:
                tmpData.input1 = bufferFreqs[BUFFER_FXOSC];                  /* fin */
                break;
            default:
                tmpData.input1 = 0U;
                break;
        }
        tmpData.input2 = ((pll[1U]->PLLDV & PLLDIG_PLLDV_RDIV_MASK) >> PLLDIG_PLLDV_RDIV_SHIFT);              /* rdiv */
        tmpData.input3 = ((pll[1U]->PLLDV & PLLDIG_PLLDV_MFI_MASK) >> PLLDIG_PLLDV_MFI_SHIFT);                /* mfi */
        tmpData.input4 = ((pll[1U]->PLLFD & PLLDIG_PLLFD_MFN_MASK) >> PLLDIG_PLLFD_MFN_SHIFT);                /* mfn */
    }

    tmpData.aux1 = tmpData.input3 / tmpData.input2;                              /* mfi divided by rdiv */
    tmpData.aux2 = tmpData.input3 - (tmpData.aux1 * tmpData.input2);             /* mfi minus aux1 multiplied by rdiv */
}

static void PERIPHPLL_B(void)
{
    tmpData.aux3 = (tmpData.input2 << 14U) + (tmpData.input2 << 11U);            /* rdiv multiplied by 18432 */
    tmpData.aux4 = tmpData.input1 / tmpData.aux3;                                /* fin divide by (rdiv multiplied by 18432) */
    tmpData.aux5 = tmpData.input1 - (tmpData.aux4 * tmpData.aux3);               /* fin minus aux4 multiplied by (rdiv mul 18432) */
    tmpData.output = tmpData.aux1 * tmpData.input1;                              /* aux1 multipied by fin */
}

static void PERIPHPLL_C(void)
{
    tmpData.output += tmpData.input1 / tmpData.input2 * tmpData.aux2;            /* fin divided by rdiv and multiplied by aux2 */
    tmpData.output += tmpData.aux4 * tmpData.input4;                             /* mfn multiplied by aux4 */
    tmpData.output += tmpData.aux5 * tmpData.input4 / tmpData.aux3;              /* aux5 multiplied by mfn and divide by (rdiv mul 18432) */
    bufferFreqs[BUFFER_PERIPHPLL] = tmpData.output;
}

static void DDRPLL_A(void)
{
    const Clock_Ip_PllConfigType *pllConfig;
    if (freqPointers[DDRPLL_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        pllConfig = &clock_config->plls[freqPointers[DDRPLL_CLK] - 1U];
        switch(pllConfig->inputReference)
        {
            case FIRC_CLK:
                tmpData.input1 = bufferFreqs[BUFFER_FIRC];                   /* fin */
                break;
            case FXOSC_CLK:
                tmpData.input1 = bufferFreqs[BUFFER_FXOSC];                  /* fin */
                break;
            default:
                tmpData.input1 = 0U;
                break;
        }
        tmpData.input2 = pllConfig->predivider;              /* rdiv */
        tmpData.input3 = pllConfig->mulFactorDiv;            /* mfi */
        tmpData.input4 = pllConfig->numeratorFracLoopDiv;    /* mfn */
    }
    else
    {
        switch((pll[2U]->PLLCLKMUX & PLLDIG_PLLCLKMUX_REFCLKSEL_MASK) >> PLLDIG_PLLCLKMUX_REFCLKSEL_SHIFT)
        {
            case 0U:
                tmpData.input1 = bufferFreqs[BUFFER_FIRC];                   /* fin */
                break;
            case 1U:
                tmpData.input1 = bufferFreqs[BUFFER_FXOSC];                  /* fin */
                break;
            default:
                tmpData.input1 = 0U;
                break;
        }
        tmpData.input2 = ((pll[2U]->PLLDV & PLLDIG_PLLDV_RDIV_MASK) >> PLLDIG_PLLDV_RDIV_SHIFT);              /* rdiv */
        tmpData.input3 = ((pll[2U]->PLLDV & PLLDIG_PLLDV_MFI_MASK) >> PLLDIG_PLLDV_MFI_SHIFT);                /* mfi */
        tmpData.input4 = ((pll[2U]->PLLFD & PLLDIG_PLLFD_MFN_MASK) >> PLLDIG_PLLFD_MFN_SHIFT);                /* mfn */
    }

    tmpData.aux1 = tmpData.input3 / tmpData.input2;                              /* mfi divided by rdiv */
    tmpData.aux2 = tmpData.input3 - (tmpData.aux1 * tmpData.input2);             /* mfi minus aux1 multiplied by rdiv */
}

static void DDRPLL_B(void)
{
    tmpData.aux3 = (tmpData.input2 << 14U) + (tmpData.input2 << 11U);            /* rdiv multiplied by 18432 */
    tmpData.aux4 = tmpData.input1 / tmpData.aux3;                                /* fin divide by (rdiv multiplied by 18432) */
    tmpData.aux5 = tmpData.input1 - (tmpData.aux4 * tmpData.aux3);               /* fin minus aux4 multiplied by (rdiv mul 18432) */
    tmpData.output = tmpData.aux1 * tmpData.input1;                              /* aux1 multipied by fin */
}

static void DDRPLL_C(void)
{
    tmpData.output += tmpData.input1 / tmpData.input2 * tmpData.aux2;            /* fin divided by rdiv and multiplied by aux2 */
    tmpData.output += tmpData.aux4 * tmpData.input4;                             /* mfn multiplied by aux4 */
    tmpData.output += tmpData.aux5 * tmpData.input4 / tmpData.aux3;              /* aux5 multiplied by mfn and divide by (rdiv mul 18432) */
    bufferFreqs[BUFFER_DDRPLL] = tmpData.output;
}

static void ACCELPLL_A(void)
{
    const Clock_Ip_PllConfigType *pllConfig;
    if (freqPointers[ACCELPLL_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        pllConfig = &clock_config->plls[freqPointers[ACCELPLL_CLK] - 1U];
        switch(pllConfig->inputReference)
        {
            case FIRC_CLK:
                tmpData.input1 = bufferFreqs[BUFFER_FIRC];                   /* fin */
                break;
            case FXOSC_CLK:
                tmpData.input1 = bufferFreqs[BUFFER_FXOSC];                  /* fin */
                break;
            default:
                tmpData.input1 = 0U;
                break;
        }
        tmpData.input2 = pllConfig->predivider;              /* rdiv */
        tmpData.input3 = pllConfig->mulFactorDiv;            /* mfi */
        tmpData.input4 = pllConfig->numeratorFracLoopDiv;    /* mfn */
    }
    else
    {
        switch((pll[3U]->PLLCLKMUX & PLLDIG_PLLCLKMUX_REFCLKSEL_MASK) >> PLLDIG_PLLCLKMUX_REFCLKSEL_SHIFT)
        {
            case 0U:
                tmpData.input1 = bufferFreqs[BUFFER_FIRC];                   /* fin */
                break;
            case 1U:
                tmpData.input1 = bufferFreqs[BUFFER_FXOSC];                  /* fin */
                break;
            default:
                tmpData.input1 = 0U;
                break;
        }
        tmpData.input2 = ((pll[3U]->PLLDV & PLLDIG_PLLDV_RDIV_MASK) >> PLLDIG_PLLDV_RDIV_SHIFT);              /* rdiv */
        tmpData.input3 = ((pll[3U]->PLLDV & PLLDIG_PLLDV_MFI_MASK) >> PLLDIG_PLLDV_MFI_SHIFT);                /* mfi */
        tmpData.input4 = ((pll[3U]->PLLFD & PLLDIG_PLLFD_MFN_MASK) >> PLLDIG_PLLFD_MFN_SHIFT);                /* mfn */
    }

    tmpData.aux1 = tmpData.input3 / tmpData.input2;                              /* mfi divided by rdiv */
    tmpData.aux2 = tmpData.input3 - (tmpData.aux1 * tmpData.input2);             /* mfi minus aux1 multiplied by rdiv */
}

static void ACCELPLL_B(void)
{
    tmpData.aux3 = (tmpData.input2 << 14U) + (tmpData.input2 << 11U);            /* rdiv multiplied by 18432 */
    tmpData.aux4 = tmpData.input1 / tmpData.aux3;                                /* fin divide by (rdiv multiplied by 18432) */
    tmpData.aux5 = tmpData.input1 - (tmpData.aux4 * tmpData.aux3);               /* fin minus aux4 multiplied by (rdiv mul 18432) */
    tmpData.output = tmpData.aux1 * tmpData.input1;                              /* aux1 multipied by fin */
}

static void ACCELPLL_C(void)
{
    tmpData.output += tmpData.input1 / tmpData.input2 * tmpData.aux2;            /* fin divided by rdiv and multiplied by aux2 */
    tmpData.output += tmpData.aux4 * tmpData.input4;                             /* mfn multiplied by aux4 */
    tmpData.output += tmpData.aux5 * tmpData.input4 / tmpData.aux3;              /* aux5 multiplied by mfn and divide by (rdiv mul 18432) */
    bufferFreqs[BUFFER_ACCELPLL] = tmpData.output;
}

static void COREDFS1_A(void)
{
    const Clock_Ip_FracDivConfigType *dfsConfig;

    if (freqPointers[CORE_PLL_DFS1_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dfsConfig = &clock_config->fracDivs[freqPointers[CORE_PLL_DFS1_CLK] - 1U];
        tmpData.input2 = dfsConfig->value[0U];              /* mfi */
        tmpData.input3 = dfsConfig->value[1U];              /* mfn */
    }
    else
    {
        tmpData.input2 = ((dfs[0U]->DVPORT[0U] & DFS_DVPORT_MFI_MASK) >> DFS_DVPORT_MFI_SHIFT);              /* mfi */
        tmpData.input3 = ((dfs[0U]->DVPORT[0U] & DFS_DVPORT_MFN_MASK) >> DFS_DVPORT_MFN_SHIFT);              /* mfn */
    }

    tmpData.input1 = bufferFreqs[BUFFER_COREPLL];   /* fin */
    tmpData.aux1 = ((tmpData.input2 << 5U) + (tmpData.input2 << 2U) + tmpData.input3);           /* mfi multiplied by 36 add mfn */
    tmpData.aux2 = (tmpData.aux1 != 0U) ? (tmpData.input1 / tmpData.aux1) : 0U;                  /* fin divide by aux1 */
}

static void COREDFS1_B(void)
{
    tmpData.aux3 = tmpData.input1 - (tmpData.aux1 * tmpData.aux2);                                                           /* fin minus aux2 multiplied by aux1 */
    tmpData.output = (tmpData.aux1 != 0U) ? ((tmpData.aux2 << 4U) + (tmpData.aux2 << 1U) + (((tmpData.aux3 << 4U) + (tmpData.aux3 << 1U)) / tmpData.aux1)) : 0U;   /* aux2 multiplied by 18 added aux3 multiplied by 18 divide by aux1 */
    bufferFreqs[BUFFER_COREPLLDFS1_COREPLL] = tmpData.output;
}

static void CALCULATE_CONFIGURED_CORE_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selectorXBAR_2X_CLK = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (XBAR_2X_CLK == clock_config->selectors[i].name)
        {
            selectorXBAR_2X_CLK = &clock_config->selectors[i];
            break;
        }
    }
    /* get core frequency according each selector */
    if (selectorXBAR_2X_CLK != NULL)
    {
        switch(selectorXBAR_2X_CLK->value)
        {
            case FIRC_CLK:
            {
                configuredCoreClock = bufferFreqs[BUFFER_FIRC] >> 1U;
            }
            break;
            case CORE_PLL_DFS1_CLK:
            {
                configuredCoreClock = bufferFreqs[BUFFER_COREPLLDFS1_COREPLL] >> 1U;
            }
            break;
            default:
            {
                configuredCoreClock = 0U;
            }
            break;
        }
    }
    else
    {
        configuredCoreClock = 0U;
    }
    /* Fix warning compiler: unused variable configuredCoreClock */
    (void)configuredCoreClock;
}


static void COREDFS2_A(void)
{
    const Clock_Ip_FracDivConfigType *dfsConfig;

    if (freqPointers[CORE_PLL_DFS2_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dfsConfig = &clock_config->fracDivs[freqPointers[CORE_PLL_DFS2_CLK] - 1U];
        tmpData.input2 = dfsConfig->value[0U];              /* mfi */
        tmpData.input3 = dfsConfig->value[1U];              /* mfn */
    }
    else
    {
        tmpData.input2 = ((dfs[0U]->DVPORT[1U] & DFS_DVPORT_MFI_MASK) >> DFS_DVPORT_MFI_SHIFT);              /* mfi */
        tmpData.input3 = ((dfs[0U]->DVPORT[1U] & DFS_DVPORT_MFN_MASK) >> DFS_DVPORT_MFN_SHIFT);              /* mfn */
    }

    tmpData.input1 = bufferFreqs[BUFFER_COREPLL];   /* fin */

    tmpData.aux1 = ((tmpData.input2 << 5U) + (tmpData.input2 << 2U) + tmpData.input3);           /* mfi multiplied by 36 add mfn */
    tmpData.aux2 = (tmpData.aux1 != 0U) ? (tmpData.input1 / tmpData.aux1) : 0U;                  /* fin divide by aux1 */
}

static void COREDFS2_B(void)
{
    tmpData.aux3 = tmpData.input1 - (tmpData.aux1 * tmpData.aux2);                                                           /* fin minus aux2 multiplied by aux1 */
    tmpData.output = (tmpData.aux1 != 0U) ? ((tmpData.aux2 << 4U) + (tmpData.aux2 << 1U) + (((tmpData.aux3 << 4U) + (tmpData.aux3 << 1U)) / tmpData.aux1)) : 0U;   /* aux2 multiplied by 18 added aux3 multiplied by 18 divide by aux1 */
    bufferFreqs[BUFFER_COREPLLDFS2_COREPLL] = tmpData.output;
}

static void COREDFS3_A(void)
{
    const Clock_Ip_FracDivConfigType *dfsConfig;

    if (freqPointers[CORE_PLL_DFS3_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dfsConfig = &clock_config->fracDivs[freqPointers[CORE_PLL_DFS3_CLK] - 1U];
        tmpData.input2 = dfsConfig->value[0U];              /* mfi */
        tmpData.input3 = dfsConfig->value[1U];              /* mfn */
    }
    else
    {
        tmpData.input2 = ((dfs[0U]->DVPORT[2U] & DFS_DVPORT_MFI_MASK) >> DFS_DVPORT_MFI_SHIFT);              /* mfi */
        tmpData.input3 = ((dfs[0U]->DVPORT[2U] & DFS_DVPORT_MFN_MASK) >> DFS_DVPORT_MFN_SHIFT);              /* mfn */
    }

    tmpData.input1 = bufferFreqs[BUFFER_COREPLL];   /* fin */

    tmpData.aux1 = ((tmpData.input2 << 5U) + (tmpData.input2 << 2U) + tmpData.input3);           /* mfi multiplied by 36 add mfn */
    tmpData.aux2 = (tmpData.aux1 != 0U) ? (tmpData.input1 / tmpData.aux1) : 0U;                  /* fin divide by aux1 */
}

static void COREDFS3_B(void)
{
    tmpData.aux3 = tmpData.input1 - (tmpData.aux1 * tmpData.aux2);                                                           /* fin minus aux2 multiplied by aux1 */
    tmpData.output = (tmpData.aux1 != 0U) ? ((tmpData.aux2 << 4U) + (tmpData.aux2 << 1U) + (((tmpData.aux3 << 4U) + (tmpData.aux3 << 1U)) / tmpData.aux1)) : 0U;   /* aux2 multiplied by 18 added aux3 multiplied by 18 divide by aux1 */
    bufferFreqs[BUFFER_COREPLLDFS3_COREPLL] = tmpData.output;
}


static void COREDFS4_A(void)
{
    const Clock_Ip_FracDivConfigType *dfsConfig;

    if (freqPointers[CORE_PLL_DFS4_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dfsConfig = &clock_config->fracDivs[freqPointers[CORE_PLL_DFS4_CLK] - 1U];
        tmpData.input2 = dfsConfig->value[0U];              /* mfi */
        tmpData.input3 = dfsConfig->value[1U];              /* mfn */
    }
    else
    {
        tmpData.input2 = ((dfs[0U]->DVPORT[3U] & DFS_DVPORT_MFI_MASK) >> DFS_DVPORT_MFI_SHIFT);              /* mfi */
        tmpData.input3 = ((dfs[0U]->DVPORT[3U] & DFS_DVPORT_MFN_MASK) >> DFS_DVPORT_MFN_SHIFT);              /* mfn */
    }

    tmpData.input1 = bufferFreqs[BUFFER_COREPLL];   /* fin */

    tmpData.aux1 = ((tmpData.input2 << 5U) + (tmpData.input2 << 2U) + tmpData.input3);           /* mfi multiplied by 36 add mfn */
    tmpData.aux2 = (tmpData.aux1 != 0U) ? (tmpData.input1 / tmpData.aux1) : 0U;                  /* fin divide by aux1 */
}

static void COREDFS4_B(void)
{
    tmpData.aux3 = tmpData.input1 - (tmpData.aux1 * tmpData.aux2);                                                           /* fin minus aux2 multiplied by aux1 */
    tmpData.output = (tmpData.aux1 != 0U) ? ((tmpData.aux2 << 4U) + (tmpData.aux2 << 1U) + (((tmpData.aux3 << 4U) + (tmpData.aux3 << 1U)) / tmpData.aux1)) : 0U;   /* aux2 multiplied by 18 added aux3 multiplied by 18 divide by aux1 */
    bufferFreqs[BUFFER_COREPLLDFS4_COREPLL] = tmpData.output;
}

static void COREDFS5_A(void)
{
    const Clock_Ip_FracDivConfigType *dfsConfig;

    if (freqPointers[CORE_PLL_DFS5_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dfsConfig = &clock_config->fracDivs[freqPointers[CORE_PLL_DFS5_CLK] - 1U];
        tmpData.input2 = dfsConfig->value[0U];              /* mfi */
        tmpData.input3 = dfsConfig->value[1U];              /* mfn */
    }
    else
    {
        tmpData.input2 = ((dfs[0U]->DVPORT[4U] & DFS_DVPORT_MFI_MASK) >> DFS_DVPORT_MFI_SHIFT);              /* mfi */
        tmpData.input3 = ((dfs[0U]->DVPORT[4U] & DFS_DVPORT_MFN_MASK) >> DFS_DVPORT_MFN_SHIFT);              /* mfn */
    }

    tmpData.input1 = bufferFreqs[BUFFER_COREPLL];   /* fin */

    tmpData.aux1 = ((tmpData.input2 << 5U) + (tmpData.input2 << 2U) + tmpData.input3);           /* mfi multiplied by 36 add mfn */
    tmpData.aux2 = (tmpData.aux1 != 0U) ? (tmpData.input1 / tmpData.aux1) : 0U;                  /* fin divide by aux1 */
}

static void COREDFS5_B(void)
{
    tmpData.aux3 = tmpData.input1 - (tmpData.aux1 * tmpData.aux2);                                                           /* fin minus aux2 multiplied by aux1 */
    tmpData.output = (tmpData.aux1 != 0U) ? ((tmpData.aux2 << 4U) + (tmpData.aux2 << 1U) + (((tmpData.aux3 << 4U) + (tmpData.aux3 << 1U)) / tmpData.aux1)) : 0U;   /* aux2 multiplied by 18 added aux3 multiplied by 18 divide by aux1 */
    bufferFreqs[BUFFER_COREPLLDFS5_COREPLL] = tmpData.output;
}

static void COREDFS6_A(void)
{
    const Clock_Ip_FracDivConfigType *dfsConfig;

    if (freqPointers[CORE_PLL_DFS6_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dfsConfig = &clock_config->fracDivs[freqPointers[CORE_PLL_DFS6_CLK] - 1U];
        tmpData.input2 = dfsConfig->value[0U];              /* mfi */
        tmpData.input3 = dfsConfig->value[1U];              /* mfn */
    }
    else
    {
        tmpData.input2 = ((dfs[0U]->DVPORT[5U] & DFS_DVPORT_MFI_MASK) >> DFS_DVPORT_MFI_SHIFT);              /* mfi */
        tmpData.input3 = ((dfs[0U]->DVPORT[5U] & DFS_DVPORT_MFN_MASK) >> DFS_DVPORT_MFN_SHIFT);              /* mfn */
    }

    tmpData.input1 = bufferFreqs[BUFFER_COREPLL];   /* fin */

    tmpData.aux1 = ((tmpData.input2 << 5U) + (tmpData.input2 << 2U) + tmpData.input3);           /* mfi multiplied by 36 add mfn */
    tmpData.aux2 = (tmpData.aux1 != 0U) ? (tmpData.input1 / tmpData.aux1) : 0U;                  /* fin divide by aux1 */
}

static void COREDFS6_B(void)
{
    tmpData.aux3 = tmpData.input1 - (tmpData.aux1 * tmpData.aux2);                                                           /* fin minus aux2 multiplied by aux1 */
    tmpData.output = (tmpData.aux1 != 0U) ? ((tmpData.aux2 << 4U) + (tmpData.aux2 << 1U) + (((tmpData.aux3 << 4U) + (tmpData.aux3 << 1U)) / tmpData.aux1)) : 0U;   /* aux2 multiplied by 18 added aux3 multiplied by 18 divide by aux1 */
    bufferFreqs[BUFFER_COREPLLDFS6_COREPLL] = tmpData.output;
}

static void PERIPHDFS1_A(void)
{
    const Clock_Ip_FracDivConfigType *dfsConfig;

    if (freqPointers[PERIPH_PLL_DFS1_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dfsConfig = &clock_config->fracDivs[freqPointers[PERIPH_PLL_DFS1_CLK] - 1U];
        tmpData.input2 = dfsConfig->value[0U];              /* mfi */
        tmpData.input3 = dfsConfig->value[1U];              /* mfn */
    }
    else
    {
        tmpData.input2 = ((dfs[1U]->DVPORT[0U] & DFS_DVPORT_MFI_MASK) >> DFS_DVPORT_MFI_SHIFT);              /* mfi */
        tmpData.input3 = ((dfs[1U]->DVPORT[0U] & DFS_DVPORT_MFN_MASK) >> DFS_DVPORT_MFN_SHIFT);              /* mfn */
    }

    tmpData.input1 = bufferFreqs[BUFFER_PERIPHPLL];   /* fin */

    tmpData.aux1 = ((tmpData.input2 << 5U) + (tmpData.input2 << 2U) + tmpData.input3);           /* mfi multiplied by 36 add mfn */
    tmpData.aux2 = (tmpData.aux1 != 0U) ? (tmpData.input1 / tmpData.aux1) : 0U;                  /* fin divide by aux1 */
}

static void PERIPHDFS1_B(void)
{
    tmpData.aux3 = tmpData.input1 - (tmpData.aux1 * tmpData.aux2);                                                           /* fin minus aux2 multiplied by aux1 */
    tmpData.output = (tmpData.aux1 != 0U) ? ((tmpData.aux2 << 4U) + (tmpData.aux2 << 1U) + (((tmpData.aux3 << 4U) + (tmpData.aux3 << 1U)) / tmpData.aux1)) : 0U;   /* aux2 multiplied by 18 added aux3 multiplied by 18 divide by aux1 */
    bufferFreqs[BUFFER_PERIPHPLLDFS1_PERIPHPLL] = tmpData.output;
}

static void PERIPHDFS2_A(void)
{
    const Clock_Ip_FracDivConfigType *dfsConfig;

    if (freqPointers[PERIPH_PLL_DFS2_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dfsConfig = &clock_config->fracDivs[freqPointers[PERIPH_PLL_DFS2_CLK] - 1U];
        tmpData.input2 = dfsConfig->value[0U];              /* mfi */
        tmpData.input3 = dfsConfig->value[1U];              /* mfn */
    }
    else
    {
        tmpData.input2 = ((dfs[1U]->DVPORT[1U] & DFS_DVPORT_MFI_MASK) >> DFS_DVPORT_MFI_SHIFT);              /* mfi */
        tmpData.input3 = ((dfs[1U]->DVPORT[1U] & DFS_DVPORT_MFN_MASK) >> DFS_DVPORT_MFN_SHIFT);              /* mfn */
    }

    tmpData.input1 = bufferFreqs[BUFFER_PERIPHPLL];   /* fin */

    tmpData.aux1 = ((tmpData.input2 << 5U) + (tmpData.input2 << 2U) + tmpData.input3);           /* mfi multiplied by 36 add mfn */
    tmpData.aux2 = (tmpData.aux1 != 0U) ? (tmpData.input1 / tmpData.aux1) : 0U;                  /* fin divide by aux1 */
}

static void PERIPHDFS2_B(void)
{
    tmpData.aux3 = tmpData.input1 - (tmpData.aux1 * tmpData.aux2);                                                           /* fin minus aux2 multiplied by aux1 */
    tmpData.output = (tmpData.aux1 != 0U) ? ((tmpData.aux2 << 4U) + (tmpData.aux2 << 1U) + (((tmpData.aux3 << 4U) + (tmpData.aux3 << 1U)) / tmpData.aux1)) : 0U;   /* aux2 multiplied by 18 added aux3 multiplied by 18 divide by aux1 */
    bufferFreqs[BUFFER_PERIPHPLLDFS2_PERIPHPLL] = tmpData.output;
}

static void PERIPHDFS3_A(void)
{
    const Clock_Ip_FracDivConfigType *dfsConfig;

    if (freqPointers[PERIPH_PLL_DFS3_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dfsConfig = &clock_config->fracDivs[freqPointers[PERIPH_PLL_DFS3_CLK] - 1U];
        tmpData.input2 = dfsConfig->value[0U];              /* mfi */
        tmpData.input3 = dfsConfig->value[1U];              /* mfn */
    }
    else
    {
        tmpData.input2 = ((dfs[1U]->DVPORT[2U] & DFS_DVPORT_MFI_MASK) >> DFS_DVPORT_MFI_SHIFT);              /* mfi */
        tmpData.input3 = ((dfs[1U]->DVPORT[2U] & DFS_DVPORT_MFN_MASK) >> DFS_DVPORT_MFN_SHIFT);              /* mfn */
    }

    tmpData.input1 = bufferFreqs[BUFFER_PERIPHPLL];   /* fin */

    tmpData.aux1 = ((tmpData.input2 << 5U) + (tmpData.input2 << 2U) + tmpData.input3);           /* mfi multiplied by 36 add mfn */
    tmpData.aux2 = (tmpData.aux1 != 0U) ? (tmpData.input1 / tmpData.aux1) : 0U;                  /* fin divide by aux1 */
}

static void PERIPHDFS3_B(void)
{
    tmpData.aux3 = tmpData.input1 - (tmpData.aux1 * tmpData.aux2);                                                           /* fin minus aux2 multiplied by aux1 */
    tmpData.output = (tmpData.aux1 != 0U) ? ((tmpData.aux2 << 4U) + (tmpData.aux2 << 1U) + (((tmpData.aux3 << 4U) + (tmpData.aux3 << 1U)) / tmpData.aux1)) : 0U;   /* aux2 multiplied by 18 added aux3 multiplied by 18 divide by aux1 */
    bufferFreqs[BUFFER_PERIPHPLLDFS3_PERIPHPLL] = tmpData.output;
}

static void PERIPHDFS4_A(void)
{
    const Clock_Ip_FracDivConfigType *dfsConfig;

    if (freqPointers[PERIPH_PLL_DFS4_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dfsConfig = &clock_config->fracDivs[freqPointers[PERIPH_PLL_DFS4_CLK] - 1U];
        tmpData.input2 = dfsConfig->value[0U];              /* mfi */
        tmpData.input3 = dfsConfig->value[1U];              /* mfn */
    }
    else
    {
        tmpData.input2 = ((dfs[1U]->DVPORT[3U] & DFS_DVPORT_MFI_MASK) >> DFS_DVPORT_MFI_SHIFT);              /* mfi */
        tmpData.input3 = ((dfs[1U]->DVPORT[3U] & DFS_DVPORT_MFN_MASK) >> DFS_DVPORT_MFN_SHIFT);              /* mfn */
    }

    tmpData.input1 = bufferFreqs[BUFFER_PERIPHPLL];   /* fin */

    tmpData.aux1 = ((tmpData.input2 << 5U) + (tmpData.input2 << 2U) + tmpData.input3);             /* mfi multiplied by 36 add mfn */
    tmpData.aux2 = (tmpData.aux1 != 0U) ? (tmpData.input1 / tmpData.aux1) : 0U;                    /* fin divide by aux1 */
}

static void PERIPHDFS4_B(void)
{
    tmpData.aux3 = tmpData.input1 - (tmpData.aux1 * tmpData.aux2);                                                           /* fin minus aux2 multiplied by aux1 */
    tmpData.output = (tmpData.aux1 != 0U) ? ((tmpData.aux2 << 4U) + (tmpData.aux2 << 1U) + (((tmpData.aux3 << 4U) + (tmpData.aux3 << 1U)) / tmpData.aux1)) : 0U;   /* aux2 multiplied by 18 added aux3 multiplied by 18 divide by aux1 */
    bufferFreqs[BUFFER_PERIPHPLLDFS4_PERIPHPLL] = tmpData.output;
}

static void PERIPHDFS5_A(void)
{
    const Clock_Ip_FracDivConfigType *dfsConfig;

    if (freqPointers[PERIPH_PLL_DFS5_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dfsConfig = &clock_config->fracDivs[freqPointers[PERIPH_PLL_DFS5_CLK] - 1U];
        tmpData.input2 = dfsConfig->value[0U];              /* mfi */
        tmpData.input3 = dfsConfig->value[1U];              /* mfn */
    }
    else
    {
        tmpData.input2 = ((dfs[1U]->DVPORT[4U] & DFS_DVPORT_MFI_MASK) >> DFS_DVPORT_MFI_SHIFT);              /* mfi */
        tmpData.input3 = ((dfs[1U]->DVPORT[4U] & DFS_DVPORT_MFN_MASK) >> DFS_DVPORT_MFN_SHIFT);              /* mfn */
    }

    tmpData.input1 = bufferFreqs[BUFFER_PERIPHPLL];   /* fin */

    tmpData.aux1 = ((tmpData.input2 << 5U) + (tmpData.input2 << 2U) + tmpData.input3);             /* mfi multiplied by 36 add mfn */
    tmpData.aux2 = (tmpData.aux1 != 0U) ? (tmpData.input1 / tmpData.aux1) : 0U;                    /* fin divide by aux1 */
}

static void PERIPHDFS5_B(void)
{
    tmpData.aux3 = tmpData.input1 - (tmpData.aux1 * tmpData.aux2);                                                           /* fin minus aux2 multiplied by aux1 */
    tmpData.output = (tmpData.aux1 != 0U) ? ((tmpData.aux2 << 4U) + (tmpData.aux2 << 1U) + (((tmpData.aux3 << 4U) + (tmpData.aux3 << 1U)) / tmpData.aux1)) : 0U;   /* aux2 multiplied by 18 added aux3 multiplied by 18 divide by aux1 */
    bufferFreqs[BUFFER_PERIPHPLLDFS5_PERIPHPLL] = tmpData.output;
}

static void PERIPHDFS6_A(void)
{
    const Clock_Ip_FracDivConfigType *dfsConfig;

    if (freqPointers[PERIPH_PLL_DFS6_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dfsConfig = &clock_config->fracDivs[freqPointers[PERIPH_PLL_DFS6_CLK] - 1U];
        tmpData.input2 = dfsConfig->value[0U];              /* mfi */
        tmpData.input3 = dfsConfig->value[1U];              /* mfn */
    }
    else
    {
        tmpData.input2 = ((dfs[1U]->DVPORT[5U] & DFS_DVPORT_MFI_MASK) >> DFS_DVPORT_MFI_SHIFT);              /* mfi */
        tmpData.input3 = ((dfs[1U]->DVPORT[5U] & DFS_DVPORT_MFN_MASK) >> DFS_DVPORT_MFN_SHIFT);              /* mfn */
    }

    tmpData.input1 = bufferFreqs[BUFFER_PERIPHPLL];   /* fin */

    tmpData.aux1 = ((tmpData.input2 << 5U) + (tmpData.input2 << 2U) + tmpData.input3);             /* mfi multiplied by 36 add mfn */
    tmpData.aux2 = (tmpData.aux1 != 0U) ? (tmpData.input1 / tmpData.aux1) : 0U;                    /* fin divide by aux1 */
}

static void PERIPHDFS6_B(void)
{
    tmpData.aux3 = tmpData.input1 - (tmpData.aux1 * tmpData.aux2);                                                                                                 /* fin minus aux2 multiplied by aux1 */
    tmpData.output = (tmpData.aux1 != 0U) ? ((tmpData.aux2 << 4U) + (tmpData.aux2 << 1U) + (((tmpData.aux3 << 4U) + (tmpData.aux3 << 1U)) / tmpData.aux1)) : 0U;   /* aux2 multiplied by 18 added aux3 multiplied by 18 divide by aux1 */
    bufferFreqs[BUFFER_PERIPHPLLDFS6_PERIPHPLL] = tmpData.output;
}

static void IntegerDividers_A(void)
{
    bufferFreqs[BUFFER_XBAR_FIRC] = bufferFreqs[BUFFER_FIRC] / 2U;

    bufferFreqs[BUFFER_XBARDIV2_FIRC] = bufferFreqs[BUFFER_FIRC] / 4U;

    bufferFreqs[BUFFER_XBARDIV3_FIRC] = bufferFreqs[BUFFER_FIRC] / 6U;

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}
static void IntegerDividers_B(void)
{
    bufferFreqs[BUFFER_XBARDIV4_FIRC] = bufferFreqs[BUFFER_FIRC] / 8U;

    bufferFreqs[BUFFER_XBARDIV6_FIRC] = bufferFreqs[BUFFER_FIRC] / 12U;

    bufferFreqs[BUFFER_A53COREDIV2_FIRC] = bufferFreqs[BUFFER_FIRC] / 2U;

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}
static void IntegerDividers_C(void)
{
    uint32 dividerValue;

        bufferFreqs[BUFFER_A53COREDIV10_FIRC] = bufferFreqs[BUFFER_FIRC] / 10U;

    if (freqPointers[PFE_PE_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[PFE_PE_CLK] - 1U].value;
    }
    else
    {
        dividerValue = cgm[2U][0U]->divider[0U];
        if (0U != (dividerValue & MC_CGM_MUX_DC_DE_MASK))
        {
            dividerValue = (((dividerValue & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);
        }
        else
        {
            dividerValue = 0U;
        }
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_PFEPE_FIRC] = bufferFreqs[BUFFER_FIRC] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_PFEPE_FIRC] = 0U;
    }

    if (freqPointers[PER_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[PER_CLK] - 1U].value;
    }
    else
    {
        dividerValue = cgm[0U][3U]->divider[0U];
        if (0U != (dividerValue & MC_CGM_MUX_DC_DE_MASK))
        {
            dividerValue = (((dividerValue & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);
        }
        else
        {
            dividerValue = 0U;
        }
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_PER_FIRC] = bufferFreqs[BUFFER_FIRC] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_PER_FIRC] = 0U;
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}
static void IntegerDividers_D(void)
{
    uint32 dividerValue;

    if (freqPointers[GMAC_REF_DIV_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[GMAC_REF_DIV_CLK] - 1U].value;
    }
    else
    {
        dividerValue = cgm[0U][15U]->divider[0U];
        if (0U != (dividerValue & MC_CGM_MUX_DC_DE_MASK))
        {
            dividerValue = (((dividerValue & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);
        }
        else
        {
            dividerValue = 0U;
        }
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_GMACREFDIV_FIRC] = bufferFreqs[BUFFER_FIRC] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_GMACREFDIV_FIRC] = 0U;
    }

    if (freqPointers[GMAC_REF_DIV_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[GMAC_REF_DIV_CLK] - 1U].value;
    }
    else
    {
        dividerValue = cgm[0U][15U]->divider[0U];
        if (0U != (dividerValue & MC_CGM_MUX_DC_DE_MASK))
        {
            dividerValue = (((dividerValue & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);
        }
        else
        {
            dividerValue = 0U;
        }
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_GMACREFDIV_gmac0extref] = bufferFreqs[BUFFER_gmac0extref] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_GMACREFDIV_gmac0extref] = 0U;
    }

    if (freqPointers[PFEMAC0_REF_DIV_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[PFEMAC0_REF_DIV_CLK] - 1U].value;
    }
    else
    {
        dividerValue = cgm[2U][7U]->divider[0U];
        if (0U != (dividerValue & MC_CGM_MUX_DC_DE_MASK))
        {
            dividerValue = (((dividerValue & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);
        }
        else
        {
            dividerValue = 0U;
        }
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_PFEMAC0REFDIV_FIRC] = bufferFreqs[BUFFER_FIRC] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_PFEMAC0REFDIV_FIRC] = 0U;
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}
static void IntegerDividers_E(void)
{
    uint32 dividerValue;

    if (freqPointers[PFEMAC0_REF_DIV_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[PFEMAC0_REF_DIV_CLK] - 1U].value;
    }
    else
    {
        dividerValue = cgm[2U][7U]->divider[0U];
        if (0U != (dividerValue & MC_CGM_MUX_DC_DE_MASK))
        {
            dividerValue = (((dividerValue & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);
        }
        else
        {
            dividerValue = 0U;
        }
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_PFEMAC0REFDIV_pfemac0extref] = bufferFreqs[BUFFER_pfemac0extref] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_PFEMAC0REFDIV_pfemac0extref] = 0U;
    }

    if (freqPointers[PFEMAC1_REF_DIV_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[PFEMAC1_REF_DIV_CLK] - 1U].value;
    }
    else
    {
        dividerValue = cgm[2U][8U]->divider[0U];
        if (0U != (dividerValue & MC_CGM_MUX_DC_DE_MASK))
        {
            dividerValue = (((dividerValue & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);
        }
        else
        {
            dividerValue = 0U;
        }
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_PFEMAC1REFDIV_FIRC] = bufferFreqs[BUFFER_FIRC] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_PFEMAC1REFDIV_FIRC] = 0U;
    }

    if (freqPointers[PFEMAC1_REF_DIV_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[PFEMAC1_REF_DIV_CLK] - 1U].value;
    }
    else
    {
        dividerValue = cgm[2U][8U]->divider[0U];
        if (0U != (dividerValue & MC_CGM_MUX_DC_DE_MASK))
        {
            dividerValue = (((dividerValue & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);
        }
        else
        {
            dividerValue = 0U;
        }
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_PFEMAC1REFDIV_pfemac1extref] = bufferFreqs[BUFFER_pfemac1extref] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_PFEMAC1REFDIV_pfemac1extref] = 0U;
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}
static void IntegerDividers_F(void)
{
    uint32 dividerValue;

    if (freqPointers[PFEMAC2_REF_DIV_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[PFEMAC2_REF_DIV_CLK] - 1U].value;
    }
    else
    {
        dividerValue = cgm[2U][9U]->divider[0U];
        if (0U != (dividerValue & MC_CGM_MUX_DC_DE_MASK))
        {
            dividerValue = (((dividerValue & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);
        }
        else
        {
            dividerValue = 0U;
        }
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_PFEMAC2REFDIV_FIRC] = bufferFreqs[BUFFER_FIRC] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_PFEMAC2REFDIV_FIRC] = 0U;
    }

    if (freqPointers[PFEMAC2_REF_DIV_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[PFEMAC2_REF_DIV_CLK] - 1U].value;
    }
    else
    {
        dividerValue = cgm[2U][9U]->divider[0U];
        if (0U != (dividerValue & MC_CGM_MUX_DC_DE_MASK))
        {
            dividerValue = (((dividerValue & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);
        }
        else
        {
            dividerValue = 0U;
        }
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_PFEMAC2REFDIV_pfemac2extref] = bufferFreqs[BUFFER_pfemac2extref] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_PFEMAC2REFDIV_pfemac2extref] = 0U;
    }

    if (freqPointers[CORE_PLL_PHI0_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[CORE_PLL_PHI0_CLK] - 1U].value;
    }
    else
    {
        dividerValue = ((pll[1U]->PLLODIV[1U] & PLLDIG_PLLODIV_DIV_MASK) >> PLLDIG_PLLODIV_DIV_SHIFT);
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_COREPLLPHI0_COREPLL] = bufferFreqs[BUFFER_COREPLL] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_COREPLLPHI0_COREPLL] = 0U;
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}
static void IntegerDividers_G(void)
{
    uint32 dividerValue;

    if (freqPointers[CORE_PLL_PHI1_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[CORE_PLL_PHI1_CLK] - 1U].value;
    }
    else
    {
        dividerValue = ((pll[1U]->PLLODIV[1U] & PLLDIG_PLLODIV_DIV_MASK) >> PLLDIG_PLLODIV_DIV_SHIFT);
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_COREPLLPHI1_COREPLL] = bufferFreqs[BUFFER_COREPLL] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_COREPLLPHI1_COREPLL] = 0U;
    }


#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}
static void IntegerDividers_I(void)
{
    uint32 dividerValue;

    if (freqPointers[PERIPH_PLL_PHI0_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[PERIPH_PLL_PHI0_CLK] - 1U].value;
    }
    else
    {
        dividerValue = ((pll[1U]->PLLODIV[0U] & PLLDIG_PLLODIV_DIV_MASK) >> PLLDIG_PLLODIV_DIV_SHIFT);
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_PERIPHPLLPHI0_PERIPHPLL] = bufferFreqs[BUFFER_PERIPHPLL] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_PERIPHPLLPHI0_PERIPHPLL] = 0U;
    }

    if (freqPointers[PERIPH_PLL_PHI1_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[PERIPH_PLL_PHI1_CLK] - 1U].value;
    }
    else
    {
        dividerValue = ((pll[1U]->PLLODIV[1U] & PLLDIG_PLLODIV_DIV_MASK) >> PLLDIG_PLLODIV_DIV_SHIFT);
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_PERIPHPLLPHI1_PERIPHPLL] = bufferFreqs[BUFFER_PERIPHPLL] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_PERIPHPLLPHI1_PERIPHPLL] = 0U;
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}
static void IntegerDividers_J(void)
{
    uint32 dividerValue;

    if (freqPointers[PERIPH_PLL_PHI2_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[PERIPH_PLL_PHI2_CLK] - 1U].value;
    }
    else
    {
        dividerValue = ((pll[1U]->PLLODIV[2U] & PLLDIG_PLLODIV_DIV_MASK) >> PLLDIG_PLLODIV_DIV_SHIFT);
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_PERIPHPLLPHI2_PERIPHPLL] = bufferFreqs[BUFFER_PERIPHPLL] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_PERIPHPLLPHI2_PERIPHPLL] = 0U;
    }

    if (freqPointers[PERIPH_PLL_PHI3_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[PERIPH_PLL_PHI3_CLK] - 1U].value;
    }
    else
    {
        dividerValue = ((pll[1U]->PLLODIV[3U] & PLLDIG_PLLODIV_DIV_MASK) >> PLLDIG_PLLODIV_DIV_SHIFT);
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_PERIPHPLLPHI3_PERIPHPLL] = bufferFreqs[BUFFER_PERIPHPLL] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_PERIPHPLLPHI3_PERIPHPLL] = 0U;
    }

    if (freqPointers[PERIPH_PLL_PHI4_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[PERIPH_PLL_PHI4_CLK] - 1U].value;
    }
    else
    {
        dividerValue = ((pll[1U]->PLLODIV[4U] & PLLDIG_PLLODIV_DIV_MASK) >> PLLDIG_PLLODIV_DIV_SHIFT);
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_PERIPHPLLPHI4_PERIPHPLL] = bufferFreqs[BUFFER_PERIPHPLL] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_PERIPHPLLPHI4_PERIPHPLL] = 0U;
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}
static void IntegerDividers_K(void)
{
    uint32 dividerValue;

    if (freqPointers[PERIPH_PLL_PHI5_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[PERIPH_PLL_PHI5_CLK] - 1U].value;
    }
    else
    {
        dividerValue = ((pll[1U]->PLLODIV[5U] & PLLDIG_PLLODIV_DIV_MASK) >> PLLDIG_PLLODIV_DIV_SHIFT);
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_PERIPHPLLPHI5_PERIPHPLL] = bufferFreqs[BUFFER_PERIPHPLL] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_PERIPHPLLPHI5_PERIPHPLL] = 0U;
    }

    if (freqPointers[PERIPH_PLL_PHI6_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[PERIPH_PLL_PHI6_CLK] - 1U].value;
    }
    else
    {
        dividerValue = ((pll[1U]->PLLODIV[6U] & PLLDIG_PLLODIV_DIV_MASK) >> PLLDIG_PLLODIV_DIV_SHIFT);
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_PERIPHPLLPHI6_PERIPHPLL] = bufferFreqs[BUFFER_PERIPHPLL] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_PERIPHPLLPHI6_PERIPHPLL] = 0U;
    }

    if (freqPointers[PERIPH_PLL_PHI7_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[PERIPH_PLL_PHI7_CLK] - 1U].value;
    }
    else
    {
        dividerValue = ((pll[1U]->PLLODIV[7U] & PLLDIG_PLLODIV_DIV_MASK) >> PLLDIG_PLLODIV_DIV_SHIFT);
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_PERIPHPLLPHI7_PERIPHPLL] = bufferFreqs[BUFFER_PERIPHPLL] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_PERIPHPLLPHI7_PERIPHPLL] = 0U;
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}
static void IntegerDividers_N(void)
{
    uint32 dividerValue;

    if (freqPointers[DDR_PLL_PHI0_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[DDR_PLL_PHI0_CLK] - 1U].value;
    }
    else
    {
        dividerValue = ((pll[2U]->PLLODIV[0U] & PLLDIG_PLLODIV_DIV_MASK) >> PLLDIG_PLLODIV_DIV_SHIFT);
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_DDRPLLPHI0_DDRPLL] = bufferFreqs[BUFFER_DDRPLL] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_DDRPLLPHI0_DDRPLL] = 0U;
    }

    if (freqPointers[ACCEL_PLL_PHI0_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[ACCEL_PLL_PHI0_CLK] - 1U].value;
    }
    else
    {
        dividerValue = ((pll[3U]->PLLODIV[0U] & PLLDIG_PLLODIV_DIV_MASK) >> PLLDIG_PLLODIV_DIV_SHIFT);
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_ACCELPLLPHI0_ACCELPLL] = bufferFreqs[BUFFER_ACCELPLL] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_ACCELPLLPHI0_ACCELPLL] = 0U;
    }

    if (freqPointers[ACCEL_PLL_PHI1_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[ACCEL_PLL_PHI1_CLK] - 1U].value;
    }
    else
    {
        dividerValue = ((pll[3U]->PLLODIV[1U] & PLLDIG_PLLODIV_DIV_MASK) >> PLLDIG_PLLODIV_DIV_SHIFT);
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_ACCELPLLPHI1_ACCELPLL] = bufferFreqs[BUFFER_ACCELPLL] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_ACCELPLLPHI1_ACCELPLL] = 0U;
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}
static void IntegerDividers_O(void)
{
    bufferFreqs[BUFFER_XBAR_COREPLLDFS1_COREPLL] = bufferFreqs[BUFFER_COREPLLDFS1_COREPLL] / 2U;

    bufferFreqs[BUFFER_XBARDIV2_COREPLLDFS1_COREPLL] = bufferFreqs[BUFFER_COREPLLDFS1_COREPLL] / 4U;

    bufferFreqs[BUFFER_XBARDIV3_COREPLLDFS1_COREPLL] = bufferFreqs[BUFFER_COREPLLDFS1_COREPLL] / 6U;

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}
static void IntegerDividers_P(void)
{
    bufferFreqs[BUFFER_XBARDIV4_COREPLLDFS1_COREPLL] = bufferFreqs[BUFFER_COREPLLDFS1_COREPLL] / 8U;

    bufferFreqs[BUFFER_XBARDIV6_COREPLLDFS1_COREPLL] = bufferFreqs[BUFFER_COREPLLDFS1_COREPLL] / 12U;

    bufferFreqs[BUFFER_A53COREDIV2_COREPLLPHI0_COREPLL] = bufferFreqs[BUFFER_COREPLLPHI0_COREPLL] / 2U;

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}
static void IntegerDividers_Q(void)
{
    bufferFreqs[BUFFER_A53COREDIV2_COREPLLDFS2_COREPLL] = bufferFreqs[BUFFER_COREPLLDFS2_COREPLL] / 2U;

    bufferFreqs[BUFFER_A53COREDIV10_COREPLLPHI0_COREPLL] = bufferFreqs[BUFFER_COREPLLPHI0_COREPLL] / 10U;

    bufferFreqs[BUFFER_A53COREDIV10_COREPLLDFS2_COREPLL] = bufferFreqs[BUFFER_COREPLLDFS2_COREPLL] / 10U;

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}
static void IntegerDividers_R(void)
{
    uint32 dividerValue;

    if (freqPointers[PFE_PE_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[PFE_PE_CLK] - 1U].value;
    }
    else
    {
        dividerValue = cgm[2U][0U]->divider[0U];
        if (0U != (dividerValue & MC_CGM_MUX_DC_DE_MASK))
        {
            dividerValue = (((dividerValue & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);
        }
        else
        {
            dividerValue = 0U;
        }
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_PFEPE_ACCELPLLPHI1_ACCELPLL] = bufferFreqs[BUFFER_ACCELPLLPHI1_ACCELPLL] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_PFEPE_ACCELPLLPHI1_ACCELPLL] = 0U;
    }

    if (freqPointers[PER_CLK] != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        dividerValue = clock_config->dividers[freqPointers[PER_CLK] - 1U].value;
    }
    else
    {
        dividerValue = cgm[0U][3U]->divider[0U];
        if (0U != (dividerValue & MC_CGM_MUX_DC_DE_MASK))
        {
            dividerValue = (((dividerValue & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);
        }
        else
        {
            dividerValue = 0U;
        }
    }
    if (dividerValue != 0U)
    {
        bufferFreqs[BUFFER_PER_PERIPHPLLPHI1_PERIPHPLL] = bufferFreqs[BUFFER_PERIPHPLLPHI1_PERIPHPLL] / dividerValue;
    }
    else
    {
        bufferFreqs[BUFFER_PER_PERIPHPLLPHI1_PERIPHPLL] = 0U;
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}



static void PCFS_COREPLL_DFS1_A(void)
{
    const Clock_Ip_PcfsConfigType *pcfsConfig;
    uint32 maxAllowableIDDchange;
    uint32 stepDuration;
    uint32 finput, fsafe;
    uint32 amaxBrut;

    if (pcfsEntries[PCFS_COREPLLDFS1].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        pcfsConfig = &clock_config->pcfs[pcfsEntries[PCFS_COREPLLDFS1].configIndex - 1U];
        maxAllowableIDDchange = pcfsConfig->maxAllowableIDDchange;
        stepDuration = pcfsConfig->stepDuration;
    }
    else
    {
        maxAllowableIDDchange = DEFAULT_MAX_ALLOWABLE_IDD_CHANGE;
        stepDuration = ((cgmPcfs[0U]->PCFS_SDUR & MC_CGM_PCFS_SDUR_SDUR_MASK) >> MC_CGM_PCFS_SDUR_SDUR_SHIFT);
    }

    finput = bufferFreqs[BUFFER_COREPLLDFS1_COREPLL] / 1000000U;
    fsafe  = bufferFreqs[BUFFER_FIRC] / 1000000U;

    tmpData.input1 = stepDuration;                       /* step duration */
    tmpData.input2 = finput;                             /* frequency of the input clock for which progressive switch is processed */
    tmpData.input3 = fsafe;                              /* frequency of safe clock */

    /* Calculate amax=fchg/Finput */
    amaxBrut = (maxAllowableIDDchange * stepDuration * 100000U / (finput * DYNAMIC_IDD_CHANGE));

    tmpData.aux1 = amaxBrut;

#ifdef RECORD_CALLBACK_TIMESTAMPS
uint32 oldSystickCounter = systickCounter;
systickCounter = S32_SysTick->CVR;
timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void PCFS_COREPLL_DFS1_B(void)
{
    uint32 amaxBrut = tmpData.aux1;
    uint32 RATE = 0U;
    uint8 i;

    /* Round pcfs rate by rounding amax */
    if (amaxBrut < aMax[0U])
    {
        RATE = pcfsRate[0U];
    }
    else if (amaxBrut > aMax[A_MAX_SIZE-1U])
    {
        RATE = pcfsRate[A_MAX_SIZE-1U];
    }
    else
    {
        for (i = 1U; i < (uint8)A_MAX_SIZE; i++)
        {
            if (aMax[i-1U] < amaxBrut)
            {
                RATE = pcfsRate[i];
            }
        }
    }

    tmpData.aux1 = RATE;                              /* RATE */

#ifdef RECORD_CALLBACK_TIMESTAMPS
uint32 oldSystickCounter = systickCounter;
systickCounter = S32_SysTick->CVR;
timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void PCFS_COREPLL_DFS1_C(void)
{
    uint32 finput = tmpData.input2;
    uint32 fsafe  = tmpData.input3;
    uint32 RATE   = tmpData.aux1;

    /* Calculate K by using formula k = ceil(0.5 + sqrt(0.25 - (2000 * (1 -(Finput/fsafe)) / RATE))) */

    tmpData.aux2 = 256U + (((1024U * 2000U) * finput) / (fsafe * RATE)) - ((1024U * 2000U) / RATE);
    tmpData.aux3 = 1UL << 30U;   /* The second-to-top bit is set: use 1u << 14 for uint16 type; use 1uL<<30 for uint32 type  */

    /* Implement sqrt from K formula by using a square-root computing in embedded C */

    /* "one" starts at the highest power of four <= than the argument */
    while (tmpData.aux3 > tmpData.aux2)
    {
        tmpData.aux3 = tmpData.aux3 >> 2;
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
uint32 oldSystickCounter = systickCounter;
systickCounter = S32_SysTick->CVR;
timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void PCFS_COREPLL_DFS1_D(void)
{
    /* Implement sqrt from K formula by using a square-root computing in embedded C */

    while (tmpData.aux3 != 0U)
    {
        if (tmpData.aux2 >= (tmpData.aux4 + tmpData.aux3))
        {
            tmpData.aux2 = tmpData.aux2 - (tmpData.aux4 + tmpData.aux3);
            tmpData.aux4 = tmpData.aux4 + (tmpData.aux3 << 1U);
        }

        tmpData.aux4 = tmpData.aux4 >> 1U;
        tmpData.aux3 = tmpData.aux3 >> 2U;
    }


#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void PCFS_COREPLL_DFS1_E(void)
{
    uint32 stepDuration = tmpData.input1;
    uint32       finput = tmpData.input2;
    uint32       fsafe  = tmpData.input3;
    uint32       RATE   = tmpData.aux1;
    uint32       K      = (64U + 127U + (tmpData.aux4 << 2U)) >> 7U;   /* Calculated K from k = ceil(0.5 + sqrt(0.25 - (2000 * (1 -(Fi/fsafe)) / RATE))) */

    pcfsEntries[PCFS_COREPLLDFS1].sdur = stepDuration * fsafe;
    pcfsEntries[PCFS_COREPLLDFS1].divc_init = RATE * K;
    pcfsEntries[PCFS_COREPLLDFS1].divc_rate = RATE;
    pcfsEntries[PCFS_COREPLLDFS1].div_startValue = 999U + ((RATE * K * (K+1U)) >> 1U);
    pcfsEntries[PCFS_COREPLLDFS1].div_endValue = (finput * 1000U / fsafe) - 1U;


#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void PCFS_COREPLL_PHI0_A(void)
{
    const Clock_Ip_PcfsConfigType *pcfsConfig;
    uint32 maxAllowableIDDchange;
    uint32 stepDuration;
    uint32 finput, fsafe;
    uint32 amaxBrut;

    if (pcfsEntries[PCFS_COREPLLPHI0].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        pcfsConfig = &clock_config->pcfs[pcfsEntries[PCFS_COREPLLPHI0].configIndex - 1U];
        maxAllowableIDDchange = pcfsConfig->maxAllowableIDDchange;
        stepDuration = pcfsConfig->stepDuration;
    }
    else
    {
        maxAllowableIDDchange = DEFAULT_MAX_ALLOWABLE_IDD_CHANGE;
        stepDuration = ((cgmPcfs[1U]->PCFS_SDUR & MC_CGM_PCFS_SDUR_SDUR_MASK) >> MC_CGM_PCFS_SDUR_SDUR_SHIFT);
    }

    finput = bufferFreqs[BUFFER_COREPLLPHI0_COREPLL] / 1000000U;
    fsafe  = bufferFreqs[BUFFER_FIRC] / 1000000U;

    tmpData.input1 = stepDuration;                       /* step duration */
    tmpData.input2 = finput;                             /* frequency of the input clock for which progressive switch is processed */
    tmpData.input3 = fsafe;                              /* frequency of safe clock */

    /* Calculate amax=fchg/Finput */
    amaxBrut = (maxAllowableIDDchange * stepDuration * 100000U / (finput * DYNAMIC_IDD_CHANGE));

    tmpData.aux1 = amaxBrut;

#ifdef RECORD_CALLBACK_TIMESTAMPS
uint32 oldSystickCounter = systickCounter;
systickCounter = S32_SysTick->CVR;
timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void PCFS_COREPLL_PHI0_B(void)
{
    uint32 amaxBrut = tmpData.aux1;
    uint32 RATE = 0U;
    uint8 i;

    /* Round pcfs rate by rounding amax */
    if (amaxBrut < aMax[0U])
    {
        RATE = pcfsRate[0U];
    }
    else if (amaxBrut > aMax[A_MAX_SIZE-1U])
    {
        RATE = pcfsRate[A_MAX_SIZE-1U];
    }
    else
    {
        for (i = 1U; i < (uint8)A_MAX_SIZE; i++)
        {
            if (aMax[i-1U] < amaxBrut)
            {
                RATE = pcfsRate[i];
            }
        }
    }

    tmpData.aux1 = RATE;                              /* RATE */

#ifdef RECORD_CALLBACK_TIMESTAMPS
uint32 oldSystickCounter = systickCounter;
systickCounter = S32_SysTick->CVR;
timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void PCFS_COREPLL_PHI0_C(void)
{
    uint32 finput = tmpData.input2;
    uint32 fsafe  = tmpData.input3;
    uint32 RATE   = tmpData.aux1;

    /* Calculate K by using formula k = ceil(0.5 + sqrt(0.25 - (2000 * (1 -(Finput/fsafe)) / RATE))) */

    tmpData.aux2 = 256U + (((1024U * 2000U) * finput) / (fsafe * RATE)) - ((1024U * 2000U) / RATE);
    tmpData.aux3 = 1UL << 30U;   /* The second-to-top bit is set: use 1u << 14 for uint16 type; use 1uL<<30 for uint32 type  */

    /* Implement sqrt from K formula by using a square-root computing in embedded C */

    /* "one" starts at the highest power of four <= than the argument */
    while (tmpData.aux3 > tmpData.aux2)
    {
        tmpData.aux3 = tmpData.aux3 >> 2;
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
uint32 oldSystickCounter = systickCounter;
systickCounter = S32_SysTick->CVR;
timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void PCFS_COREPLL_PHI0_D(void)
{
    /* Implement sqrt from K formula by using a square-root computing in embedded C */

    while (tmpData.aux3 != 0U)
    {
        if (tmpData.aux2 >= (tmpData.aux4 + tmpData.aux3))
        {
            tmpData.aux2 = tmpData.aux2 - (tmpData.aux4 + tmpData.aux3);
            tmpData.aux4 = tmpData.aux4 + (tmpData.aux3 << 1U);
        }

        tmpData.aux4 = tmpData.aux4 >> 1U;
        tmpData.aux3 = tmpData.aux3 >> 2U;
    }


#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void PCFS_COREPLL_PHI0_E(void)
{
    uint32 stepDuration = tmpData.input1;
    uint32       finput = tmpData.input2;
    uint32       fsafe  = tmpData.input3;
    uint32       RATE   = tmpData.aux1;
    uint32       K      = (64U + 127U + (tmpData.aux4 << 2U)) >> 7U;   /* Calculated K from k = ceil(0.5 + sqrt(0.25 - (2000 * (1 -(Fi/fsafe)) / RATE))) */

    pcfsEntries[PCFS_COREPLLPHI0].sdur = (uint32)(stepDuration * fsafe);
    pcfsEntries[PCFS_COREPLLPHI0].divc_init = (uint32)(RATE * K);
    pcfsEntries[PCFS_COREPLLPHI0].divc_rate = RATE;
    pcfsEntries[PCFS_COREPLLPHI0].div_startValue = 999U + (((uint32)(RATE * K * (K+1U))) >> 1U);
    pcfsEntries[PCFS_COREPLLPHI0].div_endValue = (finput * 1000U / fsafe) - 1U;


#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void PCFS_ACCELPLL_PHI1_A(void)
{
    const Clock_Ip_PcfsConfigType *pcfsConfig;
    uint32 maxAllowableIDDchange;
    uint32 stepDuration;
    uint32 finput, fsafe;
    uint32 amaxBrut;

    if (pcfsEntries[PCFS_ACCELPLLPHI1].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        pcfsConfig = &clock_config->pcfs[pcfsEntries[PCFS_ACCELPLLPHI1].configIndex - 1U];
        maxAllowableIDDchange = pcfsConfig->maxAllowableIDDchange;
        stepDuration = pcfsConfig->stepDuration;
    }
    else
    {
        maxAllowableIDDchange = DEFAULT_MAX_ALLOWABLE_IDD_CHANGE;
        stepDuration = ((cgmPcfs[2U]->PCFS_SDUR & MC_CGM_PCFS_SDUR_SDUR_MASK) >> MC_CGM_PCFS_SDUR_SDUR_SHIFT);
    }

    finput = bufferFreqs[BUFFER_ACCELPLLPHI1_ACCELPLL] / 1000000U;
    fsafe  = bufferFreqs[BUFFER_FIRC] / 1000000U;

    tmpData.input1 = stepDuration;                       /* step duration */
    tmpData.input2 = finput;                             /* frequency of the input clock for which progressive switch is processed */
    tmpData.input3 = fsafe;                              /* frequency of safe clock */

    /* Calculate amax=fchg/Finput */
    amaxBrut = (maxAllowableIDDchange * stepDuration * 100000U / (finput * DYNAMIC_IDD_CHANGE));

    tmpData.aux1 = amaxBrut;

#ifdef RECORD_CALLBACK_TIMESTAMPS
uint32 oldSystickCounter = systickCounter;
systickCounter = S32_SysTick->CVR;
timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void PCFS_ACCELPLL_PHI1_B(void)
{
    uint32 amaxBrut = tmpData.aux1;
    uint32 RATE = 0U;
    uint8 i;

    /* Round pcfs rate by rounding amax */
    if (amaxBrut < aMax[0U])
    {
        RATE = pcfsRate[0U];
    }
    else if (amaxBrut > aMax[A_MAX_SIZE-1U])
    {
        RATE = pcfsRate[A_MAX_SIZE-1U];
    }
    else
    {
        for (i = 1U; i < (uint8)A_MAX_SIZE; i++)
        {
            if (aMax[i-1U] < amaxBrut)
            {
                RATE = pcfsRate[i];
            }
        }
    }

    tmpData.aux1 = RATE;                              /* RATE */

#ifdef RECORD_CALLBACK_TIMESTAMPS
uint32 oldSystickCounter = systickCounter;
systickCounter = S32_SysTick->CVR;
timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void PCFS_ACCELPLL_PHI1_C(void)
{
    uint32 finput = tmpData.input2;
    uint32 fsafe  = tmpData.input3;
    uint32 RATE   = tmpData.aux1;

    /* Calculate K by using formula k = ceil(0.5 + sqrt(0.25 - (2000 * (1 -(Finput/fsafe)) / RATE))) */

    tmpData.aux2 = 256U + (((1024U * 2000U) * finput) / (fsafe * RATE)) - ((1024U * 2000U) / RATE);
    tmpData.aux3 = 1UL << 30U;   /* The second-to-top bit is set: use 1u << 14 for uint16 type; use 1uL<<30 for uint32 type  */

    /* Implement sqrt from K formula by using a square-root computing in embedded C */

    /* "one" starts at the highest power of four <= than the argument */
    while (tmpData.aux3 > tmpData.aux2)
    {
        tmpData.aux3 = tmpData.aux3 >> 2;
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
uint32 oldSystickCounter = systickCounter;
systickCounter = S32_SysTick->CVR;
timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void PCFS_ACCELPLL_PHI1_D(void)
{
    /* Implement sqrt from K formula by using a square-root computing in embedded C */

    while (tmpData.aux3 != 0U)
    {
        if (tmpData.aux2 >= (tmpData.aux4 + tmpData.aux3))
        {
            tmpData.aux2 = tmpData.aux2 - (tmpData.aux4 + tmpData.aux3);
            tmpData.aux4 = tmpData.aux4 + (tmpData.aux3 << 1U);
        }

        tmpData.aux4 = tmpData.aux4 >> 1U;
        tmpData.aux3 = tmpData.aux3 >> 2U;
    }


#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void PCFS_ACCELPLL_PHI1_E(void)
{
    uint32 stepDuration = tmpData.input1;
    uint32       finput = tmpData.input2;
    uint32       fsafe  = tmpData.input3;
    uint32       RATE   = tmpData.aux1;
    uint32       K      = (64U + 127U + (tmpData.aux4 << 2U)) >> 7U;   /* Calculated K from k = ceil(0.5 + sqrt(0.25 - (2000 * (1 -(Fi/fsafe)) / RATE))) */

    pcfsEntries[PCFS_ACCELPLLPHI1].sdur = stepDuration * fsafe;
    pcfsEntries[PCFS_ACCELPLLPHI1].divc_init = RATE * K;
    pcfsEntries[PCFS_ACCELPLLPHI1].divc_rate = RATE;
    pcfsEntries[PCFS_ACCELPLLPHI1].div_startValue = 999U + ((RATE * K * (K+1U)) >> 1U);
    pcfsEntries[PCFS_ACCELPLLPHI1].div_endValue = (finput * 1000U / fsafe) - 1U;


#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void CALCULATE_CONFIGURED_PER_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selectorPER_CLK = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (PER_CLK == clock_config->selectors[i].name)
        {
            selectorPER_CLK = &clock_config->selectors[i];
            break;
        }
    }

    if (selectorPER_CLK != NULL)
    {
        switch(selectorPER_CLK->value)
        {
            case FIRC_CLK:
            {
                configuredPerClock = bufferFreqs[BUFFER_PER_FIRC];
            }
            break;
            case PERIPH_PLL_PHI1_CLK:
            {
                configuredPerClock = bufferFreqs[BUFFER_PER_PERIPHPLLPHI1_PERIPHPLL];
            }
            break;
            default:
            {
                configuredPerClock = 0U;
            }
            break;
        }
    }
    else
    {
        configuredPerClock = 0U;
    }
    (void)configuredPerClock; /* Fix warning compiler: unused variable configuredPerClock */
}
static void CALCULATE_CONFIGURED_FLEXRAY_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (FLEXRAY_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredFlexRayClk = bufferFreqs[BUFFER_FIRC];
            }
            break;
            case FXOSC_CLK:
            {
                configuredFlexRayClk = bufferFreqs[BUFFER_FXOSC];
            }
            break;
            case PERIPH_PLL_PHI0_CLK:
            {
                configuredFlexRayClk = bufferFreqs[BUFFER_PERIPHPLLPHI0_PERIPHPLL];
            }
            break;
            default:
            {
                configuredFlexRayClk = 0U;
            }
            break;
        }
    }
    else
    {
        configuredFlexRayClk = 0U;
    }

    (void)configuredFlexRayClk; /* Fix warning compiler: unused variable configuredFlexRayClk */
}
static void CALCULATE_CONFIGURED_FLEXCAN_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (FLEXCAN_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredFlexCanClk = bufferFreqs[BUFFER_FIRC];
            }
            break;
            case FXOSC_CLK:
            {
                configuredFlexCanClk = bufferFreqs[BUFFER_FXOSC];
            }
            break;
            case PERIPH_PLL_PHI2_CLK:
            {
                configuredFlexCanClk = bufferFreqs[BUFFER_PERIPHPLLPHI2_PERIPHPLL];
            }
            break;
            default:
            {
                configuredFlexCanClk = 0U;
            }
            break;
        }
    }
    else
    {
        configuredFlexCanClk = 0U;
    }

    (void)configuredFlexCanClk; /* Fix warning compiler: unused variable configuredFlexCanClk */
}

static void CALCULATE_CONFIGURED_GMAC0_TX_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (GMAC0_TX_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredGmacTxClk = bufferFreqs[BUFFER_FIRC];
            }
            break;
            case PERIPH_PLL_PHI5_CLK:
            {
                configuredGmacTxClk = bufferFreqs[BUFFER_PERIPHPLLPHI5_PERIPHPLL];
            }
            break;
            case SERDES_0_LANE_0_TX:
            {
                configuredGmacTxClk = bufferFreqs[BUFFER_SERDES0LANE0TX];
            }
            break;
            case GMAC_0_EXT_TX_CLK:
            {
                configuredGmacTxClk = bufferFreqs[BUFFER_gmac0exttx];
            }
            break;
            case GMAC_0_EXT_REF_CLK:
            {
                configuredGmacTxClk = bufferFreqs[BUFFER_gmac0extref];
            }
            break;
            default:
            {
                configuredGmacTxClk = 0U;
            }
            break;
        }
    }
    else
    {
        configuredGmacTxClk = 0U;
    }

    (void)configuredGmacTxClk; /* Fix warning compiler: unused variable configuredGmacTxClk */
}

static void CALCULATE_CONFIGURED_GMAC0_TS_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (GMAC_TS_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredGmacTsClk = bufferFreqs[BUFFER_FIRC];
            }
            break;
            case PERIPH_PLL_PHI4_CLK:
            {
                configuredGmacTsClk = bufferFreqs[BUFFER_PERIPHPLLPHI4_PERIPHPLL];
            }
            break;
            case GMAC_EXT_TS_CLK:
            {
                configuredGmacTsClk = bufferFreqs[BUFFER_gmac0exttx];
            }
            break;
            default:
            {
                configuredGmacTsClk = 0U;
            }
            break;
        }
    }
    else
    {
        configuredGmacTsClk = 0U;
    }

    (void)configuredGmacTsClk; /* Fix warning compiler: unused variable configuredGmacTsClk */
}


static void CALCULATE_CONFIGURED_LIN_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (LIN_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredLinClk = bufferFreqs[BUFFER_FIRC];
            }
            break;
            case FXOSC_CLK:
            {
                configuredLinClk = bufferFreqs[BUFFER_FXOSC];
            }
            break;
            case PERIPH_PLL_PHI3_CLK:
            {
                configuredLinClk = bufferFreqs[BUFFER_PERIPHPLLPHI3_PERIPHPLL];
            }
            break;
            default:
            {
                configuredLinClk = 0U;
            }
            break;
        }
    }
    else
    {
        configuredLinClk = 0U;
    }

    (void)configuredLinClk; /* Fix warning compiler: unused variable configuredLinClk */
}

static void CALCULATE_CONFIGURED_QSPI_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (QSPI_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredQspiClk = bufferFreqs[BUFFER_FIRC];
            }
            break;
            case PERIPH_PLL_DFS1_CLK:
            {
                configuredQspiClk = bufferFreqs[BUFFER_PERIPHPLLDFS1_PERIPHPLL];
            }
            break;
            default:
            {
                configuredQspiClk = 0U;
            }
            break;
        }
    }
    else
    {
        configuredQspiClk = 0U;
    }

    (void)configuredQspiClk; /* Fix warning compiler: unused variable configuredQspiClk */
}

static void CALCULATE_CONFIGURED_USDHC_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (USDHC_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredUsdhcClk = bufferFreqs[BUFFER_FIRC];
            }
            break;
            case PERIPH_PLL_DFS3_CLK:
            {
                configuredUsdhcClk = bufferFreqs[BUFFER_PERIPHPLLDFS3_PERIPHPLL];
            }
            break;
            default:
            {
                configuredUsdhcClk = 0U;
            }
            break;
        }
    }
    else
    {
        configuredUsdhcClk = 0U;
    }

    (void)configuredUsdhcClk; /* Fix warning compiler: unused variable configuredUsdhcClk */
}

static void CALCULATE_CONFIGURED_DDR_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (DDR_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredDdrClk = bufferFreqs[BUFFER_FIRC];
            }
            break;
            case DDR_PLL_PHI0_CLK:
            {
                configuredDdrClk = bufferFreqs[BUFFER_DDRPLLPHI0_DDRPLL];
            }
            break;
            default:
            {
                configuredDdrClk = 0U;
            }
            break;
        }
    }
    else
    {
        configuredDdrClk = 0U;
    }

    (void)configuredDdrClk; /* Fix warning compiler: unused variable configuredDdrClk */
}

static void CALCULATE_CONFIGURED_GMAC_REF_DIV_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (GMAC_REF_DIV_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredGmacRefDiv = bufferFreqs[BUFFER_GMACREFDIV_FIRC];
            }
            break;
            case GMAC_0_EXT_REF_CLK:
            {
                configuredGmacRefDiv = bufferFreqs[BUFFER_GMACREFDIV_gmac0extref];
            }
            break;
            default:
            {
                configuredGmacRefDiv = 0U;
            }
            break;
        }
    }
    else
    {
        configuredGmacRefDiv = 0U;
    }

    (void)configuredGmacRefDiv; /* Fix warning compiler: unused variable configuredGmacRefDiv */
}

static void CALCULATE_CONFIGURED_GMAC0_RX_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (GMAC0_RX_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredGmacRxClk = bufferFreqs[BUFFER_FIRC];
            }
            break;
            case SERDES_0_LANE_0_CDR:
            {
                configuredGmacTxClk = bufferFreqs[BUFFER_SERDES0LANE0CDR];
            }
            break;
            case GMAC_REF_DIV_CLK:
            {
                configuredGmacRxClk = configuredGmacRefDiv;
            }
            break;
            default:
            {
                configuredGmacRxClk = 0U;
            }
            break;
        }
    }
    else
    {
        configuredGmacRxClk = 0U;
    }

    (void)configuredGmacRxClk; /* Fix warning compiler: unused variable configuredGmacRxClk */
}

static void CALCULATE_CONFIGURED_SPI_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (SPI_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredSpiClk = bufferFreqs[BUFFER_FIRC];
            }
            break;
            case PERIPH_PLL_PHI7_CLK:
            {
                configuredSpiClk = bufferFreqs[BUFFER_PERIPHPLLPHI7_PERIPHPLL];
            }
            break;
            default:
            {
                configuredSpiClk = 0U;
            }
            break;
        }
    }
    else
    {
        configuredSpiClk = 0U;
    }

    (void)configuredSpiClk; /* Fix warning compiler: unused variable configuredSpiClk */
}

static void CALCULATE_CONFIGURED_A53_CORE_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (A53_CORE_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredA53coreClk = bufferFreqs[BUFFER_FIRC];
            }
            break;
            case CORE_PLL_PHI0_CLK:
            {
                configuredA53coreClk = bufferFreqs[BUFFER_COREPLLPHI0_COREPLL];
            }
            break;
            case CORE_PLL_DFS2_CLK:
            {
                configuredA53coreClk = bufferFreqs[BUFFER_COREPLLDFS2_COREPLL];
            }
            break;
            default:
            {
                configuredA53coreClk = 0U;
            }
            break;
        }
    }
    else
    {
        configuredA53coreClk = 0U;
    }

    (void)configuredA53coreClk; /* Fix warning compiler: unused variable configuredA53coreClk */
}

static void CALCULATE_CONFIGURED_PFE_PE_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (PFE_PE_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredPfepeClk = bufferFreqs[BUFFER_PFEPE_FIRC];
            }
            break;
            case ACCEL_PLL_PHI1_CLK:
            {
                configuredPfepeClk = bufferFreqs[BUFFER_PFEPE_ACCELPLLPHI1_ACCELPLL];
            }
            break;
            default:
            {
                configuredPfepeClk = 0U;
            }
            break;
        }
    }
    else
    {
        configuredPfepeClk = 0U;
    }

    (void)configuredPfepeClk; /* Fix warning compiler: unused variable configuredPfepeClk */
}

static void CALCULATE_CONFIGURED_PFEMAC0_REF_DIV_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (PFEMAC0_REF_DIV_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredPfemac0RefDiv = bufferFreqs[BUFFER_PFEMAC0REFDIV_FIRC];
            }
            break;
            case PFE_MAC_0_EXT_REF_CLK:
            {
                configuredPfemac0RefDiv = bufferFreqs[BUFFER_PFEMAC0REFDIV_pfemac0extref];
            }
            break;
            default:
            {
                configuredPfemac0RefDiv = 0U;
            }
            break;
        }
    }
    else
    {
        configuredPfemac0RefDiv = 0U;
    }

    (void)configuredPfemac0RefDiv; /* Fix warning compiler: unused variable configuredPfemac0RefDiv */
}

static void CALCULATE_CONFIGURED_PFEMAC1_REF_DIV_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (PFEMAC1_REF_DIV_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredPfemac1RefDiv = bufferFreqs[BUFFER_PFEMAC1REFDIV_FIRC];
            }
            break;
            case PFE_MAC_0_EXT_REF_CLK:
            {
                configuredPfemac1RefDiv = bufferFreqs[BUFFER_PFEMAC1REFDIV_pfemac1extref];
            }
            break;
            default:
            {
                configuredPfemac1RefDiv = 0U;
            }
            break;
        }
    }
    else
    {
        configuredPfemac1RefDiv = 0U;
    }

    (void)configuredPfemac1RefDiv; /* Fix warning compiler: unused variable configuredPfemac1RefDiv */
}

static void CALCULATE_CONFIGURED_PFEMAC2_REF_DIV_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (PFEMAC2_REF_DIV_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredPfemac2RefDiv = bufferFreqs[BUFFER_PFEMAC2REFDIV_FIRC];
            }
            break;
            case PFE_MAC_0_EXT_REF_CLK:
            {
                configuredPfemac2RefDiv = bufferFreqs[BUFFER_PFEMAC2REFDIV_pfemac2extref];
            }
            break;
            default:
            {
                configuredPfemac2RefDiv = 0U;
            }
            break;
        }
    }
    else
    {
        configuredPfemac2RefDiv = 0U;
    }

    (void)configuredPfemac2RefDiv; /* Fix warning compiler: unused variable configuredPfemac2RefDiv */
}

static void CALCULATE_CONFIGURED_PFEMAC0_TX_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (PFEMAC0_TX_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredPfemac0txClk = bufferFreqs[BUFFER_FIRC];
            }
            break;
            case PERIPH_PLL_PHI5_CLK:
            {
                configuredPfemac0txClk = bufferFreqs[BUFFER_PERIPHPLLPHI5_PERIPHPLL];
            }
            break;
            case PFE_MAC_0_EXT_TX_CLK:
            {
                configuredPfemac0txClk = bufferFreqs[BUFFER_pfemac0exttx];
            }
            break;
            case PFE_MAC_0_EXT_REF_CLK:
            {
                configuredPfemac0txClk = bufferFreqs[BUFFER_pfemac0extref];
            }
            break;
            case SERDES_1_LANE_0_TX:
            {
                configuredPfemac0txClk = bufferFreqs[BUFFER_SERDES1LANE0TX];
            }
            break;
            default:
            {
                configuredPfemac0txClk = 0U;
            }
            break;
        }
    }
    else
    {
        configuredPfemac0txClk = 0U;
    }

    (void)configuredPfemac0txClk; /* Fix warning compiler: unused variable configuredPfemac0txClk */
}

static void CALCULATE_CONFIGURED_PFEMAC1_TX_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (PFEMAC1_TX_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredPfemac1txClk = bufferFreqs[BUFFER_FIRC];
            }
            break;
            case PERIPH_PLL_PHI5_CLK:
            {
                configuredPfemac1txClk = bufferFreqs[BUFFER_PERIPHPLLPHI5_PERIPHPLL];
            }
            break;
            case PFE_MAC_1_EXT_TX_CLK:
            {
                configuredPfemac1txClk = bufferFreqs[BUFFER_pfemac1exttx];
            }
            break;
            case PFE_MAC_1_EXT_REF_CLK:
            {
                configuredPfemac1txClk = bufferFreqs[BUFFER_pfemac1extref];
            }
            break;
            case SERDES_1_LANE_1_TX:
            {
                configuredPfemac1txClk = bufferFreqs[BUFFER_SERDES1LANE1TX];
            }
            break;
            default:
            {
                configuredPfemac1txClk = 0U;
            }
            break;
        }
    }
    else
    {
        configuredPfemac1txClk = 0U;
    }

    (void)configuredPfemac1txClk; /* Fix warning compiler: unused variable configuredPfemac1txClk */
}

static void CALCULATE_CONFIGURED_PFEMAC2_TX_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (PFEMAC2_TX_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredPfemac2txClk = bufferFreqs[BUFFER_FIRC];
            }
            break;
            case PERIPH_PLL_PHI5_CLK:
            {
                configuredPfemac2txClk = bufferFreqs[BUFFER_PERIPHPLLPHI5_PERIPHPLL];
            }
            break;
            case PFE_MAC_2_EXT_TX_CLK:
            {
                configuredPfemac2txClk = bufferFreqs[BUFFER_pfemac2exttx];
            }
            break;
            case PFE_MAC_2_EXT_REF_CLK:
            {
                configuredPfemac2txClk = bufferFreqs[BUFFER_pfemac2extref];
            }
            break;
            case SERDES_0_LANE_1_TX:
            {
                configuredPfemac2txClk = bufferFreqs[BUFFER_SERDES0LANE1TX];
            }
            break;
            default:
            {
                configuredPfemac2txClk = 0U;
            }
            break;
        }
    }
    else
    {
        configuredPfemac2txClk = 0U;
    }

    (void)configuredPfemac2txClk; /* Fix warning compiler: unused variable configuredPfemac2txClk */
}

static void CALCULATE_CONFIGURED_PFEMAC0_RX_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (PFEMAC0_RX_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredPfemac0rxClk = bufferFreqs[BUFFER_FIRC];
            }
            break;
            case PFE_MAC_0_EXT_RX_CLK:
            {
                configuredPfemac0rxClk = bufferFreqs[BUFFER_pfemac0extrx];
            }
            break;
            case PFEMAC0_REF_DIV_CLK:
            {
                configuredPfemac0rxClk = configuredPfemac0RefDiv;
            }
            break;
            case SERDES_1_LANE_0_CDR:
            {
                configuredPfemac0rxClk = bufferFreqs[BUFFER_SERDES1LANE0CDR];
            }
            break;
            default:
            {
                configuredPfemac0rxClk = 0U;
            }
            break;
        }
    }
    else
    {
        configuredPfemac0rxClk = 0U;
    }

    (void)configuredPfemac0rxClk; /* Fix warning compiler: unused variable configuredPfemac0rxClk */
}

static void CALCULATE_CONFIGURED_PFEMAC1_RX_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (PFEMAC1_RX_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredPfemac1rxClk = bufferFreqs[BUFFER_FIRC];
            }
            break;
            case PERIPH_PLL_PHI5_CLK:
            {
                configuredPfemac1rxClk = bufferFreqs[BUFFER_PERIPHPLLPHI5_PERIPHPLL];
            }
            break;
            case PFE_MAC_1_EXT_RX_CLK:
            {
                configuredPfemac1rxClk = bufferFreqs[BUFFER_pfemac1extrx];
            }
            break;
            case PFEMAC1_REF_DIV_CLK:
            {
                configuredPfemac1rxClk = configuredPfemac1RefDiv;
            }
            break;
            case SERDES_1_LANE_1_CDR:
            {
                configuredPfemac1rxClk = bufferFreqs[BUFFER_SERDES1LANE0CDR];
            }
            break;
            default:
            {
                configuredPfemac1rxClk = 0U;
            }
            break;
        }
    }
    else
    {
        configuredPfemac1rxClk = 0U;
    }

    (void)configuredPfemac1rxClk; /* Fix warning compiler: unused variable configuredPfemac1rxClk */
}

static void CALCULATE_CONFIGURED_PFEMAC2_RX_CLK(void)
{
    uint32 i;

    /* Find configured clock */
    const Clock_Ip_SelectorConfigType *selector = NULL;

    for (i = 0U; i < clock_config->selectorsCount; i++)
    {
        if (PFEMAC2_RX_CLK == clock_config->selectors[i].name)
        {
            selector = &clock_config->selectors[i];
            break;
        }
    }

    if (selector != NULL)
    {
        switch(selector->value)
        {
            case FIRC_CLK:
            {
                configuredPfemac2rxClk = bufferFreqs[BUFFER_FIRC];
            }
            break;
            case PERIPH_PLL_PHI5_CLK:
            {
                configuredPfemac2rxClk = bufferFreqs[BUFFER_PERIPHPLLPHI5_PERIPHPLL];
            }
            break;
            case PFE_MAC_2_EXT_RX_CLK:
            {
                configuredPfemac2rxClk = bufferFreqs[BUFFER_pfemac2extrx];
            }
            break;
            case PFEMAC2_REF_DIV_CLK:
            {
                configuredPfemac2rxClk = configuredPfemac2RefDiv;
            }
            break;
            case SERDES_0_LANE_1_CDR:
            {
                configuredPfemac2rxClk = bufferFreqs[BUFFER_SERDES0LANE1CDR];
            }
            break;
            default:
            {
                configuredPfemac2rxClk = 0U;
            }
            break;
        }
    }
    else
    {
        configuredPfemac2rxClk = 0U;
    }

    (void)configuredPfemac2rxClk; /* Fix warning compiler: unused variable configuredPfemac2rxClk */
}

static void IntegerDividersModule_A(void)
{
    uint32 dividerValue = 0U;
    uint8 i;

    for (i = 0U; i < clock_config->dividersCount; i++)
    {
        if (((uint8)clock_config->dividers[i].name) > ((uint8)THE_LAST_PRODUCER_CLK))
        {
            if (FLEXRAY_CLK == clock_config->dividers[i].name)
            {
                dividerValue = clock_config->dividers[i].value;
                break;
            }
        }
    }

    if (dividerValue != 0U)
    {
        configuredFlexRayClk = configuredFlexRayClk / dividerValue;
    }
    else
    {
        configuredFlexRayClk = 0U;
    }

    dividerValue = 0U;

    for (i = 0U; i < clock_config->dividersCount; i++)
    {
        if (((uint8)clock_config->dividers[i].name) > ((uint8)THE_LAST_PRODUCER_CLK))
        {
            if (GMAC_TS_CLK == clock_config->dividers[i].name)
            {
                dividerValue = clock_config->dividers[i].value;
                break;
            }
        }
    }
    if (dividerValue != 0U)
    {
        configuredGmacTsClk= configuredGmacTsClk / dividerValue;
    }
    else
    {
        configuredGmacTsClk = 0U;
    }

    dividerValue = 0U;

    for (i = 0U; i < clock_config->dividersCount; i++)
    {
        if (((uint8)clock_config->dividers[i].name) > ((uint8)THE_LAST_PRODUCER_CLK))
        {
            if (GMAC0_TX_CLK == clock_config->dividers[i].name)
            {
                dividerValue = clock_config->dividers[i].value;
                break;
            }
        }
    }
    if (dividerValue != 0U)
    {
        configuredGmacTxClk= configuredGmacTxClk / dividerValue;
    }
    else
    {
        configuredGmacTxClk = 0U;
    }


#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void IntegerDividersModule_B(void)
{
    uint32 dividerValue = 0U;
    uint8 i;

    for (i = 0U; i < clock_config->dividersCount; i++)
    {
        if (((uint8)clock_config->dividers[i].name) > ((uint8)THE_LAST_PRODUCER_CLK))
        {
            if (QSPI_CLK == clock_config->dividers[i].name)
            {
                dividerValue = clock_config->dividers[i].value;
                break;
            }
        }
    }
    if (dividerValue != 0U)
    {
        configuredQspiClk = configuredQspiClk / dividerValue;
    }
    else
    {
        configuredQspiClk = 0U;
    }

    dividerValue = 0U;

    for (i = 0U; i < clock_config->dividersCount; i++)
    {
        if (((uint8)clock_config->dividers[i].name) > ((uint8)THE_LAST_PRODUCER_CLK))
        {
            if (USDHC_CLK == clock_config->dividers[i].name)
            {
                dividerValue = clock_config->dividers[i].value;
                break;
            }
        }
    }
    if (dividerValue != 0U)
    {
        configuredUsdhcClk= configuredUsdhcClk / dividerValue;
    }
    else
    {
        configuredUsdhcClk = 0U;
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void IntegerDividersModule_C(void)
{
    uint32 dividerValue = 0U;
    uint8 i;

    for (i = 0U; i < clock_config->dividersCount; i++)
    {
        if (((uint8)clock_config->dividers[i].name) > ((uint8)THE_LAST_PRODUCER_CLK))
        {
            if (PFEMAC0_TX_CLK == clock_config->dividers[i].name)
            {
                dividerValue = clock_config->dividers[i].value;
                break;
            }
        }
    }
    if (dividerValue != 0U)
    {
        configuredPfemac0txClk = configuredPfemac0txClk / dividerValue;
    }
    else
    {
        configuredPfemac0txClk = 0U;
    }

    dividerValue = 0U;

    for (i = 0U; i < clock_config->dividersCount; i++)
    {
        if (((uint8)clock_config->dividers[i].name) > ((uint8)THE_LAST_PRODUCER_CLK))
        {
            if (PFEMAC1_TX_CLK == clock_config->dividers[i].name)
            {
                dividerValue = clock_config->dividers[i].value;
                break;
            }
        }
    }
    if (dividerValue != 0U)
    {
        configuredPfemac1txClk= configuredPfemac1txClk / dividerValue;
    }
    else
    {
        configuredPfemac1txClk = 0U;
    }

    dividerValue = 0U;

    for (i = 0U; i < clock_config->dividersCount; i++)
    {
        if (((uint8)clock_config->dividers[i].name) > ((uint8)THE_LAST_PRODUCER_CLK))
        {
            if (PFEMAC2_TX_CLK == clock_config->dividers[i].name)
            {
                dividerValue = clock_config->dividers[i].value;
                break;
            }
        }
    }
    if (dividerValue != 0U)
    {
        configuredPfemac2txClk= configuredPfemac2txClk / dividerValue;
    }
    else
    {
        configuredPfemac2txClk = 0U;
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

#define CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER 10U
#define CMU_FC_VAR 3.0F
#define CMU_REFERENCE_CLOCK_VARIATION  33.0F
#define CMU_MONITORED_CLOCK_VARIATION  11.0F

static void CMU_FXOSC_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[0U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[0U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FIRC] / 1000U;
    fMonitoredClk  = bufferFreqs[BUFFER_FXOSC] / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */
    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[0U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[0U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void CMU_FXOSC_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {
        cmuEntries[0U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[0U].refCount)) + (CMU_FC_VAR + 1.0F)));
        cmuEntries[0U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[0U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void CMU_XBAR_DIV3_CLK_FAIL_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[1U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[1U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FIRC] / 1000U;
    fMonitoredClk  = (configuredCoreClock / 3U) / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[1U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[1U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_XBAR_DIV3_CLK_FAIL_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {
        cmuEntries[1U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[1U].refCount)) + (CMU_FC_VAR + 1.0F)));
        cmuEntries[1U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[1U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void CMU_XBAR_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enableCoreM7_0, enableCoreM7_1, enableCoreM7_2;
    const Clock_Ip_CmuConfigType *cmuConfig;

    /* Check configuration Cmu core M7_0 */
    if (cmuEntries[2U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[2U].configIndex - 1U];
        enableCoreM7_0 = cmuConfig->enable;
    }
    else
    {
        enableCoreM7_0 = 0U;
    }
    /* Check configuration Cmu core M7_1 */
    if (cmuEntries[4U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[4U].configIndex - 1U];
        enableCoreM7_1 = cmuConfig->enable;
    }
    else
    {
        enableCoreM7_1 = 0U;
    }
    /* Check configuration Cmu core M7_2 */
    if (cmuEntries[5U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[5U].configIndex - 1U];
        enableCoreM7_2 = cmuConfig->enable;
    }
    else
    {
        enableCoreM7_2 = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FIRC] / 1000U;
    fMonitoredClk  = configuredCoreClock / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enableCoreM7_0;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[2U].enable = enableCoreM7_0;
    cmuEntries[4U].enable = enableCoreM7_1;
    cmuEntries[5U].enable = enableCoreM7_2;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[2U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);
    cmuEntries[4U].refCount = cmuEntries[2U].refCount;
    cmuEntries[5U].refCount = cmuEntries[2U].refCount;

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void CMU_XBAR_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

        cmuEntries[2U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[2U].refCount)) + (CMU_FC_VAR + 1.0F)));
        cmuEntries[2U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[2U].refCount)) - CMU_FC_VAR));
        cmuEntries[4U].hfRef = cmuEntries[2U].hfRef;
        cmuEntries[5U].hfRef = cmuEntries[2U].hfRef;

        cmuEntries[4U].lfRef = cmuEntries[2U].lfRef;
        cmuEntries[5U].lfRef = cmuEntries[2U].lfRef;
    }


#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void CMU_XBAR_DIV3_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[3U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[3U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FXOSC] / 1000U;
    fMonitoredClk  = (configuredCoreClock / 3U) / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[3U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[3U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_XBAR_DIV3_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

        cmuEntries[3U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[3U].refCount)) + (CMU_FC_VAR + 1.0F)));
        cmuEntries[3U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[3U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void CMU_PER_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[6U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[6U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FIRC] / 1000U;
    fMonitoredClk  = configuredPerClock / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[6U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[6U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void CMU_PER_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

        cmuEntries[6U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[6U].refCount)) + (CMU_FC_VAR + 1.0F)));
        cmuEntries[6U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[6U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_SERDES_REF_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[7U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[7U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FXOSC] / 1000U;
    fMonitoredClk  = bufferFreqs[BUFFER_PERIPHPLLPHI0_PERIPHPLL] / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[7U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[7U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void CMU_SERDES_REF_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

        cmuEntries[7U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[7U].refCount)) + (CMU_FC_VAR + 1.0F)));
        cmuEntries[7U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[7U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void CMU_FLEXRAY_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[8U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[8U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FXOSC] / 1000U;
    fMonitoredClk  = configuredFlexRayClk / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[8U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[8U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_FLEXRAY_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

        cmuEntries[8U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[8U].refCount)) + (CMU_FC_VAR + 1.0F)));
        cmuEntries[8U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[8U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_FLEXCAN_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[9U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[9U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FXOSC] / 1000U;
    fMonitoredClk  = configuredFlexCanClk / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[9U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[9U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_FLEXCAN_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

        cmuEntries[9U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[9U].refCount)) + (CMU_FC_VAR + 1.0F)));
        cmuEntries[9U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[9U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_GMAC0_TX_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[10U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[10U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FXOSC] / 1000U;
    fMonitoredClk  = configuredGmacTxClk / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[10U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[10U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_GMAC0_TX_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

        cmuEntries[10U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[10U].refCount)) + (CMU_FC_VAR + 1.0F)));
        cmuEntries[10U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[10U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}



static void CMU_GMAC_TS_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[11U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[11U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FXOSC] / 1000U;
    fMonitoredClk  = configuredGmacTsClk / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[11U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[11U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_GMAC_TS_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

        cmuEntries[11U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[11U].refCount)) + (CMU_FC_VAR + 1.0F)));
        cmuEntries[11U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[11U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_LIN_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[12U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[12U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FXOSC] / 1000U;
    fMonitoredClk  = configuredLinClk / (2U * 1000U);
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[12U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[12U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_LIN_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

        cmuEntries[12U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[12U].refCount)) + (CMU_FC_VAR + 1.0F)));
        cmuEntries[12U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[12U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}



static void CMU_QSPI_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[13U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[13U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FXOSC] / 1000U;
    fMonitoredClk  = configuredQspiClk / (2U * 1000U);
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[13U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[13U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_QSPI_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

        cmuEntries[13U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[13U].refCount)) + (CMU_FC_VAR + 1.0F)));
        cmuEntries[13U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[13U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_USDHC_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[14U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[14U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FXOSC] / 1000U;
    fMonitoredClk  = configuredUsdhcClk / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[14U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[14U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_USDHC_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {
        cmuEntries[14U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[14U].refCount)) + (CMU_FC_VAR + 1.0F)));
        cmuEntries[14U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[14U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_DDR_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[15U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[15U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FIRC] / 1000U;
    fMonitoredClk  = configuredDdrClk / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[15U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[15U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_DDR_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

        cmuEntries[15U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[15U].refCount)) + (CMU_FC_VAR + 1.0F)));
        cmuEntries[15U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[15U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}



static void CMU_GMAC0_RX_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[16U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[16U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FXOSC] / 1000U;
    fMonitoredClk  = configuredGmacRxClk / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[16U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[16U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_GMAC0_RX_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

    cmuEntries[16U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[16U].refCount)) + (CMU_FC_VAR + 1.0F)));
    cmuEntries[16U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[16U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_SPI_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[17U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[17U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FXOSC] / 1000U;
    fMonitoredClk  = configuredSpiClk / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[17U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[17U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_SPI_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

    cmuEntries[17U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[17U].refCount)) + (CMU_FC_VAR + 1.0F)));
    cmuEntries[17U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[17U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_CORE_A53_CLUSTER_0_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[18U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[18U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FXOSC] / 1000U;
    fMonitoredClk  = configuredA53coreClk / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[18U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[18U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_CORE_A53_CLUSTER_0_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

    cmuEntries[18U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[18U].refCount)) + (CMU_FC_VAR + 1.0F)));
    cmuEntries[18U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[18U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void CMU_CORE_A53_CLUSTER_1_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[19U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[19U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FIRC] / 1000U;
    fMonitoredClk  = configuredA53coreClk / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[19U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[19U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_CORE_A53_CLUSTER_1_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

    cmuEntries[19U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[19U].refCount)) + (CMU_FC_VAR + 1.0F)));
    cmuEntries[19U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[19U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

static void CMU_PFE_PE_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[20U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[20U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FXOSC] / 1000U;
    fMonitoredClk  = configuredPfepeClk / (2U * 1000U);
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[20U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[20U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_PFE_PE_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

    cmuEntries[20U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[20U].refCount)) + (CMU_FC_VAR + 1.0F)));
    cmuEntries[20U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[20U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_PFEMAC0_TX_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[21U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[21U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FXOSC] / 1000U;
    fMonitoredClk  = configuredPfemac0txClk / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[21U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[21U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_PFEMAC0_TX_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

    cmuEntries[21U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[21U].refCount)) + (CMU_FC_VAR + 1.0F)));
    cmuEntries[21U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[21U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_PFEMAC0_RX_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[22U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[22U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FXOSC] / 1000U;
    fMonitoredClk  = configuredPfemac0rxClk / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[22U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[22U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_PFEMAC0_RX_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

    cmuEntries[22U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[22U].refCount)) + (CMU_FC_VAR + 1.0F)));
    cmuEntries[22U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[22U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_PFEMAC1_TX_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[23U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[23U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FXOSC] / 1000U;
    fMonitoredClk  = configuredPfemac1txClk / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
/* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));

    cmuEntries[23U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[23U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_PFEMAC1_TX_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

    cmuEntries[23U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[23U].refCount)) + (CMU_FC_VAR + 1.0F)));
    cmuEntries[23U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[23U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_PFEMAC1_RX_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[24U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[24U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FXOSC] / 1000U;
    fMonitoredClk  = configuredPfemac1rxClk / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[24U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[24U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_PFEMAC1_RX_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

    cmuEntries[24U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[24U].refCount)) + (CMU_FC_VAR + 1.0F)));
    cmuEntries[24U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[24U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_PFEMAC2_TX_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[25U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[25U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FXOSC] / 1000U;
    fMonitoredClk  = configuredPfemac2txClk / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[25U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[25U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_PFEMAC2_TX_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

    cmuEntries[25U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[25U].refCount)) + (CMU_FC_VAR + 1.0F)));
    cmuEntries[25U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[25U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_PFEMAC2_RX_CLK_A(void)
{
    uint32 fReferenceClk, fMonitoredClk, fBusClk;
    uint32 cmp1, cmp2;
    uint8 enable;
    const Clock_Ip_CmuConfigType *cmuConfig;

    if (cmuEntries[26U].configIndex != CLOCK_ELEMENT_IS_NOT_UNDER_MCU_CONTROL)
    {
        cmuConfig = &clock_config->cmus[cmuEntries[26U].configIndex - 1U];
        enable = cmuConfig->enable;
    }
    else
    {
        enable = 0U;
    }

    fReferenceClk = bufferFreqs[BUFFER_FXOSC] / 1000U;
    fMonitoredClk  = configuredPfemac2rxClk / 1000U;
    fBusClk = (configuredCoreClock / 3U) / 1000U;

    tmpData.input1 = enable;                              /* Enable cmu */
    tmpData.input2 = fReferenceClk;                       /* Reference clock */
    tmpData.input3 = fMonitoredClk;                       /* fMonitoredClk */
    tmpData.input4 = fBusClk;                             /* frequency of safe clock */

    /* cmp1 = ceiling of (3 * fRef/ fBus) */
    cmp1 = 1U + (uint32)((float32)((3.0F * (float32)fReferenceClk) / (float32)fBusClk));
    /* cmp2 = ceiling of (8 + (5 * fRef / fMonitor)) */
    if (fMonitoredClk > 0U)
    {
        cmp2 = 9U + (uint32)((float32)((5.0F * (float32)fReferenceClk) / (float32)fMonitoredClk));
    }
    else
    {
        cmp2 = 0U;
    }

    cmuEntries[26U].enable = enable;
    /* REF count = Max(cmp1,cmp2) */
    cmuEntries[26U].refCount = (((cmp1 > cmp2) ? cmp1 : cmp2) * CMU_REFERENCE_COUNTER_MINIMUM_VALUE_MULTIPLIER);

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}


static void CMU_PFEMAC2_RX_CLK_B(void)
{
    float32 fReferenceClk, fMonitoredClk;

    fReferenceClk = (float32)tmpData.input2;                       /* Reference clock */
    fMonitoredClk = (float32)tmpData.input3;                       /* fMonitoredClk */
    if (tmpData.input3 > 0U)
    {

    cmuEntries[26U].hfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F + CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F - CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[26U].refCount)) + (CMU_FC_VAR + 1.0F)));
    cmuEntries[26U].lfRef = (uint32)((float32)((((fMonitoredClk * (1000.0F - CMU_MONITORED_CLOCK_VARIATION)) / (fReferenceClk * (1000.0F + CMU_REFERENCE_CLOCK_VARIATION))) * ((float32)cmuEntries[26U].refCount)) - CMU_FC_VAR));
    }

#ifdef RECORD_CALLBACK_TIMESTAMPS
    uint32 oldSystickCounter = systickCounter;
    systickCounter = S32_SysTick->CVR;
    timestampCallback[timestampIndexEntry++] = oldSystickCounter - systickCounter;
#endif
}

const Clock_Ip_ClockConfigType* GetClockConfig(void)
{
    return clock_config;
}

void McMeEnterKey(void)
{
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_3 The cast is used to access memory mapped registers.
    */
    MC_ME->CTL_KEY = 0x5AF0;                                         /* Enter key */

    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_3 The cast is used to access memory mapped registers.
    */
    MC_ME->CTL_KEY = 0xA50F;                                         /* Enter inverted key */
}

static void CallbackDelay(void)
{
    boolean TimeoutOccurred = FALSE;
    uint32 StartTime;
    uint32 ElapsedTime;
    uint32 TimeoutTicks;

    /* Wait until the update has finished. */
    ClockStartTimeout(&StartTime, &ElapsedTime, &TimeoutTicks, 10U);
    do
    {
        TimeoutOccurred = ClockTimeoutExpired(&StartTime, &ElapsedTime, TimeoutTicks);
    }
    while(FALSE == TimeoutOccurred);
}



const CalcFreqCallback calcFreqCallbacks[CALC_FREQ_CALLBACKS_NO] = { \
CONFIG_ELEMENTS_MAPPINGS_01, CONFIG_ELEMENTS_MAPPINGS_02, \
NOT_UNDER_MCU_CONTROL_A, NOT_UNDER_MCU_CONTROL_B, NOT_UNDER_MCU_CONTROL_C, NOT_UNDER_MCU_CONTROL_D, NOT_UNDER_MCU_CONTROL_E, NOT_UNDER_MCU_CONTROL_F, NOT_UNDER_MCU_CONTROL_G, \
IRCOSCS_XOSCS_SERDES_CLOCKS, EXTERNAL_CLOCKS, COREPLL_A, COREPLL_B, COREPLL_C, PERIPHPLL_A, PERIPHPLL_B, PERIPHPLL_C, DDRPLL_A, DDRPLL_B, DDRPLL_C, ACCELPLL_A, ACCELPLL_B, ACCELPLL_C, \
COREDFS1_A, COREDFS1_B, CALCULATE_CONFIGURED_CORE_CLK, COREDFS2_A, COREDFS2_B, COREDFS3_A, COREDFS3_B, COREDFS4_A, COREDFS4_B, COREDFS5_A, COREDFS5_B, COREDFS6_A, COREDFS6_B, \
PERIPHDFS1_A, PERIPHDFS1_B, PERIPHDFS2_A, PERIPHDFS2_B, PERIPHDFS3_A, PERIPHDFS3_B, PERIPHDFS4_A, PERIPHDFS4_B, PERIPHDFS5_A, PERIPHDFS5_B, PERIPHDFS6_A, PERIPHDFS6_B, \
IntegerDividers_A, IntegerDividers_B, IntegerDividers_C, IntegerDividers_D, IntegerDividers_E, IntegerDividers_F, IntegerDividers_G, IntegerDividers_I, IntegerDividers_J, \
IntegerDividers_K, IntegerDividers_N, IntegerDividers_O, IntegerDividers_P, IntegerDividers_Q, IntegerDividers_R, PCFS_COREPLL_DFS1_A, PCFS_COREPLL_DFS1_B, PCFS_COREPLL_DFS1_C, \
PCFS_COREPLL_DFS1_D, PCFS_COREPLL_DFS1_E, PCFS_COREPLL_PHI0_A, PCFS_COREPLL_PHI0_B, PCFS_COREPLL_PHI0_C, PCFS_COREPLL_PHI0_D, PCFS_COREPLL_PHI0_E, PCFS_ACCELPLL_PHI1_A, \
PCFS_ACCELPLL_PHI1_B, PCFS_ACCELPLL_PHI1_C, PCFS_ACCELPLL_PHI1_D, PCFS_ACCELPLL_PHI1_E, \
CALCULATE_CONFIGURED_PER_CLK, CALCULATE_CONFIGURED_FLEXRAY_CLK, CALCULATE_CONFIGURED_FLEXCAN_CLK, CALCULATE_CONFIGURED_GMAC0_TX_CLK, CALCULATE_CONFIGURED_GMAC0_TS_CLK,\
CALCULATE_CONFIGURED_LIN_CLK, CALCULATE_CONFIGURED_QSPI_CLK, CALCULATE_CONFIGURED_USDHC_CLK, CALCULATE_CONFIGURED_DDR_CLK, CALCULATE_CONFIGURED_GMAC_REF_DIV_CLK, CALCULATE_CONFIGURED_GMAC0_RX_CLK, \
CALCULATE_CONFIGURED_SPI_CLK, CALCULATE_CONFIGURED_A53_CORE_CLK, CALCULATE_CONFIGURED_PFE_PE_CLK, CALCULATE_CONFIGURED_PFEMAC0_REF_DIV_CLK, CALCULATE_CONFIGURED_PFEMAC1_REF_DIV_CLK, \
CALCULATE_CONFIGURED_PFEMAC2_REF_DIV_CLK, CALCULATE_CONFIGURED_PFEMAC0_TX_CLK, CALCULATE_CONFIGURED_PFEMAC1_TX_CLK, CALCULATE_CONFIGURED_PFEMAC2_TX_CLK, CALCULATE_CONFIGURED_PFEMAC0_RX_CLK, \
CALCULATE_CONFIGURED_PFEMAC1_RX_CLK, CALCULATE_CONFIGURED_PFEMAC2_RX_CLK, IntegerDividersModule_A, IntegerDividersModule_B, IntegerDividersModule_C, CMU_FXOSC_CLK_A, CMU_FXOSC_CLK_B, \
CMU_XBAR_DIV3_CLK_FAIL_A, CMU_XBAR_DIV3_CLK_FAIL_B, CMU_XBAR_CLK_A, CMU_XBAR_CLK_B, CMU_XBAR_DIV3_CLK_A, CMU_XBAR_DIV3_CLK_B, CMU_PER_CLK_A, CMU_PER_CLK_B, CMU_SERDES_REF_CLK_A, \
CMU_SERDES_REF_CLK_B, CMU_FLEXRAY_CLK_A, CMU_FLEXRAY_CLK_B, CMU_FLEXCAN_CLK_A, CMU_FLEXCAN_CLK_B, CMU_GMAC0_TX_CLK_A, CMU_GMAC0_TX_CLK_B, CMU_GMAC_TS_CLK_A, CMU_GMAC_TS_CLK_B, CMU_LIN_CLK_A, \
CMU_LIN_CLK_B, CMU_QSPI_CLK_A, CMU_QSPI_CLK_B, CMU_USDHC_CLK_A, CMU_USDHC_CLK_B, CMU_DDR_CLK_A, CMU_DDR_CLK_B, CMU_GMAC0_RX_CLK_A, CMU_GMAC0_RX_CLK_B, CMU_SPI_CLK_A, CMU_SPI_CLK_B, \
CMU_CORE_A53_CLUSTER_0_CLK_A, CMU_CORE_A53_CLUSTER_0_CLK_B, CMU_CORE_A53_CLUSTER_1_CLK_A, CMU_CORE_A53_CLUSTER_1_CLK_B, CMU_PFE_PE_CLK_A, CMU_PFE_PE_CLK_B, CMU_PFEMAC0_TX_CLK_A, \
CMU_PFEMAC0_TX_CLK_B, CMU_PFEMAC0_RX_CLK_A, CMU_PFEMAC0_RX_CLK_B, CMU_PFEMAC1_TX_CLK_A, CMU_PFEMAC1_TX_CLK_B, CMU_PFEMAC1_RX_CLK_A, CMU_PFEMAC1_RX_CLK_B, CMU_PFEMAC2_TX_CLK_A, \
CMU_PFEMAC2_TX_CLK_B, CMU_PFEMAC2_RX_CLK_A, CMU_PFEMAC2_RX_CLK_B, \

CallbackDelay
};


const consumerClockCallback consumerClockCallbacks[CONSUMER_CALLBACKS_COUNT] =
{
get_ADC0_CLK_Frequency,
get_ADC1_CLK_Frequency,
get_CLKOUT0_CLK_Frequency,
get_CLKOUT1_CLK_Frequency,
get_CORE_A53_CLUSTER_0_CLK_Frequency,
get_CORE_A53_CLUSTER_1_CLK_Frequency,
get_CORE_M7_0_CLK_Frequency,
get_CORE_M7_1_CLK_Frequency,
get_CORE_M7_2_CLK_Frequency,
get_CRC0_CLK_Frequency,
get_CTU0_CLK_Frequency,
get_CTU1_CLK_Frequency,
get_DAPB_CLK_Frequency,
get_DMA0_CLK_Frequency,
get_DMA1_CLK_Frequency,
get_DMAMUX0_CLK_Frequency,
get_DMAMUX1_CLK_Frequency,
get_DMAMUX2_CLK_Frequency,
get_DMAMUX3_CLK_Frequency,
get_DMA_CRC0_CLK_Frequency,
get_DMA_CRC1_CLK_Frequency,
get_EIM0_CLK_Frequency,
get_EIM1_CLK_Frequency,
get_EIM2_CLK_Frequency,
get_EIM3_CLK_Frequency,
get_EIM_CLK_Frequency,
get_ERM0_CLK_Frequency,
get_FLEXCAN_CLK_Frequency,
get_FLEXCAN0_CLK_Frequency,
get_FLEXCAN1_CLK_Frequency,
get_FLEXCAN2_CLK_Frequency,
get_FLEXCAN3_CLK_Frequency,
get_FLEXRAY_CLK_Frequency,
get_FRAY0_CLK_Frequency,
get_FLEXTIMERA_CLK_Frequency,
get_FTIMER0_CLK_Frequency,
get_FLEXTIMERB_CLK_Frequency,
get_FTIMER1_CLK_Frequency,
get_GMAC_TS_CLK_Frequency,
get_GMAC0_RX_CLK_Frequency,
get_GMAC0_TX_CLK_Frequency,
get_GMAC0_TS_CLK_Frequency,
get_IIC0_CLK_Frequency,
get_IIC1_CLK_Frequency,
get_IIC2_CLK_Frequency,
get_IIC3_CLK_Frequency,
get_IIC4_CLK_Frequency,
get_LBIST_CLK_Frequency,
get_LBIST0_CLK_Frequency,
get_LBIST1_CLK_Frequency,
get_LBIST2_CLK_Frequency,
get_LBIST3_CLK_Frequency,
get_LBIST4_CLK_Frequency,
get_LBIST5_CLK_Frequency,
get_LBIST6_CLK_Frequency,
get_LBIST7_CLK_Frequency,
get_LIN_CLK_Frequency,
get_LIN0_CLK_Frequency,
get_LIN1_CLK_Frequency,
get_LIN2_CLK_Frequency,
get_OCOTP0_CLK_Frequency,
get_PFEMAC0_RX_CLK_Frequency,
get_PFEMAC0_TX_CLK_Frequency,
get_PFEMAC1_RX_CLK_Frequency,
get_PFEMAC1_TX_CLK_Frequency,
get_PFEMAC2_RX_CLK_Frequency,
get_PFEMAC2_TX_CLK_Frequency,
get_PIT0_CLK_Frequency,
get_PIT1_CLK_Frequency,
get_QSPI_CLK_Frequency,
get_QSPI0_CLK_Frequency,
get_RTC0_CLK_Frequency,
get_SIUL0_CLK_Frequency,
get_SIUL1_CLK_Frequency,
get_SPI_CLK_Frequency,
get_SPI0_CLK_Frequency,
get_SPI1_CLK_Frequency,
get_SPI2_CLK_Frequency,
get_SPI3_CLK_Frequency,
get_SPI4_CLK_Frequency,
get_SPI5_CLK_Frequency,
get_STM0_CLK_Frequency,
get_STM1_CLK_Frequency,
get_STM2_CLK_Frequency,
get_STM3_CLK_Frequency,
get_STM4_CLK_Frequency,
get_STM5_CLK_Frequency,
get_STM6_CLK_Frequency,
get_STM7_CLK_Frequency,
get_SWT0_CLK_Frequency,
get_SWT1_CLK_Frequency,
get_SWT2_CLK_Frequency,
get_SWT3_CLK_Frequency,
get_SWT4_CLK_Frequency,
get_SWT5_CLK_Frequency,
get_SWT6_CLK_Frequency,
get_USDHC_CLK_Frequency,
get_USDHC0_CLK_Frequency,
get_WKPU0_CLK_Frequency,
get_XBAR_DIV3_FAIL_CLK_Frequency,
};
static uint32 get_ADC0_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[PER_CLK]];
}
static uint32 get_ADC1_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[PER_CLK]];
}
static uint32 get_CTU0_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[PER_CLK]];
}
static uint32 get_CTU1_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[PER_CLK]];
}
static uint32 get_CORE_A53_CLUSTER_0_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[A53_CORE_CLK]];
}
static uint32 get_CORE_A53_CLUSTER_1_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[A53_CORE_CLK]];
}
static uint32 get_CORE_M7_0_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_CLK]];
}
static uint32 get_CORE_M7_1_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_CLK]];
}
static uint32 get_CORE_M7_2_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_CLK]];
}
static uint32 get_DMA0_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_CLK]];
}
static uint32 get_DMA1_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_CLK]];
}
static uint32 get_DMA_CRC0_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_CLK]];
}
static uint32 get_DMA_CRC1_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_CLK]];
}
static uint32 get_CRC0_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV3_CLK]];
}
static uint32 get_DMAMUX0_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV3_CLK]];
}
static uint32 get_DMAMUX1_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV3_CLK]];
}
static uint32 get_DMAMUX2_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV3_CLK]];
}
static uint32 get_DMAMUX3_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV3_CLK]];
}
static uint32 get_IIC0_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV3_CLK]];
}
static uint32 get_IIC1_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV3_CLK]];
}
static uint32 get_IIC2_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV3_CLK]];
}
static uint32 get_IIC3_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV3_CLK]];
}
static uint32 get_IIC4_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV3_CLK]];
}
static uint32 get_PIT0_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV3_CLK]];
}
static uint32 get_PIT1_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV3_CLK]];
}
static uint32 get_STM0_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV3_CLK]];
}
static uint32 get_STM1_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV3_CLK]];
}
static uint32 get_STM2_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV3_CLK]];
}
static uint32 get_STM3_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV3_CLK]];
}
static uint32 get_STM4_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV3_CLK]];
}
static uint32 get_STM5_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV3_CLK]];
}
static uint32 get_STM6_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV3_CLK]];
}
static uint32 get_STM7_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV3_CLK]];
}
static uint32 get_XBAR_DIV3_FAIL_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV3_CLK]];
}
static uint32 get_EIM0_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[A53_CORE_DIV10_CLK]];
}
static uint32 get_EIM1_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV6_CLK]];
}
static uint32 get_EIM2_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV6_CLK]];
}
static uint32 get_EIM3_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV6_CLK]];
}
static uint32 get_EIM_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV6_CLK]];
}
static uint32 get_ERM0_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV6_CLK]];
}
static uint32 get_RTC0_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV6_CLK]];
}
static uint32 get_WKPU0_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[XBAR_DIV6_CLK]];
}
static uint32 get_OCOTP0_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[FIRC_CLK]];
}
static uint32 get_SIUL0_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[FIRC_CLK]];
}
static uint32 get_SIUL1_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[FIRC_CLK]];
}
static uint32 get_SWT0_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[FIRC_CLK]];
}
static uint32 get_SWT1_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[FIRC_CLK]];
}
static uint32 get_SWT2_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[FIRC_CLK]];
}
static uint32 get_SWT3_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[FIRC_CLK]];
}
static uint32 get_SWT4_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[FIRC_CLK]];
}
static uint32 get_SWT5_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[FIRC_CLK]];
}
static uint32 get_SWT6_CLK_Frequency(void) {
    /* Retrun frequency of a given clock */
    return bufferFreqs[freqPointers[FIRC_CLK]];
}
static uint32 get_CLKOUT0_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][1U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][1U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][1U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_CLKOUT1_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][2U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][2U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][2U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_DAPB_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][0U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][0U]->divider[1U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][0U]->divider[1U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_LBIST_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][0U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][0U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][0U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_LBIST0_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][0U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][0U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][0U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_LBIST1_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][0U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][0U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][0U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_LBIST2_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][0U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][0U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][0U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_LBIST3_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][0U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][0U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][0U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_LBIST4_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][0U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][0U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][0U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_LBIST5_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][0U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][0U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][0U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_LBIST6_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][0U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][0U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][0U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_LBIST7_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][0U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][0U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][0U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_FLEXCAN_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][7U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    return frequency;
}
static uint32 get_FLEXCAN0_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][7U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    return frequency;
}
static uint32 get_FLEXCAN1_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][7U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    return frequency;
}
static uint32 get_FLEXCAN2_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][7U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    return frequency;
}
static uint32 get_FLEXCAN3_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][7U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    return frequency;
}
static uint32 get_FLEXRAY_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][6U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][6U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][6U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_FRAY0_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][6U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][6U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][6U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_FLEXTIMERA_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][4U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][4U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][4U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_FTIMER0_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][4U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][4U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][4U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_FLEXTIMERB_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][5U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][5U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][5U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_FTIMER1_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][5U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][5U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][5U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_GMAC0_RX_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][11U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];  /*  Selector value */
    return frequency;
}
static uint32 get_GMAC_TS_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][9U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][9U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][9U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_GMAC0_TS_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][9U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][9U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][9U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_GMAC0_TX_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][10U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];  /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][10U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                           /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][10U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                     /*  Apply divider value */
    return frequency;
}
static uint32 get_LIN_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][8U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    return frequency;
}
static uint32 get_LIN0_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][8U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    return frequency;
}
static uint32 get_LIN1_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][8U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    return frequency;
}
static uint32 get_LIN2_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][8U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    return frequency;
}
static uint32 get_PFEMAC0_RX_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[2U][4U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    return frequency;
}
static uint32 get_PFEMAC0_TX_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[2U][1U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[2U][1U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[2U][1U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_PFEMAC1_RX_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[2U][5U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    return frequency;
}
static uint32 get_PFEMAC1_TX_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[2U][2U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[2U][2U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[2U][2U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_PFEMAC2_RX_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[2U][6U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    return frequency;
}
static uint32 get_PFEMAC2_TX_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[2U][3U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];   /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[2U][3U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                            /*  Divider enable/disable */
    frequency                                 /= (((cgm[2U][3U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                      /*  Apply divider value */
    return frequency;
}
static uint32 get_QSPI_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][12U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];  /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][12U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                           /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][12U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                     /*  Apply divider value */
    return frequency;
}
static uint32 get_QSPI0_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][12U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];  /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][12U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                           /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][12U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                     /*  Apply divider value */
    return frequency;
}
static uint32 get_SPI_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][16U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];  /*  Selector value */
    return frequency;
}
static uint32 get_SPI0_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][16U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];  /*  Selector value */
    return frequency;
}
static uint32 get_SPI1_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][16U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];  /*  Selector value */
    return frequency;
}
static uint32 get_SPI2_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][16U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];  /*  Selector value */
    return frequency;
}
static uint32 get_SPI3_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][16U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];  /*  Selector value */
    return frequency;
}
static uint32 get_SPI4_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][16U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];  /*  Selector value */
    return frequency;
}
static uint32 get_SPI5_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][16U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];  /*  Selector value */
    return frequency;
}
static uint32 get_USDHC_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][14U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];  /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][14U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                           /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][14U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                     /*  Apply divider value */
    return frequency;
}
static uint32 get_USDHC0_CLK_Frequency(void) {

    uint32 frequency;
    frequency                                  = bufferFreqs[freqPointers[hardwareValue_selectorEntry[((cgm[0U][14U]->CSS & MC_CGM_MUX_CSS_SELSTAT_MASK) >> MC_CGM_MUX_CSS_SELSTAT_SHIFT)]]];  /*  Selector value */
    frequency                                 &= enableDisableMask[((cgm[0U][14U]->divider[0U] & MC_CGM_MUX_DC_DE_MASK) >> MC_CGM_MUX_DC_DE_SHIFT)];                                           /*  Divider enable/disable */
    frequency                                 /= (((cgm[0U][14U]->divider[0U] & MC_CGM_MUX_DC_DIV_MASK) >> MC_CGM_MUX_DC_DIV_SHIFT) + 1U);                                                     /*  Apply divider value */
    return frequency;
}

#if (defined(CLOCK_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT))
void SpecificSetUserAccessAllowed(void)
{
    /* PLLDIG SetUserAccessAllowed */
#if ( defined(MCAL_PLLDIG_REG_PROT_AVAILABLE) && (STD_ON == MCAL_PLLDIG_REG_PROT_AVAILABLE) )
#if (defined(CORE_PLL_BASE))
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_3 The cast is used to access memory mapped registers.
    */
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_4 A function should be used in preference to a function-like macro where they are interchangeable.
    */
    SET_USER_ACCESS_ALLOWED(CORE_PLL_BASE, PLLDIG_PROT_MEM_U32);
#endif
#if (defined(PERIPH_PLL_BASE))
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_3 The cast is used to access memory mapped registers.
    */
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_4 A function should be used in preference to a function-like macro where they are interchangeable.
    */
    SET_USER_ACCESS_ALLOWED(PERIPH_PLL_BASE, PLLDIG_PROT_MEM_U32);
#endif
#if (defined(ACCEL_PLL_BASE))
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_3 The cast is used to access memory mapped registers.
    */
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_4 A function should be used in preference to a function-like macro where they are interchangeable.
    */
    SET_USER_ACCESS_ALLOWED(ACCEL_PLL_BASE, PLLDIG_PROT_MEM_U32);
#endif
#if (defined(DDR_PLL_BASE))
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_3 The cast is used to access memory mapped registers.
    */
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_4 A function should be used in preference to a function-like macro where they are interchangeable.
    */
    SET_USER_ACCESS_ALLOWED(DDR_PLL_BASE, PLLDIG_PROT_MEM_U32);
#endif
#endif /* MCAL_PLLDIG_REG_PROT_AVAILABLE */

    /* DFS SetUserAccessAllowed */
#if (defined(MCAL_DFS_REG_PROT_AVAILABLE) && (STD_ON == MCAL_DFS_REG_PROT_AVAILABLE))
#if (defined(CORE_DFS_BASE))
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_3 The cast is used to access memory mapped registers.
    */
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_4 A function should be used in preference to a function-like macro where they are interchangeable.
    */
    SET_USER_ACCESS_ALLOWED(CORE_DFS_BASE, DFS_PROT_MEM_U32);
#endif
#if (defined(PERIPH_DFS_BASE))
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_3 The cast is used to access memory mapped registers.
    */
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_4 A function should be used in preference to a function-like macro where they are interchangeable.
    */
    SET_USER_ACCESS_ALLOWED(PERIPH_DFS_BASE, DFS_PROT_MEM_U32);
#endif
#endif /* MCAL_DFS_REG_PROT_AVAILABLE */

    /* FXOSC SetUserAccessAllowed */
#if (defined(MCAL_FXOSC_REG_PROT_AVAILABLE) && (STD_ON == MCAL_FXOSC_REG_PROT_AVAILABLE))
#if (defined(FXOSC_BASE))
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_3 The cast is used to access memory mapped registers.
    */
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_4 A function should be used in preference to a function-like macro where they are interchangeable.
    */
    SET_USER_ACCESS_ALLOWED(FXOSC_BASE, FXOSC_PROT_MEM_U32);
#endif
#endif /* MCAL_FXOSC_REG_PROT_AVAILABLE */

    /* MC_CGM SetUserAccessAllowed */
#if ( defined(MCAL_MC_CGM_REG_PROT_AVAILABLE) && (STD_ON == MCAL_MC_CGM_REG_PROT_AVAILABLE) )
#if (defined(MC_CGM_0_BASE))
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_3 The cast is used to access memory mapped registers.
    */
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_4 A function should be used in preference to a function-like macro where they are interchangeable.
    */
    SET_USER_ACCESS_ALLOWED(MC_CGM_0_BASE, MC_CGM_PROT_MEM_U32);
#endif
#if (defined(MC_CGM_1_BASE))
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_3 The cast is used to access memory mapped registers.
    */
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_4 A function should be used in preference to a function-like macro where they are interchangeable.
    */
    SET_USER_ACCESS_ALLOWED(MC_CGM_1_BASE, MC_CGM_PROT_MEM_U32);
#endif
#if (defined(MC_CGM_2_BASE))
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_3 The cast is used to access memory mapped registers.
    */
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_4 A function should be used in preference to a function-like macro where they are interchangeable.
    */
    SET_USER_ACCESS_ALLOWED(MC_CGM_2_BASE, MC_CGM_PROT_MEM_U32);
#endif
#if (defined(MC_CGM_5_BASE))
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_3 The cast is used to access memory mapped registers.
    */
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_4 A function should be used in preference to a function-like macro where they are interchangeable.
    */
    SET_USER_ACCESS_ALLOWED(MC_CGM_5_BASE, MC_CGM_PROT_MEM_U32);
#endif
#endif /* MCAL_MC_CGM_REG_PROT_AVAILABLE */

    /* CMU SetUserAccessAllowed */
#if (defined(MCAL_CMU_REG_PROT_AVAILABLE) && (STD_ON == MCAL_CMU_REG_PROT_AVAILABLE))
#if (defined(CMU_FC_0_BASE))
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_3 The cast is used to access memory mapped registers.
    */
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_4 A function should be used in preference to a function-like macro where they are interchangeable.
    */
    SET_USER_ACCESS_ALLOWED(CMU_FC_0_BASE, CMU_PROT_MEM_U32);
#endif
#endif /* MCAL_CMU_REG_PROT_AVAILABLE */

/* SRAM SetUserAccessAllowed */
#if (defined(MCAL_SRAMC_REG_PROT_AVAILABLE) && (STD_ON == MCAL_SRAMC_REG_PROT_AVAILABLE))
#if (defined(SRAMC_BASE))
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_3 The cast is used to access memory mapped registers.
    */
    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_4 A function should be used in preference to a function-like macro where they are interchangeable.
    */
    SET_USER_ACCESS_ALLOWED(SRAMC_BASE, SRAMC_PROT_MEM_U32);
#endif
#endif /* MCAL_SRAMC_REG_PROT_AVAILABLE */
}
#endif /* CLOCK_IP_ENABLE_USER_MODE_SUPPORT */



/* Clock stop section code */
#define MCU_STOP_SEC_CODE
/**
* @violates @ref Clock_Ip_S32G2XX_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"


#ifdef FEATURE_CLOCK_IP_HAS_RAM_WAIT_STATES


/* Clock start rom section code */
#define MCU_START_SEC_CODE_AC
/**
* @violates @ref Clock_Ip_S32G2XX_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

static void SRAMC_SetRamIWS(void)
{
    uint32 iws_setting = 0U;

    if (configuredCoreClock <= 200000000U)
    {
        if (configuredCoreClock <= 100000000U)
        {
            iws_setting = 0U;
        }
        else
        {
            iws_setting = 1U;
        }
    }
    else
    {
        if (configuredCoreClock <= 300000000U)
        {
            iws_setting = 2U;
        }
        else
        {
            iws_setting = 3U;
        }
    }

    /**
    * @violates @ref Clock_Ip_S32G2XX_c_REF_3 The cast is used to access memory mapped registers.
    */
    SRAMC->PRAMCR |= SRAMC_PRAMCR_IWS(iws_setting);
}

/* Clock stop rom section code */
#define MCU_STOP_SEC_CODE_AC
/**
* @violates @ref Clock_Ip_S32G2XX_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"
#endif

#ifdef FEATURE_CLOCK_IP_HAS_FLASH_WAIT_STATES




/* Clock start ram section code */
#define MCU_START_SEC_RAMCODE
/**
* @violates @ref Clock_Ip_S32G2XX_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

void CodeInRam_SetFlashWaitStates(void)
{
}

/* Clock stop ram section code */
#define MCU_STOP_SEC_RAMCODE
/**
* @violates @ref Clock_Ip_S32G2XX_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

/* Clock start initialized section data */
#define MCU_START_SEC_VAR_INIT_UNSPECIFIED
/**
* @violates @ref Clock_Ip_S32G2XX_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

typedef void (*SetFlashWaitStatesCallbackType)(void);
SetFlashWaitStatesCallbackType SetFlashWaitStatesCallback = CodeInRam_SetFlashWaitStates;   /* Set Flash Wait States callback */


/* Clock stop initialized section data */
#define MCU_STOP_SEC_VAR_INIT_UNSPECIFIED
/**
* @violates @ref Clock_Ip_S32G2XX_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"


/* Clock start section code */
#define MCU_START_SEC_CODE
/**
* @violates @ref Clock_Ip_S32G2XX_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

void FLASH_SetFlashIWS(void)
{
    SetFlashWaitStatesCallback();
}


/* Clock stop section code */
#define MCU_STOP_SEC_CODE
/**
* @violates @ref Clock_Ip_S32G2XX_c_REF_1 #include directives should only be preceded by preprocessor
* directives or comments.
*/
#include "Mcu_MemMap.h"

#endif

#endif /* (S32G2XX) */

/*! @}*/

/*******************************************************************************
 * EOF
 ******************************************************************************/

