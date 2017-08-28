#include "node.h"

Node::Node(short x,short y,short radius){
	this->pos.x=x;
	this->pos.y=y+52;
	this->radius=radius;
	this->circle=new sf::CircleShape(radius,64);
	this->circle->setFillColor(sf::Color(255,0,0,128));
	this->circle->setOrigin(radius,radius);
	this->circle->setPosition(x,y+52);
}
void Node::Render(sf::RenderWindow *window){
	window->draw(*this->circle);
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