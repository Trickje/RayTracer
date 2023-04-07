#include "Shapes.h"
#include <math.h>
#include <random>
#include <time.h>
#include <chrono>
static const float PI = 3.1415927410125732421875f;
Cube::Cube() {
	this->m_Position.m_Y = 1.f;
	//Predefined bounds:
	std::mt19937 generator(static_cast<unsigned int>(std::chrono::high_resolution_clock::now().time_since_epoch().count()));
	std::uniform_int_distribution<unsigned int> dist(1, 100);
	int randomNumberX = dist(generator);
	float randomFloatX = static_cast<float>(randomNumberX) / 12.5f;
	int randomMultiply = dist(generator);
	float l_Multiply = static_cast<float>(randomMultiply) / 50.f;
	int randomNumberZ = dist(generator);
	float randomFloatZ = static_cast<float>(randomNumberZ) / 12.5f;
	int randomNumberNegativeX = dist(generator);
	if (randomNumberNegativeX < 50) {
		this->m_Position.m_X = (randomFloatX * 3.f);
	}
	else {

		this->m_Position.m_X = -(randomFloatX * 3.f);
	}
	int randomNumberNegativeZ = dist(generator);
	if (randomNumberNegativeZ < 50) {
		this->m_Position.m_Z = (randomFloatZ * 3.f);
	}
	else {
		this->m_Position.m_Z = -(randomFloatZ * 3.f);
	}
		float l_Multiplication = (3.f + l_Multiply * 5.f)/ m_Position.length();
		if (m_Position.m_X > 0.f) {
			m_Position.m_X *= l_Multiplication;
		}
		else {
			m_Position.m_X *= l_Multiplication;
		}
		if (m_Position.m_Z > 0.f) {
			m_Position.m_Z *= l_Multiplication;
		}
		else {
			m_Position.m_Z *= l_Multiplication;
		}
	
	//int randomNumberY = dist(generator);
	//float randomFloatY = static_cast<float>(randomNumberY) / 30.0f;
	int randomR = dist(generator);
	int randomG = dist(generator);
	int randomB = dist(generator);
	this->m_Reflectiveness = 0.f;
	this->m_RefractionIndex = 0.f;
	m_Color = Color(static_cast<float>(randomR), static_cast<float>(randomG), static_cast<float>(randomB));
	m_Color.KeepItReal();

	int randomRotateX = dist(generator);
	float rotateX = (static_cast<float>(randomRotateX) / 1.8f) * PI;
	int randomRotateY = dist(generator);
	float rotateY = (static_cast<float>(randomRotateY) / 1.8f) * PI;
	int randomRotateZ = dist(generator);
	float rotateZ = (static_cast<float>(randomRotateZ) / 1.8f) * PI;
	this->m_Size = vec3(0.3f,0.3f,0.3f);
	this->m_Rotation = vec3(rotateX, rotateY, rotateZ);
	m_Transformation = mat4::identity();

	mat4 l_RotateX = mat4::rotateX(m_Rotation.m_X);
	mat4 l_RotateY = mat4::rotateY(m_Rotation.m_Y);
	mat4 l_RotateZ = mat4::rotateZ(m_Rotation.m_Z);
	m_Transformation = l_RotateX * l_RotateY * l_RotateZ;
	m_Forward = (m_Transformation * vec3(0.f, 0.f, 1.f)).normalize();
	m_Right = (m_Transformation * vec3(1.f, 0.f, 0.f)).normalize();
	m_Up = (m_Transformation * vec3(0.f, 1.f, 0.f)).normalize();
	m_Transformation.m_03 = m_Position.m_X;
	m_Transformation.m_13 = m_Position.m_Y;
	m_Transformation.m_23 = m_Position.m_Z;
	m_InverseTransformation = m_Transformation.inverse();
	if (m_BBox == NULL) {
		vec3 l_Min;
		vec3 l_Max;
		l_Min.m_X = m_Forward.m_X * m_Size.m_Z + m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y;
		l_Min.m_X = std::min(l_Min.m_X, m_Forward.m_X * m_Size.m_Z + m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);
		l_Min.m_X = std::min(l_Min.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) + m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y);
		l_Min.m_X = std::min(l_Min.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) + m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);
		l_Min.m_X = std::min(l_Min.m_X, m_Forward.m_X * m_Size.m_Z - m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y);
		l_Min.m_X = std::min(l_Min.m_X, m_Forward.m_X * m_Size.m_Z - m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);
		l_Min.m_X = std::min(l_Min.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) - m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y);
		l_Min.m_X = std::min(l_Min.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) - m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);

		l_Min.m_Y = m_Forward.m_Y* m_Size.m_Z + m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y;
		l_Min.m_Y = std::min(l_Min.m_Y, m_Forward.m_Y * m_Size.m_Z + m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);
		l_Min.m_Y = std::min(l_Min.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) + m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y);
		l_Min.m_Y = std::min(l_Min.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) + m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);
		l_Min.m_Y = std::min(l_Min.m_Y, m_Forward.m_Y * m_Size.m_Z - m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y);
		l_Min.m_Y = std::min(l_Min.m_Y, m_Forward.m_Y * m_Size.m_Z - m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);
		l_Min.m_Y = std::min(l_Min.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) - m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y);
		l_Min.m_Y = std::min(l_Min.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) - m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);

		l_Min.m_Z = m_Forward.m_Z * m_Size.m_Z + m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y;
		l_Min.m_Z = std::min(l_Min.m_Z, m_Forward.m_Z * m_Size.m_Z + m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);
		l_Min.m_Z = std::min(l_Min.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) + m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y);
		l_Min.m_Z = std::min(l_Min.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) + m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);
		l_Min.m_Z = std::min(l_Min.m_Z, m_Forward.m_Z * m_Size.m_Z - m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y);
		l_Min.m_Z = std::min(l_Min.m_Z, m_Forward.m_Z * m_Size.m_Z - m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);
		l_Min.m_Z = std::min(l_Min.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) - m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y);
		l_Min.m_Z = std::min(l_Min.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) - m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);


		l_Max.m_X = m_Forward.m_X * m_Size.m_Z + m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y;
		l_Max.m_X = std::max(l_Max.m_X, m_Forward.m_X * m_Size.m_Z + m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);
		l_Max.m_X = std::max(l_Max.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) + m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y);
		l_Max.m_X = std::max(l_Max.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) + m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);
		l_Max.m_X = std::max(l_Max.m_X, m_Forward.m_X * m_Size.m_Z - m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y);
		l_Max.m_X = std::max(l_Max.m_X, m_Forward.m_X * m_Size.m_Z - m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);
		l_Max.m_X = std::max(l_Max.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) - m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y);
		l_Max.m_X = std::max(l_Max.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) - m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);

		l_Max.m_Y = m_Forward.m_Y* m_Size.m_Z + m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y;
		l_Max.m_Y = std::max(l_Max.m_Y, m_Forward.m_Y * m_Size.m_Z + m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);
		l_Max.m_Y = std::max(l_Max.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) + m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y);
		l_Max.m_Y = std::max(l_Max.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) + m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);
		l_Max.m_Y = std::max(l_Max.m_Y, m_Forward.m_Y * m_Size.m_Z - m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y);
		l_Max.m_Y = std::max(l_Max.m_Y, m_Forward.m_Y * m_Size.m_Z - m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);
		l_Max.m_Y = std::max(l_Max.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) - m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y);
		l_Max.m_Y = std::max(l_Max.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) - m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);

		l_Max.m_Z = m_Forward.m_Z * m_Size.m_Z + m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y;
		l_Max.m_Z = std::max(l_Max.m_Z, m_Forward.m_Z * m_Size.m_Z + m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);
		l_Max.m_Z = std::max(l_Max.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) + m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y);
		l_Max.m_Z = std::max(l_Max.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) + m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);
		l_Max.m_Z = std::max(l_Max.m_Z, m_Forward.m_Z * m_Size.m_Z - m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y);
		l_Max.m_Z = std::max(l_Max.m_Z, m_Forward.m_Z * m_Size.m_Z - m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);
		l_Max.m_Z = std::max(l_Max.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) - m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y);
		l_Max.m_Z = std::max(l_Max.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) - m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);

		l_Max += m_Position;
		l_Min += m_Position;
		m_BBox = new BoundingBox(l_Min, l_Max);
	}
}

