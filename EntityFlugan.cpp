#include "EntityFlugan.h"
#include "EntityFluganWalkState.h"
#include "EntityFluganChargeState.h"
#include "EntityFluganAttackState.h"
//#include "InputManager.h"
#include "SavesManager.h"
#include "SoundsManager.h"
#include "SoundBufferManager.h"
#include "RenderingManager.h"

#include "Particle.h"
#include "ParticleSenseFlugan.h"

#include "EntityItem.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream> 

cEntityFlugan::cEntityFlugan() : m_secondCall(false) {
	m_type = "e_flugan";

	m_width = 32;
	m_height = 32;

	m_velocityX = -0.75f;
	m_spriteOffsetX = 0.0f;
	m_spriteOffsetY = 0.0f;

	m_state = new cEntityFluganWalkState;

	m_meterHealth.setImagePath("Data\\Objects\\Images\\meter_health.png");
	m_meterHealth.setWidth((int)m_numHealth);
	m_meterHealth.setHeight(2);
	m_meterHealth.setIsHidden(false);

	m_meterHealthBackground.setImagePath("Data\\Objects\\Images\\meter_health_bg.png");
	m_meterHealthBackground.setWidth((int)m_numHealth);
	m_meterHealthBackground.setHeight(2);
	m_meterHealthBackground.setIsHidden(false);

	cRenderingManager::addObject(&m_meterHealthBackground);
	cRenderingManager::addObject(&m_meterHealth);
}

cEntityFlugan::~cEntityFlugan() {
	/*for (auto it = m_particles.begin(); it != m_particles.end(); ++it) {
		cRenderingManager::removeParticle(*it);
		delete *it;
	}
	m_particles.clear();*/

	delete m_state;
	m_state = nullptr;
	//m_isDead = true;
}


