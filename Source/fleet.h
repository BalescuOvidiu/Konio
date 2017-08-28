#ifndef FLEET_H
#define FLEET_H
#include "naval.h"
#include "player.h"
#include "node.h"

class Fleet{
private:
	//Graphics
	sf::Sprite *body,*sails,*rows;
	//Ships
	float clock;
	float provision,speed;
	short player,formation;
	std::vector<short> ship;
	std::vector<short> integrity;
	//Route
	std::vector<Node> route;
public:
	Fleet(sf::Vector2f pos,float angle,short player,short formation,float provision);
	//Update and rendering
	void Render(sf::RenderWindow *window);
	void Update();
	void Lost();
	void addShip(short ship,short integrity);
	//Route
	void addNodeRoute(Node node);
	void resetRoute();
	//Move
	void Move(float x,float y);
	void Stop();
	//Get data
	short Player();
	short Formation();
	short Provision();
	short size();
	short Ship(short i);
	short Integrity(short i);
	//Rotation
	void rotate(float angle);
	void rotateTo(float angle);
	void setRotation(float angle);
	float getRotation();
	//Points
	void setPosition(sf::Vector2f point);
	float dist(sf::Vector2f point);
	bool contains(sf::Vector2f point);
	sf::Vector2f getPosition();
	//Mouse
	bool mouseOver();
	bool left();
	~Fleet();
};
//Global variable
extern std::vector<Fleet> fleet;
//Global functions
float distFleet(short i,short j);
short getShips(short player);
short getNearestFleet(sf::Vector2f point);
bool isYourFleet(short i);
bool isEnemyFleet(short i,short j);
bool isAlliedFleet(short i,short j);
#endif