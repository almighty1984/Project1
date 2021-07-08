#include "TextureManager.h"

#include "RenderingManager.h"
#include "BitmapFont.h"

cBitmapFont::cBitmapFont() :	m_fontSize(8), m_charLimit(8),
								m_charOffsetX(nullptr), m_charOffsetY(nullptr), m_charLineNumber(nullptr),
								m_text("") {
	m_text.clear();
	m_sprites.clear();
	m_imagePath.clear();
	m_imagePath = cRenderingManager::getPathFont();
}

cBitmapFont::~cBitmapFont() {
	//std::cout << "~cBitmapFont()" << "\n";
	clearText();
	m_connectedObjects.clear();
	m_imagePath.clear();
}

void cBitmapFont::setImagePath(std::string imagePath) {
	m_imagePath = imagePath;
}

void cBitmapFont::setFontSize(unsigned short fontSize) {
	m_fontSize = fontSize;
}

void cBitmapFont::clearText() {	
	if (m_charOffsetX != nullptr) {
		delete [] m_charOffsetX;
		m_charOffsetX = nullptr;
	}
	if (m_charOffsetY != nullptr) {
		delete [] m_charOffsetY;
		m_charOffsetY = nullptr;
	}
	if (m_charLineNumber != nullptr) {
		delete [] m_charLineNumber;
		m_charLineNumber = nullptr;
	}
	
	m_text.clear();
	m_sprites.clear();
}

cSprite* cBitmapFont::getSprite(unsigned short i) {
	if (m_sprites.at(i) != nullptr) {
		return m_sprites.at(i);
	} else {
		return nullptr;
	}
}

std::string cBitmapFont::getText() {	
	if (m_text.empty()) {
		//std::cout << "m_text empty" << "\n";
		return "";
	}
	return m_text;
}

void cBitmapFont::setText(std::string text) {
	/*if (m_text == text.c_str()) {
		return;
	}*/
	clearText();	
	
	size_t size = text.size();
		
	unsigned short lineNumber = 0;
	unsigned short extraSpace = (m_width / 8 + m_height / 8) * 3;

	if (m_width > 128) {
		std::cout << "EXTRASPACE = " << extraSpace << "\n";
	}

	// Size + extra characters for padding when there's a new line character
	m_charLineNumber = new unsigned short[size + extraSpace];
	m_charOffsetX = new unsigned short[size + extraSpace];
	m_charOffsetY = new unsigned short[size + extraSpace];

	//m_lineNumber.push_back(new unsigned short[size]);

	for (unsigned short i = 0; i < size; ++i) {		
		if (i > (m_width / 8) - 1) {
			lineNumber = 1;
		}
		if (i > (m_width * 2) / 8 - 1) {
			lineNumber = 2;
		}
		if (i > (m_width * 3) / 8 - 1) {
			lineNumber = 3;
		}
		if (i > (m_width * 4) / 8 - 1) {
			lineNumber = 4;
		}
		if (i > (m_width * 5) / 8 - 1) {
			lineNumber = 5;
		}
		m_charLineNumber[i] = lineNumber;

		//std::cout << "m_charLineNumber[i] = " << lineNumber << "\n";		
		if (text.substr(i, 1) == "¤") {
			std::cout << m_width/8 << "\n";
			int padding = 0;
			if (lineNumber == 0) {
				padding = m_width / 8 - i;
				std::cout << padding << "\n";
			} else  if (lineNumber == 1) {
				padding = m_width * 2 / 8 - i;
			} else  if (lineNumber == 2) {
				padding = m_width * 3 / 8 - i;
			} else  if (lineNumber == 3) {
				padding = m_width * 4 / 8 - i;
			} else  if (lineNumber == 4) {
				padding = m_width * 5 / 8 - i;
			} else  if (lineNumber == 5) {
				padding = m_width * 6 / 8 - i;
			}
			
			for (int j = 0; j < padding-1; ++j) {
				text.insert(i, "å");
				++size;
				++i;
			}	
			std::cout << "HELLO FOUND SOMETHING HERE" << "\n";
		}
	}	
	
	m_text = text;
	
	for (unsigned short i = 0; i < m_text.size(); ++i) {
		m_sprites.push_back(new cSprite);
		m_charOffsetX[i] = 0;
		m_charOffsetY[i] = 0;
		for (unsigned short y = 0; y < 32; ++y) {
			for (unsigned short x = 0; x < 32; ++x) {			
				if (m_text.at(i) == 32 + x + y * 32) {					
					m_charOffsetX[i] = (unsigned short)(x * m_fontSize);
					m_charOffsetY[i] = (unsigned short)(y * m_fontSize);					
				}
			}
		}
		m_sprites.at(m_sprites.size() - 1)->setTexture(m_imagePath);
		m_sprites.at(m_sprites.size() - 1)->setTextureRect(m_charOffsetX[i], m_charOffsetY[i], m_fontSize, m_fontSize);
	}
}

void cBitmapFont::update(float time) {
	m_x += m_velocityX;
	m_y += m_velocityY;

	if (m_text.empty() == false) {
		for (unsigned short i=0; i<m_text.size(); ++i) {
			if (m_sprites.at(i) != nullptr) {
				/*float tmpOffsetX=0.0f;
				if(m_charLineNumber[i] > 0)
					tmpOffsetX = -8.0f;*/

				m_sprites.at(i)->setPosition(m_x + i * m_fontSize - m_charLineNumber[i] * (m_width / 8) * m_fontSize, m_y + m_charLineNumber[i] * m_fontSize);
				//m_spriteArray[i].setPosition(m_x+i*m_fontSize-m_charLineNumber[i]*(m_width/8)*m_fontSize, m_y+m_charLineNumber[i]*m_fontSize);
			}
		}
	}
}

void cBitmapFont::setColor(unsigned char r, unsigned char g, unsigned char b) {
	for (auto it = m_sprites.begin(); it != m_sprites.end(); ++it) {
		if ((*it) != nullptr) {
			(*it)->setColor(r, g, b);
		}
	}
}