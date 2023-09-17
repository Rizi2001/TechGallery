#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_
#include <iostream>
#include <fstream>
#include <iostream>
using namespace std;

class FileHandler
{
	ofstream out;
	ifstream in;	
public:
	FileHandler();
	void storePlayerInfo(string, int);
	void storeScore(int);
	void displayInfo();
	//~FileHandler();
};
#endif