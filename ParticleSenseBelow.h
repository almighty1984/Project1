#pragma once

#include "Particle.h"

class cParticleSenseBelow : public cParticle {
public:
	virtual void collisionReactionX(cBaseObject* object);
	virtual void collisionReactionY(cBaseObject* object);
};