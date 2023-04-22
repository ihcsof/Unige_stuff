/*
 * pong_server.c: server in ascolto su una porta TCP "registrata".
 *                Il client invia una richiesta specificando il protocollo
 *                desiderato (TCP/UDP), il numero di messaggi e la loro lunghezza.
 *                Il server (mediante una fork()) crea un processo dedicato
 *                a svolgere il ruolo di "pong" secondo le richieste del client.
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

#include <signal.h>
#include "pingpong.h"

void sigchld_handler(int signum)
{
	int status;
	if (waitpid(-1, &status, WNOHANG) == -1)
		fail("Pong Server cannot wait for children in SIGCHLD handler");
}

void tcp_pong(int message_no, size_t message_size, FILE *in_stream, int out_socket)
{
	char buffer[message_size], *cp;
	int n_msg, n_c;
        struct timespec time2, time3;

	for (n_msg = 1; n_msg <= message_no; ++n_msg) {
		int seq = 0;
		debug(" tcp_pong: n_msg=%d\n", n_msg);
		for (cp = buffer, n_c = 0; n_c < message_size; ++n_c, ++cp) {
			int cc = getc(in_stream);
			if (cc == EOF)
				fail("TCP Pong received fewer bytes than expected");
			*cp = (char)cc;
		}

                /*** get time-stamp time2 from the clock ***/
/*** TO BE DONE START ***/
	if(clock_gettime(CLOCK_TYPE, &time2))
		fail_errno("Error in retrieving current time");

/*** TO BE DONE END ***/


		if (sscanf(buffer, "%d\n", &seq) != 1)
			fail("TCP Pong got invalid message");
		debug(" tcp_pong: got %d sequence number (expecting %d)\n%s\n", seq, n_msg, buffer);
		if (seq != n_msg)
			fail("TCP Pong received wrong message sequence number");

                /*** get time-stamp time3 from the clock ***/
/*** TO BE DONE START ***/
	if(clock_gettime(CLOCK_TYPE, &time3))
		fail_errno("Error in retrieving current time");

/*** TO BE DONE END ***/

                sprintf(buffer,"%ld %ld, %ld %ld\n", (long)time2.tv_sec, time2.tv_nsec,
                                                     (long)time3.tv_sec, time3.tv_nsec);
		if (blocking_write_all(out_socket, buffer, message_size) != message_size)
			fail_errno("TCP Pong failed sending data back");
	}
}

void udp_pong(int dgrams_no, int dgram_sz, int pong_socket)
{
	char buffer[dgram_sz];
	ssize_t received_bytes;
	int n, resend;
	struct sockaddr_storage ping_addr;
	socklen_t ping_addr_len;
        struct timespec time2, time3;

	for (n = resend = 0; n < dgrams_no;) {
		int i;
		ping_addr_len = sizeof(struct sockaddr_storage);
		if ((received_bytes = recvfrom(pong_socket, buffer, sizeof buffer, 0, (struct sockaddr *)&ping_addr, &ping_addr_len)) < 0)
			fail_errno("UDP Pong recv failed");


                /*** get time-stamp time2 from the clock ***/
/*** TO BE DONE START ***/
	if(clock_gettime(CLOCK_TYPE, &time2))
		fail_errno("Error in retrieving current time");

/*** TO BE DONE END ***/

		if (received_bytes < dgram_sz)
			fail("UDP Pong received fewer bytes than expected");
		if (sscanf(buffer, "%d\n", &i) != 1)
			fail("UDP Pong received invalid message");
#ifdef DEBUG
		{
			struct sockaddr_in *ipv4_addr = (struct sockaddr_in *)&ping_addr;
			char addrstr[INET_ADDRSTRLEN];
			const char * const cp = inet_ntop(AF_INET, &(ipv4_addr->sin_addr), addrstr, INET_ADDRSTRLEN);
			int j;
			if (cp == NULL)
				printf(" could not convert address to string\n");
			else
				printf("  ... received %d bytes from %s, port %hu, sequence number %d (expecting %d)\n", (int)received_bytes, cp, ntohs(ipv4_addr->sin_port), i, n);
			for (j = 0; j < dgram_sz; ++j)
				printf("%c", buffer[j]);
			printf("\n-------------------------------------\n");
		}
#endif
		if (i < n || i > dgrams_no || i < 1)
			fail("UDP Pong received wrong datagram sequence number");
		if (i > n) {	/* new datagram to pong back */
			n = i;
			resend = 0;
		} else {	/* resend previous datagram */
			if (++resend > MAXUDPRESEND)
				fail("UDP Pong maximum resend count exceeded");
		}

                /*** get time-stamp time3 from the clock ***/
/*** TO BE DONE START ***/
	if(clock_gettime(CLOCK_TYPE, &time3))
		fail_errno("Error in retrieving current time");

/*** TO BE DONE END ***/

                sprintf(buffer,"%ld %ld, %ld %ld\n", (long)time2.tv_sec, time2.tv_nsec,
                                                     (long)time3.tv_sec, time3.tv_nsec);
		if (sendto(pong_socket, buffer, (size_t)received_bytes, 0, (struct sockaddr *)&ping_addr, ping_addr_len) < ping_addr_len)
			fail_errno("UDP Pong failed sending datagram back");
	}
}


