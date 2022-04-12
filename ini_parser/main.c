/*
 * Copyright (c) 2012, AVer Information, Inc.
 * All rights reserved.
 *
 * @file main.c
 * @brief main process
 *
 * This code provides a primary architecture of ini file parser
 *
 * @author Bawan <V0001534>
 * @date 2012/7/25
 * @note 
 *
 */

#include "main.h"
#include "string_linked.h"
#include "string_processing.h"

int main(int argc,char** argv){
 
    FILE* p_FileRead = 0;
    FILE* p_FileWrite = 0;

	QUEUE_NODE *psta_FrontQueNode,*psta_RearQueNode;
		
    int iRecState = CLOSE_RECORD;
	int	iQueCount = 0;
	int	iSectionCount = 0;
    char chStrLine[300];
	char* p_chStrLine;
	
    p_FileRead = fopen("1.ini", "r");
	p_FileWrite	= fopen("2.ini", "w");
	
	if (!p_FileRead) {
		printf("file open failure\n");
		exit(1);
    }
   
    
	while (NULL != fgets(chStrLine, MAX_NUM_ALINE, p_FileRead)) {
		p_chStrLine = &chStrLine[0];
		
		while(*p_chStrLine++ != '\0');
	    p_chStrLine -= 3;
	
		if('[' == chStrLine[0] && ']' == *p_chStrLine) 			
			if(0 == strncmp("[module_end]",chStrLine,NUM_END_LINE))
            	iSectionCount++;
			
	}
	iSectionCount++;

    psta_FrontQueNode = (QUEUE_NODE*) malloc (iSectionCount*sizeof(QUEUE_NODE));
	psta_RearQueNode = (QUEUE_NODE*) malloc (iSectionCount*sizeof(QUEUE_NODE));

    psta_FrontQueNode[iQueCount].front = NULL;
    psta_RearQueNode[iQueCount].front = &psta_FrontQueNode[iQueCount];
    psta_FrontQueNode[iQueCount].rear = &psta_RearQueNode[iQueCount];
    psta_RearQueNode[iQueCount].rear =	NULL;  

	fseek(p_FileRead,0,SEEK_SET);

    while (NULL != fgets(chStrLine, MAX_NUM_ALINE, p_FileRead)) {
		
		if (CLOSE_RECORD == (iRecState = str_filter_reddt( chStrLine, &psta_RearQueNode[iQueCount], iRecState ))) {
			iQueCount++;
			psta_FrontQueNode[iQueCount].front = NULL;
			psta_RearQueNode[iQueCount].front = &psta_FrontQueNode[iQueCount];
			psta_FrontQueNode[iQueCount].rear = &psta_RearQueNode[iQueCount];
			psta_RearQueNode[iQueCount].rear = NULL;		
    	}
		
	}

	str_write_det_file( psta_RearQueNode, psta_FrontQueNode, iQueCount,p_FileWrite );

    fclose(p_FileRead);
    fclose(p_FileWrite);
    return 0;
}

