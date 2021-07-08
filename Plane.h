#pragma once

//#include <vector>

#include "Object.h"

class cPlane {
public:
	cPlane();
	~cPlane();

	void update(cApp *app, float time);
	void clear();
	void loadPlaneConfig(std::string fileName, unsigned char planeNumber);
	//void createPlanes();
	void setIsHidden(bool isHidden);
	void setColor(unsigned char red, unsigned char green, unsigned char blue);
	void setX(float positionX);
	void setY(float positionY);
	float getX() const { return m_x; }
	float getY() const { return m_y; }

	void setVelocityX(float velocityX) { m_velocityX = velocityX; }
	void setVelocityY(float velocityY) { m_velocityY = velocityY; }
	float getVelocityX() { return m_velocityX; }
	float getVelocityY() { return m_velocityY; }
		
	void setNumColumns(unsigned short numColumns) { m_numColumns = numColumns; };
	void setNumRows(unsigned short numRows) { m_numRows = numRows; };
	
	unsigned short getNumColumns()	const { return m_numColumns; };
	unsigned short getNumRows()		const { return m_numRows; };

	unsigned short getWidth()	const { return m_width; };
	unsigned short getHeight()	const { return m_height; };

	float getScrollX() const { return m_scrollX; };
	float getScrollY() const { return m_scrollY; };

	void setDoSwitchRow(bool doSwitchRow) { m_doSwitchRow = doSwitchRow; };
	void setPathNext(std::string pathNext) { m_pathNext = pathNext; };
	void setNumSwitchedRows(unsigned short numSwithedRows) { m_numSwitchedRows = numSwithedRows; };

	std::string getPathNext() { return m_pathNext; };
	std::vector<cObject*>* getPlanetObjects() { return &m_planeObjects; }

	cObject* getPlaneObject(unsigned short i) { return m_planeObjects.at(i); }


	std::vector<cObject*> m_planeObjects;
private:
	bool m_secondCall;
	unsigned short m_numColumns, m_numRows, m_width, m_height;
	float m_x, m_y, m_startX, m_startY, m_previousX, m_previousY, m_velocityX, m_velocityY, m_scrollX, m_scrollY;

	std::string m_pathImage;
	
	unsigned short m_numSwitchedRows;
	bool m_doSwitchRow;

	std::string m_path, m_pathNext;

	//cObject m_referenceObject;
};