/*** The following function creates a new UDP socket and binds it
 *   to a free Ephemeral port according to IANA definition.
 *   The port number is stored at the location pointed by "pong_port".
 */
int open_udp_socket(int *pong_port)
{
	struct addrinfo gai_hints, *pong_addrinfo;
	int udp_socket, port_number, gai_rv, bind_rv;

	memset(&gai_hints, 0, sizeof gai_hints);
	gai_hints.ai_family = AF_INET;
	gai_hints.ai_socktype = SOCK_DGRAM;
	gai_hints.ai_flags = AI_PASSIVE;
	gai_hints.ai_protocol = IPPROTO_UDP;
#ifdef WEBDEV_FIREWALL
	for (port_number = MYMINEPHEM; port_number <= MYMAXEPHEM; ++port_number) {
#else
	for (port_number = IANAMINEPHEM; port_number <= IANAMAXEPHEM; ++port_number) {
#endif
		char port_number_as_str[6];
		sprintf(port_number_as_str, "%d", port_number);

                /*** create DGRAM socket, call getaddrinfo() to set port number, and bind() ***/
/*** TO BE DONE START ***/
		if((gai_rv = getaddrinfo(NULL, port_number_as_str, &gai_hints, &pong_addrinfo)))
			fail(gai_strerror(gai_rv));

		if((udp_socket = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
			fail_errno("Server failed creating socket");

		if(!bind(udp_socket, (struct sockaddr*) pong_addrinfo->ai_addr, pong_addrinfo->ai_addrlen)) {
			// Assegno a pong_port l'effettivo numero di porta scelto (assegn. nel for).
			// Il chiamante utilizzera' il port number scelto. Poi ritorno il socket udp
			*pong_port = port_number;
			return udp_socket;
		}

/*** TO BE DONE END ***/

		if (errno != EADDRINUSE) 
			fail_errno("UDP Pong could not bind the socket");
		if (close(udp_socket))
			fail_errno("UDP Pong could not close the socket");
	}
	fprintf(stderr, "UDP Pong could not find any free ephemeral port\n");
	return -1;
}

void serve_pong_udp(int request_socket, int pong_fd, int message_size, int message_no, int pong_port)
{
	char answer_buf[16];
	sprintf(answer_buf, "OK %d\n", pong_port);
	if (blocking_write_all(request_socket, answer_buf, strlen(answer_buf)) != strlen(answer_buf))
		fail_errno("Pong Server UDP cannot send ok message to the client");
	if (shutdown(request_socket, SHUT_RDWR))
		fail_errno("Pong Server UDP cannot shutdown socket");
	if (close(request_socket))
		fail_errno("Pong Server UDP cannot close request socket");
	udp_pong(message_no, message_size, pong_fd);
}

void serve_pong_tcp(int pong_fd, FILE *request_stream, size_t message_size, int message_no)
{
	const char *const ok_msg = "OK\n";
	const size_t len_ok_msg = strlen(ok_msg);
	int nodelay_value = 1;
	if (setsockopt(pong_fd, IPPROTO_TCP, TCP_NODELAY, &nodelay_value, sizeof nodelay_value))
		fail_errno("Pong Server TCP cannot set TCP_NODELAY option");
	if (blocking_write_all(pong_fd, ok_msg, len_ok_msg) != len_ok_msg)
		fail_errno("Pong Server TCP cannot send ok message to the client");
	tcp_pong(message_no, message_size, request_stream, pong_fd);
	if (shutdown(pong_fd, SHUT_RDWR))
		fail_errno("Pong Server TCP cannot shutdown socket");
}

void serve_client(int request_socket, struct sockaddr_in *client_addr)
{
	FILE *request_stream = fdopen(request_socket, "r");
	char *request_str = NULL, *strtokr_save;
	char *protocol_str, *size_str, *number_str;
	size_t n;
	int message_size, message_no;
	struct timeval receiving_timeout;
	char client_addr_as_str[INET_ADDRSTRLEN];
	int is_tcp = 0, is_udp = 0;

	if (!request_stream)
		fail_errno("Cannot obtain a stream from the socket");
	if (inet_ntop(AF_INET, &client_addr->sin_addr, client_addr_as_str, INET_ADDRSTRLEN) == NULL)
		fail_errno("Pong server could not convert client address to string");
	debug("Got connection from %s\n", client_addr_as_str);
	receiving_timeout.tv_sec = (time_t)PONGRECVTOUT;
	receiving_timeout.tv_usec = (suseconds_t)0;
	if (setsockopt(request_socket, SOL_SOCKET, SO_RCVTIMEO, &receiving_timeout, sizeof receiving_timeout))
		fail_errno("Cannot set socket timeout");
	if (getline(&request_str, &n, request_stream) < 0) {
send_request_error:
		{
			const char *const error_msg = "ERROR\n";
			const size_t len_error_msg = strlen(error_msg);
			if (blocking_write_all(request_socket, error_msg, len_error_msg) != len_error_msg)
				fail_errno("Pong server cannot send error message to the client");
			if (fclose(request_stream))
				fail_errno("Pong server cannot close request stream");
			exit(EXIT_FAILURE);
		}
	}
	protocol_str = strtok_r(request_str, " ", &strtokr_save);
	if (!protocol_str) {
free_str_and_send_request_error:
		free(request_str);
		goto send_request_error;
	}
	if (strcmp(protocol_str, "TCP") == 0)
		is_tcp = 1;
	else if (strcmp(protocol_str, "UDP") == 0)
		is_udp = 1;
	else
		goto free_str_and_send_request_error;
	size_str = strtok_r(NULL, " ", &strtokr_save);
	if (!size_str)
		goto free_str_and_send_request_error;
	if (sscanf(size_str, "%d", &message_size) != 1)
		goto free_str_and_send_request_error;
	if (message_size < MINSIZE || message_size > MAXTCPSIZE || (is_udp && message_size > MAXUDPSIZE))
		goto free_str_and_send_request_error;
	number_str = strtok_r(NULL, " ", &strtokr_save);
	if (!number_str)
		goto free_str_and_send_request_error;
	if (sscanf(number_str, "%d", &message_no) != 1)
		goto free_str_and_send_request_error;
	if (message_no < 1 || message_no > MAXREPEATS)
		goto free_str_and_send_request_error;
	free(request_str);
	if (is_udp) {
		int pong_port;
		int pong_fd = open_udp_socket(&pong_port);
		if (pong_fd < 0)
			goto send_request_error;
	        if (setsockopt(pong_fd, SOL_SOCKET, SO_RCVTIMEO, &receiving_timeout, sizeof receiving_timeout))
		        fail_errno("Cannot set UDP socket timeout");
		serve_pong_udp(request_socket, pong_fd, message_size, message_no, pong_port);
	} else {
		assert(is_tcp);
		serve_pong_tcp(request_socket, request_stream, (size_t)message_size, message_no);
	}
	fclose(request_stream);
	exit(EXIT_SUCCESS);
}

void server_loop(int server_socket) {
	for (;;) {
		struct sockaddr_in client_addr;
		socklen_t addr_size = sizeof(client_addr);
		int request_socket = accept(server_socket, (struct sockaddr *)&client_addr, &addr_size);
		pid_t pid;

/*** check for possible accept() errors, and if connection was correctly
     establised fork() and have the child process call serve_client() ***/
/*** TO BE DONE START ***/
		
		// Controllo errori sul socket di richiesta
		if(request_socket == -1) {
			/* Many system calls will report the EINTR error code if a signal occurred while the system 
			call was in progress. No error actually occurred, it's just reported that way because the system 
			isn't able to resume the system call automatically. This coding pattern simply retries the system 
			call when this happens, to ignore the interrupt. */
			if(errno == EINTR) continue;
			close(server_socket);
			fail_errno("Pong Server cannot accept");
		}

		// Se il socket e' OK, effettuo la fork...
		if((pid = fork()) == -1)
			fail_errno("failed to fork");
		//.. se la fork va a buon fine, il processo con pid 0 (figlio) serve il client:
		if(!pid)
			serve_client(request_socket, &client_addr);

/*** TO BE DONE END ***/

		if (close(request_socket))
			fail_errno("Pong Server cannot close request socket");
	}
}

int main(int argc, char **argv)
{
	struct addrinfo gai_hints, *server_addrinfo;
	int server_socket, gai_rv;
	struct sigaction sigchld_action;
	if (argc != 2)
		fail("Pong Server incorrect syntax. Use: pong_server PORT-NUMBER");
	memset(&gai_hints, 0, sizeof gai_hints);
	gai_hints.ai_family = AF_INET;
	gai_hints.ai_socktype = SOCK_STREAM;
	gai_hints.ai_flags = AI_PASSIVE;
	gai_hints.ai_protocol = IPPROTO_TCP;

        /*** call getaddrinfo() to setup port number and server address, ***
         *** create STREAM socket, bind() and listen()                   ***/
/*** TO BE DONE START ***/

	if((gai_rv = getaddrinfo(NULL, argv[1], &gai_hints, &server_addrinfo)))
		fail(gai_strerror(gai_rv));
	
	if((server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1)
		fail_errno("error creating socket");

	if(bind(server_socket, (struct sockaddr*) server_addrinfo->ai_addr, server_addrinfo->ai_addrlen) == -1)
		fail_errno("error binding socket");

	if(listen(server_socket, LISTENBACKLOG) == -1)
		fail_errno("error during listening");

/*** TO BE DONE END ***/

	freeaddrinfo(server_addrinfo);
	fprintf(stderr, "Pong server listening on port %s ...\n", argv[1]);
	sigchld_action.sa_handler = sigchld_handler;
	if (sigemptyset(&sigchld_action.sa_mask))
		fail_errno("Pong Server cannot initialize signal mask");
	sigchld_action.sa_flags = SA_NOCLDSTOP;
	if (sigaction(SIGCHLD, &sigchld_action, NULL))
		fail_errno("Pong server cannot register SIGCHLD handler");
	server_loop(server_socket);
}

