#include "Player.h"
#include "SoundsManager.h"
#include "SavesManager.h"
#include "InputManager.h"
#include "App.h"

#include "ParticleMelee.h"
#include "ParticleOpen.h"
#include "ParticleShot.h"
#include "ParticleSense.h"
#include "ParticleSenseAbove.h"
#include "ParticleSenseBelow.h"
#include "ParticleDownthrust.h"

#include "EntityBrickThrownState.h"

void cPlayer::save(cApp *app) {	
	if (!m_hasWrittenSave) {
		cSavesManager::writeSave(m_hasHover, m_hasSprint, m_hasWhirl);
		//cSavesManager::saveGame(1, m_hasHover, m_hasSprint, m_hasWhirl);
		m_hasWrittenSave = true;
	}
}

void cPlayer::hurt(cBaseObject *hurter, float amount) {
	m_vitalityMeterValue = m_vitalityMeterValue - (int)(amount / m_vitality);
	//setVitalityMeterValue(getVitalityMeterValue() - (int)(amount / getVitality()));
}

void cPlayer::jumpWall(cApp *app, float time) {
	std::cout << "cPlayer::jumpWall" << "\n";
	/*if (getAnimTag() != eAnimTag::wall) {
		return;
	}*/

	if (m_lockJump && m_useJumpLock) {
		return;
	}

	if (m_wallJumpTimer < m_wallJumpDelay) {
		m_wallJumpTimer += time;
		setAnim(eAnimTag::wall);
		m_velocityX = 0.0f;
		m_velocityY = 0.0f;
		m_x = m_previousX;
		m_y = m_previousY;
		m_isLockedMove = true;
		cSoundsManager::stop(eSoundTag::jump);
	} else {
		m_wallJumpTimer = 0.0f;
		m_isPressingWallJump = false;
		m_isLockedMove = false;
				
		if (m_isNearWallRight) {				
			if (keysHeld[cInputManager::getRightKey()] || m_joyMovedX > cInputManager::getJoyDeadzone()) {
				m_velocityX = -(m_wallJumpForceX / 4) * time;
				m_velocityY = -m_wallJumpForceY * time;
			} else {
				m_velocityX = -m_wallJumpForceX * time;
				m_velocityY = -m_wallJumpForceY * time;
			}
		}
		if (m_isNearWallLeft) {
			if (keysHeld[cInputManager::getLeftKey()] || m_joyMovedX < -cInputManager::getJoyDeadzone()) {
				m_velocityX = (m_wallJumpForceX / 4) * time;
				m_velocityY = -m_wallJumpForceY * time;
			} else {
				m_velocityX = m_wallJumpForceX * time;
				m_velocityY = -m_wallJumpForceY * time;
			}
		}

		m_isNearWallLeft = false;
		m_isNearWallRight = false;
		m_numJumps = 0;
		m_hasJumped = true;
		m_lockJump = true;
		m_isOnGround = false;
		clearSenseAbove();
		clearSenseRight();
		clearSenseLeft();
		cSoundsManager::play(eSoundTag::jump);
	}
	
}

void cPlayer::jump() {
	if (m_isCrawling || m_isDucking) {
		return;
	}
	if (getIsPressingDown() || getAnimTag() == eAnimTag::duck || getAnimTag() == eAnimTag::crawl) {
		return;
	}
	
	
	m_movedVelocityY = 0.0f;
	m_isRiding = false;
	//std::cout << "cPlayer::jump" << "\n";		

	/*if (m_isInSlope) {
		m_velocityY = 0.0f;
		m_isOnGround = true;
	}*/
	if (!m_hasJumped && m_isOnGround && (!m_lockJump || !m_useJumpLock)
		/*|| (m_isInSlope && keysHeld[cInputManager::getDownKey()])*/
		/*|| (m_hasDoubleJump && m_numJumps < 1) ) */) {
		std::cout << "cPlayer::jump" << "\n";

		m_isOnGround = false;
		m_hasJumped = true;
		m_jumpTimeHeld = 0.0f;
		m_tileOffsetX = 0.0f;
		m_delayCollisionLevel = 0.0f;

		m_y = m_y - 4.0f;

		if (m_timerSkidJump > 0.0f && !m_isCarrying/* && ((!m_isFacingLeft && m_velocityX+m_movedVelocityX > 0.0f) || (m_isFacingLeft && m_velocityX+m_movedVelocityX < 0.0f))*/) {
			cSoundsManager::play(eSoundTag::jumpHigh);
			m_velocityY = -m_jumpForce * 1.25f;
			m_hasJumpedHigh = true;
			if (m_isFacingLeft) {
				m_velocityX -= m_moveVelocity * 0.75f;
			} else {
				m_velocityX += m_moveVelocity * 0.75f;
			}
		} else {
			if (m_timeSinceHitGround < 4.0f && m_numJumps == 1 && m_velocityX != 0.0f) {
				m_timeSinceHitGround = 4.0f;
				m_numJumps = 0;
				cSoundsManager::play(eSoundTag::jumpHigh);
				m_velocityY = -m_jumpForce * 1.2f;
			} else {
				cSoundsManager::play(eSoundTag::jump);
				
				//if (m_numJumps == 0) {
					m_velocityY = -m_jumpForce;
				/*} else if (m_numJumps == 1) {
					m_velocityY = -m_jumpForce * 1.1f;
				}*/
				++m_numJumps;
				m_timeSinceHitGround = 0.0f;
			}
		}
		m_lockJump = true;
		m_lockHover = true;


	}
	//++m_numJumps;
	//m_isInSlope = false;
}

