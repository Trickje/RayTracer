#include "Camera.h"



Camera::Camera()
{
}


Camera::~Camera()
{
}

Ray Camera::shootRay(const int& a_X, const int& a_Y, const vec2& a_ScreenDimensions)
{
	float scale = static_cast<float>(tan((m_FOV / 180.f * 3.14) / 2.f));
	float aspectRatio = a_ScreenDimensions.m_X / a_ScreenDimensions.m_Y;
	float xPos = (2.f * (a_ScreenDimensions.m_X - a_X + 0.5f) / a_ScreenDimensions.m_X - 1.f) * aspectRatio * scale;
	float yPos = (2.f * (a_ScreenDimensions.m_Y - a_Y + 0.5f) / a_ScreenDimensions.m_Y - 1.f) * scale;
	return Ray(m_Position, (m_View * vec3(xPos, yPos, 1).normalize()));
	
}

Camera::Camera(mat4 lookAt, vec3 worldSpacePos)
{
	m_Position.m_X = worldSpacePos.m_X;
	m_Position.m_Y = worldSpacePos.m_Y;
	m_Position.m_Z = worldSpacePos.m_Z;
	this->m_View = lookAt;
}

vec3 const& Camera::getPos() const
{
	return m_Position;
}
