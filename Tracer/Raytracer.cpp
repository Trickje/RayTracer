#include <iostream>
#include <time.h>
#include <ctime>
#include "SFML/System.hpp"
#include "SFML/Graphics.hpp"
#include "Camera.h"
#include "Raytracer.h"
static const float PI = 3.1415927410125732421875f; //Wth?

#define SCREENWIDTH 1280
#define SCREENHEIGHT 720
//ScreenDimensions: x and y
static const vec2 screenDimensions = vec2(1280.f, 720.f);
//Do you want to use the BVH acceleration method?
static const bool useBVH = true;
//How many random spheres should there be?
static int objects = 1000;
//IF YOU ARE NOT ME TRYING TO MAINTAIN EVIDENCE, LEAVE SAVING RESULTS FALSE
//TO AVOID RANDOM IMAGES SOMEWHERE ON YOUR HARD DRIVE
static const bool savingResults = false;
//Is the m_Camera pointed towards the first object in the storage container
static const bool looksAtFirstObject = false;
//Pauses the execution at the end, showing the results of the rendering
static const bool pauseOnExit = true;
//Triggers things for testing purposes
static const bool timing = false;
static const int testFrames = 20 + 1; //What the heck?

int main()
{
	sf::RenderWindow m_Window(sf::VideoMode(SCREENWIDTH, SCREENHEIGHT), "Raytracer");
	TRayTracer tracer(m_Window);
	if(useBVH)
	printf("Using BVH\n");
	if (!useBVH)
	printf("Not using BVH\n");
	if (timing) {
		for (int test = 0; test < testFrames; test++) {
			tracer.Initialize();
			tracer.Render();
			tracer.Save();
			objects += 100000;
		}
		if (pauseOnExit) {
			system("PAUSE");
		}
	}
	else {
		tracer.Initialize();
		while (m_Window.isOpen()) {
		tracer.Render();
		tracer.Save();
		if (pauseOnExit) {
			system("PAUSE");
		}
		m_Window.close();
		}
	}
		return 0;
	
}

TRayTracer::TRayTracer(sf::RenderWindow& a_Window) : m_Window(a_Window)
{
	
}

TRayTracer::~TRayTracer()
{
}

void TRayTracer::Initialize()
{
	//m_Objects.clear();
	//m_Objects.reserve(0);
	//m_Objects.reserve(sizeof(Sphere) * spheres);
	m_Clock.restart();
	//std::cout << "The maximum objects is: " << m_Objects.max_size() << std::endl;
	m_ElapsedTime = sf::Time::Zero;
	if(!timing)
	printf("Pre-load..\n");
	//m_RenderImage to m_RenderSprite conversion
	m_RenderImage = new sf::Image();
	m_RenderImage->create(static_cast<unsigned int>(screenDimensions.m_X), static_cast<unsigned int>(screenDimensions.m_Y), sf::Color::White);
	m_RenderTexture = new sf::Texture();
	m_RenderSprite = new sf::Sprite();
	m_RenderTexture->loadFromImage(*m_RenderImage);
	m_RenderSprite->setTexture(*m_RenderTexture);
	m_RenderSprite->setPosition(0.f, 0.f);
	if(!timing)
	printf("Image foundation built!\n");
	//m_RenderImage to m_RenderSprite
	m_RenderTexture->loadFromImage(*m_RenderImage);
	m_RenderSprite->setTexture(*m_RenderTexture);
	m_Window.clear();
	m_Window.draw(*m_RenderSprite);
	m_Window.display();
	if(!timing)
	printf("First image displayed\n");
	//Shape making
	m_Plane = new TPlane(vec3(0.01f, -1.f, 1.f), vec3(0.f, 1.f, 0.f), TColor::Black());
	m_Objects.push_back(new TSphere(vec3(0.f, 1.5f, 0.f), 1.5f, 10));
	m_Objects.push_back(new TCube(vec3(0.f, 4.f, 0.f), vec3(0.5f, 0.6f, 0.2f), vec3(0.3f, 0.3f, 0.3f), 10));
	//AddObjects(t_Sphere, (objects / 2));
	//AddObjects(t_Cube, objects - (objects / 2));
	AddObjects(t_Cube, objects);

	//Lamp making
	m_Lamps.push_back(new TLamp(vec3(0.f, 5.f, 0.f), TColor::White()));
	if(!timing)
	printf("%i Objects created!\n", static_cast<int>(m_Objects.size()));
	if (useBVH) {
		m_BVH = new TBVHAcceleration();
		m_BVH->createTree(m_Objects);
	}
	if (looksAtFirstObject) {
		if (m_Objects.size() > 0) {
		m_Camera = TCamera(mat4::lookat(m_Cam,
			m_Objects[0]->getPos()
			, vec3(0, 1, 0)), m_Cam);
		}
		else {
			m_Camera = TCamera(mat4::lookat(m_Cam,
				vec3(0.f, 0.f, 0.f)
				, vec3(0, 1, 0)), m_Cam);
		}
	}else {
		m_Camera = TCamera(mat4::lookat(m_Cam,
			vec3(0.f, -2.f, 0.f)
			, vec3(0, 1, 0)), m_Cam);
	}
	//Lamp
	m_ElapsedTime = m_Clock.restart();
	std::string prerender = std::to_string(m_ElapsedTime.asMilliseconds()) + "ms";
	if(!timing)
	printf("Time to pre-render: %s\n", prerender.c_str());
	m_ElapsedTime = sf::Time::Zero;
}

