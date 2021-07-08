#pragma once

#include "Object.h"
#include "App.h"
//#include "SDL.h"
#include <string>
#include <iostream>

#include "Sprite.h"

class cBitmapFont : public cObject
{
public:
	cBitmapFont();
	~cBitmapFont();
	
	virtual void update(float time);

	virtual void setColor(unsigned char r, unsigned char g, unsigned char b);

	void setFontSize(unsigned short fontSize);
	void setText(std::string text);
	std::string getText();
	void clearText();

	unsigned short getFontSize() { return m_fontSize; };

	int getTextSize() { return m_text.size(); };

	virtual void setImagePath(std::string imagePath);

	void setCharLimit(unsigned short charLimit) { m_charLimit = charLimit; };
	
	std::vector<cSprite*> m_sprites;

	unsigned short* m_charOffsetX;
	unsigned short* m_charOffsetY;
	unsigned short* m_charLineNumber;

	cSprite* getSprite(unsigned short i);
private:
	unsigned short m_charLimit;
	std::string m_text;

	unsigned short m_fontSize;
};
