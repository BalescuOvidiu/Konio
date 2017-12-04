#include "labelPlayer.h"
//Display for player
LabelPlayer::LabelPlayer(short selected){
	this->label=new Label(32+gui.x,64+gui.y,400,140,1);
	this->select(selected);
}
void LabelPlayer::select(short selected){
	this->select(selected,this->getPosition().x,this->getPosition().y);
}
void LabelPlayer::select(short selected,short x,short y){
	this->selected=selected;
	//Label
	this->label->setTitle(::player[selected].Name()+getDiplomaticStatus(selected));
	//Population and ships
	this->pop=new LabelIcon(5+x,45+y,"data/game/icons/coins.png");
	this->pop->setText(Format(getPopulation(selected)));
	this->ships=new LabelIcon(210+gui.x,45+y,"data/game/icons/coins.png");
	this->ships->setText(Format(getShips(selected)));
	//Economy
	this->coins=new LabelIcon(5+x,75+y,"data/game/icons/coins.png");
	this->coins->setText(Format(::player[selected].Coins()));
	this->income=new LabelIcon(210+gui.x,75+y,"data/game/icons/coins.png");
	this->income->setText(Format(getIncome(selected)));
	//Statistics
	this->statistics=new LabelIcon(5+x,105+y,"data/game/icons/coins.png");
	this->statistics->setText(::player[selected].Statistics());
	//Buttons
	this->shield=new Button("data/game/icons/"+std::to_string(selected)+".png",353+x,95+y);
}
void LabelPlayer::Render(sf::RenderWindow *window){
	this->label->Render(window);
	this->pop->Render(window);
	this->ships->Render(window);
	this->coins->Render(window);
	this->income->Render(window);
	this->statistics->Render(window);
	this->shield->Render(window);
}
void LabelPlayer::move(float x,float y){
	this->label->move(x,y);
	this->pop->move(x,y);
	this->ships->move(x,y);
	this->coins->move(x,y);
	this->income->move(x,y);
	this->statistics->move(x,y);
	this->shield->move(x,y);
}
bool LabelPlayer::right(){
	return this->label->right();
}
bool LabelPlayer::mouseOver(){
	if(this->label->mouseOver()){
		this->pop->mouseOver("Total population","");
		this->ships->mouseOver("Ships","");
		this->coins->mouseOver("Coins","");
		this->income->mouseOver("Income","");
		this->statistics->mouseOver("Won/lost battles","");
		this->shield->mouseOver("Shield","This is symbol of player.");
		return 1;
	}
	return 0;
}
//Get data
short LabelPlayer::Selected(){
	return this->selected;
}
Player LabelPlayer::player(){
	return ::player[this->selected];
}
sf::Vector2f LabelPlayer::getPosition(){
	return this->label->getPosition();
}
LabelPlayer::~LabelPlayer(){

}
//Global variable
LabelPlayer *labelPlayer=NULL;