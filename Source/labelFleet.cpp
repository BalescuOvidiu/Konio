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
	this->F=::fleet[selected].Formation();
	this->form.clear();
	//Text
	this->formation=new LabelIcon(5+x,15+y,"data/game/formations/"+Format(F)+".png");
	this->formation->setText(::FormationName(::fleet[selected].Formation()));
	this->upkeep=new LabelIcon(5+x,75+y,"data/game/icons/coins.png");
	this->upkeep->setText(Format(::fleet[selected].Upkeep())+" upkeep");
	this->provision=new LabelIcon(170+x,75+y,"data/game/icons/provision.png");
	this->provision->setText(Format(::fleet[selected].Provision())+"%");
	//Buttons
	this->dip=new LabelIcon(5+x,105+y,"data/game/icons/player.png");
	this->dip->setText(PlayerInfo(::fleet[selected].Player()));
	this->player=new Button("data/game/icons/"+std::to_string(::fleet[selected].Player())+".png",353+x,95+y);
	//Formations
	if(isYourFleet(this->selected))
		for(short i=1;i<nFormation;i++)
			this->form.push_back(Button("data/game/formations/"+Format((F+i)%nFormation)+".png",412+x-40*i,30+y));
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
	this->range=new sf::CircleShape(::fleet[this->selected].Range(),64);
	this->range->setFillColor(sf::Color(220,220,220,64));
	this->range->setOutlineColor(sf::Color(220,220,220,100));
	this->range->setOutlineThickness(1);
	//Guides
	this->route.clear();
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
		for(unsigned i=nFormation-1;i--;)
			this->form[i].Render(window);
	}
}
void LabelFleet::RenderGuides(sf::RenderWindow *window){
	window->draw(*this->range);
	window->draw(&this->route[0],this->route.size(),sf::Quads);
}
//Update
void LabelFleet::Update(){
	if(isYourFleet(this->selected)){
		for(short i=1;i<nFormation;i++)
			if(this->form[i-1].left(FormationName((F+i)%nFormation),FormationText((F+i)%nFormation))){
				::fleet[this->selected].Reform((F+i)%nFormation);
				this->select(this->selected);
				break;
			}
	}
}
void LabelFleet::reload(){
	if(!this->fleet().Speed())
		if(this->route.size())
			this->route.clear();
	this->provision->setText(Format(::fleet[selected].Provision())+"%");
	this->range->setPosition(
		::fleet[this->selected].getPosition().x-::fleet[this->selected].Range(),
		::fleet[this->selected].getPosition().y-::fleet[this->selected].Range()
	);
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
		for(short i=nFormation-1;i--;)
			this->form[i].move(x,y);
	}
}
void LabelFleet::getRoute(){
	this->route=getGuide(::fleet[this->selected].Front(),::fleet[this->selected].getRoute(),sf::Color(120,120,255));
}
bool LabelFleet::playerLeft(){
	return this->player->left(PlayerInfo(::fleet[selected].Player()),"Click to see information about owner of this fleet.");
}
bool LabelFleet::right(){
	return this->label->right();
}
bool LabelFleet::mouseOver(){
	if(this->label->mouseOver()){
		//Details
		this->formation->mouseOver(FormationName(F),FormationText(F));
		this->upkeep->mouseOver("Monthly upkeep","That is pay for marines and oarsmen.");
		this->dip->mouseOver(PlayerInfo(this->fleet().Player()),getDataPlayer(this->fleet().Player()));
		this->provision->mouseOver("Provision","That is food and fresh water supply.\nYour fleet is lost without provision. You can supply your fleet on your or allied settlements.");
		//Break fleet
		short nearest=getSmallestFleetInRange(this->selected);
		for(unsigned i=naval.size();i--;)
			if(::fleet[this->selected].getShips(i)){
				if(this->ships[i].mouseOver(naval[i].Name()+" - "+Format(::fleet[selected].getShips(i))+" ships - click to break fleet",naval[i].Description()+"\n"+::fleet[this->selected].getShipsString(i))){
					if(isYourFleet(this->selected)&&(nearest>-1||this->fleet().size()>1)){
						if(this->ships[i].left()){
							for(short rank=0;rank<this->fleet().size();rank++){
								if((unsigned)this->fleet().Ship(rank)==i){
									if(nearest>0){
										::fleet[nearest].addShip(
											this->fleet().Ship(rank),
											this->fleet().Integrity(rank),
											this->fleet().Marines(rank)
										);
										::fleet[this->selected].removeShip(rank);
										if(!this->fleet().size()){
											::fleet.erase(::fleet.begin()+this->selected);
											if(nearest>this->selected)
												nearest--;
											this->select(nearest);
										}else
											this->select(this->selected);
									}else if(this->fleet().size()>1){
										add(Fleet(
											this->fleet().getPosition(),
											this->fleet().getRotation()+90,
											this->fleet().Player(),
											2,
											this->fleet().Provision())
										);
										::fleet[::fleet.size()-1].addShip(
											i,
											this->fleet().Integrity(rank),
											this->fleet().Marines(rank)
										);
										::fleet[this->selected].removeShip(rank);
										this->select(this->selected);
									}
									break;
								}
							}
						}
					}
					break;
				}
			}
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
	this->route.clear();
	this->ships.clear();

}
LabelFleet *labelFleet=NULL;