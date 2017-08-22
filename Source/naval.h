#ifndef NAVAL_H
#define NAVAL_H

#include "entity.h"
//Naval
struct Naval:Entity{
	sf::Texture ram,rows;
	short rowers,rowsWidth;
};
//Overload reading from file
std::ifstream &operator>>(std::ifstream &in,Naval &naval);
//Gameplay
extern std::vector<Naval> naval;
extern sf::Texture sails;
#endif