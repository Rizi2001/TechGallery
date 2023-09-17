#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int main()
{
	int fd = open("PIPE", O_RDONLY);
	int fd1 = open("PIPE1", O_WRONLY);

	while(1)
	{
		char buff[100];
		read(fd,buff,sizeof(buff));

		if(strcmp(buff,"exit")==0)
			break;

		cout << "Received Message by the read file: " << buff << endl;

		char buff1[100];

		cout << "Enter String in the read file: " << endl;
		cin >> buff1;

		write(fd1,buff1,strlen(buff1)+1);

		if(strcmp(buff,"exit")==0)
			break;

		cout << "Message received by the read file." << endl;
	}

	close(fd);
	close(fd1);

	return 0;
}