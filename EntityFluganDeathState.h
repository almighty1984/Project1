#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityFluganDeathState : public cEntityState
{
public:

	cEntityFluganDeathState();
	~cEntityFluganDeathState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:

};