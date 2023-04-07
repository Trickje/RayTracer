#include "Lamp.h"



TLamp::TLamp()
{
}


TLamp::~TLamp()
{
}

TLamp::TLamp(float a_X, float a_Y, float a_Z, TColor a_Color)
{
	m_Position.m_X = a_X;
	m_Position.m_Y = a_Y;
	m_Position.m_Z = a_Z;
	m_Color = a_Color;
}

TLamp::TLamp(vec3 a_Pos, TColor a_Color)
{
	m_Position.m_X = a_Pos.m_X;
	m_Position.m_Y = a_Pos.m_Y;
	m_Position.m_Z = a_Pos.m_Z;
	m_Color = a_Color;
}

vec3 TLamp::getPos()
{
	return m_Position;
}
