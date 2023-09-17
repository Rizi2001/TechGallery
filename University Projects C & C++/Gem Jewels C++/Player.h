#ifndef PLAYER_H_
#define PLAYER_H_
#include <iostream>
#include "FileHandler.h"
using namespace std;

class Player
{
	string name;
	int score;
	string level;
	int highScore;
	FileHandler file;
public:
	Player();
	void setName(string);
	string getName();
	void setScore(int);
	int getScore();
	void setLevel(string);
	string getLevel();
	void setHighscore(int);
	int getHighscore();
	void storePlayerInformation();	
	void storeScore();
	void displayPlayerInfo();
	//~Player();
};
#endif