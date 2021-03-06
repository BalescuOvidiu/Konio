#include "region.h"
//Basic
Region::Region(short x,short y,short size,std::string name){
	this->name=new sf::Text(sf::String(name),*gui.Font(),size);
	this->name->setPosition(x,y);
	this->name->setColor(sf::Color(0,0,0));
}
void Region::Render(sf::RenderWindow *window){
	if(Dist(this->name->getPosition(),gui.mousePosition())<1040400){
		this->name->setColor(sf::Color(0,0,0,(255-Dist(this->name->getPosition(),gui.mousePosition())/4080)));
		window->draw(*this->name);
	}
}
//Get data
std::string Region::getName(){
	return this->name->getString().toAnsiString();
}
//Delete
Region::~Region(){

}