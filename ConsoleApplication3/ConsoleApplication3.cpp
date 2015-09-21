// ConsoleApplication3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <string>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <sstream> 
#include <math.h> 
#include <gl\gl.h>
#include <gl\glu.h>
#include "GL/freeglut.h"
#pragma comment(lib, "OpenGL32.lib")

// window size
const int width = 800;
const int height = 640;
const int interval = 1000 / 60;

// paddle sizes
const int paddleWidth = 10;
const int paddleHeight = 80;
const int speed = 7;


// left paddle position
float leftX = 10.0f;
float leftY = 50.0f;

//right paddle position
float rightX =  width - paddleWidth - 10;
float rightY = 50.0f;

// ball
float ballPosX = width / 2;
float ballPosY = height / 2;
float ballDirX = -1.0f;
float ballDirY = 0.0f;
const int ballSize = 15;
const int ballSpeed = 2;

// Makes the game 2D, might eventually make the game 3D
void enable2D(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f, width, 0.0f, height, 0.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

// Draw the paddles
void drawPaddle(float x, float y, float width, float height) {
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

// Draws everything and keeps it legit
void draw() {
	// clear (has to be done at the beginning)
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// paddles
	drawPaddle(leftX, leftY, paddleWidth, paddleHeight);
	drawPaddle(rightX, rightY, paddleWidth, paddleHeight);

	// ball
	drawPaddle(ballPosX - ballSize / 2, ballPosY- ballSize / 2, ballSize, ballSize);

	// swap buffers (has to be done at the end)
	glutSwapBuffers();
}

// ball movement
void ballMovement()
{
	ballPosX += ballDirX * ballSpeed;
	ballPosY += ballDirY * ballSpeed;

	// hit by left paddle
	if (ballPosX < leftX + width && ballPosX > leftX && ballPosY < leftY + height && ballPosY> leftY)
	{
		float temp = ((ballPosX - leftY) / paddleHeight) - 0.5f;
		ballDirX = fabs(ballDirX); // force it to be positive
		ballDirY = temp;

	}
	// hit by right paddle
	if (ballPosX < rightX + width && ballPosX > rightX && ballPosY < rightY + height && ballPosY> rightY)
	{
		float temp = ((ballPosX - leftY) / paddleHeight) - 0.5f;
		ballDirX = fabs(ballDirX); // force it to be positive
		ballDirY = temp;

	}
	// hits left wall
	if (ballPosX < 0) {
		ballPosX = width / 2;
		ballPosY = height / 2;
		ballDirX = fabs(ballDirX); // force it to be positive
		ballDirY = 0;
	}
	// hits right wall
	if (ballPosX > width) {
		ballPosX = width / 2;
		ballPosY = height / 2;
		ballDirX= -fabs(ballDirX); // force it to be negative
		ballDirY = 0;
	}
	// hits to wall
	if (ballPosY > height) {
		ballDirY = -fabs(ballDirY); // force it to be negative
	}
	// hits bottom wall
	if (ballPosY < 0) {
		ballDirY = fabs(ballDirY); // force it to be positive
	}
}

void controls()
{

	if (GetAsyncKeyState('W'))
	{
		leftY += speed;

	}

	if (GetAsyncKeyState('S'))
	{
		leftY -= speed;

	}

	if (GetAsyncKeyState('O'))
	{
		rightY += speed;
	}

	if (GetAsyncKeyState('L'))
	{
		rightY -= speed;
	}

}

// Keeps everything updated
void update(int value) {

	controls();
	ballMovement();
	// Call update
	glutTimerFunc(interval, update, 0);

	// Redisplay frame
	glutPostRedisplay();
}


int _tmain(int argc, char** argv) {
	// opengl with glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutCreateWindow("Pong");

	// Register callback functions   
	glutDisplayFunc(draw);
	glutTimerFunc(interval, update, 0);

	// sets up 2d mode and draws to white
	enable2D(width, height);
	glColor3f(1.0f, 1.0f, 1.0f);

	// starts the whole thing
	glutMainLoop();
	return 0;
}