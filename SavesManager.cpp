#include "SavesManager.h"
#include <sstream>

unsigned char	cSavesManager::m_slotNumber					= 0;
std::string		cSavesManager::m_currentLevel				= "";
std::string		cSavesManager::m_playerName					= "";
std::string		cSavesManager::m_pathLevel					= "";
std::string		cSavesManager::m_pathSave					= "";
std::string		cSavesManager::m_strPlayerState				= "";
unsigned short	cSavesManager::m_numCoins					= 0;
std::string		cSavesManager::m_playerStart				= "center";
float			cSavesManager::m_playerStrength				 = 1.0f;
float			cSavesManager::m_playerVitality				= 1.0f;
float			cSavesManager::m_playerStamina				= 1.0f;
bool			cSavesManager::m_hasHover					= false;
bool			cSavesManager::m_hasSprint					= false;
bool			cSavesManager::m_hasWhirl					= false;
unsigned short	cSavesManager::m_numLevels					= 0;
unsigned char	cSavesManager::m_numPickedCoinsLevel		= 0;
unsigned char	cSavesManager::m_numTargetedObjectsLevel	= 0;
unsigned char	cSavesManager::m_numKilledFlugansLevel		= 0;
unsigned char	cSavesManager::m_numKilledGrodorrsLevel		= 0;
unsigned char	cSavesManager::m_vitalityMeterValue			= 64;
unsigned char	cSavesManager::m_staminaMeterValue			= 64;
std::vector<std::string>	cSavesManager::m_visitedMaps;
std::map<std::string, std::vector<unsigned short>>	cSavesManager::m_pickedCoins;
std::map<std::string, std::vector<unsigned char>>	cSavesManager::m_brokenPots;
std::map<std::string, std::vector<unsigned char>>	cSavesManager::m_targetObjects;
std::map<std::string, std::vector<unsigned char>>	cSavesManager::m_killedFlugans;
std::map<std::string, std::vector<unsigned char>>	cSavesManager::m_killedGrodorrs;

std::ofstream	cSavesManager::m_outputFile;

void cSavesManager::setSlotNumber(unsigned char slotNumber) {
	m_slotNumber = slotNumber;
}
unsigned char cSavesManager::getSlotNumber() {
	return m_slotNumber;
}
unsigned short cSavesManager::getNumCoins() {
	return m_numCoins;
}
void cSavesManager::setNumCoins(unsigned short numCoins) {
	m_numCoins = numCoins;
}
void cSavesManager::setPathSave(std::string pathSave) {
	m_pathSave = pathSave;
}
std::string cSavesManager::getPathLevel() {
	return m_pathLevel;
}
std::string cSavesManager::getPathSave() {
	return m_pathSave;
}
void cSavesManager::setPlayerStart(std::string playerStart) {
	m_playerStart = playerStart;
}
std::string cSavesManager::getPlayerStart() {
	return m_playerStart;
}
void cSavesManager::setVitalityMeterValue(unsigned char vitalityMeterValue) {
	m_vitalityMeterValue = vitalityMeterValue;
}
unsigned char cSavesManager::getVitalityMeterValue() {
	return m_vitalityMeterValue;
}
void cSavesManager::setStaminaMeterValue(unsigned char staminaMeterValue) {
	m_staminaMeterValue = staminaMeterValue;
}
unsigned char cSavesManager::getStaminaMeterValue() {
	return m_staminaMeterValue;
}

std::string cSavesManager::getStrPlayerState() {
	return m_strPlayerState;
}
void cSavesManager::setCurrentLevel(std::string const currentLevel) {
	m_currentLevel = currentLevel;
}
std::string cSavesManager::getCurrentLevel() {
	return m_currentLevel;
}
void cSavesManager::setPlayerStrength(float playerStrength) {
	m_playerStrength = playerStrength;
}
float cSavesManager::getPlayerStrength() {
	return m_playerStrength;
}
void cSavesManager::setPlayerStamina(float playerStamina) {
	m_playerStamina = playerStamina;
}
float cSavesManager::getPlayerStamina() {
	return m_playerStamina;
}
void cSavesManager::setPlayerVitality(float playerVitality) {
	m_playerVitality = playerVitality;
}
float cSavesManager::getPlayerVitality() {
	return m_playerVitality;
}
void cSavesManager::setPlayerName(std::string name) {
	m_playerName = name;
}
std::string cSavesManager::getPlayerName() {
	return m_playerName;
}
std::vector<std::string>* cSavesManager::getVisitedMaps() {
	return &m_visitedMaps;
}