void cPlayer::slideWall(cBaseObject* object) {
	/*if (m_velocityX != 0.0f) {
		return;
	}*/
	m_isSlidingWall = true;
	m_lockJump = false;
	if (getAnimTag() == eAnimTag::wall && (int)(m_timerSlideWall) % 4 == 0
		/* && m_velocityY > 0.5f*//* && m_velocityX < 0.2f && m_velocityX > -0.2f*/
		/* && cSoundsManager::m_soundWallSlide.getStatus() == sf::SoundSource::Playing*/) {

		cLevel* level = m_attachedLevel;
		level->addParticle(new cParticle);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_dust_wall.cfg");

		if (m_isNearWallLeft) {
			level->getParticleLast()->setX(object->getRight() - level->getParticleLast()->getSubtractLeft());
			//level->getParticleLast()->setWidth(8);
			//object->m_particles.back()->setOffsetX(-8);
			//object->setParticleOffsetX(-8);
		} else if (m_isNearWallRight) {
			level->getParticleLast()->setX(object->getLeft() - level->getParticleLast()->getWidth() + level->getParticleLast()->getSubtractRight());
			level->getParticleLast()->setIsFacingLeft(true);
			//level->getParticleLast()->setWidth(8);
			//object->m_particles.back()->setOffsetX(8);
			//object->setParticleOffsetX(8);
		}
		level->getParticleLast()->setY(getTop());
		//object->setParticleOffsetY(-16);

		level->getParticleLast()->setTileOffsetX(0.0f);

		short randNum = (rand() % 3) * 16;
		//std::cout << "randNum: " << randNum << "\n";
		level->getParticleLast()->setTileOffsetY((float)randNum);
		level->getParticleLast()->setColor(object->getColor('r'), object->getColor('g'), object->getColor('b'));
		level->getParticleLast()->update(0.0f);
	}
}

