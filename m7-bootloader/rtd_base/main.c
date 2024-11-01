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

#include <stdio.h>
#include <string.h>
#if defined(USING_OS_FREERTOS)
/* FreeRTOS kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#endif /* defined(USING_OS_FREERTOS) */

#include "osif.h"


#include "device.h"
#include "IntCtrl_Ip.h"
#include "Linflexd_Uart_Ip.h"
#include "Linflexd_Uart_Ip_Irq.h"
#include "Clock_Ip.h"
//#include "Crypto_MemMap.h"

extern int bootloader_main(char *msg_out);
extern void mainLoopTask(void* pvParameters);
extern void welome(const char ch, const char bg);

char g_bl_msg[1024];
#if 0
static rx_ret_t print_recv_msg(void *arg, int ch, void *buff, uint32_t size)
{
	(void)arg;
	(void)size;
	printf("ch%d: %s\r\n", ch, (char*)buff);
	if (ch == 1 && *(char*)buff == 'S') 
		ipc_show_stats();

	return IPC_RX_OK;
}

static rx_ret_t hexdump_recv_msg(void *arg, int ch, void *buff, uint32_t size)
{
	uint32_t i;
	uint32_t dump_len = size > 64 ? 64 : size;
	
	(void)arg;
	printf("ch%d: len=%u", ch, (unsigned int)size);
	for (i = 0; i < dump_len; i++)
		printf((i & 0xf) ? " %02X" : "\n\r %02X", *((uint8_t*)buff + i));

	printf("\r\n");
	return IPC_RX_OK;
}

static void mainTask(void* pvParam)
{
	uint32_t loop_cnt = 0;
	int ret;

	(void)pvParam;

	printf("***\r\n");
	if (*g_bl_msg)
		printf("Bootloader: %s\n\r", g_bl_msg);
	
	ret = ipc_init();
	ipc_reg_rx_callback(0, hexdump_recv_msg, NULL);
	ipc_reg_rx_callback(1, print_recv_msg, NULL);
	printf("Init %-10s --- [ok]\n\r", "ipc");
		
	ret = xTaskCreate(mainLoopTask, "lwip", 512U, NULL, 3, NULL);
	configASSERT(ret);
	printf("Init %-10s --- [ok]\n\r", "lwip");

	welome('*', ' ');
	printf("\n\rGo to main loop\r\n");
	for(;;) {
        if (ipc_ready()) {
			void *buf = ipc_shm_acquire_buf(1, 64);

			if (buf) {
				snprintf(buf, 64, "hello%u", (unsigned int)loop_cnt);
				if (ipc_tx(1, buf, strlen(buf)+1))
					ipc_shm_release_buf(1, buf);
			} else
				printf("acquite buf fail\n\r");
        }
		
        OsIf_TimeDelay(2000);
        loop_cnt++;
    }
}
#endif

/* main function */
int main(void)
{
	int32_t ret;
    if ((ret = device_init()) >= 0)
    {
    	printf("Devices initialization OK!\r\n");
    }
    else
    {
    	printf("Errors in device_init! %d\r\n", ret);
    }

	/* for booting A53 */
    bootloader_main(g_bl_msg);

#if 0
	ret = xTaskCreate(mainTask,
					"main",
					2048,
					NULL,
					2,
					NULL);
	configASSERT(ret);

	vTaskStartScheduler();
#endif

	while(1);

    return 0;
}
