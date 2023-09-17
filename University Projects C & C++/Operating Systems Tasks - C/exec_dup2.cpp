#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<errno.h>
#include<stdio.h>
using namespace std;

int main(){
	int fd1[2];
	pipe(fd1);

	int fd2[2];
	pipe(fd2);

	pid_t pid=fork();

	if(pid>0){
		wait(NULL);
		close(fd1[1]);

		pid_t pid1=fork();

		if(pid1>0){
			wait(NULL);
			close(fd1[0]);
			close(fd2[1]);

			pid_t pid2=fork();

			if(pid2>0){

				
				
				wait(NULL);

			}
			else if(pid2==0){
				close(fd2[1]);
				dup2(fd2[0],0);
				execl("/usr/bin/wc","wc",NULL);
			}
		}else if(pid1==0){

			close(fd1[1]);
			close(fd2[0]);
			dup2(fd1[0],0);
			dup2(fd2[1],1);
			execl("/usr/bin/sort","sort","-r",NULL);
		}
	}else if(pid==0){
		close(fd1[0]);
		dup2(fd1[1],1);
		execl("/bin/ls","ls",NULL);
	}
}