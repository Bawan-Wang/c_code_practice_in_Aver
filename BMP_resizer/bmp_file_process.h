/*
 * Copyright (c) 2012, AVerMedia Information, Inc.
 * All rights reserved.
 *
 * @file bmp_file_process.h
 * @brief bitmap file process API
 *
 * This code provides a set of bitmap image file interface, which consists of bitmap reade, bitmap write,  create and release.
 *
 * @author Bawan <V0001534>
 * @date 2012/7/19
 * @note 
 *
 */


#ifndef __BMP_RESIZER__ 
#define __BMP_RESIZER__

#include "main.h"

BITMAP_FILE* read_bmp_file(char* intput_file);
const int write_bmp_file(BITMAP_FILE* image_data,char* output_file_name);
BITMAP_FILE* create_bmp_file(int width,int height,unsigned char channel);
void release_bmp_file(BITMAP_FILE* image_data);

#endif ///__BMP_RESIZER__

