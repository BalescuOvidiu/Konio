#include "campaign.h"
//Campaign
Campaign::Campaign(){
	this->menu=new Button(90,85,15,"data/img/buttons/menu/menu.png");
	this->game=NULL;
	//Read data from file
	std::ifstream in("data/campaign/data.txt");
	if(in.is_open()){
		short x,y,i=0;
		while(in>>x>>y)
			this->button.push_back(Button(x,y,"data/game/icons/"+std::to_string(i++)+".png"));
	}
	in.close();
}
void Campaign::Render(sf::RenderWindow *window){
	if(about)
		about.Render(window);
	this->menu->Render(window);
	for(short i=0;i<(short)(button.size());i++)
		this->button[i].Render(window);
}
void Campaign::Update(sf::View *view){
	about.hide();
	if(gui.selected!=4)
		this->game=NULL;
	if(this->menu->left("Menu","Click or press M to leave from campaign.")||sf::Keyboard::isKeyPressed(sf::Keyboard::M))
		gui.selected=1;
	for(short i=0;i<(short)(this->button.size());i++){
		if(this->button[i].mouseOver()){
			if(this->button[i].left()){
				std::ifstream file("data/game/data.txt");
				if(file.is_open()){
					this->game=new Game("data/game/data.txt",view,i);
					gui.selected=4;
				}
				file.close();
			}
			//Label
			std::ifstream in("data/campaign/about/"+std::to_string(i)+".txt");
			if(in.is_open()){
				std::string title,text;
				getline(in,title);
				getline(in,text,'*');
				about.show(title,text);
			}
			in.close();
		}
	}
}
Campaign::~Campaign(){

}