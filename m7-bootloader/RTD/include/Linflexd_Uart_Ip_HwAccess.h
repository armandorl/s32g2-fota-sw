/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : LINFLEXD
*   Dependencies         : 
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


#ifndef LINFLEXD_HWACCESS_H
#define LINFLEXD_HWACCESS_H

/**
*   @file
*   @internal
*   @defgroup linflexd_ip Linflexd IPL
*   @addtogroup  linflexd_ip Linflexd  IPL
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
#include "StandardTypes.h"
#include "OsIf.h"
#include "Linflexd_Uart_Ip_Defines.h"
#include "SchM_Uart.h"
/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define LINFLEXD_UART_IP_HWACCESS_VENDOR_ID                    43
#define LINFLEXD_UART_IP_HWACCESS_MODULE_ID                    255
#define LINFLEXD_UART_IP_HWACCESS_AR_RELEASE_MAJOR_VERSION     4
#define LINFLEXD_UART_IP_HWACCESS_AR_RELEASE_MINOR_VERSION     4
#define LINFLEXD_UART_IP_HWACCESS_AR_RELEASE_REVISION_VERSION  0
#define LINFLEXD_UART_IP_HWACCESS_SW_MAJOR_VERSION             1
#define LINFLEXD_UART_IP_HWACCESS_SW_MINOR_VERSION             0
#define LINFLEXD_UART_IP_HWACCESS_SW_PATCH_VERSION             0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Checks against Linflexd_Uart_Ip_Defines.h */
#if (LINFLEXD_UART_IP_HWACCESS_VENDOR_ID != LINFLEXD_UART_IP_DEFINES_VENDOR_ID)
    #error "Linflexd_Uart_Ip_HwAccess.h and Linflexd_Uart_Ip_Defines.h have different vendor ids"
#endif
#if ((LINFLEXD_UART_IP_HWACCESS_AR_RELEASE_MAJOR_VERSION    != LINFLEXD_UART_IP_DEFINES_AR_RELEASE_MAJOR_VERSION) || \
     (LINFLEXD_UART_IP_HWACCESS_AR_RELEASE_MINOR_VERSION    != LINFLEXD_UART_IP_DEFINES_AR_RELEASE_MINOR_VERSION) || \
     (LINFLEXD_UART_IP_HWACCESS_AR_RELEASE_REVISION_VERSION != LINFLEXD_UART_IP_DEFINES_AR_RELEASE_REVISION_VERSION))
     #error "AUTOSAR Version Numbers of Linflexd_Uart_Ip_HwAccess.h and Linflexd_Uart_Ip_Defines.h are different"
#endif
#if ((LINFLEXD_UART_IP_HWACCESS_SW_MAJOR_VERSION != LINFLEXD_UART_IP_DEFINES_SW_MAJOR_VERSION) || \
     (LINFLEXD_UART_IP_HWACCESS_SW_MINOR_VERSION != LINFLEXD_UART_IP_DEFINES_SW_MINOR_VERSION) || \
     (LINFLEXD_UART_IP_HWACCESS_SW_PATCH_VERSION != LINFLEXD_UART_IP_DEFINES_SW_PATCH_VERSION))
    #error "Software Version Numbers of Linflexd_Uart_Ip_HwAccess.h and Linflexd_Uart_Ip_Defines.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if current file and StandardTypes.h header file are of the same Autosar version */
    #if ((LINFLEXD_UART_IP_HWACCESS_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
            (LINFLEXD_UART_IP_HWACCESS_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION))
        #error "Linflexd_Uart_Ip_HwAccess.h and StandardTypes.h are different"
    #endif
#endif
/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
#define DEFAULT_OSR              16U

#define BAUDRATE_FRACTION_WIDTH  LINFLEXD_LINFBRR_FBR_WIDTH

/* Wrap-around value for timeout */
#define TIMEOUT_WRAP     (0xFFFFFFU)

#ifdef CPU_BYTE_ORDER
    #if (LOW_BYTE_FIRST == CPU_BYTE_ORDER)
        #define CORE_LITTLE_ENDIAN
    #endif
#endif

#ifdef CORE_LITTLE_ENDIAN
    #define SWAP_BYTES_UINT16(x) ((((x) >> 8U) & 0xFFU) | (((x) << 8U) & 0xFF00U))
#endif
/*==================================================================================================
*                                              ENUMS
==================================================================================================*/
/**
 * @internal
 *@brief Word length in UART mode.
 *
 *
 */
