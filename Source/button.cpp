#include "button.h"

//Fixed 
Button::Button(std::string directory,short x,short y){
	this->tex=new sf::Texture();
	this->tex->loadFromFile(directory);
	this->tex->setSmooth(true);
	this->sprite=new sf::Sprite(*tex);
	this->sprite->setTextureRect(sf::IntRect(0,0,this->tex->getSize().x,this->tex->getSize().y/2));
	this->sprite->setOrigin(this->tex->getSize().x/2,this->tex->getSize().y/4);
	this->sprite->setPosition(x,y);
}
//For 2000px map
Button::Button(short x,short y,std::string directory){
	this->tex=new sf::Texture();
	this->tex->loadFromFile(directory);
	this->tex->setSmooth(true);
	this->sprite=new sf::Sprite(*tex);
	this->sprite->setTextureRect(sf::IntRect(0,0,this->tex->getSize().x,this->tex->getSize().y/2));
	this->sprite->setOrigin(this->tex->getSize().x/2,this->tex->getSize().y/4);
	this->sprite->setScale(gui.width()/2000.,gui.width()/2000.);
	this->sprite->setPosition(x*gui.width()/2000.,y*gui.width()/2000.);
}
//Percent
Button::Button(short x,short y,short width,std::string directory){
	this->tex=new sf::Texture();
	this->tex->loadFromFile(directory);
	this->tex->setSmooth(true);
	this->sprite=new sf::Sprite(*tex);
	this->sprite->setTextureRect(sf::IntRect(0,0,this->tex->getSize().x,this->tex->getSize().y/2));
	this->sprite->setScale(gui.width(width)/this->tex->getSize().x,gui.width(width)/this->tex->getSize().x);
	this->sprite->setPosition(gui.width(x),gui.height(y));
	this->sprite->setOrigin(this->tex->getSize().x/2,this->tex->getSize().y/4);
}
void Button::Render(sf::RenderWindow *window){
	window->draw(*this->sprite);
}
//Position
void Button::move(float x,float y){
	this->sprite->move(x,y);
}
void Button::setPosition(float x,float y){
	this->sprite->setPosition(x,y);
}
//Mouse over
bool Button::mouseOver(){
	if(this->sprite->getGlobalBounds().contains(gui.mousePosition())){
		this->sprite->setTextureRect(sf::IntRect(0,this->tex->getSize().y/2,this->tex->getSize().x,this->tex->getSize().y/2));
		return 1;
	}else
		this->sprite->setTextureRect(sf::IntRect(0,0,this->tex->getSize().x,this->tex->getSize().y/2));
	return 0;
}
bool Button::mouseOver(std::string title,std::string text){
	if(this->mouseOver()){
		about.show(title,text);
		return 1;
	}
	return 0;
}
//Mouse button
bool Button::left(){
	if(this->mouseOver()){
		if(gui.canLeft(400)){
			this->Pressed();
			return 1;
		}
	}
	return 0;
}
bool Button::right(){
	if(this->mouseOver()){
		if(gui.canRight(400)){
			this->Pressed();
			return 1;
		}
	}
	return 0;
}
bool Button::left(std::string title,std::string text){
	if(this->mouseOver(title,text)){
		if(gui.canLeft(400)){
			this->Pressed();
			return 1;
		}
	}
	return 0;
}
bool Button::right(std::string title,std::string text){
	if(this->mouseOver(title,text)){
		if(gui.canRight(400)){
			this->Pressed();
			return 1;
		}
	}
	return 0;
}
bool Button::left(std::string title,std::string text,sf::Keyboard::Key key){
	//Mouse
	if(this->mouseOver(title,text)){
		if(gui.canLeft(400)){
			this->Pressed();
			return 1;
		}
	}
	//Key
	if(gui.canClick(400)){
		if(sf::Keyboard::isKeyPressed(key)){
			this->Pressed();
			return 1;
		}
	}
	return 0;
}
bool Button::right(std::string title,std::string text,sf::Keyboard::Key key){
	//Mouse
	if(this->mouseOver(title,text)){
		if(gui.canRight(400)){
			this->Pressed();
			return 1;
		}
	}
	//Key
	if(gui.canClick(400)){
		if(sf::Keyboard::isKeyPressed(key)){
			this->Pressed();
			return 1;
		}
	}
	return 0;
}
void Button::Pressed(){
	gui.clickRestart();
	audio.Click();	
}
Button::~Button(){

}