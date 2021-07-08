#include "TextBox.h"
#include "RenderingManager.h"
#include "SavesManager.h"
#include <iostream>
#include <sstream>

cTextBox::cTextBox() :
m_doHide(false), m_isHidden(false),
m_fontSize(8), m_tileSize(16), m_fontPath(""),
m_numColumns(1), m_numRows(1),m_timerHide(0),
m_x(0.0f), m_y(0.0f),
m_previousX(0.0f), m_previousY(0.0f),
m_velocityX(0.0f), m_velocityY(0.0f),
m_pathUpLeft(""), m_pathUp(""), m_pathUpRight(""),
m_pathLeft(""), m_pathCenter(""), m_pathRight(""),
m_pathDownLeft(""), m_pathDown(""), m_pathDownRight("") {

}

cTextBox::~cTextBox() {
	clear();
}

void cTextBox::clear() {
	for (unsigned short y = 0; y < m_numRows; ++y) {
		for (unsigned short x = 0; x < m_numColumns; ++x) {
			cRenderingManager::removeObject(m_boxObjects.at(x + y * m_numColumns));
		}
	}
	cRenderingManager::removeBitmapFont(&m_bitmapFont);
	m_fontSize = 8;
	m_tileSize = 16;
	m_doHide = false;
	m_isHidden = false;
	m_numColumns = 1;
	m_numRows = 1;
	m_timerHide = 0;
	m_x = m_y = m_previousX = m_previousY = m_velocityX = m_velocityY = 0.0f;
	m_pathUpLeft.clear();
	m_pathUp.clear();
	m_pathUpRight.clear();
	m_pathLeft.clear();
	m_pathCenter.clear();
	m_pathRight.clear();
	m_pathDownLeft.clear();
	m_pathDown.clear();
	m_pathDownRight.clear();
	m_boxObjects.clear();	
}

void cTextBox::loadConfig(std::string fileName) {
	std::ifstream dataFile(fileName.c_str());

	// Verify the data file was opened; exit if not.
	if (!dataFile) {
		std::cout << "Error:  Cannot open file " << fileName << "\n";
		//exit( 1 );
		dataFile.open("Data\\TextBoxes\\5000_5000.cfg");
	}
	m_textMap.clear();

	std::istringstream iStr(std::ios_base::out);
	char buf[240] = { 0 };
	std::string firstField, secondField, data, data2;
	firstField.clear();
	secondField.clear();
	data.clear();
	data2.clear();

	while (!dataFile.eof()) {
		/*for (unsigned short z = 0; z < m_numLayers; ++z) {*/
		dataFile.getline(buf, sizeof(buf));

		iStr.str(std::string(buf));
		iStr >> firstField >> secondField;
		iStr.clear();
		iStr.str("");

		if (firstField == "Config" && secondField == "{") {
			while (firstField != "}" && secondField != "}" && dataFile.peek() != '}') {
				dataFile.getline(buf, sizeof(buf));

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data;
				iStr.clear();
				iStr.str("");
				if (firstField == "fontPath") {
					m_fontPath = data;
				} else if (firstField == "fontSize") {
					std::istringstream(data) >> m_fontSize;
					std::cout << "TextBox fontSize = " << (int)m_fontSize << "\n";
				} else if (firstField == "doHide") {
					if (data == "true") {
						m_doHide = true;
					} else if (data == "false") {
						m_doHide = false;
					} else {
						std::cout << "doHide illegal value " << data << "\n";
					}
				}
				/*else if (firstField == "timerHide") {
					std::istringstream(data) >> m_timerHide;
				}*/
				else if (firstField == "tileSize") {
					std::istringstream(data) >> m_tileSize;
					std::cout << "TextBox tileSize = " << m_tileSize << "\n";
				} else if (firstField == "upLeft") {
					m_pathUpLeft = data;
				} else if (firstField == "up") {
					m_pathUp = data;
				} else if (firstField == "upRight") {
					m_pathUpRight = data;
				} else if (firstField == "left") {
					m_pathLeft = data;
				} else if (firstField == "center") {
					m_pathCenter = data;
				} else if (firstField == "right") {
					m_pathRight = data;
				} else if (firstField == "downLeft") {
					m_pathDownLeft = data;
				} else if (firstField == "down") {
					m_pathDown = data;
				} else if (firstField == "downRight") {
					m_pathDownRight = data;
				}
			}
		} else if (firstField == "Text") {
			while (dataFile.peek() != '}') {
				dataFile.getline(buf, sizeof(buf));

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data;
				iStr.clear();
				iStr.str("");
				
				if (secondField == "=") {
					m_textMap[firstField] = data;
					std::cout << "\n" << firstField << " = " << m_textMap[firstField] << "\n" << "\n";

					size_t found = data.find("#NAME#");
					if (found != std::string::npos) {
						std::cout << "First occurrence is " << found << "\n";
						m_textMap[firstField].erase(found, 6);
						m_textMap[firstField].insert(found, cSavesManager::getPlayerName());
					}
					found = 0;
					found = data.find("#SLOT#");
					if (found != std::string::npos) {
						std::cout << "First occurrence is " << found << "\n";
						m_textMap[firstField].erase(found, 6);
						std::stringstream ss;
						ss << (int)(cSavesManager::getSlotNumber());
						m_textMap[firstField].insert(found, ss.str() );
					}
				}
			}
		}
	}

	dataFile.close();

	cRenderingManager::addBitmapFont(&m_bitmapFont);
	std::cout << "TextBox config loaded" << "\n";
}

