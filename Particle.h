#pragma once

//#include "Object.h"

#include <SFML/Graphics.hpp>

#include <vector>

#include "BaseObject.h"
//#include "Object.h"

//class cObject;

//#include "PlayerState.h"

//#include "Player.h"

class cParticle : public cBaseObject
{
public:
	cParticle();
	//~cParticle();

	virtual void die(cBaseObject *killer);
	virtual void hitGround(cBaseObject *object);

	virtual void loadConfig(std::string fileName);

	virtual void collisionReactionX(cBaseObject* object) {};	virtual void collisionReactionY(cBaseObject* object) {};
		
	unsigned short getDelay() const { return m_delay; }		void setDelay(unsigned short delay) { m_delay = delay; };	

	virtual void update(float time);

	bool doSpawnNewParticle() const { return m_doSpawnNewParticle; };
	

	bool getDoGravitate() const { return m_doGravitate; }			void setDoGravitate(bool doGravitate) { m_doGravitate = doGravitate; };	
		
protected:
	//std::vector<cParticle*> m_particles;

	unsigned short m_delay;

	/*unsigned short m_offsetX, m_offsetY;
	unsigned short m_oldOffsetX, m_oldOffsetY;*/

	bool m_doGravitate;
	bool m_doSpawnNewParticle;
	bool m_isBaggenHiding;
};