#include "labelDip.h"
//Display for player
LabelDip::LabelDip(){
	//Label
	this->label=new Label(gui.x+464,gui.y+64,400,50+(::player.size()*25),1);
	this->label->setTitle("Diplomacy");
	//Buttons
	for(unsigned i=0;i<::player.size();i++)
		this->player.push_back(Button("data/game/icons/"+std::to_string(i)+".png",gui.x+514+100*i%400,gui.y+164+100*(short)(i/4)));
}
void LabelDip::Render(sf::RenderWindow *window){
	this->label->Render(window);
	for(unsigned i=0;i<player.size();i++)
		this->player[i].Render(window);
}
short LabelDip::Update(){
	for(unsigned i=player.size();i--;){
		if(this->player[i].left(::player[i].Name()+getDiplomaticStatus(i),getDataPlayer(i)))
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
	for(unsigned i=player.size();i--;)
		this->player[i].setColor(sf::Color(255,255,255));
	for(unsigned i=player.size();i--;){
		if(this->player[i].mouseOver()){
			for(unsigned j=player.size();j--;){
				if(areAllies(i,j)&&i!=j)
					this->player[j].setColor(sf::Color(60,255,100));
				else if(areEnemies(i,j))
					this->player[j].setColor(sf::Color(255,100,60));
				else
					this->player[j].setColor(sf::Color(255,255,255));
			}
			return 0;
		}
	}
	return this->label->right();
}
bool LabelDip::mouseOver(){
	return this->label->mouseOver();
}
LabelDip::~LabelDip(){
	this->player.clear();
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