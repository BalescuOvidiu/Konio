#ifndef GUI_H
#define GUI_H

#include <cmath>
#include <cstdio>
#include <deque>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include <string>
#include <vector>
//File variables
extern std::ifstream in;
extern std::ifstream out;
//Math functions
bool isInTriangle(sf::Vector2f a,sf::Vector2f b,sf::Vector2f c,sf::Vector2f d);
float area(sf::Vector2f a,sf::Vector2f b,sf::Vector2f c);
float det(sf::Vector2f a,sf::Vector2f b,sf::Vector2f c);
float dist(sf::Vector2f start,sf::Vector2f end);
float Dist(sf::Vector2f start,sf::Vector2f end);
float getAngle(sf::Vector2f start,sf::Vector2f end);
float getRadians(sf::Vector2f start,sf::Vector2f end);
float max(float a,float b);
float square(float a);
float Sin(float angle);
float Cos(float angle);
float Rad(float angle);
//Text
std::string Format(double value);
std::string Format(int value);
std::string Format(unsigned value);
//GUI
class GUI{
private:
	//For text
	sf::Font *font;
	//Screen
	unsigned w,h;
	//Time
	sf::Clock click;
public:
	//Constructor
	GUI();
	//Screen
	float factor,x,y;
	short selected;
	unsigned width();
	unsigned height();
	float width(unsigned percent);
	float height(unsigned percent);
	sf::Vector2f center();
	sf::Vector2f zoomed(sf::Vector2f point,float factor);
	sf::Vector2f zoomed(sf::Vector2f point);
	//Mouse
	bool canClick(short time);
	bool canLeft(short time);
	bool canRight(short time);
	void clickRestart();
	sf::Vector2f mouseCoordinates();
	sf::Vector2f mousePosition();
	//Text
	sf::Font* Font();
	//Destructor
	~GUI();
}extern gui;
#endif