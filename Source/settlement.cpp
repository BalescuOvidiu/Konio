#include "settlement.h"
//Basic
Settlement::Settlement(short x,short y,short player,int population,int limit,int rate,short local,short import,short occupied,std::string name){
	this->region=new Region(x-6*name.length(),y-10,30,name);
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
	return (dist(sf::Vector2f(x,y),gui.mousePosition())<=40);
}
bool Settlement::left(){
	if(this->mouseOver())
		return (gui.canLeft(150));
	return 0;
}
//Get data
std::string Settlement::getName(){
	return this->region->getName();
}
std::string Settlement::getGrowthString(){
	if(!this->getGrowth())
		return "The population stagnates";
	if(this->getGrowth()>0)
		return "+"+gui.Format(this->getGrowth())+" growth";
	return gui.Format(this->getGrowth())+" growth";
}
std::string Settlement::getPopulationString(){
	if(!this->population)
		return "This place is abandoned";
	return gui.Format(this->getPopulation())+"/"+gui.Format(this->getLimit());
}
std::string Settlement::getText(){
	return "          "+this->getPopulationString()+" freemen\n          "+this->getGrowthString();
	;
}
sf::Vector2f Settlement::getPosition(){
	return sf::Vector2f(this->x,this->y);
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
	return this->occupied-1;
}
//Goods
short Settlement::getGood(){
	return this->local;
}
short Settlement::getImport(){
	return this->import;
}
bool Settlement::hasGood(short good){
	return (this->local==good||(::settlement[this->import].getGood()==good&&areAllies(this->getOwner(),::settlement[this->getImport()].getOwner())));
}
//Population
float Settlement::getRate(){
	//Rate
	return this->rate/100.;
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
bool Settlement::isOccupied(){
	return this->occupied;
}
bool Settlement::canRecruit(int population){
	return (this->population>population);
}
Settlement::~Settlement(){
	
}
//Global variable
std::vector<Settlement> settlement;
//Global functions
short getNearestSett(sf::Vector2f point){
	short nearest,begin=0,end=::settlement.size();
	while(begin+1<end){
		nearest=(begin+end)/2;
		if(dist(::settlement[begin].getPosition(),point)<dist(::settlement[end].getPosition(),point))
			end=nearest;
		else
			begin=nearest;
	}
	return nearest;
}
short getPopulation(short player){
	unsigned pop=0;
	for(short i=0;i<(short)::settlement.size();i++){
		if(isOf(i,player))
			pop+=::settlement[i].getPopulation();
	}
	return pop;
}
float getIncomeOf(short i){
	float taxes=0,trade=0,bonuses=0;
	//Tax from population
	taxes+=::settlement[i].getPopulation()/1000.;
	if(hasGood(i,0))
		bonuses+=taxes/10.;
	//Export
	if(isAllyOf(i,settlement[getImporter(i)].getOwner())){
		trade+=::good[settlement[i].getGood()].Price();
		if(hasGood(i,2))
			bonuses+=trade/5.;
		if(hasGood(i,5))
			bonuses+=trade/10.;
	}
	//Import
	if(isAllyOf(i,settlement[settlement[i].getImport()].getOwner()))
		trade-=::good[settlement[settlement[i].getImport()].getGood()].Price();
	return taxes+trade+bonuses;
}
bool isYourSett(short settlement){
	return (::settlement[settlement].getOwner()==human);
}
//Goods
bool hasGood(short settlement,short good){
	return(::settlement[settlement].getGood()==good||(getImportedGood(settlement)==good&&!isBlockedImport(settlement)));
}
bool playerHasGood(short player,short good){
	for(short i=0;i<(short)::settlement.size();i++)
		if(isOf(i,player)&&hasGood(i,good))
			return 1;
	return 0;
}
short getImporter(short settlement){
	for(short i=0;i<(short)::settlement.size();i++)
		if(::settlement[i].getImport()==settlement)
			return i;
	return -1;
}
short getImportedGood(short settlement){
	return (::settlement[::settlement[settlement].getImport()].getGood());
}
//Military
bool isOf(short i,short player){
	return (::settlement[i].getOwner()==player);
}
bool isAllyOf(short i,short player){
	return (areAllies(::settlement[i].getOwner(),player));
}
bool isEnemyOf(short i,short player){
	return (areEnemies(::settlement[i].getOwner(),player));
}
bool isBlockedImport(short sett){
	return isEnemyOf(sett,::settlement[::settlement[sett].getImport()].getOwner());
}
bool isBlockedExport(short sett){
	return isEnemyOf(sett,::settlement[getImporter(sett)].getOwner());
}