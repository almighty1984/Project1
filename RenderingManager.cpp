#include "RenderingManager.h"
#include "TextureManager.h"
#include "MusicManager.h"
#include "InputManager.h"

cLevel*						cRenderingManager::m_attachedLevel = nullptr;
sf::View					cRenderingManager::m_sfView;
cWindow						cRenderingManager::m_window;
std::list<cBitmapFont*>		cRenderingManager::m_bitmapFonts;
std::list<cObject*>			cRenderingManager::m_objects;
std::list<cParticle*>		cRenderingManager::m_particles;
std::vector<cPlane*>		cRenderingManager::m_backgroundPlanes;
std::vector<cPlane*>		cRenderingManager::m_foregroundPlanes;
std::vector<cPlayer*>		cRenderingManager::m_players;
std::vector<sf::Shader*>	cRenderingManager::m_playerShaders;
//std::vector<cEntity*>		cRenderingManager::m_entities;
std::map<unsigned char, std::vector<cEntity*>>	cRenderingManager::m_entityMap;
std::vector<sf::Shader*>	cRenderingManager::m_entityShaders;
std::string					cRenderingManager::m_pathFont;

cRenderingManager::~cRenderingManager() {
	m_objects.clear();
	m_players.clear();
	//m_entities.clear();
	m_entityMap.clear();
	m_particles.clear();
	m_bitmapFonts.clear();
	m_entityShaders.clear();
	m_playerShaders.clear();
}

std::string cRenderingManager::getPathFont() {
	return m_pathFont;
}
void cRenderingManager::setPathFont(std::string pathFont) {
	m_pathFont = pathFont;
}

void cRenderingManager::attachLevel(cLevel *level) {
	m_attachedLevel = level;
	m_window.attachLevel(level);
}

cLevel* cRenderingManager::getAttachedLevel() {
	return m_attachedLevel;
}

bool cRenderingManager::getUseVerticalSync() {
	return m_window.getUseVerticalSync();
}
bool cRenderingManager::getIsWidescreen() {
	return m_window.getIsWidescreen();
}
bool cRenderingManager::isWindowOpened() {
	return m_window.isOpen();
}
float cRenderingManager::getViewX() {
	return m_window.getViewX();
}
void cRenderingManager::setViewX(float viewX) {
	m_window.setViewX(viewX);
}
bool cRenderingManager::getIsViewLocked() {
	return m_window.getIsViewLocked();
}
void cRenderingManager::setIsViewLocked(bool isViewLocked) {
	m_window.setIsViewLocked(isViewLocked);
}
bool cRenderingManager::getShowLevelNodeGrid() {
	return m_window.getShowLevelNodeGrid();
}
void cRenderingManager::setShowLevelNodeGrid(bool showLevelNodeGrid) {
	m_window.setShowLevelNodeGrid(showLevelNodeGrid);
}

