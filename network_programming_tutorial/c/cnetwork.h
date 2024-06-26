#ifndef CNETWORK_H
#define CNETWORK_H

#include <arpa/inet.h>
#include <errno.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define PORT "3490"
#define BACKLOG 10 // максимальное колличество поключений
#define MAXDATASIZE 100 // максимальная длина принимаемых за раз данных

void  sigchld_handler(int s);
void* get_in_addr(struct sockaddr* sa);

#endif // CNETWORK_H
