#include "SoundsManager.h"
#include "SoundBufferManager.h"

std::map<eSoundTag, sf::Sound*> cSoundsManager::m_sounds;

cSoundsManager::~cSoundsManager() {
	m_sounds.clear();
}

void cSoundsManager::clearSounds() {
	m_sounds.clear();
}

void cSoundsManager::createSound(std::string id, std::string fileName) {	
	if (id.empty()) {
		return;
	}

	eSoundTag soundTag;

	if (id == "ak47") {
		soundTag = eSoundTag::ak47;
	} else if (id == "attack") {
		soundTag = eSoundTag::attack;
	} else if (id == "block") {
		soundTag = eSoundTag::block;
	} else if (id == "bounce") {
		soundTag = eSoundTag::bounce;
	} else if (id == "breakBlock") {
		soundTag = eSoundTag::breakBlock;
	} else if (id == "breakPot") {
		soundTag = eSoundTag::breakPot;
	} else if (id == "chestOpen") {
		soundTag = eSoundTag::chestOpen;
	} else if (id == "circleSaw") {
		soundTag = eSoundTag::circleSaw;
	} else if (id == "coin") {
		soundTag = eSoundTag::coin;
	} else if (id == "collidedBaggen") {
		soundTag = eSoundTag::collidedBaggen;
	} else if (id == "collidedFlugan") {
		soundTag = eSoundTag::collidedFlugan;
	} else if (id == "death") {
		soundTag = eSoundTag::death;
	} else if (id == "fluganCharge") {
		soundTag = eSoundTag::fluganCharge;
	} else if (id == "fluganAttack") {
		soundTag = eSoundTag::fluganAttack;
	} else if (id == "fluganHurt0") {
		soundTag = eSoundTag::fluganHurt0;
	} else if (id == "fluganHurt1") {
		soundTag = eSoundTag::fluganHurt1;
	} else if (id == "fluganHurt2") {
		soundTag = eSoundTag::fluganHurt2;
	} else if (id == "flylingAttack") {
		soundTag = eSoundTag::flylingAttack;
	} else if (id == "flylingHurt") {
		soundTag = eSoundTag::flylingHurt;
	} else if (id == "hit") {
		soundTag = eSoundTag::hit;
	} else if (id == "hitGround") {
		soundTag = eSoundTag::hitGround;
	} else if (id == "hitHead") {
		soundTag = eSoundTag::hitHead;
	} else if (id == "hover") {
		soundTag = eSoundTag::hover;
	} else if (id == "jump") {
		soundTag = eSoundTag::jump;
	} else if (id == "jumpHigh") {
		soundTag = eSoundTag::jumpHigh;
	} else if (id == "rainOut") {
		soundTag = eSoundTag::rainOut;
	} else if (id == "swim") {
		soundTag = eSoundTag::swim;
	} else if (id == "splash") {
		soundTag = eSoundTag::splash;
	} else if (id == "stepGrass") {
		soundTag = eSoundTag::stepGrass;
	} else if (id == "swingAttach") {
		soundTag = eSoundTag::swingAttach;
	} else if (id == "swingDetach") {
		soundTag = eSoundTag::swingDetach;
	} else if (id == "toss") {
		soundTag = eSoundTag::toss;
	} else if (id == "turn") {
		soundTag = eSoundTag::turn;
	} else if (id == "wallSlide") {
		soundTag = eSoundTag::wallSlide;
	}
	m_sounds[soundTag] = new sf::Sound;
	m_sounds[soundTag]->setBuffer(*cSoundBufferManager::load(fileName));

	std::cout << "Created sound: " << id << "\n";
}

bool cSoundsManager::isPlaying(eSoundTag soundTag) {
	if (m_sounds.find(soundTag) == m_sounds.end()) {
		std::cout << "soundTag " << (int)soundTag << "not found, cen't check if playing" << "\n";
	} else {
		if (m_sounds[soundTag] != nullptr) {
			if (m_sounds[soundTag]->getStatus() == sf::Sound::Playing) {
				return true;
			} else {
				return false;
			}
		}
	}
	return false;
}

void cSoundsManager::play(eSoundTag soundTag, float x, float y, float z) {
	if (m_sounds.find(soundTag) == m_sounds.end()) {
		std::cout << "soundTag " << (int)soundTag << "not found, can't play sound" << "\n";
	} else {
		if (m_sounds[soundTag] != nullptr) {
			m_sounds[soundTag]->setPosition(x, y, z);
			m_sounds[soundTag]->play();
		}
	}
}

void cSoundsManager::play(eSoundTag soundTag) {
	cSoundsManager::play(soundTag, 0.0f, 0.0f, 0.0f);
}
void cSoundsManager::play(eSoundTag soundTag, float x, float y) {
	cSoundsManager::play(soundTag, x, y, 0.0f);
}
void cSoundsManager::play(eSoundTag soundTag, float x) {
	cSoundsManager::play(soundTag, x, 0.0f, 0.0f);
}

