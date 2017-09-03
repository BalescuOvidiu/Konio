#include "gameData.h"
//Global functions
float getIncome(short player){
	float income=0;
	for(short i=0;i<(short)::settlement.size();i++)
		if(isOf(i,player))
			income+=getIncomeOf(i);
	return income-getShips(player)/10.;
}