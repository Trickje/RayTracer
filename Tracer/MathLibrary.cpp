#include "MathLibrary.h"
#include <iostream>
#include <math.h>
#define PI 3.1415927410125732421875

vec2::vec2() {
	this->m_X = 0.f;
	this->m_Y = 0.f;
}
vec2::vec2(float a_X, float a_Y) {
	this->m_X = a_X;
	this->m_Y = a_Y;
}


vec2 & vec2::operator+=(const vec2 & a_Rhs)
{
	this->m_X += a_Rhs.m_X;
	this->m_Y += a_Rhs.m_Y;
	return *this;
}

vec2 & vec2::operator-=(const vec2 & a_Rhs)
{
	this->m_X -= a_Rhs.m_X;
	this->m_Y -= a_Rhs.m_Y;
	return *this;
}

vec2 & vec2::operator*=(float a_Rhs)
{
	this->m_X *= a_Rhs;
	this->m_Y *= a_Rhs;
	return *this;
}

vec2 & vec2::operator/=(float a_Rhs)
{
	this->m_X /= a_Rhs;
	this->m_Y /= a_Rhs;
	return *this;
}

float vec2::operator[](int a_Index) const
{
	return v[a_Index];
}

float & vec2::operator[](int a_Index)
{
	return v[a_Index];
}



vec2& vec2::normalize()
{
	float l = length();
	float inverse = 1 / l;
	this->m_X *= inverse;
	this->m_Y *= inverse;
	return *this;
}



vec2 operator+(const vec2 & a_Lhs, const vec2 & a_Rhs)
{
	vec2 result;
	result.m_X = a_Lhs.m_X + a_Rhs.m_X;
	result.m_Y = a_Lhs.m_Y + a_Rhs.m_Y;
	return result;
}

vec2 operator-(const vec2 & a_Lhs, const vec2 & a_Rhs)
{
	vec2 result;
	result.m_X = a_Lhs.m_X - a_Rhs.m_X;
	result.m_Y = a_Lhs.m_Y - a_Rhs.m_Y;
	return result;
}

vec2 operator*(const vec2 & a_Lhs, float a_Rhs)
{
	vec2 result;
	result.m_X = a_Lhs.m_X * a_Rhs;
	result.m_Y = a_Lhs.m_Y * a_Rhs;
	return result;
}

vec2 operator/(const vec2 & a_Lhs, float a_Rhs)
{
	vec2 result;
	result.m_X = a_Lhs.m_X / a_Rhs;
	result.m_Y = a_Lhs.m_Y / a_Rhs;
	return result;
}

bool operator==(const vec2 & a_Lhs, const vec2 & a_Rhs)
{
	if (a_Lhs.m_X == a_Rhs.m_X) {
		if (a_Lhs.m_Y == a_Rhs.m_Y) {
			return true;
		}
	}
	return false;
}

bool operator!=(const vec2 & a_Lhs, const vec2 & a_Rhs)
{
	if (a_Lhs.m_X == a_Rhs.m_X) {
		if (a_Lhs.m_Y == a_Rhs.m_Y) {
			return false;
		}
	}
	return true;
}

vec3 operator+(const vec3 & a_Lhs, const vec3 & a_Rhs)
{
	vec3 result;
	result.m_X = a_Lhs.m_X + a_Rhs.m_X;
	result.m_Y = a_Lhs.m_Y + a_Rhs.m_Y;
	result.m_Z = a_Lhs.m_Z + a_Rhs.m_Z;
	return result;
}

vec3 operator-(const vec3 & a_Lhs, const vec3 & a_Rhs)
{
	vec3 result;
	result.m_X = a_Lhs.m_X - a_Rhs.m_X;
	result.m_Y = a_Lhs.m_Y - a_Rhs.m_Y;
	result.m_Z = a_Lhs.m_Z - a_Rhs.m_Z;
	return result;
}

vec3 operator*(const vec3 & a_Lhs, float a_Rhs)
{
	vec3 result;
	result.m_X = a_Lhs.m_X * a_Rhs;
	result.m_Y = a_Lhs.m_Y * a_Rhs;
	result.m_Z = a_Lhs.m_Z * a_Rhs;
	return result;
}

