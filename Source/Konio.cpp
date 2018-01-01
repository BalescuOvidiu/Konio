#include "campaign.h"
#include "history.h"
#include "menu.h"
//Local
int main(){
	//Window
	sf::RenderWindow window(sf::VideoMode(0,0,32),"Konio",sf::Style::Fullscreen,sf::ContextSettings(24,8,0,2,1));
	sf::View view(sf::FloatRect(0,0,(float)gui.width(),(float)gui.height()));
	//Initialize
	window.setFramerateLimit(60);
	window.setView(view);
	window.setSize(sf::Vector2u(gui.width(),gui.height()));
	//GUI
	background=new Background("data/img/backgrounds/menu.png");
	menu=new Menu();
	about=Label(0,gui.height()-120,gui.width(),120,0);
	//Marine texture
	arrowTexture.loadFromFile("data/texture/arrowTexture.png");
	arrowTexture.setSmooth(true);
	marineBody.loadFromFile("data/texture/marineBody.png");
	marineBody.setSmooth(true);
	//Navals texture
	sails.loadFromFile("data/navals/sails.png");
	sails.setSmooth(true);
	fleetBody.loadFromFile("data/navals/fleet.png");
	fleetBody.setSmooth(true);
	//Navals data
	in.open("data/numbers.txt");
	in>>nFormation;
	for(short i=0;i<nFormation;i++)
		naval.push_back(Naval("data/navals/"+std::to_string(i)));
	in>>nFormation>>mercenaries;
	in.close();
	//Running
	while(window.isOpen()){
		//Clear
		window.clear();
		//Select scenes
		if(gui.selected==1){
			//Menu
			background->Render(&window);
			menu->Render(&window);
			menu->Update(&window);
			//To campaign
			if(gui.selected==2){
				delete menu;
				background->Update("data/img/backgrounds/campaign.png");
				campaign=new Campaign();
			}
			//To history
			if(gui.selected==3){
				delete menu;
				background->Update("data/img/backgrounds/history.png");
				history=new History();
			}
		}else if(gui.selected==2){
			//Campaign
			background->Render(&window);
			campaign->Render(&window);
			campaign->Update(&view);
			//Back to menu
			if(gui.selected==1){
				delete campaign;
				background->Update("data/img/backgrounds/menu.png");
				menu=new Menu();
			}
			if(gui.selected==4)
				delete background;
		}else if(gui.selected==3){
			//History
			background->Render(&window);
			history->Render(&window);
			history->Update();
			//Back to menu
			if(gui.selected==1){
				delete history;
				background->Update("data/img/backgrounds/menu.png");
				menu=new Menu();
			}
		}else if(gui.selected==4){
			//Game
			campaign->game->Render(&window);
			campaign->game->Update(&window,&view);
			//Back to campaign
			if(gui.selected==2)
				background=new Background("data/img/backgrounds/campaign.png");
		}else if(gui.selected==5){
			//Battle
			campaign->game->battle->Render(&window);
			campaign->game->battle->Update(&window,&view);
		}else
			gui.selected=1;
		//Display
		window.setView(view);
		window.display();
	}
	return 0;
}