#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include "socket.h"

int makeTcpSocket(){
	int s;
	
	if((s = socket(PF_INET, SOCK_STREAM, 0)) < 0){
		perror("Failed to create socket");
		exit(0);
	}	
	return s;
}

void connectTcpClientSocket(int s, char * ip, int port){
	struct sockaddr_in server_addr;
	
	bzero((char *)&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	inet_pton(AF_INET, ip, &server_addr.sin_addr);
	server_addr.sin_port = htons(port);

	if(connect(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0 ) {
		perror("Failed to connect socket");
		exit(0);
	}

}
void removeTimeWaitState(int s){
	struct linger ling;

	ling.l_onoff=1;
	ling.l_linger=0;

	setsockopt(s, SOL_SOCKET, SO_LINGER, &ling, sizeof(ling));
}
void bindTcpServerSocket(int s, int port){
	struct sockaddr_in server_addr;
	
	bzero((char *)&server_addr, sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port = htons(port);

	if(bind(s, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0 ) {
		perror("Failed to bind socket");
		exit(0);
	}
}

void listenTcpServerSocket(int s){
	listen(s, 5);
}

int acceptTcpServerSocket(int s){
	struct sockaddr_in client_addr;
	int accept_sock;
	int addrlen;
	addrlen = sizeof(client_addr);
	accept_sock = accept(s, (struct sockaddr *)&client_addr, &addrlen);
	if(accept_sock < 0) {
		perror("Failed to accept socket");
		exit(0);
	}
	return accept_sock;
}

int sendMessage(int s, char *message, int length){
	int nbyte;
	if( (nbyte = send(s, message, length,0)) < 0) {
		printf("Failed to send message");
		exit(0);
	}
	return nbyte;
}

int receiveMessage(int s, char *message, int length){
	int nbyte;
	if( (nbyte=recv(s, message, length,0)) < 0) {
		printf("Failed to receive message");
		exit(0);
	}
	return nbyte;
}

void closeTcpSocket(int socket){
	close(socket);
}
