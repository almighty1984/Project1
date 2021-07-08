#pragma once
#include "Object.h"
#include "ObjectState.h"

class cObjectDeathState : public cObjectState
{
public:

	cObjectDeathState();
	~cObjectDeathState();

	virtual void update(cObject* object, float time);

private:

};