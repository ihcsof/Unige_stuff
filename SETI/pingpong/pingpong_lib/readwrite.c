/*
 * readwrite.c: funzioni ausiliarie per il ping-pong
 *
 * versione 8.0
 *
 * Programma sviluppato a supporto del laboratorio di
 * Sistemi di Elaborazione e Trasmissione del corso di laurea
 * in Informatica classe L-31 presso l'Universita` degli Studi di
 * Genova, anno accademico 2021/2022.
 *
 * Copyright (C) 2013-2014 by Giovanni Chiola <chiolag@acm.org>
 * Copyright (C) 2015-2016 by Giovanni Lagorio <giovanni.lagorio@unige.it>
 * Copyright (C) 2017-2021 by Giovanni Chiola <chiolag@acm.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include <stdlib.h>
#include "pingpong.h"

/* read_all and write_all, inspired by readn and writen of the 
   book "Advanced Programming in the UNIX Environment" */

ssize_t read_all(int fd, void *ptr, size_t n)
{
	size_t n_left = n;
	while (n_left > 0) {
		ssize_t n_read = read(fd, ptr, n_left);
		printf("a\n");
		if (n_read < 0) {
			if (n_left == n)
				return -1; /* nothing has been read */
			else
				break; /* we have read something */
		} else if (n_read == 0) {
			break; /* EOF */
		}
		n_left -= n_read;
		ptr += n_read;
	}
	assert(n - n_left >= 0);
	return n - n_left;
}

ssize_t blocking_write_all(int fd, const void *ptr, size_t n)
{
	size_t n_left = n;
	while (n_left > 0) {
		ssize_t n_written = write(fd, ptr, n_left);
		if (n_written < 0) {
			if (n_left == n)
				return -1; /* nothing has been written */
			else
				break; /* we have written something */
		} else if (n_written == 0) {
                        continue;
		}
		n_left -= n_written;
		ptr += n_written;
	}
	assert(n - n_left >= 0);
	return n - n_left;
}

ssize_t nonblocking_write_all(int fd, const void *ptr, size_t n)
{
	size_t n_left = n;
	while (n_left > 0) {
		ssize_t n_written = write(fd, ptr, n_left);
		if (n_written < 0) {

/*** TO BE DONE START ***/
			// Controllo su errno: send fallita perche' non_block (buffer dest pieno)
			if(errno == EAGAIN || errno == EWOULDBLOCK) continue;

/*** TO BE DONE END ***/

			if (n_left == n)
				return -1; /* nothing has been written */
			else
				break; /* we have written something */
		} else if (n_written == 0) {
                        continue;
		}
		n_left -= n_written;
		ptr += n_written;
	}
	assert(n - n_left >= 0);
	return n - n_left;
}

