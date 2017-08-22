#ifndef GOOD_H
#define GOOD_H
#include "gui.h"

class Good{
private:
	std::string name;
	short price;
public:
	Good(std::string name,short price);
	//Get data
	std::string Name();
	short Price();
	~Good();
};
//Load description
std::string goodDescription(short id);
//Global variable
extern std::vector<Good> good;
#endif