typedef enum
{
    LINFLEXD_UART_IP_7_BITS     = 0U,
    LINFLEXD_UART_IP_8_BITS     = 1U,
    LINFLEXD_UART_IP_15_BITS    = 2U,
    LINFLEXD_UART_IP_16_BITS    = 3U
} Linflexd_Uart_Ip_WordLengthType;

/**
 * @internal
 * @brief Number of stop bits.
 *
 *
 */
typedef enum
{
    LINFLEXD_UART_IP_ONE_STOP_BIT = 0U,
    LINFLEXD_UART_IP_TWO_STOP_BIT = 1U
} Linflexd_Uart_Ip_StopBitsCountType;

/**
 * @internal
 * @brief Parity type.
 *
 *
 */
typedef enum
{
    LINFLEXD_UART_IP_PARITY_EVEN    = 0U,
    LINFLEXD_UART_IP_PARITY_ODD     = 1U,
    LINFLEXD_UART_IP_PARITY_ZERO    = 2U,
    LINFLEXD_UART_IP_PARITY_ONE     = 3U
} Linflexd_Uart_Ip_ParityType;


/**
  * * @internal
  * @brief LINFLEXD mode: UART/LIN.

  */
typedef enum
{
    LINFLEXD_LIN_MODE   = 0U,
    LINFLEXD_UART_MODE  = 1U
} Linflexd_Uart_Ip_ModeType;

/**
 * @internal
 * @brief UART Mode: FIFO/BUFFER.
 */
typedef enum
{
    LINFLEXD_UART_RXTX_BUFFER_MODE  = 0U,
    LINFLEXD_UART_RXTX_FIFO_MODE    = 1U
} Linflexd_Uart_Ip_RxTxModeType;

/**
 * @internal
 * @brief LINFLEXD state.
*/
typedef enum
{
    LINFLEXD_STATE_SLEEP_MODE       = 0U,
    LINFLEXD_STATE_INIT_MODE        = 1U,
    LINFLEXD_STATE_IDLE_MODE        = 2U,
    LINFLEXD_STATE_DATA_RX_TX       = 8U
} Linflexd_Uart_Ip_StateType;

/**
 * @internal
 * @brief UART Status flags.
 * @details These identifiers provide both mask and shift for status bits in UARTSR register.
 */
typedef enum
{
    LINFLEXD_UART_NOISE_FLAG                   = LINFLEXD_UARTSR_NF_MASK,
    LINFLEXD_UART_DATA_TRANSMITTED_FLAG        = LINFLEXD_UARTSR_DTFTFF_MASK,
    LINFLEXD_UART_DATA_RECEPTION_COMPLETE_FLAG = LINFLEXD_UARTSR_DRFRFE_MASK,
    LINFLEXD_UART_WAKEUP_FLAG                  = LINFLEXD_UARTSR_WUF_MASK,
    LINFLEXD_UART_BUFFER_OVERRUN_FLAG          = LINFLEXD_UARTSR_BOF_MASK,
    LINFLEXD_UART_FRAME_ERROR_FLAG             = LINFLEXD_UARTSR_FEF_MASK,
    LINFLEXD_UART_MESSAGE_BUFFER_FULL_FLAG     = LINFLEXD_UARTSR_RMB_MASK,
    LINFLEXD_UART_PARITY_ERROR_FLAG            = LINFLEXD_UARTSR_PE_MASK
} Linflexd_Uart_Ip_StatusFlagType;

/**
 * @internal
 * @brief LINFLEXD interrupts.
 * @details These identifiers provide both mask and shift for the interrupt enable bits in LINIER register.
 */
typedef enum
{
    LINFLEXD_DATA_TRANSMITTED_INT        = LINFLEXD_LINIER_DTIE_MASK,
    LINFLEXD_DATA_RECEPTION_COMPLETE_INT = LINFLEXD_LINIER_DRIE_MASK,
    LINFLEXD_BUFFER_OVERRUN_INT          = LINFLEXD_LINIER_BOIE_MASK,
    LINFLEXD_FRAME_ERROR_INT             = LINFLEXD_LINIER_FEIE_MASK,
    LINFLEXD_WAKEUP_INT                  = LINFLEXD_LINIER_WUIE_MASK
} Linflexd_Uart_Ip_InterruptType;

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                       FUNCTION PROTOTYPES
==================================================================================================*/
#define UART_START_SEC_CODE
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

