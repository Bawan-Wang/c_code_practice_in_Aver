// swap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//#define CALLBYADDRESS

#ifdef CALLBYADDRESS
	void swap(int*,int*);
#else
	void swap(int&,int&);
#endif
int _tmain(int argc, _TCHAR* argv[])
{
	int x = 3,y = 5;
#ifdef CALLBYADDRESS
	swap(&x,&y);
#else
	swap(x,y);
#endif
	printf("x = %d,y = %d",x,y);
	return 0;
}

#ifdef CALLBYADDRESS
void swap(int *a,int *b)
{
	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;
}
#else
void swap(int &a,int &b)
{
	a = a + b;
	b = a - b;
	a = a - b;
}
#endif

