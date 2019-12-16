#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <fcntl.h>
#include <string.h>

#define buffer 1024
#define elements 10

char SEM_NAME1[] = "sem1";
char SEM_NAME2[] = "sem2";

int main() {

	key_t key = 1000;
	int volatile *shm;
	sem_t* semafor1;
	sem_t* semafor2;
	int i;

	int shmid = shmget(key, buffer, IPC_CREAT|0666);
	
	semafor1 = sem_open(SEM_NAME1,O_CREAT, 0644, 0);
	semafor2 = sem_open(SEM_NAME2,O_CREAT, 0644, 0);

	shm = shmat(shmid, (void*)0, 0);
	
	for(i=1;i<elements;i++){
		sem_post(semafor1);
		printf("%d\n",*shm);
		sleep(1);
		sem_wait(semafor2);
	}
	sem_close(semafor1);
	sem_unlink(SEM_NAME1);
	sem_close(semafor2);
	sem_unlink(SEM_NAME2);
	shmctl(shmid, IPC_RMID,0);
	exit(0);

return 0;
}
