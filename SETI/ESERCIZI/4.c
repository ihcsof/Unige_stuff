#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

#define N 64

int main(int argc, char* argv[]) {
	int fd;
	
	if(argc != 2) exit(1);
	
	// (ri)prova a duplicare fd da stdout
	// ora due file descr. puntano ad stdout
	while((fd = dup(1)) == -1);
	// chiudo il precedente stdout
	if(close(1)) exit(1);
	// apro il file di argv[1] su cui vorro' redirigere ls
	// 1 ora e' libero: open lega argv[1] ad 1: usero' 1
	while(open(argv[1], O_CREAT | O_RDWR, 00664) == -1);
	// posso chiudere fd
	if(close(fd)) exit(1);
	// faccio execl con 1 (non piu' stdout ma argv[1])
	execlp("ls", "ls", "-l", NULL);
}
