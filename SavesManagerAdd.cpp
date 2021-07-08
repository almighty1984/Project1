#include "SavesManager.h"

void cSavesManager::addMap(std::string mapPath) {
	if (mapPath.empty()) {
		return;
	}

	m_currentLevel = mapPath;
	for (unsigned short i = 0; i < m_visitedMaps.size(); ++i) {
		if (m_visitedMaps.at(i).compare(mapPath) == 0) {
			return;
			break;
		}
	}
	m_visitedMaps.push_back(mapPath);
	std::sort(m_visitedMaps.begin(), m_visitedMaps.end());
}

void cSavesManager::addCoin(std::string mapPath, unsigned short coinNumber) {
	if (mapPath.empty()) {
		return;
	}
	for (unsigned short i = 0; i < m_pickedCoins[mapPath].size(); ++i) {
		if (m_pickedCoins[mapPath].at(i) == coinNumber) {
			//std::cout << mapPath << " Coin " << coinNumber << " already added\n";
			return;
		}
	}
	m_pickedCoins[mapPath].push_back(coinNumber);
	std::sort(m_pickedCoins[mapPath].begin(), m_pickedCoins[mapPath].end());

	//std::cout << m_pickedCoins[mapPath].at( m_pickedCoins[mapPath].size()-1 ) << "\n";

	++m_numCoins;
	//std::cout << "number of coins: " << m_numCoins << "\n";
}


void cSavesManager::addTargetObject(std::string mapPath, unsigned char targetObjectNumber) {
	if (mapPath.empty()) {
		return;
	}
	for (auto it = m_targetObjects[mapPath].begin(); it != m_targetObjects[mapPath].end(); ++it) {
		if (*it == targetObjectNumber) {
			return;
		}
	}
	m_targetObjects[mapPath].push_back(targetObjectNumber);
	std::sort(m_targetObjects[mapPath].begin(), m_targetObjects[mapPath].end());
}
void cSavesManager::removeTargetObject(std::string mapPath, unsigned char targetObjectNumber) {
	for (unsigned short i = 0; i < m_targetObjects[mapPath].size(); ++i) {
		if (m_targetObjects[mapPath].at(i) == targetObjectNumber) {
			//m_particles.erase(m_particles.begin() + i, m_particles.begin() + i + 1);
			m_targetObjects[mapPath].erase(m_targetObjects[mapPath].begin() + i, m_targetObjects[mapPath].begin() + i + 1);
			return;
		}
	}
}

bool cSavesManager::hasTargetedObject(std::string mapPath, unsigned char targetObjectNumber) {
	for (unsigned short i = 0; i < m_targetObjects[mapPath].size(); ++i) {
		if (m_targetObjects[mapPath].at(i) == targetObjectNumber) {
			//std::cout << mapPath << " Target " << targetObjectNumber << " already triggered\n";
			return true;
		}
	}
	return false;
}
bool cSavesManager::hasAddedCoin(std::string mapPath, unsigned short coinNumber) {
	for (unsigned short i = 0; i < m_pickedCoins[mapPath].size(); ++i) {
		if (m_pickedCoins[mapPath].at(i) == coinNumber) {
			//std::cout << mapPath << " Coin " << coinNumber << " already added\n";
			return true;
		}
	}
	return false;
}

//void cSavesManager::addSand(std::string mapPath, unsigned short sandNumber) {
//	if (mapPath.empty()) {
//		return;
//	}
//	for (auto it = m_dugSands[mapPath].begin(); it != m_dugSands[mapPath].end(); ++it) {
//		if (*it == sandNumber) {
//			return;
//			break;
//		}
//	}
//	m_dugSands[mapPath].push_back(sandNumber);
//	std::sort(m_dugSands[mapPath].begin(), m_dugSands[mapPath].end());
//}
//
//bool cSavesManager::hasAddedSand(std::string mapPath, unsigned short sandNumber) {
//	for (auto it = m_dugSands[mapPath].begin(); it != m_dugSands[mapPath].end(); ++it) {
//		if (*it == sandNumber) {
//			return true;
//			break;
//		}
//	}
//	return false;
//}

void cSavesManager::addPot(std::string mapPath, unsigned char potNumber) {
	if (mapPath.empty()) {
		return;
	}
	for (auto it = m_brokenPots[mapPath].begin(); it != m_brokenPots[mapPath].end(); ++it) {
		if (*it == potNumber) {
			return;
			break;
		}
	}
	m_brokenPots[mapPath].push_back(potNumber);
	std::sort(m_brokenPots[mapPath].begin(), m_brokenPots[mapPath].end());
}

bool cSavesManager::hasAddedPot(std::string mapPath, unsigned char potNumber) {
	for (auto it = m_brokenPots[mapPath].begin(); it != m_brokenPots[mapPath].end(); ++it) {
		if (*it == potNumber) {
			return true;
			break;
		}
	}
	return false;
}

void cSavesManager::addKilledFlugan(std::string mapPath, unsigned char entityNumber) {
	if (mapPath.empty()) {
		return;
	}
	for (auto it = m_killedFlugans[mapPath].begin(); it != m_killedFlugans[mapPath].end(); ++it) {
		if (*it == entityNumber) {
			return;
			break;
		}
	}
	m_killedFlugans[mapPath].push_back(entityNumber);
	std::sort(m_killedFlugans[mapPath].begin(), m_killedFlugans[mapPath].end());
}

bool cSavesManager::hasKilledFlugan(std::string mapPath, unsigned char entityNumber) {
	for (auto it = m_killedFlugans[mapPath].begin(); it != m_killedFlugans[mapPath].end(); ++it) {
		if (*it == entityNumber) {
			return true;
			break;
		}
	}
	return false;
}

void cSavesManager::addKilledGrodorr(std::string mapPath, unsigned char entityNumber) {
	if (mapPath.empty()) {
		return;
	}
	for (auto it = m_killedGrodorrs[mapPath].begin(); it != m_killedGrodorrs[mapPath].end(); ++it) {
		if (*it == entityNumber) {
			return;
			break;
		}
	}
	m_killedGrodorrs[mapPath].push_back(entityNumber);
	std::sort(m_killedGrodorrs[mapPath].begin(), m_killedGrodorrs[mapPath].end());
}

bool cSavesManager::hasKilledGrodorr(std::string mapPath, unsigned char entityNumber) {
	for (auto it = m_killedGrodorrs[mapPath].begin(); it != m_killedGrodorrs[mapPath].end(); ++it) {
		if (*it == entityNumber) {
			return true;
			break;
		}
	}
	return false;
}
