#include "Color.h"



Color::Color()
{
}


Color::~Color()
{
}

void Color::KeepItReal()
{
	if (m_R > 100.f) {
		m_R = 100.f;
	}
	if (m_R < 0.f) {
		m_R = 0.f;
	}
	if (m_G > 100.f) {
		m_G = 100.f;
	}
	if (m_G < 0.f) {
		m_G = 0.f;
	}
	if (m_B > 100.f) {
		m_B = 100.f;
	}
	if (m_B < 0.f) {
		m_B = 0.f;
	}
	if (m_Alpha > 100.f) {
		m_Alpha = 100.f;
	}
	if (m_Alpha < 0.f) {
		m_Alpha = 0.f;
	}
}

void Color::Inverse()
{
	this->m_R = 100 - this->m_R;
	this->m_G = 100 - this->m_G;
	this->m_B = 100 - this->m_B;
}

sf::Color Color::toSF() const
{
	return sf::Color(static_cast<sf::Uint8>(m_R / 100 * 255), static_cast<sf::Uint8>(m_G / 100 * 255), static_cast<sf::Uint8>(m_B / 100 * 255));
}

Color & Color::Mix(const Color & Rhs)
{
	this->m_R = (this->m_R + Rhs.m_R) / 2;
	this->m_G = (this->m_G + Rhs.m_G) / 2;
	this->m_B = (this->m_B + Rhs.m_B) / 2;
	return *this;
}
Color & Color::operator+=(const Color & Rhs)
{
	this->m_R += Rhs.m_R;
	this->m_G += Rhs.m_G;
	this->m_B += Rhs.m_B;
	return *this;
}

Color const Color::White()
{
	return Color(100.f, 100.f, 100.f);
}

Color const Color::Black()
{
	return Color(0.f, 0.f, 0.f);
}

Color const Color::Red()
{
	return Color(100.f, 0.f, 0.f);
}

Color const Color::Green()
{
	return Color(0.f, 100.f, 0.f);
}

Color const Color::Blue()
{
	return Color(0.f, 0.f, 100.f);
}
Color const Color::PeachPink()
{
	return Color(97.6f, 58.4f, 51.8f);
}

Color operator+(const Color & Lhs, const Color & Rhs)
{
	if (Lhs.m_Alpha == 100.f) {
		if (Rhs.m_Alpha == 100.f) {
			return Color(Lhs.m_R + Rhs.m_R, Lhs.m_G + Rhs.m_G, Lhs.m_B + Rhs.m_B);
		}
		else {
			return Color(Lhs.m_R + Rhs.m_R, Lhs.m_G + Rhs.m_G, Lhs.m_B + Rhs.m_B, Rhs.m_Alpha);

		}
	}
	else {
		if (Rhs.m_Alpha == 100.f) {

			return Color(Lhs.m_R + Rhs.m_R, Lhs.m_G + Rhs.m_G, Lhs.m_B + Rhs.m_B, Lhs.m_Alpha);
		}
		else {

			return Color(Lhs.m_R + Rhs.m_R, Lhs.m_G + Rhs.m_G, Lhs.m_B + Rhs.m_B,Rhs.m_Alpha + Lhs.m_Alpha);
		}
	}
}

Color operator*(const Color& Lhs, const Color& Rhs)
{
	
	return Color(Lhs.m_R * Rhs.m_R, Lhs.m_G * Rhs.m_G, Lhs.m_B * Rhs.m_B, Lhs.m_Alpha);
}

Color operator*(const Color & Lhs, const float & Rhs)
{
	return Color(Lhs.m_R * Rhs, Lhs.m_G * Rhs, Lhs.m_B * Rhs, Lhs.m_Alpha);
}

Color operator-(const Color & Lhs, const Color & Rhs)
{
	return Color(Lhs.m_R - Rhs.m_R, Lhs.m_G - Rhs.m_G, Lhs.m_B - Rhs.m_B);
}

bool operator==(const Color & Lhs, const Color & Rhs)
{
	if (Lhs.m_R == Rhs.m_R) {
		if (Lhs.m_G == Rhs.m_G) {
			if (Lhs.m_B == Rhs.m_B) {
				return true;
			}
		}
	}
	return false;
}

Color::Color(vec3 a_RGB)
{
	this->m_R = a_RGB.m_X;
	this->m_G = a_RGB.m_Y;
	this->m_B = a_RGB.m_Z;
}

Color::Color(float a_R, float a_G, float a_B, float a_Alpha)
{
	this->m_R = a_R;
	this->m_G = a_G;
	this->m_B = a_B;
	this->m_Alpha = a_Alpha;
}