#include "settlement.h"
//Basic
Settlement::Settlement(short x,short y,short player,short population,short limit,int rate,short local,short import,short occupied,std::string name){
	this->region=new Region(x,y,30,name);
	this->x=x;
	this->y=y;
	this->player=player;
	this->population=population;
	this->limit=limit;
	this->rate=rate;
	this->local=local;
	this->import=import;
	this->occupied=occupied;
}
void Settlement::Render(sf::RenderWindow *window){
	this->region->Render(window);
}
//Update
void Settlement::Update(){
	this->region->Update();
}
void Settlement::Monthly(){
	this->population+=this->population*this->rate/100.;
	if(this->population>this->limit)
		this->population=this->limit;
}
bool Settlement::left(){
	return (sf::Mouse::isButtonPressed(sf::Mouse::Left)&&dist(sf::Vector2f(x,y),gui.mousePosition())<=40);
}
//Get data
std::string Settlement::getName(){
	return this->region->getName();
}
sf::Vector2f Settlement::getPosition(){
	return sf::Vector2f(this->x,this->y);
}
short Settlement::getPlayer(){
	return this->player;
}
short Settlement::getPopulation(){
	return this->population;
}
short Settlement::getOccupied(){
	return this->occupied-1;
}
short Settlement::getGood(){
	return this->local;
}
short Settlement::getImport(){
	return this->import;
}
bool Settlement::isOccupied(){
	return this->occupied;
}
Settlement::~Settlement(){
	
}
//Global variable
std::vector<Settlement> settlement;
//Global functions
short getPopulation(short player){
	short pop=0;
	for(short i=0;i<(short)::settlement.size();i++){
		if(isOf(i,player))
			pop+=::settlement[i].getPopulation();
	}
	return pop;
}
float getIncome(short player){
	float income=0;
	for(short i=0;i<(short)::settlement.size();i++)
		if(isOf(i,player)){
			//Tax from population
			income+=::settlement[i].getPopulation()/1000.;
			//Trade
			income+=::good[settlement[i].getGood()].Price();
			income-=::good[getImportedGood(i)].Price();
		}
	return income;
}
//Goods
bool hasGood(short settlement,short good){
	return(::settlement[settlement].getGood()==good||getImportedGood(settlement)==good);
}
bool playerHasGood(short player,short good){
	for(short i=0;i<(short)::settlement.size();i++)
		if(isOf(i,player)&&hasGood(i,good))
			return 1;
	return 0;
}
short getImportedGood(short settlement){
	return (::settlement[::settlement[settlement].getImport()].getGood());
}
//Military
bool isOf(short i,short player){
	return ((::settlement[i].getPlayer()==player&&::settlement[i].getOccupied()==-1)||::settlement[i].getOccupied()==player+1);
}