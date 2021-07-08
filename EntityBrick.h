#pragma once

#include "Entity.h"
#include "Particle.h"

class cEntityBrick : public cEntity
{
	//friend class cEntityBrickThrownState;
public:

	cEntityBrick();
	~cEntityBrick();
	virtual void collisionReactionX(cBaseObject *object);
	virtual void collisionReactionY(cBaseObject *object);
	virtual void die(cBaseObject *killer);
	virtual void live();

	virtual void update(cApp *app, float time);

private:
};