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

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include <stdio.h>
#include "Bootloader.h"
#include "ext_flash.h"
//#include "CDD_Mcl.h"
//#include "CDD_Mcl_Cfg.h"

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
/* Store the CRC result returned by the DMA-CRC engine for the two applications */
//uint16_t Bl_u16CrcResult[CONFIGURED_CORES_COUNT];

/* Store the enabled partitions information
   - 0: partition not enabled
   - 1: partition enabled
*/
uint8_t isPartitionEnabled[NUMBER_PARTITIONS] = {PARTITION_DISABLED};

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/
uint8_t bt_uboot_interface[64];
uint8_t bt_app_interface[64];
/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
/**
* @brief   Marks the partition used by the bootloader as enabled
* @details Marks the partition on which the bootloader application runs as enabled. 
*           This function is called once, before enabling all the other cores.       
*
* @param[in]     none
*
* @param[out]    E_OK if success
*				 E_NOT_OK if error
*/

uint8_t Bl_EnableCurrentPartition(void)
{
   uint8_t partition;
   
   partition = GET_PARTITION(0);
   
   isPartitionEnabled[partition] = PARTITION_ENABLED;
   
   return E_OK;  
}

/**
* @brief   Enables a partition
* @details Enables partition one of the common chasis platform
*
* @param[in]     partition Partition identification
*
* @param[out]    E_OK if success
*				 E_NOT_OK if error
*/

uint8_t Bl_EnablePartition(uint8_t partition)
{
	vuint16_t timeout = TIMEOUT_INIT;
	uint32_t regValue = 0;
	uint8_t status = E_NOT_OK;
	
    if (isPartitionEnabled[partition] == PARTITION_DISABLED)
    {	
        /* enable clock partition */
        REG_WRITE32 (MC_ME_PRTN_N_PCONF(partition), MC_ME_PARTITION_CLOCK_ENABLE);
        
        /* trigger hardware process for enabling clocks */
        REG_WRITE32 (MC_ME_PRTN_N_PUPD(partition), MC_ME_TRIGGER_PROCESS);
        
        /* write the valid key sequence */
        REG_WRITE32 (MC_ME_CTL_KEY_ADDR, MC_ME_CTL_KEY_VALUE);
        REG_WRITE32 (MC_ME_CTL_KEY_ADDR, MC_ME_CTL_KEY_INVERTED_VALUE);
        
        /* wait for partition clock status bit */
        while (((REG_READ32(MC_ME_PRTN_N_STAT(partition)) & MC_ME_PARTITION_CLOCK_ENABLE) != 1) && (timeout--)) ;
        
        /* unlock software reset domain control register */
        regValue = REG_READ32(RDC_RD1_CTRL_REGISTER) | RDC_RD1_CTRL_UNLOCK_ENABLE;
        REG_WRITE32(RDC_RD1_CTRL_REGISTER, regValue);
        
        /* enable the interconnect interface of software reset domain */
        regValue = REG_READ32(RDC_RD1_CTRL_REGISTER) & RDC_RD1_XBAR_INTERFACE_DISABLE;
        REG_WRITE32(RDC_RD1_CTRL_REGISTER, regValue);
        
        /* wait for software reset domain status register 
           to acknowledge interconnect interface not disabled*/
        while((((REG_READ32(RDC_RD1_STAT_REGISTER)) & RDC_RD1_XBAR_INTERFACE_STAT) != E_OK) && (timeout--));
            
        /* cluster reset */
        regValue = REG_READ32(RGM_PRST(partition)) & RGM_PRST_CLUSTER;
        REG_WRITE32 (RGM_PRST(partition), regValue);
        
        regValue = REG_READ32(MC_ME_PRTN_N_PCONF(partition)) & MC_ME_OUTPUT_PARTITION;
        REG_WRITE32 (MC_ME_PRTN_N_PCONF(partition), regValue);
        
        regValue = REG_READ32(MC_ME_PRTN_N_PUPD(partition)) | MC_ME_OUTPUT_STATUS;
        REG_WRITE32 (MC_ME_PRTN_N_PUPD(partition), regValue);
        
        /* write the valid key sequence */
        REG_WRITE32 (MC_ME_CTL_KEY_ADDR, MC_ME_CTL_KEY_VALUE);
        REG_WRITE32 (MC_ME_CTL_KEY_ADDR, MC_ME_CTL_KEY_INVERTED_VALUE);		
        
        /* wait until cluster is not in reset */
        while ((REG_READ32(RGM_PSTAT(partition)) & RGM_PSTAT_RESET_STATE) != E_OK);
        while (((REG_READ32(MC_ME_PRTN_N_STAT(partition)) & MC_ME_OUTPUT_STATUS) != 0x0) && (timeout--)) ;
        
        /* lock the reset domain controller */
        regValue = REG_READ32(RDC_RD1_CTRL_REGISTER) & RDC_RD1_CTRL_UNLOCK_DISABLE;
        REG_WRITE32(RDC_RD1_CTRL_REGISTER, regValue);	
    
        if (TIMEOUT_REACHED != timeout)
        {
            isPartitionEnabled[partition] = PARTITION_ENABLED;
            status =  E_OK;
        }
    }
    else
    {
        /* the partition is already enabled */
        status = E_OK;
    }
		
	return status;
}

