#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityGrodorrIdleState : public cEntityState
{
public:

	cEntityGrodorrIdleState();
	~cEntityGrodorrIdleState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:
	
};