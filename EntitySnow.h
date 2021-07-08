#pragma once

#include "Entity.h"

class cEntitySnow : public cEntity
{
public:
	cEntitySnow();
	~cEntitySnow();

	virtual void update(cApp *app, float time);

private:
	float m_frameCounter;

	bool m_secondCall;

};