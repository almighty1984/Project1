#pragma once

#include "Entity.h"
#include "Particle.h"

class cEntityBall : public cEntity
{
public:

	cEntityBall();
	~cEntityBall();
	//virtual bool collisionCheckX(cBaseObject *object);
	//virtual bool collisionCheckY(cBaseObject *object);
	virtual void collisionReactionX(cBaseObject *object);
	virtual void collisionReactionY(cBaseObject *object);

	//virtual void collisionReactionSlopeX(cBaseObject* object);
	//virtual void collisionReactionSlopeY(cBaseObject* object);

	virtual void update(cApp *app, float time);

private:
	bool m_secondCall;
};