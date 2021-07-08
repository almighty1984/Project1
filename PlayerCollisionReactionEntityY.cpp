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
#include "EntityPiganBounceState.h"

void cPlayer::collisionReactionEntityY(cEntity *entity) {
	/*m_isNearWallRight = false;
	m_isNearWallLeft = false;*/
	/*m_isRiding = false;
	m_belowObject = nullptr;*/
	if (entity->getNumHealth() <= 0.0f || 
		m_vitalityMeterValue <= 0) {
		return;
	}
	if (m_isOnLedge) {
		return;
	}
	/*m_movedVelocityX = 0.0f;
	m_movedVelocityY = 0.0f;*/
	/*m_isRiding = false;
	m_belowObject = entity;*/
	
	if (entity->getType() == "e_brick") {
		if (m_isCarrying && m_carriedObject == entity) { return; };
		/*if ((m_animCurrent == m_animDuck || m_animCurrent == m_animSlide)) {
			keysHeld[cInputManager::getDownKey()] = true;
			m_animCurrent = m_animDuck;
			return;
		}*/
		//return;
		if (m_velocityY >= 0.0f) {
			if (m_isDownThrusting) {
				entity->die(this);
			} else {
				m_belowObject = entity;
				m_y = entity->getY() - m_height + m_subtractDown + entity->getSubtractUp();
				m_isRiding = true;
				m_velocityY = 0.0f;
				m_movedVelocityX = entity->getMovedVelocityX();
				m_movedVelocityY = entity->getMovedVelocityY();
				m_isInSlope = false;
				m_isSlopeSliding = false;
				m_isDownThrusting = false;
				m_isPressingDownThrust = false;
				m_isInSlope = false;
				m_isNearWallRight = false;
				m_isNearWallLeft = false;
				m_hasJumped = false;
				m_hasJumpedHigh = false;
				hitGround(entity);
			}
		} else {
			m_belowObject = nullptr;
			//m_y = m_previousY;
			m_y = entity->getY() + entity->getHeight() - m_subtractUp;
			m_velocityY = 0.0f;
			entity->die(this);
		}		
		
	} else if (entity->getType() == "e_ball") {
		if (m_velocityY > 0.0f) {
			if (getMiddleX() < entity->getMiddleX() - 4) {
				m_velocityX = -m_velocityY;
				//m_x = entity->getX() - m_width + m_subtractRight;
			} else if (m_x + m_width / 2 > entity->getX() + entity->getWidth() / 2 + 4) {
				m_velocityX = m_velocityY;
				//m_x = entity->getX() - m_width + m_subtractRight;
			} else {
				m_isRiding = true;
				entity->setVelocityX(-m_velocityX);
				m_x = entity->getX()+entity->getWidth()/2-m_width/2;
				m_velocityY = entity->getVelocityY();
				m_y = entity->getY() + entity->getSubtractUp() - m_height + m_subtractDown;				
			}
		} else {
			if (getMiddleY() < entity->getMiddleY()) {
				m_y = entity->getY() + entity->getSubtractUp() - m_height + m_subtractDown;
				m_velocityY = 0.0f;
			}
			else {				
				m_velocityY = 0.0f;
				entity->setY(m_y + m_subtractUp - entity->getHeight());
				//m_velocityX = 1.0f;
				//m_x = entity->getX() + entity->getWidth() - m_subtractLeft;
			}
		}
	} else if (entity->getType().substr(0, 11) == "e_bounce_U_") {
		//std::cout << "cPlayer::collisionReactionEntityY " << entity->getLevelNode() << "\n";
		m_isNearWallLeft = false;
		m_isNearWallRight = false;
		jump();
		m_isHovering = false;
		m_isSlopeSliding = false;
		m_y = entity->getY() + entity->getSubtractUp() - m_height + m_subtractDown - 1;

		m_velocityY = -abs(m_velocityY) / 4 - 4.0f;
		m_isDownThrusting = false;
		m_isPressingDownThrust = false;
		m_isNearWallLeft = false;
		m_isNearWallRight = false;

		m_hasJumped = true;

		entity->setTileOffsetX(0.0f);
		entity->setIsDead(true);
		cSoundsManager::stop(eSoundTag::bounce);
		cSoundsManager::play(eSoundTag::bounce);
		cSoundsManager::stop(eSoundTag::jump);
		cSoundsManager::play(eSoundTag::jump);
	}
	else if (entity->getType().substr(0, 10) == "e_bounce_L" || entity->getType().substr(0, 10) == "e_bounce_R") {
		collisionReactionEntityX(entity);
	}
	else if (entity->getType() == "e_flugan") {		
		m_y = entity->getY() - m_height + entity->getSubtractUp() + 0;		
		m_movedVelocityY = entity->getVelocityY();
		entity->collisionReactionY(this);
		if (m_isDownThrusting) {
			m_velocityY = -abs(m_velocityY) * 0.25f - m_jumpForce * 1.75f;
			m_movedVelocityX = entity->getVelocityX() / 2;
			m_isDownThrusting = false;
			m_isRiding = false;
			m_hasJumped = true;
			m_belowObject = nullptr;
			cSoundsManager::play(eSoundTag::block);
			setAnim(eAnimTag::jump);
			entity->hurt(this, 10.0f);			
		} else {
			m_belowObject = entity;
			m_movedVelocityX = entity->getVelocityX();
			//m_y = entity->getY() + entity->getSubtractUp() - m_height + m_subtractDown;
			m_velocityY = 0.0f;			
			/*if (m_movedVelocityY > m_fallAcc) {
				m_velocityY = m_fallAcc;
			}*/
			if (m_isIdle) {
				m_velocityX *= 0.25f;
			}
			
			//m_y = m_previousY;
			m_isRiding = true;
			m_hasJumped = false;
			m_isOnGround = true;
			m_isInSlope = false;
			m_isSlopeSliding = false;
		}
	} else if (entity->getType() == "e_grevert") {
		if (!m_isOnGround && entity->getIsAttacking() && entity->getAnimTag() != eAnimTag::bounce) {
			m_y = entity->getTop() - m_height + m_subtractDown - 4;
			m_velocityY = -m_jumpForce * 1.0f + entity->getVelocityY() * 1.0f - abs(m_velocityY) * 1.0f;
			entity->setAnim(eAnimTag::bounce);
			entity->setTileOffsetX(0.0f);
			if (!cSoundsManager::isPlaying(eSoundTag::bounce)) {
				cSoundsManager::play(eSoundTag::bounce);
			}
		}
	} else if (entity->getType() == "e_grodorr") {
		if (getMiddleY() < entity->getMiddleY()) {
			m_y = entity->getTop() - m_height + m_subtractDown - 4;
			m_velocityY = -m_jumpForce * 1.0f + entity->getVelocityY() * 1.0f -abs(m_velocityY) * 1.0f;
			setAnim(eAnimTag::jump);
			if (m_isDownThrusting) {
				m_velocityY = -abs(m_velocityY) * 0.25f - m_jumpForce * 1.75f;
				m_isDownThrusting = false;
				m_isRiding = false;
				m_hasJumped = true;
				m_belowObject = nullptr;
				m_movedVelocityX = 0.0f;
				m_movedVelocityY = 0.0f;
				cSoundsManager::play(eSoundTag::block);
				entity->hurt(this, 10.0f);
			}			
		} else if (getMiddleY() >= entity->getMiddleY()) {
			entity->setY(getTop() - entity->getHeight() + entity->getSubtractDown());
		}
		entity->collisionReactionY(this);
	}
	else if (entity->getType() == "e_flyling") {
		//if (m_y+m_height/2+16 < entity->getY()+entity->getHeight()/2) {
		//	//std::cout << "Collided above with entity_flyling\n";
		//	m_y = entity->getY()+entity->getSubtractUp()-m_height+m_subtractDown;
		//	//m_velocityY = -2.5f;
		//} else {
		//	//std::cout << "Collided below with entity_flyling\n";
		//	m_y = entity->getY()+entity->getHeight()-entity->getSubtractDown()-m_subtractUp+16;
		//	//m_velocityY = 2.5f;
		//}

		if (m_isInSwing == true) {
			m_isInSwing = false;
			setState(new cPlayerGrassState);
		}

		if (entity->getIsAttacking() /*&& m_isHurting == false && !entity->getIsHurting()*/) {
			if (!m_isHurting) {
				m_numHealth -= 25;
				std::cout << "HEALTH: " << m_numHealth << "\n";
			}
			m_hurtAgainDelayValue = m_hurtAgainDelay;
			m_hurtSleepDelay = entity->getHurtSleepDelay();

			m_velocityY = entity->getVelocityY()*0.5f;		
			
			entity->setVelocityY( -entity->getVelocityY() );
		
			cLevel *level = m_attachedLevel;
			level->addParticle(new cParticle);

			level->getParticleLast()->loadConfig("Data\\Particles\\p_hit.cfg");

			level->getParticleLast()->setX(m_x+m_width/2-16);
			level->getParticleLast()->setY(m_y+32);
			level->getParticleLast()->setVelocityX(0.0f);
			level->getParticleLast()->setVelocityY(0.0f);
			int randNum = (rand() % 7) * 32;
			level->getParticleLast()->setTileOffsetX((float)randNum);
			level->getParticleLast()->setTileOffsetY(0.0f);
			level->getParticleLast()->setIsHidden(false);
			level->getParticleLast()->setTimeBeingAlive(0);

			level->getParticleLast()->update(0.0f);
			cSoundsManager::play(eSoundTag::hit);

			entity->setIsCharging(false);
			entity->setIsAttacking(false);
			entity->setState(new cEntityFlylingBounceState);
		}
		/*else {
			m_velocityY = -m_velocityY + entity->getVelocityY();
		}*/
		//l->getParticleLast()->update(0.0f);
	}
	else if (entity->getType() == "e_pigan") {
		if (entity->getIsCarried() && entity->getCarrier() == this) {
			return;
		}
		m_y = entity->getTop() - m_height + m_subtractDown + 0;
		if (entity->getIsOnBack()) {
			m_isDownThrusting = false;
			m_velocityY = -abs(m_velocityY) * 0.25f - m_jumpForce * 1.75f;
			setAnim(eAnimTag::jump);
			entity->setState(new cEntityPiganBounceState);
			//entity->collisionReactionY(this);
			return;
		}
		if (m_isDownThrusting) {
			m_velocityY -= 2.5f;
			m_isDownThrusting = false;
			//cSoundsManager::play(eSoundTag::block);

			cSoundsManager::play(eSoundTag::hit);
			entity->setIsFacingLeft(!entity->getIsFacingLeft());
			entity->hurt(this, 10.0f);
			entity->setVelocityX(0.0f);

		} else {
			//m_y = entity->getY() + entity->getSubtractUp() - m_height + m_subtractDown;
			m_velocityY = 0.0f;
			m_belowObject = entity;
			m_movedVelocityX = entity->getVelocityX();
			m_movedVelocityY = entity->getVelocityY();
			/*if (m_movedVelocityY > m_fallAcc) {
				m_velocityY = m_fallAcc;
			}*/
			/*if (m_isIdle) {
				m_velocityX *= 0.25f;
			}*/
			//m_y = m_previousY;
			m_isRiding = true;
			m_hasJumped = false;
			m_isOnGround = true;
			m_isInSlope = false;
			m_isSlopeSliding = false;
		}
	} 
	else if (entity->getType() == "e_item_boost") {
		collisionReactionEntityX(entity);
	}
	else if (entity->getType() == "e_item_coin") {
		collisionReactionEntityX(entity);
	}
	else if (entity->getType() == "e_item_health") {
		collisionReactionEntityX(entity);
	}
	else if (entity->getType() == "e_train") {
		if (m_velocityY <= 0.0f || m_delayCollisionEntity > 0.0f) {
			return;
		}
		//std::cout << "Collided entity_train\n";
		float a = getMiddleX() - entity->getMiddleX();
		float b = (getMiddleY() + 16) - entity->getMiddleY();

		float distance = sqrtf(powf(a, 2) + powf(b, 2));
		
		if (entity->getIsCircle() && distance < entity->getRadius()) {
			std::cout << "distance = " << distance << "\n";
			//cSoundsManager::stop(eSoundTag::hit);
			if (!cSoundsManager::isPlaying(eSoundTag::hit)) {
				cSoundsManager::play(eSoundTag::hit);
			}
			//m_x = m_previousX;
			//m_y = entity->getMiddleY() - m_height;
			m_velocityX = entity->getVelocityX();
			m_velocityY = entity->getVelocityY();
			//m_belowObject = entity;
			//m_isRiding = true;
			//hit(getMiddleX(), getMiddleY()+16);
			hurt(entity, entity->getDamage() / m_vitality);
		} else if (!entity->getIsCircle()) {
			/*if (m_velocityY < m_fallAcc) {
				return;
			}*/
			m_belowObject = entity;
			m_movedVelocityX = entity->getVelocityX();
			m_movedVelocityY = entity->getVelocityY();
			
			if (m_isDownThrusting) {
				m_velocityY -= 2.5f;
				m_isDownThrusting = false;
				cSoundsManager::play(eSoundTag::block);
			}
			else {
				if (m_isIdle) {
					m_velocityX *= 0.75f;
				}
				//m_y = entity->getY() + entity->getSubtractUp() - m_height + m_subtractDown;
				//if (m_movedVelocityY <= 0.2f) {					
					m_velocityY = 0.0f;
				//}
					m_movedVelocityY = entity->getVelocityY();
					m_movedVelocityX = entity->getVelocityX();
					/*if (m_movedVelocityY > m_fallAcc) {
						m_velocityY = m_fallAcc;
					}*/
					/*if (m_isIdle) {
						m_velocityX *= 0.125f;
					}*/
				m_y = entity->getY() - m_height + entity->getSubtractUp() + 0.0f; 
				//m_y = m_previousY;
				m_isRiding = true;
				m_hasJumped = false;
				m_isOnGround = true;
				m_isInSlope = false;
				m_isSlopeSliding = false;
			}
		}
		

		if (((m_joyMovedY > cInputManager::getJoyDeadzone() && joyButtonsHeld[cInputManager::getJumpJoyButton()])
			||
			(keysHeld[cInputManager::getDownKey()] && keysHeld[cInputManager::getJumpKey()] || mouseButtonsHeld[cInputManager::getJumpMouseButton()])
			)) {
			std::cout << "YEPEP\n";
			m_y = entity->getY() - m_height + m_subtractDown + 12;
			m_delayCollisionEntity = 20.0f;
		}
		//hit(getMiddleX(), getMiddleY()+16);
		//hit(entity->getMiddleX(), entity->getMiddleY());
	}
}