void TRayTracer::AddObjects(const int & a_Type, const int & a_Amount)
{
	for (int o = 0; o < a_Amount; o++) {
		if (a_Type == t_Sphere) {
			m_Objects.push_back(new TSphere());
		}
		if (a_Type == t_Cube) {
			m_Objects.push_back(new TCube());
		}
	}
}

void TRayTracer::Render()
{
	int y = 0;
	m_ElapsedTime += m_Clock.restart();
	m_ElapsedTime = sf::Time::Zero;
	while (y < SCREENHEIGHT && m_Window.isOpen()) {
		//	std::cout <<"Loading: " << (std::to_string((y * 100) / 800)) << "%"  <<std::endl;

		if (y >= SCREENHEIGHT) {
      break;
		}
		for (int x = 0; x < SCREENWIDTH; x++) {
			////RAY TRACING PART
			TRay currentRay = m_Camera.shootRay(x, y, screenDimensions);
			currentRay.setPlane(m_Plane);
			if (useBVH) {
				if (!m_Objects.empty()) {
					m_BVH->Intersect(currentRay);
					currentRay.anotherRay(*m_BVH, m_Lamps);
					currentRay.Trace(m_Lamps);
				}
				else {
					currentRay.Trace(m_Lamps);
				}
			}
			else {
				currentRay.Trace(m_Objects, m_Lamps);
			}

			

			m_RenderImage->setPixel(x, y, currentRay.getSFColor()); //set the pixel color to the sphere color
		
				//END OF RAY TRACING PART

		}
		y++;
	//m_RenderImage to m_RenderSprite
		m_RenderTexture->loadFromImage(*m_RenderImage);
		m_RenderSprite->setTexture(*m_RenderTexture);
		//Check for exit
		sf::Event event;
		while (m_Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				printf("Closing program\n");
				m_Window.close();
			}
		}
		m_Window.clear();
		m_Window.draw(*m_RenderSprite);
		m_Window.display();
	}

}
void TRayTracer::Save()
{
	m_ElapsedTime += m_Clock.restart();
	//AUTOMATIC FILE SAVING
	if(!timing)
	printf("Frame Complete!\n");
	std::string finalTime = std::to_string(m_ElapsedTime.asMilliseconds()) + "ms";
	printf("Time to render %i Objects: %s\n", static_cast<int>(m_Objects.size()), finalTime.c_str());
	m_Window.setTitle("Raytracer " + finalTime);
	if (savingResults) {
		printf("Saving to file: ");
		time_t now;
		time(&now);
		struct tm timeinfo;
		localtime_s(&timeinfo, &now);
		std::string mon;
		std::string day;
		std::string hour;
		std::string minute;
		std::string year;
		if (timeinfo.tm_mon < 9) {
			mon = "0" + std::to_string(timeinfo.tm_mon + 1);		//returns 0-11
		}
		else {
			mon = std::to_string(timeinfo.tm_mon + 1);		//returns 0-11
		}
		if (timeinfo.tm_mday < 10) {
			day = "0" + std::to_string(timeinfo.tm_mday);		//returns 1-31
		}
		else {
			day = std::to_string(timeinfo.tm_mday);		//returns 1-31
		}
		if (timeinfo.tm_hour < 10) {
			hour = "0" + std::to_string(timeinfo.tm_hour);		//returns 0-23
		}
		else {
			hour = std::to_string(timeinfo.tm_hour);		//returns 0-23
		}
		year = std::to_string(timeinfo.tm_year + 1900);
		if (timeinfo.tm_min < 10) {
			minute = "0" + std::to_string(timeinfo.tm_min);		//returns 0-59
		}
		else {
			minute = std::to_string(timeinfo.tm_min);		//returns 0-59
		}
		std::string filename = "RenderImage " + mon + "-" + day + "-" + year + " [" + hour + "-" + minute + "]";
		//std::cin >> filename;
		std::string filepath = "../../../../../../RenderImages/" + filename + ".png";
		m_RenderImage->saveToFile(filepath);
		std::cout << "D:\\RenderImages\\ " << filename << std::endl;
	}
	if (useBVH) {
		delete m_BVH;
	}
	m_Objects.clear();
	m_Lamps.clear();
	delete m_Plane;
	delete m_RenderImage;
	delete m_RenderTexture;
	delete m_RenderSprite;
	//END AUTOMATIC FILE SAVING
}
