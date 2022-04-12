/*
 * Copyright (c) 2012, AVerMedia Information, Inc.
 * All rights reserved.
 *
 * @file bmp_file_process.c
 * @brief bitmap file process API
 *
 * This code provides a set of bitmap image file interface, which consists of several function, such as bitmap reade, bitmap write,  create and release.
 *
 * @author Bawan <V0001534>
 * @date 2012/7/19
 * @note 
 *
 */

#include "bmp_file_process.h"

/**
 * @brief
 * decode raw data of file header into a readable value. 
 *
 * This function performs the translation of raw data of parameters of file header.
 * 
 *
 * @param[in] header
 *     This is an argument passed in the raw data of header .
 *
 * @param[in] number_of_byte
 *     This is an argument passed in the number of byte of the parameter.
 * 
 * @param[in.out] header_index
 *     This is an argument passed to the record index about the current parameter.
 * 
 * @return Result of the operation
 *     @li integer number is the readable value about the parameter of current parameter.
 *
 */
const int 
header_byte_decode(unsigned char* header,const int number_of_byte,int* header_index){
    int    counted,result = 0;

    for(counted = 0 ; counted < number_of_byte ; counted++)           
       result |= ((unsigned int) *(header + *header_index + counted)) << (8*counted);

    *header_index += counted;
    return result;
}

/**
 * @brief
 * read a bitmap file. 
 *
 * This function performs to catch the data from the bitmap file.
 * 
 *
 * @param[in] intput_file_name
 *     This is an argument passed in the file name of reading bitmap image.
 * 
 * @return Result of the operation
 *     @li 0 if create bitmap file failure
 *     @li BITMAP_FILE* file pointer if bitmap file opened sucessfully
 *
 */
BITMAP_FILE*
read_bmp_file(char* intput_file_name){
    BITMAP_FILE*    image_data;   
    FILE*           input_file = 0;
    unsigned char*  pfile_header_temp = 0;
    unsigned char*  pinfo_header_temp = 0;
    int             header_index = 0;



    image_data = (BITMAP_FILE*) malloc (sizeof(BITMAP_FILE));
    image_data->pfile_header = (FILE_HEADER*) malloc (sizeof(FILE_HEADER));    
    image_data->pinfo_header = (INFO_HEADER*) malloc (sizeof(INFO_HEADER));

     

    input_file = fopen(intput_file_name,"rb");
    if(0 == (input_file = fopen(intput_file_name,"rb")))
        return 0;
    
    pfile_header_temp = (unsigned char*) malloc (14*sizeof(unsigned char)); 
    pinfo_header_temp = (unsigned char*) malloc (40*sizeof(unsigned char));
 
    fread(pfile_header_temp,1,14,input_file);    
    fread(pinfo_header_temp,1,40,input_file);
    
    image_data->pfile_header->type = header_byte_decode(pfile_header_temp,2,&header_index);
    image_data->pfile_header->size = header_byte_decode(pfile_header_temp,4,&header_index);
    image_data->pfile_header->reserved1 = header_byte_decode(pfile_header_temp,2,&header_index);
    image_data->pfile_header->reserved2 = header_byte_decode(pfile_header_temp,2,&header_index);
    image_data->pfile_header->offset = header_byte_decode(pfile_header_temp,4,&header_index);
    
    header_index = 0;

    image_data->pinfo_header->size = header_byte_decode(pinfo_header_temp,4,&header_index);    
    image_data->pinfo_header->width = header_byte_decode(pinfo_header_temp,4,&header_index);
    image_data->pinfo_header->height = header_byte_decode(pinfo_header_temp,4,&header_index);
    image_data->pinfo_header->planes = header_byte_decode(pinfo_header_temp,2,&header_index);
    image_data->pinfo_header->bits = header_byte_decode(pinfo_header_temp,2,&header_index);
    image_data->pinfo_header->compression = header_byte_decode(pinfo_header_temp,4,&header_index);
    image_data->pinfo_header->imagesize = header_byte_decode(pinfo_header_temp,4,&header_index);
    image_data->pinfo_header->xresolution = header_byte_decode(pinfo_header_temp,4,&header_index);
    image_data->pinfo_header->yresolution = header_byte_decode(pinfo_header_temp,4,&header_index);
    image_data->pinfo_header->ncolours = header_byte_decode(pinfo_header_temp,4,&header_index);
    image_data->pinfo_header->importantcolours = header_byte_decode(pinfo_header_temp,4,&header_index);
    
    image_data->raw_data = (unsigned char*) malloc (image_data->pinfo_header->imagesize*sizeof(unsigned char));

    fread(image_data->raw_data,1,image_data->pinfo_header->imagesize,input_file);     

	image_data->channel = image_data->pinfo_header->bits / 8;
	image_data->widthstep = image_data->pinfo_header->width*image_data->channel;
	       
    free (pfile_header_temp);
    free (pinfo_header_temp);
    fclose (input_file);    

    return image_data;
}

/**
 * @brief
 * encode a readable value of file header into raw data. 
 *
 * This function performs the retranslation of readable value of parameters of file header.
 * 
 *
 * @param[in] header_data
 *     This is an argument passed in the readable value of the parameterof of header .
 *
 * @param[in.out] header
 *     This is an argument passed in the raw data of header .
 *
 * @param[in] number_of_byte
 *     This is an argument passed to the number of byte of the parameter.
 * 
 * @param[in.out] header_index
 *     This is an argument passed to the record index about the current parameter.
 * 
 *
 */
