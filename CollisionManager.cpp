#include "CollisionManager.h"
#include <algorithm>

std::vector<cLevelNode> cCollisionManager::m_playerNodes;
std::vector<cLevelNode> cCollisionManager::m_entityNodes;
std::vector<cLevelNode> cCollisionManager::m_particleNodes;

cCollisionManager::~cCollisionManager() {	
	m_playerNodes.clear();
	m_entityNodes.clear();
	m_particleNodes.clear();
}

void cCollisionManager::checkPlayer(cApp* app, cLevel* level, cPlayer* player, float time) {
	if (level == nullptr || player == nullptr || level->getTileObjects() == nullptr) {
		return;
	}
	float edgeLeft = -(float)player->getWidth();
	float edgeRight = (float)level->getNumColumns() * 16;
	float edgeUp = -(float)player->getHeight();
	float edgeDown = (float)level->getNumRows() * 16;
	if (player->getLevelX() <= edgeLeft|| player->getLevelX() >= edgeRight ||
		player->getLevelY() <= edgeUp || player->getLevelY() >= edgeDown) {
		return;
	}

	m_playerNodes.clear();

	int upperTileX = (int)(player->getLevelX() / 16);
	int upperTileY = (int)(player->getLevelY() / 16);

	// Extra tiles from object boundaries to check in each direction
	unsigned char extraTilesX = 0;
	unsigned char extraTilesY = 1;

	if (upperTileX < extraTilesX) {
		upperTileX = extraTilesX;
	}
	if (upperTileX > level->getNumColumns() - 5 - extraTilesX) {
		upperTileX = level->getNumColumns() - 5 - extraTilesX;
	}
	if (upperTileY < extraTilesY) {
		upperTileY = extraTilesY;
	}
	if (upperTileY > level->getNumRows() - 5 - extraTilesY) {
		upperTileY = level->getNumRows() - 5 - extraTilesY;
	}

	unsigned short tileWidth = (int)(player->getWidth() / 16);
	unsigned short tileHeight = (int)(player->getHeight() / 16);
	unsigned short tileSubtractLeft = (int)(player->getSubtractLeft() / 16) - extraTilesX;
	unsigned short tileSubtractRight = (int)(player->getSubtractRight() / 16) + extraTilesX;
	unsigned short tileSubtractUp = (int)(player->getSubtractUp() / 16) - extraTilesY;
	unsigned short tileSubtractDown = (int)(player->getSubtractDown() / 16) + extraTilesY;

	//std::cout << "cCollisionManager " << (int)(player->getSubtractUp() / 16) << " " << tileX << " " << tileY << "  " << tileSubtractLeft << " " << tileSubtractRight << " " << tileSubtractUp << " " << tileSubtractDown << "\n";
	/*cLevelNode node0(2, 0, 5);
	cLevelNode node1(1, 1, 5);
	if (node0 == node1) {
		std::cout << "cCollisionManager " << node0.get() << " " << node1.get() << "\n";
	}*/

	unsigned short columns = (int)(level->getNumColumns() / 5);
	cLevelNode currentNode(0, 0, columns);
	cLevelNode previousNode(0, 0, columns);

	//m_playerNodes.clear();
	// Top left	
	currentNode.setX((int)((upperTileX + tileSubtractLeft) / 5));
	currentNode.setY((int)((upperTileY / 5)));
	m_playerNodes.push_back(currentNode);
	previousNode = currentNode;
	//Top center
	currentNode.setX((int)((upperTileX + tileWidth / 2) / 5));
	currentNode.setY((int)((upperTileY / 5)));
	if (currentNode != previousNode) {
		m_playerNodes.push_back(currentNode);
		previousNode = currentNode;
	}
	// Top right
	currentNode.setX((int)((upperTileX + tileWidth - tileSubtractRight) / 5));
	currentNode.setY((int)((upperTileY / 5)));
	if (currentNode != previousNode) {
		m_playerNodes.push_back(currentNode);
		previousNode = currentNode;
	}
	// Center right
	//currentNode.setX((int)((tileX + tileWidth - tileSubtractRight + 4) / 5));
	//currentNode.setY((int)(((tileY + tileHeight - 0) / 5)));
	//if (currentNode != previousNode) {
	//	m_playerNodes.push_back(currentNode);
	//	previousNode = currentNode;
	//}
	// Center
	currentNode.setX((int)((upperTileX + tileWidth / 2) / 5));
	currentNode.setY((int)(((upperTileY + tileHeight / 2) / 5)));
	if (currentNode != previousNode) {
		m_playerNodes.push_back(currentNode);
		previousNode = currentNode;
	}
	// Center left
	//currentNode.setX((int)((tileX + tileSubtractLeft - 4) / 5));					
	//currentNode.setY((int)(((tileY + tileHeight - 0) / 5)));
	//if (currentNode != previousNode) {
	//	m_playerNodes.push_back(currentNode);
//	previousNode = currentNode;
//}
// Bottom left
currentNode.setX((int)((upperTileX + tileSubtractLeft) / 5));
currentNode.setY((int)(((upperTileY + tileHeight) / 5)));
if (currentNode != previousNode) {
	m_playerNodes.push_back(currentNode);
	previousNode = currentNode;
}
// Bottom center
currentNode.setX((int)((upperTileX + tileWidth / 2) / 5));
currentNode.setY((int)(((upperTileY + tileHeight + 0) / 5)));
if (currentNode != previousNode) {
	m_playerNodes.push_back(currentNode);
	previousNode = currentNode;
}
// Bottom right
currentNode.setX((int)((upperTileX + tileWidth - tileSubtractRight) / 5));
currentNode.setY((int)(((upperTileY + tileHeight) / 5)));
if (currentNode != previousNode) {
	m_playerNodes.push_back(currentNode);
	previousNode = currentNode;
}
//std::cout << "cCollisionManager " << m_playerNodes.size() << " ";
// Remove duplicates
//std::sort(m_playerNodes.begin(), m_playerNodes.end());
m_playerNodes.erase(std::unique(m_playerNodes.begin(), m_playerNodes.end()), m_playerNodes.end());

//std::cout << m_playerNodes.size() << "\n";

/*if (!player->getIsInMap()) {
	std::cout << "cCollisionManager ";
	for (auto it = m_playerNodes.begin(); it != m_playerNodes.end(); ++it) {
		std::cout << (*it).get() << " ";
	}
	std::cout << "\n";
}*/
//m_tileObjects[z][x + y * m_numColumns].setLevelNode(x / 10 + (y / 5) * m_numColumns / 10);

for (unsigned short a = 0; a < m_playerNodes.size(); ++a) {
	//unsigned short numNodeChecks = 0;
	//for (auto it=m_levelNodes.begin(); it != m_levelNodes.end(); ++it) {
		//std::cout << (*it)->get() << " ";
	for (int y = 0; y < 5; ++y) {
		for (int x = 0; x < 5; ++x) {
			for (int z = 0; z < level->getNumLayers(); ++z) {

				unsigned short n = x + (m_playerNodes.at(a).getX() * 5) + (y + (m_playerNodes.at(a).getY() * 5)) * level->getNumColumns();

				unsigned short tileX = x + (m_playerNodes.at(a).getX() * 5);
				unsigned short tileY = y + (m_playerNodes.at(a).getY() * 5);



				//unsigned short n = x + ((*it)->getX() * 20) + (y + ((*it)->getY() * 15)) * level->getNumColumns();

				//if (level->m_tileObjects != nullptr && level->m_tileObjects[z] != nullptr) {
				//	// Update here if not a coin or brick, they're updated every frame
				//	//if (!level->m_tileObjects[z][n].getDoUpdateEveryFrame()/* && a == 0*/) {
				//		level->m_tileObjects[z][n].update(time);
				//	//}
				//}

				if (level->getTileObject(z, tileX, tileY)->getIsSolidPlayerY() && player->getIsSolidLevelY() && player->collisionCheckY(level->getTileObject(z, tileX, tileY))) {
					player->collisionReactionY(level->getTileObject(z, tileX, tileY));
				} else if (level->getTileObject(z, tileX, tileY)->getIsSolidPlayerX() && player->getIsSolidLevelX() && player->collisionCheckX(level->getTileObject(z, tileX, tileY))) {
					player->collisionReactionX(level->getTileObject(z, tileX, tileY));
				}

				//}
				/*for (auto it = player->m_particles.begin(); it != player->m_particles.end(); ++it) {
					(*it)->collisionCheckX(&level->m_tileObjects[z][n]);
					(*it)->collisionCheckY(&level->m_tileObjects[z][n]);
				}*/

				/*for (auto it = level->m_tileObjects[z][n].m_particles.begin(); it != level->m_tileObjects[z][n].m_particles.end(); ++it) {
					std::cout << (*it)->getType() << " "  << m_playerNodes.at(a)->getX() << " " << m_playerNodes.at(a)->getY() << "\n";
					(*it)->collisionCheckX(&level->m_tileObjects[z][n]);
					(*it)->collisionCheckY(&level->m_tileObjects[z][n]);
				}*/
			}
		}
	}
	//++numNodeChecks;
}
//std::cout << "\n";
//std::cout << m_playerNodes.size() << "\n";
}

