#pragma once

#include <SFML/Audio.hpp>

class cMusicManager {	
public:
	static std::string getPath(unsigned char number) { return m_path[number]; };
	static void setMusic(unsigned char number, std::string fileName);	
	static void play(unsigned char number);
	static void pause(unsigned char number);
	static void stop(unsigned char number);
		
	static float getVolume(unsigned char number);		static void setVolume(unsigned char number, float volume);
	static sf::Time getOffset(unsigned char number);	static void setOffset(unsigned char number, sf::Time timeOffset);
	static void resetOffset();
	static bool getDoLoop(unsigned char number);		static void setDoLoop(unsigned char number, bool doLoop);
	static bool getDoPlay();
	static void setDoPlay(bool doPlay) { m_doPlay = doPlay; };

	static sf::Time getDuration(unsigned char number);
	static sf::Time getDurationPrevious() { return m_durationPrevious;	};
	
	static bool isPlaying(unsigned char number);

private:
	static sf::Music m_music[2];
	static std::string m_path[2];

	static sf::Time m_durationPrevious;

	static bool m_doPlay;
};