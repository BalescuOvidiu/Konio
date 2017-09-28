#include "node.h"

Node::Node(short x,short y,short radius){
	this->pos.x=x;
	this->pos.y=y;
	this->radius=radius;
}
//Get data
sf::Vector2f Node::getPosition(){
	return this->pos;
}
short Node::r(){
	return this->radius;
}
float Node::dist(sf::Vector2f point){
	return ::dist(this->pos,point);
}
float Node::dist(Node node){
	return ::dist(this->pos,node.getPosition());
}
//Collsions
bool Node::contains(sf::Vector2f point){
	return(this->dist(point)<=this->radius);
}
bool Node::collision(Node node){
	return(this->dist(node.getPosition())<=(this->radius+node.r()));
}
Node::~Node(){

}