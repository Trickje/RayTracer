#include "BoundingBox.h"
#include <algorithm>
TBoundingBox::TBoundingBox() {

}

TBoundingBox::~TBoundingBox() {

}

TBoundingBox::TBoundingBox(const vec3& a_Min, const vec3& a_Max) {

	m_Min.m_X = std::min(a_Min.m_X, a_Max.m_X);
	m_Min.m_Y = std::min(a_Min.m_Y, a_Max.m_Y);
	m_Min.m_Z = std::min(a_Min.m_Z, a_Max.m_Z);

	m_Max.m_X = std::max(a_Min.m_X, a_Max.m_X);
	m_Max.m_Y = std::max(a_Min.m_Y, a_Max.m_Y);
	m_Max.m_Z = std::max(a_Min.m_Z, a_Max.m_Z);
}

bool TBoundingBox::Intersects(const vec3& a_Origin, const vec3& a_Direction, float& a_Distance) const{
	
	volatile float t1X = -1.f;
	volatile float t1Y = -1.f;
	volatile float t1Z = -1.f;
	volatile float t0X = -1.f;
	volatile float t0Y = -1.f;
	volatile float t0Z = -1.f;
	if (a_Direction.m_X <= 0.f) {
		t1X = (m_Min.m_X - a_Origin.m_X) / a_Direction.m_X;
		t0X = (m_Max.m_X - a_Origin.m_X) / a_Direction.m_X;
	}
	else {
		t1X = (m_Max.m_X - a_Origin.m_X) / a_Direction.m_X;
		t0X = (m_Min.m_X - a_Origin.m_X) / a_Direction.m_X;
	}
	if (a_Direction.m_Y <= 0.f) {
		t1Y = (m_Min.m_Y - a_Origin.m_Y) / a_Direction.m_Y;
		t0Y = (m_Max.m_Y - a_Origin.m_Y) / a_Direction.m_Y;
	}
	else {
		t1Y = (m_Max.m_Y - a_Origin.m_Y) / a_Direction.m_Y;
		t0Y = (m_Min.m_Y - a_Origin.m_Y) / a_Direction.m_Y;
	}
	if (a_Direction.m_Z <= 0.f) {
		t1Z = (m_Min.m_Z - a_Origin.m_Z) / a_Direction.m_Z;
		t0Z = (m_Max.m_Z - a_Origin.m_Z) / a_Direction.m_Z;
	}
	else {
		t1Z = (m_Max.m_Z - a_Origin.m_Z) / a_Direction.m_Z;
		t0Z = (m_Min.m_Z - a_Origin.m_Z) / a_Direction.m_Z;
	}
	

	if (t0X > t1Y || t0Y > t1X) {
		return false;
	}
	if (t0X > t1Z || t0Z > t1X) {
		return false;
	}
	if (t0Z > t1Y || t0Y > t1Z) {
		return false;
	}
	if (t1X < 0.f) {
		//No intersection
		return false;
	}
	if (t1Y < 0.f) {
		//No intersection
		return false;
	}
	if (t1Z < 0.f) {
		//No intersection
		return false;
	}

	float distMax;
	float distMin;
	//Max distance
	if (t1X < t1Y) {
		//t1Y is not used
		if (t1X < t1Z) {
			//t1X is the smallest of max
			distMax = t1X;
		}
		else {
			distMax = t1Z;
		}
	}
	else {
		//t1X is not used
		if (t1Y < t1Z) {
			//t1Y is the smallest of max
			distMax = t1Y;
		}
		else {
			//t1Z is the smallest of max
			distMax = t1Z;
		}
	}

	//Min distance
	if (t0X > t0Y) {
		//t1Y is not used
		if (t0X > t0Z) {
			//t1X is the biggest of min
			distMin = t0X;
		}
		else {
			distMin = t0Z;
		}
	}
	else {
		//t1X is not used
		if (t0Y > t0Z) {
			//t1Y is the biggest of min
			distMin = t0Y;
		}
		else {
			//t1Z is the biggest of min
			distMin = t0Z;
		}
	}
		if (distMin < distMax) {
			//Get the smallest of the two
			a_Distance = distMin;
			return true;
		}
		else {
			a_Distance = distMax;
			return true;
		}
}


bool TBoundingBox::Collides(const TBoundingBox& a_BBox) const{
	//Start with the X check
	if (a_BBox.m_Min.m_X >= m_Min.m_X) {
		if (a_BBox.m_Min.m_X <= m_Max.m_X) {
			//X check complete -> Y check
			if (a_BBox.m_Min.m_Y >= m_Min.m_Y) {
				if (a_BBox.m_Min.m_Y <= m_Max.m_Y) {
					//Y check complete -> Z check
					if (a_BBox.m_Min.m_Z >= m_Min.m_Z) {
						if (a_BBox.m_Min.m_Z <= m_Max.m_Z) {
							//Z check complete -> is inside the node
							return true;
						}
					}
				}
			}
		}
	}
	
	if (a_BBox.m_Max.m_X >= m_Min.m_X) {
		if (a_BBox.m_Max.m_X <= m_Max.m_X) {
			//X check complete -> Y check
			if (a_BBox.m_Max.m_Y >= m_Min.m_Y) {
				if (a_BBox.m_Max.m_Y <= m_Max.m_Y) {
					//Y check complete -> Z check
					if (a_BBox.m_Max.m_Z >= m_Min.m_Z) {
						if (a_BBox.m_Max.m_Z <= m_Max.m_Z) {
							//Z check complete -> is inside the node
							return true;
						}
					}
				}
			}
		}
	}

	return false;
}

const vec3& TBoundingBox::getMin() const
{
	return  m_Min;
}

const vec3& TBoundingBox::getMax() const
{
	return m_Max;
}

void TBoundingBox::Resize(const vec3& a_Min, const vec3& a_Max)
{
	this->m_Min = a_Min;
	this->m_Max = a_Max;
}
