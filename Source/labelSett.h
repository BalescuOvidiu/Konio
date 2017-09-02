#ifndef LABELSETT_H
#define LABELSETT_H
#include "settlement.h"
#include "player.h"
#include "fleet.h"
//Display for settlement
class LabelSett{
private:
	short selected;
	Label *label;
	//Trade and player
	Button *local,*import,*player;
	//Navy
	Button *first,*second,*third;
public:
	LabelSett(short selected);
	void Render(sf::RenderWindow *window);
	//Update
	void move(float x,float y);
	bool playerLeft();
	bool localMouseOver();
	bool localLeft();
	bool importMouseOver();
	bool importLeft();
	bool right();
	bool mouseOver();
	short getShip();
	//Get data
	short Selected();
	Settlement sett();
	~LabelSett();
};
//Global variable for GUI
extern LabelSett *labelSett;
//Global functions
void deselectSett();
void reloadLabelSett(short i);
bool isSelectedSett(short i);
#endif