#include <iostream>
#include "GameHandler.h"
using namespace std;

GameHandler::GameHandler()
{
	menu = true;
}

void GameHandler::setState(int s)
{
	state=s;
}

void GameHandler::setxP(int x)
{
	xP=x;
}

void GameHandler::setxL(int c)
{
	xL=c;
}

void GameHandler::setyP(int y)
{
	yP=y;
}

void GameHandler::setyL(int c)
{
	yL=c;
}

void GameHandler::setMenuX(int x)
{
	menuX=x;
	
}

void GameHandler::setMenuY(int y)
{
	menuY =y;
}

void GameHandler::showMenu()
{
	DrawSquare( 0 , 0 ,800,colors[MAGENTA]);
	DrawString( 170, 800, "WELCOME TO THE GAME MENU!!!", colors[MISTY_ROSE]);

	DrawRoundRect(180,700,360,70,colors[LIME_GREEN],20);
	DrawString( 245, 720, "Double click here to Play!", colors[BLACK]);

	DrawString( 550, 660, "Select Level:", colors[BLACK]);
	DrawSquare(570,550, 100, colors[BLUE]);
	DrawString( 570, 520, "Easy", colors[BLACK]);	

	DrawSquare(570,400, 100, colors[BLUE]);
	DrawString( 570,370, "Hard", colors[BLACK]);

	DrawSquare(570,200, 100, colors[GRAY]);
	DrawString( 570,170, "Settings", colors[BLACK]);

	DrawString( 40,450, "Type your name and then press enter.", colors[BLACK]);

	cout << "MenuX: " << menuX << " menuY: " << menuY << endl;
	if((menuX > 180 && menuX<540) && (menuY <100 && menuY>55))
	{
		cout << "MenuX: " << menuX << " menuY: " << menuY << endl;
		menu = false;			
	}
}

void GameHandler::populateGrid()
{
	int sqX = 75, sqY=75;
	int crclX = 100, crclY=100;
	int v1x=75, v1y=75, v2x=100, v2y=125, v3x=125, v3y=75;
	int tpp=60;		
	int num=60;		

	int r;

	for (int j = 0; j < 8; j++)
	{	
		for (int i = 0; i < 8; i++)
		{
			r = g1.getVal(j, i);

			if (sqX<650 && sqY<650 && r==0 )
				DrawSquare(sqX , sqY ,50,colors[GRAY]);
			
			if (sqX<650 && sqY<650 && r==1)
				DrawSquare(sqX , sqY ,50,colors[GOLD]);

			if (crclX<650 && crclY<650 && r ==2)		//crclX<650 && crclY<650
				DrawCircle(crclX,crclY,25,colors[DARK_TURQUOISE]);

			if (crclX<650 && crclY<650 && r ==3)		//crclX<650 && crclY<650
				DrawCircle(crclX,crclY,25,colors[SIENNA]);
			
			if (v3x<550 && v3y<650 && r ==4)
				DrawTriangle(v1x, v1y, v2x, v2y, v3x, v3y, colors[MAGENTA]);

			if (v3x<550 && v3y<650 && r ==5)
				DrawTriangle(v1x, v1y, v2x, v2y, v3x, v3y, colors[DARK_SLATE_BLUE]);
			
			sqX+=num;
			crclX+=60;
			v1x+=tpp;
			v2x+=tpp;
			v3x+=tpp;
		}

		sqX = 75, sqY+=75;
	 	crclX = 100, crclY+=75;
	 	v1x=75, v1y+=75, v2x=100, v2y+=75, v3x=125, v3y+=75;	
	}		
}

void GameHandler::takePlayerInfo()									//****************************************************//
{
	//displays to enter player's name and input's name
	string name;
	p1.setName(name);
	//int hScore;
	//p1.setHighscore(hScore);

	p1.storePlayerInformation();
}

void GameHandler::swapGem(int direction, int row, int col)	//1 is up, 2 down, 3 right, 4 left
{	
	if(direction==1)		//up
	{
		int v = g1.getVal(row,col);
		int g = g1.getVal(row-1,col);

		g1.setVal(row-1,col,v);
		g1.setVal(row,col,g);
	}
	else if(direction==2)	//down
	{
		int v = g1.getVal(row,col);
		int g = g1.getVal(row+1,col);

		g1.setVal(row+1,col,v);
		g1.setVal(row,col,g);
	}
	else if(direction==3)	//right
	{
		int v = g1.getVal(row,col);
		int g = g1.getVal(row,col+1);

		g1.setVal(row,col+1,v);
		g1.setVal(row,col,g);
	}
	else					//left
	{
		int v = g1.getVal(row,col);
		int g = g1.getVal(row,col-1);

		g1.setVal(row,col-1,v);
		g1.setVal(row,col,g);
	}					
}

