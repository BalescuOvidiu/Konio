#ifndef FLEET_H
#define FLEET_H
#include "ship.h"

class Fleet{
private:
	//Graphics
	sf::Sprite *body,*sails,*rows;
	//Ships
	float provision,speed;
	short player,formation;
	std::vector<short> ship;
	std::vector<short> integrity;
	//Route
	std::vector<sf::Vector2i> route;
public:
	Fleet(sf::Vector2f pos,float angle,short player,short faction,short formation,float provision);
	//Update and rendering
	void Render(sf::RenderWindow *window);
	void Update();
	void addShip(short ship,short integrity);
	void addNodeRoute(sf::Vector2f point);
	void Move(float x,float y);
	void Stop();
	//Get data
	short Player();
	short Formation();
	short size();
	short Ship(short i);
	short Integrity(short i);
	//Rotation
	void rotate(float angle);
	void rotateTo(float angle);
	void setRotation(float angle);
	float getRotation();
	//Points
	void setOrigin();
	void setPosition(sf::Vector2f point);
	float getDist(sf::Vector2f point);
	bool contains(sf::Vector2f point);
	sf::Vector2f Origin();
	//Front points
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
	//Mouse
	bool mouseOver();
	bool left();
	~Fleet();
};
//Global variable
extern std::vector<Fleet> fleet;
//Global functions
short getShips(short player);
#endif