#pragma once
#include<iostream>
using namespace std;

class DataPair
{
public:
	int key;
	string value;

	DataPair(int k = 0, string val = " ")
	{
		key = k;
		value = val;
	}
};
