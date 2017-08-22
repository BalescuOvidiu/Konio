#ifndef NODE_H
#define NODE_H
#include "gui.h"
//Node
class Node{
private:
	sf::Vector2f pos;
	sf::CircleShape *circle;
	short radius;
public:
	Node(short x,short y,short radius);
	//Rendering
	void Render(sf::RenderWindow *window);
	//Get data
	sf::Vector2f Pos();
	short X();
	short Y();
	short R();
	float dist(sf::Vector2f point);
	//Collisions
	bool contain(sf::Vector2f point);
	bool collision(Node node);
	~Node();
};
#endif