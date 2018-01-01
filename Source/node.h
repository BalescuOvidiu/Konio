#ifndef NODE_H
#define NODE_H
#include "gui.h"
//Node
class Node{
private:
	sf::Vector2f pos;
	short radius;
public:
	Node(sf::Vector2f point,short radius);
	Node(short x,short y,short radius);
	//Get data
	sf::Vector2f getPosition();
	short r();
	float Dist(sf::Vector2f point);
	float Dist(Node node);
	//Collisions
	bool contains(sf::Vector2f point);
	bool collision(Node node);
	~Node();
};
//Guide
std::vector<sf::Vertex> getGuide(sf::Vector2f point,std::deque<sf::Vector2f> route,sf::Color color);
std::vector<sf::Vertex> getGuide(sf::Vector2f point,std::vector<Node> route,sf::Color color);
std::vector<sf::Vertex> setGuideColor(std::vector<sf::Vertex> guide,sf::Color color);
#endif