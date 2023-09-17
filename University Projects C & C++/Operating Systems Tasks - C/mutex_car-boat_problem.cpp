#include<iostream>
#include<pthread.h>
#include<unistd.h>

using namespace std;

pthread_mutex_t lock1=PTHREAD_MUTEX_INITIALIZER;

int car, car_t, boat, boat_t = 0;

int iter = 1;
int iter1 = 1;

void* Car(void* arg)
{
	pthread_mutex_lock(&lock1);
	
	cout << "Car " << iter << " Passing" << endl;
	iter++;
	
	for(int i=0; i<car_t; i++){
	
		sleep(1);
		
		cout << "*" << endl;
	}

	pthread_mutex_unlock(&lock1);
	
	pthread_exit(NULL);
}

void* Boat(void* arg)
{
	pthread_mutex_lock(&lock1);
	
	cout << "Boat " << iter1 << " Passing" << endl;
	iter1++;
	
	for(int i=0; i<boat_t; i++){
	
		sleep(1);
		
		cout << "*" << endl;
	}

	pthread_mutex_unlock(&lock1);
	
	pthread_exit(NULL);
}

int main()
{
	cout << "Enter the total number of Cars: " << endl;
	cin >> car;
	
	cout << "Enter the total time for cars to pass: " << endl;
	cin >> car_t;
	
	cout << "Enter the total number of Boats: " << endl;
	cin >> boat;
	
	cout << "Enter the total time for boats to pass: " << endl;
	cin >> boat_t;
	
	pthread_t tid[car];
	pthread_t tid1[boat];
	
	for(int i=0; i<car; i++)
		pthread_create(&tid[i],NULL,Car,NULL);
	
	for(int i=0; i<boat; i++)
		pthread_create(&tid1[i],NULL,Boat,NULL);
		
	pthread_exit(NULL);

	return 0;
}