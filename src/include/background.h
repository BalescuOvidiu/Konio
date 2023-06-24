#ifndef BACKGROUND_H
#define BACKGROUND_H
#include "audio.h"
//Declaration
class Background{
private:
	sf::Texture *tex;
	sf::Sprite *sprite;
public:
	Background(std::string directory);
	void Update(std::string directory);
	void Render(sf::RenderWindow *window);
	void move(float x,float y);
	void setPosition(float x,float y);
	~Background();
}extern *background;
#endif