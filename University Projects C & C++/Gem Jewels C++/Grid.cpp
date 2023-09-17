#include <iostream>
#include <time.h>
#include "Grid.h"
using namespace std;

Grid::Grid()
{
	srand(time(0));

	rows = cols = 8;

	ptr = new int* [rows];

	for (int i=0; i<rows; i++)
		ptr[i] = new int[cols];

	for (int i=0; i<rows; i++)
		for (int j = 0; j < cols; j++)
			ptr[i][j] = rand() % 6;

}

void Grid::setVal(int r,int c,int val)
{
	ptr[r][c] = val;
}

int Grid::getVal(int x, int y)
{
	return ptr[x][y];
}

void Grid::display()
{
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < cols; ++j)
			cout << ptr[i][j] << "	";
		cout << endl << endl << endl;
	}

	cout << endl<< endl << endl;
}

int Grid::getRows()
{
	return rows;
}

int Grid::getCols()
{
	return cols;
}

Grid::~Grid()
{
	for (int i = 0; i < rows; ++i)
		delete []ptr[i];

	delete []ptr;
}