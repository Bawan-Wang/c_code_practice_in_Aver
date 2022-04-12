/*
 * Copyright (c) 2012, AVer Information, Inc.
 * All rights reserved.
 *
 * @file string_processing.c
 * @brief string processing
 *
 * This code provides some functions for string processing
 *
 * @author Bawan <V0001534>
 * @date 2012/7/24
 * @note 
 *
 */

#include "string_processing.h"

int str_find_det_char( char* p_chFindStr, char chCmpChar ){

	int iEqualIdx = 0;

	while(*p_chFindStr++ != chCmpChar)
		iEqualIdx++;
	
	return iEqualIdx;
		
}

int	str_filter_reddt( char* p_chStrLine, QUEUE_NODE* pst_RearQueNode, int iRecState ){

	int chEqualIdx, chSlashIdx;
	int iRddtPrintIdx;
	char* p_chStr_Line = p_chStrLine;

	while(*p_chStrLine++ != '\0');

	p_chStrLine -= 3;

	if('[' == *p_chStr_Line && ']' == *p_chStrLine){				
		if(0 == strncmp( "[module_end]", p_chStr_Line, NUM_END_LINE )){
			linkNode_add_rearNode( pst_RearQueNode, p_chStr_Line );
			return CLOSE_RECORD;	
		}else{
			if(FALSE == linkNode_add_rearNode(pst_RearQueNode,p_chStr_Line))
				return CLOSE_RECORD;
			return START_RECORD;
		}
	}

	if(START_RECORD == iRecState){
		
		if('[' != p_chStr_Line[0] && ']' != *p_chStrLine){
			
			int temp_link_str_idx = 0;
			char temp_char[MAX_NUM_ALINE];
			chEqualIdx = str_find_det_char( p_chStr_Line, '=' );
			chSlashIdx = str_find_det_char( p_chStr_Line, '/' );
	
			if(chEqualIdx < chSlashIdx){
				for(iRddtPrintIdx = chEqualIdx + 1; iRddtPrintIdx < chSlashIdx; iRddtPrintIdx++){
					
					if(';' == p_chStr_Line[iRddtPrintIdx]){
                       // temp_char[temp_link_str_idx] = ' ';
						continue;
					}else if('\0' == p_chStr_Line[iRddtPrintIdx] || '\n' == p_chStr_Line[iRddtPrintIdx]){
					    //temp_char[temp_link_str_idx] = '\0';
						break;
					}	
					temp_char[temp_link_str_idx] = p_chStr_Line[iRddtPrintIdx];
					temp_link_str_idx++;
					
				}
				temp_char[temp_link_str_idx++] = '\n';
				temp_char[temp_link_str_idx] = '\0';

			    //linkNode_add_rearNode(pst_RearQueNode,temp_char);
				if(FALSE == linkNode_add_rearNode(pst_RearQueNode,temp_char))
					return CLOSE_RECORD;				
			}
			
		}	

	}

    return START_RECORD;
}

void str_send_to_file( QUEUE_NODE* pst_RearNode, QUEUE_NODE* pst_FrontNode, FILE* p_FileWrite ){

	QUEUE_NODE* pst_ListNode = pst_FrontNode;
	//QUEUE_NODE* pst_DelNode;
	
	pst_ListNode = pst_ListNode->rear;
	while(pst_ListNode){

        if(pst_ListNode == pst_RearNode)
			break;

        fputs( pst_ListNode->string_line, p_FileWrite );
		if(FALSE == linkNode_rm_frtNode(&pst_ListNode))
			break;
		/*
		pst_DelNode = pst_ListNode;
		pst_ListNode = pst_DelNode->rear;
		pst_ListNode->front = NULL;
		free( pst_DelNode->string_line );
		free( pst_DelNode );
		*/
	}

}

void str_write_det_file( QUEUE_NODE* psta_RearNode, QUEUE_NODE* psta_FrontNode, int iNumOfQue, FILE* p_FileWrite){

    int iQueCount;

    for(iQueCount = iNumOfQue - 1; iQueCount >= 0; iQueCount--)
		str_send_to_file( psta_RearNode + iQueCount, psta_FrontNode + iQueCount, p_FileWrite );

}

