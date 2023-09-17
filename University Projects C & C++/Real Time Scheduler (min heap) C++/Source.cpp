#include <iostream>
#include<fstream>
#include <string.h>
#include<cstring>
#include <chrono>
#include <ctime>
#include <cmath>
#include "Heap.h"

#define SIZE 1000

using namespace std;

process p_array_run[SIZE];
int iter_run = 0;

process p_array[SIZE];

void readFile(const string& file_name)
{
	clock_t time_req;

	time_req = clock();

	fstream file;
	string word;

	file.open(file_name.c_str());
	
	int i = 0;
	int counter = 0;

	while (file >> word) 
	{ 
		if (counter > 3)
		{
			counter = 0;
			i++;
		}

		if (counter == 0)
		{
			if (word == "schedule")
				p_array[i].run = false;

			else
				p_array[i].run = true;
		}

		if(p_array[i].run == false)
		{
			if (counter == 1)
				p_array[i].taskName = word;

			if (counter == 2)
				p_array[i].dueTime = atoi(word.c_str());
			
			if (counter == 3)
				p_array[i].duration = atoi(word.c_str());//stoi(word);

			counter++;
		}
		
		if (p_array[i].run == true)
		{
			if (counter == 0)
				p_array[i].taskName = "Run";

			if (counter == 1)
			{
				p_array[i].runTime = atoi(word.c_str());//stoi(word);

				i++;
				counter = 0;
			}
			else
				counter++;
		}
	}
	
	file.close();

	time_req = clock() - time_req;

	cout << "Time taken by the Read File function is: " << ((float)time_req / CLOCKS_PER_SEC) / 1000000000 << " nanoseconds" << endl << endl;
}

void schedular(MinHeap& h, int len)
{	
	clock_t time_req;

	time_req = clock();

	int t = 0;
	int rt = 0;

	int r = p_array_run[iter_run].runTime;

	while (len > 0)
	{
		process p1 = h.extractMin();
		
		cout << day_time << ": busy with " << p1.taskName << " with deadline " << p1.dueTime << " and duration " << p1.duration << endl;
		
		if ((r - day_time) < p1.duration && (iter_run < 2))
		{
			t = p_array_run[iter_run].runTime - p1.duration;

			p1.duration -= (r - day_time);

			day_time = r;// p_array_run[iter_run].runTime;
			
			iter_run++;

			r = p_array_run[iter_run].runTime;

			h.insertKey(p1);
		}
		else
		{
			int temp = day_time;

			day_time += p1.duration;

			cout << day_time << ": " << " done with " << p1.taskName << endl;

			//cout << day_time << endl;

			iter_run++;
		
			len--;
		}
	}

	time_req = clock() - time_req;

	cout << endl;
	cout << "Time taken by the Scheduler function is: " << ((float)time_req / CLOCKS_PER_SEC) / 1000000000 << " nanoseconds" << endl;
}

int main(void)
{
	clock_t time_req;

	time_req = clock();

	string file = "file.txt"; 

	readFile("file1.txt");

	int iterCount = 0;

	for (int i = 0; i < totalObj; i++)
	{
		if (p_array[i].taskName == "")
			break;

		iterCount++;
	}

	//cout << iterCount << endl;

	//for (int i = 0; i < iterCount; i++)
		//p_array[i].displayP();

	process p_array_new[SIZE];
	
	int j = 0;
	int k = 0;

	for (int i = 0; i < iterCount; i++)
	{
		if (p_array[i].taskName == "Run")
			p_array_run[k++] = p_array[i];
		else
			p_array_new[j++] = p_array[i];
	}

	//for (int i = 0; i < j; i++)
		//p_array_new[i].displayP();

	//for (int i = 0; i < k; i++)
		//p_array_run[i].displayP();

	MinHeap h(iterCount);

	for (int i = 0; i < j; i++)
		h.insertKey(p_array_new[i]);

	//h.display();
	//cout << h.extractMin() << endl;

	schedular(h, j);

	time_req = clock() - time_req;

	cout << endl;
	cout << "Total Time Taken by program is: " << ((float)time_req / CLOCKS_PER_SEC)/1000000000 << " nanoseconds" << endl;


	return 0;
}