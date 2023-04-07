#pragma once
#include <math.h>
inline float vec2::dot(vec2 const & a_Rhs) const
{
	float result;
	result = this->m_X * a_Rhs.m_X + this->m_Y * a_Rhs.m_Y;
	return result;
}

inline float vec2::length() const
{
#pragma warning(push)
#pragma warning(disable : 4244)
	return sqrt(this->m_X * this->m_X + this->m_Y * this->m_Y);
#pragma warning(pop)
}
inline float vec3::dot(vec3 const & a_Rhs) const
{
	float result;
	result = this->m_X * a_Rhs.m_X + this->m_Y * a_Rhs.m_Y + this->m_Z * a_Rhs.m_Z;
	return result;
}
inline vec3 vec3::cross(vec3 const & rhs) const
{

	return vec3(
	this->m_Y * rhs.m_Z - rhs.m_Y * this->m_Z,
	this->m_Z * rhs.m_X - rhs.m_Z * this->m_X,
	this->m_X * rhs.m_Y - rhs.m_X * this->m_Y
	);
}
inline float vec3::length() const
{
#pragma warning(push)
#pragma warning(disable : 4244)
	return sqrt(m_X * m_X + m_Y * m_Y + m_Z * m_Z);
#pragma warning(pop)
}

inline mat4& mat4::inverse()
{
	mat4 temp;
	temp.m_00 = (m_12 * m_23*m_31 - m_13 * m_22*m_31 + m_13 * m_21*m_32 - m_11 * m_23*m_32 - m_12 * m_21*m_33 + m_11 * m_22*m_33) * (1 / this->determinant());
	temp.m_01 = (m_03 * m_22*m_31 - m_02 * m_23*m_31 - m_03 * m_21*m_32 + m_01 * m_23*m_32 + m_02 * m_21*m_33 - m_01 * m_22*m_33) * (1 / this->determinant());
	temp.m_02 = (m_02 * m_13*m_31 - m_03 * m_12*m_31 + m_03 * m_11*m_32 - m_01 * m_13*m_32 - m_02 * m_11*m_33 + m_01 * m_12*m_33) * (1 / this->determinant());
	temp.m_03 = (m_03 * m_12*m_21 - m_02 * m_13*m_21 - m_03 * m_11*m_22 + m_01 * m_13*m_22 + m_02 * m_11*m_23 - m_01 * m_12*m_23) * (1 / this->determinant());
	temp.m_10 = (m_13 * m_22*m_30 - m_12 * m_23*m_30 - m_13 * m_20*m_32 + m_10 * m_23*m_32 + m_12 * m_20*m_33 - m_10 * m_22*m_33) * (1 / this->determinant());
	temp.m_11 = (m_02 * m_23*m_30 - m_03 * m_22*m_30 + m_03 * m_20*m_32 - m_00 * m_23*m_32 - m_02 * m_20*m_33 + m_00 * m_22*m_33) * (1 / this->determinant());
	temp.m_12 = (m_03 * m_12*m_30 - m_02 * m_13*m_30 - m_03 * m_10*m_32 + m_00 * m_13*m_32 + m_02 * m_10*m_33 - m_00 * m_12*m_33) * (1 / this->determinant());
	temp.m_13 = (m_02 * m_13*m_20 - m_03 * m_12*m_20 + m_03 * m_10*m_22 - m_00 * m_13*m_22 - m_02 * m_10*m_23 + m_00 * m_12*m_23) * (1 / this->determinant());
	temp.m_20 = (m_11 * m_23*m_30 - m_13 * m_21*m_30 + m_13 * m_20*m_31 - m_10 * m_23*m_31 - m_11 * m_20*m_33 + m_10 * m_21*m_33) * (1 / this->determinant());
	temp.m_21 = (m_03 * m_21*m_30 - m_01 * m_23*m_30 - m_03 * m_20*m_31 + m_00 * m_23*m_31 + m_01 * m_20*m_33 - m_00 * m_21*m_33) * (1 / this->determinant());
	temp.m_22 = (m_01 * m_13*m_30 - m_03 * m_11*m_30 + m_03 * m_10*m_31 - m_00 * m_13*m_31 - m_01 * m_10*m_33 + m_00 * m_11*m_33) * (1 / this->determinant());
	temp.m_23 = (m_03 * m_11*m_20 - m_01 * m_13*m_20 - m_03 * m_10*m_21 + m_00 * m_13*m_21 + m_01 * m_10*m_23 - m_00 * m_11*m_23) * (1 / this->determinant());
	temp.m_30 = (m_12 * m_21*m_30 - m_11 * m_22*m_30 - m_12 * m_20*m_31 + m_10 * m_22*m_31 + m_11 * m_20*m_32 - m_10 * m_21*m_32) * (1 / this->determinant());
	temp.m_31 = (m_01 * m_22*m_30 - m_02 * m_21*m_30 + m_02 * m_20*m_31 - m_00 * m_22*m_31 - m_01 * m_20*m_32 + m_00 * m_21*m_32) * (1 / this->determinant());
	temp.m_32 = (m_02 * m_11*m_30 - m_01 * m_12*m_30 - m_02 * m_10*m_31 + m_00 * m_12*m_31 + m_01 * m_10*m_32 - m_00 * m_11*m_32) * (1 / this->determinant());
	temp.m_33 = (m_01 * m_12*m_20 - m_02 * m_11*m_20 + m_02 * m_10*m_21 - m_00 * m_12*m_21 - m_01 * m_10*m_22 + m_00 * m_11*m_22) * (1 / this->determinant());
	for (int i = 0; i < 16; i++) {
		this->m[i] = temp.m[i];
	}
	return *this;
}