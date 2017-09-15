#ifndef LABELDIP_H
#define LABELDIP_H
#include "gameData.h"
//Diplomatic status display
class LabelDip{
private:
	Label *label;
	std::vector <Button> player;
public:
	LabelDip();
	void Render(sf::RenderWindow *window);
	//Update
	short Update();
	void move(float x,float y);
	bool right();
	bool mouseOver();
	~LabelDip();
};
//Global variable
extern LabelDip *labelDip;
//Global function
void deselectDip();
void reloadLabelDip();
#endif