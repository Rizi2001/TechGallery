#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

using namespace std;

int main(int argc, char* argv[])
{
	char str1[100];

	int fd1[2];
	pipe(fd1);

	int fd2[2];
	pipe(fd2);
	
	pid_t pid = fork();

	if(pid > 0)
	{
		wait(NULL);

		pid_t pid1 = fork();

		if(pid1>0)
		{
			wait(NULL);

			pid_t pid2 = fork();

			if(pid2 > 1)
				wait(NULL);

			else if(pid2 == 0)
			{
				char buf[100];

				read(fd2[0], buf, sizeof(buf));
				cout << "Received by C3: "<< buf << endl;

				close(fd2[0]);
			}
		}
		else if(pid1==0)
		{
			close(fd2[0]);

			char buf[100];

			read(fd1[0], buf, sizeof(buf));
			cout << "Received by C2: "<< buf << endl;

			char buf2[100];

			for(int i=0; i<100; i++)
				buf2[i]=buf[i];

			write(fd2[1], buf2, strlen(buf2) + 1);

			cout << "Sent to C3" << endl;
			
			close(fd2[1]);
			close(fd1[0]);
		}
	}
	else 
	{
		char buf[100];

		close(fd1[0]);
        close(fd2[0]);
        close(fd2[1]);

		cout << "Enter string in C1: "<< endl;
		cin>>buf;

		write(fd1[1],buf,strlen(buf)+1);
		//cout << "Sent by child: " << endl;

		close(fd1[1]);
	}

	return 0;
}