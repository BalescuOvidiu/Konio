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
float Node::Dist(sf::Vector2f point){
	return ::Dist(this->pos,point);
}
float Node::Dist(Node node){
	return ::Dist(this->pos,node.getPosition());
}
//Collsions
bool Node::contains(sf::Vector2f point){
	return(this->Dist(point)<=this->radius*this->radius);
}
bool Node::collision(Node node){
	return(::Dist(this->pos,node.getPosition())<=((this->radius+node.r())*(this->radius+node.r())));
}
Node::~Node(){

}//Guide
std::vector<sf::Vertex> getGuide(sf::Vector2f point,std::deque<sf::Vector2f> route,sf::Color color){
	std::vector<sf::Vertex> guide;
	while(route.size()){
		float angle=getAngle(point,route[0]);
		float SIN=2*Sin(angle);
		float COS=2*Cos(angle);
		while(dist(route[0],point)>8){
			point.x+=8*COS;
			point.y+=8*SIN;
			//Back points
			guide.push_back(sf::Vertex(sf::Vector2f(point.x-COS+SIN,point.y-SIN-COS),color));
			guide.push_back(sf::Vertex(sf::Vector2f(point.x-COS-SIN,point.y-SIN+COS),color));
			//Front points
			guide.push_back(sf::Vertex(sf::Vector2f(point.x+2*COS-SIN,point.y+2*SIN+COS),color));
			guide.push_back(sf::Vertex(sf::Vector2f(point.x+2*COS+SIN,point.y+2*SIN-COS),color));
			//Next point
		}
		route.erase(route.begin());
	}
	return guide;
}
std::vector<sf::Vertex> getGuide(sf::Vector2f point,std::vector<Node> route,sf::Color color){
	std::vector<sf::Vertex> guide;
	//Guide
	while(route.size()){
		float angle=getAngle(point,route[0].getPosition());
		float SIN=2*Sin(angle);
		float COS=2*Cos(angle);
		if(route.size()>1){
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
				if(route[0].r()<16)
					break;
			}
			angle=getAngle(point,route[1].getPosition());
			SIN=2*Sin(angle);
			COS=2*Cos(angle);
			if(route.size()!=2||!route[0].contains(route[1].getPosition()))
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
					if(Dist(route[0].getPosition(),route[1].getPosition())<256)
						break;
				}
		}else{
			while(Dist(route[0].getPosition(),point)>64){
				point.x+=8*COS;
				point.y+=8*SIN;
				//Back points
				guide.push_back(sf::Vertex(sf::Vector2f(point.x-COS+SIN,point.y-SIN-COS),color));
				guide.push_back(sf::Vertex(sf::Vector2f(point.x-COS-SIN,point.y-SIN+COS),color));
				//Front points
				guide.push_back(sf::Vertex(sf::Vector2f(point.x+2*COS-SIN,point.y+2*SIN+COS),color));
				guide.push_back(sf::Vertex(sf::Vector2f(point.x+2*COS+SIN,point.y+2*SIN-COS),color));
				if(route[0].r()<16)
					break;
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