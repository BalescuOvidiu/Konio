#ifndef NODE_H
#define NODE_H
#include "gui.h"
//Node
class Node{
private:
	sf::Vector2f pos;
	short radius;
public:
	Node(short x,short y,short radius);
	//Rendering
	//Get data
	sf::Vector2f getPosition();
	short r();
	float dist(sf::Vector2f point);
	float dist(Node node);
	//Collisions
	bool contains(sf::Vector2f point);
	bool collision(Node node);
	~Node();
};
#endif