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


#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#if 0
#include "typedefs.h"
#include "Std_Types.h"
#include "Platform.h"
#include "StdRegMacros.h"
#else
#include <stdint.h>

#define REG_WRITE32(addr, val) *(volatile uint32_t *)(addr) = (val)
#define REG_READ32(addr) *(volatile uint32_t *)(addr) 

#define E_OK 0
#define E_NOT_OK 1
typedef volatile uint16_t vuint16_t;

#endif
#include "BootloaderRegs.h"
#include "BootloaderSpecific.h"
#include "Bootloader_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/* Timeout initial value */
#define TIMEOUT_INIT 0xffff

/* Timeout reach value */
#define TIMEOUT_REACHED 0x0

/* Parameter used to indicate an enabled partition */
#define PARTITION_ENABLED 1
/* parameter used to indicate that a partition is not enabled */
#define PARTITION_DISABLED 0
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/* Core identification abstraction. Cores are identified based on the partition and their id */

/* CRC values calculated for all the applications
 *
 * CRC calculation parameters:
 *
 * Polynomial used: 0x1021
 * Initial value: 0xffff
 * Final Xor Value: 0x0
*/
/* Application details used by the bootloader to start the image on a core */
typedef struct _Bl_ApplicationDetails
{
    uint8_t            coreId;        /* Identifies the core uniquely on a platform */
    uint32_t           startAddress;  /* The start address of the application */
    uint32_t           flashAddress;  /* The flash address at which the application is stored */
    uint32_t           crcValue;      /* CRC value of the application */
    uint32_t           size;          /* Size of the application */
} Bl_ApplicationDetails;

#define SLOT_MAGIC_EMPTY	(0xFFFFFFFF)
#define SLOT_MAGIC_START	(0x5678A5A5)
#define SLOT_MAGIC_END		(0x1234B6B6)
#define SLOT_FLAGS_ACTIVE	(0x00000010)
#define SLOT_FLAGS_VALID	(0x00000001)
typedef struct {
	uint32_t magic_start;
	uint32_t slot_index;
	uint32_t flags;
	uint8_t major_version;
	uint8_t minor_version;
	uint8_t retry_remain;
	uint8_t reserved1;
	uint32_t install_counter;
	uint32_t crc_checksum;
	uint32_t reserved2;
	uint32_t magic_end;
} slot_swap_ctrl_t;

typedef struct {
	slot_swap_ctrl_t app_slot_ctrl;
	slot_swap_ctrl_t uboot_slot_ctrl;
	slot_swap_ctrl_t os_slot_ctrl;
} slot_swap_ctrl_flash;

/* MAX. 64 bytes */
typedef struct {
	uint32_t magic_start;
	uint32_t is_boot_ok;
	uint8_t slot_select;
	uint8_t slot_active;
	uint8_t boot_ver_major;
	uint8_t boot_ver_minor;
	uint32_t magic_end;
} bt_app_intface_t;

/* MAX. 64 bytes */
typedef struct {
	uint32_t magic_start;
	uint32_t is_boot_ok;
	uint8_t slot_select;
	uint8_t slot_active;
	uint8_t boot_ver_major;
	uint8_t boot_ver_minor;
	uint8_t os_slot_select;		// used by uboot to select Linux images
	uint8_t os_slot_active;
	uint8_t os_boot_ver_major;
	uint8_t os_boot_ver_minor;
	uint32_t magic_end;
} bt_uboot_intface_t;
/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

/* Starts specified core based on the application description */
uint8_t Bl_StartApplication(Bl_ApplicationDetails * applicationConfig);

uint8_t Bl_DisableCore(uint8_t coreId);

uint8_t Bl_DisablePartition(uint8_t partition);

uint8_t Bl_DisableDDR(void);

/* get the active slot that will be used for boot */
int32_t get_active_slot(uint8_t *slot_app, uint8_t *slot_uboot, uint8_t *slot_os);

#ifdef __cplusplus
}
#endif

#endif/* BOOTLOADER_H */

/** @} */
