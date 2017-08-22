#include "region.h"
//Basic
Region::Region(short x,short y,short size,std::string name){
	this->name=new sf::Text(sf::String(name),*gui.Font(),size);
	this->name->setPosition(x,y);
	this->name->setColor(sf::Color(0,0,0));
}
void Region::Render(sf::RenderWindow *window){
	if(this->name->getColor().a>0)
		window->draw(*this->name);
}
//Update
void Region::Update(){
	if(dist(this->name->getPosition(),gui.mousePosition())<1020)
		this->name->setColor(sf::Color(0,0,0,(255-dist(this->name->getPosition(),gui.mousePosition())/4)));
	else
		this->name->setColor(sf::Color(0,0,0,0));
}
//Get data
std::string Region::getName(){
	return this->name->getString().toAnsiString();
}
//Delete
Region::~Region(){

}