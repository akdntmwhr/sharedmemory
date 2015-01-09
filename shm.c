#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include "shm.h"

int makeSharedMemory(key_t key, int length, char **msg){
	int shmid;
	shmid = shmget(key, length,  IPC_CREAT|0666);
	if(shmid==-1){
		perror("producer segmet()");
		exit(2);
	}
	
	*msg = shmat(shmid, (char *) 0, 0);
	return shmid;
}

void removeSharedMemory(int shmid, char *shm_msg){
	shmdt(shm_msg);
	shmctl(shmid, IPC_RMID, NULL);
}
