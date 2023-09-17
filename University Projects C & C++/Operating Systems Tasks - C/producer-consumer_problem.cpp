#include <pthread.h>
#include <iostream>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
using namespace std;

int buffer[10];
int itr = 0;

pthread_t pid[10], cid[10];
pthread_mutex_t mutex;

sem_t producer_s, consumer_s;

void* producer(void*){

    while (1)
    {  
        sleep(1);
        int x = rand()%100;

        sem_wait(&producer_s);

        pthread_mutex_lock(&mutex);
        
        buffer[itr] = x;
        itr++;         

        pthread_mutex_unlock(&mutex);

        sem_post(&consumer_s);
    }

    pthread_exit(NULL);
}

void* consumer(void*)
{
    while (1)
    { 
        sleep(1);

        sem_wait(&consumer_s);

        pthread_mutex_lock(&mutex);
        
        int y = buffer[itr-1];
        itr--;
        cout<<"got at "<<itr<<", "<<y<<endl;
        
        pthread_mutex_unlock(&mutex);

        sem_post(&producer_s);
    }
    
    pthread_exit(NULL);
}

int main()
{
    pthread_mutex_init(&mutex, NULL);
    
    sem_init(&producer_s, 0, 10);
    sem_init(&consumer_s, 0, 0);

    for (int i = 0; i < 10; i++)
    {
        pthread_create(&pid[i], NULL, producer, NULL);
        pthread_create(&cid[i], NULL, consumer, NULL); 
    }

    pthread_mutex_destroy(&mutex);

    sem_destroy(&producer_s);
    sem_destroy(&consumer_s);

    pthread_exit(NULL);
}