void cSavesManager::clearCoins() {
	m_pickedCoins.clear();
	m_numCoins = 0;
	m_numPickedCoinsLevel = 0;
}
void cSavesManager::clearTargetObjects() {
	m_targetObjects.clear();
	m_numTargetedObjectsLevel = 0;
}

void cSavesManager::clearKilled() {
	m_killedFlugans.clear();
	m_numKilledFlugansLevel = 0;

	m_killedGrodorrs.clear();
	m_numKilledGrodorrsLevel = 0;
}

void cSavesManager::clearPlayerStatus() {
	m_hasHover = false;
	m_hasSprint = false;
	m_hasWhirl = false;
}
void cSavesManager::clearAll() {
	m_slotNumber = 0;
	m_numCoins = 0;
	m_playerStrength = 1.0f;
	m_playerVitality = 1.0f;
	m_playerStamina = 1.0f;
	m_hasHover = false;
	m_hasSprint = false;
	m_hasWhirl = false;
	m_strPlayerState.clear();
	m_pathSave = "Data\\Saves\\0.bin";
	m_pathLevel = "Data\\Levels\\5000_5000.bin";
	m_currentLevel = "Data\\Levels\\5000_5000.bin";
	m_playerStart = "center";
	
	m_playerName.clear();
	/*m_strHasHover.clear();
	m_strHasSprint.clear();
	m_strHasWhirl.clear();*/
	m_currentLevel.clear();
	m_pathSave.clear();
	m_pathLevel.clear();
	m_playerStart.clear();

	m_visitedMaps.clear();
	m_pickedCoins.clear();
	m_targetObjects.clear();
	//m_dugSands.clear();
	m_brokenPots.clear();
	m_killedFlugans.clear();
	m_killedGrodorrs.clear();

	m_numKilledFlugansLevel = 0;
	m_numKilledGrodorrsLevel = 0;

	/*for (int i = 0; i < m_numLevels; ++i) {
		for (int j = 0; j < 26; ++j) {
			m_levelData[i].path[j] = 0;
		}
		for (int j = 0; j < 64; ++j) {
			m_levelData[i].coins[j] = 0;
		}
	}*/
}

bool cSavesManager::readSave(std::string fileName) {
	std::cout << "cSavesManager::readSave()\n";
	
	std::ifstream file;
	file.open(fileName.c_str(), std::ios::in | std::ios::binary);
	
	if (file.is_open()) {
		sPlayerStatus playerStatus;
		file.read((char*)&playerStatus, sizeof(sPlayerStatus));
		m_playerName = playerStatus.name;
		m_pathLevel = playerStatus.mapPath;		
		m_hasHover = playerStatus.hasHover;
		m_hasSprint = playerStatus.hasSprint;
		m_hasWhirl = playerStatus.hasWhirl;
		m_playerStrength = playerStatus.strength;
		m_playerVitality = playerStatus.vitality;
		m_playerStamina = playerStatus.stamina;
		m_numLevels = playerStatus.numLevels;

		for (unsigned short i = 0; i < m_numLevels; ++i) {
			char mapPath[26];
			for (char j = 0; j < 26; ++j) {
				mapPath[j] = 0;
			}
			file.read((char*)mapPath, sizeof(char) * 26);
			//std::cout << "Read mapPath " << i << mapPath << "\n";
			cSavesManager::addMap(mapPath);
			//std::cout << "Added map " << i << mapPath << "\n";
			m_numPickedCoinsLevel = 0;
			file.read((char*)&m_numPickedCoinsLevel, sizeof(unsigned char));
			//std::cout << "Read m_numPickedCoinsLevel " << i << m_numPickedCoinsLevel << "\n";
			char pickedCoin = 0;
			for (unsigned short j = 0; j < m_numPickedCoinsLevel; ++j) {
				file.read((char*)& pickedCoin, sizeof(unsigned char));
				//std::cout << "Read coin " << j << mapPath << "\n";
				cSavesManager::addCoin(mapPath, (int)pickedCoin);
				//std::cout << "Added coin " << j << mapPath << "\n";
			}

			m_numTargetedObjectsLevel = 0;
			file.read((char*)&m_numTargetedObjectsLevel, sizeof(unsigned char));
			//std::cout << "Read m_numPickedCoinsLevel " << i << m_numPickedCoinsLevel << "\n";
			char targetObject = 0;
			for (unsigned short j = 0; j < m_numTargetedObjectsLevel; ++j) {
				file.read((char*)& targetObject, sizeof(unsigned char));
				//std::cout << "Read coin " << j << mapPath << "\n";
				cSavesManager::addTargetObject(mapPath, targetObject);
				//std::cout << "Added coin " << j << mapPath << "\n";
			}

			char entityNumber = 0;
			m_numKilledFlugansLevel = 0;
			file.read((char*)&m_numKilledFlugansLevel, sizeof(unsigned char));
			//std::cout << "Read m_numPickedCoinsLevel " << i << m_numPickedCoinsLevel << "\n";
			
			for (unsigned short j = 0; j < m_numKilledFlugansLevel; ++j) {
				file.read((char*)&entityNumber, sizeof(unsigned char));
				//std::cout << "Read coin " << j << mapPath << "\n";
				cSavesManager::addKilledFlugan(mapPath, entityNumber);
				//std::cout << "Added coin " << j << mapPath << "\n";
			}

			entityNumber = 0;
			m_numKilledGrodorrsLevel = 0;
			file.read((char*)&m_numKilledGrodorrsLevel, sizeof(unsigned char));			
			for (unsigned short j = 0; j < m_numKilledGrodorrsLevel; ++j) {
				file.read((char*)&entityNumber, sizeof(unsigned char));
				cSavesManager::addKilledGrodorr(mapPath, entityNumber);
			}

		}
		file.close();
		return true;
	}
	else {
		return false;
	}
}

