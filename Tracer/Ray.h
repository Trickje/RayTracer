#pragma once
#include "Color.h"
#include "Shapes.h"
#include "BoundingBox.h"
#include "Lamp.h"
#include <vector>
#include "BVHNode.h"
#include "BVHAcceleration.h"


static const int MAXREFLECTIONS = 3;
class Object;
class Sphere;
class Plane;
class BoundingBox;
class BVHAcceleration;

struct CollisionInfo {
	Object* m_ClosestObject = NULL;
	vec3 m_IntersectionPoint = vec3();
	float m_Intersection = - 1.f;
};
struct ColorInfo {
	Color m_FinalColor = Color::Black();
	Color m_SpecularColor = Color::Black();
	Color m_DiffuseColor = Color::Black();
	float m_LightLevel = 1.f;
};
struct RayInfo {

	int m_Reflecting = 0;	//Bounces the ray has made
	vec3 m_Origin = vec3();	//Start coordinates
	vec3 m_Direction = vec3();	//Unit vector
	float m_N1 = 1.000293f; //refractive index
};
class Ray
{
public:
	Ray();
	Ray(vec3 a_Origin, vec3 a_Direction);
	~Ray();
	void setPlane(Plane* a_Plane);
	void Trace(const std::vector<Lamp*> a_Lamps);
	void Trace(const std::vector<Object*> &a_Objects, const std::vector<Lamp*> a_Lamps);
	bool Collides(const std::vector<Object*> &a_Objects);
	bool Diffuse(const std::vector<Lamp*> &a_Lamps);
	bool Specular(const std::vector<Lamp*> &a_Lamps);
	bool Reflection(const std::vector<Object*>& a_Objects, const  std::vector<Lamp*> &a_Lamps);
	bool Refraction(const std::vector<Object*>& a_Objects, const std::vector<Lamp*> &a_Lamps);
	bool anotherRay(BVHAcceleration& a_BVH, const std::vector<Lamp*> a_Lamps);
	sf::Color getSFColor();
	CollisionInfo m_CollisionInfo;
	ColorInfo m_ColorInfo;
	RayInfo m_RayInfo;
	Ray* m_SecondaryRay = NULL;
private:
	Plane* m_Plane;
	
};
