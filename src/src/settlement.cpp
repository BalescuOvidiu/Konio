#include "settlement.h"
//Basic
Settlement::Settlement(short x,short y,short player,int population,int limit,short local,short import,short occupied,std::string name){
	this->region=new Region(x-6*name.length(),y-18,30,name);
	this->x=x;
	this->y=y;
	this->player=player;
	this->population=population;
	this->limit=limit;
	this->local=local;
	this->import=import;
	this->occupied=occupied;
}
void Settlement::Render(sf::RenderWindow *window){
	this->region->Render(window);
}
//Update
void Settlement::Monthly(){
	//Population
	this->population+=this->getGrowth();
	if(this->population>this->getLimit())
		this->population-=this->population%this->getLimit();
	if(this->population<0)
		this->population=0;
}
void Settlement::Conquest(short player){
	if(areAllies(this->player,player))
		this->occupied=0;
	else
		this->occupied=player+1;
}
void Settlement::Recruit(short population){
	this->population-=population;
}
//Mouse
bool Settlement::mouseOver(){
	return (Dist(sf::Vector2f(x,y),gui.mousePosition())<=1600);
}
bool Settlement::left(){
	if(this->mouseOver())
		return (gui.canLeft(150));
	return 0;
}
//Get data
sf::Vector2f Settlement::getPosition(){
	return sf::Vector2f(this->x,this->y);
}
sf::Vector2f Settlement::getRangePosition(){
	return sf::Vector2f(this->x-this->getRange(),this->y-this->getRange());
}
std::string Settlement::getName(){
	return this->region->getName();
}
std::string Settlement::getGrowthString(){
	if(!this->getGrowth())
		return "Stagned";
	if(this->getGrowth()>0)
		return "+"+Format(this->getGrowth());
	return Format(this->getGrowth());
}
std::string Settlement::getPopulationString(){
	if(!this->population)
		return "Abandoned";
	return Format(this->getPopulation())+"/"+Format(this->getLimit());
}
std::string Settlement::getText(){
	return "          "+this->getPopulationString()+" freemen\n          "+this->getGrowthString()+" growth";
}
short Settlement::getOwner(){
	if(!this->isOccupied())
		return this->player;
	return this->occupied-1;
}
short Settlement::getPlayer(){
	return this->player;
}
short Settlement::getOccupied(){
	return this->occupied;
}
short Settlement::getRange(){
	return 90+this->population/300;
}
//Goods
short Settlement::getGood(){
	return this->local;
}
short Settlement::getImport(){
	return this->import;
}
bool Settlement::hasGood(short good){
	if((unsigned)this->import<::settlement.size())
		if((::settlement[this->import].getGood()==good&&areAllies(this->getOwner(),::settlement[this->getImport()].getOwner())))
			return 1;
	return this->local==good;
}
//Population
float Settlement::getRate(){
	return this->limit/367879.;
}
int Settlement::getGrowth(){
	//Bonuses
	float bonuses=1;
	if(this->hasGood(3))
		bonuses+=0.1;
	if(this->hasGood(5))
		bonuses+=0.1;
	if(this->hasGood(6))
		bonuses+=0.2;
	//Growth
	return this->population*this->getRate()*bonuses;
}
int Settlement::getLimit(){
	//Bonuses
	int bonuses=0;
	if(this->hasGood(0))
		bonuses+=limit*0.4;
	if(this->hasGood(3))
		bonuses+=limit/10;
	if(this->hasGood(4))
		bonuses+=limit/5;
	if(this->hasGood(5))
		bonuses+=limit/10;
	//Limit
	return this->limit+bonuses;
}
int Settlement::getPopulation(){
	return this->population;
}
//Military
bool Settlement::isOccupied(){
	return this->occupied;
}
bool Settlement::canRecruit(int population){
	return (this->population>population);
}
bool Settlement::isInRange(sf::Vector2f point){
	return ((8100+this->population*9/15+this->population*this->population/90000)>Dist(sf::Vector2f(x,y),point));
}
Settlement::~Settlement(){
	
}
//Global variable
std::vector<Settlement> settlement;