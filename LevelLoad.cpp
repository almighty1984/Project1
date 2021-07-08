#include "Level.h"
#include "RenderingManager.h"
#include "SavesManager.h"
#include <sstream>
#include <random>
//#include "Globals.h"

void cLevel::load(std::string fileName, cApp* app) {
	if (app == nullptr) { return; };
	m_attachedApp = app;
	if (fileName.empty()) {
		std::cout << "Level not found: " << fileName << "\n";
		fileName = "Data\\Levels\\5000_5000.bin";
	}

	std::cout << "cLevel::load() begin" << "\n";
	std::string pathShop = "Data\\Shops\\" + fileName.substr(12, 9) + ".cfg";
	loadShop(pathShop);
	createTiles(fileName);
	createTileset("Data\\Tiles\\tileset_data.bin");
	createTileObjects();

	createBackground(app->getPathBackground());

	m_path = fileName;

	std::cout << "cLevel::load() end" << "\n";
}

void cLevel::createTiles(std::string fileName) {
	std::cout << "createTiles start" << "\n";
	std::ifstream dataFile;
	dataFile.open(fileName.c_str(), std::ios::in | std::ios::binary);

	dataFile.read((char*)&m_numLayers, sizeof(unsigned char));
	dataFile.read((char*)&m_numColumns, sizeof(unsigned short));
	dataFile.read((char*)&m_numRows, sizeof(unsigned short));

	m_tiles = new unsigned short[m_numLayers * m_numColumns * m_numRows];
	m_tilesetNumbers = new unsigned char[m_numLayers * m_numColumns * m_numRows];

	std::cout << "cLevel::createTiles: read tiles...";
	for (unsigned char z = 0; z < m_numLayers; ++z) {
		dataFile.read((char*)&m_tiles[z * (m_numColumns * m_numRows)], static_cast<std::streamsize>(sizeof(unsigned short) * m_numColumns * m_numRows));
		dataFile.read((char*)&m_tilesetNumbers[z * (m_numColumns * m_numRows)], static_cast<std::streamsize>(sizeof(unsigned char) * m_numColumns * m_numRows));
	}
	std::cout << "done.\n";

	dataFile.close();
	m_path = fileName;

	std::cout << "createTiles end " << m_path << "\n";
}

void cLevel::createTileset(std::string fileName) {
	std::cout << "createTileset " << fileName << "\n";
	std::ifstream dataFile;
	dataFile.open(fileName.c_str(), std::ios::in | std::ios::binary);
	
	m_tilesetTypes = new char* [32 * 32];
	for (unsigned short i = 0; i < 32 * 32; ++i) {
		m_tilesetTypes[i] = new char[32];
		dataFile.read((char*)m_tilesetTypes[i], sizeof(char[32]));
		//std::cout << m_tilesetTypes[i] << "\n";
	}

	m_tilesetTypesEntities = new char* [32 * 32];
	for (unsigned short i = 0; i < 32 * 32; ++i) {
		m_tilesetTypesEntities[i] = new char[32];
		dataFile.read((char*)m_tilesetTypesEntities[i], sizeof(char[32]));
		//std::cout << m_tilesetTypesEntities[i] << "\n";
	}

	dataFile.close();
	std::cout << "done\n";
}

void cLevel::createBackground(std::string fileName) {
	std::cout << "createBackground..." << "\n";
	if (m_backgroundPlanes != nullptr) {
		deleteBackground();
	}
	//m_pathBackground = fileName;
	std::ifstream dataFile(fileName.c_str());
	if (!dataFile) {
		std::cout << "Error:  Cannot open file " << fileName << "\n";
		//exit( 1 );
	}
	std::istringstream iStr(std::ios_base::out);
	char buf[240] = { 0 };
	std::string firstField, secondField;
	firstField.clear();
	secondField.clear();

	while (!dataFile.eof()) {
		dataFile.getline(buf, sizeof(buf));
		iStr.str(std::string(buf));
		iStr >> firstField >> secondField;
		iStr.clear();
		iStr.str("");
		if (secondField == "{") {
			++m_numBackgroundPlanes;
		}
	}
	m_backgroundPlanes = new cPlane[m_numBackgroundPlanes];
	for (unsigned char i = 0; i < m_numBackgroundPlanes; ++i) {
		m_backgroundPlanes[i].loadPlaneConfig(fileName, i);
		cRenderingManager::addBackgroundPlane(&m_backgroundPlanes[i]);
	}
	dataFile.close();
	std::cout << "done " << (int)m_numBackgroundPlanes << " " << fileName << "\n";
}

