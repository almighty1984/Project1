#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityBrickDeathState : public cEntityState
{
public:

	cEntityBrickDeathState();
	~cEntityBrickDeathState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:

};