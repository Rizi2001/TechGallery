#include <iostream>
#include "Grid.h"
#include "Player.h"
#include "util.h"
using namespace std;

class GameHandler
{	
	int state;	//State of Mouse Clicked
	int xP;	//pressed coordinates
	int yP;	
	int xL;
	int yL;	//coordinates when mouse is released
	int menuX;
	int menuY;	//coordinates for the menu buttons
public:
	Player p1;
	Grid g1;
	bool menu;
	GameHandler();
	void setState(int);
	void setxP(int);
	void setxL(int);
	void setyP(int);
	void setyL(int);
	void setMenuX(int);
	void setMenuY(int);
	void showMenu();
	void populateGrid();
	void takePlayerInfo();
	void swapGem(int,int,int);
	void checkGrid(bool);
	void executeGame();
	void saveInfo();
	~GameHandler();
};