void cEntityFlugan::collisionReactionX(cBaseObject* object) {
	if (object->getIsSlope()) {
		collisionReactionSlopeX(object);
		return;
	}
	//std::cout << object->getType() << "\n";
	if (object->getType().substr(0, 11) == "e_bounce_U_" ||
		object->getType().substr(0, 3) == "cam" ||
		object->getType().substr(0, 4) == "door" ||
		/*object->getType().substr(0, 14) == "e_grodorr" ||*/
		object->getType().substr(0, 6) == "e_item" ||
		/*object->getType().substr(0, 6) == "entity" ||*/
		object->getType().substr(0, 4) == "sign" ||
		object->getType() == "swing" ||		
		object->getType().substr(0, 4) == "view" ||
		object->getType().substr(0, 4) == "wall") {
		return;
	} else if (object->getType() == "clip_top" || object->getType() == "clip_drop") {
	} else if (object->getType().substr(0, 4) == "coin") {
	} else if (object->getType().substr(0, 7) == "e_brick") {
		if (object->getIsDead() || object->getNumHealth() <= 0.0f) { return; };
		if (m_isAttacking) {
			object->die(this);
		} else {
			if (m_velocityX < 0.0f) {
				m_x = object->getX() + object->getWidth() - m_subtractLeft;
			} else if (m_velocityX > 0.0f) {
				m_x = object->getX() - m_width + m_subtractRight;
			}
			m_velocityX *= -1.0f;
			m_isFacingLeft = !m_isFacingLeft;
			//m_x = m_previousX;
			m_levelX = m_previousLevelX;
		}
	} else if (object->getType() == "e_flugan") {
	} else if (object->getType() == "e_flyling") {
	} else if (object->getType() == "e_grass") {
		object->setIsIdle(false);
		int num = 0;
		if (getMiddleX() < object->getMiddleX()) {
			object->setIsFacingLeft(false);
			num = (int)abs(object->getMiddleX() - getMiddleX());
			//std::cout << num << " " << num / 2 << "\n";
		} else {
			object->setIsFacingLeft(true);
			num = (int)abs(object->getMiddleX() - getMiddleX());
			//std::cout << num << " " << num / 2 << "\n";
		}
		float tileX = (num / 4) * 32.0f;
		object->setTileOffsetX(32 * 7 - tileX);
	} else if (object->getType() == "e_grodorr") {
	} else if (object->getType() == "e_grevert") {
	} else if (object->getType() == "e_grodorr") {
	} else if (object->getType() == "e_pigan") {
	}
	/*else if (object->getType().substr(0, 9) == "e_grodorr") {
		std::cout << m_type << "colliided with " << object->getType() << "\n";
		object->die(this);
	}*/
	else if (object->getType() == "player") {
		std::cout << "Flugan collided with player X\n";
		if (object->getMiddleX() < getMiddleX()) {
			m_x = object->getRight() - m_subtractLeft + 0;
			if (object->getIsNearWallLeft()) {
				m_isFacingLeft = false;
			}
			object->setVelocityX(-2.5f);
		} else if (object->getMiddleX() > getMiddleX()) {
			m_x = object->getLeft() - m_width + m_subtractRight - 0;
			if (object->getIsNearWallRight()) {
				m_isFacingLeft = true;
			}
			object->setVelocityX(2.5f);
		}
	} else if (object->getType().substr(0, 7) == "level_L") {
		m_x = m_previousX;
		m_velocityX = abs(m_velocityX);
	} else if (object->getType().substr(0, 7) == "level_R") {
		m_x = m_previousX;
		m_velocityX = -abs(m_velocityX);
	} else if (object->getType() == "slope_top") {
		m_y = object->getY() - m_height;
		m_velocityY = 0.0f;
	} else if (object->getType().substr(0, 7) == "target_") {
		if (object->getAnimTag() == eAnimTag::death) {
			return;
		}
		if (m_velocityX < 0.0f) {
			m_x = object->getRight() - m_subtractLeft;
		}
		if (m_velocityX > 0.0f) {
			m_x = object->getLeft() - m_width + m_subtractRight;
		}
		m_velocityX *= -1.0f;
		m_isFacingLeft = !m_isFacingLeft;
		//m_x = m_previousX;
		//m_levelX = m_previousLevelX;
	} else {
		if (m_velocityX < 0.0f) {
			m_x = object->getRight() - m_subtractLeft;
		}
		if (m_velocityX > 0.0f) {
			m_x = object->getLeft() - m_width + m_subtractRight;
		}
		m_velocityX *= -1.0f;
		m_isFacingLeft = !m_isFacingLeft;
		//m_x = m_previousX;
		//m_levelX = m_previousLevelX;
	}
}
void cEntityFlugan::collisionReactionY(cBaseObject* object) {
	//std::cout << object->getType() << "\n";
	if (object->getIsSlope()) {
		collisionReactionSlopeY(object);
		return;
	}
	if (object->getType().substr(0, 11) == "e_bounce_U_" ||
		object->getType().substr(0, 3) == "cam" ||
		object->getType().substr(0, 4) == "door" ||
		object->getType().substr(0, 6) == "e_item" ||
		/*object->getType().substr(0, 6) == "entity" ||*/
		object->getType().substr(0, 4) == "sign" ||
		object->getType() == "swing" ||
		object->getType().substr(0, 6) == "target" ||
		object->getType().substr(0, 5) == "level" ||
		object->getType().substr(0, 4) == "view" ||
		object->getType().substr(0, 4) == "wall") {
		return;
	} else if (object->getType() == "e_flugan") {
	} else if (object->getType() == "e_flyling") {
	} else if (object->getType() == "e_grass") {
		collisionReactionX(object);
	}
	/*else if (object->getType().substr(0, 7) == "e_brick") {
		if (object->getIsDead()) { return; };
		if (m_velocityY >= 0.0f) {
			m_y = object->getY() - m_height + m_subtractDown;
		} else {
			m_y = m_previousY;
		}
		m_velocityY = 0.0f;
		m_isOnGround = true;
	}*/
	else if (object->getType() == "e_grevert") {
	} else if (object->getType() == "e_grodorr") {
	} else if (object->getType() == "e_pigan") {
	} else if (object->getType() == "player") {
		//std::cout << "Flugan collided with player Y\n";
		if (getIsAttacking() && !getIsCharging()) {
			m_timerState = 0.0f;
		}
		if (!getIsCharging() && !getIsAttacking()/* && !m_isRiding*/) {
			setState(new cEntityFluganAttackState);
		}


		//if (m_isDownThrusting == true) {
		//	m_isDownThrusting = false;
		//	m_velocityY = -2.5f;
		//	cSoundsManager::play(eSoundTag::block);
		//	return;
		//}

		//m_isRiding = true;
		//m_isOnGround = true;
		//m_hasJumped = false;
		//m_velocityY = 0.0f;
		//
		////m_velocityY -= object->getForceYPlayerY();
		////m_y = m_previousY;
		//m_belowObject = entity;

		//m_y = entity->getY() + entity->getSubtractUp() - m_height + m_subtractDown/*+0.2f*/;
		//
	} else if (object->getType() == "clip_top") {
		if (m_velocityY >= 0.0f) {
			m_isOnGround = true;
			m_y = object->getY() - m_height + m_subtractDown + object->getSubtractUp();
		} else {
			return;
		}
	} else if (object->getType() == "clip_ledge_L") {
		m_y = object->getY() - m_height + m_subtractDown + object->getSubtractUp();
		m_velocityY = 0.0f;
		m_velocityX = abs(m_velocityX);
		m_isFacingLeft = false;
	} else if (object->getType() == "clip_ledge_R") {
		m_y = object->getY() - m_height + m_subtractDown + object->getSubtractUp();
		m_velocityY = 0.0f;
		if (m_velocityX > 0.0f && !m_isFacingLeft) {
			m_velocityX = -abs(m_velocityX);
			m_isFacingLeft = true;
		}
	} else if (object->getType().substr(0, 4) == "coin") {
	} else if (object->getType() == "e_grodorr") {
		return;
	} else if (object->getType() == "e_grevert") {
		return;
	} else if (object->getType() == "e_grodorr") {
		return;
	} else if (object->getType() == "e_pigan") {
		return;
	} else if (object->getType() == "slope_top") {
		m_y = object->getY() - m_height + m_subtractDown + object->getSubtractUp();
		m_isOnGround = true;
	} else {
		if (m_velocityY >= 0.0f) {
			m_y = object->getY() - m_height + m_subtractDown;
		} else {
			m_y = m_previousY;
		}
		//m_y = m_previousY;
		/*if (m_velocityY >= 0.0f) {
			m_y = object->getY()-m_height+m_subtractDown;
		}*/
		m_velocityY = 0.0f;
		m_isOnGround = true;

		//m_y = m_previousY;
		//m_levelY = m_previousLevelY;
		//m_y = object->getY()-m_height;
	}
}

