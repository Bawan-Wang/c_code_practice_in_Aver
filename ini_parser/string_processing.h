/*
* @file string_processing.h
* @brief string processing
*
* This code provides some functions for string processing
*
* @author Bawan <V0001534>
* @date 2012/7/19
* @note 
*
*/

#ifndef __STRING_PROCESSING__
#define __STRING_PROCESSING__

#include "main.h"
#include "string_linked.h"

int str_find_det_char( char* p_chFindStr, char chCmpChar );
int	str_filter_reddt( char* p_chStrLine, QUEUE_NODE* pst_RearQueNode, int iRecState );
void str_send_to_file( QUEUE_NODE* pst_RearNode, QUEUE_NODE* pst_FrontNode, FILE* p_FileWrite );
void str_write_det_file( QUEUE_NODE* psta_RearNode, QUEUE_NODE* psta_FrontNode, int iNumOfQue, FILE* p_FileWrite);

#endif ///__STRING_PROCESSING__

