#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include <list>
#include <vector>

#include "App.h"
#include "Object.h"
#include "Level.h"
#include "Player.h"
#include "BitmapFont.h"
#include "Entity.h"
#include "Particle.h"

#include "Window.h"

#include "Plane.h"
//#include "QuadNode.h"

class cRenderingManager {
public:	
	static void attachLevel(cLevel *level);
	static cLevel *getAttachedLevel();
	//static void setRenderer(char* renderer) { m_renderer = renderer; };
	
	static void addBackgroundPlane(cPlane *backgroundPlane);
	static void addForegroundPlane(cPlane *foregroundPlane);
	static void addObject(cObject *object);
	static void addPlayer(cPlayer *player);
	static void addLevel(cLevel *level);
	static void addBitmapFont(cBitmapFont *bitmapFont);
	static void addEntity(cEntity *entity);
	static void addParticle(cParticle *particle);

	static void clearBackgroundPlanes();
	static void clearForegroundPlanes();

	static void clearObjects();
	static void clearPlayers();
	static void clearLevel();
	static void clearEntities();
	static void clearParticles();

	static void clearBitmapFonts();
	//void clearBitmapFont(cBitmapFont *bitmapFont);

	static std::string getPathFont();
	static void setPathFont(std::string pathFont);

	static void removeBitmapFont(cBitmapFont *bitmapFont);
	//void removeEntity(cEntity *entity);
	static void removeObject(cObject *object);
	static void removeParticle(cParticle *particle);
	//static void eraseBitmapFont(unsigned short i);
	//static void eraseParticle(unsigned short i);

	static void renderBackgroundPlanes(cApp *app);
	static void renderForegroundPlanes(cApp *app);
	static void renderObjects(cApp *app);
	static void renderPlayers(cApp *app);
	static void renderLevel(unsigned char layerNumber, cApp* app);
	static void renderBitmapFonts(cApp *app);
	//static void renderEntities(cApp *app);

	static void renderEntities(unsigned char layer, cApp* app);

	static void renderParticles(cApp *app);

	static void renderQuadNodes(cApp *app);

	static void sleep(unsigned int msecond);
	static void clear();
	static void display();
	static void setView(float x1, float y1, float x2, float y2);
	static void setFramerateLimit(unsigned short framerateLimit);
	static void setUseVerticalSync(bool useVerticalSync);
	static void createWindow(unsigned short width, unsigned short height, unsigned short bits, char *title, float multiplier, bool isFullscreen, bool isWidescreen);
	static bool isWindowOpened();
	static void closeWindow();

	static bool getUseVerticalSync();
	static bool getIsWidescreen();

	static float getViewX();			static void setViewX(float viewX);
	static bool getIsViewLocked();		static void setIsViewLocked(bool isViewLocked);
	static bool getShowLevelNodeGrid(); static void setShowLevelNodeGrid(bool showLevelNodeGrid);

	//sf::RenderWindow m_sfApp;
	static sf::View m_sfView;

	static cWindow m_window;
	
	//cQuadNode m_quadNode;
private:
	//cRenderingManager();
	~cRenderingManager();

	//std::string m_renderer;
	static cLevel *m_attachedLevel;
	
	static std::list<cBitmapFont*> m_bitmapFonts;
	static std::list<cObject*> m_objects;
	static std::list<cParticle*> m_particles;
	static std::vector<cPlane*> m_backgroundPlanes;
	static std::vector<cPlane*> m_foregroundPlanes;	
	static std::vector<cPlayer*> m_players;
	static std::vector<sf::Shader*> m_playerShaders;
	//static std::vector<cEntity*> m_entities;
	static std::vector<sf::Shader*> m_entityShaders;
	//cObject m_objectCursor;

	static std::map<unsigned char, std::vector<cEntity*>> m_entityMap;

	static std::string m_pathFont;
};