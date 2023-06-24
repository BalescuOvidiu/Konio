#include "battle.h"
//Basic
Battle::Battle(short yourFleet,short enemyFleet,sf::View *view){
	//Begin
	this->paused=0;
	this->selected=0;
	this->your.ships=this->enemy.ships=0;
	op=NULL;
	//Music
	audio.changeAmbient("data/audio/sound/water.ogg");
	//Size
	if(::fleet[yourFleet].size()<::fleet[enemyFleet].size())
		this->size=::fleet[enemyFleet].size()*700;
	else
		this->size=::fleet[yourFleet].size()*700;
	//Fleets position
	float angle=getAngle(::fleet[yourFleet].getPosition(),::fleet[enemyFleet].getPosition());
	this->your.pos.x=this->size/2-size/4*Cos(angle);
	this->your.pos.y=this->size/2-size/4*Sin(angle);
	this->enemy.pos.x=this->size/2+size/4*Cos(angle);
	this->enemy.pos.y=this->size/2+size/4*Sin(angle);
	this->AddFleet(view,yourFleet,this->your.pos);
	this->AddFleet(view,enemyFleet,this->enemy.pos);
	//Other fleets
	sf::Vector2f pos;
	for(unsigned i=::fleet.size();i--;){
		if(i!=(unsigned)yourFleet&&i!=(unsigned)enemyFleet){
			if(::fleet[i].isInRange(::fleet[yourFleet].getPosition())){
				angle=getAngle(::fleet[yourFleet].getPosition(),::fleet[i].getPosition());
				pos.x=this->your.pos.x+size/4*Cos(angle);
				pos.y=this->your.pos.y+size/4*Sin(angle);
				this->AddFleet(view,i,pos);
			}else if(::fleet[i].isInRange(::fleet[enemyFleet].getPosition())){
				angle=getAngle(::fleet[enemyFleet].getPosition(),::fleet[i].getPosition());
				pos.x=this->enemy.pos.x+size/4*Cos(angle);
				pos.y=this->enemy.pos.y+size/4*Sin(angle);
				this->AddFleet(view,i,pos);
			}
		}
	}
	//Get tactics for AI
	this->your.tactic=::fleet[yourFleet].Formation();
	this->enemy.tactic=::fleet[enemyFleet].Formation();
	//GUI
	this->battleGUI=new BattleGUI(this->getStatistic());
	this->retreat=new Button(96,3,15,"data/img/buttons/menu/retreat.png");
	//Camera for human player
	this->moveView(view,this->your.pos.x-gui.width(50),this->your.pos.y-gui.height(50));
}
void Battle::AddFleet(sf::View *view,short fleet,sf::Vector2f pos){
	//Ships
	if(areAllies(::human,::fleet[fleet].Player()))
		this->your.ships+=::fleet[fleet].size();
	else
		this->enemy.ships+=::fleet[fleet].size();
	this->target.resize(this->target.size()+::fleet[fleet].size());
	//Add fleet in list
	this->fleets.push_back(fleet);
	//Angle and position
	float x,y,angle;
	if(::fleet[fleet].Formation()<2)
		angle=::fleet[fleet].getRotation();
	//Add ships
	for(short i=0;i<::fleet[fleet].size();i++){
		//Get position and rotation
		if(::fleet[fleet].Formation()==2){
			//Kyklos
			if(::fleet[fleet].size()>3)
				angle=360/::fleet[fleet].size()*i+::fleet[fleet].getRotation();
			else
				angle=180/::fleet[fleet].size()*i+::fleet[fleet].getRotation();
			x=pos.x+::fleet[fleet].size()*65*Cos(angle);
			y=pos.y+::fleet[fleet].size()*65*Sin(angle);
		}else if(::fleet[fleet].Formation()==1){
			//Diekplous
			x=pos.x+(i-::fleet[fleet].size()/2)*300*Sin(angle)-abs(i-::fleet[fleet].size()/2)*200*Cos(angle);
			y=pos.y-(i-::fleet[fleet].size()/2)*300*Cos(angle)-abs(i-::fleet[fleet].size()/2)*200*Sin(angle);
		}else{
			//Periplous
			x=pos.x+(i-::fleet[fleet].size()/2)*300*Sin(angle);
			y=pos.y-(i-::fleet[fleet].size()/2)*300*Cos(angle);
		}
		//Deploy ship
		this->ship.push_back(Ship(fleet,i,::fleet[fleet].Ship(i),player[::fleet[fleet].Player()].Faction(),x,y,angle));
	}
}
void Battle::Render(sf::RenderWindow *window){
	//Water
	map->RenderWater(window);
	//Track
	if(this->selected)
		if(this->target[this->selected-1].size())
			window->draw(&this->track[0],this->track.size(),sf::Quads);
	//Rammed ships ram
	for(unsigned i=this->ship.size();i--;)
		if(!this->ship[i].Float()&&this->ship[i].FloatRam())
			this->ship[i].RenderRam(window);
	//Rammed ships rows
	for(unsigned i=this->ship.size();i--;)
		if(!this->ship[i].FloatRam()&&this->ship[i].FloatRows())
			this->ship[i].RenderRows(window);
	//Rammed ships body
	for(unsigned i=this->ship.size();i--;)
		if(!this->ship[i].FloatRows()&&this->ship[i].FloatBody())
			this->ship[i].RenderBody(window);
	//Rammed ships sails
	for(unsigned i=this->ship.size();i--;)
		if(!this->ship[i].FloatBody()&&this->ship[i].FloatSails())
			this->ship[i].RenderSails(window);
	//Ships ram
	for(unsigned i=this->ship.size();i--;)
		if(this->ship[i].Float())
			this->ship[i].RenderRam(window);
	//Ships rows
	for(unsigned i=this->ship.size();i--;)
		if(this->ship[i].FloatRam())
			this->ship[i].RenderRows(window);
	//Ships body
	for(unsigned i=this->ship.size();i--;)
		if(this->ship[i].FloatRows())
			this->ship[i].RenderBody(window);
	//Ships sails
	for(unsigned i=this->ship.size();i--;)
		if(this->ship[i].FloatBody())
			this->ship[i].RenderSails(window);
	//GUI
	if(about)
		about.Render(window);
	if(op!=NULL)
		op->Render(window);
	this->battleGUI->Render(window);
	this->retreat->Render(window);
}
//AI
void Battle::SetTactic(unsigned i,short tactic){
	if(isYourEnemy(i))
		this->enemy.tactic=tactic;
	else
		this->your.tactic=tactic;
}
void Battle::Periplous(unsigned i){
	//Move
	if(this->validPoint(this->localLeft(this->ship[i].width()*2,i)))
		this->SetTarget(i,this->localForward(200,i));
	else
		this->SetTarget(i,this->localBackward(200,i));		
	//Into in attack if is possible
	for(unsigned j=this->ship.size();j--;){
		if(isEnemyShip(i,j)){
			if(DistShip(i,j)<=square(3*this->ship[i].width())){
				SetTactic(i,3);
			}
		}else if(this->ship[j].contains(this->localForward(this->ship[i].width(),i)))
			this->Stop(i);
	}
}
void Battle::Diekplous(unsigned i){
	float angle=360;
	short nearest=-1;
	//Get nearest enemy ship
	for(unsigned j=0;j<this->ship.size();j++){
		if(i!=j){
			if(isEnemyShip(i,j)){
				if(angle<fabs(this->ship[i].getRotation()-getAngle(this->ship[i].Origin(),this->localLeft(100,j)))){
					nearest=j;
					angle=getAngle(this->ship[i].Origin(),this->localLeft(100,j));
				}
				if(angle<fabs(this->ship[i].getRotation()-getAngle(this->ship[i].Origin(),this->localRight(100,j)))){
					nearest=j;
					angle=getAngle(this->ship[i].Origin(),this->localRight(100,j));
				}
				//into to attack
				if(DistShip(i,j)<square(2*this->ship[i].width()))
					SetTactic(i,3);
			}else if(this->ship[j].contains(this->localForward(this->ship[i].width(),i)))
				this->Stop(i);
		}
	}
	//Set target
	if(nearest>=0){
		if(this->ship[i].Dist(this->localRight(100,nearest))>this->ship[i].Dist(this->localLeft(100,nearest)))
			this->SetTarget(i,this->localLeft(100,nearest));
		else
			this->SetTarget(i,this->localRight(100,nearest));
	}else if(this->validPoint(this->localLeft(this->ship[i].width()*2,i)))
		this->SetTarget(i,this->localForward(200,i));
	else
		this->SetTarget(i,this->localBackward(200,i));
}
void Battle::Kyklos(unsigned i){
	//Into in attack if is possible
	for(unsigned j=this->ship.size();j--;){
		if(isEnemyShip(i,j)){
			if(DistShip(i,j)<square(3*this->ship[i].width())){
				SetTactic(i,1);
				return ;
			}
		}
	}
}
void Battle::Attack(unsigned i){
	float dist=this->size*this->size*2;
	short nearest=-1;
	//Get nearest enemy ship
	for(unsigned j=0;j<this->ship.size();j++){
		if(i!=j){
			if(isEnemyShip(i,j)){
				if(DistShip(i,j)<dist){
					if(this->ship[i].DistBack(this->ship[j])<this->ship[i].DistFront(this->ship[j])){
						if(DistShip(i,j)>square(this->ship[i].width()+this->ship[j].width()+200)){
							dist=DistShip(i,j);
							nearest=j;
						}
					}else{
						dist=DistShip(i,j);
						nearest=j;
					}
				}
			}else if(this->ship[j].contains(this->localForward(this->ship[i].height(),i)))
				this->Stop(i);
			else if(this->ship[j].contains(this->localForward(1.5*this->ship[i].width(),i)))
				this->SetTarget(i,this->localBackward(this->ship[i].width()*2,i));
		}
	}
	//Set target
	if(nearest>=0){
		this->SetTarget(i,this->ship[nearest].Origin());
	}else if(this->validPoint(this->localForward(this->ship[i].width()*2,i))){
		this->SetTarget(i,this->localForward(this->ship[i].width()*2,i));
	}else if(this->validPoint(this->localLeft(this->ship[i].width()*2,i))){
		this->SetTarget(i,this->localLeft(this->ship[i].width()*2,i));
	}else if(this->validPoint(this->localRight(this->ship[i].width()*2,i))){
		this->SetTarget(i,this->localRight(this->ship[i].width()*2,i));
	}else{
		this->SetTarget(i,this->localBackward(this->ship[i].width()*2,i));
	}
}
void Battle::AI(){
	for(unsigned i=this->ship.size();i--;){
		if(!this->isYourShip(i)&&this->ship[i].Float()){
			if(isYourEnemy(i)){
				switch(this->enemy.tactic){
					case 0: Periplous(i); break;
					case 1: Diekplous(i); break;
					case 2: Kyklos(i); break;
					default: Attack(i); break;
				}
			}else{
				switch(this->your.tactic){
					case 0: Periplous(i); break;
					case 1: Diekplous(i); break;
					case 2: Kyklos(i); break;
					default: Attack(i); break;
				}
			}
		}
	}
}
//Ship's local target points
sf::Vector2f Battle::local(float dist, float angle,short ship){
	return sf::Vector2f(
		this->ship[ship].Origin().x+dist*cos(this->ship[ship].getRotationRad()+Rad(angle)),
		this->ship[ship].Origin().y+dist*sin(this->ship[ship].getRotationRad()+Rad(angle))
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
float Battle::DistShip(short i,short j){
	return Dist(this->ship[i].Origin(),this->ship[j].Origin());
}
bool Battle::validPoint(sf::Vector2f point){
	return (point.x>=0&&point.y>=0&&point.x<=this->size&&point.y<=this->size);
}
bool Battle::canCollide(short i,short j){
	return (DistShip(i,j)<=square(this->ship[i].width()+this->ship[j].width()));
}
//Teams
bool Battle::isYourShip(short ship){
	return (this->ship[ship].Float()&&isYourFleet(this->ship[ship].Fleet()));
}
bool Battle::isYourEnemy(short ship){
	return areEnemies(::human,this->ship[ship].Player());
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
//Ships and physics
void Battle::SetTarget(short ship,sf::Vector2f target){
	this->target[ship].clear();
	this->target[ship].push_front(target);
}
void Battle::Sink(short i){
	if(!this->ship[i].Float()){
		if(this->selected-1==i)
			this->deselect();
	}
}
void Battle::Stop(short ship){
	this->target[ship].clear();
	this->ship[ship].Speed(0);
}
bool Battle::Ramming(short i,short j){
	if(this->ship[j].contains(this->ship[i].Ram())&&this->ship[j].Float()){
		if(this->ship[i].Speed()>0){
			if(this->ship[i].SpeedRatio()>0.6){
				//Ramming on front
				if(this->ship[j].DistFront(this->ship[i].Front())<400){
					if(this->ship[i].Power()<this->ship[j].Power())
						return 0;
					this->ship[i].takeDamage(15*this->ship[j].Power()/this->ship[i].Power());
					this->ship[j].push(
						10*this->ship[i].SpeedOnFrame()*cos(this->ship[i].getRotationRad()),
						10*this->ship[i].SpeedOnFrame()*sin(this->ship[i].getRotationRad())
					);
				}
				//Ramming on back
				if(this->ship[i].contains(this->ship[j].Back())){
					if(this->ship[i].Speed()<=this->ship[j].Speed())
						return 0;
				}
				//Collision damage
				this->ship[j].takeDamage(30*this->ship[i].Power()/this->ship[j].Power());
				Stop(i);
				Stop(j);
				this->SetTarget(i,this->localBackward(30,i));
				this->Sink(i);
				this->Sink(j);
				return 1;
			}
			this->ship[j].push(
				10*this->ship[i].SpeedOnFrame()*cos(this->ship[i].getRotationRad()),
				10*this->ship[i].SpeedOnFrame()*sin(this->ship[i].getRotationRad())
			);
			Stop(i);
		}
	}
	return 0;
}
bool Battle::Collision(short i,short j){
	//Front
	if(this->ship[j].contains(this->ship[i].Front())){
		if(this->Ramming(i,j))
			return 1;
		if(this->ship[j].Speed()){
			this->ship[i].push(
				-fabs(this->ship[j].SpeedOnFrame())*cos(this->ship[i].getRotationRad()),
				-fabs(this->ship[j].SpeedOnFrame())*sin(this->ship[i].getRotationRad())
			);
		}
	}
	//Back
	if(this->ship[j].contains(this->ship[i].Back())){
		if(this->ship[j].Speed()){
			this->ship[i].push(
				fabs(this->ship[j].SpeedOnFrame())*cos(this->ship[i].getRotationRad()),
				fabs(this->ship[j].SpeedOnFrame())*sin(this->ship[i].getRotationRad())
			);
		}
	}
	//Stopped ship
	if(this->ship[i].Stopped())
		return 0;
	if(this->isRammedShip(i))
		return 0;
	//Rammed
	if(this->isRammedShip(j)){
		if(this->ship[j].contains(this->ship[i].Front())){
			this->SetTarget(i,this->localBackward(30,i));
			return 1;
		}
	}
	//Back
	if(this->ship[j].contains(this->ship[i].Back())){
		if(this->ship[i].Speed()<0){
			Stop(i);
		}
	}
	//Front points
	if(this->ship[j].contains(this->ship[i].FrontLeft())){
		this->ship[i].rotate(fabs(this->ship[i].RotationSpeed()));
	}
	else if(this->ship[j].contains(this->ship[i].FrontRight())){
		this->ship[i].rotate(-fabs(this->ship[i].RotationSpeed()));
	}
	//Back points
	if(this->ship[j].contains(this->ship[i].BackLeft())){
		this->ship[i].rotate(-fabs(this->ship[i].RotationSpeed()));
	}
	else if(this->ship[j].contains(this->ship[i].BackRight())){
		this->ship[i].rotate(fabs(this->ship[i].RotationSpeed()));
	}
	return 0;
}
//GUI
std::string Battle::getStatistic(){
	if(this->paused)
		return Format(this->your.ships)+"/"+Format(this->enemy.ships)+" - PAUSED";
	return Format(this->your.ships)+"/"+Format(this->enemy.ships);
}
bool Battle::mouseOverGUI(){
	if(op!=NULL)
		if(op->mouseOver())
			return 1;
	if(this->battleGUI->mouseOver())
		return 1;
	return this->retreat->mouseOver();
}
bool Battle::Pause(){
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)&&gui.canClick(400)){
		this->paused=!this->paused;
		this->battleGUI->Reload(this->getStatistic());
		gui.clickRestart();
	}
	return this->paused;
}
void Battle::moveView(sf::View *view,float x,float y){
	if(gui.x+x<0||gui.x+gui.width()+x>this->size)
		x=0;
	if(gui.y+y<0||gui.y+gui.height()+y>this->size)
		y=0;
	if(!x&&!y)
		return ;
	//Move
	gui.x+=x;
	gui.y+=y;
	about.move(x,y);
	map->move(x,y);
	view->move(x,y);
	if(op!=NULL)
		op->move(x,y);
	this->battleGUI->move(x,y);
	this->retreat->move(x,y);
}
void Battle::moveCamera(sf::RenderWindow *window,sf::View *view){
	//View and camera
	sf::Vector2f camera=gui.mousePosition();
	if(camera.x<0)
		camera.x=0;
	if(camera.y<0)
		camera.y=0;
	//Move camera by mouse cursor
	if(camera.x<window->getSize().x/20+gui.x)
		this->moveView(view,-10,0);
	if(camera.x>window->getSize().x*19/20+gui.x)
		this->moveView(view,10,0);
	if(camera.y<window->getSize().y/10+gui.y&&!this->battleGUI->mouseOver())
		this->moveView(view,0,-10);
	if(camera.y>window->getSize().y*9/10+gui.y){
		this->moveView(view,0,10);
	}
	//Move camera by key
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->moveView(view,-10,0);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->moveView(view,10,0);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->moveView(view,0,-10);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->moveView(view,0,10);
}
void Battle::zoom(sf::View *view,float factor){
	this->battleGUI->zoom(factor);
	this->retreat->zoom(factor);
	about.zoom(factor);
	if(op!=NULL)
		op->zoom(factor);
	map->zoom(factor);
	view->zoom(factor);
	gui.factor*=factor;
}
//Human ships
void Battle::select(unsigned ship){
	if(ship<0)
		ship=0;
	if(this->selected)
		deselect();
	if(ship<this->ship.size())
		if(this->isYourShip(ship)&&this->ship[ship].Float()){
			this->selected=ship+1;
			this->ship[ship].setColor(sf::Color(255,95,118));
			this->battleGUI->ReloadDetails(this->ship[this->selected].getDetails());
		}
}
void Battle::deselect(){
	this->ship[this->selected-1].setColor(sf::Color(255,255,255));
	this->selected=0;
	this->battleGUI->ReloadDetails("");
	this->track.clear();
}
//Update
void Battle::Update(sf::RenderWindow *window,sf::View *view){
	//Label
	about.hide();
	//Retreat button
	if(this->retreat->left("Retreat","Click or press R to retreat from battle.",sf::Keyboard::R)){
		gui.selected=4;
		for(unsigned i=0;i<this->fleets.size();i++)
			if(isYourFleet(this->fleets[i])){
				::fleet[this->fleets[i]].Retreat();
			}
	}
	//Options
	if(gui.canClick(200)){
		if(op!=NULL){
			op->Update();
			if(!(*op))
				op=NULL;
		}else{
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::O)){
				gui.clickRestart();
				op=new Options();
				op->show();
			}
		}
	}
	//Zoom
	if(gui.canClick(20)){
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)&&gui.factor>1.0203){
			gui.clickRestart();
			this->zoom(view,0.98);
		}
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)&&gui.factor<2){
			gui.clickRestart();
			this->zoom(view,1/0.98);
		}
	}
	//View
	this->moveCamera(window,view);
	//Gameplay
	if(!this->Pause()){
		//Water
		if(this->clock&1)
			map->Update();
		//Selected
		if(this->selected){
			//Selected ship by player
			this->battleGUI->ReloadDetails(ship[this->selected-1].getDetails());
			if(gui.canRight(30)){
				if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
					this->target[this->selected-1].clear();
				this->target[this->selected-1].push_back(gui.mouseCoordinates());
			}
			if(this->clock%4==0){
				if(this->ship[this->selected-1].Speed()>0)
					this->track=getGuide(this->ship[this->selected-1].Front(),this->target[selected-1],sf::Color(120,120,255));
				else if(this->ship[this->selected-1].Speed()<0)
					this->track=getGuide(this->ship[this->selected-1].Back(),this->target[selected-1],sf::Color(120,120,255));
			}
			//Deselect
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&&!this->ship[this->selected-1].contains(gui.mouseCoordinates()))
				this->deselect();
		}
		//Ships
		for(unsigned i=this->ship.size();i--;){
			//Arrows
			for(unsigned rank=this->ship[i].marine.size();rank--;)
				if(this->ship[i].marine[rank].arrow!=NULL){
					if(this->ship[i].marine[rank].arrow->canHit()){
						this->ship[i].marine[rank].reload();
					}else
						this->ship[i].marine[rank].arrow->Update();
				}
			//Unbroken Ships
			if(this->ship[i].Float()){
				//Interaction with other ships
				for(unsigned j=this->ship.size();j--;)
					if(i!=j){
						if(DistShip(i,j)<490000){
							//Marine attack
							if(isEnemyShip(i,j)){
								//Attack marine
								unsigned q=this->ship[i].marine.size();
								for(unsigned rank=this->ship[i].marine.size();rank--;){
									for(unsigned target=this->ship[j].marine.size();target--;){
										if(this->ship[i].marine[rank].arrow!=NULL){
											//Arrow
											if(this->ship[j].marine[target].Alive()){
												if(this->ship[j].marine[target].kill(this->ship[i].marine[rank].arrow->getPosition())){
													this->ship[j].marineDeath();
													this->ship[i].marine[rank].reload();
												}
											}else if(this->ship[i].marine[rank].arrow->canHit()){
												if(this->ship[j].contains(this->ship[i].marine[rank].arrow->getPosition()))
													this->ship[j].takeDamage(0.8);
												this->ship[i].marine[rank].reload();
											}
										}else if(this->ship[i].marine[rank].Alive()){
											//Select alive target
											if(this->ship[j].marine[target].Alive()){
												q=rank;
												this->ship[i].marine[rank].attack(this->ship[j].marine[target].getPosition());
												break;
											}
										}
									}
								}
								//Attack ship
								while(q--){
									if(this-ship[i].marine[q].Alive())
										if(this->ship[i].marine[q].arrow==NULL&&this->ship[j].Float())
											this->ship[i].marine[q].attack(this->ship[j].Origin());
								}
							}
							//Collision
							if(this->canCollide(i,j))
								this->Collision(i,j);
						}
					}
				//Mouse event
				if(!this->mouseOverGUI()){
					if(this->isYourShip(i)&&this->ship[i].left())
						this->select(i);
					else
						this->ship[i].mouseOver();
				}
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
				//Statistics
				if(isYourEnemy(i))
					this->enemy.ships--;
				else
					this->your.ships--;
				this->battleGUI->Reload(this->getStatistic());
				//Remove
				::fleet[this->ship[i].Fleet()].removeShip(this->ship[i].Rank());
				for(unsigned k=i+1;k<this->ship.size();k++)
					if(this->ship[k].Fleet()==this->ship[i].Fleet())
						this->ship[k].rankDown();
				//Clear memory
				this->ship.erase(this->ship.begin()+i);
				this->target.erase(this->target.begin()+i);
				//Selected ship
				if(selected>1){
					if(((short)i)<(this->selected-1)){
						this->select(this->selected-2);
					}
				}
			}
		}
		//Clock and AI
		if(!((this->clock++)%60))
			AI();
	}
	//Exit if a team is destroyed
	if(!this->your.ships||!this->enemy.ships){
		gui.selected=4;
	}
	//Exit from battle
	if(gui.selected==4){
		//Camera
		this->zoom(view,1/gui.factor);
		this->moveView(view,-gui.x,-gui.y);
		//Empty memory
		this->target.clear();
		this->ship.clear();
		op=NULL;
	}
}
Battle::~Battle(){
}