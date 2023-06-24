#ifndef H_BAR
#define H_BAR
#include "labelDip.h"
#include "labelFleet.h"
#include "labelIcon.h"
#include "labelPlayer.h"
#include "labelSett.h"
#include "submenu.h"
//Definition of bar menu
class Bar{
private:
	sf::RectangleShape *rectangle;
	Button *main,*submenu,*diplomacy;
	LabelIcon *coins,*pop,*calendar;
public:
	//Constructor
	Bar(std::string data);
	//Render
	void Render(sf::RenderWindow *window);
	//Update
	void Update();
	void Reload();
	void Reload(std::string data);
	void move(float x,float y);
	bool mouseOver();
	//Destructor
	~Bar();
}extern *bar;
//LabelFleet global functions
void changedFleets(short i,short j);
void selectFleet(short fleet);
void deselectFleet();
void reloadLabelFleet(short i);
bool isSelectedFleet(short i);
//LabelSett global functions
void selectSett(short sett);
void deselectSett();
void reloadLabelSett(short i);
bool isSelectedSett(short i);
//LabelPlayer global functions
void selectPlayer(short player);
void deselectPlayer();
void reloadLabelPlayer(short i);
bool isSelectedPlayer(short i);
#endif