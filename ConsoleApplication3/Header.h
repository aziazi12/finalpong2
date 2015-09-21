#pragma once
#include "ConsoleApplication3.cpp"

struct Paddle
{
	// paddle sizes
	int paddleWidth = 10;
	int paddleHeight = 80;
	int speed = 7;

	

};

struct Ball
{
	// ball
	float posX = width / 2;
	float posY = height / 2;
	float dirX = -1.0f;
	float dirY = 0.0f;
	int size = 15;
	int speed = 2;

};