void cSoundsManager::pause(eSoundTag soundTag) {
	if (m_sounds.find(soundTag) == m_sounds.end()) {		
		std::cout << "soundTag " << (int)soundTag << "not found, can't pause sound" << "\n";
	} else {
		if (m_sounds[soundTag] != nullptr) {
			m_sounds[soundTag]->pause();
		}
	}
}

void cSoundsManager::stop(eSoundTag soundTag) {
	if (m_sounds.find(soundTag) == m_sounds.end()) {
		std::cout << "soundTag " << (int)soundTag << "not found, can't stop sound" << "\n";
	} else {
		if (m_sounds[soundTag] != nullptr) {
			m_sounds[soundTag]->stop();
		}
	}
}

sf::Time cSoundsManager::getPlayingOffset(eSoundTag soundTag) {
	if (m_sounds[soundTag] != nullptr) {
		return m_sounds[soundTag]->getPlayingOffset();
	} else {
		return sf::Time();
	}
}

void cSoundsManager::setPlayingOffset(eSoundTag soundTag, sf::Time playingOffset) {
	if (m_sounds[soundTag] != nullptr) {
		m_sounds[soundTag]->setPlayingOffset(playingOffset);
	}
}

sf::SoundSource::Status cSoundsManager::getStatus(eSoundTag soundTag) {
	if (m_sounds[soundTag] != nullptr) {
		return m_sounds[soundTag]->getStatus();
	} else {
		return sf::SoundSource::Status::Stopped;
	}
}

void cSoundsManager::setLoop(eSoundTag soundTag, bool loop) {
	m_sounds[soundTag]->setLoop(loop);
}

void cSoundsManager::setVolume(eSoundTag soundTag, float volume) {
	m_sounds[soundTag]->setVolume(volume);
}


//void cPlayer::loadConfig(std::string fileName)
//{
//	std::ifstream dataFile( fileName.c_str() );
//
//	  // Verify the data file was opened; exit if not.
//	if ( !dataFile ) {
//		std::cout << "Error:  Cannot open file " << fileName << "\n";
//		//exit( 1 );
//	} 
//
//	std::istringstream iStr(std::ios_base::out);
//	char buf[ 80 ] = {0};
//	std::string firstField;
//	std::string secondField;
//	std::string data;
//	std::string data2;
//	std::string data3;
//
//	while (!dataFile.eof() ) {	
//		dataFile.getline( buf, sizeof( buf ) );
//
//		iStr.str(std::string(buf));
//		iStr >> firstField;
//		iStr.clear();
//		iStr.str("");
//
//		if(firstField == "Sounds") {
//			while (dataFile.peek() != '}' ) {
//				dataFile.getline( buf, sizeof( buf ) );
//
//				iStr.str(std::string(buf));
//				iStr >> firstField >> secondField >> data;
//				iStr.clear();
//				iStr.str("");
//
//				if(firstField == "stepGrass")
//					m_soundStepGrass.setBuffer( *cSoundBufferManager::load(data) );
//				else if(firstField == "jump")
//					m_soundJump.setBuffer( *cSoundBufferManager::load(data) );
//				else if(firstField == "swim")
//					m_soundSwim.setBuffer( *cSoundBufferManager::load(data) );
//				else if(firstField == "death")
//					m_soundDeath.setBuffer( *cSoundBufferManager::load(data) );
//				else if(firstField == "attack")
//					m_soundAttack.setBuffer( *cSoundBufferManager::load(data) );
//				else if(firstField == "hit")
//					m_soundHit.setBuffer( *cSoundBufferManager::load(data) );
//				else if(firstField == "block")
//					m_soundBlock.setBuffer( *cSoundBufferManager::load(data) );
//				else if(firstField == "collidedBaggen")
//					m_soundCollidedBaggen.setBuffer( *cSoundBufferManager::load(data) );
//				else if(firstField == "collidedFlugan")
//					m_soundCollidedFlugan.setBuffer( *cSoundBufferManager::load(data) );
//				else if(firstField == "wallSlide")
//					m_soundWallSlide.setBuffer( *cSoundBufferManager::load(data) );
//				else if(firstField == "swingAttach")
//					m_soundSwingAttach.setBuffer( *cSoundBufferManager::load(data) );
//				else if(firstField == "swingDetach")
//					m_soundSwingDetach.setBuffer( *cSoundBufferManager::load(data) );
//				else if(firstField == "hover")
//					m_soundHover.setBuffer( *cSoundBufferManager::load(data) );
//			}
//		}		
//	} 
//
//	dataFile.close();
//}