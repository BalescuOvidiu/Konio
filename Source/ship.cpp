#include "ship.h"
//Constructor
Ship::Ship(short fleet,short rank,short id,short faction,short x,short y,float angle){
	//Data
	this->fleet=fleet;
	this->rank=rank;
	this->id=id;
	this->integrity=::fleet[fleet].Integrity(rank);
	this->marines=::fleet[fleet].Marines(rank);
	this->floating=100;
	//Physic
	this->speed=0;
	this->rotationSpeed=0;
	//Sprites
	this->ram=new sf::Sprite(naval[this->id].Ram());
	this->rows=new sf::Sprite(naval[this->id].Rows());
	this->body=new sf::Sprite(naval[this->id].Body());
	//Sail
	this->sails=new sf::Sprite(::sails);
	this->sails->setTextureRect(sf::IntRect(14*faction,0,14,140));
	this->strings.resize(10);
	for(unsigned i=10;i--;)
		this->strings[i].color=sf::Color(176,164,157,90);
	//Marine
	for(short i=0;i<this->marines;i++)
		marine.push_back(Marine(0,0,angle));
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
	//Marines
	for(unsigned i=this->marine.size();i--;)
		this->marine[i].Render(window);
	//Sails
	window->draw(*this->sails);
	//Strings
	if(this->FloatBody())
		window->draw(&this->strings[0],10,sf::Lines);
}
//Basic
void Ship::setColor(sf::Color color){
	this->body->setColor(color);
	this->ram->setColor(color);
	this->sails->setColor(color);
	this->rows->setColor(color);
}
void Ship::setString(){
	//Middle
	this->strings[0].position=this->StringsFront();
	this->strings[1].position=this->StringsBack();
	//Left
	this->strings[2].position=this->StringsLeft();
	this->strings[3].position=this->SailsLeft();
	this->strings[4].position=this->StringsBack();
	this->strings[5].position=this->SailsLeft();
	//Right
	this->strings[6].position=this->StringsRight();
	this->strings[7].position=this->SailsRight();
	this->strings[8].position=this->StringsBack();
	this->strings[9].position=this->SailsRight();
}
void Ship::rankDown(){
	this->rank--;
}
//Rotation
void Ship::rotate(float angle){
	//Rotate ship
	this->body->rotate(angle);
	this->ram->rotate(angle);
	this->rows->rotate(angle);
	this->sails->rotate(angle);
	this->setString();
	//Marines
	this->setPositionMarines();
}
void Ship::setRotation(float angle){
	//Set angle of ship
	this->body->setRotation(angle);
	this->ram->setRotation(angle);
	this->rows->setRotation(angle);
	this->sails->setRotation(angle);
	this->setString();
	//Marines
	this->setPositionMarines();
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
	this->setPositionMarines();
}
void Ship::setPositionMarines(){
	sf::Vector2f pos=this->StringsFront();
	float SIN=sin(this->getRotationRad());
	float COS=cos(this->getRotationRad());
	for(unsigned i=marine.size();i--;){
		if(i%2){
			this->marine[i].setPosition(
				pos.x-(i<<3)*COS-8*SIN,
				pos.y-(i<<3)*SIN+8*COS
			);
		}else{
			this->marine[i].setPosition(
				pos.x-((i<<3)+8)*COS+8*SIN,
				pos.y-((i<<3)+8)*SIN-8*COS
			);
		}
		this->marine[i].rotate(this->rotationSpeed);
	}
}
float Ship::Dist(sf::Vector2f point){
	return ::Dist(this->Origin(),point);
}
float Ship::Dist(Ship ship){
	return ::Dist(this->Origin(),ship.Origin());
}
float Ship::DistFront(sf::Vector2f point){
	return ::Dist(this->Front(),point);
}
float Ship::DistFront(Ship ship){
	return ::Dist(this->Front(),ship.Origin());	
}
float Ship::DistBack(sf::Vector2f point){
	return ::Dist(this->Back(),point);
}
float Ship::DistBack(Ship ship){
	return ::Dist(this->Back(),ship.Origin());	
}
//Collision
bool Ship::contains(sf::Vector2f point){
	if(::Dist(this->body->getPosition(),point)>square(this->width()/2))
		return 0;
	return (fabs(det(this->A(),this->B(),point))/(this->width()-this->height()-5))<=this->height()/2;
}
sf::Vector2f Ship::Origin(){
	return this->body->getPosition();
}
sf::Vector2f Ship::A(){
	sf::Vector2f point;
	point.x=this->Origin().x+(this->width()-8-this->height())/2*cos(this->getRotationRad());
	point.y=this->Origin().y+(this->width()-8-this->height())/2*sin(this->getRotationRad());
	return point;
}
sf::Vector2f Ship::B(){
	sf::Vector2f point;
	point.x=this->Origin().x-(this->width()-2-this->height())/2*cos(this->getRotationRad());
	point.y=this->Origin().y-(this->width()-2-this->height())/2*sin(this->getRotationRad());
	return point;
}
//Front points
sf::Vector2f Ship::Ram(){
	sf::Vector2f point;
	point.x=this->Origin().x+(this->width()-16)/2*cos(this->getRotationRad());
	point.y=this->Origin().y+(this->width()-16)/2*sin(this->getRotationRad());
	return point;
}
sf::Vector2f Ship::Front(){
	sf::Vector2f point;
	point.x=this->Origin().x+(this->width()-18)/2*cos(this->getRotationRad());
	point.y=this->Origin().y+(this->width()-18)/2*sin(this->getRotationRad());
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
//Sails points
sf::Vector2f Ship::SailsLeft(){
	sf::Vector2f point;
	point.x=this->Origin().x+70*sin(this->sails->getRotation()*0.017453293);
	point.y=this->Origin().y-70*cos(this->sails->getRotation()*0.017453293);
	return point;
}
sf::Vector2f Ship::SailsRight(){
	sf::Vector2f point;
	point.x=this->Origin().x-70*sin(this->sails->getRotation()*0.017453293);
	point.y=this->Origin().y+70*cos(this->sails->getRotation()*0.017453293);
	return point;
}
sf::Vector2f Ship::StringsFront(){
	sf::Vector2f point;
	point.x=this->Origin().x+(this->width())/3*cos(this->getRotationRad());
	point.y=this->Origin().y+(this->width())/3*sin(this->getRotationRad());
	return point;
}
sf::Vector2f Ship::StringsBack(){
	sf::Vector2f point;
	point.x=this->Origin().x-(this->width())/3*cos(this->getRotationRad());
	point.y=this->Origin().y-(this->width())/3*sin(this->getRotationRad());
	return point;
}
sf::Vector2f Ship::StringsLeft(){
	sf::Vector2f point;
	point.x=this->Left().x-(this->width())/3*cos(this->getRotationRad());
	point.y=this->Left().y-(this->width())/3*sin(this->getRotationRad());
	return point;
}
sf::Vector2f Ship::StringsRight(){
	sf::Vector2f point;
	point.x=this->Right().x-(this->width())/3*cos(this->getRotationRad());
	point.y=this->Right().y-(this->width())/3*sin(this->getRotationRad());
	return point;
}
//Mouse
bool Ship::mouseOver(){
	if(this->contains(gui.mouseCoordinates())){
		if(this->integrity)
			about.show(
				::player[this->Player()].Name()+"'s "+naval[this->id].Name()+getDiplomaticStatus(::fleet[this->fleet].Player())+" "+Format(this->integrity)+"%",
				Format(fabs(this->speed))+"/"+Format(naval[this->id].Speed())+" km/h\n"+Format(naval[this->id].Rowers())+" rowers    "+Format(this->marines)+" marines"
			);
		return 1;
	}
	return 0;
}
bool Ship::left(){
	return this->mouseOver()&&sf::Mouse::isButtonPressed(sf::Mouse::Left);
}
bool Ship::right(){
	return this->mouseOver()&&sf::Mouse::isButtonPressed(sf::Mouse::Right);
}
//Main data
std::string Ship::getDetails(){
	return naval[this->id].Name()+" - "+Format(this->integrity)+"%    "+Format(fabs(this->speed))+"/"+Format(naval[this->id].Speed())+" km/h    "+Format(this->marines)+" marines";
}
bool Ship::Stopped(){
	return !this->speed;
}
//Float
bool Ship::FloatBody(){
	return this->floating>20;
}
bool Ship::FloatRam(){
	return this->floating>70;
}
bool Ship::FloatRows(){
	return this->floating>60;
}
bool Ship::FloatSails(){
	return this->floating;
}
bool Ship::Float(){
	return (this->integrity>30);
}
//Data
float Ship::Integrity(){
	return this->integrity;
}
float Ship::RotationSpeed(){
	return this->rotationSpeed;
}
float Ship::SpeedMax(){
	return (naval[this->id].Speed()*this->integrity/100);
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
float Ship::Floating(){
	return this->floating;
}
short Ship::Direction(){
	if(this->speed<0)
		return -1;
	return 1;
}
short Ship::Fleet(){
	return this->fleet;
}
short Ship::Rank(){
	return this->rank;
}
short Ship::Id(){
	return this->id;
}
short Ship::Player(){
	return ::fleet[this->fleet].Player();
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
	//Get direction
	int direction=1;
	if(this->DistFront(target)>40000&&this->DistBack(target)<40000)
		direction=-1;
	//If direction is change
	if(direction*this->speed<0){
		this->speed=0;
		Rows(0);
	}
	//Move
	if(!this->contains(target)){
		//Get angles
		float angle=getAngle(this->Origin(),target);
		float delta=this->body->getRotation()-angle;
		this->rotationSpeed=this->speed/60;
		if(fabs(delta)>180)
			this->rotationSpeed*=-1;
		//Change angle
		if(delta<0){
			if(0<delta+this->rotationSpeed)
				this->rotate(angle-this->body->getRotation());
			else
				this->rotate(this->rotationSpeed);
		}
		else if(delta>0){
			if(0>delta-this->rotationSpeed)
				this->rotate(angle-this->body->getRotation());
			else{
				this->rotationSpeed*=-1;
				this->rotate(this->rotationSpeed);
			}
		}else
			this->rotationSpeed=0;
		//Sails
		if(this->rotationSpeed){
			if(fabs(this->rotationSpeed+this->sails->getRotation()-this->body->getRotation())<20)
				this->sails->rotate(this->rotationSpeed);
		}
		//Modify speed
		if((int)delta)
			delta=0.67;
		else
			delta=1;
		this->speed+=0.025*(clock+1)/6*delta*direction;
		//Max speed
		if(this->speed*direction>this->SpeedMax()*delta)
			this->speed=direction*this->SpeedMax()*delta;
		//Rows
		if(this->speed){
			//Forward
			if(floor(this->clock)==11)
				this->Rows(0);
			//Reverse
			if(this->clock<0)
				this->Rows(11);
			//Sprite
			this->Rows(this->clock+0.065*direction);
		}
	//Stop
	}else{
		//Speed
		this->speed-=0.08*direction;
		if(this->speed*direction<0)
			this->speed=0;
		this->rotationSpeed=0;
		//Rows
		this->Rows(0);
	}
	//Move
	this->push(
		this->SpeedOnFrame()*cos(this->getRotationRad()),
		this->SpeedOnFrame()*sin(this->getRotationRad())
	);
	return !this->speed;
}
void Ship::push(float x,float y){
	this->body->move(x,y);
	this->ram->move(x,y);
	this->sails->move(x,y);
	this->rows->move(x,y);
	this->setString();
	for(unsigned i=marine.size();i--;)
		this->marine[i].move(x,y);
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
void Ship::marineDeath(){
	::fleet[this->fleet].setMarines(this->rank,--this->marines);
}
void Ship::takeDamage(float damage){
	if(this->integrity>damage)
		this->integrity-=damage;
	else
		this->integrity=0;
	::fleet[this->fleet].setIntegrity(this->rank,(short)this->integrity);
	if(damage>10)
		audio.Boom();
}
bool Ship::sink(){
	this->floating-=0.2;
	//Sails
	if(this->floating<20){
		this->sails->setColor(sf::Color(255,255,255,255*this->floating/20));
		for(unsigned i=marine.size();i--;)
			this->marine[i].setColor(sf::Color(255,255,255,255*this->floating/20));
	}
	//Body
	if(20<=this->floating&&this->floating<60)
		this->body->setColor(sf::Color(255,255,255,255*(this->floating-20)/40));
	//Rows
	if(60<=this->floating&&this->floating<70)
		this->rows->setColor(sf::Color(255,255,255,255*(this->floating-60)/10));
	//Ram
	if(70<=this->floating&&this->floating<100)
		this->ram->setColor(sf::Color(255,255,255,255*(this->floating-70)/30));
	//Sinked
	if(this->floating<=0)
		return 1;
	return 0;
}
Ship::~Ship(){

}