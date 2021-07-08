#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityGrevertDeathState : public cEntityState
{
public:

	cEntityGrevertDeathState();
	~cEntityGrevertDeathState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:

};