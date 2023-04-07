#pragma once
#include "Color.h"
class TColor;
class TLamp
{
public:
	TLamp();
	~TLamp();
	TLamp(float a_X, float a_Y, float a_Z, TColor a_Color);
	TLamp(vec3 a_Pos, TColor a_Color);
	vec3 getPos();
	TColor m_Color;
private:
	vec3 m_Position;
};

