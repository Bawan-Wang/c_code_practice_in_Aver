/*
 * Copyright (c) 2012, AVer Information, Inc.
 * All rights reserved.
 *
 * @file string_linked.c
 * @brief linked list model
 *
 * This code provides a model for linked list, which is utilized to save each paramater.
 *
 * @author Bawan <V0001534>
 * @date 2012/7/25
 * @note 
 *
 */
 
#include "string_linked.h"

int linkNode_add_rearNode( QUEUE_NODE* pst_RearNode, const char* p_chInputString ){

    int iTmpStrIdx;
	QUEUE_NODE* pst_NewNode;
	
	if(NULL == (pst_NewNode = (QUEUE_NODE*)malloc( sizeof(QUEUE_NODE) )))
		return FALSE;
		//return -1;

	if(NULL == (pst_NewNode->string_line = (char*)malloc( strlen( p_chInputString ) + 1 )))
		return FALSE;
		//return -1;
	
    pst_NewNode->rear = pst_RearNode;
	pst_NewNode->front = pst_RearNode->front;
	pst_RearNode->front->rear = pst_NewNode;
	pst_RearNode->front= pst_NewNode;

    for(iTmpStrIdx = 0; '\0' != (pst_NewNode->string_line[iTmpStrIdx] = *p_chInputString ); iTmpStrIdx++,p_chInputString++);	

	return TRUE;
	//return 1;
}

int linkNode_rm_frtNode( QUEUE_NODE** pst_ListNode ){

	QUEUE_NODE* pst_DelNode;

	if(*pst_ListNode == NULL)
		return FALSE;
		//return -1;
	
	pst_DelNode = *pst_ListNode;
	*pst_ListNode = pst_DelNode->rear;
	(*pst_ListNode)->front = NULL;
	free( pst_DelNode->string_line );
	free( pst_DelNode );

	return TRUE;
	//return 1;
}


