#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <memory.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include "socket.h"
#include "shm.h"
#define SHMKEY 5355
#define MAXLINE 127

int main(int argc, char *argv[]){
	struct timeval tv1, tv2;
	double millisec;
	key_t shmkey = SHMKEY;
	struct sockaddr_in server_addr;
	int s, nbyte, shmid;
	char *shm_msg;
	char tcp_buf[MAXLINE+1];

	if(argc!=3){
		printf("usage: %s ip_address\n", argv[0]);
		exit(0);
	}	
	makeSharedMemory(shmkey, MAXLINE+1, &shm_msg);

	strcpy(shm_msg, "ABCDEFGHIJKLMNOP");
	sprintf(tcp_buf, "%d", SHMKEY);

	s=makeTcpSocket();
	connectTcpClientSocket(s, argv[1], atoi(argv[2]));

	printf("공유 메모리 키 : %d\n", SHMKEY);

	nbyte = sizeof(SHMKEY);

	gettimeofday(&tv1, NULL);	
	sendMessage(s, tcp_buf, nbyte);

	printf("수신 : ");
	
	receiveMessage(s, tcp_buf, MAXLINE+1);
	printf("%s\n", tcp_buf);	
	gettimeofday(&tv2, NULL);
	millisec = tv2.tv_usec - tv1.tv_usec;
	millisec/= (double) 1000000;
	printf("결과 : %s\n", shm_msg); 
	printf("w - r : %lf sec \n", millisec);
	removeSharedMemory(shmid, shm_msg);
	closeTcpSocket(s);
	return 0;
}

