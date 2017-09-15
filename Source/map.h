#ifndef MAP_H
#define MAP_H
#include "node.h"
#include "region.h"
//Map
class Map{
private:
	//Graphics
	sf::Texture *tex;
	sf::Sprite *sprite;
	//Water
	Layer *water;
	//Regions
	std::vector<Region> region;
	//Graph
	std::vector<Node> node;
	std::vector<Node> route;
	//For search of route
	std::vector<bool> selected;
	std::vector<short> t;
	std::vector<short> d;
public:
	Map();
	//Rendering and update
	void Render(sf::RenderWindow *window);
	void move(short x,short y);
	void Update();
	//Graphs
	void Dijkstra(short begin,short end);
	void clearRoute();
	bool collision(short i,short j);
	float dist(short i,short j);
	short getNearestNode(sf::Vector2f point);
	Node GetNearestNode(sf::Vector2f point);
	Node getNode(short i);
	std::vector<Node> getRoute(short begin,short end);
	//Add functions
	void add(Region region);
	void add(Node node);
	~Map();
};
//Global Variable
extern Map *map;
#endif