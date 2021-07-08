#include "EntityGrodorr.h"
#include "EntityGrodorrBounceState.h"
#include "EntityGrodorrDeathState.h"
#include "EntityGrodorrIdleState.h"
#include "EntityGrodorrJumpState.h"
#include "EntityGrodorrStunnedState.h"
#include "EntityItem.h"
//#include "InputManager.h"
#include "SavesManager.h"
#include "SoundsManager.h"
#include "SoundBufferManager.h"
#include "RenderingManager.h"

#include "Particle.h"
#include "ParticleBrick.h"
#include "ParticleHealth.h"
#include "ParticleSenseGrodorr.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream> 

cEntityGrodorr::cEntityGrodorr() : m_secondCall(false) {
	m_type = "e_grodorr";

	m_width = 32;
	m_height = 32;

	m_velocityX = 0.0f;

	m_state = new cEntityGrodorrIdleState;

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

cEntityGrodorr::~cEntityGrodorr() {
	/*for (std::vector<cParticle*>::const_iterator itr = m_particles.begin(); itr != m_particles.end(); ++itr) {
		cRenderingManager::removeParticle(*itr);
		delete *itr;
	}
	m_particles.clear();*/

	delete m_state;
	m_state = nullptr;
	//m_isDead = true;
}

void cEntityGrodorr::collisionReactionX(cBaseObject *object) {
	if (object->getIsSlope()) {
		collisionReactionSlopeX(object);
		return;
	}
	if (object->getType().substr(0, 4) == "cam_") {
	} else if (object->getType().substr(0, 5) == "door_") {
	} else if (object->getType().substr(0, 8) == "slope_L_") {
	} else if (object->getType().substr(0, 8) == "slope_R_") {
	} else if (object->getType().substr(0, 5) == "sign_") {
	} else if (object->getType() == "swing") {
	} else if (object->getType().substr(0, 7) == "trigger") {
	} else if (object->getType().substr(0, 6) == "level_") {
	} else if (object->getType().substr(0, 5) == "view_") {
	} else if (object->getType().substr(0, 5) == "wall_") {
	} else if (object->getType().substr(0, 4) == "coin") {
	} else if (object->getType() == "e_flugan") {		
	} else if (object->getType().substr(0, 11) == "e_bounce_U_") {		
	} else if (object->getType().substr(0, 7) == "e_grass") {		
	} else if (object->getType() == "e_grevert") {		
	} else if (object->getType() == "e_grodorr") {		
	} else if (object->getType() == "e_pigan") {		
	} else if (object->getType() == "player") {
		std::cout << "Grodorr collided with player X\n";
		if (object->getX() < getX()) {
			object->setVelocityX(-2.5f);
		} else {
			object->setVelocityX(2.5f);
		}
	} else if (object->getType().substr(0, 7) == "target_") {
		if (object->getAnimTag() == eAnimTag::death) {
			return;
		}
		if (m_velocityX < 0.0f) {
			m_x = object->getX() + object->getWidth() - m_subtractLeft;
		}
		if (m_velocityX > 0.0f) {
			m_x = object->getX() - m_width + m_subtractRight;
		}
		m_velocityX *= -1.0f;
		m_isFacingLeft = !m_isFacingLeft;
		//m_x = m_previousX;
		m_levelX = m_previousLevelX;
	} else {
		if (m_velocityX < 0.0f) {
			m_x = object->getX() + object->getWidth() - m_subtractLeft;
		}
		if (m_velocityX > 0.0f) {
			m_x = object->getX() - m_width + m_subtractRight;
		}
		m_velocityX *= -1.0f;
		m_isFacingLeft = !m_isFacingLeft;
		//m_x = m_previousX;
		m_levelX = m_previousLevelX;
	}
}
void cEntityGrodorr::collisionReactionY(cBaseObject *object) {
	if (object->getIsSlope()) {
		collisionReactionSlopeY(object);
		m_isRiding = false;
		return;
	}
	if (object->getType().substr(0, 4) == "cam_") {
	} else if (object->getType().substr(0, 4) == "door") {
	} else if (object->getType().substr(0, 11) == "e_bounce_U_") {
	} else if (object->getType().substr(0, 7) == "e_grass") {
	} else if (object->getType().substr(0, 8) == "slope_L_") {
	} else if (object->getType().substr(0, 8) == "slope_R_") {
	} else if (object->getType().substr(0, 5) == "sign_") {
	} else if (object->getType() == "swing") {
	} else if (object->getType().substr(0, 7) == "target_") {
	} else if (object->getType().substr(0, 7) == "trigger") {
	} else if (object->getType().substr(0, 5) == "level") {
	} else if (object->getType().substr(0, 4) == "view") {
	} else if (object->getType().substr(0, 4) == "coin") {
	} else if (object->getType() == "player") {
		std::cout << "Grodorr collided with player Y\n";
		if (getMiddleY() < object->getMiddleY()) {
			m_velocityY = object->getVelocityY() / 4 - 4.0f;
			hit(getMiddleX(), getTop());
			if (object->getVelocityY() < 0.0f) {
				//die(object);
				hurt(object, 10.0f);				
			} else {
				object->hurt(this, 1.0f);
				//object->hit(getMiddleX() - 8, object->getBottom() - 8);
			}
			object->setVelocityY(3.0f);
			return;
		}
		m_isStunned = true;
		m_velocityY = m_fallVelocity;
		setState(new cEntityGrodorrBounceState);
	} else if (object->getType() == "clip_drop") {
		if (m_velocityY >= 0.0f) {
			m_isOnGround = true;
			m_isRiding = false;
			m_y = object->getTop() - m_height + m_subtractDown;
			m_velocityY = 0.0f;
		}
	} else if (object->getType() == "e_flugan") {
	} else if (object->getType() == "e_grevert") {
	} else if (object->getType() == "e_grodorr") {
	} else if (object->getType() == "e_pigan") {
		return;
		/*m_y = object->getTop() - m_height + m_subtractDown;
		m_velocityY = 0.0f;
		m_velocityX = 0.0f;
		m_movedVelocityY = object->getVelocityY();
		m_movedVelocityX = object->getVelocityX();
		m_isRiding = true;
		m_isOnGround = true;
		if (object->getIsOnBack()) {
			m_velocityY -= 3.0f;
		}*/
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
		m_isRiding = false;

		//m_y = m_previousY;
		//m_levelY = m_previousLevelY;
		//m_y = object->getY()-m_height;
	}
}

void cEntityGrodorr::die(cBaseObject *killer) {
	if (m_isDead || m_attachedLevel == nullptr) {
		return;
	}
	m_isDead = true;
	setVelocityY(0.0f);

	setState(new cEntityGrodorrDeathState);

	cSavesManager::addKilledGrodorr(m_attachedLevel->getPath(), m_tile);
	
	std::cout << "Entity number: " << m_tile << "\n";
	float posX = getLevelX() + getWidth() / 2 - 8;
	float posY = getLevelY() + getHeight() / 2 - 8;

	cLevel *level = m_attachedLevel;
	if (level == nullptr) { return; };

	float velX = 0.0f;
	
	if (killer != nullptr) {
		velX = killer->getVelocityX()/10;
	}

	level->addParticle(new cParticleBrick);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_brick.cfg");
	level->getParticleLast()->attachLevel(level);
	level->getParticleLast()->setX(getMiddleX() - 8);
	level->getParticleLast()->setY(getMiddleY() - 8);
	level->getParticleLast()->setStartX(posX);
	level->getParticleLast()->setStartY(posY);
	level->getParticleLast()->setLevelX(posX);
	level->getParticleLast()->setLevelY(posY);
	level->getParticleLast()->setVelocityX(-0.71f * 2.0f + m_velocityX * 0.25f + velX);
	level->getParticleLast()->setVelocityY(-0.71f * 2.0f - 2.0f);
	level->getParticleLast()->update(0.0f);

	level->addParticle(new cParticleBrick);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_brick.cfg");
	level->getParticleLast()->attachLevel(level);
	level->getParticleLast()->setX(getMiddleX() - 8);
	level->getParticleLast()->setY(getMiddleY() - 8);
	level->getParticleLast()->setStartX(posX);
	level->getParticleLast()->setStartY(posY);
	level->getParticleLast()->setLevelX(posX);
	level->getParticleLast()->setLevelY(posY);
	level->getParticleLast()->setVelocityX(-0.71f * 2.0f + m_velocityX * 0.25f + velX);
	level->getParticleLast()->setVelocityY(0.71f * 2.0f - 2.0f);
	level->getParticleLast()->update(0.0f);

	level->addParticle(new cParticleBrick);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_brick.cfg");
	level->getParticleLast()->attachLevel(level);
	level->getParticleLast()->setX(getMiddleX() - 8);
	level->getParticleLast()->setY(getMiddleY() - 8);
	level->getParticleLast()->setStartX(posX);
	level->getParticleLast()->setStartY(posY);
	level->getParticleLast()->setLevelX(posX);
	level->getParticleLast()->setLevelY(posY);
	level->getParticleLast()->setVelocityX(0.71f * 2.0f + m_velocityX * 0.25f + velX);
	level->getParticleLast()->setVelocityY(-0.71f * 2.0f - 2.0f);
	level->getParticleLast()->update(0.0f);

	level->addParticle(new cParticleBrick);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_brick.cfg");
	level->getParticleLast()->attachLevel(level);
	level->getParticleLast()->setX(getMiddleX() - 8);
	level->getParticleLast()->setY(getMiddleY() - 8);
	level->getParticleLast()->setStartX(posX);
	level->getParticleLast()->setStartY(posY);
	level->getParticleLast()->setLevelX(posX);
	level->getParticleLast()->setLevelY(posY);
	level->getParticleLast()->setVelocityX(0.71f * 2.0f + m_velocityX * 0.25f + velX);
	level->getParticleLast()->setVelocityY(0.71f * 2.0f - 2.0f);
	level->getParticleLast()->update(0.0f);

	for (int i = 0; i < 1; ++i) {
		level->addParticle(new cParticleHealth);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_health.cfg");
		level->getParticleLast()->attachLevel(level);
		level->getParticleLast()->attachParent(this);
		level->getParticleLast()->setIsDead(false);
		level->getParticleLast()->setX(getX() + getWidth() / 2 - 8.0f);
		level->getParticleLast()->setY(getY() + getHeight() / 2 + 8.0f);
		level->getParticleLast()->setStartX(posX);
		level->getParticleLast()->setStartY(posY);
		level->getParticleLast()->setLevelX(posX);
		level->getParticleLast()->setLevelY(posY);
	}
}

void cEntityGrodorr::hurt(cBaseObject *hurter, float amount) {
	if (getVelocityY() == 0.0f) {
		setVelocityY(-1.0f);
	}

	m_tileOffsetX = 0.0f;
	unsigned char randNum;
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
	cSoundsManager::stop(eSoundTag::hit);
	cSoundsManager::play(eSoundTag::hit);
	
	m_numHealth = m_numHealth - amount * m_attachedPlayer->getStrength();
	
	std::cout << getNumHealth() << "\n" << getNumHealth() << "\n" << "\n" << "\n" << "\n";
	
	//hit(basicObject->getX(), basicObject->getY());
	m_hurtAgainDelayValue = m_hurtAgainDelay;

	if (hurter->getType() == "p_shot") {
		m_velocityX += hurter->getVelocityX() * 0.1f;
		m_velocityY -= amount * 0.25f;
		setState(new cEntityGrodorrStunnedState);
	}
}

void cEntityGrodorr::spawnSenses() {
	if (m_attachedLevel == nullptr) { return; };
	cLevel* level;
	level = m_attachedLevel;
	level->addParticle(new cParticleSenseGrodorr);
	level->getParticleLast()->attachParent(this);
	level->getParticleLast()->attachLevel(level);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_sense_grodorr.cfg");
	level->getParticleLast()->setIsHidden(!cRenderingManager::getShowLevelNodeGrid());
	float posX = (float)(m_width / 2 /*+ m_particleOffsetX*/ + 4 - level->getParticleLast()->getWidth());
	level->getParticleLast()->setX(m_x + posX);
	level->getParticleLast()->setLevelX(m_levelX + posX);
	level->getParticleLast()->setStartX(m_startX + posX);
	level->getParticleLast()->setVelocityX(-level->getParticleLast()->getVelocityX());
	float posY = (float)(m_height - level->getParticleLast()->getHeight() + level->getParticleLast()->getOffsetY());
	level->getParticleLast()->setY(m_y + posY);
	level->getParticleLast()->setLevelY(m_levelY + posY);
	level->getParticleLast()->setStartY(m_startY + posY);

	level->addParticle(new cParticleSenseGrodorr);
	level->getParticleLast()->attachParent(this);
	level->getParticleLast()->attachLevel(level);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_sense_grodorr.cfg");
	level->getParticleLast()->setIsHidden(!cRenderingManager::getShowLevelNodeGrid());
	posX = (float)(m_width / 2 /*+ m_particleOffsetX*/ - 4);
	level->getParticleLast()->setX(m_x + posX);
	level->getParticleLast()->setLevelX(m_levelX + posX);
	level->getParticleLast()->setStartX(m_startX + posX);
	posY = (float)(m_height - level->getParticleLast()->getHeight() + level->getParticleLast()->getOffsetY());
	level->getParticleLast()->setY(m_y + posY);
	level->getParticleLast()->setLevelY(m_levelY + posY);
	level->getParticleLast()->setStartY(m_startY + posY);
}

void cEntityGrodorr::update(cApp *app, float time) {
	
	if (m_attachedLevel == nullptr) {
		return;
	}
	if (m_isLocked) {
		m_velocityX = 0.0f;
		m_velocityY = 0.0f;
		m_tileOffsetX = 0.0f;
		m_tileOffsetY = 0.0f;
		return;
	} else {
		if (m_state != nullptr) {
			m_state->update(app, this, time);
		}
	}
	if (m_isDead) {
		m_timeBeingDead += time;
	} else {
		m_timeBeingAlive += time;
	}

	// Update animation	
	if (m_animTime > 10.0f) {
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

	m_lastTime = time;	
	
	// Regenerate health
	if (m_numHealth > 0.0f) {
		if (m_numHealth < m_startHealth) {
			m_numHealth += 0.025f;
		} else if (m_numHealth > m_startHealth) {
			m_numHealth = m_startHealth;
		}
	}
	// Hide health bar at full health
	if (m_numHealth <= 0.0f || m_numHealth == m_startHealth || m_isDead) {
		m_meterHealthBackground.setIsHidden(true);
		m_meterHealth.setIsHidden(true);
	} else {
		m_meterHealthBackground.setIsHidden(false);
		m_meterHealth.setIsHidden(false);
	}
	m_meterHealthBackground.setX(m_x + (float)(m_width / 2 - m_meterHealthBackground.getWidth()/2));
	m_meterHealthBackground.setY(m_y + 16.0f);
	m_meterHealthBackground.setWidth((int)m_startHealth);
	m_meterHealthBackground.update(time);
	m_meterHealth.setX(m_x + m_width / 2 - m_meterHealthBackground.getWidth() / 2);
	m_meterHealth.setY(m_y + 16);
	m_meterHealth.setWidth((int)m_numHealth);
	m_meterHealth.update(time);

	if (m_velocityY < 0.0f) {
		m_isOnGround = false;
	}	

	m_previousX = m_x;
	m_previousY = m_y;
	m_previousLevelX = m_levelX;
	m_previousLevelY = m_levelY;

	m_x += (m_velocityX + m_movedVelocityX);
	m_y += (m_velocityY + m_movedVelocityY);

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

	/*for (unsigned short i = 0; i < m_particles.size(); ++i) {
		m_particles.at(i)->update(time);

		if (m_particles.at(i)->getIsDead()) {
			cRenderingManager::removeParticle(m_particles.at(i));
			m_particles.erase(m_particles.begin() + i, m_particles.begin() + i + 1);
		}
	}*/

	// Stop at small velocity
	if (m_isOnGround) {
		if (m_velocityX < m_moveDec && m_velocityX > -m_moveDec) {
			m_velocityX = 0.0f;
		}
	}
}