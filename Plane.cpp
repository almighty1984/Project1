#include "Plane.h"
#include <iostream>
#include <sstream>

cPlane::cPlane() :	m_secondCall(false), m_numColumns(0), m_numRows(0), m_numSwitchedRows(0),
					m_x(0.0f), m_y(0.0f), m_startX(0.0f), m_startY(0.0f),
					m_previousX(0.0f), m_previousY(0.0f),
					m_velocityX(0.0f), m_velocityY(0.0f),
					m_scrollX(0.0f), m_scrollY(0.0f),
					m_pathImage(""),
					m_path(""), m_pathNext(""),
					m_doSwitchRow(false) {
}


cPlane::~cPlane() {
	clear();
	m_path.clear();
	m_pathNext.clear();
	m_planeObjects.clear();
	m_pathImage.clear();
}

void cPlane::clear() {
	std::cout << "cPlane::clear()" << "\n";
	m_secondCall = false;
	//m_planeObjects.clear();
	m_numSwitchedRows = 0;
	m_numColumns = 0;
	m_numRows = 0;
	m_x = -(float)m_width/* / 2*/;
	m_y = 0.0f;
	m_startX = 0.0f;
	m_startY = 0.0f;
	m_previousX = 0.0f;
	m_previousY = 0.0f;
	m_velocityX = 0.0f;
	m_velocityY = 0.0f;
	m_scrollX = 0.0f;
	m_scrollY = 0.0f;
	//m_pathImage.clear();
	//m_path.clear();
	//m_pathNext.clear();
	m_doSwitchRow = false;
}