uint8_t Bl_DisablePartition(uint8_t partition)
{
	vuint16_t timeout = TIMEOUT_INIT;
	uint32_t regValue = 0;
	uint8_t status = E_NOT_OK;

	if (partition != 1)
		return E_NOT_OK;

	if (isPartitionEnabled[partition] == PARTITION_DISABLED)
		return 0;

	/* S1. Disable all core in partition */
	

	/* S2. Disable XBAR interface */
	if ((REG_READ32(RDC_RD1_STAT_REGISTER) & (1<<4)) == 0) {

		/* unlock software reset domain control register */
        regValue = REG_READ32(RDC_RD1_CTRL_REGISTER) | RDC_RD1_CTRL_UNLOCK_ENABLE;
        REG_WRITE32(RDC_RD1_CTRL_REGISTER, regValue);
	
		regValue = REG_READ32(RDC_RD1_CTRL_REGISTER) | (1<<3);
		REG_WRITE32(RDC_RD1_CTRL_REGISTER, regValue);

		timeout = TIMEOUT_INIT;
		while((((REG_READ32(RDC_RD1_STAT_REGISTER)) & (1<<4)) == 0) && (timeout--));
		if ((REG_READ32(RDC_RD1_STAT_REGISTER) & (1<<4)) == 0) {
			printf("Disable partition 1 interconnet timeout\r\n");
			return -2;
		}
		regValue = REG_READ32(RDC_RD1_CTRL_REGISTER) & RDC_RD1_CTRL_UNLOCK_DISABLE;
        REG_WRITE32(RDC_RD1_CTRL_REGISTER, regValue);
	}
	
	/* S3. Disable partition clock */
	if (REG_READ32(MC_ME_PRTN_N_STAT(partition)) & 1) {
		
		regValue = REG_READ32(MC_ME_PRTN_N_PCONF(partition)) & (~1u);
        REG_WRITE32 (MC_ME_PRTN_N_PCONF(partition), regValue);
        
        regValue = REG_READ32(MC_ME_PRTN_N_PUPD(partition)) | 1;
        REG_WRITE32 (MC_ME_PRTN_N_PUPD(partition), regValue);
        
        /* write the valid key sequence */
        REG_WRITE32 (MC_ME_CTL_KEY_ADDR, MC_ME_CTL_KEY_VALUE);
        REG_WRITE32 (MC_ME_CTL_KEY_ADDR, MC_ME_CTL_KEY_INVERTED_VALUE);

		timeout = TIMEOUT_INIT;
		while((REG_READ32(MC_ME_PRTN_N_STAT(partition)) & 1) && (timeout--));
		if (REG_READ32(MC_ME_PRTN_N_STAT(partition)) & 1) {
			printf("Disable partition 1 clock timeout\r\n");
			return -3;
		}
	}
	
	/* S4. Enable partition isolation */
	if ((REG_READ32(MC_ME_PRTN_N_STAT(partition)) & (1<<2)) == 0) {
		
		regValue = REG_READ32(MC_ME_PRTN_N_PCONF(partition)) | (1<<2);
        REG_WRITE32 (MC_ME_PRTN_N_PCONF(partition), regValue);
        
        regValue = REG_READ32(MC_ME_PRTN_N_PUPD(partition)) | (1<<2);
        REG_WRITE32 (MC_ME_PRTN_N_PUPD(partition), regValue);
        
        /* write the valid key sequence */
        REG_WRITE32 (MC_ME_CTL_KEY_ADDR, MC_ME_CTL_KEY_VALUE);
        REG_WRITE32 (MC_ME_CTL_KEY_ADDR, MC_ME_CTL_KEY_INVERTED_VALUE);

		timeout = TIMEOUT_INIT;
		while(((REG_READ32(MC_ME_PRTN_N_STAT(partition)) & (1<<2)) == 0) && (timeout--));
		if ((REG_READ32(MC_ME_PRTN_N_STAT(partition)) & (1<<2)) == 0) {
			printf("Enable partition 1 iso timeout\r\n");
			return -4;
		}
	}
	/* S5. Assert partition reset */
	if ((REG_READ32(RGM_PSTAT(partition)) & RGM_PSTAT_RESET_STATE) == 0) {
		regValue = REG_READ32(RGM_PRST(partition)) | 1;
        REG_WRITE32 (RGM_PRST(partition), regValue);
		timeout = TIMEOUT_INIT;
		while(((REG_READ32(RGM_PSTAT(partition)) & RGM_PSTAT_RESET_STATE) == 0) && (timeout--));
		if ((REG_READ32(RGM_PSTAT(partition)) & RGM_PSTAT_RESET_STATE) == 0) {
			printf("Assert partition 1 reset timeout\r\n");
			return -5;
		}
	}
	isPartitionEnabled[partition] = PARTITION_DISABLED;
	return E_OK;
}

