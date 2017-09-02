#include "campaign.h"
#include "history.h"
#include "menu.h"
//Local
int main(){
	//Window
	sf::RenderWindow window(sf::VideoMode::getDesktopMode(),"Konio");
	sf::View view(sf::FloatRect(0,0,(float)gui.width(),(float)gui.height()));
	sf::ContextSettings settings;
	window.setView(view);
	window.setFramerateLimit(60);
	//GUI
	Background *background;
	Menu *menu;
	Campaign *campaign;
	History *history;
	//Data game
	background=new Background("data/img/backgrounds/menu.png");
	menu=new Menu();
	//Navals
	sails.loadFromFile("data/navals/sails.png");
	sails.setSmooth(true);
	for(short i=0;i<5;i++)
		naval.push_back(i);
	//Running
	while(window.isOpen()){
		gui.Update(&window);
		//Events
		sf::Event event;
		while(window.pollEvent(event)){
			//Close
			if(event.type==sf::Event::Closed)
				window.close();
		}
		//Draw
		window.clear();
		if(!gui.selected||gui.selected>5){
			//GUI
			gui.selected=1;
		}else if(gui.selected==1){
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
				background->Update("data/img/backgrounds/menu.png");
				delete campaign;
				menu=new Menu();
			}
			if(gui.selected==4){
				delete background;
			}
		}else if(gui.selected==3){
			//History
			background->Render(&window);
			history->Render(&window);
			history->Update();
			//Back to menu
			if(gui.selected==1){
				background->Update("data/img/backgrounds/menu.png");
				delete history;
				menu=new Menu();
			}
		}else if(gui.selected==4){
			//Game
			campaign->game->Render(&window);
			campaign->game->Update(&window,&view);
			//Back to campaign
			if(gui.selected==2){
				background=new Background("data/img/backgrounds/campaign.png");
			}
		}else if(gui.selected==5){
			//Battle
			campaign->game->battle->Render(&window);
			campaign->game->battle->Update(&window,&view);
		}
		//Display
		window.setView(view);
		window.display();
	}
	return 0;
}