void cPlayer::hitGround(cBaseObject* object) {
	if (m_attachedLevel == nullptr || object == nullptr) {
		return;
	}
	//std::cout << "cPlayer::hitGround " << object->getType() << " " << "\n";

	/*if (!m_isSkidding && !m_isSliding && m_velocityY < 2.0f) {
		return;
	}*/

	if ((m_isSkidding && (int)(m_timerSkidJump) % 5 != 0)
		||
		(m_isSliding && (int)(m_timerSlide) % 5 != 0)) {
		return;
	}

	/*if (m_velocityY < 2.0f) {
		return;
	}*/

	//std::cout << "Player::hitGround " << m_velocityY << "\n";

	//m_hasJumped = false;
	
	if (m_isOnGround && !m_isSliding && !m_isSkidding) {
		return;
	}

	
	//m_isOnGround = true;

	/*if (m_isInSlope) {
		return;
	}*/

	cLevel* level = m_attachedLevel;

	if (m_isDownThrusting) {
		/*if (m_isInSlope) {
			setVelocityFromSlope(object);
			return;
		}*/
		m_isDownThrusting = false;
		// Shoot particle left
		level->addParticle(new cParticleDownthrust);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_downthrust.cfg");
		level->getParticleLast()->setIsHidden(!cRenderingManager::getShowLevelNodeGrid());
		level->getParticleLast()->attachParent(this);
		level->getParticleLast()->setY(m_y + m_height - level->getParticleLast()->getHeight());
		level->getParticleLast()->setX(m_x + m_width / 2 /*+ m_particleOffsetX*/ + 32 - level->getParticleLast()->getWidth());

		level->getParticleLast()->setStartX(object->getMiddleX() - level->getParticleLast()->getWidth()/2);
		level->getParticleLast()->setStartY(object->getMiddleY() - level->getParticleLast()->getHeight()/2);

		level->getParticleLast()->setVelocityX(-level->getParticleLast()->getVelocityX());
		//level->getParticleLast()->update(0.0f);
		//cRenderingManager::addParticle(level->getParticleLast());
		// Shoot particle right
		level->addParticle(new cParticleDownthrust);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_downthrust.cfg");
		level->getParticleLast()->setIsHidden(!cRenderingManager::getShowLevelNodeGrid());
		level->getParticleLast()->attachParent(this);
		level->getParticleLast()->setY(m_y + m_height - level->getParticleLast()->getHeight());
		level->getParticleLast()->setX(m_x + m_width / 2 - 32);

		level->getParticleLast()->setStartX(object->getMiddleX() - level->getParticleLast()->getWidth() / 2);
		level->getParticleLast()->setStartY(object->getMiddleY() - level->getParticleLast()->getHeight() / 2);

		//level->getParticleLast()->update(0.0f);

		//m_velocityX = 0.0f;
		//m_velocityY = m_fallVelocity;
		cSoundsManager::play(eSoundTag::hitGround);
		level->addParticle(new cParticle);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_dust_thrust.cfg");
		if (object->getType() == "slope_L_2x1_0" || object->getType() == "slope_L_2x1_1") {
			level->getParticleLast()->setOrigin(8.0f, 8.0f);
			level->getParticleLast()->setRotation(-26.565f);
			level->getParticleLast()->setX(m_x + m_width / 2 - 48);
			level->getParticleLast()->setY(m_y + m_height / 2 - 4);
			
			setVelocityFromSlope(32.0f, 16.0f);

			m_velocityX = -m_moveVelocity;
		} else if (object->getType() == "slope_R_2x1_0" || object->getType() == "slope_R_2x1_1") {
			level->getParticleLast()->setOrigin(8.0f, 8.0f);
			level->getParticleLast()->setRotation(26.565f);
			level->getParticleLast()->setX(m_x + m_width / 2 + 0);
			level->getParticleLast()->setY(m_y + m_height / 2 - 28);
			//setVelocityFromSlope(-32.0f, 16.0f);
			m_velocityX = m_moveVelocity;
		} else if (object->getType() == "slope_L_1x1") {
			level->getParticleLast()->setOrigin(8.0f, 8.0f);
			level->getParticleLast()->setRotation(-45.0f);
			level->getParticleLast()->setX(m_x + m_width / 2 - 56);
			level->getParticleLast()->setY(m_y + m_height / 2 + 10);
			//setVelocityFromSlope(16.0f, 16.0f);
			m_velocityX = -m_moveVelocity;
		} else if (object->getType() == "slope_R_1x1") {
			level->getParticleLast()->setOrigin(8.0f, 8.0f);
			level->getParticleLast()->setRotation(45.0f);
			level->getParticleLast()->setX(m_x + m_width / 2 + 16);
			level->getParticleLast()->setY(m_y + m_height / 2 - 28);
			//setVelocityFromSlope(-16.0f, 16.0f);
			m_velocityX = m_moveVelocity;
		} else {
			level->getParticleLast()->setIsHidden(true);
			level->getParticleLast()->setX(m_x + m_width / 2 - 32);
			level->getParticleLast()->setY(m_y + m_height / 2 - 32);
		}		
	} else {
		if (m_velocityY < m_fallAcc) { return; }
		level->addParticle(new cParticle);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_dust_grass.cfg");
		if (object->getType() == "slope_L_2x1_0" || object->getType() == "slope_L_2x1_1") {
			level->getParticleLast()->setOrigin(8.0f, 8.0f);
			level->getParticleLast()->setRotation(-26.565f);
			level->getParticleLast()->setX(m_x + m_width / 2 - 4);
			level->getParticleLast()->setY(m_y + m_height / 2 + 28);
		} else if (object->getType() == "slope_R_2x1_0" || object->getType() == "slope_R_2x1_1") {
			level->getParticleLast()->setOrigin(8.0f, 8.0f);
			level->getParticleLast()->setRotation(26.565f);
			level->getParticleLast()->setX(m_x + m_width / 2 + 4);
			level->getParticleLast()->setY(m_y + m_height / 2 + 28);
		} else if (object->getType() == "slope_L_1x1") {
			level->getParticleLast()->setOrigin(8.0f, 8.0f);
			level->getParticleLast()->setRotation(-45.0f);
			level->getParticleLast()->setX(m_x + m_width / 2);
			level->getParticleLast()->setY(m_y + m_height / 2 + 24);
		} else if (object->getType() == "slope_R_1x1") {
			level->getParticleLast()->setOrigin(8.0f, 8.0f);
			level->getParticleLast()->setRotation(45.0f);
			level->getParticleLast()->setX(m_x + m_width / 2);
			level->getParticleLast()->setY(m_y + m_height / 2 + 24);
		} else {			
			level->getParticleLast()->setIsHidden(true);
			level->getParticleLast()->setX(m_x + m_width / 2 - 8);
			level->getParticleLast()->setY(m_y + m_height / 2 + 16);
		}		
	}

	level->getParticleLast()->setStartX(object->getStartX());
	level->getParticleLast()->setStartY(object->getStartY()-16);	
	level->getParticleLast()->setIsHidden(false);
	
	if (!m_isSlopeSliding) {
		m_velocityY = 0.0f;
	}
}

