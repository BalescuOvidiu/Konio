#include "ship.h"
//Constructor
Ship::Ship(short fleet,short id,short faction,short integrity,short x,short y,float angle){
	//Data
	this->fleet=fleet;
	this->id=id;
	this->integrity=integrity;
	//Physic
	this->speed=0;
	//Sprites
	this->ram=new sf::Sprite(naval[this->id].Ram());
	this->rows=new sf::Sprite(naval[this->id].Rows());
	this->body=new sf::Sprite(naval[this->id].Body());
	this->sails=new sf::Sprite(::sails);
	this->sails->setTextureRect(sf::IntRect(13*faction,0,12,100));
	if(naval[this->id].Rowers()>=120)
		this->sails->setScale(1.,1.2);
	//Origin	
	this->body->setOrigin(naval[this->id].Body().getSize().x/2,naval[this->id].Body().getSize().y/2);
	this->ram->setOrigin(naval[this->id].Ram().getSize().x/2,naval[this->id].Ram().getSize().y/2);
	this->rows->setOrigin(naval[this->id].Rows().getSize().x/24,naval[this->id].Rows().getSize().y/2);
	this->sails->setOrigin(0,::sails.getSize().y/2);
	//Orientation
	this->setPosition(x,y);
	this->setRotation(angle);
	this->Rows(0);
}
//Render
void Ship::RenderBody(sf::RenderWindow *window){
	window->draw(*this->body);
}
void Ship::RenderRam(sf::RenderWindow *window){
	window->draw(*this->ram);
}
void Ship::RenderRows(sf::RenderWindow *window){
	window->draw(*this->rows);
}
void Ship::RenderSails(sf::RenderWindow *window){
	window->draw(*this->sails);
}
//Basic
void Ship::show(){
	if(this->integrity)
		detail.show(naval[this->id].Name(),
			"Integrity "+gui.Format(this->integrity)+"%\nSpeed "+gui.Format(fabs(this->speed))+" km/h\nMax speed "+gui.Format(naval[this->id].Speed())+" km/h\n"+gui.Format(naval[this->id].Rowers())+" rowers");
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
float Ship::getRotationRad(){
	return this->body->getRotation()*0.017453293;
}
//Points
void Ship::setPosition(float x,float y){
	this->body->setPosition(x,y);
	this->ram->setPosition(x,y);
	this->rows->setPosition(x,y);
	this->sails->setPosition(x,y);
}
float Ship::dist(sf::Vector2f point){
	return ::dist(this->Front(),point);
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
	point.x=this->Origin().x+(this->width()-8)/2*cos(this->getRotationRad());
	point.y=this->Origin().y+(this->width()-8)/2*sin(this->getRotationRad());
	return point;
}
sf::Vector2f Ship::Front(){
	sf::Vector2f point;
	point.x=this->Origin().x+(this->width())/2*cos(this->getRotationRad());
	point.y=this->Origin().y+(this->width())/2*sin(this->getRotationRad());
	return point;
}
sf::Vector2f Ship::FrontLeft(){
	sf::Vector2f point;
	point.x=this->Left().x+(this->width())/3*cos(this->getRotationRad());
	point.y=this->Left().y+(this->width())/3*sin(this->getRotationRad());
	return point;
}
sf::Vector2f Ship::FrontRight(){
	sf::Vector2f point;
	point.x=this->Right().x+(this->width())/3*cos(this->getRotationRad());
	point.y=this->Right().y+(this->width())/3*sin(this->getRotationRad());
	return point;
}
//Back points
sf::Vector2f Ship::Back(){
	sf::Vector2f point;
	point.x=this->Origin().x-(this->width())/2*cos(this->getRotationRad());
	point.y=this->Origin().y-(this->width())/2*sin(this->getRotationRad());
	return point;
}
sf::Vector2f Ship::BackLeft(){
	sf::Vector2f point;
	point.x=this->Left().x-(this->width())/2.2*cos(this->getRotationRad());
	point.y=this->Left().y-(this->width())/2.2*sin(this->getRotationRad());
	return point;
}
sf::Vector2f Ship::BackRight(){
	sf::Vector2f point;
	point.x=this->Right().x-(this->width())/2.2*cos(this->getRotationRad());
	point.y=this->Right().y-(this->width())/2.2*sin(this->getRotationRad());
	return point;
}
//Side points
sf::Vector2f Ship::Left(){
	sf::Vector2f point;
	point.x=this->Origin().x+(this->height())/2*sin(this->getRotationRad());
	point.y=this->Origin().y-(this->height())/2*cos(this->getRotationRad());
	return point;
}
sf::Vector2f Ship::Right(){
	sf::Vector2f point;
	point.x=this->Origin().x-(this->height())/2*sin(this->getRotationRad());
	point.y=this->Origin().y+(this->height())/2*cos(this->getRotationRad());
	return point;
}
//Rows points
sf::Vector2f Ship::rowsFrontLeft(){
	sf::Vector2f point;
	point.x=this->Front().x+(this->widthRows()/2)*sin(this->getRotationRad());
	point.y=this->Front().y-(this->widthRows()/2)*cos(this->getRotationRad());
	return point;
}
sf::Vector2f Ship::rowsFrontRight(){
	sf::Vector2f point;
	point.x=this->Front().x-(this->widthRows()/2)*sin(this->getRotationRad());
	point.y=this->Front().y+(this->widthRows()/2)*cos(this->getRotationRad());
	return point;
}
sf::Vector2f Ship::rowsBackLeft(){
	sf::Vector2f point;
	point.x=this->Back().x+(this->widthRows()/2)*sin(this->getRotationRad());
	point.y=this->Back().y-(this->widthRows()/2)*cos(this->getRotationRad());
	return point;
}
sf::Vector2f Ship::rowsBackRight(){
	sf::Vector2f point;
	point.x=this->Back().x-(this->widthRows()/2)*sin(this->getRotationRad());
	point.y=this->Back().y+(this->widthRows()/2)*cos(this->getRotationRad());
	return point;
}
sf::Vector2f Ship::rowsLeft(){
	sf::Vector2f point;
	point.x=this->Origin().x+(this->widthRows())/2*sin(this->getRotationRad());
	point.y=this->Origin().y-(this->widthRows())/2*cos(this->getRotationRad());
	return point;
}
sf::Vector2f Ship::rowsRight(){
	sf::Vector2f point;
	point.x=this->Origin().x-(this->widthRows())/2*sin(this->getRotationRad());
	point.y=this->Origin().y+(this->widthRows())/2*cos(this->getRotationRad());
	return point;
}
//Mouse
bool Ship::mouseOver(){
	if(this->contains(gui.mousePosition())){
		if(this->integrity)
			about.show(
				naval[this->id].Name()+getDiplomaticStatus(::fleet[this->fleet].Player())+" "+gui.Format((int)this->integrity)+"%",
				"Max speed "+gui.Format(naval[this->id].Speed())+" km/h\n"+gui.Format(naval[this->id].Rowers())+" rowers"
			);
		return 1;
	}
	return 0;
}
bool Ship::left(){
	if(this->mouseOver()&&sf::Mouse::isButtonPressed(sf::Mouse::Left)){
		this->show();
		return 1;
	}
	return 0;
}
bool Ship::right(){
	return this->mouseOver()&&sf::Mouse::isButtonPressed(sf::Mouse::Right);
}
//Get data
bool Ship::Stopped(){
	return !this->speed;
}
bool Ship::Float(){
	return (this->integrity>50);
}
float Ship::Integrity(){
	return this->integrity;
}
float Ship::SpeedMax(){
	return ((naval[this->id].Speed()*4/5+naval[this->id].Speed()/5*clock/11+1)*this->integrity/100);
}
float Ship::SpeedOnFrame(){
	return this->speed*0.032;
}
float Ship::Speed(){
	return this->speed;
}
float Ship::SpeedRatio(){
	return fabs(this->speed/naval[this->id].Speed());
}
float Ship::Power(){
	return fabs(this->speed)*naval[this->id].Rowers();
}
short Ship::Direction(){
	if(this->speed<0)
		return -1;
	return 1;
}
short Ship::Fleet(){
	return this->fleet;
}
//Size
short Ship::width(){
	return naval[this->id].width();
}
short Ship::widthRows(){
	return naval[this->id].widthRows();
}
short Ship::height(){
	return naval[this->id].height();
}
sf::Vector2f Ship::getSize(){
	return sf::Vector2f(this->width(),this->height());
}
//Move
bool Ship::move(sf::Vector2f target){
	int direction=1,way=1;
	//Get direction
	if(::dist(this->Front(),target)>200&&::dist(this->Back(),target)<200)
		direction=-1;
	//If direction is change
	if(direction*this->speed<0){
		this->speed=0;
		Rows(0);
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
				this->rotate(this->speed/60*way);
		}else if(angleShip>angle){
			if(angle>angleShip-way*this->speed/60)
				this->setRotation(angle);
			else
				this->rotate(-this->speed/60*way);
		}
		//Modify speed
		if((int)(angleShip-angle)){
			if(fabs(this->speed)>fabs(this->SpeedMax()*0.9))
				this->speed=fabs(this->SpeedMax()*0.9)*direction;
			else
				this->speed+=0.015*direction*(clock+1)/6;
		}else{
			if(fabs(this->speed)>fabs(this->SpeedMax()))
				this->speed=fabs(this->SpeedMax())*direction;
			else
				this->speed+=0.025*direction*(clock+1)/6;
		}
		if(this->speed*direction>naval[this->id].Speed())
			this->speed=direction*naval[this->id].Speed();
		//Rows
		if(this->speed){
			//Forward
			if(floor(this->clock)==11)
				this->Rows(0);
			//Reverse
			if(this->clock<0)
				this->Rows(11);
			this->Rows(this->clock+0.065*direction);
		}
	//Stop
	}else{
		//Speed
		this->speed-=0.1*direction;
		if(this->speed*direction<0)
			this->speed=0;
		//Rows
		this->Rows(0);
	}
	//Move
	this->Move(
		this->SpeedOnFrame()*cos(this->getRotationRad()),
		this->SpeedOnFrame()*sin(this->getRotationRad())
	);
	return !this->speed;
}
void Ship::Speed(float speed){
	this->speed=speed;
	if(!speed)
		this->Rows(0);
}
void Ship::Rows(float clock){
	this->clock=clock;
	this->rows->setTextureRect(
	sf::IntRect(
		naval[this->id].Rows().getSize().x/12*floor(clock),
		0,
		naval[this->id].Rows().getSize().x/12,
		naval[this->id].Rows().getSize().y)
	);
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