vec3 operator/(const vec3 & a_Lhs, float a_Rhs)
{
	vec3 result;
	result.m_X = a_Lhs.m_X / a_Rhs;
	result.m_Y = a_Lhs.m_Y / a_Rhs;
	result.m_Z = a_Lhs.m_Z / a_Rhs;
	return result;
}

bool operator==(const vec3 & a_Lhs, const vec3 & a_Rhs)
{
	if (a_Lhs.m_X == a_Rhs.m_X) {
		if (a_Lhs.m_Y == a_Rhs.m_Y) {
			if (a_Lhs.m_Z == a_Rhs.m_Z) {
				return true;
			}
		}
	}
	return false;
}

bool operator!=(const vec3 & a_Lhs, const vec3 & a_Rhs)
{
	if (a_Lhs.m_X == a_Rhs.m_X) {
		if (a_Lhs.m_Y == a_Rhs.m_Y) {
			if (a_Lhs.m_Z == a_Rhs.m_Z) {
				return false;
			}
		}
	}
	return true;
}

vec3::vec3()
{
	this->m_X = 0.f;
	this->m_Y = 0.f;
	this->m_Z = 0.f;
}

vec3::vec3(float a_X, float a_Y, float a_Z)
{
	this->m_X = a_X;
	this->m_Y = a_Y;
	this->m_Z = a_Z;
}

vec3 & vec3::operator=(const vec3 & rhs)
{
	this->m_X = rhs.m_X;
	this->m_Y = rhs.m_Y;
	this->m_Z = rhs.m_Z;
	return *this;
}

vec3 & vec3::operator+=(const vec3 & a_Rhs)
{
	this->m_X += a_Rhs.m_X;
	this->m_Y += a_Rhs.m_Y;
	this->m_Z += a_Rhs.m_Z;
	return *this;
}

vec3 & vec3::operator-=(const vec3 & a_Rhs)
{
	this->m_X -= a_Rhs.m_X;
	this->m_Y -= a_Rhs.m_Y;
	this->m_Z -= a_Rhs.m_Z;
	return *this;
}

vec3 & vec3::operator*=(float a_Rhs)
{
	this->m_X *= a_Rhs;
	this->m_Y *= a_Rhs;
	this->m_Z *= a_Rhs;
	return *this;
}

vec3 & vec3::operator/=(float a_Rhs)
{
	this->m_X /= a_Rhs;
	this->m_Y /= a_Rhs;
	this->m_Z /= a_Rhs;
	return *this;
	// TODO: insert return statement here
}

float vec3::operator[](int a_Index) const
{
	return v[a_Index];
}

float & vec3::operator[](int a_Index)
{
	return v[a_Index];
}





vec3& vec3::normalize()
{
	float length = this->length();
	this->m_X /= length;
	this->m_Y /= length;
	this->m_Z /= length;
	return *this;
}

vec3 operator*(const mat4 & a_Lhs, const vec3 & a_Rhs)
{
	float k = 1.f;
	//1 so it doesnt change the bottom row values
	vec3 result;
	result.m_X = a_Rhs.m_X * a_Lhs.m_00 +
		a_Rhs.m_Y * a_Lhs.m_01 +
		a_Rhs.m_Z * a_Lhs.m_02 +
		k * a_Lhs.m_03;

	result.m_Y = a_Rhs.m_X * a_Lhs.m_10 +
		a_Rhs.m_Y * a_Lhs.m_11 +
		a_Rhs.m_Z * a_Lhs.m_12 +
		k * a_Lhs.m_13;

	result.m_Z = a_Rhs.m_X * a_Lhs.m_20 +
		a_Rhs.m_Y * a_Lhs.m_21 +
		a_Rhs.m_Z * a_Lhs.m_22 +
		k * a_Lhs.m_23;
	return result;
}
mat4 operator+(const mat4 & a_Lhs, const mat4 & a_Rhs)
{
	mat4 result;
	for (int i = 0; i < 16; i++) {
		result.m[i] = a_Lhs.m[i] + a_Rhs.m[i];
	}
	return result;
}

mat4 operator-(const mat4 & a_Lhs, const mat4 & a_Rhs)
{
	mat4 result;
	for (int i = 0; i < 16; i++) {
		result.m[i] = a_Lhs.m[i] - a_Rhs.m[i];
	}
	return result;
}

