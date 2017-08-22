#ifndef BATTLE_H
#define BATTLE_H
#include "background.h"
#include "ship.h"
#include "submenu.h"
#include "fleet.h"
//Definition
class Battle{
private:
	//Informational
	std::string name,description;
	//GUI
	SubMenu *subMenu;
	Button *submenu;
	sf::Text *text;
	//Gameplay
	short human;
	bool pause;
	//AI
	int nearest,best;
	float d,minDist;
	std::vector<std::deque<sf::Vector2f> > target;
	std::vector<short> team;
	//Water
	Layer *water;
	//Entity
	std::vector<Player> player;
	std::vector<Ship> ship;
	//Ship's points
	sf::Vector2f local(sf::Vector2f point, short ship);
	sf::Vector2f localForward(float dist,short ship);
	sf::Vector2f localBackward(float dist,short ship);
	sf::Vector2f localLeft(float dist,short ship);
	sf::Vector2f localRight(float dist,short ship);
	bool validPoint(sf::Vector2f point);
	//Team
	bool isYour(short ship);
	bool isRammed(short ship);
	bool isEnemy(short i,short j);
	bool isFriend(short i,short j);
	//Event
	void Stop(short ship);
	bool ramming(short i,short j);
	bool collision(short i,short j);
	//GUI
	std::string getStatistic();
	bool Pause();
	void moveView(sf::View *view,float x,float y);
	void moveCamera(sf::RenderWindow *window,sf::View *view);
	//Human
	void select(short ship);
	void deselect();
public:
	//Basic
	Battle(std::string directory,sf::View *view);
	void Render(sf::RenderWindow *window);
	void Reset(sf::RenderWindow *window,sf::View *view);
	void Load(sf::View *view,std::string directory);
	//Update
	void Update(sf::RenderWindow *window,sf::View *view);
	~Battle();
};
#endif