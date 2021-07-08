#include "Level.h"
#include "RenderingManager.h"
#include "SavesManager.h"
#include <sstream>

cLevel::cLevel() :	m_secondCall(false),
					m_isLockedEntities(false),
					m_path(""),
					m_attachedApp(nullptr),
					m_attachedPlayer(nullptr),
					m_startObject(nullptr),
					m_r(255), m_g(255), m_b(255),
					m_numColumns(0), m_numRows(0), m_numLayers(0), 
					m_numBackgroundPlanes(0), m_numForegroundPlanes(0),
					m_x(0.0f), m_y(0.0f),
					m_orthoWidth(0.0f), m_orthoHeight(0.0f),
					m_playerHasSprint(false), m_playerHasHover(false), m_playerHasWhirl(false),
					m_shopItemCurrent(0),
					m_tiles(nullptr),
					m_tilesetNumbers(nullptr),
					m_tilesetTypes(nullptr), m_tilesetTypesEntities(nullptr),
					m_tileObjects(nullptr),
					m_backgroundPlanes(nullptr), m_foregroundPlanes(nullptr) {
	m_path.clear();
	m_particles.clear();
	m_doShowShopBox = false;
}

cLevel::~cLevel() {
	std::cout << "~cLevel() start" << "\n";
	
	deleteTiles();
	deleteTileObjects();
	deleteTileset();
	
	deleteBackground();
	deleteForeground();

	std::cout << "Erase particles...";
	for (unsigned short i = 0; i < m_particles.size(); ++i) {
		m_particles.erase(m_particles.begin() + i, m_particles.begin() + i + 1);
	}
	m_particles.clear();
	std::cout << "done\n";
	std::cout << "Erase entities...";	
	for (unsigned short i = 0; i < m_entities.size(); ++i) {
		m_entities.erase(m_entities.begin() + i, m_entities.begin() + i + 1);
	}
	m_entities.clear();
	std::cout << "done.\n";

	m_updateEveryFrameList.clear();	
	m_pathObjectsList.clear();

	m_pathShop.clear();
	
	for (int i = 0; i < 3; ++i) {
		m_costItem[i] = 0;
		m_typeItem[i].clear();
		m_fontCost[i].clearText();
	}
	std::cout << "~cLevel() end\n";
}

cObject* cLevel::getTileObject(unsigned char z, unsigned short x, unsigned short y) {
	return &m_tileObjects[z * m_numColumns * m_numRows + y * m_numColumns + x];
}

unsigned short cLevel::getTile(unsigned char z, unsigned short x, unsigned short y) {
	return m_tiles[z * m_numColumns * m_numRows + y * m_numColumns + x];
}

unsigned char cLevel::getTilesetNumber(unsigned char z, unsigned short x, unsigned short y) {
	return m_tilesetNumbers[z * m_numColumns * m_numRows + y * m_numColumns + x];
}

void cLevel::deleteTiles() {
	if (m_tiles == nullptr || m_tilesetNumbers == nullptr) { return; }

	delete[] m_tiles;
	delete[] m_tilesetNumbers;
	m_tiles = nullptr;
	m_tilesetNumbers = nullptr;
}

void cLevel::deleteTileObjects() {
	std::cout << "delete[] m_tileObjects...";
	if (m_tileObjects != nullptr) {
		delete[] m_tileObjects;
		m_tileObjects = nullptr;
	}
	std::cout << "done.\n";
}

void cLevel::deleteTileset() {
	std::cout << "deleting tileset...";
	for (unsigned short i = 0; i < 32 * 32; ++i) {
		if (m_tilesetTypes[i] != nullptr && m_tilesetTypesEntities[i] != nullptr) {
			delete[] m_tilesetTypes[i];
			delete[] m_tilesetTypesEntities[i];
			m_tilesetTypes[i] = nullptr;
			m_tilesetTypesEntities[i] = nullptr;
		}
	}
	if (m_tilesetTypes != nullptr && m_tilesetTypesEntities != nullptr) {
		delete[] m_tilesetTypes;
		delete[] m_tilesetTypesEntities;
		m_tilesetTypes = nullptr;
		m_tilesetTypesEntities = nullptr;
	}
	std::cout << "done.\n";
}

