#include "BVHNode.h"
#include <algorithm>


BVHNode::BVHNode()
{
}


BVHNode::~BVHNode()
{

	if (m_BBox != NULL) {
		delete m_BBox;
	}
	
	if (m_LeftObject != NULL) {
		delete m_LeftObject;
	}
	if (m_RightObject != NULL) {
		delete m_RightObject;
	}
	
	if (m_LeftChild != NULL) {
		delete m_LeftChild;
	}
	if (m_RightChild != NULL) {
		delete m_RightChild;
	}
}

BVHNode::BVHNode(vec3 a_Min, vec3 a_Max) 
{
	m_BBox = new BoundingBox(a_Min, a_Max);
}

BVHNode::BVHNode(const std::vector<Object*>& a_Objects)
{
	if (a_Objects.size() < 3) {
		m_IsLeaf = true;
	}
	//Create the bounding box
	if (!a_Objects.empty()) {
		vec3 l_Min = a_Objects[0]->getPos();
		vec3 l_Max = a_Objects[0]->getPos();
		for (int o = 0; o < a_Objects.size(); o++) {
			vec3 obj_Min = a_Objects[o]->getBoundBox().getMin();
			vec3 obj_Max = a_Objects[o]->getBoundBox().getMax();
			//Set the minimum
			l_Min.m_X = std::min(l_Min.m_X, obj_Min.m_X);
			l_Min.m_Y = std::min(l_Min.m_Y, obj_Min.m_Y);
			l_Min.m_Z = std::min(l_Min.m_Z, obj_Min.m_Z);
			//Set the maximum
			l_Max.m_X = std::max(l_Max.m_X, obj_Max.m_X);
			l_Max.m_Y = std::max(l_Max.m_Y, obj_Max.m_Y);
			l_Max.m_Z = std::max(l_Max.m_Z, obj_Max.m_Z);
		}
		if (l_Min != l_Max) {
			m_BBox = new BoundingBox(l_Min, l_Max);
		}
	}
	else {
		m_IsLeaf = true;
		m_BBox = NULL;
		//ERROR
		//NO OBJECTS IN THE SCENE OR SOMETHING WENT BAD
	}
	//Created the bounding box
	if (m_IsLeaf) {
		//Do the stuff here that a Leaf should be doing
		if (a_Objects.size() > 0) {
			if (a_Objects.size() == 2) {
				//Divide the remaining 2 objects in the left or right object
				float l_XAxis = m_BBox->getMax().m_X - m_BBox->getMin().m_X;
				float l_YAxis = m_BBox->getMax().m_Y - m_BBox->getMin().m_Y;
				float l_ZAxis = m_BBox->getMax().m_Z - m_BBox->getMin().m_Z;
				if (l_XAxis < l_YAxis) {
					if (l_YAxis < l_ZAxis) {
						//Z Axis is the biggest
						if (a_Objects[0]->getPos().m_Z < a_Objects[1]->getPos().m_Z) {
							//Object 0 is the left object
							m_LeftObject = a_Objects[0];
							m_RightObject = a_Objects[1];
						}
						else {
							//Object 1 is the left object
							m_LeftObject = a_Objects[1];
							m_RightObject = a_Objects[0];
						}
						//Objects divided
					}
					else {
						//Y Axis is the biggest
						if (a_Objects[0]->getPos().m_Y < a_Objects[1]->getPos().m_Y) {
							//Object 0 is the left object
							m_LeftObject = a_Objects[0];
							m_RightObject = a_Objects[1];
						}
						else {
							//Object 1 is the left object
							m_LeftObject = a_Objects[1];
							m_RightObject = a_Objects[0];
						}
						//Objects divided
					}
				}
				else {
					if (l_XAxis < l_ZAxis) {
						//Z Axis is the biggest
						if (a_Objects[0]->getPos().m_Z < a_Objects[1]->getPos().m_Z) {
							//Object 0 is the left object
							m_LeftObject = a_Objects[0];
							m_RightObject = a_Objects[1];
						}
						else {
							//Object 1 is the left object
							m_LeftObject = a_Objects[1];
							m_RightObject = a_Objects[0];
						}
						//Objects divided
					}
					else {
						//X Axis is the biggest
						if (a_Objects[0]->getPos().m_X < a_Objects[1]->getPos().m_X) {
							//Object 0 is the left object
							m_LeftObject = a_Objects[0];
							m_RightObject = a_Objects[1];
						}
						else {
							//Object 1 is the left object
							m_LeftObject = a_Objects[1];
							m_RightObject = a_Objects[0];
						}
						//Objects divided
					}
				}
			}
			else {
				//1 Object!!!!!!!!!!!!!!!!
				m_LeftObject = a_Objects[0];
			}
		}
	}
	else {
		this->Branch(a_Objects);
		if (m_LeftChild != NULL && m_RightChild != NULL) {
			vec3 l_Min = m_LeftChild->m_BBox->getMin();
			l_Min.m_X = std::min(l_Min.m_X, m_RightChild->m_BBox->getMin().m_X);
			l_Min.m_Y = std::min(l_Min.m_Y, m_RightChild->m_BBox->getMin().m_Y);
			l_Min.m_Z = std::min(l_Min.m_Z, m_RightChild->m_BBox->getMin().m_Z);
			vec3 l_Max = m_LeftChild->m_BBox->getMax();
			l_Max.m_X = std::max(l_Max.m_X, m_RightChild->m_BBox->getMax().m_X);
			l_Max.m_Y = std::max(l_Max.m_Y, m_RightChild->m_BBox->getMax().m_Y);
			l_Max.m_Z = std::max(l_Max.m_Z, m_RightChild->m_BBox->getMax().m_Z);
			this->m_BBox->Resize(l_Min, l_Max);
		}
		else if (m_LeftChild != NULL) {
			this->m_BBox->Resize(m_LeftChild->m_BBox->getMin(), m_LeftChild->m_BBox->getMax());
		}
		else if (m_RightChild != NULL) {
			this->m_BBox->Resize(m_RightChild->m_BBox->getMin(), m_RightChild->m_BBox->getMax());
		}
		else {
			this->m_BBox->Resize(vec3(0.f,0.f,0.f), vec3(0.f,0.f,0.f));
		}
	}
}

