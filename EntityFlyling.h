#pragma once

#include "Entity.h"
#include "Particle.h"

class cEntityFlyling : public cEntity
{
public:
	
	cEntityFlyling();
	~cEntityFlyling();

	virtual void die(cBaseObject *killer);
	
	virtual void collisionReactionX(cBaseObject *object);
	virtual void collisionReactionY(cBaseObject *object);

	virtual void update(cApp *app, float time);

private:	
	bool m_secondCall;
	unsigned short m_moveTimerX;
};