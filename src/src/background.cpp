#include "background.h"

Background::Background(std::string directory) {
	this->tex = new sf::Texture();

	this->tex->loadFromFile(directory);
	this->tex->setRepeated(true);
	this->tex->setSmooth(true);
	
	this->sprite = new sf::Sprite(*tex);
	this->sprite->setScale(gui.width() / 2000., gui.width() / 2000.);
}
void Background::Update(std::string directory) {
	this->tex->loadFromFile(directory);
	this->tex->setRepeated(true);
	this->tex->setSmooth(true);
	this->sprite->setScale(gui.width() / 2000., gui.width() / 2000.);
}
void Background::Render(sf::RenderWindow* window) {
	window->draw(*this->sprite);
}
void Background::move(float x, float y) {
	this->sprite->move(x, y);
}
void Background::setPosition(float x, float y) {
	this->sprite->move(x, y);
}
Background::~Background() {

}
//Variable
Background* background;
