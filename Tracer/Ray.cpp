#include "Ray.h"
Ray::Ray()
{
}


Ray::~Ray()
{
	if (m_SecondaryRay != NULL) {
		delete m_SecondaryRay;
	}
}

void Ray::setPlane(Plane * a_Plane)
{
	m_Plane = a_Plane;
}

void Ray::Trace(const std::vector<Lamp*> a_Lamps)
{
		if (this->m_CollisionInfo.m_ClosestObject != NULL) {
			float l_PlaneDistance = 999.f;
			m_Plane->Collides(m_RayInfo.m_Origin, m_RayInfo.m_Direction, l_PlaneDistance);
			if (m_CollisionInfo.m_Intersection < l_PlaneDistance) {
				//Not the plane
				this->Diffuse(a_Lamps);
				this->Specular(a_Lamps);
				this->m_ColorInfo.m_FinalColor = this->m_ColorInfo.m_DiffuseColor + this->m_ColorInfo.m_SpecularColor;
				this->m_ColorInfo.m_FinalColor.KeepItReal();
				this->m_ColorInfo.m_FinalColor.KeepItReal();
				
			}
			else {
				//Plane
				this->m_CollisionInfo.m_ClosestObject = m_Plane;
				this->m_CollisionInfo.m_Intersection = l_PlaneDistance;
				this->m_CollisionInfo.m_IntersectionPoint = this->m_RayInfo.m_Origin + (this->m_RayInfo.m_Direction * l_PlaneDistance);

				this->Diffuse(a_Lamps);
				this->m_ColorInfo.m_FinalColor = this->m_ColorInfo.m_DiffuseColor;
			}
		}
		else {
			if (m_Plane->Collides(m_RayInfo.m_Origin, m_RayInfo.m_Direction, this->m_CollisionInfo.m_Intersection)) {

				this->m_CollisionInfo.m_ClosestObject = m_Plane;
				this->m_CollisionInfo.m_IntersectionPoint = this->m_RayInfo.m_Origin + (this->m_RayInfo.m_Direction * this->m_CollisionInfo.m_Intersection);

				this->Diffuse(a_Lamps);
				this->m_ColorInfo.m_FinalColor = this->m_ColorInfo.m_DiffuseColor;
			}
			else {
				m_ColorInfo.m_FinalColor = Color::Black();
			}
		}
		if (m_SecondaryRay != NULL) {
			this->m_ColorInfo.m_FinalColor += m_SecondaryRay->m_ColorInfo.m_FinalColor;
			this->m_ColorInfo.m_FinalColor.KeepItReal();
		}
}

void Ray::Trace(const std::vector<Object*>& a_Objects, const std::vector<Lamp*> a_Lamps)
{
	this->Collides(a_Objects);
	if (this->m_CollisionInfo.m_ClosestObject == 0) {
		this->m_ColorInfo.m_FinalColor = Color::Black();
	}
	else {
		if (this->m_CollisionInfo.m_ClosestObject->getType() == t_Plane) {
			this->Diffuse(a_Lamps);
			this->m_ColorInfo.m_FinalColor = this->m_ColorInfo.m_DiffuseColor;
		}
		else {
			if (this->m_CollisionInfo.m_ClosestObject->getRefractionIndex() > 0.f) {
				this->Refraction(a_Objects, a_Lamps);
				this->m_ColorInfo.m_FinalColor.KeepItReal();
			}
			else {
				this->Diffuse(a_Lamps);
				this->Specular(a_Lamps);

				this->m_ColorInfo.m_FinalColor = this->m_ColorInfo.m_DiffuseColor + this->m_ColorInfo.m_SpecularColor;
				this->m_ColorInfo.m_FinalColor.KeepItReal();
				this->Reflection(a_Objects, a_Lamps);
				this->m_ColorInfo.m_FinalColor.KeepItReal();
			}
		}
	}
	if (m_SecondaryRay != NULL) {
		this->m_ColorInfo.m_FinalColor += m_SecondaryRay->m_ColorInfo.m_FinalColor;
		this->m_ColorInfo.m_FinalColor.KeepItReal();
	}
}

bool Ray::Collides(const std::vector<Object*> &a_Objects)
{
	std::vector<Object*> tempObjects = a_Objects;
	tempObjects.push_back(m_Plane);
	float dist = 100.f;
	for (int o = 0; o < tempObjects.size(); o++) {
		if (tempObjects[o]->Collides(this->m_RayInfo.m_Origin, this->m_RayInfo.m_Direction, this->m_CollisionInfo.m_Intersection)) {
			if (this->m_CollisionInfo.m_Intersection > 0) {
				vec3 tempIntersectionPoint = this->m_RayInfo.m_Origin + (this->m_RayInfo.m_Direction * this->m_CollisionInfo.m_Intersection);
				bool newdist = false;
				if (tempIntersectionPoint != vec3(0.f, 0.f, 0.f))
					if (tempIntersectionPoint.length() < dist) {
						newdist = true;
						this->m_CollisionInfo.m_ClosestObject = tempObjects[o];
						this->m_CollisionInfo.m_IntersectionPoint = tempIntersectionPoint;
					}
				if (newdist) {
					dist = this->m_CollisionInfo.m_IntersectionPoint.length();
				}
			}
		}
	}
	if (dist < 100.f) { return true; }
	else { return false; }
}

