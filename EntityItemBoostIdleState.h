#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityItemBoostIdleState : public cEntityState
{
public:

	cEntityItemBoostIdleState();
	~cEntityItemBoostIdleState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:

};