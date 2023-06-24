#include "gui.h"
//File variables
std::ifstream in;
std::ifstream out;
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
float Dist(sf::Vector2f start,sf::Vector2f end){
	return ((start.x-end.x)*(start.x-end.x)+(start.y-end.y)*(start.y-end.y));
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
float getRadians(sf::Vector2f start,sf::Vector2f end){
	//Calculate the angle
	float angle=atan((end.y-start.y)/(end.x-start.x))/0.017453293;
	//Get value on trigonometric circle
	if(end.x<start.x)
		angle+=180;
	if(angle<0)
		angle+=360;
	return angle*0.017453293;
}
float max(float a,float b){
	if(a<b)
		return b;
	return a;
}
float square(float a){
	return a*a;
}
float Sin(float angle){
	return sin(angle*0.017453293);
}
float Cos(float angle){
	return cos(angle*0.017453293);
}
float Rad(float angle){
	return angle*0.017453293;
}
//Text
std::string Format(double value){
	std::stringstream stream;
	stream<<std::fixed<<std::setprecision(1)<<value;
	return stream.str();
}
std::string Format(int value){
	if(value>999){
		return std::to_string(value/1000)+"."+std::to_string(value/100%10)+" k";
	}
	return std::to_string(value);
}
std::string Format(unsigned value){
	if(value>999){
		return std::to_string(value/1000)+"."+std::to_string(value/100%10)+" k";
	}
	return std::to_string(value);
}
//Constructor
GUI::GUI(){
	//Screen
	this->factor=1;
	this->selected=1;
	this->w=sf::VideoMode::getDesktopMode().width;
	this->h=sf::VideoMode::getDesktopMode().height;
	//Font
	this->font=new sf::Font();
	this->font->loadFromFile("data/GFSNeohellenic.ttf");
}
//Screen
unsigned GUI::width(){
	return this->w;
}
unsigned GUI::height(){
	return this->h;
}
float GUI::width(unsigned percent){
	return this->w*percent/100.;
}
float GUI::height(unsigned percent){
	return this->h*percent/100.;
}
sf::Vector2f GUI::center(){
	return sf::Vector2f(
		this->x+this->w/2,
		this->y+this->h/2
	);
}
sf::Vector2f GUI::zoomed(sf::Vector2f point,float factor){
	return sf::Vector2f(
		(point.x-this->center().x)*factor+this->center().x,
		(point.y-this->center().y)*factor+this->center().y
	);
}
sf::Vector2f GUI::zoomed(sf::Vector2f point){
	return sf::Vector2f(
		(point.x-this->center().x)*this->factor+this->center().x,
		(point.y-this->center().y)*this->factor+this->center().y
	);
}
//Mouse
bool GUI::canClick(short time){
	return (this->click.getElapsedTime().asMilliseconds()>=time);
}
bool GUI::canLeft(short time){
	if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return (this->canClick(time));
	return 0;
}
bool GUI::canRight(short time){
	if(sf::Mouse::isButtonPressed(sf::Mouse::Right))
		return (this->canClick(time));
	return 0;
}
void GUI::clickRestart(){
	this->click.restart();
}
sf::Vector2f GUI::mouseCoordinates(){
	return this->zoomed(this->mousePosition());
}
sf::Vector2f GUI::mousePosition(){
	return sf::Vector2f(sf::Mouse::getPosition().x+this->x,sf::Mouse::getPosition().y+this->y);
}
//Text
sf::Font* GUI::Font(){
	return this->font;
}
//Destructor
GUI::~GUI(){
	
}
GUI gui;