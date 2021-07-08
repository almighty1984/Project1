#include "MapsManager.h"
#include "SavesManager.h"
#include "RenderingManager.h"

int cMapsManager::m_x = 0;
int cMapsManager::m_y = 0;
int cMapsManager::m_mapOffsetX = 0;
int cMapsManager::m_mapOffsetY = 0;
bool cMapsManager::m_isHidden = true;
cObject cMapsManager::m_mapPlayerObject;
std::vector<cMap*> cMapsManager::m_maps;
std::vector<std::string> cMapsManager::m_levelList;

cMapsManager::~cMapsManager() {
	//m_maps.clear();
}

void cMapsManager::clearMaps() {
	m_maps.clear();
}
cMapsManager::cMapsManager() {
	
	//m_imagePaths.clear();
	//m_imageWidths.clear();
	//m_imageHeights.clear();				
	//m_positionsX.clear();
	//m_positionsY.clear();

	
}

void cMapsManager::addMap(cMap* map) {
	m_maps.push_back(new cMap);
}

cMap *cMapsManager::getMapLast() {
	if (m_maps.empty()) {
		return nullptr;
	}
	return m_maps.at(m_maps.size() - 1);
}

void cMapsManager::init(cApp *app) {
	if (app == nullptr) {
		return;
	}

	if (!m_maps.empty()) {
		m_maps.clear();
	}

	//m_mapPlayerObject.setImagePath("Data\\Maps\\player.png");
	m_mapPlayerObject.setX(0.0f);
	m_mapPlayerObject.setY(0.0f);
	m_mapPlayerObject.loadConfig("Data\\Objects\\map_player.cfg");
	m_mapPlayerObject.setWidth(8);
	m_mapPlayerObject.setHeight(8);
	m_mapPlayerObject.setIsHidden(true);
	m_mapPlayerObject.setIsAnim(true);

	m_mapOffsetX = -40000 + (int)(app->getWindowWidth() / 2);
	m_mapOffsetY = -40000 + (int)(app->getWindowHeight() / 2);
	std::cout << "cMapsManager init" << "\n";
	unsigned short i = 0;

	m_levelList = *cSavesManager::getVisitedMaps();
	
	/*if (m_levelList.empty()) {
		return;
	}*/
	std::cout << "m_levelList.size() == " << m_levelList.size() << "\n";

	if (m_levelList.empty()) {
		m_levelList.push_back(app->getPathLevel());
	}
	//m_levelList.at(0) == app->getPathLevel();
	if (m_levelList.at(i).size() == 25) {
		while (i < m_levelList.size()) {
		
			//std::cout << "m_levelList.at(" << i << ") = " << m_levelList.at(i) << " " << m_levelList.at(i).substr(12, 13) << " " << m_levelList.at(i).size() << "\n";
			addMap(new cMap);
			
			// Should not be needed sinze size is stored but crashes without it
			getMapLast()->setSize(getMapLast()->getMapSizeFromLevel(m_levelList.at(i)));
			getMapLast()->load("Data\\Maps\\" + m_levelList.at(i).substr(12, 13));
			//
			//// Make level name position of map
			//if (m_levelList.at(i).substr(0, 12) == "Data\\Levels\\"/* && m_levelList.at(i).size() == 25*/) {
			//	float posX = (float)(atof(m_levelList.at(i).substr(12, 4).c_str())) * 8.0f - 40000 + m_mapOffsetX;
			//	float posY = (float)(atof(m_levelList.at(i).substr(17, 4).c_str())) * 8.0f - 40000 + m_mapOffsetY;
			//	
			//	std::cout << posX << " " << posY << "\n";

			//	m_maps.at(m_maps.size() - 1)->setX(posX);
			//	m_maps.at(m_maps.size() - 1)->setY(posY);
			//}

			if (m_levelList.at(i) == app->getPathLevel()) {
				m_mapOffsetX = -getMapLast()->getStartX() + (int)(app->getWindowWidth() / 2);
				m_mapOffsetY = -getMapLast()->getStartY() + (int)(app->getWindowHeight() / 2);
			}

			++i;
		}
	}

	cRenderingManager::addObject(&m_mapPlayerObject);
	std::cout << "cMapsManager init end" << "\n";
}

void cMapsManager::update(cApp *app, cLevel *level, float time) {
	if (app == nullptr || level == nullptr) {
		return;
	}
	for (auto it = m_maps.begin(); it != m_maps.end(); ++it) {
		(*it)->setX((*it)->getStartX() + m_x + (float)m_mapOffsetX);
		(*it)->setY((*it)->getStartY() + m_y + (float)m_mapOffsetY);
		(*it)->update(time);
	}
	//std::cout << (level->getX()/320)*8 << " " << (level->getY()/240)*8 << "\n";
	m_mapPlayerObject.setX((float)(m_x + (level->getX() / 320) * 8 + app->getWindowWidth() / 2));
	m_mapPlayerObject.setY((float)(m_y + (level->getY() / 240) * 8 + app->getWindowHeight() / 2));
	m_mapPlayerObject.update(time);
}

void cMapsManager::setIsHidden(bool isHidden) {
	if (isHidden == m_isHidden) {
		return;
	}
	m_isHidden = isHidden;
	m_mapPlayerObject.setIsHidden(isHidden);
	for (auto it = m_maps.begin(); it != m_maps.end(); ++it) {
		(*it)->setIsHidden(isHidden);
	}
	
}

void cMapsManager::setColor(unsigned char r, unsigned char g, unsigned char b) {
	for (auto it = m_maps.begin(); it != m_maps.end(); ++it) {
		(*it)->setColor(r, g, b);
	}
	m_mapPlayerObject.setColor((unsigned char)r, (unsigned char)g, (unsigned char)b);
	
}

//void cMapsManager::setX(int x) {
//	for (auto it = m_levelList.begin(); it != m_levelList.end(); ++it) {
//		float posX = (float)(atof((*it).substr(12, 4).c_str())) * 8.0f - 40000 + m_mapOffsetX;
//
//		m_mapObjects.at(i)->setX(m_mapObjects.at(i)->getX() + m_x);
//		m_mapObjects.at(i)->setY(m_mapObjects.at(i)->getY() + m_y);
//	}
//}


//
//void cMapsManager::scrollX(int x) {
//	for (unsigned short i = 0; i < m_mapObjects.size(); ++i)
//		m_mapObjects.at(i)->setX(m_mapObjects.at(i)->getX() + 16);
//
//	m_mapPlayerObject.setX(m_mapPlayerObject.getX() + 16);
//}