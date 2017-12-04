#ifndef FLEET_H
#define FLEET_H
#include "naval.h"
#include "player.h"
#include "node.h"

class Fleet{
private:
	//Graphics
	sf::Sprite *body,*sails;
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
	void Supply(float provision);
	//Route
	void addNodeRoute(Node node);
	void getRoute(std::vector<Node> route);
	void resetRoute();
	//Move
	void Move(float x,float y);
	void Stop();
	//Get data
	short Player();
	short Formation();
	short Provision();
	short Direction();
	short size();
	short getShips(short id);
	short Ship(short i);
	short Integrity(short i);
	float Upkeep();
	float Speed();
	float SpeedOnFrame();
	float Power();
	float Randament();
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
	sf::Vector2f getTarget();
	std::vector<Node> getRoute();
	//Mouse
	bool mouseOver();
	bool left();
	~Fleet();
};
//Global variables
extern std::vector<Fleet> fleet;
extern sf::Texture fleetBody;
//Formations
std::string FormationName(short formation);
std::string FormationText(short formation);
#endif