void cLevel::createForeground(std::string fileName) {
	if (m_foregroundPlanes != nullptr) {
		deleteForeground();
	}
	//m_pathForeground = fileName;
	std::cout << "loadForeground start" << "\n";
	std::ifstream dataFile(fileName.c_str());
	if (!dataFile) {
		std::cout << "Error:  Cannot open file " << fileName << "\n";
		//exit( 1 );
	}
	std::istringstream iStr(std::ios_base::out);
	char buf[240] = { 0 };
	std::string firstField, secondField;
	firstField.clear();
	secondField.clear();

	while (!dataFile.eof()) {
		dataFile.getline(buf, sizeof(buf));
		iStr.str(std::string(buf));
		iStr >> firstField >> secondField;
		iStr.clear();
		iStr.str("");

		if (secondField == "{") {
			++m_numForegroundPlanes;
		}
	}		
	
	m_foregroundPlanes = new cPlane[m_numForegroundPlanes];

	for (unsigned char i = 0; i < m_numForegroundPlanes; ++i) {
		m_foregroundPlanes[i].loadPlaneConfig(fileName, i);
		//cRenderingManager::addForegroundPlane(&m_foregroundPlanes[i]);
	}
	dataFile.close();
	std::cout << "numForegroundPlanes = " << (int)m_numForegroundPlanes << "\n";
}

void cLevel::loadShop(std::string fileName) {
	std::ifstream dataFile(fileName.c_str());

	if (!dataFile) {
		std::cout << "Error:  Cannot open file " << fileName << "\n";
		//exit( 1 );
		fileName = "Data\\Shops\\5000_5000.cfg";
		dataFile.open(fileName.c_str());
	}

	std::istringstream iStr(std::ios_base::out);
	char buf[80] = { 0 };
	std::string firstField;
	std::string secondField;
	std::string data;
	std::string data2;
	std::string data3;

	while (!dataFile.eof()) {
		dataFile.getline(buf, sizeof(buf));

		iStr.str(std::string(buf));
		iStr >> firstField >> secondField;
		iStr.clear();
		iStr.str("");

		for (int i = 0; i < 3; ++i) {
			if (firstField == "Item" + std::to_string(i)) {
				std::cout << firstField << " ";
				while (dataFile.peek() != '}') {
					dataFile.getline(buf, sizeof(buf));

					iStr.str(std::string(buf));
					iStr >> firstField >> secondField >> data;
					iStr.clear();
					iStr.str("");

					if (firstField == "type") {
						m_typeItem[i] = data;
						std::cout << data << " ";
					} else if (firstField == "cost") {
						m_costItem[i] = atoi(data.c_str());
						std::cout << m_costItem[i] << " ";

						m_fontCost[i].setWidth(64);
						m_fontCost[i].setText("Exit");
						m_fontCost[i].setImagePath(cRenderingManager::getPathFont());
						//m_fontCost[i].setX(m_shopItems.at(i)->getX());
						//m_fontCost[i].setY(m_shopItems.at(i)->getY());
						m_fontCost[i].setIsHidden(true);
						m_fontCost[i].setText(data);
					} else if (firstField == "currency") {
						m_currencyItem[i] = data;
						std::cout << "Level::loadShop currency = " << data << "\n";
					}
				}
			}
			cRenderingManager::addBitmapFont(&m_fontCost[i]);
			//cRenderingManager::addObject(m_currencyObject[i]);
		}
		std::cout << "\n";
	}
}

