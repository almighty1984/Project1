#pragma once

#include "Entity.h"

class cEntityRain : public cEntity
{
public:
	cEntityRain();
	~cEntityRain();

	virtual void update(cApp *app, float time);

private:
	float m_frameCounter;

	bool m_secondCall;

};