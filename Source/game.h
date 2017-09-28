#ifndef GAME_H
#define GAME_H
#include "battle.h"
#include "labelDip.h"
#include "labelFleet.h"
#include "labelIcon.h"
#include "labelPlayer.h"
#include "labelSett.h"
#include "map.h"
#include "options.h"
#include "submenu.h"
//Definition
class Game{
private:
	//Informational
	std::string name,description;
	//GUI
	SubMenu *subMenu;
	Button *submenu,*main,*diplomacy;
	LabelIcon *coins,*pop;
	//Toggle GUI
	sf::CircleShape* range;
	sf::Text *paused;
	void showHumanStatus();
	void showData();
	void deselectAll();
	void selectPlayer(short player);
	void selectFleet(short fleet);
	void selectSett(short sett);
	void goToSett(sf::View *view,short sett);
	bool mouseOverGUI();
	void gameGUI(sf::RenderWindow *window,sf::View *view);
	//Map
	Map *map;
	//Clock
	unsigned month;
	short year;
	bool Pause();
	std::string getMonthName();
	void Clock();
	void Monthly();
	//AI
	void AI();
	void DefeatedFleet(short i,short j);
	void CombatFleet(short i,short j);
	void getRoute(short fleet,sf::Vector2f target);
	void buyShip(short id,short sett);
	//View
	void moveView(sf::View *view,float x,float y);
	void moveViewTo(sf::View *view,sf::Vector2f pos);
	void moveCamera(sf::RenderWindow *window,sf::View *view,float speed);
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