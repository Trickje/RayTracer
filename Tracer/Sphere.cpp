#include "Shapes.h"
#include <iostream>
#include "MathLibrary.h"
#include "Ray.h"
#include <math.h>
#include <algorithm>
#include <random>
#include <time.h>
#include <chrono>

TSphere::TSphere() {
	//Predefined bounds:
	std::mt19937 generator(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
	std::uniform_int_distribution<unsigned int> dist(1, 100);
	int randomNumberX = dist(generator);
	float randomFloatX = static_cast<float>(randomNumberX) / 12.5f;

	int randomMultiply = dist(generator);
	float l_Multiply = static_cast<float>(randomMultiply) / 50.f;
	int randomNumberZ = dist(generator);
	float randomFloatZ = static_cast<float>(randomNumberZ) / 12.5f;
	int randomNumberNegativeX = dist(generator);
	if (randomNumberNegativeX < 50) {
		this->m_Position.m_X = (randomFloatX * 3.f);
	}
	else {

		this->m_Position.m_X = -(randomFloatX * 3.f);
	}
	int randomNumberNegativeZ = dist(generator);
	if (randomNumberNegativeZ < 50) {
		this->m_Position.m_Z = (randomFloatZ * 3.f);
	}
	else {
		this->m_Position.m_Z = -(randomFloatZ * 3.f);
	}
	//int randomNumberY = dist(generator);
	//float randomFloatY = static_cast<float>(randomNumberY) / 30.0f;
	this->m_Radius = 0.3f;
	this->m_Position.m_Y = 0.3f;

		float l_Multiplication = (3.f + l_Multiply * 2.f) / m_Position.length();
		if (m_Position.m_X > 0.f) {
			m_Position.m_X *= l_Multiplication;
		}
		else {
			m_Position.m_X *= l_Multiplication;
		}
		if (m_Position.m_Z > 0.f) {
			m_Position.m_Z *= l_Multiplication;
		}
		else {
			m_Position.m_Z *= l_Multiplication;
		}
	

	int randomR = dist(generator);
	int randomG = dist(generator);
	int randomB = dist(generator);
	this->m_Reflectiveness = 0.f;
	this->m_RefractionIndex = 0.f;
	m_Color = TColor(static_cast<float>(randomR), static_cast<float>(randomG), static_cast<float>(randomB));
	m_Color.KeepItReal();
}

TSphere::TSphere(const float& a_X, const float& a_Y, const float& a_Z, const float& a_Radius, const TColor& a_Color) {
	this->m_Position.m_X = a_X;
	this->m_Position.m_Y = a_Y;
	this->m_Position.m_Z = a_Z;
	this->m_Radius = a_Radius;
	this->m_Color = a_Color;
	this->m_Reflectiveness = 0.f;
}

TSphere::TSphere(const vec3& a_Coords, const float& a_Radius, const TColor& a_Color) {
	this->m_Position.m_X = a_Coords.m_X;
	this->m_Position.m_Y = a_Coords.m_Y;
	this->m_Position.m_Z = a_Coords.m_Z;
	this->m_Radius = a_Radius;
	this->m_Color = a_Color;
	this->m_Reflectiveness = 0.f;
}

TSphere::TSphere(const vec3& a_Coords, const float& a_Radius, const TColor& a_Color, const float& a_Reflectiveness)
{
	this->m_Position.m_X = a_Coords.m_X;
	this->m_Position.m_Y = a_Coords.m_Y;
	this->m_Position.m_Z = a_Coords.m_Z;
	this->m_Radius = a_Radius;
	this->m_Color = a_Color;
	this->m_Reflectiveness = a_Reflectiveness;
}

TSphere::TSphere(const vec3& a_Coords, const float& a_Radius, const int& a_MaterialType)
{
	this->m_Position.m_X = a_Coords.m_X;
	this->m_Position.m_Y = a_Coords.m_Y;
	this->m_Position.m_Z = a_Coords.m_Z;
	this->m_Radius = a_Radius;
	this->m_Reflectiveness = 0.f;
	this->m_RefractionIndex = 0.f;
	switch (a_MaterialType) {
	case 10:
		this->m_RefractionIndex = 1.52f;
		break;
	case 20:
		this->m_Reflectiveness = 100.f;
	}
}

TSphere::~TSphere() {

}

bool TSphere::Collides(const vec3& a_Origin, const vec3& a_Direction, float& a_IntersectPoint) {

	//l = the distance between the camera and the sphere center
	vec3 l = a_Origin - m_Position;
	//a is the a in the Discriminant calculation
	//is actually 1 
	float a = 1.f;
	float b = a_Direction.dot(l) * 2;
	float c = l.dot(l) - m_Radius * m_Radius;
	float D = b*b - 4 * a * c;
	if (D > 0) {
		a_IntersectPoint = (-b - sqrt(D)) / 2 * a;
		float intersect2 = (-b + sqrt(D)) / 2 * a;
		if (a_IntersectPoint > intersect2) {
			a_IntersectPoint = intersect2;
		}//printf("intersectionPoint:\t%f\n", intersectPoint);

		return true;
	}
	if (D == 0) {
		//1 collision x = -b / 2a;
		a_IntersectPoint = -b / (2 * a);
		return true;
	}
	if (D < 0) {
		return false;
	}
	return false;
}

sf::Color TSphere::getSFColor() const
{
	return sf::Color(static_cast<sf::Uint8>(m_Color.m_R), static_cast<sf::Uint8>(m_Color.m_G), static_cast<sf::Uint8>(m_Color.m_B), static_cast<sf::Uint8>(m_Color.m_Alpha));
}

const TColor& TSphere::getColor() const {

	return m_Color;
}

vec3 TSphere::getPos() const{
	return m_Position;
}

TColor TSphere::Specular(const vec3& a_IntersectionPoint, const vec3& a_LampPos, const TRay& a_Ray)
{
	//Add materials later
	float specular = 0.2f;
	//Surface normal
	vec3 normal = (a_IntersectionPoint - m_Position) / m_Radius;
	//h calculations
	vec3 l = (a_LampPos - a_IntersectionPoint).normalize();
	vec3 v = (a_Ray.m_RayInfo.m_Origin - a_IntersectionPoint).normalize();
	vec3 h = (v + l) / (v + l).length();
	//Calculating the difference of h and normal
	float L = specular * pow(std::max(normal.dot(h), 0.f),100);

	return TColor(100 * L, 100 * L, 100 * L);
}

vec3 TSphere::getNormal(const vec3& a_IntersectionPoint) const
{
	return vec3(a_IntersectionPoint - m_Position);
}

float const& TSphere::getReflectiveness() const
{
	return m_Reflectiveness;
}

int TSphere::getType() const
{
	return t_Sphere;
}

float TSphere::getRefractionIndex() const
{
	return m_RefractionIndex;
}

float TSphere::getRadius() const
{
	return this->m_Radius;
}

TBoundingBox TSphere::getBoundBox() const
{
	return TBoundingBox(vec3(this->m_Position.m_X - this->m_Radius, this->m_Position.m_Y - this->m_Radius, this->m_Position.m_Z - this->m_Radius), vec3(this->m_Position.m_X + this->m_Radius, this->m_Position.m_Y + this->m_Radius, this->m_Position.m_Z + this->m_Radius));
}


