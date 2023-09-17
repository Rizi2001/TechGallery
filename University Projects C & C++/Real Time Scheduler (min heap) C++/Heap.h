#pragma once
#include<iostream>
#include <ctime>
#include <cmath>

using namespace std;

int totalObj = 0;

int day_time = 0;

class process
{
public:
    string taskName;
    int dueTime;
    int duration;
    bool run;
    int runTime;
    static int countObj;

    process()
    {
        taskName = "";
        dueTime = 0;
        duration = 0;
        run = false;
        runTime = 0;
        countObj += 1;

        totalObj = countObj;
    }

    void displayP()
    {
        cout << "Task Name: " << taskName << " " << " Due Time: " << dueTime << " Duration: " << " " << duration << " " << " Run: " << run << " " << " runTime: " << runTime << endl;
    }
};

int process::countObj = 0;

void swap(process* x, process* y)
{
    process temp = *x;
    *x = *y;
    *y = temp; 
}

class MinHeap
{
    process* arr; 
    int capacity; 
    int heap_size;
public:
    MinHeap()
    {
        heap_size = 0;
        capacity = 0;
        arr = NULL;
    }

    MinHeap(int cap)
    {
        heap_size = 0;
        capacity = cap;
        arr = new process[cap];
    }

    void MinHeapify(int i)
    {
        //clock_t time_req;

        //time_req = clock();

        int l = left(i);
        int r = right(i);
        int smallest = i;
        if (l < heap_size && arr[l].dueTime < arr[i].dueTime)
            smallest = l;
        if (r < heap_size && arr[r].dueTime < arr[smallest].dueTime)
            smallest = r;
        if (smallest != i)
        {
            swap(&arr[i], &arr[smallest]);
            MinHeapify(smallest);
        }

        //time_req = clock() - time_req;

        //cout << endl;
        //cout << "Time taken by the whole Min Heap to execute is: " << ((float)time_req / CLOCKS_PER_SEC) / 1000000000 << " nanoseconds" << endl << endl;
    }

    int parent(int i) 
    { 
        return (i - 1) / 2; 
    }

    int left(int i) 
    { 
        return (2 * i + 1); 
    }
    
    int right(int i)
    {
        return (2 * i + 2); 
    }

    process extractMin()
    {
        if (heap_size == 1)
        {
            heap_size--;
            return arr[0];
        }

        process root = arr[0];
        arr[0] = arr[heap_size - 1];
        heap_size--;
        MinHeapify(0);

        return root;
    }

    process getMin() 
    {
        return arr[0]; 
    }

    void insertKey(process k)
    {
        clock_t time_req;

        time_req = clock();

        if (heap_size == capacity)
        {
            cout << "\nOverflow: Could not insertKey\n";
            return;
        }

        heap_size++;
        int i = heap_size - 1;
        arr[i] = k;

        while (i != 0 && arr[parent(i)].dueTime > arr[i].dueTime)
        {
            swap(&arr[i], &arr[parent(i)]);

            i = parent(i);
        }

        time_req = clock() - time_req;

        cout << day_time << ": " << "Adding "<< k.taskName << " with deadline " << k.dueTime << " and duration " << k.duration << ", " << (((float)time_req / CLOCKS_PER_SEC) / 1000000000) << " nanoseconds" << endl;
    }

    void display()
    {
        for (int i = 0; i < heap_size; i++)
        {
            cout << arr[i].dueTime << endl;
        }
    }
};