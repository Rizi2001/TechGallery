#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <cmath>
#include <time.h>
#include "Tree.h"
#include "DataPair.h"
#include "FTP.h"

using namespace std;

static int x = 0;

class Machine
{
public:
	string machineId, data;
	int key;
	bool isPrimaryMachine;
	Machine* next;
	avl_tree avl;
	int serialNo;

	Machine()
	{
		serialNo = x++;
		machineId = "";
		data = "";
		key = 0;
		isPrimaryMachine = false;
		next = NULL;
	}
	Machine(string mN, string d, int k, bool iPM, Machine* m = NULL)
	{
		machineId = mN;
		data = d;
		key = k;
		isPrimaryMachine = iPM;
		next = m;
	}

	int getSerialNum()
	{
		return this->serialNo;
	}
	void setMachineID(string id)
	{
		machineId = id;
	}
};



class CircularLinkedList
{
public:
	Machine* head;
	DoubleList ftp;

	CircularLinkedList()
	{
		head = NULL;
	}

	unsigned int hash(unsigned int x)
	{
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = ((x >> 16) ^ x) * 0x45d9f3b;
		x = (x >> 16) ^ x;
		return x;
	}
	void insertAtEnd(Machine* m)
	{
		Machine* current = head;
		if (head == NULL)
		{
			head = m;
			m->next = head;
		}
		else
		{
			while (current->next != head)
			{
				current = current->next;
			}
			current->next = m;
			m->next = head;
		}
	}

	DoubleList getFTP()
	{
		return ftp;
	}

	int getSerialNumber(string mID)
	{
		Machine* current = head;

		do
		{
			if (current->machineId == mID)
				break;

			current = current->next;

		} while (current != head);

		return current->serialNo;
	}

	void insertAtStart(Machine m)
	{
		Machine* current = head;
		if (head == NULL)
		{
			head = &m;
			m.next = head;
		}
		else
		{
			while (current->next != head)
			{
				current = current->next;
			}
			current->next = &m;
			m.next = head;
			head = &m;
		}
	}

	Machine* searchByKey(int k)
	{
		Machine* current = head;

		if (head == NULL)
		{
			return current;
		}
		else
		{
			while (current->next != head)
			{
				if (current->key == k)
				{
					cout << "Key Found\n";
					return current;
				}

				current = current->next;
			}
		}
	}

	void del()
	{
		Machine* current = head;

		if (head == NULL)
			cout << "List in Empty\n";
		else
		{
			while (current->next->next != head)
			{
				current = current->next;
			}
			current->next = head;
		}

	}

	void updateMachine(Machine* m)
	{
		Machine* ptr = searchByKey(m->key);
		//cout << ptr->machineNo << endl;
		if (ptr == NULL)
			cout << "Sorry! Machine doesn't Exits.\n";
		
		else
		{
			ptr->data = m->data;
			ptr->isPrimaryMachine = m->isPrimaryMachine;
			ptr->machineId = m->machineId;
		}
	}

	void updateMachine(int k, string d)
	{
		Machine* ptr = searchByKey(k);
		if (ptr == NULL)
			cout << "Sorry! Machine doesn't Exits.\n";
		else
			ptr->data = d;
		
	}

	void displayAVLTrees(string machineID)
	{
		Machine* current = head;

		do
		{
			if (current->machineId == machineID)
				break;

			current = current->next;

		} while (current != head);

		current->avl.inorder(current->avl.getRoot());
	}

