#pragma once
#include "Color.h"
#include "Shapes.h"
#include "BoundingBox.h"
#include "Lamp.h"
#include <vector>
#include "BVHNode.h"
#include "BVHAcceleration.h"


static const int MAXREFLECTIONS = 3;
class TObject;
class TSphere;
class TPlane;
class TBoundingBox;
class TBVHAcceleration;

struct TCollisionInfo {
	TObject* m_ClosestObject = NULL;
	vec3 m_IntersectionPoint = vec3();
	float m_Intersection = - 1.f;
};
struct TColorInfo {
	TColor m_FinalColor = TColor::Black();
	TColor m_SpecularColor = TColor::Black();
	TColor m_DiffuseColor = TColor::Black();
	float m_LightLevel = 1.f;
};
struct TRayInfo {

	int m_Reflecting = 0;	//Bounces the ray has made
	vec3 m_Origin = vec3();	//Start coordinates
	vec3 m_Direction = vec3();	//Unit vector
	float m_N1 = 1.000293f; //refractive index
};
class TRay
{
public:
	TRay();
	TRay(vec3 a_Origin, vec3 a_Direction);
	~TRay();
	void setPlane(TPlane* a_Plane);
	void Trace(const std::vector<TLamp*> a_Lamps);
	void Trace(const std::vector<TObject*> &a_Objects, const std::vector<TLamp*> a_Lamps);
	bool Collides(const std::vector<TObject*> &a_Objects);
	bool Diffuse(const std::vector<TLamp*> &a_Lamps);
	bool Specular(const std::vector<TLamp*> &a_Lamps);
	bool Reflection(const std::vector<TObject*>& a_Objects, const  std::vector<TLamp*> &a_Lamps);
	bool Refraction(const std::vector<TObject*>& a_Objects, const std::vector<TLamp*> &a_Lamps);
	bool anotherRay(TBVHAcceleration& a_BVH, const std::vector<TLamp*> a_Lamps);
	sf::Color getSFColor();
	TCollisionInfo m_CollisionInfo;
	TColorInfo m_ColorInfo;
	TRayInfo m_RayInfo;
	TRay* m_SecondaryRay = NULL; //Check out if this is needed?
private:
	TPlane* m_Plane;
	
};
