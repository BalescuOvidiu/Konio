#ifndef LABELSETT_H
#define LABELSETT_H
#include "gameData.h"
#include "labelIcon.h"
//Display for settlement
class LabelSett{
private:
	short selected;
	Label *label;
	//Economy and population
	LabelIcon *pop,*growth,*income,*dip;
	//Trade and player
	Button *local,*import,*player;
	//Military
	std::vector<short> id;
	std::vector<Button> recruit;
	//Range
	sf::CircleShape *range;
	//Guides
	bool L,I;
	std::vector<sf::Vertex> Export,Import;
public:
	LabelSett(short selected);
	void select(short selected);
	void select(short selected,short x,short y);
	void Render(sf::RenderWindow *window);
	void RenderGuides(sf::RenderWindow *window);
	//Update
	void move(float x,float y);
	bool playerLeft();
	bool localLeft();
	bool importLeft();
	bool right();
	bool mouseOver();
	short Ship();
	//Get data
	short Selected();
	Settlement sett();
	sf::Vector2f getPosition();
	~LabelSett();
}extern *labelSett;
#endif