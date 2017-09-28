#include "label.h"

Label::Label(short x,short y,short width,short height,bool visible){
	this->visible=visible;
	//Rectangle
	this->rectangle=new sf::RectangleShape();
	this->rectangle->setPosition(x,y);
	this->rectangle->setSize(sf::Vector2f(width,height));
	this->rectangle->setFillColor(sf::Color(0,0,0,200));
	//Title
	this->title=new sf::Text();
	this->title->setString(sf::String(""));
	this->title->setFont(*gui.Font());
	this->title->setCharacterSize(32);
	this->title->setColor(sf::Color(255,255,255));
	this->title->setPosition(x+8,y+5);
	//Text
	this->text=new sf::Text();
	this->text->setString(sf::String(""));
	this->text->setFont(*gui.Font());
	this->text->setCharacterSize(22);
	this->text->setColor(sf::Color(255,255,255));
	this->text->setPosition(x+8,y+55);
}
//Properties
void Label::move(float x,float y){
	this->title->move(x,y);
	this->text->move(x,y);
	this->rectangle->move(x,y);
}
void Label::setPosition(float x,float y){
	this->title->setPosition(x,y);
	this->text->setPosition(x,y);
	this->rectangle->setPosition(x,y);
}
void Label::setTitle(std::string string){
	this->title->setString(sf::String(string));
}
void Label::setText(std::string string){
	this->text->setString(sf::String(string));
}
void Label::setSize(short width,short height){
	this->rectangle->setSize(sf::Vector2f(width,height));
}
//Toggle
void Label::hide(){
	this->visible=0;
}
void Label::show(){
	this->visible=1;
}
void Label::show(std::string title,std::string text){
	this->title->setString(sf::String(title));
	this->text->setString(sf::String(text));
	this->visible=1;
}
void Label::reset(){
	this->move(-gui.x,-gui.y);
	this->hide();
}
//Mouse
bool Label::mouseOver(){
	return (this->rectangle->getGlobalBounds().contains(gui.mousePosition().x,gui.mousePosition().y));
}
bool Label::left(){
	return (this->mouseOver()&&sf::Mouse::isButtonPressed(sf::Mouse::Left));
}
bool Label::right(){
	return (this->mouseOver()&&sf::Mouse::isButtonPressed(sf::Mouse::Right));
}
void Label::Render(sf::RenderWindow *window){
	window->draw(*this->rectangle);
	window->draw(*this->title);
	window->draw(*this->text);
}
Label::operator bool(){
	return this->visible;
}
Label::~Label(){
	
}
//Label with information about content
Label about(0,gui.height()-120,gui.width(),120,0),detail(0,0,325,180,0);