mat4 operator*(const mat4 & a_Lhs, const mat4 & a_Rhs)
{
	mat4 temp(a_Lhs.m_00 * a_Rhs.m_00 +
		a_Lhs.m_01 * a_Rhs.m_10 +
		a_Lhs.m_02 * a_Rhs.m_20 +
		a_Lhs.m_03 * a_Rhs.m_30,

		a_Lhs.m_00 * a_Rhs.m_01 +
		a_Lhs.m_01 * a_Rhs.m_11 +
		a_Lhs.m_02 * a_Rhs.m_21 +
		a_Lhs.m_03 * a_Rhs.m_31,

		a_Lhs.m_00 * a_Rhs.m_02 +
		a_Lhs.m_01 * a_Rhs.m_12 +
		a_Lhs.m_02 * a_Rhs.m_22 +
		a_Lhs.m_03 * a_Rhs.m_32,

		a_Lhs.m_00 * a_Rhs.m_03 +
		a_Lhs.m_01 * a_Rhs.m_13 +
		a_Lhs.m_02 * a_Rhs.m_23 +
		a_Lhs.m_03 * a_Rhs.m_33,
		//Second row
		a_Lhs.m_10 * a_Rhs.m_00 +
		a_Lhs.m_11 * a_Rhs.m_10 +
		a_Lhs.m_12 * a_Rhs.m_20 +
		a_Lhs.m_13 * a_Rhs.m_30,

		a_Lhs.m_10 * a_Rhs.m_01 +
		a_Lhs.m_11 * a_Rhs.m_11 +
		a_Lhs.m_12 * a_Rhs.m_21 +
		a_Lhs.m_13 * a_Rhs.m_31,

		a_Lhs.m_10 * a_Rhs.m_02 +
		a_Lhs.m_11 * a_Rhs.m_12 +
		a_Lhs.m_12 * a_Rhs.m_22 +
		a_Lhs.m_13 * a_Rhs.m_32,

		a_Lhs.m_10 * a_Rhs.m_03 +
		a_Lhs.m_11 * a_Rhs.m_13 +
		a_Lhs.m_12 * a_Rhs.m_23 +
		a_Lhs.m_13 * a_Rhs.m_33,
		//Third row
		a_Lhs.m_20 * a_Rhs.m_00 +
		a_Lhs.m_21 * a_Rhs.m_10 +
		a_Lhs.m_22 * a_Rhs.m_20 +
		a_Lhs.m_23 * a_Rhs.m_30,

		a_Lhs.m_20 * a_Rhs.m_01 +
		a_Lhs.m_21 * a_Rhs.m_11 +
		a_Lhs.m_22 * a_Rhs.m_21 +
		a_Lhs.m_23 * a_Rhs.m_31,

		a_Lhs.m_20 * a_Rhs.m_02 +
		a_Lhs.m_21 * a_Rhs.m_12 +
		a_Lhs.m_22 * a_Rhs.m_22 +
		a_Lhs.m_23 * a_Rhs.m_32,

		a_Lhs.m_20 * a_Rhs.m_03 +
		a_Lhs.m_21 * a_Rhs.m_13 +
		a_Lhs.m_22 * a_Rhs.m_23 +
		a_Lhs.m_23 * a_Rhs.m_33,
		//Fourth row
		a_Lhs.m_30 * a_Rhs.m_00 +
		a_Lhs.m_31 * a_Rhs.m_10 +
		a_Lhs.m_32 * a_Rhs.m_20 +
		a_Lhs.m_33 * a_Rhs.m_30,

		a_Lhs.m_30 * a_Rhs.m_01 +
		a_Lhs.m_31 * a_Rhs.m_11 +
		a_Lhs.m_32 * a_Rhs.m_21 +
		a_Lhs.m_33 * a_Rhs.m_31,

		a_Lhs.m_30 * a_Rhs.m_02 +
		a_Lhs.m_31 * a_Rhs.m_12 +
		a_Lhs.m_32 * a_Rhs.m_22 +
		a_Lhs.m_33 * a_Rhs.m_32,

		a_Lhs.m_30 * a_Rhs.m_03 +
		a_Lhs.m_31 * a_Rhs.m_13 +
		a_Lhs.m_32 * a_Rhs.m_23 +
		a_Lhs.m_33 * a_Rhs.m_33);
	return temp;
}

