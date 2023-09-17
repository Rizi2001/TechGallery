#include <iostream>
#include "Player.h"
using namespace std;

Player::Player()
{
	name = "Rizwan";
	score = 0;
}

void Player::setName(string n)
{
	name = n;
}

string Player::getName()
{
	return name;
}

void Player::setScore(int s)
{
	score += s;
}

void Player::setLevel(string l)
{
	level = l;
}

string Player::getLevel()
{
	return level;
}

void Player::setHighscore(int h)
{
	highScore = h;
}

int Player::getHighscore()
{
	return highScore;
}

int Player::getScore()
{
	return score;
}

void Player::storePlayerInformation()
{
	file.storePlayerInfo(name, highScore);
}

void Player::storeScore()
{
	file.storeScore(score);
}

void Player::displayPlayerInfo()
{
	file.displayInfo();
}


	