/**
 * @internal
 * @brief Requests LINFLEXD module to enter init mode.
 *
 * This function enters initialization mode.
 *
 * @param base LINFLEXD base pointer.
 */
static inline void LINFLEXD_EnterInitMode(LINFLEXD_Type *base)
{
    uint32 regValTemp;

    regValTemp = base->LINCR1;
    regValTemp &= ~(LINFLEXD_LINCR1_SLEEP_MASK);
    regValTemp |= LINFLEXD_LINCR1_INIT(1UL);
    base->LINCR1 = regValTemp;
}

/**
 * @internal
 * @brief Requests LINFLEXD module to enter normal mode.
 *
 * This function enters normal mode. *
 *
 * @param base LINFLEXD base pointer.
 */
static inline void LINFLEXD_EnterNormalMode(LINFLEXD_Type *base)
{
    uint32 regValTemp;

    regValTemp = base->LINCR1;
    regValTemp &= ~(LINFLEXD_LINCR1_SLEEP_MASK);
    regValTemp &= ~(LINFLEXD_LINCR1_INIT_MASK);
    base->LINCR1 = regValTemp;
}

/**
 * @internal
 * @brief Sets the LINFLEXD mode.
 *
 * This function sets LIN or UART mode, based on the parameter received.
 *
 * @param base LINFLEXD base pointer.
 * @param mode LINFLEXD mode - UART/LIN.
 */
static inline void LINFLEXD_SetMode(LINFLEXD_Type *base, Linflexd_Uart_Ip_ModeType mode)
{
    uint32 regValTemp;

    regValTemp = base->UARTCR;
    regValTemp &= ~(LINFLEXD_UARTCR_UART_MASK);
    regValTemp |= LINFLEXD_UARTCR_UART((uint32)mode);
    base->UARTCR = regValTemp;
}

/**
 * @internal
 * @brief Returns the current LINFLEXD state.
 *
 * This function returns the state of the LINFLEXD instance. The possible states are:
 *    - Sleep mode
 *    - Init mode
 *    - Idle mode
 *    - Sync Break Reception/Transmission
 *    - Sync Delimiter Reception/Transmission
 *    - Sync Field Reception/Transmission
 *    - Identifier Field Reception/Transmission
 *    - Header Reception/Transmission
 *    - Data Reception/Transmission
 *    - Checksum Reception/Transmission
 *
 * @param base LINFLEXD base pointer.
 * @return LINFLEXD mode - UART/LIN.
 */
static inline Linflexd_Uart_Ip_StateType LINFLEXD_GetLinState(const LINFLEXD_Type * base)
{
    uint8 state = (uint8)((base->LINSR & LINFLEXD_LINSR_LINS_MASK) >> LINFLEXD_LINSR_LINS_SHIFT);
    return (Linflexd_Uart_Ip_StateType)state;
}

/**
 * @internal
 * @brief Sets the word length.
 *
 * This function sets the word length in UART mode.
 * Should be called only when the module is in init mode.
 *
 * @param base LINFLEXD base pointer.
 * @param length UART mode word length.
 */
static inline void LINFLEXD_SetUartWordLength(LINFLEXD_Type *base, Linflexd_Uart_Ip_WordLengthType length)
{
    uint32 regValTemp;

    regValTemp = base->UARTCR;
    regValTemp &= ~(LINFLEXD_UARTCR_WL0_MASK);
    regValTemp |= LINFLEXD_UARTCR_WL0((uint32)length & 1U);
    regValTemp &= ~(LINFLEXD_UARTCR_WL1_MASK);
    regValTemp |= LINFLEXD_UARTCR_WL1(((uint32)length >> 1U) & 1U);
    base->UARTCR = regValTemp;
}

/**
 * @internal
 * @brief Enables/disables parity bit.
 *
 * This function enables or disables the parity bit from UART bytes.
 * Should be called only when the module is in init mode.
 *
 * @param base LINFLEXD base pointer.
 * @param enable true - enable parity queuing/checking, false - disable parity queuing/checking.
 */
static inline void LINFLEXD_SetParityControl(LINFLEXD_Type *base, boolean enable)
{
    uint32 regValTemp;

    regValTemp = base->UARTCR;
    regValTemp &= ~(LINFLEXD_UARTCR_PCE_MASK);
    regValTemp |= LINFLEXD_UARTCR_PCE(enable ? 1UL : 0UL);
    base->UARTCR = regValTemp;
}

/**
 * @internal
 * @brief Sets parity type.
 *
 * This function sets the type of parity to be used for UART bytes. Available options are:
 *    - odd
 *    - even
 *    - always 0
 *    - always 1
 * Should be called only when the module is in init mode.
 *
 * @param base LINFLEXD base pointer.
 * @param parityType the type of parity.
 */
static inline void LINFLEXD_SetParityType(LINFLEXD_Type *base, Linflexd_Uart_Ip_ParityType parityType)
{
    uint32 regValTemp;

    regValTemp = base->UARTCR;
    regValTemp &= ~(LINFLEXD_UARTCR_PC0_MASK);
    regValTemp |= LINFLEXD_UARTCR_PC0((uint32)parityType & 1U);
    regValTemp &= ~(LINFLEXD_UARTCR_PC1_MASK);
    regValTemp |= LINFLEXD_UARTCR_PC1(((uint32)parityType >> 1U) & 1U);
    base->UARTCR = regValTemp;
}

/**
 * @internal
 * @brief Enables/disables transmitter.
 *
 * This function enables or disables the UART transmitter, based on the parameter received.
 * Should be called only when the module is in UART mode.
 *
 * @param base LINFLEXD base pointer.
 * @param enable enable/disable transmitter.
 */
static inline void LINFLEXD_SetTransmitterState(LINFLEXD_Type *base, boolean enable)
{
    uint32 regValTemp;

    SchM_Enter_Uart_UART_EXCLUSIVE_AREA_00();
    regValTemp = base->UARTCR;
    regValTemp &= ~(LINFLEXD_UARTCR_TxEn_MASK);
    regValTemp |= LINFLEXD_UARTCR_TxEn(enable ? 1UL : 0UL);
    base->UARTCR = regValTemp;
    SchM_Exit_Uart_UART_EXCLUSIVE_AREA_00();
}

/**
 * @internal
 * @brief Enables/disables receiver.
 *
 * This function enables or disables the UART receiver, based on the parameter received.
 * Should be called only when the module is in UART mode.
 *
 * @param base LINFLEXD base pointer.
 * @param enable enable/disable receiver.
 */
static inline void LINFLEXD_SetReceiverState(LINFLEXD_Type *base, boolean enable)
{
    uint32 regValTemp;

    SchM_Enter_Uart_UART_EXCLUSIVE_AREA_01();
    regValTemp = base->UARTCR;
    regValTemp &= ~(LINFLEXD_UARTCR_RxEn_MASK);
    regValTemp |= LINFLEXD_UARTCR_RxEn(enable ? 1UL : 0UL);
    base->UARTCR = regValTemp;
    SchM_Exit_Uart_UART_EXCLUSIVE_AREA_01();
}

/**
 * @internal
 * @brief Sets the transmission mode (FIFO/Buffer).
 *
 * This function sets the transmission mode (FIFO/Buffer).
 * Should be called only when the module is in init mode.
 *
 * @param base LINFLEXD base pointer.
 * @param mode tx mode: FIFO/Buffer.
 */
static inline void LINFLEXD_SetTxMode(LINFLEXD_Type *base, Linflexd_Uart_Ip_RxTxModeType mode)
{
    uint32 regValTemp;

    regValTemp = base->UARTCR;
    regValTemp &= ~(LINFLEXD_UARTCR_TFBM_MASK);
    regValTemp |= LINFLEXD_UARTCR_TFBM((uint32)mode);
    base->UARTCR = regValTemp;
}

/**
 * @internal
 * @brief Sets the reception mode (FIFO/Buffer).
 *
 * This function sets the reception mode (FIFO/Buffer).
 * Should be called only when the module is in init mode.
 *
 * @param base LINFLEXD base pointer.
 * @param mode rx mode: FIFO/Buffer.
 */
static inline void LINFLEXD_SetRxMode(LINFLEXD_Type *base, Linflexd_Uart_Ip_RxTxModeType mode)
{
    uint32 regValTemp;

    regValTemp = base->UARTCR;
    regValTemp &= ~(LINFLEXD_UARTCR_RFBM_MASK);
    regValTemp |= LINFLEXD_UARTCR_RFBM((uint32)mode);
    base->UARTCR = regValTemp;
}

