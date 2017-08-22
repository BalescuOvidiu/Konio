#include "player.h"
//Constructors
Player::Player(){
	this->name="";
	this->faction=0;
}
Player::Player(short faction,float coins,short team,std::string name){
	this->faction=faction;
	this->name=name;
	this->coins=coins;
	this->team=team;
	this->reset();
}
//Set data functions
void Player::Faction(short faction){
	this->faction=faction;
}
void Player::Name(std::string name){
	this->name=name;
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
std::string Player::Coins(){
	std::stringstream stream;
	stream<<std::fixed<<std::setprecision(1)<<this->coins;
	return stream.str();
}
void Player::reset(){
	this->destroyed=this->lost=this->total=this->selected=0;
}
bool Player::operator!=(Player player){
	return (this->Name()!=player.Name()||this->Faction()!=player.Faction());
}
Player::~Player(){
	
}
//Global variable
short human;
std::vector<Player> player;
//Global function
std::string getDiplomaticStatus(short player){
	if(player==human)
		return " - You";
	if(::player[player].Team()==::player[human].Team())
		return " - Ally";
	return " - Enemy";
}