void cPlayer::attackOpen(cApp *app, float time) {	
	if (m_isLockedOpen) {
		return;
	}
	if (m_attachedLevel == nullptr) { return; }
	cLevel *level = m_attachedLevel;

	m_timerOpen = 20.0f;

	level->addParticle(new cParticleOpen);
		
	level->getParticleLast()->loadConfig("Data\\Particles\\p_open.cfg");
	level->getParticleLast()->setIsHidden(!cRenderingManager::getShowLevelNodeGrid());
	level->getParticleLast()->attachParent(this);

	if (m_isFacingLeft) {
		level->getParticleLast()->setX(getMiddleX()+8 - level->getParticleLast()->getWidth() / 2 + level->getParticleLast()->getOffsetX());
		level->getParticleLast()->setVelocityX(-level->getParticleLast()->getStartVelocityX());
	} else {
		level->getParticleLast()->setX(getMiddleX()-8 - level->getParticleLast()->getWidth() / 2 - level->getParticleLast()->getOffsetX());
	}		

	float tempY = 0.0f;
	if (getIsPressingDown()) {
		tempY = 8.0f;
	}

	level->getParticleLast()->setY(getMiddleY() + level->getParticleLast()->getOffsetY() + tempY);
	//level->getParticleLast()->setVelocityY(-4.0f);

	//level->getParticleLast()->setIsSolid(false);

	float posX = m_levelX + m_width / 2 - level->getParticleLast()->getWidth() / 2;
	float posY = m_levelY + m_height / 2 - level->getParticleLast()->getHeight() / 2;

	

	level->getParticleLast()->setStartX(posX);
	level->getParticleLast()->setStartY(posY);
	level->getParticleLast()->setLevelX(posX);
	level->getParticleLast()->setLevelY(posY);
	level->getParticleLast()->update(0.0f);	
}

void cPlayer::attackMelee(cApp* app, float time) {
	//std::cout << m_timerMelee << "\n";
	if (m_lockMelee) {
		return;
	}
	if (!getIsPressingDown() || m_hasWhirl) {	// for whirl to work
		//std::cout << "cPlayer::attackMelee " << m_particles.size() << "\n";
		m_isLockedMove = true;
		if ((m_timerMelee == 0 || m_timerMelee >= m_timeLimitMelee) && !m_isMeleeing) {
			if (!getIsPressingDown()) {
				m_lockMelee = true;
			}
			//m_doAnimateBackwards = false;

			m_staminaCounter -= (5.0f / m_stamina) * time;

			m_isMeleeing = true;
			m_tileOffsetX = 0.0f;
			
			if (!m_isCrawling) {
				cSoundsManager::stop(eSoundTag::attack);
				cSoundsManager::play(eSoundTag::attack);
			}
			
			// Shoot particle
			cLevel *level = m_attachedLevel;
			level->addParticle(new cParticleMelee);
			level->getParticleLast()->loadConfig("Data\\Particles\\p_melee.cfg");
			level->getParticleLast()->setIsHidden(!cRenderingManager::getShowLevelNodeGrid());
			level->getParticleLast()->attachParent(this);

			//std::cout << m_particles.at(m_particles.size()-1)->getOffsetY() << "\n";

			float offsetX = (float)level->getParticleLast()->getOffsetX();
			float offsetY = (float)level->getParticleLast()->getOffsetY();
			
			float levelPosX = m_levelX + m_width * 0.5f - level->getParticleLast()->getWidth() * 0.5f;
			float levelPosY = m_levelY + m_height * 0.5f - level->getParticleLast()->getHeight() * 0.5f;

			float posX = m_x + m_width * 0.5f - level->getParticleLast()->getWidth() * 0.5f;
			float posY = m_y + m_height /*+ m_particleOffsetY*/ - level->getParticleLast()->getHeight() + offsetY;
			if (getIsPressingDown()) {				
				posY += 12.0f;
			}
			
			//if (cInputManager::getMouseX() - 32 <= m_objectWeapon.getX() + m_objectWeapon.getWidth() / 2) {
			if (m_isFacingLeft) {	
				posX -= offsetX;
				levelPosX -= offsetX;
				level->getParticleLast()->setVelocityX(-level->getParticleLast()->getVelocityX() + m_velocityX + m_movedVelocityX);
			} else {
				posX += offsetX;
				levelPosX += offsetX;
				level->getParticleLast()->setVelocityX(level->getParticleLast()->getVelocityX() + m_velocityX + m_movedVelocityX);
			}		

			level->getParticleLast()->setX(posX);
			level->getParticleLast()->setY(posY);

			level->getParticleLast()->setStartX(levelPosX);
			level->getParticleLast()->setStartY(levelPosY);
			level->getParticleLast()->setLevelX(levelPosX);
			level->getParticleLast()->setLevelY(levelPosY);
			level->getParticleLast()->update(0.0f);

			//std::cout << player->m_particles.at(player->m_particles.size()-1)->getY() << "\n";
		}
	}
}

