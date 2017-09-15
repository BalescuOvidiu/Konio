#ifndef GAMEDATA_H
#define GAMEDATA_H
#include "settlement.h"
#include "player.h"
#include "fleet.h"
//Players
float getIncome(short player);
//Goods
std::string ExportedGoodStatus(short sett);
std::string ImportedGoodStatus(short sett);
std::string EconomicStatus(short sett);
#endif