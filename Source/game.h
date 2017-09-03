#ifndef GAME_H
#define GAME_H
#include "map.h"
#include "battle.h"
#include "labelSett.h"
#include "labelPlayer.h"
#include "labelFleet.h"
#include "labelDip.h"
#include "submenu.h"
#include "options.h"
//Definition
class Game{
private:
	//Informational
	std::string name,description;
	//GUI
	SubMenu *subMenu;
	Button *submenu,*main,*diplomacy;
	sf::Text *text;
	void showDiplomaticStatus(short player);
	void showHumanStatus();
	void showData();
	void deselectAll();
	void selectPlayer(short player);
	void selectFleet(short fleet);
	void selectSett(short sett);
	bool mouseOverGUI();
	void gameGUI(sf::RenderWindow *window,sf::View *view);
	//Map
	Map *map;
	//Clock
	bool pause;
	unsigned month;
	short year;
	bool Pause();
	std::string getMonthName();
	void Clock();
	void Monthly();
	//AI
	void AI();
	void getRoute(short fleet,sf::Vector2f target);
	void buyShip(short id,short sett);
	//View
	void moveView(sf::View *view,float x,float y);
	void moveViewTo(sf::View *view,sf::Vector2f pos);
	void moveCamera(sf::RenderWindow *window,sf::View *view);
public:
	//Battle
	Battle *battle;
	//Basic
	Game(std::string directory,sf::View *view,short human);
	void Render(sf::RenderWindow *window);
	void Reset(sf::RenderWindow *window,sf::View *view);
	//Update
	void Update(sf::RenderWindow *window,sf::View *view);
	~Game();
};
#endif