#pragma once

#include "Particle.h"

class cParticleSenseGrevert : public cParticle {
public:
	virtual void collisionReactionX(cBaseObject* object);
	virtual void collisionReactionY(cBaseObject* object);
};