#include "RenderingManager.h"
#include "TextureManager.h"
#include "Globals.h"

cRenderingManager::cRenderingManager() : m_backgroundSprites(NULL), m_levelSprites(NULL), m_attachedLevel(NULL), m_isWidescreen(false)
{
	m_numLayers = 0;
}

cRenderingManager::~cRenderingManager() {
	for (std::vector<cObject*>::const_iterator itr = m_objects.begin(); itr != m_objects.end(); ++itr) {
		delete *itr;
	}
	for (std::vector<cPlayer*>::const_iterator itr = m_players.begin(); itr != m_players.end(); ++itr) {
		delete *itr;
	}
	for (std::vector<cEnemy*>::const_iterator itr = m_enemies.begin(); itr != m_enemies.end(); ++itr) {
		delete *itr;
	}
	for (std::list<cProjectile*>::const_iterator itr = m_projectiles.begin(); itr != m_projectiles.end(); ++itr) {
		delete *itr;
	}
	for (std::vector<cBitmapFont*>::const_iterator itr = m_bitmapFonts.begin(); itr != m_bitmapFonts.end(); ++itr) {
		delete *itr;
	}	

	m_objects.clear();
	m_players.clear();
	m_enemies.clear();
	m_projectiles.clear();
	m_bitmapFonts.clear();

	m_objectSprites.clear();

	m_playerSprites.clear();
	m_playerShaders.clear();

	//clearLevel();	
}

