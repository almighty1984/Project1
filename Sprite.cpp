#include "Sprite.h"
#include "TextureManager.h"

cSprite::cSprite()	:	m_x(0.0f), m_y(0.0f),
						m_originX(0.0f), m_originY(0.0f),
						m_rectX(0), m_rectY(0),
						m_rectWidth(0), m_rectHeight(0),
						m_r(0), m_g(0), m_b(0) {
}

unsigned char cSprite::getColor(char element) const {
	switch (element) {
	case 'r':	return m_r;
	case 'g':	return m_g;
	case 'b':	return m_b;
	default:	return 0;
	}
}

void cSprite::setColor(int r, int g, int b) {
	if (r < 0) r = 0;
	if (r > 255) r = 255;
	if (g < 0) g = 0;
	if (g > 255) g = 255;
	if (b < 0) b = 0;
	if (b > 255) b = 255;
	
	m_sfSprite.setColor(sf::Color(r, g, b));
	m_r = r;
	m_g = g;
	m_b = b;
}

void cSprite::setX(float x) {
	m_x = x;
	m_sfSprite.setPosition(m_x, m_y);
}

void cSprite::setY(float y) {
	m_y = y;
	m_sfSprite.setPosition(m_x, m_y);
}

void cSprite::setPosition(float x, float y) {
	m_x = x;
	m_y = y;
	m_sfSprite.setPosition(m_x/*+m_originX*/, m_y/*+m_originY*/);
}

void cSprite::setRectX(unsigned short rectX) {
	m_rectX = rectX;
}

void cSprite::setRectY(unsigned short rectY) {
	m_rectY = rectY;
}

void cSprite::setRectWidth(unsigned short rectWidth) {
	m_rectWidth = rectWidth;
}

void cSprite::setRectHeight(unsigned short rectHeight) {
	m_rectHeight = rectHeight;
}

void cSprite::setScale(float factorX, float factorY) {
	m_sfSprite.setScale(factorX, factorY);
}

void cSprite::setRotation(float angle) {
	m_sfSprite.setRotation(angle);
}

void cSprite::rotate(float angle) {
	m_sfSprite.rotate(angle);
}

void cSprite::setOrigin(float x, float y) {
	m_sfSprite.setOrigin(x, y);

	/*sf::Vector2f v = m_sfSprite.getPosition();
	v.x = x;
	v.y = y;
	m_sfSprite.setPosition(v);*/

	m_originX = x;
	m_originY = y;
}

void cSprite::setTexture(std::string imagePath) {	
	m_sfSprite.setTexture(*cTextureManager::load(imagePath), true);
	m_sfSprite.setTextureRect(sf::IntRect(m_rectX, m_rectY, m_rectWidth, m_rectHeight));
}

void cSprite::setTextureRect(unsigned short rectX, unsigned short rectY, unsigned short rectWidth, unsigned short rectHeight) {
	m_rectX = rectX;
	m_rectY = rectY;
	m_rectWidth = rectWidth;
	m_rectHeight = rectHeight;
	m_sfSprite.setTextureRect( sf::IntRect(m_rectX, m_rectY, m_rectWidth, m_rectHeight) );
}

//void cSprite::update(float time) {
//	m_sfSprite.setPosition(m_x, m_y);
//	m_sfSprite.setTextureRect(sf::IntRect((int)m_rectX, (int)m_rectY, m_rectWidth, m_rectHeight));	
//}