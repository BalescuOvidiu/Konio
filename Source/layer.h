#ifndef LAYER_H
#define LAYER_H
#include "audio.h"

class Layer{
private:
	short clock,speed,width;
	sf::RectangleShape *rectangle;
	sf::Texture *tex;
	std::string directory;
public:
	Layer(short speed,short width,std::string directory);
	void move(float x,float y);
	void zoom(float factor);
	void Update();
	void Reset();
	void Render(sf::RenderWindow *window);
	~Layer();
};
#endif