#include "submenu.h"

SubMenu::SubMenu(){
	this->visible=1;
	this->resume=new Button(20,40,16,"data/img/buttons/menu/resume.png");
	this->campaign=new Button(40,40,16,"data/img/buttons/menu/campaign.png");
	this->options=new Button(60,40,16,"data/img/buttons/menu/options_small.png");
	this->exit=new Button(80,40,16,"data/img/buttons/menu/exit_small.png");
	this->move(gui.x,gui.y);
}
void SubMenu::Render(sf::RenderWindow *window){
	this->resume->Render(window);
	this->campaign->Render(window);
	this->options->Render(window);
	this->exit->Render(window);
	if(op!=NULL)
		op->Render(window);
}
void SubMenu::Update(sf::RenderWindow *window){
	//Keys
	if(this->resume->left("Resume","Click or press R to remain in game.",sf::Keyboard::R))
		this->visible=0;
	else if(this->campaign->left("Campaign","Click or press C to exit from game and to see campaign map.",sf::Keyboard::C))
		gui.selected=2;
	else if(this->exit->left("Exit","Click or press Esc to exit from game.",sf::Keyboard::Escape))
		window->close();
	//Options
	if(op!=NULL){
		op->Update();
		if(this->options->left("Options","Press left button of mouse or O to close options section."))
			op->hide();
		if(!(*op)){
			op=NULL;
		}
	}else{
		if(this->options->left("Options","You can set sound and volume music. Click or press O to open options section.",sf::Keyboard::O)){
			op=new Options();
			op->show();
		}
	}
	if(!this->visible)
		about.hide();
}
void SubMenu::show(){
	this->visible=1;
}
void SubMenu::hide(){
	this->visible=0;
}
void SubMenu::move(float x,float y){
	this->resume->move(x,y);
	this->campaign->move(x,y);
	this->options->move(x,y);
	this->exit->move(x,y);
}
void SubMenu::setPosition(float x,float y){
	this->resume->setPosition(x,y);
	this->campaign->setPosition(x,y);
	this->options->setPosition(x,y);
	this->exit->setPosition(x,y);
}
SubMenu::operator bool(){
	return this->visible;
}
SubMenu::~SubMenu(){

}
//Global Variable
SubMenu *subMenu=NULL;