void cRenderingManager::sleep(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void cRenderingManager::clear() {
	m_window.clear();
}

void cRenderingManager::display() {
	m_window.display();
}

void cRenderingManager::createWindow(unsigned short width, unsigned short height, unsigned short bits, char *title, float multiplier, bool isFullscreen, bool isWidescreen) {
	m_window.create(width, height, bits, title, multiplier, isFullscreen, isWidescreen);
}

void cRenderingManager::closeWindow() {
	m_window.close();
}

void cRenderingManager::setView(float x1, float y1, float x2, float y2) {
	m_window.setView(x1,y1,x2,y2);
}

void cRenderingManager::setFramerateLimit(unsigned short framerateLimit) {
	m_window.setFramerateLimit(framerateLimit);
}

void cRenderingManager::setUseVerticalSync(bool useVerticalSync) {
	m_window.setUseVerticalSync(useVerticalSync);
}

void cRenderingManager::renderBackgroundPlanes(cApp *app) {
for (unsigned short i = 0; i < m_backgroundPlanes.size(); ++i) {
	if (m_backgroundPlanes.at(i) == nullptr) {
		continue;
	}
	for (unsigned short x = 0; x < m_backgroundPlanes.at(i)->getNumColumns() * m_backgroundPlanes.at(i)->getNumRows(); ++x) {
		m_backgroundPlanes.at(i)->getPlaneObject(x)->setSpriteRect((int)m_backgroundPlanes.at(i)->getPlaneObject(x)->getTileOffsetX(), (int)m_backgroundPlanes.at(i)->getPlaneObject(x)->getTileOffsetY(), m_backgroundPlanes.at(i)->getPlaneObject(x)->getWidth(), m_backgroundPlanes.at(i)->getPlaneObject(x)->getHeight());
		m_window.draw(m_backgroundPlanes.at(i)->m_planeObjects.at(x)->getSprite());
	}
}
}

void cRenderingManager::renderForegroundPlanes(cApp* app) {
	for (unsigned short i = 0; i < m_foregroundPlanes.size(); ++i) {
		if (m_foregroundPlanes.at(i) == nullptr) {
			continue;
		}
		for (unsigned short x = 0; x < m_foregroundPlanes.at(i)->getNumColumns() * m_foregroundPlanes.at(i)->getNumRows(); ++x) {
			if (m_foregroundPlanes.at(i)->getPlaneObject(x) != nullptr && !m_foregroundPlanes.at(i)->getPlaneObject(x)->getIsHidden()) {
				m_foregroundPlanes.at(i)->getPlaneObject(x)->setSpriteRect((int)m_foregroundPlanes.at(i)->getPlaneObject(x)->getTileOffsetX(), (int)m_foregroundPlanes.at(i)->getPlaneObject(x)->getTileOffsetY(), m_foregroundPlanes.at(i)->getPlaneObject(x)->getWidth(), m_foregroundPlanes.at(i)->getPlaneObject(x)->getHeight());
				m_window.draw(m_foregroundPlanes.at(i)->m_planeObjects.at(x)->getSprite());
			}
		}
	}
}

void cRenderingManager::renderObjects(cApp* app) {
	for (auto it = m_objects.begin(); it != m_objects.end(); ++it) {
		if (*it == nullptr || (*it)->getSprite() == nullptr) {
			return;
		}
		if ((*it)->getIsFacingLeft()) {
			if ((*it)->getIsUpsideDown()) {
				(*it)->setSpriteScale(-1.0f, -1.0f);
			} else {
				(*it)->setSpriteScale(-1.0f, 1.0f);
			}
			(*it)->setSpritePosition((*it)->getX() + (*it)->getSpriteOffsetX() + (*it)->getWidth(), (*it)->getY() + (*it)->getSpriteOffsetY());
		} else {
			if ((*it)->getIsUpsideDown()) {
				(*it)->setSpriteScale(1.0f, -1.0f);
			} else {
				(*it)->setSpriteScale(1.0f, 1.0f);
			}
			(*it)->setSpritePosition((*it)->getX() + (*it)->getSpriteOffsetX(), (*it)->getY() + (*it)->getSpriteOffsetY());
		}

		if (!(*it)->getIsHidden()) {
			(*it)->setSpriteRect((int)(*it)->getTileOffsetX(), (int)(*it)->getTileOffsetY(), (*it)->getWidth(), (*it)->getHeight());

			if ((*it)->getDoUseShader()) {
				m_window.draw((*it)->getSprite(), (*it)->getShader());
			} else {
				m_window.draw((*it)->getSprite());
			}
		}
	}
}

void cRenderingManager::renderPlayers(cApp* app) {
	float scaleX = 1.0f;
	float scaleY = 1.0f;

	float spritePosX = 0.0f;
	float spritePosY = 0.0f;
	for (auto it = m_players.begin(); it != m_players.end(); ++it) {
		if ((*it)->getIsFacingLeft()) {
			scaleX = -1.0f;
			spritePosX = (*it)->getX() + (*it)->getSpriteOffsetX() + (*it)->getWidth();
		} else {
			scaleX = 1.0f;
			spritePosX = (*it)->getX() + (*it)->getSpriteOffsetX();
		}
		if ((*it)->getIsUpsideDown()) {
			scaleY = -1.0f;
			spritePosY = (*it)->getY() + (*it)->getSpriteOffsetY() + (*it)->getHeight();
		} else {
			scaleY = 1.0f;
			spritePosY = (*it)->getY() + (*it)->getSpriteOffsetY();
		}

		(*it)->setSpriteScale(scaleX, scaleY);
		(*it)->setSpritePosition(spritePosX, spritePosY);

		(*it)->setSpriteRect((int)(*it)->getTileOffsetX(), (int)(*it)->getTileOffsetY(), (*it)->getWidth(), (*it)->getHeight());

		if (!(*it)->getIsHidden()) {
			if ((*it)->getDoUseShader()/* && m_players.at(i)->getIsHurting()*/) {
				m_window.draw((*it)->getSprite(), (*it)->getShader());
			} else {
				m_window.draw((*it)->getSprite());
			}
		}
	}
}

void cRenderingManager::renderEntities(unsigned char layer, cApp* app) {
	for (auto it = m_entityMap[layer].begin(); it != m_entityMap[layer].end(); ++it) {
		if (*it == nullptr) {
			continue;
		}
		
		if ((*it)->getIsFacingLeft() && !(*it)->getDontFlipSprite()) {
			(*it)->setSpriteScale(-1.0f, 1.0f);
			(*it)->setSpritePosition((*it)->getX()+ (*it)->getWidth()+ (*it)->getSpriteOffsetX(), (*it)->getY() + (*it)->getSpriteOffsetY());
		} else {
			(*it)->setSpriteScale(1.0f, 1.0f);
			(*it)->setSpritePosition((*it)->getX() + (*it)->getSpriteOffsetX(), (*it)->getY() + (*it)->getSpriteOffsetY());
		}				
		(*it)->setSpriteRect((int)(*it)->getTileOffsetX(), (int)(*it)->getTileOffsetY() , (*it)->getWidth(), (*it)->getHeight() );

		if (!(*it)->getIsHidden()) {
			if ((*it)->getDoUseShader() && (*it)->getIsHurting()) {
				//m_sfApp.draw( *m_players.at(i)->m_sprite.getSprite(), m_playerShaders.at(i) );
				m_window.draw((*it)->getSprite(), (*it)->getShader() );
			} else {
				//m_sfApp.draw( *m_players.at(i)->m_sprite.getSprite() );
				
				m_window.draw((*it)->getSprite() );
			}
		}		
	}
	
	//for (auto it = m_entities.begin(); it != m_entities.end(); ++it) {
	//	if (*it == nullptr) {
	//		continue;
	//	}
	//	
	//	if ((*it)->getIsFacingLeft() && !(*it)->getDontFlipSprite()) {
	//		(*it)->setSpriteScale(-1.0f, 1.0f);
	//		(*it)->setSpritePosition((*it)->getX()+ (*it)->getWidth()+ (*it)->getSpriteOffsetX(), (*it)->getY() + (*it)->getSpriteOffsetY());
	//	} else {
	//		(*it)->setSpriteScale(1.0f, 1.0f);
	//		(*it)->setSpritePosition((*it)->getX() + (*it)->getSpriteOffsetX(), (*it)->getY() + (*it)->getSpriteOffsetY());
	//	}				
	//	(*it)->setSpriteRect((int)(*it)->getTileOffsetX(), (int)(*it)->getTileOffsetY() , (*it)->getWidth(), (*it)->getHeight() );

	//	if (!(*it)->getIsHidden()) {
	//		if ((*it)->getDoUseShader() && (*it)->getIsHurting()) {
	//			//m_sfApp.draw( *m_players.at(i)->m_sprite.getSprite(), m_playerShaders.at(i) );
	//			m_window.draw((*it)->getSprite(), (*it)->getShader() );
	//		} else {
	//			//m_sfApp.draw( *m_players.at(i)->m_sprite.getSprite() );
	//			
	//			m_window.draw((*it)->getSprite() );
	//		}
	//	}		
	//}
}

void cRenderingManager::renderLevel(unsigned char layerNumber, cApp *app) {
	if (m_attachedLevel == nullptr || m_attachedLevel->getTileObjects() == nullptr) {
		return;
	}
	if (m_window.getShowLevelNodeGrid()) {
		m_window.drawGrid();
	}

	cLevel* level = m_attachedLevel;

	// Find position of the tile in the upper left corner
	short upperTileX = (int)(level->getX() / 16) + (int)(m_window.getViewX() / 16) - 0;
	short upperTileY = (int)(level->getY()/16);

	//std::cout << m_window.getViewX()/16 << "\n";	

	//std::cout << viewOffsetX << "\n";

	if (app->getIsWidescreen()) {
		if (upperTileX < 4) {
			upperTileX = 4;
		}
	} else {
		if (upperTileX < 0) {
			upperTileX = 0;
		}
	}
	if (upperTileX > (int)(level->getNumColumns() - app->getViewWidth() / 16)) {
		upperTileX = (int)(level->getNumColumns() - app->getViewWidth() / 16);
	}
	if (upperTileY < 0) {
		upperTileY = 0;
	}
	if (upperTileY > (int)(level->getNumRows() - app->getViewHeight() / 16)) {
		upperTileY = (int)(level->getNumRows() - app->getViewHeight() / 16);
	}

	unsigned short tileX = 0;
	unsigned short tileY = 0;

	if (app->getIsWidescreen()) {
		for (int y = 0; y < app->getViewHeight() / 16 + 1; ++y) {
			for (int x = -4; x < app->getViewWidth() / 16 + 5; ++x) {
				if ((upperTileY + y) >= 0 && (upperTileX + x) < level->getNumColumns() && (upperTileY + y) < level->getNumRows()) {

					tileX = (upperTileX + x);
					tileY = (upperTileY + y);

					if (level->getTileObject(layerNumber, tileX, tileY) == nullptr) {
						return;
					}
					if (level->getTileObject(layerNumber, tileX, tileY)->getIsFacingLeft()) {
						level->getTileObject(layerNumber, tileX, tileY)->setSpriteScale(-1.0f, 1.0f);
					} else {
						level->getTileObject(layerNumber, tileX, tileY)->setSpriteScale(1.0f, 1.0f);
					}

					level->getTileObject(layerNumber, tileX, tileY)->setSpritePosition(level->getTileObject(layerNumber, tileX, tileY)->getX() + level->getTileObject(layerNumber, tileX, tileY)->getSpriteOffsetX(), level->getTileObject(layerNumber, tileX, tileY)->getY() + level->getTileObject(layerNumber, tileX, tileY)->getSpriteOffsetY());
					level->getTileObject(layerNumber, tileX, tileY)->setSpriteRect((int)level->getTileObject(layerNumber, tileX, tileY)->getTileOffsetX(), (int)level->getTileObject(layerNumber, tileX, tileY)->getTileOffsetY(), level->getTileObject(layerNumber, tileX, tileY)->getWidth(), level->getTileObject(layerNumber, tileX, tileY)->getHeight());

					if (level->getTileObject(layerNumber, tileX, tileY)->getTile() != 0 && (!level->getTileObject(layerNumber, tileX, tileY)->getIsHidden() || getShowLevelNodeGrid())) {
						//m_sfApp.draw( *level->getTileObject(layerNumber, currentTile)->m_sprite.getSprite() );

						m_window.draw(level->getTileObject(layerNumber, tileX, tileY)->getSprite());
					}
				}
			}
		}
	} else {
		for (int y = 0; y < app->getViewHeight() / 16 + 1; ++y) {
			for (int x = 0; x < app->getViewWidth() / 16 + 2; ++x) {
				if ((upperTileX + x) < level->getNumColumns() && (upperTileY + y) < level->getNumRows()) {

					tileX = (upperTileX + x);
					tileY = (upperTileY + y);

					/*if (level->getTileObjects() == nullptr) {
						return;
					}*/

					if (level->getTileObject(layerNumber, tileX, tileY)->getIsFacingLeft()) {
						level->getTileObject(layerNumber, tileX, tileY)->setSpriteScale(-1.0f, 1.0f);
					} else {
						level->getTileObject(layerNumber, tileX, tileY)->setSpriteScale(1.0f, 1.0f);
					}
					level->getTileObject(layerNumber, tileX, tileY)->setSpritePosition(level->getTileObject(layerNumber, tileX, tileY)->getX() + level->getTileObject(layerNumber, tileX, tileY)->getSpriteOffsetX(), (level->getTileObject(layerNumber, tileX, tileY)->getY() + level->getTileObject(layerNumber, tileX, tileY)->getSpriteOffsetY()));
					level->getTileObject(layerNumber, tileX, tileY)->setSpriteRect((int)level->getTileObject(layerNumber, tileX, tileY)->getTileOffsetX(), (int)level->getTileObject(layerNumber, tileX, tileY)->getTileOffsetY(), level->getTileObject(layerNumber, tileX, tileY)->getWidth(), level->getTileObject(layerNumber, tileX, tileY)->getHeight());

					if (level->getTileObject(layerNumber, tileX, tileY)->getTile() != 0 && (!level->getTileObject(layerNumber, tileX, tileY)->getIsHidden() || getShowLevelNodeGrid())) {
						//m_sfApp.draw( *level->getTileObject(layerNumber, currentTile)->m_sprite.getSprite() );
						m_window.draw(level->getTileObject(layerNumber, tileX, tileY)->getSprite());
					}
				}
			}
		}
	}

	/*for (unsigned short i = 0; i < level->m_rectangleShapes.size(); ++i){
		m_window.m_sfApp.draw(*level->m_rectangleShapes.at(i));
	}*/
}

void cRenderingManager::renderQuadNodes(cApp *app) {
	//cGlobals::get().m_quadNode.draw(m_sfApp);
	//m_quadNode.update(0.0f);
	//m_quadNode.draw(m_window.m_sfApp);

	//m_window.draw(&m_quadNode);	
}

void cRenderingManager::renderBitmapFonts(cApp *app) {
	for (auto it = m_bitmapFonts.begin(); it != m_bitmapFonts.end(); ++it) {
		if (*it == nullptr) {
			return;
		}		
		if (!(*it)->getText().empty() && *it != nullptr) {
			for (unsigned short i = 0; i < (*it)->getText().size(); ++i) {
				if ((*it)->getIsHidden() != true) {
					m_window.draw((*it)->getSprite(i));
				}
			}
		}
	}
}

void cRenderingManager::addBitmapFont(cBitmapFont *bitmapFont) {
	m_bitmapFonts.push_back(bitmapFont);
}
void cRenderingManager::removeBitmapFont(cBitmapFont *bitmapFont) {
	m_bitmapFonts.remove(bitmapFont);
}
void cRenderingManager::clearBitmapFonts() {
	m_bitmapFonts.clear();
}

void cRenderingManager::renderParticles(cApp *app) {
	for (auto it = m_particles.begin(); it != m_particles.end(); ++it) {
		if (*it == nullptr) {
			continue;
		}
		/*if ((*it)->getX() < app->getViewWidth()+64 && (*it)->getX() > -48.0f &&
			(*it)->getY() < app->getViewHeight() && (*it)->getY() > 0.0f) {*/
		//std::cout << (*itr)->getIsHidden() << "\n";
			if ((*it)->getIsFacingLeft()) {
				if ((*it)->getIsUpsideDown()) {
					(*it)->setSpriteScale(-1.0f, -1.0f);
				} else {
					(*it)->setSpriteScale(-1.0f, 1.0f);
				}
				(*it)->setSpritePosition((*it)->getX() + (*it)->getSpriteOffsetX() + (*it)->getWidth(), (*it)->getY() + (*it)->getSpriteOffsetY());
			} else {
				if ((*it)->getIsUpsideDown()) {
					(*it)->setSpriteScale(1.0f, -1.0f);
				} else {
					(*it)->setSpriteScale(1.0f, 1.0f);
				}
				(*it)->setSpritePosition((*it)->getX() + (*it)->getSpriteOffsetX(), (*it)->getY() + (*it)->getSpriteOffsetY());
			}
			(*it)->setSpriteRect((int)(*it)->getTileOffsetX(), (int)(*it)->getTileOffsetY(), (*it)->getWidth(), (*it)->getHeight());

			if (!(*it)->getIsHidden()) {
				//m_sfApp.draw( *(*itr)->m_sprite.getSprite() ) ;
				m_window.draw((*it)->getSprite());
			}
		//}
	}
}

void cRenderingManager::addBackgroundPlane(cPlane *plane) {
	m_backgroundPlanes.push_back(plane);
}
void cRenderingManager::addForegroundPlane(cPlane *plane) {
	m_foregroundPlanes.push_back(plane);
}

void cRenderingManager::addObject(cObject *object) {
	m_objects.push_back(object);
}

void cRenderingManager::removeObject(cObject *object) {
	m_objects.remove(object);
}

void cRenderingManager::addPlayer(cPlayer* player) {
	m_players.push_back(player);
}

void cRenderingManager::addEntity(cEntity* entity) {
	//m_entities.push_back(entity);

	m_entityMap[entity->getLayer()].push_back(entity);
}

void cRenderingManager::addLevel(cLevel* level) {
	if (m_attachedLevel != nullptr) {
		return;
	}

	m_attachedLevel = level;
		
	for (unsigned short j=0; j<level->getEntities()->size(); ++j) {
		addEntity(level->getEntities()->at(j));
	}
}

void cRenderingManager::addParticle(cParticle* particle) {
	m_particles.push_back(particle);
}

void cRenderingManager::removeParticle(cParticle *particle) {
	m_particles.remove(particle);
}

//void cRenderingManager::eraseBitmapFont(unsigned short i) {
//	if (i < m_bitmapFonts.size()) {
//		m_bitmapFonts.erase(m_bitmapFonts.begin() + i, m_bitmapFonts.begin() + i + 1);
//	}
//}
//void cRenderingManager::eraseParticle(unsigned short i) {
//	if (i < m_particles.size()) {
//		m_particles.erase(m_particles.begin() + i, m_particles.begin() + i + 1);
//	}
//}

void cRenderingManager::clearParticles() {
	m_particles.clear();
}

void cRenderingManager::clearBackgroundPlanes() {
	m_backgroundPlanes.clear();
}
void cRenderingManager::clearForegroundPlanes() {
	m_foregroundPlanes.clear();
}
void cRenderingManager::clearObjects() {	
	m_objects.clear();
}

void cRenderingManager::clearPlayers() {
	m_players.clear();
	m_playerShaders.clear();
}

void cRenderingManager::clearEntities() {
	//m_entities.clear();
	m_entityMap.clear();
	m_entityShaders.clear();
}

void cRenderingManager::clearLevel() {	
	m_attachedLevel = nullptr;
	clearObjects();
	clearEntities();
	clearBackgroundPlanes();
}

