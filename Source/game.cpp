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
		::settlement[i].Render(window);
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
	detail.setText(gui.Format(::player[human].Coins())+" coins  "+gui.Format(getPopulation(human))+" freemen");
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
	info.hide();
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
		::player[i].Income(getIncome(i)-getShips(i)/10.);
	//Settlements
	for(short i=0;i<(short)::settlement.size();i++)
		::settlement[i].Monthly();
	//GUI
	this->showHumanStatus();
	this->showData();
	//Label for settlement, player, fleet
	if(labelSett!=NULL){
		this->selectSett(labelSett->Selected());
	}
	else if(labelPlayer!=NULL){
		this->selectPlayer(labelPlayer->Selected());
	}
	else if(labelFleet!=NULL){
		this->selectFleet(labelFleet->Selected());
	}
	//Diplomacy label
	if(labelDip!=NULL){
		labelDip->showData(labelDip->Selected());
	}
}
//AI
void Game::AI(){

}
void Game::getRoute(short fleet){
	//Route
	std::vector<short> route=map->getRoute(
		map->getNearestNode(::fleet[fleet].getPosition()),
		map->getNearestNode(gui.mousePosition())
	);
	::fleet[fleet].Stop();
	while(route.size()){
		::fleet[fleet].addNodeRoute(map->getNode(route[0]));
		route.erase(route.begin());
	}
	::fleet[fleet].addNodeRoute(Node(gui.mousePosition().x,gui.mousePosition().y,60));
}
void Game::lostFleet(short i){
	::player[::fleet[this->battle->fleets[i]].Player()].LostBattle();
	//GUI
	if(labelFleet!=NULL)
		if(labelFleet->Selected()==this->battle->fleets[i]){
			deselectFleet();
		}
	if(labelPlayer!=NULL)
		if(labelPlayer->Selected()==::fleet[this->battle->fleets[i]].Player()){
			selectPlayer(labelPlayer->Selected());
		}
	if(labelDip!=NULL)
		deselectDip();
	//Empty memory
	::fleet.erase(::fleet.begin()+this->battle->fleets[i]);
	for(short j=i+1;j<(short)this->battle->fleets.size();j++)
		if(this->battle->fleets[i]<this->battle->fleets[j])
			this->battle->fleets[j]--;
}
void Game::buyShip(short id,short sett){
	if(id<0||id>(short)naval.size())
		return ;
	if(!::player[::settlement[sett].getOwner()].canBuy(naval[id].Cost()))
		return ;
	if(::settlement[sett].canRecruit(naval[id].Rowers())){
		//Pay and recruit
		::player[::settlement[sett].getOwner()].Income(-naval[id].Cost());
		::settlement[sett].Recruit(naval[id].Rowers());
		//Labels
		if(isYourSett(sett))
			this->showHumanStatus();
		if(isSelectedSett(sett))
			selectSett(labelSett->Selected());
		//Add ship to fleet from port
		for(short i=0;i<(short)::fleet.size();i++){
			if(
				::dist(::fleet[i].getPosition(),::settlement[sett].getPosition())<70&&
				::fleet[i].Player()==::settlement[sett].getOwner()
			){
				::fleet[i].addShip(id,100);
				return ;
			}
		}
		//Create new fleet
		::fleet.push_back(Fleet(::settlement[sett].getPosition(),::settlement[sett].getOwner(),0,2,100));
		::fleet[::fleet.size()-1].addShip(id,100);
	}
}
//Update
void Game::Update(sf::RenderWindow *window,sf::View *view){
	//After the battle
	if(this->battle!=NULL){
		//Change statistics
		for(short i=0;i<(short)this->battle->fleets.size();i++)
			if(::fleet[this->battle->fleets[i]].size()){
				::player[::fleet[this->battle->fleets[i]].Player()].WonBattle();
				//Move camera to battle location
				moveViewTo(view,::fleet[i].getPosition());
			}else{
				lostFleet(this->battle->fleets[i]);
			}
		//Clear memory
		delete this->battle;
		this->battle=NULL;
		void showData();
		void showHumanStatus();
	}
	//GUI
	about.hide();
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
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)||this->main->left(::player[::human].Name(),"Click or press F for to see economic and military status of your city-state."))
			this->selectPlayer(::human);
		//Label of selected settlement, player, fleet...
		if(labelSett!=NULL){
			//Ship
			buyShip(labelSett->getShip(),labelSett->Selected());
			//Local good
			if(labelSett->localMouseOver()){
				about.show(
					good[::labelSett->sett().getGood()].Name()+" to "+(::settlement[getImporter(labelSett->Selected())].getName()),
					goodDescription(::labelSett->sett().getGood())
				);
				if(labelSett->localLeft()){
					this->moveViewTo(view,settlement[getImporter(labelSett->Selected())].getPosition());
					selectSett(getImporter(labelSett->Selected()));
				}
			}
			//Import good
			if(labelSett->importMouseOver()){
				about.show(
					good[getImportedGood(labelSett->Selected())].Name()+" from "+::settlement[::labelSett->sett().getImport()].getName(),
					goodDescription(getImportedGood(labelSett->Selected()))
				);
				if(labelSett->importLeft()){
					this->moveViewTo(view,settlement[labelSett->sett().getImport()].getPosition());
					selectSett(labelSett->sett().getImport());
				}
			}
			//Owner
			if(labelSett->playerLeft()){
				this->selectPlayer(::labelSett->sett().getOwner());
			}else if(labelSett->right()){
				deselectSett();
			}
		}
		if(labelPlayer!=NULL){
			if(labelPlayer->right())
				deselectPlayer();
		}
		if(labelFleet!=NULL){
			if(labelFleet->right())
				deselectFleet();
			else if(labelFleet->playerLeft()){
				this->selectPlayer(labelFleet->fleet().Player());
			}else if(!this->mouseOverGUI()&&gui.canRight(100)&&isYourFleet(labelFleet->Selected())){
				this->getRoute(labelFleet->Selected());
			}	
		}
		if(labelDip!=NULL){
			labelDip->Update();
			if(labelDip->right()){
				deselectDip();
			}
		}
	}
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
				::settlement[i].Update();
				if(!this->mouseOverGUI())
					if(::settlement[i].left())
						this->selectSett(i);
				//Conquest
				for(short j=0;j<(short)::fleet.size();j++){
					if(
						areEnemies(::settlement[i].getOwner(),::fleet[j].Player())&&
						dist(::settlement[i].getPosition(),::fleet[j].getPosition())<80
					){
						//Conquest
						::settlement[i].Conquest(::fleet[j].Player());
						//Labels
						showHumanStatus();
						if(isSelectedSett(i))
							selectSett(i);
					}
				}
			}
			//Fleets
			for(short i=0;i<(short)::fleet.size();i++){
				::fleet[i].Update();
				if(!this->mouseOverGUI())
					if(::fleet[i].left())
						this->selectFleet(i);
				//Into to battle
				if(isYourFleet(i))
					for(short j=0;j<(short)::fleet.size();j++){
						if(i!=j)
							if(isEnemyFleet(i,j)&&distFleet(i,j)<=70){
								this->moveViewTo(view,sf::Vector2f(0,0));
								this->battle=new Battle(i,j,view);
								gui.selected=5;
								break;
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
