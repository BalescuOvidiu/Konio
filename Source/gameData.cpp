#include "gameData.h"
//Players
float getIncome(short player){
	float income=0;
	//Get income from settlements
	for(unsigned i=::settlement.size();i--;)
		if(isOf(i,player))
			income+=getIncomeOf(i);
	//Upkeep of ships
	for(unsigned i=::fleet.size();i--;)
		if(::fleet[i].Player()==player)
			income-=::fleet[i].Upkeep();
	return income;
}
void Defeated(short winner,short defeated){
	::player[winner].WonBattle();
	::player[defeated].LostBattle();
}
std::string getDataPlayer(short i){
	return "Population: "+Format(getPopulation(i))+"   Coins: "+Format(::player[i].Coins())+"   Income: "+Format(getIncome(i))+"\nShips: "+Format(getShips(i))+"   Battles: "+::player[i].Statistics();
}
//Fleets
bool canCombat(short i,short j){
	return isEnemyFleet(i,j)&&(::fleet[j].isInRange(::fleet[i].getPosition())||::fleet[j].isInRange(::fleet[i].getPosition()));
}
float distFleet(short i,short j){
	return ::fleet[i].Dist(fleet[j].getPosition());
}
float DistFleet(short i,short j){
	return Dist(::fleet[i].getPosition(),fleet[j].getPosition());
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
	float distance=Dist(point,fleet[0].getPosition());
	for(unsigned i=::fleet.size();(i--)>1;)
		if(distance>Dist(::fleet[i],point)){
			distance=Dist(::fleet[i],point);
			nearest=i;
		}
	return nearest;
}
short getSmallestFleetInRange(unsigned i){
	short nearest=-1;
	short size=1000;
	for(unsigned j=::fleet.size();j--;){
		if(j!=i&&::fleet[i].Player()==::fleet[j].Player()){
			if(::fleet[i].isInRange(::fleet[j].getPosition())){
				if(size>::fleet[j].size()){
					size=::fleet[j].size();
					nearest=j;
				}
			}
		}
	}
	return nearest;
}
std::string FleetInfo(short i){
	return Format(::fleet[i].size())+" ships - "+Format(::fleet[i].Provision())+"%";
}
//Settlements
bool hasSettlement(short player){
	for(unsigned i=::settlement.size();i--;)
		if(::settlement[i].getOwner()==player)
			return 1;
	return 0;
}
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
bool isInDanger(short sett){
	short i=getNearestFleet(::settlement[sett].getPosition());
	return (Dist(::fleet[i],::settlement[sett])>Dist(::fleet[i].getTarget(),::settlement[sett].getPosition())&&isEnemyOf(sett,::fleet[i].Player()));
}
bool isRecruitable(short id,short sett){
	if((id<mercenaries)==(!hasGood(sett,1)))
		return 0;
	return 1;
}
bool canRecruit(short id,short sett){
	if(player[settlement[sett].getOwner()].canBuy(naval[id].Cost()))
		return (settlement[sett].canRecruit(naval[id].Men()));
	return 0;
}
float getIncomeOf(short i){
	float taxes=0,trade=0,bonuses=0;
	//Tax from population
	taxes+=::settlement[i].getPopulation()>>9;
	if(hasGood(i,0))
		bonuses+=taxes/10.;
	//Export
	if(hasExport(i))
		if(isAllyOf(i,settlement[getImporter(i)].getOwner())){
			trade+=::good[settlement[i].getGood()].Price();
			if(hasGood(i,2))
				bonuses+=trade/5.;
			if(hasGood(i,5))
				bonuses+=trade/10.;
		}
	//Import
	if(hasImport(i))
		if(isAllyOf(i,settlement[settlement[i].getImport()].getOwner()))
			trade-=::good[settlement[settlement[i].getImport()].getGood()].Price();
	return taxes+trade+bonuses;
}
short getNearestSett(sf::Vector2f point){
	short nearest=0;
	float distance=Dist(point,settlement[0].getPosition());
	for(unsigned i=1;i<settlement.size();i++)
		if(distance>Dist(point,settlement[i].getPosition())){
			distance=Dist(point,settlement[i].getPosition());
			nearest=i;
		}
	return nearest;
}
unsigned getPopulation(short player){
	unsigned pop=0;
	for(unsigned i=::settlement.size();i--;){
		if(isOf(i,player))
			pop+=::settlement[i].getPopulation();
	}
	return pop;
}
std::string getPopulationStatus(short i){
	return settlement[i].getPopulationString()+" freemen  "+settlement[i].getGrowthString()+" growth  ";
}
std::string getSettlementTitle(short i){
	return player[settlement[i].getOwner()].Name()+"'s settlement"+getDiplomaticStatus(settlement[i].getOwner());
}
std::string getSettlementDescription(short i){
	return getPopulationStatus(i)+Format(getIncomeOf(i))+" income\n"+EconomicStatus(i);
}
std::vector<Node> getTradeRoute(short i,short j){
	std::vector<Node> route=map->getRoute(::settlement[i].getPosition(),::settlement[j].getPosition());
	route.push_back(Node(::settlement[j].getPosition(),20));
	return route;
}
//Diplomacy
bool isOf(short i,short player){
	return ::settlement[i].getOwner()==player;
}
bool isAllyOf(short i,short player){
	return areAllies(::settlement[i].getOwner(),player);
}
bool isEnemyOf(short i,short player){
	return areEnemies(::settlement[i].getOwner(),player);
}
bool isYourFleet(short i){
	return ::fleet[i].Player()==human;
}
bool isEnemyFleet(short i,short j){
	return areEnemies(::fleet[i].Player(),::fleet[j].Player());
}
bool isAlliedFleet(short i,short j){
	return areAllies(::fleet[i].Player(),::fleet[j].Player());;
}
//Goods
bool isBlockedExport(short sett){
	return isEnemyOf(sett,::settlement[getImporter(sett)].getOwner());
}
bool isBlockedImport(short sett){
	return isEnemyOf(sett,::settlement[::settlement[sett].getImport()].getOwner());
}
bool playerHasGood(short player,short good){
	for(unsigned i=::settlement.size();i--;)
		if(isOf(i,player)&&hasGood(i,good))
			return 1;
	return 0;
}
short getImporter(short settlement){
	for(unsigned i=::settlement.size();i--;){
		if(::settlement[i].getImport()==settlement)
			return i;
	}
	return -1;
}
short getImportedGood(short settlement){
	return (::settlement[::settlement[settlement].getImport()].getGood());
}
std::string ExportedGoodStatus(short sett){
	if(!hasExport(sett))
		return "route is not enstablished";
	if(isBlockedExport(sett))
		return good[::settlement[sett].getGood()].Name()+" to "+(settlement[getImporter(sett)].getName())+" (blocked)";
	return good[::settlement[sett].getGood()].Name()+" to "+(settlement[getImporter(sett)].getName());
}
std::string ImportedGoodStatus(short sett){
	if(!hasImport(sett))
		return "route is not enstablished";
	if(isBlockedImport(sett))
		return good[getImportedGood(sett)].Name()+" from "+::settlement[::settlement[sett].getImport()].getName()+ "(blocked)";
	return good[getImportedGood(sett)].Name()+" from "+::settlement[::settlement[sett].getImport()].getName();
}
std::string EconomicStatus(short sett){
	return "Export "+ExportedGoodStatus(sett)+".   Import "+ImportedGoodStatus(sett)+".";
}
//Distances
float Dist(Fleet fleet,sf::Vector2f point){
	return Dist(fleet.getPosition(),point);
}
float Dist(Fleet fleet,Settlement settlement){
	return Dist(fleet.getPosition(),settlement.getPosition());
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