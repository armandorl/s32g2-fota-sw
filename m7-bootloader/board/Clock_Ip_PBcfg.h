/**
*   @file       Clock_Ip_PBcfg.h
*   @implements Clock_Ip_PBcfg.h_Artifact
*   @version    0.9.0
*
*   @brief   AUTOSAR Mcu - Post-Build(PB) configuration file code template.
*   @details Code template for Post-Build(PB) configuration file generation.
*
*   @addtogroup CLOCK_DRIVER_CONFIGURATION Clock Driver
*   @{
*/

#ifndef CLOCK_IP_PBCFG_H
#define CLOCK_IP_PBCFG_H


#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Clock_Ip_Types.h"

#define MCU_START_SEC_CONST_UNSPECIFIED
#include "Mcu_MemMap.h"

/*==================================================================================================
                                           DEFINES AND MACROS
==================================================================================================*/
/*! @brief User Configuration structure clock_Cfg_0 */
extern const Clock_Ip_ClockConfigType Mcu_aClockConfigPB[];

#define MCU_STOP_SEC_CONST_UNSPECIFIED
#include "Mcu_MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* CLOCK_IP_PBCFG_H */

/** @} */
