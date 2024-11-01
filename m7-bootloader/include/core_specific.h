/*==================================================================================================
*   Project              : RTD AUTOSAR 4.4
*   Platform             : CORTEXM
*   Peripheral           : 
*   Dependencies         : none
*
*   Autosar Version      : 4.4.0
*   Autosar Revision     : ASR_REL_4_4_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 1.0.0
*   Build Version        : S32_RTD_1_0_0_D2012_ASR_REL_4_4_REV_0000_20201222
*
*   (c) Copyright 2020 NXP Semiconductors
*   All Rights Reserved.
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef CORE_SPECIFIC_H
#define CORE_SPECIFIC_H

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Std_Types.h"

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/* MPU setting */
#ifndef MULTIPLE_IMAGE
/* Single ELF for one or all cores */
/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/
/* Number of entries in the memory tables */
#define CPU_MPU_MEMORY_COUNT (12U)

/*
  Region  Description        Start       End           Size[KB]  Type              Inner Cache Policy    Outer Cache Policy    Shareable    Executable    Privileged Access    Unprivileged Access
--------  -----------------  ----------  ----------  ----------  ----------------  --------------------  --------------------  -----------  ------------  -------------------  ---------------------
       0  Whole memory map   0x0         0xFFFFFFFF     4194304  Strongly Ordered  None                  None                  Yes          No            No Access            No Access
       1  QSPI AHB           0x0         0x1FFFFFFF      524288  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       2  DTCM               0x20000000  0x201FFFFF        2048  Strongly Ordered  None                  None                  Yes          Yes           Read/Write           Read/Write
       3  HSE Shared RAM     0x22C00000  0x22C03FFF          16  Normal            None                  None                  Yes          Yes           Read/Write           Read/Write
       4  Standby RAM        0x24000000  0x24007FFF          32  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       5  RAM(1st 4MB)       0x34000000  0x343FFFFF        4096  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       6  RAM(4MB)           0x34400000  0x347FFFFF        4096  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       7  Non-Cacheable RAM  0x34600000  0x347FFFFF        2048  Normal            None                  None                  Yes          Yes           Read/Write           Read/Write
       8  Peripherals        0x40000000  0x5FFFFFFF      524288  Device            None                  None                  Yes          No            Read/Write           Read/Write
       9  LLCE               0x43800000  0x4383FFFF         256  Device            None                  None                  Yes          No            Read/Write           Read/Write
       10 PPB                0xE0000000  0xE00FFFFF        1024  Strongly Ordered  None                  None                  Yes          No            Read/Write           Read/Write
       11 Non-Cacheable RAM  0x34500000  0x345FFFFF        1024  Normal            None                  None                  Yes          No            Read/Write           Read/Write
*/

static const uint32 rbar[CPU_MPU_MEMORY_COUNT] = {0x00000000UL, 0x00000000UL, 0x20000000UL, 0x22C00000UL, 0x24000000UL, 0x34000000UL, 0x34400000UL, 0x34600000UL, 0x40000000UL, 0x43800000UL, 0xE0000000UL, 0x34500000UL};
static const uint32 rasr[CPU_MPU_MEMORY_COUNT] = {0x1004003FUL, 0x030B0039UL, 0x0104001FUL, 0x130C001BUL, 0x030B001DUL, 0x030B002BUL, 0x030B002BUL, 0x130C0029UL, 0x13050039UL, 0x13050023UL, 0x13040027UL, 0x130C0027UL};
#else
#if defined(CORE0)
/* Multiple core approach */
/* Number of entries in the memory tables */
#define CPU_MPU_MEMORY_COUNT (11U)

/*
  Region  Description        Start       End           Size[KB]  Type              Inner Cache Policy    Outer Cache Policy    Shareable    Executable    Privileged Access    Unprivileged Access
--------  -----------------  ----------  ----------  ----------  ----------------  --------------------  --------------------  -----------  ------------  -------------------  ---------------------
       0  Whole memory map   0x0         0xFFFFFFFF     4194304  Strongly Ordered  None                  None                  Yes          No            No Access            No Access
       1  QSPI AHB           0x0         0x1FFFFFFF      524288  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       2  DTCM               0x20000000  0x201FFFFF        2048  Strongly Ordered  None                  None                  Yes          Yes           Read/Write           Read/Write
       3  HSE Shared RAM     0x22C00000  0x22C03FFF          16  Normal            None                  None                  Yes          Yes           Read/Write           Read/Write
       4  Standby RAM        0x24000000  0x24007FFF          32  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       5  RAM(1st 1MB)       0x34000000  0x340FFFFF        1024  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       6  RAM(second 512K)   0x34100000  0x3417FFFF         512  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       7  Non-Cacheable RAM  0x34180000  0x341FFFFF         512  Normal            None                  None                  Yes          Yes           Read/Write           Read/Write
       8  Peripherals        0x40000000  0x5FFFFFFF      524288  Device            None                  None                  Yes          No            Read/Write           Read/Write
       9  LLCE               0x43800000  0x4383FFFF         256  Device            None                  None                  Yes          No            Read/Write           Read/Write
       10 PPB                0xE0000000  0xE00FFFFF        1024  Strongly Ordered  None                  None                  Yes          No            Read/Write           Read/Write
*/

