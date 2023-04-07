#pragma once
#include "BVHNode.h"
#include "Ray.h"
#include "Shapes.h"

class TObject;
class TBVHNode;
class TRay;

class TBVHAcceleration
{
public:
	TBVHAcceleration();
	~TBVHAcceleration();
	void createTree(const std::vector<TObject*>& a_Objects);
	bool Intersect(TRay& a_Ray);

private:
	TBVHNode* m_Scene = NULL;
	
};

