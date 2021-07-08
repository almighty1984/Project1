#pragma once

#include <SFML/Audio.hpp>

#include <iostream>
#include <map>

enum class eSoundTag {
	ak47 = 0, attack,
	block, bounce, breakBlock, breakPot,
	chestOpen, circleSaw, coin, collidedBaggen, collidedFlugan,
	death, fluganCharge, fluganAttack, fluganHurt0, fluganHurt1, fluganHurt2, flylingAttack, flylingHurt,
	hit, hitGround, hitHead, hover,
	jump, jumpHigh,
	rainOut,
	swim, splash, stepGrass, swingAttach, swingDetach,
	toss, turn, wallSlide
};

class cSoundsManager {
public:	
	~cSoundsManager();

	static void clearSounds();
	static void createSound(std::string id, std::string fileName);

	static void play(eSoundTag soundTag);
	static void play(eSoundTag soundTag, float x);
	static void play(eSoundTag soundTag, float x, float y);
	static void play(eSoundTag soundTag, float x, float y, float z);
	static void stop(eSoundTag soundTag);
	static void pause(eSoundTag soundTag);
	static void setPlayingOffset(eSoundTag soundTag, sf::Time playingOffset);
	static sf::Time getPlayingOffset(eSoundTag soundTag);
	static void setLoop(eSoundTag soundTag, bool loop);
	static void setVolume(eSoundTag soundTag, float volume);
	
	static bool isPlaying(eSoundTag soundTag);

	static sf::SoundSource::Status getStatus(eSoundTag soundTag);

	static std::map<eSoundTag, sf::Sound*> m_sounds;
	
	//void loadConfig(std::string fileName);
private:
	//cSoundsManager();	
};
