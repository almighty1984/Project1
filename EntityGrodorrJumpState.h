#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityGrodorrJumpState : public cEntityState
{
public:

	cEntityGrodorrJumpState();
	~cEntityGrodorrJumpState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:

};