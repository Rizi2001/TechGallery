#include <iostream>
#include <fstream>
#include <iostream>
#include "FileHandler.h"
using namespace std;

FileHandler::FileHandler()
{
	
}

void FileHandler::storePlayerInfo(string n, int h)
{
	out.open("PlayerInfo.txt",ios::app|ios::out);
	out << "The name of Player is : " << n << endl;
	out << "The highest score of Player is: " << h << endl;
	out.close();
}

void FileHandler::storeScore(int s)
{
	out.open("PlayerInfo.txt",ios::app|ios::out);
	//out << "The current level of Player is: " << l << endl;
	out << "The score of the Player right now is: "<< s << endl;
	out.close();
}

void FileHandler::displayInfo()
{
	in.open("PlayerInfo.txt");
	string text;

	while (getline (in, text)) 
    	cout << text;

    in.close();
}