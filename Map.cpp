#include "Map.h"
#include "RenderingManager.h"

sMapSize::sMapSize() : columns(0), rows(0) {
}
sMapSize& sMapSize::operator =(const sMapSize& other) {
	columns = other.columns;
	rows = other.rows;
	return *this;
}
bool sMapSize::operator ==(const sMapSize& other) {
	return (columns == other.columns && rows == other.rows);
}
bool sMapSize::operator !=(const sMapSize& other) {
	return (columns != other.columns || rows != other.rows);
}

cMap::cMap() :	m_startX(0), m_startY(0), m_x(0.0f), m_y(0.0f),
				m_tileData(nullptr), m_tileObjects(nullptr),
				m_isHidden(true) {

}
cMap::~cMap() {
	delete[] m_tileData;
	m_tileData = nullptr;
	delete[] m_tileObjects;
	m_tileObjects = nullptr;
}

void cMap::update(float time) {
	if (m_tileObjects == nullptr) {
		return;
	}
	for (unsigned short i = 0; i < m_size.columns * m_size.rows; ++i) {
		m_tileObjects[i].update(time);
	}
}

sMapSize cMap::getMapSizeFromLevel(std::string pathLevel) {
	std::cout << "getMapSizeFromLevel: " << pathLevel << "\n";
	std::ifstream strFile;
	strFile.open(pathLevel.c_str(), std::ios::in | std::ios::binary);

	unsigned char numLayers = 0;
	unsigned short numColumnsLevel = 0;
	unsigned short numRowsLevel = 0;

	sMapSize mapSize;
	if (strFile.is_open()) {
		strFile.read((char*)&numLayers, sizeof(unsigned char));
		//std::cout << "\n\n\n\n" << (int)numLayers << "\n\n\n\n";
		strFile.read((char*)&numColumnsLevel, sizeof(unsigned short));
		strFile.read((char*)&numRowsLevel, sizeof(unsigned short));
		//std::cout << "numColumnsLevel = " << numColumnsLevel;
		//std::cout << " numRowsLevel = " << numRowsLevel;		
		mapSize.columns = (int)(numColumnsLevel / 20);
		mapSize.rows = (int)(numRowsLevel / 15);		
		std::cout << " m_size.columns = " << (int)m_size.columns;
		std::cout << " m_size.rows = " << (int)m_size.rows;
	}
	strFile.close();
	std::cout << " done.\n";
	return mapSize;
}

void cMap::load(std::string pathMap) {
	std::cout << "cMap::load ";
	if (pathMap.empty()) {
		std::cout << "fileName empty ";
		pathMap = "Data\\Maps\\5000_5000.bin";
	}
	std::cout << pathMap;
	m_tileData = new unsigned short[m_size.columns * m_size.rows];
	for (unsigned short i = 0; i < m_size.columns * m_size.rows; ++i) {
		m_tileData[i] = 0;
	}
	std::ifstream strFile;
	strFile.open(pathMap.c_str(), std::ios::in | std::ios::binary);
	strFile.read((char*)&m_size.columns, sizeof(unsigned char));
	strFile.read((char*)&m_size.rows, sizeof(unsigned char));
	strFile.read((char*)m_tileData, sizeof(unsigned short) * (m_size.columns * m_size.rows));
	strFile.read((char*)&m_startX, sizeof(unsigned short));
	strFile.read((char*)&m_startY, sizeof(unsigned short));
	std::cout << " " << m_startX << " " << m_startY;	

	m_tileObjects = new cObject[m_size.columns * m_size.rows];

	for (unsigned char y = 0; y < m_size.rows; ++y) {
		for (unsigned char x = 0; x < m_size.columns; ++x) {
			unsigned short i = x + y * m_size.columns;

			m_tileObjects[i].setIsDead(false);
			m_tileObjects[i].setIsHidden(true);
			m_tileObjects[i].setType("");
			m_tileObjects[i].setImagePath("Data\\Maps\\tiles_0.png");
			m_tileObjects[i].setX((float)(x * 8));
			m_tileObjects[i].setY((float)(y * 8));
			m_tileObjects[i].setStartX((float)(x * 8));
			m_tileObjects[i].setStartY((float)(y * 8));
			m_tileObjects[i].setWidth(8);
			m_tileObjects[i].setHeight(8);

			//std::cout << "m_tiles " << (int)x << " " << (int)y << " " << m_tiles[i] << "\n";
			m_tileObjects[i].setTile(m_tileData[i]);

			for (unsigned short ty = 0; ty < 32; ++ty) {	//row								
				for (unsigned short tx = 0; tx < 32; ++tx) {  //column
					if (m_tileData[x + y * m_size.columns] == (1 + tx + ty * 32)) {
						m_tileObjects[i].setTileOffsetX((float)(tx * 8));
						m_tileObjects[i].setTileOffsetY((float)(ty * 8));
					}
				}
			}

			cRenderingManager::addObject(&m_tileObjects[i]);
		}
	}
	strFile.close();
	std::cout << " done.\n";
}

void cMap::setX(float positionX) {
	if (m_tileObjects == nullptr) {
		return;
	}
	m_x = positionX;
	for (unsigned char y = 0; y < m_size.rows; ++y) {
		for (unsigned char x = 0; x < m_size.columns; ++x) {
			m_tileObjects[x + y * m_size.columns].setX(m_x + x * 8);
		}
	}
}

void cMap::setY(float positionY) {
	if (m_tileObjects == nullptr) {
		return;
	}
	m_y = positionY;
	for (unsigned char y = 0; y < m_size.rows; ++y) {
		for (unsigned char x = 0; x < m_size.columns; ++x) {
			m_tileObjects[x + y * m_size.columns].setY(m_y + y * 8);
		}
	}
}
void cMap::setIsHidden(bool isHidden) {
	if (m_tileObjects == nullptr) {
		return;
	}
	m_isHidden = isHidden;
	for (unsigned char y = 0; y < m_size.rows; ++y) {
		for (unsigned char x = 0; x < m_size.columns; ++x) {
			m_tileObjects[x + y * m_size.columns].setIsHidden(isHidden);
		}
	}
}

void cMap::setColor(unsigned char r, unsigned char g, unsigned char b) {
	if (m_tileObjects == nullptr) {
		return;
	}
	for (unsigned char y = 0; y < m_size.rows; ++y) {
		for (unsigned char x = 0; x < m_size.columns; ++x) {
			m_tileObjects[x + y * m_size.columns].setColor(r, g, b);
		}
	}
}