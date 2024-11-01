/**
**  Copyright 2018-2020 NXP.
**  This software is owned or controlled by NXP and may only be used strictly in accordance with the applicable license terms.  
**  By expressly accepting such terms or by downloading, installing, activating and/or otherwise using the software  
**  you are agreeing that you have read, and that you agree to comply with and are bound by, such license terms.  
**  If you do not agree to be bound by the applicable license terms, then you may not retain, install, activate or otherwise use the software.  
*/  

#if defined (__GNUC__)
#include "stdint.h"

/* IVT binary */
const uint8_t ivt_binary[256] = {

	/* HEADER */
	0xd1, 0x1, 0x0, 0x60, 
	
	/* reserved_1 */
	0x0, 0x0, 0x0, 0x0, 
	/* Self-Test DCD */
	0x0, 0x0, 0x0, 0x0, 
	/* Self-Test DCD (backup) */
	0x0, 0x0, 0x0, 0x0, 
	/* DCD */
	0x0, 0x0, 0x0, 0x0, 
	/* DCD (backup) */
	0x0, 0x0, 0x0, 0x0, 
	/* HSE */
	0x0, 0x0, 0x0, 0x0, 
	/* HSE (backup) */
	0x0, 0x0, 0x0, 0x0, 
	/* Application bootloader */
	0x0, 0x0, 0x1, 0x0, 
	/* Application bootloader (backup) */
	0x0, 0x0, 0x0, 0x0, 
	/* boot_config */
	0x0, 0x0, 0x0, 0x0, 
	/* life_cycle_config */
	0x0, 0x0, 0x0, 0x0, 
	/* reserved_2 */
	0x0, 0x0, 0x0, 0x0, 
	/* hse_fw_config */
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
	/* reserved_3 */
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
	/* gmac */
	0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 
	
};

#endif