void cEntityFlugan::die(cBaseObject* killer) {
	if (m_isDead) {
		return;
	}
	//m_isDead = true;
	setVelocityY(0.0f);

	if (m_attachedLevel == nullptr) {
		return;
	}

	cLevel* level = m_attachedLevel;

	cSavesManager::addKilledFlugan(level->getPath(), m_tile);

	std::cout << "Entity number: " << m_tile << "\n";
	level->addParticle(new cParticle);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_dust.cfg");
	level->getParticleLast()->attachParent(this);
	level->getParticleLast()->setX(getX() + getWidth() / 2);
	level->getParticleLast()->setY(getY() + getHeight() / 2);
	level->getParticleLast()->setDoGravitate(true);
	level->getParticleLast()->setVelocityX(getVelocityX() - 2.0f);
	level->getParticleLast()->setVelocityY(getVelocityY() - 2.0f);
	level->getParticleLast()->setTimeToBeAlive(15);

	level->addParticle(new cParticle);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_dust.cfg");
	level->getParticleLast()->attachParent(this);
	level->getParticleLast()->setX(getX() + getWidth() / 2);
	level->getParticleLast()->setY(getY() + getHeight() / 2);
	level->getParticleLast()->setDoGravitate(true);
	level->getParticleLast()->setVelocityX(getVelocityX() + 2.0f);
	level->getParticleLast()->setVelocityY(getVelocityY() - 2.0f);
	level->getParticleLast()->setTimeToBeAlive(15);

	for (int i = 0; i < 1; ++i) {
		level->addParticle(new cParticle);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_health.cfg");
		level->getParticleLast()->setIsDead(false);
		level->getParticleLast()->setIsAnim(true);
		level->getParticleLast()->setX(getX() + getWidth() / 2 - 8.0f);
		level->getParticleLast()->setY(getY() + getHeight() / 2 + 8.0f);
		level->getParticleLast()->setStartX((getX() + getWidth() / 2) - 8.0f);
		level->getParticleLast()->setStartY((getY() + getHeight() / 2) + 8.0f);
		level->getParticleLast()->setLevelX(getLevelX());
		level->getParticleLast()->setLevelY(getLevelY());

		level->getParticleLast()->setVelocityX(0.0f);
		level->getParticleLast()->setVelocityY(0.0f);
		level->getParticleLast()->attachLevel(level);

		level->getParticleLast()->attachParent(this);
	}
}

