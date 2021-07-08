#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityFluganStunnedState : public cEntityState
{
public:

	cEntityFluganStunnedState();
	~cEntityFluganStunnedState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:

};