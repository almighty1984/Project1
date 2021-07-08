#pragma once

#include "PlayerState.h"
#include "Player.h"

class cPlayerShopState : public cPlayerState
{
public:

	cPlayerShopState();
	~cPlayerShopState();

	virtual void update(cApp *app, cPlayer *p, float time);

private:
	//cBitmapFont m_fontCost;
	//cObject m_shopBox;

	unsigned char m_shopItemCurrent;

	cLevel* m_levelPtr;

	std::stringstream m_strStream;
};