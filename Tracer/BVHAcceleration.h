#pragma once
#include "BVHNode.h"
#include "Ray.h"
#include "Shapes.h"

class Object;
class BVHNode;
class Ray;

class BVHAcceleration
{
public:
	BVHAcceleration();
	~BVHAcceleration();
	void createTree(const std::vector<Object*>& a_Objects);
	bool Intersect(Ray& a_Ray);

private:
	BVHNode* m_Scene = NULL;
	
};

