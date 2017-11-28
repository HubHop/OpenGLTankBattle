#pragma once
#include <vector>
#include "Tank.h"

class Bomb
{
public:
	//property
	double x, y, z;
	int hurt;
	int speed;
	int direction;
	int id;

public:
	//Bomb();
	Bomb();
	~Bomb();
	void drawSelf();
	void fly(float speed);
};

