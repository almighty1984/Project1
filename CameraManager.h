#pragma once

#include "Player.h"
#include "Level.h"

class cCameraManager {
public:
	static bool getIsLockedX() { return m_isLockedX; };	static void setIsLockedX(bool isLockedX) { m_isLockedX = isLockedX; };
	static bool getIsLockedY() { return m_isLockedY; };	static void setIsLockedY(bool isLockedY) { m_isLockedY = isLockedY; };

	static float getOffsetX() { return m_offsetX; };	static void setOffsetX(float offsetX) { m_offsetX = offsetX; };
	static float getOffsetY() { return m_offsetY; };	static void setOffsetY(float offsetY) { m_offsetY = offsetY; };

	static float getX() { return m_x; };	static void setX(float positionX) { m_x = positionX; };
	static float getY() { return m_y; };	static void setY(float positionY) { m_y = positionY; };
	
	static void scrollY(cLevel* level, cPlayer* player1, float scrollY);

	static void resetY(cLevel* level, cPlayer* player1, float scrollY);

	static void update(cApp *app, cLevel* level, cPlayer *player1, float time);
private:
	static bool m_secondCall;
	static bool m_isLockedX, m_isLockedY;
	static float m_offsetX, m_offsetY;
	static float m_scrollLimitUp, m_scrollLimitDown;
	static float m_x, m_y;
	static float m_velocityX, m_velocityY;	
};