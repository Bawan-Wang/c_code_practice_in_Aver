/*
 * Copyright (c) 2012, AVerMedia Information, Inc.
 * All rights reserved.
 *
 * @file main.c
 * @brief main process
 *
 * This code provides a primary architecture of bitmap image resizer, 
 *
 * @author Bawan <V0001534>
 * @date 2012/7/19
 * @note 
 *
 */

#include "main.h"
#include "bmp_file_process.h"
#include "img_process.h"

int 
main(int argc,char** argv){
    //char input_file[] = "./XGA.bmp";
    //char output_file[] = "./XGA_o.bmp";
 
    BITMAP_FILE* input_image_data = 0;
	
	BITMAP_FILE* resize_image_data = 0;

    if(0 == (input_image_data = read_bmp_file(argv[1]))){ 
        printf("File open failure.\n");
        return 0;
    }

    if(0 == (resize_image_data = resize_process(input_image_data,640,480))){
        printf("Resize failure.\n");
        return 0;       
	}

    if(0 == write_bmp_file(resize_image_data,argv[2])){
        printf("Write file failure.\n");
        return 0;       
	}	

    release_bmp_file(input_image_data);
    release_bmp_file(resize_image_data);
    return 0;
}

