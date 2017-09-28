#include "game.h"
//Basic
Game::Game(std::string directory,sf::View *view,short human){
	//Begin
	this->battle=NULL;
	this->paused=NULL;
	::human=human;
	//Map
	map=new Map();
	//GUI
	this->subMenu=new SubMenu();
	this->submenu=new Button("data/game/icons/menu.png",275,132);
	this->diplomacy=new Button("data/game/icons/diplomacy.png",160,132);
	this->main=new Button("data/game/icons/"+std::to_string(human)+".png",45,132);
	this->coins=new LabelIcon(10,50,"data/game/icons/coins.png");
	this->pop=new LabelIcon(150,50,"data/game/icons/coins.png");
	detail.show();
	//Range
	this->range=new sf::CircleShape(90,64);
	this->range->setFillColor(sf::Color(255,255,255,64));
	this->range->setOutlineColor(sf::Color(255,255,255,100));
	this->range->setOutlineThickness(1);
	//Music
	audio.changeMusic("data/audio/music/Winds of Ithaca.ogg");
	audio.changeAmbient("data/audio/sound/water.ogg");
	//Reading variables
	short faction,formation,local,import,integrity,m,n,occupied;
	short player,price,ship,size,team,radius;
	int limit,population,rate;
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
	//Range
	if(labelSett!=NULL||labelFleet!=NULL)
		window->draw(*this->range);
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
	if(this->paused!=NULL&&!(*this->subMenu)){
		window->draw(*this->paused);
	}
	//GUI
	if(*this->subMenu){
		this->subMenu->Render(window);
		if(op)
			op.Render(window);
	}else{
		detail.Render(window);
		//Buttons and icons
		this->main->Render(window);
		this->diplomacy->Render(window);
		this->submenu->Render(window);
		this->coins->Render(window);
		this->pop->Render(window);
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
void Game::showHumanStatus(){
	this->coins->setText(gui.Format(player[human].Coins()));
	this->pop->setText(gui.Format(getPopulation(human)));
}
void Game::showData(){
	if(year<0)
		detail.show(std::to_string(-this->year)+" BC - "+this->getMonthName(),"");
	else
		detail.show(std::to_string(this->year)+" AD - "+this->getMonthName(),"");
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
	this->range->setPosition(::fleet[fleet].getPosition().x-90,::fleet[fleet].getPosition().y-90);
	this->deselectAll();
	labelFleet=new LabelFleet(fleet);
}
void Game::selectSett(short sett){
	this->range->setPosition(::settlement[sett].getPosition().x-90,::settlement[sett].getPosition().y-90);
	this->deselectAll();
	labelSett=new LabelSett(sett);
}
void Game::goToSett(sf::View *view,short sett){
	this->moveViewTo(view,settlement[sett].getPosition());
	selectSett(sett);
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
	//Map
	map->Update();
	//View
	this->moveCamera(window,view,8);
	//GUI
	if(labelFleet!=NULL)
		this->range->setPosition(labelFleet->fleet().getPosition().x-90,labelFleet->fleet().getPosition().y-90);
	if(*this->subMenu){
		about.hide();
		//Options
		if(op)
			op.Update();
		//Submenu
		this->subMenu->Update(window);
	}else if(gui.canClick(400)){
		//About
		about.hide();
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
		//Human label
		this->coins->mouseOver("Coins","Coins are used to buy ships and pay marines.\nYou can get coins from populations and trades.");
		this->pop->mouseOver("Population","It's used to recruit marines.\nPopulation increase revenue in your settlements.");
		if(this->submenu->left("Menu","Click or press M for menu.\nPress P for pause.",sf::Keyboard::M))
			this->subMenu->show();
		if(labelDip==NULL){
			if(this->diplomacy->left("Diplomacy","Click or press R to see relations with other city-states.",sf::Keyboard::R))
				labelDip=new LabelDip();
		}else{
			if(this->diplomacy->left("Diplomacy","Click or press R to close diplomacy label.",sf::Keyboard::R))
				deselectDip();
		}
		if(isSelectedPlayer(::human)){
			if(this->main->left(player[::human].Name(),"Click or press F for to close faction label.",sf::Keyboard::F))
				deselectPlayer();
		}else{
			if(this->main->left(player[::human].Name(),"Click or press F for to see your status.",sf::Keyboard::F))
				this->selectPlayer(::human);
		}
		//Label of selected settlement, player, fleet...
		if(labelSett!=NULL){
			//Ship
			buyShip(labelSett->getShip(),labelSett->Selected());
			//Local good
			if(labelSett->localLeft())
				this->goToSett(view,getImporter(labelSett->Selected()));
			//Import good
			if(labelSett->importLeft())
				this->goToSett(view,labelSett->sett().getImport());
			//Deselect
			if(labelSett->playerLeft()){
				this->selectPlayer(labelSett->sett().getOwner());
			}else if(labelSett->right()){
				deselectSett();
			}
		}
		//Label player
		if(labelPlayer!=NULL){
			if(labelPlayer->right())
				deselectPlayer();
		}
		//Label fleet
		if(labelFleet!=NULL){
			if(labelFleet->fleet().Player()==human){
				//Formation
				if(labelFleet->FormationUpdate())
					reloadLabelFleet(labelFleet->Selected());
			}
			//Deselect
			if(labelFleet->playerLeft()){
				this->selectPlayer(labelFleet->fleet().Player());
			}else if(labelFleet->right())
				deselectFleet();
			else
				labelFleet->reload();
		}
		//Label diplomacy
		if(labelDip!=NULL){
			short selected=labelDip->Update();
			if(selected>=0){
				this->selectPlayer(selected);
			}
			if(labelDip->right()){
				deselectDip();
			}
		}
		//Gameplay
		if(!this->mouseOverGUI()){
			//Selected fleet
			if(labelFleet!=NULL){
				if(labelFleet->fleet().Player()==human){
					if(sf::Mouse::isButtonPressed(sf::Mouse::Right)){
						this->getRoute(labelFleet->Selected(),gui.mousePosition());
					}
				}
			}
			//Settlements
			for(short i=0;i<(short)::settlement.size();i++){
				if(settlement[i].mouseOver()){
					about.show(
						::player[settlement[i].getOwner()].Name()+"'s settlement"+getDiplomaticStatus(settlement[i].getOwner()),
						settlement[i].getPopulationString()+" freemen  "+settlement[i].getGrowthString()+" growth  "+gui.Format(getIncomeOf(i))+" income\n"+EconomicStatus(i)
					);
					if(settlement[i].left())
						this->selectSett(i);
					return ;
				}
			}
			//Fleets
			for(short i=0;i<(short)::fleet.size();i++)
				if(::fleet[i].left())
					this->selectFleet(i);
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
	this->subMenu->move(x,y);
	this->main->move(x,y);
	this->diplomacy->move(x,y);
	this->submenu->move(x,y);
	this->coins->move(x,y);
	this->pop->move(x,y);
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
	if(this->mouseOverGUI()&&!(*this->subMenu))
		return ;
	sf::Vector2f camera=gui.mousePosition();
	if((short)camera.x<0)
		camera.x=0;
	if((short)camera.y<0)
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
	reloadLabelDip();
	//Save game
	std::ofstream out("data/game/saved/"+std::to_string(::human)+".txt");
	out<<this->month<<' '<<this->year<<'\n';
	//Write settlements
	out<<::settlement.size()<<'\n';
	for(short i=0;i<(short)::settlement.size();i++){
		out<<::settlement[i].getPosition().x<<' '<<::settlement[i].getPosition().y<<' '<<::settlement[i].getPlayer()<<' '<<::settlement[i].getPopulation()<<' '<<::settlement[i].getLimit()<<' '<<(int)(::settlement[i].getRate()*100)<<' '<<::settlement[i].getGood()<<' '<<::settlement[i].getImport()<<' '<<::settlement[i].getOccupied();
		out<<'\n'<<::settlement[i].getName()<<'\n';
	}
	//Write players
	out<<::player.size()<<'\n';
	for(short i=0;i<(short)::player.size();i++){
		out<<::player[i].Faction()<<' '<<::player[i].Coins()<<' '<<::player[i].Team();
		out<<'\n'<<::player[i].Name()<<'\n';
	}
	//Write fleets
	out<<::fleet.size()<<'\n';
	for(short i=0;i<(short)::fleet.size();i++){
		out<<::fleet[i].getPosition().x<<' '<<::fleet[i].getPosition().y<<' '<<::fleet[i].getRotation()<<' '<<::fleet[i].Player()<<' '<<::fleet[i].Formation()<<' '<<::fleet[i].Provision()<<' '<<::fleet[i].size()<<'\n';
		for(short j=0;j<(short)::fleet[i].size();j++){
			out<<::fleet[i].Ship(j)<<' '<<::fleet[i].Integrity(j)<<' ';
		}
		out<<'\n';
	}
	out.close();
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
				//Go to the enemy fleet
				if(nearest>=0){
					send[player[fleet[j].Player()].Team()]=1;
					getRoute(j,fleet[nearest].getPosition());
					fleet[j].Reform(1);
				}
			}
		}
	}
}
void Game::DefeatedFleet(short i,short j){
	//Lost ships
	short lost=::fleet[i].size()*::fleet[j].Power()/::fleet[i].Power();
	short ship=0;
	while(lost){
		::fleet[i].removeShip(ship);
		if(ship+1<::fleet[i].size())
			ship++;
		lost--;
	}
	//Change statistics
	Defeated(fleet[i].Player(),fleet[j].Player());
	if(isSelectedFleet(j))
		deselectFleet();
	else
		reloadLabelFleet(i);
	//Clear memory
	fleet.erase(fleet.begin()+j);
}
void Game::CombatFleet(short i,short j){
	if(::fleet[i].Power()>::fleet[j].Power())
		DefeatedFleet(i,j);
	else
		DefeatedFleet(j,i);
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
		sf::Vector2f pos=map->GetNearestNode(settlement[sett].getPosition()).getPosition();
		::fleet.push_back(Fleet(
			pos,
			getAngle(settlement[sett].getPosition(),pos),
			settlement[sett].getOwner(),
			2,
			100
		));
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
				::fleet.erase(::fleet.begin()+i);
				i--;
			}
		delete this->battle;
		this->battle=NULL;
		//GUI
		this->showData();
		this->showHumanStatus();
		audio.changeMusic("data/audio/music/Winds of Ithaca.ogg");
	}
	//GUI
	this->gameGUI(window,view);
	//Gameplay
	if(!(*this->subMenu)&&this->paused==NULL){
		//Clock
		this->Clock();
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
			//Into to battle
			for(short j=0;j<(short)::fleet.size();j++){
				if(i!=j){
					if(isEnemyFleet(i,j)&&distFleet(i,j)<=90){
						//Human fleet and AI fleet
						if(isYourFleet(i)){
							this->moveViewTo(view,sf::Vector2f(0,0));
							this->battle=new Battle(i,j,view);
							gui.selected=5;
							break;
						//AI fleets
						}else if(!isYourFleet(j))
							this->CombatFleet(i,j);
					}
				}					
			}
		}
		//Settlements
		for(short i=0;i<(short)::settlement.size();i++){
			//Interactions with allied fleets
			bool free=1;
			for(short j=0;j<(short)::fleet.size();j++){
				if(fleet[j].Speed()<1&&::fleet[j].dist(settlement[i].getPosition())<90){
					//Supply
					if(!isEnemyOf(i,::fleet[j].Player())){
						::fleet[j].Supply();
						free=0;
						if(!isYourFleet(j)){
							::fleet[j].Reform(2);
						}
					}
				}
			}
			//Interactions with enemy fleets
			if(free)
				for(short j=0;j<(short)::fleet.size();j++){
					if(::fleet[j].dist(settlement[i].getPosition())<90){
						//Conquest
						if(isEnemyOf(i,::fleet[j].Player())){
							settlement[i].Conquest(::fleet[j].Player());
							reloadLabelSett(i);
							reloadLabelSett(::settlement[i].getImport());
							reloadLabelSett(getImporter(i));
						}
						showHumanStatus();
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