#include "ship.h"
//Constructor
Ship::Ship(short player,short id,short faction,short x,short y,float angle){
	//Data
	this->player=player;
	this->id=id;
	//Physic
	this->speed=0;
	this->integrity=100;
	this->clock=0;
	//Sprites
	this->ram=new sf::Sprite(naval[this->id].ram);
	this->rows=new sf::Sprite(naval[this->id].rows);
	this->body=new sf::Sprite(naval[this->id].body);
	this->sails=new sf::Sprite(::sails);
	this->sails->setTextureRect(sf::IntRect(13*faction,0,12,100));
	if(naval[this->id].rowers>120)
		this->sails->setScale(1.,1.2);
	//Orientation
	this->setOrigin();
	this->setPosition(x,y);
	this->setRotation(angle);
	this->rows->setTextureRect(sf::IntRect(0,0,naval[this->id].rows.getSize().x/12,naval[this->id].rows.getSize().y));
}
//Basic
void Ship::show(){
	if(this->integrity)
		detail.show(naval[this->id].basic.name,
			"Integrity "+std::to_string((int)this->integrity)+"%\nSpeed "+std::to_string((int)this->speed)+" k/h\nMax speed "+std::to_string(naval[this->id].basic.speed)+" k/h\n"+std::to_string(naval[this->id].rowers)+" rowers");
	else
		detail.hide();
}
void Ship::setColor(sf::Color color){
	this->body->setColor(color);
	this->ram->setColor(color);
	this->sails->setColor(color);
	this->rows->setColor(color);
}
//Private
void Ship::Move(float x,float y){
	this->body->move(x,y);
	this->ram->move(x,y);
	this->sails->move(x,y);
	this->rows->move(x,y);
}
//Rotation
void Ship::rotate(float angle){
	this->setRotation(this->getRotation()+angle);
}
void Ship::rotateTo(float angle){
	this->rotate(angle);
}
void Ship::setRotation(float angle){
	//Set angle of ship
	this->body->setRotation(angle);
	this->ram->setRotation(angle);
	this->rows->setRotation(angle);
	//Set angle of sail
	if(angle>=0&&angle<=180)
		this->sails->setRotation(angle/2);
	else
		this->sails->setRotation(360-(360-angle)/2);
}
float Ship::getRotation(){
	return this->body->getRotation();
}
//Points
void Ship::setOrigin(){
	this->body->setOrigin(naval[id].body.getSize().x/2,naval[id].body.getSize().y/2);
	this->ram->setOrigin(naval[id].ram.getSize().x/2,naval[id].ram.getSize().y/2);
	this->rows->setOrigin(naval[id].rows.getSize().x/24,naval[id].rows.getSize().y/2);
	this->sails->setOrigin(0,::sails.getSize().y/2);
}
void Ship::setPosition(float x,float y){
	this->body->setPosition(x,y);
	this->ram->setPosition(x,y);
	this->rows->setPosition(x,y);
	this->sails->setPosition(x,y);
}
float Ship::getDist(sf::Vector2f point){
	return dist(this->Front(),point);
}
bool Ship::contains(sf::Vector2f point){
	if(isInTriangle(this->BackLeft(),this->BackRight(),this->Back(),point))
		return 1;
	if(isInTriangle(this->FrontLeft(),this->Front(),this->FrontRight(),point))
		return 1;
	if(isInTriangle(this->BackLeft(),this->FrontLeft(),this->BackRight(),point))
		return 1;
	if(isInTriangle(this->FrontLeft(),this->FrontRight(),this->BackLeft(),point))
		return 1;
	return 0;
}
bool Ship::rowsContains(sf::Vector2f point){
	if(isInTriangle(this->rowsBackLeft(),this->rowsFrontLeft(),this->rowsBackRight(),point))
		return 1;
	if(isInTriangle(this->rowsFrontLeft(),this->rowsFrontRight(),this->rowsBackLeft(),point))
		return 1;
	return 0;
}
sf::Vector2f Ship::Origin(){
	return this->body->getPosition();
}
//Front points
sf::Vector2f Ship::Ram(){
	sf::Vector2f point;
	point.x=this->body->getPosition().x+(naval[this->id].width-8)/2*cos(this->body->getRotation()*0.017453293);
	point.y=this->body->getPosition().y+(naval[this->id].width-8)/2*sin(this->body->getRotation()*0.017453293);
	return point;
}
sf::Vector2f Ship::Front(){
	sf::Vector2f point;
	point.x=this->body->getPosition().x+(naval[this->id].width)/2*cos(this->body->getRotation()*0.017453293);
	point.y=this->body->getPosition().y+(naval[this->id].width)/2*sin(this->body->getRotation()*0.017453293);
	return point;
}
sf::Vector2f Ship::FrontLeft(){
	sf::Vector2f point;
	point.x=this->Left().x+(naval[this->id].width)/3*cos(this->body->getRotation()*0.017453293);
	point.y=this->Left().y+(naval[this->id].width)/3*sin(this->body->getRotation()*0.017453293);
	return point;
}
sf::Vector2f Ship::FrontRight(){
	sf::Vector2f point;
	point.x=this->Right().x+(naval[this->id].width)/3*cos(this->body->getRotation()*0.017453293);
	point.y=this->Right().y+(naval[this->id].width)/3*sin(this->body->getRotation()*0.017453293);
	return point;
}
//Back points
sf::Vector2f Ship::Back(){
	sf::Vector2f point;
	point.x=this->body->getPosition().x-(naval[this->id].width)/2*cos(this->body->getRotation()*0.017453293);
	point.y=this->body->getPosition().y-(naval[this->id].width)/2*sin(this->body->getRotation()*0.017453293);
	return point;
}
sf::Vector2f Ship::BackLeft(){
	sf::Vector2f point;
	point.x=this->Left().x-(naval[this->id].width)/2.2*cos(this->body->getRotation()*0.017453293);
	point.y=this->Left().y-(naval[this->id].width)/2.2*sin(this->body->getRotation()*0.017453293);
	return point;
}
sf::Vector2f Ship::BackRight(){
	sf::Vector2f point;
	point.x=this->Right().x-(naval[this->id].width)/2.2*cos(this->body->getRotation()*0.017453293);
	point.y=this->Right().y-(naval[this->id].width)/2.2*sin(this->body->getRotation()*0.017453293);
	return point;
}
//Side points
sf::Vector2f Ship::Left(){
	sf::Vector2f point;
	point.x=this->body->getPosition().x+(naval[this->id].height)/2*sin(this->body->getRotation()*0.017453293);
	point.y=this->body->getPosition().y-(naval[this->id].height)/2*cos(this->body->getRotation()*0.017453293);
	return point;
}
sf::Vector2f Ship::Right(){
	sf::Vector2f point;
	point.x=this->body->getPosition().x-(naval[this->id].height)/2*sin(this->body->getRotation()*0.017453293);
	point.y=this->body->getPosition().y+(naval[this->id].height)/2*cos(this->body->getRotation()*0.017453293);
	return point;
}
//Rows points
sf::Vector2f Ship::rowsFrontLeft(){
	sf::Vector2f point;
	point.x=this->Front().x+(naval[this->id].rowsWidth/2)*sin(this->body->getRotation()*0.017453293);
	point.y=this->Front().y-(naval[this->id].rowsWidth/2)*cos(this->body->getRotation()*0.017453293);
	return point;
}
sf::Vector2f Ship::rowsFrontRight(){
	sf::Vector2f point;
	point.x=this->Front().x-(naval[this->id].rowsWidth/2)*sin(this->body->getRotation()*0.017453293);
	point.y=this->Front().y+(naval[this->id].rowsWidth/2)*cos(this->body->getRotation()*0.017453293);
	return point;
}
sf::Vector2f Ship::rowsBackLeft(){
	sf::Vector2f point;
	point.x=this->Back().x+(naval[this->id].rowsWidth/2)*sin(this->body->getRotation()*0.017453293);
	point.y=this->Back().y-(naval[this->id].rowsWidth/2)*cos(this->body->getRotation()*0.017453293);
	return point;
}
sf::Vector2f Ship::rowsBackRight(){
	sf::Vector2f point;
	point.x=this->Back().x-(naval[this->id].rowsWidth/2)*sin(this->body->getRotation()*0.017453293);
	point.y=this->Back().y+(naval[this->id].rowsWidth/2)*cos(this->body->getRotation()*0.017453293);
	return point;
}
sf::Vector2f Ship::rowsLeft(){
	sf::Vector2f point;
	point.x=this->body->getPosition().x+(naval[this->id].rowsWidth)/2*sin(this->body->getRotation()*0.017453293);
	point.y=this->body->getPosition().y-(naval[this->id].rowsWidth)/2*cos(this->body->getRotation()*0.017453293);
	return point;
}
sf::Vector2f Ship::rowsRight(){
	sf::Vector2f point;
	point.x=this->body->getPosition().x-(naval[this->id].rowsWidth)/2*sin(this->body->getRotation()*0.017453293);
	point.y=this->body->getPosition().y+(naval[this->id].rowsWidth)/2*cos(this->body->getRotation()*0.017453293);
	return point;
}
//Mouse
bool Ship::mouseOver(){
	if(this->contains(gui.mousePosition())){
		about.show(naval[this->id].basic.name+" - "+std::to_string((short)this->integrity)+"%","Max speed "+std::to_string(naval[this->id].basic.speed)+" k/h\n"+std::to_string(naval[this->id].rowers)+" rowers");
		return 1;
	}
	return 0;
}
bool Ship::mouseOver(std::string text){
	if(this->contains(gui.mousePosition())){
		about.show(naval[this->id].basic.name+" - "+text+" "+std::to_string((short)this->integrity)+"%","Max speed "+std::to_string(naval[this->id].basic.speed)+" k/h\n"+std::to_string(naval[this->id].rowers)+" rowers");
		return 1;
	}
	return 0;
}
bool Ship::left(){
	if(this->mouseOver("(YOU)")&&sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		this->show();
		return 1;
	}
	return 0;
}
bool Ship::right(){
	return this->mouseOver("(YOU)")&&sf::Mouse::isButtonPressed(sf::Mouse::Right);
}
//Get data
bool Ship::Float(){
	return (this->integrity>50);
}
float Ship::Integrity(){
	return this->integrity;
}
float Ship::Speed(){
	return this->speed;
}
float Ship::SpeedRatio(){
	return fabs(this->speed/naval[this->id].basic.speed);
}
float Ship::Power(){
	return fabs(this->speed)*naval[this->id].rowers;
}
short Ship::width(){
	return naval[this->id].width;
}
short Ship::Player(){
	return this->player;
}
sf::Vector2f Ship::getSize(){
	return sf::Vector2f(naval[this->id].width+10,naval[this->id].rowsWidth+10);
}
//Move
bool Ship::move(sf::Vector2f target){
	int direction=1,way=1;
	//Get direction
	if(dist(this->Front(),target)>200&&dist(this->Back(),target)<200)
		direction=-1;
	//If direction is change
	if(direction*this->speed<0){
		this->speed=0;
		//Rows
		this->rows->setTextureRect(sf::IntRect(0,0,naval[this->id].rows.getSize().x/12,naval[this->id].rows.getSize().y));
		this->clock=0;
	}
	//Move
	if(!this->contains(target)){
		//Get the angles the angle
		float angleShip=this->body->getRotation();
		float angle=getAngle(this->Origin(),target);
		//Get way
		if(fabs(angleShip-angle)>180)
			way*=-1;
		//Change angle
		if(angleShip<angle){
			if(angle<angleShip+way*this->speed/60)
				this->setRotation(angle);
			else
				this->rotateTo(this->speed/60*way);
		}
		else if(angleShip>angle){
			if(angle>angleShip-way*this->speed/60)
				this->setRotation(angle);
			else
				this->rotateTo(-this->speed/60*way);
		}
		//Modify speed
		if((int)(angleShip-angle)){
			if(fabs(this->speed)>fabs((naval[this->id].basic.speed*4/5+naval[this->id].basic.speed/5*clock/12)*this->integrity/100))
				this->speed=fabs((naval[this->id].basic.speed*4/5+naval[this->id].basic.speed/5*clock/12)*this->integrity/100)*direction;
			else
				this->speed+=0.015*direction*(clock+1)/6;			
		}else{
			if(fabs(this->speed)>fabs((naval[this->id].basic.speed*4/5+naval[this->id].basic.speed/5*clock/11+1)*this->integrity/100))
				this->speed=fabs((naval[this->id].basic.speed*4/5+naval[this->id].basic.speed/5*clock/11+1)*this->integrity/100)*direction;
			else
				this->speed+=0.025*direction*(clock+1)/6;
		}
		if(this->speed*direction>naval[this->id].basic.speed)
			this->speed=direction*naval[this->id].basic.speed;	
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
				this->rows->setTextureRect(sf::IntRect(naval[this->id].rows.getSize().x/12*floor(clock),0,naval[this->id].rows.getSize().x/12,naval[this->id].rows.getSize().y));
		}
	//Stop
	}else{
		//Speed
		this->speed-=0.1*direction;
		if(this->speed<0&&direction>0)
			this->speed=0;
		else if(this->speed>0&&direction<0)
			this->speed=0;
		//Rows
		this->rows->setTextureRect(sf::IntRect(0,0,naval[this->id].rows.getSize().x/12,naval[this->id].rows.getSize().y));
		this->clock=0;
	}
	//Move
	this->Move(this->speed*0.0384151667*cos(this->getRotation()*0.017453293),this->speed*0.0384151667*sin(this->getRotation()*0.017453293));
	return !this->speed;
}
void Ship::moveOrtogonal(float dist){
	this->Move(dist*this->speed/15*sin(this->getRotation()*0.017453293),dist*this->speed/15*cos(this->getRotation()*0.017453293));
}

void Ship::Speed(float speed){
	this->speed=speed;
	if(!speed)
		Rows(0);
}
void Ship::Rows(float clock){
	this->clock=clock;
	this->rows->setTextureRect(sf::IntRect(naval[this->id].rows.getSize().x/12*floor(clock),0,naval[this->id].rows.getSize().x/12,naval[this->id].rows.getSize().y));	
}
//Fight
void Ship::takeDamage(short damage){
	this->speed/=2;
	if(this->integrity>damage)
		this->integrity-=damage;
	else
		integrity=0;
}
bool Ship::sink(){
	this->integrity-=0.08;
	if(this->integrity<=0)
		return 1;
	return 0;
}
Ship::~Ship(){

}