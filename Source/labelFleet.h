#ifndef LABELFLEET_H
#define LABELFLEET_H
#include "gameData.h"
#include "labelIcon.h"
//Display for player
class LabelFleet{
private:
	short selected,F;
	Label *label;
	//Buttons and icons
	LabelIcon *formation,*upkeep,*dip,*provision;
	Button *player,*form1,*form2;
	//Ships
	std::vector<LabelIcon> ships;
	//Range
	sf::CircleShape *range;
	//Guides
	std::vector<sf::Vertex> route;
public:
	LabelFleet(short selected);
	void select(short selected);
	void select(short selected,short x,short y);
	void Render(sf::RenderWindow *window);
	void RenderGuides(sf::RenderWindow *window);
	//Update
	void Update();
	void reload();
	void move(float x,float y);
	void getRoute();
	bool playerLeft();
	bool right();
	bool mouseOver();
	//Get data
	short Selected();
	Fleet fleet();
	sf::Vector2f getPosition();
	~LabelFleet();
}extern *labelFleet;
#endif