void cTextBox::setupBoxObjects(unsigned char numColumns, unsigned char numRows) {
	m_boxObjects.clear();
	m_numColumns = numColumns;
	m_numRows = numRows;
	for (unsigned char y = 0; y < numRows; ++y) {
		for (unsigned char x = 0; x < numColumns; ++x) {
			m_boxObjects.push_back(new cObject);
			// First row
			if (y == 0) {
				if (x == 0) {
					m_boxObjects.at(x + y * numColumns)->setImagePath(m_pathUpLeft);
				} else if (x == numColumns - 1) {
					m_boxObjects.at(x + y * numColumns)->setImagePath(m_pathUpRight);
				} else {
					m_boxObjects.at(x + y * numColumns)->setImagePath(m_pathUp);
				}
			}
			// Last row
			else if (y == numRows - 1) {
				if (x == 0) {
					m_boxObjects.at(x + y * numColumns)->setImagePath(m_pathDownLeft);
				} else if (x == numColumns - 1) {
					m_boxObjects.at(x + y * numColumns)->setImagePath(m_pathDownRight);
				} else {
					m_boxObjects.at(x + y * numColumns)->setImagePath(m_pathDown);
				}
			}
			//Middle rows
			else {
				if (x == 0) {
					m_boxObjects.at(x + y * numColumns)->setImagePath(m_pathLeft);
				} else if (x == numColumns - 1) {
					m_boxObjects.at(x + y * numColumns)->setImagePath(m_pathRight);
				} else {
					m_boxObjects.at(x + y * numColumns)->setImagePath(m_pathCenter);
				}
			}

			m_boxObjects.at(x + y * numColumns)->setX((float)x * m_tileSize);
			m_boxObjects.at(x + y * numColumns)->setY((float)y * m_tileSize);
			m_boxObjects.at(x + y * numColumns)->setWidth(m_tileSize);
			m_boxObjects.at(x + y * numColumns)->setHeight(m_tileSize);

			cRenderingManager::addObject(m_boxObjects.at(x + y * numColumns));
		}
	}
}

void cTextBox::setTextFromKey(std::string key) {
	setText(getTextFromKey(key));
}
std::string cTextBox::getTextFromKey(std::string key) {
	return m_textMap[key];
}
void cTextBox::setText(std::string text) {
	m_bitmapFont.clearText();
	m_bitmapFont.setX(m_x + 8);
	m_bitmapFont.setY(m_y + 8);
	m_bitmapFont.setFontSize(8);
	m_bitmapFont.setWidth((m_numColumns - 1) * m_tileSize);
	m_bitmapFont.setHeight((m_numRows - 1) * m_tileSize);
	m_bitmapFont.setImagePath("Data\\Fonts\\font_8_brown.png");
	m_bitmapFont.setText(text);
}

void cTextBox::setColor(unsigned char r, unsigned char g, unsigned char b) {
	m_bitmapFont.setColor(r, g, b);
	for (auto it = m_boxObjects.begin(); it != m_boxObjects.end(); ++it) {
		(*it)->setColor(r, g, b);
	}
}

void cTextBox::setIsHidden(bool isHidden) {
	m_isHidden = isHidden;

	for (auto it = m_boxObjects.begin(); it != m_boxObjects.end(); ++it) {
		(*it)->setIsHidden(isHidden);
	}
	m_bitmapFont.setIsHidden(isHidden);
}
void cTextBox::setX(float positionX) {
	m_x = positionX;
	m_bitmapFont.setX(positionX + 8);
	if (m_boxObjects.empty()) {
		return;
	}
	for (unsigned short y = 0; y < m_numRows; ++y) {
		for (unsigned short x = 0; x < m_numColumns; ++x) {
			m_boxObjects.at(x + y * m_numColumns)->setX(positionX + m_boxObjects.at(x + y * m_numColumns)->getWidth() * x);
		}
	}
}

void cTextBox::setY(float positionY) {
	m_y = positionY;
	m_bitmapFont.setY(positionY + 8);
	
	if (m_boxObjects.empty()) {
		return;
	}
	for (unsigned short y = 0; y < m_numRows; ++y) {
		for (unsigned short x = 0; x < m_numColumns; ++x) {
			m_boxObjects.at(x + y * m_numColumns)->setY(positionY + m_boxObjects.at(x + y * m_numColumns)->getHeight() * y);			
		}
	}
}

void cTextBox::update(float time) {
	if (m_doHide) {
		if (m_timerHide > 0) {
			--m_timerHide;
			setIsHidden(false);
		} else {
			setIsHidden(true);
			m_timerHide = 0;
		}
	}
	m_bitmapFont.update(time);
	/*m_previousX = m_x;
	m_previousY = m_y;
	m_x += m_velocityX;
	m_y += m_velocityY;*/
	//std::cout << "cTextBox::update" << m_y << "\n";

	for (auto it = m_boxObjects.begin(); it != m_boxObjects.end(); ++it) {
		(*it)->update(time);
	}
}
