#ifndef LABELICON_H
#define LABELICON_H
#include "label.h"

class LabelIcon{
private:
	sf::Texture *tex;
	sf::Sprite *sprite;
	sf::Text *text;
	void Pressed();
public:
	LabelIcon(short x,short y,std::string directory);
	void move(float x,float y);
	void zoom(float factor);
	void setPosition(float x,float y);
	void setText(std::string string);
	//Mouse over
	bool mouseOver();
	bool mouseOver(std::string title,std::string text);
	//Mouse button
	bool left();
	bool right();
	bool left(std::string title,std::string text);
	bool right(std::string title,std::string text);
	void Render(sf::RenderWindow *window);
	~LabelIcon();
};
#endif