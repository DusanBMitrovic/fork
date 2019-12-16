#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>

int main() {

int broj = 1;
int rv;
int pid = fork();


if(pid == 0){
	printf("%d: Pozdrav od Child Procesa\n",getpid());
	
	scanf("%d", &rv);

	printf("Child broj ima vrednost: %d\n", ++broj);
	exit(rv);

} else {
	printf("%d: Pozdrav od Parent Procesa\n",getpid());
	
	printf("Parent ceka na child\n");
	wait(&rv);
	
	printf("rv vrednost: %d\n",WEXITSTATUS(rv));
	printf("Parent broj ima vrednost: %d\n", --broj);
}


return 0;
}
