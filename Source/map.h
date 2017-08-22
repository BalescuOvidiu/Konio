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
	std::vector<bool> selected;
	std::vector<short> route;
public:
	Map();
	//Rendering and update
	void Render(sf::RenderWindow *window);
	void move(short x,short y);
	void Update();
	//Graph
	bool DFS(short begin,short end);
	short getNearestNode(sf::Vector2f point);
	std::vector<short> getRoute(short begin,short end);
	Node getNode(short i);
	//Add functions
	void add(Region region);
	void add(Node node);
	~Map();
};
//Global Variable
extern Map *map;
#endif