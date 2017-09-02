#include "labelFleet.h"
//Display for fleet
LabelFleet::LabelFleet(short selected){
	this->selected=selected;
	//Label
	this->label=new Label(gui.x,232+gui.y,325,200+25*(::fleet[selected].size()-2),1);
	this->label->setTitle(::player[::fleet[selected].Player()].Name()+getDiplomaticStatus(::fleet[selected].Player()));
	//Text
	std::string text="          "+std::to_string(::fleet[selected].size())+" ships\n          "+::FormationName(::fleet[selected].Formation())+"\n          Provision: "+gui.Format(::fleet[selected].Provision())+"%";
	//Ships
	for(short i=0;i<(short)::fleet[selected].size();i++)
		text+="\n"+naval[::fleet[selected].Ship(i)].Name()+" - "+gui.Format(::fleet[selected].Integrity(i))+"%";
	//Text of label
	this->label->setText(text);
	//Buttons
	this->player=new Button("data/game/icons/"+std::to_string(::fleet[selected].Player())+".png",45+gui.x,322+gui.y);
	if(isYourFleet(this->selected)){
		this->form1=new Button("data/game/formations/0.png",220+gui.x,387+gui.y);
		this->form2=new Button("data/game/formations/1.png",260+gui.x,387+gui.y);
		this->form3=new Button("data/game/formations/2.png",300+gui.x,387+gui.y);
	}
}
void LabelFleet::Render(sf::RenderWindow *window){
	this->label->Render(window);
	this->player->Render(window);
	if(isYourFleet(this->selected)){
		this->form1->Render(window);
		this->form2->Render(window);
		this->form3->Render(window);
	}
}
//Update
bool LabelFleet::FormationUpdate(){
	if(isYourFleet(this->selected)){
		if(this->form1->left(FormationName(0),FormationText(0))){
			::fleet[this->selected].Reform(0);
			return 1;
		}else if(this->form2->left(FormationName(1),FormationText(1))){
			::fleet[this->selected].Reform(1);
			return 1;
		}else if(this->form3->left(FormationName(2),FormationText(2))){
			::fleet[this->selected].Reform(2);
			return 1;
		}	
	}
	return 0;
}
void LabelFleet::move(float x,float y){
	this->label->move(x,y);
	this->player->move(x,y);
	if(::fleet[this->selected].Player()==::human){
		this->form1->move(x,y);
		this->form2->move(x,y);
		this->form3->move(x,y);
	}
}
bool LabelFleet::playerLeft(){
	return this->player->left(::player[::fleet[selected].Player()].Name()+getDiplomaticStatus(::fleet[selected].Player()),"Click to see information about owner of this fleet.");
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
Fleet LabelFleet::fleet(){
	return ::fleet[this->selected];
}
LabelFleet::~LabelFleet(){

}
LabelFleet *labelFleet=NULL;
//Global functions
void deselectFleet(){
	if(labelFleet!=NULL){
		delete labelFleet;
		labelFleet=NULL;
	}
}
void reloadLabelFleet(short i){
	if(isSelectedFleet(i)){
		deselectFleet();
		labelFleet=new LabelFleet(i);
	}
}
bool isSelectedFleet(short i){
	if(labelFleet!=NULL)
		return (i==labelFleet->Selected());
	return 0;
}