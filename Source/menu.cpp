#include "menu.h"

Menu::Menu(){
	this->play=new Button(20,40,16,"data/img/buttons/menu/play.png");
	this->history=new Button(40,40,16,"data/img/buttons/menu/history.png");
	this->options=new Button(60,40,16,"data/img/buttons/menu/options.png");
	this->exit=new Button(80,40,16,"data/img/buttons/menu/exit.png");
}
void Menu::Render(sf::RenderWindow *window){
	this->play->Render(window);
	this->history->Render(window);
	this->options->Render(window);
	this->exit->Render(window);
	if(op!=NULL)
		op->Render(window);
	if(about)
		about.Render(window);
}
void Menu::Update(sf::RenderWindow *window){
	about.hide();
	//Keys or button
	if(this->play->left("Campaign","It's a map with of Ancient Greece. Click or press P to play.",sf::Keyboard::P))
		gui.selected=2;
	else if(this->history->left("History","Click or press H to read and learn about life from Ancient Greece period.",sf::Keyboard::H))
		gui.selected=3;
	else if(this->exit->left("Exit","Click or press Esc to exit from game.",sf::Keyboard::Escape))
		window->close();
	//Options
	if(op!=NULL){
		op->Update();
		//Hide
		if(this->options->left("Options","Press left button of mouse or O to close options section.",sf::Keyboard::O))
			op->hide();
		//Clear memory
		if(!(*op))
			op=NULL;
	}else{
		if(this->options->left("Options","You can set sound and volume music. Click or press O to open options section.",sf::Keyboard::O)){
			op=new Options();
			op->show();
		}
	}
}
Menu::~Menu(){
	delete op;
	op=NULL;
}
//Variable
Menu *menu;