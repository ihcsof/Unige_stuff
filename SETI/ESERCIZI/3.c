#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define N 64

int main() {
	for(;;) {
		printf("\nveronica $ ");
		
		char fn[N];
		if(scanf("%s", fn) == EOF || !strcmp(fn, "exit")) exit(EXIT_SUCCESS);

		pid_t pid = fork();
		int status;

		switch(pid) {
			case -1: perror("errore fork");
			case 0: execlp(fn, fn, NULL); perror("Exec fallita");
			default: wait(&status);
		}

		// Va bene se e' uscito (exited) e con uno stato = 0
		if (WIFEXITED(status)) {
			  	if(WEXITSTATUS(status)) exit(WEXITSTATUS(status));
		}
		else exit(1);
	}
}
