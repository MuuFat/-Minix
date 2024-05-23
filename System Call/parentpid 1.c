#include <stdio.h>
#include <stdlib.h>
#include <lib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char ** argv )
{
  if(argc != 2)
  {
    printf("No. of children to create not specified.\n");
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
      printf("Child process: %d\n", getpid());
      message m;
      int ret = _syscall(PM_PROC_NR, PM_GETPARENTPID, &m);
      printf("syscall return - parent process ID: %d\n", m.m1_i1);
      return 0;
    }
  }
	
  message m;
  int ret = _syscall(PM_PROC_NR, PM_CHILDREN, &m);
  printf("syscall return - no. of children: %d\n", ret );
  wait(NULL);
  printf("Parent process: %d\n", getpid());
  return(0);
}