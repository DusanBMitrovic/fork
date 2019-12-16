#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stdio.h>
#include <sys/stdlib.h>
#include <sys/semaphore.h>
#include <sys/fcntl.h>
#include <sys/string.h>

#define buffer 1024
#define elements 10

char SEM_NAME1[] = "sem1";
char SEM_NAME2[] = "sem2";

int main() {

	key_t key = 1000;
	int volatile *shm, *s;
	sem_t* semafor1;
	sem_t* semafor2;
	int i;

	int shmid = shmget(key, buffer, IPC_CREAT|0666);
	
	semafor1 = sem_open(SEM_NAME1,O_CREAT, 0644, 0);
	semafor2 = sem_open(SEM_NAME2,O_CREAT, 0644, 0);

	shm = shmat(shmid, (void*)0, 0);
	
	*shm = i;
	sem_wait(semafor1);
	printf("%d\n",*shm);
	sem_post(semafor2);


return 0;
}
