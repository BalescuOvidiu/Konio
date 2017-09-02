#include "labelSett.h"
//Display for settlement
LabelSett::LabelSett(short selected){
	this->selected=selected;
	//Label
	this->label=new Label(gui.x,232+gui.y,325,180,1);
	this->label->setTitle(::settlement[selected].getName());
	//Human settlement
	if(isYourSett(selected)){
		//Navy buttons
		if(hasGood(selected,1)){
			first=new Button("data/game/icons/naval/0.png",220+gui.x,387+gui.y);
			second=new Button("data/game/icons/naval/1.png",260+gui.x,387+gui.y);
			third=new Button("data/game/icons/naval/2.png",300+gui.x,387+gui.y);
		}else{
			first=new Button("data/game/icons/naval/3.png",260+gui.x,387+gui.y);
			second=new Button("data/game/icons/naval/4.png",300+gui.x,387+gui.y);
			third=NULL;
		}
		//Label
		this->label->setText(::settlement[selected].getText()+"\n          "+gui.Format(getIncomeOf(selected))+" income");
	//AI settlement
	}else{
		//Label
		this->label->setText(::settlement[selected].getText()+"\n          "+gui.Format(getIncomeOf(selected))+" income\n          "+::player[::settlement[selected].getOwner()].Name()+getDiplomaticStatus(::settlement[selected].getOwner()));
	}
	//Goods
	this->local=new Button("data/game/goods/"+std::to_string(::settlement[selected].getGood())+".png",25+gui.x,387+gui.y);
	this->import=new Button("data/game/goods/"+std::to_string(getImportedGood(selected))+".png",65+gui.x,387+gui.y);
	//Player of settlement
	this->player=new Button("data/game/icons/"+std::to_string(::settlement[selected].getOwner())+".png",45+gui.x,322+gui.y);
}
void LabelSett::Render(sf::RenderWindow *window){
	this->label->Render(window);
	//Informational
	this->player->Render(window);
	this->local->Render(window);
	this->import->Render(window);
	//Navy buttons
	if(isYourSett(selected)){
		if(hasGood(selected,1)){
			this->first->Render(window);
			this->second->Render(window);
			this->third->Render(window);
		}else{
			this->first->Render(window);
			this->second->Render(window);
		}
	}
}
void LabelSett::move(float x,float y){
	this->label->move(x,y);
	this->player->move(x,y);
	this->local->move(x,y);
	this->import->move(x,y);
	//Navy buttons
	if(isYourSett(selected)){
		if(hasGood(selected,1)){
			this->first->move(x,y);
			this->second->move(x,y);
			this->third->move(x,y);
		}else{
			this->first->move(x,y);
			this->second->move(x,y);
		}
	}
}
bool LabelSett::playerLeft(){
	return this->player->left(::player[::settlement[selected].getPlayer()].Name()+getDiplomaticStatus(::settlement[selected].getPlayer()),"Click to see information about owner of this settlement.");
}
bool LabelSett::localMouseOver(){
	return this->local->mouseOver();
}
bool LabelSett::localLeft(){
	return this->local->left();
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
short LabelSett::getShip(){
	//Navy buttons
	if(isYourSett(selected)){
		if(hasGood(selected,1)){
			if(this->first->left(naval[0].Name(),naval[0].Description())){
				return 0;
			}
			if(this->second->left(naval[1].Name(),naval[1].Description())){
				return 1;
			}
			if(this->third->left(naval[2].Name(),naval[2].Description())){
				return 2;
			}
		}else{
			if(this->first->left(naval[3].Name(),naval[3].Description())){
				return 3;
			}
			if(this->second->left(naval[4].Name(),naval[4].Description())){
				return 4;
			}
		}
	}
	return -1;
}
//Get data
short LabelSett::Selected(){
	return this->selected;
}
Settlement LabelSett::sett(){
	return ::settlement[this->selected];
}
LabelSett::~LabelSett(){

}
//Global variable for GUI
LabelSett *labelSett=NULL;
//Global functions
void deselectSett(){
	if(labelSett!=NULL){
		delete labelSett;
		labelSett=NULL;
	}
}
void reloadLabelSett(short i){
	if(isSelectedSett(i)){
		deselectSett();
		labelSett=new LabelSett(i);
	}
}
bool isSelectedSett(short i){
	if(labelSett!=NULL)
		return (i==labelSett->Selected());
	return 0;
}