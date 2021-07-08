#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityFluganWalkState : public cEntityState
{	
public:

	cEntityFluganWalkState();
	~cEntityFluganWalkState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:

};