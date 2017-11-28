#pragma once
#include "Bomb.h"
#include <gl\GLU.h>
#include <gl\GL.h>
#include <vector>
#include <gl\glut.h>

using namespace std;

class Tank
{
public:
	//property
	int hp;
	//vector<Bomb> bombs;
	double x, z;
	int angle;
	double width, height, length;


public:
	Tank();
	~Tank();

	/*
	right: 0
	left: 1
	*/
	void moveX(int direction);

	/*
	forward: 0
	back: 1
	*/
	void moveZ(int direction);

	/*draw tank body*/
	void drawSelf();

	/*public draw a cuboid*/
	void DrawCuboid(double width, double height, double length, float red, float green, float blue);

	void emission(double angle);
};

