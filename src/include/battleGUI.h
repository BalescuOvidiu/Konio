#ifndef H_BATTLEGUI
#define H_BATTLEGUI
#include "button.h"
#include "labelIcon.h"
#include "options.h"
//Definition of bar menu
class BattleGUI{
private:
	sf::RectangleShape *rectangle;
	LabelIcon *ships,*details;
public:
	//Constructor
	BattleGUI(std::string data);
	//Render
	void Render(sf::RenderWindow *window);
	//Update
	void Reload(std::string data);
	void ReloadDetails(std::string data);
	void move(float x,float y);
	void zoom(float factor);
	bool mouseOver();
	//Destructor
	~BattleGUI();
};
#endif