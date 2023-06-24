#ifndef ARROW_H
#define ARROW_H
#include "naval.h"
#include "gameData.h"

class Arrow{
private:
	float distance;
	sf::Sprite *sprite;
public:
	//Constructor
	Arrow(sf::Vector2f position,sf::Vector2f target);
	//Render
	void Render(sf::RenderWindow *window);
	//Basic
	void Update();
	bool canHit();
	//Rotation
	void rotate(float angle);
	void setRotation(float angle);
	float getRotation();
	float getRotationRad();
	//Points
	sf::Vector2f getPosition();
	void setPosition(float x,float y);
	~Arrow();
};
//Texture
extern sf::Texture arrowTexture;
#endif