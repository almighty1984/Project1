#include "EntityGrass.h"
#include "RenderingManager.h"
#include "SoundsManager.h"

cEntityGrass::cEntityGrass() : m_isSwayingLeft(false) {
	m_type = "e_grass";

	m_velocityX = 0.0f;
	m_velocityY = 0.0f;

	setAnim(eAnimTag::idle);
	//m_state = new cEntityGrassIdleState;

}

cEntityGrass::~cEntityGrass() {
	/*for (std::vector<cParticle*>::const_iterator itr = m_particles.begin(); itr != m_particles.end(); ++itr) {
		cRenderingManager::removeParticle(*itr);
		delete* itr;
	}
	m_particles.clear();*/

	/*delete m_state;
	m_state = nullptr;*/
	//m_isDead = true;
}


void cEntityGrass::update(cApp* app, float time) {
	if (m_isLocked) {
		m_velocityX = 0.0f;
		m_velocityY = 0.0f;
		m_tileOffsetX = 0.0f;
		m_tileOffsetY = 0.0f;
	}

	if (getTimerSense() > (app->getWeatherColor() / 29.0f) && m_attachedLevel != nullptr && !m_isDead && m_isIdle) {
		setTimerSense(0.0f);		
		if (m_tileOffsetX <= 0.0f) {
			m_tileOffsetX = 32.0f;
			//m_isFacingLeft = !m_isFacingLeft;
			m_isSwayingLeft = !m_isSwayingLeft;
		} else if (m_tileOffsetX > 0.0f && m_tileOffsetX <= 48.0f) {
			if (m_isSwayingLeft) {
				m_tileOffsetX = 0.0f;
			} else {
				m_tileOffsetX = 64.0f;
			}			
		} else if (m_tileOffsetX > 48.0f && m_tileOffsetX <= 80.0f) {
			if (m_isSwayingLeft) {
				m_tileOffsetX = 32.0f;
			} else {
				m_tileOffsetX = 96.0f;
			}
		} else if (m_tileOffsetX >= 96.0f) {
			m_tileOffsetX = 64.0f;
			m_isSwayingLeft = !m_isSwayingLeft;
		}
	}

	m_isIdle = true;	

	setTimerSense(getTimerSense() + (time * (rand() % 4)) );
	
	m_lastTime = time;

	m_previousX = m_x;
	m_previousY = m_y;
	m_previousLevelX = m_levelX;
	m_previousLevelY = m_levelY;

	m_x += (m_velocityX + m_movedVelocityX);
	m_y += (m_velocityY + m_movedVelocityY);

	if (m_attachedLevel != nullptr) {
		m_levelX = m_startX + (m_x - m_startX) + m_attachedLevel->getX();
		m_levelY = m_startY + (m_y - m_startY) + m_attachedLevel->getY();
	}

	/*if (m_state != nullptr) {
		m_state->update(app, this, time);
	}*/

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