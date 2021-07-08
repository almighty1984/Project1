#include "EntityBrick.h"
#include "EntityBrickIdleState.h"
#include "EntityBrickDeathState.h"
#include "RenderingManager.h"
#include "ParticleBrick.h"
#include "ParticleSenseBrick.h"
#include "SoundsManager.h"

cEntityBrick::cEntityBrick() {
	m_type = "e_brick";

	m_velocityX = 0.0f;

	m_state = new cEntityBrickIdleState;

}

cEntityBrick::~cEntityBrick() {
	/*for (std::vector<cParticle*>::const_iterator itr = m_particles.begin(); itr != m_particles.end(); ++itr) {
		cRenderingManager::removeParticle(*itr);
		delete* itr;
	}
	m_particles.clear();*/

	delete m_state;
	m_state = nullptr;
	//m_isDead = true;
}

void cEntityBrick::collisionReactionX(cBaseObject *object) {
	if (object->getIsSlope()) {
		collisionReactionSlopeX(object);
		return;
	}
	/*if (m_isCarried) {
		std::cout << "hello" << "\n";
	}*/
	if (object->getType() == "e_bounce_U_0" || object->getType() == "e_bounce_U_1" ||
		object->getType().substr(0, 3) == "cam" ||
		object->getType().substr(0, 4) == "coin" ||
		object->getType().substr(0, 4) == "door" ||
		object->getType().substr(0, 6) == "e_item" ||		
		object->getType().substr(0, 4) == "sign" ||
		object->getType() == "swing" ||
		object->getType().substr(0, 5) == "level" ||
		object->getType().substr(0, 4) == "view" ||
		object->getType().substr(0, 4) == "wall") {
		return;
	} else if (object->getType() == "clip" || object->getType() == "clip_crawl") {
		m_velocityX = 0.0f;
		m_movedVelocityX = 0.0f;
		if (getMiddleX() < object->getMiddleX()) {
			m_x = object->getLeft() - m_width + m_subtractRight;
		} else {
			m_x = object->getRight() - m_subtractLeft;
		}
		if (m_isCarried && m_carrier != nullptr) {
			std::cout << "x" << "\n";
			m_carrier->setVelocityX(0.0f);
			m_carrier->setMovedVelocityX(0.0f);
			if (getMiddleX() < object->getMiddleX()) {
				m_carrier->setX(object->getLeft() - m_carrier->getWidth() + m_carrier->getSubtractRight());
			} else {
				m_carrier->setX(object->getRight() - m_carrier->getSubtractLeft());
			}
		}
		//die(object);
	} else if (object->getType() == "clip_drop" || object->getType() == "clip_top") {
		return;
	} else if (object->getType() == "e_brick") {
		if (getMiddleX() < object->getMiddleX()) {
			m_x = object->getLeft() - m_width;
		} else {
			m_x = object->getRight();
		}
		/*die(object);
		object->die(this);*/
	} else if (object->getType() == "e_grodorr") {
		if (m_isThrown) {
			die(object);
			object->die(this);
		}
	} else if (object->getType() == "e_pigan") {
		if (m_isThrown) {
			die(object);
			object->die(this);
		}
	} else if (object->getType().substr(0, 7) == "target_") {
		if (object->getAnimTag() == eAnimTag::death) {
			return;
		}
		if (getMiddleX() < object->getMiddleX()) {
			m_x = object->getLeft() - m_width;
		} else {
			m_x = object->getRight();
		}
		m_velocityX = 0.0f;
		m_movedVelocityX = object-> getVelocityX() + object->getMovedVelocityX();
		/*if (object->getAnimTag() == eAnimTag::idle) {
			die(object);
		}*/
	}
}

