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

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include "BootLoader.h"
//#include <S32G274A.h>
#include "ext_flash.h"
#include "Swt_Ip.h"

#define BINDER_TAG_LE 0x00646E62
#define M7_CORE_START_INDEX 4
#define BOOTLOADER_CORE M7_CORE_START_INDEX

struct binder_item {
	uint32_t tag;
	uint32_t offset;
	uint32_t to;
	uint32_t length;
	uint32_t entry;
	uint32_t core;
	uint32_t reserved[2];
};

extern uint8_t __INT_SRAM_START[];
extern uint8_t __VECTOR_TABLE[];
extern uint8_t __BT_SHARE_DATA_START[];

extern uint8_t bt_uboot_interface[64];
extern uint8_t bt_app_interface[64];

#define M7_CCR 0xE000ED14
#define M7_DCCMVAU 0xE000EF64
#define DCACHE_ENABLE() (REG_READ32(M7_CCR) & (1<<16))
static void clean_dcache(unsigned long addr, unsigned long size)
{
	unsigned long i;

	for (i = 0; i < size; i += 32)
		REG_WRITE32(M7_DCCMVAU, addr +i);
	__asm__ volatile ("dsb");
}

static int copy_item(struct binder_item *item)
{
	void *src = __INT_SRAM_START + item->offset;
	void *dest = (void*)item->to;

	/* check address scope */
	memmove(dest, src, item->length);

	if (DCACHE_ENABLE())
		clean_dcache((unsigned long)dest, item->length);
	return 0;
}

int start_a53(uint32_t entry, uint32_t core)
{
	Bl_ApplicationDetails app;

	app.coreId = 0x10 | core;
	app.startAddress = entry;
	return Bl_StartApplication(&app);
}

static void start_m7(uint32_t entry, uint32_t core)
{
	Bl_ApplicationDetails app;

	app.coreId = core;
	app.startAddress = entry;
	Bl_StartApplication(&app);
}

static int startup_application(uint32_t entry, uint32_t core)
{
	if (core < M7_CORE_START_INDEX)
		start_a53(entry, core);
	else
		start_m7(entry, core - M7_CORE_START_INDEX);
	return 0;
}

#define AIRCR 0xE000ED0C
#define VTOR 0xE00ED08

static void jump_to_application(uint32_t entry)
{
#if 0
	REG_WRITE32 (MC_ME_PRTN_N_CORE_M_ADDR(0, 0), entry);

	REG_WRITE32(AIRCR, 0x05FA0001);
	while(1);
#else
	__asm__ volatile (
	"LDR %0, [%0, 4]\n\r"
	"BLX %0\n\r"
	::"r"(entry)
	);
#endif
}

/* for debug */
void boot_delay(int32_t cycle)
{
	int32_t delay = cycle;
	while(delay > 0)
		delay--;
}

/**
* @brief        SWT notification
* @details		first timeout
*/
void Swt_CallbackNotification0(void)
{
	// do nothing, reset after next timeout
}

int bootloader_main(char *msg_out)
{
	struct binder_item *item = (void*)__INT_SRAM_START;
	int ret;
	uint32_t entry = 1;
	uint32_t img_entry = 0, m7_entry = 0, size = 0;
	uint8_t slot_app = 0, slot_uboot = 0, slot_os = 0;

	bt_app_intface_t *bt_app;
	bt_uboot_intface_t *bt_uboot;

    /* Service SWT0 */
    Swt_Ip_Service(0);

	while (--item, (item->tag & 0x00ffffff) == BINDER_TAG_LE) {
		switch (item->tag >> 24) {
		case 0x55: /* data file */
			ret = copy_item(item);
			if (msg_out)
				msg_out += sprintf(msg_out, "Copied data for core %d size %d\r\n", (unsigned int)item->core, (unsigned int)item->length);
			break;
		case 0xaa: /* application file*/
			ret = copy_item(item);
			if (ret)
				break;
			if (msg_out)
				msg_out += sprintf(msg_out, "Copied text for core %d size %d\r\n", (unsigned int)item->core, (unsigned int)item->length);
			if (item->core == BOOTLOADER_CORE) {
				entry = item->entry;
				break;
			}
			ret = startup_application(item->entry, item->core);
			if (msg_out)
				msg_out += sprintf(msg_out, "Startup core %d at entry 0x%x\r\n", (unsigned int)item->core, (unsigned int)item->entry);
			break;
		}
	}

	if (entry != 1) {
		if (msg_out)
			msg_out += sprintf(msg_out, "Jump to application at entry 0x%x\r\n", (unsigned int)entry);

		if (DCACHE_ENABLE())
			clean_dcache((unsigned long)0x342c0000, 4*1024);

		jump_to_application(entry);
	}

    /* Service SWT0 */
    Swt_Ip_Service(0);

	if (get_active_slot(&slot_app, &slot_uboot, &slot_os) < 0)
	{
		/* error happens, use slot 0 */
		slot_app = 0;
		slot_uboot = 0;
	}

	if (msg_out)
		msg_out += sprintf(msg_out, "Loaded M7 APP from slot %d \r\n"
									"Loaded U-BOOT from slot %d\r\n", (unsigned int)slot_app, slot_uboot);

	/* load M7 application */
	if (load_app_m7(slot_app, &m7_entry, &size) > 0) {
		/* flush cache */
		if (DCACHE_ENABLE())
			clean_dcache((unsigned long)m7_entry, size);

		if (msg_out)
			msg_out += sprintf(msg_out, "M7 APP image is loaded @0x%x,%x\r\n", (unsigned int)m7_entry, size);
	}
#if 0
	/* load pfe firmware */
	if (load_pfe_fw(&img_entry, &size) > 0) {
		/* flush cache */
		if (DCACHE_ENABLE())
			clean_dcache((unsigned long)img_entry, size);

		if (msg_out)
			msg_out += sprintf(msg_out, "PFE fw image is loaded @0x%x,%x\r\n", (unsigned int)img_entry, size);
	}
#endif
	/* load u-bopot for A53 cores */
	if (load_uboot(slot_uboot, &img_entry, &size) > 0) {
		/* flush cache */
		if (DCACHE_ENABLE())
			clean_dcache((unsigned long)img_entry, size);

		bt_uboot = (bt_uboot_intface_t *)bt_uboot_interface;
		bt_uboot->is_boot_ok = 1;
		/* flush cache */
		if (DCACHE_ENABLE())
			clean_dcache((unsigned long)__BT_SHARE_DATA_START, 4*1024);

		startup_application(img_entry, 0);
		if (msg_out)
			msg_out += sprintf(msg_out, "U-BOOT image is loaded. Startup core 0 at entry 0x%x\r\n",
					(unsigned int)img_entry);
	}

    /* Service SWT0 */
    Swt_Ip_Service(0);

	if (m7_entry != 0) {
		if (msg_out)
			msg_out += sprintf(msg_out, "Jump to M7 APP at entry 0x%x\r\n", (unsigned int)m7_entry);

		/* de-init nor-flash */
		qspi_deinit();

		bt_app = (bt_app_intface_t *)bt_app_interface;
		bt_app->is_boot_ok = 1;

		/* flush cache */
		if (DCACHE_ENABLE())
			clean_dcache((unsigned long)__BT_SHARE_DATA_START, 4*1024);

		boot_delay(60 * 1000000);

		jump_to_application(m7_entry);
	}

	return 0;
}
