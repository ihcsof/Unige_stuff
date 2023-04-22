#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void my_printf(char*p){
	char s[strlen(p)+1], *q=s;
        strcpy(s,p);

/*** TO BE DONE START ***/while(isspace(*q))q++;*q=toupper(*q);puts(s);/*** TO BE DONE END ***/

}

int main(){
	my_printf("hello world!");
	my_printf(" how are you?");
	my_printf("  I\'m OK, thanks, and you?");
	my_printf("   1, 2, 3, testing ...");
	my_printf("\t  looks OK :-)");
	my_printf(" \t    bye bye!");
	exit(0);
}
