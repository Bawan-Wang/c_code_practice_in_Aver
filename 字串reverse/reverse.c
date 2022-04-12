#include "stdafx.h"
#include <stdio.h>
#include <string.h>

void reverse(char *,int);
int _tmain(int argc, _TCHAR* argv[])
{
	char string[] = "time";
	reverse(string,strlen(string));
	printf("str=%s\n", string);
	return 0;
}

void reverse(char *str,int n)
{

	int i,j;
	char tmp_char;
    for(i=0,j=n-1; i<j;i++,j--){
		tmp_char = *(str + i);
		*(str + i) = *(str + j);
        *(str + j) = tmp_char;
    }
	
}