static const uint32 rbar[CPU_MPU_MEMORY_COUNT] = {0x00000000UL, 0x00000000UL, 0x20000000UL, 0x22C00000UL, 0x24000000UL, 0x34000000UL, 0x34100000UL, 0x34180000UL, 0x40000000UL, 0x43800000UL, 0xE0000000UL};
static const uint32 rasr[CPU_MPU_MEMORY_COUNT] = {0x1004003FUL, 0x030B0039UL, 0x0104001FUL, 0x130C001BUL, 0x030B001DUL, 0x030B0027UL, 0x030B0025UL, 0x130C0025UL, 0x13050039UL, 0x13050023UL, 0x13040027UL};
#elif defined(CORE1)
/* Multiple core approach */
/* Number of entries in the memory tables */
#define CPU_MPU_MEMORY_COUNT (11U)

/*
  Region  Description        Start       End           Size[KB]  Type              Inner Cache Policy    Outer Cache Policy    Shareable    Executable    Privileged Access    Unprivileged Access
--------  -----------------  ----------  ----------  ----------  ----------------  --------------------  --------------------  -----------  ------------  -------------------  ---------------------
       0  Whole memory map   0x0         0xFFFFFFFF     4194304  Strongly Ordered  None                  None                  Yes          No            No Access            No Access
       1  QSPI AHB           0x0         0x1FFFFFFF      524288  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       2  DTCM               0x20000000  0x201FFFFF        2048  Strongly Ordered  None                  None                  Yes          Yes           Read/Write           Read/Write
       3  HSE Shared RAM     0x22C00000  0x22C03FFF          16  Normal            None                  None                  Yes          Yes           Read/Write           Read/Write
       4  Standby RAM        0x24000000  0x24007FFF          32  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       5  RAM(1st 1MB)       0x34200000  0x342FFFFF        1024  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       6  RAM(second 512K)   0x34300000  0x3437FFFF         512  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       7  Non-Cacheable RAM  0x34380000  0x343FFFFF         512  Normal            None                  None                  Yes          Yes           Read/Write           Read/Write
       8  Peripherals        0x40000000  0x5FFFFFFF      524288  Device            None                  None                  Yes          No            Read/Write           Read/Write
       9  LLCE               0x43800000  0x4383FFFF         256  Device            None                  None                  Yes          No            Read/Write           Read/Write
       10 PPB                0xE0000000  0xE00FFFFF        1024  Strongly Ordered  None                  None                  Yes          No            Read/Write           Read/Write
*/

static const uint32 rbar[CPU_MPU_MEMORY_COUNT] = {0x00000000UL, 0x00000000UL, 0x20000000UL, 0x22C00000UL, 0x24000000UL, 0x34200000UL, 0x34300000UL, 0x34380000UL, 0x40000000UL, 0x43800000UL, 0xE0000000UL};
static const uint32 rasr[CPU_MPU_MEMORY_COUNT] = {0x1004003FUL, 0x030B0039UL, 0x0104001FUL, 0x130C001BUL, 0x030B001DUL, 0x030B0027UL, 0x030B0025UL, 0x130C0025UL, 0x13050039UL, 0x13050023UL, 0x13040027UL};
#elif defined(CORE2)
/* Multiple core approach */
/* Number of entries in the memory tables */
#define CPU_MPU_MEMORY_COUNT (11U)

/*
  Region  Description        Start       End           Size[KB]  Type              Inner Cache Policy    Outer Cache Policy    Shareable    Executable    Privileged Access    Unprivileged Access
--------  -----------------  ----------  ----------  ----------  ----------------  --------------------  --------------------  -----------  ------------  -------------------  ---------------------
       0  Whole memory map   0x0         0xFFFFFFFF     4194304  Strongly Ordered  None                  None                  Yes          No            No Access            No Access
       1  QSPI AHB           0x0         0x1FFFFFFF      524288  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       2  DTCM               0x20000000  0x201FFFFF        2048  Strongly Ordered  None                  None                  Yes          Yes           Read/Write           Read/Write
       3  HSE Shared RAM     0x22C00000  0x22C03FFF          16  Normal            None                  None                  Yes          Yes           Read/Write           Read/Write
       4  Standby RAM        0x24000000  0x24007FFF          32  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       5  RAM(1st 1MB)       0x34400000  0x344FFFFF        1024  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       6  RAM(second 512K)   0x34500000  0x3457FFFF         512  Normal            Write-Back/Allocate   Write-Back/Allocate   No           Yes           Read/Write           Read/Write
       7  Non-Cacheable RAM  0x34580000  0x345FFFFF         512  Normal            None                  None                  Yes          Yes           Read/Write           Read/Write
       8  Peripherals        0x40000000  0x5FFFFFFF      524288  Device            None                  None                  Yes          No            Read/Write           Read/Write
       9  LLCE               0x43800000  0x4383FFFF         256  Device            None                  None                  Yes          No            Read/Write           Read/Write
       10 PPB                0xE0000000  0xE00FFFFF        1024  Strongly Ordered  None                  None                  Yes          No            Read/Write           Read/Write
*/

static const uint32 rbar[CPU_MPU_MEMORY_COUNT] = {0x00000000UL, 0x00000000UL, 0x20000000UL, 0x22C00000UL, 0x24000000UL, 0x34400000UL, 0x34500000UL, 0x34580000UL, 0x40000000UL, 0x43800000UL, 0xE0000000UL};
static const uint32 rasr[CPU_MPU_MEMORY_COUNT] = {0x1004003FUL, 0x030B0039UL, 0x0104001FUL, 0x130C001BUL, 0x030B001DUL, 0x030B0027UL, 0x030B0025UL, 0x130C0025UL, 0x13050039UL, 0x13050023UL, 0x13040027UL};
#endif
#endif /* MULTIPLE_IMAGE */

#ifdef __cplusplus
}
#endif

#endif /* CORE_SPECIFIC_H */
