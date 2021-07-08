#include "MusicManager.h"
#include "SoundBufferManager.h"
#include <iostream>

sf::Music cMusicManager::m_music[2];
std::string cMusicManager::m_path[2];
sf::Time cMusicManager::m_durationPrevious;
bool cMusicManager::m_doPlay = false;

void cMusicManager::resetOffset() {
	m_music[0].setPlayingOffset(sf::Time::Zero);
	m_music[1].setPlayingOffset(sf::Time::Zero);
}

sf::Time cMusicManager::getDuration(unsigned char number) {
	if (number > 2) {
		number = 2;
	}
	return m_music[number].getDuration();
}

sf::Time cMusicManager::getOffset(unsigned char number) {
	if (number > 2) {
		number = 2;
	}
	return m_music[number].getPlayingOffset();
}

void cMusicManager::setOffset(unsigned char number, sf::Time timeOffset) {
	if (number > 2) {
		number = 2;
	}
	if (timeOffset > m_music[number].getDuration()) {
		timeOffset = m_music[number].getDuration();
	}
	m_music[number].setPlayingOffset(timeOffset);
}

void cMusicManager::setMusic(unsigned char number, std::string fileName) {
	m_path[number] = fileName;

	m_durationPrevious = m_music[0].getDuration();

	if (!m_music[number].openFromFile(fileName)) {
		std::cout << "Couldn't open " + fileName << "\n";
	}
	//m_music0.setLoop(true);
	//std::cout << "Background music volume: " << m_musicBackground.GetVolume() << "\n";
}

void cMusicManager::play(unsigned char number) {
	m_music[number].play();
}

void cMusicManager::pause(unsigned char number) {
	m_music[number].pause();
}

void cMusicManager::stop(unsigned char number) {
	m_music[number].stop();
}

void cMusicManager::setDoLoop(unsigned char number, bool doLoop) {
	m_music[number].setLoop(doLoop);
}

float cMusicManager::getVolume(unsigned char number) {
	return m_music[number].getVolume();
}

void cMusicManager::setVolume(unsigned char number, float volume) {
	m_music[number].setVolume(volume);
}

bool cMusicManager::getDoLoop(unsigned char number) {
	return m_music[number].getLoop();
}

bool cMusicManager::getDoPlay() {
	return m_doPlay;
}

bool cMusicManager::isPlaying(unsigned char number) {
	if (m_music[number].getStatus() == sf::Music::Playing) {
		return true;
	}
	return false;
}