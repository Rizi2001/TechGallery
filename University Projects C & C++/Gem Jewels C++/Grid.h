#ifndef GRID_H_
#define GRID_H_
#include <iostream>
using namespace std;

class Grid
{
	int **ptr;
	int rows;
	int cols;
public:
	Grid();
	void setVal(int,int,int);
	int getVal(int, int);
	void display();
	int getRows();
	int getCols();
	~Grid();
};
#endif