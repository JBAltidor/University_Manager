#include<stdio.h>
#include <string.h>
#include <stdlib.h>
char *MoneyCheck();
int main()
{
    
    printf("Enter money \n");
    printf("%s",MoneyCheck());
}

char *MoneyCheck()
{
    char *p;
   static char str[100];
    scanf("%s",str);


double f = strtod(str,&p);
if (strlen(str)==0) {
    printf("empty string\n");
} else {
    if (*p == 0) {
        return str;
    } else {
        MoneyCheck();
    }
}
}