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
	if(op)
		op.Render(window);
	if(about)
		about.Render(window);
}
void Menu::Update(sf::RenderWindow *window){
	about.hide();
	//Keys or button
	if(this->play->left("Campaign","It's a map with of Ancient Greece. Click or press P to play.")||sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
		gui.selected=2;
	}else if(this->history->left("History","Click or press H to read and learn about life from Ancient Greece period.")||sf::Keyboard::isKeyPressed(sf::Keyboard::H)){
		gui.selected=3;
	}else if(this->exit->left("Exit","Click or press Esc to exit from game.")||sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
		window->close();
	}	
	//Options
	if(op){
		if(this->options->right("Options","Press right button of mouse or I to close options section."))
			op.hide();
		op.Update();
	}else{
		if(this->options->left("Options","You can set sound and volume music. Click or press O to open options section.")||sf::Keyboard::isKeyPressed(sf::Keyboard::O))
			op.show();
	}
	//Run from menu to campaign or history
	if(gui.selected!=1){
		op.hide();
		about.hide();
		sf::sleep(sf::Time(sf::milliseconds(200)));
	}
}
Menu::~Menu(){

}