void cPlayer::attackShoot() {
	if ((m_timerShoot == 0 || m_timerShoot >= m_timeLimitShoot) && !m_isShooting && !m_lockShoot) {
		//m_lockThrow = true;
		m_isShooting = true;
		m_lockShoot = true;
		//m_tileOffsetX = 0.0f;
		cSoundsManager::play(eSoundTag::ak47);

		// Shoot particle
		cLevel *level = m_attachedLevel;
		level->addParticle(new cParticleShot);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_shot.cfg");
		level->getParticleLast()->attachParent(this);
			

		int offsetX = 0;
		/*if (m_isFacingLeft) {
		offsetX = -16;
		}*/
		if (cRenderingManager::getIsWidescreen()) {
			offsetX -= 60;
		}

		float startX = m_x + m_width / 2;
		float startY = 0.0f;
		startX = m_x + m_width / 2 - 8;

		if (getIsPressingDown()) {
			startY = getMiddleY() + 16;
		} else {
			startY = getMiddleY() + 8;
		}

		level->getParticleLast()->setX(startX);
		level->getParticleLast()->setY(startY);

		if (m_isFacingLeft) {
			level->getParticleLast()->setVelocityX(-10.0f + m_velocityX);
		} else {
			level->getParticleLast()->setVelocityX(10.0f + m_velocityX);
		}

		/*double direction = atan2(cInputManager::getMouseY() - 8 - startY, cInputManager::getMouseX() + offsetX - startX) * 180 / 3.141592f;
		level->getParticleLast()->setDirection(direction);

		level->getParticleLast()->setStartVelocityX(m_velocityX);
		level->getParticleLast()->setStartVelocityY(m_velocityY);

		level->getParticleLast()->setX(startX + (float)cos(direction * 3.141592f / 180.0f)*10.0f);
		level->getParticleLast()->setY(startY + (float)sin(direction * 3.141592f / 180.0f)*10.0f);

		level->getParticleLast()->setVelocityX(m_velocityX + (float)cos(direction * 3.141592f / 180.0f) * 10.0f);
		level->getParticleLast()->setVelocityY(m_velocityY + (float)sin(direction * 3.141592f / 180.0f) * 10.0f);*/

		//std::cout << player->m_particles.at(player->m_particles.size()-1)->getY() << "\n";		
	}
}

void cPlayer::digSand() {
	if (m_belowObject == nullptr) {
		return;
	}
	if (m_belowObject->getType().substr(0, 4) != "sand") {
		return;
	}
	if (m_velocityY < 0.0f || m_velocityY > m_fallAcc) {
		return;
	}
	/*if (cSoundsManager::getStatus(eSoundTag::swingDetach) == sf::SoundStream::Playing) {
		return;
	}*/
	m_velocityX = 0.0f;
	m_velocityY = 0.0f;
	m_downThrustCooldownValue = 10.0f;

	m_timerDig = 0;
	m_belowObject->setIsDead(true);
	m_belowObject->setTimeToBeDead(500.0f);

	m_belowObject->setTileOffsetX(0.0f);	
	
	cSoundsManager::stop(eSoundTag::swingDetach);
	cSoundsManager::play(eSoundTag::swingDetach);
	//int tmpInt = 0;
	//if (m_belowObject->getType().size() == 6) { // below 10
	//	std::istringstream(m_belowObject->getType().substr(5, 1)) >> tmpInt;
	//}
	//else if (m_belowObject->getType().size() == 7) { // 10 or above
	//	std::istringstream(m_belowObject->getType().substr(5, 2)) >> tmpInt;
	//}
	//cSavesManager::addSand(m_currentLevel, tmpInt);

	cLevel *level = m_attachedLevel;
	level->addParticle(new cParticle);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_dust.cfg");
	level->getParticleLast()->attachParent(this);
	level->getParticleLast()->setX(m_belowObject->getX());
	level->getParticleLast()->setY(m_belowObject->getY()-4.0f);
	level->getParticleLast()->setDoGravitate(true);
	level->getParticleLast()->setVelocityX(-2.0f);
	level->getParticleLast()->setVelocityY(-4.0f);
	level->getParticleLast()->setTimeToBeAlive(15);

	level->addParticle(new cParticle);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_dust.cfg");
	level->getParticleLast()->attachParent(this);
	level->getParticleLast()->setX(m_belowObject->getX());
	level->getParticleLast()->setY(m_belowObject->getY() - 4.0f);
	level->getParticleLast()->setDoGravitate(true);
	level->getParticleLast()->setVelocityX(2.0f);
	level->getParticleLast()->setVelocityY(-4.0f);
	level->getParticleLast()->setTimeToBeAlive(15);
}

