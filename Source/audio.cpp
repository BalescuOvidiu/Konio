#include "audio.h"

Audio::Audio(){
	//Music
	this->music=new sf::Music();
	this->music->setLoop(true);
	this->changeMusic("data/audio/music/Athena.ogg");
	//Click sound
	this->click=new sf::Music();
	this->click->openFromFile("data/audio/sound/click.wav");
	this->boom=new sf::Music();
	this->boom->openFromFile("data/audio/sound/boom.ogg");
	//Ambient
	this->ambient=new sf::Music();
	this->ambient->setLoop(true);
	this->ambient->openFromFile("data/audio/sound/water.ogg");
	this->ambient->stop();
	//Volume
	std::ifstream in("data/audio/volume.txt");
	if(in.is_open())
		in>>this->musicVolume>>this->soundVolume;
	else
		this->musicVolume=this->soundVolume=100;
	in.close();
	this->Update();
}
void Audio::Update(){
	this->music->setVolume((short)this->musicVolume);
	this->boom->setVolume((short)this->soundVolume);
	this->click->setVolume((short)this->soundVolume);
	this->ambient->setVolume((short)this->soundVolume);
	//Write new volumes
	std::ofstream out("data/audio/volume.txt");
	out<<this->musicVolume<<' '<<this->soundVolume;
	out.close();
}
void Audio::Boom(){
	this->boom->play();
}
void Audio::Click(){
	if(this->click->getStatus()==sf::Sound::Stopped)
		this->click->play();
}
void Audio::changeMusic(std::string directory){
	this->music->stop();
	if(this->music->openFromFile(directory))
		this->music->play();
}
void Audio::changeAmbient(std::string directory){
	this->ambient->stop();
	if(this->ambient->openFromFile(directory))
		this->ambient->play();
}
void Audio::stopAmbient(){
	this->ambient->stop();
}
Audio::~Audio(){

}
Audio audio;



	

