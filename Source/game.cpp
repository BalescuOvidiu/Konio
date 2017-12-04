#include "game.h"
//Other functions
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
			if(::fleet[i].dist(settlement[sett].getPosition())<100)
				if(::fleet[i].Player()==settlement[sett].getOwner()&&!::fleet[i].Speed()){
					if(selected<0)
						selected=i;
					else if(::fleet[i].size()<::fleet[selected].size())
						selected=i;
				}
		}
		if(selected>=0){
			//Add ship
			::fleet[selected].addShip(id,100);
			reloadLabelFleet(selected);
		}else{
			//Create new fleet
			sf::Vector2f pos=map->GetNearestNode(settlement[sett].getPosition()).getPosition();
			add(Fleet(pos,getAngle(settlement[sett].getPosition(),pos),settlement[sett].getOwner(),2,100));
			::fleet[::fleet.size()-1].addShip(id,100);
		}
		//Labels
		reloadLabelPlayer(settlement[sett].getOwner());
		reloadLabelSett(sett);
	}
}
void CombatFleet(short i,short j){
	if(::fleet[i].Power()>::fleet[j].Power()){
		DefeatedFleet(i,j);
	}else{
		DefeatedFleet(j,i);
	}
}
void DefeatedFleet(short i,short j){
	//Change statistics
	Defeated(fleet[i].Player(),fleet[j].Player());
	fleet[i].Supply(fleet[j].Provision()/2.);
	//Labelplayer
	reloadLabelPlayer(fleet[i].Player());
	reloadLabelPlayer(fleet[j].Player());
	//Clear memory
	fleet.erase(fleet.begin()+j);
	//LabelFleet
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
void takeSettlement(short i,short player){
	settlement[i].Conquest(player);
	//LabelSett
	reloadLabelSett(i);
	if(hasImport(i))
		reloadLabelSett(::settlement[i].getImport());
		reloadLabelPlayer(::settlement[::settlement[i].getImport()].getPlayer());
	if(hasExport(i)){
		reloadLabelSett(getImporter(i));
		reloadLabelPlayer(::settlement[getImporter(i)].getPlayer());
	}
	//LabelPlayer
	reloadLabelPlayer(player);
	reloadLabelPlayer(::settlement[i].getPlayer());
	if(player==human||::settlement[i].getPlayer()==human)
		bar->Reload();
}
void MoveFleet(short fleet,sf::Vector2f target){
	if(map->isOnWater(target)&&::fleet[fleet].getTarget()!=target){
		::fleet[fleet].getRoute(map->getRoute(::fleet[fleet].getPosition(),target));
		::fleet[fleet].addNodeRoute(Node(target,60));
	}
}
//Basic
Game::Game(std::string directory,sf::View *view,short human){
	//Begin
	this->battle=NULL;
	this->paused=NULL;
	::human=human;
	//Map
	map=new Map();
	//Music
	audio.changeMusic("data/audio/music/Winds of Ithaca.ogg");
	audio.changeAmbient("data/audio/sound/water.ogg");
	//Reading variables
	short faction,formation,local,import,integrity,m,n,occupied;
	short player,price,ship,size,team,radius;
	int limit,population;
	float angle,coins,provision,x,y;
	std::string name;
	sf::Vector2f pos;
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
		if(player==human){
			pos.x=x;
			pos.y=y;
		}
	}
	//Read players
	in>>n;
	while(n--){
		in>>faction>>coins>>team;
		std::getline(in,name);
		std::getline(in,name);
		add(Player(faction,coins,team,name));
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
			in>>ship>>integrity;
			::fleet.back().addShip(ship,integrity);
		}
		//Route
		in>>m;
		while(m--){
			in>>x>>y>>size;
			::fleet.back().addNodeRoute(Node(x,y,size));
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
	if(labelFleet!=NULL)
		labelFleet->RenderGuides(window);
	//Fleets
	for(unsigned i=0;i<::fleet.size();i++)
		fleet[i].Render(window);
	//Regions
	map->RenderRegions(window);
	//Settlements
	for(unsigned i=0;i<::settlement.size();i++)
		settlement[i].Render(window);
	//About
	if(about)
		about.Render(window);
	//Pause
	if(subMenu==NULL&&this->paused!=NULL){
		window->draw(*this->paused);
	}
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
	if(labelSett!=NULL)
		if(labelSett->mouseOver())
			return 1;
	if(labelPlayer!=NULL)
		if(labelPlayer->mouseOver())
			return 1;
	if(labelFleet!=NULL)
		if(labelFleet->mouseOver())
			return 1;
	if(labelDip!=NULL)
		if(labelDip->mouseOver())
			return 1;
	return (bar->mouseOver());
}
void Game::gameGUI(sf::RenderWindow *window,sf::View *view){
	//View
	this->moveCamera(window,view,8);
	if(labelFleet!=NULL){
		labelFleet->reload();
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
			if(this->paused==NULL){
				this->paused=new sf::Text(sf::String("PAUSED"),*gui.Font(),36);
				this->paused->setPosition(gui.x+gui.width(50)-100,gui.y+gui.height(50)-36);
				this->paused->setColor(sf::Color(255,255,255));
			}else{
				delete this->paused;
				this->paused=NULL;
			}
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
			if(month%3==0)
				labelFleet->getRoute();
			labelFleet->Update();
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
		//Gameplay
		if(!this->mouseOverGUI()){
			//Selected fleet
			if(labelFleet!=NULL){
				if(labelFleet->fleet().Player()==human){
					if(gui.canRight(400)&&distSquare(labelFleet->fleet().getTarget(),gui.mousePosition())>=64){
						MoveFleet(labelFleet->Selected(),gui.mousePosition());
					}
				}
			}
			//Settlements
			for(unsigned i=0;i<::settlement.size();i++){
				if(settlement[i].mouseOver()){
					about.show(
						::player[settlement[i].getOwner()].Name()+"'s settlement"+getDiplomaticStatus(settlement[i].getOwner()),
						settlement[i].getPopulationString()+" freemen  "+settlement[i].getGrowthString()+" growth  "+Format(getIncomeOf(i))+" income\n"+EconomicStatus(i)
					);
					if(settlement[i].left())
						selectSett(i);
					return ;
				}
			}
			//Fleets
			for(unsigned i=0;i<::fleet.size();i++)
				if(::fleet[i].left())
					selectFleet(i);
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
	//Pause
	if(this->paused!=NULL)
		this->paused->move(x,y);
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
		return std::to_string(-this->year)+" BC - "+this->getMonthName();
	return std::to_string(this->year)+" AD - "+this->getMonthName();
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
	for(unsigned i=0;i<::player.size();i++)
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
	std::ofstream out("data/game/saved/"+std::to_string(::human)+".txt");
	out<<this->month<<' '<<this->year<<'\n';
	//Write settlements
	out<<::settlement.size()<<'\n';
	for(unsigned i=0;i<::settlement.size();i++){
		out<<::settlement[i].getPosition().x<<' '<<::settlement[i].getPosition().y<<' '<<::settlement[i].getPlayer()<<' '<<::settlement[i].getPopulation()<<' '<<::settlement[i].getLimit()<<' '<<::settlement[i].getGood()<<' '<<::settlement[i].getImport()<<' '<<::settlement[i].getOccupied();
		out<<'\n'<<::settlement[i].getName()<<'\n';
	}
	//Write players
	out<<::player.size()<<'\n';
	for(unsigned i=0;i<::player.size();i++){
		out<<::player[i].Faction()<<' '<<::player[i].Coins()<<' '<<::player[i].Team();
		out<<'\n'<<::player[i].Name()<<'\n';
	}
	//Write fleets
	out<<::fleet.size()<<'\n';
	for(unsigned i=0;i<::fleet.size();i++){
		out<<::fleet[i].getPosition().x<<' '<<::fleet[i].getPosition().y<<' '<<::fleet[i].getRotation()<<' '<<::fleet[i].Player()<<' '<<::fleet[i].Formation()<<' '<<::fleet[i].Provision()<<' '<<::fleet[i].size()<<'\n';
		for(short j=0;j<::fleet[i].size();j++){
			out<<::fleet[i].Ship(j)<<' '<<::fleet[i].Integrity(j)<<' ';
		}
		std::vector<Node> route=::fleet[i].getRoute();
		out<<'\n'<<route.size()<<'\n';
		for(unsigned j=0;j<route.size();j++){
			out<<route[j].getPosition().x<<' '<<route[j].getPosition().y<<' '<<route[j].r()<<' ';
		}
		out<<'\n';
	}
	out.close();
}
//AI
void Game::AI(){
	//Buy ships
	if(this->month%8000==0){
		for(unsigned i=0;i<settlement.size();i++){
			if(!isYourSett(i)){
				if(hasGood(i,1))
					BuyShip(1,i);
				else
					BuyShip(4,i);
			}
		}
	}
	//Attack
	if(this->month%6000==0){
		//Get number of team
		short max=0;
		for(unsigned i=0;i<player.size();i++)
			if(max<player[i].Team())
				max=player[i].Team();
		std::vector<bool> send;
		send.resize(max,0);
		//Send a fleet for each team
		for(unsigned j=0;j<fleet.size();j++){
			if(!isYourFleet(j)&&!send[player[fleet[j].Player()].Team()]){
				short nearest=-1;
				float dist=999999999;
				for(unsigned i=0;i<settlement.size();i++){
					if(i!=j)
						if(isEnemyFleet(i,j)&&fleet[i].size()<fleet[j].size())
							if(dist>fleet[j].dist(fleet[i].getPosition())){
								nearest=i;
								dist=fleet[j].dist(fleet[i].getPosition());
							}
				}
				//Go to the enemy fleet
				if(nearest>=0){
					send[player[fleet[j].Player()].Team()]=1;
					MoveFleet(j,fleet[nearest].getPosition());
					fleet[j].Reform(1);
				}
			}
		}
	}
}
//Battle
void Game::newBattle(short yourFleet,short enemyFleet,sf::View *view){
	//Select scene
	this->moveViewTo(view,sf::Vector2f(0,0));
	this->battle=new Battle(yourFleet,enemyFleet,view);
	gui.selected=5;
}
void Game::afterBattle(sf::View *view){
	//Move view
	moveViewTo(view,::fleet[this->battle->fleets[0]].getPosition());
	//Statistics
	if(::fleet[this->battle->fleets[0]].size())
		DefeatedFleet(this->battle->fleets[0],this->battle->fleets[1]);
	else
		DefeatedFleet(this->battle->fleets[1],this->battle->fleets[0]);
	bar->Reload();
	//Clear memory
	delete this->battle;
	this->battle=NULL;
}
//Update
void Game::Update(sf::RenderWindow *window,sf::View *view){
	//After the battle
	if(this->battle!=NULL)
		this->afterBattle(view);
	//GUI
	this->gameGUI(window,view);
	//Gameplay
	if(subMenu==NULL&&this->paused==NULL){
		//Clock
		this->Clock();
		//Fleets
		for(unsigned i=0;i<::fleet.size();i++){
			//Move
			::fleet[i].Update();
			//Provision
			if(::fleet[i].Provision()<=0){
				if(isSelectedFleet(i))
					deselectFleet();
				::fleet.erase(::fleet.begin()+i);
			}
			//Combat
			for(unsigned j=0;j<::fleet.size();j++){
				if(i!=j){
					if(isEnemyFleet(i,j)&&distFleet(i,j)<=90){
						//Human fleet and AI fleet
						if(isYourFleet(i)){
							this->newBattle(i,j,view);
							break;
						//AI fleets
						}else if(!isYourFleet(j))
							CombatFleet(i,j);
					}
				}
			}
		}
		//Settlements
		for(unsigned i=0;i<::settlement.size();i++){
			//Interactions fleets
			if(isFree(i))
				for(unsigned j=0;j<::fleet.size();j++){
					if(::fleet[j].dist(settlement[i].getPosition())<90){
						//Conquest
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