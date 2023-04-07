#pragma once
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "Camera.h"

class TRayTracer {
public:
	TRayTracer(sf::RenderWindow& a_Window);
	~TRayTracer();
	//Initialize handles the pre-render
	void Initialize();
	void AddObjects(const int &a_Type, const int &a_Amount);
	void Render();
	void Save();
private:
	TCamera m_Camera;
	std::vector<TObject*> m_Objects;
	std::vector<TLamp*> m_Lamps;
	//Camera position
	vec3 m_Cam = vec3(4.f, 6.f, -6.f);
	sf::Clock m_Clock;
	//BVH acceleration class
	TBVHAcceleration* m_BVH;
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
	TPlane* m_Plane;
};