#include "fleet.h"
//Constructor
Fleet::Fleet(sf::Vector2f pos,float angle,short player,short formation,float provision){
	//Main properties
	this->player=player;
	this->provision=provision;
	this->formation=formation;
	this->speed=0;
	//Body
	this->body=new sf::Sprite(fleetBody);
	//Sails
	this->sails=new sf::Sprite(::sails);
	this->sails->setTextureRect(sf::IntRect(14*(::player[player].Faction()),0,14,140));
	//Origin
	this->body->setOrigin(fleetBody.getSize().x/2,fleetBody.getSize().y/2);
	this->sails->setOrigin(0,::sails.getSize().y/2);
	//Orientation
	this->setPosition(pos);
	this->setRotation(angle);
	//Scale
	this->sails->setScale(0.4,0.4);
}
//Update and rendering
void Fleet::RenderBody(sf::RenderWindow *window){
	window->draw(*this->body);
}
void Fleet::RenderSail(sf::RenderWindow *window){
	window->draw(*this->sails);
}
void Fleet::Update(){
	this->provision-=0.014;
	//Move
	if(this->route.size()){
		//Stop
		if(this->route[0].contains(this->getPosition())){
			this->route.erase(this->route.begin());
			return;
		}
		if(this->Dist(route[0].getPosition())<64&&route.size()<16){
			this->route.erase(this->route.begin());
			return;
		}
		//Get the angles
		float angle=getAngle(this->getPosition(),this->route[0].getPosition());
		float delta=this->body->getRotation()-angle;
		float rotationSpeed=this->Randament();
		//Get way
		if(fabs(delta)>180)
			rotationSpeed*=-1;
		//Change angle
		if(delta<0){
			if(0<delta+rotationSpeed)
				this->rotate(angle-this->body->getRotation());
			else{
				this->rotate(rotationSpeed);
			}
		}
		else if(delta>0){
			if(0>delta-rotationSpeed)
				this->rotate(angle-this->body->getRotation());
			else{
				rotationSpeed*=-1;
				this->rotate(rotationSpeed);
			}
		}else
			rotationSpeed=0;
		//Sails
		if(rotationSpeed){
			if(fabs(rotationSpeed+this->sails->getRotation()-this->body->getRotation())<30)
				this->sails->rotate(rotationSpeed);
		}
		//Modify speed
		this->speed=10*this->Randament();
		//Move
		this->move(
			this->SpeedOnFrame()*cos(this->getRotationRad()),
			this->SpeedOnFrame()*sin(this->getRotationRad())
		);
	}else if(this->speed){
		this->Stop();
	}
}
void Fleet::addShip(short ship,short integrity,short marines){
	this->ship.push_back(ship);
	this->integrity.push_back(integrity);
	this->marines.push_back(marines);
}
void Fleet::removeShip(short ship){
	this->ship.erase(this->ship.begin()+ship);
	this->integrity.erase(this->integrity.begin()+ship);
	this->marines.erase(this->marines.begin()+ship);
}
void Fleet::setIntegrity(short ship,short integrity){
	this->integrity[ship]=integrity;
}
void Fleet::setMarines(short ship,short marines){
	this->marines[ship]=marines;
}
void Fleet::Reform(short formation){
	this->formation=formation;
}
void Fleet::Retreat(){
	this->integrity.clear();
	this->ship.clear();
}
void Fleet::Supply(){
	this->provision=100;
	for(short i=0;i<(short)this->integrity.size();i++)
		this->integrity[i]=100;
}
void Fleet::Supply(float provision){
	this->provision+=provision;
	if(this->provision>100)
		this->provision=100;
}
void Fleet::setColor(sf::Color color){
	this->body->setColor(color);
	this->sails->setColor(color);
}
//Move
void Fleet::Move(sf::Vector2f target){
	if(map->isOnWater(target)&&::Dist(this->getTarget(),target)>=64){
		this->route.clear();
		this->route=map->getRoute(this->getPosition(),target);
		this->route.push_back(Node(target,60));
	}
}
void Fleet::MoveAdd(sf::Vector2f target){
	if(map->isOnWater(target)&&::Dist(this->getTarget(),target)>=64){
		std::vector<Node> data=map->getRoute(this->getTarget(),target);
		while(data.size()){
			this->route.push_back(data[0]);
			data.erase(data.begin());
		}
		this->route.push_back(Node(target,60));
	}
}
void Fleet::move(float x,float y){
	this->body->move(x,y);
	this->sails->move(x,y);
}
void Fleet::Stop(){
	this->speed=0;
	this->route.clear();
}
//Get data
short Fleet::Player(){
	return this->player;
}
short Fleet::Formation(){
	return this->formation;
}
short Fleet::Provision(){
	return this->provision;
}
short Fleet::Direction(){
	if(this->speed<0)
		return -1;
	return 1;
}
short Fleet::size(){
	return this->ship.size();
}
short Fleet::getShips(short id){
	short number=0;
	for(unsigned i=this->ship.size();i--;)
		if(ship[i]==id)
			number++;
	return number;
}
std::string Fleet::getShipsString(short id){
	std::string string="";
	for(unsigned i=this->ship.size();i--;)
		if(ship[i]==id)
			string+=Format(this->marines[i])+"/"+Format(this->integrity[i])+"%  ";
	return string;
}
short Fleet::Ship(short i){
	return this->ship[i];
}
short Fleet::Integrity(short i){
	return this->integrity[i];
}
short Fleet::Marines(short i){
	return this->marines[i];
}
short Fleet::Range(){
	return 90+this->ship.size()*5;
}
float Fleet::Upkeep(){
	float upkeep=0;
	for(unsigned i=this->ship.size();i--;){
		upkeep+=naval[this->ship[i]].Upkeep();
	}
	return upkeep;
}
float Fleet::Speed(){
	return this->speed;
}
float Fleet::SpeedOnFrame(){
	return this->speed*0.032;
}
float Fleet::Power(){
	float power=0;
	for(unsigned i=this->ship.size();i--;)
		power+=::naval[this->ship[i]].Power();
	return (power*this->formation*this->integrity.size()*this->provision/100);
}
float Fleet::Randament(){
	return 0.3+this->provision*0.007;
}
//Rotation
void Fleet::rotate(float angle){
	this->body->rotate(angle);
	this->sails->rotate(angle);
}
void Fleet::setRotation(float angle){
	this->body->setRotation(angle);
	this->sails->setRotation(angle);
}
float Fleet::getRotation(){
	return this->body->getRotation();
}
float Fleet::getRotationRad(){
	return this->body->getRotation()*0.017453293;
}
//Points
void Fleet::setPosition(sf::Vector2f point){
	this->body->setPosition(point);
	this->sails->setPosition(point);
}
float Fleet::Dist(sf::Vector2f point){
	return ::Dist(this->getPosition(),point);
}
bool Fleet::contains(sf::Vector2f point){
	return (this->Dist(point)<=4225);
}
bool Fleet::isInRange(sf::Vector2f point){
	return (this->Range()*Range()>this->Dist(point));
}
sf::Vector2f Fleet::Front(){
	sf::Vector2f point;
	point.x=this->getPosition().x+fleetBody.getSize().x/2*cos(this->getRotationRad());
	point.y=this->getPosition().y+fleetBody.getSize().x/2*sin(this->getRotationRad());
	return point;
}
sf::Vector2f Fleet::getPosition(){
	return this->body->getPosition();
}
sf::Vector2f Fleet::getRangePosition(){
	return sf::Vector2f(this->body->getPosition().x-this->Range(),this->body->getPosition().y-this->Range());
}
sf::Vector2f Fleet::getTarget(){
	if(this->route.size())
		return this->route[this->route.size()-1].getPosition();
	return this->body->getPosition();
}
std::vector<Node> Fleet::getRoute(){
	return this->route;
}
//Mouse
bool Fleet::mouseOver(){
	if(this->contains(gui.mousePosition())){
		about.show(
			::player[this->player].Name()+"'s fleet"+getDiplomaticStatus(this->player)+" - Provision "+Format((int)this->provision)+"%",
			FormationName(this->formation)+"\n"+Format(this->size())+" ships  "+Format(this->Upkeep())+" upkeep"
		);
		this->setColor(sf::Color(255,95,118));
		return 1;
	}
	return 0;
}
bool Fleet::left(){
	if(this->mouseOver()&&gui.canLeft(200)){
		gui.clickRestart();
		this->setColor(sf::Color(255,255,255));
		return 1;
	}
	return 0;
}
bool Fleet::right(){
	if(this->mouseOver()&&gui.canRight(200)){
		gui.clickRestart();
		return 1;
	}
	return 0;
}
Fleet::~Fleet(){
	
}
//Global variables
std::vector<Fleet> fleet;
sf::Texture fleetBody;
short nFormation;
//Formations
std::string FormationName(short formation){
	std::ifstream in("data/game/formations/"+std::to_string(formation)+".txt");
	if(in.is_open()){
		std::string text;
		std::getline(in,text);
		in.close();
		return text;
	}
	return "";
}
std::string FormationText(short formation){
	std::ifstream in("data/game/formations/"+std::to_string(formation)+".txt");
	if(in.is_open()){
		std::string text;
		std::getline(in,text);
		std::getline(in,text);
		in.close();
		return text;
	}
	return "";
}