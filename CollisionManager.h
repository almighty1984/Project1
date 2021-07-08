#pragma once

#include "App.h"
#include "Player.h"
#include "Level.h"
#include "LevelNode.h"
//#include "QuadNode.h"

class cCollisionManager {
public:	
	static void checkPlayer(cApp* app, cLevel* level, cPlayer* player, float time);
	static void checkEntities(cApp* app, cLevel* level, cPlayer* player, float time);
	static void checkParticles(cApp* app, cLevel* level, cPlayer* player, float time);

	static void update(cApp* app, cPlayer* player, cLevel* level, float time);

	~cCollisionManager();
private:	
	static std::vector<cLevelNode> m_playerNodes;
	static std::vector<cLevelNode> m_entityNodes;
	static std::vector<cLevelNode> m_particleNodes;
	//cQuadNode m_quadNode;
};

