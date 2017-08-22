#include "labelPlayer.h"
//Display for player
LabelPlayer::LabelPlayer(short selected){
	this->selected=selected;
	//Label
	this->label=new Label(gui.x,232+gui.y,320,140,1);
	this->label->setTitle(::player[selected].Name()+getDiplomaticStatus(selected));
	if(selected==human)
		this->label->setText("               "+std::to_string(getShips(selected))+" ships");
	else
		this->label->setText("               "+::player[selected].Coins()+" coins \n               "+std::to_string(getPopulation(selected))+" freemen\n               "+std::to_string(getShips(selected))+" ships");
	//Buttons
	this->player=new Button("data/game/icons/"+std::to_string(selected)+".png",45+gui.x,322+gui.y);
}
void LabelPlayer::Render(sf::RenderWindow *window){
	this->label->Render(window);
	this->player->Render(window);
}
void LabelPlayer::move(float x,float y){
	this->label->move(x,y);
	this->player->move(x,y);
}
bool LabelPlayer::right(){
	return this->label->right();
}
bool LabelPlayer::mouseOver(){
	return this->label->mouseOver();
}
//Get data
short LabelPlayer::Selected(){
	return this->selected;
}
LabelPlayer::~LabelPlayer(){

}
//Global variable
LabelPlayer *labelPlayer=NULL;
//Deselect function
void deselectPlayer(){
	if(labelPlayer!=NULL){
		delete labelPlayer;
		labelPlayer=NULL;
	}
}