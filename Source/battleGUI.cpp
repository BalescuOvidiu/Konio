#include "battleGUI.h"
//Constructor
BattleGUI::BattleGUI(std::string data){
	//Black rectangle
	this->rectangle=new sf::RectangleShape(sf::Vector2f(gui.width(),32));
	this->rectangle->setPosition(0,0);
	this->rectangle->setFillColor(sf::Color(0,0,0,200));
	//Game data
	this->ships=new LabelIcon(5,0,"data/game/icons/population.png");
	this->details=new LabelIcon(115,0,"data/game/icons/zero.png");
	this->details->setText("");
	//Text
	this->Reload(data);
}
//Render
void BattleGUI::Render(sf::RenderWindow *window){
	window->draw(*this->rectangle);
	this->ships->Render(window);
	this->details->Render(window);
}
//Update
void BattleGUI::Reload(std::string data){
	this->ships->setText(data);
}
void BattleGUI::ReloadDetails(std::string data){
	if(data=="")
		this->details=new LabelIcon(115+gui.x,0+gui.y,"data/game/icons/zero.png");
	else
		this->details=new LabelIcon(115+gui.x,0+gui.y,"data/game/icons/player.png");
	this->details->setText(data);
	this->details->zoom(gui.factor);
}
void BattleGUI::move(float x,float y){
	this->rectangle->move(x,y);
	//Game data
	this->ships->move(x,y);
	this->details->move(x,y);
}
void BattleGUI::zoom(float factor){
	//Rectangle
	this->rectangle->setPosition(gui.zoomed(this->rectangle->getPosition(),factor));
	this->rectangle->setSize(sf::Vector2f(this->rectangle->getSize().x*factor,this->rectangle->getSize().y*factor));
	//Icons
	this->ships->zoom(factor);
	this->details->zoom(factor);
}
bool BattleGUI::mouseOver(){
	this->ships->mouseOver("Ships","That is report of battles.\nIf ships is too big for you use Q and E to zoom in/out.");
	this->details->mouseOver("Details","That is your selected ship.");
	return (this->rectangle->getGlobalBounds().contains(gui.mouseCoordinates().x,gui.mouseCoordinates().y));
}
//Destructor
BattleGUI::~BattleGUI(){
	
}