void cPlane::loadPlaneConfig(std::string fileName, unsigned char planeNumber) {
	m_path = fileName;
	std::ifstream dataFile(fileName.c_str());

	// Verify the data file was opened; exit if not.
	if (!dataFile) {
		std::cout << "Error:  Cannot open file " << fileName << "\n";
		//exit( 1 );
		return;
	}

	std::istringstream iStr(std::ios_base::out);
	char buf[240] = { 0 };
	std::string firstField, secondField, data, data2;
	firstField.clear();
	secondField.clear();
	data.clear();
	data2.clear();

	m_numColumns = 3;
	m_numRows = 2;

	//m_velocityX = -1.0f;

	// Go back to beginning
	//std::cout << "Go back to beginning" << "\n";
	dataFile.clear();
	dataFile.seekg(0, std::ios::beg);

	// Create the planes
	//std::cout << "Create the planes" << "\n";
	//m_planeObjects = new cObject*[m_numLayers];

	/*for (unsigned short z = 0; z < m_numLayers; ++z) {
		std::cout << "Create the planes objects" << "\n";*/
		//m_planeObjects = new cObject[m_numColumns*m_numRows];
	//}

	while (!dataFile.eof()) {
		/*for (unsigned short z = 0; z < m_numLayers; ++z) {*/
		dataFile.getline(buf, sizeof(buf));

		iStr.str(std::string(buf));
		iStr >> firstField >> secondField;
		iStr.clear();
		iStr.str("");

		int tmpInt = 0;
		std::istringstream(firstField) >> tmpInt;

		if (tmpInt == planeNumber && secondField == "{") {
			while (firstField != "}" && secondField != "}" && dataFile.peek() != '}') {
				//std::cout << "FOUND A LAYER!!!!!!!!!!!!" << "\n";
				dataFile.getline(buf, sizeof(buf));

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data;
				iStr.clear();
				iStr.str("");

				if (firstField == "image") {
					m_pathImage = data;
				} else if (firstField == "width") {
					std::istringstream(data) >> m_width;
					std::cout << "width = " << m_width << "\n";
					m_x = -(float)m_width / 2;
				} else if (firstField == "height") {
					std::istringstream(data) >> m_height;
					std::cout << "height = " << m_height << "\n";
				} else if (firstField == "velocityX") {
					if (data.at(0) == '-') {
						data.erase(data.begin(), data.begin() + 1);
						m_velocityX = -(float)atof(data.c_str());
					} else {
						m_velocityX = (float)atof(data.c_str());
					}
				} else if (firstField == "velocityY") {
					if (data.at(0) == '-') {
						data.erase(data.begin(), data.begin() + 1);
						m_velocityY = -(float)atof(data.c_str());
					} else {
						m_velocityY = (float)atof(data.c_str());
					}
				} else if (firstField == "scrollX") {
					if (data.at(0) == '-') {
						data.erase(data.begin(), data.begin() + 1);
						m_scrollX = -(float)atof(data.c_str());
					} else {
						m_scrollX = (float)atof(data.c_str());
					}
				} else if (firstField == "scrollY") {
					if (data.at(0) == '-') {
						data.erase(data.begin(), data.begin() + 1);
						m_scrollY = -(float)atof(data.c_str());
					} else {
						m_scrollY = (float)atof(data.c_str());
					}
				}
			}
			for (unsigned short y = 0; y < m_numRows; ++y) {
				for (unsigned short x = 0; x < m_numColumns; ++x) {
					m_planeObjects.push_back(new cObject);
					m_planeObjects.at(x + y * m_numColumns)->setImagePath(m_pathImage);
					m_planeObjects.at(x + y * m_numColumns)->setIsHidden(true);
					m_planeObjects.at(x + y * m_numColumns)->setWidth(m_width);					
					m_planeObjects.at(x + y * m_numColumns)->setX((float)(x * m_width)-m_width/*/2*/);
					m_planeObjects.at(x + y * m_numColumns)->setStartX(m_planeObjects.at(x + y * m_numColumns)->getX());
					m_planeObjects.at(x + y * m_numColumns)->setVelocityX(m_velocityX);
					m_planeObjects.at(x + y * m_numColumns)->setStartVelocityX(m_velocityX);
					//std::cout << "velocityX = " << m_velocityX << "\n";
					m_planeObjects.at(x + y * m_numColumns)->setHeight(m_height);
					m_planeObjects.at(x + y * m_numColumns)->setY((float)(y * m_height)/* + m_height*/);
					m_planeObjects.at(x + y * m_numColumns)->setStartY(m_planeObjects.at(x + y * m_numColumns)->getY());
					m_planeObjects.at(x + y * m_numColumns)->setVelocityY(m_velocityY);
					m_planeObjects.at(x + y * m_numColumns)->setStartVelocityY(m_velocityY);
					m_planeObjects.at(x + y * m_numColumns)->setType("plane");
					m_planeObjects.at(x + y * m_numColumns)->update(0.0f);
				}
			}
			m_startX = m_planeObjects.at(0)->getX();
			m_startY = m_planeObjects.at(0)->getY();
		}
	}
	dataFile.close();
	//std::cout << "Planes loaded" << "\n";
}

void cPlane::setIsHidden(bool isHidden) {
	if (m_planeObjects.empty()) {
		return;
	}
	for (auto it = m_planeObjects.begin(); it != m_planeObjects.end(); ++it) {
		if ((*it) != nullptr) {
			(*it)->setIsHidden(isHidden);
		}
	}
}

void cPlane::setColor(unsigned char red, unsigned char green, unsigned char blue) {
	if (m_planeObjects.empty()) {
		return;
	}
	for (auto it = m_planeObjects.begin(); it != m_planeObjects.end(); ++it) {
		if ((*it) != nullptr) {
			(*it)->setColor(red, green, blue);
		}
	}
}

