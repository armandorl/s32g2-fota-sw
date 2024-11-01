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


#ifndef BOOTLOADERSPECIFIC_H
#define BOOTLOADERSPECIFIC_H

#ifdef __cplusplus
extern "C" {
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/* Enumerates all the cores on the platform 
 * First 4 bits mask the partition
 * Last  4 bits mask the core id
 */
#define M7_0  0x00 /* Partition 0, Core 0 */
#define M7_1  0x01 /* Partition 0, Core 1 */
#define M7_2  0x02 /* Partition 0, Core 2 */
#define A53_0 0x10 /* Partition 1, Core 0 */
#define A53_1 0x11 /* Partition 1, Core 1 */
#define A53_2 0x12 /* Partition 1, Core 2 */
#define A53_3 0x13 /* Partition 1, Core 3 */

/* Get the partition from the core identity */
#define GET_PARTITION(n) ((n) >> 4)

/* Get the core id from the core identity */
#define GET_CORE_ID(n)   ((n) & 0x0F)
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/
#define DMA_CHANNEL (0U)

#define DMA_CRC_CHANNEL (0U)

/* Define the number of applications used in the demo */
#define NUM_APPLICATIONS 1U

/* Defines the type of core to boot */
#define BOOT_CORE_TYPE A53

/* Defines the number of cores on a platform */
#define NUMBER_CORES 7U

/* Defines a core offset. On some platforms the bootloader may be running on the first core */
#define CORE_OFFSET 0U

/* Disable DMA features SMOD and DMOD. */ 
#define DISABLE_FEATURE     ((uint32)0x00000000UL)

/* Number of DMA major loops */
#define ITER_COUNT          ((uint32)0x00000001UL)

/* Defines the address for the MCL configuration structure. */
#define MCL_CONFIGURATION (&MclConfigSet_0)

#ifdef __cplusplus	
}
#endif

#endif/* BOOTLOADERSPECIFIC_H */

/** @} */