bool Ray::Diffuse(const std::vector<Lamp*> &a_Lamps)
{
	Color objectColor;
	objectColor = this->m_CollisionInfo.m_ClosestObject->getColor();
	if (this->m_CollisionInfo.m_ClosestObject->getType() == t_Plane) {
		//Plane
		//TileSize is 2x2 
		float tileSize = 1.f;
		float xCol = this->m_CollisionInfo.m_IntersectionPoint.m_X;
		float zCol = this->m_CollisionInfo.m_IntersectionPoint.m_Z;

		if (xCol < 0.f) {
			xCol = xCol * -1.f + (0.5f * tileSize);
		}if (zCol < 0.f) {
			zCol = zCol * -1.f + (0.5f * tileSize);
		}

		int xMultiply = static_cast<int>(xCol / tileSize);
		int zMultiply = static_cast<int>(zCol / tileSize);
		xCol = xCol - (static_cast<float>(xMultiply) * tileSize);
		zCol = zCol - (static_cast<float>(zMultiply) * tileSize);
	if (xCol < (tileSize / 2.f)) {
	//Left side of the 2x2
	if (zCol < (tileSize / 2.f)) {
		//Closest side of the 2x2
		objectColor = Color(100.f, 0.f, 0.f);
	}
	else {
		//Back side of the 2x2
		objectColor = Color(100.f, 100.f, 100.f);
	}
}
else {
	//Right side of the 2x2
	if (zCol < (tileSize / 2.f)) {
		//Closest side of the 2x2
		objectColor = Color(100.f, 100.f, 100.f);
	}
	else {
		//Back side of the 2x2
		objectColor = Color(100.f, 0.f, 0.f);
	}
}
	}
		for (int l = 0; l < a_Lamps.size(); l++) {
			objectColor.Inverse();
			Color TempColor = (a_Lamps[l]->m_Color * this->m_ColorInfo.m_LightLevel) - objectColor;
			TempColor.KeepItReal();
			vec3 l_Normal = this->m_CollisionInfo.m_ClosestObject->getNormal(this->m_CollisionInfo.m_IntersectionPoint);
			l_Normal.normalize();
			if (l > 0) {
				this->m_ColorInfo.m_DiffuseColor += TempColor * ( a_Lamps[l]->getPos()- this->m_CollisionInfo.m_IntersectionPoint).normalize().dot(l_Normal);
				this->m_ColorInfo.m_DiffuseColor.KeepItReal();
			}
			else {
				this->m_ColorInfo.m_DiffuseColor = TempColor * (a_Lamps[l]->getPos() - this->m_CollisionInfo.m_IntersectionPoint).normalize().dot(l_Normal);
			}
			//this->m_ColorInfo.m_DiffuseColor = TempColor;
			this->m_ColorInfo.m_DiffuseColor.KeepItReal();

		}
		return true;
}

bool Ray::Specular(const std::vector<Lamp*> &a_Lamps)
{
	if (this->m_CollisionInfo.m_ClosestObject != 0) {
		for (int l = 0; l < a_Lamps.size(); l++) {
			this->m_ColorInfo.m_SpecularColor = this->m_CollisionInfo.m_ClosestObject->Specular(this->m_CollisionInfo.m_IntersectionPoint, a_Lamps[l]->getPos(), *this);
		}return true;
	}
	return false;
}

bool Ray::Reflection(const std::vector<Object*>& a_Objects, const std::vector<Lamp*> &a_Lamps)
{
	if (this->m_CollisionInfo.m_ClosestObject->getReflectiveness() <= 0.f) {
		return false;
	}
	
	if (m_SecondaryRay->m_RayInfo.m_Reflecting < MAXREFLECTIONS) {
		m_SecondaryRay->Trace(a_Objects, a_Lamps);

		if (m_SecondaryRay->m_ColorInfo.m_FinalColor.m_R != 0
			|| m_SecondaryRay->m_ColorInfo.m_FinalColor.m_G != 0
			|| m_SecondaryRay->m_ColorInfo.m_FinalColor.m_B != 0) {
			//	this->m_ColorInfo.m_FinalColor.Mix(reflectiveRay.m_ColorInfo.m_FinalColor, this->m_CollisionInfo.m_ClosestObject->getReflectiveness());
			this->m_ColorInfo.m_FinalColor = this->m_ColorInfo.m_FinalColor * (1.f - (this->m_CollisionInfo.m_ClosestObject->getReflectiveness() / 100.f)) + m_SecondaryRay->m_ColorInfo.m_FinalColor * (this->m_CollisionInfo.m_ClosestObject->getReflectiveness() / 100.f);
		}
	}

	return false;
}

