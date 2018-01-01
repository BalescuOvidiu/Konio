#ifndef SHIP_H
#define SHIP_H
#include "marine.h"
//Ship
class Ship{
private:
	//Extern data
	short fleet,marines,rank,id;
	//Move
	float speed,integrity,clock,floating;
	float rotationSpeed;
	//Sprites
	sf::Sprite *body,*ram,*rows,*sails;
	std::vector<sf::Vertex> strings;
public:
	//Soldiers
	std::vector<Marine> marine;
	//Constructor
	Ship(short fleet,short rank,short id,short faction,short x,short y,float angle);
	//Render
	void RenderBody(sf::RenderWindow *window);
	void RenderRam(sf::RenderWindow *window);
	void RenderRows(sf::RenderWindow *window);
	void RenderSails(sf::RenderWindow *window);
	//Basic
	void setString();
	void setColor(sf::Color color);
	void rankDown();
	//Rotation
	void rotate(float angle);
	void setRotation(float angle);
	float getRotation();
	float getRotationRad();
	//Points
	void setPosition(float x,float y);
	void setPositionMarines();
	float Dist(sf::Vector2f point);
	float Dist(Ship ship);
	float DistFront(sf::Vector2f point);
	float DistFront(Ship ship);
	float DistBack(sf::Vector2f point);
	float DistBack(Ship ship);
	//Collision
	bool contains(sf::Vector2f point);
	sf::Vector2f Origin();
	sf::Vector2f A();
	sf::Vector2f B();
	//Front points
	sf::Vector2f Ram();
	sf::Vector2f Front();
	sf::Vector2f FrontLeft();
	sf::Vector2f FrontRight();
	//Back points
	sf::Vector2f Back();
	sf::Vector2f BackLeft();
	sf::Vector2f BackRight();
	//Side points
	sf::Vector2f Left();
	sf::Vector2f Right();
	//Sails points
	sf::Vector2f SailsLeft();
	sf::Vector2f SailsRight();
	sf::Vector2f StringsFront();
	sf::Vector2f StringsBack();
	sf::Vector2f StringsLeft();
	sf::Vector2f StringsRight();
	//Mouse
	bool mouseOver();
	bool left();
	bool right();
	//Main data
	std::string getDetails();
	bool Stopped();
	//Float
	bool FloatBody();
	bool FloatRam();
	bool FloatRows();
	bool FloatSails();
	bool Float();
	//Data
	float Integrity();
	float RotationSpeed();
	float SpeedMax();
	float SpeedOnFrame();
	float Speed();
	float SpeedRatio();
	float Power();
	float Floating();
	short Direction();
	short Fleet();
	short Player();
	short Rank();
	short Id();
	//Size
	short width();
	short widthRows();
	short height();
	sf::Vector2f getSize();
	//Move
	bool move(sf::Vector2f target);
	void push(float x,float y);
	void Speed(float speed);
	void Rows(float clock);
	//Fight
	void marineDeath();
	void takeDamage(float damage);
	bool sink();
	~Ship();
};
#endif