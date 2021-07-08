#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityGrodorrDeathState : public cEntityState
{
public:

	cEntityGrodorrDeathState();
	~cEntityGrodorrDeathState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:

};