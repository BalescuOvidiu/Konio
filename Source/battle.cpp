#include "battle.h"
//Basic
Battle::Battle(short yourFleet,short enemyFleet,sf::View *view){
	//Begin
	this->pause=0;
	this->selected=0;
	detail.show();
	//GUI
	this->retreat=new Button(90,85,15,"data/img/buttons/menu/retreat.png");
	this->text=new sf::Text(sf::String(""),*gui.Font(),36);
	this->text->setPosition(gui.width(50)-100,gui.height(50)-36);
	this->text->setColor(sf::Color(255,255,255));
	//Water
	this->water=new Layer(1,256,"data/img/water.png");
	//Music
	audio.changeMusic("data/audio/music/Winds of Ithaca.ogg");
	audio.changeAmbient("data/audio/sound/water.ogg");
	//Size
	if(::fleet[yourFleet].size()<::fleet[enemyFleet].size())
		size=::fleet[enemyFleet].size()*500;
	else
		size=::fleet[yourFleet].size()*500;
	//Ships
	this->target.resize(::fleet[yourFleet].size()+::fleet[enemyFleet].size());
	this->AddFleet(view,yourFleet);
	this->AddFleet(view,enemyFleet);
	//Statistics
	detail.show("Battle",this->getStatistic());
	//Get tactics for AI
	this->tactic=::fleet[enemyFleet].Formation();
}
void Battle::AddFleet(sf::View *view,short fleet){
	//Add fleet in list
	this->fleets.push_back(fleet);
	short x,y,angle;
	//Add ships
	for(short i=0;i<(short)::fleet[fleet].size();i++){
		//Get position and rotation
		if(::fleet[fleet].Formation()==2){
			angle=360/::fleet[fleet].size()*i;
			x=this->size/2+::fleet[fleet].size()*65*cos(angle*0.017453293);
			y=this->size*3/4-this->size/2*(fleets.size()%2)+::fleet[fleet].size()*65*sin(angle*0.017453293);
			angle+=90;
		}else if(::fleet[fleet].Formation()==1){
			angle=270-180*(fleets.size()%2);
			x=this->size/2-(::fleet[fleet].size()*75)+i/2*500;
			y=this->size*3/4-this->size/2*(fleets.size()%2)+i%2*500;
		}else{
			angle=270-180*(fleets.size()%2);
			x=this->size/2-(::fleet[fleet].size()*150)+i*300;
			y=this->size*3/4-this->size/2*(fleets.size()%2);
		}
		//Deploy ship
		this->ship.push_back(Ship(fleet,::fleet[fleet].Ship(i),player[::fleet[fleet].Player()].Faction(),::fleet[fleet].Integrity(i),x,y,angle));
	}
	//Camera for human player
	if(isYourFleet(fleet)){
		this->moveView(view,this->size/2-gui.width(50),this->size*3/4-this->size/2*(fleets.size()%2)-gui.height(50));
	}
}
void Battle::Render(sf::RenderWindow *window){
	//Water
	this->water->Render(window);
	//Ships rows
	for(short i=0;i<(short)this->ship.size();i++)
		if(this->ship[i].Integrity()>40)
			this->ship[i].RenderRows(window);
	//Ships ram
	for(short i=0;i<(short)this->ship.size();i++)
		if(this->ship[i].Integrity()>20)
			this->ship[i].RenderRam(window);
	//Ships body
	for(short i=0;i<(short)this->ship.size();i++)
		if(this->ship[i].Integrity()>20)
			this->ship[i].RenderBody(window);
	//Ships sails
	for(short i=0;i<(short)this->ship.size();i++)
			this->ship[i].RenderSails(window);
	//Labels
	if(about)
		about.Render(window);
	detail.Render(window);
	//Retreat button
	this->retreat->Render(window);
	//Pause
	if(this->pause)
		window->draw(*this->text);
}
//AI
void Battle::Forward(){
	for(short i=0;i<(short)this->ship.size();i++){
		//Move
		if(!this->isYourShip(i)){
			this->target[i].clear();
			if(this->ship[i].Origin().x<this->size/2)
				this->target[i].push_front(this->localForward(200,i));
		}
		//Into in attack if is possible
		for(short j=0;j<(short)this->ship.size();j++){
			if(isEnemyShip(i,j)){
				if(distShip(i,j)<550){
					this->tactic=4;
					Attack();
					break;
				}
			}
		}
	}
}
void Battle::Diekplous(){
	for(short i=0;i<(short)this->ship.size();i++){
		if(!this->isYourShip(i)){
			float dist=99999999;
			short nearest=-1;
			//Get nearest enemy ship
			for(short j=0;j<(short)this->ship.size();j++){
				if(isEnemyShip(i,j)){
					if(dist>this->ship[i].dist(this->localLeft(100,j))){
						dist=this->ship[i].dist(this->localLeft(100,j));
						nearest=j;
					}
				}
			}
			//Set target
			this->target[i].clear();
			if(nearest>=0){
				this->target[i].push_front(this->localLeft(100,nearest));
				//Into to attack
				if(dist<100){
					tactic=4;
					Attack();
				}
			}else
				this->target[i].push_front(this->localForward(200,i));
		}
	}
}
void Battle::Periplous(){
	short begin=-1;
	for(short i=0;i<(short)this->ship.size();i++){
		if(!this->isYourShip(i)){
			if(begin<0)
				begin=i;
			//Move
			this->target[i].clear();
			if(i<(short)this->ship.size()-1)
				this->target[i].push_front(this->ship[i+1].rowsBackLeft());
			else					
				this->target[i].push_front(this->ship[begin].rowsBackLeft());
			//Into in attack if is possible
			for(short j=0;j<(short)this->ship.size();j++){
				if(isEnemyShip(i,j)){
					if(distShip(i,j)<320){
						this->tactic=4;
						Attack();
						break;
					}
				}
			}
		}
	}
}
void Battle::Attack(){
	for(short i=0;i<(short)this->ship.size();i++){
		if(!this->isYourShip(i)){
			float dist=99999999;
			short nearest=-1;
			//Get nearest enemy ship
			for(short j=0;j<(short)this->ship.size();j++){
				if(isEnemyShip(i,j)){
					if(distShip(i,j)<dist&&distShip(i,j)<this->ship[i].dist(this->ship[j].Back())){
						dist=distShip(i,j);
						nearest=j;
					}
				}
			}
			//Set target
			if(nearest>=0){
				this->target[i].clear();
				if(dist<320)
					this->target[i].push_front(this->ship[nearest].Origin());
				else
					this->target[i].push_front(this->localLeft(100,nearest));
			}
		}
	}	
}
void Battle::AI(){
	switch(this->tactic){
		case 0: Forward(); break;
		case 1: Diekplous(); break;
		case 2: Periplous(); break;
		default: Attack(); break;
	}
}
//Ship's pints target
sf::Vector2f Battle::local(float dist, float angle,short ship){
	return sf::Vector2f(
		this->ship[ship].Origin().x+dist*cos(this->ship[ship].getRotationRad()+angle*0.017453293),
		this->ship[ship].Origin().y+dist*sin(this->ship[ship].getRotationRad()+angle*0.017453293)
	);
}
sf::Vector2f Battle::localForward(float dist,short ship){
	return sf::Vector2f(
		this->ship[ship].Front().x+dist*cos(this->ship[ship].getRotationRad()),
		this->ship[ship].Front().y+dist*sin(this->ship[ship].getRotationRad())
	);
}
sf::Vector2f Battle::localBackward(float dist,short ship){
	return sf::Vector2f(
		this->ship[ship].Back().x-dist*cos(this->ship[ship].getRotationRad()),
		this->ship[ship].Back().y-dist*sin(this->ship[ship].getRotationRad())
	);
}
sf::Vector2f Battle::localLeft(float dist,short ship){
	return sf::Vector2f(
		this->ship[ship].FrontLeft().x+dist*sin(this->ship[ship].getRotationRad()),
		this->ship[ship].FrontLeft().y+dist*cos(this->ship[ship].getRotationRad())
	);
}
sf::Vector2f Battle::localRight(float dist,short ship){
	return sf::Vector2f(
		this->ship[ship].FrontRight().x-dist*sin(this->ship[ship].getRotationRad()),
		this->ship[ship].FrontRight().y-dist*cos(this->ship[ship].getRotationRad())
	);
}
float Battle::distShip(short i,short j){
	return this->ship[i].dist(this->ship[j].Origin());
}
bool Battle::validPoint(sf::Vector2f point){
	return (point.x>=0&&point.y>=0&&point.x<=this->size&&point.y<=this->size);
}
//Teams
bool Battle::isYourShip(short ship){
	return (this->ship[ship].Float()&&isYourFleet(this->ship[ship].Fleet()));
}
bool Battle::isRammedShip(short ship){
	return (this->ship[ship].Integrity()<=50);
}
bool Battle::isEnemyShip(short i,short j){
	return (isEnemyFleet(this->ship[i].Fleet(),this->ship[j].Fleet())&&this->ship[i].Float()&&this->ship[j].Float());
}
bool Battle::isFriendShip(short i,short j){
	return (isAlliedFleet(this->ship[i].Fleet(),this->ship[j].Fleet())&&this->ship[i].Float()&&this->ship[j].Float());
}
//Events
void Battle::Stop(short ship){
	this->target[ship].clear();
	this->ship[ship].Speed(0);
}
bool Battle::ramming(short i,short j){
	if(this->ship[i].SpeedRatio()>0.5&&this->ship[j].contains(this->ship[i].Ram())){
		//Ramming in front
		if(dist(this->ship[j].Front(),this->ship[i].Front())<50){
			if(this->ship[i].Power()<this->ship[j].Power())
				return 0;
			else if(this->ship[j].SpeedRatio()>0.5)
				this->ship[i].takeDamage(10);
		}
		//Ramming on back
		if(this->ship[i].contains(this->ship[j].Back())){
			if(this->ship[i].Speed()<this->ship[j].Speed())
				return 0;
		}
		//After colision
		this->ship[j].takeDamage(40);
		if(this->ship[i].Power()/this->ship[j].Power()>0.5)
			this->ship[j].takeDamage(10);
		Stop(j);
		Stop(i);
		detail.show("Battle",this->getStatistic());
		if(!this->ship[j].Float()){
		}
		if(!this->ship[i].Float()){

		}
		return 1;
	}
	return 0;
}
bool Battle::collision(short i,short j){
	if(!this->ship[i].Speed())
		return 0;
	if(isRammedShip(i))
		return 0;
	//Enemy
	if(isEnemyShip(i,j)){
		if(this->ramming(i,j))
			return 1;
	//Rammed
	}else if(this->isRammedShip(j)){
			if(this->ship[j].contains(this->ship[i].Front())){
			this->target[i].clear();
			this->target[i].push_back(this->localBackward(30,i));
			return 1;
		}
	//Friend
	}else if(this->isFriendShip(i,j)){
		//Possible collision from beside
		if(dist(this->ship[i].Front(),this->ship[j].Back())<50&&this->ship[i].Direction()*this->ship[j].Direction()<0){
			this->target[i].clear();
			this->target[i].push_back(this->localBackward(50,i));
			return 1;
		}
		//Front
		if(this->ship[j].rowsContains(this->ship[i].Front())&&this->ship[i].Speed()>0){
			this->Stop(i);
			return 1;
		}
		//Back		
		if(this->ship[j].rowsContains(this->ship[i].Back())&&this->ship[i].Speed()<0){
			this->Stop(j);
			return 1;
		}
		//Front points
		if(this->ship[j].rowsContains(this->ship[i].rowsFrontLeft())){
			this->ship[i].rotate(fabs(this->ship[i].Speed())/60);
			return 1;
		}else if(this->ship[j].rowsContains(this->ship[i].rowsFrontRight())){
			this->ship[i].rotate(-fabs(this->ship[i].Speed())/60);
			return 1;
		}
		//Reverse case
		if(this->ship[i].rowsContains(this->ship[j].rowsFrontLeft())){
			this->ship[i].rotate(-fabs(this->ship[i].Speed())/60);
			return 1;
		}else if(this->ship[i].rowsContains(this->ship[j].rowsFrontRight())){
			this->ship[i].rotate(fabs(this->ship[i].Speed())/60);
			return 1;
		}
		//Back points
		if(this->ship[j].rowsContains(this->ship[i].rowsBackLeft())){
			this->ship[i].rotate(-fabs(this->ship[i].Speed())/60);
			return 1;
		}
		if(this->ship[j].rowsContains(this->ship[i].rowsBackRight())){
			this->ship[i].rotate(fabs(this->ship[i].Speed())/60);
			return 1;
		}
		//Reverse case
		if(this->ship[i].rowsContains(this->ship[j].rowsBackLeft())){
			this->ship[i].rotate(fabs(this->ship[i].Speed())/60);
			return 1;
		}
		if(this->ship[j].rowsContains(this->ship[i].rowsBackRight())){
			this->ship[i].rotate(-fabs(this->ship[i].Speed())/60);
			return 1;
		}
	}
	//Front
	if(this->ship[j].contains(this->ship[i].Front())&&this->ship[i].Speed()>0&&!isEnemyShip(i,j)){
		Stop(i);
		return 1;
	}
	//Back
	if(this->ship[j].contains(this->ship[i].Back())&&this->ship[i].Speed()<0){
		Stop(i);
		return 1;
	}
	//Front points
	if(this->ship[j].contains(this->ship[i].FrontLeft())){
		this->ship[i].rotate(fabs(this->ship[i].Speed())/60);
		return 1;
	}
	if(this->ship[j].contains(this->ship[i].FrontRight())){
		this->ship[i].rotate(-fabs(this->ship[i].Speed())/60);
		return 1;
	}
	//Reverse case
	if(this->ship[i].contains(this->ship[j].FrontLeft())){
		this->ship[i].rotate(-fabs(this->ship[i].Speed())/60);
		return 1;
	}
	if(this->ship[i].contains(this->ship[j].FrontRight())){
		this->ship[i].rotate(fabs(this->ship[i].Speed())/60);
		return 1;
	}
	//Back points
	if(this->ship[j].contains(this->ship[i].BackLeft())){
		this->ship[i].rotate(-fabs(this->ship[i].Speed())/60);
		return 1;
	}
	if(this->ship[j].contains(this->ship[i].BackRight())){
		this->ship[i].rotate(fabs(this->ship[i].Speed())/60);
		return 1;
	}
	//Reverse case
	if(this->ship[i].contains(this->ship[j].BackLeft())){
		this->ship[i].rotate(fabs(this->ship[i].Speed())/60);
		return 1;
	}
	if(this->ship[i].contains(this->ship[j].BackRight())){
		this->ship[i].rotate(-fabs(this->ship[i].Speed())/60);
		return 1;
	}	
	return 0;
}
//GUI
std::string Battle::getStatistic(){
	short friends=0,enemies=0;
	for(short k=0;k<(short)this->ship.size();k++){
		if(this->isFriendShip(0,k))
			friends++;
		else if(this->isEnemyShip(0,k))
			enemies++;
	}
	return "Friend ships: "+std::to_string(friends)+"\nEnemy ships: "+std::to_string(enemies);
}
bool Battle::Pause(){
	this->text->setString(sf::String("PAUSED"));
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
		this->pause=!this->pause;
		sf::sleep(sf::Time(sf::milliseconds(200)));
	}
	return this->pause;
}
void Battle::moveView(sf::View *view,float x,float y){
	if(gui.x+x<0||gui.x+x>this->size-view->getSize().x)
		x=0;
	if(gui.y+y<0||gui.y+y>this->size-view->getSize().y)
		y=0;
	if(!x&&!y)
		return ;
	//Move
	gui.x+=x;
	gui.y+=y;
	about.move(x,y);
	detail.move(x,y);
	view->move(x,y);
	this->water->move(x,y);
	this->text->move(x,y);
	this->retreat->move(x,y);
}
void Battle::moveCamera(sf::RenderWindow *window,sf::View *view){
	//View and camera
	sf::Vector2f camera=gui.mousePosition();
	if((short)camera.x<0)
		camera.x=0;
	if((short)camera.y<0)
		camera.y=0;
	//Move camera by mouse cursor
	if(camera.x<window->getSize().x/20+gui.x)
		this->moveView(view,-6,0);
	if(camera.x>window->getSize().x*19/20+gui.x)
		this->moveView(view,6,0);
	if(camera.y<window->getSize().y/10+gui.y)
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
//Human
void Battle::select(short ship){
	if(ship<0)
		ship=0;
	if(this->selected)
		deselect();
	if(ship<(short)this->ship.size())
		if(this->isYourShip(ship)&&this->ship[ship].Float()){
			this->selected=ship+1;
			this->ship[ship].setColor(sf::Color(255,95,118));
		}
}
void Battle::deselect(){
	this->ship[this->selected-1].setColor(sf::Color(255,255,255));
	this->selected=0;
}
//Update
void Battle::Update(sf::RenderWindow *window,sf::View *view){
	//GUI
	about.hide();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)||this->retreat->left("Retreat","Click or press R to retreat from battle.")){
		gui.selected=4;
		for(short i=0;i<(short)this->fleets.size();i++)
			if(isYourFleet(this->fleets[i])){
				::fleet[this->fleets[i]].Retreat();
			}
	}
	//Gameplay
	if(!this->Pause()){
		//Clock and AI
		if(!(this->clock=(clock+1)%60)){
			detail.show("Battle",this->getStatistic());
			AI();
		}
		//View
		this->moveCamera(window,view);
		//Water
		this->water->Update();
		//Select ship with keyboard
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
			if(gui.canClick(80))
				this->select(this->selected-2);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
			if(gui.canClick(80))
				this->select(this->selected);
		}
		//Selected
		if(this->selected){
			//Selected ship by player
			this->ship[this->selected-1].show();
			if(gui.canRight(30)){
				if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
					this->target[this->selected-1].clear();
				this->target[this->selected-1].push_back(gui.mousePosition());
			}
			//Deselect
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)||isRammedShip(this->selected-1)){
				this->deselect();
				detail.show("Battle",this->getStatistic());
			}
		}
		//Ships
		for(short i=0;i<(short)this->ship.size();i++){
			//Unbroken Ships
			if(this->ship[i].Float()){
				for(short j=0;j<(short)this->ship.size();j++){
					if(i!=j){
						//Collision
						if(this->ship[i].dist(this->ship[j].Origin())<=this->ship[i].width()+this->ship[j].width())
							this->collision(i,j);
					}
				}
				//Player's ships
				if(this->isYourShip(i)&&this->ship[i].left())
					this->select(i);
				//AI's ships
				else
					this->ship[i].mouseOver();
				//Move
				if(this->target[i].size()){
					if(this->target[i].size()==1){
						if(this->ship[i].move(this->target[i].front())){
							this->target[i].pop_front();
						}
					}else{
						this->ship[i].move(this->target[i].front());
						if(this->ship[i].contains(this->target[i].front())){
							this->target[i].pop_front();
						}
					}
				}
			//Broken ships
			}else if(this->ship[i].sink()){
				short sinked=i;
				for(short j=0;j<(short)this->fleets.size();j++){
					if(fleets[j]==this->ship[i].Fleet())
						break;
					sinked-=::fleet[this->fleets[j]].size();
				}
				//Remove
				::fleet[this->ship[i].Fleet()].removeShip(sinked);
				//Clear memory
				this->ship.erase(this->ship.begin()+i);
				this->target.erase(this->target.begin()+i);
			}
		}
	}
	//Exit if a fleet is destroyed
	for(short i=0;i<(short)this->fleets.size();i++)
		if(!fleet[this->fleets[i]].size()){
			gui.selected=4;
			break;
		}
	//Exit from battle
	if(gui.selected==4){
		//Get to initial position
		this->moveView(view,-gui.x,-gui.y);
		//Empty memory
		this->target.clear();
		this->ship.clear();
		//Wait
		sf::sleep(sf::Time(sf::milliseconds(100)));
	}
}
Battle::~Battle(){

}