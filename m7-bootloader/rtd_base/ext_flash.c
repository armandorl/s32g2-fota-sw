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

/* Including necessary configuration files. */
#include "osif.h"
#include "Qspi_Ip.h"
#include "Qspi_Ip_Cfg.h"
#include "ext_flash.h"

#define QSPI_INSTANCE 0U

uint32_t flash_image_table[] = {
		0x200000,	// uboot A
		0x400000,	// uboot B
		0x600000,	// m7 app A
		0x800000,	// m7 app B
		0xA00000,	// PFE firmware

		0xC00000,	// slot ctrl A
		0xC80000,	// slot ctrl B
		0xD00000,	// slot ctrl backup A
		0xD80000,	// slot ctrl backup B
};

int32_t qspi_init(void)
{
	Qspi_Ip_StatusType status;

    /* Initialize QSPI */
    status = Qspi_Ip_ControllerInit(QSPI_INSTANCE, QspiConfigSet_BOARD_InitPeripherals_paQspiUnitCfg);
    if (STATUS_QSPI_IP_SUCCESS == status)
    {
        status = Qspi_Ip_Init(QSPI_INSTANCE, QspiConfigSet_BOARD_InitPeripherals_paFlashCfg, QspiConfigSet_BOARD_InitPeripherals_paFlashConnectionCfg);
        if (STATUS_QSPI_IP_SUCCESS != status)
        {
        	return -2;
        }
    }
    else
    {
    	return -3;
    }

    return 0;
}

int32_t qspi_deinit(void)
{
	int32_t ret;

	ret = Qspi_Ip_Deinit(QSPI_INSTANCE);
	if (ret != STATUS_QSPI_IP_SUCCESS)
		return -ret;

	ret = Qspi_Ip_ControllerDeinit(QSPI_INSTANCE);
	if (ret != STATUS_QSPI_IP_SUCCESS)
		return -ret;
}

int32_t flash_read(uint8_t *data, uint32_t address, uint32_t length)
{
	uint32_t size, chunk_size;
	Qspi_Ip_StatusType status;

    chunk_size = 256;
    for (size = 0; size < length; size += chunk_size)
    {
    	if ((size + chunk_size) > length)
    	{
    		chunk_size = length - size;
    	}
    	status = Qspi_Ip_Read(QSPI_INSTANCE, address + size, data + size, chunk_size);
    	if (status != STATUS_QSPI_IP_SUCCESS)
    	{
    		break;
    	}
    }

    if ((size >= length) && ((status == STATUS_QSPI_IP_SUCCESS)))
    {
    	return 1;
    }

    return -1;
}

int32_t flash_prog(uint8_t *data, uint32_t address, uint32_t length)
{
	uint32_t erase_addr = address;
	uint32_t sector_size = 0x1000U;
	uint32_t chunk_size = 256;
	int32_t i;
	Qspi_Ip_StatusType status;

    /* erase a sector */
    status = Qspi_Ip_EraseBlock(QSPI_INSTANCE, erase_addr, sector_size);
    if (status ==  STATUS_QSPI_IP_SUCCESS) {
    	while ((STATUS_QSPI_IP_BUSY == Qspi_Ip_GetMemoryStatus(QSPI_INSTANCE)));

    	if (STATUS_QSPI_IP_SUCCESS != Qspi_Ip_EraseVerify(QSPI_INSTANCE, erase_addr, sector_size)) {
    		return -1;
    	}
    }

    /* Write data in chunks of 256 bytes */
    for (i = 0; i < (length / chunk_size); i++)
    {
        status = Qspi_Ip_Program(QSPI_INSTANCE, erase_addr + i * chunk_size, data + i * chunk_size, chunk_size);
        if (status == STATUS_QSPI_IP_SUCCESS) {
        	while ((STATUS_QSPI_IP_BUSY == Qspi_Ip_GetMemoryStatus(QSPI_INSTANCE)));

        	/* verify written data */
        	if (STATUS_QSPI_IP_SUCCESS != Qspi_Ip_ProgramVerify(QSPI_INSTANCE, erase_addr + i * chunk_size, data + i * chunk_size, chunk_size))
        	{
        		return -2;
        	}
        }
    }
    if (length % chunk_size)
    {
        /* Write last data chunk */
        status = Qspi_Ip_Program(QSPI_INSTANCE, erase_addr + i * chunk_size, data + i * chunk_size, length % chunk_size);
        if (status == STATUS_QSPI_IP_SUCCESS) {
        	while ((STATUS_QSPI_IP_BUSY == Qspi_Ip_GetMemoryStatus(QSPI_INSTANCE)));

        	/* verify written data */
        	if (STATUS_QSPI_IP_SUCCESS != Qspi_Ip_ProgramVerify(QSPI_INSTANCE, erase_addr + i * chunk_size, data + i * chunk_size, length % chunk_size))
        	{
        		return -3;
        	}
        }
    }

    return 1;
}