bool Ray::Refraction(const std::vector<Object*>& a_Objects, const std::vector<Lamp*> &a_Lamps)
{
	if (this->m_RayInfo.m_Reflecting < MAXREFLECTIONS) {
		this->m_RayInfo.m_Reflecting++;
		//sin(angle2) * n2 = sin(angle1) * n1;
		float l_n1 = this->m_RayInfo.m_N1;
		float l_n2 = this->m_CollisionInfo.m_ClosestObject->getRefractionIndex();
		if (l_n2 > 0.f) {
			//Refractionray 1
			vec3 normal1 = this->m_CollisionInfo.m_ClosestObject->getNormal(this->m_CollisionInfo.m_IntersectionPoint);
			float l_angle1 = acos((this->m_RayInfo.m_Direction).dot(normal1.normalize()));
			float l_angle2 = 3.14159265359f * -0.5f
				- ((l_angle1 * l_n1) / l_n2);
			Ray l_RefractedRay1 = Ray(this->m_CollisionInfo.m_IntersectionPoint + (normal1.normalize() * (cos(l_angle2))).normalize() * 0.1f, (normal1.normalize() * (cos(l_angle2))).normalize());
			l_RefractedRay1.setPlane(m_Plane);
			l_RefractedRay1.m_RayInfo.m_N1 = l_n2;
			l_RefractedRay1.m_RayInfo.m_Reflecting = this->m_RayInfo.m_Reflecting;
			l_RefractedRay1.Trace(a_Objects, a_Lamps);
				if (l_RefractedRay1.m_ColorInfo.m_FinalColor == Color::Black()) {
					return false;
				}
				if(!l_RefractedRay1.Refraction(a_Objects, a_Lamps)){
				
					this->m_ColorInfo.m_FinalColor = l_RefractedRay1.m_ColorInfo.m_FinalColor;
					return true;
				}
		}
		else {
			//Not refractable object -> cancel
			return false;
		}
	}
	return false;
}

