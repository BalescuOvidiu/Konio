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
	void addShip(short ship,short integrity);
	void removeShip(short ship);
	void setIntegrity(short ship,short integrity);
	void Reform(short formation);
	void Retreat();
	void Supply();
	//Route
	void addNodeRoute(Node node);
	void getRoute(std::vector<Node> route);
	void resetRoute();
	//Move
	void Move(float x,float y);
	void Clock(float clock);
	void Stop();
	//Get data
	short Player();
	short Formation();
	short Provision();
	short Direction();
	short size();
	short Ship(short i);
	short Integrity(short i);
	float Upkeep();
	float Speed();
	float SpeedOnFrame();
	float Power();
	//Rotation
	void rotate(float angle);
	void rotateTo(float angle);
	void setRotation(float angle);
	float getRotation();
	float getRotationRad();
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
//Global variables
extern std::vector<Fleet> fleet;
extern Naval nFleet;
//Global functions
float distFleet(short i,short j);
short getShips(short player);
short getNearestFleet(sf::Vector2f point);
std::string FleetInfo(short i);
//Diplomacy
bool isYourFleet(short i);
bool isEnemyFleet(short i,short j);
bool isAlliedFleet(short i,short j);
//Formations
std::string FormationName(short formation);
std::string FormationText(short formation);
#endif