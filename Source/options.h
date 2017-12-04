#ifndef OPTIONS_H
#define OPTIONS_H
#include "button.h"
#include "value.h"
#include "label.h"
#include "layer.h"

class Options{
private:
	bool visible;
	Button *close;
	Value *music,*sound;
public:
	Options();
	void Render(sf::RenderWindow *window);
	void Update();
	void show();
	void hide();
	void move(float x,float y);
	void setPosition(float x,float y);
	void reset();
	operator bool();
	~Options();
}extern *op;
#endif