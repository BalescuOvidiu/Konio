#ifndef LABELFLEET_H
#define LABELFLEET_H
#include "gameData.h"
//Display for player
class LabelFleet{
private:
	short selected;
	Label *label;
	Button *player,*form1,*form2,*form3;
public:
	LabelFleet(short selected);
	void Render(sf::RenderWindow *window);
	//Update
	void reload();
	void move(float x,float y);
	bool FormationUpdate();
	bool playerLeft();
	bool right();
	bool mouseOver();
	//Get data
	short Selected();
	Fleet fleet();
	~LabelFleet();
};
extern LabelFleet *labelFleet;
//Global functions
void deselectFleet();
void reloadLabelFleet(short i);
bool isSelectedFleet(short i);
#endif