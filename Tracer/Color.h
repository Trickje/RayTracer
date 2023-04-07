#pragma once
#include "MathLibrary.h"
#include "SFML/Graphics.hpp"
class TColor
{
public:
	TColor();
	TColor(vec3 a_RGB);
	TColor(float a_R, float a_G, float a_B,float a_Alpha = 100.f);
	~TColor();
	//Clamps values to the
	void KeepItReal();
	void Inverse();
	//Converts my own color to a sfml-compatible color
	sf::Color toSF() const;
	float m_R;
	float m_G;
	float m_B;
	float m_Alpha;
	TColor& Mix(const TColor& Rhs);
	TColor& operator+=(const TColor& Rhs);
	static TColor const White();
	static TColor const Black();
	static TColor const Red();
	static TColor const Green();
	static TColor const Blue();
	static TColor const PeachPink();

};
TColor operator+(const TColor& Lhs, const TColor& Rhs);
TColor operator*(const TColor& Lhs, const TColor& Rhs);
TColor operator*(const TColor& Lhs, const float& Rhs);
TColor operator-(const TColor& Lhs, const TColor& Rhs);
bool operator==(const TColor& Lhs, const TColor& Rhs);
