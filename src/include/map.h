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
	void RenderRegions(sf::RenderWindow *window);
	void RenderWater(sf::RenderWindow *window);
	void move(short x,short y);
	void zoom(float factor);
	void Update();
	//Graphs
	void Dijkstra(short begin,short end);
	void clearRoute();
	bool collision(short i,short j);
	bool isOnWater(sf::Vector2f point);
	float Dist(short i,short j);
	short getNearestNode(sf::Vector2f point);
	Node GetNearestNode(sf::Vector2f point);
	Node getNode(short i);
	std::vector<Node> getRoute(sf::Vector2f begin,sf::Vector2f end);
	//Add functions
	void add(Region region);
	void add(Node node);
	~Map();
};
//Global Variable
extern Map *map;
#endif