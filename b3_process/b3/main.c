#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
void func()
{
	int status, rv;
	rv = wait(&status);
	if (rv == -1) {
		printf("wait() unsuccessful\n");
	}        
	if (WIFEXITED(status)) {
		printf("Normally termination, status = %d\n", WEXITSTATUS(status));
	} else if (WIFSIGNALED(status)) {
		printf("killed by signal, value = %d\n", WTERMSIG(status));
	}
}
int main(int argc, char const *argv[])
{
	pid_t child_pid;

	child_pid = fork();
	if(child_pid >= 0)
	{
		if(child_pid == 0)
		{
			printf("Child_pid = %d\n", getpid());
			printf("Parent_pid = %d\n", getppid());
			// while(1);
			sleep(2);
			exit(0);
		}
		else
		{
			signal(SIGCHLD, func);
			while(1); 
		}
	} else {
		printf("fork() unsuccessfully\n");
	}
}
