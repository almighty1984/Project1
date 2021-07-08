#include "EnemyItemIdleState.h"
#include "Player.h"
#include "SoundsManager.h"

cEnemyItemIdleState::cEnemyItemIdleState()
{
	m_secondCall = false;
}

cEnemyItemIdleState::~cEnemyItemIdleState()
{

}

void cEnemyItemIdleState::update(float time, cEnemy* enemy)
{
	if (m_secondCall == false) {
		m_secondCall = true;
		enemy->setFlags(1);
		enemy->setIsDead(false);
		enemy->setVelocityY(0.0f);
	}

	if (enemy->getVelocityY() >= enemy->getFallVelocity()) {
		enemy->setVelocityY(enemy->getFallVelocity());
	}
	else {
		enemy->setVelocityY(enemy->getVelocityY() + enemy->getFallAcc());
	}

	// Death animation
	if (enemy->getIsDead() == true) {
		//m_velocityX = 0.0f;

		enemy->setTimerDeath(enemy->getTimerDeath() + 1);
		enemy->setAnimCurrent(enemy->getAnimDeath());
		//std::cout << m_timerDeath << std::endl;
	}
	else {
		enemy->setAnimCurrent(enemy->getAnimIdle());
	}
	// Set current animation
	enemy->setTileOffsetY(enemy->getAnimCurrent().y);
	enemy->setAnimationSpeed(enemy->getAnimCurrent().speed);
	enemy->setAnimationLoops(enemy->getAnimCurrent().loop);

	// Update animation	
	if (enemy->getAnimationTime() > 1.0f) {
		enemy->setTileOffsetX(enemy->getTileOffsetX() + enemy->getWidth());

		if (enemy->getTileOffsetX() >= (enemy->getWidth()*enemy->getNumFrames())) {
			if (enemy->getCurrentLoops() < enemy->getAnimationLoops() && enemy->getAnimationLoops() != 0) {
				//enemy->m_tileOffsetX = 0;
				enemy->setTileOffsetX((float)enemy->getWidth()*enemy->getNumFrames());
				enemy->setCurrentLoops(enemy->getCurrentLoops() + 1);
			}
			if (enemy->getAnimationLoops() == 0) {
				enemy->setTileOffsetX(0.0f);;
				enemy->setCurrentLoops(0);
			}
		}

		enemy->setAnimationTime(0.0f);
	}
	else {
		enemy->setAnimationTime(enemy->getAnimationTime() + enemy->getAnimationSpeed());
	}

	if (enemy->getTileOffsetX() >= (enemy->getWidth()*enemy->getNumFrames()) - enemy->getWidth()) {
		enemy->setTileOffsetX((float)enemy->getWidth() * enemy->getNumFrames() - enemy->getWidth());
	}

}