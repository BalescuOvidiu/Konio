#include "game.h"
//Basic
Game::Game(std::string directory,sf::View *view,short human){
	//Begin
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
	short faction,formation,limit,local,import,integrity,m,n,occupied,player,population,price,ship,size,team,radius,x,y;
	float angle,coins,provision;
	std::string name;
	int rate;
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
		::fleet.push_back(Fleet(sf::Vector2f(x,y),angle,player,::player[player].Faction(),formation,provision));
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
	//GUI
	if(*this->subMenu){
		this->subMenu->Render(window);
		if(op)
			op.Render(window);
	}else{
		//Diplomacy label
		if(info){
			info.Render(window);
			for(short i=0;i<(short)dip.size();i++)
				dip[i].Render(window);
		}
		if(detail)
			detail.Render(window);
		this->main->Render(window);
		this->diplomacy->Render(window);
		this->submenu->Render(window);
		//Label of selected settlement, player, fleet
		if(labelSett!=NULL)
			labelSett->Render(window);
		else if(labelPlayer!=NULL)
			labelPlayer->Render(window);
		else if(labelFleet!=NULL)
			labelFleet->Render(window);
	}
	if(this->pause&&!(*this->subMenu)){
		window->draw(*this->text);
	}
}
//GUI
void Game::showDiplomaticStatus(short player){
	info.setText("\n\n\n\n\n\n\n\n\n"+::player[player].Name()+getDiplomaticStatus(player)+"\n"+::player[player].Coins()+" coins\n"+std::to_string(getPopulation(player))+" freeman\n"+std::to_string(getShips(player))+" ships");
}
void Game::showHumanStatus(){
	detail.setText(::player[human].Coins()+" coins  "+std::to_string(getPopulation(human))+" freeman");
}
void Game::showData(){
	if(year<0)
		detail.setTitle(std::to_string(-this->year)+" BC - "+this->getMonthName());
	else
		detail.setTitle(std::to_string(this->year)+" AD - "+this->getMonthName());
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
	}
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
	//Diplomacy label
	info.move(x,y);
	for(short i=0;i<(short)dip.size();i++)
		dip[i].move(x,y);
	//Label of selected settlement, player, fleet
	if(labelSett!=NULL)
		labelSett->move(x,y);
	else if(labelPlayer!=NULL)
		labelPlayer->move(x,y);
	else if(labelFleet!=NULL)
		labelFleet->move(x,y);
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
	//Get to initial position
	this->moveView(view,-gui.x,-gui.y);
	//Empty memory
	::player.clear();
	good.clear();
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
	//Label for settlement, player, fleet
	if(labelSett!=NULL){

	}
	if(labelPlayer!=NULL){
		this->selectPlayer(labelPlayer->Selected());
	}
	//AI
}
void Game::Monthly(){
	//Income
	for(short i=0;i<(short)::player.size();i++)
		::player[i].coins+=getIncome(i);
	//Settlements
	for(short i=0;i<(short)::settlement.size();i++)
		::settlement[i].Monthly();
	//GUI
	this->showHumanStatus();
	this->showData();
	//Label of selected settlement, player, fleet
	if(labelSett!=NULL)
		this->selectSett(labelSett->Selected());
	else if(labelPlayer!=NULL)
		this->selectPlayer(labelPlayer->Selected());
}
//Update
void Game::Update(sf::RenderWindow *window,sf::View *view){
	//GUI
	about.hide();
	if(info){
		if(info.right()){
			dip.clear();
			info.hide();
		}
		//Diplomacy label
		for(short i=0;i<(short)player.size();i++)
			if(dip[i].left())
				this->showDiplomaticStatus(i);
	}
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
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)||this->diplomacy->left("Diplomacy","Click or press R to see relations with other city-states.")){
			info.show("Diplomacy","");
			if(!this->dip.size())
				for(short i=0;i<(short)player.size();i++){
					this->dip.push_back(Button("data/game/icons/"+std::to_string(i)+".png",gui.x+gui.width(50)-250+100*i%600,gui.y+gui.height(50)-100+100*(short)(i/6)));
				}
		}
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::F)||this->main->left(::player[human].Name(),"Click or press F for to see economic and military status of your city-state."))
			this->selectPlayer(human);
		//Label of selected settlement, player, fleet
		if(labelSett!=NULL){
			if(labelSett->localMouseOver()){
				about.show(good[::settlement[labelSett->Selected()].getGood()].Name(),goodDescription(::settlement[labelSett->Selected()].getGood()));
			}
			if(labelSett->importMouseOver()){
				about.show(good[getImportedGood(labelSett->Selected())].Name()+" from "+::settlement[::settlement[labelSett->Selected()].getImport()].getName(),goodDescription(getImportedGood(labelSett->Selected())));
				if(labelSett->importLeft()){
					this->moveViewTo(view,settlement[settlement[labelSett->Selected()].getImport()].getPosition());
					selectSett(settlement[labelSett->Selected()].getImport());
					sf::sleep(sf::Time(sf::milliseconds(200)));
				}
			}
			if(labelSett->playerLeft()){
				this->selectPlayer(::settlement[labelSett->Selected()].getPlayer());
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
			else if(sf::Mouse::isButtonPressed(sf::Mouse::Right)&&::fleet[labelFleet->Selected()].Player()==human){
				short begin=map->getNearestNode(::fleet[labelFleet->Selected()].Origin());
				short end=map->getNearestNode(gui.mousePosition());
				std::vector<short> route=map->getRoute(begin,end);
				::fleet[labelFleet->Selected()].Stop();
				while(route.size()){
					::fleet[labelFleet->Selected()].addNodeRoute(map->getNode(route[0]).Pos());
					route.erase(route.begin());
				}
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
				::settlement[i].Update();
				if(::settlement[i].left())
					this->selectSett(i);
			}
			//Fleets
			for(short i=0;i<(short)::fleet.size();i++){
				::fleet[i].Update();
				if(::fleet[i].left())
					this->selectFleet(i);
			}
		}
	}
	//Exit from game
	if(gui.selected==2){
		//Audio
		audio.stopAmbient();
		audio.changeMusic("data/audio/music/Athena.ogg");
		//View
		this->moveView(view,-gui.x,-gui.y);
		//GUI
		op.hide();
		detail.hide();
		sf::sleep(sf::Time(sf::milliseconds(200)));
	}
}
Game::~Game(){

}
