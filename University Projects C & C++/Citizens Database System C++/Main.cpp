#include <iostream>
#include <string>
#include <fstream>
#include"CitizensDatabase.h"
using namespace std;

int main(void)
{
	Database d1("CBID.txt", "CCID.txt", "CCND.txt");

	//d1.dataPipeline.display_Pipeline_Nodes();
	//d1.CBID_Search_by_CNIC(5960);
	//cout << d1.CBID_Search_by_CNIC(3740);
	//cout << d1.CCND_Search_by_CNIC(6287);
	
	//cout << d1.updateCBIDAddress("12 Ann Street", 8372);
	//cout << d1.updateCBIDAddress("21 Downing Street",9639);

	//cout << d1.updateCBIDFName("Kevin", 9177);
	//cout << d1.updateCBIDFName("Steve", 1234);

	//cout << d1.addCrime(7564, "Robbery", "2 years in prison", "1000");
	//cout << d1.updateCrime(5960, "murder", "20 years in prison", "10000");

	return 0;
}