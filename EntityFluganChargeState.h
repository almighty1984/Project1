#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityFluganChargeState : public cEntityState {	
public:
	cEntityFluganChargeState();
	virtual void update(cApp *app, cEntity *entity, float time);
private:
};