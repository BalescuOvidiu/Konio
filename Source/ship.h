#ifndef SHIP_H
#define SHIP_H
#include "naval.h"
#include "labelPlayer.h"
//Ship
class Ship{
private:
	short player,id;
	float speed,integrity,clock;
	//Move
	void Move(float x,float y);
public:
	sf::Sprite *body,*ram,*rows,*sails;
	//Constructor
	Ship(short player,short id,short faction,short x,short y,float angle);
	//Basic
	void show();
	void setColor(sf::Color color);
	//Rotation
	void rotate(float angle);
	void rotateTo(float angle);
	void setRotation(float angle);
	float getRotation();
	//Points
	void setOrigin();
	void setPosition(float x,float y);
	float getDist(sf::Vector2f point);
	bool contains(sf::Vector2f point);
	bool rowsContains(sf::Vector2f point);
	sf::Vector2f Origin();
	//Front points
	sf::Vector2f Ram();
	sf::Vector2f Front();
	sf::Vector2f FrontLeft();
	sf::Vector2f FrontRight();
	//Back points
	sf::Vector2f Back();
	sf::Vector2f BackLeft();
	sf::Vector2f BackRight();
	//Side points
	sf::Vector2f Left();
	sf::Vector2f Right();
	//Rows points
	sf::Vector2f rowsFrontLeft();
	sf::Vector2f rowsFrontRight();
	sf::Vector2f rowsBackLeft();
	sf::Vector2f rowsBackRight();
	sf::Vector2f rowsLeft();
	sf::Vector2f rowsRight();
	//Mouse
	bool mouseOver();
	bool mouseOver(std::string text);
	bool left();
	bool right();
	//Get data
	bool Float();
	float Integrity();
	float Speed();
	float SpeedRatio();
	float Power();
	short width();
	short Player();
	sf::Vector2f getSize();
	//Move
	bool move(sf::Vector2f target);
	void moveOrtogonal(float dist);
	void Speed(float speed);
	void Rows(float clock);
	//Fight
	void takeDamage(short damage);
	bool sink();
	~Ship();
};
#endif