void cEntityFlugan::hurt(cBaseObject* hurter, float amount) {
	/*if (getX() + getWidth() / 2 < basicObject->getX() + basicObject->getWidth() / 2) {
		hit(basicObject->getX() + basicObject->getWidth() / 2, basicObject->getY() + basicObject->getHeight() / 2);
	}
	else {
		hit(basicObject->getX() + basicObject->getWidth() / 2 - 32, basicObject->getY() + basicObject->getHeight() / 2);
	}*/

	m_tileOffsetX = 0.0f;
	if (!m_isDead) {
		unsigned char randNum;
		cSoundsManager::stop(eSoundTag::hit);
		cSoundsManager::play(eSoundTag::hit);

		randNum = (rand() % 3);
		if (randNum == 0) {
			cSoundsManager::stop(eSoundTag::fluganHurt0);
			cSoundsManager::play(eSoundTag::fluganHurt0);
		} else if (randNum == 1) {
			cSoundsManager::stop(eSoundTag::fluganHurt1);
			cSoundsManager::play(eSoundTag::fluganHurt1);
		} else if (randNum == 2) {
			cSoundsManager::stop(eSoundTag::fluganHurt2);
			cSoundsManager::play(eSoundTag::fluganHurt2);
		}

		m_numHealth = m_numHealth - amount * m_attachedPlayer->getStrength();
		m_hurtAgainDelayValue = m_hurtAgainDelay;
		m_isAttacking = true;
		//cRenderingManager::sleep(120);
	}
}