void cRenderingManager::sleep(unsigned int mseconds) {
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void cRenderingManager::clear() {
	m_sfApp.clear();
}

void cRenderingManager::display() {
	m_sfApp.display();
}

bool cRenderingManager::isWindowOpened() const {
	return m_sfApp.isOpen();
}

bool cRenderingManager::getEvent(sf::Event &sfEvent) {
	return m_sfApp.pollEvent(sfEvent);
}

void cRenderingManager::createWindow(unsigned short width, unsigned short height, unsigned short bits, char *title, float multiplier, bool isFullscreen, bool isWidescreen) {
	//sf::WindowSettings Settings;
	//Settings.DepthBits         = 24; // Request a 24 bits depth buffer
	//Settings.StencilBits       = 8;  // Request a 8 bits stencil buffer
	//Settings.AntialiasingLevel = 0;  // Request 2 levels of antialiasing

	m_isWidescreen = isWidescreen;

	if(isFullscreen) {
		m_sfApp.create(sf::VideoMode(width*multiplier, height*multiplier, bits), title,sf::Style::Fullscreen);
		
		if(isWidescreen)
			m_sfApp.setView(sf::View((sf::FloatRect(-54,0,427,240))));
		else
			m_sfApp.setView(sf::View((sf::FloatRect(0,0,320,240))));

	}
	else {
		if(isWidescreen) {
			m_sfApp.create(sf::VideoMode(427*multiplier, 240*multiplier, bits), title,sf::Style::Close);			
			m_sfApp.setView(sf::View((sf::FloatRect(-54,0,427,240))));		
		}
		else {
			m_sfApp.create(sf::VideoMode(width*multiplier, height*multiplier, bits), title,sf::Style::Close);			
			m_sfApp.setView(sf::View((sf::FloatRect(0,0,320,240))));
		}
	}

	m_sfApp.setMouseCursorVisible(false);

	m_leftRectangle.setFillColor(sf::Color(31,31,31,255));
	m_leftRectangle.setSize(sf::Vector2f(16.0f, 240));		
	
	m_rightRectangle.setFillColor(sf::Color(31,31,31,255));
	m_rightRectangle.setSize(sf::Vector2f(16.0f, 240));

	//m_shader.loadFromFile("Data\\Shaders\\gaussian_blur.vert", "Data\\Shaders\\gaussian_blur.frag");
}

void cRenderingManager::closeWindow() {
	m_sfApp.close();
}

void cRenderingManager::setView(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2) {
	m_sfView.setViewport( sf::FloatRect(x1,y1,x2,y2) );
	m_sfApp.setView( m_sfView );
	//m_sfApp.SetView(sf::View(sf::FloatRect(0,0,320,240)));
}

void cRenderingManager::setFramerateLimit(unsigned short framerateLimit) {
	m_sfApp.setFramerateLimit(framerateLimit);
}

void cRenderingManager::setUseVerticalSync(bool useVerticalSync) {
	m_useVerticalSync = useVerticalSync;
	m_sfApp.setVerticalSyncEnabled(useVerticalSync);
}

void cRenderingManager::renderBackgrounds(unsigned short layerNumber, cApplication* application) {
	for (unsigned short j=0; j< m_attachedLevel->getNumColumns()/20 + 1; ++j) {
		m_backgroundSprites[layerNumber][j].setPosition( m_attachedLevel->m_backgrounds[layerNumber][j].getPositionX()-64+8, m_attachedLevel->m_backgrounds[layerNumber][j].getPositionY()-64+8);
		m_backgroundSprites[layerNumber][j].setTextureRect(sf::IntRect( m_attachedLevel->m_backgrounds[layerNumber][j].getTileOffsetX(), m_attachedLevel->m_backgrounds[layerNumber][j].getTileOffsetY(), m_attachedLevel->m_backgrounds[layerNumber][j].getWidth(), m_attachedLevel->m_backgrounds[layerNumber][j].getHeight()));	
		m_sfApp.draw( m_backgroundSprites[layerNumber][j] );	
	}
}

//void cRenderingManager::renderForegrounds(unsigned short layerNumber, cApplication* application)
//{
//	for(std::vector<cLevel*>::iterator itr = m_levels.begin(); itr != m_levels.end(); ++itr) {
//		for(unsigned short j=0; j<12; ++j) {
//			(*itr)->m_foregrounds[layerNumber][j].setImagePath(  application->getPathForeground(layerNumber) );
//
//			m_sfApp.draw(*(*itr)->m_foregrounds[layerNumber][j].getSprite());
//		}
//	}
//}

void cRenderingManager::renderObjects(cApplication* application) {
	for (unsigned short i=0; i<m_objects.size(); ++i) {
		if (m_objects.at(i)->getIsMorphable() == true) {
			if (m_objects.at(i)->getFacingLeft() ) {
				m_objectSprites.at(i)->setScale(-1.0f, 1.0f);
				m_objectSprites.at(i)->setPosition((int)(m_objects.at(i)->getPositionX()-64+8+m_objects.at(i)->getWidth()), (int)(m_objects.at(i)->getPositionY()-64+8));
			} else {
				m_objectSprites.at(i)->setScale(1.0f, 1.0f);
				m_objectSprites.at(i)->setPosition((int)(m_objects.at(i)->getPositionX()-64+8), (int)(m_objects.at(i)->getPositionY()-64+8));			
			}
		} else {
			if (m_objects.at(i)->getUseFloatPosition()) {
				m_objectSprites.at(i)->setPosition(m_objects.at(i)->getPositionX(), m_objects.at(i)->getPositionY());
			} else {
				m_objectSprites.at(i)->setPosition((int)m_objects.at(i)->getPositionX(), (int)(m_objects.at(i)->getPositionY()));
			}
		}

		m_objectSprites.at(i)->setTextureRect(sf::IntRect((int)m_objects.at(i)->getTileOffsetX(), (int)m_objects.at(i)->getTileOffsetY(), m_objects.at(i)->getWidth(), m_objects.at(i)->getHeight()));	

		if ( m_objects.at(i)->getIsHidden() != true/* && m_objects.at(i)->getTile() != 0*/) {
			m_sfApp.draw( *m_objectSprites.at(i) );
		}
	}
}

void cRenderingManager::renderPlayers(cApplication* application) {
	for (unsigned short i=0; i<m_players.size(); ++i) {
		if (m_players.at(i)->getFacingLeft() == true) {
			m_playerSprites.at(i)->setScale(-1.0f, 1.0f);

			if ( m_playerSprites.at(i)->getRotation() != 0.0f ) {
				m_playerSprites.at(i)->setPosition(m_players.at(i)->getPositionX()+m_players.at(i)->getWidth()-64, m_players.at(i)->getPositionY()+64);
			} else {
				m_playerSprites.at(i)->setPosition(m_players.at(i)->getPositionX()+m_players.at(i)->getWidth(), m_players.at(i)->getPositionY() );
			}
		} else {
			m_playerSprites.at(i)->setScale(1.0f, 1.0f);

			if (m_playerSprites.at(i)->getRotation() != 0.0f) {
				m_playerSprites.at(i)->setPosition(m_players.at(i)->getPositionX()+64, m_players.at(i)->getPositionY()+64);
			} else {
				m_playerSprites.at(i)->setPosition(m_players.at(i)->getPositionX(), m_players.at(i)->getPositionY() );
			}
		}		
				
		m_playerSprites.at(i)->setTextureRect(sf::IntRect((int)m_players.at(i)->getTileOffsetX(), (int)m_players.at(i)->getTileOffsetY() , m_players.at(i)->getWidth(), m_players.at(i)->getHeight() ));

		if ( m_players.at(i)->getIsHidden() != true) {
			if ( m_players.at(i)->getUseShader() == true) {
				m_sfApp.draw( *m_playerSprites.at(i), m_playerShaders.at(i) );
			} else {
				m_sfApp.draw( *m_playerSprites.at(i) );
			}
		}
	}
}

void cRenderingManager::renderEnemies(cApplication* application) {
	for (unsigned short i=0; i<m_enemies.size(); ++i) {
		if (m_enemies.at(i)->getFacingLeft() == true) {
			m_enemySprites.at(i)->setScale(-1.0f, 1.0f);

			if ( m_enemySprites.at(i)->getRotation() != 0.0f ) {
				m_enemySprites.at(i)->setPosition(m_enemies.at(i)->getPositionX()+m_enemies.at(i)->getWidth()-64, m_enemies.at(i)->getPositionY()+64);
			} else {
				m_enemySprites.at(i)->setPosition(m_enemies.at(i)->getPositionX()+m_enemies.at(i)->getWidth(), m_enemies.at(i)->getPositionY() );
			}
		} else {
			m_enemySprites.at(i)->setScale(1.0f, 1.0f);

			if (m_enemySprites.at(i)->getRotation() != 0.0f) {
				m_enemySprites.at(i)->setPosition(m_enemies.at(i)->getPositionX()+64, m_enemies.at(i)->getPositionY()+64);
			} else {
				m_enemySprites.at(i)->setPosition(m_enemies.at(i)->getPositionX(), m_enemies.at(i)->getPositionY() );
			}
		}		
				
		m_enemySprites.at(i)->setTextureRect(sf::IntRect((int)m_enemies.at(i)->getTileOffsetX(), (int)m_enemies.at(i)->getTileOffsetY() , m_enemies.at(i)->getWidth(), m_enemies.at(i)->getHeight() ));

		if ( m_enemies.at(i)->getIsHidden() != true) {
			if ( m_enemies.at(i)->getUseShader() == true) {
				m_sfApp.draw( *m_enemySprites.at(i), m_enemyShaders.at(i) );
			} else {
				m_sfApp.draw( *m_enemySprites.at(i) );
			}
		}
	}
}

void cRenderingManager::renderLevel(unsigned short layerNumber, cApplication* application) {
	if (m_attachedLevel == NULL || m_attachedLevel->m_tileObjects == NULL || m_levelSprites == NULL) {
		return;
	}

	// Find position of the tile in the upper left corner
	m_tileX = m_attachedLevel->getPositionX()/16;
	m_tileY = m_attachedLevel->getPositionY()/16;
	
	if (application->getIsWidescreen()) {
		if (m_tileX <= 4) {
			m_tileX = 4;
		}
	} else {
		if (m_tileX <= 0) {
			m_tileX = 0;
		}
	}
	if (m_tileX >= m_attachedLevel->getNumColumns()-application->getViewWidth()/16) {
		m_tileX = m_attachedLevel->getNumColumns()-application->getViewWidth()/16;
	}
	if (m_tileY <= 0) {
		m_tileY = 0;
	}
	if (m_tileY >= m_attachedLevel->getNumRows()-application->getViewHeight()/16) {
		m_tileY = m_attachedLevel->getNumRows()-application->getViewHeight()/16;
	}

	if (application->getIsWidescreen()) {
		for (int y=0; y<application->getViewHeight()/16+1; ++y) {			
			for (int x=-4; x<application->getViewWidth()/16+4; ++x) {
				if ( (m_tileX+x) < m_attachedLevel->getNumColumns() && (m_tileY+y) < m_attachedLevel->getNumRows() ) {
					m_currentTile = (m_tileX+x)+(m_tileY+y)*m_attachedLevel->getNumColumns();						
					//(*itr)->m_tileObjects[layerNumber][m_currentTile].update(time);						
					if ( m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getIsMorphable() == true) {
						if (m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getFacingLeft() ) {
							m_levelSprites[layerNumber][m_currentTile].setScale(-1.0f, 1.0f);
							m_levelSprites[layerNumber][m_currentTile].setPosition(m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getPositionX()-64+8+m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getWidth(), m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getPositionY()-64+8);
						} else {
							m_levelSprites[layerNumber][m_currentTile].setScale(1.0f, 1.0f);
							m_levelSprites[layerNumber][m_currentTile].setPosition(m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getPositionX()-64+8, m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getPositionY()-64+8);
						}
					} else {
						if (m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getUseFloatPosition()) {
							m_levelSprites[layerNumber][m_currentTile].setPosition(m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getPositionX(), m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getPositionY());
						} else {
							m_levelSprites[layerNumber][m_currentTile].setPosition(m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getPositionX(), m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getPositionY());
						}
					}
					m_levelSprites[layerNumber][m_currentTile].setTextureRect(sf::IntRect((int)m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getTileOffsetX(), (int)m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getTileOffsetY(), m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getWidth(), m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getHeight()));	

					if ( m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getTile() != 0 && m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getIsHidden() != true	) {
						m_sfApp.draw( m_levelSprites[layerNumber][m_currentTile] );
					}					
				}
			}
		}
	} else {
		for (int y=0; y<application->getViewHeight()/16+1; ++y) {			
			for (int x=0; x<application->getViewWidth()/16+1; ++x) {			
				if ( (m_tileX+x) < m_attachedLevel->getNumColumns() && (m_tileY+y) < m_attachedLevel->getNumRows() ) {					
					
					m_currentTile = (m_tileX+x)+(m_tileY+y)*m_attachedLevel->getNumColumns();						
					//(*itr)->m_tileObjects[layerNumber][m_currentTile].update(time);						
					if ( m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getIsMorphable() == true) {
						if (m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getFacingLeft() ) {
							m_levelSprites[layerNumber][m_currentTile].setScale(-1.0f, 1.0f);
							m_levelSprites[layerNumber][m_currentTile].setPosition((m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getPositionX()-64+8+m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getWidth()), (m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getPositionY()-64+8));
						} else {
							m_levelSprites[layerNumber][m_currentTile].setScale(1.0f, 1.0f);
							m_levelSprites[layerNumber][m_currentTile].setPosition((m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getPositionX()-64+8), (m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getPositionY()-64+8));			
						}
					} else {
						if (m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getUseFloatPosition()) {
							m_levelSprites[layerNumber][m_currentTile].setPosition(m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getPositionX(), m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getPositionY());
						} else {
							m_levelSprites[layerNumber][m_currentTile].setPosition(m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getPositionX(), (m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getPositionY()));
						}
					}

					m_levelSprites[layerNumber][m_currentTile].setTextureRect(sf::IntRect((int)m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getTileOffsetX(), (int)m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getTileOffsetY(), m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getWidth(), m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getHeight()));	

					if ( m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getTile() != 0 && m_attachedLevel->m_tileObjects[layerNumber][m_currentTile].getIsHidden() != true	) {
						m_sfApp.draw( m_levelSprites[layerNumber][m_currentTile] );
					}
				}
			}
		}
	}
}

//void cRenderingManager::renderQuadNodes(cApplication* application)
//{
//	cGlobals::get().m_quadNode.draw(m_sfApp);
//}

void cRenderingManager::renderBitmapFonts(cApplication* application) {
	for (unsigned short k=0; k<m_bitmapFonts.size(); ++k) {
		if (m_bitmapFonts.at(k)->getText().empty() == false) {
			for (unsigned short i=0; i<m_bitmapFonts.at(k)->getText().size(); ++i) {
				if (m_bitmapFonts.at(k)->m_sfSpriteArray != NULL) {
					m_bitmapFonts.at(k)->m_sfSpriteArray[i].setPosition(m_bitmapFonts.at(k)->getPositionX()+i*m_bitmapFonts.at(k)->getFontSize()-m_bitmapFonts.at(k)->m_charLineNumber[i]*(m_bitmapFonts.at(k)->getWidth()/8)*m_bitmapFonts.at(k)->getFontSize(), m_bitmapFonts.at(k)->getPositionY()+m_bitmapFonts.at(k)->m_charLineNumber[i]*m_bitmapFonts.at(k)->getFontSize());
					if ( m_bitmapFonts.at(k)->getIsHidden() != true) {

						//m_bitmapFonts.at(k)->m_sfSpriteArray[i].setTexture( *cTextureManager::get().load(m_imagePath) );

						//m_bitmapFonts.at(k)->m_sfSpriteArray[i].setTextureRect(sf::IntRect( m_bitmapFonts.at(k)->m_charOffsetX[i], m_bitmapFonts.at(k)->m_charOffsetY[i], m_bitmapFonts.at(k)->getFontSize(), m_bitmapFonts.at(k)->getFontSize() ));

						m_sfApp.draw( m_bitmapFonts.at(k)->m_sfSpriteArray[i] );

						//m_sfApp.draw( *m_bitmapFontVector.at(k).at(i) );
					}
				}
			}
		}
	}	
}

void cRenderingManager::addBitmapFont(cBitmapFont* bitmapFont) {
	m_bitmapFonts.push_back(bitmapFont);

	/*std::vector<sf::Sprite*> tmpSpriteVector;

	tmpSpriteVector.push_back(new sf::Sprite);

	for(unsigned short i=0; i<bitmapFont->getTextSize(); ++i) {
		tmpSpriteVector.at( tmpSpriteVector.size()-1 )->setTexture(*cTextureManager::get().load( bitmapFont->getImagePath() ), true );
		tmpSpriteVector.at( tmpSpriteVector.size()-1 )->setTextureRect(sf::IntRect(bitmapFont->m_charOffsetX[i], bitmapFont->m_charOffsetY[i], bitmapFont->getFontSize() , bitmapFont->getFontSize() ));
	}

	m_bitmapFontVector.push_back( tmpSpriteVector );*/
}

//void cRenderingManager::removeBitmapFont(cBitmapFont* bitmapFont) {
//	m_bitmapFonts.remove(bitmapFont);
//}

void cRenderingManager::renderProjectiles(cApplication* application) {
	for(std::list<cProjectile*>::iterator itr = m_projectiles.begin(); itr != m_projectiles.end(); ++itr) {
		//std::cout << (*itr)->getIsHidden() << std::endl;
		if( (*itr)->getIsHidden() != true) {
			m_sfApp.draw( *(*itr)->getSprite() ) ;
		}
	}
}

void cRenderingManager::addObject(cObject* object) {	
	//if (object->getImagePath().empty() == true) {
	//	//std::cout << object->getIsHidden() << " " << object->getType() << " not found " << object->getTile()  << std::endl << std::endl << std::endl;
	//	return;
	//}
	m_objects.push_back(object);
	m_objectSprites.push_back(new sf::Sprite);

	m_objectSprites.at( m_objectSprites.size()-1 )->setTexture( *cTextureManager::get().load( object->getImagePath() ), true );
	m_objectSprites.at( m_objectSprites.size()-1 )->setTextureRect(sf::IntRect((int)object->getTileOffsetX(), (int)object->getTileOffsetY(), (int)object->getWidth(), (int)object->getHeight()));
}

void cRenderingManager::addPlayer(cPlayer* player) {
	m_players.push_back(player);
	m_playerSprites.push_back(new sf::Sprite);
	m_playerShaders.push_back(new sf::Shader);
	m_playerSprites.at( m_playerSprites.size()-1 )->setTexture( *cTextureManager::get().load( player->getImagePath() ),true );
	m_playerShaders.at( m_playerShaders.size()-1 )->loadFromFile(player->getPathShader(), sf::Shader::Type::Fragment);
	m_playerSprites.at( m_playerSprites.size()-1 )->setTextureRect(sf::IntRect((int)player->getTileOffsetX(), (int)player->getTileOffsetY(), (int)player->getWidth(), (int)player->getHeight()));
}

void cRenderingManager::addEnemy(cEnemy* enemy) {
	m_enemies.push_back(enemy);
	m_enemySprites.push_back(new sf::Sprite);
	m_enemyShaders.push_back(new sf::Shader);
	m_enemySprites.at( m_enemySprites.size()-1 )->setTexture( *cTextureManager::get().load( enemy->getImagePath() ),true );
	m_enemyShaders.at( m_enemyShaders.size()-1 )->loadFromFile(enemy->getPathShader(), sf::Shader::Type::Fragment);
	m_enemySprites.at( m_enemySprites.size()-1 )->setTextureRect(sf::IntRect((int)enemy->getTileOffsetX(), (int)enemy->getTileOffsetY(), (int)enemy->getWidth(), (int)enemy->getHeight()));
}

void cRenderingManager::addLevel(cLevel* level) {
	/*if (m_attachedLevel != NULL) {
		return;
	}*/

	m_attachedLevel = level;
	m_levelSprites = new sf::Sprite*[level->getNumLayers()];

	m_numLayers = level->getNumLayers();

	for (unsigned short z=0; z<level->getNumLayers(); ++z) {
		//m_levelObjects[z] = new cObject [ level->getNumColumns() * level->getNumRows() ];
		m_levelSprites[z] = new sf::Sprite [ level->getNumColumns() * level->getNumRows() ];
		
		for (unsigned short i=0; i<level->getNumColumns()*level->getNumRows(); ++i) {
			m_levelSprites[z][i].setTexture( *cTextureManager::get().load( level->m_tileObjects[z][i].getImagePath() ), true );
			m_levelSprites[z][i].setTextureRect(sf::IntRect((int)level->m_tileObjects[z][i].getTileOffsetX(), (int)level->m_tileObjects[z][i].getTileOffsetY(), (int)level->m_tileObjects[z][i].getWidth(), (int)level->m_tileObjects[z][i].getHeight()));
		}
	}
	
	for (unsigned short j=0; j<level->m_enemies.size(); ++j) {
		addEnemy(level->m_enemies.at(j));
	}

	// CRASH

	/*for (unsigned short j=0; j<level->m_specialObjects.size(); ++j) {
		addObject(level->m_specialObjects.at(j));
	}*/

	//addObject( &level->m_flagObject );
	
	m_backgroundSprites = new sf::Sprite*[2];

	for (unsigned short z=0; z<2; ++z) {
		m_backgroundSprites[z] = new sf::Sprite [level->getNumColumns()/20 + 1];

		for (unsigned short i=0; i<level->getNumColumns()/20 + 1; ++i) {
			m_backgroundSprites[z][i].setTexture( *cTextureManager::get().load( level->m_backgrounds[z][i].getImagePath() ), true );
			m_backgroundSprites[z][i].setTextureRect(sf::IntRect((int)level->m_backgrounds[z][i].getTileOffsetX(), (int)level->m_backgrounds[z][i].getTileOffsetY(), (int)level->m_backgrounds[z][i].getWidth(), (int)level->m_backgrounds[z][i].getHeight()));
		}
	}

}

void cRenderingManager::addProjectile(cProjectile* projectile) {
	m_projectiles.push_back(projectile);
}

void cRenderingManager::removeProjectile(cProjectile* projectile) {
	m_projectiles.remove(projectile);
}

void cRenderingManager::clearProjectiles() {
	m_projectiles.clear();	
}

void cRenderingManager::clearObjects() {
	/*for (std::vector<cObject*>::const_iterator itr = m_objects.begin(); itr != m_objects.end(); ++itr) {
		delete *itr;
	}*/
	m_objects.clear();
	m_objectSprites.clear();
}

void cRenderingManager::clearPlayers() {
	m_players.clear();
	m_playerSprites.clear();
	m_playerShaders.clear();
}

void cRenderingManager::clearEnemies() {
	m_enemies.clear();
	m_enemySprites.clear();
	m_enemyShaders.clear();
}

void cRenderingManager::clearLevel() {	
	/*if (m_attachedLevel == NULL) {
		return;
	}*/
	std::cout << "delete [] m_backgroundSprites[i];" << std::endl;

	for (unsigned short i=0; i<2; ++i) {
		delete [] m_backgroundSprites[i];
		m_backgroundSprites[i] = NULL;		
	}

	delete [] m_backgroundSprites;	
	m_backgroundSprites = NULL;
	
	std::cout << "delete [] m_levelSprites[i];" << std::endl;
	for (unsigned char i=0; i<m_numLayers; ++i) {
		std::cout << "i " << (int)i << std::endl;
		delete [] m_levelSprites[i];
		m_levelSprites[i] = NULL;
	}
	std::cout << "delete [] m_levelSprites;" << std::endl;
	delete [] m_levelSprites;
	m_levelSprites = NULL;
	
	m_attachedLevel = NULL;

	/*m_objects.clear();
	m_objectSprites.clear();*/
	
	m_enemies.clear();
	m_enemySprites.clear();
	m_enemyShaders.clear();
}

//void cRenderingManager::clearBitmapFont(cBitmapFont* bitmapFont) {	
//	//m_bitmapFonts.clear();
//	bitmapFont->clearText();
//}
void cRenderingManager::clearBitmapFonts() {
	m_bitmapFonts.clear();

	//for(int i=0; i<m_bitmapFontVector.size(); ++i) {
	//	//for(j=0; j<m_bitmapFontVector.at(i).size(); ++j) {
	//		m_bitmapFontVector.at(i).clear();
	//	//}
	//}

	
	//for(int j=0; j<cRenderingManager::get().m_bitmapFontSprites.size(); ++j) {
	//	delete cRenderingManager::get().m_bitmapFontSprites.at(j);
	//	//for(i=0; i<cRenderingManager::get().m_bitmapFontSprites.at(j).size(); ++i) {
	//	//	//for(int j=0; j<cRenderingManager::get().m_bitmapFontSprites.size(); ++i) {
	//	//	delete [] cRenderingManager::get().m_bitmapFontSprites.at(i);
	//	//}
	//}
	//cRenderingManager::get().m_bitmapFontSprites.clear();
}