void cSavesManager::writeSave(bool hasHover, bool hasSprint, bool hasWhirl) {
	sPlayerStatus playerStatus;
	for (unsigned char i = 0; i < 8; ++i) {
		playerStatus.name[i] = 0;
	}
	snprintf(playerStatus.name, sizeof(char) * 8, "%s", m_playerName.c_str());

	for (unsigned char i = 0; i < 26; ++i) {
		playerStatus.mapPath[i] = 0;
	}
	snprintf(playerStatus.mapPath, sizeof(char) * 26, "%s", m_currentLevel.c_str());
	playerStatus.hasHover = hasHover;
	playerStatus.hasSprint = hasSprint;
	playerStatus.hasWhirl = hasWhirl;
	playerStatus.strength = m_playerStrength;
	playerStatus.vitality = m_playerVitality;
	playerStatus.stamina = m_playerStamina;
	playerStatus.numLevels = (unsigned short)m_visitedMaps.size();

	m_numLevels = playerStatus.numLevels;

	//std::cout << "m_numLevels = " << m_numLevels << "\n";
	std::stringstream strStream;

	strStream.clear();
	strStream.str("");
	strStream << (int)m_slotNumber;
	std::ofstream strOutput("Data\\Saves\\" + strStream.str() + ".bin", std::ios::out | std::ios::binary);

	strOutput.write((char*)&playerStatus, sizeof(sPlayerStatus));	

	for (unsigned short i = 0; i < m_numLevels; ++i) {
		char mapPath[26];
		for (int k = 0; k < 26; ++k) {
			mapPath[k] = 0;
		}
		snprintf(mapPath, sizeof(char) * 26, "%s", m_visitedMaps.at(i).c_str());
		strOutput.write((char*)mapPath, sizeof(char) * 26);

		// Write picked coins
		m_numPickedCoinsLevel = (unsigned char)m_pickedCoins[m_visitedMaps.at(i)].size();
		strOutput.write((char*)& m_numPickedCoinsLevel, sizeof(unsigned char));
		char* coinArray = new char[m_numPickedCoinsLevel];
		char pickedCoin = 0;
		for (unsigned char j = 0; j < m_numPickedCoinsLevel; ++j) {
			pickedCoin = (int)m_pickedCoins[m_visitedMaps.at(i)].at(j);
			std::cout << (int)pickedCoin << ",";
			coinArray[j] = pickedCoin;
		}
		std::cout << "Writing level " << i << " coins...";
		strOutput.write((char*)coinArray, sizeof(char) * (m_numPickedCoinsLevel));
		std::cout << "done." << "\n";
		delete[] coinArray;
		coinArray = nullptr;


		// Write triggered targets
		m_numTargetedObjectsLevel = (unsigned char)m_targetObjects[m_visitedMaps.at(i)].size();
		strOutput.write((char*)&m_numTargetedObjectsLevel, sizeof(unsigned char));

		char* targetObjectsArray = new char[m_numTargetedObjectsLevel];
		char targetObject = 0;
		for (unsigned char j = 0; j < m_numTargetedObjectsLevel; ++j) {
			targetObject = m_targetObjects[m_visitedMaps.at(i)].at(j);
			std::cout << (int)targetObject << ",";
			targetObjectsArray[j] = targetObject;
		}
		std::cout << "Writing level " << i << " target objects...";
		strOutput.write((char*)targetObjectsArray, sizeof(char) * (m_numTargetedObjectsLevel));
		std::cout << "done." << "\n";
		delete[] targetObjectsArray;
		targetObjectsArray = nullptr;


		char entityNumber = 0;
		char* entityArray;

		// Write killed EntityFlugans
		m_numKilledFlugansLevel = (unsigned char)m_killedFlugans[m_visitedMaps.at(i)].size();
		strOutput.write((char*)&m_numKilledFlugansLevel, sizeof(unsigned char));

		entityArray = new char[m_numKilledFlugansLevel];
		
		for (unsigned short j = 0; j < m_numKilledFlugansLevel; ++j) {
			entityNumber = m_killedFlugans[m_visitedMaps.at(i)].at(j);
			std::cout << (int)entityNumber << ",";
			entityArray[j] = entityNumber;
		}
		std::cout << "Writing level " << i << " killed Flugans...";
		strOutput.write((char*)entityArray, sizeof(char) * (m_numKilledFlugansLevel));
		std::cout << "done." << "\n";
		delete[] entityArray;
		entityArray = nullptr;


		// Write killed EntityGrodorrs
		m_numKilledGrodorrsLevel = (unsigned char)m_killedGrodorrs[m_visitedMaps.at(i)].size();
		strOutput.write((char*)&m_numKilledGrodorrsLevel, sizeof(unsigned char));

		entityArray = new char[m_numKilledGrodorrsLevel];
		entityNumber = 0;
		for (unsigned char j = 0; j < m_numKilledGrodorrsLevel; ++j) {
			entityNumber = m_killedGrodorrs[m_visitedMaps.at(i)].at(j);
			std::cout << (int)entityNumber << ",";
			entityArray[j] = entityNumber;
		}
		std::cout << "Writing level " << i << " killed Grodorrs...";
		strOutput.write((char*)entityArray, sizeof(char) * (m_numKilledGrodorrsLevel));
		std::cout << "done." << "\n";
		delete[] entityArray;
		entityArray = nullptr;




	}
	strOutput.close();
}

