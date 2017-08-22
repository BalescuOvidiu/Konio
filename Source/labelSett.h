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
	Button *player,*local,*import;
public:
	LabelSett(short selected);
	void Render(sf::RenderWindow *window);
	//Update
	void move(float x,float y);
	bool playerLeft();
	bool localMouseOver();
	bool importMouseOver();
	bool importLeft();
	bool right();
	bool mouseOver();
	//Get data
	short Selected();
	~LabelSett();
};
//Global variable for GUI
extern LabelSett *labelSett;
//Deselect function
void deselectSett();
#endif