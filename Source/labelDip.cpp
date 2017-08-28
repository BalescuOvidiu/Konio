#include "labelDip.h"
//Display for player
LabelDip::LabelDip(){
	this->selected=-1;
	//Label
	this->label=new Label(gui.x+gui.width(50)-300,gui.y+gui.height(50)-200,600,400,1);
	this->label->setTitle("Diplomacy");
	//Buttons
	for(short i=0;i<(short)::player.size();i++)
		this->player.push_back(Button("data/game/icons/"+std::to_string(i)+".png",gui.x+gui.width(50)-250+100*i%600,gui.y+gui.height(50)-100+100*(short)(i/6)));
}
void LabelDip::Render(sf::RenderWindow *window){
	this->label->Render(window);
	for(short i=0;i<(short)player.size();i++)
		this->player[i].Render(window);
}
void LabelDip::Update(){
	for(short i=0;i<(short)player.size();i++){
		//Select
		if(this->player[i].left())
			this->showData(i);
		//Deselect
		if(this->player[i].right()&&this->selected==i)
			this->label->setText("");
	}
}
void LabelDip::move(float x,float y){
	this->label->move(x,y);
	for(short i=0;i<(short)player.size();i++)
		this->player[i].move(x,y);
}
bool LabelDip::right(){
	for(short i=0;i<(short)player.size();i++)
		if(this->player[i].mouseOver())
			return 0;
	return this->label->right();
}
bool LabelDip::mouseOver(){
	return this->label->mouseOver();
}
//Get data
short LabelDip::Selected(){
	return this->selected;
}
//Show data
void LabelDip::showData(short player){
	this->selected=player;
	this->label->setText("\n\n\n\n\n\n\n\n\n"+::player[player].Name()+getDiplomaticStatus(player)+"\n"+gui.Format(::player[player].Coins())+" coins\n"+std::to_string(getPopulation(player))+" freeman\n"+std::to_string(getShips(player))+" ships");
}
LabelDip::~LabelDip(){

}
//Global variable
LabelDip *labelDip=NULL;
//Global function
void deselectDip(){
	delete labelDip;
	labelDip=NULL;
}