void cEntityFlugan::update(cApp* app, float time) {
	if (m_attachedLevel == nullptr) {
		return;
	}
	if (m_isLocked) {
		m_velocityX = 0.0f;
		m_velocityY = 0.0f;
		m_tileOffsetX = 0.0f;
		m_tileOffsetY = 0.0f;
	} else {
		if (m_state != nullptr) {
			m_state->update(app, this, time);
		}
	}

	// Update animation	
	if (m_animTime >= 10.0f) {
		m_tileOffsetX += m_width;

		if (m_tileOffsetX >= m_width * m_numAnimFrames) {
			if (m_currentLoops < m_numAnimLoops && m_numAnimLoops != 0) {
				//m_tileOffsetX = 0;
				m_tileOffsetX = (float)(m_width * m_numAnimFrames);
				setCurrentLoops(getCurrentLoops() + 1);
			}
			if (getNumAnimLoops() == 0) {
				setTileOffsetX(0.0f);
				setCurrentLoops(0);
			}
		}
		setAnimTime(0.0f);
	} else {
		setAnimTime(getAnimTime() + getAnimSpeed());
	}

	if (getTileOffsetX() >= (getWidth() * getNumAnimFrames()) - getWidth()) {
		setTileOffsetX((float)(getWidth() * getNumAnimFrames() - getWidth()));
	}

	// Regenerate health
	if (m_numHealth > 0.0f) {
		if (m_numHealth < m_startHealth) {
			m_numHealth += 0.025f;
		} else if (m_numHealth > m_startHealth) {
			m_numHealth = m_startHealth;
		}
	}
	// Hide health bar at full health
	if (m_numHealth <= 0.0f || m_numHealth == m_startHealth) {
		m_meterHealthBackground.setIsHidden(true);
		m_meterHealth.setIsHidden(true);
	} else {
		m_meterHealthBackground.setIsHidden(false);
		m_meterHealth.setIsHidden(false);
	}

	m_meterHealthBackground.setX(m_x);
	m_meterHealthBackground.setY(m_y + 16);
	m_meterHealthBackground.setWidth((int)m_startHealth);
	m_meterHealthBackground.update(time);

	m_meterHealth.setX(m_x);
	m_meterHealth.setY(m_y + 16);
	m_meterHealth.setWidth((int)m_numHealth);
	m_meterHealth.update(time);


	//m_particles.at(0)->update(time);

	//if (m_particles.at(0)->getIsDead() == true) {
	//	m_particles.at(0)->setIsHidden(true);
	//	m_particles.at(0)->setTimeBeingAlive(0);
	//	//m_particles.at(0)->setCollidedBaggen(false);
	//	m_particles.at(0)->setIsDead(false);
	//	cRenderingManager::addParticle(m_particles.at(0));
	//}

	if (m_isCharging == false) {
		m_secondCall = false;
	}

	m_previousX = m_x;
	m_previousY = m_y;
	m_previousLevelX = m_levelX;
	m_previousLevelY = m_levelY;

	m_x += m_velocityX;
	m_y += m_velocityY;

	m_levelX = m_startX + (m_x - m_startX) + m_attachedLevel->getX();
	m_levelY = m_startY + (m_y - m_startY) + m_attachedLevel->getY();

	//std::cout << (int)m_levelX << "  " << (int)m_levelY << "  " << m_attachedLevel->getX() << "\n";

/*if (m_velocityX > 0.0f) {
	m_isFacingLeft = false;
} else if (m_velocityX < 0.0f) {
	m_isFacingLeft = true;
}
*/

	if (m_hurtAgainDelayValue > 0.0f) {
		m_isHurting = true;
		m_hurtAgainDelayValue -= time;
		m_doUseShader = true;
	} else {
		m_isHurting = false;
		m_hurtAgainDelayValue = 0.0f;
		m_doUseShader = false;
		//std::cout << m_hurtAgainDelayValue << "\n";
	}

	//if(m_attachedPlayer != nullptr) {
	//	if(( m_y < m_attachedPlayer->getY() && m_attachedPlayer->getY() - m_y < 32) || ( m_y > m_attachedPlayer->getY() && m_y - m_attachedPlayer->getY() < 32) )  {
	//		if( (m_x+32 < m_attachedPlayer->getX()+32) && (m_attachedPlayer->getX() - m_x < 96 && !m_isFacingLeft) ||	(m_x+32 > m_attachedPlayer->getX()+32) && (m_x - m_attachedPlayer->getX() < 96 && m_isFacingLeft)	) {
	//			if(m_isCharging == false && m_isMeleeing == false) {
	//				//m_chargeTimer = 0;
	//				std::cout << "new cEntityFluganChargeState" << "\n";
	//				setState(new cEntityFluganChargeState);
	//				m_isCharging = true;
	//				m_isMeleeing = false;
	//				m_timerState = 0;
	//			}
	//		}
	//		else {
	//			if(m_isMeleeing == true && m_timerState > 200) {
	//				std::cout << "new cEntityFluganWalkState" << "\n";
	//				setState(new cEntityFluganWalkState);
	//				m_isCharging = false;
	//				m_isMeleeing = false;
	//				m_timerState = 0;
	//			}
	//		}
	//	}		
	//}

	/*for (unsigned short i = 0; i < m_particles.size(); ++i) {
		m_particles.at(i)->update(time);

		if (m_particles.at(i)->getIsDead() == true) {
			cRenderingManager::removeParticle(m_particles.at(i));
			m_particles.erase(m_particles.begin() + i, m_particles.begin() + i + 1);
		}
	}*/
}

void cEntityFlugan::spawnSenses() {
	cLevel* level = m_attachedLevel;

	level->addParticle(new cParticleSenseFlugan);
	level->getParticleLast()->attachParent(this);
	level->getParticleLast()->attachLevel(level);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_sense_flugan.cfg");
	level->getParticleLast()->setIsHidden(!cRenderingManager::getShowLevelNodeGrid());
	//level->getParticleLast()->setTimeToBeAlive(20);

	float posX = getMiddleX() - level->getParticleLast()->getWidth() / 2;
	float posY = getMiddleY() - level->getParticleLast()->getHeight() / 2 + level->getParticleLast()->getOffsetY();
	float levelPosX = getLevelX() + getWidth() / 2 - level->getParticleLast()->getWidth() / 2;
	float levelPosY = getLevelY() + getHeight() / 2 - level->getParticleLast()->getHeight() / 2 + level->getParticleLast()->getOffsetY();

	if (m_isFacingLeft) {
		//posX -= level->getParticleLast()->getWidth();
		//levelPosX -= level->getParticleLast()->getWidth();
		level->getParticleLast()->setVelocityX(-level->getParticleLast()->getVelocityX());
	}

	level->getParticleLast()->setX(posX);
	level->getParticleLast()->setY(posY);

	level->getParticleLast()->setStartX(levelPosX);
	level->getParticleLast()->setStartY(levelPosY);
	level->getParticleLast()->setLevelX(levelPosX);
	level->getParticleLast()->setLevelY(levelPosY);
}