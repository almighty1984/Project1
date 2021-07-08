#include "EntityFlyling.h"
#include "EntityFlylingDeathState.h"
#include "EntityFlylingFlightState.h"
#include "EntityItem.h"
//#include "InputManager.h"
#include "SoundBufferManager.h"
#include "RenderingManager.h"
#include "SoundsManager.h"

#include "Particle.h"
#include "ParticleBrick.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream> 

cEntityFlyling::cEntityFlyling() : m_secondCall(false) {
	//m_type = "e_flyling";
	m_numHealth = 50;
	

	m_state = new cEntityFlylingFlightState;
}

cEntityFlyling::~cEntityFlyling() {
	/*for (auto it = m_particles.begin(); it != m_particles.end(); ++it) {
		cRenderingManager::removeParticle(*it);
		delete *it;
	}
	m_particles.clear();*/

	delete m_state;
	m_state = nullptr;
	//m_isDead = true;
}

void cEntityFlyling::die(cBaseObject *killer) {
	m_numHealth = 0.0f;
	cSoundsManager::stop(eSoundTag::breakBlock);
	cSoundsManager::play(eSoundTag::breakBlock);

	cSoundsManager::stop(eSoundTag::hit);
	cSoundsManager::play(eSoundTag::hit);

	if (m_attachedLevel == nullptr) {
		return;
	}
	cLevel *level = m_attachedLevel;

	//object->update(NULL, 0.0f);
	float posX = getLevelX() + getWidth() / 2 - 8;
	float posY = getLevelY() + getHeight() / 2 - 8;

	//m_doSpawnNewParticle = true;

	level->addParticle(new cParticleBrick);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_brick.cfg");
	level->getParticleLast()->attachLevel(level);
	level->getParticleLast()->setX(getMiddleX() - 8);
	level->getParticleLast()->setY(getMiddleY() - 8);
	level->getParticleLast()->setStartX(m_levelX + m_width / 2 - level->getParticleLast()->getWidth() / 2);
	level->getParticleLast()->setStartY(m_levelY + m_width / 2 - level->getParticleLast()->getHeight() / 2);
	level->getParticleLast()->setLevelX(m_levelX + m_height / 2 - level->getParticleLast()->getWidth() / 2);
	level->getParticleLast()->setLevelY(m_levelY + m_height / 2 - level->getParticleLast()->getHeight() / 2);
	level->getParticleLast()->setVelocityX(-0.71f * 2.0f + m_velocityX * 0.25f);
	level->getParticleLast()->setVelocityY(-0.71f * 2.0f - 2.0f);
	level->getParticleLast()->update(0.0f);

	level->addParticle(new cParticleBrick);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_brick.cfg");
	level->getParticleLast()->attachLevel(level);
	level->getParticleLast()->setX(getMiddleX() - 8);
	level->getParticleLast()->setY(getMiddleY() - 8);
	level->getParticleLast()->setStartX(m_levelX + m_width / 2 - level->getParticleLast()->getWidth() / 2);
	level->getParticleLast()->setStartY(m_levelY + m_width / 2 - level->getParticleLast()->getHeight() / 2);
	level->getParticleLast()->setLevelX(m_levelX + m_height / 2 - level->getParticleLast()->getWidth() / 2);
	level->getParticleLast()->setLevelY(m_levelY + m_height / 2 - level->getParticleLast()->getHeight() / 2);
	level->getParticleLast()->setVelocityX(-0.71f * 2.0f + m_velocityX * 0.25f);
	level->getParticleLast()->setVelocityY(0.71f * 2.0f - 2.0f);
	level->getParticleLast()->update(0.0f);

	level->addParticle(new cParticleBrick);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_brick.cfg");
	level->getParticleLast()->attachLevel(level);
	level->getParticleLast()->setX(getMiddleX() - 8);
	level->getParticleLast()->setY(getMiddleY() - 8);
	level->getParticleLast()->setStartX(m_levelX + m_width / 2 - level->getParticleLast()->getWidth() / 2);
	level->getParticleLast()->setStartY(m_levelY + m_width / 2 - level->getParticleLast()->getHeight() / 2);
	level->getParticleLast()->setLevelX(m_levelX + m_height / 2 - level->getParticleLast()->getWidth() / 2);
	level->getParticleLast()->setLevelY(m_levelY + m_height / 2 - level->getParticleLast()->getHeight() / 2);
	level->getParticleLast()->setVelocityX(0.71f * 2.0f + m_velocityX * 0.25f);
	level->getParticleLast()->setVelocityY(-0.71f * 2.0f - 2.0f);
	level->getParticleLast()->update(0.0f);

	level->addParticle(new cParticleBrick);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_brick.cfg");
	level->getParticleLast()->attachLevel(level);
	level->getParticleLast()->setX(getMiddleX() - 8);
	level->getParticleLast()->setY(getMiddleY() - 8);
	level->getParticleLast()->setStartX(m_levelX + m_width / 2 - level->getParticleLast()->getWidth() / 2);
	level->getParticleLast()->setStartY(m_levelY + m_width / 2 - level->getParticleLast()->getHeight() / 2);
	level->getParticleLast()->setLevelX(m_levelX + m_height / 2 - level->getParticleLast()->getWidth() / 2);
	level->getParticleLast()->setLevelY(m_levelY + m_height / 2 - level->getParticleLast()->getHeight() / 2);
	level->getParticleLast()->setVelocityX(0.71f * 2.0f + m_velocityX * 0.25f);
	level->getParticleLast()->setVelocityY(0.71f * 2.0f - 2.0f);
	level->getParticleLast()->update(0.0f);
}


