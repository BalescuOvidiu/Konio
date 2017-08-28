#include "battle.h"
//Basic
Battle::Battle(short yourFleet,short enemyFleet,sf::View *view){
	//Begin
	this->pause=0;
	this->selected=0;
	//GUI
	this->retreat=new Button(90,85,15,"data/img/buttons/menu/retreat.png");
	this->text=new sf::Text(sf::String(""),*gui.Font(),36);
	this->text->setPosition(gui.width(50)-100,gui.height(50)-36);
	this->text->setColor(sf::Color(255,255,255));
	detail.show();
	//Water
	this->water=new Layer(1,256,"data/img/water.png");
	//Music
	audio.changeMusic("data/audio/music/Winds of Ithaca.ogg");
	audio.changeAmbient("data/audio/sound/water.ogg");
	//Ships
	this->target.resize(::fleet[yourFleet].size()+::fleet[enemyFleet].size());
	this->AddFleet(view,yourFleet);
	this->AddFleet(view,enemyFleet);
}
void Battle::AddFleet(sf::View *view,short fleet){
	//Add fleet in list
	this->fleets.push_back(fleet);
	short x,y=2350-1900*(fleets.size()%2),angle=270-180*(fleets.size()%2);
	//Add ships
	for(short i=0;i<(short)::fleet[fleet].size();i++){
		x=i*300+300;
		this->ship.push_back(Ship(fleet,::fleet[fleet].Ship(i),player[::fleet[fleet].Player()].Faction(),::fleet[fleet].Integrity(i),x,y,angle));
	}
	//Camera for human player
	if(isYourFleet(fleet))
		this->moveView(view,::fleet[fleet].size()*50+50,0);
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
	if(info)
		info.Render(window);
	if(detail)
		detail.Render(window);
	//Retreat button
	this->retreat->Render(window);
	//Pause
	if(this->pause)
		window->draw(*this->text);
}
//AI
void Battle::AI(){

}
//Gameplay
std::string Battle::getStatistic(){
	short friends=0,enemies=0;
	for(short k=0;k<(short)this->ship.size();k++){
		if(this->isFriend(0,k))
			friends++;
		else if(this->isEnemy(0,k))
			enemies++;
	}
	return "Friend ships: "+std::to_string(friends)+"\nEnemy ships: "+std::to_string(enemies);
}
sf::Vector2f Battle::local(sf::Vector2f point,short ship){
	return sf::Vector2f(
		this->ship[ship].Origin().x+point.x*cos(this->ship[ship].getRotationRad()),
		this->ship[ship].Origin().y+point.y*sin(this->ship[ship].getRotationRad())
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
void Battle::Stop(short ship){
	this->target[ship].clear();
	this->ship[ship].Speed(0);
}
bool Battle::Pause(){
	this->text->setString(sf::String("PAUSED"));
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
		this->pause=!this->pause;
		sf::sleep(sf::Time(sf::milliseconds(100)));
	}
	return this->pause;
}
bool Battle::validPoint(sf::Vector2f point){
	return (point.x>=0&&point.y>=0&&point.x<=3000&&point.y<=3000);
}
bool Battle::isYour(short ship){
	return (this->ship[ship].Float()&&isYourFleet(this->ship[ship].Fleet()));
}
bool Battle::isRammed(short ship){
	return (this->ship[ship].Integrity()<=50);
}
bool Battle::isEnemy(short i,short j){
	return (isEnemyFleet(this->ship[i].Fleet(),this->ship[j].Fleet())&&this->ship[i].Float()&&this->ship[j].Float());
}
bool Battle::isFriend(short i,short j){
	return (isAlliedFleet(this->ship[i].Fleet(),this->ship[j].Fleet())&&this->ship[i].Float()&&this->ship[j].Float());
}
void Battle::moveView(sf::View *view,float x,float y){
	if(gui.x+x<0||gui.x+x>3000-view->getSize().x)
		x=0;
	if(gui.y+y<0||gui.y+y>3000-view->getSize().y)
		y=0;
	if(!x&&!y)
		return ;
	//Move
	gui.x+=x;
	gui.y+=y;
	about.move(x,y);
	detail.move(x,y);
	info.move(x,y);
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
		return 1;
	}
	return 0;
}
bool Battle::collision(short i,short j){
	//Rammed
	if(this->isRammed(j)&&this->ship[j].contains(this->ship[i].Front())){
		this->target[i].clear();
		this->target[i].push_back(this->localBackward(30,i));
		return 1;
	}
	//Ramming
	if(this->isEnemy(i,j)){
		if(this->ramming(i,j))
			return 1;
		//Front points
		if(!this->ship[j].contains(this->ship[i].Front())){
			if(this->ship[j].contains(this->ship[i].FrontLeft())){
				this->ship[i].rotate(fabs(this->ship[i].Speed())/50);
				return 1;
			}
			if(this->ship[j].contains(this->ship[i].FrontRight())){
				this->ship[i].rotate(-fabs(this->ship[i].Speed())/50);
				return 1;
			}
			//Reverse case
			if(this->ship[i].contains(this->ship[j].FrontLeft())){
				this->ship[i].rotate(-fabs(this->ship[i].Speed())/50);
				return 1;
			}
			if(this->ship[i].contains(this->ship[j].FrontRight())){
				this->ship[i].rotate(fabs(this->ship[i].Speed())/50);
				return 1;
			}
		}
		//Back points
		if(!this->ship[j].contains(this->ship[i].Back())){
			if(this->ship[j].contains(this->ship[i].BackLeft())){
				this->ship[i].rotate(-fabs(this->ship[i].Speed())/50);
				return 1;
			}
			if(this->ship[j].contains(this->ship[i].BackRight())){
				this->ship[i].rotate(fabs(this->ship[i].Speed())/50);
				return 1;
			}
			//Reverse case
			if(this->ship[i].contains(this->ship[j].BackLeft())){
				this->ship[i].rotate(fabs(this->ship[i].Speed())/50);
				return 1;
			}
			if(this->ship[i].contains(this->ship[j].BackRight())){
				this->ship[i].rotate(-fabs(this->ship[i].Speed())/50);
				return 1;
			}
		}else if(this->ship[i].Speed()<0){
			Stop(i);
		}
		return 0;
	}
	//Passive
	if(this->ship[i].Float()&&this->ship[j].Float()){
		//Friend
		if(this->isFriend(i,j)){
			//Front
			if(this->ship[j].rowsContains(this->ship[i].Front())&&this->ship[i].Speed()>0){
				this->ship[i].Speed(0);
				return 1;
			}
			//Back		
			if(this->ship[j].rowsContains(this->ship[i].Back())&&this->ship[i].Speed()<0){
				this->ship[i].Speed(0);
				return 1;
			}
			//Front points
			if(this->ship[j].rowsContains(this->ship[i].rowsFrontLeft())){
				this->ship[i].rotate(fabs(this->ship[i].Speed())/50);
				return 1;
			}
			if(this->ship[j].rowsContains(this->ship[i].rowsFrontRight())){
				this->ship[i].rotate(-fabs(this->ship[i].Speed())/50);
				return 1;
			}
			//Reverse case
			if(this->ship[i].rowsContains(this->ship[j].rowsFrontLeft())){
				this->ship[i].rotate(-fabs(this->ship[i].Speed())/50);
				return 1;
			}
			if(this->ship[i].rowsContains(this->ship[j].rowsFrontRight())){
				this->ship[i].rotate(fabs(this->ship[i].Speed())/50);
				return 1;
			}
			//Back points
			if(this->ship[j].rowsContains(this->ship[i].rowsBackLeft())){
				this->ship[i].rotate(-fabs(this->ship[i].Speed())/50);
				return 1;
			}
			if(this->ship[j].rowsContains(this->ship[i].rowsBackRight())){
				this->ship[i].rotate(fabs(this->ship[i].Speed())/50);
				return 1;
			}
			//Reverse case
			if(this->ship[i].rowsContains(this->ship[j].rowsBackLeft())){
				this->ship[i].rotate(fabs(this->ship[i].Speed())/50);
				return 1;
			}
			if(this->ship[j].rowsContains(this->ship[i].rowsBackRight())){
				this->ship[i].rotate(-fabs(this->ship[i].Speed())/50);
				return 1;
			}
			//Possible collision from beside
			if(dist(this->ship[i].Front(),this->ship[j].Back())<50&&this->ship[j].Speed()<0){
				this->target[i].clear();
				this->target[i].push_back(this->localBackward(50,i));
				return 1;
			}
		//Rammed or enemy
		}
		//Front
		if(this->ship[j].contains(this->ship[i].Front())&&this->ship[i].Speed()>0){
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
			this->ship[i].rotate(fabs(this->ship[i].Speed())/50);
			return 1;
		}
		if(this->ship[j].contains(this->ship[i].FrontRight())){
			this->ship[i].rotate(-fabs(this->ship[i].Speed())/50);
			return 1;
		}
		//Reverse case
		if(this->ship[i].contains(this->ship[j].FrontLeft())){
			this->ship[i].rotate(-fabs(this->ship[i].Speed())/50);
			return 1;
		}
		if(this->ship[i].contains(this->ship[j].FrontRight())){
			this->ship[i].rotate(fabs(this->ship[i].Speed())/50);
			return 1;
		}
		//Back points
		if(this->ship[j].contains(this->ship[i].BackLeft())){
			this->ship[i].rotate(-fabs(this->ship[i].Speed())/50);
			return 1;
		}
		if(this->ship[j].contains(this->ship[i].BackRight())){
			this->ship[i].rotate(fabs(this->ship[i].Speed())/50);
			return 1;
		}
		//Reverse case
		if(this->ship[i].contains(this->ship[j].BackLeft())){
			this->ship[i].rotate(fabs(this->ship[i].Speed())/50);
			return 1;
		}
		if(this->ship[i].contains(this->ship[j].BackRight())){
			this->ship[i].rotate(-fabs(this->ship[i].Speed())/50);
			return 1;
		}
	}
	return 0;
}
//Human
void Battle::select(short ship){
	if(this->selected)
		deselect();
	if(ship<(short)this->ship.size())
		if(this->isYour(ship)&&this->ship[ship].Float()){
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
			if(isYourFleet(this->fleets[i]))
				::fleet[this->fleets[i]].Lost();
	}
	//Gameplay
	if(!this->Pause()){
		//Clock and AI
		if(!(this->clock=(clock+1)%60))
			AI();
		//View
		this->moveCamera(window,view);
		//Water
		this->water->Update();
		//Select ship with keyboard
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
			this->select(this->selected-1);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
			this->select(this->selected+1);
		//Selected
		if(this->selected){
			//Selected ship by player
			this->ship[this->selected-1].show();
			if(sf::Mouse::isButtonPressed(sf::Mouse::Right)&&gui.canClick(100)){
				if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
					this->target[this->selected-1].clear();
				this->target[this->selected-1].push_back(gui.mousePosition());
			}
			//Deselect
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)||isRammed(this->selected-1))
				this->deselect();
		}else
			detail.show("Battle",this->getStatistic());
		//Ships
		for(int i=0;i<(int)this->ship.size();i++){
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
				if(this->isYour(i)&&this->ship[i].left()){
					this->select(i);
				//AI's ships
				}else{
					this->ship[i].mouseOver();
				}
				//Move
				if(!this->target[i].empty()){
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
	}
}
Battle::~Battle(){

}