void cPlayer::dropCarried() {
	if (m_carriedObject != nullptr/* && m_belowObject != nullptr*/) {
		float offsetX = 0.0f;
		float posX = 0.0f;

		if (getSenseCollidedLeft() && getIsFacingLeft() && getLeftObject() != nullptr && m_carriedObject->getLeftObject() == nullptr && m_carriedObject != getLeftObject()) {
			std::cout << "stacked left" << "\n";
			m_carriedObject->setStartY(getLeftObject()->getStartY() - 16);
			m_carriedObject->setY(getLeftObject()->getY() - 16);
			m_carriedObject->setStartX(getLeftObject()->getStartX());
			m_carriedObject->setX(getLeftObject()->getX());
			m_carriedObject->setIsCarried(false);
			setIsCarrying(false);
			setIsDropping(true);
			clearSenseLeft();;
		} else if (getSenseCollidedRight() && !getIsFacingLeft() && getRightObject() != nullptr && m_carriedObject->getRightObject() == nullptr && m_carriedObject != getRightObject()) {
			std::cout << "stacked right" << getRightObject()->getType() << "\n";
			m_carriedObject->setStartY(getRightObject()->getStartY() - 16);
			m_carriedObject->setY(getRightObject()->getY() - 16);
			m_carriedObject->setStartX(getRightObject()->getStartX());
			m_carriedObject->setX(getRightObject()->getX());
			m_carriedObject->setIsCarried(false);
			setIsCarrying(false);
			setIsDropping(true);
			clearSenseRight();
		} else {
			//std::cout << "hello" << "\n";
			if ((m_isFacingLeft && m_leftObject == nullptr && m_carriedObject->getLeftObject() == nullptr) || (!m_isFacingLeft && m_rightObject == nullptr && m_carriedObject->getRightObject() == nullptr)) {
				std::cout << "dropped" << "\n";
				if (m_isFacingLeft) {
					posX = getLeft() - m_carriedObject->getWidth() + m_carriedObject->getSubtractRight();
				} else {
					posX = getRight() - m_carriedObject->getSubtractLeft();
				}
				m_carriedObject->setX(posX);
				m_carriedObject->setY(getTop() - m_carriedObject->getHeight() / 2);
				m_carriedObject->setLevelY(getLevelY() + getSubtractUp() - m_carriedObject->getHeight() / 2);

				m_carriedObject->setIsCarried(false);
				m_carriedObject->setVelocityX(m_velocityX);
				if (m_velocityY < 0.0f) {
					m_carriedObject->setVelocityY(0.0f);
				} else {
					m_carriedObject->setVelocityY(m_velocityY);
				}
				setIsCarrying(false);
				setIsDropping(true);
				clearSenseLeft();
				clearSenseRight();
			}
		}		
	}
}

void cPlayer::throwCarried() {
	if (m_isInShop) {
		return;
	}
	m_thrownObject = m_carriedObject;
	m_carriedObject = nullptr;
	m_isCarrying = false;

	m_thrownObject->setIsCarried(false);
	m_thrownObject->setIsStatic(false);
	//object->setIsUsingFloatPosition(true);
	
	float velX = 0.0f;	
	m_isFacingLeft ? velX = -4.0f : velX = 4.0f;
	m_thrownObject->setVelocityX(velX + m_velocityX * 0.5f + m_movedVelocityX);
	addVelocityX(-m_thrownObject->getVelocityX() * 0.125f);

	setIsCarrying(false);
	setIsThrowing(true);
	setTimerThrow(getTimeLimitThrow());	

	setDelayCollisionEntity(15.0f);

	m_thrownObject->setVelocityY(m_velocityY * 1.0f - 2.5f);

	setAnim(eAnimTag::toss);
	setTileOffsetX(0.0f);

	if (!m_thrownObject->getIsThrown()) {
		m_thrownObject->setIsThrown(true);
		cEntityBrick* e = static_cast<cEntityBrick*>(m_thrownObject);
		e->setState(new cEntityBrickThrownState);
	}
	
}


