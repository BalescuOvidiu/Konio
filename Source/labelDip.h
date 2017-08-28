#ifndef LABELDIP_H
#define LABELDIP_H
#include "settlement.h"
#include "player.h"
#include "fleet.h"
//Diplomatic status display
class LabelDip{
private:
	short selected;
	Label *label;
	std::vector <Button> player;
public:
	LabelDip();
	void Render(sf::RenderWindow *window);
	//Update
	void Update();
	void move(float x,float y);
	bool right();
	bool mouseOver();
	//Get data
	short Selected();
	//Show data
	void showData(short player);
	~LabelDip();
};
//Global variable
extern LabelDip *labelDip;
//Global function
void deselectDip();
#endif