#include "good.h"
//Constructor
Good::Good(std::string name,short price){
	this->name=name;
	this->price=price;
}
//Get data
std::string Good::Name(){
	return this->name;
}
short Good::Price(){
	return this->price;
}
Good::~Good(){
	
}
//Load description
std::string goodDescription(short id){
	std::ifstream in("data/game/goods/"+std::to_string(id)+".txt");
	if(in.is_open()){
		std::string text;
		std::getline(in,text,'*');
		return text+" Price: "+Format(::good[id].Price())+" coins";
	}
	in.close();
	return " ";
}
//Global variable
std::vector<Good> good;