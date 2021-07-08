#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityFlylingDeathState : public cEntityState
{
public:

	cEntityFlylingDeathState();
	~cEntityFlylingDeathState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:

};