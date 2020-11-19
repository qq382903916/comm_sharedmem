//============================================================================
// Name        : comm_sharedmem_s.cpp
// Author      : hex
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
using namespace std;

#define BUF_SIZE 1024
struct shared_mem_st {
	int flag;
	char buf[BUF_SIZE];
};
struct shared_mem_st buf_mem;

int main() {
	void *shm = NULL;
	struct shared_mem_st *shared = NULL;
	int shmid;
	key_t key = ftok("/tmp", 66);
	shmid = shmget(key, sizeof(struct shared_mem_st), 0666 | IPC_CREAT);
	if (shmid == -1) {
		cout << "shmget failed" << endl;
		exit(-1);
	}
	shm = shmat(shmid, (void*) 0, 0);
	if (shm == (void*) -1) {
		cout << "shmat failed" << endl;
		exit(-1);
	}

	shared = (struct shared_mem_st*) shm;

	memset(buf_mem.buf, 0, BUF_SIZE);
	while (1) {
		//
		strncpy(buf_mem.buf, shared->buf, BUF_SIZE);
		if (strlen(buf_mem.buf) > 0) {
			cout << buf_mem.buf << endl;
		}
		usleep(1000 * 200);
	}

	if (shmdt(shm) == -1) {
		cout << "shmdt failed" << endl;
		exit(-1);
	}
	return 0;
}
