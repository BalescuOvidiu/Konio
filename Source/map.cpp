#include "map.h"
//Constructor
Map::Map(){
	this->tex=new sf::Texture();
	this->tex->loadFromFile("data/game/map/sprite.png");
	this->sprite=new sf::Sprite(*tex);
	this->sprite->setPosition(0,52);
	water=new Layer(1,64,"data/game/map/water.png");
}
//Rendering and update
void Map::Render(sf::RenderWindow *window){
	//Water
	this->water->Render(window);
	//Lands
	window->draw(*sprite);
	//Graph
	for(short i=0;i<(short)this->node.size();i++)
		this->node[i].Render(window);
	//Regions and settlements
	for(short i=0;i<(short)this->region.size();i++)
		this->region[i].Render(window);
}
void Map::move(short x,short y){
	this->water->move(x,y);
}
void Map::Update(){
	//Water
	this->water->Update();
	//Regions
	for(short i=0;i<(short)this->region.size();i++)
		this->region[i].Update();

}
//Graph
std::vector<short> Map::getRoute(short begin,short end){
	this->route.clear();
	this->selected.clear();
	this->selected.resize(this->node.size(),0);
	DFS(begin,end);
	return this->route;
}
bool Map::DFS(short begin,short end){
	this->selected[begin]=1;
	for(short i=0;i<(short)this->node.size();i++)
		if(i!=begin){
			if(i==end){
				this->route.push_back(i);
				return 1;
			}
			if(this->node[begin].collision(this->node[i])){
				if(DFS(i,end))
					this->route.push_back(i);
				else
					this->selected[i]=0;
			}
		}
	return 0;
}
short Map::getNearestNode(sf::Vector2f point){
	short min=0;
	float Dist=dist(point,this->node[0].Pos());
	for(short i=1;i<(short)this->node.size();i++)
		if(Dist>dist(point,this->node[i].Pos())){
			Dist=dist(point,this->node[i].Pos());
			min=i;
		}
	return min;
}
Node Map::getNode(short i){
	return this->node[i];
}
//Add functions
void Map::add(Region region){
	this->region.push_back(region);
}
void Map::add(Node node){
	this->node.push_back(node);
}
Map::~Map(){
	
}
//Global variable
Map *map;