#ifndef SHIP_H
#define SHIP_H
#include "naval.h"
#include "gameData.h"
//Ship
class Ship{
private:
	short fleet,id;
	float speed,integrity,clock;
	//Sprites
	sf::Sprite *body,*ram,*rows,*sails;
	//Move
	void Move(float x,float y);
public:
	//Constructor
	Ship(short fleet,short id,short faction,short integrity,short x,short y,float angle);
	//Render
	void RenderBody(sf::RenderWindow *window);
	void RenderRam(sf::RenderWindow *window);
	void RenderRows(sf::RenderWindow *window);
	void RenderSails(sf::RenderWindow *window);
	//Basic
	void show();
	void setColor(sf::Color color);
	//Rotation
	void rotate(float angle);
	void setRotation(float angle);
	float getRotation();
	float getRotationRad();
	//Points
	void setPosition(float x,float y);
	float dist(sf::Vector2f point);
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
	bool left();
	bool right();
	//Get data
	bool Stopped();
	bool Float();
	float Integrity();
	float SpeedMax();
	float SpeedOnFrame();
	float Speed();
	float SpeedRatio();
	float Power();
	short Direction();
	short Fleet();
	//Size
	short width();
	short widthRows();
	short height();
	sf::Vector2f getSize();
	//Move
	bool move(sf::Vector2f target);
	void Speed(float speed);
	void Rows(float clock);
	//Fight
	void takeDamage(short damage);
	bool sink();
	~Ship();
};
#endif