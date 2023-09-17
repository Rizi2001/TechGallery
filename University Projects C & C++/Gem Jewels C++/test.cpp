#include <iostream>
#include "Player.cpp"
#include "FileHandler.cpp"
#include "Grid.cpp"
#include "GameHandler.cpp"
using namespace std;

int main(int argc, char const *argv[])
{
	/*FileHandler f1;
	f1.storeInfo("High level", 240);
	f1.displayInfo();*/

	/*Player p1;
	p1.setName("Rizwan");
	p1.setScore(443);
	p1.storeInformation("Next level", 1000);
	p1.displayPlayerInfo();*/

	//Grid g1;
	//g1.display();	

	GameHandler g;
	g.g1.display();

	return 0;
}