Cube::~Cube() {
	if (m_BBox != NULL) {
		delete m_BBox;
	}
}

bool Cube::Collides(const vec3& a_Origin, const vec3& a_Direction, float& a_Intersection)
{
	vec3 l_Origin = m_InverseTransformation * a_Origin;

	vec3 l_Direction = vec3(
		m_InverseTransformation.m_00 * a_Direction.m_X + m_InverseTransformation.m_01 * a_Direction.m_Y + m_InverseTransformation.m_02 * a_Direction.m_Z,
		m_InverseTransformation.m_10 * a_Direction.m_X + m_InverseTransformation.m_11 * a_Direction.m_Y + m_InverseTransformation.m_12 * a_Direction.m_Z,
		m_InverseTransformation.m_20 * a_Direction.m_X + m_InverseTransformation.m_21 * a_Direction.m_Y + m_InverseTransformation.m_22 * a_Direction.m_Z);
	l_Direction.normalize();
	vec3 l_Min;
	vec3 l_Max;
	l_Min.m_X = m_Size.m_X * -1.f;
	l_Min.m_Y = m_Size.m_Y * -1.f;
	l_Min.m_Z = m_Size.m_Z * -1.f;

	l_Max.m_X = m_Size.m_X;
	l_Max.m_Y = m_Size.m_Y;
	l_Max.m_Z = m_Size.m_Z;

	float t1X = -1.f;
	float t1Y = -1.f;
	float t1Z = -1.f;
	float t0X = -1.f;
	float t0Y = -1.f;
	float t0Z = -1.f;
	if (l_Direction.m_X <= 0.f) {
		t1X = (l_Min.m_X - l_Origin.m_X) / l_Direction.m_X;
		t0X = (l_Max.m_X - l_Origin.m_X) / l_Direction.m_X;
	}
	else {
		t1X = (l_Max.m_X - l_Origin.m_X) / l_Direction.m_X;
		t0X = (l_Min.m_X - l_Origin.m_X) / l_Direction.m_X;
	}
	if (l_Direction.m_Y <= 0.f) {
		t1Y = (l_Min.m_Y - l_Origin.m_Y) / l_Direction.m_Y;
		t0Y = (l_Max.m_Y - l_Origin.m_Y) / l_Direction.m_Y;
	}
	else {
		t1Y = (l_Max.m_Y - l_Origin.m_Y) / l_Direction.m_Y;
		t0Y = (l_Min.m_Y - l_Origin.m_Y) / l_Direction.m_Y;
	}
	if (l_Direction.m_Z <= 0.f) {
		t1Z = (l_Min.m_Z - l_Origin.m_Z) / l_Direction.m_Z;
		t0Z = (l_Max.m_Z - l_Origin.m_Z) / l_Direction.m_Z;
	}
	else {
		t1Z = (l_Max.m_Z - l_Origin.m_Z) / l_Direction.m_Z;
		t0Z = (l_Min.m_Z - l_Origin.m_Z) / l_Direction.m_Z;
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
		a_Intersection = distMin;
		return true;
	}
	else {
		a_Intersection = distMax;
		return true;
	}
}

