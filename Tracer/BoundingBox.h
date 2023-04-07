#pragma once
#include "MathLibrary.h"

class TBoundingBox {
public:
	TBoundingBox();
	~TBoundingBox();
	TBoundingBox(const vec3& a_Min, const vec3& a_Max);
	bool Intersects(const vec3& a_Origin, const vec3& a_Direction, float& a_Distance) const;
	bool Collides(const TBoundingBox& a_BBox) const;
	const vec3& getMin() const;
	const vec3& getMax() const;
	void Resize(const vec3& a_Min, const vec3& a_Max);
private:
	vec3 m_Min;
	vec3 m_Max;
};