uint8_t Bl_DisableCore(uint8_t coreId)
{
	uint8_t partition = GET_PARTITION(coreId);
	uint8_t core    = GET_CORE_ID(coreId);
	volatile uint32_t timeout;
	
	/* S1. wait for WFI status */
	if ((REG_READ32(MC_ME_PRTN_N_CORE_M_STAT(partition, core)) & (1u<<31)) == 0)
		printf("coreId %x is not in WFI\r\n", coreId);
	
	/* S2. Disable core clock */
	if (REG_READ32(MC_ME_PRTN_N_CORE_M_STAT(partition, core)) & 1) {
		
		REG_WRITE32 (MC_ME_PRTN_N_CORE_M_PCONF(partition, core), 0);	    
	    /* trigger hardware process */
		REG_WRITE32 (MC_ME_PRTN_N_CORE_M_PUPD(partition, core), 1);
		
	    /* write key sequence */
		REG_WRITE32 (MC_ME_CTL_KEY_ADDR, MC_ME_CTL_KEY_VALUE);
		REG_WRITE32 (MC_ME_CTL_KEY_ADDR, MC_ME_CTL_KEY_INVERTED_VALUE);
		
	    /* wait for clock to be enabled */ 
		timeout = 0xffff;
		while ((REG_READ32(MC_ME_PRTN_N_CORE_M_STAT(partition, core)) & 1) && (timeout--)) ;
		if (REG_READ32(MC_ME_PRTN_N_CORE_M_STAT(partition, core)) & 1) {
			printf("coorId %x shutdown clock timeout\r\n", coreId);
			return -2;
		}
		
	}
	
	/* S3. Assert core reset */
	if ((REG_READ32(RGM_PSTAT(partition)) & (2<<core)) == 0) {
		REG_WRITE32 (RGM_PRST(partition), REG_READ32(RGM_PRST(partition)) | (2<<core));

		timeout = 0xffff;
		while ((REG_READ32(RGM_PSTAT(partition)) & (2<<core)) == 0 && timeout--);
		if ((REG_READ32(RGM_PSTAT(partition)) & (2<<core)) == 0) {
			printf("coorId %x assert reset timeout\r\n", coreId);
			return -3;
		}
	}
	return 0;
}

uint8_t Bl_DisableDDR(void)
{
	vuint16_t timeout = TIMEOUT_INIT;
	
	if ((REG_READ32(RGM_PSTAT(0)) & (1<<3)) == 0) {
		REG_WRITE32 (RGM_PRST(0), REG_READ32(RGM_PRST(0)) | (1<<3));

		timeout = 0xffff;
		while ((REG_READ32(RGM_PSTAT(0)) & (1<<3)) == 0 && timeout--);
		if ((REG_READ32(RGM_PSTAT(0)) & (1<<3)) == 0) {
			printf("ddr assert reset timeout\r\n");
			return -1;
		}
	}
	return 0;
}

