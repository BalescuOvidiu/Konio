#ifndef GAME_H
#define GAME_H
#include "battle.h"
#include "gameGUI.h"
//Other functions
void BuyShip(short id,short sett);
void CombatFleet(short i,short j);
void DefeatedFleet(short i,short j);
void takeSettlement(short i,short player);
void MoveFleet(short fleet,sf::Vector2f target);
//Definition
class Game{
private:
	//GUI
	sf::Text *paused;
	bool mouseOverGUI();
	void gameGUI(sf::RenderWindow *window,sf::View *view);
	//View
	void moveView(sf::View *view,float x,float y);
	void moveViewTo(sf::View *view,sf::Vector2f pos);
	void moveViewToSett(sf::View *view,short sett);
	void moveCamera(sf::RenderWindow *window,sf::View *view,float speed);
	//Clock
	unsigned month;
	short year;
	bool Pause();
	std::string getMonthName();
	std::string getCalendar();
	void Clock();
	void Monthly();
	//AI
	void AI();
	//Battle
	void newBattle(short yourFleet,short enemyFleet,sf::View *view);
	void afterBattle(sf::View *view);
public:
	//Battle
	Battle *battle;
	//Basic
	Game(std::string directory,sf::View *view,short human);
	void Render(sf::RenderWindow *window);
	void Update(sf::RenderWindow *window,sf::View *view);
	~Game();
};
#endif