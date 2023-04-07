#pragma once
#include "MathLibrary.h"
#include "SFML/Graphics.hpp"
class Color
{
public:
	Color();
	Color(vec3 a_RGB);
	Color(float a_R, float a_G, float a_B,float a_Alpha = 100.f);
	~Color();
	//Clamps values to the
	void KeepItReal();
	void Inverse();
	//Converts my own color to a sfml-compatible color
	sf::Color toSF() const;
	float m_R;
	float m_G;
	float m_B;
	float m_Alpha;
	Color& Mix(const Color& Rhs);
	Color& operator+=(const Color& Rhs);
	static Color const White();
	static Color const Black();
	static Color const Red();
	static Color const Green();
	static Color const Blue();
	static Color const PeachPink();

};
Color operator+(const Color& Lhs, const Color& Rhs);
Color operator*(const Color& Lhs, const Color& Rhs);
Color operator*(const Color& Lhs, const float& Rhs);
Color operator-(const Color& Lhs, const Color& Rhs);
bool operator==(const Color& Lhs, const Color& Rhs);