void cEntityBrick::collisionReactionY(cBaseObject* object) {
	if (object->getIsSlope()) {
		collisionReactionSlopeY(object);
		return;
	}
	if (object->getType() == "e_bounce_U_0" || object->getType() == "e_bounce_U_1" ||
		object->getType().substr(0, 3) == "cam" ||
		object->getType().substr(0, 4) == "coin" ||
		object->getType().substr(0, 4) == "door" ||
		object->getType().substr(0, 6) == "e_item" ||
		object->getType().substr(0, 4) == "sign" ||
		object->getType() == "swing" ||
		object->getType().substr(0, 5) == "level" ||
		object->getType().substr(0, 4) == "view" ||
		object->getType().substr(0, 4) == "wall") {
		return;
	} else if (object->getType() == "clip" || object->getType() == "clip_crawl") {
		m_movedVelocityX = 0.0f;
		if (m_velocityY >= 0.0f) {
			if (getMiddleY() < object->getMiddleY()) {
				m_isThrown = false;
				m_movedVelocityX = 0.0f;
				//die(object);
				m_velocityX *= 0.5f;
				m_velocityY = 0.0f;
				m_y = object->getTop() - m_height;
			}
		} else if (m_velocityY < 0.0f) {
			m_y = object->getBottom() - m_subtractUp;
			m_velocityY = 0.0f;
			if (m_isCarried && m_carrier != nullptr) {
				m_carrier->setVelocityY(0.0f);
				m_carrier->setY(getBottom() - m_carrier->getSubtractUp());
			}
		}
	} else if (object->getType() == "clip_drop" || object->getType() == "clip_top" || object->getType() == "slope_top") {
		if (m_velocityY >= 0.0f) {
			if (getMiddleY() < object->getMiddleY()) {
				m_movedVelocityX = 0.0f;
				//die(object);
				m_velocityX *= 0.5f;
				m_velocityY = 0.0f;
				m_y = object->getTop() - m_height;
			}
		}
	} else if (object->getType() == "e_brick") {
		if (m_velocityY >= 0.0f) {
			if (getMiddleY() < object->getMiddleY()) {
				m_velocityX *= 0.5f;
				m_velocityY = 0.0f;
				m_y = object->getTop() - m_height;
				m_belowObject = object;
				if (m_belowObject != nullptr) {
					if (m_belowObject->getBelowObject() != nullptr) {
						if (m_belowObject->getBelowObject()->getBelowObject() != nullptr) {
							m_movedVelocityX = m_belowObject->getBelowObject()->getBelowObject()->getVelocityX() + m_belowObject->getBelowObject()->getBelowObject()->getMovedVelocityX();
							m_movedVelocityY = m_belowObject->getBelowObject()->getBelowObject()->getVelocityY() + m_belowObject->getBelowObject()->getBelowObject()->getMovedVelocityY();
						} else {
							m_movedVelocityX = m_belowObject->getBelowObject()->getVelocityX() + m_belowObject->getBelowObject()->getMovedVelocityX();
							m_movedVelocityY = m_belowObject->getBelowObject()->getVelocityY() + m_belowObject->getBelowObject()->getMovedVelocityY();
						}						
					} else {
						m_movedVelocityX = m_belowObject->getVelocityX() + m_belowObject->getMovedVelocityX();
						m_movedVelocityY = m_belowObject->getVelocityY() + m_belowObject->getMovedVelocityY();
					}
				}/* else {					
					m_movedVelocityX = object->getVelocityX() + object->getMovedVelocityX();
					m_movedVelocityY = object->getVelocityY() + object->getMovedVelocityY();
				}*/
			}
		} else if (m_velocityY < 0.0f) {
			m_y = object->getBottom() - m_subtractUp;
			m_velocityY = 0.0f;
			if (m_isCarried && m_carrier != nullptr) {
				m_carrier->setVelocityY(0.0f);
				m_carrier->setY(getBottom() - m_carrier->getSubtractUp());
			}
		}
	} else if (object->getType() == "e_grodorr") {
		collisionReactionX(object);
	} else if (object->getType().substr(0, 7) == "e_train") {
		if (getMiddleY() < object->getMiddleY()) {
			//if (m_velocityY > m_fallAcc) {
				m_velocityX *= 0.5f;
			//}
			m_velocityY = 0.0f;
			m_y = object->getTop() - m_height;
			m_movedVelocityX = object->getVelocityX() + object->getMovedVelocityX();
			m_movedVelocityY = object->getVelocityY() + object->getMovedVelocityY();
		}
	} else if (object->getType() == "e_pigan") {
		collisionReactionX(object);
	} else if (object->getType().substr(0, 7) == "target_") {
		if (object->getAnimTag() == eAnimTag::death) {
			return;
		}
		if (getMiddleY() < object->getMiddleY()) {
			m_y = object->getTop() - m_height;
		} else {
			m_y = object->getBottom();
		}
		m_isThrown = false;
		m_velocityY = 0.0f;
		m_movedVelocityX = object->getVelocityX() + object->getMovedVelocityX();
		m_movedVelocityY = object->getVelocityY() + object->getMovedVelocityY();
	}
}
void cEntityBrick::die(cBaseObject *killer) {
	std::cout << "cEntityBrick::die start";
	if (killer == nullptr) {
		return;
	}
	if (m_isDead) {
		return;
	}
	m_numHealth = 0.0f;
	m_isDead = true;	

	cSoundsManager::stop(eSoundTag::breakBlock);
	cSoundsManager::play(eSoundTag::breakBlock);

	cSoundsManager::stop(eSoundTag::hit);
	cSoundsManager::play(eSoundTag::hit);

	cLevel *level = m_attachedLevel;
	if (level == nullptr) { return; };

	//object->update(NULL, 0.0f);

	//m_doSpawnNewParticle = true;

	float velX = killer->getVelocityX();
	if (killer->getType() == "p_melee") {
		cParticle *particle;
		particle = static_cast<cParticle*>(killer);
		if (particle->getParent() != nullptr) {
			velX = particle->getParent()->getVelocityX();
		}		
	}

	float posX = getLevelX() + getWidth() / 2 - 8;
	float posY = getLevelY() + getHeight() / 2 - 8;

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

	
	/*m_startX = m_oldStartX;
	m_startY = m_oldStartY;
	if (m_attachedLevel == nullptr) {
		return;
	}
	m_x = -m_attachedLevel->getX() + m_startX;
	m_y = -m_attachedLevel->getY() + m_startY;
	m_levelX = m_startX + (m_x - m_startX) + m_attachedLevel->getX();
	m_levelY = m_startY + (m_y - m_startY) + m_attachedLevel->getY();*/
	
	setState(new cEntityBrickDeathState);
	std::cout << "cEntityBrick::die end" << "\n";
}


