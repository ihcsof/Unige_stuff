/*
 * write_log.c: implementazione dell'esercizio "Stardate UTC: Captain's Log".
 *
 * versione 1.5 del 7/04/2021
 *
 * Programma sviluppato a supporto del laboratorio di
 * Architettura dei Calcolatori del corso di laurea triennale
 * in Informatica classe L-31 presso l'Universita` degli Studi di
 * Genova, anno accademico 2020/2021.
 *
 * Copyright (C) 2013-2021 by Giovanni Chiola <chiolag@acm.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#define FNAM "captains_log"
#define SS 128

void fail_errno(const char * msg) {
    perror(msg);
    exit(1);
}

void fail(const char * msg) {
    fprintf(stderr,"ERROR: %s\n",msg);
    exit(1);
}


int main(int argc, char** argv){
    char string[SS], *msg;
    struct tm btm;
    time_t now_t = time(NULL); /* get current time */
    struct flock fls;
    int fc, fd, tm_sz, rc, wc;

/*** TO BE DONE START ***/
    /* open() log file in R/W mode, create if it doesn't exist already,
       and check the returned value */
	 // Apro in R/W, oppure CREO. Modo: 0644 (permesso)
	 if((fd = open(FNAM,O_RDWR | O_CREAT, 0644)) == 0)

/*** TO BE DONE END ***/

        fail_errno("Could not open log file in R/W mode");
    
    /*** Prepare string to append ***/
    memset((void*)string,0,sizeof(string));

/*** TO BE DONE START ***/
    /* call gmtime_r() and strftime() to print current date in *
     * standard RFC3339 format, followed by ", " into "string" */
	 gmtime_r(&now_t, &btm);
	 strftime(string,SS, "%F %XZ, ",&btm);

/*** TO BE DONE END ***/

    if ( argc < 2 )
        msg = "???";
    else
        msg = argv[1];

/*** TO BE OPTIONALLY MODIFIED START ***/
	 tm_sz = strlen(string);
	 // Concateniamo la prima porzione di str (tempo #1 + msg)
    strncat(string,msg,sizeof(string)-tm_sz-2);

/*** TO BE OPTIONALLY MODIFIED END ***/

    /*** Acquire a POSIX Advisory Write lock on the entire file ***/

/*** TO BE DONE START ***/
    /* initialize "fls" struct */
	 fls.l_type = F_WRLCK;
	 fls.l_whence = SEEK_SET;
	 fls.l_start = 0;
	 fls.l_len = 0;
	 fls.l_pid = 0;

/*** TO BE DONE END ***/
    while ( (fc = fcntl(fd,F_SETLKW,&fls)) < 0 && errno == EINTR ); /*** wait ***/
    if ( fc < 0 )
        fail_errno("Could not acquire write lock on log file");


/*** TO BE OPTIONALLY MODIFIED START ***/
    /* include log registration time, avoiding possible "string" overflow */
	 // Ri-ottengo il tempo (#2) e creo la nuova str
	 now_t = time(NULL); /* get current time */
	 gmtime_r(&now_t, &btm);
	 char newstr[tm_sz+1];
	 // Formattazione del tempo#2 (+1 per il terminatore \0)
	 strftime(newstr,tm_sz+1, ", %F %XZ",&btm);
	 // Se sono in overflow: elimino ciò che eccede
	 // string = tempo#1+msg ; newstr = tempo#2
	 if(strlen(string) > (SS - sizeof(newstr)))
		string[SS - sizeof(newstr)] = '\0';
	 // Ora posso usare strcat senza problemi ;-)
	 strcat(string, newstr);
	 strcat(string,"\n");

/*** TO BE OPTIONALLY MODIFIED END ***/

    /*** append string to the end of the log file ***/

/*** TO BE DONE START ***/
    /* call lseek() to move pointer to the end of the file */
	 lseek(fd, 0L, SEEK_END);

/*** TO BE DONE END ***/

    for ( rc = strlen(string), msg = string ; rc > 0 ; rc -= wc )
        if ( (wc = write(fd,(const void*)string,(size_t)rc)) < 0 ) {

/*** TO BE DONE START ***/
            /* check errno comparing with EINTR */
				if(errno != EINTR)
					fail_errno(msg);

/*** TO BE DONE END ***/

        } else
            msg += wc;
        
    if ( argc >= 3 ) { /*** hold lock until reading a new line ***/
        printf("holding lock until you hit <ENTER>\n"); fflush(stdout);
        getchar();
      }
    close(fd); /*** this also releases the Advisory Write lock on the log file ***/
    exit(0);
}
