#include "naval.h"

//Constructor
Naval::Naval(short id){
	//Read data from file
	std::ifstream in("data/navals/"+std::to_string(id)+".txt");
	in>>this->basic;
	in>>this->rowers;
	in>>this->cost;
	in.close();
	//load texture
	loadTexture(id);
}
//Get data
std::string Naval::Name(){
	return this->basic.name;
}
std::string Naval::Description(){
	return "Cost: "+std::to_string((int)this->cost)+" coins    Speed: "+std::to_string(this->basic.speed)+" km/h with "+std::to_string(this->rowers)+" rowers";
}
float Naval::Speed(){
	return this->basic.speed;
}
float Naval::Cost(){
	return this->cost;
}
short Naval::Rowers(){
	return this->rowers;
}
//Size
short Naval::width(){
	return (short)this->body.getSize().x;
}
short Naval::widthRows(){
	return (short)this->rows.getSize().y;
}
short Naval::height(){
	return (short)this->body.getSize().y;
}
//Texture
sf::Texture& Naval::Body(){
	return this->body;
}
sf::Texture& Naval::Ram(){
	return this->ram;
}
sf::Texture& Naval::Rows(){
	return this->rows;
}
void Naval::loadTexture(short id){
	//Texture
	this->body.loadFromFile("data/navals/"+std::to_string(id)+".png");
	this->ram.loadFromFile("data/navals/"+std::to_string(id)+"_ram.png");
	this->rows.loadFromFile("data/navals/"+std::to_string(id)+"_rows.png");
	this->body.setSmooth(true);
	this->ram.setSmooth(true);
	this->rows.setSmooth(true);	
}
std::vector<Naval> naval;
//The sails
sf::Texture sails;