#ifndef INCLUDED_RENDERINGMANAGER
#define INCLUDED_RENDERINGMANAGER

#include "Application.h"
#include "Singleton.h"
#include "Object.h"
#include <list>
#include <vector>

#include "Level.h"
#include "Player.h"
#include "BitmapFont.h"
#include "Enemy.h"
#include "Projectile.h"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class cRenderingManager : public Singleton<cRenderingManager>
{
	friend class Singleton<cRenderingManager>;	
public:	
	void setRenderer(char* renderer) { m_renderer = renderer; };

	/*void addBackground0(cObject* object);
	void addBackground1(cObject* object);*/

	void addObject(cObject* object);
	void addPlayer(cPlayer* player);
	void addLevel(cLevel* level);
	void addBitmapFont(cBitmapFont* bitmapFont);
	void addEnemy(cEnemy* enemy);
	void addProjectile(cProjectile* projectile);

	void clearLevel();
	void clearObjects();
	void clearPlayers();
	void clearEnemies();
	void clearProjectiles();

	void clearBitmapFonts();
	//void clearBitmapFont(cBitmapFont* bitmapFont);

	//void removeBitmapFont(cBitmapFont* bitmapFont);
	//void removeEnemy(cEnemy* enemy);
	void removeProjectile(cProjectile* projectile);

	void renderLevel(unsigned short layerNumber, cApplication* application);
	void renderBackgrounds(unsigned short layerNumber, cApplication* application);
	//void renderForegrounds(unsigned short layerNumber, cApplication* application);
	void renderObjects(cApplication* application);
	void renderPlayers(cApplication* application);	
	void renderBitmapFonts(cApplication* application);
	void renderEnemies(cApplication* application);
	void renderProjectiles(cApplication* application);

	void sleep(unsigned int msecond);
	void clear();
	void display();
	void setView(unsigned short x1, unsigned short y1, unsigned short x2, unsigned short y2);
	void setFramerateLimit(unsigned short framerateLimit);
	void setUseVerticalSync(bool useVerticalSync);
	bool getUseVerticalSync() { return m_useVerticalSync; };
	void createWindow(unsigned short width, unsigned short height, unsigned short bits, char *title, float multiplier, bool isFullscreen, bool isWidescreen);
	bool isWindowOpened() const;
	void closeWindow();

	/*void setPathBackground0(std::string pathBackground0) { m_pathBackground0 = pathBackground0; };
	void setPathBackground1(std::string pathBackground1) { m_pathBackground1 = pathBackground1; };
	void setPathForeground0(std::string pathForeground0) { m_pathForeground0 = pathForeground0; };

	std::string getPathBackground0() { return m_pathBackground0; };
	std::string getPathBackground1() { return m_pathBackground1; };*/

	bool getEvent(sf::Event &sfEvent);

	const bool getIsWidescreen() { return m_isWidescreen; };

	sf::RenderWindow m_sfApp;
	sf::View m_sfView;

	sf::RectangleShape m_leftRectangle, m_rightRectangle;

	//sf::Shader m_shader;

	//std::vector< std::vector<sf::Sprite*>* > m_bitmapFontSprites;
	std::vector<cBitmapFont*> m_bitmapFonts;
	std::vector<sf::Sprite**> m_bitmapFontSprites;
	
private:
	cRenderingManager();
	~cRenderingManager();

	std::string m_renderer;

	cLevel* m_attachedLevel;

	std::list<cProjectile*> m_projectiles;

	//std::list<cObject*> m_listeners;

	unsigned short m_tileX, m_tileY;
	unsigned short m_currentTile;

	unsigned char m_numLayers;

	bool m_useVerticalSync;
	
	bool m_isWidescreen;

	std::vector<cObject*> m_objects;	
	std::vector<sf::Sprite*> m_objectSprites;
	
	std::vector<cPlayer*> m_players;
	std::vector<sf::Sprite*> m_playerSprites;	
	std::vector<sf::Shader*> m_playerShaders;

	std::vector<cEnemy*> m_enemies;
	std::vector<sf::Sprite*> m_enemySprites;
	std::vector<sf::Shader*> m_enemyShaders;

	sf::Sprite** m_backgroundSprites;
	sf::Sprite** m_levelSprites;	

	std::vector< std::vector<sf::Sprite*> > m_bitmapFontVector;

	



	
};
#endif