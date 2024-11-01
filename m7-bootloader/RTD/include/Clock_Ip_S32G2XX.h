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
*   @file    Clock_Ip_S32G2XX.h
*   @version    1.0.0
*
*   @brief   CLOCK IP specific header file.
*   @details CLOCK IP specific header file.
*
*   @addtogroup CLOCK_DRIVER Clock Driver
*   @{
*/


#if !defined(SPECIFIC_CLOCK_S32G274A_H)
#define SPECIFIC_CLOCK_S32G274A_H
#include "S32G274A_COMMON.h"
#include "S32G274A_MC_CGM.h"
#include "S32G274A_MC_CGM_1.h"
#include "S32G274A_MC_CGM_2.h"
#include "S32G274A_FXOSC.h"
#include "S32G274A_PLLDIG.h"
#include "S32G274A_MC_ME.h"
#include "S32G274A_SRAMC.h"
#include "S32G274A_DFS.h"
#include "S32G274A_CMU_FC.h"
#include "S32G274A_SYSTICK.h"
#include <stdbool.h>
#include <stddef.h>
#include "Mcal.h"






#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

#define CALC_FREQ_CALLBACKS_NO                                                155U
#define CONSUMER_CALLBACKS_COUNT                                              FEATURE_CLOCK_CONSUMER_COUNT
#define SELECTOR_HARDWARE_VALUES_NO                                           64U

#define PCFS_ENTRIES_NO                                                       3U
#define PCFS_COREPLLDFS1                                                      0U
#define PCFS_COREPLLPHI0                                                      1U
#define PCFS_ACCELPLLPHI1                                                     2U

#define CMU_ENTRIES_NO                                                        27U


#define DIVIDER_CALLBACKS_COUNT                                               5U
#define CGM_X_DE_DIV_STAT_WITHOUT_PHASE                                       1U
#define CGM_X_DE_DIV_WITHOUT_PHASE                                            2U
#define CGM_X_DE_DIV_STAT_WITH_PHASE                                          3U
#define PLLDIG_PLL0DIV_DE_DIV_OUTPUT                                          4U

#define DIVIDERTRIGGER_CALLBACKS_COUNT                                        2U
#define CGM_X_DIV_TRIG_CTRL_TCTL_HHEN_UPD_STAT                                1U

#define XOSC_CALLBACKS_COUNT                                                  2U
#define FXOSC_OSCON_BYP_EOCV_GM_SEL                                           1U

#define IRCOSC_CALLBACKS_COUNT                                                1U

#define GATE_CALLBACKS_COUNT                                                  2U
#define MC_ME_PARTITION_COFB_ENABLE_REQUEST                                   1U

#define FRACTIONAL_DIVIDER_CALLBACKS_COUNT                                    2U
#define DFS_MFI_MFN                                                           1U

#define PLL_CALLBACKS_COUNT                                                   3U
#define PLLDIG_RDIV_MFI_MFN_SDMEN_SSCGBYP_SPREADCTL_STEPNO_STEPSIZE           1U
#define PLLDIG_RDIV_MFI_MFN_SDMEN                                             2U

#define SELECTOR_CALLBACKS_COUNT                                              4U
#define CGM_X_CSC_CSS_CLK_SW_SWIP                                             1U
#define CGM_X_CSC_CSS_CLK_SW_RAMPDOWN_RAMPUP_SWIP                             2U
#define CGM_X_CSC_CSS_CS_GRIP                                                 3U

#define PCFS_CALLBACKS_COUNT                                                  2U
#define CGM_X_PCFS_SDUR_DIVC_DIVE_DIVS                                        1U

#define CMU_CALLBACKS_COUNT                                                   2U
#define CMU_FC_FCE_REF_CNT_LFREF_HFREF                                        1U

#define ALL_CALLBACKS_COUNT                                                   12U



#define MC_CGM_MUX_MUX_DIV_COUNT                  2u
typedef struct {
  uint32 CSC;
  const  uint32 CSS;
  uint32 divider[MC_CGM_MUX_MUX_DIV_COUNT];
  uint8 RESERVED_0[36];
  uint32 MUX_DIV_TRIG_CTRL;               /**< Clock Mux 0 Divider Trigger Control Register, offset: 0x334 */
  uint32 MUX_DIV_TRIG;                    /**< Clock Mux 0 Divider Trigger Register, offset: 0x338 */
  const  uint32 MUX_DIV_UPD_STAT;

}volatile cgmMux_Type;

#define MC_CGM_PCFS_COUNT                         12u
typedef struct {

    uint32 PCFS_SDUR;                           /**< PCFS Step Duration, offset: 0x0 */
    struct {                                    /* offset: 0x4, array step: 0xC */
      uint32 DIVC;                              /**< PCFS Divider Change 12 Register, array offset: 0x4, array step: 0xC */
      uint32 DIVE;                              /**< PCFS Divider End 12 Register, array offset: 0x8, array step: 0xC */
      uint32 DIVS;                              /**< PCFS Divider Start 12 Register, array offset: 0xC, array step: 0xC */
    } PCFS[MC_CGM_PCFS_COUNT];

}volatile cgmPcfs_Type;


#define PRTN_COFB_NO                            4u
typedef struct {
	volatile uint32 PRTN_COFB_CLKEN[PRTN_COFB_NO];
}mcmePartitionSet_Type;

typedef struct {
	  volatile const  uint32 PRTN_COFB_STAT[PRTN_COFB_NO];
}mcmePartitionGet_Type;

typedef struct {
	volatile uint32 PRTN_PCONF;
	volatile uint32 PRTN_PUPD;
	volatile const  uint32 PRTN_STAT;
}mcmePartitionTrigger_Type;

/** XOSC - Register Layout Typedef */
typedef struct {
  uint32 CTRL;                        /**< XOSC Control Register, offset: 0x0 */
  const  uint32 STAT;                        /**< Oscillator Status Register, offset: 0x4 */
}volatile ExtOSC_Type;


typedef struct{

    Clock_Ip_NameType name;    /* Name of the clock source that supports pcfs (ramp up / ramp down) */
    uint8  configIndex;
    uint32 sdur;
    uint32 divc_init;
    uint32 divc_rate;
    uint32 div_startValue;
    uint32 div_endValue;

}pcfsEntry;

typedef struct{

    Clock_Ip_NameType name;    /* Name of the clock that can be monitored/supports cmu (clock monitor) */
    uint8 configIndex;
    uint32 enable;
    uint32 refCount;
    uint32 hfRef;
    uint32 lfRef;

}cmuEntry;

/** CMU - Register Layout Typedef */
typedef struct {
  uint32_t GCR;                               /**< Global Configuration Register, offset: 0x0 */
  uint32_t RCCR;                              /**< Reference Count Configuration Register, offset: 0x4 */
  uint32_t HTCR;                              /**< High Threshold Configuration Register, offset: 0x8 */
  uint32_t LTCR;                              /**< Low Threshold Configuration Register, offset: 0xC */
  uint32_t SR;                                /**< Status Register, offset: 0x10 */
  uint32_t IER;                               /**< Interrupt Enable Register, offset: 0x14 */

} ClockMonitor_Type;
#define MC_CGM_instances_count      6U
#define MC_CGM_muxs_count           17U
#define XOSC_INSTANCES_ARRAY_SIZE   1U
#define PLL_INSTANCES_ARRAY_SIZE    4U
#define DFS_INSTANCES_ARRAY_SIZE    2U
#define CMU_INSTANCES_ARRAY_SIZE    27U
#define MC_ME_partitions_count      4U



#define MC_CGM_MUX_DC_DE_MASK                MC_CGM_MUX_0_DC_0_DE_MASK
#define MC_CGM_MUX_DC_DE_SHIFT               MC_CGM_MUX_0_DC_0_DE_SHIFT
#define MC_CGM_MUX_DC_DIV_MASK               MC_CGM_MUX_0_DC_0_DIV_MASK
#define MC_CGM_MUX_DC_DIV_SHIFT              MC_CGM_MUX_0_DC_0_DIV_SHIFT
#define MC_CGM_MUX_DC_DIV(x)                 MC_CGM_MUX_0_DC_0_DIV(x)
#define MC_CGM_MUX_DC_PHASE_MASK             0xFFU
#define MC_CGM_MUX_DC_PHASE_SHIFT            0x0U
#define MC_CGM_MUX_DC_PHASE(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_DC_PHASE_SHIFT)) & MC_CGM_MUX_DC_PHASE_MASK)
#define MC_CGM_MUX_CSS_SELSTAT_MASK          MC_CGM_MUX_0_CSS_SELSTAT_MASK
#define MC_CGM_MUX_CSS_SELSTAT_SHIFT         MC_CGM_MUX_0_CSS_SELSTAT_SHIFT
#define MC_CGM_MUX_CSC_SELCTL(x)             MC_CGM_MUX_0_CSC_SELCTL(x)
#define MC_CGM_MUX_CSC_SELCTL_MASK           MC_CGM_MUX_0_CSC_SELCTL_MASK
#define MC_CGM_MUX_CSC_SELCTL_SHIFT          MC_CGM_MUX_0_CSC_SELCTL_SHIFT
#define MC_CGM_MUX_CSC_SAFE_SW_MASK          MC_CGM_MUX_0_CSS_SAFE_SW_MASK
#define MC_CGM_MUX_CSC_CLK_SW_MASK           MC_CGM_MUX_0_CSC_CLK_SW_MASK
#define MC_CGM_MUX_CSC_RAMPUP_MASK           MC_CGM_MUX_0_CSC_RAMPUP_MASK
#define MC_CGM_MUX_CSC_RAMPDOWN_MASK         MC_CGM_MUX_0_CSC_RAMPDOWN_MASK
#define MC_CGM_MUX_CSS_SWIP_MASK             MC_CGM_MUX_0_CSS_SWIP_MASK
#define MC_CGM_MUX_CSS_SWIP_IN_PROGRESS      MC_CGM_MUX_CSS_SWIP_MASK
#define MC_CGM_MUX_CSS_SWTRG_MASK            MC_CGM_MUX_0_CSS_SWTRG_MASK
#define MC_CGM_MUX_CSS_SWTRG_SHIFT           MC_CGM_MUX_0_CSS_SWTRG_SHIFT
#define MC_CGM_MUX_CSS_SWTRG_SUCCEEDED       1U
#define MC_CGM_MUX_CSS_CLK_SW_MASK           MC_CGM_MUX_0_CSS_CLK_SW_MASK
#define MC_CGM_MUX_CSS_CLK_SW_NOT_REQUESTED  0U
#define MC_CGM_MUX_CSC_CG_MASK               MC_CGM_MUX_1_CSC_CG_MASK
#define MC_CGM_MUX_CSC_FCG_MASK              MC_CGM_MUX_1_CSC_FCG_MASK
#define MC_CGM_MUX_CSS_CS_MASK               MC_CGM_MUX_1_CSS_CS_MASK
#define MC_CGM_MUX_CSS_CS_TRANSPARENT        MC_CGM_MUX_CSS_CS_MASK
#define MC_CGM_MUX_DIV_UPD_STAT_DIV_STAT_MASK MC_CGM_MUX_0_DIV_UPD_STAT_DIV_STAT_MASK
#define MC_CGM_MUX_DIV_UPD_STAT_DIV_STAT_PENDING MC_CGM_MUX_DIV_UPD_STAT_DIV_STAT_MASK
#define MC_CGM_MUX_DIV_TRIG_CTRL_TCTL_MASK                       MC_CGM_2_MUX_0_DIV_TRIG_CTRL_TCTL_MASK
#define MC_CGM_MUX_DIV_TRIG_CTRL_COMMON_TRIGGER_DIVIDER_UPDATE   MC_CGM_MUX_DIV_TRIG_CTRL_TCTL_MASK
#define MC_CGM_MUX_DIV_TRIG_TRIGGER(x)                           MC_CGM_2_MUX_0_DIV_TRIG_TRIGGER(x)
#define MC_CGM_PCFS_DIVC_INIT(x)             MC_CGM_PCFS_DIVC12_INIT(x)
#define MC_CGM_PCFS_DIVC_RATE(x)             MC_CGM_PCFS_DIVC12_RATE(x)
#define MC_CGM_PCFS_DIVE_DIVE(x)             MC_CGM_PCFS_DIVE12_DIVE(x)
#define MC_CGM_PCFS_DIVS_DIVS(x)             MC_CGM_PCFS_DIVS12_DIVS(x)

#define CMU_FREQUENCY_CHECK_ENABLED          CMU_FC_GCR_FCE_MASK
#define CMU_FREQUENCY_CHECK_STOPPED          0U
#define CMU_ISR_MASK                         3U
#define CMU_RESET_COUNTER_VALUE              0U
#define CMU_RESET_LOW_LIMIT                  3U
#define CMU_RESET_HIGH_LIMIT                 0x00FFFFFCU

/* Clock start constant section data */
#define MCU_START_SEC_CONST_UNSPECIFIED

#include "Mcu_MemMap.h"

extern cgmMux_Type* const cgm[MC_CGM_instances_count][MC_CGM_muxs_count];
extern cgmPcfs_Type* const cgmPcfs[MC_CGM_instances_count];
extern ExtOSC_Type* const xosc[XOSC_INSTANCES_ARRAY_SIZE];
extern PLLDIG_Type* const pll[PLL_INSTANCES_ARRAY_SIZE];
extern DFS_Type* const dfs[DFS_INSTANCES_ARRAY_SIZE];
extern volatile ClockMonitor_Type * const cmu[CMU_INSTANCES_ARRAY_SIZE];
extern cmuEntry cmuEntries[CMU_ENTRIES_NO];

extern volatile mcmePartitionSet_Type* const mcmeSetPartitions[MC_ME_partitions_count];
extern volatile const mcmePartitionGet_Type* const mcmeGetPartitions[MC_ME_partitions_count];
extern volatile mcmePartitionTrigger_Type* const mcmeTriggerPartitions[MC_ME_partitions_count];

/* Clock stop constant section data */
#define MCU_STOP_SEC_CONST_UNSPECIFIED

#include "Mcu_MemMap.h"


/* Clock start initialized section data */
#define MCU_START_SEC_VAR_INIT_UNSPECIFIED

#include "Mcu_MemMap.h"

extern pcfsEntry pcfsEntries[PCFS_ENTRIES_NO];

/* Clock stop initialized section data */
#define MCU_STOP_SEC_VAR_INIT_UNSPECIFIED

#include "Mcu_MemMap.h"

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

/* Clock start section code */
#define MCU_START_SEC_CODE

#include "Mcu_MemMap.h"

#if (defined(CLOCK_IP_ENABLE_USER_MODE_SUPPORT) && (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT))
void SpecificSetUserAccessAllowed(void);
#endif /* CLOCK_IP_ENABLE_USER_MODE_SUPPORT */
void McMeEnterKey(void);
const Clock_Ip_ClockConfigType* GetClockConfig(void);

/* Clock stop section code */
#define MCU_STOP_SEC_CODE

#include "Mcu_MemMap.h"

#if defined(__cplusplus)
}
#endif /* __cplusplus*/


/*! @}*/

#endif /* SPECIFIC_CLOCK_S32G274A_H */
/*******************************************************************************
 * EOF
 ******************************************************************************/
