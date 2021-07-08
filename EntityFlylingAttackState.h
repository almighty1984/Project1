#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityFlylingAttackState : public cEntityState
{	
public:

	cEntityFlylingAttackState();
	~cEntityFlylingAttackState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:

};