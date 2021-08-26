#include "Point2D.h"

Point2D::Point2D()
{
	this->x = 0;
	this->y = 0;
}

Point2D::Point2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

float Point2D::GetX()
{
	return this->x;
}

float Point2D::GetY()
{
	return this->y;
}
