#include "naval.h"

std::ifstream &operator>>(std::ifstream &in,Naval &naval){
	in>>naval.basic;
	short id;
	in>>id;
	naval.body.loadFromFile("data/navals/"+std::to_string(id)+".png");
	naval.ram.loadFromFile("data/navals/"+std::to_string(id)+"_ram.png");
	naval.rows.loadFromFile("data/navals/"+std::to_string(id)+"_rows.png");
	naval.body.setSmooth(true);
	naval.ram.setSmooth(true);
	naval.rows.setSmooth(true);
	naval.width=naval.body.getSize().x;
	naval.height=naval.body.getSize().y;
	naval.rowsWidth=naval.rows.getSize().y;
	in>>naval.rowers;
	return in;
}
std::vector<Naval> naval;
//The sails
sf::Texture sails;