#include "fleet.h"

Fleet::Fleet(sf::Vector2f pos,float angle,short player,short formation,float provision){
	//Main properties
	this->player=player;
	this->provision=provision;
	this->formation=formation;
	this->speed=0;
	this->clock=0;
	//Rows
	this->rows=new sf::Sprite(naval[5].Rows());
	this->rows->setTextureRect(sf::IntRect(0,0,naval[5].Rows().getSize().x/12,naval[5].Rows().getSize().y));
	//Body
	this->body=new sf::Sprite(naval[5].Body());
	//Sails
	this->sails=new sf::Sprite(::sails);
	this->sails->setTextureRect(sf::IntRect(13*(::player[player].Faction()),0,12,100));
	//Origin	
	this->body->setOrigin(naval[5].Body().getSize().x/2,naval[5].Body().getSize().y/2);
	this->rows->setOrigin(naval[5].Rows().getSize().x/24,naval[5].Rows().getSize().y/2);
	this->sails->setOrigin(0,::sails.getSize().y/2);
	//Orientation
	this->setPosition(pos);
	this->setRotation(angle);
	//Scale
	this->sails->setScale(0.4,0.5);
}
//Update and rendering
void Fleet::Render(sf::RenderWindow *window){
	window->draw(*this->rows);
	window->draw(*this->body);
	window->draw(*this->sails);
}
void Fleet::Update(){
	if(this->route.size()){
		//Get the angles
		float angleShip=this->body->getRotation();
		float angle=getAngle(this->getPosition(),this->route[0].getPosition());
		int direction=1,way=1;
		//Get direction
		if(140<fabs(angleShip-angle)&&fabs(angleShip-angle)<230)
			direction=-1;
		//If direction is change
		if(direction*this->speed<0){
			this->speed=0;
			//Rows
			this->rows->setTextureRect(sf::IntRect(0,0,naval[5].Rows().getSize().x/12,naval[5].Rows().getSize().y));
			this->clock=0;
		}
		if(!this->route[0].contains(this->getPosition())){
			//Get way
			if(fabs(angleShip-angle)>180)
				way*=-1;
			//Change angle
			if(angleShip<angle){
				if(angle<angleShip+way*this->speed/30)
					this->setRotation(angle);
				else
					this->rotateTo(this->speed/30*way);
			}
			else if(angleShip>angle){
				if(angle>angleShip-way*this->speed/30)
					this->setRotation(angle);
				else
					this->rotateTo(-this->speed/30*way);
			}
			//Modify speed
			if((int)(angleShip-angle)){
				if(fabs(this->speed)>fabs((naval[5].Speed()*4/5+naval[5].Speed()/5*clock/12)*this->provision/100))
					this->speed=fabs((naval[5].Speed()*4/5+naval[5].Speed()/5*clock/12)*this->provision/100)*direction;
				else
					this->speed+=0.015*direction*(clock+1)/6;			
			}else{
				if(fabs(this->speed)>fabs((naval[5].Speed()*4/5+naval[5].Speed()/5*clock/11+1)*this->provision/100))
					this->speed=fabs((naval[5].Speed()*4/5+naval[5].Speed()/5*clock/11+1)*this->provision/100)*direction;
				else
					this->speed+=0.025*direction*(clock+1)/6;
			}
			if(this->speed*direction>naval[5].Speed())
				this->speed=direction*naval[5].Speed();	
			//Rows
			if(this->speed){
				this->clock+=0.075*direction;
				//Forward
				if(this->clock>=12)
					this->clock=0;
				//Reverse
				if(this->clock<0)
					this->clock=11.9;
				//Stop
				if(!this->speed)
					this->clock=0;
				if(floor(this->clock-0.075*direction)!=floor(this->clock))
					this->rows->setTextureRect(sf::IntRect(naval[5].Rows().getSize().x/12*floor(clock),0,naval[5].Rows().getSize().x/12,naval[5].Rows().getSize().y));
			}
		//Stop
		}else{
			this->route.erase(this->route.begin());
			if(!this->route.size()){
				//Speed
				this->speed-=0.1*direction;
				if(this->speed<0&&direction>0)
					this->speed=0;
				else if(this->speed>0&&direction<0)
					this->speed=0;
				//Rows
				this->rows->setTextureRect(sf::IntRect(0,0,naval[5].Rows().getSize().x/12,naval[5].Rows().getSize().y));
				this->clock=0;
			}
		}
		//Move
		this->Move(this->speed*0.0384151667*cos(this->getRotation()*0.017453293),this->speed*0.0384151667*sin(this->getRotation()*0.017453293));
	}else{

	}
}
void Fleet::addShip(short ship,short integrity){
	this->ship.push_back(ship);
	this->integrity.push_back(integrity);
}
void Fleet::Lost(){
	this->integrity.clear();
	this->ship.clear();
}
//Route
void Fleet::addNodeRoute(Node node){
	this->route.push_back(node);
}
void Fleet::resetRoute(){
	this->route.clear();
}
void Fleet::Move(float x,float y){
	this->body->move(x,y);
	this->sails->move(x,y);
	this->rows->move(x,y);
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
short Fleet::size(){
	return this->ship.size();
}
short Fleet::Ship(short i){
	return this->ship[i];
}
short Fleet::Integrity(short i){
	return this->integrity[i];
}
//Rotation
void Fleet::rotate(float angle){
	this->setRotation(this->getRotation()+angle);
}
void Fleet::rotateTo(float angle){
	this->rotate(angle);
}
void Fleet::setRotation(float angle){
	//Set angle of fleet
	this->body->setRotation(angle);
	this->rows->setRotation(angle);
	//Set angle of sail
	if(angle>=0&&angle<=180)
		this->sails->setRotation(angle/2);
	else
		this->sails->setRotation(360-(360-angle)/2);
}
float Fleet::getRotation(){
	return this->body->getRotation();
}
//Points
void Fleet::setPosition(sf::Vector2f point){
	this->body->setPosition(point);
	this->rows->setPosition(point);
	this->sails->setPosition(point);
}
float Fleet::dist(sf::Vector2f point){
	return ::dist(this->getPosition(),point);
}
bool Fleet::contains(sf::Vector2f point){
	return (this->dist(point)<=65);
}
sf::Vector2f Fleet::getPosition(){
	return this->body->getPosition();
}
//Mouse
bool Fleet::mouseOver(){
	if(this->contains(gui.mousePosition())){
		about.show(
			::player[this->player].Name()+"'s fleet"+getDiplomaticStatus(this->player),
			std::to_string(this->size())+" ships"
		);
		return 1;
	}
	return 0;
}
bool Fleet::left(){
	return (this->mouseOver()&&sf::Mouse::isButtonPressed(sf::Mouse::Left));
}
Fleet::~Fleet(){
	
}
//Global variable
std::vector<Fleet> fleet;
//Global functions
float distFleet(short i,short j){
	return ::fleet[i].dist(fleet[j].getPosition());
}
short getShips(short player){
	short ships=0;
	for(short i=0;i<(short)::fleet.size();i++)
		if(::fleet[i].Player()==player)
			ships+=::fleet[i].size();
	return ships;
}
short getNearestFleet(sf::Vector2f point){
	short nearest=0;
	float Dist=dist(point,fleet[5].getPosition());
	for(short i=1;i<(short)fleet.size();i++)
		if(Dist>dist(point,fleet[i].getPosition())){
			Dist=dist(point,fleet[i].getPosition());
			nearest=i;
		}
	return nearest;
}
bool isYourFleet(short i){
	return ::fleet[i].Player()==human;
}
bool isEnemyFleet(short i,short j){
	return ::player[::fleet[i].Player()].Team()!=::player[::fleet[j].Player()].Team();
}
bool isAlliedFleet(short i,short j){
	return ::player[::fleet[i].Player()].Team()==::player[::fleet[j].Player()].Team();
}