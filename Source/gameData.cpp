#include "gameData.h"
//Players
float getIncome(short player){
	float income=0;
	//Get income from settlements
	for(unsigned i=0;i<::settlement.size();i++)
		if(isOf(i,player))
			income+=getIncomeOf(i);
	//Upkeep of ships
	for(unsigned i=0;i<::fleet.size();i++)
		if(::fleet[i].Player()==player)
			income-=::fleet[i].Upkeep();
	return income;
}
void Defeated(short winner,short defeated){
	::player[winner].WonBattle();
	::player[defeated].LostBattle();
}
//Fleets
float distFleet(short i,short j){
	return ::fleet[i].dist(fleet[j].getPosition());
}
short getShips(short player){
	short ships=0;
	for(unsigned i=0;i<::fleet.size();i++)
		if(::fleet[i].Player()==player)
			ships+=::fleet[i].size();
	return ships;
}
short getNearestFleet(sf::Vector2f point){
	short nearest=0;
	float Dist=distSquare(point,fleet[0].getPosition());
	for(unsigned i=1;i<fleet.size();i++)
		if(Dist>distSquare(point,fleet[i].getPosition())){
			Dist=distSquare(point,fleet[i].getPosition());
			nearest=i;
		}
	return nearest;
}
std::string FleetInfo(short i){
	return Format(::fleet[i].size())+" ships - "+Format(::fleet[i].Provision())+"%";
}
//Settlements
bool hasExport(short i){
	return getImporter(i)>=0;
}
bool hasImport(short i){
	return ::settlement[i].getImport()<(short)::settlement.size();
}
bool hasGood(short settlement,short good){
	if(hasImport(settlement))
		if(getImportedGood(settlement)==good&&!isBlockedImport(settlement))
			return 1;
	return(::settlement[settlement].getGood()==good);
}
bool isYourSett(short settlement){
	return (::settlement[settlement].getOwner()==human);
}
bool isFree(short k){
	bool free=1;
	for(unsigned j=0;j<::fleet.size();j++){
		if(!fleet[j].Speed()&&::fleet[j].dist(settlement[k].getPosition())<90){
			//Supply
			if(!isEnemyOf(k,::fleet[j].Player())){
				free=0;
				::fleet[j].Supply();
				if(!isYourFleet(j))
					::fleet[j].Reform(2);
			}
		}
	}
	return free;
}
bool canRecruit(short id,short sett){
	if(player[settlement[sett].getOwner()].canBuy(naval[id].Cost()))
		return (settlement[sett].canRecruit(naval[id].Rowers()));
	return 0;
}
float getIncomeOf(short i){
	float taxes=0,trade=0,bonuses=0;
	//Tax from population
	taxes+=::settlement[i].getPopulation()/1000.;
	if(hasGood(i,0))
		bonuses+=taxes/10.;
	//Export
	if(isAllyOf(i,settlement[getImporter(i)].getOwner())){
		trade+=::good[settlement[i].getGood()].Price();
		if(hasGood(i,2))
			bonuses+=trade/5.;
		if(hasGood(i,5))
			bonuses+=trade/10.;
	}
	//Import
	if(isAllyOf(i,settlement[settlement[i].getImport()].getOwner()))
		trade-=::good[settlement[settlement[i].getImport()].getGood()].Price();
	return taxes+trade+bonuses;
}
short getNearestSett(sf::Vector2f point){
	short nearest=0;
	float Dist=distSquare(point,settlement[0].getPosition());
	for(unsigned i=1;i<settlement.size();i++)
		if(Dist>distSquare(point,settlement[i].getPosition())){
			Dist=distSquare(point,settlement[i].getPosition());
			nearest=i;
		}
	return nearest;
}
short getPopulation(short player){
	unsigned pop=0;
	for(unsigned i=0;i<::settlement.size();i++){
		if(isOf(i,player))
			pop+=::settlement[i].getPopulation();
	}
	return pop;
}
std::vector<Node> getTradeRoute(short i,short j){
	std::vector<Node> route=map->getRoute(::settlement[i].getPosition(),::settlement[j].getPosition());
	route.push_back(Node(::settlement[j].getPosition(),20));
	return route;
}
//Diplomacy
bool isOf(short i,short player){
	return (::settlement[i].getOwner()==player);
}
bool isAllyOf(short i,short player){
	return (areAllies(::settlement[i].getOwner(),player));
}
bool isEnemyOf(short i,short player){
	return (areEnemies(::settlement[i].getOwner(),player));
}
bool isYourFleet(short i){
	return ::fleet[i].Player()==human;
}
bool isEnemyFleet(short i,short j){
	return ::player[::fleet[i].Player()].Team()!=::player[::fleet[j].Player()].Team();
}
bool isAlliedFleet(short i,short j){
	return ::player[::fleet[i].Player()].Team()==::player[::fleet[j].Player()].Team();
}
//Goods
bool isBlockedExport(short sett){
	return isEnemyOf(sett,::settlement[getImporter(sett)].getOwner());
}
bool isBlockedImport(short sett){
	return isEnemyOf(sett,::settlement[::settlement[sett].getImport()].getOwner());
}
bool playerHasGood(short player,short good){
	for(unsigned i=0;i<::settlement.size();i++)
		if(isOf(i,player)&&hasGood(i,good))
			return 1;
	return 0;
}
short getImporter(short settlement){
	for(unsigned i=0;i<::settlement.size();i++)
		if(::settlement[i].getImport()==settlement)
			return i;
	return -1;
}
short getImportedGood(short settlement){
	return (::settlement[::settlement[settlement].getImport()].getGood());
}
std::string ExportedGoodStatus(short sett){
	if(isBlockedExport(sett))
		return good[::settlement[sett].getGood()].Name()+" to "+(settlement[getImporter(sett)].getName())+" (blocked)";
	return good[::settlement[sett].getGood()].Name()+" to "+(settlement[getImporter(sett)].getName());
}
std::string ImportedGoodStatus(short sett){
	if(isBlockedImport(sett))
		return good[getImportedGood(sett)].Name()+" from "+::settlement[::settlement[sett].getImport()].getName()+ "(blocked)";
	return good[getImportedGood(sett)].Name()+" from "+::settlement[::settlement[sett].getImport()].getName();
}
std::string EconomicStatus(short sett){
	return "Export "+ExportedGoodStatus(sett)+".   Import "+ImportedGoodStatus(sett)+".";
}
//Add functions
void add(Settlement settlement){
	::settlement.push_back(settlement);
}
void add(Player player){
	::player.push_back(player);
}
void add(Fleet fleet){
	::fleet.push_back(fleet);
}