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
#ifdef LINFLEXD_1_LIN_UART_MODE
#include "Linflexd_Uart_Ip.h"
#endif
#include "OsIf.h"

#ifdef LINFLEXD_1_LIN_UART_MODE
//static mutex_t g_write_mutex;
static void mutex_lock(void)
{
//	if (!g_write_mutex)
//		OsIf_MutexCreate(&g_write_mutex);
//	OsIf_MutexLock(&g_write_mutex, OSIF_WAIT_FOREVER);
}

static void mutex_unlock(void)
{
//	OsIf_MutexUnlock(&g_write_mutex);
}
#endif

int _write(int handle, char *data, int size )
{
    handle = handle ; // unused
#ifdef LINFLEXD_1_LIN_UART_MODE
	mutex_lock();
	Linflexd_Uart_Ip_SyncSend(1, (uint8*)data, size);
	mutex_unlock();
#else
	(void)data;
#endif
    return size;
}

_ssize_t _write_r (struct _reent *r, int fd, const void *buf, size_t nbytes)
{
	(void)r;
	(void)fd;
	
 #ifdef LINFLEXD_1_LIN_UART_MODE
	mutex_lock();
	Linflexd_Uart_Ip_SyncSend(1, (uint8*)buf, nbytes);
	mutex_unlock();
#else
	(void)buf;
#endif
  return nbytes;
}


