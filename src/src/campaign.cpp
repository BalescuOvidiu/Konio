#include "campaign.h"
//Campaign
Campaign::Campaign(){
	this->menu=new Button(90,85,15,"data/img/buttons/menu/menu.png");
	this->game=NULL;
	LoadGames();
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
	if(this->game!=NULL){
		delete game;
		game=NULL;
		this->LoadGames();
	}
	if(gui.canClick(600)){
		for(unsigned i=this->button.size();i--;)
			if(this->button[i].mouseOver()){
				//Saved progress
				std::ifstream saved("data/game/saved/"+std::to_string(i)+".txt");
				//Play game
				if(this->button[i].left()){
					in.open("data/game/data.txt");
					if(in.is_open()){
						//Enter in game
						if(saved.is_open())
							this->game=new Game("data/game/saved/"+std::to_string(i)+".txt",view,i);
						else
							this->game=new Game("data/game/data.txt",view,i);
						this->button.clear();
						gui.selected=4;
					}
					in.close();
					return ;
				//Label
				}else{
					if(saved.is_open())
						in.open("data/campaign/about/"+std::to_string(i)+"_saved.txt");
					else
						in.open("data/campaign/about/"+std::to_string(i)+".txt");
					if(in.is_open()){
						std::string title,text;
						getline(in,title);
						getline(in,text,'*');
						if(saved.is_open()){
							about.show(title+" Right-click to delete saved game.",text);
							if(this->button[i].right()){
								remove(("data/game/saved/"+std::to_string(i)+".txt").c_str());
								remove(("data/campaign/about/"+std::to_string(i)+"_saved.txt").c_str());
							}
						}
						else
							about.show(title,text);
					}
					in.close();
				}
			}
	}
}
void Campaign::LoadGames(){
	std::ifstream in("data/campaign/data.txt");
	if(in.is_open()){
		short x,y,i=0;
		while(in>>x>>y)
			this->button.push_back(Button(x,y,"data/game/icons/"+std::to_string(i++)+".png"));
	}
	in.close();
}
Campaign::~Campaign(){
	button.clear();
}
//Variable
Campaign *campaign;