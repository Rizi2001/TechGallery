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
	if(mkfifo("PIPE", 0660) < 0)				//d rw- rw- rw-
	{
		/*if(errno == EEXIST)
			//cout << "mkfifo failed" << endl;	//0  6   6   6
			perror("Error");
		*/
		if(errno != EEXIST)
			cout << "mkfifo failed" << endl;
	}

	if(mkfifo("PIPE1", 0660) < 0)				//d rw- rw- rw-
	{
		/*if(errno == EEXIST)
			//cout << "mkfifo failed" << endl;	//0  6   6   6
			perror("Error");
		*/
		if(errno != EEXIST)
			cout << "mkfifo failed" << endl;
	}

	int fd = open("PIPE", O_WRONLY);
	int fd1 = open("PIPE1", O_RDONLY);

	while(1)
	{
		char buff[100];
		cout << "Enter string: " << endl;
		cin >> buff;

		write(fd,buff,strlen(buff)+1);

		if(strcmp(buff, "exit") == 0)
			break;

		cout << "Message Received in the write file: " << endl;
		
		char buff1[100];

		read(fd1,buff1,sizeof(buff1));

		if(strcmp(buff, "exit") == 0)
			break;

		cout << "Message Received in the write file" << buff1 << endl;
	}

	close(fd);
	close(fd1);

	return 0;
}