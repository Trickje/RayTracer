#pragma once
#include "Ray.h"
class Ray;
class BoundingBox;
enum types {
	t_Plane = 100,
	t_Sphere = 101,
	t_Cube = 102
};

//2D
class Object {
public:
	virtual ~Object() {};
	virtual Color const& getColor() const = 0;
	virtual sf::Color getSFColor() const = 0;
	virtual bool Collides(const vec3& a_Origin, const vec3& a_Direction, float& a_IntersectPoint) = 0;
	virtual vec3 getPos() const = 0;
	virtual Color Specular(const vec3& a_IntersectionPoint, const vec3& a_LampPos, const Ray& a_Ray) = 0;
	virtual vec3 getNormal(const vec3& a_IntersectionPoint) const = 0;
	virtual float const& getReflectiveness() const = 0;
	virtual int getType() const = 0;
	virtual float getRefractionIndex() const = 0;
	virtual float getRadius() const = 0;
	virtual BoundingBox getBoundBox() const = 0;
protected:
	vec3 m_Position;
	Color m_Color;
	float m_Reflectiveness;
};
class Plane : public Object {
public:
	Plane();
	Plane(const vec3& a_Position, const vec3& a_Up, const Color& a_Color);
	Plane(const vec3& a_Position, const vec3& a_Up, const Color& a_Color, const float& a_Reflectiveness);
	~Plane();
	bool intersect(const Ray& a_Ray);
	Color const& getColor() const;
	sf::Color getSFColor() const;
	bool Collides(const vec3& a_Origin, const vec3& a_Direction, float& a_IntersectionPoint);
	vec3 getPos() const;
	Color Specular(const vec3& a_IntersectionPoint, const vec3& a_LampPos, const Ray& a_Ray);
	vec3 getNormal(const vec3& a_IntersectionPoint) const;
	float const& getReflectiveness() const;
	int getType() const;
	float getRefractionIndex() const { return -1.f; };
	float getRadius() const { return -1.f; };
	BoundingBox getBoundBox() const;
private:
	vec3 m_Up;
};
class Cube : public Object {
public:
	Cube();
	Cube(const vec3& a_Position, const vec3& a_Rotation, const vec3& a_Size, const Color& a_Color);
	Cube(const vec3& a_Position, const vec3& a_Rotation, const vec3& a_Size, int a_MaterialType);
	~Cube();
	bool Collides(const vec3& a_Origin, const vec3& a_Direction, float& a_Intersection);
	Color const& getColor() const;
	sf::Color getSFColor() const;
	vec3 getPos() const;
	Color Specular(const vec3& a_IntersectionPoint, const vec3& a_LampPos, const Ray& a_Ray);
	vec3 getNormal(const vec3& a_IntersectionPoint) const;
	float const& getReflectiveness() const;
	int getType() const;
	float getRefractionIndex() const { return m_RefractionIndex; };
	float getRadius() const { return -1.f; };
	BoundingBox getBoundBox() const;
private:
	mat4 m_Transformation;
	mat4 m_InverseTransformation;
	vec3 m_Rotation;
	vec3 m_Up;
	vec3 m_Forward;
	vec3 m_Right;
	vec3 m_Size;
	BoundingBox* m_BBox = NULL;
	float m_RefractionIndex = 0.f;
};
class Sphere : public Object{
public:
	Sphere();
	Sphere(const float& a_X, const float& a_Y, const float& a_Z, const float& a_Radius, const Color& a_Color);
	Sphere(const vec3& a_Coords, const float& a_Radius, const Color& a_Color);
	Sphere(const vec3& a_Coords, const float& a_Radius, const Color& a_Color, const float& a_Reflectiveness);
	Sphere(const vec3& a_Coords, const float& a_Radius, const int& a_MaterialType);
	~Sphere();
	bool Collides(const vec3& a_Origin, const vec3& a_Direction, float& a_IntersectPoint);
	sf::Color getSFColor() const;
	Color const& getColor() const;
	vec3 getPos() const;
	Color Specular(const vec3& a_IntersectionPoint, const vec3& a_LampPos, const Ray& a_Ray);
	vec3 getNormal(const vec3& a_IntersectionPoint) const;
	float const& getReflectiveness() const;
	int getType() const;
	float getRefractionIndex() const;
	float getRadius() const;
	BoundingBox getBoundBox() const;
private:
	float m_Radius;
	float m_RefractionIndex;
};

