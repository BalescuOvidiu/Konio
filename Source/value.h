#ifndef VALUE_H
#define VALUE_H
#include "label.h"

class Value{
private:
	sf::Texture *tex;
	sf::Sprite *sprite;
	sf::Text *text;
public:
	Value(short x,short y,short width,std::string directory);
	void move(float x,float y);
	void setPosition(float x,float y);
	bool mouseOver();
	bool left();
	bool right();
	bool Update(float &value,float min,short max,float step,short type,std::string title,std::string text);
	void Render(sf::RenderWindow *window);
	~Value();
};
#endif