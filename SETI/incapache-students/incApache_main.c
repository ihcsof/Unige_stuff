/* 
 * incApache_main.c: implementazione del main per il web server del corso di SETI
 *
 * Programma sviluppato a supporto del laboratorio di
 * Sistemi di Elaborazione e Trasmissione del corso di laurea
 * in Informatica classe L-31 presso l'Universita` degli Studi di
 * Genova per l'anno accademico 2021/2022.
 *
 * Copyright (C) 2012-2014 by Giovanni Chiola <chiolag@acm.org>
 * Copyright (C) 2015-2016 by Giovanni Lagorio <giovanni.lagorio@unige.it>
 * Copyright (C) 2016-2021 by Giovanni Chiola <chiolag@acm.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 */

#include "incApache.h"

int listen_fd;
FILE *mime_request_stream, *mime_reply_stream;

void create_listening_socket(const char *const port_as_str)
{
	struct addrinfo hints;
	struct addrinfo *server_addr;
	int gai_rv;
	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;
	hints.ai_protocol = IPPROTO_TCP;
	if ((gai_rv = getaddrinfo(NULL, port_as_str, &hints, &server_addr)))
		fail(gai_strerror(gai_rv));
	if ((listen_fd = socket(server_addr->ai_family, server_addr->ai_socktype, server_addr->ai_protocol)) == -1)
		fail_errno("Could not allocate socket descriptor");
	if (bind(listen_fd, server_addr->ai_addr, server_addr->ai_addrlen) == -1)
		fail_errno("Could not bind socket");
	freeaddrinfo(server_addr);
	if (listen(listen_fd, BACKLOG) == -1)
		fail_errno("Could not listen on socket");
}

void drop_privileges()
{
	uid_t uid = getuid();
	assert(uid);
	if (setuid(uid))
		fail_errno("Cannot drop privileges");
}

void run_file(const int *p_to_file, const int *p_from_file)
{
	drop_privileges();
	if (close(p_to_file[PIPE_WRITE_END]))
		fail_errno("close p_to_file write-end");
	if (dup2(p_to_file[PIPE_READ_END], STDIN_FILENO) == -1)
		fail_errno("dup2 stdin");
	if (close(p_from_file[PIPE_READ_END]))
		fail_errno("close p_from_file read-end");
	if (dup2(p_from_file[PIPE_WRITE_END], STDOUT_FILENO) == -1)
		fail_errno("dup2 stdout");
	execlp("file", "file", "--no-buffer", "--brief", "--mime", "--files-from", "-", (char *) NULL);
	fprintf(stderr, "Cannot exec \"file\"\n");
	exit(-1);
}

void run_webserver(const char *const port_as_str, char *www_root, const int *const p_to_file,
		   const int *const p_from_file)
{
	int i;

	/*** perform chroot to www_root; then, create, bind, and listen to
	 *** listen_fd, and eventually drop root privileges ***/
/*** TO BE DONE 5.0 START ***/
#ifndef PRETEND_TO_BE_ROOT
	if(chroot(www_root)) fail_errno("run_webserver");
#endif
	create_listening_socket(port_as_str);
	drop_privileges();

/*** TO BE DONE 5.0 END ***/

#ifdef INCaPACHE_5_1
	printf("Server HTTP 1.1 (with pipelining support)");
#else /* #ifdef INCaPACHE_5_1 */
	printf("Server HTTP 1.0");
#endif /* #ifdef INCaPACHE_5_1 */
	printf(" listening on port %s\nwith WWW root set to %s\n\n", port_as_str, www_root);
	free(www_root);
	mime_request_stream = fdopen(p_to_file[1], "w");
	if (!mime_request_stream)
		fail_errno("Cannot create MIME request stream");
	if (close(p_to_file[0]))
		fail_errno("Cannot close p_to_file read-end");
	mime_reply_stream = fdopen(p_from_file[0], "r");
	if (!mime_reply_stream)
		fail_errno("Cannot create MIME reply stream");
	if (close(p_from_file[1]))
		fail_errno("Cannot close p_from_file write-end");
#ifdef INCaPACHE_5_1
	for (i = MAX_CONNECTIONS; i < MAX_THREADS; i++)
		connection_no[i] = FREE_SLOT;
#endif /* #ifdef INCaPACHE_5_1 */
	for (i = 0; i < MAX_CONNECTIONS; i++) {
		connection_no[i] = i;
#ifdef INCaPACHE_5_1
		no_response_threads[i] = 0;
#endif /* #ifdef INCaPACHE_5_1 */

		/*** create PTHREAD number i, running client_connection_thread() ***/
/*** TO BE DONE 5.0 START ***/
		
		if(pthread_create(&thread_ids[i], NULL, client_connection_thread, (void*)&connection_no[i]))
			fail_errno("pthread_create");

/*** TO BE DONE 5.0 END ***/

	}
	for (i = 0; i < MAX_CONNECTIONS; i++)
		if (pthread_join(thread_ids[i], NULL))
			fail_errno("Could not join thread");
	if (close(listen_fd))
		fail_errno("Cannot close listening socket");
	if (fclose(mime_request_stream))
		fail_errno("Cannot close MIME request stream");
	if (fclose(mime_reply_stream))
		fail_errno("Cannot close MIME reply stream");
}

void check_uids()
{
#ifndef PRETEND_TO_BE_ROOT
	if (geteuid()) {
		fprintf(stderr, "The effective UID should be zero (that is, the executable should be owned by root and have the SETUID flag on).\n");
		exit(EXIT_FAILURE);
	}
#endif /* #ifndef PRETEND_TO_BE_ROOT */
	if (getuid() == 0) {
		fprintf(stderr,
			"The real UID should be non-zero (that is, the executable should be run by a non-root account).\n");
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char **argv)
{
	int p_to_file[2], p_from_file[2];
	const char *port_as_str;
	const char *const default_port = "8000";
	char *www_root;
	pid_t pid;
	signal(SIGPIPE, SIG_IGN);
#ifdef PRETEND_TO_BE_ROOT
	fprintf(stderr, "\n\n\n*** Debug UNSAFE version - DO NOT DISTRIBUTE ***\n\n");
#endif /* #ifdef PRETEND_TO_BE_ROOT */
	check_uids();
	if (argc < 2 || argc > 3) {
		fprintf(stderr, "Usage: %s <www-root> [<port-number>]\nDefault port: %s\n", *argv, default_port);
		return EXIT_FAILURE;
	}
	port_as_str = argc == 3 ? argv[2] : default_port;
	www_root = argv[1];
	if (pipe(p_to_file))
		fail_errno("Cannot create pipe to-file");
	if (pipe(p_from_file))
		fail_errno("Cannot create pipe from-file");
	if (chdir(www_root))
		fail_errno("Cannot chdir to www-root directory");
	www_root = getcwd(NULL, 0);
	if (!www_root)
		fail_errno("Cannot get current directory");
	pid = fork();
	if (pid < 0)
		fail_errno("Cannot fork");
	if (pid == 0)
		run_file(p_to_file, p_from_file);
            else
	        run_webserver(port_as_str, www_root, p_to_file, p_from_file);
	return EXIT_SUCCESS;
}

