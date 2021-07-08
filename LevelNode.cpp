#include "LevelNode.h"

cLevelNode::cLevelNode() : m_x(0), m_y(0), m_columns(0) {
}

cLevelNode::~cLevelNode() {
	m_x = 0;
	m_y = 0;
	m_columns = 0;
}

cLevelNode& cLevelNode::operator= (const cLevelNode& other) {
	m_x = other.m_x;
	m_y = other.m_y;
	m_columns = other.m_columns;
	return *this;
}

bool cLevelNode::operator== (const cLevelNode& other) {
	return ((m_x + m_y * m_columns) == (other.m_x + other.m_y * other.m_columns));
}

bool cLevelNode::operator!= (const cLevelNode& other) {
	return ((m_x + m_y * m_columns) != (other.m_x + other.m_y * other.m_columns));
}

bool cLevelNode::operator< (const cLevelNode& other) {
	return ((m_x + m_y * m_columns) < (other.m_x + other.m_y * other.m_columns));
}

bool cLevelNode::operator> (const cLevelNode& other) {
	return ((m_x + m_y * m_columns) > (other.m_x + other.m_y * other.m_columns));
}
cLevelNode::cLevelNode(const cLevelNode& other) : m_x(other.m_x), m_y(other.m_y), m_columns(other.m_columns) {
}