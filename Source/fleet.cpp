#include "fleet.h"

Fleet::Fleet(sf::Vector2f pos,float angle,short player,short faction,short formation,float provision){
	//Main properties
	this->player=player;
	this->provision=provision;
	this->formation=formation;
	this->speed=0;
	//Rows
	this->rows=new sf::Sprite(naval[2].rows);
	this->rows->setTextureRect(sf::IntRect(0,0,naval[2].rows.getSize().x/12,naval[2].rows.getSize().y));
	//Body
	this->body=new sf::Sprite(naval[2].body);
	//Sails
	this->sails=new sf::Sprite(::sails);
	this->sails->setTextureRect(sf::IntRect(13*faction,0,12,100));
	//Orientation
	this->setOrigin();
	this->setPosition(pos);
	this->setRotation(angle);
	//Scale
	this->rows->setScale(0.4,0.5);
	this->body->setScale(0.4,0.4);
	this->sails->setScale(0.4,0.5);
}
//Update and rendering
void Fleet::Render(sf::RenderWindow *window){
	window->draw(*this->rows);
	window->draw(*this->body);
	window->draw(*this->sails);
}
void Fleet::Update(){

}
void Fleet::addShip(short ship,short integrity){
	this->ship.push_back(ship);
	this->integrity.push_back(integrity);
}
void Fleet::addNodeRoute(sf::Vector2f point){
	this->route.push_back(sf::Vector2i(point.x,point.y));
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
//Points
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
void Fleet::setOrigin(){
	this->body->setOrigin(naval[2].body.getSize().x/2,naval[2].body.getSize().y/2);
	this->rows->setOrigin(naval[2].rows.getSize().x/24,naval[2].rows.getSize().y/2);
	this->sails->setOrigin(0,::sails.getSize().y/2);
}
void Fleet::setPosition(sf::Vector2f point){
	this->body->setPosition(point);
	this->rows->setPosition(point);
	this->sails->setPosition(point);
}
float Fleet::getDist(sf::Vector2f point){
	return dist(this->Front(),point);
}

sf::Vector2f Fleet::Origin(){
	return this->body->getPosition();
}
bool Fleet::contains(sf::Vector2f point){
	if(isInTriangle(this->BackLeft(),this->FrontLeft(),this->BackRight(),point))
		return 1;
	if(isInTriangle(this->FrontLeft(),this->FrontRight(),this->BackLeft(),point))
		return 1;
	return 0;
}
//Front points
sf::Vector2f Fleet::Front(){
	sf::Vector2f point;
	point.x=this->body->getPosition().x+(naval[2].width)/5*cos(this->body->getRotation()*0.017453293);
	point.y=this->body->getPosition().y+(naval[2].width)/5*sin(this->body->getRotation()*0.017453293);
	return point;
}
sf::Vector2f Fleet::FrontLeft(){
	sf::Vector2f point;
	point.x=this->Left().x+(naval[2].width)/5*cos(this->body->getRotation()*0.017453293);
	point.y=this->Left().y+(naval[2].width)/5*sin(this->body->getRotation()*0.017453293);
	return point;
}
sf::Vector2f Fleet::FrontRight(){
	sf::Vector2f point;
	point.x=this->Right().x+(naval[2].width)/5*cos(this->body->getRotation()*0.017453293);
	point.y=this->Right().y+(naval[2].width)/5*sin(this->body->getRotation()*0.017453293);
	return point;
}
//Back points
sf::Vector2f Fleet::Back(){
	sf::Vector2f point;
	point.x=this->body->getPosition().x-(naval[2].width)/5*cos(this->body->getRotation()*0.017453293);
	point.y=this->body->getPosition().y-(naval[2].width)/5*sin(this->body->getRotation()*0.017453293);
	return point;
}
sf::Vector2f Fleet::BackLeft(){
	sf::Vector2f point;
	point.x=this->Left().x-(naval[2].width)/5*cos(this->body->getRotation()*0.017453293);
	point.y=this->Left().y-(naval[2].width)/5*sin(this->body->getRotation()*0.017453293);
	return point;
}
sf::Vector2f Fleet::BackRight(){
	sf::Vector2f point;
	point.x=this->Right().x-(naval[2].width)/5*cos(this->body->getRotation()*0.017453293);
	point.y=this->Right().y-(naval[2].width)/5*sin(this->body->getRotation()*0.017453293);
	return point;
}
//Side points
sf::Vector2f Fleet::Left(){
	sf::Vector2f point;
	point.x=this->body->getPosition().x+(naval[2].height)/5*sin(this->body->getRotation()*0.017453293);
	point.y=this->body->getPosition().y-(naval[2].height)/5*cos(this->body->getRotation()*0.017453293);
	return point;
}
sf::Vector2f Fleet::Right(){
	sf::Vector2f point;
	point.x=this->body->getPosition().x-(naval[2].height)/5*sin(this->body->getRotation()*0.017453293);
	point.y=this->body->getPosition().y+(naval[2].height)/5*cos(this->body->getRotation()*0.017453293);
	return point;
}
//Mouse
bool Fleet::mouseOver(){
	if(this->contains(gui.mousePosition())){
		//about.show(naval[this->id].basic.name+" - "+std::to_string((short)this->integrity)+"%","Max speed "+std::to_string(naval[this->id].basic.speed)+" k/h\n"+std::to_string(naval[this->id].rowers)+" rowers");
		return 1;
	}
	return 0;
}
bool Fleet::left(){
	if(this->mouseOver()&&sf::Mouse::isButtonPressed(sf::Mouse::Left))
		return 1;
	return 0;
}
Fleet::~Fleet(){
	
}
//Global variable
std::vector<Fleet> fleet;
//Global functions
short getShips(short player){
	short ships=0;
	for(short i=0;i<(short)::fleet.size();i++)
		if(::fleet[i].Player()==player)
			ships+=::fleet[i].size();
	return ships;
}