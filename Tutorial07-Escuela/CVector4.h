/**
* @LC		: 20/01/2020
* @file		: CVector4.h
* @Author	: Jesús Alberto Del Moral Cupil
* @Email	: idv18c.jmoral@uartesdigitales.edu.mx
* @date		: 20/01/2020
* @brief	: The class for math operations with Vectors4.
* @bug		: No Bugs known.
**/


#pragma once

#ifndef CVECTOR4_H
#define CVECTOR4_H

// Simple class to practice C++ class creation
// It will be more helpful later when more code is added
class CVector4 {
public:
	float X, Y, Z, W;

public:
	CVector4();
	CVector4(float _x, float _y, float _z, float _w);
	CVector4(const CVector4 &other);
	~CVector4();

	CVector4& operator=(const CVector4 &other);

	CVector4 operator+(const CVector4 & other);
	CVector4& operator+=(const CVector4 &other);

	CVector4 operator-(const CVector4 & other);
	CVector4& operator-=(const CVector4 &other);

	CVector4 operator*(float delta);
	CVector4& operator*=(float delta);

	CVector4 cross(const CVector4 & other1, const CVector4 & other2);
	float dot(const CVector4 & other);

	void setValues(float _x, float _y, float _z, float _w);
	void setValues(float *values);
	float getX() const { return X; }
	float getY() const { return Y; }
	float getZ() const { return Z; }
	float getW() const { return W; }
	void getValues(float *values) const { values[0] = X; values[1] = Y; values[2] = Z; values[3] = W; }
	void normalize();
	float magnitude();

	inline static CVector4 ZeroVector()
	{
		return CVector4(0.0f, 0.0f, 0.0f,0.0f);
	}

private:
	float quickReverseSqrt(float number);
	float quickReverseSqrt2(float number);
};

#endif // !CVector4_H



//Todo list
/*
* Cross
* quickReverseSqrt
* quickReverseSqrt2
*/
