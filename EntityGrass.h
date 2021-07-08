#pragma once

#include "Entity.h"
#include "Particle.h"

class cEntityGrass : public cEntity {
	//friend class cEntityBrickThrownState;
public:

	cEntityGrass();
	~cEntityGrass();
	virtual void collisionReactionX(cBaseObject* object) {};
	virtual void collisionReactionY(cBaseObject* object) {};
	//virtual void die(cBaseObject* killer);
	//virtual void live();

	virtual void update(cApp* app, float time);

private:

	bool m_isSwayingLeft;
};