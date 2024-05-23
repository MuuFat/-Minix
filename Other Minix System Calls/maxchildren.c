#include <stdio.h>
#include <stdlib.h>
#include <lib.h>
#include <unistd.h>
#include <sys/wait.h>

int main (int argc, char ** argv)
{
	if( argc != 2)
	  {
	  printf("No. of children to creaete not specified.\n");
	  return 0;
	  }
	int children_to_create;
	int i;
	
	children_to_create = atoi(argv[1]);
	for(int i=0;i<children_to_create;i++)
	{
	  if (fork()==0)
	  {
		 printf("Child no. %d created\n",i);
		 sleep(10);
		 return 0;
	  }
	}
	
	message m;
	int ret;
	
	printf("Parent PID: %d\n", getpid());
	ret=_syscall( PM_PROC_NR, PM_MAXCHILDREN, & m);
	printf("syscall return - PID - no. of children: %d\n", ret );
	ret=_syscall( PM_PROC_NR, PM_WHOMAXCHILDREN, & m );
	printf("syscall reeturn - PID- max no. of children: %d\n",ret);
	wait(NULL);
	return 0;
}