#pragma once

//#include "Object.h"
#include "Entity.h"

class cApp;
class cEntity;

class cEntityState
{
public:
	cEntityState() { m_secondCall = false; };
	//virtual ~cPlayerState(){}
	//virtual void enter(cPlayer *player, cPlayerState* previousState) {}
	virtual void update(cApp *app, cEntity *entity, float time) {}
	//virtual void exit(cPlayer *player) {}
	
protected:	
	bool m_secondCall;
//
//private:
//	bool m_secondCall;

};