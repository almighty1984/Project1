#pragma once

#include "Particle.h"

class cParticleBrick : public cParticle
{
public:
	virtual void die(cBaseObject *killer);
	virtual void collisionReactionX(cBaseObject *object);
	virtual void collisionReactionY(cBaseObject *object);
};