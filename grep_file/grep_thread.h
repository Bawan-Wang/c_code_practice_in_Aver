#ifndef __GREP_THREAD__ 
#define __GREP_THREAD__

#include "grep_main.h"

#define THREAD_SMALLEST_NUM		(1)
#define INF_LOOP			(10000)

void *list_srh_file_to_txt ( void *p_VaryType );
void *prt_file_path ( void *p_VaryType );

#endif ///__GREP_THREAD__

