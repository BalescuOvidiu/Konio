#include "game.h"
//Other data
bool isFree(short sett){
	bool free=1;
	for(unsigned i=fleet.size();i--;){
		if(!fleet[i].Speed()&&settlement[sett].isInRange(::fleet[i].getPosition())){
			//Supply
			if(!isEnemyOf(sett,::fleet[i].Player())){
				//Supply
				free=0;
				supply(i,sett);
				//AI
				if(!isYourFleet(i)&&::fleet[i].Formation()!=2)
					Reform(i,2);
			}
		}
	}
	return free;
}
//Actions
void BuyShip(short id,short sett){
	if(id<0)
		return ;
	if(canRecruit(id,sett)){
		//Pay and recruit
		player[settlement[sett].getOwner()].Income(-naval[id].Cost());
		settlement[sett].Recruit(naval[id].Rowers());
		//Bar
		if(isYourSett(sett))
			bar->Reload();
		//Add ship to fleet from port
		short selected=-1;
		for(unsigned i=0;i<::fleet.size();i++){
			if(settlement[sett].isInRange(::fleet[i].getPosition()))
				if(::fleet[i].Player()==settlement[sett].getOwner()&&!::fleet[i].Speed()){
					if(selected<0)
						selected=i;
					else if(::fleet[i].size()<::fleet[selected].size())
						selected=i;
				}
		}
		if(selected>=0){
			//Add ship
			::fleet[selected].addShip(id,100,naval[id].Marines());
			reloadLabelFleet(selected);
		}else{
			//Create new fleet
			sf::Vector2f pos=map->GetNearestNode(settlement[sett].getPosition()).getPosition();
			add(Fleet(pos,getAngle(settlement[sett].getPosition(),pos),settlement[sett].getOwner(),2,100));
			::fleet[::fleet.size()-1].addShip(id,100,naval[id].Marines());
		}
		//Labels
		reloadLabelPlayer(settlement[sett].getOwner());
		reloadLabelSett(sett);
	}
}
void BreakFleet(short i,short id){
	if(::fleet[i].getShips(id)){
		//Get smallest fleet
		short nearest=getSmallestFleetInRange(i);
		if((nearest>-1||::fleet[i].size()>1)){
			//Get first ship
			for(short rank=0;rank<::fleet[i].size();rank++){
				if(::fleet[i].Ship(rank)==id){
					if(nearest>0){
						::fleet[nearest].addShip(
							::fleet[i].Ship(rank),
							::fleet[i].Integrity(rank),
							::fleet[i].Marines(rank)
						);
						::fleet[i].removeShip(rank);
						if(!::fleet[i].size())
							changedFleets(i,nearest);
						else
							reloadLabelFleet(i);
					}else if(::fleet[i].size()>1){
						add(Fleet(
							::fleet[i].getPosition(),
							::fleet[i].getRotation()+90,
							::fleet[i].Player(),
							2,
							::fleet[i].Provision())
						);
						::fleet[::fleet.size()-1].addShip(
							id,
							::fleet[i].Integrity(rank),
							::fleet[i].Marines(rank)
						);
						::fleet[i].removeShip(rank);
						reloadLabelFleet(i);
					}
					break;
				}
			}
		}
	}
}
void CombatFleet(short i,short j){
	if(fleet[i].Power()>fleet[j].Power()){
		for(short k=fleet[j].size()/2;fleet[i].size()>1&&k--;)
			fleet[i].removeShip(0);	
		DefeatedFleet(i,j);
	}else{
		for(short k=fleet[i].size()/2;fleet[j].size()>1&&k--;)
			fleet[j].removeShip(0);	
		DefeatedFleet(j,i);
	}
}
void DefeatedFleet(short i,short j){
	//Change statistics
	Defeated(fleet[i].Player(),fleet[j].Player());
	fleet[i].Supply(fleet[j].Provision()/2.);
	//LabelPlayer
	reloadLabelPlayer(fleet[i].Player());
	reloadLabelPlayer(fleet[j].Player());
	//Clear memory
	fleet.erase(fleet.begin()+j);
	//LabelFleet
	changedFleets(i,j);
}
void GiveCoins(short i,short j,float coins){
	player[i].Income(coins);
	player[j].Income(-coins);
	//GUI
	reloadLabelPlayer(i);
	reloadLabelPlayer(j);
	if(i==human||j==human)
		bar->Reload();
}
void MergeFleet(short i,short j){
	if(i!=j&&fleet[i].Player()==fleet[j].Player()){
		if(fleet[i].isInRange(fleet[j].getPosition())&&fleet[i].isInRange(fleet[j].getPosition())){
			while(fleet[j].size()){
				fleet[i].addShip(fleet[j].Ship(0),fleet[j].Integrity(0),fleet[j].Marines(0));
				fleet[j].removeShip(0);
			}			
			fleet.erase(fleet.begin()+j);
			changedFleets(i,j);
		}
	}
}
void MoveFleet(short fleet,sf::Vector2f target){
	::fleet[fleet].Move(target);
	if(isSelectedFleet(fleet))
		labelFleet->getRoute();
}
void MoveFleetPlayer(short fleet,sf::Vector2f target){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		::fleet[fleet].MoveAdd(target);
	else
		::fleet[fleet].Move(target);
	if(isSelectedFleet(fleet))
		labelFleet->getRoute();
}
void Reform(short fleet,short formation){
	::fleet[fleet].Reform(formation);
	if(isSelectedFleet(fleet))
		labelFleet->select(fleet);
}
void takeSettlement(short i,short player){
	short owner=settlement[i].getOwner();
	settlement[i].Conquest(player);
	//LabelSett
	reloadLabelSett(i);
	if(hasImport(i))
		reloadLabelSett(::settlement[i].getImport());
		reloadLabelPlayer(::settlement[::settlement[i].getImport()].getOwner());
	if(hasExport(i)){
		reloadLabelSett(getImporter(i));
		reloadLabelPlayer(::settlement[getImporter(i)].getOwner());
	}
	//Player
	if(!hasSettlement(owner)){
		GiveCoins(::settlement[i].getOwner(),owner,::player[owner].Coins());
	}else{
		//LabelPlayer
		reloadLabelPlayer(::settlement[i].getOwner());
		reloadLabelPlayer(owner);
		if(::settlement[i].getOwner()==human||owner==human)
			bar->Reload();
	}
}
void supply(short f,short i){
	//Provision
	fleet[f].Supply();
	//Marines
	for(unsigned j=fleet[f].size();j--;){
		short need=naval[fleet[f].Ship(j)].Marines()-fleet[f].Marines(j);
		if(settlement[i].getPopulation()>need){
			settlement[i].Recruit(need);
			fleet[f].setMarines(j,naval[fleet[f].Ship(j)].Marines());
		}
	}
}
//Basic
Game::Game(std::string directory,sf::View *view,short human){
	//Begin
	::human=human;
	this->battle=NULL;
	//GUI
	this->range=new sf::CircleShape(0,64);
	this->range->setFillColor(sf::Color(220,220,220,64));
	this->range->setOutlineColor(sf::Color(220,220,220,100));
	this->range->setOutlineThickness(1);
	this->hoveredFleet=0;
	this->paused=0;
	//Map
	map=new Map();
	//Music
	audio.changeMusic("data/audio/music/Winds of Ithaca.ogg");
	audio.changeAmbient("data/audio/sound/water.ogg");
	//Reading variables
	short faction,formation,local,lost,import,integrity,m,marines,n,occupied;
	short player,price,ship,size,team,radius,won;
	int limit,population;
	float angle,coins,provision,x,y;
	std::string name;
	sf::Vector2f pos;
	bool camera=0;
	//Read goods
	std::ifstream in("data/game/goods/data.txt");
	while(in>>price){
		std::getline(in,name);
		std::getline(in,name);
		good.push_back(Good(name,price));
	}
	in.close();
	//READ MAP
	in.open("data/game/map/data.txt");
	//Read regions
	in>>n;
	while(n--){
		in>>x>>y>>size;
		std::getline(in,name);
		std::getline(in,name);
		map->add(Region(x,y,size,name));
	}
	//Read graph
	while(in>>x>>y>>radius)
		map->add(Node(x,y,radius));
	in.close();
	//Load data of game
	in.open(directory.c_str());
	in>>month>>year;
	//Read settlements
	in>>n;
	while(n--){
		//Get data of settlement
		in>>x>>y>>player>>population>>limit>>local>>import>>occupied;
		std::getline(in,name);
		std::getline(in,name);
		add(Settlement(x,y,player,population,limit,local,import,occupied,name));
		//Get position for camera
		if(player==human&&!camera){
			pos.x=x;
			pos.y=y;
			camera=1;
		}
	}
	//Read players
	in>>n;
	while(n--){
		in>>faction>>coins>>team>>won>>lost;
		std::getline(in,name);
		std::getline(in,name);
		add(Player(faction,coins,team,name,won,lost));
	}
	//Read fleets
	in>>n;
	while(n--){
		in>>x>>y>>angle>>player>>formation;
		in>>provision;
		in>>m;
		add(Fleet(sf::Vector2f(x,y),angle,player,formation,provision));
		//Ships
		while(m--){
			in>>ship>>integrity>>marines;
			::fleet.back().addShip(ship,integrity,marines);
		}
		//Route
		in>>size;
		if(size){
			in>>x>>y;
			::fleet.back().Move(sf::Vector2f(x,y));
		}
	}
	in.close();
	//Human player GUI
	bar=new Bar(this->getCalendar());
	this->moveViewTo(view,pos);
}
//Rendering
void Game::Render(sf::RenderWindow *window){
	//Map
	map->Render(window);
	//Guides
	if(labelSett!=NULL)
		labelSett->RenderGuides(window);
	window->draw(*this->range);
	if(labelFleet!=NULL)
		labelFleet->RenderGuides(window);
	//Fleets
	if(hoveredFleet){
		//Body
		for(unsigned i=::fleet.size();i--;)
			if(i!=hoveredFleet-1)
				fleet[i].RenderBody(window);
		fleet[hoveredFleet-1].RenderBody(window);
		//Sails
		for(unsigned i=::fleet.size();i--;)
			if(i!=hoveredFleet-1)
				fleet[i].RenderSail(window);
		fleet[hoveredFleet-1].RenderSail(window);
	}else{
		//Body
		for(unsigned i=::fleet.size();i--;)
			fleet[i].RenderBody(window);
		//Sails
		for(unsigned i=::fleet.size();i--;)
			fleet[i].RenderSail(window);
	}
	//Regions
	map->RenderRegions(window);
	//Settlements
	for(unsigned i=::settlement.size();i--;)
		settlement[i].Render(window);
	//About
	if(about)
		about.Render(window);
	//GUI
	if(subMenu!=NULL){
		subMenu->Render(window);
	}else{
		bar->Render(window);
		//Labels
		if(labelSett!=NULL)
			labelSett->Render(window);
		if(labelPlayer!=NULL)
			labelPlayer->Render(window);
		if(labelFleet!=NULL)
			labelFleet->Render(window);
		if(labelDip!=NULL)
			labelDip->Render(window);
	}
}
bool Game::mouseOverGUI(){
	short q=0;
	if(labelSett!=NULL)
		q+=labelSett->mouseOver();
	if(labelPlayer!=NULL)
		q+=labelPlayer->mouseOver();
	if(labelFleet!=NULL)
		q+=labelFleet->mouseOver();
	if(labelDip!=NULL)
		q+=labelDip->mouseOver();
	if(q)
		return 1;
	return (bar->mouseOver());
}
void Game::gameGUI(sf::RenderWindow *window,sf::View *view){
	//View
	this->moveCamera(window,view,8);
	if(labelFleet!=NULL&&(month&1)){
		labelFleet->reload();
		labelFleet->getRoute();
	}
	//GUI
	if(subMenu!=NULL){
		about.hide();
		subMenu->Update(window);
		if(!(*subMenu))
			subMenu=NULL;
	}else if(gui.canClick(400)){
		//About
		about.hide();
		bar->Update();
		//Pause
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
			this->paused=!this->paused;
			bar->Reload(getCalendar());
			gui.clickRestart();
		}
		//Label settlement
		if(labelSett!=NULL){
			//Recruit
			if(isYourSett(labelSett->Selected()))
				BuyShip(labelSett->Ship(),labelSett->Selected());
			//Local good
			if(labelSett->localLeft())
				this->moveViewToSett(view,getImporter(labelSett->Selected()));
			//Import good
			if(labelSett->importLeft())
				this->moveViewToSett(view,labelSett->sett().getImport());
			//Deselect
			if(labelSett->playerLeft())
				selectPlayer(labelSett->sett().getOwner());
			if(labelSett->right())
				deselectSett();
		}
		//Label player
		if(labelPlayer!=NULL){
			if(labelPlayer->right())
				deselectPlayer();
		}
		//Label fleet
		if(labelFleet!=NULL){
			labelFleet->Update();
			//Hovered fleet
			if(this->hoveredFleet&&::fleet[this->hoveredFleet-1].Player()==::human)
				if(::fleet[this->hoveredFleet-1].right())
					MergeFleet(labelFleet->Selected(),this->hoveredFleet-1);
			//Other
			if(labelFleet->playerLeft())
				selectPlayer(labelFleet->fleet().Player());
			else if(labelFleet->right())
				deselectFleet();
		}
		//Label diplomacy
		if(labelDip!=NULL){
			selectPlayer(labelDip->Update());
			//Deselect
			if(labelDip->right())
				deselectDip();
		}
		//Hovered Fleet
		if(hoveredFleet){
			::fleet[hoveredFleet-1].setColor(sf::Color(255,255,255));
			hoveredFleet=0;
			this->range->setRadius(0);
			this->range->setPosition(sf::Vector2f(0,0));
		}
		//Gameplay
		if(!this->mouseOverGUI()){
			//Selected fleet
			if(labelFleet!=NULL){
				if(labelFleet->fleet().Player()==human){
					if(gui.canRight(400))
						MoveFleetPlayer(labelFleet->Selected(),gui.mousePosition());
				}
			}
			//Fleets
			hoveredFleet=0;
			distFleet=999999999;
			for(unsigned i=::fleet.size();i--;){
				if(!isSelectedFleet(i))
					if(distFleet>Dist(::fleet[i].getPosition(),gui.mousePosition())){
						distFleet=Dist(::fleet[i].getPosition(),gui.mousePosition());
						hoveredFleet=i+1;
					}
			}
			//Settlements
			for(unsigned i=::settlement.size();i--;){
				if(!isSelectedSett(i)){
					if(settlement[i].mouseOver()){
						if(Dist(settlement[i].getPosition(),gui.mousePosition())<distFleet){
							//Hovered fleet
							if(hoveredFleet){
								::fleet[hoveredFleet-1].setColor(sf::Color(255,255,255));
								hoveredFleet=0;
							}
							//Range
							this->range->setRadius(settlement[i].getRange());
							this->range->setPosition(settlement[i].getRangePosition());
							//Label
							about.show(getSettlementTitle(i),getSettlementDescription(i));
							//Click
							if(settlement[i].left())
								selectSett(i);
							return ;
						}
						break;
					}else{
						this->range->setRadius(0);
						this->range->setPosition(sf::Vector2f(0,0));

					}
				}
			}
			if(this->hoveredFleet){
				if(::fleet[this->hoveredFleet-1].mouseOver()){
					this->range->setRadius(::fleet[hoveredFleet-1].Range());
					this->range->setPosition(::fleet[hoveredFleet-1].getRangePosition());
					if(::fleet[this->hoveredFleet-1].left()){
						this->range->setRadius(0);
						this->range->setPosition(sf::Vector2f(0,0));
						selectFleet(this->hoveredFleet-1);
					}
				}
			}
		}
	}
}
//View
void Game::moveView(sf::View *view,float x,float y){
	if(gui.x+x<0||gui.x+gui.width()+x>4000)
		x=0;
	if(gui.y+y<0||gui.y+gui.height()+y>2000)
		y=0;
	if((!x)&&(!y))
		return ;
	//Move
	gui.x+=x;
	gui.y+=y;
	about.move(x,y);
	view->move(x,y);
	map->move(x,y);
	if(op!=NULL)
		op->move(x,y);
	if(subMenu!=NULL)
		subMenu->move(x,y);
	bar->move(x,y);
	//Label of selected settlement, player, fleet...
	if(labelSett!=NULL)
		labelSett->move(x,y);
	if(labelPlayer!=NULL)
		labelPlayer->move(x,y);
	if(labelFleet!=NULL)
		labelFleet->move(x,y);
	if(labelDip!=NULL)
		labelDip->move(x,y);
}
void Game::moveViewTo(sf::View *view,sf::Vector2f pos){
	//Reset view
	this->moveView(view,-gui.x,-gui.y);
	//Limits of map
	if(pos.x-gui.width()/2<0)
		pos.x=0;
	if(pos.y-gui.height()/2<0)
		pos.y=0;
	pos.x-=(int)pos.x%8;
	pos.y-=(int)pos.y%8;
	if(pos.x>4000-gui.width()/2)
		pos.x=4000-gui.width()/2;
	if(pos.y>2000-gui.height()/2)
		pos.y=2000-gui.height()/2;
	//Move view to point pos
	moveView(view,pos.x-gui.width()/2,pos.y-gui.height()/2);
}
void Game::moveViewToSett(sf::View *view,short sett){
	this->moveViewTo(view,::settlement[sett].getPosition());
	selectSett(sett);
}
void Game::moveCamera(sf::RenderWindow *window,sf::View *view,float speed){
	//Move camera by key
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->moveView(view,-speed,0);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->moveView(view,speed,0);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->moveView(view,0,-speed);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->moveView(view,0,speed);
	//Move camera by mouse cursor
	if(this->mouseOverGUI()&&subMenu==NULL)
		return ;
	sf::Vector2f camera=gui.mousePosition();
	if(camera.x<0)
		camera.x=0;
	if(camera.y<0)
		camera.y=0;
	if(camera.x<window->getSize().x/20+gui.x)
		this->moveView(view,-speed,0);
	if(camera.x>window->getSize().x*19/20+gui.x)
		this->moveView(view,speed,0);
	if(camera.y<window->getSize().y/10+gui.y)
		this->moveView(view,0,-speed);
	if(camera.y>window->getSize().y*9/10+gui.y){
		this->moveView(view,0,speed);
	}
}
//Gameplay
std::string Game::getMonthName(){
	if(this->paused)
		switch(this->month/3600){
			case 0: return "January - PAUSED"; break;
			case 1: return "February - PAUSED"; break;
			case 2: return "March - PAUSED"; break;
			case 3: return "April - PAUSED"; break;
			case 4: return "May - PAUSED"; break;
			case 5: return "June - PAUSED"; break;
			case 6: return "July - PAUSED"; break;
			case 7: return "August - PAUSED"; break;
			case 8: return "September - PAUSED"; break;
			case 9: return "October - PAUSED"; break;
			case 10: return "November - PAUSED"; break;
			default: return "December - PAUSED"; break;
		}
	switch(this->month/3600){
		case 0: return "January"; break;
		case 1: return "February"; break;
		case 2: return "March"; break;
		case 3: return "April"; break;
		case 4: return "May"; break;
		case 5: return "June"; break;
		case 6: return "July"; break;
		case 7: return "August"; break;
		case 8: return "September"; break;
		case 9: return "October"; break;
		case 10: return "November"; break;
		default: return "December"; break;
	}
}
std::string Game::getCalendar(){
	if(year<0)
		return std::to_string(-this->year)+" B.C. "+this->getMonthName();
	return std::to_string(this->year)+" A.D. "+this->getMonthName();
}
void Game::Save(){
	std::ofstream out("data/game/saved/"+std::to_string(::human)+".txt");
	out<<this->month<<' '<<this->year<<'\n';
	//Write settlements
	out<<::settlement.size()<<'\n';
	for(unsigned i=0;i<::settlement.size();i++){
		out<<::settlement[i].getPosition().x<<' '<<::settlement[i].getPosition().y<<' ';
		out<<::settlement[i].getPlayer()<<' '<<::settlement[i].getPopulation()<<' ';
		out<<::settlement[i].getLimit()<<' '<<::settlement[i].getGood()<<' ';
		out<<::settlement[i].getImport()<<' '<<::settlement[i].getOccupied();
		out<<'\n'<<::settlement[i].getName()<<'\n';
	}
	//Write players
	out<<::player.size()<<'\n';
	for(unsigned i=0;i<::player.size();i++){
		out<<::player[i].Faction()<<' '<<::player[i].Coins()<<' '<<::player[i].Team()<<' '<<::player[i].Battles();
		out<<'\n'<<::player[i].Name()<<'\n';
	}
	//Write fleets
	out<<::fleet.size()<<'\n';
	for(unsigned i=0;i<::fleet.size();i++){
		out<<::fleet[i].getPosition().x<<' '<<::fleet[i].getPosition().y<<' ';
		out<<::fleet[i].getRotation()<<' '<<::fleet[i].Player()<<' ';
		out<<::fleet[i].Formation()<<' '<<::fleet[i].Provision()<<' '<<::fleet[i].size()<<'\n';
		for(short j=0;j<::fleet[i].size();j++){
			out<<::fleet[i].Ship(j)<<' '<<::fleet[i].Integrity(j)<<' '<<::fleet[i].Marines(j)<<'\n';
		}
		if(::fleet[i].getRoute().size())
			out<<::fleet[i].getRoute().size()<<' '<<::fleet[i].getTarget().x<<' '<<::fleet[i].getTarget().y<<'\n';
		else
			out<<"0\n";
	}
	out.close();
	//Save introduction file
	in.open("data/campaign/about/"+std::to_string(::human)+".txt");
	if(in.is_open()){
		std::string title,text;
		getline(in,title);
		getline(in,text,'*');
		in.close();
		out.open("data/campaign/about/"+std::to_string(::human)+"_saved.txt");
		out<<::player[::human].Name()<<' '<<this->getCalendar()<<'\n'<<text<<'*';
		out.close();
	}
}
void Game::Clock(){
	//Map
	if(this->month&1)
		map->Update();
	//Time are traveling
	this->month++;
	if(this->month>=43200){
		this->month=0;
		this->year++;
	}
	//Show date
	if(month%3600==0)
		this->Monthly();
	//AI
	this->AI();
}
void Game::Monthly(){
	//Income
	for(unsigned i=::player.size();i--;)
		player[i].Income(getIncome(i));
	//Settlements
	for(unsigned i=0;i<::settlement.size();i++)
		settlement[i].Monthly();
	//GUI
	bar->Reload(getCalendar());
	if(labelSett!=NULL)
		reloadLabelSett(labelSett->Selected());
	if(labelPlayer!=NULL)
		reloadLabelPlayer(labelPlayer->Selected());
	//Save game
	this->Save();
}
//AI
void Game::AI(){
	//Buy ships
	if(this->month%600==100){
		for(unsigned i=settlement.size();i--;){
			if(!isYourSett(i)){
				if(isFree(i)){
					//Check if is possible to recruit a fleet
					short max=1;
					for(unsigned id=naval.size();id--;)
						if(1<player[settlement[i].getPlayer()].Coins()/naval[id].Cost()){
							max=player[settlement[i].getPlayer()].Coins()/naval[id].Cost();
							break;
						}
					//Recruit
					if(max>1)
						for(unsigned id=naval.size();id--;){
							if(isRecruitable(id,i)){
								while(canRecruit(id,i)){
									BuyShip(id,i);
								}
							}
						}
				}
			}
		}
	}
	//Attack fleets
	if(this->month%1000==0){
		for(unsigned j=::fleet.size();j--;){
			if(!isYourFleet(j)&&!::fleet[j].Speed()){
				short nearest=-1;
				float dist=999999999;
				for(unsigned i=::fleet.size();i--;){
					if(i!=j){
						if(isEnemyFleet(i,j)&&fleet[i].size()<fleet[j].size()){
							if(dist>fleet[j].Dist(fleet[i].getPosition())){
								nearest=i;
								dist=fleet[j].Dist(fleet[i].getPosition());
							}
						}else if(fleet[i].size()*fleet[j].size()<=25)
							MergeFleet(i,j);
					}
				}
				//Send to the enemy fleet
				if(nearest>=0){
					MoveFleet(j,fleet[nearest].getPosition());
					Reform(j,1);
				}
			}
		}
	}
	//Attack settlements
	if(this->month%1000==400){
		for(unsigned j=::fleet.size();j--;){
			if(!isYourFleet(j)){
				short nearest=-1;
				float dist=999999999;
				for(unsigned i=::settlement.size();i--;){
					if(i!=j)
						if(isEnemyOf(i,fleet[j].Player())&&isFree(i))
							if(dist>fleet[j].Dist(settlement[i].getPosition())){
								nearest=i;
								dist=fleet[j].Dist(settlement[i].getPosition());
							}
				}
				//Send to the enemy fleet
				if(nearest>=0){
					MoveFleet(j,settlement[nearest].getPosition());
					Reform(j,1);
				}
			}
		}
	}
	//Supply
	if(this->month%100==0){
		for(unsigned j=::fleet.size();j--;)
			if(!isYourFleet(j)&&(::fleet[j].Provision()<40||(::fleet[j].Provision()<100&&!::fleet[j].Speed()))){
				//Get nearest allied settlement
				short nearest=-1;
				float dist=9999999999;
				for(unsigned i=::settlement.size();i--;){
					if(i!=j)
						if(isAllyOf(i,fleet[j].Player())&&isFree(i))
							if(dist>fleet[j].Dist(settlement[i].getPosition())){
								nearest=i;
								dist=fleet[j].Dist(settlement[i].getPosition());
							}
				}
				//Move fleet
				if(nearest>=0){
					MoveFleet(j,settlement[nearest].getPosition());
					Reform(j,1);
				}
			}
	}
}
//Battle
void Game::newBattle(short yourFleet,short enemyFleet,sf::View *view){
	//Select scene
	this->moveView(view,-gui.x,-gui.y);
	this->battle=new Battle(yourFleet,enemyFleet,view);
	gui.selected=5;
}
void Game::afterBattle(sf::View *view){
	//Statistics
	std::vector<bool> selected;
	selected.resize(::player.size(),0);
	for(unsigned i=this->battle->fleets.size();i--;){
		if(!selected[::fleet[this->battle->fleets[i]].Player()]){
			selected[::fleet[this->battle->fleets[i]].Player()]=1;
			if(::fleet[this->battle->fleets[i]].size()){
				::player[::fleet[this->battle->fleets[i]].Player()].WonBattle();
			}else{
				::player[::fleet[this->battle->fleets[i]].Player()].LostBattle();
			}
		}
	}
	//GUI
	bar=new Bar(this->getCalendar());
	deselectSett();
	deselectPlayer();
	if(::fleet[this->battle->fleets[0]].size()&&isSelectedFleet(this->battle->fleets[0]))
		reloadLabelFleet(this->battle->fleets[0]);
	else
		deselectFleet();
	//Move view
	moveViewTo(view,::fleet[this->battle->fleets[0]].getPosition());
	//Clear memory
	for(unsigned i=::fleet.size();i--;)
		if(!::fleet[i].size())
			::fleet.erase(::fleet.begin()+i);
	delete this->battle;
	this->battle=NULL;
	this->Save();
}
//Update
void Game::Update(sf::RenderWindow *window,sf::View *view){
	//After the battle
	if(this->battle!=NULL)
		this->afterBattle(view);
	//GUI
	this->gameGUI(window,view);
	//Gameplay
	if(subMenu==NULL&&!this->paused){
		//Clock
		this->Clock();
		//Fleets
		for(unsigned i=::fleet.size();i--;){
			//Move
			::fleet[i].Update();
			//Provision
			if(::fleet[i].Provision()<=0){
				if(isSelectedFleet(i))
					deselectFleet();
				::fleet.erase(::fleet.begin()+i);
				break;
			}
			//Combat
			for(unsigned j=::fleet.size();j--;){
				if(i!=j)
					if(canCombat(i,j)){
						//Combat
						if(isYourFleet(i))
							this->newBattle(i,j,view);
						else if(isYourFleet(j))
							this->newBattle(j,i,view);
						else
							CombatFleet(i,j);
						//End of cicle
						this->Save();
						break;
					}
			}
		}
		//Settlements interactions with fleets
		for(unsigned i=::settlement.size();i--;){
			//Conquest
			if(isFree(i))
				for(unsigned j=::fleet.size();j--;){
					if(::fleet[j].isInRange(settlement[i].getPosition())){
						if(isEnemyOf(i,::fleet[j].Player()))
							takeSettlement(i,::fleet[j].Player());
					}
				}
		}
	}
	//Exit from game
	if(gui.selected==2)
		this->moveView(view,-gui.x,-gui.y);
}
Game::~Game(){
	//Empty memory
	delete bar;
	delete map;
	delete subMenu;
	delete op;
	bar=NULL;
	map=NULL;
	subMenu=NULL;
	op=NULL;
	deselectDip();
	deselectPlayer();
	deselectFleet();
	deselectSett();
	::settlement.clear();
	::player.clear();
	::fleet.clear();
	::good.clear();
	//Audio
	audio.stopAmbient();
	audio.changeMusic("data/audio/music/Athena.ogg");
}