void cPlayer::spawnSenses() {
	if (m_isOnLedge) { return; }
	cLevel* level;
	level = getAttachedLevel();

	float posX = 0.0f, posY = 0.0f;
	
	// ABOVE
	//if (getAnimTag() == eAnimTag::duck || m_isCrawling || keysHeld[cInputManager::getDownKey()]) {
	level->addParticle(new cParticleSenseAbove);
	level->getParticleLast()->attachParent(this);
	level->getParticleLast()->attachLevel(level);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_sense.cfg");
	level->getParticleLast()->setTimeToBeAlive(5.0f);
	level->getParticleLast()->setIsHidden(!cRenderingManager::getShowLevelNodeGrid());
	level->getParticleLast()->setWidth(m_width - m_subtractLeft - m_subtractRight + 2);
	level->getParticleLast()->setHeight(4);
	level->getParticleLast()->setOffsetY(-24);
	if (m_isFacingLeft) {
		level->getParticleLast()->setVelocityX(-level->getParticleLast()->getVelocityX() + m_velocityX + m_movedVelocityX);
		posX = (float)(getWidth() / 2 - level->getParticleLast()->getWidth() / 2) + 4;
	} else {
		level->getParticleLast()->setVelocityX(level->getParticleLast()->getVelocityX() + m_velocityX + m_movedVelocityX);
		posX = (float)(getWidth() / 2 - level->getParticleLast()->getWidth() / 2) - 4;
	}
	level->getParticleLast()->setX(getX() + posX);
	level->getParticleLast()->setLevelX(getLevelX() + posX);
	level->getParticleLast()->setStartX(getStartX() + posX);
	
	//level->getParticleLast()->setVelocityX(0.0f/*m_velocityX*//* + m_movedVelocityX*/);
	//level->getParticleLast()->setVelocityY(-2.0f);
	posY = (float)(getHeight() - level->getParticleLast()->getHeight() + level->getParticleLast()->getOffsetY());
	level->getParticleLast()->setY(getY() + posY);
	level->getParticleLast()->setLevelY(getLevelY() + posY);
	level->getParticleLast()->setStartY(getStartY() + posY);

	//// BELOW
	//level->addParticle(new cParticleSenseBelow);
	//level->getParticleLast()->attachParent(this);
	//level->getParticleLast()->attachLevel(level);
	//level->getParticleLast()->loadConfig("Data\\Particles\\p_sense.cfg");
	//level->getParticleLast()->setTimeToBeAlive(2.0f);
	//level->getParticleLast()->setIsHidden(!cRenderingManager::getShowLevelNodeGrid());
	//level->getParticleLast()->setWidth(16);
	//level->getParticleLast()->setHeight(8);
	//level->getParticleLast()->setOffsetX(0);
	//level->getParticleLast()->setOffsetY(0);	
	//level->getParticleLast()->setVelocityX(m_velocityX + m_movedVelocityX);
	//posX = (float)(getWidth() / 2 - level->getParticleLast()->getWidth() / 2);
	//level->getParticleLast()->setVelocityY(5.0f + m_velocityY + m_movedVelocityY);
	//level->getParticleLast()->setX(getX() + posX);
	//level->getParticleLast()->setLevelX(getLevelX() + posX);
	//level->getParticleLast()->setStartX(getStartX() + posX);
	//posY = (float)(getHeight() - level->getParticleLast()->getHeight() - 4);
	//level->getParticleLast()->setY(getY() + posY);
	//level->getParticleLast()->setLevelY(getLevelY() + posY);
	//level->getParticleLast()->setStartY(getStartY() + posY);

	// LEFT
	//level->getParticleLast()->update(0.0f);
	/*}
	else {*/
	level->addParticle(new cParticleSense);
	level->getParticleLast()->attachParent(this);
	level->getParticleLast()->attachLevel(level);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_sense.cfg");
	level->getParticleLast()->setTimeToBeAlive(8.0f);
	level->getParticleLast()->setIsHidden(!cRenderingManager::getShowLevelNodeGrid());
	level->getParticleLast()->setHeight(8);
	level->getParticleLast()->setOffsetY(-6);
	posX = (float)(getWidth() / 2 /*+ m_particleOffsetX*/ + 8 - level->getParticleLast()->getWidth());
	level->getParticleLast()->setX(getX() + posX);
	level->getParticleLast()->setLevelX(getLevelX() + posX);
	level->getParticleLast()->setStartX(getStartX() + posX);
	level->getParticleLast()->setVelocityX(-level->getParticleLast()->getVelocityX() + m_velocityX + m_movedVelocityX);
	posY = (float)(getHeight() - level->getParticleLast()->getHeight() + level->getParticleLast()->getOffsetY());
	level->getParticleLast()->setY(getY() + posY);
	level->getParticleLast()->setLevelY(getLevelY() + posY);
	level->getParticleLast()->setStartY(getStartY() + posY);
	//level->getParticleLast()->update(0.0f);


	// RIGHT
	level->addParticle(new cParticleSense);
	level->getParticleLast()->attachParent(this);
	level->getParticleLast()->attachLevel(level);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_sense.cfg");
	level->getParticleLast()->setTimeToBeAlive(8.0f);
	level->getParticleLast()->setIsHidden(!cRenderingManager::getShowLevelNodeGrid());
	level->getParticleLast()->setHeight(8);
	level->getParticleLast()->setOffsetY(-6);
	posX = (float)(getWidth() / 2 /*+ m_particleOffsetX*/ - 8);
	level->getParticleLast()->setX(getX() + posX);
	level->getParticleLast()->setLevelX(getLevelX() + posX);
	level->getParticleLast()->setStartX(getStartX() + posX);
	level->getParticleLast()->setVelocityX(level->getParticleLast()->getVelocityX() + m_velocityX + m_movedVelocityX);
	posY = (float)(getHeight() - level->getParticleLast()->getHeight() + level->getParticleLast()->getOffsetY());
	level->getParticleLast()->setY(getY() + posY);
	level->getParticleLast()->setLevelY(getLevelY() + posY);
	level->getParticleLast()->setStartY(getStartY() + posY);
	//level->getParticleLast()->update(0.0f);
}

