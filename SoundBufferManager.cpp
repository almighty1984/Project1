#include "SoundBufferManager.h"

std::map<std::string, sf::SoundBuffer*> cSoundBufferManager::m_soundBuffers;

cSoundBufferManager::~cSoundBufferManager() {	
	unloadAll();
}

sf::SoundBuffer* cSoundBufferManager::load( std::string fileName ) {
	auto it = m_soundBuffers.find(fileName);
	
	sf::SoundBuffer *sfBuffer;

	if (it == m_soundBuffers.end()) {
		sfBuffer = new sf::SoundBuffer;

		sfBuffer->loadFromFile(fileName);			
		m_soundBuffers[fileName] = sfBuffer;
		return sfBuffer;
	} else {
		std::cout << "SoundBuffer already in map: " << it->second << " " << fileName << "\n";
		return it->second;
	}
}

void cSoundBufferManager::unloadAll() {
	for (auto it = m_soundBuffers.begin(); it != m_soundBuffers.end(); ++it) {
		delete it->second;
	}
	m_soundBuffers.clear();
}