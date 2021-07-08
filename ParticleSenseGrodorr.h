#pragma once

#include "Particle.h"

class cParticleSenseGrodorr : public cParticle {
public:
	virtual void collisionReactionX(cBaseObject *object);
	virtual void collisionReactionY(cBaseObject *object);
};