#include "value.h"

Value::Value(short x,short y,short width,std::string directory){
	//Load texture
	this->tex=new sf::Texture();
	this->tex->loadFromFile(directory);
	this->tex->setSmooth(true);
	//Sprite
	this->sprite=new sf::Sprite(*tex);
	this->sprite->setTextureRect(sf::IntRect(0,0,this->tex->getSize().x,this->tex->getSize().y/2));
	this->sprite->setScale(gui.width(width)/this->tex->getSize().x,gui.width(width)/this->tex->getSize().x);
	this->sprite->setOrigin(this->tex->getSize().x/2,this->tex->getSize().y/4);
	this->sprite->setPosition(gui.width(x),gui.height(y));
	//Text
	this->text=new sf::Text();
	this->text->setString(sf::String(""));
	this->text->setFont(*gui.Font());
	this->text->setCharacterSize(36);
	this->text->setColor(sf::Color(255,255,255,230));
}
void Value::move(float x,float y){
	this->text->move(x,y);
	this->sprite->move(x,y);
}
void Value::zoom(float factor){
	//Sprite
	this->sprite->setPosition(gui.zoomed(this->sprite->getPosition(),factor));
	this->sprite->scale(factor,factor);
	//Text
	this->text->setPosition(gui.zoomed(this->text->getPosition(),factor));
	this->text->scale(factor,factor);
}
void Value::setPosition(float x,float y){
	this->text->setPosition(x,y);
	this->sprite->setPosition(x,y);
}
bool Value::mouseOver(){
	if(this->sprite->getGlobalBounds().contains(gui.mouseCoordinates().x,gui.mouseCoordinates().y)){
		this->sprite->setTextureRect(sf::IntRect(0,this->tex->getSize().y/2,this->tex->getSize().x,this->tex->getSize().y/2));
		return 1;
	}else
		this->sprite->setTextureRect(sf::IntRect(0,0,this->tex->getSize().x,this->tex->getSize().y/2));
	return 0;
}
bool Value::left(){
	return (sf::Mouse::isButtonPressed(sf::Mouse::Left));
}
bool Value::right(){
	return (sf::Mouse::isButtonPressed(sf::Mouse::Right));
}
bool Value::Update(float &value,float min,short max,float step,short type,std::string title,std::string text){
	bool change=0;
	if(this->mouseOver()){
		about.show(title,text);
		if(gui.canLeft(100)&&value>min){
			value-=step;
			change=1;
			gui.clickRestart();
		}
		else if(gui.canRight(100)&&value<max){
			value+=step;
			change=1;
			gui.clickRestart();
		}
	}
	if(value<10)
		this->text->setPosition(sprite->getPosition().x-gui.factor*tex->getSize().x/5+gui.factor*18,sprite->getPosition().y-gui.factor*tex->getSize().y/32);
	else if(value<100)
		this->text->setPosition(sprite->getPosition().x-gui.factor*tex->getSize().x/5+gui.factor*9,sprite->getPosition().y-gui.factor*tex->getSize().y/32);
	else
		this->text->setPosition(sprite->getPosition().x-gui.factor*tex->getSize().x/5,sprite->getPosition().y-gui.factor*tex->getSize().y/32);
	if(type)
		this->text->setString(sf::String(std::to_string((int)value)+" %"));
	else
		this->text->setString(sf::String(std::to_string((int)value)));
	return change;
}
void Value::Render(sf::RenderWindow *window){
	window->draw(*this->sprite);
	window->draw(*this->text);
}
Value::~Value(){

}