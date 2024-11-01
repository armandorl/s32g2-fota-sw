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


#ifndef EXT_FLASH_H_
#define EXT_FLASH_H_


#define FLASH_IMG_UBOOT_A 	(0)
#define FLASH_IMG_UBOOT_B 	(1)
#define FLASH_IMG_APP_A 	(2)
#define FLASH_IMG_APP_B 	(3)
#define FLASH_IMG_PFE_FW 	(4)
#define FLASH_CTRL_A		(5)
#define FLASH_CTRL_B		(6)

extern int32_t qspi_init(void);
extern int32_t qspi_deinit(void);
extern int32_t flash_read(uint8_t *data, uint32_t address, uint32_t length);
extern int32_t load_uboot(uint8_t slot, uint32_t *entry, uint32_t *size);
extern int32_t load_app_m7(uint8_t slot, uint32_t *entry, uint32_t *size);
extern int32_t load_pfe_fw(uint32_t *entry, uint32_t *image_size);
int32_t flash_read_slot(uint8_t *data, uint8_t slot, uint32_t length);
int32_t flash_prog_slot(uint8_t *data, uint8_t slot, uint32_t length);
int32_t qspi_read_test(void);

#endif /* EXT_FLASH_H_ */
