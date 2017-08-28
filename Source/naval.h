#ifndef NAVAL_H
#define NAVAL_H

#include "entity.h"
//Naval
class Naval:Entity{
private:
	sf::Texture ram,rows;
	float cost;
	short rowers;
public:
	Naval(short id);
	//Get data
	std::string Name();
	std::string Description();
	float Speed();
	float Cost();
	short Rowers();
	//Size
	short width();
	short widthRows();
	short height();
	//Texture
	sf::Texture& Body();
	sf::Texture& Ram();
	sf::Texture& Rows();
	//Load texture
	void loadTexture(short id);
};
//Gameplay global variable
extern std::vector<Naval> naval;
extern sf::Texture sails;
#endif