/**
 * @internal
 * @brief Sets the reception data field length/FIFO depth.
 *
 * This function sets either the reception data field length or the number of bytes in the Rx FIFO, according to
 * the current reception mode.
 *
 * @param base LINFLEXD base pointer.
 * @param length data field length/FIFO depth.
 */
static inline void LINFLEXD_SetRxDataFieldLength(LINFLEXD_Type *base, uint8 length)
{
    uint32 regValTemp;

    regValTemp = base->UARTCR;
    regValTemp &= ~(LINFLEXD_UARTCR_RDFL_RFC_MASK);
    regValTemp |= LINFLEXD_UARTCR_RDFL_RFC(length);
    base->UARTCR = regValTemp;
}

/**
 * @internal
 * @brief Sets the transmission data field length/FIFO depth.
 *
 * This function sets either the transmission data field length or the number of bytes in the Tx FIFO, according to
 * the current transmission mode.
 * Should be called only when the module is in init mode.
 *
 * @param base LINFLEXD base pointer.
 * @param length data field length/FIFO depth.
 */
static inline void LINFLEXD_SetTxDataFieldLength(LINFLEXD_Type *base, uint8 length)
{
    uint32 regValTemp;

    regValTemp = base->UARTCR;
    regValTemp &= ~(LINFLEXD_UARTCR_TDFL_TFC_MASK);
    regValTemp |= LINFLEXD_UARTCR_TDFL_TFC(length);
    base->UARTCR = regValTemp;
}

/**
 * @internal
 * @brief Sets the number of stop bits for Rx.
 *
 * This function sets the number of stop bits for received bytes.
 *
 * @param base LINFLEXD base pointer.
 * @param stopBitsCount number of stop bits.
 */
static inline void LINFLEXD_SetRxStopBitsCount(LINFLEXD_Type *base, Linflexd_Uart_Ip_StopBitsCountType stopBitsCount)
{
    uint32 regValTemp;
    regValTemp = base->UARTCR;
    regValTemp &= ~(LINFLEXD_UARTCR_SBUR_MASK);
    regValTemp |= LINFLEXD_UARTCR_SBUR(stopBitsCount);
    base->UARTCR = regValTemp;
}

/**
 * @internal
 * @brief Sets fractional baud rate.
 *
 * This function configures the bits that decide the fractional part of the LIN Baud Rate.
 * Should be called only when the module is in init mode.
 *
 * @param base LINFLEXD base pointer.
 * @param fbr fractional baud rate.
 */
static inline void LINFLEXD_SetFractionalBaudRate(LINFLEXD_Type *base, uint8 fbr)
{
    base->LINFBRR = LINFLEXD_LINFBRR_FBR(fbr);
}

/**
 * @internal
 * @brief Gets fractional baud rate.
 *
 * This function returns the bits that decide the fractional part of the LIN Baud Rate.
 *
 * @param base LINFLEXD base pointer.
 * @return fractional baud rate.
 */
static inline uint8 LINFLEXD_GetFractionalBaudRate(const LINFLEXD_Type * base)
{
    return (uint8)((base->LINFBRR & LINFLEXD_LINFBRR_FBR_MASK) >> LINFLEXD_LINFBRR_FBR_SHIFT);
}

/**
 * @internal
 * @brief Sets integer baud rate.
 *
 * This function configures the bits that decide the integer part of the LIN Baud Rate.
 * Should be called only when the module is in init mode.
 *
 * @param base LINFLEXD base pointer.
 * @param fbr integer baud rate.
 */
static inline void LINFLEXD_SetIntegerBaudRate(LINFLEXD_Type *base, uint32 ibr)
{
    base->LINIBRR = LINFLEXD_LINIBRR_IBR(ibr);
}

/**
 * @internal
 * @brief Gets integer baud rate.
 *
 * This function returns the bits that decide the integer part of the LIN Baud Rate.
 *
 * @param base LINFLEXD base pointer.
 * @return integer baud rate.
 */
static inline uint32 LINFLEXD_GetIntegerBaudRate(const LINFLEXD_Type * base)
{
    return (uint32)((base->LINIBRR & LINFLEXD_LINIBRR_IBR_MASK) >> LINFLEXD_LINIBRR_IBR_SHIFT);
}

/**
 * @internal
 * @brief Sets the number of stop bits for Tx.
 *
 * This function sets the number of stop bits for transmitted bytes.
 * Should be called only when the module is in init mode.
 *
 * @param base LINFLEXD base pointer.
 * @param defaultOffset - true - use the memory map defined in the header file to access the register;
 *                      - false - use custom memory map to access the register.
 * @param stopBitsCount number of stop bits.
 */
