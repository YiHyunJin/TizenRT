/****************************************************************************
 *
 * Copyright 2016 Samsung Electronics All Rights Reserved.
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
/****************************************************************************
 * kernel/mqueue/mq_waitirq.c
 *
 *   Copyright (C) 2007-2009, 2011, 2014 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
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
 ****************************************************************************/

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <tinyara/config.h>

#include <sched.h>
#include <errno.h>

#include <tinyara/arch.h>
#include <tinyara/mqueue.h>

#include "mqueue/mqueue.h"

#include "../../arch/arm/src/imxrt/imxrt_gpio.h"
#include "../../arch/arm/include/imxrt/imxrt102x_irq.h"
#include "../../arch/arm/src/imxrt/chip/imxrt102x_pinmux.h"


#define IOMUX_GOUT      (IOMUX_PULL_NONE | IOMUX_CMOS_OUTPUT | \
                         IOMUX_DRIVE_40OHM | IOMUX_SPEED_MEDIUM | \
                         IOMUX_SLEW_SLOW)

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Type Declarations
 ****************************************************************************/

/****************************************************************************
 * Public Variables
 ****************************************************************************/

/****************************************************************************
 * Private Variables
 ****************************************************************************/

/****************************************************************************
 * Private Functions
 ****************************************************************************/

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * Name: mq_waitirq
 *
 * Description:
 *   This function is called when a signal or a timeout is received by a
 *   task that is waiting on a message queue -- either for a queue to
 *   becoming not full (on mq_send) or not empty (on mq_receive).
 *
 * Parameters:
 *   wtcb - A pointer to the TCB of the task that is waiting on a message
 *          queue, but has received a signal instead.
 *
 * Return Value:
 *   None
 *
 * Assumptions:
 *
 ****************************************************************************/

void mq_waitirq(FAR struct tcb_s *wtcb, int errcode)
{
	FAR struct mqueue_inode_s *msgq;
	irqstate_t saved_state;

	/* Disable interrupts.  This is necessary because an interrupt handler may
	 * attempt to send a message while we are doing this.
	 */
	gpio_pinset_t w_set;
	w_set = GPIO_PIN28 | GPIO_PORT1 | GPIO_OUTPUT | IOMUX_GOUT;
	saved_state = irqsave();

	/* It is possible that an interrupt/context switch beat us to the punch and
	 * already changed the task's state.  NOTE:  The operations within the if
	 * are safe because interrupts are always disabled with the msgwaitq,
	 * nwaitnotempty, and nwaitnotfull fields are modified.
	 */

	if (wtcb->task_state == TSTATE_WAIT_MQNOTEMPTY || wtcb->task_state == TSTATE_WAIT_MQNOTFULL) {
		/* Get the message queue associated with the waiter from the TCB */

		msgq = wtcb->msgwaitq;
		DEBUGASSERT(msgq);

		wtcb->msgwaitq = NULL;

		/* Decrement the count of waiters and cancel the wait */

		if (wtcb->task_state == TSTATE_WAIT_MQNOTEMPTY) {
			DEBUGASSERT(msgq->nwaitnotempty > 0);
			msgq->nwaitnotempty--;
		} else {
			DEBUGASSERT(msgq->nwaitnotfull > 0);
			msgq->nwaitnotfull--;
		}

		/* Mark the errno value for the thread. */

		wtcb->pterrno = errcode;

		/* Restart the task. */
		imxrt_gpio_write(w_set, true);
		imxrt_gpio_write(w_set, false);
		up_unblock_task(wtcb);
	}

	/* Interrupts may now be enabled. */

	irqrestore(saved_state);
}
