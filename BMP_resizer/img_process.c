/*
 * Copyright (c) 2012, AVerMedia Information, Inc.
 * All rights reserved.
 *
 * @file img_process.c
 * @brief image proces API
 *
 * This code provides an image resize API, 
 *
 * @author Bawan <V0001534>
 * @date 2012/7/19
 * @note 
 *
 */
#include "img_process.h"
#include "bmp_file_process.h"


/**
 * @brief
 * Resize image. 
 *
 * This function performs image resize.  The argument 
 * passed is used to determine the size of output image.
 *
 * @param[in] origianl_image
 *     This is an argument passed to the process before image resize.
 *
 * @param[in] resize_width
 *     This is an argument passed to the width of resized image.
 * 
 * @param[in] resize_height
 *     This is an argument passed to the height of resized image.
 * 
 * @return Result of the operation
 *     @li 0 if create bitmap file failure
 *     @li BITMAP_FILE* file pointer if resize is sucess
 *
 */
BITMAP_FILE* 
resize_process(BITMAP_FILE* origianl_image,const int resize_width,const int resize_height){


	BITMAP_FILE*    resize_image = 0;
    unsigned int    width_array_index[resize_width],height_array_index[resize_height];
    int             resize_w_idx_count,resize_h_idx_count,ori_w_idx_count,ori_h_idx_count;
    unsigned int    re_img_a_idx,ori_img_a_idx;

	if( 0 == (resize_image = create_bmp_file(resize_width,resize_height,origianl_image->channel) ) )
		return 0;

    resize_image->pfile_header->type = origianl_image->pfile_header->type;
    resize_image->pfile_header->reserved1 = origianl_image->pfile_header->reserved1;
    resize_image->pfile_header->reserved2 = origianl_image->pfile_header->reserved2;
    resize_image->pfile_header->offset = origianl_image->pfile_header->offset;
 
    resize_image->pinfo_header->size = origianl_image->pinfo_header->size;
    resize_image->pinfo_header->planes = origianl_image->pinfo_header->planes;
    resize_image->pinfo_header->bits = origianl_image->pinfo_header->bits;
    resize_image->pinfo_header->compression = origianl_image->pinfo_header->compression;
    resize_image->pinfo_header->xresolution = origianl_image->pinfo_header->xresolution;
    resize_image->pinfo_header->yresolution = origianl_image->pinfo_header->yresolution;
    resize_image->pinfo_header->ncolours = origianl_image->pinfo_header->ncolours;
    resize_image->pinfo_header->importantcolours = origianl_image->pinfo_header->importantcolours;


    if(origianl_image->pinfo_header->width >= resize_width){
		
        int      resize_w_a_idx;
		float    idx_count;
		float    gap = (float) origianl_image->pinfo_header->width / (float) resize_width;

		for(resize_w_a_idx = 0,idx_count = 0 ; resize_w_a_idx < resize_width ; resize_w_a_idx++,idx_count += gap)
			width_array_index[resize_w_a_idx] = (int)(idx_count + 0.5) * origianl_image->channel;		

		if( width_array_index[resize_w_a_idx] > origianl_image->pinfo_header->width * origianl_image->channel)
			width_array_index[resize_w_a_idx] = origianl_image->pinfo_header->width * origianl_image->channel;


	}

    if(origianl_image->pinfo_header->height >= resize_height){
		
        int      resize_h_a_idx;
		float    idx_count;
		float    gap = (float) origianl_image->pinfo_header->height / (float) resize_height;

		for(resize_h_a_idx = 0,idx_count = 0 ; resize_h_a_idx < resize_height ; resize_h_a_idx++,idx_count += gap)
			height_array_index[resize_h_a_idx] = (int)(idx_count + 0.5);	
	
		if((int)(idx_count + 0.5) > origianl_image->pinfo_header->height)
			height_array_index[resize_h_a_idx] = origianl_image->pinfo_header->height;

	}		

	if( resize_image->channel > 1){


		for(resize_h_idx_count = 0 , ori_h_idx_count = 0 ; resize_h_idx_count < resize_height ; resize_h_idx_count++ , ori_h_idx_count++ ){
			for(resize_w_idx_count = 0 , ori_w_idx_count = 0 ; resize_w_idx_count < resize_image->widthstep ; resize_w_idx_count += resize_image->channel , ori_w_idx_count++ ){
			
				re_img_a_idx   =  resize_h_idx_count * resize_image->widthstep + resize_w_idx_count;
				ori_img_a_idx  =  height_array_index[ori_h_idx_count] * origianl_image->widthstep + width_array_index[ori_w_idx_count];
				
	            resize_image->raw_data[ re_img_a_idx ] = 
					origianl_image->raw_data[ ori_img_a_idx ];
				
		            resize_image->raw_data[ re_img_a_idx + 1 ] = 
						origianl_image->raw_data[ ori_img_a_idx + 1 ];	
					
		            resize_image->raw_data[ re_img_a_idx + 2 ] = 
						origianl_image->raw_data[ ori_img_a_idx + 2 ];	

			}
		}

	}	else{

		for(resize_h_idx_count = 0 , ori_h_idx_count = 0 ; resize_h_idx_count < resize_height ; resize_h_idx_count++ , ori_h_idx_count++ ){
			for(resize_w_idx_count = 0 , ori_w_idx_count = 0 ; resize_w_idx_count < resize_image->widthstep ; resize_w_idx_count += resize_image->channel , ori_w_idx_count++ ){
			
				re_img_a_idx   =  resize_h_idx_count * resize_image->widthstep + resize_w_idx_count;
				ori_img_a_idx  =  height_array_index[ori_h_idx_count] * origianl_image->widthstep + width_array_index[ori_w_idx_count];
				
	            resize_image->raw_data[ re_img_a_idx ] = 
					origianl_image->raw_data[ ori_img_a_idx ];
				
			}
		}

	}

    return resize_image;
}