void cEntityFlyling::collisionReactionX(cBaseObject *object) {
	if (!m_isAttacking) {
		return;
	}

	/*std::cout << object->getType() << "\n";
	if (!m_isMeleeing) {
		return;
	}

	if (object->getType() == "e_brick") {
		object->die(this);
	}*/
	if (object->getType() == "e_brick") {
		//if (m_isMeleeing && !object->getIsDead() && !m_isDead) {
		//	die(object);
		//	object->die(this);
		//	/*m_isDead = true;
		//	setState(new cEntityFlylingDeathState);*/
		//}
	}
	else if (object->getType() == "e_grodorr") {
		if (object->getNumHealth() <= 0) { return; }

		if (object->getIsDead() == false && m_isHurting || m_isAttacking) {
			m_isDead = true;
			m_isAttacking = false;
			m_isCharging = false;
			setState(new cEntityFlylingDeathState);
			object->setVelocityX(0.0f);
			//object->setVelocityY(-1.0f);
			object->setTileOffsetX(0.0f);
			cSoundsManager::stop(eSoundTag::hit);
			cSoundsManager::play(eSoundTag::hit);

			unsigned char randNum;
			randNum = (rand() % 3);
			if (randNum == 0) {
				cSoundsManager::play(eSoundTag::fluganHurt0);
			}
			else if (randNum == 1) {
				cSoundsManager::play(eSoundTag::fluganHurt1);
			}
			else if (randNum == 2) {
				cSoundsManager::play(eSoundTag::fluganHurt2);
			}
			object->setHurtAgainDelayValue(object->getHurtAgainDelay());

			/*object->setVelocityX(m_velocityX*0.25f);
			object->setVelocityY(-2.0f);*/

			if (object->getIsHurting() == false) {
				m_numHealth = 0;
				object->setNumHealth(0/*object->getNumHealth() - 25 * player->getVitality()*/);
				if (object->getNumHealth() <= 0) {
					object->die(this);
				}
				std::cout << "cEntityFlyling::collisionReactionX " << object->getNumHealth() << "\n" << object->getNumHealth() << "\n" << "\n" << "\n" << "\n";
			}
			object->setHurtAgainDelayValue(object->getHurtAgainDelay());

			cLevel *level = m_attachedLevel;
			level->addParticle(new cParticle);
			level->getParticleLast()->loadConfig("Data\\Particles\\p_hit.cfg");
			level->getParticleLast()->attachParent(object);

			if (object->getX() + object->getWidth() / 2 < m_x + m_width / 2) {
				level->getParticleLast()->setX(object->getX() + object->getWidth() / 2 + level->getParticleLast()->getOffsetX());
			}
			else {
				level->getParticleLast()->setX(object->getX() + object->getWidth() / 2 + level->getParticleLast()->getOffsetX() - 32);
			}
			level->getParticleLast()->setY(object->getY() + object->getHeight() / 2 + level->getParticleLast()->getOffsetY());
			randNum = (rand() % 7) * 32;
			std::cout << "randNum: " << randNum << "\n";
			level->getParticleLast()->setTileOffsetX((float)randNum);
			level->getParticleLast()->setTileOffsetY(0.0f);
			level->getParticleLast()->setIsHidden(false);
			level->getParticleLast()->update(0.0f);

			//cRenderingManager::addParticle(object->m_particles.back());		
		}
	}
	else if (object->getType() == "e_train") {
		float a = getMiddleX() - object->getMiddleX();
		float b = (getMiddleY() + 16) - object->getMiddleY();

		float distance = sqrtf(powf(a, 2) + powf(b, 2));
		std::cout << "distance = " << distance << "\n";
		if (distance < 40) {
			cSoundsManager::stop(eSoundTag::hit);
			cSoundsManager::play(eSoundTag::hit);
			m_x = m_previousX;
			m_y = m_previousY;
			m_velocityX = -m_velocityX * 2;
			m_velocityY = -m_velocityY * 2;
			hit(getMiddleX(), getMiddleY() + 16);
			hurt(object, 100.0f);

		}
		//hit(getMiddleX(), getMiddleY()+16);
		//hit(entity->getMiddleX(), entity->getMiddleY());
	}
}