void 
header_byte_encode(unsigned int header_data,unsigned char* header,const int number_of_byte,int* header_index){
    int          counted,result = 0;
    unsigned int mask_byte = 0xff;
    unsigned char catch_byte;
    for(counted = 0 ; counted < number_of_byte ; counted++){
       *(header + *header_index + counted) = (unsigned char)((header_data & (mask_byte << (8*counted))) >> (8*counted));
    }
    *header_index += counted;
}

/**
 * @brief
 * write a bitmap file. 
 *
 * This function performs to save the image data to a bitmap file.
 * 
 *
 * @param[in] image_data
 *     This is an argument passed in the structure of output file.
 * 
 * @param[in] output_file_name
 *     This is an argument passed in the file name of writing bitmap image.
 *
 * @return Result of the operation
 *     @li 0 if create bitmap file failure
 *     @li BITMAP_FILE* file pointer if bitmap file opened sucessfully
 *
 */
const int 
write_bmp_file(BITMAP_FILE* image_data,char* output_file_name){
    FILE*           output_file = 0;
    unsigned char*  pfile_header_temp = 0;
    unsigned char*  pinfo_header_temp = 0;
    int             header_index = 0;
 
    if(0 == (output_file = fopen(output_file_name,"wb")))
        return 0;
    
    pfile_header_temp = (unsigned char*) malloc (14*sizeof(unsigned char)); 
    pinfo_header_temp = (unsigned char*) malloc (40*sizeof(unsigned char));
    
    header_byte_encode(image_data->pfile_header->type,pfile_header_temp,2,&header_index); 
    header_byte_encode(image_data->pfile_header->size,pfile_header_temp,4,&header_index); 
    header_byte_encode(image_data->pfile_header->reserved1,pfile_header_temp,2,&header_index); 
    header_byte_encode(image_data->pfile_header->reserved2,pfile_header_temp,2,&header_index); 
    header_byte_encode(image_data->pfile_header->offset,pfile_header_temp,4,&header_index); 

    header_index = 0;
   
    header_byte_encode(image_data->pinfo_header->size,pinfo_header_temp,4,&header_index); 
    header_byte_encode(image_data->pinfo_header->width,pinfo_header_temp,4,&header_index); 
    header_byte_encode(image_data->pinfo_header->height,pinfo_header_temp,4,&header_index); 
    header_byte_encode(image_data->pinfo_header->planes,pinfo_header_temp,2,&header_index); 
    header_byte_encode(image_data->pinfo_header->bits,pinfo_header_temp,2,&header_index); 
    header_byte_encode(image_data->pinfo_header->compression,pinfo_header_temp,4,&header_index); 
    header_byte_encode(image_data->pinfo_header->imagesize,pinfo_header_temp,4,&header_index); 
    header_byte_encode(image_data->pinfo_header->xresolution,pinfo_header_temp,4,&header_index); 
    header_byte_encode(image_data->pinfo_header->yresolution,pinfo_header_temp,4,&header_index); 
    header_byte_encode(image_data->pinfo_header->ncolours,pinfo_header_temp,4,&header_index); 
    header_byte_encode(image_data->pinfo_header->importantcolours,pinfo_header_temp,4,&header_index); 

    fwrite (pfile_header_temp,1,14,output_file);
    fwrite (pinfo_header_temp,1,40,output_file);
    fwrite (image_data->raw_data,1,image_data->pinfo_header->imagesize,output_file);
     
    free (pfile_header_temp);
    free (pinfo_header_temp);
    fclose(output_file);
   
    return 1; 
}

/**
 * @brief
 * create a structure of bitmap file. 
 *
 * This function performs the creation of  structure of bitmap file.
 * 
 *
 * @param[in] width
 *     This is an argument passed to the width of creating bitmap structure.
 * 
 * @param[in] height
 *     This is an argument passed to the height of creating bitmap structure.
 *
 * @param[in] channel
 *     This is an argument passed to the channel of creating bitmap structure.
 *
 * @return Result of the operation
 *     @li BITMAP_FILE* file pointer that is the creating bitmap structure
 *
 */
BITMAP_FILE*
create_bmp_file(int width,int height,unsigned char channel){
	BITMAP_FILE*	image_data; 
	
    image_data = (BITMAP_FILE*) malloc (sizeof(BITMAP_FILE));
    image_data->pfile_header = (FILE_HEADER*) malloc (sizeof(FILE_HEADER));    
    image_data->pinfo_header = (INFO_HEADER*) malloc (sizeof(INFO_HEADER));

	image_data->channel = channel;
	image_data->widthstep = width*image_data->channel;	

	image_data->pinfo_header->width = width;
	image_data->pinfo_header->height = height;
	image_data->pinfo_header->imagesize	= width*height*image_data->channel;
    image_data->pfile_header->size = image_data->pinfo_header->imagesize + 54;

    image_data->raw_data = (unsigned char*) malloc (image_data->pinfo_header->imagesize*sizeof(unsigned char));
	//memset(image_data->raw_data,0,image_data->pinfo_header->imagesize*sizeof(unsigned char));

	return image_data;
}

/**
 * @brief
 * release a structure of bitmap file. 
 *
 * This function performs to free the memory of  structure of bitmap file.
 * 
 * @param[in] image_data
 *     This is an argument passed that is to release a structure of bitmap file. 
 *
 *
 */
void 
release_bmp_file(BITMAP_FILE* image_data){

    free (image_data->pfile_header);
    free (image_data->pinfo_header);
    free (image_data->raw_data);
    free (image_data);
    
}

