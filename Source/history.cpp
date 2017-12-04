#include "history.h"

History::History(){
	this->menu=new Button(90,85,15,"data/img/buttons/menu/menu.png");
	this->info=new Label(gui.width(50)-300,gui.height(50)-200,600,400,0);
}
void History::Render(sf::RenderWindow *window){
	if(*this->info)
		this->info->Render(window);
	this->menu->Render(window);
}
void History::Update(){
	about.hide();
	for(short i=0;i<4&&!(*this->info);i++){
		for(short j=0;j<2&&!(*this->info);j++){
			if(sf::IntRect(gui.width(25)*i,gui.width(12)+gui.width(20)*j,gui.width(25),gui.width(20)).contains(gui.mousePosition().x,gui.mousePosition().y)&&sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				//Label
				in.open("data/history/"+std::to_string(i+j*5)+".txt");
				if(in.is_open()){
					std::string title,text;
					getline(in,title);
					getline(in,text,'*');
					this->info->show(title,text);
				}else
					this->info->show("Unvailable!","The file "+std::to_string(i+j*5)+".txt is unvailable.");
				in.close();
			}
		}
	}
	if(this->info->right())
		this->info->hide();
	if(this->menu->left("Menu","Click or press M to leave from campaign.",sf::Keyboard::M)){
		gui.selected=1;
		this->info->hide();
	}
}
History::~History(){

}
//Variable
History *history;