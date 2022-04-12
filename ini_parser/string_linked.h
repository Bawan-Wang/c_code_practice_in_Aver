/*
* @file string_linked.h
* @brief linked list model
*
* This code provides a model for linked list, which is utilized to save each paramater.
*
* @author Bawan <V0001534>
* @date 2012/7/25
* @note 
*
*/

#ifndef __STRING_LINKED__
#define __STRING_LINKED__

#include "main.h"

typedef struct queue_node{
	char				*string_line;
	struct queue_node	*front;
	struct queue_node	*rear;
}QUEUE_NODE;

int linkNode_add_rearNode( QUEUE_NODE* pst_RearNode, const char* p_chInputString );
int linkNode_rm_frtNode( QUEUE_NODE** pst_ListNode );

#endif ///__STRING_LINKED__

