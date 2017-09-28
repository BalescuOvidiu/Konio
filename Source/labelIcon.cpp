#include "labelIcon.h"

LabelIcon::LabelIcon(short x,short y,std::string directory){
	//Button
	this->tex=new sf::Texture();
	this->tex->loadFromFile(directory);
	this->tex->setSmooth(true);
	this->sprite=new sf::Sprite(*tex);
	this->sprite->setTextureRect(sf::IntRect(0,0,this->tex->getSize().x,this->tex->getSize().y/2));
	this->sprite->setPosition(x,y);
	//Text
	this->text=new sf::Text();
	this->text->setString(sf::String(""));
	this->text->setFont(*gui.Font());
	this->text->setCharacterSize(22);
	this->text->setColor(sf::Color(255,255,255));
	this->text->setPosition(x+this->tex->getSize().x+5,y);
}
//Properties
void LabelIcon::move(float x,float y){
	this->sprite->move(x,y);
	this->text->move(x,y);
}
void LabelIcon::setPosition(float x,float y){
	this->sprite->setPosition(x,y);
	this->text->setPosition(x,y);
}
void LabelIcon::setText(std::string string){
	this->text->setString(sf::String(string));
}
//Mouse
bool LabelIcon::mouseOver(){
	if(this->sprite->getGlobalBounds().contains(gui.mousePosition())){
		this->sprite->setTextureRect(sf::IntRect(0,this->tex->getSize().y/2,this->tex->getSize().x,this->tex->getSize().y/2));
		return 1;
	}else
		this->sprite->setTextureRect(sf::IntRect(0,0,this->tex->getSize().x,this->tex->getSize().y/2));
	return 0;
}
bool LabelIcon::mouseOver(std::string title,std::string text){
	if(this->mouseOver()){
		about.show(title,text);
		return 1;
	}
	return 0;
}
bool LabelIcon::left(){
	return (this->mouseOver()&&sf::Mouse::isButtonPressed(sf::Mouse::Left));
}
bool LabelIcon::right(){
	return (this->mouseOver()&&sf::Mouse::isButtonPressed(sf::Mouse::Right));
}
void LabelIcon::Render(sf::RenderWindow *window){
	window->draw(*this->sprite);
	window->draw(*this->text);
}
LabelIcon::~LabelIcon(){
	
}