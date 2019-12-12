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
#ifndef __INCLUDE_SLSIDRV_H__
#define __INCLUDE_SLSIDRV_H__

#include <tinyara/config.h>
#include <tinyara/lwnl/lwnl.h>

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <debug.h>



/****************************************************************************
 * Public Types
 ****************************************************************************/
struct slsi_drv_dev_s {
	bool initialized;
	struct lwnl_lowerhalf_s dev;
};

/****************************************************************************
 * Public Functions
 ****************************************************************************/


#endif /*  __INCLUDE_SLSIDRV_H__ */
