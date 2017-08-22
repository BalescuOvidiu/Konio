#include "labelFleet.h"
//Display for fleet
LabelFleet::LabelFleet(short selected){
	this->selected=selected;
	//Label
	this->label=new Label(gui.x,232+gui.y,320,140,1);
	this->label->setTitle(::player[::fleet[selected].Player()].Name()+getDiplomaticStatus(::fleet[selected].Player()));
	this->label->setText("");
	//Buttons
	this->player=new Button("data/game/icons/"+std::to_string(::fleet[selected].Player())+".png",45+gui.x,322+gui.y);
}
void LabelFleet::Render(sf::RenderWindow *window){
	this->label->Render(window);
	this->player->Render(window);
}
void LabelFleet::move(float x,float y){
	this->label->move(x,y);
	this->player->move(x,y);
}
bool LabelFleet::right(){
	return this->label->right();
}
bool LabelFleet::mouseOver(){
	return this->label->mouseOver();
}
//Get data
short LabelFleet::Selected(){
	return this->selected;
}
LabelFleet::~LabelFleet(){

}
LabelFleet *labelFleet=NULL;
//Deselect function
void deselectFleet(){
	if(labelFleet!=NULL){
		delete labelFleet;
		labelFleet=NULL;
	}
}