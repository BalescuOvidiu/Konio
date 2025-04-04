#include "arrow.h"
//Constructor
Arrow::Arrow(sf::Vector2f position, sf::Vector2f target) {
	this->sprite = new sf::Sprite(arrowTexture);
	this->sprite->setPosition(position);
	this->sprite->setRotation(getAngle(position, target) + rand() % 4 * 5);
	this->distance = dist(position, target);
}
//Render
void Arrow::Render(sf::RenderWindow* window) {
	window->draw(*this->sprite);
}
//Basic
void Arrow::Update() {
	this->sprite->move(
		1.7 * cos(this->getRotationRad()),
		1.7 * sin(this->getRotationRad())
	);
	this->distance -= 1.7;
}
bool Arrow::canHit() {
	return this->distance < 0;
}
//Rotation
void Arrow::rotate(float angle) {
	this->sprite->rotate(angle);
}
void Arrow::setRotation(float angle) {
	this->sprite->setRotation(angle);
}
float Arrow::getRotation() {
	return this->sprite->getRotation();
}
float Arrow::getRotationRad() {
	return this->sprite->getRotation() * 0.017453293;
}
//Points
sf::Vector2f Arrow::getPosition() {
	return this->sprite->getPosition();
}
void Arrow::setPosition(float x, float y) {
	this->sprite->setPosition(x, y);
}
Arrow::~Arrow() {
	delete this->sprite;
}
//Texture
sf::Texture arrowTexture;