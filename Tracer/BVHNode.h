#pragma once
#include "Shapes.h"
class Object;
class BoundingBox;
class Ray;
class BVHNode
{
public:
	BVHNode();
	~BVHNode();
	BVHNode(vec3 a_Min, vec3 a_Max);
	BVHNode(const std::vector<Object*>& a_Objects);
	bool Intersect(Ray& a_Ray);
	bool Branch(const std::vector<Object*>& a_Objects);
private:
	bool m_IsLeaf = false;

	BoundingBox* m_BBox;
	//if m_IsLeaf == true
	Object* m_LeftObject;
	Object* m_RightObject;
	//if m_IsLeaf == false
	BVHNode* m_LeftChild;
	BVHNode* m_RightChild;

};

