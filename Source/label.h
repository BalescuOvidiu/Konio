#ifndef LABEL_H
#define LABEL_H
#include "audio.h"

class Label{
private:
	bool visible;
	sf::RectangleShape *rectangle;
	sf::Text *title,*text;
public:
	Label(short x,short y,short width,short height,bool visible);
	void move(float x,float y);
	void setPosition(float x,float y);
	void setTitle(std::string string);
	void setText(std::string string);
	void setSize(short width,short height);
	void reset();
	void hide();
	void show();
	void show(std::string title,std::string text);
	bool mouseOver();
	bool left();
	bool right();
	void Render(sf::RenderWindow *window);
	operator bool();
	~Label();
}extern about,detail,info;
#endif