#include "grep_main.h"
#include "grep_thread.h"
#include "grep_cmd_info_proc.h"

FILE* p_ListFilePath = NULL;
pthread_mutex_t mutex_op_file;
pthread_cond_t condition_read;
pthread_attr_t thread_attr;
long int iPraseFileCot = 0;

static void prt_message(const int iArgument){

	switch ( iArgument ) {
		case ARUGMENT_NUM_WRONG:
			fprintf ( stderr, "\n\nToo few or more input arguments.\n\n" );
			fprintf ( stderr, "The correct command is consisted of one executed file followed by three arguments as below.\n\n" );
			fprintf ( stderr, "For example, grep.out (1)DIR (2)Keyword (3)ThreadNum\n\n");
			fprintf ( stderr, "(1)DIR, set the path for the parsing directory.\n\n" );
			fprintf ( stderr, "(2)Keyword, the word used to limit that the listing files need to contain it.\n\n" );
			fprintf ( stderr, "(3)ThreadNum, set the number of thread for the parsing directory.\n\n" );
			break;
		case KEY_WRONG:
			fprintf ( stderr, "\n\nThe correct command is consisted of one executed file followed by three arguments as below.\n\n" );
			fprintf ( stderr, "For example, grep.out (1)DIR (2)Keyword (3)ThreadNum\n\n");			
			fprintf ( stderr, "Keyword usage is illegal in (2).\n" );
			fprintf ( stderr, "The keyword used to limit that the listing files need to contain it.\n" );
			fprintf ( stderr, "The characters of legal keyword are within a~z, A~Z or dot, slash and under line\n\n" );
			break;
		case THREAD_NUM_WRONG:
			fprintf ( stderr, "\n\nThe correct command is consisted of one executed file followed by three arguments as below.\n\n" );
			fprintf ( stderr, "For example, grep.out (1)DIR (2)Keyword (3)ThreadNum\n\n");			
			fprintf ( stderr, "Set the wrong number for (3).\n" );
			fprintf ( stderr, "Please set an positive integer.\n\n" );
			break;			
		case CEATE_WRONG:
			fprintf ( stderr, "\n\nMemory allocated error.\n\n" );
			break;
	}

}

int main ( int argc, char** argv ) {
	
	if ( ARUGMENT_NUM != argc ) {
		prt_message(ARUGMENT_NUM_WRONG);
		exit ( EXIT_FAILURE );
	}
	int iThreadCot;
	const int iThreadNum = atoi ( argv[3] );
	pthread_t main_thread;
	pthread_t sub_threads[iThreadNum];	
	MAIN_THREAD_INFO *pst_MainThreadInfo;
	SUB_THREAD_INFO *sta_SubThreadInfo; 
    
	if ( THREAD_NUM_WRONG == check_thread_num( argv[3] ) ) {
        prt_message(THREAD_NUM_WRONG);  
		//prt_message(iCmdThdNumStatus);		
		exit ( EXIT_FAILURE );
	}
	if ( CEATE_WRONG == create_main_info( &pst_MainThreadInfo, argv[1] ,argv[2] ) ) {
        prt_message ( CEATE_WRONG );
		release_main_info( &pst_MainThreadInfo );		
		exit ( EXIT_FAILURE );
	}
	if( KEY_WRONG == check_keyword( pst_MainThreadInfo->cSrhStr ) ){
        prt_message( KEY_WRONG );
		release_main_info( &pst_MainThreadInfo );			
		exit ( EXIT_FAILURE );
	}
	if ( CEATE_WRONG == create_sub_info( &sta_SubThreadInfo, iThreadNum) ){
		prt_message ( CEATE_WRONG );
		release_main_info( &pst_MainThreadInfo );
		exit ( EXIT_FAILURE );
	}
	
	p_ListFilePath = fopen("file_path_list.txt", "w+");

	pthread_mutex_init ( &mutex_op_file, NULL );
	pthread_cond_init ( &condition_read, NULL );
	pthread_attr_init ( &thread_attr );
	pthread_attr_setdetachstate ( &thread_attr, PTHREAD_CREATE_JOINABLE );

	pthread_create ( &main_thread, &thread_attr,
		list_srh_file_to_txt, (void*)pst_MainThreadInfo );
	for (iThreadCot = 0; iThreadCot < iThreadNum; iThreadCot++){
		sta_SubThreadInfo[iThreadCot].iThreadNum = iThreadNum;
		sta_SubThreadInfo[iThreadCot].iThreadID = iThreadCot;
		pthread_create ( &sub_threads[iThreadCot], &thread_attr,
			prt_file_path, (void*)&sta_SubThreadInfo[iThreadCot] );
	}	

	pthread_join( main_thread, NULL );
	for ( iThreadCot = 0; iThreadCot < iThreadNum; iThreadCot++ ){
		pthread_join( sub_threads[iThreadCot], NULL );
	}	

	if(!iPraseFileCot){
		fprintf ( stderr, "\nCan't find any matched file!\n\n" );
	}

	pthread_attr_destroy ( &thread_attr );	
	pthread_mutex_destroy ( &mutex_op_file );
	pthread_cond_destroy ( &condition_read );
	pthread_exit ( NULL );
	release_SUB_info ( &sta_SubThreadInfo );
	release_main_info ( &pst_MainThreadInfo );
	fclose ( p_ListFilePath );
	
	return 0;
}

