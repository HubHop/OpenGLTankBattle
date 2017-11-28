#include "stdafx.h"
#include "Tank.h"

#define TankSpeed 1


Tank::Tank()
{
	this->x = 0;
	this->z = 0;
	this->width = 8;
	this->height = 3;
	this->length = 6;
	this->angle = 90;

}


Tank::~Tank()
{
}

void Tank::moveX(int direction)
{
	if (direction > 0)
	{
		this->x += TankSpeed;
		this->angle = 0;
	}
	else {
		this->x -= TankSpeed;
		this->angle = -180;
	}

}

void Tank::moveZ(int direction)
{
	if (direction > 0)
	{
		this->z += TankSpeed;
		this->angle = -90;
	}
	else {
		this->z -= TankSpeed;
		this->angle = 90;
	}

}

void Tank::drawSelf()
{
	glPushMatrix();
	glTranslatef(x, 0, z);
	glRotatef(angle, 0, 1, 0);
	double tbody_l = this->length / 2, tbody_w = this->width / 2, tbody_h = this->height;

	double barrel_l = 0.8, barrel_w = 10, barrel_h = 0.8;
	//tank bottom body
	glPushMatrix();
	DrawCuboid(this->width, this->height, this->length, 1, 1, 1);
	glPopMatrix();

	//tank top body
	glPushMatrix();
	glTranslatef(0, tbody_h / 2 + this->height / 2, 0);
	//glColor3f(0.269, 0.471, 0.654)
	DrawCuboid(tbody_w, tbody_h, tbody_l, 0.269, 0.471, 0.654);
	glPopMatrix();

	//glColor3f(0.605, 0.706, 0.727)
	//tank barrel
	glPushMatrix();
	glTranslatef(barrel_w / 3, this->height + tbody_h / 2, 0);
	DrawCuboid(barrel_w, barrel_h, barrel_l, 0.605, 0.706, 0.727);
	glPopMatrix();
	glPopMatrix();
}

void Tank::DrawCuboid(double width, double height, double length, float red, float green, float blue)
{
	//draw at center
	glColor3f(red, green, blue);
	glPushMatrix();

	glBegin(GL_QUADS);
	//front face
	glNormal3f(0, 0, 1);
	glVertex3f(-width / 2, 0, length / 2);
	glVertex3f(width / 2, 0, length / 2);
	glVertex3f(width / 2, height, length / 2);
	glVertex3f(-width / 2, height, length / 2);
	/*glVertex3f(0, 0, length);
	glVertex3f(width, 0, length);
	glVertex3f(width, height, length);
	glVertex3f(0, height, length);*/

	// bottom  face
	glNormal3f(0, -1, 0);
	glVertex3f(-width / 2, 0, length / 2);
	glVertex3f(width / 2, 0, length / 2);
	glVertex3f(width / 2, 0, -length / 2);
	glVertex3f(-width / 2, 0, -length / 2);
	/*glVertex3f(0, 0, 0);
	glVertex3f(width, 0, 0);
	glVertex3f(width, 0, length);
	glVertex3f(0, 0, length);*/

	//right  face
	glNormal3f(1, 0, 0);
	glVertex3f(width / 2, 0, length / 2);
	glVertex3f(width / 2, 0, -length / 2);
	glVertex3f(width / 2, height, -length / 2);
	glVertex3f(width / 2, height, length / 2);

	/*glVertex3f(width, 0, 0);
	glVertex3f(width, height, 0);
	glVertex3f(width, height, length);
	glVertex3f(width, 0, length);*/

	//left   face
	glNormal3f(-1, 0, 0);
	glVertex3f(-width / 2, 0, length / 2);
	glVertex3f(-width / 2, 0, -length / 2);
	glVertex3f(-width / 2, height, -length / 2);
	glVertex3f(-width / 2, height, length / 2);

	//glVertex3f(0, 0, 0);
	//glVertex3f(0, 0, length);
	//glVertex3f(0, height, length);
	//glVertex3f(0, height, 0);

	//top   face
	glNormal3f(0, 1, 0);
	glVertex3f(-width / 2, height, length / 2);
	glVertex3f(width / 2, height, length / 2);
	glVertex3f(width / 2, height, -length / 2);
	glVertex3f(-width / 2, height, -length / 2);

	//glVertex3f(0, height, 0);
	//glVertex3f(0, height, length);
	//glVertex3f(width, height, length);
	//glVertex3f(width, height, 0);

	// back   face
	glNormal3f(0, 0, -1);
	glVertex3f(-width / 2, 0, -length / 2);
	glVertex3f(width / 2, 0, -length / 2);
	glVertex3f(width / 2, height, -length / 2);
	glVertex3f(-width / 2, height, -length / 2);

	//glVertex3f(0, 0, 0);
	//glVertex3f(0, height, 0);
	//glVertex3f(width, height, 0);
	//glVertex3f(width, 0, 0);

	glEnd();
	glPopMatrix();
}

void Tank::emission(double angle)
{
	Bomb bomb = Bomb();
	//bombs.push_back(bomb);
	bomb.fly(0.1);
}

