#include "Player.h"
#include "Entity.h"

#include "InputManager.h"
#include "SoundBufferManager.h"
#include "SoundsManager.h"
#include "RenderingManager.h"

#include "PlayerGrassState.h"
#include "PlayerWaterState.h"
#include "PlayerShopState.h"

#include "MusicManager.h"

#include "EntityFluganAttackState.h"
#include "EntityFluganChargeState.h"
#include "EntityFlylingFlightState.h"
#include "EntityFlylingChargeState.h"
#include "EntityFlylingBounceState.h"

#include "EntityGrodorrBounceState.h"

void cPlayer::collisionReactionEntityX(cEntity *entity) {
	/*m_isNearWallRight = false;
	m_isNearWallLeft = false;*/
	//std::cout << "collisionReactionEntityX\n";
	/*m_isRiding = false;
	m_belowObject = nullptr;*/
	if (entity->getNumHealth() <= 0.0f ||
		m_vitalityMeterValue <= 0) {
		return;
	}

	if (m_isOnLedge) {
		return;
	}

	//m_isRiding = false;
	//m_isDownThrusting = false;	

	if (entity->getType() == "e_pigan") {
		if (entity->getIsCarried() && entity->getCarrier() == this) {
			return;
		}
		//std::cout << m_isNearWallLeft << " " << m_isNearWallRight << "\n";
		entity->setTimerState(0.0f);
		m_movedVelocityX = entity->getVelocityX();
		m_movedVelocityY = entity->getVelocityY();
		if (entity->getMiddleX() < getMiddleX()) {
			if (m_isNearWallRight) {
				std::cout << "Player collided X with e_pigan near wall right" << "\n";
				entity->setIsFacingLeft(true);
				entity->setX(getLeft() - entity->getWidth() + entity->getSubtractRight());
			} else {
				m_x = entity->getRight() - m_subtractLeft + 0;
				if (entity->getIsOnBack()) {
					entity->setVelocityX(m_velocityX);
				} else {
					m_velocityX = 2.0f;
					m_velocityY = -1.0f;
				}
			}
		} else if (entity->getMiddleX() > getMiddleX()) {
			if (m_isNearWallLeft) {
				std::cout << "Player collided X with e_pigan near wall left" << "\n";
				entity->setX(getRight() - entity->getSubtractLeft());
				entity->setIsFacingLeft(false);
			} else {
				m_x = entity->getLeft() - m_width + m_subtractRight - 0;
				if (entity->getIsOnBack()) {
					entity->setVelocityX(m_velocityX);
				} else {
					m_velocityX = -2.0f;
					m_velocityY = -1.0f;
				}
			}
		}
	} else if (entity->getType() == "e_brick") {
		if (m_isCarrying && m_carriedObject == entity) { return; };
		//m_x = m_previousX;
		if (getMiddleX() > entity->getMiddleX()) {
			m_x = entity->getRight() - m_subtractLeft + 0;
		} else {
			m_x = entity->getLeft() - m_width + m_subtractRight;
		}
		if (!m_isCrawling) {
			m_velocityX *= 0.9f;
		}
		entity->setVelocityX(m_velocityX);

		/*if (entity->getAboveObject() != nullptr) {
			entity->getAboveObject()->setMovedVelocityX(m_velocityX);
			if (entity->getAboveObject()->getAboveObject() != nullptr) {
				entity->getAboveObject()->getAboveObject()->setMovedVelocityX(m_velocityX);
				if (entity->getAboveObject()->getAboveObject()->getAboveObject() != nullptr) {
					entity->getAboveObject()->getAboveObject()->getAboveObject()->setMovedVelocityX(m_velocityX);
				}
			}			
		}*/
		//m_velocityX = 0.0f;
		//m_movedVelocityX = 0.0f;
		if (m_isNearWallLeft || m_isNearWallRight && !m_isOnGround) {
			slideWall(entity);
		}
	} else if (entity->getType() == "e_ball") {
		if (abs(m_velocityX) < m_moveAcc && abs(entity->getVelocityX()) < m_moveAcc) {
			m_velocityX = 0.0;
			m_x = m_previousX;
		}
		if (m_hasSprint) {
			m_velocityX *= 0.75f * m_sprintValue;
			entity->setVelocityX(m_velocityX * 0.75f * m_sprintValue);
		}
		else {
			m_velocityX *= 0.75f;
			entity->setVelocityX(m_velocityX * 0.75f);
		}
		if (m_velocityX < 0.0f && entity->getX() + entity->getWidth() / 2 < m_x + m_width / 2) {
			m_x = entity->getX() + entity->getWidth() - m_subtractLeft + 0;
		}
		if (m_velocityX > 0.0f && entity->getX() + entity->getWidth() / 2 > m_x + m_width / 2) {
			m_x = entity->getX() - m_width + m_subtractRight - 0;
		}
		//m_x = m_previousX;


		//entity->rotate(m_velocityX);

		/*if (cSoundsManager::m_soundHover.getStatus() != sf::SoundSource::Playing) {
			cSoundsManager::play(eSoundTag::hover);
		}*/
	} else if (entity->getType() == "e_bounce_U_0" || entity->getType() == "e_bounce_U_1") {
		collisionReactionEntityY(entity);
	} else if (entity->getType() == "e_bounce_L_0" || entity->getType() == "e_bounce_L_1") {
		m_isNearWallLeft = false;
		m_isNearWallRight = false;
		//jump();
		m_isHovering = false;
		m_isSlopeSliding = false;
		m_x = entity->getX() + entity->getWidth() - m_width + m_subtractRight - 8;

		m_velocityX = -m_moveVelocity;
		m_movedVelocityX = -m_moveVelocity;
		m_isDownThrusting = false;
		m_isPressingDownThrust = false;
		m_isNearWallLeft = false;
		m_isNearWallRight = false;

		entity->setTileOffsetX(0.0f);
		entity->setIsDead(true);
		cSoundsManager::stop(eSoundTag::bounce);
		cSoundsManager::play(eSoundTag::bounce);
		cSoundsManager::stop(eSoundTag::jump);
		cSoundsManager::play(eSoundTag::jump);
	}
	else if (entity->getType() == "e_bounce_R_0" || entity->getType() == "e_bounce_R_1") {
		m_isNearWallLeft = false;
		m_isNearWallRight = false;
		//jump();
		m_isHovering = false;
		m_isSlopeSliding = false;
		m_x = entity->getX() + entity->getWidth() - entity->getSubtractRight() - m_subtractLeft + 8;

		m_velocityX = m_moveVelocity;
		m_movedVelocityX = m_moveVelocity;
		m_isDownThrusting = false;
		m_isPressingDownThrust = false;
		m_isNearWallLeft = false;
		m_isNearWallRight = false;

		entity->setTileOffsetX(0.0f);
		entity->setIsDead(true);
		cSoundsManager::stop(eSoundTag::bounce);
		cSoundsManager::play(eSoundTag::bounce);
		cSoundsManager::stop(eSoundTag::jump);
		cSoundsManager::play(eSoundTag::jump);
	} else if (entity->getType() == "e_flugan") {
		m_movedVelocityX = entity->getVelocityX();
		m_movedVelocityY = entity->getVelocityY();
		m_isInSwing = false;
		entity->collisionReactionX(this);
	} else if (entity->getType() == "e_flyling") {
		if (m_isInSwing && abs(m_velocityX) >= abs(entity->getVelocityX())) {
			cSoundsManager::stop(eSoundTag::hit);
			cSoundsManager::play(eSoundTag::hit);

			if (!entity->getIsDead()) {
				entity->setIsHurting(true);
				m_vitalityMeterValue -= (int)(20.0f / m_vitality);
				entity->setHurtAgainDelayValue(entity->getHurtAgainDelay());
				entity->setVelocityX(m_velocityX * 2.0f);
				entity->setVelocityY(m_velocityY * 1.0f);
			}
		} else {
			m_isInSwing = false;
			setState(new cPlayerGrassState);
		}
		if (entity->getIsAttacking() && !m_isInSwing/* && m_isHurting == false*/) {
			if (!m_isHurting) {				
				m_hurtAgainDelayValue = m_hurtAgainDelay;
				m_hurtSleepDelay = entity->getHurtSleepDelay();
				m_vitalityMeterValue -= (int)(20.0f / m_vitality);
				m_velocityX = entity->getVelocityX() * 0.5f;

				cLevel *level = m_attachedLevel;
				level->addParticle(new cParticle);
				level->getParticleLast()->loadConfig("Data\\Particles\\p_hit.cfg");
				level->getParticleLast()->setIsHidden(true);
				level->getParticleLast()->attachParent(this);
				level->getParticleLast()->setX(m_x + m_width / 2 - level->getParticleLast()->getWidth() / 2/* + level->getParticleLast()->getOffsetX()*/);
				level->getParticleLast()->setY(m_y + m_height - level->getParticleLast()->getHeight()/* + level->getParticleLast()->getOffsetY()*/);

				unsigned char randNum = (rand() % 7) * 32;

				std::cout << "randNum: " << randNum << "\n";

				level->getParticleLast()->setTileOffsetX((float)randNum);
				level->getParticleLast()->setTileOffsetY(0.0f);
				level->getParticleLast()->setIsHidden(false);
				level->getParticleLast()->update(0.0f);

				cSoundsManager::play(eSoundTag::hit);

				entity->die(this);
			}
		}
	} else if (entity->getType() == "e_grass") {
		
	} else if (entity->getType() == "e_grevert") {
		collisionReactionEntityY(entity);
	} else if (entity->getType() == "e_grodorr") {
		entity->collisionReactionX(this);
	} else if (entity->getType() == "e_item_boost") {
		if (m_staminaMeterValue < 64) {
			entity->setNumHealth(0);
			m_staminaMeterValue = 64;
		}
	} else if (entity->getType() == "e_item_coin") {
		//entity->setVelocityX(m_velocityX);
			//if (entity->getIsDead() == false) {
			//	entity->setIsDead(true);
			//	//entity->setIsHidden(true);
			//	entity->setAnimCurrent(entity->getAnimDeath());


			//	cSoundsManager::stop(eSoundTag::coin);
			//	cSoundsManager::play(eSoundTag::coin);
			//}		
	}
	else if (entity->getType() == "e_item_health") {
		//if (m_isDownThrusting) { return; };
		if (m_vitalityMeterValue < 64) {
			m_vitalityMeterValue += 32;
			entity->setIsDead(true);
			entity->setNumHealth(0);
			entity->setTileOffsetX(0.0f);
			if (m_vitalityMeterValue > 64) {
				m_vitalityMeterValue = 64;
			}
		}
	}
	else if (entity->getType() == "e_train") {
		collisionReactionEntityY(entity);
		//float a = getMiddleX()-entity->getMiddleX();
		//float b = (getMiddleY()+16) - entity->getMiddleY();
		//
		//float distance = sqrtf(powf(a,2) + powf(b,2));
		//std::cout << "distance = " << distance << "\n";
		//if (entity->getIsCircle() && distance < entity->getRadius() || !entity->getIsCircle()) {
		//	//cSoundsManager::stop(eSoundTag::hit);
		//	//cSoundsManager::play(eSoundTag::hit);
		//	m_x = m_previousX;
		//	//m_y = m_previousY;
		//	m_velocityX = entity->getVelocityX();
		//	//m_velocityY = entity->getVelocityY();
		//	//hit(getMiddleX(), getMiddleY()+16);
		//	hurt(entity->getDamage() / m_vitality);

		//}		
		////hit(getMiddleX(), getMiddleY()+16);
		////hit(entity->getMiddleX(), entity->getMiddleY());
	}
}