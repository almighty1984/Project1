#pragma once

#include "Entity.h"
#include "Particle.h"

class cEntityGrodorr : public cEntity {
public:

	cEntityGrodorr();
	~cEntityGrodorr();
	virtual void collisionReactionX(cBaseObject *object);
	virtual void collisionReactionY(cBaseObject *object);
	virtual void die(cBaseObject *killer);
	virtual void hurt(cBaseObject *hurter, float amount);
	virtual void spawnSenses();
	virtual void update(cApp *app, float time);

private:
	bool m_secondCall;
};