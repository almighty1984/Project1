#include "EntityGrevert.h"
#include "EntityGrevertIdleState.h"
#include "RenderingManager.h"

#include "ParticleBrick.h"
#include "ParticleHealth.h"

cEntityGrevert::cEntityGrevert() : m_secondCall(false) {
	m_type = "e_grevert";

	m_width = 32;
	m_height = 32;

	m_velocityX = 0.0f;
	m_velocityY = 0.0f;

	m_state = new cEntityGrevertIdleState;

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

cEntityGrevert::~cEntityGrevert() {
	/*for (auto it = m_particles.begin(); it != m_particles.end(); ++it) {
		cRenderingManager::removeParticle(*it);
		delete* it;
	}
	m_particles.clear();*/

	delete m_state;
	m_state = nullptr;
	//m_isDead = true;
}

void cEntityGrevert::collisionReactionX(cBaseObject *object) {
	if (object->getType().substr(0, 4) == "cam_" ||
		object->getType().substr(0, 5) == "coin_" ||
		object->getType().substr(0, 5) == "door_" ||
		object->getType().substr(0, 11) == "e_bounce_U_" ||
		object->getType().substr(0, 9) == "e_grevert" ||
		object->getType().substr(0, 9) == "e_grodorr" ||
		object->getType().substr(0, 5) == "sign_" ||
		object->getType() == "swing" ||
		object->getType().substr(0, 6) == "level_" ||
		object->getType().substr(0, 5) == "view_" ||
		object->getType().substr(0, 5) == "wall_") {
		return;
	} else if (object->getType() == "e_flugan") {
		return;
	} else if (object->getType() == "e_grevert") {
		return;
	} else if (object->getType() == "e_grodorr") {
		return;
	} else if (object->getType() == "e_pigan") {
		return;
	} else if (object->getType() == "clip" || object->getType().substr(0, 10) == "clip_ledge" || object->getType() == "clip_left" || object->getType() == "clip_right" || object->getType() == "clip_bot") {
		if (m_velocityX < 0.0f) {
			m_x = object->getX() + object->getWidth() - m_subtractLeft;
		}
		if (m_velocityX > 0.0f) {
			m_x = object->getX() - m_width + m_subtractRight;
		}

		//m_velocityX *= -1.0f;
		m_velocityX = 0.0f;
		m_isFacingLeft = !m_isFacingLeft;
		//m_x = m_previousX;

		m_levelX = m_previousLevelX;
	}
}

void cEntityGrevert::collisionReactionY(cBaseObject *object) {
	if (object->getType().substr(0, 4) == "cam_" ||
		object->getType().substr(0, 5) == "coin_" ||
		object->getType().substr(0, 4) == "door" ||
		object->getType().substr(0, 11) == "e_bounce_U_" ||
		object->getType().substr(0, 9) == "e_grevert" ||
		object->getType().substr(0, 9) == "e_grodorr" ||
		object->getType().substr(0, 5) == "sign_" ||
		object->getType() == "swing" ||
		object->getType().substr(0, 7) == "target_" ||
		object->getType().substr(0, 8) == "trigger_" ||
		object->getType().substr(0, 5) == "level" ||
		object->getType().substr(0, 4) == "view" ||
		object->getType().substr(0, 4) == "wall") {
		return;
	} else if (object->getType() == "e_flugan") {
		return;
	} else if (object->getType() == "e_grevert") {
		return;
	} else if (object->getType() == "e_grodorr") {
		return;
	} else if (object->getType() == "e_pigan") {
		return;
	} else if (object->getType() == "player") {
		return;
	} else if (object->getType() == "clip_drop") {
		if (m_velocityY >= 0.0f) {
			m_isOnGround = true;
			m_y = object->getY() - m_height + m_subtractDown;
			if (m_isIdle) {
				hitGround(object);
			}
		} else {
			return;
		}
	} else {
		if (m_velocityY >= 0.0f) {
			m_y = object->getY() - m_height + m_subtractDown;
			if (m_isIdle) {
				hitGround(object);
			}			
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

void cEntityGrevert::die(cBaseObject* killer) {
	//m_isDead = true;
	setVelocityY(0.0f);
	if (m_attachedLevel == nullptr) {
		return;
	}

	float posX = getLevelX() + getWidth() / 2 - 8;
	float posY = getLevelY() + getHeight() / 2 - 16;

	float velX = 0.0f;

	cLevel* level = m_attachedLevel;
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
		level->getParticleLast()->setY(getY() + getHeight() / 2 + 0.0f);
		level->getParticleLast()->setStartX(posX);
		level->getParticleLast()->setStartY(posY);
		level->getParticleLast()->setLevelX(posX);
		level->getParticleLast()->setLevelY(posY);
		level->getParticleLast()->setVelocityX(0.0f);
		level->getParticleLast()->setVelocityY(0.0f);
	}
}

void cEntityGrevert::hitGround(cBaseObject* object) {
	if (m_attachedLevel == nullptr || object == nullptr || this == nullptr) {
		return;
	}
	
	//std::cout << "cEntityGrevert::hitGround " << object->getType() << " " << "\n";

	if (m_isIdle && (int)(m_timeBeingIdle) % 4 != 0) {
		return;
	}

	cLevel* level = m_attachedLevel;

	float offsetY = -16.0f;	

	level->addParticle(new cParticle);		
	level->getParticleLast()->loadConfig("Data\\Particles\\p_dust_grass.cfg");
	if (object->getType() == "slope_L_2x1_0" || object->getType() == "slope_L_2x1_1") {
		level->getParticleLast()->setOrigin(8.0f, 8.0f);
		level->getParticleLast()->setRotation(-26.565f);
		level->getParticleLast()->setX(m_x + m_width / 2 - 4);
		level->getParticleLast()->setY(m_y + m_height / 2 + 28 + offsetY);
	} else if (object->getType() == "slope_R_2x1_0" || object->getType() == "slope_R_2x1_1") {
		level->getParticleLast()->setOrigin(8.0f, 8.0f);
		level->getParticleLast()->setRotation(26.565f);
		level->getParticleLast()->setX(m_x + m_width / 2 + 4);
		level->getParticleLast()->setY(m_y + m_height / 2 + 28 + offsetY);
	} else if (object->getType() == "slope_L_1x1") {
		level->getParticleLast()->setOrigin(8.0f, 8.0f);
		level->getParticleLast()->setRotation(-45.0f);
		level->getParticleLast()->setX(m_x + m_width / 2);
		level->getParticleLast()->setY(m_y + m_height / 2 + 24 + offsetY);
	} else if (object->getType() == "slope_R_1x1") {
		level->getParticleLast()->setOrigin(8.0f, 8.0f);
		level->getParticleLast()->setRotation(45.0f);
		level->getParticleLast()->setX(m_x + m_width / 2);
		level->getParticleLast()->setY(m_y + m_height / 2 + 24 + offsetY);
	} else {
		level->getParticleLast()->setIsHidden(true);
		level->getParticleLast()->setX(m_x + m_width / 2 - 8);
		level->getParticleLast()->setY(m_y + m_height / 2 + 16 + offsetY);
	}
	

	level->getParticleLast()->setStartX(object->getStartX());
	level->getParticleLast()->setStartY(object->getStartY() - 16 + offsetY);
	level->getParticleLast()->setIsHidden(false);
	level->getParticleLast()->setTileOffsetX(0.0f);

	/*if (m_velocityY < 0.0f) {
		level->getParticleLast()->setIsUpsideDown(true);
		level->getParticleLast()->setY(object->getBottom()+level->getParticleLast()->getHeight());
		level->getParticleLast()->setLevelY(object->getLevelY() + object->getHeight());
	} else {
		m_isOnGround = true;
	}*/
	//level->getParticleLast()->update(0.0f);

	//m_isOnGround = true;
	//m_velocityY = 0.0f;
}

void cEntityGrevert::update(cApp *app, float time) {
	if (m_attachedLevel == nullptr) {
		return;
	}
	if (m_isLocked) {
		//std::cout << "EntityGrevert locked!" << "\n" << "\n" << "\n";
		m_velocityX = 0.0f;
		m_velocityY = 0.0f;
		m_tileOffsetX = 0.0f;
		m_tileOffsetY = 0.0f;
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

	// Regenerate health
	if (m_numHealth > 0.0f) {
		if (m_numHealth < m_startHealth) {
			m_numHealth += 0.05f;
		}
		else if (m_numHealth > m_startHealth) {
			m_numHealth = m_startHealth;
		}
	}
	// Hide health bar at full health
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

	/*if (m_velocityY < 0.0f) {
		m_isOnGround = false;
	}*/
	/*for (unsigned short i = 0; i < m_particles.size(); ++i) {
		m_particles.at(i)->update(time);

		if (m_particles.at(i)->getIsDead()) {
			cRenderingManager::removeParticle(m_particles.at(i));
			m_particles.erase(m_particles.begin() + i, m_particles.begin() + i + 1);
		}
	}*/


	m_previousX = m_x;
	m_previousY = m_y;
	m_previousLevelX = m_levelX;
	m_previousLevelY = m_levelY;

	m_x += m_velocityX;
	m_y += m_velocityY;

	if (m_attachedLevel != nullptr) {
		m_levelX = m_startX + (m_x - m_startX) + m_attachedLevel->getX();
		m_levelY = m_startY + (m_y - m_startY) + m_attachedLevel->getY();

		//std::cout << (int)m_levelX << "  " << (int)m_levelY << "  " << m_attachedLevel->getX() << "\n";
	}


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
	}
	else {
		m_isHurting = false;
		m_hurtAgainDelayValue = 0.0f;
		m_doUseShader = false;
		//std::cout << m_hurtAgainDelayValue << "\n";
	}
}