#ifndef SETTLEMENT_H
#define SETTLEMENT_H
#include "good.h"
#include "region.h"
#include "player.h"
//Definition
class Settlement{
private:
	//Location
	Region *region;
	short x,y,player;
	//Population
	int population,limit,rate;
	//Goods
	short local,import,occupied;
public:
	//Basic
	Settlement(short x,short y,short player,int population,int limit,int rate,short local,short import,short occupied,std::string name);
	void Render(sf::RenderWindow *window);
	//Update
	void Monthly();
	void Conquest(short player);
	void Recruit(short population);
	//Mouse
	bool mouseOver();
	bool left();
	//Get data
	sf::Vector2f getPosition();
	std::string getName();
	std::string getGrowthString();
	std::string getPopulationString();
	std::string getText();
	short getOwner();
	short getPlayer();
	short getOccupied();
	//Goods
	short getGood();
	short getImport();
	bool hasGood(short good);
	//Population
	float getRate();
	int getGrowth();
	int getLimit();
	int getPopulation();
	//Military
	bool isOccupied();
	bool canRecruit(int population);
	~Settlement();
};
//Global variable
extern std::vector<Settlement> settlement;
//End declaration
#endif