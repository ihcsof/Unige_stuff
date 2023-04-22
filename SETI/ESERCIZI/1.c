#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define N 64

int main() {
	pid_t pid = fork();
	int status;

	switch(pid) {
		case -1: perror("errore fork");
		case 0: execlp("ls", "ls", "-l", NULL); exit(1);
		default: wait(&status);
	}

	// Va bene se e' uscito (exited) e con uno stato = 0
	if (WIFEXITED(status)) {
		  	if(WEXITSTATUS(status)) exit(WEXITSTATUS(status));
	}
	else exit(1);

	exit(0);	
}
