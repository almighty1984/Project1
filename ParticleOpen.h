#pragma once

#include "Particle.h"

class cParticleOpen : public cParticle
{
public:
	virtual void collisionReactionX(cBaseObject *object);
	virtual void collisionReactionY(cBaseObject *object);
};