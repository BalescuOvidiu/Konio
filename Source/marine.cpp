#include "marine.h"
//Constructor
Marine::Marine(short x,short y,float angle){
	this->alive=1;
	this->arrow=NULL;
	this->body=new sf::Sprite(marineBody);
	this->body->setOrigin(5,5);
	this->body->setPosition(x,y);
	this->body->setRotation(angle);
	this->body->setTextureRect(sf::IntRect(0,0,10,10));
}
//Render
void Marine::Render(sf::RenderWindow *window){
	if(this->arrow!=NULL)
		this->arrow->Render(window);
	window->draw(*this->body);
}
//Basic
bool Marine::Alive(){
	return this->alive;
}
bool Marine::kill(sf::Vector2f arrowPosition){
	if(this->contains(arrowPosition)){
		this->alive=0;
		this->body->setTextureRect(sf::IntRect(10,0,10,10));
		return 1;
	}
	return 0;
}
void Marine::reload(){
	delete this->arrow;
	this->arrow=NULL;
}
void Marine::attack(sf::Vector2f target){
	if(alive){
		this->body->setRotation(getAngle(this->body->getPosition(),target));
		this->arrow=new Arrow(this->body->getPosition(),target);
	}
}
void Marine::setColor(sf::Color color){
	this->body->setColor(color);
}
//Rotation
void Marine::rotate(float angle){
	this->body->rotate(angle);
}
void Marine::setRotation(float angle){
	this->body->setRotation(angle);
}
float Marine::getRotation(){
	return this->body->getRotation();
}
float Marine::getRotationRad(){
	return this->body->getRotation()*0.017453293;
}
//Points
sf::Vector2f Marine::getPosition(){
	return this->body->getPosition();
}
void Marine::setPosition(float x,float y){
	this->body->setPosition(x,y);
}
void Marine::move(float x,float y){
	this->body->move(x,y);
}
float Marine::Dist(sf::Vector2f point){
	return ::Dist(this->body->getPosition(),point);
}
//Collision
bool Marine::contains(sf::Vector2f point){
	return Dist(point)<64;
}
//Mouse
bool Marine::mouseOver(){
	return this->contains(gui.mouseCoordinates());
}
bool Marine::left(){
	return this->mouseOver()&&gui.canLeft(300);
}
bool Marine::right(){
	return this->mouseOver()&&gui.canRight(300);
}
Marine::~Marine(){
	
}
//Texture
sf::Texture marineBody;