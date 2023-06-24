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
	this->id.clear();
	this->recruit.clear();
	this->Export.clear();
	this->Import.clear();
	this->selected=selected;
	//Label
	this->label->setTitle(this->sett().getName());
	//Population
	this->pop=new LabelIcon(5+x,75+y,"data/game/icons/population.png");
	this->pop->setText(this->sett().getPopulationString());
	//Growth population
	if(this->sett().getGrowth()>0)
		this->growth=new LabelIcon(10+x,45+y,"data/game/icons/up.png");
	else if(this->sett().getGrowth()<0)
		this->growth=new LabelIcon(10+x,45+y,"data/game/icons/down.png");
	else
		this->growth=new LabelIcon(10+x,45+y,"data/game/icons/null.png");
	this->growth->setText(this->sett().getGrowthString());
	//Economy
	this->income=new LabelIcon(128+x,45+y,"data/game/icons/coins.png");
	this->income->setText(Format(getIncomeOf(selected)));
	//Military
	if(isYourSett(selected)){
		for(unsigned i=0;i<naval.size();i++){
			if(isRecruitable(i,selected)){
				this->recruit.push_back(Button("data/game/icons/naval/"+Format(i)+".png",x+15+45*id.size(),y+120));
				this->id.push_back(i);
				if(!canRecruit(i,selected))
					this->recruit.back().setColor(sf::Color(220,80,40));
			}
		}
	}else{
		this->dip=new LabelIcon(5+x,105+y,"data/game/icons/player.png");
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
	if(hasExport(selected)){
		this->Export=getGuide(
			this->sett().getPosition(),
			getTradeRoute(this->selected,getImporter(selected)),
			sf::Color(220,220,220)
		);
	}
	this->local=new Button("data/game/goods/"+std::to_string(this->sett().getGood())+".png",374+x,30+y);
	//Owner of settlement
	this->player=new Button("data/game/icons/"+std::to_string(this->sett().getOwner())+".png",353+x,95+y);
	//Range
	this->range=new sf::CircleShape(this->sett().getRange(),64);
	this->range->setFillColor(sf::Color(220,220,220,64));
	this->range->setOutlineColor(sf::Color(220,220,220,100));
	this->range->setOutlineThickness(1);
	this->range->setPosition(this->sett().getRangePosition());
}
void LabelSett::Render(sf::RenderWindow *window){
	this->label->Render(window);
	//Informational
	this->player->Render(window);
	this->local->Render(window);
	if(hasImport(this->selected))
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
	if(hasImport(this->selected)){
		if(this->import->mouseOver()){
			window->draw(&this->Export[0],this->Export.size(),sf::Quads);
			if(this->Import.size())
				window->draw(&this->Import[0],this->Import.size(),sf::Quads);
		}else{
			window->draw(&this->Import[0],this->Import.size(),sf::Quads);
			if(this->Export.size())
				window->draw(&this->Export[0],this->Export.size(),sf::Quads);
		}
	}else{
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
	if(hasImport(this->selected))
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
	if(hasExport(this->selected)){
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
	if(hasImport(this->selected)){
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
		this->income->mouseOver("Income","That is monthly income from that settlement.\nIncome is represented by taxes of population and trade revenue.");
		this->pop->mouseOver("Population","Population increase revenue in your settlements.\nYou can recruit oarsmen and marines from population.\n");
		this->growth->mouseOver("Growth","That is montly population spore.");
		if(!isYourSett(selected))
			this->dip->mouseOver(PlayerInfo(::settlement[this->selected].getOwner()),getDataPlayer(::settlement[this->selected].getOwner()));
		return 1;
	}
	return 0;
}
short LabelSett::Ship(){
	for(unsigned i=this->recruit.size();i--;){
		if(canRecruit(this->id[i],this->selected)){
			if(this->recruit[i].left(naval[this->id[i]].Name(),naval[this->id[i]].Description())){
				return this->id[i];
			}
		}else if(this->recruit[i].mouseOver(naval[this->id[i]].Name(),naval[this->id[i]].Description()))
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
	this->recruit.clear();
	this->Export.clear();
	this->Import.clear();
}
//Global variable for GUI
LabelSett *labelSett=NULL;