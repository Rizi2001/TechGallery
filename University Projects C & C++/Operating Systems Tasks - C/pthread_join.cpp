#include <iostream>
#include <pthread.h>
#include <string.h>

using namespace std;

pthread_t tid_rev;
pthread_t tid_cap;
pthread_t tid_shift;

void* rev(void* arg)
{
	char *argv=(char*)arg;
	
	char temp[100];
	
	int i;
	
	for(i = 0; argv[i] ; i++)
		temp[i] = argv[i];

	temp[i] = '\0';

	int size=strlen(argv);
	int j=0;
	
	for(i=size-1 ; i>=0 ; i--,j++)
		argv[j] = temp[i];

	for(i=0; i<size; i++)
		cout << argv[i];

	cout << endl;

	pthread_exit(NULL);
}

void* cap(void* arg)
{
	char *argv=(char*)arg;
	for(int i = 0; argv[i] ; i++)
		argv[i] -= 32;

	int size=strlen(argv);

	for(int i=0; i<size; i++)
		cout << argv[i];

	cout << endl;

	pthread_exit(NULL);
}

void* shift(void* arg)
{
	char *argv=(char*)arg;
	int size=strlen(argv);
	int i;

	for(i=0; i<size-2 ;i++)
		argv[i]=argv[i+2];
	
	argv[i] = '\0';

	for(i=0; i<size-1; i++)
		cout << argv[i];

	cout << endl;

	pthread_exit(NULL);
}


int main()	
{
	char str[100];

	cout << "Input String: " << endl;
	cin >> str;

	pthread_create(&tid_rev, NULL, rev, str);
	pthread_join(tid_rev, NULL);
	
	pthread_create(&tid_cap, NULL, cap, str);
	pthread_join(tid_cap, NULL);

	pthread_create(&tid_shift, NULL, shift, str);
	pthread_join(tid_shift, NULL);

	pthread_exit(NULL);

	return 0;
}