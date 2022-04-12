/*
 * Copyright (c) 2012, AVerMedia Information, Inc.
 * All rights reserved.
 *
 * @file main.h
 * @brief main process
 *
 * This code provides a primary architecture of bitmap image resizer, 
 *
 * @author Bawan <V0001534>
 * @date 2012/7/19
 * @note 
 *
 */

#ifndef __MAIN__ 
#define __MAIN__

#include <stdio.h>
#include <stdlib.h>

///
///This is a file header structure that will record bitmap file header of bitmap file fotmat
///
typedef struct file_header{ 
    unsigned short int     type;                    /// System type
    unsigned int           size;                    /// File size in bytes  
    unsigned short int     reserved1, reserved2;    ///Reserved byte 
    unsigned int           offset;                  /// Offset 
} FILE_HEADER;

///
///This is a info header structure that will record bitmap information header of bitmap file fotmat
///
typedef struct info_header{ 
    unsigned int           size;                    /// Info Header size in bytes,  
    int                    width,height;            /// Width and height of image  
    unsigned short int     planes;                  /// Number of colour planes 
    unsigned short int     bits;                    /// Bits per pixel 
    unsigned int           compression;             /// Compression type 
    unsigned int           imagesize;               /// Image size in bytes 
    int                    xresolution,yresolution; /// Pixels per meter 
    unsigned int           ncolours;                /// Number of colours  
    unsigned int           importantcolours;        /// Important colours  
} INFO_HEADER;

///
///This is a bitmap file structure that will record both the bitmap parameters and raw data
///
typedef struct bitmap_file{
    FILE_HEADER*           pfile_header;            /// File Header
    INFO_HEADER*           pinfo_header;            /// Info Header
    unsigned char*         raw_data;                /// Raw data of the bitmap image
	unsigned char          channel;                 /// Channel of the bitmap image
	unsigned int           widthstep;               /// Row size of raw data of the bitmap image
} BITMAP_FILE;

#endif ///__MAIN__

