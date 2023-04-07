#pragma once
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "Camera.h"

class RayTracer {
public:
	RayTracer(sf::RenderWindow& a_Window);
	~RayTracer();
	//Initialize handles the pre-render
	void Initialize();
	void AddObjects(const int &a_Type, const int &a_Amount);
	void Render();
	void Save();
private:
	Camera m_Camera;
	std::vector<Object*> m_Objects;
	std::vector<Lamp*> m_Lamps;
	//Camera position
	vec3 m_Cam = vec3(4.f, 6.f, -6.f);
	sf::Clock m_Clock;
	//BVH acceleration class
	BVHAcceleration* m_BVH;
	//The image that will be displayed on screen later
	sf::Image* m_RenderImage;
	//Texture will be used in converting the image to the screen
	sf::Texture* m_RenderTexture;
	//Used for convertion
	sf::Sprite* m_RenderSprite;
	//This contains the window
	sf::RenderWindow& m_Window;//Contains the elapsed time, calculated by using the clock
	sf::Time m_ElapsedTime;
	//This is the plane
	Plane* m_Plane;
};