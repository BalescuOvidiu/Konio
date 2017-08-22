#include "labelSett.h"
//Display for settlement
LabelSett::LabelSett(short selected){
	this->selected=selected;
	//Label
	this->label=new Label(gui.x,232+gui.y,320,140,1);
	this->label->setTitle(::settlement[selected].getName()+getDiplomaticStatus(::settlement[selected].getPlayer()));
	this->label->setText("               "+std::to_string(::settlement[selected].getPopulation())+" freemen");
	//Buttons
	this->local=new Button("data/game/goods/"+std::to_string(::settlement[selected].getGood())+".png",160+gui.x,342+gui.y);
	this->import=new Button("data/game/goods/"+std::to_string(getImportedGood(selected))+".png",260+gui.x,342+gui.y);
	//Player of settlement
	if(::settlement[selected].getOccupied()==-1)
		this->player=new Button("data/game/icons/"+std::to_string(::settlement[selected].getPlayer())+".png",45+gui.x,322+gui.y);
	else
		this->player=new Button("data/game/icons/"+std::to_string(::settlement[selected].getOccupied())+".png",45+gui.x,322+gui.y);
}
void LabelSett::Render(sf::RenderWindow *window){
	this->label->Render(window);
	this->player->Render(window);
	this->local->Render(window);
	this->import->Render(window);
}
void LabelSett::move(float x,float y){
	this->label->move(x,y);
	this->player->move(x,y);
	this->local->move(x,y);
	this->import->move(x,y);
}
bool LabelSett::playerLeft(){
	return this->player->left();
}
bool LabelSett::localMouseOver(){
	return this->local->mouseOver();
}
bool LabelSett::importMouseOver(){
	return this->import->mouseOver();
}
bool LabelSett::importLeft(){
	return this->import->left();
}
bool LabelSett::right(){
	return this->label->right();
}
bool LabelSett::mouseOver(){
	return this->label->mouseOver();
}
//Get data
short LabelSett::Selected(){
	return this->selected;
}
LabelSett::~LabelSett(){

}
//Global variable for GUI
LabelSett *labelSett=NULL;
//Deselect function
void deselectSett(){
	if(labelSett!=NULL){
		delete labelSett;
		labelSett=NULL;
	}
}