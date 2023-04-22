#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>

#define N 64

int main(int argc, char* argv[]) {
	int f[2];
	int status1, status2;

	// Imposto il pipe
	if(pipe(f) == -1) perror("pipe fail");

	pid_t pid = fork();
	
	switch(pid) {
		case -1: perror("errore fork");
		case 0: 
					// la write end del pipe va sullo stdout ( |-> = stdout )
					if(dup2(f[1], 1) == -1) exit(1);
					execlp("ps", "ps", "aux", NULL); 
					exit(1);		
	}	

	close(f[1]);

	pid = fork();
	switch(pid) {
		case -1: perror("errore fork");
		case 0: 		
					// la read end del pipe va sullo stdin ( ->| = stdin )
					if(dup2(f[0], 0) == -1) exit(2);
					execlp("grep", "grep", "bash", NULL);
					exit(1);		
	}
	
	// andrebbero controllati gli WEXTISTATUS
	wait(&status1);
	wait(&status2);
	close(f[0]);
}
