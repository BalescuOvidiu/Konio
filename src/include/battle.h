#ifndef BATTLE_H
#define BATTLE_H
#include "battleGUI.h"
#include "ship.h"
//Auxiliary structure
struct Team{
	short tactic,ships;
	sf::Vector2f pos;
};
//Definition
class Battle{
private:
	//GUI
	BattleGUI *battleGUI;
	Button *retreat;
	std::vector<sf::Vertex> track;
	bool paused;
	short clock,selected;
	unsigned size;
	//AI
	Team your,enemy;
	void SetTactic(unsigned i,short tactic);
	void Periplous(unsigned i);
	void Diekplous(unsigned i);
	void Kyklos(unsigned i);
	void Attack(unsigned i);
	void AI();
	//Entities
	std::vector<Ship> ship;
	std::vector<std::deque<sf::Vector2f> > target;
	//Ship's points target
	sf::Vector2f local(float dist, float angle, short ship);
	sf::Vector2f localForward(float dist,short ship);
	sf::Vector2f localBackward(float dist,short ship);
	sf::Vector2f localLeft(float dist,short ship);
	sf::Vector2f localRight(float dist,short ship);
	float DistShip(short i,short j);
	bool validPoint(sf::Vector2f point);
	bool canCollide(short i,short j);
	//Teams
	bool isYourShip(short ship);
	bool isYourEnemy(short ship);
	bool isRammedShip(short ship);
	bool isEnemyShip(short i,short j);
	bool isFriendShip(short i,short j);
	//Ships and physics
	void SetTarget(short ship,sf::Vector2f target);
	void Sink(short i);
	void Stop(short ship);
	bool Ramming(short i,short j);
	bool Collision(short i,short j);
	//GUI
	std::string getStatistic();
	bool mouseOverGUI();
	bool Pause();
	void moveView(sf::View *view,float x,float y);
	void moveCamera(sf::RenderWindow *window,sf::View *view);
	void zoom(sf::View *view,float factor);
	//Human ships
	void select(unsigned ship);
	void deselect();
public:
	//Basic
	Battle(short yourFleet,short enemyFleet,sf::View *view);
	void AddFleet(sf::View *view,short fleet,sf::Vector2f pos);
	void Render(sf::RenderWindow *window);
	//Update
	std::vector<short> fleets;
	void Update(sf::RenderWindow *window,sf::View *view);
	~Battle();
};
#endif