void cLevel::createTileObjects() {
	if (m_attachedApp == nullptr) { return; }
	m_tileObjects = new cObject[m_numLayers * m_numColumns * m_numRows];

	for (unsigned char z = 0; z < m_numLayers; ++z) {
		for (unsigned short y = 0; y < m_numRows; ++y) {
			for (unsigned short x = 0; x < m_numColumns; ++x) {
				getTileObject(z, x, y)->setTile(0);
			}
		}
	}

	m_referenceObject.setX(0.0f);
	m_referenceObject.setLevelX(0.0f);
	m_referenceObject.setY(0.0f);
	m_referenceObject.setLevelY(0.0f);

	for (unsigned char z = 0; z < m_numLayers; ++z) {
		for (unsigned short y = 0; y < m_numRows; ++y) {
			for (unsigned short x = 0; x < m_numColumns; ++x) {
				getTileObject(z, x, y)->setTile(getTile(z, x, y));
				getTileObject(z, x, y)->setX((float)(x * getTileObject(z, x, y)->getWidth()));
				getTileObject(z, x, y)->setY((float)(y * getTileObject(z, x, y)->getHeight()));
				getTileObject(z, x, y)->setStartX(getTileObject(z, x, y)->getX());
				getTileObject(z, x, y)->setStartY(getTileObject(z, x, y)->getY());
				getTileObject(z, x, y)->setLevelX(getTileObject(z, x, y)->getX());
				getTileObject(z, x, y)->setLevelY(getTileObject(z, x, y)->getY());
				getTileObject(z, x, y)->attachLevel(this);

				//app->sleep(10000);
				//cGlobals::get().m_quadNode.setMaxLevel( 2 );
				/*cGlobals::get().m_quadNode.setMaxLevel( m_numColumns/20 + 0);
				cGlobals::get().m_quadNode.setMaxObjects(8);*/

				// Go through every possible tile to load
				for (unsigned char tsy = 0; tsy < 32; ++tsy) {	//row								
					for (unsigned char tsx = 0; tsx < 32; ++tsx) {  //column
						if (getTile(z, x, y) == (1 + tsx + tsy * 32)) {
							getTileObject(z, x, y)->setTileOffsetX((float)(tsx * 16));
							getTileObject(z, x, y)->setTileOffsetY((float)(tsy * 16));

							if (getTilesetNumber(z, x, y) == 255) {
								//m_tileObjects[z][x+y*m_numColumns].setFlags(m_tilesetFlags/*[ m_tilesetNumbers[z][x+y*m_numColumns] ]*/[i+j*32]);
								getTileObject(z, x, y)->setType(m_tilesetTypes[tsx + tsy * 32]);
							} else if (getTilesetNumber(z, x, y) == 254) {
								getTileObject(z, x, y)->setType(m_tilesetTypesEntities[tsx + tsy * 32]);
							}
						}
					}
				}
				// Tileset path
				std::stringstream stringStream;
				stringStream.str("");
				stringStream.clear();
				std::string path, type;				
				path.clear();				
				type.clear();

				stringStream << (int)getTilesetNumber(z, x, y);
				path = "Data\\Tiles\\tileset_" + stringStream.str() + ".png";
				getTileObject(z, x, y)->setImagePath(path);

				stringStream.str("");
				stringStream.clear();

				type.clear();
				type = getTileObject(z, x, y)->getType();

				// Player start positions
				if (type.substr(0, 11) == "level_left_") {
					int a = atoi(getTileObject(z, x, y)->getType().substr(11, 1).c_str());
					/*if (m_secondFoundLeft[a] == false) {
						m_secondFoundLeft[a] = true;*/
					m_playerStartsLeft[a].x = getTileObject(z, x, y)->getX() - 0;
					//}
					m_playerStartsLeft[a].y = getTileObject(z, x, y)->getY() + 16;
				} else if (type.substr(0, 12) == "level_right_") {
					int a = atoi(getTileObject(z, x, y)->getType().substr(12, 1).c_str());
					m_playerStartsRight[a].x = getTileObject(z, x, y)->getX() + 16;
					m_playerStartsRight[a].y = getTileObject(z, x, y)->getY() + 16;
				} else if (type.substr(0, 5) == "door_" && type != "door_exit") {
					int a = atoi(getTileObject(z, x, y)->getType().substr(5, 1).c_str());
					m_playerStartsDoor[a].x = getTileObject(z, x, y)->getX();
					m_playerStartsDoor[a].y = getTileObject(z, x, y)->getY() + 16;
				} else if (type.substr(0, 13) == "level_bottom_") {
					int a = atoi(getTileObject(z, x, y)->getType().substr(13, 1).c_str());
					m_playerStartsBottom[a].x = getTileObject(z, x, y)->getX();
					m_playerStartsBottom[a].y = getTileObject(z, x, y)->getY() + 0;
				} else if (type.substr(0, 10) == "level_top_") {
					int a = atoi(getTileObject(z, x, y)->getType().substr(10, 1).c_str());
					m_playerStartsTop[a].x = getTileObject(z, x, y)->getX() + 8;
					m_playerStartsTop[a].y = getTileObject(z, x, y)->getY() + 0;
				} else if (type == "level_start") {
					m_startObject = getTileObject(z, x, y);
					//if (m_playerStartCenter.x == 0.0f) {
					m_playerStartCenter.x = getTileObject(z, x, y)->getX() + 8;
					//}
					//if (m_playerStartCenter.y == 0.0f) {
					m_playerStartCenter.y = getTileObject(z, x, y)->getY();
					//}					
				}
				/*if (type == "swing") {
					getTileObject(z, x, y)->loadConfig("Data\\Objects\\swing.cfg");
				} else*/
				if (type.substr(0, 5) == "coin_") {
					int tmpInt = 0;
					if (type.size() == 6) {
						tmpInt = 0;
						std::istringstream(type.substr(5, 1)) >> tmpInt;
					} else if (type.size() == 7) {
						tmpInt = 0;
						std::istringstream(type.substr(5, 2)) >> tmpInt;
					}
					if (cSavesManager::hasAddedCoin(m_path, tmpInt) == true) {
						std::cout << "Already added coin " << tmpInt << "\n";
						getTileObject(z, x, y)->setIsDead(true);
						getTileObject(z, x, y)->setIsHidden(true);
					} else {
						getTileObject(z, x, y)->loadConfig("Data\\Objects\\coin.cfg");
						//m_updateEveryFrameList.push_back(&getTileObject(z, x, y));
					}
					//getTileObject(z, x, y)->setIsLocked(true);
				} else if (type == "item_sprint") {
					if (m_playerHasSprint == true) {
						getTileObject(z, x, y)->setIsSolid(false);
						getTileObject(z, x, y)->setIsHidden(true);
					} else {
						path.clear();
						path = "Data\\Objects\\" + getTileObject(z, x, y)->getType() + ".cfg";
						getTileObject(z, x, y)->loadConfig(path);
						getTileObject(z, x, y)->setIsDead(false);
					}
				} else if (type == "item_hover") {
					if (m_playerHasHover == true) {
						getTileObject(z, x, y)->setIsSolid(false);
						getTileObject(z, x, y)->setIsHidden(true);
					} else {
						path.clear();
						path = "Data\\Objects\\" + getTileObject(z, x, y)->getType() + ".cfg";
						getTileObject(z, x, y)->loadConfig(path);
						getTileObject(z, x, y)->setIsDead(false);
					}
				} else if (type == "item_whirl") {
					if (m_playerHasWhirl == true) {
						getTileObject(z, x, y)->setIsSolid(false);
						getTileObject(z, x, y)->setIsHidden(true);
					} else {
						path.clear();
						path = "Data\\Objects\\" + getTileObject(z, x, y)->getType() + ".cfg";
						getTileObject(z, x, y)->loadConfig(path);
						getTileObject(z, x, y)->setIsDead(false);
					}
				} else if (type.substr(0, 10) == "shop_item_") {
					addShopItem(getTileObject(z, x, y));
				} else if (type.substr(0, 4) == "sand") {
					getTileObject(z, x, y)->loadConfig("Data\\Objects\\sand.cfg");
					m_updateEveryFrameList.push_back(getTileObject(z, x, y));
				} else if (type.substr(0, 3) == "pot") {
					unsigned char tmpChar = 0;
					if (type.size() == 6) {
						std::istringstream(type.substr(4, 1)) >> tmpChar;
					} else if (type.size() == 7) {
						std::istringstream(type.substr(4, 2)) >> tmpChar;
					}
					if (cSavesManager::hasAddedPot(m_path, tmpChar)) {
						getTileObject(z, x, y)->setIsDead(true);
						getTileObject(z, x, y)->setIsHidden(true);
					} else {
						getTileObject(z, x, y)->loadConfig("Data\\Objects\\pot.cfg");
						getTileObject(z, x, y)->setStartX((float)(16 * x - getTileObject(z, x, y)->getWidth() / 2 + 16));
						getTileObject(z, x, y)->setStartY((float)(16 * y));
						//m_tileObjects[z][x+y*m_numColumns].setType("pot");
						getTileObject(z, x, y)->setX((float)(16 * x - getTileObject(z, x, y)->getWidth() / 2 + 16));
						getTileObject(z, x, y)->setY((float)16 * y);
						//m_tileObjects[z][x+y*m_numColumns].setUseFloatPosition(true);
						getTileObject(z, x, y)->update(0.0f);
					}
				} else if (type.substr(0, 5) == "path_") {
					getTileObject(z, x, y)->loadConfig("Data\\Objects\\path.cfg");
					int tmpInt = 0;
					if (type.size() == 6) {
						std::istringstream(type.substr(5, 1)) >> tmpInt;
					} else if (type.size() == 7) {
						std::istringstream(type.substr(5, 2)) >> tmpInt;
					}
					m_pathObjectsList[tmpInt] = getTileObject(z, x, y);
				} else if (type.substr(0, 8) == "trigger_") {
					int tmpInt = 0;
					if (type.size() == 9) {
						std::istringstream(type.substr(8, 1)) >> tmpInt;
					} else if (type.size() == 10) {
						std::istringstream(type.substr(8, 2)) >> tmpInt;
					}
					getTileObject(z, x, y)->loadConfig(m_attachedApp->getPathTrigger(tmpInt));
					getTileObject(z, x, y)->setStartX((float)(16 * x + getTileObject(z, x, y)->getOffsetX()));
					getTileObject(z, x, y)->setStartY((float)(16 * y + getTileObject(z, x, y)->getOffsetY()));
					getTileObject(z, x, y)->setX((float)(16 * x + getTileObject(z, x, y)->getOffsetX()));
					getTileObject(z, x, y)->setY((float)(16 * y + getTileObject(z, x, y)->getOffsetY()));
					getTileObject(z, x, y)->setTileOffsetX((float)(getTileObject(z, x, y)->getNumAnimFrames() * getTileObject(z, x, y)->getWidth() - getTileObject(z, x, y)->getWidth()));

					if (cSavesManager::hasTargetedObject(m_path, tmpInt)) {
						std::cout << "We have targeted the target " << tmpInt << "\n";
						getTileObject(z, x, y)->setIsDead(true);
						//getTileObject(z, x, y)->setTileOffsetY(32.0f);
						getTileObject(z, x, y)->setAnim(eAnimTag::death);
					}
					getTileObject(z, x, y)->update(0.0f);

					// If there's already a trigger, connect it to this one
					//if (m_triggerObjectsList[tmpInt] != nullptr) {
					//	m_triggerObjectsList[tmpInt]->m_connectedObjects.push_back(&getTileObject(z, x, y));
					//	//m_triggerObjectsList[tmpInt]->m_connectedObject = &getTileObject(z, x, y);
					//} else {

					/*if (m_triggerObjectsList[tmpInt] != nullptr) {
						m_triggerObjectsList[tmpInt]->m_connectedObjects.push_back(&getTileObject(z, x, y));
					}*/

					m_triggerObjectsList[tmpInt] = getTileObject(z, x, y);
					//}

					if (m_targetObjectsList[tmpInt] != nullptr) {
						m_triggerObjectsList[tmpInt]->m_connectedObjects.push_back(m_targetObjectsList[tmpInt]);
					}
				} else if (type.substr(0, 7) == "target_") {
					unsigned short tmpInt = 0;
					if (type.size() == 8) {
						std::istringstream(type.substr(7, 1)) >> tmpInt;
					} else if (type.size() == 9) {
						std::istringstream(type.substr(7, 2)) >> tmpInt;
					}
					getTileObject(z, x, y)->loadConfig("Data\\Objects\\target_door_right.cfg");
					getTileObject(z, x, y)->setStartX((float)(16 * x - getTileObject(z, x, y)->getWidth() / 2 + getTileObject(z, x, y)->getOffsetX()));
					getTileObject(z, x, y)->setStartY((float)(16 * y + 16 - getTileObject(z, x, y)->getHeight() + getTileObject(z, x, y)->getOffsetY()));
					getTileObject(z, x, y)->setX(getTileObject(z, x, y)->getStartX());
					getTileObject(z, x, y)->setY(getTileObject(z, x, y)->getStartY());
					getTileObject(z, x, y)->setTileOffsetX((float)(getTileObject(z, x, y)->getNumAnimFrames() * getTileObject(z, x, y)->getWidth() - getTileObject(z, x, y)->getWidth()));
					getTileObject(z, x, y)->setAnim(eAnimTag::idle);
					getTileObject(z, x, y)->setIsDead(false);

					if (cSavesManager::hasTargetedObject(m_path, (unsigned char)tmpInt)) {
						std::cout << "We have triggered the target " << tmpInt << "\n";
						getTileObject(z, x, y)->setIsDead(true);
						//getTileObject(z, x, y)->setTileOffsetY(32.0f);
						getTileObject(z, x, y)->setAnim(eAnimTag::death);

					}
					getTileObject(z, x, y)->update(0.0f);

					// If there's already a target, connect it to this one
					if (m_targetObjectsList[tmpInt] != nullptr) {
						m_targetObjectsList[tmpInt]->m_connectedObjects.push_back(getTileObject(z, x, y));
						//m_targetObjectsList[tmpInt]->m_connectedObject = &getTileObject(z, x, y);
					} else {
						m_targetObjectsList[tmpInt] = getTileObject(z, x, y);
					}
					if (m_triggerObjectsList[tmpInt] != nullptr) {
						m_triggerObjectsList[tmpInt]->m_connectedObjects.push_back(m_targetObjectsList[tmpInt]);
					} else {
						m_triggerObjectsList[tmpInt] = m_targetObjectsList[tmpInt];
					}
				} else {
					// Regular object, not entity
					if (!type.empty() && type.substr(0, 2) != "e_") {
						path.clear();
						path = "Data\\Objects\\" + getTileObject(z, x, y)->getType() + ".cfg";
						getTileObject(z, x, y)->loadConfig(path);

						getTileObject(z, x, y)->setStartX((float)(16 * x + getTileObject(z, x, y)->getOffsetX()));
						getTileObject(z, x, y)->setStartY((float)(16 * y + getTileObject(z, x, y)->getOffsetY())/* - m_tileObjects[z][x+y*m_numColumns].getHeight() + 16*/);
						getTileObject(z, x, y)->setX((float)(16 * x + getTileObject(z, x, y)->getOffsetX()));
						getTileObject(z, x, y)->setY((float)(16 * y + getTileObject(z, x, y)->getOffsetY()/* - m_tileObjects[z][x+y*m_numColumns].getHeight() + 16 */));
						//return;
					}
				}

				if (getTileObject(z, x, y)->getIsUpdatedEveryFrame()) {
					m_updateEveryFrameList.push_back(getTileObject(z, x, y));
				}

				if (type.substr(0, 2) == "e_") {
					loadEntity(z, x, y, type);
				}
				/*if(m_tileObjects[z][x+y*m_numColumns].getFlags() == 1)
					cGlobals::get().m_quadNode.insert(& m_tileObjects[z][x+y*m_numColumns] );*/
			}
		}
	}

	for (unsigned short i = 0; i < m_triggerObjectsList.size() - 0; ++i) {
		if (m_triggerObjectsList[i] != nullptr) {
			for (unsigned short j = 0; j < m_triggerObjectsList[i]->m_connectedObjects.size(); ++j) {
				m_triggerObjectsList[i]->m_connectedObjects.at(j) = m_targetObjectsList[i];
			}
			//m_triggerObjectsList[i]->m_connectedObjects.push_back(m_targetObjectsList[i]);

			/*if (m_triggerObjectsList[i]->m_connectedObject != nullptr) {
				m_triggerObjectsList[i]->m_connectedObject->m_connectedObject = m_targetObjectsList[i];
			}*/
		} else {
			m_triggerObjectsList[i] = m_targetObjectsList[i];
		}
	}
}