//cObject* cLevel::getTileObject(unsigned char layer, unsigned short tile) {
//	return &m_tileObjects[layer][tile];
//}

void cLevel::deleteBackground() {
	if (m_backgroundPlanes != nullptr) {
		delete[] m_backgroundPlanes;
		m_backgroundPlanes = nullptr;
	}
	m_numBackgroundPlanes = 0;
}
void cLevel::deleteForeground() {
	if (m_foregroundPlanes != nullptr) {
		delete[] m_foregroundPlanes;
		m_foregroundPlanes = nullptr;
	}
	m_numForegroundPlanes = 0;
}

void cLevel::setColor(int r, int g, int b) {
	if (r < 0) r = 0;
	if (r > 255) r = 255;
	if (g < 0) g = 0;
	if (g > 255) g = 255;
	if (b < 0) b = 0;
	if (b > 255) b = 255;
	m_r = r;
	m_g = g;
	m_b = b;

	/*m_fontCost.setColor(m_r, m_g, m_b);
	m_shopBox.setColor(m_r, m_g, m_b);*/

	for (unsigned short i = 0; i < m_numBackgroundPlanes; ++i) {
		if (m_backgroundPlanes != nullptr) {
			m_backgroundPlanes[i].setColor(r, g, b);
		}
	}
	for (unsigned short i = 0; i < m_numForegroundPlanes; ++i) {
		if (m_foregroundPlanes != nullptr) {
			m_foregroundPlanes[i].setColor(r, g, b);
		}
	}
	for (unsigned char z = 0; z < m_numLayers; ++z) {
		for (unsigned short y = 0; y < m_numRows; ++y) {
			for (unsigned short x = 0; x < m_numColumns; ++x) {
				getTileObject(z, x, y)->setColor(r, g, b);
			}
		}
	}
	for (unsigned short i = 0; i < m_particles.size(); ++i) {
		m_particles.at(i)->setColor(r, g, b);
	}
	for (unsigned short i = 0; i < m_entities.size(); ++i) {		
		m_entities.at(i)->setColor(r, g, b);		
		/*for (unsigned short j = 0; j < m_entities.at(i)->m_particles.size(); ++j) {
			m_entities.at(i)->m_particles.at(j)->setColor(r, g , b);
		}*/
	}
}

//void cLevel::setColor3(int r, int g, int b) {
//	if (r < 0) r = 0;
//	if (r > 255) r = 255;
//	if (g < 0) g = 0;
//	if (g > 255) g = 255;
//	if (b < 0) b = 0;
//	if (b > 255) b = 255;
//	m_r = r;
//	m_g = g;
//	m_b = b;
//
//	/*m_fontCost.setColor(m_r, m_g, m_b);
//	m_shopBox.setColor(m_r, m_g, m_b);*/
//
//	for (unsigned short i = 0; i < m_numBackgroundPlanes; ++i) {
//		if (m_backgroundPlanes != nullptr) {
//			m_backgroundPlanes[i].setColor(r, g, b);
//		}
//	}
//	for (unsigned short i = 0; i < m_numForegroundPlanes; ++i) {
//		if (m_foregroundPlanes != nullptr) {
//			m_foregroundPlanes[i].setColor(r, g, b);
//		}
//	}
//	for (unsigned char z = 0; z < m_numLayers; ++z) {
//		for (unsigned short y = 0; y < m_numRows; ++y) {
//			for (unsigned short x = 0; x < m_numColumns; ++x) {
//				getTileObject(z, x, y)->setColor(r, g, b);
//			}
//		}
//	}
//	for (unsigned short i = 0; i < m_particles.size(); ++i) {
//		m_particles.at(i)->setColor(r, g, b);
//	}
//	for (unsigned short i = 0; i < m_entities.size(); ++i) {
//		m_entities.at(i)->setColor(r, g, b);
//		/*for (unsigned short j = 0; j < m_entities.at(i)->m_particles.size(); ++j) {
//			m_entities.at(i)->m_particles.at(j)->setColor(r, g , b);
//		}*/
//	}
//}

