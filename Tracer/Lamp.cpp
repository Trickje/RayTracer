#include "Lamp.h"



Lamp::Lamp()
{
}


Lamp::~Lamp()
{
}

Lamp::Lamp(float a_X, float a_Y, float a_Z, Color a_Color)
{
	m_Position.m_X = a_X;
	m_Position.m_Y = a_Y;
	m_Position.m_Z = a_Z;
	m_Color = a_Color;
}

Lamp::Lamp(vec3 a_Pos, Color a_Color)
{
	m_Position.m_X = a_Pos.m_X;
	m_Position.m_Y = a_Pos.m_Y;
	m_Position.m_Z = a_Pos.m_Z;
	m_Color = a_Color;
}

vec3 Lamp::getPos()
{
	return m_Position;
}
