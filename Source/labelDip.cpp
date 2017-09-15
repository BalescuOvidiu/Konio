#include "labelDip.h"
//Display for player
LabelDip::LabelDip(){
	//Label
	this->label=new Label(gui.x+gui.width(50)-300,gui.y+gui.height(50)-200,600,250,1);
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
short LabelDip::Update(){
	for(short i=0;i<(short)player.size();i++){
		//Select
		if(this->player[i].left(::player[i].Name()+getDiplomaticStatus(i),""))
			return i;
	}
	return -1;
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
LabelDip::~LabelDip(){

}
//Global variable
LabelDip *labelDip=NULL;
//Global functions
void deselectDip(){
	delete labelDip;
	labelDip=NULL;
}
void reloadLabelDip(){
	if(labelDip!=NULL){
		delete labelDip;
		labelDip=NULL;
		labelDip=new LabelDip();
	}
}