mat4::mat4()
{
	this->m_00 = 0.f;
	this->m_01 = 0.f;
	this->m_02 = 0.f;
	this->m_03 = 0.f;

	this->m_10 = 0.f;
	this->m_11 = 0.f;
	this->m_12 = 0.f;
	this->m_13 = 0.f;

	this->m_20 = 0.f;
	this->m_21 = 0.f;
	this->m_22 = 0.f;
	this->m_23 = 0.f;

	this->m_30 = 0.f;
	this->m_31 = 0.f;
	this->m_32 = 0.f;
	this->m_33 = 0.f;
}

mat4::mat4(vec3 a_Row0, float a_03, vec3 a_Row1, float a_13, vec3 a_Row2, float a_23, vec3 a_Row3, float a_33)
{
	this->m_00 = a_Row0.m_X;
	this->m_01 = a_Row0.m_Y;
	this->m_02 = a_Row0.m_Z;
	this->m_03 = a_03;

	this->m_10 = a_Row1.m_X;
	this->m_11 = a_Row1.m_Y;
	this->m_12 = a_Row1.m_Z;
	this->m_13 = a_13;

	this->m_20 = a_Row2.m_X;
	this->m_21 = a_Row2.m_Y;
	this->m_22 = a_Row2.m_Z;
	this->m_23 = a_23;

	this->m_30 = a_Row3.m_X;
	this->m_31 = a_Row3.m_Y;
	this->m_32 = a_Row3.m_Z;
	this->m_33 = a_33;
}

mat4::mat4(float a_00, float a_01, float a_02, float a_03, float a_10, float a_11, float a_12, float a_13, float a_20, float a_21, float a_22, float a_23, float a_30, float a_31, float a_32, float a_33)
{
	this->m_00 = a_00;
	this->m_01 = a_01;
	this->m_02 = a_02;
	this->m_03 = a_03;

	this->m_10 = a_10;
	this->m_11 = a_11;
	this->m_12 = a_12;
	this->m_13 = a_13;

	this->m_20 = a_20;
	this->m_21 = a_21;
	this->m_22 = a_22;
	this->m_23 = a_23;

	this->m_30 = a_30;
	this->m_31 = a_31;
	this->m_32 = a_32;
	this->m_33 = a_33;
}

mat4 & mat4::operator=(const mat4 & rhs)
{
	this->m_00 = rhs.m_00;
	this->m_01 = rhs.m_01;
	this->m_02 = rhs.m_02;
	this->m_03 = rhs.m_03;

	this->m_10 = rhs.m_10;
	this->m_11 = rhs.m_11;
	this->m_12 = rhs.m_12;
	this->m_13 = rhs.m_13;

	this->m_20 = rhs.m_20;
	this->m_21 = rhs.m_21;
	this->m_22 = rhs.m_22;
	this->m_23 = rhs.m_23;

	this->m_30 = rhs.m_30;
	this->m_31 = rhs.m_31;
	this->m_32 = rhs.m_32;
	this->m_33 = rhs.m_33;
	return *this;
}

mat4 & mat4::operator+=(const mat4 & a_Rhs)
{
	this->m_00 += a_Rhs.m_00;
	this->m_01 += a_Rhs.m_01;
	this->m_02 += a_Rhs.m_02;
	this->m_03 += a_Rhs.m_03;

	this->m_10 += a_Rhs.m_10;
	this->m_11 += a_Rhs.m_11;
	this->m_12 += a_Rhs.m_12;
	this->m_13 += a_Rhs.m_13;

	this->m_20 += a_Rhs.m_20;
	this->m_21 += a_Rhs.m_21;
	this->m_22 += a_Rhs.m_22;
	this->m_23 += a_Rhs.m_23;

	this->m_30 += a_Rhs.m_30;
	this->m_31 += a_Rhs.m_31;
	this->m_32 += a_Rhs.m_32;
	this->m_33 += a_Rhs.m_33;
	return *this;
}

