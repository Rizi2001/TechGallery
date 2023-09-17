#include<iostream>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<string>
#include<pthread.h>

using namespace std;

pthread_t tid;
pthread_t tid2;
pthread_t tid3;
pthread_t tid4;

int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100 };

void* thread1(void*arg)
{
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
	
	int* x = (int*)arg;
	//cout<<*x<<endl;
	for(int i=0;i<25;i++)
	{
	if(arr[i]==*x)
		{
			cout<<arr[i]<<" Found at Thread 1\n";
			pthread_testcancel();
		}
	}
	
	pthread_exit(NULL);
}


void* thread2(void*arg)
{
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
	
	int* x = (int*)arg;
	
	for(int i=25;i<49;i++)
	{
	if(arr[i]==*x)
		{
			cout<<arr[i]<<" Found at Thread 2\n";
			pthread_testcancel();
		}
	}
	pthread_exit(NULL);
}


void* thread3(void*arg)
{
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);

	int* x = (int*)arg;
	
	for(int i=49;i<74;i++)
	{
	if(arr[i]==*x)
		{
			cout<<arr[i]<<" Found at Thread 3\n";
			pthread_testcancel();
		}
	}
	pthread_exit(NULL);
}


void* thread4(void*arg)
{
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
	int* x = (int*)arg;
	for(int i=74;i<99;i++)
	{
	if(arr[i]==*x)
		{
			cout<<arr[i]<<" Found at Thread 4\n";
			pthread_testcancel();
		}
	}
	pthread_exit(NULL);
}




int main()
{
	int x;

	cout<<"Enter a number to search" << endl;
	cin>>x;
	
	pthread_create(&tid,NULL,thread1,(void*)&x);
	pthread_create(&tid2,NULL,thread2,(void*)&x);
	pthread_create(&tid3,NULL,thread3,(void*)&x);
	pthread_create(&tid4,NULL,thread4,(void*)&x);
	
	pthread_exit(NULL);
}