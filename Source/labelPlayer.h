#ifndef LABELPLAYER_H
#define LABELPLAYER_H
#include "settlement.h"
#include "player.h"
#include "fleet.h"
//Display for player
class LabelPlayer{
private:
	short selected;
	Label *label;
	Button *shield;
public:
	LabelPlayer(short selected);
	void Render(sf::RenderWindow *window);
	//Update
	void move(float x,float y);
	bool right();
	bool mouseOver();
	//Get data
	short Selected();
	Player player();
	~LabelPlayer();
};
//Global variable
extern LabelPlayer *labelPlayer;
//Global functions
void deselectPlayer();
void reloadLabelPlayer(short i);
bool isSelectedPlayer(short i);
#endif