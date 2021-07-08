#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityPiganWalkState : public cEntityState
{	
public:

	cEntityPiganWalkState();
	~cEntityPiganWalkState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:

};