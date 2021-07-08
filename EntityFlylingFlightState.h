#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityFlylingFlightState : public cEntityState
{	
public:

	cEntityFlylingFlightState();
	~cEntityFlylingFlightState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:

};