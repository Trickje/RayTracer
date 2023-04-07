#include "Shapes.h"
#include <iostream>
TPlane::TPlane() {

}

TPlane::~TPlane() {

}

TPlane::TPlane(const vec3& a_Position, const vec3&  a_Up, const TColor& a_Color) {
	m_Position = a_Position;
	m_Up = a_Up;
	m_Color = a_Color;
}

TPlane::TPlane(const vec3& a_Position, const vec3& a_Up, const TColor& a_Color, const float& a_Reflectiveness)
{
	m_Position = a_Position;
	m_Up = a_Up;
	m_Color = a_Color;
	m_Reflectiveness = a_Reflectiveness;
}

bool TPlane::intersect(const TRay& a_Ray) {
	if (a_Ray.m_RayInfo.m_Reflecting < 3) {
		return true;
	}
	return false;
}

const TColor& TPlane::getColor() const
{
	return m_Color;
}
sf::Color TPlane::getSFColor() const
{
	return m_Color.toSF();
}
bool TPlane::Collides(const vec3& a_Origin, const vec3& a_Direction, float & a_IntersectionPoint)
{
	float dot = -m_Up.dot(a_Direction);
	vec3 w = a_Origin - m_Position;
	if (dot < 0) {
		return false; 
	}else if (dot > 0.0001f) {
		a_IntersectionPoint = w.dot(m_Up) / dot;
			return true;
		
	}
	return false;
}

vec3 TPlane::getPos() const
{
	return m_Position;
}

TColor TPlane::Specular(const vec3& a_IntersectionPoint, const vec3& a_LampPos, const TRay& a_Ray)
{
	//Got this from https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_shading_model
	//Add materials later
	float specular = 0.2f;
	//Surface normal
	vec3 normal = m_Up.normalize();
	//h calculations
	vec3 l = (a_LampPos - a_IntersectionPoint);
	vec3 v = (a_Ray.m_RayInfo.m_Origin - a_IntersectionPoint);
	vec3 h = (v + l) / (v + l).length();
	//Calculating the difference of h and normal
	float L = specular * pow(std::max(normal.dot(h), 0.f), 100);

	return TColor(100 * L, 100 * L, 100 * L);
}

vec3 TPlane::getNormal(const vec3& a_IntersectionPoint) const
{
	a_IntersectionPoint;
	return m_Up;
}

float const& TPlane::getReflectiveness() const
{
	return m_Reflectiveness;
}

int TPlane::getType() const
{
	return t_Plane;
}

TBoundingBox TPlane::getBoundBox() const
{
	return TBoundingBox(vec3(0.f, 0.f, 0.f), vec3(0.f, 0.f, 0.f));
}


