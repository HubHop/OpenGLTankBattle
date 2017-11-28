#include "stdafx.h"
#include "Bomb.h"
#include <gl\GLU.h>
#include <gl\GL.h>
#include <gl\glut.h>

Bomb::Bomb()
{

}

//Bomb::Bomb(Tank *tank)
//{
//	this->x = tank->x + tank->width;
//	this->y = tank->height / 2;
//	this->z = tank->z + tank->length;
//	this->angle = tank->angle;
//}


Bomb::~Bomb()
{
}

void Bomb::drawSelf()
{
	glPushMatrix();
	glTranslatef(this->x, this->y, this->z);
	//glRotatef(this->direction, 0, 1, 0);
	glutSolidSphere(1, 10, 10);
	glPopMatrix();
}

void Bomb::fly(float speed)
{
	switch (direction)
	{
	case 90:
		//forward
		this->z -= speed;
		break;
	case -90:
		//back
		this->z += speed;
		break;
	case 0:
		this->x += speed;
		break;
	case -180:
		this->x -= speed;
		break;
	}
	//drawSelf();
}
