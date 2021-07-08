#pragma once

//#include <vector>

#include "Object.h"
#include "BitmapFont.h"

class cTextBox {
public:
	cTextBox();
	~cTextBox();

	void clear();
	void clearText() { m_bitmapFont.clearText(); };

	bool getIsHidden() const { return m_isHidden; }					void setIsHidden(bool isHidden);
	void setColor(unsigned char r, unsigned char g, unsigned char b);

	void update(float time);
	void loadConfig(std::string fileName);
	float getX() const { return m_x; }						void setX(float positionX);
	float getY() const { return m_y; }						void setY(float positionY);	

	float getVelocityX() const { return m_velocityX; }				void setVelocityX(float velocityX) { m_velocityX = velocityX; }	
	float getVelocityY() const { return m_velocityY; }				void setVelocityY(float velocityY) { m_velocityY = velocityY; }

	unsigned char getNumColumns()	const { return m_numColumns; }	void setNumColumns(unsigned char numColumns)	{ m_numColumns = numColumns; };
	unsigned char getNumRows()		const { return m_numRows; }		void setNumRows(unsigned char numRows)			{ m_numRows = numRows; };

	unsigned short getTileSize()	const { return m_tileSize; };

	short getTimerHide()	const { return m_timerHide; }			void setTimerHide(short timerHide) { m_timerHide = timerHide; };
	bool getDoHide()		const { return m_doHide; }				void setDoHide(bool doHide) { m_doHide = doHide; };

	void setupBoxObjects(unsigned char numColumns, unsigned char numRows);

	//void setSlotNumber(unsigned char slotNumber) { m_slotNumber = slotNumber; };

	std::string getText() { return m_bitmapFont.getText(); };	void setText(std::string text);
	std::string getTextFromKey(std::string key);				void setTextFromKey(std::string key);
		
private:
	cBitmapFont m_bitmapFont;
	bool m_isHidden, m_doHide;
	short m_timerHide;
	unsigned char m_numColumns, m_numRows;
	unsigned short m_tileSize;
	unsigned char m_fontSize;
	std::string m_fontPath;

	//unsigned char m_slotNumber;
	//unsigned short m_width, m_height;

	float m_x, m_y;
	float m_previousX, m_previousY;
	float m_velocityX, m_velocityY;
	
	std::string m_pathUpLeft, m_pathUp, m_pathUpRight, m_pathLeft, m_pathCenter, m_pathRight, m_pathDownLeft, m_pathDown, m_pathDownRight;

	std::vector<cObject*> m_boxObjects;
	std::map<std::string, std::string> m_textMap;
};