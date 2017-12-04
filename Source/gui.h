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
float distSquare(sf::Vector2f start,sf::Vector2f end);
float getAngle(sf::Vector2f start,sf::Vector2f end);
float getRadians(sf::Vector2f start,sf::Vector2f end);
//Text
std::string Format(double value);
std::string Format(int value);
std::string Format(unsigned value);
//GUI
class GUI{
private:
	//For text
	sf::Font *font;
	//Screen and window properties
	unsigned winH,winW;
	//Time
	sf::Clock click;
public:
	float x,y;
	short selected;
	//Functions
	GUI();
	unsigned width();
	unsigned height();
	float width(unsigned percent);
	float height(unsigned percent);
	//Mouse
	bool canClick(short time);
	bool canLeft(short time);
	bool canRight(short time);
	void clickRestart();
	sf::Vector2f mousePosition();
	//Text
	sf::Font* Font();
	//Destructor
	~GUI();
}extern gui;
#endif