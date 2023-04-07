#include "BVHAcceleration.h"



BVHAcceleration::BVHAcceleration()
{
}


BVHAcceleration::~BVHAcceleration()
{
	delete m_Scene;
}

void BVHAcceleration::createTree(const std::vector<Object*>& a_Objects)
{
	if (m_Scene == NULL) {
		m_Scene = new BVHNode(a_Objects);
	}
	else {
		//This would be weird if this would be called
		printf("\nBVH Acceleration 'createTree is called a second time!\n");
	}
}

bool BVHAcceleration::Intersect(Ray & a_Ray)
{
	return m_Scene->Intersect(a_Ray);
}

