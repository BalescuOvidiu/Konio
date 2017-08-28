#ifndef SETTLEMENT_H
#define SETTLEMENT_H
#include "good.h"
#include "region.h"
#include "player.h"
//Class
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
	void Update();
	void Monthly();
	void Conquest(short player);
	void Recruit(short population);
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
//Global functions
short getNearestSett(sf::Vector2f point);
short getPopulation(short player);
float getIncomeOf(short i);
float getIncome(short player);
bool isYourSett(short settlement);
//Goods
bool hasGood(short settlement,short good);
bool playerHasGood(short player,short good);
short getImporter(short settlement);
short getImportedGood(short settlement);
//Military
bool isOf(short i,short player);
bool isAllyOf(short i,short player);
bool isEnemyOf(short i,short player);
#endif