Color const& Cube::getColor() const
{
	return m_Color;
}

sf::Color Cube::getSFColor() const
{
	return sf::Color(static_cast<sf::Uint8>(m_Color.m_R), static_cast<sf::Uint8>(m_Color.m_G), static_cast<sf::Uint8>(m_Color.m_B), static_cast<sf::Uint8>(m_Color.m_Alpha));
}

vec3 Cube::getPos() const
{
	return m_Position;
}

Color Cube::Specular(const vec3 & a_IntersectionPoint, const vec3 & a_LampPos, const Ray & a_Ray)
{
	//Add materials later
	float specular = 0.2f;
	//Surface normal
	vec3 normal = this->getNormal(a_IntersectionPoint);
	normal.normalize();
	//h calculations
	vec3 l = (a_LampPos - a_IntersectionPoint).normalize();
	vec3 v = (a_Ray.m_RayInfo.m_Origin - a_IntersectionPoint).normalize();
	vec3 h = (v + l) / (v + l).length();
	//Calculating the difference of h and normal
	float L = specular * pow(std::max(normal.dot(h), 0.f), 100);
	return Color(100.f * L, 100.f * L, 100.f * L);
}

vec3 Cube::getNormal(const vec3 & a_IntersectionPoint) const
{
	vec3 l_IntersectionPoint = m_InverseTransformation * a_IntersectionPoint;
	vec3 l_Min;
	vec3 l_Max;
	l_Min.m_X = m_Size.m_X * -1.f;
	l_Min.m_Y = m_Size.m_Y * -1.f;
	l_Min.m_Z = m_Size.m_Z * -1.f;
	l_Max.m_X = m_Size.m_X;
	l_Max.m_Y = m_Size.m_Y;
	l_Max.m_Z =  m_Size.m_Z;
	vec3 l_Right = vec3(l_Max.m_X, 0.f, 0.f).normalize();
	vec3 l_Forward = vec3(0.f, 0.f, l_Max.m_Z).normalize();
	vec3 l_Up = vec3(0.f, l_Max.m_Y, 0.f).normalize();
	float t0X;
	float t1X;
	float t0Y;
	float t1Y;
	float t0Z;
	float t1Z;
	t0X = l_Right.dot(l_IntersectionPoint);
	t1X = (l_Right * -1.f).dot(l_IntersectionPoint);

	t0Y = l_Up.dot(l_IntersectionPoint);
	t1Y = (l_Up * -1.f).dot(l_IntersectionPoint);

	t0Z = l_Forward.dot(l_IntersectionPoint);
	t1Z = (l_Forward * -1.f).dot(l_IntersectionPoint);
	if (t0X > t1X && t0X > t0Y && t0X > t1Y && t0X > t0Z && t0X > t1Z) {
		return m_Right;
	}
	if (t1X > t0X && t1X > t0Y && t1X > t1Y && t1X > t0Z && t1X > t1Z) {
		return m_Right * -1.f;
	}
	if (t0Y > t1X && t0Y > t0X && t0Y > t1Y && t0Y > t0Z && t0Y > t1Z) {
		return m_Up;
	}
	if (t1Y > t0X && t1Y > t0Y && t1Y > t1X && t1Y > t0Z && t1Y > t1Z) {
		return m_Up * -1.f;
	}
	if (t0Z > t1X && t0Z > t0Y && t0Z > t1Y && t0Z > t0X && t0Z > t1Z) {
		return m_Forward;
	}
	if (t1Z > t0X && t1Z > t0Y && t1Z > t1Y && t1Z > t0Z && t1Z > t1X) {
		return m_Forward * -1.f;
	}
	return m_Up;
	/*
	if (t0X < t1X) {
		//The minimum is closer than the maximum
		if (t0Y < t1Y) {
			if (t0Z < t1Z) {
				if (t0X < t0Y) {
					if (t0X < t0Z) {
						return m_Right * -1.f;
					}
					else {
						return m_Forward * -1.f;
					}
				}
				else {
					if (t0Y < t0Z) {
						return m_Up * -1.f;
					}
					else {
						return m_Forward * -1.f;
					}
				}
			}
			else {
				if (t0X < t0Y) {
					if (t0X < t1Z) {
						return m_Right * -1.f;
					}
					else {
						return m_Forward;
					}
				}
				else {
					if (t0Y < t1Z) {
						return m_Up * -1.f;
					}
					else {
						return m_Forward;
					}
				}
			}
		}
		else {

			if (t0Z < t1Z) {
				if (t0X < t1Y) {
					if (t0X < t0Z) {
						return m_Right * -1.f;
					}
					else {
						return m_Forward * -1.f;
					}
				}
				else {
					if (t1Y < t0Z) {
						return m_Up;
					}
					else {
						return m_Forward * -1.f;
					}
				}
			}
			else {
				if (t0X < t1Y) {
					if (t0X < t1Z) {
						return m_Right * -1.f;
					}
					else {
						return m_Forward;
					}
				}
				else {
					if (t1Y < t1Z) {
						return m_Up;
					}
					else {
						return m_Forward;
					}
				}
			}
		}
	}
	else {
		// Max X is closer than Min X
		if (t0Y < t1Y) {
			if (t0Z < t1Z) {
				if (t1X < t0Y) {
					if (t1X < t0Z) {
						return m_Right;
					}
					else {
						return m_Forward * -1.f;
					}
				}
				else {
					if (t0Y < t0Z) {
						return m_Up * -1.f;
					}
					else {
						return m_Forward * -1.f;
					}
				}
			}
			else {
				if (t1X < t0Y) {
					if (t1X < t1Z) {
						return m_Right;
					}
					else {
						return m_Forward;
					}
				}
				else {
					if (t0Y < t1Z) {
						return m_Up * -1.f;
					}
					else {
						return m_Forward;
					}
				}
			}
		}
		else {

			if (t0Z < t1Z) {
				if (t1X < t1Y) {
					if (t1X < t0Z) {
						return m_Right;
					}
					else {
						return m_Forward * -1.f;
					}
				}
				else {
					if (t1Y < t0Z) {
						return m_Up;
					}
					else {
						return m_Forward * -1.f;
					}
				}
			}
			else {
				if (t1X < t1Y) {
					if (t1X < t1Z) {
						return m_Right;
					}
					else {
						return m_Forward;
					}
				}
				else {
					if (t1Y < t1Z) {
						return m_Up;
					}
					else {
						return m_Forward;
					}
				}
			}
		}
	}*/
}

