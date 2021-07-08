#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityBrickThrownState : public cEntityState {
public:

	cEntityBrickThrownState();
	~cEntityBrickThrownState();

	virtual void update(cApp *app, cEntity *entity, float time);

private:

};