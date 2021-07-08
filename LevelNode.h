#pragma once

class cLevelNode {
public:
	cLevelNode();
	~cLevelNode();
	cLevelNode(unsigned short x, unsigned short y, unsigned short columns) { m_x = x; m_y = y; m_columns = columns; };

	cLevelNode(const cLevelNode& other);
	cLevelNode& operator= (const cLevelNode& other);
	bool operator== (const cLevelNode& other);
	bool operator!= (const cLevelNode& other);
	bool operator< (const cLevelNode& other);
	bool operator> (const cLevelNode& other);
	void setX(unsigned short x) { m_x = x; }; unsigned short getX() { return m_x; };
	void setY(unsigned short y) { m_y = y; }; unsigned short getY() { return m_y; };
	void setColumns(unsigned short columns) { m_columns = columns; }; unsigned short getColumns() { return m_columns; };
	void set(unsigned short x, unsigned short y, unsigned short columns) {
		m_x = x;
		m_y = y;
		m_columns = columns;
	}
	unsigned short get() { return m_x + m_y * m_columns; };
private:
	unsigned short m_x;
	unsigned short m_y;
	unsigned short m_columns;
};