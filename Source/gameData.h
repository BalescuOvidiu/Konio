#ifndef GAMEDATA_H
#define GAMEDATA_H
#include "settlement.h"
#include "player.h"
#include "fleet.h"
//Players
float getIncome(short player);
void Defeated(short winner,short defeated);
//Fleets
float distFleet(short i,short j);
short getShips(short player);
short getNearestFleet(sf::Vector2f point);
std::string FleetInfo(short i);
//Settlements
bool isYourSett(short settlement);
float getIncomeOf(short i);
short getNearestSett(sf::Vector2f point);
short getPopulation(short player);
//Diplomacy
bool isOf(short i,short player);
bool isAllyOf(short i,short player);
bool isEnemyOf(short i,short player);
bool isYourFleet(short i);
bool isEnemyFleet(short i,short j);
bool isAlliedFleet(short i,short j);
//Goods
bool hasGood(short settlement,short good);
bool isBlockedExport(short sett);
bool isBlockedImport(short sett);
bool playerHasGood(short player,short good);
short getImporter(short settlement);
short getImportedGood(short settlement);
std::string ExportedGoodStatus(short sett);
std::string ImportedGoodStatus(short sett);
std::string EconomicStatus(short sett);
//End declarations
#endif