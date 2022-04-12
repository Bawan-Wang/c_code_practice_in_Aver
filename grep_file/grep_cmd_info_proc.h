#ifndef __GREP_CMD_INFO_PROC__ 
#define __GREP_CMD_INFO_PROC__

#include "grep_main.h"

typedef enum{
	ASCII_DOT			= 0x2E,
	ASCII_NUM_0			= 0x30,
	ASCII_NUM_9			= 0x39,
	ASCII_LETTER_C_A	= 0x41,
	ASCII_LETTER_C_Z	= 0x5A,
	ASCII_LETTER_L_A	= 0x61,
	ASCII_LETTER_L_Z	= 0x7A,
	ASCII_UNDER_LINE	= 0x5F
}ASCII_CODE;

const int check_thread_num(char* ca_ThdNum);
const int check_keyword ( char* ca_KeyWord );
const int create_main_info ( MAIN_THREAD_INFO **pst_RetInfo, char *p_cCmdOPDir ,char *p_cCmdSrh );
void release_main_info ( MAIN_THREAD_INFO **pst_RetInfo);
const int create_sub_info ( SUB_THREAD_INFO **sta_RetInfo, const int iThreadNum );
void release_SUB_info ( SUB_THREAD_INFO **sta_RetInf );

#endif ///__GREP_CMD_INFO_PROC__

