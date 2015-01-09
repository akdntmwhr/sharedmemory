#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "socket.h"
#include "shm.h"

#define MAXLINE 127

void reverseString(int i);

int main(int argc, char *argv[])
{
	struct sockaddr_in server_addr, client_addr;
	int listen_sock, accp_sock, addrlen=sizeof(client_addr), nbyte;
	char tcp_buf[MAXLINE+1];
	int key, shmid;
	char *shm_msg;
	
	if(argc != 2) {
		printf("usage : %s port\n", argv[0]);
		exit(0);
	}

	listen_sock = makeTcpSocket();

	removeTimeWaitState(listen_sock);
	bindTcpServerSocket(listen_sock, atoi(argv[1]));
	listenTcpServerSocket(listen_sock);
	while(1){
		printf("클라이언트의 요청을 기다리는 중 [listen]\n");
		accp_sock = acceptTcpServerSocket(listen_sock);
		printf("클라이언트가 연결됨\n:");
		receiveMessage(accp_sock, tcp_buf, MAXLINE+1);
		key = atoi(tcp_buf);
		reverseString(key);
		strcpy(tcp_buf, "문자열 역순 치환 완료");
		sendMessage(accp_sock, tcp_buf, MAXLINE+1);
		closeTcpSocket(accp_sock);
	}
	closeTcpSocket(listen_sock);
	return 0;
}

void reverseString(int key){
	char *shm_msg;
	char *tmp_msg="";
	int shmid;
	int count,i;
	makeSharedMemory(key, MAXLINE+1, &shm_msg);
	count = strlen(shm_msg);
	tmp_msg = (char *)malloc(sizeof(char)*(count+1));
	strcpy(tmp_msg, shm_msg);
	for(i=0; i<count; i++){
		shm_msg[i] = tmp_msg[count-1-i];
	}
	free(tmp_msg);
}