void cCollisionManager::checkEntities(cApp* app, cLevel* level, cPlayer* player, float time) {
	if (level == nullptr || level->getTileObjects() == nullptr) {
		return;
	}
	m_entityNodes.clear();
	for (auto it = level->getEntities()->begin(); it != level->getEntities()->end(); ++it) {
		if (*it == nullptr) {
			return;
		}

		float edgeLeft = -(float)(*it)->getWidth();
		float edgeRight = (float)level->getNumColumns() * 16;
		float edgeUp = -(float)(*it)->getHeight();
		float edgeDown = (float)level->getNumRows() * 16;
	
		if ((*it)->getLevelX() <= edgeLeft || (*it)->getLevelX() >= edgeRight ||
			(*it)->getLevelY() <= edgeUp || (*it)->getLevelY() >= edgeDown) {
			continue;
		}


		// Entity on other entities
		for (auto it2 = level->getEntities()->begin(); it2 != level->getEntities()->end(); ++it2) {
			if (it2 != it && *it != nullptr) {
				//std::cout << (*it2)->getType() << "\n";
				if ((*it)->getIsSolidEntityY() && (*it2)->getIsSolidEntityY() && (*it)->collisionCheckY((*it2))) {
					(*it)->collisionReactionY((*it2));
				} else 	if ((*it)->getIsSolidEntityX() && (*it2)->getIsSolidEntityX() && (*it)->collisionCheckX((*it2))) {
					(*it)->collisionReactionX((*it2));
				}
			}
		}

		int upperTileX = (int)((*it)->getLevelX() / 16);
		int upperTileY = (int)((*it)->getLevelY() / 16);

		if (upperTileX < 0) {
			upperTileX = 0;
		}
		if (upperTileX > level->getNumColumns() - 5) {
			upperTileX = level->getNumColumns() - 5;
		}

		if (upperTileY < 0) {
			upperTileY = 0;
		}
		if (upperTileY > level->getNumRows() - 5) {
			upperTileY = level->getNumRows() - 5;
		}

		//std::cout << "cCollisionManager " << tileX << " " << tileY << "\n";

		int tileWidth = (int)((*it)->getWidth() / 16);
		int tileHeight = (int)(*it)->getHeight() / 16;

		int tileSubtractLeft = (*it)->getSubtractLeft() / 16;
		int tileSubtractRight = (*it)->getSubtractRight() / 16;
		int tileSubtractUp = (*it)->getSubtractUp() / 16;
		int tileSubtractDown = (*it)->getSubtractDown() / 16;

		//std::cout << "cCollisionManager " << tileSubtractLeft << " " << tileSubtractUp << "\n";
		unsigned short columns = level->getNumColumns() / 5;
		cLevelNode currentNode(0, 0, columns);
		cLevelNode previousNode(0, 0, columns);

		m_entityNodes.clear();
		//m_playerNodes.clear();

		//Center
		currentNode.setX((int)((upperTileX + tileWidth / 2) / 5));
		currentNode.setY((int)(((upperTileY + tileHeight) / 5)));
		m_entityNodes.push_back(currentNode);
		previousNode = currentNode;
		//Top left
		currentNode.setX((int)((upperTileX + tileSubtractLeft) / 5));
		currentNode.setY((int)((upperTileY / 5)));
		if (currentNode != previousNode) {
			m_entityNodes.push_back(currentNode);
			previousNode = currentNode;
		}
		//Top right
		currentNode.setX((int)((upperTileX + tileWidth - tileSubtractRight) / 5));
		currentNode.setY((int)((upperTileY / 5)));
		if (currentNode != previousNode) {
			m_entityNodes.push_back(currentNode);
			previousNode = currentNode;
		}
		//Bottom left
		currentNode.setX((int)((upperTileX + tileSubtractLeft) / 5));
		currentNode.setY((int)(((upperTileY + tileHeight) / 5)));
		if (currentNode != previousNode) {
			m_entityNodes.push_back(currentNode);
			previousNode = currentNode;
		}
		//Bottom right
		currentNode.setX((int)((upperTileX + tileWidth - tileSubtractRight) / 5));
		currentNode.setY((int)(((upperTileY + tileHeight) / 5)));
		if (currentNode != previousNode) {
			m_entityNodes.push_back(currentNode);
		}
		// Remove duplicates
		std::sort(m_entityNodes.begin(), m_entityNodes.end());
		m_entityNodes.erase(std::unique(m_entityNodes.begin(), m_entityNodes.end()), m_entityNodes.end());

		for (unsigned short a = 0; a < m_entityNodes.size(); ++a) {
			//unsigned short numNodeChecks = 0;
			//for (auto it=m_levelNodes.begin(); it != m_levelNodes.end(); ++it) {
				//std::cout << (*it)->get() << " ";
			for (int y = 0; y < 5; ++y) {
				for (int x = 0; x < 5; ++x) {
					for (int z = 0; z < level->getNumLayers(); ++z) {

						unsigned short n = x + (m_entityNodes.at(a).getX() * 5) + (y + (m_entityNodes.at(a).getY() * 5)) * level->getNumColumns();

						unsigned short tileX = x + (m_entityNodes.at(a).getX() * 5);
						unsigned short tileY = y + (m_entityNodes.at(a).getY() * 5);

						//unsigned short n = x + ((*it)->getX() * 20) + (y + ((*it)->getY() * 15)) * level->getNumColumns();

						//if (level->m_tileObjects != nullptr && level->m_tileObjects[z] != nullptr) {
						//	// Update here if not a coin or brick, they're updated every frame
						//	if (!level->m_tileObjects[z][n].getDoUpdateEveryFrame()/* && a == 0*/) {
						//		level->m_tileObjects[z][n].update(time);
						//	}
						//}

						//level->m_tileObjects[z][n].setIsHidden(true);
						if ((*it)->getIsSolidLevelY() && level->getTileObject(z, tileX, tileY)->getIsSolidEntityY() && (*it)->collisionCheckY(level->getTileObject(z, tileX, tileY))) {
							(*it)->collisionReactionY(level->getTileObject(z, tileX, tileY));
						} else if ((*it)->getIsSolidLevelX() && level->getTileObject(z, tileX, tileY)->getIsSolidEntityX() && (*it)->collisionCheckX(level->getTileObject(z, tileX, tileY))) {
							(*it)->collisionReactionX(level->getTileObject(z, tileX, tileY));
						}




					}
				}
			}
			/*	for (int b = 0; b < m_playerNodes.size(); ++b) {
					if (m_playerNodes.at(b)->get() == m_entityNodes.at(a)->get()) {
						player->collisionCheckEntityX((*it));
						player->collisionCheckEntityY((*it));
					}
				}*/
				//++numNodeChecks;
		}
		//std::cout << "\n";
		//std::cout << m_entityNodes.size() << "\n";		

		if (player != nullptr) {
			if (player->getIsSolidEntityY() && player->collisionCheckEntityY((*it))) {
				player->collisionReactionEntityY((*it));
			} else if (player->getIsSolidEntityX() && player->collisionCheckEntityX((*it))) {
				player->collisionReactionEntityX((*it));
			}
		}
	}
}

