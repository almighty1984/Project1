#pragma once

#include "Entity.h"
#include "EntityState.h"

class cEntityPiganBounceState : public cEntityState {
public:

	cEntityPiganBounceState();
	~cEntityPiganBounceState();

	virtual void update(cApp* app, cEntity* entity, float time);

private:

};