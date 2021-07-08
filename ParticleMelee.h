#pragma once

#include "Particle.h"

class cParticleMelee : public cParticle {
public:
	virtual void collisionReactionX(cBaseObject *object);
	virtual void collisionReactionY(cBaseObject *object);
};