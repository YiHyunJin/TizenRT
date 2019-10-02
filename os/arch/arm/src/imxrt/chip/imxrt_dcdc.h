/****************************************************************************
 *
 * Copyright 2019 NXP Semiconductors All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/
/****************************************************************************************************
 * os/arch/arm/src/imxrt/chip/imxrt_dcdc.h
 *
 *   Copyright (C) 2018 Gregory Nutt. All rights reserved.
 *   Author:  Janne Rosberg <janne@offcode.fi>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************************************/

#ifndef __ARCH_ARM_SRC_IMXRT_CHIP_IMXRT_DCDC_H
#define __ARCH_ARM_SRC_IMXRT_CHIP_IMXRT_DCDC_H

/****************************************************************************************************
 * Included Files
 ****************************************************************************************************/

#include <tinyara/config.h>
#include "imxrt_memorymap.h"
#if defined(CONFIG_ARCH_CHIP_FAMILY_IMXRT102x)
#include "imxrt102x_config.h"
#elif defined(CONFIG_ARCH_CHIP_FAMILY_IMXRT105x)
#include "imxrt105x_config.h"
#else
#error Unrecognized i.MX RT architecture
#endif

/****************************************************************************************************
 * Pre-processor Definitions
 ****************************************************************************************************/

/* Register offsets *********************************************************************************/

#define IMXRT_DCDC_REG0_OFFSET              0x0000	/* DCDC Register 0 */
#define IMXRT_DCDC_REG1_OFFSET              0x0004	/* DCDC Register 1 */
#define IMXRT_DCDC_REG2_OFFSET              0x0008	/* DCDC Register 2 */
#define IMXRT_DCDC_REG3_OFFSET              0x000c	/* DCDC Register 3 */

/* Register addresses *******************************************************************************/

#define IMXRT_DCDC_REG0                     (IMXRT_DCDC_BASE + IMXRT_DCDC_REG0_OFFSET)
#define IMXRT_DCDC_REG1                     (IMXRT_DCDC_BASE + IMXRT_DCDC_REG1_OFFSET)
#define IMXRT_DCDC_REG2                     (IMXRT_DCDC_BASE + IMXRT_DCDC_REG2_OFFSET)
#define IMXRT_DCDC_REG3                     (IMXRT_DCDC_BASE + IMXRT_DCDC_REG3_OFFSET)

#endif							/* __ARCH_ARM_SRC_IMXRT_CHIP_IMXRT_DCDC_H */
