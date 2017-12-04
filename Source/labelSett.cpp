#include "labelSett.h"
//Display for settlement
LabelSett::LabelSett(short selected){
	this->label=new Label(32+gui.x,64+gui.y,400,140,1);
	this->select(selected);
}
void LabelSett::select(short selected){
	this->select(selected,this->getPosition().x,this->getPosition().y);
}
void LabelSett::select(short selected,short x,short y){
	this->L=this->I=0;
	this->recruit.clear();
	this->selected=selected;
	//Label
	this->label->setTitle(this->sett().getName());
	//Population
	this->pop=new LabelIcon(5+x,75+y,"data/game/icons/coins.png");
	this->pop->setText(this->sett().getPopulationString());
	this->growth=new LabelIcon(5+x,45+y,"data/game/icons/coins.png");
	this->growth->setText(this->sett().getGrowthString());
	//Economy
	this->income=new LabelIcon(128+x,45+y,"data/game/icons/coins.png");
	this->income->setText(Format(getIncomeOf(selected)));
	//Military
	if(isYourSett(selected)){
		for(short i=0;i<2+hasGood(selected,1);i++){
			recruit.push_back(Button("data/game/icons/naval/"+Format(i+3*(!hasGood(selected,1)))+".png",x+15+45*i,y+120));
			if(!canRecruit(i+3*(!hasGood(selected,1)),selected))
				this->recruit[i].setColor(sf::Color(220,80,40));
		}
	}else{
		this->dip=new LabelIcon(5+x,105+y,"data/game/icons/coins.png");
		this->dip->setText(PlayerInfo(this->sett().getOwner()));
	}
	//Import
	if(hasImport(selected)){
		this->import=new Button("data/game/goods/"+std::to_string(getImportedGood(selected))+".png",338+x,30+y);
		this->Import=getGuide(
			this->sett().getPosition(),
			getTradeRoute(this->selected,this->sett().getImport()),
			sf::Color(220,220,220)
		);
	}
	//Local and export
	if(hasImport(selected)){
		this->Export=getGuide(
			this->sett().getPosition(),
			getTradeRoute(this->selected,getImporter(selected)),
			sf::Color(220,220,220)
		);
	}
	this->local=new Button("data/game/goods/"+std::to_string(this->sett().getGood())+".png",374+x,30+y);
	//Player of settlement
	this->player=new Button("data/game/icons/"+std::to_string(this->sett().getOwner())+".png",353+x,95+y);
	//Range
	this->range=new sf::CircleShape(90,64);
	this->range->setFillColor(sf::Color(220,220,220,64));
	this->range->setOutlineColor(sf::Color(220,220,220,100));
	this->range->setOutlineThickness(1);
	this->range->setPosition(this->sett().getPosition().x-90,this->sett().getPosition().y-90);
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
	if(isYourSett(selected))
		for(unsigned i=0;i<recruit.size();i++)
			this->recruit[i].Render(window);
	else
		this->dip->Render(window);
}
void LabelSett::RenderGuides(sf::RenderWindow *window){
	window->draw(*this->range);
	if(this->import->mouseOver()){
		if(this->Export.size())
			window->draw(&this->Export[0],this->Export.size(),sf::Quads);
		if(this->Import.size())
			window->draw(&this->Import[0],this->Import.size(),sf::Quads);
	}else{
		if(this->Import.size())
			window->draw(&this->Import[0],this->Import.size(),sf::Quads);
		if(this->Export.size())
			window->draw(&this->Export[0],this->Export.size(),sf::Quads);		
	}
}
void LabelSett::move(float x,float y){
	this->label->move(x,y);
	this->player->move(x,y);
	this->pop->move(x,y);
	this->growth->move(x,y);
	this->local->move(x,y);
	this->import->move(x,y);
	this->income->move(x,y);
	if(isYourSett(selected))
		for(unsigned i=0;i<recruit.size();i++)
			this->recruit[i].move(x,y);
	else
		this->dip->move(x,y);
}
bool LabelSett::playerLeft(){
	return this->player->left(PlayerInfo(::settlement[this->selected].getOwner()),"Click to see information about owner of this settlement.");
}
bool LabelSett::localLeft(){
	if(this->Export.size()){
		if(this->local->mouseOver()!=L){
			L=!L;
			this->Export=setGuideColor(this->Export,sf::Color(220-L*40,220-L*40,220-L*140));
		}
		return this->local->left(ExportedGoodStatus(this->selected),goodDescription(this->sett().getGood()));

	}
	this->local->mouseOver(::good[this->sett().getGood()].Name(),goodDescription(this->sett().getGood()));
	return 0;
}
bool LabelSett::importLeft(){
	if(this->sett().getImport()<(short)::settlement.size()){
		if(this->import->mouseOver()!=I){
			I=!I;
			this->Import=setGuideColor(this->Import,sf::Color(220-I*40,220-I*40,220-I*140));
		}
		return this->import->left(ImportedGoodStatus(this->selected),goodDescription(getImportedGood(this->selected)));
	}
	return 0;
}
bool LabelSett::right(){
	return this->label->right();
}
bool LabelSett::mouseOver(){
	if(this->label->mouseOver()){
		this->income->mouseOver("Income","");
		this->pop->mouseOver("Population","");
		this->growth->mouseOver("Growth","");
		if(!isYourSett(selected))
			this->dip->mouseOver("Diplomacy","");
		return 1;
	}
	return 0;
}
short LabelSett::Ship(){
	for(unsigned i=0;i<recruit.size();i++){
		short id=i+3*(!hasGood(this->selected,1));
		if(canRecruit(id,this->selected)){
			if(this->recruit[i].left(naval[id].Name(),naval[id].Description())){
				return id;
			}
		}else if(this->recruit[i].mouseOver(naval[id].Name(),naval[id].Description()))
			break;
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
sf::Vector2f LabelSett::getPosition(){
	return this->label->getPosition();
}
LabelSett::~LabelSett(){

}
//Global variable for GUI
LabelSett *labelSett=NULL;