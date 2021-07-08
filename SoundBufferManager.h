#pragma once

#include <SFML/Audio.hpp>

#include <iostream>
#include <map>

class cSoundBufferManager {	
public:
	static sf::SoundBuffer* load(std::string fileName);
	static void unloadAll();

	~cSoundBufferManager();

private:	
	static std::map<std::string, sf::SoundBuffer*> m_soundBuffers;
};

