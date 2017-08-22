#ifndef BUTTON_H
#define BUTTON_H
#include "label.h"

class Button{
private:
	sf::Texture *tex;
	sf::Sprite *sprite;
public:
	Button(std::string directory,short x,short y);
	Button(short x,short y,std::string directory);
	Button(short x,short y,short width,std::string directory);
	void Render(sf::RenderWindow *window);
	void move(float x,float y);
	void setPosition(float x,float y);
	bool mouseOver();
	bool mouseOver(std::string title,std::string text);
	bool left();
	bool right();
	bool left(std::string title,std::string text);
	bool right(std::string title,std::string text);
	~Button();
};
#endif