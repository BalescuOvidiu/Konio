#ifndef GAMEDATA_H
#define GAMEDATA_H
#include "settlement.h"
#include "player.h"
#include "fleet.h"
#include "map.h"
//Players
float getIncome(short player);
void Defeated(short winner,short defeated);
std::string getDataPlayer(short i);
//Fleets
bool canCombat(short i,short j);
float distFleet(short i,short j);
float DistFleet(short i,short j);
short getShips(short player);
short getNearestFleet(sf::Vector2f point);
short getSmallestFleetInRange(unsigned i);
std::string FleetInfo(short i);
//Settlements
bool hasSettlement(short player);
bool hasExport(short i);
bool hasImport(short i);
bool hasGood(short settlement,short good);
bool isYourSett(short settlement);
bool isInDanger(short sett);
bool isRecruitable(short id,short sett);
bool canRecruit(short id,short sett);
float getIncomeOf(short i);
short getNearestSett(sf::Vector2f point);
unsigned getPopulation(short player);
std::string getPopulationStatus(short i);
std::string getSettlementTitle(short i);
std::string getSettlementDescription(short i);
std::vector<Node> getTradeRoute(short i,short j);
//Diplomacy
bool isOf(short i,short player);
bool isAllyOf(short i,short player);
bool isEnemyOf(short i,short player);
bool isYourFleet(short i);
bool isEnemyFleet(short i,short j);
bool isAlliedFleet(short i,short j);
//Goods
bool isBlockedExport(short sett);
bool isBlockedImport(short sett);
bool playerHasGood(short player,short good);
short getImporter(short settlement);
short getImportedGood(short settlement);
std::string ExportedGoodStatus(short sett);
std::string ImportedGoodStatus(short sett);
std::string EconomicStatus(short sett);
//Distances
float Dist(Fleet fleet,sf::Vector2f point);
float Dist(Fleet fleet,Settlement settlement);
//Add functions
void add(Settlement settlement);
void add(Player player);
void add(Fleet fleet);
//End of declarations
#endif