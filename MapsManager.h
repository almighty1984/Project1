#pragma once

//#include <fstream>
#include <string>
#include <vector>

#include "Object.h"
#include "Level.h"

#include "Map.h"

class cMapsManager {	
public:	
	~cMapsManager();

	static void clearMaps();
	static void addMap(cMap *map);
	static cMap* getMapLast();
	static void init(cApp *app);

	/*void scrollX(int x);
	void scrollY(int y);*/

	static void setColor(unsigned char r, unsigned char g, unsigned char b);

	static int getX() { return m_x;}			static void setX(int x) { m_x = x;	};
	static int getY() { return m_y;}			static void setY(int positionY) { m_y = positionY;	};
	static bool getIsHidden() { return m_isHidden;}		static void setIsHidden(bool isHidden);

	static void update(cApp* app, cLevel* level, float time);	
	
	static std::vector<std::string> m_levelList;

private:
	cMapsManager();	

	static int m_x, m_y;
	static int m_mapOffsetX, m_mapOffsetY;	
	static bool m_isHidden;

	static cObject m_mapPlayerObject;
	static std::vector<cMap*> m_maps;
	//std::vector<cObject*> m_mapObjects;
};