static inline void LINFLEXD_SetTxStopBitsCount(LINFLEXD_Type *base, Linflexd_Uart_Ip_StopBitsCountType stopBitsCount,
                                               boolean defaultOffset)
{
    uint32 regValTemp;

#if defined(FEATURE_LINFLEXD_HAS_DIFFERENT_MEM_MAP)
    if (!defaultOffset)
    {
        regValTemp = ((LINFLEXD_0IFCR_Type *)base)->GCR;
        regValTemp &= ~(LINFLEXD_GCR_STOP_MASK);
        regValTemp |= LINFLEXD_GCR_STOP(stopBitsCount);
        ((LINFLEXD_0IFCR_Type *)base)->GCR = regValTemp;
    }
    else
    {
        regValTemp = base->GCR;
        regValTemp &= ~(LINFLEXD_GCR_STOP_MASK);
        regValTemp |= LINFLEXD_GCR_STOP(stopBitsCount);
        base->GCR = regValTemp;
    }
#else
    (void)defaultOffset;
    regValTemp = base->GCR;
    regValTemp &= ~(LINFLEXD_GCR_STOP_MASK);
    regValTemp |= LINFLEXD_GCR_STOP(stopBitsCount);
    base->GCR = regValTemp;
#endif
}

/**
 * @internal
 * @brief Clears an UART interrupt flag.
 *
 * This function clears the UART status flag received as parameter.
 *
 * @param base LINFLEXD base pointer.
 * @param flag UART status flag.
 */
static inline void LINFLEXD_ClearStatusFlag(LINFLEXD_Type * base, Linflexd_Uart_Ip_StatusFlagType flag)
{
    base->UARTSR = flag;
}

/**
 * @internal
 * @brief Returns an UART interrupt flag.
 *
 * This function returns the value of the UART status flag received as parameter.
 *
 * @param base LINFLEXD base pointer.
 * @return true - UART status flag set, false - UART status flag reset.
 */
static inline boolean LINFLEXD_GetStatusFlag(const LINFLEXD_Type * base, Linflexd_Uart_Ip_StatusFlagType flag)
{
    return ((base->UARTSR & (uint32)flag) != 0U);
}

/**
 * @internal
 * @brief Enables/disables an UART interrupt.
 *
 * This function configures whether the UART event will trigger an interrupt.
 *
 * @param base LINFLEXD base pointer.
 * @param intSrc UART interrupt source.
 * @param enable true - enable interrupt, false - disable interrupt.
 */
static inline void LINFLEXD_SetInterruptMode(LINFLEXD_Type * base, Linflexd_Uart_Ip_InterruptType intSrc, boolean enable)
{
    uint32 regValTemp;

    SchM_Enter_Uart_UART_EXCLUSIVE_AREA_02();
    regValTemp = base->LINIER;
    if (enable)
    {
        regValTemp |= (uint32)intSrc;
    }
    else
    {
        regValTemp &= ~(uint32)intSrc;
    }
    base->LINIER = regValTemp;
    SchM_Exit_Uart_UART_EXCLUSIVE_AREA_02();
}

#if defined (FEATURE_LINFLEXD_ORED_INT_LINES)
/**
 * @internal
 * @brief Returns the state of an UART interrupt.
 *
 * This function returns whether the UART event will trigger an interrupt.
 *
 * @param base LINFLEXD base pointer.
 * @param intSrc UART interrupt source.
 * @return true - interrupt enabled, false - interrupt disabled.
 */
static inline boolean LINFLEXD_IsInterruptEnabled(const LINFLEXD_Type * base, Linflexd_Uart_Ip_InterruptType intSrc)
{
    return ((base->LINIER & (uint32)intSrc) != 0U);
}
#endif

/**
 * @internal
 * @brief Sets the first byte of the tx data buffer.
 *
 * This function writes one byte to the tx data buffer.
 *
 * @param base LINFLEXD base pointer.
 * @param data data byte.
 */
static inline void LINFLEXD_SetTxDataBuffer1Byte(LINFLEXD_Type * base, uint8 data)
{
    uint32 regValTemp;
    regValTemp = base->BDRL;
    regValTemp &= ~(LINFLEXD_BDRL_DATA0_MASK);
    regValTemp |= LINFLEXD_BDRL_DATA0(data);
    base->BDRL = regValTemp;
}