bool BVHNode::Intersect(Ray & a_Ray)
{
	if (m_BBox == NULL) {
		return false;
	}
	float l_Distance;
	if (m_BBox != NULL && m_BBox->Intersects(a_Ray.m_RayInfo.m_Origin, a_Ray.m_RayInfo.m_Direction, l_Distance)) {
		if (m_IsLeaf) {

			//Check the objects in this for intersection
			float l_LeftDistance = -1.f;
			float l_RightDistance = -1.f;
			if (m_LeftObject != NULL) {
				m_LeftObject->Collides(a_Ray.m_RayInfo.m_Origin, a_Ray.m_RayInfo.m_Direction, l_LeftDistance);
			}
			if (m_RightObject != NULL) {
				m_RightObject->Collides(a_Ray.m_RayInfo.m_Origin, a_Ray.m_RayInfo.m_Direction, l_RightDistance);
			}
			if (l_LeftDistance > 0.f) {
				if (l_RightDistance > 0.f) {

					if (l_LeftDistance < l_RightDistance) {
						a_Ray.m_CollisionInfo.m_ClosestObject = m_LeftObject;
						a_Ray.m_CollisionInfo.m_Intersection = l_LeftDistance;
						a_Ray.m_CollisionInfo.m_IntersectionPoint = a_Ray.m_RayInfo.m_Origin + (a_Ray.m_RayInfo.m_Direction * l_LeftDistance);
						return true;
					}
					else {
						a_Ray.m_CollisionInfo.m_ClosestObject = m_RightObject;
						a_Ray.m_CollisionInfo.m_Intersection = l_RightDistance;
						a_Ray.m_CollisionInfo.m_IntersectionPoint = a_Ray.m_RayInfo.m_Origin + (a_Ray.m_RayInfo.m_Direction * l_RightDistance);
						return true;
					}
				}
				else {
					a_Ray.m_CollisionInfo.m_ClosestObject = m_LeftObject;
					a_Ray.m_CollisionInfo.m_Intersection = l_LeftDistance;
					a_Ray.m_CollisionInfo.m_IntersectionPoint = a_Ray.m_RayInfo.m_Origin + (a_Ray.m_RayInfo.m_Direction * l_LeftDistance);
					return true;
				}
			}
			else {
				if (l_RightDistance > 0.f) {
					a_Ray.m_CollisionInfo.m_ClosestObject = m_RightObject;
					a_Ray.m_CollisionInfo.m_Intersection = l_RightDistance;
					a_Ray.m_CollisionInfo.m_IntersectionPoint = a_Ray.m_RayInfo.m_Origin + a_Ray.m_RayInfo.m_Direction * l_RightDistance;
					return true;
				}
			} return false;
		}
		else {
			//Check the Child nodes in this for intersection
			if (m_LeftChild != NULL) {
				if (m_RightChild != NULL) {
					//Right AND Left child are made
					bool hitChild = false; 
					float l_LeftDistance = -1.f;
					float l_RightDistance = -1.f;
					Object* l_LeftObj = NULL;
					if (m_LeftChild->Intersect(a_Ray)) {
						l_LeftDistance = a_Ray.m_CollisionInfo.m_Intersection;
						l_LeftObj = a_Ray.m_CollisionInfo.m_ClosestObject;
						hitChild = true;
					}
					if (m_RightChild->Intersect(a_Ray)) {
						l_RightDistance = a_Ray.m_CollisionInfo.m_Intersection;
						hitChild = true;
					}
					if (l_LeftDistance > 0.f && l_RightDistance > 0.f && l_LeftDistance < l_RightDistance) {
						a_Ray.m_CollisionInfo.m_ClosestObject = l_LeftObj;
						a_Ray.m_CollisionInfo.m_Intersection = l_LeftDistance;
						a_Ray.m_CollisionInfo.m_IntersectionPoint = a_Ray.m_RayInfo.m_Origin + (a_Ray.m_RayInfo.m_Direction * l_LeftDistance);
					}

					return hitChild;
				}
				if (m_LeftChild->Intersect(a_Ray)) {
					return true;
				}
			}
			if (m_RightChild != NULL) {
				if (m_RightChild->Intersect(a_Ray)) {
					return true;
				}
			}

		}
	}

	return false;
}

