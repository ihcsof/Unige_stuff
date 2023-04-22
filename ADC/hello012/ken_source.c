	0
};

/*
 * The string s is a
 * representation of the body
 * of this program from '0'
 * to the end.
 */

int main(){
	int i;
/*** Notice: the include files at the beginning and the "exit(0);" at the end,
 *** as well as the "int" explicit type declaration for function "main()",
 *** have been added to the original code by Ken Thompson in order to keep
 *** the current version of GCC happy, and avoid compilation errors/warnings.
 *** Moreover, the printing of the string initialization has been changed
 *** in order to print 10 characters per line for better readability   :-)
 ***/
        INITIAL_PRINTF
	for(i=0;s[i];i++)
		printf("\t%d,%c",s[i],((i+1)%10)?' ':'\n');

/*** TO BE DONE START ***/
	//Printf della stringa come da file di Ken
	printf("%s",s);
/*** TO BE DONE END ***/

}
