#pragma once

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>

#include <string>
#include <fstream>

struct sPlayerStatus {
	char name[8];
	char mapPath[26];	
	bool hasHover;
	bool hasSprint;
	bool hasWhirl;
	float strength;
	float vitality;
	float stamina;
	unsigned short numLevels;
};

class cSavesManager {	
public:	
	static void clearCoins();
	static void clearTargetObjects();
	static void clearKilled();
	static void clearPlayerStatus();
	static void clearAll();
	//void loadConfig(std::string fileName);
	static void setSlotNumber(unsigned char slotNumber);	
	static unsigned char getSlotNumber();
	static void addMap(std::string mapPath);
	static void addCoin(std::string mapPath, unsigned short coinNumber);
	static bool hasAddedCoin(std::string mapPath, unsigned short coinNumber);

	/*void addSand(std::string mapPath, unsigned short sandNumber);
	bool hasAddedSand(std::string mapPath, unsigned short sandNumber);*/

	static void addPot(std::string mapPath, unsigned char potNumber);
	static bool hasAddedPot(std::string mapPath, unsigned char potNumber);

	static void addTargetObject(std::string mapPath, unsigned char targetObjectNumber);
	static void removeTargetObject(std::string mapPath, unsigned char targetObjectNumber);
	static bool hasTargetedObject(std::string mapPath, unsigned char targetObjectNumber);

	static void addKilledFlugan(std::string mapPath, unsigned char entityNumber);
	static bool hasKilledFlugan(std::string mapPath, unsigned char entityNumber);

	static void addKilledGrodorr(std::string mapPath, unsigned char entityNumber);
	static bool hasKilledGrodorr(std::string mapPath, unsigned char entityNumber);	
	
	static void initSave();
	static bool readSave(std::string fileName);
	static void writeSave(bool hasHover, bool hasSprint, bool hasWhirl);
	
	static void setPathSave(std::string pathSave);
	static std::string getPathLevel();
	static std::string getPathSave();

	static bool getHasHover();
	static bool getHasSprint();
	static bool getHasWhirl();

	static unsigned short getNumCoins();				static void setNumCoins(unsigned short numCoins);
	
	static void setPlayerStart(std::string playerStart);
	static std::string getPlayerStart();
	static unsigned char getVitalityMeterValue();		static void setVitalityMeterValue(unsigned char vitalityMeterValue);	
	static unsigned char getStaminaMeterValue();		static void setStaminaMeterValue(unsigned char staminaMeterValue);	

	static void setHasHover(bool hasHover);
	static void setHasSprint(bool hasSprint);
	static void setHasWhirl(bool hasWhirl);

	static std::string getStrPlayerState();	
	static std::string getCurrentLevel();				static void setCurrentLevel(std::string const currentLevel);		
	static float getPlayerStrength();					static void setPlayerStrength(float playerStrength);
	static float getPlayerVitality();					static void setPlayerVitality(float playerVitality);
	static float getPlayerStamina();					static void setPlayerStamina(float playerStamina);
	static std::string getPlayerName();					static void setPlayerName(std::string name);	

	static std::vector<std::string>* getVisitedMaps();
	
private:
	//cSavesManager();
	static unsigned char m_slotNumber;
	/*char** m_levelDataCoins;
	char** m_levelDataPath;*/	
	static std::string m_currentLevel;

	static std::string m_playerName;
	static std::string m_pathLevel;
	static std::string m_pathSave;
	static std::string m_strPlayerState;
	/*std::string m_strHasHover;
	std::string m_strHasSprint;
	std::string m_strHasWhirl;*/
	static std::ofstream m_outputFile;
	
	static unsigned short m_numCoins;
	static std::string m_playerStart;
	static float m_playerStrength, m_playerVitality, m_playerStamina;

	static bool m_hasHover, m_hasSprint, m_hasWhirl;

	static unsigned short m_numLevels;
	//sLevelData* m_levelData;
	static unsigned char m_numPickedCoinsLevel, m_numTargetedObjectsLevel;
	static unsigned char m_numKilledFlugansLevel, m_numKilledGrodorrsLevel;

	static unsigned char m_vitalityMeterValue, m_staminaMeterValue;


	static std::vector<std::string> m_visitedMaps;
	// Level, object number
	static std::map<std::string, std::vector<unsigned short>> m_pickedCoins;
	//std::map<std::string, std::vector<unsigned short>> m_dugSands;
	static std::map<std::string, std::vector<unsigned char>> m_brokenPots;
	static std::map<std::string, std::vector<unsigned char>> m_targetObjects;
	static std::map<std::string, std::vector<unsigned char>> m_killedFlugans;
	static std::map<std::string, std::vector<unsigned char>> m_killedGrodorrs;

};

