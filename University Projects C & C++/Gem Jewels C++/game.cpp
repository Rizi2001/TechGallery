//============================================================================
// Name        : .cpp
// Author      : Sibt ul Hussain
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Centipede...
//============================================================================

#ifndef CENTIPEDE_CPP_
#define CENTIPEDE_CPP_
#include "util.h"
#include "GameHandler.h"
#include <iostream>
#include<string>
#include<cmath> // for basic math functions such as cos, sin, sqrt

using namespace std;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */
GameHandler g;

void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	//glClearColor(0.0f, 0.0f, 0.0f, 1.0f); 
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors
/*	//Fire Gun
	DrawSquare( 400 , 20 ,40,colors[RED]); 
	//Mushroom
	DrawSquare( 250 , 250 ,20,colors[GREEN]); 
*/	//Display Score
	//DrawString( 300, 800, "Score=0", colors[MISTY_ROSE]);

	if(g.menu==false)
	{
		//glutCreateWindow("OOP Project"); // set the title of our game window
		//SetCanvasSize(width, height); // set the number of pixels...

		g.populateGrid();

		//DrawString( 240, 800, "WELCOME TO GAME!!!", colors[MISTY_ROSE]);

		string intro = "Hi ";
		intro = intro + (g.p1.getName()) + ". Just swipe and Enjoy.";

		DrawString( 200, 730, intro, colors[MISTY_ROSE]);

	/*	//Spider
		DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
		// Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	*/

		//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	//	DrawLine( 550 , 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	
		DrawLine(50		,50  	,50		,700 	,10 , colors[MAGENTA]);
		DrawLine(570 	,50 	,570 	,700  	,10 , colors[MAGENTA]);
		
		DrawLine(50		,700 	,570 	,700 	,10 , colors[MAGENTA]);
		DrawLine(570 	,50  	,50  	,50  	,10 , colors[MAGENTA]);

		//DrawCircle(50,750,10,colors[RED]);//DrawCircle(50,670,10,colors[RED]);
		//DrawCircle(90,750,10,colors[RED]);
	//	DrawRoundRect(500,200,50,100,colors[DARK_SEA_GREEN],70);
	//	DrawRoundRect(100,200,100,50,colors[DARK_OLIVE_GREEN],20);
	//	DrawRoundRect(100,100,50,100,colors[DARK_OLIVE_GREEN],30);
	//	DrawRoundRect(200,100,100,50,colors[LIME_GREEN],40);
	//	DrawRoundRect(350,100,100,50,colors[LIME_GREEN],20);
		
	//	DrawCircle(125,85,10,colors[WHITE]);

	}
	else
	{
		g.showMenu();		
	}

	glutSwapBuffers(); // do not modify this line..
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int x, int y) {
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...

	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {

	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {

	}

	else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {

	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();

}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	
	//char name[20] = {'\0'};
	//int i=0;

	//if(key)
	//{
	//	name[i++] = key;
	//	cout << name[i];	
	//}
	
	//if(name[i-1] == '\n')
	//	g.p1.setName(name);

	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	//if (key == 'b' || key == 'B') //Key for placing the bomb
	//{
		
	//}
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here

	// once again we tell the library to call our Timer function after next 1000/FPS
	glutTimerFunc(100.0, Timer, 0);
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {
	//cout << x << " " << y << endl;
	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	//int row=0,col=0;

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
	{
		//g.g1.display();

		if(state == 0)
		{
			g.setxP(x);
			g.setyP(y);
			g.setState(0);

			//cout << "Pressed x: " << x << "		y: " << y << endl; 
		}

		if(state==1)
		{
			g.setxL(x);
			g.setyL(y);
			g.setState(1);

			g.setMenuX(x);
			g.setMenuY(y);

			g.executeGame();
			//cout << "Released x: " << x << "	y: " << y << endl;
		}

		//g.g1.display();

	}
	else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
	{
		//cout << "Right Button Pressed" << " " << state << " = " << button << endl;
	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
int main(int argc, char*argv[])
{
	int width = 700, height = 840; 

	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("OOP Project"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	//glutCreateWindow("Menu");
	 //Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	//glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	glutTimerFunc(100.0, Timer, 0);

	glutMouseFunc(MouseClicked);
	
	//glutPassiveMotionFunc(MouseMoved); // Mouse
	//glutMotionFunc(MousePressedAndMoved); // Mouse

/*	int** slot = new int*[8];
	for(int i = 0; i < 64; i++)
	{
		slot[i] = new int[8];
	}*/

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */


