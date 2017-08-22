#include "node.h"

Node::Node(short x,short y,short radius){
	this->pos.x=x;
	this->pos.y=y;
	this->radius=radius;
	this->circle=new sf::CircleShape(radius,30);
	this->circle->setFillColor(sf::Color(255,0,0,128));
	this->circle->setPosition(x,y+52);
}
void Node::Render(sf::RenderWindow *window){
	window->draw(*this->circle);
}
//Get data
sf::Vector2f Node::Pos(){
	return this->pos;
}
short Node::X(){
	return this->pos.x;
}
short Node::Y(){
	return this->pos.y;
}
short Node::R(){
	return this->radius;
}
float Node::dist(sf::Vector2f point){
	return ::dist(this->pos,point);
}
//Collsions
bool Node::contain(sf::Vector2f point){
	return(dist(point)<=this->radius);
}
bool Node::collision(Node node){
	return(this->dist(node.Pos())<=(this->radius+node.R()));
}
Node::~Node(){

}