void GameHandler::checkGrid(bool isFirst)	
{	

	//(i+1>7) || (i+2>7) || 
	for (int i=0; i<8; i++)
	{
		for (int j=0; j<8; j++)
		{
			// column wise

			if(!((j+1>=7) || (j+2>=7)))
			{
				cout << "First if i:" << i << " j:" << j << endl;
				if ((i==6 || i==7))
				{
					cout << "Second if i:" << i << " j:" << j << endl;
					if((g1.getVal(i,j) == g1.getVal(i,j+1)) && (g1.getVal(i,j+1) == g1.getVal(i,j+2)))
					{
						cout << "Third if i:" << i << " j:" << j << endl;
						g1.setVal(i,j,10);

						g1.setVal(i,j+1,10);
						g1.setVal(i,j+2,10);

						p1.setScore(10);
					}
					else
					{
						if (!isFirst)
						{
							cout << "Setting score -5" << endl;
							//p1.setScore(-5);
						}
					}	
				}
				else
				{
					cout << "First else i:" << i << " j:" << j << endl;

					if (!(j+3>7))
					{
						cout << "Bonus if i:" << i << " j:" << j << endl;
						if(g1.getVal(i,j) == g1.getVal(i,j+3))
						{
							g1.setVal(i,j+3,10);
							//cout << endl << "20 value set" << endl;
							p1.setScore(20);	//Bonus points

							cout << "Bonus" << endl;
							//cout << "20 score in else condition col wise" << endl;
						}

					}
					

					if((g1.getVal(i,j) == g1.getVal(i,j+1)) && (g1.getVal(i,j+1) == g1.getVal(i,j+2)))
					{
						cout << "4th if i:" << i << " j:" << j << endl;
						g1.setVal(i,j,10);

						g1.setVal(i,j+1,10);
						g1.setVal(i,j+2,10);

						p1.setScore(10);
					}
					else
					{
						if (!isFirst)
						{
							cout << "Setting score -5" << endl;
							//p1.setScore(-5);
						}
					}	
				}

				
			}
			else // if (j == 6 && j == 7)
			{
				cout << "2nd else i:" << i << " j:" << j << endl;
				if(!((i+1>= 7) || (i+2 >=7)))
				{
					cout << "5th if i:" << i << " j:" << j << endl;
					if((g1.getVal(i,j) == g1.getVal(i+1,j)) && (g1.getVal(i+1,j) == g1.getVal(i+2,j)))
					{
						cout << "6th if i:" << i << " j:" << j << endl;
						g1.setVal(i,j,10);	//10 at the grid means to delete gem
						g1.setVal(i+1,j,10);
						g1.setVal(i+2,j,10);

						p1.setScore(10);
					}
					else
					{
						if (!isFirst)
						{
							cout << "Setting score -5" << endl;
							//p1.setScore(-5);
						}
					}		
				}
				else
				{
					cout << "3rd else i:" << i << " j:" << j << endl;
					// do nothing
				}
					
			}
		}
	}

	cout << "Current score: "<< p1.getScore() << endl;

	//Filling the deleted gems' space
	srand(time(0));
	int n;

	for (int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			n = rand()%6;

			if(g1.getVal(i,j) == 10)
				g1.setVal(i,j,n);
		}
	}
}

void GameHandler::executeGame()
{
	int row=0,col=0;

	checkGrid(true);

	if((xP>70 && xP<530) && (yP>140 && yP<560))
	{
		if((yP%8 <= 6) && (xP%8 <= 4))
		{	
			row=(yP/55)-3;
			row=(8-row)-2;
			col=(xP/60)-1;
			
			if((xL-xP) > 45)	//xP<xL
			{
				if(state==1)
				{
					swapGem(3,row,col);
					checkGrid(false);
					cout << "Going right  " << endl ;//<< xL-xP << endl << endl;	
				}	
			}
				
			else if((xP-xL) > 45)	//xP>xL
			{
				if(state==1)
				{
					swapGem(4,row,col);
					checkGrid(false);
					cout << "Going left  " << endl ;//<< xP-xL << endl << endl;
				}
			}

			else if ((yL-yP) > 45)	//yL>yP
			{
				if(state==1)
				{
					swapGem(1,row,col);
					checkGrid(false);
					cout << "Going down  " << endl ;//<< yL-yP << endl << endl;
				}
			}

			else if ((yP-yL) > 45)	//yP>yL
			{
				if(state==1)
				{
					swapGem(2,row,col);
					checkGrid(false);
					cout << "Going up  " << endl ;//<< yP-yL << endl << endl;
				}
			}

			p1.storeScore();
		}
	}
}

void GameHandler::saveInfo()
{

}

GameHandler::~GameHandler()
{
	
}
