#pragma once

#include "Entity.h"

class cEntityPigan : public cEntity
{
public:
	
	cEntityPigan();
	~cEntityPigan();

	virtual void collisionReactionX(cBaseObject* object);
	virtual void collisionReactionY(cBaseObject* object);

	virtual void hurt(cBaseObject* hurter, float amount);

	virtual void update(cApp *app, float time);

private:
	bool m_secondCall;

};