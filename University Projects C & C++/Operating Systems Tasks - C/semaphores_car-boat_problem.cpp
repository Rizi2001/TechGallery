#include<iostream>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
using namespace std;

int count = 0;
pthread_t* tid;
int fact[5];
int itr=0;
int numcars = 0, numboats = 0, time1, time2;
sem_t lock1;
sem_t lock2;

void* car(void* arg)
{
	int var=9999;

	int n = *((int*) arg);
	sem_getvalue(&lock1,&var);

	// cout << var <<  " First " <<endl;

	sem_wait(&lock1);
	
	// cout << var << " Second " << endl;

	cout << "Car " << n << " Passing " << endl; 
	for(int i = 0; i < time1; i++){
		sleep(1);
		// cout << "C" << n << endl;
		
	}
	cout << endl;
	sem_post(&lock1);
	
	//sleep(1);
	pthread_exit(NULL);
}

void* boat(void* arg)
{	
	int n = *((int*) arg);
	
	sem_wait(&lock2);

	cout << "Boat " << n << " Passing " << endl; 
	for(int i = 0; i < time2; i++){
		sleep(1);
		// cout << "B" << i <<endl;
	}
	cout << endl;

	sem_post(&lock2);
	
	//sleep(1);
	pthread_exit(NULL);
}

int main()
{
	sem_init(&lock1,0,3);
	sem_init(&lock2,0,2);

	cout << "Enter The number of Cars: ";
	cin >> numcars;
	cout << "Enter The time for car to pass: ";
	cin >> time1;
	cout << "Enter The number of Boats: ";
	cin >> numboats;
	cout << "Enter The time for boat to pass: ";
	cin >> time2;
	

	tid = new pthread_t[numcars+numboats];
	
	
	for(int i = 0; i < numcars; i++)
	{
		int* id = new int;
		*id = i;
		pthread_create(&tid[i], NULL, car,(void*) id);
	}
		
	for(int i = numcars, j = 0; i < numboats+numcars, j < numboats; i++, j++)
	{
		int* id = new int;
		*id = j;
		pthread_create(&tid[i], NULL, boat,(void*) id);
	}

	for(int i = 0; i < numboats+numcars; i++)	
		pthread_join(tid[i], NULL);
	
	sem_destroy(&lock1);
	sem_destroy(&lock2);

	pthread_exit(NULL);
	
	return 0;
}
