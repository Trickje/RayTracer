#pragma once
#include "Ray.h"
class Camera
{
public:
	Camera();
//	Camera(float x, float y, float z);
	Camera(mat4 lookAt, vec3 worldSpacePos);
	vec3 const& getPos() const;
	~Camera();
	Ray shootRay(const int& a_X, const int& a_Y, const vec2& a_ScreenDimensions);
	mat4 m_View;
private:
	float m_FOV = 70.f;
	vec3 m_Position;
}

;
