#include "grep_cmd_info_proc.h"

const int check_thread_num(char* ca_ThdNum){
	
	char* ca_TmpKeyWord = ca_ThdNum;
	int iRetVal = SUCCESS;

	while ( '\0' != *ca_TmpKeyWord ){
		if( !( ASCII_NUM_0 <= *ca_TmpKeyWord && ASCII_NUM_9 >= *ca_TmpKeyWord) ){
			iRetVal = THREAD_NUM_WRONG;
			break;
		}
		ca_TmpKeyWord++;
	}

	return iRetVal;
}

const int check_keyword(char* ca_KeyWord){
	
	char* ca_TmpKeyWord = ca_KeyWord;
	int iRetVal = SUCCESS;

	while ( '\0' != *ca_TmpKeyWord ){
		if( !( (ASCII_DOT <= *ca_TmpKeyWord && ASCII_NUM_9 >= *ca_TmpKeyWord) ||
			(ASCII_LETTER_C_A <= *ca_TmpKeyWord && ASCII_LETTER_C_Z >= *ca_TmpKeyWord) ||
			(ASCII_LETTER_L_A <= *ca_TmpKeyWord && ASCII_LETTER_L_Z >= *ca_TmpKeyWord) ||
			ASCII_UNDER_LINE == *ca_TmpKeyWord) ){
			iRetVal = KEY_WRONG;
			break;
		}
		ca_TmpKeyWord++;
	}

	return iRetVal;
}

static char* copy_str ( char *str2 ) {
	
	char *result;
	size_t str2_len;
	
	if(NULL == str2){
		return NULL;
	}
	
	str2_len = strlen( str2 );
	result = malloc ( str2_len );
	strcpy ( result, str2 );	

	return result;
}

const int create_main_info ( MAIN_THREAD_INFO **pst_RetInfo, char *ca_CmdOPDir ,char *ca_CmdSrh ) {

	int iRetVal = SUCCESS;
	
	MAIN_THREAD_INFO *pst_TmpRetInfo; 

	if (NULL == ( pst_TmpRetInfo = (MAIN_THREAD_INFO*) malloc ( sizeof(MAIN_THREAD_INFO) ) ) ){
		iRetVal = CEATE_WRONG;
		return iRetVal;
	}
	
	if (NULL == ( pst_TmpRetInfo->open_directory = (char*) malloc ( strlen(ca_CmdOPDir) ) ) ){
		iRetVal = CEATE_WRONG;
		return iRetVal;
	} else{
		strcpy(pst_TmpRetInfo->open_directory,ca_CmdOPDir);
	}
	if (NULL == ( pst_TmpRetInfo->cSrhStr = (char*) malloc ( strlen(ca_CmdSrh) ) ) ){
		iRetVal = CEATE_WRONG;
		return iRetVal;
	} else{
		strcpy(pst_TmpRetInfo->cSrhStr,ca_CmdSrh);	
	}	

	*pst_RetInfo = pst_TmpRetInfo;
	return iRetVal;
}

void release_main_info ( MAIN_THREAD_INFO **pst_RetInfo) {
	
	MAIN_THREAD_INFO *pst_TmpRetInfo = *pst_RetInfo; 
	
	free(pst_TmpRetInfo->open_directory);
	free(pst_TmpRetInfo->cSrhStr);
	free(pst_TmpRetInfo);
}

const int create_sub_info ( SUB_THREAD_INFO **sta_RetInfo, const int iThreadNum ) {
	
	int iRetVal = SUCCESS;
	SUB_THREAD_INFO *sta_TmpRetInfo; 

	if(NULL == (sta_TmpRetInfo = ( SUB_THREAD_INFO* ) malloc ( iThreadNum * sizeof( SUB_THREAD_INFO ) ) ) ){
		iRetVal = CEATE_WRONG;
		return iRetVal;
	}

	*sta_RetInfo = sta_TmpRetInfo;
	
	return iRetVal;
}

void release_SUB_info ( SUB_THREAD_INFO **sta_RetInf ) {
	
	SUB_THREAD_INFO *sta_TmpRetInfo = *sta_RetInf; 
	
	free(sta_TmpRetInfo);
}


