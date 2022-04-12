#include "grep_thread.h"

extern FILE* p_ListFilePath;
extern pthread_mutex_t mutex_op_file;
extern pthread_cond_t condition_read;
extern pthread_attr_t thread_attr;
extern long int iPraseFileCot;

static int cmp_file_name ( const char *ca_CmpedName, const char *ca_SearchName ) {
    size_t Str1Len = strlen( ca_CmpedName );
	size_t Str2Len = strlen( ca_SearchName );

    char temp[Str2Len];

	int iSlideIdx, iSlideLimit;
	int iWordIdx, iRetVal;

	iRetVal = STR_NOFOUND;

	if ( Str1Len < Str2Len ){
		return iRetVal;
	}
	
	iSlideLimit = Str1Len - Str2Len;

	for ( iSlideIdx = 0; iSlideIdx < iSlideLimit ;iSlideIdx++ ){
		for ( iWordIdx = 0; iWordIdx < Str2Len; iWordIdx++ ) {
			temp[iWordIdx] = ca_CmpedName[iSlideIdx + iWordIdx];
		}
		if ( strncmp ( temp, ca_SearchName, Str2Len ) == 0 ) {
			iRetVal = STR_FOUND;
			break;
		}
	}

	return iRetVal;
}

const int list_dir ( const char * ca_DirDame, const char * ca_SearchName ){

	int iRetVal = SUCCESS;
    DIR *pst_Dir;
	struct dirent *pst_Entry;
	const char * ca_DName;
	int path_length;
	char path[PATH_MAX];
	int iInfCount;

    pst_Dir = opendir ( ca_DirDame );

    if ( !pst_Dir ) {
        fprintf ( stderr, "Cannot open directory '%s': %s\n",
                 ca_DirDame, strerror ( errno ) );
		iRetVal = DIR_WRONG;
    } else{
		iInfCount = 0;
	    while ( 1 ) {	
	        pst_Entry = readdir ( pst_Dir );
	        if ( !pst_Entry ) {
	            /// There are no more entries in this directory, so break out of the while loop.
	            break;
	        }
	        ca_DName = pst_Entry->d_name;

	        if (pst_Entry->d_type & DT_DIR) {
	            /// Check that the directory is not "pst_Dir" or pst_Dir's parent.
	            if ( strcmp (ca_DName, "..") != 0 &&
	                 strcmp (ca_DName, ".") != 0 ) {
	 
	                path_length = snprintf ( path, PATH_MAX,
	                                        "%s/%s", ca_DirDame, ca_DName );

	                if ( PATH_MAX <= path_length ) {
						break;
	                }
	                /// Recursively call "list_dir" with the new path.
	                if( DIR_WRONG == list_dir ( path, ca_SearchName ) ) {
						iRetVal = DIR_WRONG;
                        closedir ( pst_Dir );
						goto exit;
					}
	            }
	        } else{
				if ( STR_FOUND == cmp_file_name ( ca_DName, ca_SearchName ) ) {
					fprintf ( p_ListFilePath, "%s/%s\n", ca_DirDame, ca_DName );
				}
			}
			
			if ( INF_LOOP <= iInfCount ) {
				iRetVal = DIR_WRONG;
                closedir ( pst_Dir );
    			goto exit;
			}
			iInfCount++;
	    }
		
	    if ( closedir ( pst_Dir ) ) {
	        fprintf ( stderr, "Could not close '%s': %s\n",
	                 ca_DirDame, strerror (errno) );
			iRetVal = DIR_WRONG;
	    }		
	}

exit:
    
	return iRetVal;
}

void *list_srh_file_to_txt ( void *p_VaryType ) {

	MAIN_THREAD_INFO *pst_CommandInfo = ( MAIN_THREAD_INFO* )p_VaryType;	

	if( DIR_WRONG != list_dir ( pst_CommandInfo->open_directory, pst_CommandInfo->cSrhStr ) ){
		fseek ( p_ListFilePath, 0, SEEK_SET );
	}
	
	pthread_mutex_trylock( &mutex_op_file );	
	pthread_cond_broadcast( &condition_read );
	pthread_mutex_unlock ( &mutex_op_file );

	pthread_exit( NULL );
	
}

void *prt_file_path ( void *p_VaryType ) {
	
	int iStrIdx;
	char cFilePath[PATH_MAX];
	SUB_THREAD_INFO *st_SubThreadInfo = (SUB_THREAD_INFO *)p_VaryType;

	int iLimitFailNum;
	struct timeval st_NowTime;
	struct timespec st_FailTime;

	iLimitFailNum = 0;
	pthread_mutex_trylock( &mutex_op_file );
	if ( THREAD_SMALLEST_NUM == st_SubThreadInfo->iThreadNum ){
		pthread_cond_wait ( &condition_read, &mutex_op_file );
	}
	while(1){
		if (THREAD_SMALLEST_NUM < st_SubThreadInfo->iThreadNum) {
			gettimeofday(&st_NowTime, NULL);
			st_FailTime.tv_sec = st_NowTime.tv_sec + 1;
			st_FailTime.tv_nsec = st_NowTime.tv_usec * 1000;
			if ( ETIMEDOUT == pthread_cond_timedwait( &condition_read, &mutex_op_file, &st_FailTime ) ){
				iLimitFailNum++;
			}
			pthread_cond_broadcast ( &condition_read );	
		}	
		if ( NULL == fgets( cFilePath, PATH_MAX, p_ListFilePath ) ) {	
			break;
		}
		if ( INF_LOOP <= iLimitFailNum ) {
			break;
		}
		
		for ( iStrIdx = 0; cFilePath[iStrIdx] != '\n'; iStrIdx++ );
		cFilePath[iStrIdx] = '\0';			
		printf( "%s", cFilePath );
		printf( " finded by thread %d\n", st_SubThreadInfo->iThreadID);
		iPraseFileCot++;
	}
	pthread_mutex_unlock ( &mutex_op_file );
	
	pthread_exit( NULL );
}