mat4 & mat4::operator-=(const mat4 & a_Rhs)
{
	this->m_00 -= a_Rhs.m_00;
	this->m_01 -= a_Rhs.m_01;
	this->m_02 -= a_Rhs.m_02;
	this->m_03 -= a_Rhs.m_03;

	this->m_10 -= a_Rhs.m_10;
	this->m_11 -= a_Rhs.m_11;
	this->m_12 -= a_Rhs.m_12;
	this->m_13 -= a_Rhs.m_13;

	this->m_20 -= a_Rhs.m_20;
	this->m_21 -= a_Rhs.m_21;
	this->m_22 -= a_Rhs.m_22;
	this->m_23 -= a_Rhs.m_23;

	this->m_30 -= a_Rhs.m_30;
	this->m_31 -= a_Rhs.m_31;
	this->m_32 -= a_Rhs.m_32;
	this->m_33 -= a_Rhs.m_33;
	return *this;
}

mat4 & mat4::operator*=(const mat4 & a_Rhs)
{
	mat4 temp(m_00 * a_Rhs.m_00 +
		m_01 * a_Rhs.m_10 +
		m_02 * a_Rhs.m_20 +
		m_03 * a_Rhs.m_30,

		m_00 * a_Rhs.m_01 +
		m_01 * a_Rhs.m_11 +
		m_02 * a_Rhs.m_21 +
		m_03 * a_Rhs.m_31,

		m_00 * a_Rhs.m_02 +
		m_01 * a_Rhs.m_12 +
		m_02 * a_Rhs.m_22 +
		m_03 * a_Rhs.m_32,

		m_00 * a_Rhs.m_03 +
		m_01 * a_Rhs.m_13 +
		m_02 * a_Rhs.m_23 +
		m_03 * a_Rhs.m_33,
		//Second row
		m_10 * a_Rhs.m_00 +
		m_11 * a_Rhs.m_10 +
		m_12 * a_Rhs.m_20 +
		m_13 * a_Rhs.m_30,

		m_10 * a_Rhs.m_01 +
		m_11 * a_Rhs.m_11 +
		m_12 * a_Rhs.m_21 +
		m_13 * a_Rhs.m_31,

		m_10 * a_Rhs.m_02 +
		m_11 * a_Rhs.m_12 +
		m_12 * a_Rhs.m_22 +
		m_13 * a_Rhs.m_32,

		m_10 * a_Rhs.m_03 +
		m_11 * a_Rhs.m_13 +
		m_12 * a_Rhs.m_23 +
		m_13 * a_Rhs.m_33,
		//Third row
		m_20 * a_Rhs.m_00 +
		m_21 * a_Rhs.m_10 +
		m_22 * a_Rhs.m_20 +
		m_23 * a_Rhs.m_30,

		m_20 * a_Rhs.m_01 +
		m_21 * a_Rhs.m_11 +
		m_22 * a_Rhs.m_21 +
		m_23 * a_Rhs.m_31,

		m_20 * a_Rhs.m_02 +
		m_21 * a_Rhs.m_12 +
		m_22 * a_Rhs.m_22 +
		m_23 * a_Rhs.m_32,

		m_20 * a_Rhs.m_03 +
		m_21 * a_Rhs.m_13 +
		m_22 * a_Rhs.m_23 +
		m_23 * a_Rhs.m_33,
		//Fourth row
		m_30 * a_Rhs.m_00 +
		m_31 * a_Rhs.m_10 +
		m_32 * a_Rhs.m_20 +
		m_33 * a_Rhs.m_30,

		m_30 * a_Rhs.m_01 +
		m_31 * a_Rhs.m_11 +
		m_32 * a_Rhs.m_21 +
		m_33 * a_Rhs.m_31,

		m_30 * a_Rhs.m_02 +
		m_31 * a_Rhs.m_12 +
		m_32 * a_Rhs.m_22 +
		m_33 * a_Rhs.m_32,

		m_30 * a_Rhs.m_03 +
		m_31 * a_Rhs.m_13 +
		m_32 * a_Rhs.m_23 +
		m_33 * a_Rhs.m_33);
	//Change the current matrix values to the temporary matrix values
	this->m_00 = temp.m_00;
	this->m_01 = temp.m_01;
	this->m_02 = temp.m_02;
	this->m_03 = temp.m_03;

	this->m_10 = temp.m_10;
	this->m_11 = temp.m_11;
	this->m_12 = temp.m_12;
	this->m_13 = temp.m_13;

	this->m_20 = temp.m_20;
	this->m_21 = temp.m_21;
	this->m_22 = temp.m_22;
	this->m_23 = temp.m_23;

	this->m_30 = temp.m_30;
	this->m_31 = temp.m_31;
	this->m_32 = temp.m_32;
	this->m_33 = temp.m_33;
	return *this;
}

