#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityGrevertHideState : public cEntityState 
{
public:

	cEntityGrevertHideState();
	~cEntityGrevertHideState();

	virtual void update(cApp *app, cEntity *entity, float time);
private:

};