/**
 * @internal
 * @brief Sets the first half-word of the tx data buffer.
 *
 * This function writes two bytes to the tx data buffer.
 *
 * @param base LINFLEXD base pointer.
 * @param data data half-word.
 */
static inline void LINFLEXD_SetTxDataBuffer2Bytes(LINFLEXD_Type * base, uint16 data)
{
    uint32 mask, regValTemp;
    uint16 dataTemp;
#ifdef CORE_LITTLE_ENDIAN
    dataTemp = SWAP_BYTES_UINT16(data);
#else
    dataTemp = data;
#endif
    mask = LINFLEXD_BDRL_DATA0_MASK | LINFLEXD_BDRL_DATA1_MASK;
    regValTemp = base->BDRL;
    regValTemp &= ~(mask);
    regValTemp |= ((uint32)dataTemp & mask);
    base->BDRL = regValTemp;
}

/**
 * @brief Gets the first byte of the rx data buffer.
 *
 * This function retrieves one byte from the rx data buffer.
 *
 * @param base LINFLEXD base pointer.
 * @return data byte.
 */
static inline uint8 LINFLEXD_GetRxDataBuffer1Byte(const LINFLEXD_Type * base)
{
    return (uint8)((base->BDRM & LINFLEXD_BDRM_DATA4_MASK) >> LINFLEXD_BDRM_DATA4_SHIFT);
}

/**
 * @internal
 * @brief Gets the first half-word of the rx data buffer.
 *
 * This function retrieves two bytes from the rx data buffer.
 *
 * @param base LINFLEXD base pointer.
 * @return data half-word.
 */
static inline uint16 LINFLEXD_GetRxDataBuffer2Bytes(const LINFLEXD_Type * base)
{
    uint16 data;
    uint32 mask = LINFLEXD_BDRM_DATA4_MASK | LINFLEXD_BDRM_DATA5_MASK;
    data = (uint16)(base->BDRM & mask);
#ifdef CORE_LITTLE_ENDIAN
    data = SWAP_BYTES_UINT16(data);
#endif
    return data;
}

/**
 * @internal
 * @brief DMA Tx channel enable.
 *
 * This function configures the bit that decide the DMA Tx channel enable or disable.
 *
 * @param base LINFLEXD base pointer.
 * @param enable Set Dma Tx enable/disable.
 */
static inline void LINFLEXD_SetDmaTxEnable(LINFLEXD_Type *base, boolean enable)
{
    base->DMATXE = LINFLEXD_DMATXE_DTE0(enable ? 1UL : 0UL);
}

/**

 * @brief DMA Rx channel enable.
 *
 * This function configures the bit that decide the DMA Rx channel enable or disable.
 *
 * @param base LINFLEXD base pointer.
 * @param enable Set Dma Rx enable/disable.
 */
static inline void LINFLEXD_SetDmaRxEnable(LINFLEXD_Type *base, boolean enable)
{
    base->DMARXE = LINFLEXD_DMARXE_DRE0(enable ? 1UL : 0UL);
}

/**
 * @brief   : Checks for timeout condition
 * @internal
 * @return  TRUE     Timeout occurs
 *          FALSE    Timeout does not occur
 */
static inline boolean LINFLEXD_CheckTimeout(uint32 startTime, uint32 timeoutUs)
{
    uint32 timeoutTicks;
    uint32 currentTime;
    boolean retVal;
    timeoutTicks = OsIf_MicrosToTicks(timeoutUs,LINFLEXD_UART_IP_TIMEOUT_TYPE);
    currentTime = OsIf_GetCounter(LINFLEXD_UART_IP_TIMEOUT_TYPE);

    if (currentTime <= startTime)
    {
        retVal = ((startTime - currentTime) > timeoutTicks) ? TRUE : FALSE;
    }
    else
    {
        /* wrap around */
        retVal = ((TIMEOUT_WRAP + startTime - currentTime) > timeoutTicks) ? TRUE : FALSE;
    }
    return retVal;
}
#define UART_STOP_SEC_CODE
/* @violates @ref Uart_c_REF_1 This violation is not fixed since the inclusion of Uart_MemMap.h is as per AUTOSAR requirement*/
#include "Uart_MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */

#endif /* LINFLEXD_HWACCESS_H */
