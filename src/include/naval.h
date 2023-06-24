#ifndef NAVAL_H
#define NAVAL_H

#include "entity.h"
//Naval
class Naval:Entity{
private:
	sf::Texture ram,rows;
	float cost;
	short rowers,marines;
public:
	Naval(std::string directory);
	//Get data
	std::string Name();
	std::string Description();
	float Speed();
	float Cost();
	float Upkeep();
	float Power();
	short Rowers();
	short Marines();
	short Men();
	//Size
	short width();
	short widthRows();
	short height();
	//Texture
	sf::Texture& Body();
	sf::Texture& Ram();
	sf::Texture& Rows();
};
//Gameplay global variable
extern std::vector<Naval> naval;
extern sf::Texture sails;
extern short mercenaries;
//Get functions
#endif