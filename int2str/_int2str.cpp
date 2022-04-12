#include <stdio.h>
#include <stdlib.h>

char* _int2str(int);

void main()
{
	int number = 1288365;
	char *string;
	string = _int2str(number);
	printf("string = %s\n",string);
}

char* _int2str(int num)
{
	int count;
	int digit = 1,tempnum = num;
	char *strreverse;

	while((tempnum /= 10) > 0)
		digit++;

	strreverse = (char*)malloc(digit*sizeof(char));

	for(count = digit - 1; count >= 0 ;count--)
	{
		*(strreverse + count) = (num % 10) | 0x30;
		num /= 10;
	}
	*(strreverse + digit) = '\0';

	return strreverse;
}