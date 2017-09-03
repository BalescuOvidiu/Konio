#include "game.h"
//Basic
Game::Game(std::string directory,sf::View *view,short human){
	//Begin
	this->battle=NULL;
	this->pause=0;
	::human=human;
	//Map
	map=new Map();
	//GUI
	this->subMenu=new SubMenu();
	this->submenu=new Button("data/game/icons//menu.png",275,185);
	this->diplomacy=new Button("data/game/icons//diplomacy.png",160,185);
	this->main=new Button("data/game/icons/"+std::to_string(human)+".png",45,185);
	this->text=new sf::Text(sf::String(""),*gui.Font(),36);
	this->text->setPosition(gui.width(50)-100,gui.height(50)-36);
	this->text->setColor(sf::Color(255,255,255));
	detail.show();
	//Music
	audio.changeMusic("data/audio/music/Winds of Ithaca.ogg");
	audio.changeAmbient("data/audio/sound/water.ogg");
	//Reading variables
	short faction,formation,local,import,integrity,m,n,occupied;
	short player,price,ship,size,team,radius,x,y;
	int limit,population,rate;
	float angle,coins,provision;
	std::string name;
	sf::Vector2f pos;
	//Read data from file
	std::ifstream in(directory.c_str());
	in>>month>>year;
	//Read regions
	in>>n;
	while(n--){
		in>>x>>y>>size;
		std::getline(in,name);
		std::getline(in,name);
		map->add(Region(x,y,size,name));
	}
	//Read settlements
	in>>n;
	while(n--){
		//Get data of settlement
		in>>x>>y>>player>>population>>limit>>rate>>local>>import>>occupied;
		std::getline(in,name);
		std::getline(in,name);
		::settlement.push_back(Settlement(x,y,player,population,limit,rate,local,import,occupied,name));
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
		::player.push_back(Player(faction,coins,team,name));
	}
	//Read fleets
	in>>n;
	while(n--){
		in>>x>>y>>angle>>player>>formation;
		in>>provision;
		in>>m;
		::fleet.push_back(Fleet(sf::Vector2f(x,y),angle,player,formation,provision));
		while(m--){
			in>>ship>>integrity;
			::fleet.back().addShip(ship,integrity);
		}
	}
	//Read graph
	while(in>>x>>y>>radius)
		map->add(Node(x,y,radius));
	in.close();
	//Read goods
	in.open("data/game/goods/data.txt");
	while(in>>price){
		std::getline(in,name);
		std::getline(in,name);
		good.push_back(Good(name,price));
	}
	in.close();
	//Human player GUI
	this->showHumanStatus();
	this->showData();
	this->moveViewTo(view,pos);
}
//Rendering
void Game::Render(sf::RenderWindow *window){
	//Map
	map->Render(window);
	//Settlements
	for(short i=0;i<(short)::settlement.size();i++)
		settlement[i].Render(window);
	//Fleets
	for(short i=0;i<(short)::fleet.size();i++)
		::fleet[i].Render(window);
	//About
	if(about)
		about.Render(window);
	//Pause
	if(this->pause&&!(*this->subMenu)){
		window->draw(*this->text);
	}
	//GUI
	if(*this->subMenu){
		this->subMenu->Render(window);
		if(op)
			op.Render(window);
	}else{
		if(detail)
			detail.Render(window);
		this->main->Render(window);
		this->diplomacy->Render(window);
		this->submenu->Render(window);
		//Label of selected settlement, player, fleet...
		if(labelSett!=NULL)
			labelSett->Render(window);
		else if(labelPlayer!=NULL)
			labelPlayer->Render(window);
		else if(labelFleet!=NULL)
			labelFleet->Render(window);
		if(labelDip!=NULL)
			labelDip->Render(window);
	}
}
//GUI
void Game::showDiplomaticStatus(short player){
	if(labelDip==NULL)
		labelDip=new LabelDip();
	labelDip->showData(player);
}
void Game::showHumanStatus(){
	detail.setText(gui.Format(player[human].Coins())+" coins  "+gui.Format(getPopulation(human))+" freemen");
	detail.hide();
	detail.show();
}
void Game::showData(){
	if(year<0)
		detail.setTitle(std::to_string(-this->year)+" BC - "+this->getMonthName());
	else
		detail.setTitle(std::to_string(this->year)+" AD - "+this->getMonthName());
	detail.hide();
	detail.show();
}
void Game::deselectAll(){
	deselectPlayer();
	deselectSett();
	deselectFleet();
}
void Game::selectPlayer(short player){
	this->deselectAll();
	labelPlayer=new LabelPlayer(player);
}
void Game::selectFleet(short fleet){
	this->deselectAll();
	labelFleet=new LabelFleet(fleet);
}
void Game::selectSett(short sett){
	this->deselectAll();
	labelSett=new LabelSett(sett);
}
bool Game::mouseOverGUI(){
	if(labelSett!=NULL){
		if(labelSett->mouseOver())
			return 1;
	}else if(labelPlayer!=NULL){
		if(labelPlayer->mouseOver())
			return 1;
	}else if(labelFleet!=NULL){
		if(labelFleet->mouseOver())
			return 1;
	}
	if(labelDip!=NULL)
		if(labelDip->mouseOver())
			return 1;
	return (detail.mouseOver());
}
void Game::gameGUI(sf::RenderWindow *window,sf::View *view){
	if(*this->subMenu){
		//Options
		if(op)
			op.Update();
		//Submenu
		this->subMenu->Update(window);
	}else{
		//Key
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)||this->submenu->left("Menu","Click or press M for menu.\nPress P for pause."))
			this->subMenu->show();
		//Diplomacy label
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)||this->diplomacy->left("Diplomacy","Click or press R to see relations with other city-states."))
			labelDip=new LabelDip();
		//Human faction
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)||this->main->left(player[::human].Name(),"Click or press F for to see economic and military status of your city-state."))
			this->selectPlayer(::human);
		//Label of selected settlement, player, fleet...
		if(labelSett!=NULL){
			//Ship
			buyShip(labelSett->getShip(),labelSett->Selected());
			//Local good
			if(labelSett->localMouseOver()){
				about.show();
				//Title
				if(isBlockedExport(labelSett->Selected()))
					about.setTitle(good[labelSett->sett().getGood()].Name()+" to "+(settlement[getImporter(labelSett->Selected())].getName())+" (blocked)");
				else
					about.setTitle(good[labelSett->sett().getGood()].Name()+" to "+(settlement[getImporter(labelSett->Selected())].getName()));
				//Text
				about.setText(goodDescription(labelSett->sett().getGood()));
				//Left button
				if(labelSett->localLeft()){
					this->moveViewTo(view,settlement[getImporter(labelSett->Selected())].getPosition());
					selectSett(getImporter(labelSett->Selected()));
				}
			}
			//Import good
			if(labelSett->importMouseOver()){
				about.show();
				//Title
				if(isBlockedImport(labelSett->Selected()))
					about.setTitle(good[getImportedGood(labelSett->Selected())].Name()+" from "+settlement[labelSett->sett().getImport()].getName()+ "(blocked)");
				else
					about.setTitle(good[getImportedGood(labelSett->Selected())].Name()+" from "+settlement[labelSett->sett().getImport()].getName());
				//Text
				about.setText(goodDescription(getImportedGood(labelSett->Selected())));
				//Left button
				if(labelSett->importLeft()){
					this->moveViewTo(view,settlement[labelSett->sett().getImport()].getPosition());
					selectSett(labelSett->sett().getImport());
				}
			}
			//Deselect
			if(labelSett->playerLeft()){
				this->selectPlayer(labelSett->sett().getOwner());
			}else if(labelSett->right()){
				deselectSett();
			}
		}
		//Label player
		else if(labelPlayer!=NULL){
			if(labelPlayer->right())
				deselectPlayer();
		}
		//Label fleet
		else if(labelFleet!=NULL){
			if(isYourFleet(labelFleet->Selected())){
				//Move
				if(!this->mouseOverGUI()&&gui.canRight(100))
					this->getRoute(labelFleet->Selected(),gui.mousePosition());
				//Formation
				if(labelFleet->FormationUpdate())
					reloadLabelFleet(labelFleet->Selected());
			}
			//Deselect
			if(labelFleet->playerLeft()){
				this->selectPlayer(labelFleet->fleet().Player());
			}else if(labelFleet->right())
				deselectFleet();
		}
		//Label diplomacy
		if(labelDip!=NULL){
			labelDip->Update();
			if(labelDip->right()){
				deselectDip();
			}
		}
	}
}
//View
void Game::moveView(sf::View *view,float x,float y){
	if(gui.x+x<0||gui.x+x>4000-view->getSize().x)
		x=0;
	if(gui.y+y<0||gui.y+y>2000-view->getSize().y)
		y=0;
	if((!x)&&(!y))
		return ;
	//Move
	gui.x+=x;
	gui.y+=y;
	about.move(x,y);
	detail.move(x,y);
	op.move(x,y);
	view->move(x,y);
	this->text->move(x,y);
	this->subMenu->move(x,y);
	this->main->move(x,y);
	this->diplomacy->move(x,y);
	this->submenu->move(x,y);
	map->move(x,y);
	//Label of selected settlement, player, fleet...
	if(labelSett!=NULL)
		labelSett->move(x,y);
	else if(labelPlayer!=NULL)
		labelPlayer->move(x,y);
	else if(labelFleet!=NULL)
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
	if(pos.x>4000-gui.width()/2)
		pos.x=4000-gui.width()/2;
	if(pos.y>2000-gui.height()/2)
		pos.y=2000-gui.height()/2;
	//Move view to point pos
	moveView(view,pos.x-gui.width()/2,pos.y-gui.height()/2);
}
void Game::moveCamera(sf::RenderWindow *window,sf::View *view){
	//View and camera
	sf::Vector2f camera=gui.mousePosition();
	if((short)camera.x<0)
		camera.x=0;
	if((short)camera.y<0)
		camera.y=0;
	//Move camera by mouse cursor
	if(camera.x<window->getSize().x/20+gui.x&&!this->mouseOverGUI())
		this->moveView(view,-6,0);
	if(camera.x>window->getSize().x*19/20+gui.x)
		this->moveView(view,6,0);
	if(camera.y<window->getSize().y/10+gui.y&&!this->mouseOverGUI())
		this->moveView(view,0,-6);
	if(camera.y>window->getSize().y*9/10+gui.y){
		this->moveView(view,0,6);
	}
	//Move camera by key
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->moveView(view,-6,0);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->moveView(view,6,0);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->moveView(view,0,-6);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->moveView(view,0,6);
}
//Status
void Game::Reset(sf::RenderWindow *window,sf::View *view){
	//GUI
	op.hide();
	detail.hide();
	about.hide();
	this->moveView(view,-gui.x,-gui.y);
	//Empty memory
	deselectDip();
	deselectAll();
	::settlement.clear();
	::player.clear();
	::fleet.clear();
	::good.clear();
	//Audio
	audio.stopAmbient();
	audio.changeMusic("data/audio/music/Athena.ogg");
}
bool Game::Pause(){
	this->text->setString(sf::String("PAUSED"));
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
		this->pause=!this->pause;
		sf::sleep(sf::Time(sf::milliseconds(100)));
	}
	return this->pause;
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
void Game::Clock(){
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
	for(short i=0;i<(short)::player.size();i++)
		player[i].Income(getIncome(i)-getShips(i)/10.);
	//Settlements
	for(short i=0;i<(short)::settlement.size();i++)
		settlement[i].Monthly();
	//GUI
	this->showHumanStatus();
	this->showData();
	//Label for settlement, player, fleet
	if(labelSett!=NULL)
		selectSett(labelSett->Selected());
	if(labelPlayer!=NULL)
		selectPlayer(labelPlayer->Selected());
	if(labelFleet!=NULL)
		selectFleet(labelFleet->Selected());
	//Diplomacy label
	if(labelDip!=NULL)
		labelDip->showData(labelDip->Selected());
}
//AI
void Game::AI(){
	//Buy ships
	if(this->month%8000==0){
		for(short i=0;i<(short)settlement.size();i++){
			if(!isYourSett(i)){
				if(hasGood(i,1))
					this->buyShip(1,i);
				else
					this->buyShip(4,i);
			}
		}
	}
	//Attack
	if(this->month%6000==0){
		//Get number of team
		short max=0;
		for(short i=0;i<(short)player.size();i++)
			if(max<player[i].Team())
				max=player[i].Team();
		std::vector<bool> send;
		send.resize(max,0);
		//Send a fleet for each team
		for(short j=0;j<(short)fleet.size();j++){
			if(!isYourFleet(j)&&!send[player[fleet[j].Player()].Team()]){
				short nearest=-1;
				float dist=999999999;
				for(short i=0;i<(short)settlement.size();i++){
					if(i!=j)
						if(isEnemyFleet(i,j)&&fleet[i].size()<fleet[j].size())
							if(dist>fleet[j].dist(fleet[i].getPosition())){
								nearest=i;
								dist=fleet[j].dist(fleet[i].getPosition());
							}
				}
				//Go to the enemy settlement
				if(nearest>=0){
					send[player[fleet[j].Player()].Team()]=1;
					getRoute(j,fleet[nearest].getPosition());
					break;
				}
			}
		}
	}
}
void Game::getRoute(short fleet,sf::Vector2f target){
	//Route
	::fleet[fleet].getRoute(map->getRoute(
		map->getNearestNode(::fleet[fleet].getPosition()),
		map->getNearestNode(target)
	));
	//Point of target
	::fleet[fleet].addNodeRoute(Node(target.x,target.y,60));
}
void Game::buyShip(short id,short sett){
	//Check if id is valid
	if(id<0||id>(short)naval.size())
		return ;
	//Check if player has enough coins
	if(!player[settlement[sett].getOwner()].canBuy(naval[id].Cost()))
		return ;
	//Check if settlement has enough population
	if(settlement[sett].canRecruit(naval[id].Rowers())){
		//Pay and recruit
		player[settlement[sett].getOwner()].Income(-naval[id].Cost());
		settlement[sett].Recruit(naval[id].Rowers());
		//Labels
		if(isYourSett(sett))
			this->showHumanStatus();
		reloadLabelPlayer(settlement[sett].getOwner());
		if(labelSett!=NULL)
			reloadLabelSett(labelSett->Selected());
		//Add ship to fleet from port
		for(short i=0;i<(short)::fleet.size();i++){
			if(::fleet[i].dist(settlement[sett].getPosition())<100)
				if(::fleet[i].Player()==settlement[sett].getOwner()){
					::fleet[i].addShip(id,100);
					reloadLabelFleet(i);
					return ;					
				}
		}
		//Create new fleet
		::fleet.push_back(Fleet(map->getNode(map->getNearestNode(settlement[sett].getPosition())).getPosition(),0,settlement[sett].getOwner(),2,100));
		::fleet[::fleet.size()-1].addShip(id,100);
	}
}
//Update
void Game::Update(sf::RenderWindow *window,sf::View *view){
	//After the battle
	if(this->battle!=NULL){
		//Change statistics
		for(short i=0;i<(short)this->battle->fleets.size();i++){
			//Labels
			reloadLabelPlayer(::fleet[this->battle->fleets[i]].Player());
			reloadLabelFleet(this->battle->fleets[i]);
			reloadLabelDip(::fleet[this->battle->fleets[i]].Player());
			//Statistics
			if(::fleet[this->battle->fleets[i]].size())
				player[::fleet[this->battle->fleets[i]].Player()].WonBattle();
			else
				player[::fleet[this->battle->fleets[i]].Player()].LostBattle();
		}
		//Move view
		moveViewTo(view,::fleet[this->battle->fleets[0]].getPosition());
		//Clear memory
		for(short i=0;i<(short)::fleet.size();i++)
			if(!::fleet[i].size()){
				//Labels
				if(isSelectedFleet(i))
					deselectFleet();
				reloadLabelPlayer(::fleet[i].Player());
				reloadLabelDip(::fleet[i].Player());
				::fleet.erase(::fleet.begin()+i);
				i--;
			}
		delete this->battle;
		this->battle=NULL;
		//GUI
		showData();
		showHumanStatus();
	}
	//GUI
	about.hide();
	if(gui.timeElapsed(200))
		this->gameGUI(window,view);
	//Gameplay
	if(!this->Pause()){
		//View
		this->moveCamera(window,view);
		//Clock
		this->Clock();
		if(!(*this->subMenu)){
			//Map
			map->Update();
			//Settlements
			for(short i=0;i<(short)::settlement.size()&&!this->mouseOverGUI();i++){
				//GUI
				settlement[i].Update();
				if(!this->mouseOverGUI())
					if(settlement[i].left())
						this->selectSett(i);
				//Interactions with fleets
				for(short j=0;j<(short)::fleet.size();j++){
					//Near fleets
					if(dist(settlement[i].getPosition(),::fleet[j].getPosition())<100){
						//Conquest
						if(areEnemies(settlement[i].getOwner(),::fleet[j].Player())){
							settlement[i].Conquest(::fleet[j].Player());
							reloadLabelSett(i);
							reloadLabelSett(::settlement[i].getImport());
							reloadLabelSett(getImporter(i));
						//Supply
						}else{
							::fleet[j].Supply();
						}
						showHumanStatus();
						reloadLabelFleet(j);
					}						
				}
			}
			//Fleets
			for(short i=0;i<(short)::fleet.size();i++){
				//Move
				::fleet[i].Update();
				//Provision
				if(::fleet[i].Provision()<=0){
					if(isSelectedFleet(i))
						deselectFleet();
					::fleet.erase(::fleet.begin()+i);
				}
				//Label
				if(gui.timeElapsed(200))
					reloadLabelFleet(i);
				//Mouse
				if(!this->mouseOverGUI())
					if(::fleet[i].left()){
						this->selectFleet(i);
					}
				//Into to battle
				for(short j=0;j<(short)::fleet.size();j++){
					if(i!=j){
						if(isEnemyFleet(i,j)&&distFleet(i,j)<=70){
							//Human fleet and AI fleet
							if(isYourFleet(i)){
								this->moveViewTo(view,sf::Vector2f(0,0));
								this->battle=new Battle(i,j,view);
								gui.selected=5;
								break;
							//AI fleets
							}else if(!isYourFleet(j)){
								if(fleet[i].size()>fleet[j].size()){
									//Clear memory
									fleet.erase(fleet.begin()+j);
									//Change statistics
									Defeated(i,j);
								}else{
									//Clear memory
									fleet.erase(fleet.begin()+i);
									//Change statistics
									Defeated(j,i);								
								}
							}
						}
					}					
				}
			}
		}
	}
	//Exit from game
	if(gui.selected==2)
		this->Reset(window,view);
}
Game::~Game(){

}