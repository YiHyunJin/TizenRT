/****************************************************************************
 *
 * Copyright 2019 Samsung Electronics All Rights Reserved.
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

#ifndef __BINARY_MANAGER_INTERNAL_H
#define __BINARY_MANAGER_INTERNAL_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <stdio.h>
#include <debug.h>
#include <unistd.h>
#include <tinyara/binary_manager.h>

#define SEND_REQUEST(type)								\
	do {										\
		request_msg.cmd = (type);						\
		request_msg.requester_pid = getpid();					\
		snprintf(request_msg.data.bin_name, BIN_NAME_MAX, "%s", binary_name);	\
		ret = binary_manager_send_request(&request_msg);			\
		if (ret < 0) {								\
			bmdbg("Failed to send request msg %d\n", ret);			\
			return BINMGR_COMMUNICATION_FAIL;				\
		}									\
	} while (0)

/****************************************************************************
 * Public Function Prototypes
 ****************************************************************************/
int binary_manager_send_request(binmgr_request_t *request_msg);
int binary_manager_receive_response(void *response_msg, int msg_size);

#endif							/* __BINARY_MANAGER_INTERNAL_H */
