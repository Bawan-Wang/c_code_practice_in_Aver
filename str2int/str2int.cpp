// str2int.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string.h>

int str2int(char*);
int _tmain(int argc, _TCHAR* argv[])
{
	int num;
    char str[] = "54862330";
    num = str2int(str);
    printf("number = %d\n",num);

	return 0;
}

int str2int(char* str)
{
	int i=0,num=0;
	while(str[i]!='\0')
	{
		num=num*10+(str[i] & 0x0f);
		i++;
	}
	return num;
}
