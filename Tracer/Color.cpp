#include "Color.h"



TColor::TColor()
{
}


TColor::~TColor()
{
}

void TColor::KeepItReal()
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

void TColor::Inverse()
{
	this->m_R = 100 - this->m_R;
	this->m_G = 100 - this->m_G;
	this->m_B = 100 - this->m_B;
}

sf::Color TColor::toSF() const
{
	return sf::Color(static_cast<sf::Uint8>(m_R / 100 * 255), static_cast<sf::Uint8>(m_G / 100 * 255), static_cast<sf::Uint8>(m_B / 100 * 255));
}

TColor & TColor::Mix(const TColor& Rhs)
{
	this->m_R = (this->m_R + Rhs.m_R) / 2;
	this->m_G = (this->m_G + Rhs.m_G) / 2;
	this->m_B = (this->m_B + Rhs.m_B) / 2;
	return *this;
}

TColor& TColor::operator+=(const TColor& Rhs)
{
	this->m_R += Rhs.m_R;
	this->m_G += Rhs.m_G;
	this->m_B += Rhs.m_B;
	return *this;
}

const TColor TColor::White()
{
	return TColor(100.f, 100.f, 100.f);
}

const TColor TColor::Black()
{
	return TColor(0.f, 0.f, 0.f);
}

const TColor TColor::Red()
{
	return TColor(100.f, 0.f, 0.f);
}

const TColor TColor::Green()
{
	return TColor(0.f, 100.f, 0.f);
}

const TColor TColor::Blue()
{
	return TColor(0.f, 0.f, 100.f);
}
const TColor TColor::PeachPink()
{
	return TColor(97.6f, 58.4f, 51.8f);
}

TColor operator+(const TColor& Lhs, const TColor& Rhs)
{
	if (Lhs.m_Alpha == 100.f) {
		if (Rhs.m_Alpha == 100.f) {
			return TColor(Lhs.m_R + Rhs.m_R, Lhs.m_G + Rhs.m_G, Lhs.m_B + Rhs.m_B);
		}
		else {
			return TColor(Lhs.m_R + Rhs.m_R, Lhs.m_G + Rhs.m_G, Lhs.m_B + Rhs.m_B, Rhs.m_Alpha);

		}
	}
	else {
		if (Rhs.m_Alpha == 100.f) {

			return TColor(Lhs.m_R + Rhs.m_R, Lhs.m_G + Rhs.m_G, Lhs.m_B + Rhs.m_B, Lhs.m_Alpha);
		}
		else {

			return TColor(Lhs.m_R + Rhs.m_R, Lhs.m_G + Rhs.m_G, Lhs.m_B + Rhs.m_B,Rhs.m_Alpha + Lhs.m_Alpha);
		}
	}
}

TColor operator*(const TColor& Lhs, const TColor& Rhs)
{
	
	return TColor(Lhs.m_R * Rhs.m_R, Lhs.m_G * Rhs.m_G, Lhs.m_B * Rhs.m_B, Lhs.m_Alpha);
}

TColor operator*(const TColor & Lhs, const float & Rhs)
{
	return TColor(Lhs.m_R * Rhs, Lhs.m_G * Rhs, Lhs.m_B * Rhs, Lhs.m_Alpha);
}

TColor operator-(const TColor& Lhs, const TColor& Rhs)
{
	return TColor(Lhs.m_R - Rhs.m_R, Lhs.m_G - Rhs.m_G, Lhs.m_B - Rhs.m_B);
}

bool operator==(const TColor& Lhs, const TColor& Rhs)
{
  return  Lhs.m_R == Rhs.m_R
          && Lhs.m_G == Rhs.m_G
          && Lhs.m_B == Rhs.m_B;
}

TColor::TColor(vec3 a_RGB)
{
	this->m_R = a_RGB.m_X;
	this->m_G = a_RGB.m_Y;
	this->m_B = a_RGB.m_Z;
}

TColor::TColor(float a_R, float a_G, float a_B, float a_Alpha)
{
	this->m_R = a_R;
	this->m_G = a_G;
	this->m_B = a_B;
	this->m_Alpha = a_Alpha;
}