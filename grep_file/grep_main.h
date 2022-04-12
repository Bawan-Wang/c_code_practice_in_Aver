#ifndef __GREP_MAIN__ 
#define __GREP_MAIN__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/types.h>
#include <errno.h>
#include <limits.h>

typedef enum{
	ARUGMENT_NUM 		= 4,
	ARUGMENT_NUM_WRONG 	= -1,
	THREAD_NUM_WRONG 	= -2,
	CEATE_WRONG 		= -3,
	DIR_WRONG 			= -4,
	KEY_WRONG 			= -5,
	STR_FOUND 			= -6,
	STR_NOFOUND			= -7,
	SUCCESS 			= -10
}CHK_MESSAGE;


typedef struct main_thread_info{	
	char   *open_directory;
	char   *cSrhStr;
}MAIN_THREAD_INFO;

typedef struct sub_thread_info{	
	int   iThreadNum;
	int   iThreadID;
}SUB_THREAD_INFO;


#endif ///__GREP_MAIN__