/**
* @brief   Starts an application
* @details Starts an application based on the input application configuration
*
* @param[in]     applicationConfig The application configuration.
*
* @param[out]    E_OK if success
*				 E_NOT_OK if error
*/
uint8_t Bl_StartApplication(Bl_ApplicationDetails * applicationConfig)
{
	vuint16_t timeout = 0xffff;
	uint32_t coreStartAddress;
	uint8_t partition, coreId;
	uint32_t resetCore;
	uint8_t status = E_NOT_OK;
	
	Bl_EnableCurrentPartition();

	coreStartAddress = (applicationConfig->startAddress) & 0xfffffffc;
	partition = GET_PARTITION(applicationConfig->coreId);
	coreId    = GET_CORE_ID(applicationConfig->coreId);
	
	if (E_OK == Bl_EnablePartition(partition))
	{
		REG_WRITE32 (MC_ME_PRTN_N_CORE_M_ADDR(partition,coreId), coreStartAddress);

        /* enable core clock */
		REG_WRITE32 (MC_ME_PRTN_N_CORE_M_PCONF(partition,coreId), 1);
		REG_WRITE32 (MC_ME_PRTN_N_PCONF(partition), 1);
        
        /* trigger hardware process */
		REG_WRITE32 (MC_ME_PRTN_N_CORE_M_PUPD(partition,coreId), 1);
		
        /* write key sequence */
		REG_WRITE32 (MC_ME_CTL_KEY_ADDR, MC_ME_CTL_KEY_VALUE);
		REG_WRITE32 (MC_ME_CTL_KEY_ADDR, MC_ME_CTL_KEY_INVERTED_VALUE);
		
        /* wait for clock to be enabled */ 
		while ((REG_READ32(MC_ME_PRTN_N_CORE_M_STAT(partition,coreId)) != 1) && (timeout--)) ;
		while (((REG_READ32(MC_ME_PRTN_N_STAT(partition)) & MC_ME_CLOCK_ACTIVE) != 1) && (timeout--)) ;
		
        /* pull the core out of reset and wait for it */
		resetCore = REG_READ32(RGM_PRST(partition)) & RGM_PRST_RESET_CORE(partition, coreId);
		REG_WRITE32 (RGM_PRST(partition), resetCore);
		while ((REG_READ32(RGM_PSTAT(partition)) & RGM_PRST_STATUS_CORE(partition, coreId)) != 0);
		
		if (TIMEOUT_REACHED != timeout)
			status = E_OK;
	}
	
	return status;
}

int32_t slot_ctrl_init(slot_swap_ctrl_t *slot_ctrl, uint8_t slot_index)
{
	int32_t ret = -1;

	slot_ctrl->magic_start = SLOT_MAGIC_START;
	slot_ctrl->slot_index = slot_index;
	slot_ctrl->major_version = 0;
	slot_ctrl->minor_version = 0;
	slot_ctrl->retry_remain = 4;
	slot_ctrl->install_counter = 0;

	if (slot_index == 0)
		slot_ctrl->flags = SLOT_FLAGS_ACTIVE | SLOT_FLAGS_VALID;
	else
		slot_ctrl->flags = SLOT_FLAGS_VALID;

	/* todo: calculate CRC */
	slot_ctrl->crc_checksum = 0;

	slot_ctrl->magic_end = SLOT_MAGIC_END;

	return 0;
}