void cLevel::loadEntity(unsigned char z, unsigned short x, unsigned short y, std::string type) {

	if (m_attachedApp == nullptr) { return; }

	getTileObject(z, x, y)->setIsSolid(false);
	getTileObject(z, x, y)->setIsHidden(true);
	getTileObject(z, x, y)->setTile(0);
	getTileObject(z, x, y)->setType("");

	bool doRandomizeDirection = true;
	
	std::string pathEntity;
	pathEntity.clear();

	unsigned char numToBeCreated = 1;

	if (type.substr(2, 5) == "grass") {
		numToBeCreated = 4;
	}

	for (unsigned char i = 0; i < numToBeCreated; ++i) {
		if (type.substr(2, 4) == "ball") {
			addEntity(new cEntityBall);
			pathEntity = "Data\\Entities\\e_ball.cfg";
		} else if (type.substr(2, 5) == "brick") {
			doRandomizeDirection = false;
			addEntity(new cEntityBrick);
			pathEntity = "Data\\Entities\\e_brick.cfg";
		} else if (type.substr(2, 6) == "bounce") {
			doRandomizeDirection = false;
			addEntity(new cEntity);
			pathEntity = "Data\\Entities\\" + type + ".cfg";
		} else if (type.substr(2, 6) == "flugan") {
			int numEntity = 0;
			if (type.size() == 10) {
				numEntity = atoi(type.substr(9, 1).c_str());
			} else if (type.size() == 11) {
				numEntity = atoi(type.substr(9, 2).c_str());
			}
			std::cout << "Level::loadEntity NUM = " << numEntity << "\n";
			if (cSavesManager::hasKilledFlugan(m_path, numEntity)) {
				return;
			} else {
				addEntity(new cEntityFlugan);
				getEntityLast()->setTile(numEntity);
			}
			pathEntity = "Data\\Entities\\e_flugan.cfg";
		} else if (type.substr(2, 7) == "flyling") {
			addEntity(new cEntityFlyling);
			pathEntity = "Data\\Entities\\e_flyling.cfg";
		} else if (type.substr(2, 5) == "grass") {
			doRandomizeDirection = false;
			addEntity(new cEntityGrass);
			pathEntity = "Data\\Entities\\e_grass.cfg";
		} else if (type.substr(2, 7) == "grodorr") {
			int numEntity = 0;
			if (type.size() == 11) {
				numEntity = atoi(type.substr(10, 1).c_str());
			} else if (type.size() == 12) {
				numEntity = atoi(type.substr(10, 2).c_str());
			}
			std::cout << "Level::loadEntity NUM = " << numEntity << "\n";
			if (cSavesManager::hasKilledGrodorr(m_path, numEntity)) {
				return;
			} else {
				addEntity(new cEntityGrodorr);
				getEntityLast()->setNumber(numEntity);
			}
			pathEntity = "Data\\Entities\\e_grodorr.cfg";
		} else if (type.substr(2, 7) == "grevert") {
			addEntity(new cEntityGrevert);
			pathEntity = "Data\\Entities\\e_grevert.cfg";
		} else if (type.substr(2, 5) == "pigan") {
			addEntity(new cEntityPigan);
			pathEntity = "Data\\Entities\\e_pigan.cfg";
		} else if (type.substr(2, 5) == "swing") {
			doRandomizeDirection = false;
			addEntity(new cEntity);
			pathEntity = "Data\\Entities\\e_swing.cfg";
		} else if (type.substr(2, 5) == "train") {
			doRandomizeDirection = false;
			addEntity(new cEntityTrain);

			int numEntity = 0;
			if (type.size() == 9) {
				numEntity = atoi(type.substr(8, 1).c_str());
			} else if (type.size() == 10) {
				numEntity = atoi(type.substr(8, 2).c_str());
			}
			getEntityLast()->setNumber(numEntity);

			std::cout << "\n" << "\n" << "LoadLevel train entity " << numEntity << "\n" << "\n";

			for (unsigned short i = 0; i < m_attachedApp->getTrainNumber(numEntity).size(); ++i) {
				getEntityLast()->addPathNumber(m_attachedApp->getTrainNumber(numEntity).at(i));
			}
			std::cout << "cLevel::loadEntity trainPath " << numEntity << " = " << m_attachedApp->getTrainPath(numEntity) << "\n";

			if (m_attachedApp->getTrainPath(numEntity).empty() || m_attachedApp->getTrainPath(numEntity).substr(0, 4) != "Data") {
				pathEntity = "Data\\Entities\\e_train_saw.cfg";
			} else {
				pathEntity = m_attachedApp->getTrainPath(numEntity);
			}
		} else if (type.substr(2, 4) == "rain") {
			addEntity(new cEntityRain);
			pathEntity.clear();
			pathEntity = "Data\\Entities\\e_rain.cfg";
		} else if (type.substr(2, 4) == "snow") {
			addEntity(new cEntitySnow);
			pathEntity.clear();
			pathEntity = "Data\\Entities\\e_snow.cfg";
		}

		getEntityLast()->setIsEntity(true);
		getEntityLast()->setType(type);
		getEntityLast()->setLayer(z);
		getEntityLast()->setNumHealth(1.0f);
		getEntityLast()->loadConfig(pathEntity);
		getEntityLast()->setX(-numToBeCreated * 2 + i * 4 + getEntityLast()->getOffsetX() + getTileObject(z, x, y)->getX() + getTileObject(z, x, y)->getWidth() / 2 - getEntityLast()->getWidth() / 2);
		getEntityLast()->setY(getEntityLast()->getOffsetY() + getTileObject(z, x, y)->getY() + 16 - getEntityLast()->getHeight());
		getEntityLast()->setStartX(getEntityLast()->getX());
		getEntityLast()->setStartY(getEntityLast()->getY());
		getEntityLast()->setOldStartX(getEntityLast()->getStartX());
		getEntityLast()->setOldStartY(getEntityLast()->getStartY());
		getEntityLast()->setLevelX(getEntityLast()->getStartX());
		getEntityLast()->setLevelY(getEntityLast()->getStartY());
		getEntityLast()->attachLevel(this);
		getEntityLast()->attachPlayer(m_attachedPlayer);

		char randNum = (rand() % 2);
		if (randNum == 0 || !doRandomizeDirection) {
			getEntityLast()->setIsFacingLeft(false);
		} else {
			getEntityLast()->setIsFacingLeft(true);
		}
		//getEntityLast()->update(app, 0.0f);
	}
}