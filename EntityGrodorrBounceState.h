#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityGrodorrBounceState : public cEntityState
{
public:

	cEntityGrodorrBounceState();
	~cEntityGrodorrBounceState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:

};