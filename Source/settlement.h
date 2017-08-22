#ifndef SETTLEMENT_H
#define SETTLEMENT_H
#include "good.h"
#include "region.h"
//Class
class Settlement{
private:
	//Location
	Region *region;
	short x,y,player;
	//Population
	short population,limit;
	int rate;
	//Goods
	short local,import,occupied;
public:
	//Basic
	Settlement(short x,short y,short player,short population,short limit,int rate,short local,short import,short occupied,std::string name);
	void Render(sf::RenderWindow *window);
	//Update
	void Update();
	void Monthly();
	bool left();
	//Get data
	sf::Vector2f getPosition();
	std::string getName();
	short getPlayer();
	short getPopulation();
	short getOccupied();
	short getGood();
	short getImport();
	bool isOccupied();
	~Settlement();
};
//Global variable
extern std::vector<Settlement> settlement;
//Global functions
short getPopulation(short player);
float getIncome(short player);
//Goods
bool hasGood(short settlement,short good);
bool playerHasGood(short player,short good);
short getImportedGood(short settlement);
//Military
bool isOf(short i,short player);
#endif