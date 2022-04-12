#include "main.h"



void main(){

	const int iDataNum = 10;

    int iNumbers[] = {5, 77, 45, 9, 31, 89, 92, 17, 259,4};
	char cLetters[] = {'a', 'H', 'o', 'd', 'E', 'A', 'D', 'Q', 'Z', 'h'};
	
	sort_get_dualIntOrder(iNumbers, iDataNum, LITTLE_SORT);
	sort_get_dualIntOrder(iNumbers, iDataNum, BIG_SORT);
	sort_get_dualCharOrder(cLetters, iDataNum, LITTLE_SORT);
	sort_get_dualCharOrder(cLetters, iDataNum, BIG_SORT);
	
}

void sort_get_dualIntOrder(int *iNumbers, const int iNumOfDig, const int iSortType){

    int iCmpedIdx,iCmpingIdx;
    int iPrtIdx;

	for (iCmpedIdx = 0; iCmpedIdx < iNumOfDig - 1; iCmpedIdx++) {
		for (iCmpingIdx = iCmpedIdx + 1; iCmpingIdx < iNumOfDig; iCmpingIdx++) {
			if (BIG_SORT == iSortType) {	
				if (iNumbers[iCmpedIdx] < iNumbers[iCmpingIdx]) {
					SWAP(iNumbers[iCmpedIdx],iNumbers[iCmpingIdx]);
				}
			}else if(LITTLE_SORT == iSortType){
				if (iNumbers[iCmpedIdx] > iNumbers[iCmpingIdx]) {
					SWAP(iNumbers[iCmpedIdx],iNumbers[iCmpingIdx]);
				}
			}
		}
	}

	for(iPrtIdx = 0; iPrtIdx < 10; iPrtIdx++)
		printf("%d ",iNumbers[iPrtIdx]);
	printf("\n");	
}

void sort_get_dualCharOrder(char *cLetters, const int iNumOfDig, const int iSortType){

    int iCmpedIdx,iCmpingIdx;
	char chtempCmpedIdx,chtempCmpingIdx;
    int iPrtIdx;

	for (iCmpedIdx = 0; iCmpedIdx < iNumOfDig - 1; iCmpedIdx++) {
		for (iCmpingIdx = iCmpedIdx + 1; iCmpingIdx < iNumOfDig; iCmpingIdx++) {
			///Catch the ASCII codes about the two processed words
			if (cLetters[iCmpedIdx] >= 'a') {
				chtempCmpedIdx = cLetters[iCmpedIdx] - 'a';
			}else if (cLetters[iCmpedIdx] <= 'Z') {
				chtempCmpedIdx = cLetters[iCmpedIdx] - 'A';
			}	
			
			if (cLetters[iCmpingIdx] >= 'a') {
				chtempCmpingIdx = cLetters[iCmpingIdx] - 'a';
			}else if (cLetters[iCmpingIdx] <= 'Z') {
				chtempCmpingIdx = cLetters[iCmpingIdx] - 'A';		
			}
			
			if (BIG_SORT == iSortType) {
				if (cLetters[iCmpedIdx] >= 'a') {
						if(chtempCmpedIdx <= chtempCmpingIdx){ ///Compare the ASCII codes of the two characters
							SWAP(cLetters[iCmpedIdx],cLetters[iCmpingIdx]);
						}
				}else if (cLetters[iCmpedIdx] <= 'Z') {
					if (chtempCmpedIdx != chtempCmpingIdx) {
						if (chtempCmpedIdx < chtempCmpingIdx) { ///Compare the ASCII codes of the two characters
							SWAP(cLetters[iCmpedIdx],cLetters[iCmpingIdx]);
						}
					}			
				}				
			}else if (LITTLE_SORT == iSortType) {
				if (cLetters[iCmpedIdx] >= 'a') {
					if (chtempCmpedIdx != chtempCmpingIdx) {
						if (chtempCmpedIdx > chtempCmpingIdx) { ///Compare the ASCII codes of the two characters
							SWAP(cLetters[iCmpedIdx],cLetters[iCmpingIdx]);
						}
					}
				}else if (cLetters[iCmpedIdx] <= 'Z') {
					if(chtempCmpedIdx >= chtempCmpingIdx){ ///Compare the ASCII codes of the two characters
						SWAP(cLetters[iCmpedIdx],cLetters[iCmpingIdx]);
					}			
				}
			}
		}
	}

	for (iPrtIdx = 0; iPrtIdx < 10; iPrtIdx++)
		printf("%c ",cLetters[iPrtIdx]);
	printf("\n");	
}