void cCollisionManager::checkParticles(cApp* app, cLevel* level, cPlayer* player, float time) {
	if (player == nullptr || level == nullptr || level->getTileObjects() == nullptr) {
		return;
	}

	int playerNodeX = (int)(player->getLevelX() / 16 / 20);
	int playerNodeY = (int)(player->getLevelY() / 16 / 15);


	//std::cout << "cCollisionManager::checkParticles " <<  << " " <<  << std::endl;

	m_particleNodes.clear();

	for (auto it = level->getParticles()->begin(); it != level->getParticles()->end(); ++it) {
		if (*it == nullptr) {
			return;
			//continue;
		}

		//float levelY = (*it)->getLevelY();

		/*if (levelY > level->getNumRows() * 16) {
			levelY = level->getNumRows() * 16;
		}*/

		int particleNodeX = (int)((*it)->getLevelX() / 16 / 20);
		int particleNodeY = (int)((*it)->getLevelY() / 16 / 15);

		//std::cout << playerNodeY << " " << particleNodeY << "\n";
		
		// Skip collision for particles more than 1 screen away in each direction
		if (!((particleNodeX == playerNodeX || particleNodeX == playerNodeX + 1 || particleNodeX == playerNodeX - 1)
			&&
			(particleNodeY == playerNodeY || particleNodeY == playerNodeY + 1 || particleNodeY == playerNodeY - 1))) {
			//std::cout << "Particle not within bounds, skipping collision\n";
			continue;
		}

		float edgeLeft = -(float)(*it)->getWidth();
		float edgeRight = (float)level->getNumColumns() * 16;
		float edgeUp = -(float)(*it)->getHeight();
		float edgeDown = (float)level->getNumRows() * 16;
		if ((*it)->getLevelX() <= edgeLeft || (*it)->getLevelX() >= edgeRight ||
			(*it)->getLevelY() <= edgeUp || (*it)->getLevelY() >= edgeDown) {
			continue;
		}

		if (player != nullptr) {
			if ((*it)->getIsSolidPlayerY() && (*it)->collisionCheckY(player)) {
				(*it)->collisionReactionY(player);
			} else if ((*it)->getIsSolidPlayerX() && (*it)->collisionCheckX(player)) {
				(*it)->collisionReactionX(player);
			}
		}

		for (auto eit = level->getEntities()->begin(); eit != level->getEntities()->end(); ++eit) {
			if (*eit == nullptr) {
				return;
			}
			if ((*it)->getIsSolidEntityY() && (*it)->collisionCheckY(*eit)) {
				(*it)->collisionReactionY(*eit);
			} else if ((*it)->getIsSolidEntityX() && (*it)->collisionCheckX(*eit)) {
				(*it)->collisionReactionX(*eit);
			}
		}

		if (!(*it)->getIsSolidLevelX() && !(*it)->getIsSolidLevelY()) {
			//std::cout << "no solid level" << "\n";
			continue;
		}

		unsigned char extraTilesX = 2;
		unsigned char extraTilesY = 2;


		int upperTileX = (int)((*it)->getLevelX() / 16);
		int upperTileY = (int)((*it)->getLevelY() / 16);

		if (upperTileX < extraTilesX) {
			upperTileX = extraTilesX;
		}
		if (upperTileX > level->getNumColumns() - 5 - extraTilesX) {
			upperTileX = level->getNumColumns() - 5 - extraTilesX;
		}
		if (upperTileY < extraTilesY) {
			upperTileY = extraTilesY;
		}
		if (upperTileY > level->getNumRows() - 5 - extraTilesY) {
			upperTileY = level->getNumRows() - 5 - extraTilesY;
		}

		//std::cout << "cCollisionManager " << tileX << " " << tileY << "\n";

		int tileWidth = (int)(*it)->getWidth() / 16;
		int tileHeight = (int)(*it)->getHeight() / 16;

		int tileSubtractLeft = (*it)->getSubtractLeft() / 16/* - extraTilesX*/;
		int tileSubtractRight = (*it)->getSubtractRight() / 16/* + extraTilesX*/;
		int tileSubtractUp = (*it)->getSubtractUp() / 16/* - extraTilesY*/;
		int tileSubtractDown = (*it)->getSubtractDown() / 16/* + extraTilesY*/;

		//std::cout << "cCollisionManager " << tileSubtractLeft << " " << tileSubtractUp << "\n";

		unsigned short columns = level->getNumColumns() / 5;
		cLevelNode currentNode(0, 0, columns);
		cLevelNode previousNode(0, 0, columns);

		/* Add nodes in this order
		 _ _ _
		 _ _ _|
		|_ _ _

		TL TC TR
		ML MC MR
		BL BC BR
		*/
		m_particleNodes.clear();
		// top left
		currentNode.setX((int)((upperTileX - extraTilesX) / 5));
		currentNode.setY((int)(((upperTileY + tileSubtractUp) / 5)));
		m_particleNodes.push_back(currentNode);
		previousNode = currentNode;
		// Top center
		currentNode.setX((int)((upperTileX + tileWidth / 2) / 5));
		currentNode.setY((int)(((upperTileY - extraTilesY) / 5)));
		m_particleNodes.push_back(currentNode);
		if (currentNode != previousNode) {
			m_particleNodes.push_back(currentNode);
			previousNode = currentNode;
		}
		// Top right
		currentNode.setX((int)((upperTileX + tileWidth + extraTilesX) / 5));
		currentNode.setY((int)(((upperTileY - extraTilesY) / 5)));
		if (currentNode != previousNode) {
			m_particleNodes.push_back(currentNode);
			previousNode = currentNode;
		}
		// Mid right
		currentNode.setX((int)((upperTileX + tileWidth + extraTilesX) / 5));
		currentNode.setY((int)(((upperTileY + tileHeight / 2) / 5)));
		m_particleNodes.push_back(currentNode);
		if (currentNode != previousNode) {
			m_particleNodes.push_back(currentNode);
			previousNode = currentNode;
		}
		// Mid center
		currentNode.setX((int)((upperTileX + tileWidth / 2) / 5));
		currentNode.setY((int)(((upperTileY + tileHeight / 2) / 5)));
		m_particleNodes.push_back(currentNode);
		if (currentNode != previousNode) {
			m_particleNodes.push_back(currentNode);
			previousNode = currentNode;
		}
		// Mid Left
		currentNode.setX((int)((upperTileX - extraTilesX) / 5));
		currentNode.setY((int)(((upperTileY + tileHeight / 2) / 5)));
		m_particleNodes.push_back(currentNode);
		if (currentNode != previousNode) {
			m_particleNodes.push_back(currentNode);
			previousNode = currentNode;
		}
		// Bottom left
		currentNode.setX((int)((upperTileX - extraTilesX) / 5));
		currentNode.setY((int)(((upperTileY + tileHeight + extraTilesY) / 5)));
		if (currentNode != previousNode) {
			m_particleNodes.push_back(currentNode);
			previousNode = currentNode;
		}
		// Bottom center
		currentNode.setX((int)((upperTileX + tileWidth / 2) / 5));
		currentNode.setY((int)(((upperTileY + tileHeight + extraTilesY) / 5)));
		m_particleNodes.push_back(currentNode);
		if (currentNode != previousNode) {
			m_particleNodes.push_back(currentNode);
			previousNode = currentNode;
		}
		// Bottom right
		currentNode.setX((int)((upperTileX + tileWidth + extraTilesX) / 5));
		currentNode.setY((int)(((upperTileY + tileHeight + extraTilesY) / 5)));
		if (currentNode != previousNode) {
			m_particleNodes.push_back(currentNode);
			previousNode = currentNode;
		}

		// Remove duplicates
		//std::sort(m_particleNodes.begin(), m_particleNodes.end());
		m_particleNodes.erase(std::unique(m_particleNodes.begin(), m_particleNodes.end()), m_particleNodes.end());

		for (size_t a = 0; a < m_particleNodes.size(); ++a) {
			//unsigned short numNodeChecks = 0;
			//for (auto it=m_levelNodes.begin(); it != m_levelNodes.end(); ++it) {
				//std::cout << (*it)->get() << " ";
			for (int z = 0; z < level->getNumLayers(); ++z) {
				/*if (level->getTileObjects() == nullptr) {
					return;
				}*/
				for (unsigned char y = 0; y < 5; ++y) {
					for (unsigned char x = 0; x < 5; ++x) {

						unsigned short n = x + (m_particleNodes.at(a).getX() * 5) + (y + (m_particleNodes.at(a).getY() * 5)) * level->getNumColumns();


						unsigned short tileX = x + (m_particleNodes.at(a).getX() * 5);
						unsigned short tileY = y + (m_particleNodes.at(a).getY() * 5);

						//level->m_tileObjects[z][n].setIsHidden(true);
						//std::cout << currentNode.get() << " " << "\n";

						//if (currentNode.get() == level->m_tileObjects[z][n].getLevelNode()) {
						/*if ((*it)->doSpawnNewParticle()) {
							m_particleNodes.clear();
							return;
						}*/


						//	//std::cout << currentNode.get() << " " << "\n";


						if (level->getTileObject(z, tileX, tileY) == nullptr) {
							return;
						}
						//if (player != nullptr) {
						//	// The ones updated every frame are in Level::update
						//	if (!level->getTileObject(z, tileX, tileY)->getIsUpdatedEveryFrame() &&
						//		level->getTileObject(z, tileX, tileY)->getLevelX() > player->getLevelX() &&
						//		level->getTileObject(z, tileX, tileY)->getLevelX() < player->getLevelX() + 100) {
						//		level->getTileObject(z, tileX, tileY)->update(time);
						//	}
						//}
						if (level->getTileObject(z, tileX, tileY)->getIsSolidLevelY() && (*it)->collisionCheckY(level->getTileObject(z, tileX, tileY))) {
							(*it)->collisionReactionY(level->getTileObject(z, tileX, tileY));
						} else if (level->getTileObject(z, tileX, tileY)->getIsSolidLevelX() && (*it)->collisionCheckX(level->getTileObject(z, tileX, tileY))) {
							(*it)->collisionReactionX(level->getTileObject(z, tileX, tileY));
						}
						//}

					}
				}
			}

			/*	for (int b = 0; b < m_playerNodes.size(); ++b) {
					if (m_playerNodes.at(b)->get() == m_entityNodes.at(a)->get()) {
						player->collisionCheckEntityX((*it));
						player->collisionCheckEntityY((*it));
					}
				}*/
				//++numNodeChecks;
		}
		//std::cout << "\n";
		//std::cout << m_levelNodes.size() << "\n";



		m_particleNodes.clear();

	}
	//std::cout << level->getX() << "\n";
}

void cCollisionManager::update(cApp *app, cPlayer *player, cLevel *level, float time) {		
	checkPlayer(app, level, player, time);
	checkEntities(app, level, player, time);
	checkParticles(app, level, player, time);
	//std::cout << "cCollisionManager::update" << "\n";
}