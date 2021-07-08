#pragma once

#include <iostream>
#include "App.h"
#include "Object.h"

struct sMapSize {
	sMapSize();
	sMapSize& operator=(const sMapSize& other);
	bool operator==(const sMapSize& other);
	bool operator!=(const sMapSize& other);

	unsigned char columns, rows;
};

class cMap {
public:
	cMap();
	//cMap(const cMap& other);
	~cMap();

	void update(float time);

	void load(std::string pathMap);
	sMapSize getMapSizeFromLevel(std::string pathLevel);

	void setSize(sMapSize size) { m_size = size; };
	const unsigned char getNumColumns() {	return m_size.columns; };	void setNumColumns(unsigned char numColumns) {	m_size.columns = numColumns; };
	const unsigned char getNumRows() {		return m_size.rows; };		void setNumRows(unsigned char numRows) {		m_size.rows = numRows; };

	void setX(float positionX); float getX() { return m_x; };
	void setY(float positionY); float getY() { return m_y; };

	void setStartX(unsigned short startX) { m_startX = startX; }; unsigned short getStartX() { return m_startX; };
	void setStartY(unsigned short startY) { m_startY = startY; }; unsigned short getStartY() { return m_startY; };

	void setIsHidden(bool isHidden); bool getIsHidden() { return m_isHidden; };
	void setColor(unsigned char r, unsigned char g, unsigned char b);

	unsigned short* m_tileData;

	cObject* m_tileObjects;
private:
	sMapSize m_size;
	//unsigned char m_numColumns, m_numRows;

	unsigned short m_startX, m_startY;
	float m_x, m_y;
	bool m_isHidden;
};