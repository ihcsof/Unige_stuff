#ifndef PINGPONG_H
#define PINGPONG_H

/*
 * pingpong.h: include file per l'implementazione del ping-pong TCP e UDP.
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

#define WEBDEV_FIREWALL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <assert.h>

#define MINREPEATS 151		/* Min number of tests */
#define REPEATS 501		/* Default number of tests */
#define MAXREPEATS 1501		/* Max number of tests */
#define MINSIZE 32		/* Minimum message size */
#define LISTENBACKLOG 1
#define UDP_TIMEOUT ((double)3000.0)	/* 3.0 seconds, Ping side */
#define MAXTCPSIZE (1024*1024)	/* 1 MiB */
#define MAXUDPSIZE 65500        /* Less than 64 KiB */
#define MAXUDPRESEND 3
#define IANAMINEPHEM 49152
#define MYMINEPHEM 62831
#define IANAMAXEPHEM 65535
#define MYMAXEPHEM 62930
#define PONGRECVTOUT 10
#define MAX_REQ 30
#define MAX_ANSW 10

extern void fail_errno(const char *const msg);
extern void fail(const char *const msg);
extern double timespec_delta2milliseconds(struct timespec *last, struct timespec *previous);
extern void print_statistics(FILE * outf, const char *name, int repeats,
			     double rtt[repeats], int msg_sz, double resolution);

#define CLOCK_TYPE CLOCK_MONOTONIC

#ifdef DEBUG
#define debug(...) printf(__VA_ARGS__)
#else
#define debug(...)
#endif

ssize_t read_all(int fd, void *ptr, size_t n);
ssize_t blocking_write_all(int fd, const void *ptr, size_t n);
ssize_t nonblocking_write_all(int fd, const void *ptr, size_t n);

#endif /* #ifdef PINGPONG_H */

