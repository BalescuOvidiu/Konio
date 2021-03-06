#include "player.h"
//Constructor
Player::Player(short faction,float coins,short team,std::string name,short won,short lost){
	//Basic
	this->faction=faction;
	this->name=name;
	this->coins=coins;
	this->team=team;
	//Statistics
	this->won=won;
	this->lost=lost;
}
//Set data functions
void Player::Faction(short faction){
	this->faction=faction;
}
void Player::Name(std::string name){
	this->name=name;
}
void Player::Income(float coins){
	this->coins+=coins;
}
void Player::WonBattle(){
	this->won++;
}
void Player::LostBattle(){
	this->lost++;
}
void Player::reset(){
	this->lost=this->won=0;
}
//Get data functions
short Player::Faction(){
	return this->faction;
}
short Player::Team(){
	return this->team;
}
std::string Player::Name(){
	return this->name;
}
std::string Player::Statistics(){
	if(this->won||this->lost)
		return Format(this->won)+"/"+Format(this->lost);
	return "No battles.";
}
std::string Player::Battles(){
	return Format(this->won)+" "+Format(this->lost);
}
float Player::Coins(){
	return this->coins;
}
bool Player::canBuy(float cost){
	if(this->coins-cost>=0)
		return 1;
	return 0;
}
//Operator
bool Player::operator!=(Player player){
	return (this->Name()!=player.Name()||this->Faction()!=player.Faction());
}
//Destructor
Player::~Player(){
	
}
//Global variables
short human;
std::vector<Player> player;
//Global functions
bool areAllies(short i,short j){
	return ::player[i].Team()==::player[j].Team();
}
bool areEnemies(short i,short j){
	return ::player[i].Team()!=::player[j].Team();
}
bool areNeutrals(short i,short j){
	return areAllies(i,j)&&areEnemies(i,j);
}
std::string getDiplomaticStatus(short player){
	if(player==human)
		return " - You";
	if(areAllies(human,player))
		return " - Ally";
	if(areEnemies(human,player))
		return " - Enemy";
	return " - Neutral";
}
std::string PlayerInfo(short player){
	return ::player[player].Name()+getDiplomaticStatus(player);
}