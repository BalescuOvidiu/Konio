#include "battle.h"
//Basic
Battle::Battle(std::string directory,sf::View *view){
	this->Load(view,directory);
}
void Battle::Render(sf::RenderWindow *window){
	//Water
	this->water->Render(window);
	//Ships rows
	for(short i=0;i<(short)this->ship.size();i++)
		if(this->ship[i].Integrity()>40)
			window->draw(*this->ship[i].rows);
	//Ships ram
	for(short i=0;i<(short)this->ship.size();i++)
		if(this->ship[i].Integrity()>20)
			window->draw(*this->ship[i].ram);
	//Ships body
	for(short i=0;i<(short)this->ship.size();i++)
		if(this->ship[i].Integrity()>20)
			window->draw(*this->ship[i].body);
	//Ships sails
	for(short i=0;i<(short)this->ship.size();i++)
		window->draw(*this->ship[i].sails);
	//About
	if(about)
		about.Render(window);
	//GUI
	if(*this->subMenu){
		this->subMenu->Render(window);
		if(op)
			op.Render(window);
	}else{
		if(info)
			info.Render(window);
		if(detail)
			detail.Render(window);
		this->submenu->Render(window);
	}
	//Gameplay
	if(this->pause&&!(*this->subMenu)){
		window->draw(*this->text);
	}
}
void Battle::Reset(sf::RenderWindow *window,sf::View *view){
	//Get to initial position
	this->moveView(view,-gui.x,-gui.y);
	//Empty memory
	this->player.clear();
	this->team.clear();
	this->target.clear();
	this->ship.clear();
}
void Battle::Load(sf::View *view,std::string directory){
	//Begin
	this->pause=0;
	std::ifstream in(directory.c_str());
	//Informational
	std::getline(in,this->name);
	//GUI
	this->subMenu=new SubMenu();
	this->submenu=new Button(90,85,15,"data/img/buttons/menu/menu.png");
	this->text=new sf::Text(sf::String(""),*gui.Font(),36);
	this->text->setPosition(gui.width(50)-100,gui.height(50)-36);
	this->text->setColor(sf::Color(255,255,255));
	detail.show();
	short x,y;
	in>>x>>y;
	//Water
	this->water=new Layer(1,256,"data/img/water.png");
	//Music
	audio.changeMusic("data/audio/music/Winds of Ithaca.ogg");
	audio.changeAmbient("data/audio/sound/water.ogg");
	//Camera
	this->moveView(view,x,y);
	//Players
	in>>this->human;
	short n;
	in>>n;
	in.ignore();
	//Get data of each player
	this->player.resize(n,Player());
	for(short i=0;i<n;i++)
		//in>>this->player[i];
	//Get team of each player
	this->team.resize(n);
	if(n>2){
		for(short i=0;i<n;i++)
			in>>this->team[i];
	}else{
		this->team[0]=0;
		this->team[1]=1;
	}
	//Ships
	in>>n;
	this->target.resize(n);
	for(short i=0;i<n;i++){
		short player,naval,x,y;
		float rotation;
		in>>player>>naval>>x>>y;
		in>>rotation;
		this->ship.push_back(Ship(player%this->player.size(),naval%(::naval.size()),this->player[player].Faction(),abs(x)%3000,abs(y)%3000,rotation));
		this->player[player].total++;
		this->player[player].last=i+1;
		if(player!=human)
			this->player[player].selected=i+1;

	}
	in.close();
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
	point.x=this->ship[ship].Origin().x+point.x*cos(this->ship[ship].getRotation()*0.017453293);
	point.y=this->ship[ship].Origin().y+point.y*sin(this->ship[ship].getRotation()*0.017453293);
	return point;
}
sf::Vector2f Battle::localForward(float dist,short ship){
	sf::Vector2f target;
	target.x=this->ship[ship].Front().x+dist*cos(this->ship[ship].getRotation()*0.017453293);
	target.y=this->ship[ship].Front().y+dist*sin(this->ship[ship].getRotation()*0.017453293);
	return target;
}
sf::Vector2f Battle::localBackward(float dist,short ship){
	sf::Vector2f target;
	target.x=this->ship[ship].Back().x-dist*cos(this->ship[ship].getRotation()*0.017453293);
	target.y=this->ship[ship].Back().y-dist*sin(this->ship[ship].getRotation()*0.017453293);
	return target;
}
sf::Vector2f Battle::localLeft(float dist,short ship){
	sf::Vector2f target;
	target.x=this->ship[ship].FrontLeft().x+dist*sin(this->ship[ship].getRotation()*0.017453293);
	target.y=this->ship[ship].FrontLeft().y+dist*cos(this->ship[ship].getRotation()*0.017453293);
	return target;
}
sf::Vector2f Battle::localRight(float dist,short ship){
	sf::Vector2f target;
	target.x=this->ship[ship].FrontRight().x-dist*sin(this->ship[ship].getRotation()*0.017453293);
	target.y=this->ship[ship].FrontRight().y-dist*cos(this->ship[ship].getRotation()*0.017453293);
	return target;
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
	return (this->ship[ship].Float()&&this->ship[ship].Player()==this->human);
}
bool Battle::isRammed(short ship){
	return (this->ship[ship].Integrity()<=50);
}
bool Battle::isEnemy(short i,short j){
	if(this->team[this->ship[i].Player()]==this->team[ship[j].Player()])
		return 0;
	return (this->ship[i].Float()&&this->ship[j].Float());
}
bool Battle::isFriend(short i,short j){
	return (this->ship[i].Float()&&this->ship[j].Float()&&this->team[this->ship[i].Player()]==this->team[ship[j].Player()]);
}
void Battle::moveView(sf::View *view,float x,float y){
	if(gui.x+x<0||gui.x+x>3000-view->getSize().x)
		x=0;
	if(gui.y+y<0||gui.y+y>3000-view->getSize().y)
		y=0;
	//Move
	gui.x+=x;
	gui.y+=y;
	about.move(x,y);
	detail.move(x,y);
	info.move(x,y);
	op.move(x,y);
	view->move(x,y);
	this->water->move(x,y);
	this->text->move(x,y);
	this->subMenu->move(x,y);
	this->submenu->move(x,y);
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
		if(!this->ship[j].Float()){
			//Change the score
			this->player[this->ship[i].Player()].destroyed++;
			this->player[this->ship[j].Player()].lost++;
		}
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
				this->ship[i].rotateTo(fabs(this->ship[i].Speed())/50);
				return 1;
			}
			if(this->ship[j].contains(this->ship[i].FrontRight())){
				this->ship[i].rotateTo(-fabs(this->ship[i].Speed())/50);
				return 1;
			}
			//Reverse case
			if(this->ship[i].contains(this->ship[j].FrontLeft())){
				this->ship[i].rotateTo(-fabs(this->ship[i].Speed())/50);
				return 1;
			}
			if(this->ship[i].contains(this->ship[j].FrontRight())){
				this->ship[i].rotateTo(fabs(this->ship[i].Speed())/50);
				return 1;
			}
		}
		//Back points
		if(!this->ship[j].contains(this->ship[i].Back())){
			if(this->ship[j].contains(this->ship[i].BackLeft())){
				this->ship[i].rotateTo(-fabs(this->ship[i].Speed())/50);
				return 1;
			}
			if(this->ship[j].contains(this->ship[i].BackRight())){
				this->ship[i].rotateTo(fabs(this->ship[i].Speed())/50);
				return 1;
			}
			//Reverse case
			if(this->ship[i].contains(this->ship[j].BackLeft())){
				this->ship[i].rotateTo(fabs(this->ship[i].Speed())/50);
				return 1;
			}
			if(this->ship[i].contains(this->ship[j].BackRight())){
				this->ship[i].rotateTo(-fabs(this->ship[i].Speed())/50);
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
				this->ship[i].rotateTo(fabs(this->ship[i].Speed())/50);
				return 1;
			}
			if(this->ship[j].rowsContains(this->ship[i].rowsFrontRight())){
				this->ship[i].rotateTo(-fabs(this->ship[i].Speed())/50);
				return 1;
			}
			//Reverse case
			if(this->ship[i].rowsContains(this->ship[j].rowsFrontLeft())){
				this->ship[i].rotateTo(-fabs(this->ship[i].Speed())/50);
				return 1;
			}
			if(this->ship[i].rowsContains(this->ship[j].rowsFrontRight())){
				this->ship[i].rotateTo(fabs(this->ship[i].Speed())/50);
				return 1;
			}
			//Back points
			if(this->ship[j].rowsContains(this->ship[i].rowsBackLeft())){
				this->ship[i].rotateTo(-fabs(this->ship[i].Speed())/50);
				return 1;
			}
			if(this->ship[j].rowsContains(this->ship[i].rowsBackRight())){
				this->ship[i].rotateTo(fabs(this->ship[i].Speed())/50);
				return 1;
			}
			//Reverse case
			if(this->ship[i].rowsContains(this->ship[j].rowsBackLeft())){
				this->ship[i].rotateTo(fabs(this->ship[i].Speed())/50);
				return 1;
			}
			if(this->ship[j].rowsContains(this->ship[i].rowsBackRight())){
				this->ship[i].rotateTo(-fabs(this->ship[i].Speed())/50);
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
			this->ship[i].rotateTo(fabs(this->ship[i].Speed())/50);
			return 1;
		}
		if(this->ship[j].contains(this->ship[i].FrontRight())){
			this->ship[i].rotateTo(-fabs(this->ship[i].Speed())/50);
			return 1;
		}
		//Reverse case
		if(this->ship[i].contains(this->ship[j].FrontLeft())){
			this->ship[i].rotateTo(-fabs(this->ship[i].Speed())/50);
			return 1;
		}
		if(this->ship[i].contains(this->ship[j].FrontRight())){
			this->ship[i].rotateTo(fabs(this->ship[i].Speed())/50);
			return 1;
		}			
		//Back points
		if(this->ship[j].contains(this->ship[i].BackLeft())){
			this->ship[i].rotateTo(-fabs(this->ship[i].Speed())/50);
			return 1;
		}
		if(this->ship[j].contains(this->ship[i].BackRight())){
			this->ship[i].rotateTo(fabs(this->ship[i].Speed())/50);
			return 1;
		}
		//Reverse case
		if(this->ship[i].contains(this->ship[j].BackLeft())){
			this->ship[i].rotateTo(fabs(this->ship[i].Speed())/50);
			return 1;
		}
		if(this->ship[i].contains(this->ship[j].BackRight())){
			this->ship[i].rotateTo(-fabs(this->ship[i].Speed())/50);
			return 1;
		}
	}
	return 0;
}
//Human
void Battle::select(short ship){
	if(this->player[human].selected)
		deselect();
	if(ship<(short)this->ship.size())
		if(this->isYour(ship)&&this->ship[ship].Float()){
			this->player[human].selected=ship+1;
			std::cout<<this->player[human].selected<<'\n';
			this->ship[ship].setColor(sf::Color(255,95,118));
		}
}
void Battle::deselect(){
	this->ship[this->player[human].selected-1].setColor(sf::Color(255,255,255));
	this->player[human].selected=0;
}
//Update
void Battle::Update(sf::RenderWindow *window,sf::View *view){
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
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)||this->submenu->left("Menu","Click or press M for menu."))
			this->subMenu->show();
	}
	//Gameplay
	if(!this->Pause()){
		//View
		this->moveCamera(window,view);
		//Water
		this->water->Update();
		//Select ship with keyboard
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			this->select(0);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			this->select(1);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			this->select(2);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
			this->select(3);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
			this->select(4);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
			this->select(5);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
			this->select(6);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num8))
			this->select(7);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num9))
			this->select(8);
		else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
			this->select(9);
		//Selected
		if(this->player[human].selected){
			//Selected ship by player
			this->ship[this->player[human].selected-1].show();
			if(!op&&sf::Mouse::isButtonPressed(sf::Mouse::Right)){
				if(!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
					this->target[this->player[human].selected-1].clear();
				this->target[this->player[human].selected-1].push_back(gui.mousePosition());
			}
			//Deselect
			if(sf::Mouse::isButtonPressed(sf::Mouse::Left)||!this->ship[this->player[human].selected-1].Float())
				this->deselect();
		}else
			detail.show("Battle",this->getStatistic());
		//Ships
		for(int i=0;i<(int)this->ship.size();i++){
			//Select ship and target
			if(this->ship[i].Float()){
				//Target for AI
				best=-1;
				nearest=-1;
				minDist=5000;
				for(short j=0;j<(short)this->ship.size();j++){
					if(i!=j){
						//Dist
						d=this->ship[i].getDist(this->ship[j].Origin());
						//Collision
						if(d<=this->ship[i].width()+this->ship[j].width()){
							this->collision(i,j);
						//Select if have a good target
						}else if(this->player[this->ship[i].Player()].selected==i+1&&this->isEnemy(i,j)&&!this->isYour(i)){
							//Nearest enemy
							if(d<minDist){
								minDist=d;
								nearest=j;
							}
							//Best or necesary case
							if(d<500&&dist(this->ship[i].Front(),this->ship[j].Origin())<dist(this->ship[j].Front(),this->ship[i].Origin())){
								best=j;
							}
						}
					}
				}
				//Player
				if(!op&&this->isYour(i)&&this->ship[i].left()){
					this->select(i);
				//AI
				}else{
					//Mouse over ship
					if(!op){
						if(team[this->ship[i].Player()]==team[this->human])
							this->ship[i].mouseOver("(FRIEND)");
						else
							this->ship[i].mouseOver("(ENEMY)");
					}
					//Select target if is selected
					if(this->player[this->ship[i].Player()].selected==i+1){
						this->target[i].clear();
						//Best case
						if(best>-1){
							this->target[i].push_back(this->ship[best].Origin());
						//Forward or nearest enemy
						}else{
							if(this->validPoint(this->localForward(700,i)))
								this->target[i].push_back(this->localForward(300,i));
							else{
								this->target[i].push_back(this->ship[nearest].Origin());
							}
						}
						//Select next ship
						this->player[this->ship[i].Player()].selected=(this->player[this->ship[i].Player()].selected+1)%this->ship.size();
						if(this->ship[this->player[this->ship[i].Player()].selected].Player()!=this->ship[i].Player())
							this->player[this->ship[i].Player()].selected=this->player[this->ship[i].Player()].last-this->player[this->ship[i].Player()].total+1;
					}
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
			//Sink if ship is rammed
			}else if(this->ship[i].sink()){
				this->ship.erase(this->ship.begin()+i);
				this->target.erase(this->target.begin()+i);
				for(short j=this->ship[i].Player();j<(short)this->player.size();j++){
					this->player[j].last--;
				}
			}
		}
	}
	//Exit from battle
	if(gui.selected!=4){
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
Battle::~Battle(){

}