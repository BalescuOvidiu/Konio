#ifndef SOUND_H
#define SOUND_H

#include "gui.h"
class Audio{
private:
	//Sounds and music
	sf::Music *music,*ambient,*click;
public:
	//Volume variable
	float musicVolume,soundVolume;
	//Methods
	Audio();
	void Update();
	void Click();
	void changeMusic(std::string directory);
	void changeAmbient(std::string directory);
	void stopAmbient();
	~Audio();
};
extern Audio audio;
#endif