#pragma once

#include "Entity.h"
#include "Particle.h"

class cEntityGrevert : public cEntity
{
public:
	cEntityGrevert();
	~cEntityGrevert();	

	virtual void collisionReactionX(cBaseObject *object);
	virtual void collisionReactionY(cBaseObject *object);

	virtual void die(cBaseObject* killer);

	virtual void hitGround(cBaseObject* object);

	virtual void update(cApp *app, float time);

private:
	bool m_secondCall;
};