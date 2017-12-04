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
	for(unsigned i=0;i<this->button.size();i++)
		this->button[i].Render(window);
}
void Campaign::Update(sf::View *view){
	about.hide();
	if(this->menu->left("Menu","Click or press M to leave from campaign.",sf::Keyboard::M))
		gui.selected=1;
	for(unsigned i=0;i<this->button.size();i++){
		if(this->button[i].mouseOver()){
			std::ifstream saved("data/game/saved/"+std::to_string(i)+".txt");
			if(this->button[i].left()){
				std::ifstream file("data/game/data.txt");
				if(file.is_open()){
					//Enter in game
					if(saved.is_open())
						this->game=new Game("data/game/saved/"+std::to_string(i)+".txt",view,i);
					else
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
				if(saved.is_open()){
					about.show(title+" Right-click to delete saved game.",text);
					if(this->button[i].right())
						remove(("data/game/saved/"+std::to_string(i)+".txt").c_str());
				}
				else
					about.show(title,text);
			}
			in.close();
		}
	}
}
Campaign::~Campaign(){

}
//Variable
Campaign *campaign;