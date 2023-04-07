#pragma once
#include "MathLibrary.h"
class BoundingBox {
public:
	BoundingBox();
	~BoundingBox();
	BoundingBox(const vec3& a_Min, const vec3& a_Max);
	bool Intersects(const vec3& a_Origin, const vec3& a_Direction, float& a_Distance) const;
	bool Collides(const BoundingBox& a_BBox) const;
	vec3 const& getMin() const;
	vec3 const& getMax() const;
	void Resize(const vec3& a_Min, const vec3& a_Max);
private:
	vec3 m_Min;
	vec3 m_Max;
};