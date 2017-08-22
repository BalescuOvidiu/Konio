#include "history.h"

History::History(){
	this->menu=new Button(90,85,15,"data/img/buttons/menu/menu.png");
}
void History::Render(sf::RenderWindow *window){
	if(info)
		info.Render(window);
	this->menu->Render(window);
}
void History::Update(){
	about.hide();
	for(short i=0;i<4&&!(info);i++){
		for(short j=0;j<2&&!(info);j++){
			if(sf::IntRect(gui.width(25)*i,gui.width(12)+gui.width(20)*j,gui.width(25),gui.width(20)).contains(gui.mousePosition().x,gui.mousePosition().y)&&sf::Mouse::isButtonPressed(sf::Mouse::Left)){
				//Label
				std::ifstream in("data/history/"+std::to_string(i+j*5)+".txt");
				if(in.is_open()){
					std::string title,text;
					getline(in,title);
					getline(in,text,'*');
					info.show(title,text);
				}else{
					info.setTitle(std::to_string(i)+" "+std::to_string(j));
					info.setText(std::to_string(gui.width(25)*i)+" "+std::to_string(gui.width(20)+gui.width(20)*j)+" "+std::to_string(gui.width(25))+" "+std::to_string(gui.width(20)));
					info.show();
				}
				in.close();
			}
		}
	}
	if(info.right())
		info.hide();
	if(this->menu->left("Menu","Click or press M to leave from campaign.")||sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
		gui.selected=1;
		info.hide();
	}
}
History::~History(){

}