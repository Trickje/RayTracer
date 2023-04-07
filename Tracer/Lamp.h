#pragma once
#include "Color.h"
class Color;
class Lamp
{
public:
	Lamp();
	~Lamp();
	Lamp(float a_X, float a_Y, float a_Z, Color a_Color);
	Lamp(vec3 a_Pos, Color a_Color);
	vec3 getPos();
	Color m_Color;
private:
	vec3 m_Position;
};

