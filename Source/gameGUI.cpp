#include "gameGUI.h"
//Constructor
Bar::Bar(std::string data){
	//Black rectangle
	this->rectangle=new sf::RectangleShape(sf::Vector2f(gui.width(),32));
	this->rectangle->setPosition(0,0);
	this->rectangle->setFillColor(sf::Color(0,0,0,200));
	//Game data
	this->coins=new LabelIcon(0,0,"data/game/icons/coins.png");
	this->pop=new LabelIcon(125,0,"data/game/icons/population.png");
	this->calendar=new LabelIcon(250,0,"data/game/icons/time.png");
	//Buttons
	this->main=new Button("data/game/icons/"+std::to_string(human)+".png",gui.width()-250,30);
	this->diplomacy=new Button("data/game/icons/diplomacy.png",gui.width()-150,30);
	this->submenu=new Button("data/game/icons/menu.png",gui.width()-50,30);
	//Text
	this->Reload(data);
}
//Render
void Bar::Render(sf::RenderWindow *window){
	window->draw(*this->rectangle);
	//Game data
	this->coins->Render(window);
	this->pop->Render(window);
	this->calendar->Render(window);
	//Buttons
	this->main->Render(window);
	this->diplomacy->Render(window);
	this->submenu->Render(window);
}
//Update
void Bar::Update(){
	//Faction button
	if(isSelectedPlayer(::human)){
		if(this->main->left(player[::human].Name(),"Click or press F for to close faction label.",sf::Keyboard::F)){
			deselectPlayer();
		}
	}else{
		if(this->main->left(player[::human].Name(),"Click or press F for to see your status.",sf::Keyboard::F)){
			selectPlayer(::human);
		}
	}
	//Diplomacy button	
	if(labelDip==NULL){
		if(this->diplomacy->left("Diplomacy","Click or press R to see relations with other city-states.",sf::Keyboard::R))
			labelDip=new LabelDip();
	}else{
		if(this->diplomacy->left("Diplomacy","Click or press R to close diplomacy label.",sf::Keyboard::R))
			deselectDip();
	}
	//Submenu
	if(this->submenu->left("Menu","Click or press M to show menu.",sf::Keyboard::M))
		subMenu=new SubMenu();
}
void Bar::Reload(){
	this->coins->setText(Format(player[human].Coins()));
	this->pop->setText(Format(getPopulation(human)));
}
void Bar::Reload(std::string data){
	this->Reload();
	this->calendar->setText(data);
}
void Bar::move(float x,float y){
	this->rectangle->move(x,y);
	//Game data
	this->coins->move(x,y);
	this->pop->move(x,y);
	this->calendar->move(x,y);
	//Buttons
	this->main->move(x,y);
	this->diplomacy->move(x,y);
	this->submenu->move(x,y);
}
bool Bar::mouseOver(){
	this->calendar->mouseOver("Calendar","That show year and month.");
	this->coins->mouseOver("Coins","You use coins to recruit navy and to pay marines and oarsmen.\nYou gain coins from taxes and trades.");
	this->pop->mouseOver("Population","Population increase revenue in your settlements.\nYou can recruit oarsmen and marines from population.\n");
	return (this->rectangle->getGlobalBounds().contains(gui.mousePosition().x,gui.mousePosition().y));
}
//Destructor
Bar::~Bar(){
	
}
//Variables
Bar *bar=NULL;
//LabelFleet global functions
void changedFleets(short i,short j){
	if(labelFleet!=NULL){
		if(labelFleet->Selected()>j)
			selectFleet(labelFleet->Selected()-1);
		else{
			if(isSelectedFleet(j))
				deselectFleet();
			else
				reloadLabelFleet(i);
		}
	}
}
void selectFleet(short fleet){
	if(labelFleet==NULL){
		labelFleet=new LabelFleet(fleet);
		//Position
		if(labelSett!=NULL)
			labelFleet->move(0,172);
		if(labelPlayer!=NULL)
			labelFleet->move(0,172);
	}else
		labelFleet->select(fleet);
}
void deselectFleet(){
	if(labelFleet!=NULL){
		//Positions
		if(labelSett!=NULL)
			if(labelSett->getPosition().y>labelFleet->getPosition().y)
				labelSett->move(0,-172);
		if(labelPlayer!=NULL)
			if(labelPlayer->getPosition().y>labelFleet->getPosition().y)
				labelPlayer->move(0,-172);
			//Clear memory
		delete labelFleet;
		labelFleet=NULL;
	}
}
void reloadLabelFleet(short i){
	if(isSelectedFleet(i))
		labelFleet->select(i);
}
bool isSelectedFleet(short i){
	if(labelFleet!=NULL)
		return (i==labelFleet->Selected());
	return 0;
}
//LabelSett global functions
void selectSett(short sett){
	if(labelSett==NULL){
		labelSett=new LabelSett(sett);
		//Position
		if(labelPlayer!=NULL)
			labelSett->move(0,172);
		if(labelFleet!=NULL)
			labelSett->move(0,172);
	}else
		labelSett->select(sett);
}
void deselectSett(){
	if(labelSett!=NULL){
		//Position
		if(labelPlayer!=NULL)
			if(labelPlayer->getPosition().y>labelSett->getPosition().y)
				labelPlayer->move(0,-172);
		if(labelFleet!=NULL)
			if(labelFleet->getPosition().y>labelSett->getPosition().y)
				labelFleet->move(0,-172);
			//Clear memory
		delete labelSett;
		labelSett=NULL;
	}
}
void reloadLabelSett(short i){
	if(isSelectedSett(i))
		labelSett->select(i);
}
bool isSelectedSett(short i){
	if(labelSett!=NULL)
		return (i==labelSett->Selected());
	return 0;
}
//LabelPlayer global functions
void selectPlayer(short player){
	if(player>=0){
		if(labelPlayer==NULL){
			labelPlayer=new LabelPlayer(player);
			//Position
			if(labelSett!=NULL)
				labelPlayer->move(0,172);
			if(labelFleet!=NULL)
				labelPlayer->move(0,172);
		}else
			labelPlayer->select(player);
	}
}
void deselectPlayer(){
	if(labelPlayer!=NULL){
		//Positions
		if(labelSett!=NULL)
			if(labelSett->getPosition().y>labelPlayer->getPosition().y)
				labelSett->move(0,-172);
		if(labelFleet!=NULL)
			if(labelFleet->getPosition().y>labelPlayer->getPosition().y)
				labelFleet->move(0,-172);
			//Clear memory
		delete labelPlayer;
		labelPlayer=NULL;
	}
}
void reloadLabelPlayer(short i){
	if(isSelectedPlayer(i))
		labelPlayer->select(i);
}
bool isSelectedPlayer(short i){
	if(labelPlayer!=NULL)
		return (i==labelPlayer->Selected());
	return 0;
}
