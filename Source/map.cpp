#include "map.h"
//Constructor
Map::Map(){
	this->tex=new sf::Texture();
	this->tex->loadFromFile("data/game/map/sprite.png");
	this->sprite=new sf::Sprite(*tex);
	this->sprite->setPosition(0,0);
	water=new Layer(1,256,"data/game/map/water.png");
}
//Rendering and update
void Map::Render(sf::RenderWindow *window){
	//Water
	this->water->Render(window);
	//Lands
	window->draw(*sprite);
}
void Map::RenderRegions(sf::RenderWindow *window){
	for(unsigned i=0;i<this->region.size();i++)
		this->region[i].Render(window);
}
void Map::RenderWater(sf::RenderWindow *window){
	this->water->Render(window);
}
void Map::move(short x,short y){
	this->water->move(x,y);
}
void Map::zoom(float factor){
	this->water->zoom(factor);
}
void Map::Update(){
	//Water
	this->water->Update();
}
//Graph
void Map::Dijkstra(short begin,short end){
	//If begin is adiacent with end
	if(this->node[begin].collision(this->node[end])){
		this->selected[end]=1;
		this->route.push_back(this->node[end]);
		return ;
	}
	//Arrays data for search
	this->selected[begin]=1;
	for(unsigned i=0;i<this->node.size();i++)
		if(!selected[i]){
			if(collision(begin,i)){
				d.push_back(1);
				t.push_back(begin);
			}else{
				d.push_back(999);
				t.push_back(-1);
			}
		}else{
			d.push_back(0);
			t.push_back(-1);
		}
	//Search
	for(unsigned j=1;j<this->node.size();j++){
		//Get nearest unselected node
		short near=-1;
		float minDist=999999999;
		for(unsigned i=0;i<this->node.size();i++)
			if(!selected[i]){
				if(minDist>this->d[i]){
					near=i;
					minDist=this->d[i];
				}
			}
		selected[near]=1;
		//Get list
		minDist=999999999;
		for(unsigned i=0;i<this->node.size();i++)
			if(collision(near,i)&&!selected[i]){
				if(d[i]>d[near]+1){
					d[i]=d[near]+1;
					t[i]=near;
				}
			}
	}
	//Get route
	while(t[end]!=-1){
		this->route.insert(this->route.begin(),this->node[end]);
		end=t[end];
	}
}
void Map::clearRoute(){
	this->t.clear();
	this->route.clear();
	this->selected.clear();
	this->d.clear();
}
bool Map::collision(short i,short j){
	return (this->node[i].collision(this->node[j]));
}
bool Map::isOnWater(sf::Vector2f point){
	for(unsigned i=1;i<this->node.size();i++)
		if(this->node[i].contains(point))
			return 1;
	return 0;
}
float Map::Dist(short i,short j){
	return this->node[i].Dist(this->node[j]);
}
short Map::getNearestNode(sf::Vector2f point){
	short nearest=0;
	float Dist=this->node[0].Dist(point);
	if(this->node[0].contains(point))
		return 0;
	for(unsigned i=1;i<this->node.size();i++){
		if(this->node[i].contains(point))
			return i;
		if(Dist>this->node[i].Dist(point)){
			Dist=this->node[i].Dist(point);
			nearest=i;
		}
	}
	return nearest;
}
Node Map::GetNearestNode(sf::Vector2f point){
	return this->getNode(this->getNearestNode(point));
}
Node Map::getNode(short i){
	return this->node[i];
}
std::vector<Node> Map::getRoute(sf::Vector2f begin,sf::Vector2f end){
	this->clearRoute();
	this->selected.resize(this->node.size(),0);
	this->Dijkstra(this->getNearestNode(begin),this->getNearestNode(end));
	return this->route;
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