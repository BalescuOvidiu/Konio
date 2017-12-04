#include "node.h"
//Constructors
Node::Node(short x,short y,short radius){
	this->pos.x=x;
	this->pos.y=y;
	this->radius=radius;
}
Node::Node(sf::Vector2f point,short radius){
	this->pos=point;
	this->radius=radius;
}
//Get data
sf::Vector2f Node::getPosition(){
	return this->pos;
}
short Node::r(){
	return this->radius;
}
float Node::dist(sf::Vector2f point){
	return ::dist(this->pos,point);
}
float Node::dist(Node node){
	return ::dist(this->pos,node.getPosition());
}
//Collsions
bool Node::contains(sf::Vector2f point){
	return(this->dist(point)<=this->radius);
}
bool Node::collision(Node node){
	return(distSquare(this->pos,node.getPosition())<=((this->radius+node.r())*(this->radius+node.r())));
}
Node::~Node(){

}
//Guide
std::vector<sf::Vertex> getGuide(sf::Vector2f point,std::vector<Node> route,sf::Color color){
	std::vector<sf::Vertex> guide;
	if(route.size()>2)
		if(route[route.size()-2].contains(route[route.size()-1].getPosition()))
			route.erase(route.begin()+route.size()-2);
	//Guide
	while(route.size()>=1){
		float angle=getAngle(point,route[0].getPosition());
		float SIN=2*sin(angle*0.017453293);
		float COS=2*cos(angle*0.017453293);
		while(!route[0].contains(point)){
			//Back points
			guide.push_back(sf::Vertex(sf::Vector2f(point.x-COS+SIN,point.y-SIN-COS),color));
			guide.push_back(sf::Vertex(sf::Vector2f(point.x-COS-SIN,point.y-SIN+COS),color));
			//Front points
			guide.push_back(sf::Vertex(sf::Vector2f(point.x+2*COS-SIN,point.y+2*SIN+COS),color));
			guide.push_back(sf::Vertex(sf::Vector2f(point.x+2*COS+SIN,point.y+2*SIN-COS),color));
			//Next point
			point.x+=8*COS;
			point.y+=8*SIN;
		}
		if(route.size()>1){
			angle=getAngle(point,route[1].getPosition());
			SIN=2*sin(angle*0.017453293);
			COS=2*cos(angle*0.017453293);
			while(route[0].contains(point)){
				//Back points
				guide.push_back(sf::Vertex(sf::Vector2f(point.x-COS+SIN,point.y-SIN-COS),color));
				guide.push_back(sf::Vertex(sf::Vector2f(point.x-COS-SIN,point.y-SIN+COS),color));
				//Front points
				guide.push_back(sf::Vertex(sf::Vector2f(point.x+2*COS-SIN,point.y+2*SIN+COS),color));
				guide.push_back(sf::Vertex(sf::Vector2f(point.x+2*COS+SIN,point.y+2*SIN-COS),color));
				//Next point
				point.x+=8*COS;
				point.y+=8*SIN;
			}
		}else{
			while(dist(route[0].getPosition(),point)>8){
				//Back points
				guide.push_back(sf::Vertex(sf::Vector2f(point.x-COS+SIN,point.y-SIN-COS),color));
				guide.push_back(sf::Vertex(sf::Vector2f(point.x-COS-SIN,point.y-SIN+COS),color));
				//Front points
				guide.push_back(sf::Vertex(sf::Vector2f(point.x+2*COS-SIN,point.y+2*SIN+COS),color));
				guide.push_back(sf::Vertex(sf::Vector2f(point.x+2*COS+SIN,point.y+2*SIN-COS),color));
				//Next point
				point.x+=8*COS;
				point.y+=8*SIN;
			}
		}
		point.x-=8*COS;
		point.y-=8*SIN;
		route.erase(route.begin());
	}
	return guide;
}
std::vector<sf::Vertex> setGuideColor(std::vector<sf::Vertex> guide,sf::Color color){
	for(unsigned i=0;i<guide.size();i++)
		guide[i].color=color;
	return guide;
}