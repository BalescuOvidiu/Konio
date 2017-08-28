#ifndef PLAYER_H
#define PLAYER_H
#include "button.h"

class Player{
private:
	//Basic
	std::string name;
	short faction,team;
	float coins;
	//Statistic
	short lost,won;
public:
	//Constructor
	Player(short faction,float coins,short team,std::string name);
	//Set data functions
	void Faction(short faction);
	void Name(std::string name);
	void Income(float coins);
	void WonBattle();
	void LostBattle();
	void reset();
	//Get data functions
	short Faction();
	short Team();
	std::string Name();
	std::string Statistics();
	float Coins();
	bool canBuy(float cost);
	//Operator
	bool operator!=(Player player);
	//Destructor
	~Player();
};
//Global variables
extern short human;
extern std::vector<Player> player;
//Global functions
std::string getDiplomaticStatus(short player);
bool areAllies(short i,short j);
bool areEnemies(short i,short j);
#endif