#ifndef ENTITY_H
#define ENTITY_H

#include "gui.h"

struct Basic{
	std::string name;
	short speed;
};
struct Entity{
	Basic basic;
	sf::Texture body;
};
//Overload reading from file
std::ifstream &operator>>(std::ifstream &in,Basic &basic);
std::ifstream &operator>>(std::ifstream &in,Entity &entity);
#endif