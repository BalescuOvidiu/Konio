#ifndef MENU_H
#define MENU_H
#include "options.h"
#include "background.h"

class Menu{
private:
	Button *play,*history,*options,*exit;
public:
	Menu();
	void Render(sf::RenderWindow *window);
	void Update(sf::RenderWindow *window);
	~Menu();
}extern *menu;
#endif