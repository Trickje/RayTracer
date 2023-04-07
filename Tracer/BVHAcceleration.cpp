#include "BVHAcceleration.h"



TBVHAcceleration::TBVHAcceleration()
{
}


TBVHAcceleration::~TBVHAcceleration()
{
	delete m_Scene;
}

void TBVHAcceleration::createTree(const std::vector<TObject*>& a_Objects)
{
	if (m_Scene == NULL) {
		m_Scene = new TBVHNode(a_Objects);
	}
	else {
		//This would be weird if this would be called
		printf("\nBVH Acceleration 'createTree is called a second time!\n");
	}
}

bool TBVHAcceleration::Intersect(TRay& a_Ray)
{
	return m_Scene->Intersect(a_Ray);
}

