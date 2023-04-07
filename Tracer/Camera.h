#pragma once
#include "Ray.h"
class TCamera
{
public:
	TCamera();
//	Camera(float x, float y, float z);
	TCamera(mat4 lookAt, vec3 worldSpacePos);
	vec3 const& getPos() const;
	~TCamera();
	TRay shootRay(const int& a_X, const int& a_Y, const vec2& a_ScreenDimensions);
	mat4 m_View;
private:
	float m_FOV = 70.f;
	vec3 m_Position;
}

;
