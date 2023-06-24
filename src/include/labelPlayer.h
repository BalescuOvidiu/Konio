#ifndef LABELPLAYER_H
#define LABELPLAYER_H
#include "gameData.h"
#include "labelIcon.h"
//Display for player
class LabelPlayer{
private:
	short selected;
	Label *label;
	LabelIcon *pop,*ships,*coins,*income,*statistics;
	Button *shield;
public:
	LabelPlayer(short selected);
	void select(short selected);
	void select(short selected,short x,short y);
	void Render(sf::RenderWindow *window);
	//Update
	void move(float x,float y);
	bool right();
	bool mouseOver();
	//Get data
	short Selected();
	Player player();
	sf::Vector2f getPosition();
	~LabelPlayer();
}extern *labelPlayer;
#endif