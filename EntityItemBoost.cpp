#include "EntityItemBoost.h"
//#include "InputManager.h"
#include "SoundBufferManager.h"
#include "RenderingManager.h"
#include "SoundsManager.h"

#include "EntityItemBoostIdleState.h"
#include "Particle.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream> 

cEntityItemBoost::cEntityItemBoost() {
	//m_animCurrent = m_animIdle;


	m_state = new cEntityItemBoostIdleState;
}

cEntityItemBoost::~cEntityItemBoost() {
	/*for (std::vector<cParticle*>::const_iterator itr = m_particles.begin(); itr != m_particles.end(); ++itr) {
		cRenderingManager::removeParticle(*itr);
		delete *itr;
	}
	m_particles.clear();*/
}

void cEntityItemBoost::update(cApp *app, float time) {
	m_previousX = m_x;
	m_previousY = m_y;
	m_previousLevelX = m_levelX;
	m_previousLevelY = m_levelY;

	m_x += m_velocityX;
	m_y += m_velocityY;
	m_levelX += m_velocityX;
	m_levelY += m_velocityY;

	if (m_state != nullptr) {
		m_state->update(app, this, time);
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

		if (m_particles.at(i)->getIsDead() == true) {
			cRenderingManager::removeParticle(m_particles.at(i));
			m_particles.erase(m_particles.begin() + i, m_particles.begin() + i + 1);
		}
	}*/
}