bool BVHNode::Branch(const std::vector<Object*>& a_Objects)
{
	if (!m_IsLeaf) {
		if (!a_Objects.empty()) {
			vec3 l_Min = a_Objects[0]->getPos();
			vec3 l_Max = a_Objects[0]->getPos();
			for (int o = 0; o < a_Objects.size(); o++) {
				vec3 obj_Min = a_Objects[o]->getBoundBox().getMin();
				vec3 obj_Max = a_Objects[o]->getBoundBox().getMax();
				//Set the minimum
				l_Min.m_X = std::min(l_Min.m_X, obj_Min.m_X);
				l_Min.m_Y = std::min(l_Min.m_Y, obj_Min.m_Y);
				l_Min.m_Z = std::min(l_Min.m_Z, obj_Min.m_Z);
				//Set the maximum
				l_Max.m_X = std::max(l_Max.m_X, obj_Max.m_X);
				l_Max.m_Y = std::max(l_Max.m_Y, obj_Max.m_Y);
				l_Max.m_Z = std::max(l_Max.m_Z, obj_Max.m_Z);
			}
			if (l_Min != l_Max) {
				m_BBox = new BoundingBox(l_Min, l_Max);
			}
		}
		else {
			printf("ERROR BVHNODE CPP 60!");
			//ERROR
		}
		//Sort the Objects on the biggest axis of X Y and Z
		float l_XAxis = m_BBox->getMax().m_X - m_BBox->getMin().m_X;
		float l_YAxis = m_BBox->getMax().m_Y - m_BBox->getMin().m_Y;
		float l_ZAxis = m_BBox->getMax().m_Z - m_BBox->getMin().m_Z;
		std::vector<Object*> l_LeftObjects;
		std::vector<Object*> l_RightObjects;
		l_LeftObjects.reserve(a_Objects.size());
		l_RightObjects.reserve(a_Objects.size());
		if (l_XAxis < l_YAxis) {
			//X < Y
			if (l_YAxis < l_ZAxis) {
				//Z is the biggest
				float l_HalfZ = m_BBox->getMin().m_Z + (0.5f *l_ZAxis); //multiplying is cheaper than dividing
				//l_HalfZ is the Z in worldspace

				for (int o = 0; o < a_Objects.size(); o++) {
					if (a_Objects[o]->getPos().m_Z < l_HalfZ) {
						//Left side filling
						l_LeftObjects.push_back(a_Objects[o]);
					}
					else {
						//Right side filling
						l_RightObjects.push_back(a_Objects[o]);
					}
				}
				//The left and right side are now divided
			}
			else {
				//Y is the biggest
				float l_HalfY = m_BBox->getMin().m_Y + (0.5f *l_YAxis); //multiplying is cheaper than dividing
				//l_HalfY is the Y in worldspace

				for (int o = 0; o < a_Objects.size(); o++) {
					if (a_Objects[o]->getPos().m_Y < l_HalfY) {
						//Left side filling (Lowest side)
						l_LeftObjects.push_back(a_Objects[o]);
					}
					else {
						//Right side filling (Highest side)
						l_RightObjects.push_back(a_Objects[o]);
					}
				}
				//The left and right side are now divided

			}
		}
		else {
			//Y < X
			if (l_XAxis < l_ZAxis) {
				//Z is the biggest
				float l_HalfZ = m_BBox->getMin().m_Z + (0.5f *l_ZAxis); //multiplying is cheaper than dividing
				//l_HalfZ is the Z in worldspace

				for (int o = 0; o < a_Objects.size(); o++) {
					if (a_Objects[o]->getPos().m_Z < l_HalfZ) {
						//Left side filling
						l_LeftObjects.push_back(a_Objects[o]);
					}
					else {
						//Right side filling
						l_RightObjects.push_back(a_Objects[o]);
					}
				}
				//The left and right side are now divided

			}
			else {
				//X is the biggest
				float l_HalfX = m_BBox->getMin().m_X + (0.5f *l_XAxis); //multiplying is cheaper than dividing
				//l_HalfZ is the Z in worldspace

				for (int o = 0; o < a_Objects.size(); o++) {
					if (a_Objects[o]->getPos().m_X < l_HalfX) {
						//Left side filling
						l_LeftObjects.push_back(a_Objects[o]);
					}
					else {
						//Right side filling
						l_RightObjects.push_back(a_Objects[o]);
					}
				}
				//The left and right side are now divided

			}
		}
		if (l_LeftObjects.size() > 2 && l_RightObjects.empty()) {
			l_RightObjects.push_back(l_LeftObjects[l_LeftObjects.size() - 1]);
			l_LeftObjects.pop_back();
		}
		if (l_RightObjects.size() > 2 && l_LeftObjects.empty()) {
			l_LeftObjects.push_back(l_RightObjects[l_RightObjects.size() - 1]);
			l_RightObjects.pop_back();
		}
		//The Objects have been divided in either the right of left side
		//Now create the child nodes
		if (!l_LeftObjects.empty()) {
			m_LeftChild = new BVHNode(l_LeftObjects);
		}
		if (!l_RightObjects.empty()) {
			m_RightChild = new BVHNode(l_RightObjects);
		}
		if (m_LeftChild == NULL && m_RightChild == NULL) {
			printf("BIGGGG YIKES!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n\n\n\n");
		}
		l_LeftObjects.clear();
		l_RightObjects.clear();
	
	}
	return false;
}

