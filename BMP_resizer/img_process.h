/*
 * Copyright (c) 2012, AVerMedia Information, Inc.
 * All rights reserved.
 *
 * @file img_process.h
 * @brief image proces API
 *
 * This code provides an image resize API, 
 *
 * @author Bawan <V0001534>
 * @date 2012/7/19
 * @note 
 *
 */

#ifndef __IMG_PROCESS__ 
#define __IMG_PROCESS__ 

#include "main.h"

BITMAP_FILE* resize_process(BITMAP_FILE* origianl_image,const int resize_width,const int resize_height);

#endif ///__IMG_PROCESS__ 

