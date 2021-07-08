#pragma once

#include "Sprite.h"
#include "Shader.h"

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "QuadNode.h"

#include "Level.h"

class cWindow
{
public:	
	cWindow();

	void create(unsigned short width, unsigned short height, unsigned short bits, char *title, float multiplier, bool isFullscreen, bool isWidescreen);
	void setView(float x1, float y1, float x2, float y2);
	void setFramerateLimit(unsigned short framerateLimit);
	void setUseVerticalSync(bool useVerticalSync);

	void draw(cSprite* sprite);
	void draw(cSprite* sprite, cShader* shader);

	void draw(cQuadNode* quadNode);
	void clear();
	void display();

	bool getEvent(sf::Event &sfEvent);

	bool isOpen() const;
	void close();
	
	bool getUseVerticalSync() const { return m_useVerticalSync; };
	bool getIsWidescreen() const { return m_isWidescreen; };

	float getViewTargetX() const { return m_viewTargetX; }		void setViewTargetX(float viewTargetX) { m_viewTargetX = viewTargetX; };
	float getViewX() const { return m_viewX; }					void setViewX(float viewX) { m_viewX = viewX; };

	bool getIsViewLocked() const { return m_isViewLocked; }				void setIsViewLocked(bool isViewLocked) { m_isViewLocked = isViewLocked; };
	bool getShowLevelNodeGrid() const { return m_showLevelNodeGrid; }	void setShowLevelNodeGrid(bool showLevelNodeGrid);
	void clearGrid();
	void drawGrid();

	sf::RenderWindow m_sfApp;

	void attachLevel(cLevel *level); cLevel *getAttachedLevel() { return m_attachedLevel; };
	
private:

	cLevel *m_attachedLevel;
	
	sf::View m_sfView;
	//cShader m_shader;

	bool m_useVerticalSync;
	bool m_isWidescreen;

	bool m_isViewLocked;
	unsigned short m_framerateLimit;
	float m_viewTargetX, m_viewX;

	//std::vector<sf::RectangleShape*> m_gridShapes;

	std::vector<sf::RectangleShape*> m_horizontalLines;
	std::vector<sf::RectangleShape*> m_verticalLines;

	bool m_showLevelNodeGrid;
	bool m_secondCall;
};