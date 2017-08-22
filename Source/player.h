#ifndef PLAYER_H
#define PLAYER_H
#include "button.h"

class Player{
private:
	std::string name;
	short faction,team;
public:
	//Gameplay
	short destroyed,last,lost,total,selected;
	float coins;
	//Constructor
	Player();
	Player(short faction,float coins,short team,std::string name);
	void Faction(short faction);
	void Name(std::string name);
	void reset();
	short Faction();
	short Team();
	std::string Name();
	std::string Coins();
	bool operator!=(Player player);
	~Player();
};
//Global variables
extern short human;
extern std::vector<Player> player;
//Global functions
std::string getDiplomaticStatus(short player);
#endif