	void insertInTree(DataPair d, string machineID)
	{
		//Obtain key from SHA 1 function in integer form 
		//Machine to store the data, Filename user wants
/*
		Machine* current = head;

		while (current->next != head)
		{
			if (current->isPrimaryMachine == true)
			{
				if (current->machineId == machineID)
				{
					current->avl.insert(d);
					cout << endl << "Value  inserted Successfully!" << endl;

					return;
				}
			}

			current = current->next;
		}


		return;

*/
		cout << "Entring the insert function" << endl;

		Machine* current = head;
		
		do
		{
			ftp.insert(current->serialNo);

			current = current->next;

		} while (current != head);
		
		//ftp.printAll();

		int s = head->serialNo;
		int c = 0;
		bool machineFlag = false;

		int k = d.key;

		d.key = hash(k);

		current = head;

		do
		{
			if (current->machineId == machineID)
			{
				cout << "Machine located" << endl;
				machineFlag = true;
				break;
			}

			current = current->next;
	
		} while (current != head);

		if (machineFlag == false)
		{
			cout << "Machine not found" << endl;
			return;
		}

		//int serialNum = current->serialNo;

		int* arr = new int[5];

		arr = ftp.succ(current->serialNo);

		//for (int i = 0; i < 5; i++)
			//cout << arr[i] << endl;
		
		srand(time(0));

		int idx = rand() % 5;

		int startingSerial = current->serialNo;

		do
		{
			if (current->isPrimaryMachine == true)
			{
				//cout << "Machine is Primary" << endl;

				if (current->serialNo == arr[idx])
				{
					current->avl.insert(d);
					cout << endl << "Value  inserted Successfully!" << endl;
					return;
				}
			}

			current = current->next;

		} while (current->serialNo != startingSerial);
		 

		cout << "Value Not inserted :/" << endl;
		
		return;
	}

	void search(int key, string machineID)
	{
		cout << "Going into search function" << endl;

		int s = head->serialNo;
		int c = 0;
		bool machineFlag = false;

		Machine* current = head;

		do
		{
			if (current->machineId == machineID)
			{
				cout << "Machine located" << endl;
				machineFlag = true;
				break;
			}

			current = current->next;

			c++;
			cout << c << endl;
			if (c > 100)
			{
				cout << "Value not found";
				return;
			}

		} while (current != head);

		if (machineFlag == false)
		{
			cout << "Machine not found" << endl;
			return;
		}

		int* arr = new int[5];

		cout << "To be succed" << endl;

		arr = ftp.succ(current->serialNo);

		//cout << "123";

		int startingSerial = current->serialNo;

		do
		{			
			for (int i = 0; i < 5; i++)
			{
				if (current->serialNo == arr[i])
				{
					if (current->avl.searchTree(key) == true)
					{
						cout << "Value is found the corresponding key: " << key << endl;
						return;
					}
				}
			}

			current = current->next;

		} while (current->serialNo != startingSerial);


		cout << "Key Not Found :/" << endl;

		return;

		/*
		cout << "Going into search function" << endl;

		//We will hash the key
		Machine* current = head;

		while (current->next != head)
		{
			if (current->machineId == startingMachineID)
			{
				cout << "Machine located" << endl;
				break;
			}

			current = current->next;
		}

		cout << "came out of the while loop" << endl;

		if (current->next == head)
		{
			cout << "Key not found" << endl;
			return;
		}

		cout << "To be succed" << endl;

		int serialNum = current->serialNo;

		int* arr = new int[5];

		arr = ftp->succ(serialNum);

		cout << "Succed" << endl;

		//current = head;
		int startingSerial = current->serialNo;
		Machine* start = current;

		do		
		{	
			cout << "Going in the last while" << endl;

			if (current->isPrimaryMachine == true)
			{
				cout << "Machine is Primary" << endl;

				for (int i = 0; i < 5; i++)
				{
					if (current->serialNo == arr[i])
					{
						if (current->avl.searchTree(key) == true)
						{
							cout << "Value is found the corresponding key: " << key << endl;
							return;
						}	
					}
				}
			}

			if (current->serialNo == startingSerial)
				break;

			current = current->next;

		} while (current != start);

		cout << "Value is not found." << endl;

		return;
		*/
	}

	void display()
	{
		if (head == NULL)
		{
			cout << "List is Empty!\n";
		}
		else
		{
			cout << "Circular Linked List : " << endl;

			Machine* temp = head;

			do
			{
				cout << " --> (Serial Num = " << temp->serialNo << ", Machine ID = " << temp->machineId << ", Key = " << temp->key << ", Data = " << temp->data << ", Is Machine = " << temp->isPrimaryMachine << ")\n";
				temp = temp->next;
			} while (temp != head);
		}
	}
};

