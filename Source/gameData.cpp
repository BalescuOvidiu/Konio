#include "gameData.h"
//Players
float getIncome(short player){
	float income=0;
	//Get income from settlements
	for(short i=0;i<(short)::settlement.size();i++)
		if(isOf(i,player))
			income+=getIncomeOf(i);
	//Upkeep of ships
	for(short i=0;i<(short)::fleet.size();i++)
		if(::fleet[i].Player()==player)
			income-=::fleet[i].Upkeep();
	return income;
}
//Goods
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