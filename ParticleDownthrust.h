#pragma once

#include "Particle.h"

class cParticleDownthrust : public cParticle
{
public:
	virtual void collisionReactionX(cBaseObject *object);
	virtual void collisionReactionY(cBaseObject *object);
};