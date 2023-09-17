#ifndef CITIZENSDB_H
#define CITIZENSDB_H
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//template <class T>

class CBID_Data
{
public:
	int cnic;
	string name;
	string fname;
	string gender;
	int age;
	string address;
	string nationality;
};

class CCID_Data
{
public:
	int cnic;
	string charge;
	string punishment;
	string fine;
};

class CCND_data
{
public:
	int cnic;
	int number;
	string network;
	string act_date;
	string deact_date;
	string status;
};

class Dat
{
public:
	int CNIC;
	CBID_Data cbid;
	CCID_Data ccid;
	CCND_data ccnd;

	Dat()
	{
		cbid.address = " ";
		cbid.age = 0;
		cbid.cnic = 0;
		cbid.fname = " ";
		cbid.gender = " ";
		cbid.name = " ";
		cbid.nationality = " ";

		ccid.charge = " ";
		ccid.cnic = 0;
		ccid.fine = " ";
		ccid.punishment = " ";

		ccnd.cnic = 0;
		ccnd.act_date = " ";
		ccnd.deact_date = " ";
		ccnd.network = " ";
		ccnd.number = 0;
		ccnd.status = " ";
	}
};

class DataPipeline_Node
{
public:
	DataPipeline_Node* next;
	Dat data;
};

class DataPipeline
{
	/*	A linkedlist based queue to implement databases
		Implement additional functions as per requirement
	*/
	//T* front;
	//T* back;
	DataPipeline_Node* front;
	DataPipeline_Node* back;
	
public:
	
	DataPipeline () {
		front = NULL;
		back = NULL;
	}

	DataPipeline_Node* get_front() {
		return front;
	}
	DataPipeline_Node* get_back() {
		return back;
	}

	DataPipeline_Node enqueue(DataPipeline_Node val) {
		
		DataPipeline_Node* temp = new DataPipeline_Node;

		temp->data.CNIC = val.data.CNIC;

		temp->data.cbid.cnic = val.data.cbid.cnic;
		temp->data.cbid.name = val.data.cbid.name;
		temp->data.cbid.fname = val.data.cbid.fname;
		temp->data.cbid.gender = val.data.cbid.gender;
		temp->data.cbid.age = val.data.cbid.age;
		temp->data.cbid.address = val.data.cbid.address;
		temp->data.cbid.nationality = val.data.cbid.nationality;

		temp->data.ccid.charge = val.data.ccid.charge;
		temp->data.ccid.cnic = val.data.ccid.cnic;
		temp->data.ccid.fine = val.data.ccid.fine;
		temp->data.ccid.punishment = val.data.ccid.punishment;

		temp->data.ccnd.act_date = val.data.ccnd.act_date;
		temp->data.ccnd.cnic = val.data.ccnd.cnic;
		temp->data.ccnd.deact_date = val.data.ccnd.deact_date;
		temp->data.ccnd.network = val.data.ccnd.network;
		temp->data.ccnd.number = val.data.ccnd.number;
		temp->data.ccnd.status = val.data.ccnd.status;
		
		temp->next = NULL;

		if (is_empty())
		{
			front = temp;
			back = temp;
			return *temp;
		}

		back->next = temp;
		back = temp;

		return *temp;
	}

	DataPipeline_Node dequeue(){

		DataPipeline_Node  temporary;
		
		temporary.next = NULL;

		if (is_empty())
			return temporary;

		DataPipeline_Node* temp = front;

		front = front->next;

		if (front == NULL)
			back = NULL;

		return *temp;
	}

	bool is_empty() {
		if (front == NULL)
			return true;

		return false;
	}