void cSavesManager::initSave() {
	std::cout << "cSavesManager::initSave()\n";
	m_currentLevel = "Data\\Levels\\5000_5000.bin";
	//m_numCoins = 0;
	m_playerStrength = 1.0f;
	m_playerVitality = 1.0f;
	m_playerStamina = 1.0f;
	m_numLevels = 1;	
	m_numPickedCoinsLevel = 0;
	m_numTargetedObjectsLevel = 0;
	m_numKilledFlugansLevel = 0;
	m_hasHover = false;
	m_hasSprint = false;
	m_hasWhirl = false;
	m_playerName.clear();
	m_pathLevel = "Data\\Levels\\5000_5000.bin";
	/*m_strHasHover = "false";
	m_strHasSprint = "false";
	m_strHasWhirl = "false";*/
	//clearAll();
}

bool cSavesManager::getHasHover() {
	return m_hasHover;
	/*if (m_binaryPlayerStatus & m_bitHasHover) {
		return true;
	} else {
		return false;
	}*/
}

bool cSavesManager::getHasSprint() {
	return m_hasSprint;
	/*if (m_binaryPlayerStatus & m_bitHasSprint) {
		return true;
	} else {
		return false;
	}*/
}

bool cSavesManager::getHasWhirl() {
	return m_hasWhirl;
	/*if (m_binaryPlayerStatus & m_bitHasWhirl) {
		return true;
	} else {
		return false;
	}*/
}

void cSavesManager::setHasHover(bool hasHover) {
	m_hasHover = hasHover;
	/*if (hasHover == true) {
		m_strHasHover = "true";
	} else {
		m_strHasHover = "false";
	}*/
}

void cSavesManager::setHasSprint(bool hasSprint) {
	m_hasSprint = hasSprint;
	/*if (hasSprint == true) {
		m_strHasSprint = "true";
	} else {
		m_strHasSprint = "false";
	}*/
}

void cSavesManager::setHasWhirl(bool hasWhirl) {
	m_hasWhirl = hasWhirl;
	/*if (hasWhirl == true) {
		m_strHasWhirl = "true";
	} else {
		m_strHasWhirl = "false";
	}*/
}