#ifndef GUI_H
#define GUI_H

#include <cmath>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <string>
#include <vector>
//Math functions
bool isInTriangle(sf::Vector2f a,sf::Vector2f b,sf::Vector2f c,sf::Vector2f d);
float area(sf::Vector2f a,sf::Vector2f b,sf::Vector2f c);
float det(sf::Vector2f a,sf::Vector2f b,sf::Vector2f c);
float dist(sf::Vector2f start,sf::Vector2f end);
float getAngle(sf::Vector2f start,sf::Vector2f end);
//GUI
class GUI{
private:
	//For text
	sf::Font *font;
	//Screen and window properties
	unsigned winH,winW;
	float scale;
	unsigned winX,winY;	
public:
	float x,y;
	short selected;
	//Functions
	GUI();
	void Update(sf::RenderWindow *window);
	unsigned width();
	unsigned height();
	float width(unsigned percent);
	float height(unsigned percent);
	sf::Vector2f mousePosition();
	sf::Font* Font();
	~GUI();
};
extern GUI gui;
#endif