#ifndef SUBMENU_H
#define SUBMENU_H
#include "options.h"

class SubMenu{
private:
	bool visible;
	Button *resume,*campaign,*options,*exit;
public:
	SubMenu();
	void Render(sf::RenderWindow *window);
	void Update(sf::RenderWindow *window);
	void show();
	void hide();
	void move(float x,float y);
	void setPosition(float x,float y);
	operator bool();
	~SubMenu();
}extern *subMenu;
#endif