#include "EntityTrainIdleState.h"
#include "Player.h"
#include "SoundsManager.h"


cEntityTrainIdleState::cEntityTrainIdleState() {
	m_switchDirectionDelay = 0.0f;
}

cEntityTrainIdleState::~cEntityTrainIdleState() {

}

void cEntityTrainIdleState::update(cApp *app, cEntity *entity, float time) {
	if (!m_secondCall) {
		m_secondCall = true;

		entity->setNextObject(entity->getPathNumber(0));
		//m_nextObject = entity->getPathNumber(0);
		entity->setI(0);
		entity->setIsStunned(false);
		entity->setTimerState(0.0f);
		entity->setIsDead(false);
		entity->setVelocityX(0.0f);
		entity->setVelocityY(0.0f);		
	}

	if (entity->getDoRotate()) {
		entity->setOrigin((float)(entity->getWidth() / 2), (float)(entity->getHeight() / 2));

		entity->setSpriteOffsetX((float)(entity->getWidth() / 2));
		entity->setSpriteOffsetY((float)(entity->getHeight() / 2));
		//entity->setOrigin(128.0f, 128.0f);
		/*if (entity->getIsFacingLeft()) {
			entity->rotate(-7.5f);
		} else {*/
		entity->rotate(-5.0f);
		//}
	}

	// Regenerate health
	if (entity->getNumHealth() < entity->getStartHealth()) {
		entity->setNumHealth(entity->getNumHealth() + 0.05f);
	}
	if (entity->getNumHealth() > entity->getStartHealth()) {
		entity->setNumHealth(entity->getStartHealth());
	}

	//if (entity->getAttachedPlayer() != nullptr) {
	//	float pointX = entity->getMiddleX() - entity->getAttachedPlayer()->getMiddleX();
	//	float pointY = entity->getMiddleY() - (entity->getAttachedPlayer()->getMiddleY()-0);

	//	/*pointX *= pointX;
	//	pointY *= pointY;*/

	//	float distanceToPlayer = sqrtf((powf(pointX, 2.0f) + powf(pointY, 2.0f)));

	//	if (distanceToPlayer < 384.0f) {
	//		//std::cout << "distanceToPlayer < 384 " << entity->getMiddleX() - app->getViewWidth() / 2 << " " << entity->getMiddleY() - app->getViewHeight() / 2 << "\n";
	//		//std::cout << cSoundsManager::getPlayingOffset(entity->getSoundIdle()).asSeconds() << "\n";
	//		if (!cSoundsManager::isPlaying(entity->getSoundIdle()) ||
	//			cSoundsManager::getPlayingOffset(entity->getSoundIdle()).asSeconds() > 0.15f) {
	//			cSoundsManager::play(entity->getSoundIdle(), entity->getMiddleX() - app->getViewWidth()/2, entity->getMiddleY() - app->getViewHeight() / 2);
	//			//cSoundsManager::setVolume(entity->getSoundIdle(), 200.0f);
	//			//cSoundsManager::setLoop(entity->getSoundIdle(), true);
	//		}
	//	}/*
	//	else {
	//		cSoundsManager::stop(entity->getSoundIdle());
	//	}*/
	//}
	
	

	/*if (m_switchDirectionDelay > 0.0f) {
		std::cout << m_switchDirectionDelay << "\n";
		m_switchDirectionDelay -= time;
	}*/

	cLevel* level = entity->getAttachedLevel();
	
	if (level == nullptr) {
		return;
	}

	if (entity->getNumPathNumbers() > 0 && level->getPathObjects()->at(entity->getNextObject()) != nullptr && !level->getPathObjects()->empty() && level->getPathObjects()->at(entity->getNextObject())->getType().substr(0, 4) == "path") {
		double direction = atan2(level->getPathObjects()->at(entity->getNextObject())->getMiddleY() - (entity->getMiddleY()-entity->getOffsetY()), level->getPathObjects()->at(entity->getNextObject())->getMiddleX() - entity->getMiddleX()) * 180 / 3.141592f;

		//if (m_switchDirectionDelay <= 0.0f) {
			entity->setVelocityX((float)cos(direction * 3.141592f / 180) * entity->getMoveVelocity());
			entity->setVelocityY((float)sin(direction * 3.141592f / 180) * entity->getMoveVelocity());
			//m_switchDirectionDelay = 30.0f;
		//}
		
		if ((entity->getVelocityX() >= 0.0f && entity->getMiddleX() >= level->getPathObjects()->at(entity->getNextObject())->getX() ||
			entity->getVelocityX() <= 0.0f && entity->getMiddleX() < entity->getAttachedLevel()->getPathObjects()->at(entity->getNextObject())->getX() + 9) &&

			(entity->getVelocityY() >= 0.0f && entity->getMiddleY()-entity->getOffsetY()  >= level->getPathObjects()->at(entity->getNextObject())->getY() ||
				entity->getVelocityY() <= 0.0f && entity->getMiddleY()-entity->getOffsetY() < level->getPathObjects()->at(entity->getNextObject())->getY() + 9)
			) {


			
			//std::cout << "Reached point " << (int)m_nextObject << "\n";
			
			if (entity->getIsFacingLeft()) {
				entity->setI(entity->getI() - 1);
				//--i;
			}
			else {
				entity->setI(entity->getI() + 1);
				//++i;
			}
			

			//std::cout << "entity->getPathNumber(i) = " << m_nextObject << "\n";
			if (entity->getI() > entity->getNumPathNumbers() - 1 || entity->getI() < 0 || entity->getI() > level->getPathObjects()->size() - 1) {
				//std::cout << "Reached end point" << "\n";
				/*entity->setX(entity->getPreviousX());
				entity->setY(entity->getPreviousY());*/

				//entity->setI((entity->getNumPathNumbers() - 1));
				//i = entity->getPathNumberSize();
				////--i;
				
				//entity->setNextObject(entity->getPathNumber(entity->getI()));
				//m_nextObject = entity->getPathNumber(i-1);
				entity->setIsFacingLeft(!entity->getIsFacingLeft());

				/*if (entity->getIsFacingLeft()) {
					entity->setVelocityX(-entity->getVelocityX());
					entity->setVelocityY(-entity->getVelocityY());

				}
				else {
					entity->setVelocityX(entity->getVelocityX());
					entity->setVelocityY(entity->getVelocityY());

				}*/
				m_switchDirectionDelay = 30.0f;

			}
			
			

			//else if (entity->getI() < 0) {
			//	std::cout << "Reached starting point" << "\n";
			//	/*entity->setX(entity->getPreviousX());
			//	entity->setY(entity->getPreviousY());*/

			//	entity->setI(0);
			//	entity->setNextObject(entity->getPathNumber(1));
			//	//i = 0;
			//	//m_nextObject = entity->getPathNumber(0);
			//	entity->setIsFacingLeft(false);


			//	//entity->setVelocityX(-entity->getVelocityX());
			//	//entity->setVelocityY(-entity->getVelocityY());
			//	m_switchDirectionDelay = 30.0f;

			//}
			else {
				entity->setNextObject(entity->getPathNumber(entity->getI()));
			//	////std::cout << "entity->getPathNumber(m_nextObject + 1) = " << entity->getPathNumber(m_nextObject + 1) << " ";			
			//	//m_nextObject = entity->getPathNumber(i);
			//	////entity->setIsFacingLeft(false);
			}
		}

	}	

	//// Update animation	
	//if (entity->getAnimTime() >= 10.0f) {
	//	entity->setTileOffsetX(entity->getTileOffsetX() + entity->getWidth());

	//	if (entity->getTileOffsetX() >= (entity->getWidth() * entity->getNumAnimFrames())) {
	//		if (entity->getCurrentLoops() < entity->getNumAnimLoops() && entity->getNumAnimLoops() != 0) {
	//			//entity->m_tileOffsetX = 0;
	//			entity->setTileOffsetX((float)entity->getWidth() * entity->getNumAnimFrames());
	//			entity->setCurrentLoops(entity->getCurrentLoops() + 1);
	//		}
	//		if (entity->getNumAnimLoops() == 0) {
	//			entity->setTileOffsetX(0.0f);
	//			entity->setCurrentLoops(0);
	//		}
	//	}
	//	entity->setAnimTime(0.0f);
	//}
	//else {
	//	entity->setAnimTime(entity->getAnimTime() + entity->getAnimSpeed() );
	//}
	//if (entity->getTileOffsetX() >= (entity->getWidth() * entity->getNumAnimFrames()) - entity->getWidth()) {
	//	entity->setTileOffsetX((float)entity->getWidth() * entity->getNumAnimFrames() - entity->getWidth());
	//}	
}