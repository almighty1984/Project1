#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityItemBoostDeadState : public cEntityState
{
public:

	cEntityItemBoostDeadState();
	~cEntityItemBoostDeadState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:

};