#include "gui.h"
//Math functions
bool isInTriangle(sf::Vector2f a,sf::Vector2f b,sf::Vector2f c,sf::Vector2f d){
	return ((det(a,d,b)*det(a,c,d)>0)&&(det(a,d,b)*det(b,d,c)>0));
}
float area(sf::Vector2f a,sf::Vector2f b,sf::Vector2f c){
	return abs(det(a,b,c)/2);
}
float det(sf::Vector2f a,sf::Vector2f b,sf::Vector2f c){
	return a.x*b.y+a.y*c.x+b.x*c.y-b.y*c.x-a.x*c.y-a.y*b.x;
}
float dist(sf::Vector2f start,sf::Vector2f end){
	return sqrt((start.x-end.x)*(start.x-end.x)+(start.y-end.y)*(start.y-end.y));
}
float getAngle(sf::Vector2f start,sf::Vector2f end){
	//Calculate the angle
	float angle=atan((end.y-start.y)/(end.x-start.x))/0.017453293;
	//Get value on trigonometric circle
	if(end.x<start.x)
		angle+=180;
	if(angle<0)
		angle+=360;
	return angle;
}
//Constructor
GUI::GUI(){
	this->selected=0;
	//Screen
	this->winH=sf::VideoMode::getDesktopMode().height;
	this->winW=sf::VideoMode::getDesktopMode().width;
	this->scale=1;
	this->winX=this->winY=this->x=this->y=0;
	//Font
	this->font=new sf::Font();
	this->font->loadFromFile("data/GFSNeohellenic.ttf");
}
void GUI::Update(sf::RenderWindow *window){
	//Screen and window
	this->scale=(float)winW/window->getSize().x;
	this->winX=window->getPosition().x;
	this->winY=window->getPosition().y;
	window->setSize(sf::Vector2u(window->getSize().x,this->winH/this->scale));
}
unsigned GUI::width(){
	return this->winW;
}
unsigned GUI::height(){
	return this->winH;
}
float GUI::width(unsigned percent){
	return this->winW*percent/100.;
}
float GUI::height(unsigned percent){
	return this->winH*percent/100.;
}
//Mouse
bool GUI::canClick(short time){
	if(sf::milliseconds(click.getElapsedTime().asMilliseconds())<sf::milliseconds(time))
		return 0;
	click.restart();
	return 1;	
}
bool GUI::canLeft(short time){
	return (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&this->canClick(time));
}
bool GUI::canRight(short time){
	return (sf::Mouse::isButtonPressed(sf::Mouse::Right)&&this->canClick(time));
}
sf::Vector2f GUI::mousePosition(){
	float x=(sf::Mouse::getPosition().x-this->winX)*this->scale+this->x;
	float y=(sf::Mouse::getPosition().y-this->winY-30)*this->scale+this->y;
	if(this->scale<1.1)
		y+=50*this->scale;
	return sf::Vector2f(x,y);
}
//Text
sf::Font* GUI::Font(){
	return this->font;
}
std::string GUI::Format(float value){
	std::stringstream stream;
	stream<<std::fixed<<std::setprecision(1)<<value;
	return stream.str();
}
std::string GUI::Format(int value){
	if(value>999){
		return std::to_string(value/1000)+"."+std::to_string(value/100%10)+" k";
	}
	return std::to_string(value);
}
//Destructor
GUI::~GUI(){
	
}
GUI gui;