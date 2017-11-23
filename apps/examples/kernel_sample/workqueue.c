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
 * Included Files
 ****************************************************************************/

#include <tinyara/config.h>
#include <tinyara/clock.h>
#include <tinyara/wqueue.h>
#include <sys/types.h>
#include <stdio.h>

#if defined(CONFIG_SCHED_WORKQUEUE) || defined(CONFIG_LIB_USRWORK)

/****************************************************************************
 * Definitions
 ****************************************************************************/

/****************************************************************************
 * Private Data
 ****************************************************************************/

uint64_t wq_order[4];

/****************************************************************************
 * Private Functions
 ****************************************************************************/
static void wq_test1(FAR void *arg)
{
	systime_t cur_time = 0;
	cur_time = clock_systimer();

	wq_order[1] = (uint64_t)cur_time;

	printf("workqueue_test: test1 is excuted at (%lld) ticks\n", (uint64_t)cur_time);
}

static void wq_test2(FAR void *arg)
{
	systime_t cur_time = 0;
	cur_time = clock_systimer();

	wq_order[0] = (uint64_t)cur_time;

	printf("workqueue_test: test2 is excuted at (%lld) ticks\n", (uint64_t)cur_time);
}

static void wq_test3(FAR void *arg)
{
	systime_t cur_time = 0;
	cur_time = clock_systimer();
	
	wq_order[2] = (uint64_t)cur_time;

	printf("workqueue_test: test3 is excuted at (%lld) ticks\n", (uint64_t)cur_time);
}

static void wq_test4(FAR void *arg)
{
	systime_t cur_time = 0;
	cur_time = clock_systimer();
	
	wq_order[3] = (uint64_t)cur_time;

	printf("workqueue_test: test4 is excuted at (%lld) ticks\n", (uint64_t)cur_time);
}

/****************************************************************************
 * Public Functions
 ****************************************************************************/

/****************************************************************************
 * workqueue_test
 ****************************************************************************/

int workqueue_test(void)
{
	int order;
	systime_t cur_time;
	struct work_s *test_wq1;
	struct work_s *test_wq2;
	struct work_s *test_wq3;
	struct work_s *test_wq4;

	test_wq1 = (struct work_s *)malloc(sizeof(struct work_s));
	test_wq2 = (struct work_s *)malloc(sizeof(struct work_s));
	test_wq3 = (struct work_s *)malloc(sizeof(struct work_s));
	test_wq4 = (struct work_s *)malloc(sizeof(struct work_s));

	cur_time = clock_systimer();

	printf("workqueue_test: current time is (%lld)\n", (uint64_t)cur_time);
	printf("workqueue_test: test1 is queued and will excute it after 50 ticks\n");
	work_queue(HPWORK, test_wq1, wq_test1, NULL, 50);

	printf("workqueue_test: test2 is queued and will excute it after 30 ticks\n");
	work_queue(HPWORK, test_wq2, wq_test2, NULL, 30);

	printf("workqueue_test: test3 is queued and will excute it after 70 ticks\n");
	work_queue(HPWORK, test_wq3, wq_test3, NULL, 70);

	printf("workqueue_test: test4 is queued and will excute it after 90 ticks\n");
	work_queue(HPWORK, test_wq4, wq_test4, NULL, 90);
	
	sleep(1);

	free(test_wq1);
	free(test_wq2);
	free(test_wq3);
	free(test_wq4);

	for (order = 0; order < 3; order++) {
		if (wq_order[order] > wq_order[order + 1]) {
			printf("workqueue_test: fail\n");
			return ERROR;
		}
	}	
	printf("workqueue_test: success\n");
	return 0;
}

#endif