	string search_cnic(int cnic)
	{
		DataPipeline_Node* current;
		current = front;

		while (current != NULL)
		{
			if (current->data.CNIC == cnic)
				break;

			current = current->next;
		}
		
		if(current->data.ccid.cnic==0)
			return current->data.cbid.name + " " + current->data.cbid.fname + " " + current->data.cbid.gender + " " + to_string(current->data.cbid.age) + " " + current->data.cbid.address + " " + current->data.cbid.nationality + " " + to_string(current->data.ccnd.number) + " " + current->data.ccnd.network + " " + current->data.ccnd.act_date + " " + current->data.ccnd.deact_date + " " + current->data.ccnd.status;

		if(current->data.ccnd.cnic==0)
			return current->data.cbid.name + " " + current->data.cbid.fname + " " + current->data.cbid.gender + " " + to_string(current->data.cbid.age) + " " + current->data.cbid.address + " " + current->data.cbid.nationality + " " + current->data.ccid.charge + " " + current->data.ccid.punishment + " " + current->data.ccid.fine;

		string out = current->data.cbid.name + " " + current->data.cbid.fname + " " + current->data.cbid.gender + " " + to_string(current->data.cbid.age) + " " + current->data.cbid.address + " " + current->data.cbid.nationality + " " + current->data.ccid.charge + " " + current->data.ccid.punishment + " " + current->data.ccid.fine + " " + to_string(current->data.ccnd.number) + " " + current->data.ccnd.network + " " + current->data.ccnd.act_date + " " + current->data.ccnd.deact_date + " " + current->data.ccnd.status;
		return out;
	}

	bool update_CBID_Name(string n, int cnic)
	{
		DataPipeline_Node* current;
		current = front;

		while (current != NULL)
		{
			if (current->data.CNIC == cnic)
				break;

			current = current->next;
		}
		if (current == NULL)
			return false;

		current->data.cbid.name = n;

		return true;

	}

	bool update_CBID_FName(string n, int cnic)
	{
		DataPipeline_Node* current;
		current = front;

		while (current != NULL)
		{
			if (current->data.CNIC == cnic)
				break;

			current = current->next;
		}
		if (current == NULL)
			return false;

		current->data.cbid.fname = n;

		return true;
	}

	bool update_CBID_Add(string n, int cnic)
	{
		DataPipeline_Node* current;
		current = front;

		while (current != NULL)
		{
			if (current->data.CNIC == cnic)
				break;

			current = current->next;
		}
		if (current == NULL)
			return false;

		current->data.cbid.address = n;

		return true;
	}

	bool update_CBID_Nat(string n, int cnic)
	{
		DataPipeline_Node* current;
		current = front;

		while (current != NULL)
		{
			if (current->data.CNIC == cnic)
				break;

			current = current->next;
		}

		if (current == NULL)
			return false;

		current->data.cbid.nationality = n;

		return true;
	}

	bool update_crime(int cnic, string charges, string punishment, string fine)
	{
		DataPipeline_Node* current;
		current = front;

		while (current != NULL)
		{
			if (current->data.CNIC == cnic)
				break;

			current = current->next;
		}

		if (current == NULL)
			return false;

		current->data.ccid.charge = charges;
		current->data.ccid.punishment = punishment;
		current->data.ccid.fine = fine;

		return true;
	}

	bool add_crime(int cnic, string charges, string punishment, string fine)
	{
		DataPipeline_Node* current;
		current = front;

		while (current != NULL)
		{
			if (current->data.CNIC == cnic)
				break;

			current = current->next;
		}

		if (current == NULL)
			return false;

		current->data.ccid.charge = charges;
		current->data.ccid.punishment = punishment;
		current->data.ccid.fine = fine;

		return true;
	}

	int add_number(int cnic, int num)
	{
		DataPipeline_Node* current;
		current = front;
		int counter = 1;

		while (current != NULL)
		{
			if (current->data.CNIC == cnic)
			{
				if (current->data.ccnd.number == num)
					counter++;
			}

			current = current->next;
		}

		if (current == NULL)
			return 0;

		return counter;
	}

	int check_registered(int cnic)
	{
		DataPipeline_Node* current;
		current = front;
		int counter = 0;

		while (current != NULL)
		{
			if (current->data.CNIC == cnic)
			{
				if (current->data.ccnd.number)
					counter++;
			}

			current = current->next;
		}

		if (current == NULL)
			return 0;

		return counter;
	}

