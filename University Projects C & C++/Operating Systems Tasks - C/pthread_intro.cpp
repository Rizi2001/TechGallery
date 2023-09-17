#include <iostream>
#include<unistd.h>
#include<pthread.h>

using namespace std;

pthread_t tid[3];

struct rect
{
	int length;
	int width;
	int height;
};

void* Area(void* arg)
{
	rect *a = (rect * ) arg;
	cout << "Area: " << a->length * a->width << endl;

	pthread_exit(NULL);
}

void* Perimeter(void* arg)
{
	rect *a = (rect * ) arg;
	
	cout << "Perimeter: " << 2*a->length + 2*a->width << endl;

	pthread_exit(NULL);
}

void* surfaceArea(void* arg)
{
	rect *a = (rect * ) arg;
	
	int surA = 2*(a->length * a->width) + 2*(a->length * a->height) + 2*(a->width * a-> height);

	cout << "surface Area: " << surA << endl;

	pthread_exit(NULL);
}

int main(void)
{
	rect r;

	cout << "Enter Length: " << endl;
	cin >> r.length;

	cout << "Enter width: " << endl;
	cin >> r.width;

	cout << "Enter height: " << endl;
	cin >> r.height;
	
	pthread_create(&tid[0], NULL, Area, (void*)&r);
	pthread_create(&tid[1], NULL, Perimeter, (void*)&r);
	pthread_create(&tid[2], NULL, surfaceArea, (void*)&r);

	pthread_exit(NULL);

	return 0;
}