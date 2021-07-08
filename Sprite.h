#pragma once

#include <string>
#include <SFML/Graphics.hpp>

//#include "Object.h"
//#include "Particle.h"

class cSprite
{
public:
	cSprite();
	//cSprite(const cBaseObject& other);
	//cSprite& operator=(const cBaseObject& other);
	//~cSprite();
	//void update(float time);
	unsigned char getColor(char element)	const;			void setColor(int r, int g, int b);
	float getOriginX()		const { return m_originX; };	void setOriginX(float originX) { m_originX = originX; };
	float getOriginY()		const { return m_originY; };	void setOriginY(float originY) { m_originY = originY; };
	float getX()			const { return m_x; };			void setX(float x);
	float getY()			const { return m_y; };			void setY(float y);	
	void setPosition(float x, float y);	

	void setRectX(unsigned short rectX);
	void setRectY(unsigned short rectY);
	void setRectWidth(unsigned short rectWidth);
	void setRectHeight(unsigned short rectHeight);

	void setScale(float factorX, float factorY);
	
	void rotate(float angle);
	void setRotation(float angle);
	void setOrigin(float x, float y);

	void setTexture(std::string imagePath);
	void setTextureRect(unsigned short rectX, unsigned short rectY, unsigned short rectWidth, unsigned short rectHeight);

	sf::Sprite* getSfSprite() { return &m_sfSprite; };
	//sf::Shader* getSfShader() { return &m_sfShader; };

protected:
	sf::Sprite m_sfSprite;
	float m_x, m_y, m_originX, m_originY;		
	unsigned short m_rectX, m_rectY, m_rectWidth, m_rectHeight;
	unsigned char m_r, m_g, m_b;
};