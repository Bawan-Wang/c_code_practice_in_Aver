#include <stdio.h>

void _strcat(char*, char*);
int main(){
    char String1[30] = "ABCD";
    char String2[] = "1234";
 
    _strcat(String1, String2);
    printf("String1=%s\n", String1);
 
}
 
void _strcat(char *str1, char *str2){
   
    while(*str1++ != '\0');
    
    str1--;

    while(*str2 != '\0')
        *str1++ = *str2++; 
     *str1 = '\0';
}
