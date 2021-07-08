#ifndef INCLUDED_ENEMYITEMIDLESTATE
#define INCLUDED_ENEMYITEMIDLESTATE

#include "Enemy.h"
#include "EnemyState.h"

class cEnemyItemIdleState : public cEnemyState
{
public:

	cEnemyItemIdleState();
	~cEnemyItemIdleState();

	virtual void update(float time, cEnemy* enemy);

private:

};
#endif