float mat4::determinant() const
{
	return(
		m[3] * m[6] * m[9] * m[12] - m[2] * m[7] * m[9] * m[12] -
		m[3] * m[5] * m[10] * m[12] + m[1] * m[7] * m[10] * m[12] +
		m[2] * m[5] * m[11] * m[12] - m[1] * m[6] * m[11] * m[12] -
		m[3] * m[6] * m[8] * m[13] + m[2] * m[7] * m[8] * m[13] +
		m[3] * m[4] * m[10] * m[13] - m[0] * m[7] * m[10] * m[13] -
		m[2] * m[4] * m[11] * m[13] + m[0] * m[6] * m[11] * m[13] +
		m[3] * m[5] * m[8] * m[14] - m[1] * m[7] * m[8] * m[14] -
		m[3] * m[4] * m[9] * m[14] + m[0] * m[7] * m[9] * m[14] +
		m[1] * m[4] * m[11] * m[14] - m[0] * m[5] * m[11] * m[14] -
		m[2] * m[5] * m[8] * m[15] + m[1] * m[6] * m[8] * m[15] +
		m[2] * m[4] * m[9] * m[15] - m[0] * m[6] * m[9] * m[15] -
		m[1] * m[4] * m[10] * m[15] + m[0] * m[5] * m[10] * m[15]);

}



mat4 mat4::identity()
{
	return mat4(1.f, 0.f, 0.f, 0.f,
		0.f, 1.f, 0.f, 0.f,
		0.f, 0.f, 1.f, 0.f,
		0.f, 0.f, 0.f, 1.f);
}
//Static function, doesnt need a matrix to be called :)
mat4 mat4::rotateX(float a_Radians)
{
	mat4 result = mat4(
		1, 0, 0, 0,
		0, static_cast<float>(cos(a_Radians)), static_cast<float>(-sin(a_Radians)), 0,
		0, static_cast<float>(sin(a_Radians)), static_cast<float>(cos(a_Radians)), 0,
		0, 0, 0, 1
	);
	return result;
}

mat4 mat4::rotateY(float a_Radians)
{
	mat4 result = mat4(
		static_cast<float>(cos(a_Radians)), 0, static_cast<float>(sin(a_Radians)), 0,
		0, 1, 0, 0,
		static_cast<float>(-sin(a_Radians)), 0, static_cast<float>(cos(a_Radians)), 0,
		0, 0, 0, 1
	);
	return result;
}

mat4 mat4::rotateZ(float a_Radians)
{
	mat4 result = mat4(
		static_cast<float>(cos(a_Radians)), static_cast<float>(-sin(a_Radians)), 0, 0,
		static_cast<float>(sin(a_Radians)), static_cast<float>(cos(a_Radians)), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
	return result;
}

mat4 mat4::translate(const vec3 & a_Translation)
{
	mat4 result = identity();
	result.m_03 = a_Translation.m_X;
	result.m_13 = a_Translation.m_Y;
	result.m_23 = a_Translation.m_Z;
	return result;
}

mat4 mat4::lookat(const vec3 & a_Eye, const vec3 & a_Center, const vec3 & a_Up)
{
	vec3 z = (a_Center - a_Eye).normalize();
	vec3 x = a_Up.cross(z).normalize();
	vec3 y = z.cross(x);
	return mat4(
		x.m_X, y.m_X, z.m_X, 0.f,
		x.m_Y, y.m_Y, z.m_Y, 0.f,
		x.m_Z, y.m_Z, z.m_Z, 0.f,
		-x.dot(a_Eye), -y.dot(a_Eye), -z.dot(a_Eye), 1.f
	);
}

mat4 mat4::projection(float a_FovY, float a_AspectRatio, float a_Near, float a_Far)
{
	float top = tan(a_FovY / 2) * a_Near;
	float bottom = -top;
	float right = top * a_AspectRatio;
	float left = -right;

	return mat4(
		(2 * a_Near) / (right - left), 0, 0, 0,
		0, (2 * a_Near) / (top - bottom), 0, 0,
		0, 0, -((a_Far + a_Near) / (a_Far - a_Near)), -1,
		0, 0, -((2 * a_Far * a_Near) / (a_Far - a_Near)), 0
	);

}
