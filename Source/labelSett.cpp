#include "labelSett.h"
//Display for settlement
LabelSett::LabelSett(short selected){
	this->selected=selected;
	//Label
	this->label=new Label(gui.x,180+gui.y,325,140,1);
	this->label->setTitle(::settlement[selected].getName());
	//Population
	this->pop=new LabelIcon(5+gui.x,255+gui.y,"data/game/icons/coins.png");
	this->pop->setText(::settlement[selected].getPopulationString());
	this->growth=new LabelIcon(5+gui.x,225+gui.y,"data/game/icons/coins.png");
	this->growth->setText(::settlement[selected].getGrowthString());
	//Economy
	this->income=new LabelIcon(130+gui.x,225+gui.y,"data/game/icons/coins.png");
	this->income->setText(gui.Format(getIncomeOf(selected)));
	//Military
	if(isYourSett(selected))
		recruit=new Button("data/game/icons/naval/3.png",220+gui.x,210+gui.y);
	//Goods
	this->local=new Button("data/game/goods/"+std::to_string(::settlement[selected].getGood())+".png",260+gui.x,210+gui.y);
	this->import=new Button("data/game/goods/"+std::to_string(getImportedGood(selected))+".png",300+gui.x,210+gui.y);
	//Player of settlement
	this->dip=new LabelIcon(5+gui.x,285+gui.y,"data/game/icons/coins.png");
	this->dip->setText(PlayerInfo(::settlement[selected].getPlayer()));
	this->player=new Button("data/game/icons/"+std::to_string(::settlement[selected].getOwner())+".png",275+gui.x,275+gui.y);
}
void LabelSett::Render(sf::RenderWindow *window){
	this->label->Render(window);
	//Informational
	this->player->Render(window);
	this->local->Render(window);
	this->import->Render(window);
	this->income->Render(window);
	this->pop->Render(window);
	this->growth->Render(window);
	this->dip->Render(window);
	if(isYourSett(this->selected))
		this->recruit->Render(window);
}
void LabelSett::move(float x,float y){
	this->label->move(x,y);
	this->dip->move(x,y);
	this->player->move(x,y);
	this->pop->move(x,y);
	this->growth->move(x,y);
	this->local->move(x,y);
	this->import->move(x,y);
	this->income->move(x,y);
	if(isYourSett(this->selected))
		this->recruit->move(x,y);
}
bool LabelSett::playerLeft(){
	return this->player->left(PlayerInfo(::settlement[this->selected].getPlayer()),"Click to see information about owner of this settlement.");
}
bool LabelSett::localLeft(){
	return this->local->left(ExportedGoodStatus(this->selected),goodDescription(this->sett().getGood()));
}
bool LabelSett::importLeft(){
	return this->import->left(ImportedGoodStatus(this->selected),goodDescription(getImportedGood(this->selected)));
}
bool LabelSett::right(){
	return this->label->right();
}
bool LabelSett::mouseOver(){
	return this->label->mouseOver();
}
short LabelSett::getShip(){
	//Navy buttons
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