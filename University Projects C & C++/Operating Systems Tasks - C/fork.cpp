#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
using namespace std;

int main()
{
	int a = 9999;
	int status = 9999;

	string str1,str2;

	cout << "Input a string (without spaces)" << endl;
	cin >> str1;

	cout << "Input the second string" << endl;
	cin >> str2;

	pid_t pid = fork();

	if(pid > 0)
	{
		cout << "Parent " << endl;

		wait(&status);

		cout << "Status " << WEXITSTATUS(status)<< endl;

		
		if(WEXITSTATUS(status) == 1)
			cout << "Equal as Status is 1" << endl;

		else if(WEXITSTATUS(status) == 0)
			cout << "Not Equal as Status is 0" << endl;
		
		else
			cout << "Invalid Entry" << endl;
	}

	else if(pid == 0)
	{
		if(str1 == str2)
			a = 1;	//String is same	
		else
			a = 0;	//Strings are different

		exit(a);
	}

	else
		cout << "Fork Failed"<< endl;

	return 0;
}