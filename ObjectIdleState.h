#pragma once
#include "Object.h"
#include "ObjectState.h"

class cObjectIdleState : public cObjectState
{
public:

	cObjectIdleState();
	~cObjectIdleState();

	virtual void update(cObject* object, float time);

private:

};