void cLevel::setIsLockedEntities(bool isLockedEntities) {
	m_isLockedEntities = isLockedEntities;
	for (auto it = m_entities.begin(); it != m_entities.end(); ++it) {
		(*it)->setIsLocked(isLockedEntities);
	}
}

void cLevel::setX(float positionX) {
	m_x = positionX;
}

void cLevel::setY(float positionY) {
	m_y = positionY;
	//cRenderingManager::m_quadNode.setY(positionY);
}

void cLevel::scrollPlaneX(float scrollX) {
	for (unsigned short i = 0; i < m_numBackgroundPlanes; ++i) {
		if (m_backgroundPlanes != nullptr) {
			m_backgroundPlanes[i].setX(m_backgroundPlanes[i].getX() - scrollX);
		}
	}
	for (unsigned short i = 0; i < m_numForegroundPlanes; ++i) {
		if (m_foregroundPlanes != nullptr) {
			m_foregroundPlanes[i].setX(m_foregroundPlanes[i].getX() - scrollX);
		}
	}
}
void cLevel::scrollPlaneY(float scrollY) {
	for (unsigned short i = 0; i < m_numBackgroundPlanes; ++i) {
		if (m_backgroundPlanes != nullptr) {
			m_backgroundPlanes[i].setX(m_backgroundPlanes[i].getY() - scrollY);
		}
	}
	for (unsigned short i = 0; i < m_numForegroundPlanes; ++i) {
		if (m_foregroundPlanes != nullptr) {
			m_foregroundPlanes[i].setY(m_foregroundPlanes[i].getY() - scrollY);
		}
	}
}

void cLevel::scrollX(float scrollX) {
	m_x += scrollX;

	m_referenceObject.setX( m_referenceObject.getX() - scrollX);
	
	if (m_backgroundPlanes != nullptr) {
		for (unsigned char i = 0; i < m_numBackgroundPlanes; ++i) {		
			m_backgroundPlanes[i].setX(scrollX);
		}
	}
	if (m_foregroundPlanes != nullptr) {
		for (unsigned char i = 0; i < m_numForegroundPlanes; ++i) {		
			m_foregroundPlanes[i].setX(scrollX);
		}
	}

	for (unsigned char z = 0; z < m_numLayers; ++z) {
		for (unsigned short y = 0; y < m_numRows; ++y) {
			for (unsigned short x = 0; x < m_numColumns; ++x) {
				if (getTileObject(z, x, y)->getIsUsingFloatPosition()) {

					getTileObject(z, x, y)->setX(getTileObject(z, x, y)->getX() - scrollX);
					//m_tileObjects[z][x+y*m_numColumns].setX( m_tileObjects[z][x+y*m_numColumns].getX() - scrollX) ;
				} else {
					//m_tileObjects[z][x+y*m_numColumns].setX((float)((int)(m_referenceObject.getX()) + m_tileObjects[z][x+y*m_numColumns].getStartX()) );
					getTileObject(z, x, y)->setX((float)(-(int)(m_x) + getTileObject(z, x, y)->getStartX()));
				}
			}			
		}
	}
	for (unsigned short i = 0; i < m_particles.size(); ++i) {
		m_particles.at(i)->setX(m_particles.at(i)->getX() - scrollX);
	}

	scrollEntitiesX(scrollX);
}