float const & Cube::getReflectiveness() const
{
	return m_Reflectiveness;
}

int Cube::getType() const
{
	return t_Cube;
}

BoundingBox Cube::getBoundBox() const
{
	return *m_BBox;
}

Cube::Cube(const vec3& a_Position, const vec3& a_Rotation, const vec3& a_Size, const Color& a_Color) {
	this->m_Size = a_Size;
	this->m_Position = a_Position;
	this->m_Color = a_Color;
	this->m_Rotation = a_Rotation;
	m_Transformation = mat4::identity();

	mat4 l_RotateX = mat4::rotateX(m_Rotation.m_X * PI);
	mat4 l_RotateY = mat4::rotateY(m_Rotation.m_Y * PI);
	mat4 l_RotateZ = mat4::rotateZ(m_Rotation.m_Z * PI);
	m_Transformation = l_RotateX * l_RotateY * l_RotateZ;
	m_Forward = (m_Transformation * vec3(0.f, 0.f, 1.f)).normalize();
	m_Right = (m_Transformation * vec3(1.f, 0.f, 0.f)).normalize();
	m_Up = (m_Transformation * vec3(0.f, 1.f, 0.f)).normalize();
	m_Transformation.m_03 = m_Position.m_X;
	m_Transformation.m_13 = m_Position.m_Y;
	m_Transformation.m_23 = m_Position.m_Z;
	m_InverseTransformation = m_Transformation.inverse();

	if (m_BBox == NULL) {
		vec3 l_Min;
		vec3 l_Max;
		l_Min.m_X = m_Forward.m_X * m_Size.m_Z + m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y;
		l_Min.m_X = std::min(l_Min.m_X, m_Forward.m_X * m_Size.m_Z + m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);
		l_Min.m_X = std::min(l_Min.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) + m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y);
		l_Min.m_X = std::min(l_Min.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) + m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);
		l_Min.m_X = std::min(l_Min.m_X, m_Forward.m_X * m_Size.m_Z - m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y);
		l_Min.m_X = std::min(l_Min.m_X, m_Forward.m_X * m_Size.m_Z - m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);
		l_Min.m_X = std::min(l_Min.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) - m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y);
		l_Min.m_X = std::min(l_Min.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) - m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);

		l_Min.m_Y = m_Forward.m_Y* m_Size.m_Z + m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y;
		l_Min.m_Y = std::min(l_Min.m_Y, m_Forward.m_Y * m_Size.m_Z + m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);
		l_Min.m_Y = std::min(l_Min.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) + m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y);
		l_Min.m_Y = std::min(l_Min.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) + m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);
		l_Min.m_Y = std::min(l_Min.m_Y, m_Forward.m_Y * m_Size.m_Z - m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y);
		l_Min.m_Y = std::min(l_Min.m_Y, m_Forward.m_Y * m_Size.m_Z - m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);
		l_Min.m_Y = std::min(l_Min.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) - m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y);
		l_Min.m_Y = std::min(l_Min.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) - m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);

		l_Min.m_Z = m_Forward.m_Z * m_Size.m_Z + m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y;
		l_Min.m_Z = std::min(l_Min.m_Z, m_Forward.m_Z * m_Size.m_Z + m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);
		l_Min.m_Z = std::min(l_Min.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) + m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y);
		l_Min.m_Z = std::min(l_Min.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) + m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);
		l_Min.m_Z = std::min(l_Min.m_Z, m_Forward.m_Z * m_Size.m_Z - m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y);
		l_Min.m_Z = std::min(l_Min.m_Z, m_Forward.m_Z * m_Size.m_Z - m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);
		l_Min.m_Z = std::min(l_Min.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) - m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y);
		l_Min.m_Z = std::min(l_Min.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) - m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);


		l_Max.m_X = m_Forward.m_X * m_Size.m_Z + m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y;
		l_Max.m_X = std::max(l_Max.m_X, m_Forward.m_X * m_Size.m_Z + m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);
		l_Max.m_X = std::max(l_Max.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) + m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y);
		l_Max.m_X = std::max(l_Max.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) + m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);
		l_Max.m_X = std::max(l_Max.m_X, m_Forward.m_X * m_Size.m_Z - m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y);
		l_Max.m_X = std::max(l_Max.m_X, m_Forward.m_X * m_Size.m_Z - m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);
		l_Max.m_X = std::max(l_Max.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) - m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y);
		l_Max.m_X = std::max(l_Max.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) - m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);

		l_Max.m_Y = m_Forward.m_Y* m_Size.m_Z + m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y;
		l_Max.m_Y = std::max(l_Max.m_Y, m_Forward.m_Y * m_Size.m_Z + m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);
		l_Max.m_Y = std::max(l_Max.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) + m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y);
		l_Max.m_Y = std::max(l_Max.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) + m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);
		l_Max.m_Y = std::max(l_Max.m_Y, m_Forward.m_Y * m_Size.m_Z - m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y);
		l_Max.m_Y = std::max(l_Max.m_Y, m_Forward.m_Y * m_Size.m_Z - m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);
		l_Max.m_Y = std::max(l_Max.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) - m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y);
		l_Max.m_Y = std::max(l_Max.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) - m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);

		l_Max.m_Z = m_Forward.m_Z * m_Size.m_Z + m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y;
		l_Max.m_Z = std::max(l_Max.m_Z, m_Forward.m_Z * m_Size.m_Z + m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);
		l_Max.m_Z = std::max(l_Max.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) + m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y);
		l_Max.m_Z = std::max(l_Max.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) + m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);
		l_Max.m_Z = std::max(l_Max.m_Z, m_Forward.m_Z * m_Size.m_Z - m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y);
		l_Max.m_Z = std::max(l_Max.m_Z, m_Forward.m_Z * m_Size.m_Z - m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);
		l_Max.m_Z = std::max(l_Max.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) - m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y);
		l_Max.m_Z = std::max(l_Max.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) - m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);

		l_Max += m_Position;
		l_Min += m_Position;
		m_BBox = new BoundingBox(l_Min, l_Max);
	}
}

