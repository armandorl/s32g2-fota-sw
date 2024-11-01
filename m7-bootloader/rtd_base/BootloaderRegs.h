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


#ifndef BOOTLOADERREGS_H
#define BOOTLOADERREGS_H

#ifdef __cplusplus
extern "C" {
#endif

#define MC_ME_BASE_ADDR (0x40088000UL)

/* MC_ME registers. */
#define MC_ME_CTL_KEY_ADDR              (MC_ME_BASE_ADDR)
#define MC_ME_CTL_KEY_VALUE             (0x00005AF0)
#define MC_ME_CTL_KEY_INVERTED_VALUE    (0x0000A50F)
#define MC_ME_PARTITION_CLOCK_ENABLE    (0x00000001U)
#define MC_ME_TRIGGER_PROCESS           (0x00000001U)
#define MC_ME_OUTPUT_PARTITION          (0xFFFFFFFD)
#define MC_ME_OUTPUT_STATUS             (0x4)
#define MC_ME_CLOCK_ACTIVE              (0x1)

/* MC_ME partition definitions */
#define MC_ME_PRTN_N(n)             (MC_ME_BASE_ADDR + 0x100 + (n) * 0x200)
#define MC_ME_PRTN_N_PCONF(n)       (MC_ME_PRTN_N(n))
#define MC_ME_PRTN_N_PUPD(n)        (MC_ME_PRTN_N(n) + 0x4)
#define MC_ME_PRTN_N_STAT(n)        (MC_ME_PRTN_N(n) + 0x8)


/* MC_ME partition n core m definitions. */
#define MC_ME_PRTN_N_CORE_M(n, m)   (MC_ME_BASE_ADDR + 0x140 + \
                                    (n) * 0x200 + (m) * 0x20)
#define MC_ME_PRTN_N_CORE_M_PCONF(n, m) (MC_ME_PRTN_N_CORE_M(n, m))
#define MC_ME_PRTN_N_CORE_M_PUPD(n, m)  (MC_ME_PRTN_N_CORE_M(n, m) + 0x4)
#define MC_ME_PRTN_N_CORE_M_STAT(n, m)  (MC_ME_PRTN_N_CORE_M(n, m) + 0x8)
#define MC_ME_PRTN_N_CORE_M_ADDR(n, m)  (MC_ME_PRTN_N_CORE_M(n, m) + 0xC)

/* MC_RGM registers */
#define MC_RGM_BASE_ADDR (0x40078000UL)

#define RGM_DES             (MC_RGM_BASE_ADDR + 0x0)
#define RGM_DES_POR         (0x00000001)

#define RGM_FES             (MC_RGM_BASE_ADDR + 0x8)
#define RGM_FES_EXT         (0x00000001)

#define RGM_PRST(per)       (MC_RGM_BASE_ADDR + 0x40 + (per) * 0x8)
#define RGM_PSTAT(per)      (MC_RGM_BASE_ADDR + 0x140 + (per) * 0x8)

#define RGM_PRST_CLUSTER           (0xFFFFFFFE)
#define RGM_PSTAT_RESET_STATE      (0x1)
#define RGM_PRST_RESET_CORE(n, m)  (~(1 << (m + n)))
#define RGM_PRST_STATUS_CORE(n, m) ((1 << (m + n)))


/* RDC registers */
#define RDC_BASE_ADDR (0x40080000UL)

#define RDC_RD1_CTRL_REGISTER  (RDC_BASE_ADDR + 0x4)
#define RDC_RD1_STAT_REGISTER  (RDC_BASE_ADDR + 0x84)

#define RDC_RD1_CTRL_UNLOCK_ENABLE (0x80000000)
#define RDC_RD1_CTRL_UNLOCK_DISABLE (~(0x80000000))
#define RDC_RD1_XBAR_INTERFACE_DISABLE (~(0x8))
#define RDC_RD1_XBAR_INTERFACE_STAT   (0x10U)

#ifdef __cplusplus  
}
#endif

#endif/* BOOTLOADERREGS_H */