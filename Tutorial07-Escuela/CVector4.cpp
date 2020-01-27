/**
* @LC		: 20/01/2020
* @file		: CVector4.cpp
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 20/01/2020
* @brief	: The structure for the class CVector4.
* @bug		: No Bugs known.
**/

/**
* Headers
*/
#include <math.h>
#include "CVector4.h"


/*
*/
CVector4::CVector4() : X(0.0f), Y(0.0f), Z(0.0f) {

}

/*
*/
CVector4::CVector4(float _x, float _y, float _z,float _w) : X(_x), Y(_y), Z(_z), W(_w) {

}

/*
*/
CVector4::CVector4(const CVector4 &other) {
	X = other.X;
	Y = other.Y;
	Z = other.Z;
	W = other.W;
}

/*
*/
CVector4::~CVector4() {

}

/*
*/
CVector4& CVector4::operator=(const CVector4 &other)
{
	X = other.X;
	Y = other.Y;
	Z = other.Z;
	W = other.W;

	return *this;
}

/*
*/
CVector4& CVector4::operator+=(const CVector4 &other)
{
	X += other.X;
	Y += other.Y;
	Z += other.Z;
	W += other.W;

	return *this;
}

/*
*/
CVector4& CVector4::operator-=(const CVector4 &other)
{
	X -= other.X;
	Y -= other.Y;
	Z -= other.Z;
	W -= other.W;

	return *this;
}



CVector4 CVector4::cross(const CVector4 & other1, const CVector4 & other2) {
	CVector4 res;
	res.setValues(
		(((other1.Z * other2.W) - (other1.W * other2.Z))*this->Y) - (((other1.Y * other2.W) - (other1.W * other2.Y))*this->Z) + (((other1.Y * other2.Z) - (other1.Z * other2.Y))*this->W),
	(((other1.W * other2.Z) - (other1.Z * other2.W))*this->X) - (((other1.W * other2.X) - (other1.X * other2.W))*this->Z) + (((other1.Z * other2.X) - (other1.X * other2.Z))*this->W),
	(((other1.Y * other2.W) - (other1.W * other2.Y))*this->X) - (((other1.X * other2.W) - (other1.W * other2.X))*this->Y) + (((other1.X * other2.Y) - (other1.Y * other2.X))*this->W),
	(((other1.Z * other2.Y) - (other1.Y * other2.Z))*this->X) - (((other1.Z * other2.X) - (other1.X * other2.Z))*this->Y) + (((other1.Y * other2.X) - (other1.X * other2.Y))*this->Z)
	);


	return res;
}

/*
*/
float CVector4::dot(const CVector4 & other)
{
	return ((this->X * other.X) + (this->Y * other.Y) + (this->Z * other.Z) + (this->W * other.W));
}

/*
*/
CVector4 CVector4::operator+(const CVector4 & other)
{
	CVector4 res;
	res.setValues(
		this->X + other.X,
		this->Y + other.Y,
		this->Z + other.Z,
		this->W + other.W
	);
	return res;
}

/*
*/
CVector4 CVector4::operator-(const CVector4 & other)
{
	CVector4 res;
	res.setValues(
		this->X - other.X,
		this->Y - other.Y,
		this->Z - other.Z,
		this->W - other.W
	);
	return res;
}

/*
*/
CVector4 CVector4::operator*(float delta)
{
	CVector4 res;
	res.setValues(
		this->X * delta,
		this->Y * delta,
		this->Z * delta,
		this->W * delta
	);
	return res;
}

/*
*/
CVector4& CVector4::operator*=(float delta)
{
	X *= delta;
	Y *= delta;
	Z *= delta;
	W *= delta;
	return *this;
}

/*
*/
void CVector4::normalize()
{
	float mag = magnitude();
	X /= mag;
	Y /= mag;
	Z /= mag;
	W /= mag;
}

// https://en.wikipedia.org/wiki/Fast_inverse_square_root
// https://www.codeproject.com/Articles/69941/Best-Square-Root-Method-Algorithm-Function-Precisi
/*
*/
float CVector4::quickReverseSqrt(float number)
{
	long i;
	float x2, y;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	y = number;
	i = *(long *)&y;                       // evil floating point bit level hacking
	i = 0x5f3759df - (i >> 1);             // what the fuck? 
	y = *(float *)&i;
	y = y * (threehalfs - (x2 * y * y));   // 1st iteration
//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

	return y;
}

/*
*/
float CVector4::quickReverseSqrt2(float number) {
	union {
		float f;
		long i;
	} conv;

	float x2;
	const float threehalfs = 1.5F;

	x2 = number * 0.5F;
	conv.f = number;
	conv.i = 0x5f3759df - (conv.i >> 1);	// what the fuck? 
	conv.f = conv.f * (threehalfs - (x2 * conv.f * conv.f));
	return conv.f;
}

/*
*/
float CVector4::magnitude()
{
	float len = (X * X) + (Y * Y) + (Z * Z) + (W * W);
	float invSqRoot = quickReverseSqrt2(len);
	float sqRoot = 1 / invSqRoot;

	return sqRoot;
	//return sqrt(len);
}

/*
*/
void CVector4::setValues(float _x, float _y, float _z, float _w)
{
	X = _x;
	Y = _y;
	Z = _z;
	W = _w;
}

/*
*/
void CVector4::setValues(float *values)
{
	X = *(values + 0);
	Y = *(values + 1);
	Z = *(values + 2);
	W = *(values + 3);
}