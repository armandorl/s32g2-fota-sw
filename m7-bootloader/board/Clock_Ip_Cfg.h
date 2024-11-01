/**
*   @file       Clock_Ip_Cfg.h
*   @implements Clock_Ip_Cfg.h_Artifact
*   @version    0.9.0
*
*   @brief   Clock configuration header file.
*   @details This file is the header containing all the necessary information for CLOCK
*            module configuration(s).
*
*   @addtogroup CLOCK_DRIVER_CONFIGURATION Clock Driver
*   @{
*/


#ifndef CLOCK_IP_CFG_H
#define CLOCK_IP_CFG_H


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

/*==================================================================================================
                                           DEFINES AND MACROS
==================================================================================================*/
/**
* @brief            Pre-processor switch for enabling the default error detection and reporting to the DET.
*                   The detection of default errors is configurable (ON / OFF) at pre-compile time.
*/

#define CLOCK_IP_DEV_ERROR_DETECT         (STD_OFF)

#define CLOCK_TIMEOUT_TYPE                (OSIF_COUNTER_DUMMY)

#define CLOCK_TIMEOUT_VALUE_US            (10000U)

/**
* @brief        Support for User mode.
*               If this parameter has been configured to 'TRUE' the Clock can be executed from both supervisor and user mode.
*/
#ifndef MCAL_ENABLE_USER_MODE_SUPPORT
  #define CLOCK_IP_ENABLE_USER_MODE_SUPPORT  (STD_OFF)
#else
  #define CLOCK_IP_ENABLE_USER_MODE_SUPPORT  (STD_ON)
#endif
/** Check the driver user mode is enabled only when the MCAL_ENABLE_USER_MODE_SUPPORT is enabled */
#ifndef MCAL_ENABLE_USER_MODE_SUPPORT
  #if (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT)
    #error MCAL_ENABLE_USER_MODE_SUPPORT is not enabled. For running Clock in user mode the MCAL_ENABLE_USER_MODE_SUPPORT needs to be defined.
  #endif /* (STD_ON == CLOCK_IP_ENABLE_USER_MODE_SUPPORT) */
#endif /* ifndef MCAL_ENABLE_USER_MODE_SUPPORT */

/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
                                             ENUMS
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* CLOCK_IP_CFG_H */

/** @} */
