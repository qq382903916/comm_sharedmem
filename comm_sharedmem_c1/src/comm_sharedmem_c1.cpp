//============================================================================
// Name        : comm_sharedmem_c1.cpp
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

int main() {
	string str = "this is c1";

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

	while (1) {
		sleep(1);
		strncpy(shared->buf, str.c_str(), BUF_SIZE > str.length() ? str.length() : BUF_SIZE);
		usleep(1000 * 500);
	}

	if (shmdt(shm) == -1) {
		cout << "shmdt failed" << endl;
		exit(-1);
	}
	return 0;
}
