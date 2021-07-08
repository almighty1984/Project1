#pragma once

#include "Object.h"

class cObject;

class cObjectState
{
public:
	virtual void update(cObject* object, float time) {}
	
protected:
	bool m_secondCall;	

};