void cLevel::scrollY(float scrollY) {
	m_y += scrollY;

	m_referenceObject.setY( m_referenceObject.getY() - scrollY );
		
	if (m_backgroundPlanes != nullptr) {
		for (unsigned char i = 0; i < m_numBackgroundPlanes; ++i) {
			m_backgroundPlanes[i].setY(scrollY);
		}
	}
	if (m_foregroundPlanes != nullptr) {
		for (unsigned char i = 0; i < m_numForegroundPlanes; ++i) {
			m_foregroundPlanes[i].setY(scrollY);
		}
	}
	// Move tiles
	for (unsigned char z = 0; z < m_numLayers; ++z) {
		for (unsigned short x = 0; x < m_numColumns; ++x) {
			for (unsigned short y = 0; y < m_numRows; ++y) {
				if (getTileObject(z, x, y)->getIsUsingFloatPosition()) {
					getTileObject(z, x, y)->setY(getTileObject(z, x, y)->getY() - scrollY) ;
				} else {
					//m_tileObjects[z][x + y*m_numColumns].setY((float)((int)(m_referenceObject.getY()) + m_tileObjects[z][x + y*m_numColumns].getStartY()));
					getTileObject(z, x, y)->setY((float)(-(int)(m_y) + getTileObject(z, x, y)->getStartY()));
				}
			}
		}
	}
	for (unsigned short i = 0; i < m_particles.size(); ++i) {
		m_particles.at(i)->setY(m_particles.at(i)->getY() - scrollY);
	}

	scrollEntitiesY(scrollY);
}

void cLevel::scrollEntitiesX(float scrollX) {
	for (auto e = m_entities.begin(); e != m_entities.end(); ++e) {
		if ((*e)->getIsLocked()) {
			continue;
		}
		if ((*e)->getIsStatic() && !(*e)->getIsCarried() && !(*e)->getIsThrown()) {
			(*e)->setX((float)((int)(m_referenceObject.getX())) + (*e)->getStartX());
		} else {
			(*e)->setX((*e)->getX() - scrollX);
		}
	}
}

void cLevel::scrollEntitiesY(float scrollY) {
	for (auto e = m_entities.begin(); e != m_entities.end(); ++e) {
		if ((*e)->getIsLocked()) {
			continue;
		}
		if ((*e)->getIsStatic() && !(*e)->getIsCarried() && !(*e)->getIsThrown()) {
			(*e)->setY((float)((int)(m_referenceObject.getY())) + (*e)->getStartY());
		} else {
			(*e)->setY((*e)->getY() - scrollY);
		}
	}	
}


std::string cLevel::getNextForegroundPath(unsigned short num) {
	if (m_foregroundPlanes != nullptr) {
		return m_foregroundPlanes[num].getPathNext();
	} else {
		std::cout << "m_foregroundPlanes was NULL" << "\n";
		return "";
	}
}
void cLevel::setNextForegroundPath(unsigned short num, std::string path) {
	if (m_foregroundPlanes != nullptr && m_foregroundPlanes[num].getPathNext() != path) {
		std::cout << m_foregroundPlanes[num].getPathNext() << " " << path << "\n";
		m_foregroundPlanes[num].setPathNext(path);
		m_foregroundPlanes[num].setDoSwitchRow(true);
		m_foregroundPlanes[num].setNumSwitchedRows(0);
	}
}

void cLevel::setDoShowShopBox(unsigned char num, bool doShowShopBox) {
	m_doShowShopBox = doShowShopBox;

	//m_shopBox.setIsHidden(!showShopBox);
	m_currencyObject[num].setIsHidden(!doShowShopBox);

	m_fontCost[num].setIsHidden(!doShowShopBox);
	m_shopItems.at(num)->setIsHidden(!doShowShopBox);

	for (int i = 0; i < 3; ++i) {
		m_fontCost[i].setX(m_shopItems.at(i)->getX());
		m_fontCost[i].setY(m_shopItems.at(i)->getY() + 32);
		m_fontCost[i].setColor(m_r, m_g, m_b);
		m_fontCost[i].update(0.0f);

		m_currencyObject[i].setX(m_shopItems.at(i)->getRight() - 8);
		m_currencyObject[i].setY(m_shopItems.at(i)->getBottom());
		m_currencyObject[i].setColor(m_r, m_g, m_b);		
	}
	
}