bool Ray::anotherRay(BVHAcceleration& a_BVH, const std::vector<Lamp*> a_Lamps)
{
	if(this->m_CollisionInfo.m_ClosestObject == NULL){
		return false;
	}
	else {
		if (this->m_CollisionInfo.m_ClosestObject->getRefractionIndex() > 0.f) {
			if (this->m_RayInfo.m_Reflecting < MAXREFLECTIONS) {
				//sin(angle2) * n2 = sin(angle1) * n1;
				float l_n1 = this->m_RayInfo.m_N1;
				float l_n2 = this->m_CollisionInfo.m_ClosestObject->getRefractionIndex();
				if (l_n2 > 0.f) {
					//Refractionray 1
					vec3 normal1 = this->m_CollisionInfo.m_ClosestObject->getNormal(this->m_CollisionInfo.m_IntersectionPoint);
					float l_angle1 = acos((this->m_RayInfo.m_Direction).dot(normal1.normalize()));
					float l_angle2 = 3.14159265359f * -0.5f
						- ((l_angle1 * l_n1) / l_n2);
					m_SecondaryRay = new Ray();
					m_SecondaryRay->m_RayInfo.m_Origin = this->m_CollisionInfo.m_IntersectionPoint + (normal1.normalize() * (cos(l_angle2))).normalize() * 0.1f;
					m_SecondaryRay->m_RayInfo.m_Direction = (normal1.normalize() * (cos(l_angle2))).normalize();
					m_SecondaryRay->setPlane(m_Plane);
					m_SecondaryRay->m_RayInfo.m_N1 = l_n2;
					m_SecondaryRay->m_RayInfo.m_Reflecting = this->m_RayInfo.m_Reflecting + 1;
					a_BVH.Intersect(*m_SecondaryRay);
					float l_PlaneDistance = -1.f;
					m_Plane->Collides(m_SecondaryRay->m_RayInfo.m_Origin, m_SecondaryRay->m_RayInfo.m_Direction, l_PlaneDistance);
					if (l_PlaneDistance > 0.f) {
						if (m_SecondaryRay->m_CollisionInfo.m_Intersection > l_PlaneDistance) {
							//Use the plane
							m_SecondaryRay->m_CollisionInfo.m_ClosestObject = m_Plane;
							m_SecondaryRay->m_CollisionInfo.m_Intersection = l_PlaneDistance;
							m_SecondaryRay->m_CollisionInfo.m_IntersectionPoint = m_SecondaryRay->m_RayInfo.m_Origin + (m_SecondaryRay->m_RayInfo.m_Direction * l_PlaneDistance);
						}
						else {
							//Change nothing
						}
					}
					if (m_SecondaryRay->m_CollisionInfo.m_ClosestObject == this->m_CollisionInfo.m_ClosestObject) {
						vec3 normal2 = m_SecondaryRay->m_CollisionInfo.m_ClosestObject->getNormal(m_SecondaryRay->m_CollisionInfo.m_IntersectionPoint);
						float l_angle3 = acos((m_SecondaryRay->m_RayInfo.m_Direction).dot(normal2.normalize()));
						float l_angle4 = 3.14159265359f * -0.5f
							- ((l_angle3 * m_SecondaryRay->m_RayInfo.m_N1) / 1.000293f);
						m_SecondaryRay->m_RayInfo.m_Origin = m_SecondaryRay->m_CollisionInfo.m_IntersectionPoint + (normal2.normalize() * (cos(l_angle4))).normalize() * 0.1f;
						m_SecondaryRay->m_RayInfo.m_Direction = (normal2.normalize() * (cos(l_angle4))).normalize();
						m_SecondaryRay->setPlane(m_Plane);
						m_SecondaryRay->m_RayInfo.m_N1 = l_n2;
						m_SecondaryRay->m_RayInfo.m_Reflecting = this->m_RayInfo.m_Reflecting + 1;
						a_BVH.Intersect(*m_SecondaryRay);

						float l_PlaneDistance2 = -1.f;
						m_Plane->Collides(m_SecondaryRay->m_RayInfo.m_Origin, m_SecondaryRay->m_RayInfo.m_Direction, l_PlaneDistance2);
						if (l_PlaneDistance2 > 0.f) {
							if (m_SecondaryRay->m_CollisionInfo.m_Intersection > l_PlaneDistance2) {
								//Use the plane
								m_SecondaryRay->m_CollisionInfo.m_ClosestObject = m_Plane;
								m_SecondaryRay->m_CollisionInfo.m_Intersection = l_PlaneDistance2;
								m_SecondaryRay->m_CollisionInfo.m_IntersectionPoint = m_SecondaryRay->m_RayInfo.m_Origin + (m_SecondaryRay->m_RayInfo.m_Direction * l_PlaneDistance2);
							}
							else {
								//Change nothing
							}
						}
					}
						if (m_SecondaryRay->anotherRay(a_BVH, a_Lamps)) {

							m_SecondaryRay->m_ColorInfo.m_FinalColor = m_SecondaryRay->m_SecondaryRay->m_ColorInfo.m_FinalColor;
							m_SecondaryRay->m_ColorInfo.m_FinalColor.KeepItReal();
						}
						else {
							m_SecondaryRay->Trace(a_Lamps);
						}
				}
				return true;
		}
		else {
				return false;
		}
		}
		if (this->m_CollisionInfo.m_ClosestObject->getReflectiveness() > 0.f) {
			if (this->m_RayInfo.m_Reflecting < MAXREFLECTIONS) {
				this->m_SecondaryRay = new Ray();
				m_SecondaryRay->m_RayInfo.m_Reflecting = this->m_RayInfo.m_Reflecting;
				this->m_SecondaryRay->setPlane(m_Plane);
				vec3 surfaceNormal = this->m_CollisionInfo.m_ClosestObject->getNormal(this->m_CollisionInfo.m_IntersectionPoint).normalize();
				this->m_SecondaryRay->m_RayInfo.m_Direction = (surfaceNormal * (surfaceNormal.dot(this->m_RayInfo.m_Direction) * 2) - this->m_RayInfo.m_Direction) * -1;
				this->m_SecondaryRay->m_RayInfo.m_Origin = this->m_CollisionInfo.m_IntersectionPoint;
				this->m_SecondaryRay->m_RayInfo.m_Reflecting = this->m_RayInfo.m_Reflecting + 1;
				a_BVH.Intersect(*m_SecondaryRay);
				if (m_SecondaryRay->anotherRay(a_BVH, a_Lamps)) {
					m_SecondaryRay->m_ColorInfo.m_FinalColor = m_SecondaryRay->m_SecondaryRay->m_ColorInfo.m_FinalColor;
					m_SecondaryRay->m_ColorInfo.m_FinalColor.KeepItReal();
				}
				else {
					m_SecondaryRay->Trace(a_Lamps);
				}
				return true;
			}
		}
	}
	return false;
}

sf::Color Ray::getSFColor()
{
	return this->m_ColorInfo.m_FinalColor.toSF();
}

Ray::Ray(vec3 a_Origin, vec3 a_Direction)
{
	this->m_RayInfo.m_Origin = a_Origin;
	this->m_RayInfo.m_Direction = a_Direction;
}