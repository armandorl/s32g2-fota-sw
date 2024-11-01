#ifndef _SIUL2_PORT_IP_CFG_H_
#define _SIUL2_PORT_IP_CFG_H_

#include "S32G274A_SIUL2.h"
#include "Siul2_Port_Ip_Types.h"

/***********************************************************************************************************************
 * Definitions
 **********************************************************************************************************************/

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SIUL2_PORT_IP_VENDOR_ID_CFG_H                       43
#define SIUL2_PORT_IP_AR_RELEASE_MAJOR_VERSION_CFG_H        4
#define SIUL2_PORT_IP_AR_RELEASE_MINOR_VERSION_CFG_H        4
#define SIUL2_PORT_IP_AR_RELEASE_REVISION_VERSION_CFG_H     0
#define SIUL2_PORT_IP_SW_MAJOR_VERSION_CFG_H                1
#define SIUL2_PORT_IP_SW_MINOR_VERSION_CFG_H                0
#define SIUL2_PORT_IP_SW_PATCH_VERSION_CFG_H                0

/*!
 * @addtogroup Siul2_Port_Ip_Cfg
 * @{
 */

/***********************************************************************************************************************
 * API
 **********************************************************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif

/*! @brief Definitions for BOARD_InitPins Functional Group */

/*! @brief User number of configured pins */
#define DEV_ASSERT(par)
#define NUM_OF_CONFIGURED_PINS0 18
/*! @brief User configuration structure */
extern Siul2_Port_Ip_PinSettingsConfig g_pin_mux_InitConfigArr0[NUM_OF_CONFIGURED_PINS0];


#if defined(__cplusplus)
}
#endif

/*!
 * @}
 */
#endif /* _SIUL2_PORT_IP_CFG_H_ */

/***********************************************************************************************************************
 * EOF
 **********************************************************************************************************************/

