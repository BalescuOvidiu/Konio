#ifndef REGION_H
#define REGION_H

#include "layer.h"
#include "button.h"
class Region{
private:
	sf::Text *name;
public:
	//Basic
	Region(short x,short y,short size,std::string name);
	void Render(sf::RenderWindow *window);
	//Update
	void Update();
	//Get data
	std::string getName();
	//Delete
	~Region();
};
#endif