//void cLevel::moveShopBoxLeft() {
//	if (m_shopItemCurrent > 0) {
//		--m_shopItemCurrent;
//		std::cout << (int)m_shopItemCurrent << "\n";
//	}
//	for (auto it = m_shopItems.begin(); it != m_shopItems.end(); ++it) {
//		(*it)->setIsHidden(true);
//	}
//	m_shopItems.at(m_shopItemCurrent)->setIsHidden(false);	
//}
//
//void cLevel::moveShopBoxRight() {
//	if (m_shopItemCurrent < 3) {
//		m_shopItemCurrent++;
//		std::cout << (int)m_shopItemCurrent << "\n";
//	}
//	for (auto it = m_shopItems.begin(); it != m_shopItems.end(); ++it) {
//		(*it)->setIsHidden(true);
//	}
//	m_shopItems.at(m_shopItemCurrent)->setIsHidden(false);
//}

void cLevel::update(cApp *app, float time) {
	for (unsigned char i = 0; i < 3; ++i) {
		m_currencyObject[i].update(1.0f);
	}

	if (!m_secondCall) {
		m_secondCall = true;

		// Sync animations
		for (auto it = m_updateEveryFrameList.begin(); it != m_updateEveryFrameList.end(); ++it) {
			(*it)->setTileOffsetX(0.0f);
		}
		//std::cout << "cLevel::update " << "\n";
	}

	m_referenceObject.update(time);	
	
	if (m_backgroundPlanes != nullptr) {
		for (unsigned short i = 0; i < m_numBackgroundPlanes; ++i) {
			m_backgroundPlanes[i].update(app, time);
		}		
	}
	if (m_foregroundPlanes != nullptr) {
		for (unsigned short i = 0; i < m_numForegroundPlanes; ++i) {		
			m_foregroundPlanes[i].update(app, time);
		}
	}	

	// Update every frame so their animation is the same
	for (auto it = m_updateEveryFrameList.begin(); it != m_updateEveryFrameList.end(); ++it) {
		(*it)->update(time);
	}

	for (unsigned short k = 0; k < m_entities.size(); ++k) {
		if (m_entities.at(k) != nullptr) {
			m_entities.at(k)->update(app, time);
			/*if(m_entities.at(k)->getTimerDeath() >= 1000) {
				m_entities.erase(m_entities.begin()+k, m_entities.begin()+k+1);
				cRenderingManager::removeObject(m_entities.at(k));
			}*/
		}
	}

	//std::cout << "cLevel::update " << m_particles.size() << "\n";

	for (unsigned short i = 0; i < m_particles.size(); ++i) {
		if (m_particles.at(i) != nullptr) {
			m_particles.at(i)->update(time);
			if (m_particles.at(i)->getDoRemove() /*|| m_particles.at(i)->getTimeBeingAlive() > 1000.0f*/) {
				//std::cout << "remove particle " << i << "\n";
				cRenderingManager::removeParticle(m_particles.at(i));
				//cRenderingManager::eraseParticle(i);
				m_particles.erase(m_particles.begin() + i, m_particles.begin() + i + 1);
			}
		}
	}
	//std::cout << m_particles.size() << "\n";
}

void cLevel::attachPlayer(cPlayer *player) {
	m_attachedPlayer = player;
	for (unsigned short k=0; k<m_entities.size(); ++k) {
		m_entities.at(k)->attachPlayer(player);
	}
}

