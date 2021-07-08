#pragma once

#include "Entity.h"
#include "Particle.h"

class cEntityItem : public cEntity
{
public:

	cEntityItem();
	~cEntityItem();

	//virtual void loadConfig(std::string & fileName);

	virtual void collisionReactionX(cBaseObject *object);
	virtual void collisionReactionY(cBaseObject *object);

	virtual void update(cApp *app, float time);

private:
	//bool m_secondCall;
};