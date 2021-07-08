#pragma once

#include <vector>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

#include "Object.h"

class cQuadNode {
public:
	cQuadNode();
	~cQuadNode();
	
	void setMaxLevel(int _maxLevel);
	void setMaxObjects(int _maxObjects);
	void setX(float _x) { x = _x; };
	void setY(float _y) { y = _y; };

	void setWidth(int _width) { width = _width; };
	void setHeight(int _height) { height = _height; };

	int getMaxLevel() { return maxLevel; };
	int getMaxObjects() { return maxObjects; };
	float getX() { return x; };
	float getY() { return y; };
	
	float x;
	float y;
	int width;
	int height;

	int id;
	int level;

	int maxLevel;
	int maxObjects, numObjects;

	bool isLeaf;

	cQuadNode* parent;
	
	sf::RectangleShape	leftShape;
	sf::RectangleShape	rightShape;
	sf::RectangleShape	upShape;
	sf::RectangleShape	downShape;

	void draw(sf::RenderTarget &canvas);

	void update(float time);

	void insert(cObject *object);
	void split();
	void clearAll();
	void clearNodeAt(float _x, float _y);
	std::vector<cObject*> &getObjectsAt(float _x, float _y);

	cQuadNode &getNodeAt(float _x, float _y);
		
	std::vector<cObject*> objects;
	std::vector<cQuadNode*> nodes;

	// Purely visual information
	void setPositionX(float positionX) { m_x = positionX; };
	void setPositionY(float positionY) { m_y = positionY; };
	void setVelocityX(float velocityX) { m_velocityX = velocityX; };
	void setVelocityY(float velocityY) { m_velocityY = velocityY; };
	void setPreviousX(float previousX) { m_previousX = previousX; };
	void setPreviousY(float previousY) { m_previousY = previousY; };

	float getPositionX() { return m_x; };
	float getPositionY() { return m_y; };
	float getVelocityX() { return m_velocityX; };
	float getVelocityY() { return m_velocityY; };
	float getPreviousX() { return m_previousX; };
	float getPreviousY() { return m_previousY; };

	float m_x, m_y, m_velocityX, m_velocityY;
	float m_previousX, m_previousY;
private:
};