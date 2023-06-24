#ifndef MARINE_H
#define MARINE_H
#include "arrow.h"

class Marine{
private:
	bool alive;
	sf::Sprite *body;
public:
	//Weapon
	Arrow *arrow;
	//Constructor
	Marine(short x,short y,float angle);
	//Render
	void Render(sf::RenderWindow *window);
	//Basic
	bool Alive();
	bool kill(sf::Vector2f arrowPosition);
	void reload();
	void attack(sf::Vector2f target);
	void setColor(sf::Color color);
	//Rotation
	void rotate(float angle);
	void setRotation(float angle);
	float getRotation();
	float getRotationRad();
	//Points
	sf::Vector2f getPosition();
	void setPosition(float x,float y);
	void move(float x,float y);
	float Dist(sf::Vector2f point);
	//Collision
	bool contains(sf::Vector2f point);
	//Mouse
	bool mouseOver();
	bool left();
	bool right();
	~Marine();
};
//Texture
extern sf::Texture marineBody;
#endif