	void display_Pipeline_Nodes()
	{
		DataPipeline_Node* current;

		current = front;

		while (current != NULL)
		{
			cout << endl;
			cout << "CNIC: " << current->data.CNIC << endl;

			cout << current->data.cbid.cnic << " ";
			cout << current->data.cbid.name << " ";
			cout << current->data.cbid.fname << " ";
			cout << current->data.cbid.gender << " ";
			cout << current->data.cbid.age << " ";
			cout << current->data.cbid.address << " ";
			cout << current->data.cbid.nationality << endl;

			cout << current->data.ccid.cnic << " ";
			cout << current->data.ccid.charge << " ";
			cout << current->data.ccid.punishment << " ";
			cout << current->data.ccid.fine << endl;

			cout << current->data.ccnd.cnic << " ";
			cout << current->data.ccnd.network << " ";
			cout << current->data.ccnd.number << " ";
			cout << current->data.ccnd.act_date << " ";
			cout << current->data.ccnd.deact_date << " ";
			cout << current->data.ccnd.status << endl;

			current = current->next;
		}
	}
};

/*
class AD {
	// Implement a stack for your Alien Database operations 
public:
	AD() {

	}

	void push_roll(int value) {
		
	}

	T& top() {
		
		return ADTop;
	}

	void pop() {

	}

	bool is_empty() {
		return true;
	}

	void empty() {
		while (!is_empty()) {
			pop();
		}
	}
};
*/


struct CBID_NODE {
	CBID_NODE* next;
	CBID_NODE *previous;
	//CBID_Data data;
};


struct CCID_NODE {
	CCID_NODE* first;
	CCID_NODE* next;
	CCID_NODE* previous;
	//CCID_Data data;
};



struct CCND_NODE {
	CCND_NODE* next;
	CCND_NODE* previous;
	//CCND_data data;
};

class Database
{
    
	//CBID_NODE CBID;
	//CCID_NODE CCID;
	//CCND_NODE CCND;
public:
	DataPipeline dataPipeline;
    
	Database(string filename, string filename1, string filename2) 
	{	
		//filename = CBID
		Dat temp;
		
		ifstream file1(filename);
		
		int i = 0, c = 0;
		
		string text;
		DataPipeline_Node * arr;

		arr = new DataPipeline_Node[50];

		while (file1 >> text)	//CBID.txt
		{
			if (c > 7)
			{
				c = 0;
				i++;
			}

			if (c == 0)
			{
				arr[i].data.cbid.cnic = stoi(text);
				arr[i].data.CNIC = stoi(text);
			}
				
			if (c == 1)
				arr[i].data.cbid.name = text;
			if (c == 2)
				arr[i].data.cbid.fname = text;
			if (c == 3)
				arr[i].data.cbid.gender = text;
			if (c == 4)
				arr[i].data.cbid.age = stoi(text);
			if (c == 5)
				arr[i].data.cbid.address = text + " ";
			if (c == 6)
				arr[i].data.cbid.address += text;
			if (c == 7)
				arr[i].data.cbid.nationality = text;

			c++;
		}

		ifstream file2(filename1);

		int j = 0;
		i = c = 0;
		

		while (file2 >> text)		//filename1 is CCID.txt
		{
			if (c > 6)
				c = 0;

			if (c == 0)
			{
				for (j = 0; j < 50; j++)
				{
					if (stoi(text) == arr[j].data.CNIC)
						break;
					else
						continue;
				}
			}

			if (c == 0)
			{
				arr[j].data.ccid.cnic = stoi(text);
				arr[j].data.CNIC = stoi(text);
			}

			if (c == 1)
				arr[j].data.ccid.charge = text;
			if (c == 2)
				arr[j].data.ccid.punishment = text + " ";
			if (c == 3)
				arr[j].data.ccid.punishment += text + " ";
			if (c == 4)
				arr[j].data.ccid.punishment += text + " ";
			if (c == 5)
				arr[j].data.ccid.punishment += text;
			if (c == 6)
				arr[j].data.ccid.fine = text;

			c++;
		}

		c = 0;

		ifstream file3(filename2);

		while (file3 >> text)	//filename2 is CCND.txt
		{
			if (c > 5)
				c = 0;

			if (c == 0)
			{
				for (j = 0; j < 50; j++)
				{
					if (stoi(text) == arr[j].data.CNIC)
						break;
					else
						continue;
				}
			}

			if (c == 0)
			{
				arr[j].data.ccnd.cnic = stoi(text);
				arr[j].data.CNIC = stoi(text);
			}

			if (c == 1)
				arr[j].data.ccnd.number = stoi(text);
			if (c == 2)
				arr[j].data.ccnd.network = text;
			if (c == 3)
				arr[j].data.ccnd.act_date = text;
			if (c == 4)
				arr[j].data.ccnd.deact_date = text;
			if (c == 5)
				arr[j].data.ccnd.status = text;

			c++;
		}
		
		for (int k = 0; k < 50; k++)
			dataPipeline.enqueue(arr[k]);
	}
    /*Return a string in following format "Name FName Gender Address Nationality Crimes(if any) Charges punishment fine number network activation_date deactivation_date status"
     Refer to test cases for further clerification*/
	