float cLevel::getPlayerStart(std::string start, unsigned short number, unsigned char axis) const {
	if (start == "center") {
		if (axis == 'x' || axis == 'X') {
			return m_playerStartCenter.x;
		} else if (axis == 'y' || axis == 'Y') {
			return m_playerStartCenter.y;
		}
	} else if (start == "left") {
		if (axis == 'x' || axis == 'X') {
			return m_playerStartsLeft[number].x;
		} else if (axis == 'y' || axis == 'Y') {
			return m_playerStartsLeft[number].y;
		}
	} else if (start == "right") {
		if (axis == 'x' || axis == 'X') {
			return m_playerStartsRight[number].x;
		} else if (axis == 'y' || axis == 'Y') {
			return m_playerStartsRight[number].y;
		}
	} else if (start == "door") {		
		if (axis == 'x' || axis == 'X') {
			return m_playerStartsDoor[number].x;
		} else if (axis == 'y' || axis == 'Y') {
			return m_playerStartsDoor[number].y;
		}		
	} else if (start == "top") {
		if (axis == 'x' || axis == 'X') {
			return m_playerStartsTop[number].x;
		}
		else if (axis == 'y' || axis == 'Y') {
			return m_playerStartsTop[number].y;
		}
	} else if (start == "bottom") {
		if (axis == 'x' || axis == 'X') {
			return m_playerStartsBottom[number].x;
		} else if (axis == 'y' || axis == 'Y') {
			return m_playerStartsBottom[number].y;
		}
	}
	return 0.0f;
}

void cLevel::addParticle(cParticle *particle) {
	if (particle == nullptr) { return; };

	m_particles.push_back(particle);
	cRenderingManager::addParticle(m_particles.back());
}

void cLevel::addShopItem(cObject *object) {
	m_shopItems.push_back(object);
	m_shopItems.back()->loadConfig("Data\\Objects\\shop_box.cfg");
	m_shopItems.back()->setX(object->getX() + object->getOffsetX());
	m_shopItems.back()->setY(object->getY() + object->getOffsetY());
	m_shopItems.back()->setStartX(object->getX());
	m_shopItems.back()->setStartY(object->getY());
	m_shopItems.back()->setLevelX(object->getX());
	m_shopItems.back()->setLevelY(object->getY());
	m_shopItems.back()->setTileOffsetX(0.0f);
	m_shopItems.back()->setTileOffsetY(0.0f);
	m_shopItems.back()->setIsHidden(true);

	m_fontCost[m_shopItems.size() - 1].setX(m_shopItems.back()->getX());
	m_fontCost[m_shopItems.size() - 1].setY(m_shopItems.back()->getY());
	m_fontCost[m_shopItems.size() - 1].setIsHidden(true);

	m_currencyObject[m_shopItems.size() - 1].setX(m_shopItems.back()->getRight() - 8);
	m_currencyObject[m_shopItems.size() - 1].setY(m_shopItems.back()->getBottom());
	m_currencyObject[m_shopItems.size() - 1].setIsHidden(true);
	if (m_currencyItem[m_shopItems.size() - 1] == "gold") {
		m_currencyObject[m_shopItems.size() - 1].loadConfig("Data\\Objects\\coin_8.cfg");
	}
	cRenderingManager::addObject(&m_currencyObject[m_shopItems.size() - 1]);
}

cParticle *cLevel::getParticle(size_t n) {
	if (m_particles.empty() || n > (m_particles.size()-1)) {
		std::cout << "cLevel::getParticle no particles added to level" << "\n";
		return nullptr;
	}
	return m_particles.at(n);
}

cParticle *cLevel::getParticleLast() {
	if (m_particles.size() < 1 || m_particles.empty()) {
		std::cout << "cLevel::getParticleLast no particles added to level" << "\n";
		return nullptr;
	}
	return m_particles.back();
}

void cLevel::addEntity(cEntity *entity) {
	if (entity == nullptr) { return; };

	m_entities.push_back(entity);
	cRenderingManager::addEntity(m_entities.back());
}

cEntity *cLevel::getEntity(size_t n) {
	if (m_entities.empty()) {
		std::cout << "cLevel::getParticle no entities added to level" << "\n";
		return NULL;
	}
	return m_entities.at(n);
}

cEntity *cLevel::getEntityLast() {
	if (m_entities.size() < 1) {
		std::cout << "cLevel::getEntityLast no entities added to level" << "\n";
		return nullptr;
	}
	return m_entities.back();
}