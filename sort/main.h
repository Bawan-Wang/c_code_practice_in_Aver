#ifndef __MAIN__ 
#define __MAIN__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LITTLE_SORT		(-10)
#define BIG_SORT		(10)

#define SWAP(x,y)		x = x + y; y = x - y; x = x - y;

void sort_get_dualIntOrder(int *iNumbers, const int iNumOfDig, const int iSortType);
void sort_get_dualCharOrder(char *cLetters, const int iNumOfDig, const int iSortType);

#endif ///__MAIN__
#
