#pragma once
#include "App.h"
#include "BitmapFont.h"
#include "Object.h"
//#include "Entity.h"
#include "EntityPigan.h"
#include "EntityFlugan.h"
#include "EntityFlyling.h"
#include "EntityGrass.h"
#include "EntityGrodorr.h"
#include "EntityBall.h"
#include "EntityGrevert.h"
#include "Entitytrain.h"
#include "EntityRain.h"
#include "EntitySnow.h"
#include "EntityBrick.h"
#include "Plane.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <array>

template <typename T>
struct sPoint2D {
	sPoint2D() : x(T()), y(T()) {
		/*x = T();
		y = T();*/
		/*for (int i = 0; i < 1000; ++i) {
			std::cout << x << " " << y << "\n";
		}*/
	};

	sPoint2D(const sPoint2D& other) : x(other.x), y(other.y) {};
	sPoint2D& operator=(const sPoint2D& other) { x = other.x; y = other.y; };

	T x, y;
};

class cLevel {
public:
	cLevel();
	~cLevel();

	void attachPlayer(cPlayer* player);

	void addEntity(cEntity* entity);
	cEntity* getEntity(size_t n);
	cEntity* getEntityLast();
	size_t getNumEntities() { return m_entities.size(); };

	void addParticle(cParticle* particle);
	cParticle* getParticle(size_t n);
	cParticle* getParticleLast();
	size_t getNumParticles() { return m_particles.size(); };	

	void addShopItem(cObject* object);
	void loadShop(std::string fileName);
	cObject* getShopItem(int itemNumber) { return m_shopItems.at(itemNumber); };
	bool getDoShowShopBox() const { return m_doShowShopBox; }		void setDoShowShopBox(unsigned char num, bool doShowShopBox);

	void load(std::string fileName, cApp *app);	
	//void loadTiles(std::string fileName);
	//void deleteTiles();
	//void createTileObjects(cApp* app);
	//void deleteTileObjects();
	

	

	void setColor(int r, int g, int b);
	//void setColor3(int r, int g, int b);
	unsigned char getR() const { return m_r; };
	unsigned char getG() const { return m_g; };
	unsigned char getB() const { return m_b; };

	float getX() const { return m_x; };	void setX(float positionX);
	float getY() const { return m_y; };	void setY(float positionY);
	void scrollPlaneX(float scrollX);
	void scrollPlaneY(float scrollY);
	void scrollX(float positionX);
	void scrollY(float positionY);
	void scrollEntitiesX(float positionX);
	void scrollEntitiesY(float positionY);
	
	unsigned char getNumLayers()	const { return m_numLayers; };
	unsigned short getNumColumns()	const { return m_numColumns; };
	unsigned short getNumRows()		const { return m_numRows; };
		
	float getPlayerStart(std::string start, unsigned short number, unsigned char axis) const;

	std::string getPath() const { return m_path; };

	void setPlayerHasSprint(bool playerHasSprint) { m_playerHasSprint = playerHasSprint; };
	void setPlayerHasHover(bool playerHasHover) { m_playerHasHover = playerHasHover; };
	void setPlayerHasWhirl(bool playerHasWhirl) { m_playerHasWhirl = playerHasWhirl; };

	std::string getNextForegroundPath(unsigned short num);	void setNextForegroundPath(unsigned short num, std::string path);
	
	void update(cApp *app, float time);
	
	float getReferenceX() { return m_referenceObject.getX(); };
	float getReferenceY() { return m_referenceObject.getY(); };

	bool getIsLockedEntities() const { return m_isLockedEntities;	};	void setIsLockedEntities(bool isLockedEntities);

	//cQuadNode m_quadNode;
	
	cObject* getStartObject() { return m_startObject; };

	cObject* getTileObjects() { return m_tileObjects; }
	cObject* getTileObject(unsigned char z, unsigned short x, unsigned short y);
	unsigned short getTile(unsigned char z, unsigned short x, unsigned short y);
	unsigned char getTilesetNumber(unsigned char z, unsigned short x, unsigned short y);

	std::vector<cEntity*>* getEntities() { return &m_entities; };
	std::vector<cParticle*>* getParticles() { return &m_particles; };
	std::vector<cObject*>* getShopItems() { return &m_shopItems; };
	std::map<int, cObject*>* getTriggerObjects() { return &m_triggerObjectsList; };
	std::map<int, cObject*>* getTargetObjects() { return &m_targetObjectsList; };
	std::map<int, cObject*>* getPathObjects() { return &m_pathObjectsList; };
private:
	void createTiles(std::string fileName);
	void createTileObjects();
	void deleteTiles();
	void deleteTileObjects();
	void createTileset(std::string fileName);
	void deleteTileset();
	void createBackground(std::string fileName);	void deleteBackground();
	void createForeground(std::string fileName);	void deleteForeground();
	void loadEntity(unsigned char z, unsigned short x, unsigned short y, std::string type);

	bool m_secondCall;
	bool m_isLockedEntities;

	cObject* m_startObject;

	cObject* m_tileObjects;
	unsigned short* m_tiles;
	unsigned char* m_tilesetNumbers;

	char** m_tilesetTypes;
	char** m_tilesetTypesEntities;
	cPlane* m_backgroundPlanes;
	cPlane* m_foregroundPlanes;
	cApp* m_attachedApp;
	cPlayer* m_attachedPlayer;

	std::vector<cEntity*> m_entities;
	std::vector<cParticle*> m_particles;
	std::vector<cObject*> m_shopItems;
	std::vector <cObject*> m_updateEveryFrameList;
	std::map<int, cObject*> m_triggerObjectsList;
	std::map<int, cObject*> m_targetObjectsList;
	std::map<int, cObject*> m_pathObjectsList;

	std::string m_path;

	unsigned char m_numBackgroundPlanes, m_numForegroundPlanes;	

	cObject m_referenceObject;

	std::string m_pathShop;
	std::string m_typeItem[3];
	std::string m_currencyItem[3];
	unsigned short m_costItem[3];
	cBitmapFont m_fontCost[3];
	cObject m_currencyObject[3];
	bool m_doShowShopBox;
	
	unsigned char m_shopItemCurrent;

	unsigned short m_numColumns, m_numRows;
	unsigned char m_numLayers;

	float m_x, m_y;	
	unsigned char m_r, m_g, m_b;
	float m_orthoWidth, m_orthoHeight;

	sPoint2D<float> m_playerStartCenter;

	std::array<sPoint2D<float>, 4> m_playerStartsLeft;
	std::array<sPoint2D<float>, 4> m_playerStartsRight;
	std::array<sPoint2D<float>, 4> m_playerStartsDoor;
	std::array<sPoint2D<float>, 4> m_playerStartsTop;
	std::array<sPoint2D<float>, 4> m_playerStartsBottom;
	
	bool m_playerHasSprint, m_playerHasHover, m_playerHasWhirl;
};