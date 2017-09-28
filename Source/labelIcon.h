#ifndef LABELICON_H
#define LABELICON_H
#include "label.h"

class LabelIcon{
private:
	sf::Texture *tex;
	sf::Sprite *sprite;
	sf::Text *text;
public:
	LabelIcon(short x,short y,std::string directory);
	void move(float x,float y);
	void setPosition(float x,float y);
	void setText(std::string string);
	bool mouseOver();
	bool mouseOver(std::string title,std::string text);
	bool left();
	bool right();
	void Render(sf::RenderWindow *window);
	~LabelIcon();
};
#endif