int32_t flash_prog_slot(uint8_t *data, uint8_t slot, uint32_t length)
{
	if ((slot == 0) || (slot == 1)) {
		return flash_prog(data, flash_image_table[slot + FLASH_CTRL_A], length);
	}

	return -1;
}

int32_t flash_read_slot(uint8_t *data, uint8_t slot, uint32_t length)
{
	if ((slot == 0) || (slot == 1)) {
		return flash_read(data, flash_image_table[slot + FLASH_CTRL_A], length);
	}

	return -1;
}

int32_t load_pfe_fw(uint32_t *entry, uint32_t *image_size)
{
	uint32_t header[0x40 >> 2] = {0};
	uint32_t image_ptr;
	int32_t ret = -1;

	*entry = 0;

    image_ptr = flash_image_table[FLASH_IMG_PFE_FW];

    /* load header */
    if (flash_read((uint8_t *)header, image_ptr, sizeof(header)) > 0)
    {
    	if (header[0] != 0x600000d5)
    	{
    		goto F_RET_;
    	}

    	if (flash_read((uint8_t *)header[1], image_ptr + 0x40, header[3]) > 0)
    	{
        	*entry = header[2];
        	*image_size = header[3];
        	ret = 1;
    	}
    }

F_RET_:
	return ret;
}

int32_t load_uboot(uint8_t slot, uint32_t *entry, uint32_t *image_size)
{
	uint32_t header[0x40 >> 2] = {0};
	uint32_t image_ptr;
	int32_t ret = -1;

	*entry = 0;

    image_ptr = flash_image_table[slot + FLASH_IMG_UBOOT_A];	// TODO: stub

    /* load header */
    if (flash_read((uint8_t *)header, image_ptr, sizeof(header)) > 0)
    {
    	if (header[0] != 0x600000d5)
    	{
    		goto F_RET_;
    	}

    	if (flash_read((uint8_t *)header[1], image_ptr + 0x40, header[3]) > 0)
    	{
        	*entry = header[2];
        	*image_size = header[3];
        	ret = 1;
    	}
    }

F_RET_:
	return ret;
}

int32_t load_app_m7(uint8_t slot, uint32_t *entry, uint32_t *image_size)
{
	uint32_t header[0x40 >> 2] = {0};
	uint32_t image_ptr;
	int32_t ret = -1;

	*entry = 0;

    image_ptr = flash_image_table[slot + FLASH_IMG_APP_A];	// TODO: stub

    /* load header */
    if (flash_read((uint8_t *)header, image_ptr, sizeof(header)) > 0)
    {
    	if (header[0] != 0x600000d5)
    	{
    		goto F_RET_;
    	}

    	if (flash_read((uint8_t *)header[1], image_ptr + 0x40, header[3]) > 0)
    	{
        	*entry = header[2];
        	*image_size = header[3];
        	ret = 1;
    	}
    }

F_RET_:
	return ret;
}

int32_t qspi_read_test(void)
{
	uint32_t read_buff[256 >> 2];

    /* Read data from external flash*/
    if (STATUS_QSPI_IP_SUCCESS != Qspi_Ip_Read(0, 0x0, read_buff, sizeof(read_buff)))
    {
        return -10;
    }

    if (read_buff[0] != 0x600001D1)
    {
    	return -11;
    }

    return 0;
}
