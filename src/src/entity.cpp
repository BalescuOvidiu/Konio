#include "entity.h"
//Basic
std::ifstream &operator>>(std::ifstream &in,Basic &basic){
	std::getline(in,basic.name);
	in>>basic.speed;
	return in;
}
//Entity
std::ifstream &operator>>(std::ifstream &in,Entity &entity){
	in>>entity.basic;
	return in;
}