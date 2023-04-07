#pragma once
#include "Shapes.h"
class TObject;
class TBoundingBox;
class TRay;
class TBVHNode
{
public:
	TBVHNode();
	~TBVHNode();
	TBVHNode(vec3 a_Min, vec3 a_Max);
	TBVHNode(const std::vector<TObject*>& a_Objects);
	bool Intersect(TRay& a_Ray);
	bool Branch(const std::vector<TObject*>& a_Objects);
private:
	bool m_IsLeaf = false;

	TBoundingBox* m_BBox;
	//if m_IsLeaf == true
	TObject* m_LeftObject;
	TObject* m_RightObject;
	//if m_IsLeaf == false
	TBVHNode* m_LeftChild;
	TBVHNode* m_RightChild;

};

