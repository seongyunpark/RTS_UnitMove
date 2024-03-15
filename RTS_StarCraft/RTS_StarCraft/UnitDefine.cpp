#include "UnitDefine.h"
#include <math.h>

CPoint::CPoint()
	: x(0), y(0)
{

}

CPoint::CPoint(float px, float py)
	: x(px), y(py)
{
}

CPoint::~CPoint()
{

}

CPoint CPoint::operator+(const CPoint& r)
{
	CPoint result;
	result.x = this->x + r.x;
	result.y = this->y + r.y;

	return result;
}

CPoint CPoint::operator-(const CPoint& r)
{
	CPoint result;
	result.x = this->x - r.x;
	result.y = this->y - r.y;

	return result;
}

CPoint CPoint::operator*(const float& f)
{
	CPoint result;
	result.x = this->x * f;
	result.y = this->y * f;

	return result;
}

void CPoint::Normalize()
{
	float _magnitude = sqrtf(powf((float)x, 2.0f) + powf((float)y, 2.0f));

	x = x / _magnitude;
	y = y / _magnitude;

}

float CPoint::Length()
{
	float _magnitude = sqrtf(powf((float)x, 2.0f) + powf((float)y, 2.0f));

	return _magnitude;
}
