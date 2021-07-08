#include "CollisionManager.h"

cCollisionManager::cCollisionManager()
: m_secondCall(false),
  m_windowWidth(0), m_windowHeight(0), m_tileX(0), m_tileY(0), m_enemyTileX(0), m_enemyTileY(0), m_oldEnemyTileX(0), m_oldEnemyTileY(0),
  m_boxTileX(0), m_boxTileY(0), m_oldBoxTileX(0), m_oldBoxTileY(0),
  m_tileXWidener(0) {

	m_playerNodes = new unsigned short[4];

	m_playerNodes[0] = 0;
	m_playerNodes[1] = 0;
	m_playerNodes[2] = 0;
	m_playerNodes[3] = 0;

}

cCollisionManager::~cCollisionManager() {
	//cGlobals::get().m_quadNode.clear();
}

void cCollisionManager::update(cApplication* application, cPlayer* player, cLevel* level, float time) {
	// Find position of the tile in the upper left corner

	if (level == NULL) {
		return;
	}

	if (m_secondCall == false) {
		m_secondCall = true;
		if (application->getIsWidescreen() == true) {
			m_tileXWidener = 3;
		} else {
			m_tileXWidener = 0;
		}

		/*cGlobals::get().m_quadNode.clearAll();
		cGlobals::get().m_quadNode.width = level->getNumColumns()*16;
		cGlobals::get().m_quadNode.height = level->getNumRows()*16;
		
		cGlobals::get().m_quadNode.setMaxLevel(level->getNumColumns()*16 / 320 + 1);
		cGlobals::get().m_quadNode.insert(player);*/

		/*for (k=0; k<level->m_enemies.size(); ++k) {
			cGlobals::get().m_quadNode.insert(level->m_enemies.at(k));
		}*/
		
	
		/*cGlobals::get().m_quadNode.x = 0;
		cGlobals::get().m_quadNode.y = 0;

		for(int h=0; h<level->getNumLayers(); ++h) {
			for(int i=0; i<level->getNumColumns(); ++i) {
				for(int j=0; j<level->getNumRows(); ++j) {					
					cGlobals::get().m_quadNode.insert( &level->m_tileObjects[h][ i+j*level->getNumColumns() ] );
				}
			}
		}*/
		
	}

	m_tileX = (int)(level->getPositionX()/16) - m_tileXWidener;

	if (m_tileX < 0 - m_tileXWidener) {
		m_tileX = 0 - m_tileXWidener;
	} else if (m_tileX > level->getNumColumns()-(int)(application->getViewWidth()/16) + m_tileXWidener) {
		m_tileX = level->getNumColumns()-(int)(application->getViewWidth()/16) + m_tileXWidener;
	}

	m_tileY = (int)(level->getPositionY()/16);

	if (m_tileY < 0) {
		m_tileY = 0;
	} else if (m_tileY > level->getNumRows()-application->getViewHeight()/16) {
		m_tileY = level->getNumRows()-application->getViewHeight()/16;
	}

	//std::cout << m_tileX << " " << m_tileY << std::endl;

	//std::cout << player->getLevelPositionX()+player->getWidth()/2/20 << std::endl;

	//m_tileObjects[z][x + y*m_numColumns].setLevelNode(x / 20 + (y / 15)*m_numColumns / 20);

	//if ((m_tileX*16) % 20 == 0) {
	//	//m_tileObjects[z][x + y*m_numColumns].setLevelNode(x/20 + (y/15)*m_numColumns/20);
	//	if ((m_tileY*16) % 15 == 0) {
	//		player->setLevelNode(m_tileX*16 / 20 + (m_tileY*16 / 15)*level->getNumColumns() / 20);
	//		std::cout << "LEVELNODE: " << player->getLevelNode() << std::endl;
	//	}
	//}

	//std::cout << player->getLevelPositionX() << " " << player->getLevelPositionY() << std::endl;

	
	/*player->setLevelNode((int)((player->getLevelPositionX()) / 320 + (player->getLevelPositionY() / 240)*level->getNumColumns() ));
	*/

	/*player->setLevelNode((int)((player->getLevelPositionX()) / 320)  + (int)((player->getLevelPositionY() / 240)*level->getNumColumns() / 20));
	std::cout << player->getLevelNode() << std::endl;*/

	//unsigned char node[4] = { 0,0,0,0};

	//x / 20 + (y / 15)*m_numColumns / 20
	//std::cout << ( m_tileY+7) << std::endl;
	m_playerNodes[0] = (m_tileX + 5 + m_tileXWidener) / 20 + ((m_tileY + 4) / 15)*level->getNumColumns() / 20;
	m_playerNodes[1] = (m_tileX + 5 + 10 + m_tileXWidener) / 20 + ((m_tileY + 4) / 15)*level->getNumColumns() / 20;
	m_playerNodes[2] = (m_tileX + 5 + m_tileXWidener) / 20 + ((m_tileY + 4 + 7) / 15)*level->getNumColumns() / 20;
	m_playerNodes[3] = (m_tileX + 5 + 10 + m_tileXWidener) / 20 + ((m_tileY + 4 + 7) / 15)*level->getNumColumns() / 20;
	/*m_playerNodes[0] = (int)((int)player->getLevelPositionX() - 64) / 320 + (int)(player->getLevelPositionY() - 64) / 240 * (level->getNumColumns() / 20);
	m_playerNodes[1] = (int)((int)player->getLevelPositionX() + 64) / 320 + (int)(player->getLevelPositionY() - 64) / 240 * (level->getNumColumns() / 20);
	m_playerNodes[2] = (int)((int)player->getLevelPositionX() - 64) / 320 + (int)(player->getLevelPositionY() + 64) / 240 * (level->getNumColumns() / 20);
	m_playerNodes[3] = (int)((int)player->getLevelPositionX() + 64) / 320 + (int)(player->getLevelPositionY() + 64) / 240 * (level->getNumColumns() / 20);
	*/
	//std::cout << (int)m_playerNodes[0] << " " << (int)m_playerNodes[1] << " " << (int)m_playerNodes[2] << " " << (int)m_playerNodes[3] << std::endl;
	//std::cout << level->getPositionX() << " " << level->getPositionY() << std::endl;
	//std::cout << player->getLevelPositionX() << " " << player->getLevelPositionY() << std::endl;
	//std::cout << (int)(level->getPositionX()) << " " << (int)(level->getPositionY()) << std::endl;

	// Player on tiles
	for (int h=0; h<level->getNumLayers(); ++h) {
		for (int j=0; j<(application->getViewHeight()/16)+1; ++j) {
			for (int i=0; i<(application->getViewWidth()/16)+m_tileXWidener*2+1; ++i) {
				if ((m_tileX + i) < level->getNumColumns() && (m_tileY + j) < level->getNumRows()) {
					
					if (level->m_tileObjects != NULL && level->m_tileObjects[h] != NULL) {						
						level->m_tileObjects[h][(m_tileX + i) + (m_tileY + j)*level->getNumColumns()].update(time);						
					}
					

					/*if( (player->getPositionX() > level->m_tileObjects[h][ (m_tileX+i)+(m_tileY+j)*level->getNumColumns() ].getPositionX() && player->getPositionX() - level->m_tileObjects[h][ (m_tileX+i)+(m_tileY+j)*level->getNumColumns() ].getPositionX() < 64
						||	player->getPositionX() < level->m_tileObjects[h][ (m_tileX+i)+(m_tileY+j)*level->getNumColumns() ].getPositionX() && level->m_tileObjects[h][ (m_tileX+i)+(m_tileY+j)*level->getNumColumns() ].getPositionX() - player->getPositionX() < 64)
						|| (player->getPositionY() > level->m_tileObjects[h][ (m_tileX+i)+(m_tileY+j)*level->getNumColumns() ].getPositionY() && player->getPositionY() - level->m_tileObjects[h][ (m_tileX+i)+(m_tileY+j)*level->getNumColumns() ].getPositionY() < 64
						||	player->getPositionY() < level->m_tileObjects[h][ (m_tileX+i)+(m_tileY+j)*level->getNumColumns() ].getPositionY() && level->m_tileObjects[h][ (m_tileX+i)+(m_tileY+j)*level->getNumColumns() ].getPositionY() - player->getPositionY() < 64) ) {						*/

					//if (level->m_tileObjects[h][(m_tileX + i) + (m_tileY + j)*level->getNumColumns()].getLevelNode() == m_tileX)
					/*for (unsigned short n = 0; n < 4; ++n) {
						if (node[n] == level->m_tileObjects[h][(m_tileX + i) + (m_tileY + j)*level->getNumColumns()].getLevelNode()) {
							player->checkCollisionX(&level->m_tileObjects[h][(m_tileX + i) + (m_tileY + j)*level->getNumColumns()]);
							player->checkCollisionY(&level->m_tileObjects[h][(m_tileX + i) + (m_tileY + j)*level->getNumColumns()]);
						}
					}*/
					
					// Skip collision check if not in the same node as tile
					if (m_playerNodes[0] == level->m_tileObjects[h][(m_tileX + i) + (m_tileY + j)*level->getNumColumns()].getLevelNode() ||
						m_playerNodes[1] == level->m_tileObjects[h][(m_tileX + i) + (m_tileY + j)*level->getNumColumns()].getLevelNode() ||
						m_playerNodes[2] == level->m_tileObjects[h][(m_tileX + i) + (m_tileY + j)*level->getNumColumns()].getLevelNode() ||
						m_playerNodes[3] == level->m_tileObjects[h][(m_tileX + i) + (m_tileY + j)*level->getNumColumns()].getLevelNode()) {
						player->checkCollisionX(&level->m_tileObjects[h][(m_tileX + i) + (m_tileY + j)*level->getNumColumns()]);
						player->checkCollisionY(&level->m_tileObjects[h][(m_tileX + i) + (m_tileY + j)*level->getNumColumns()]);
					}
					
					for (unsigned short m = 0; m < level->m_tileObjects[h][(m_tileX + i) + (m_tileY + j)*level->getNumColumns()].m_projectiles.size(); ++m) {
						level->m_tileObjects[h][(m_tileX + i) + (m_tileY + j)*level->getNumColumns()].m_projectiles.at(m)->checkCollisionX(player);
						level->m_tileObjects[h][(m_tileX + i) + (m_tileY + j)*level->getNumColumns()].m_projectiles.at(m)->checkCollisionY(player);

						//level->m_tileObjects[h][(m_tileX + i) + (m_tileY + j)*level->getNumColumns()].checkCollisionX(level->m_tileObjects[h][(m_tileX + i) + (m_tileY + j)*level->getNumColumns()].m_projectiles.at(m));
						//level->m_tileObjects[h][(m_tileX + i) + (m_tileY + j)*level->getNumColumns()].checkCollisionY(level->m_tileObjects[h][(m_tileX + i) + (m_tileY + j)*level->getNumColumns()].m_projectiles.at(m));

						//level->m_tileObjects[h][(m_tileX + i) + (m_tileY + j)*level->getNumColumns()].m_projectiles.at(m)->checkCollisionY(&level->m_tileObjects[h][(m_tileX + i) + (m_tileY + j)*level->getNumColumns()]);
					}

					for (int l=0; l<player->m_projectiles.size(); ++l) {
						/*if( (player->m_projectiles.at(l)->getPositionX() > level->m_tileObjects[h][ (m_tileX+i)+(m_tileY+j)*level->getNumColumns() ].getPositionX() && player->m_projectiles.at(l)->getPositionX() - level->m_tileObjects[h][ (m_tileX+i)+(m_tileY+j)*level->getNumColumns() ].getPositionX() < 16
						||	player->m_projectiles.at(l)->getPositionX() < level->m_tileObjects[h][ (m_tileX+i)+(m_tileY+j)*level->getNumColumns() ].getPositionX() && level->m_tileObjects[h][ (m_tileX+i)+(m_tileY+j)*level->getNumColumns() ].getPositionX() - player->m_projectiles.at(l)->getPositionX() < 16)
						|| (player->m_projectiles.at(l)->getPositionY() > level->m_tileObjects[h][ (m_tileX+i)+(m_tileY+j)*level->getNumColumns() ].getPositionY() && player->m_projectiles.at(l)->getPositionY() - level->m_tileObjects[h][ (m_tileX+i)+(m_tileY+j)*level->getNumColumns() ].getPositionY() < 16
						||	player->m_projectiles.at(l)->getPositionY() < level->m_tileObjects[h][ (m_tileX+i)+(m_tileY+j)*level->getNumColumns() ].getPositionY() && level->m_tileObjects[h][ (m_tileX+i)+(m_tileY+j)*level->getNumColumns() ].getPositionY() - player->m_projectiles.at(l)->getPositionY() < 16) ) {*/
						player->m_projectiles.at(l)->checkCollisionX(&level->m_tileObjects[h][ (m_tileX+i)+(m_tileY+j)*level->getNumColumns() ]);
						player->m_projectiles.at(l)->checkCollisionY(&level->m_tileObjects[h][ (m_tileX+i)+(m_tileY+j)*level->getNumColumns() ]);
						//}
					}					
				}

			}
		}
	}
	// Enemies on tiles
	for (unsigned char h=0; h<level->getNumLayers(); ++h) {
		for (unsigned short j=0; j<(int)(application->getViewHeight()/16); ++j) {
			for (unsigned short i=0; i<(int)(application->getViewWidth()/16); ++i) {
				// Do collision detection for enemies on tiles
				for (unsigned short k=0; k<level->m_enemies.size(); ++k) {
					m_oldEnemyTileX = m_enemyTileX;
					m_oldEnemyTileY = m_enemyTileY;

					m_enemyTileX = (int)((level->m_enemies.at(k)->getLevelPositionX()-160)/16);
					m_enemyTileY = (int)((level->m_enemies.at(k)->getLevelPositionY()-120)/16);

					if (m_enemyTileX < 0) {
						m_enemyTileX = 0;
					} else if (m_enemyTileX > level->getNumColumns()-application->getViewWidth()/16) {
						m_enemyTileX = level->getNumColumns()-application->getViewWidth()/16;
					}
					if (m_enemyTileY < 0) {
						m_enemyTileY = 0;
					} else if (m_enemyTileY > level->getNumRows()-application->getViewHeight()/16) {
						m_enemyTileY = level->getNumRows()-application->getViewHeight()/16;
					}
					
					/*if(m_enemyTileY != m_oldEnemyTileY) {
						std::cout << m_enemyTileY << std::endl;
					}*/
					if (level->m_enemies.at(k)->getDoCollisionWorld() == true) {
						/*if( (level->m_enemies.at(k)->getPositionX() > level->m_tileObjects[h][ (m_enemyTileX+i)+(m_enemyTileY+j)*level->getNumColumns() ].getPositionX() && level->m_enemies.at(k)->getPositionX() - level->m_tileObjects[h][ (m_enemyTileX+i)+(m_enemyTileY+j)*level->getNumColumns() ].getPositionX() < 64
							||
							level->m_enemies.at(k)->getPositionX() < level->m_tileObjects[h][ (m_enemyTileX+i)+(m_enemyTileY+j)*level->getNumColumns() ].getPositionX() && level->m_tileObjects[h][ (m_enemyTileX+i)+(m_enemyTileY+j)*level->getNumColumns() ].getPositionX() - level->m_enemies.at(k)->getPositionX() < 64)
						|| 
						(level->m_enemies.at(k)->getPositionY() > level->m_tileObjects[h][ (m_enemyTileX+i)+(m_enemyTileY+j)*level->getNumColumns() ].getPositionY() && level->m_enemies.at(k)->getPositionY() - level->m_tileObjects[h][ (m_enemyTileX+i)+(m_enemyTileY+j)*level->getNumColumns() ].getPositionY() < 64
							||	level->m_enemies.at(k)->getPositionY() < level->m_tileObjects[h][ (m_enemyTileX+i)+(m_enemyTileY+j)*level->getNumColumns() ].getPositionY() && level->m_tileObjects[h][ (m_enemyTileX+i)+(m_enemyTileY+j)*level->getNumColumns() ].getPositionY() - level->m_enemies.at(k)->getPositionY() < 64)
						) {		*/	
							level->m_enemies.at(k)->checkCollisionX(&level->m_tileObjects[h][ (m_enemyTileX+i) + (m_enemyTileY+j) * level->getNumColumns() ]);
							level->m_enemies.at(k)->checkCollisionY(&level->m_tileObjects[h][ (m_enemyTileX+i) + (m_enemyTileY+j) * level->getNumColumns() ]);
						//}
					}
				}				
			}
		}
	}
	//Player on enemies
	for (unsigned short k = 0; k < level->m_enemies.size(); ++k) {
		//cGlobals::get().m_quadNode.insert(level->m_enemies.at(k));

		for (unsigned short i = 0; i < level->m_enemies.size(); ++i) {
			level->m_enemies.at(k)->checkCollisionX(level->m_enemies.at(i));
			level->m_enemies.at(k)->checkCollisionY(level->m_enemies.at(i));
		}

		if ((player->getPositionX() > level->m_enemies.at(k)->getPositionX() && player->getPositionX() - level->m_enemies.at(k)->getPositionX() < 256 || player->getPositionX() < level->m_enemies.at(k)->getPositionX() && level->m_enemies.at(k)->getPositionX() - player->getPositionX() < 256) || (player->getPositionY() > level->m_enemies.at(k)->getPositionY() && player->getPositionY() - level->m_enemies.at(k)->getPositionY() < 256 || player->getPositionY() < level->m_enemies.at(k)->getPositionY() && level->m_enemies.at(k)->getPositionY() - player->getPositionY() < 256)) {
			player->checkCollisionEnemyX(level->m_enemies.at(k));
			player->checkCollisionEnemyY(level->m_enemies.at(k));

			for (unsigned short l = 0; l < player->m_projectiles.size(); ++l) {
				player->m_projectiles.at(l)->checkCollisionX(level->m_enemies.at(k));
				player->m_projectiles.at(l)->checkCollisionY(level->m_enemies.at(k));
			}

			for (unsigned short m = 0; m < level->m_enemies.at(k)->m_projectiles.size(); ++m) {
				level->m_enemies.at(k)->m_projectiles.at(m)->checkCollisionX(player);
				level->m_enemies.at(k)->m_projectiles.at(m)->checkCollisionY(player);
			}
		}
	}

	//cGlobals::get().m_quadNode.clearAll();
	//cGlobals::get().m_quadNode.width = level->getNumColumns()*16;
	//cGlobals::get().m_quadNode.height = level->getNumRows()*16;
	//	
	//cGlobals::get().m_quadNode.setMaxLevel(level->getNumColumns()*16 / 320 + 1);
	//	
	////cGlobals::get().m_quadNode.x = level->getPositionX();
	////cGlobals::get().m_quadNode.y = level->getPositionY();

	//cGlobals::get().m_quadNode.insert(player);	
	
	/*for (k=0; k<level->m_enemies.size(); ++k) {
		cGlobals::get().m_quadNode.insert(level->m_enemies.at(k));
	}*/		

	//std::cout << player->getLevelPositionX() << " " << player->getLevelPositionY() << std::endl;

	//std::cout << cGlobals::get().m_quadNode.getX() << std::endl;

	//std::cout << level->getPositionX() << " " << level->getPositionY() << std::endl;
	
	//std::cout << cGlobals::get().m_quadNode.getObjectsAt( player->getLevelPositionX(), player->getLevelPositionY() ).size() << std::endl;

	//std::cout << cGlobals::get().m_quadNode.getNodeAt( player->getLevelPositionX(), player->getLevelPositionY() ).getX() << std::endl;
	//std::cout << cGlobals::get().m_quadNode.getNodeAt( level->getPositionX(), level->getPositionY() ).getX() << std::endl;

	//cGlobals::get().m_quadNode.x += 0.5f;

	/*for(i=0; i<cGlobals::get().m_quadNode.getNodeAt( player->getLevelPositionX()-player->getWidth(), player->getLevelPositionY() ).objects.size(); ++i) {
		player->checkCollisionX( cGlobals::get().m_quadNode.getNodeAt( player->getLevelPositionX()-player->getWidth(), player->getLevelPositionY() ).objects.at(i) );
		player->checkCollisionY( cGlobals::get().m_quadNode.getNodeAt( player->getLevelPositionX()-player->getWidth(), player->getLevelPositionY() ).objects.at(i) );
	}

	for(i=0; i<cGlobals::get().m_quadNode.getNodeAt( player->getLevelPositionX(), player->getLevelPositionY() ).objects.size(); ++i) {
		player->checkCollisionX( cGlobals::get().m_quadNode.getNodeAt( player->getLevelPositionX(), player->getLevelPositionY() ).objects.at(i) );
		player->checkCollisionY( cGlobals::get().m_quadNode.getNodeAt( player->getLevelPositionX(), player->getLevelPositionY() ).objects.at(i) );
	}
	for(i=0; i<cGlobals::get().m_quadNode.getNodeAt( player->getLevelPositionX()+player->getWidth(), player->getLevelPositionY() ).objects.size(); ++i) {
		player->checkCollisionX( cGlobals::get().m_quadNode.getNodeAt( player->getLevelPositionX()+player->getWidth(), player->getLevelPositionY() ).objects.at(i) );
		player->checkCollisionY( cGlobals::get().m_quadNode.getNodeAt( player->getLevelPositionX()+player->getWidth(), player->getLevelPositionY() ).objects.at(i) );
	}*/


	//for(i=0; i<cGlobals::get().m_quadNode.getObjectsAt( player->getLevelPositionX(), player->getLevelPositionY() ).size(); ++i) {
	//	//player->checkCollisionX(cGlobals::get().m_quadNode.getObjectsAt( player->getLevelPositionX(), player->getLevelPositionY() ).at(i) );
	//	//player->checkCollisionX(cGlobals::get().m_quadNode.getObjectsAt( player->getLevelPositionX()+player->getWidth()/2, player->getLevelPositionY() ).at(i) );

	//	//player->checkCollisionY(cGlobals::get().m_quadNode.getObjectsAt( player->getLevelPositionX(), player->getLevelPositionY() ).at(i) );

	//	for(unsigned int l=1; l<player->m_projectiles.size(); ++l) {
	//		player->m_projectiles.at(l)->checkCollisionX( cGlobals::get().m_quadNode.getObjectsAt( player->getLevelPositionX(), player->getLevelPositionY() ).at(i) );
	//		player->m_projectiles.at(l)->checkCollisionY( cGlobals::get().m_quadNode.getObjectsAt( player->getLevelPositionX(), player->getLevelPositionY() ).at(i) );
	//	}

	//	/*for(int k=0; k< level->m_enemies.size(); ++k) {
	//		level->m_enemies.at(k)->checkCollisionX( cGlobals::get().m_quadNode.getObjectsAt( level->m_enemies.at(k)->getLevelPositionX(), level->m_enemies.at(k)->getLevelPositionY()+32 ).at(i) );
	//		level->m_enemies.at(k)->checkCollisionY( cGlobals::get().m_quadNode.getObjectsAt( level->m_enemies.at(k)->getLevelPositionX(), level->m_enemies.at(k)->getLevelPositionY()+32 ).at(i) );
	//	}*/
	//}
	/*for(int i=0; i<cGlobals::get().m_quadNode.getObjectsAt( player->getLevelPositionX()-64, player->getLevelPositionY()-32 ).size(); ++i) {	
		player->checkCollisionX(cGlobals::get().m_quadNode.getObjectsAt( player->getLevelPositionX()-64, player->getLevelPositionY()-32 ).at(i) );
		player->checkCollisionY(cGlobals::get().m_quadNode.getObjectsAt( player->getLevelPositionX()-64, player->getLevelPositionY()-32 ).at(i) );
	}*/

	/*for(int i=0; i<cGlobals::get().m_quadNode.getObjectsAt( player->getPositionX(), player->getPositionY() ).size(); ++i) {	
		player->checkCollisionX(cGlobals::get().m_quadNode.getObjectsAt( player->getPositionX(), player->getPositionY() ).at(i) );
		player->checkCollisionY(cGlobals::get().m_quadNode.getObjectsAt( player->getPositionX(), player->getPositionY() ).at(i) );
	}*/

		
		/*for(int h=0; h<level->getNumLayers(); ++h) {
			for(int i=0; i<level->getNumColumns(); ++i) {
				for(int j=0; j<level->getNumRows(); ++j) {
					cGlobals::get().m_quadNode.insert( &level->m_tileObjects[h][ i+j*level->getNumColumns() ] );
				}
			}
		}*/


	//for(int h=0; h<level->getNumLayers(); ++h) {
	//	for(int i=0; i<level->getNumColumns(); ++i) {
	//		for(int j=0; j<level->getNumRows(); ++j) {

	//			//cGlobals::get().m_quadNode.insert( &level->m_tileObjects[h][ i+j*level->getNumColumns() ] );
	//			
	//			/*player->checkCollisionX( &level->m_tileObjects[h][ i+j*level->getNumColumns() ] );
	//			player->checkCollisionY( &level->m_tileObjects[h][ i+j*level->getNumColumns() ] );

	//			for(int l=1; l<player->m_projectiles.size(); ++l) {						
	//				player->m_projectiles.at(l)->checkCollisionX(&level->m_tileObjects[h][ i+j*level->getNumColumns() ]);
	//				player->m_projectiles.at(l)->checkCollisionY(&level->m_tileObjects[h][ i+j*level->getNumColumns() ]);
	//			}*/

	//			for (int k=0; k<level->m_enemies.size(); ++k) {
	//			//	cGlobals::get().m_quadNode.insert(level->m_enemies.at(k))
	//				
	//				level->m_enemies.at(k)->checkCollisionX( &level->m_tileObjects[h][ i+j*level->getNumColumns() ] );
	//				level->m_enemies.at(k)->checkCollisionY( &level->m_tileObjects[h][ i+j*level->getNumColumns() ] );

	//				player->checkCollisionEnemyX(level->m_enemies.at(k));
	//				player->checkCollisionEnemyY(level->m_enemies.at(k));

	//				for(int l=1; l<player->m_projectiles.size(); ++l) {
	//					player->m_projectiles.at(l)->checkCollisionX(level->m_enemies.at(k));
	//					player->m_projectiles.at(l)->checkCollisionY(level->m_enemies.at(k));
	//				}

	//				for(int m=1; m<level->m_enemies.at(k)->m_projectiles.size(); ++m) {
	//					level->m_enemies.at(k)->m_projectiles.at(m)->checkCollisionX(player);
	//					level->m_enemies.at(k)->m_projectiles.at(m)->checkCollisionY(player);
	//				}

	//				//if( (player->getPositionX() > level->m_enemies.at(k)->getPositionX() && player->getPositionX() - level->m_enemies.at(k)->getPositionX() < 256 ||	player->getPositionX() < level->m_enemies.at(k)->getPositionX() && level->m_enemies.at(k)->getPositionX() - player->getPositionX() < 256) || (player->getPositionY() > level->m_enemies.at(k)->getPositionY() && player->getPositionY() - level->m_enemies.at(k)->getPositionY() < 256 ||	player->getPositionY() < level->m_enemies.at(k)->getPositionY() && level->m_enemies.at(k)->getPositionY() - player->getPositionY() < 256) ) {
	//					/*player->checkCollisionEnemyX(level->m_enemies.at(k));
	//					player->checkCollisionEnemyY(level->m_enemies.at(k));
	//					
	//					for(l=1; l<player->m_projectiles.size(); ++l) {
	//						player->m_projectiles.at(l)->checkCollisionX(level->m_enemies.at(k));
	//						player->m_projectiles.at(l)->checkCollisionY(level->m_enemies.at(k));
	//					}

	//					for(m=1; m<level->m_enemies.at(k)->m_projectiles.size(); ++m) {
	//						level->m_enemies.at(k)->m_projectiles.at(m)->checkCollisionX(player);
	//						level->m_enemies.at(k)->m_projectiles.at(m)->checkCollisionY(player);
	//					}*/
	//				//}
	//			}



	//		}
	//	}
	//}

	

	/*cGlobals::get().m_quadNode.clearAll();

	for(int h=0; h<level->getNumLayers(); ++h) {
		for(int i=0; i<level->getNumColumns(); ++i) {
			for(int j=0; j<level->getNumRows(); ++j) {
				cGlobals::get().m_quadNode.insert( &level->m_tileObjects[h][ i+j*level->getNumColumns() ] );
			}
		}
	}*/


	//std::cout << player->getLevelPositionX() << " " << player->getLevelPositionY() << std::endl;

	/*for(int k=0; k< cGlobals::get().m_quadNode.getObjectsAt( player->getLevelPositionX(), player->getLevelPositionY() ).size(); ++k) {
		player->checkCollisionX( cGlobals::get().m_quadNode.getObjectsAt( player->getLevelPositionX(), player->getLevelPositionY() ).at(k) );
		player->checkCollisionY( cGlobals::get().m_quadNode.getObjectsAt( player->getLevelPositionX(), player->getLevelPositionY() ).at(k) );
	}*/

	/*std::cout << level->getPositionX()+application->getWindowWidth()/2 << " " << level->getPositionY()+application->getWindowHeight()/2 << std::endl;
	
	for(int k=0; k< cGlobals::get().m_quadNode.getObjectsAt( level->getPositionX(), level->getPositionY() ).size(); ++k) {		
		player->checkCollisionX( cGlobals::get().m_quadNode.getObjectsAt( level->getPositionX()+application->getWindowWidth()/2, level->getPositionY()+application->getWindowHeight()/2 ).at(k) );
		player->checkCollisionY( cGlobals::get().m_quadNode.getObjectsAt( level->getPositionX()+application->getWindowWidth()/2, level->getPositionY()+application->getWindowHeight()/2 ).at(k) );
	}*/

	//cGlobals::get().m_quadNode.clear();

	// Box objects on tiles
	for (unsigned char h=0; h<level->getNumLayers(); ++h) {
		for (unsigned short j=0; j<(int)(application->getViewHeight()/16); ++j) {
			for (unsigned short i=0; i<(int)(application->getViewWidth()/16); ++i) {
				// Do collision detection for enemies on tiles
				for (unsigned short k=0; k<level->m_boxObjects.size(); ++k) {
					m_oldBoxTileX = m_boxTileX;
					m_oldBoxTileY = m_boxTileY;

					m_boxTileX = (level->m_boxObjects.at(k)->getLevelPositionX()/16);
					m_boxTileY = (level->m_boxObjects.at(k)->getLevelPositionY()/16);

					if (m_boxTileX < 0) {
						m_boxTileX = 0;
					} else if (m_boxTileX > level->getNumColumns()-application->getViewWidth()/16) {
						m_boxTileX = level->getNumColumns()-application->getViewWidth()/16;
					}
					if (m_boxTileY < 0) {
						m_boxTileY = 0;
					} else if (m_boxTileY > level->getNumRows()-application->getViewHeight()/16) {
						m_boxTileY = level->getNumRows()-application->getViewHeight()/16;
					}
					
					//std::cout << m_boxTileX << " " << m_boxTileY << std::endl;

					/*if( (level->m_enemies.at(k)->getPositionX() > level->m_tileObjects[h][ (m_enemyTileX+i)+(m_enemyTileY+j)*level->getNumColumns() ].getPositionX() && level->m_enemies.at(k)->getPositionX() - level->m_tileObjects[h][ (m_enemyTileX+i)+(m_enemyTileY+j)*level->getNumColumns() ].getPositionX() < 64
						||
						level->m_enemies.at(k)->getPositionX() < level->m_tileObjects[h][ (m_enemyTileX+i)+(m_enemyTileY+j)*level->getNumColumns() ].getPositionX() && level->m_tileObjects[h][ (m_enemyTileX+i)+(m_enemyTileY+j)*level->getNumColumns() ].getPositionX() - level->m_enemies.at(k)->getPositionX() < 64)
					|| 
					(level->m_enemies.at(k)->getPositionY() > level->m_tileObjects[h][ (m_enemyTileX+i)+(m_enemyTileY+j)*level->getNumColumns() ].getPositionY() && level->m_enemies.at(k)->getPositionY() - level->m_tileObjects[h][ (m_enemyTileX+i)+(m_enemyTileY+j)*level->getNumColumns() ].getPositionY() < 64
						||	level->m_enemies.at(k)->getPositionY() < level->m_tileObjects[h][ (m_enemyTileX+i)+(m_enemyTileY+j)*level->getNumColumns() ].getPositionY() && level->m_tileObjects[h][ (m_enemyTileX+i)+(m_enemyTileY+j)*level->getNumColumns() ].getPositionY() - level->m_enemies.at(k)->getPositionY() < 64)
					) {		*/	
						level->m_boxObjects.at(k)->checkCollisionX(&level->m_tileObjects[h][ (m_boxTileX+i) + (m_boxTileY+j) * level->getNumColumns() ]);
						level->m_boxObjects.at(k)->checkCollisionY(&level->m_tileObjects[h][ (m_boxTileX+i) + (m_boxTileY+j) * level->getNumColumns() ]);
					//}					
				}				
			}
		}
	}





	// Player on box objects
	for (unsigned short k=0; k<level->m_boxObjects.size(); ++k) {
		for (unsigned short i=0; i<level->m_boxObjects.size(); ++i) {
			level->m_boxObjects.at(i)->checkCollisionX(level->m_boxObjects.at(k));
			level->m_boxObjects.at(i)->checkCollisionY(level->m_boxObjects.at(k));
		}

		if( (player->getPositionX() > level->m_boxObjects.at(k)->getPositionX() && player->getPositionX() - level->m_boxObjects.at(k)->getPositionX() < 256 ||	player->getPositionX() < level->m_boxObjects.at(k)->getPositionX() && level->m_boxObjects.at(k)->getPositionX() - player->getPositionX() < 256) || (player->getPositionY() > level->m_boxObjects.at(k)->getPositionY() && player->getPositionY() - level->m_boxObjects.at(k)->getPositionY() < 256 ||	player->getPositionY() < level->m_boxObjects.at(k)->getPositionY() && level->m_boxObjects.at(k)->getPositionY() - player->getPositionY() < 256) ) {
			player->checkCollisionX(level->m_boxObjects.at(k));
			player->checkCollisionY(level->m_boxObjects.at(k));
		}
		for (unsigned short l=0; l<player->m_projectiles.size(); ++l) {
			player->m_projectiles.at(l)->checkCollisionX(level->m_boxObjects.at(k));
			player->m_projectiles.at(l)->checkCollisionY(level->m_boxObjects.at(k));
		}
	}
}