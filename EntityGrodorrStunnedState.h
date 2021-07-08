#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityGrodorrStunnedState : public cEntityState
{
public:

	cEntityGrodorrStunnedState();
	~cEntityGrodorrStunnedState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:

};