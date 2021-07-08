#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityGrevertAttackState : public cEntityState {
public:
	cEntityGrevertAttackState();

	virtual void update(cApp *app, cEntity *entity, float time);
private:
	
};
