#pragma once

#include "Particle.h"

class cParticleGrodorrAttack : public cParticle
{
public:
	virtual void collisionReactionX(cBaseObject *object);
	virtual void collisionReactionY(cBaseObject *object);
};