#pragma once
#include "Ray.h"
class TRay;
class TBoundingBox;

enum types {
	t_Plane = 100,
	t_Sphere = 101,
	t_Cube = 102
};

//2D
class TObject {
public:
	virtual ~TObject() {};
	virtual const TColor& getColor() const = 0;
	virtual sf::Color getSFColor() const = 0;
	virtual bool Collides(const vec3& a_Origin, const vec3& a_Direction, float& a_IntersectPoint) = 0;
	virtual vec3 getPos() const = 0;
	virtual TColor Specular(const vec3& a_IntersectionPoint, const vec3& a_LampPos, const TRay& a_Ray) = 0;
	virtual vec3 getNormal(const vec3& a_IntersectionPoint) const = 0;
	virtual float const& getReflectiveness() const = 0;
	virtual int getType() const = 0;
	virtual float getRefractionIndex() const = 0;
	virtual float getRadius() const = 0;
	virtual TBoundingBox getBoundBox() const = 0;
protected:
	vec3 m_Position;
	TColor m_Color;
	float m_Reflectiveness;
};

class TPlane : public TObject {
public:
	TPlane();
	TPlane(const vec3& a_Position, const vec3& a_Up, const TColor& a_Color);
	TPlane(const vec3& a_Position, const vec3& a_Up, const TColor& a_Color, const float& a_Reflectiveness);
	~TPlane();
	bool intersect(const TRay& a_Ray);
  const TColor& getColor() const;
	sf::Color getSFColor() const;
	bool Collides(const vec3& a_Origin, const vec3& a_Direction, float& a_IntersectionPoint);
	vec3 getPos() const;
	TColor Specular(const vec3& a_IntersectionPoint, const vec3& a_LampPos, const TRay& a_Ray);
	vec3 getNormal(const vec3& a_IntersectionPoint) const;
	float const& getReflectiveness() const;
	int getType() const;
	float getRefractionIndex() const { return -1.f; };
	float getRadius() const { return -1.f; };
	TBoundingBox getBoundBox() const;
private:
	vec3 m_Up;
};

class TCube : public TObject {
public:
	TCube();
	TCube(const vec3& a_Position, const vec3& a_Rotation, const vec3& a_Size, const TColor& a_Color);
	TCube(const vec3& a_Position, const vec3& a_Rotation, const vec3& a_Size, int a_MaterialType);
	~TCube();
	bool Collides(const vec3& a_Origin, const vec3& a_Direction, float& a_Intersection);
  const TColor& getColor() const;
	sf::Color getSFColor() const;
	vec3 getPos() const;
	TColor Specular(const vec3& a_IntersectionPoint, const vec3& a_LampPos, const TRay& a_Ray);
	vec3 getNormal(const vec3& a_IntersectionPoint) const;
	float const& getReflectiveness() const;
	int getType() const;
	float getRefractionIndex() const { return m_RefractionIndex; };
	float getRadius() const { return -1.f; };
	TBoundingBox getBoundBox() const;
private:
	mat4 m_Transformation;
	mat4 m_InverseTransformation;
	vec3 m_Rotation;
	vec3 m_Up;
	vec3 m_Forward;
	vec3 m_Right;
	vec3 m_Size;
	TBoundingBox* m_BBox = NULL;
	float m_RefractionIndex = 0.f;
};

class TSphere : public TObject{
public:
	TSphere();
	TSphere(const float& a_X, const float& a_Y, const float& a_Z, const float& a_Radius, const TColor& a_Color);
	TSphere(const vec3& a_Coords, const float& a_Radius, const TColor& a_Color);
	TSphere(const vec3& a_Coords, const float& a_Radius, const TColor& a_Color, const float& a_Reflectiveness);
	TSphere(const vec3& a_Coords, const float& a_Radius, const int& a_MaterialType);
	~TSphere();
	bool Collides(const vec3& a_Origin, const vec3& a_Direction, float& a_IntersectPoint);
	sf::Color getSFColor() const;
  const TColor& getColor() const;
	vec3 getPos() const;
	TColor Specular(const vec3& a_IntersectionPoint, const vec3& a_LampPos, const TRay& a_Ray);
	vec3 getNormal(const vec3& a_IntersectionPoint) const;
	float const& getReflectiveness() const;
	int getType() const;
	float getRefractionIndex() const;
	float getRadius() const;
	TBoundingBox getBoundBox() const;
private:
	float m_Radius;
	float m_RefractionIndex;
};

