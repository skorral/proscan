#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include "net.h"

int openConnection(char* ip, char* port) {
	int sockfd;
	struct sockaddr_in sockaddr;

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("can't assign fd for socket");
		perror("socket");
		exit(EXIT_FAILURE);
	}
	memset(&sockaddr, 0,sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	inet_aton(ip, &(sockaddr.sin_addr));
	sockaddr.sin_port = htons(atoi(port));
	printf("connect\n");
	if (connect(sockfd, (struct sockaddr*) &sockaddr, sizeof (sockaddr)) == -1) {
		perror("Connection error");
		exit(EXIT_FAILURE);
	}
	printf("Connection Established\n");
	return sockfd;
}

int listenConnection(char* port) {
	int sockfd;
	struct sockaddr_in sockaddr;
	socklen_t addrlen = sizeof (sockaddr);
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("can't assign fd for socket");
		perror("socket");
		exit(EXIT_FAILURE);
	}
	memset(&sockaddr, 0, sizeof(sockaddr));
	sockaddr.sin_family = AF_INET;
	sockaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	sockaddr.sin_port = htons(atoi(port));

	if (bind(sockfd, (struct sockaddr*) &sockaddr, addrlen) < 0) {
		printf("can't bind socket\n");
		perror("bind");
		exit(EXIT_FAILURE);
	}

	if (listen(sockfd, 10) < 0) {
		printf("can't listen\n");
		perror("listen");
		exit(EXIT_FAILURE);
	}

	return sockfd;
}