Cube::Cube(const vec3 & a_Position, const vec3 & a_Rotation, const vec3 & a_Size, int a_MaterialType)
{
	this->m_Position = a_Position;
	this->m_Rotation = a_Rotation;
	this->m_Size = a_Size;
	if (a_MaterialType == 10) {
		this->m_RefractionIndex = 1.52f;
	}
	m_Transformation = mat4::identity();

	mat4 l_RotateX = mat4::rotateX(m_Rotation.m_X * PI);
	mat4 l_RotateY = mat4::rotateY(m_Rotation.m_Y * PI);
	mat4 l_RotateZ = mat4::rotateZ(m_Rotation.m_Z * PI);
	m_Transformation = l_RotateX * l_RotateY * l_RotateZ;
	m_Forward = (m_Transformation * vec3(0.f, 0.f, 1.f)).normalize();
	m_Right = (m_Transformation * vec3(1.f, 0.f, 0.f)).normalize();
	m_Up = (m_Transformation * vec3(0.f, 1.f, 0.f)).normalize();
	m_Transformation.m_03 = m_Position.m_X;
	m_Transformation.m_13 = m_Position.m_Y;
	m_Transformation.m_23 = m_Position.m_Z;
	m_InverseTransformation = m_Transformation.inverse();

	if (m_BBox == NULL) {
		vec3 l_Min;
		vec3 l_Max;
		l_Min.m_X = m_Forward.m_X * m_Size.m_Z + m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y;
		l_Min.m_X = std::min(l_Min.m_X, m_Forward.m_X * m_Size.m_Z + m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);
		l_Min.m_X = std::min(l_Min.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) + m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y);
		l_Min.m_X = std::min(l_Min.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) + m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);
		l_Min.m_X = std::min(l_Min.m_X, m_Forward.m_X * m_Size.m_Z - m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y);
		l_Min.m_X = std::min(l_Min.m_X, m_Forward.m_X * m_Size.m_Z - m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);
		l_Min.m_X = std::min(l_Min.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) - m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y);
		l_Min.m_X = std::min(l_Min.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) - m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);

		l_Min.m_Y = m_Forward.m_Y* m_Size.m_Z + m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y;
		l_Min.m_Y = std::min(l_Min.m_Y, m_Forward.m_Y * m_Size.m_Z + m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);
		l_Min.m_Y = std::min(l_Min.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) + m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y);
		l_Min.m_Y = std::min(l_Min.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) + m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);
		l_Min.m_Y = std::min(l_Min.m_Y, m_Forward.m_Y * m_Size.m_Z - m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y);
		l_Min.m_Y = std::min(l_Min.m_Y, m_Forward.m_Y * m_Size.m_Z - m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);
		l_Min.m_Y = std::min(l_Min.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) - m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y);
		l_Min.m_Y = std::min(l_Min.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) - m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);

		l_Min.m_Z = m_Forward.m_Z * m_Size.m_Z + m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y;
		l_Min.m_Z = std::min(l_Min.m_Z, m_Forward.m_Z * m_Size.m_Z + m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);
		l_Min.m_Z = std::min(l_Min.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) + m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y);
		l_Min.m_Z = std::min(l_Min.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) + m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);
		l_Min.m_Z = std::min(l_Min.m_Z, m_Forward.m_Z * m_Size.m_Z - m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y);
		l_Min.m_Z = std::min(l_Min.m_Z, m_Forward.m_Z * m_Size.m_Z - m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);
		l_Min.m_Z = std::min(l_Min.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) - m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y);
		l_Min.m_Z = std::min(l_Min.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) - m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);


		l_Max.m_X = m_Forward.m_X * m_Size.m_Z + m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y;
		l_Max.m_X = std::max(l_Max.m_X, m_Forward.m_X * m_Size.m_Z + m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);
		l_Max.m_X = std::max(l_Max.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) + m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y);
		l_Max.m_X = std::max(l_Max.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) + m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);
		l_Max.m_X = std::max(l_Max.m_X, m_Forward.m_X * m_Size.m_Z - m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y);
		l_Max.m_X = std::max(l_Max.m_X, m_Forward.m_X * m_Size.m_Z - m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);
		l_Max.m_X = std::max(l_Max.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) - m_Right.m_X * m_Size.m_X + m_Up.m_X * m_Size.m_Y);
		l_Max.m_X = std::max(l_Max.m_X, (m_Forward.m_X * m_Size.m_Z * -1.f) - m_Right.m_X * m_Size.m_X - m_Up.m_X * m_Size.m_Y);

		l_Max.m_Y = m_Forward.m_Y* m_Size.m_Z + m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y;
		l_Max.m_Y = std::max(l_Max.m_Y, m_Forward.m_Y * m_Size.m_Z + m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);
		l_Max.m_Y = std::max(l_Max.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) + m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y);
		l_Max.m_Y = std::max(l_Max.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) + m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);
		l_Max.m_Y = std::max(l_Max.m_Y, m_Forward.m_Y * m_Size.m_Z - m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y);
		l_Max.m_Y = std::max(l_Max.m_Y, m_Forward.m_Y * m_Size.m_Z - m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);
		l_Max.m_Y = std::max(l_Max.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) - m_Right.m_Y * m_Size.m_X + m_Up.m_Y * m_Size.m_Y);
		l_Max.m_Y = std::max(l_Max.m_Y, (m_Forward.m_Y * m_Size.m_Z * -1.f) - m_Right.m_Y * m_Size.m_X - m_Up.m_Y * m_Size.m_Y);

		l_Max.m_Z = m_Forward.m_Z * m_Size.m_Z + m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y;
		l_Max.m_Z = std::max(l_Max.m_Z, m_Forward.m_Z * m_Size.m_Z + m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);
		l_Max.m_Z = std::max(l_Max.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) + m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y);
		l_Max.m_Z = std::max(l_Max.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) + m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);
		l_Max.m_Z = std::max(l_Max.m_Z, m_Forward.m_Z * m_Size.m_Z - m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y);
		l_Max.m_Z = std::max(l_Max.m_Z, m_Forward.m_Z * m_Size.m_Z - m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);
		l_Max.m_Z = std::max(l_Max.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) - m_Right.m_Z * m_Size.m_X + m_Up.m_Z * m_Size.m_Y);
		l_Max.m_Z = std::max(l_Max.m_Z, (m_Forward.m_Z * m_Size.m_Z * -1.f) - m_Right.m_Z * m_Size.m_X - m_Up.m_Z * m_Size.m_Y);

		l_Max += m_Position;
		l_Min += m_Position;
		m_BBox = new BoundingBox(l_Min, l_Max);
	}
}