uint8_t select_slot(slot_swap_ctrl_t *slot_A, slot_swap_ctrl_t *slot_B, uint8_t flags)
{
	uint8_t slot = 0;
	uint8_t ver_major, ver_minor;
	bt_app_intface_t *bt_app;
	bt_uboot_intface_t *bt_uboot;

	if (((slot_A->flags & SLOT_FLAGS_VALID) != 0) &&
			((slot_A->flags & SLOT_FLAGS_ACTIVE) != 0)) {
//		slot = slot_A->slot_index;
		slot = 0;
		ver_major = slot_A->major_version;
		ver_minor = slot_A->minor_version;
	}

	if (((slot_B->flags & SLOT_FLAGS_VALID) != 0) &&
			((slot_B->flags & SLOT_FLAGS_ACTIVE) != 0)) {
//		slot = slot_B->slot_index;
		slot = 1;
		ver_major = slot_B->major_version;
		ver_minor = slot_B->minor_version;
	}

	if (flags == 0x1) {
		bt_app = (bt_app_intface_t *)bt_app_interface;
		bt_app->magic_start = SLOT_MAGIC_START;
		bt_app->is_boot_ok = 0;
		bt_app->slot_select = slot;
		bt_app->slot_active = slot;
		bt_app->boot_ver_major = ver_major;
		bt_app->boot_ver_minor = ver_minor;
		bt_app->magic_end = SLOT_MAGIC_END;
	} else if (flags == 0x2) {
		bt_uboot = (bt_uboot_intface_t *)bt_uboot_interface;
		bt_uboot->magic_start = SLOT_MAGIC_START;
		bt_uboot->is_boot_ok = 0;
		bt_uboot->slot_select = slot;
		bt_uboot->slot_active = slot;
		bt_uboot->boot_ver_major = ver_major;
		bt_uboot->boot_ver_minor = ver_minor;
		bt_uboot->magic_end = SLOT_MAGIC_END;
	} else if (flags == 0x4) {
		bt_uboot = (bt_uboot_intface_t *)bt_uboot_interface;
		bt_uboot->magic_start = SLOT_MAGIC_START;
		bt_uboot->os_slot_select = slot;
		bt_uboot->os_slot_active = slot;
		bt_uboot->os_boot_ver_major = ver_major;
		bt_uboot->os_boot_ver_minor = ver_minor;
		bt_uboot->magic_end = SLOT_MAGIC_END;
	}

	return slot;
}

int32_t check_slot_ctrl(slot_swap_ctrl_t *slot_ctrl, uint8_t slot_index, uint8_t *update)
{
	int32_t ret = 1;

	if ((slot_ctrl->magic_start == SLOT_MAGIC_EMPTY) &&
				(slot_ctrl->magic_end == SLOT_MAGIC_EMPTY)) {
		ret = slot_ctrl_init(slot_ctrl, slot_index);

		if (update != 0L)
			*update += 1;
	}

	if ((slot_ctrl->magic_start != SLOT_MAGIC_START) ||
			(slot_ctrl->magic_end != SLOT_MAGIC_END)) {
		ret = -1;
	}

	/* todo: check CRC */

	return ret;
}

int32_t get_active_slot(uint8_t *slot_app, uint8_t *slot_uboot, uint8_t *slot_os)
{
	int32_t ret = -1;
	slot_swap_ctrl_flash slot_A, slot_B;
	uint8_t update = 0;

	/* read slot A data */
	if (flash_read_slot((uint8_t *)&slot_A, 0, sizeof(slot_A)) > 0) {
		if (check_slot_ctrl(&slot_A.app_slot_ctrl, 0, &update) < 0) {
			return ret;
		}

		if (check_slot_ctrl(&slot_A.uboot_slot_ctrl, 0, &update) < 0) {
			return ret;
		}

		if (check_slot_ctrl(&slot_A.os_slot_ctrl, 0, &update) < 0) {
			return ret;
		}

		if (update > 0)
			flash_prog_slot(&slot_A, 0, sizeof(slot_A));
	}

	update = 0;

	/* read slot B data */
	if (flash_read_slot((uint8_t *)&slot_B, 1, sizeof(slot_B)) > 0) {
		if (check_slot_ctrl(&slot_B.app_slot_ctrl, 1, &update) < 0) {
			return ret;
		}

		if (check_slot_ctrl(&slot_B.uboot_slot_ctrl, 1, &update) < 0) {
			return ret;
		}

		if (check_slot_ctrl(&slot_B.os_slot_ctrl, 1, &update) < 0) {
			return ret;
		}

		if (update > 0)
			flash_prog_slot(&slot_B, 1, sizeof(slot_B));
	}

	if (slot_app != 0L)
		*slot_app = select_slot(&slot_A.app_slot_ctrl, &slot_B.app_slot_ctrl, 0x1);

	if (slot_uboot != 0L)
		*slot_uboot = select_slot(&slot_A.uboot_slot_ctrl, &slot_B.uboot_slot_ctrl, 0x2);

	if (slot_os != 0L)
		*slot_os = select_slot(&slot_A.os_slot_ctrl, &slot_B.os_slot_ctrl, 0x4);

	ret = 0;

	return ret;
}



/** @} */