void cEntityFlyling::collisionReactionY(cBaseObject *object) {
	collisionReactionX(object);
}

void cEntityFlyling::update(cApp *app, float time) {
	if (m_attachedLevel == nullptr) {
		return;
	}
	if (m_isLocked) {
		//std::cout << "EntityFlugan locked!" << "\n" << "\n" << "\n";
		m_velocityX = 0.0f;
		m_velocityY = 0.0f;
		m_tileOffsetX = 0.0f;
		m_tileOffsetY = 0.0f;
	}
	else {
		// Update whatever state we're in, walk, charge, attack etc.
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
	}
	else {
		setAnimTime(getAnimTime() + getAnimSpeed());
	}

	if (getTileOffsetX() >= (getWidth() * getNumAnimFrames()) - getWidth()) {
		setTileOffsetX((float)(getWidth() * getNumAnimFrames() - getWidth()));
	}

	m_lastTime = time;

	if (m_numHealth <= 0.0f || m_numHealth == m_startHealth) {
		m_meterHealthBackground.setIsHidden(true);
		m_meterHealth.setIsHidden(true);
	}
	else {
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


	m_previousX = m_x;
	m_previousY = m_y;
	m_previousLevelX = m_levelX;
	m_previousLevelY = m_levelY;

	m_x += m_velocityX;
	m_y += m_velocityY;
	
	if (m_attachedLevel != nullptr) {
		m_levelX = m_startX + (m_x - m_startX) + m_attachedLevel->getX();
		m_levelY = m_startY + (m_y - m_startY) + m_attachedLevel->getY();

		//std::cout << "EntityFlyling " << (int)m_levelX << "  " << (int)m_levelY << "  " << m_attachedLevel->getX() << "\n";
	}
	
	if (m_hurtAgainDelayValue > 0.0f) {
		std::cout << m_hurtAgainDelayValue << "\n";
		m_isHurting = true;
		m_hurtAgainDelayValue -= time;
		m_doUseShader = true;
	} else {
		m_isHurting = false;
		m_hurtAgainDelayValue = 0.0f;
		m_doUseShader = false;		
	}

	//m_particles.at(0)->update(time);
	//if (m_particles.at(0)->getIsDead() == true) {
	//	m_particles.at(0)->setIsHidden(true);
	//	m_particles.at(0)->setTimeBeingAlive(0);
	//	//m_particles.at(0)->setCollidedBaggen(false);
	//	m_particles.at(0)->setIsDead(false);
	//	//cRenderingManager::addParticle(m_particles.at(0));
	//}

	/*for (unsigned short i=0; i<m_particles.size(); ++i) {
		m_particles.at(i)->update(time);

		if (m_particles.at(i)->getIsDead() == true) {
			cRenderingManager::removeParticle(m_particles.at(i));
			m_particles.erase(m_particles.begin()+i, m_particles.begin()+i+1);
		}
	}*/
}