void cPlane::setX(float positionX) {
	//m_referenceObject.setX(m_referenceObject.getX() - x * m_scrollX);

	m_x = m_x - positionX * m_scrollX;

	for (unsigned short y = 0; y < m_numRows; ++y) {
		for (unsigned short x = 0; x < m_numColumns; ++x) {
			m_planeObjects.at(x + y * m_numColumns)->setX(m_planeObjects.at(x + y * m_numColumns)->getX() - positionX * m_scrollX);
			//m_planeObjects.at(x + y * m_numColumns)->setX(m_referenceObject.getX() + x * m_width);
		}
	}


	/*std::cout << abs(x - m_previousX) << "\n";
	if (abs(x - m_previousX) < 2.0f) {
		return;
	}*/
	/*m_x = x;

	if (!m_planeObjects.empty()) {
		m_planeObjects.at(0)->setX(x);

		for (unsigned short x = 1; x < m_numColumns; ++x) {
			for (unsigned short y = 0; y < m_numRows; ++y) {
				m_planeObjects.at(x + y * m_numColumns)->setX((float)((int)(m_planeObjects.at(0)->getX()) + 256 * x));
			}
		}
	}*/
	/*
	for (unsigned short y = 0; y < m_numRows; ++y) {
		for (unsigned short x = 0; x < m_numColumns; ++x) {
			m_planeObjects.at(x + y * m_numColumns)->setX(x + m_planeObjects.at(x + y * m_numColumns)->getWidth() * x);
		}
	}*/
}

void cPlane::setY(float positionY) {
	//m_referenceObject.setY(m_referenceObject.getY() - y * m_scrollY);
	m_y = m_y - positionY * m_scrollY;

	for (unsigned short y = 0; y < m_numRows; ++y) {
		for (unsigned short x = 0; x < m_numColumns; ++x) {
			//m_planeObjects.at(x + y * m_numColumns)->setY(m_height * y + m_referenceObject.getY());
			m_planeObjects.at(x + y * m_numColumns)->setY(m_planeObjects.at(x + y * m_numColumns)->getY() - positionY * m_scrollY);
		}
	}

	/*m_y = positionY;
	if (!m_planeObjects.empty()) {
		m_planeObjects.at(0)->setY(positionY);
		for (unsigned short x = 1; x < m_numColumns; ++x) {
			for (unsigned short y = 0; y < m_numRows; ++y) {
				m_planeObjects.at(x + y * m_numColumns)->setY((float)((int)(m_planeObjects.at(0)->getY()) + 256 * y));
			}
		}
	}*/
	/*	
	for (unsigned short y = 0; y < m_numRows; ++y) {
		for (unsigned short x = 0; x < m_numColumns; ++x) {
			m_planeObjects.at(x + y * m_numColumns)->setY(positionY + m_planeObjects.at(x + y * m_numColumns)->getHeight() * y);
		}
	}*/
}

//void cPlane::createPlanes() {
//	m_planes = new cObject*[m_numPlanes];
//
//	for (unsigned short i = 0; i<m_numPlanes; ++i) {
//		m_planes[i] = new cObject[m_numColumns];
//	}
//
//	for (unsigned char i = 0; i < m_numPlanes; ++i) {
//		for (unsigned short j = 0; j < m_numColumns; ++j) {
//			m_planes[i][j].setX(j * 320 - 64);
//			m_planes[i][j].setY(0);
//			m_planes[i][j].setWidth(320);
//			m_planes[i][j].setHeight(480);
//
//			m_planes[i][j].setImagePath("Data\\Objects\\Images\\background_blue.png");
//		}
//	}
//}

void cPlane::update(cApp *app, float time) {
	if (m_planeObjects.empty()) {
		return;
	}
	if (!m_secondCall) {
		m_secondCall = true;
		if (app->getWeatherColor() < 255.0f) {
			setIsHidden(false);
		}
	}

	m_x += m_velocityX;
	m_y += m_velocityY;

	//std::cout << m_x - m_startX << " " << m_planeObjects.at(0)->getX() - m_planeObjects.at(0)->getStartX() << "\n";

	if (m_x - m_startX < -128.0f) {
		m_x += 256.0f;		
	} else if (m_x - m_startX > 128.0f) {
		m_x -= 256.0f;
	}

	for (unsigned short y = 0; y < m_numRows; ++y) {
		for (unsigned short x = 0; x < m_numColumns; ++x) {
			if (!m_planeObjects.empty() && m_planeObjects.at(x + y * m_numColumns) != nullptr) {
				m_planeObjects.at(x + y * m_numColumns)->setX(m_x + x * 256);
				m_planeObjects.at(x + y * m_numColumns)->setY(m_y + y * 256);

				m_planeObjects.at(x + y * m_numColumns)->update(time);
			}
		}
	}
}
