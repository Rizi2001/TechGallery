#pragma once
#include <iostream>
#include <math.h>
using namespace std;

class DoubleNode
{
public:
	int data;
	DoubleNode* next;
	DoubleNode* prev;

};

class DoubleList
{
public:

	DoubleNode* Head;
	DoubleNode* Tail;
	//DoubleNode* current;
	int FTp[5];

	DoubleList()
	{
		Head = NULL;
		Tail = NULL;
		//current = NULL;
		for (int i = 0; i < 5; i++)
			FTp[i] = i + 1;

	}
	void insert(int newdata)
	{
		DoubleNode* current;

		if (Head == NULL)
		{
			Head = new DoubleNode;
			Head->data = newdata;
			Head->prev = NULL;
			Head->next = NULL;
			Tail = Head;
		}
		else
		{
			current = Head;
			while (current->next != NULL)
				current = current->next;

			current->next = new DoubleNode;
			current->next->data = newdata;
			current->next->next = NULL;
			current->next->prev = current;
		}
	}
	void insertAt(int index, int newdata)
	{
		DoubleNode* current;

		int i = 0;
		current = Head;
		while (i < index - 1)
		{
			i++;
			current = current->next;
		}
		DoubleNode* temp;
		temp = new DoubleNode;
		temp->data = newdata;
		temp->prev = current;
		temp->next = current->next;
		current->next = temp;
		temp->next->prev = temp;
		current = temp;
	}
	void printAll()
	{
		DoubleNode* current;

		current = Head;
		while (current != NULL)
		{
			cout << current->data << " ";
			current = current->next;
		}
	}
	//****************Removes node from the back**********************//
	void removeLast()
	{
		DoubleNode* current;

		DoubleNode* temp;

		if (Head == NULL)
		{
			cout << "Empty List";
		}
		else
		{
			current = Head;

			while (current->next != NULL)
				current = current->next;

			temp = current;
			current = current->prev;
			temp->prev = NULL;
			current->next = NULL;
			delete temp;
		}
	}
	void removeAt(int index)
	{
		DoubleNode* current;

		int i = 0;
		current = Head;
		while (i < index)
		{
			i++;
			current = current->next;
		}
		DoubleNode* temp;
		temp = current;
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
		current = current->next;
		delete temp;
	}


	//*************here data is the node number or id and "p" represents the machine *****************///////////////
	int* succ(int p)
	{
		int succ[5] = { 0 };
		int* machvals = new int[5];
		int j = 0;
		for (int i = 0; i < 5; i++)
		{
			succ[i] = (p + pow(2, j));
			j++;
		}

		DoubleNode* current=Head;
		//current = Head;

		//cout << Head->data << endl;

		//cout << current->data << endl;

		while (current && current->data <= p)
		{
			current = current->next;
			//i = current->data;
		}

		//cout << current->data;
		for (int i = 0; i < 5; i++)
		{
			if (succ[i] > current->data)
			{
				current = current->next;
				while (current->data < succ[i])
					current = current->next;

				machvals[i] = current->data;
			}
			else if (succ[i] == current->data)
			{
				machvals[i] = current->data;
				current = current->next;
			}
			else
			{
				machvals[i] = current->data;
			}
		}

		//for (int i = 0; i < 5; i++)
			//cout << machvals[i] << " ";

		return machvals;
	}

	~DoubleList()
	{

	}
};