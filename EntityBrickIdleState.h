#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityBrickIdleState : public cEntityState
{
public:

	cEntityBrickIdleState();
	~cEntityBrickIdleState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:

};