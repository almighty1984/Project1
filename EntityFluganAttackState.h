#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityFluganAttackState : public cEntityState {	
public:
	virtual void update(cApp *app, cEntity *entity, float time);
private:

};