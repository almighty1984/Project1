#pragma once

#include "Singleton.h"

#include "QuadNode.h"

class cGlobals : public Singleton<cGlobals>
{
	friend class Singleton<cGlobals>;
public:
	~cGlobals();

	cQuadNode m_quadNode;

private:
	cGlobals();	
};