#ifndef BATTLE_H
#define BATTLE_H
#include "ship.h"
#include "button.h"
#include "layer.h"
//Definition
class Battle{
private:
	//Informational
	std::string name,description;
	//GUI
	sf::Vector2f position;
	sf::Text *text;
	Button *retreat;
	bool pause;
	short selected;
	//AI
	short clock;
	void AI();
	std::vector<std::deque<sf::Vector2f> > target;
	//Water
	Layer *water;
	//Entities
	std::vector<Ship> ship;
	//Ship's points target
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
	Battle(short yourFleet,short enemyFleet,sf::View *view);
	void AddFleet(sf::View *view,short fleet);
	void Render(sf::RenderWindow *window);
	//Update
	std::vector<short> fleets;
	void Update(sf::RenderWindow *window,sf::View *view);
	~Battle();
};
#endif