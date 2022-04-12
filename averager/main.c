#include "main.h"

void main ( int argc, char** argv ) {

	const int iDataNum = argc;
	long int lRetVal;
	int iSum = 0;
	int iDataNumIdx;
	
	for ( iDataNumIdx = 1; iDataNumIdx < iDataNum; iDataNumIdx++ ) {
		lRetVal = convertor_str_to_int( argv[iDataNumIdx] );
		if ( WORNG_NUM == lRetVal ) {
			printf("You type some wrong numbers.\n");
			iSum = lRetVal;
			break;
		} else{
			iSum += (int)lRetVal;
		}
	}

	if ( WORNG_NUM == iSum ) {
		printf("Error");
	}else{
		printf("Average = %d",iSum/(iDataNum - 1));

	}
	
	printf("\n");
}

long int convertor_str_to_int ( char *cDataNum ){

	int iDigit = 0;
	long int iNum = 0;
	
	while ( cDataNum[iDigit] != '\0' ) {
		if (ASCII_NUM_0 > cDataNum[iDigit] || ASCII_NUM_9 < cDataNum[iDigit]) {
			iNum = WORNG_NUM;
			break;
		}
			
		iNum = iNum * 10 + (cDataNum[iDigit] - ASCII_NUM_0);
		iDigit++;
	}
	
	return iNum;
}

