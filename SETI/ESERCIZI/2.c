#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define N 64

int main() {
	char fn[N] = "/usr/bin/";
	printf("\nInserisci il nome di un file: ");
	fgets(fn + 9, N - 9, stdin);
	// fgets legge anche /n
	fn[strlen(fn)-1] = '\0';

	execl(fn, fn + 9, NULL);
	perror("Errore execl");
}
