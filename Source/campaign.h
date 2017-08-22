#ifndef CAMPAIGN_H
#define CAMPAIGN_H

#include "game.h"

class Campaign{
private:
	Button *menu;
	std::vector<Button> button;
public:
	Game *game;
	Campaign();	
	void Render(sf::RenderWindow *window);
	void Update(sf::View *view);
	~Campaign();
};
#endif