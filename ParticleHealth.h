#pragma once

#include "Particle.h"

class cParticleHealth : public cParticle {
public:
	virtual bool collisionCheckX(cBaseObject* object);				virtual bool collisionCheckY(cBaseObject* object);
	virtual void collisionReactionX(cBaseObject *object);
	virtual void collisionReactionY(cBaseObject *object);
};