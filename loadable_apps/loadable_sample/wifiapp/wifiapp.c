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
#include <sys/prctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>
#include <errno.h>
#ifdef CONFIG_BINARY_MANAGER
#include <binary_manager/binary_manager.h>
#endif

#include "wifiapp_internal.h"
/****************************************************************************
 * Public Functions
 ****************************************************************************/
static void *mq_wait_thread(void *index)
{
	int nbytes;
	mqd_t mqfd;
	char mq_name[32];
	char data[32];

	struct mq_attr attr;
	attr.mq_maxmsg = 32;
	attr.mq_msgsize = 16;
	attr.mq_flags = 0;

	memset(mq_name, 0, 32);

	sprintf(mq_name, "mymqueue%d", getpid());
	
	mqfd = mq_open(mq_name, O_RDWR | O_CREAT, 0666, &attr);
	if (mqfd < 0) {
		printf("Failed to open message queue\n");
		return 0;
	}

	nbytes = mq_receive(mqfd, (char *)data, 32, NULL);
	if (nbytes <= 0) {
		printf("Receive ERROR %d, errno %d, retry!\n", nbytes, errno);
	}
}

static int mq_wait_task(int argc, char *argv[])
{
	int nbytes;
	mqd_t mqfd;
	char mq_name[32];
	char data[32];

	struct mq_attr attr;
	attr.mq_maxmsg = 32;
	attr.mq_msgsize = 16;
	attr.mq_flags = 0;

	memset(mq_name, 0, 32);

	sprintf(mq_name, "mymqueue%d", getpid());
	
	mqfd = mq_open(mq_name, O_RDWR | O_CREAT, 0666, &attr);
	if (mqfd < 0) {
		printf("Failed to open message queue\n");
		return 0;
	}

	nbytes = mq_receive(mqfd, (char *)data, 32, NULL);
	if (nbytes <= 0) {
		printf("Receive ERROR %d, errno %d, retry!\n", nbytes, errno);
	}
}

int count = 0;
bool start =  false;
bool end = false;
int cnt = 0;
static int switch_test(int argc, char *argv[])
{
	usleep(1);
	int id = ++cnt;
	if (start == false) {
		start = true;
		prctl(TC_GPIO_PIN20_FALSE, NULL);
	}
	while(count < 100000) {
		count++;
		printf("hello - %d\n", id);
		sched_yield();
	}
	if(end == false){
		end = true;
		prctl(TC_GPIO_PIN20_FALSE, NULL);
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

#if defined(CONFIG_SYSTEM_PREAPP_INIT) && defined(CONFIG_APP_BINARY_SEPARATION)
	preapp_start(argc, argv);
#endif
	prctl(TC_GPIO_PIN20_CONFIG, NULL);
	int pid;
	int i;
	// pthread_t thd;
	// pthread_attr_t attr;

	// pthread_attr_init(&attr);
	// attr.priority = 210;

	end = start = false;
	for (i = 0; i < 2; i++) {
		pid = task_create("mqwait", 239, 1024, switch_test, (FAR char *const *)NULL);
		//pthread_create(&thd, &attr, (pthread_startroutine_t)mq_wait_thread, (pthread_addr_t)NULL);
	}
	// sleep(2);
	// volatile uint32_t *addr;
	// *addr = 0xdeadbeef;
	// pthread_create(&thd, &attr, (pthread_startroutine_t)mq_wait_thread, (pthread_addr_t)NULL);
	// printf("This is WIFI App\n");
	// recovery_test();
	sleep(5);
	printf("[%d] WIFI ALIVE\n", getpid());
	return 0;
}
