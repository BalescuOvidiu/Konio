#include "labelFleet.h"
//Display for fleet
LabelFleet::LabelFleet(short selected){
	this->label=new Label(32+gui.x,64+gui.y,400,140,1);
	this->select(selected);
}
void LabelFleet::select(short selected){
	this->select(selected,this->getPosition().x,this->getPosition().y);
}
void LabelFleet::select(short selected,short x,short y){
	this->selected=selected;
	//Text
	this->formation=new LabelIcon(5+x,15+y,"data/game/formations/"+Format(this->fleet().Formation())+".png");
	this->formation->setText(::FormationName(::fleet[selected].Formation()));
	this->upkeep=new LabelIcon(5+x,75+y,"data/game/icons/coins.png");
	this->upkeep->setText(Format(::fleet[selected].Upkeep())+" upkeep");
	this->provision=new LabelIcon(170+x,75+y,"data/game/icons/coins.png");
	this->provision->setText(Format(::fleet[selected].Provision())+"%");
	//Buttons
	this->dip=new LabelIcon(5+x,105+y,"data/game/icons/coins.png");
	this->dip->setText(PlayerInfo(::fleet[selected].Player()));
	this->player=new Button("data/game/icons/"+std::to_string(::fleet[selected].Player())+".png",353+x,95+y);
	if(isYourFleet(this->selected)){
		F=this->fleet().Formation();
		this->form1=new Button("data/game/formations/"+Format((F+1)%3)+".png",332+x,30+y);
		this->form2=new Button("data/game/formations/"+Format((F+2)%3)+".png",372+x,30+y);
	}
	//Ships
	this->ships.clear();
	short X=x+5;
	for(unsigned id=0;id<naval.size();id++){
		ships.push_back(LabelIcon(X,45+y,"data/game/icons/naval/"+Format(id)+".png"));
		ships[id].setText(Format(::fleet[selected].getShips(id)));
		if(::fleet[selected].getShips(id))
			X+=50;
	}
	//Range
	this->range=new sf::CircleShape(90,64);
	this->range->setFillColor(sf::Color(220,220,220,64));
	this->range->setOutlineColor(sf::Color(220,220,220,100));
	this->range->setOutlineThickness(1);
	this->range->setPosition(::fleet[selected].getPosition().x-90,::fleet[selected].getPosition().y-90);
	//Guides
	this->getRoute();
}
void LabelFleet::Render(sf::RenderWindow *window){
	this->label->Render(window);
	this->formation->Render(window);
	this->upkeep->Render(window);
	this->provision->Render(window);
	this->dip->Render(window);
	this->player->Render(window);
	for(unsigned i=0;i<naval.size();i++)
		if(::fleet[selected].getShips(i))
			ships[i].Render(window);
	if(isYourFleet(this->selected)){
		this->form1->Render(window);
		this->form2->Render(window);
	}
}
void LabelFleet::RenderGuides(sf::RenderWindow *window){
	window->draw(*this->range);
	window->draw(&this->route[0],this->route.size(),sf::Quads);
}
//Update
void LabelFleet::Update(){
	if(isYourFleet(this->selected)){
		if(this->form1->left(FormationName((F+1)%3),FormationText((F+1)%3))){
			::fleet[this->selected].Reform((F+1)%3);
			this->select(this->selected);
		}else if(this->form2->left(FormationName((F+2)%3),FormationText((F+2)%3))){
			::fleet[this->selected].Reform((F+2)%3);
			this->select(this->selected);
		}
	}
}
void LabelFleet::reload(){
	this->provision->setText(Format(::fleet[selected].Provision())+"%");
	this->range->setPosition(::fleet[this->selected].getPosition().x-90,::fleet[this->selected].getPosition().y-90);
}
void LabelFleet::move(float x,float y){
	this->label->move(x,y);
	this->formation->move(x,y);
	this->upkeep->move(x,y);
	this->provision->move(x,y);
	this->dip->move(x,y);
	this->player->move(x,y);
	for(unsigned i=0;i<naval.size();i++)
		ships[i].move(x,y);
	if(::fleet[this->selected].Player()==::human){
		this->form1->move(x,y);
		this->form2->move(x,y);
	}
}
void LabelFleet::getRoute(){
	this->route=getGuide(::fleet[this->selected].getPosition(),::fleet[this->selected].getRoute(),sf::Color(120,120,255));
}
bool LabelFleet::playerLeft(){
	return this->player->left(PlayerInfo(::fleet[selected].Player()),"Click to see information about owner of this fleet.");
}
bool LabelFleet::right(){
	return this->label->right();
}
bool LabelFleet::mouseOver(){
	if(this->label->mouseOver()){
		this->formation->mouseOver(FormationName(F),FormationText(F));
		this->upkeep->mouseOver("Monthly upkeep","");
		this->dip->mouseOver("Fleet owner","");
		this->provision->mouseOver("Provision","");
		for(unsigned i=0;i<naval.size();i++)
			if(::fleet[selected].getShips(i))
				this->ships[i].mouseOver(naval[i].Name()+" - "+Format(::fleet[selected].getShips(i))+" ships",naval[i].Description());
		return 1;
	}
	return 0;
}
//Get data
short LabelFleet::Selected(){
	return this->selected;
}
Fleet LabelFleet::fleet(){
	return ::fleet[this->selected];
}
sf::Vector2f LabelFleet::getPosition(){
	return this->label->getPosition();
}
LabelFleet::~LabelFleet(){

}
LabelFleet *labelFleet=NULL;