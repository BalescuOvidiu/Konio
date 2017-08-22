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
	Button *player;
public:
	LabelPlayer(short selected);
	void Render(sf::RenderWindow *window);
	//Update
	void move(float x,float y);
	bool right();
	bool mouseOver();
	//Get data
	short Selected();
	~LabelPlayer();
};
//Global variable
extern LabelPlayer *labelPlayer;
//Deselect function
void deselectPlayer();
#endif