	string CBID_Search_by_CNIC(int cnic) 
	{	
		return dataPipeline.search_cnic(cnic);
	}
	
	string CCID_Search_by_CNIC(int cnic) {

        return dataPipeline.search_cnic(cnic);
    }
	string CCND_Search_by_CNIC(int cnic) {
        
		return dataPipeline.search_cnic(cnic);
    }
	
	bool updateCBIDName(string Name, int cnic) {
		//update and return true when cnic found else return false

		return dataPipeline.update_CBID_Name(Name, cnic);
	}

	bool updateCBIDFName(string Father_Name, int cnic) {
		//update and return true when cnic found else return false
		return dataPipeline.update_CBID_FName(Father_Name,cnic);
	}

	bool updateCBIDAddress(string Address, int cnic) {
		//update and return true when cnic found else return false
		return dataPipeline.update_CBID_Add(Address, cnic);
	}

	bool updateCBIDNationality(string Nationality, int cnic) {
		//update and return true when cnic found else return false
		return dataPipeline.update_CBID_Nat(Nationality, cnic);
	}
	
    bool addCrime(int cnic, string charges, string punishment, string fine){
        //update and return true when crime found else return false
		return dataPipeline.add_crime(cnic, charges, punishment, fine);
    }

	bool updateCrime(int cnic, string charges, string punishment, string fine) {
		//update and return true when crime found else return false
		return dataPipeline.update_crime(cnic, charges, punishment, fine);
	}

	bool deleteCrime(int cnic, string charges, string punishment, string fine) {
		//update and return true when crime found else return false

		return false;
	}
	
	int addNumber(int cnic, int number) {
		int num = dataPipeline.add_number(cnic, number);
		//return number of cell-numbers registered on given cnic after adding this number
		
		return num;
	}

    int checkRegistred_No(int cnic){
		int num = dataPipeline.check_registered(cnic);

        //return number of cell-numbers registered on given cnic
        return num;
    }
	/*
     CCND_NODE& swap(T cnic, T cnic1, T number, T number1){
        
        return CCND;
    }	

AD& declareAlien(CBID) {
//For Implementation of this function, Refer to CBID point 'iv', CCID point 'vi' and CCND point 'vii'. Also,
write test-cases for this function yourself
		return top;
	}

bool verifyAlienDBUpdate(T cnic, AD, CBID){
		//Verify that given CNIC is moved from CBID to AD, Also add test-case for this function yourself
	}

    int printcount(){
        int total;
        //Print count of cell phone numbers registered on each network. For example: (Telenor= 10, Jazz= 5, Ufone= 8, Zong= 9, Total= 32)
         Return total
        return total;
    }
    void Display_AD(){
        //Display data as instructed in point (xiv) of PDF
    }

	~Database() {
		// deallocate and cleanup 
	}
*/
};

#endif
