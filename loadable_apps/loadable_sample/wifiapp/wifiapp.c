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

/****************************************************************************
 * Included Files
 ****************************************************************************/
#include <tinyara/config.h>
#include <sys/ioctl.h>
#include <sys/prctl.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>

#include <tinyara/timer.h>
#include <tinyara/clock.h>

#define TIMER_DEVNAME  "/dev/timer%d"

#ifdef CONFIG_BINARY_MANAGER
#include <binary_manager/binary_manager.h>
#endif

#include "wifiapp_internal.h"
/****************************************************************************
 * Public Functions
 ****************************************************************************/
static void display_test_scenario(void)
{
	printf("\nSelect Test Scenario.\n");
#ifdef CONFIG_EXAMPLES_MESSAGING_TEST
	printf("\t-Press M or m : Messaging F/W Test\n");	
#endif
#ifdef CONFIG_EXAMPLES_RECOVERY_TEST
	printf("\t-Press R or r : Recovery Test\n");
#endif
#ifdef CONFIG_EXAMPLES_BINARY_UPDATE_TEST
	printf("\t-Press U or u : Binary Update Test\n");
#endif
	printf("\t-Press X or x : Terminate Tests.\n");
}

extern int preapp_start(int argc, char **argv);

int g_count = 0;
bool g_start =  false;
bool g_end = false;
int cnt = 0;
int frt_fd;
struct timer_status_s g_before;
struct timer_status_s g_after;

static void switch_test(int argc, char *argv[])
{
	usleep(1);
	if (g_start == false) {
		g_start = true;
		if (ioctl(frt_fd, TCIOC_GETSTATUS, (unsigned long)(uintptr_t)&g_before) < 0) {
			fprintf(stderr, "ERROR: Failed to get Free Run Timer status: %d\n", errno);
		}
	}
	while(++g_count < 100000) {
		sched_yield();
	}
	if(g_end == false){
		g_end = true;
		if (ioctl(frt_fd, TCIOC_GETSTATUS, (unsigned long)(uintptr_t)&g_after) < 0) {
			fprintf(stderr, "ERROR: Failed to get Free Run Timer status: %d\n", errno);
		}
	}
}

#ifdef CONFIG_APP_BINARY_SEPARATION
int main(int argc, char **argv)
#else
int wifiapp_main(int argc, char **argv)
#endif
{
	char ch;
	bool is_testing = true;
	char path[_POSIX_PATH_MAX];

#if defined(CONFIG_SYSTEM_PREAPP_INIT) && defined(CONFIG_APP_BINARY_SEPARATION)
	preapp_start(argc, argv);
#endif

	// prctl(TC_GPIO_PIN20_CONFIG);
	// snprintf(path, _POSIX_PATH_MAX, TIMER_DEVNAME, 1);

	// frt_fd = open(path, O_RDONLY);
	// if (frt_fd < 0) {
	// 	fprintf(stderr, "ERROR: Failed to open Free Run Timer: %d\n", errno);
	// }
	// if (ioctl(frt_fd, TCIOC_SETFREERUN, TRUE) < 0) {
	// 	fprintf(stderr, "ERROR: Failed to set Free Run Timer: %d\n", errno);
	// }
	// if (ioctl(frt_fd, TCIOC_START, TRUE) < 0) {
	// 	fprintf(stderr, "ERROR: Failed to start Free Run Timer: %d\n", errno);
	// }

	// for (int i = 0; i < 2; i++) {
	// 	task_create("mqwait", 251, 1024, switch_test, (FAR char *const *)NULL);
	// }
	while (1) {
		sleep(3);
	}
	// printf("%lu\n", g_after.timeleft - g_before.timeleft);
	return 0;
}
