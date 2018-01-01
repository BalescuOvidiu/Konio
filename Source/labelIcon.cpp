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
void LabelIcon::zoom(float factor){
	//Sprite
	this->sprite->setPosition(gui.zoomed(this->sprite->getPosition(),factor));
	this->sprite->scale(factor,factor);
	//Text
	this->text->setPosition(gui.zoomed(this->text->getPosition(),factor));
	this->text->scale(factor,factor);
}
void LabelIcon::setPosition(float x,float y){
	this->sprite->setPosition(x,y);
	this->text->setPosition(x,y);
}
void LabelIcon::setText(std::string string){
	this->text->setString(sf::String(string));
}
//Mouse over
bool LabelIcon::mouseOver(){
	if(this->sprite->getGlobalBounds().contains(gui.mouseCoordinates())){
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
//Mouse button
bool LabelIcon::left(){
	if(this->mouseOver()){
		if(gui.canLeft(400)){
			this->Pressed();
			return 1;
		}
	}
	return 0;
}
bool LabelIcon::right(){
	if(this->mouseOver()){
		if(gui.canRight(400)){
			this->Pressed();
			return 1;
		}
	}
	return 0;
}
bool LabelIcon::left(std::string title,std::string text){
	if(this->mouseOver(title,text)){
		if(gui.canLeft(400)){
			this->Pressed();
			return 1;
		}
	}
	return 0;
}
bool LabelIcon::right(std::string title,std::string text){
	if(this->mouseOver(title,text)){
		if(gui.canRight(400)){
			this->Pressed();
			return 1;
		}
	}
	return 0;
}
void LabelIcon::Render(sf::RenderWindow *window){
	window->draw(*this->sprite);
	window->draw(*this->text);
}
void LabelIcon::Pressed(){
	gui.clickRestart();
	audio.Click();	
}
LabelIcon::~LabelIcon(){
	
}