bool cPlayer::getIsPressingUp() const {
	if (keysHeld[cInputManager::getUpKey()] || m_joyMovedY < -cInputManager::getJoyDeadzone()) {
		return true;
	}
	return false;
}
bool cPlayer::getIsPressingDown() const {
	if (keysHeld[cInputManager::getDownKey()] || m_joyMovedY > cInputManager::getJoyDeadzone()) {
		return true;
	}
	return false;
}
bool cPlayer::getIsPressingLeft() const {
	if ((keysHeld[cInputManager::getLeftKey()] || m_joyMovedX < -cInputManager::getJoyDeadzone()) && !m_isLockedMove) {
		return true;
	}
	return false;
}
bool cPlayer::getIsPressingRight() const {
	if ((keysHeld[cInputManager::getRightKey()] || m_joyMovedX > cInputManager::getJoyDeadzone()) && !m_isLockedMove) {
		return true;
	}
	return false;
}

void cPlayer::setIsPressingUp(bool isPressingUp) {
	keysHeld[cInputManager::getUpKey()] = isPressingUp;
	if (!isPressingUp) {
		m_joyMovedY = 0.0f;
	} else {
		m_joyMovedY = -cInputManager::getJoyDeadzone();
	}
}
void cPlayer::setIsPressingDown(bool isPressingDown) {
	keysHeld[cInputManager::getDownKey()] = isPressingDown;
	if (!isPressingDown) {
		m_joyMovedY = 0.0f;
	} else {
		m_joyMovedY = cInputManager::getJoyDeadzone();
	}
}
void cPlayer::setIsPressingLeft(bool isPressingLeft) {
	keysHeld[cInputManager::getLeftKey()] = isPressingLeft;
	if (!isPressingLeft) {
		m_joyMovedX = 0.0f;
	} else {
		m_joyMovedX = -cInputManager::getJoyDeadzone();
	}
}
void cPlayer::setIsPressingRight(bool isPressingRight) {
	keysHeld[cInputManager::getRightKey()] = isPressingRight;
	if (!isPressingRight) {
		m_joyMovedX = 0.0f;
	} else {
		m_joyMovedX = cInputManager::getJoyDeadzone();
	}
}

bool cPlayer::getIsPressingMelee() const {
	if (keysHeld[cInputManager::getMeleeKey()] || joyButtonsHeld[cInputManager::getMeleeJoyButton()] || mouseButtonsHeld[cInputManager::getMeleeMouseButton()]) {		
		return true;
	}
	return false;
}
void cPlayer::setIsPressingMelee(bool isPressingMelee) {
	keysHeld[cInputManager::getMeleeKey()] = isPressingMelee;
	joyButtonsHeld[cInputManager::getMeleeJoyButton()] = isPressingMelee;
	mouseButtonsHeld[cInputManager::getMeleeMouseButton()] = isPressingMelee;
}
bool cPlayer::getIsPressingJump() const {
	if (keysHeld[cInputManager::getJumpKey()] || joyButtonsHeld[cInputManager::getJumpJoyButton()] || mouseButtonsHeld[cInputManager::getJumpMouseButton()]) {
		return true;
	}
	return false;
}
void cPlayer::setIsPressingJump(bool isPressingJump) {
	keysHeld[cInputManager::getJumpKey()] = isPressingJump;
	joyButtonsHeld[cInputManager::getJumpJoyButton()] = isPressingJump;
	mouseButtonsHeld[cInputManager::getJumpMouseButton()] = isPressingJump;
}
bool cPlayer::getIsPressingSprint() const {
	if (keysHeld[cInputManager::getSprintKey()] || joyButtonsHeld[cInputManager::getSprintJoyButton()]) {
		return true;
	}
	return false;
}
void cPlayer::setIsPressingSprint(bool isPressingSprint) {
	keysHeld[cInputManager::getSprintKey()] = isPressingSprint;
	joyButtonsHeld[cInputManager::getSprintJoyButton()] = isPressingSprint;
}

bool cPlayer::getIsPressingShoot() const {
	if (keysHeld[cInputManager::getShootKey()] || joyButtonsHeld[cInputManager::getShootJoyButton()] || mouseButtonsHeld[cInputManager::getShootMouseButton()]) {
		return true;
	}
	return false;
}
void cPlayer::setIsPressingShoot(bool isPressingShoot) {
	keysHeld[cInputManager::getShootKey()] = isPressingShoot;
	joyButtonsHeld[cInputManager::getShootJoyButton()] = isPressingShoot;
	mouseButtonsHeld[cInputManager::getShootMouseButton()] = isPressingShoot;
}

bool cPlayer::getIsPressingThrow() const {
	if (keysHeld[cInputManager::getThrowKey()] || mouseButtonsHeld[cInputManager::getThrowMouseButton()]) {
		return true;
	}
	return false;
}
void cPlayer::setIsPressingThrow(bool isPressingThrow) {
	keysHeld[cInputManager::getThrowKey()] = isPressingThrow;
	mouseButtonsHeld[cInputManager::getThrowMouseButton()] = isPressingThrow;
}