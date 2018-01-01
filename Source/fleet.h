#ifndef FLEET_H
#define FLEET_H
#include "naval.h"
#include "player.h"
#include "map.h"

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
	std::vector<short> marines;
	//Route
	std::vector<Node> route;
public:
	Fleet(sf::Vector2f pos,float angle,short player,short formation,float provision);
	//Update and rendering
	void RenderBody(sf::RenderWindow *window);
	void RenderSail(sf::RenderWindow *window);
	void Update();
	void addShip(short ship,short integrity,short marines);
	void removeShip(short ship);
	void setIntegrity(short ship,short integrity);
	void setMarines(short ship,short marines);
	void Reform(short formation);
	void Retreat();
	void Supply();
	void Supply(float provision);
	void setColor(sf::Color color);
	//Move
	void Move(sf::Vector2f target);
	void MoveAdd(sf::Vector2f target);
	void move(float x,float y);
	void Stop();
	//Get data
	short Player();
	short Formation();
	short Provision();
	short Direction();
	short size();
	short getShips(short id);
	std::string getShipsString(short id);
	short Ship(short i);
	short Integrity(short i);
	short Marines(short i);
	short Range();
	float Upkeep();
	float Speed();
	float SpeedOnFrame();
	float Power();
	float Randament();
	//Rotation
	void rotate(float angle);
	void setRotation(float angle);
	float getRotation();
	float getRotationRad();
	//Points
	void setPosition(sf::Vector2f point);
	float Dist(sf::Vector2f point);
	bool contains(sf::Vector2f point);
	bool isInRange(sf::Vector2f point);
	sf::Vector2f Front();
	sf::Vector2f getPosition();
	sf::Vector2f getRangePosition();
	sf::Vector2f getTarget();
	std::vector<Node> getRoute();
	//Mouse
	bool mouseOver();
	bool left();
	bool right();
	~Fleet();
};
//Global variables
extern std::vector<Fleet> fleet;
extern sf::Texture fleetBody;
extern short nFormation;
//Formations
std::string FormationName(short formation);
std::string FormationText(short formation);
#endif