void cEntityBrick::live() {
	if (!m_isDead) {
		return;
	}
	std::cout << "cEntityBrick::live " << "\n";
	m_isDead = false;
	setState(new cEntityBrickIdleState);

	m_x += (m_velocityX + m_movedVelocityX)/**time*/;
	m_y += (m_velocityY + m_movedVelocityY)/**time*/;

	m_startX = m_oldStartX;
	m_startY = m_oldStartY;

	/*if (m_attachedLevel == nullptr) {
		return;
	}
	m_x = -m_attachedLevel->getX() + m_startX;
	m_y = -m_attachedLevel->getY() + m_startY;
	m_levelX = m_startX + (m_x - m_startX) + m_attachedLevel->getX();
	m_levelY = m_startY + (m_y - m_startY) + m_attachedLevel->getY();*/
}


void cEntityBrick::update(cApp *app, float time) {
	//if (m_isCarried) {
	//	//std::cout << "carried" << "\n";
	//	if (m_leftObject != nullptr) {
	//		std::cout << m_leftObject->getType() << " ";
	//	}
	//	if (m_rightObject != nullptr) {
	//		std::cout << m_rightObject->getType() << "\n";
	//	}
	//}	
	
	if (getTimerSense() > 1.0f && m_attachedLevel != nullptr && !m_isDead) {
		setTimerSense(0.0f);

		cLevel* level;
		level = getAttachedLevel();
		float posX = 0.0f, posY = 0.0f;
		//if (getAnimTag() == eAnimTag::duck || m_isCrawling || keysHeld[cInputManager::getDownKey()]) {
		level->addParticle(new cParticleSenseBrick);
		level->getParticleLast()->attachParent(this);
		level->getParticleLast()->attachLevel(level);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_sense_brick.cfg");
		level->getParticleLast()->setIsHidden(!cRenderingManager::getShowLevelNodeGrid());
		level->getParticleLast()->setTimeToBeAlive(4);
		level->getParticleLast()->setWidth(m_width - m_subtractLeft - m_subtractRight - 0);
		level->getParticleLast()->setWidth(8);
		level->getParticleLast()->setHeight(8);
		level->getParticleLast()->setOffsetY(-8);
		posX = (float)(getWidth() / 2 /*+ m_particleOffsetX*/ - level->getParticleLast()->getWidth() / 2);
		level->getParticleLast()->setX(getX() + posX);
		level->getParticleLast()->setLevelX(getLevelX() + posX);
		level->getParticleLast()->setStartX(getStartX() + posX);
		level->getParticleLast()->setVelocityX(m_velocityX/* + m_movedVelocityX*/);
		level->getParticleLast()->setVelocityY(-2.0f);
		posY = (float)(getHeight() - level->getParticleLast()->getHeight() + level->getParticleLast()->getOffsetY());
		level->getParticleLast()->setY(getY() + posY);
		level->getParticleLast()->setLevelY(getLevelY() + posY);
		level->getParticleLast()->setStartY(getStartY() + posY);
		level->getParticleLast()->update(0.0f);

		level->addParticle(new cParticleSenseBrick);
		level->getParticleLast()->attachParent(this);
		level->getParticleLast()->attachLevel(level);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_sense_brick.cfg");
		level->getParticleLast()->setTimeToBeAlive(8);
		level->getParticleLast()->setIsHidden(!cRenderingManager::getShowLevelNodeGrid());
		level->getParticleLast()->setHeight(12);
		level->getParticleLast()->setOffsetY(0);
		posX = (float)(getWidth() / 2 /*+ m_particleOffsetX*/ + 8 - level->getParticleLast()->getWidth());
		level->getParticleLast()->setX(getX() + posX);
		level->getParticleLast()->setLevelX(getLevelX() + posX);
		level->getParticleLast()->setStartX(getStartX() + posX);
		level->getParticleLast()->setVelocityX(-level->getParticleLast()->getVelocityX() + m_velocityX + m_movedVelocityX);
		posY = (float)(getHeight() - level->getParticleLast()->getHeight() + level->getParticleLast()->getOffsetY());
		level->getParticleLast()->setY(getY() + posY);
		level->getParticleLast()->setLevelY(getLevelY() + posY);
		level->getParticleLast()->setStartY(getStartY() + posY);
		level->getParticleLast()->update(0.0f);

		level->addParticle(new cParticleSenseBrick);
		level->getParticleLast()->attachParent(this);
		level->getParticleLast()->attachLevel(level);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_sense_brick.cfg");
		level->getParticleLast()->setTimeToBeAlive(8);
		level->getParticleLast()->setIsHidden(!cRenderingManager::getShowLevelNodeGrid());
		level->getParticleLast()->setHeight(12);
		level->getParticleLast()->setOffsetY(0);
		posX = (float)(getWidth() / 2 /*+ m_particleOffsetX*/ - 8);
		level->getParticleLast()->setX(getX() + posX);
		level->getParticleLast()->setLevelX(getLevelX() + posX);
		level->getParticleLast()->setStartX(getStartX() + posX);
		level->getParticleLast()->setVelocityX(level->getParticleLast()->getVelocityX() + m_velocityX + m_movedVelocityX);
		posY = (float)(getHeight() - level->getParticleLast()->getHeight() + level->getParticleLast()->getOffsetY());
		level->getParticleLast()->setY(getY() + posY);
		level->getParticleLast()->setLevelY(getLevelY() + posY);
		level->getParticleLast()->setStartY(getStartY() + posY);
		level->getParticleLast()->update(0.0f);
		//}
		
	}
	setTimerSense(getTimerSense() + time);
	
	if (getTimerSenseClear() > 1.0f && !m_isDead) {
		setTimerSenseClear(0.0f);
		clearSenseAbove();
		clearSenseLeft();
		clearSenseRight();
	}
	setTimerSenseClear(getTimerSenseClear() + time);
	
	
	/*if (m_numHealth <= 0) {
		m_isDead = true;
	}*/
	m_lastTime = time;
	
	/*if (m_aboveObject != nullptr) {
		std::cout << m_aboveObject->getType() << "\n";
	}*/

	/*m_velocityX = 0.1f;
	m_isStatic = false;*/

	m_previousX = m_x;
	m_previousY = m_y;
	m_previousLevelX = m_levelX;
	m_previousLevelY = m_levelY;


	if (m_velocityY >= m_fallVelocity) {
		m_velocityY = m_fallVelocity;
	} else {
		m_velocityY += m_fallAcc;
	}

	if (m_velocityX > -0.2f && m_velocityX < 0.2f) {
		m_velocityX = 0.0f;
	}

	if (m_isCarried && m_carrier != nullptr) {
		if (m_leftObject != nullptr) {
			std::cout << m_leftObject->getType() << "\n";
		}
		m_x = m_carrier->getMiddleX() - m_width / 2;
		m_y = m_carrier->getTop() - m_height;
		m_startX = m_carrier->getLevelX() + m_carrier->getWidth() * 0.5f - m_width * 0.5f;
		m_startY = m_carrier->getLevelY() + m_carrier->getHeight() - m_height;
		m_velocityX = m_carrier->getVelocityX();
		m_velocityY = m_carrier->getVelocityY();
	} else {
		m_x += (m_velocityX + m_movedVelocityX);
		m_y += (m_velocityY + m_movedVelocityY);
		/*m_startX = m_oldStartX;
		m_startY = m_oldStartY;
		if (m_attachedLevel != nullptr) {
			m_x = -m_attachedLevel->getX() + m_startX;
			m_y = -m_attachedLevel->getY() + m_startY;
		}*/
	}


	if (m_attachedLevel != nullptr) {
		m_levelX = m_startX + (m_x - m_startX) + m_attachedLevel->getX();
		m_levelY = m_startY + (m_y - m_startY) + m_attachedLevel->getY();

		//m_x = m_levelX - m_attachedLevel->getX();
		//m_y = m_levelX - m_attachedLevel->getY();
		//std::cout << "cEntityBrick::update " << m_attachedLevel->getX() << " " << m_attachedLevel->getY() << "\n";
		//std::cout << (int)m_levelX << "  " << (int)m_levelY << "  " << m_attachedLevel->getX() << "\n";
	}

	if (m_state != nullptr) {
		m_state->update(app, this, time);
	}

	if (m_isDead) {
		m_timeBeingDead += time;
	} else {
		m_timeBeingAlive += time;
	}

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

	if (m_isDead) {
		m_isCarried = false;
		m_carrier = nullptr;
		m_startX = m_oldStartX;
		m_startY = m_oldStartY;
		

		/*if (m_attachedLevel != nullptr) {
			
		}*/
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
		setAnimTime(getAnimTime() + getAnimSpeed()/* * time*/);
	}

	if (getTileOffsetX() >= (getWidth() * getNumAnimFrames()) - getWidth()) {
		setTileOffsetX((float)(getWidth() * getNumAnimFrames() - getWidth()));
	}
}