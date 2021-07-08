#include "EntityBall.h"
//#include "InputManager.h"
#include "SoundBufferManager.h"
#include "RenderingManager.h"
#include "SoundsManager.h"

#include "Particle.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream> 

cEntityBall::cEntityBall() {
	//m_animCurrent = m_animIdle;
	m_spriteOffsetX = 16.0f;
	m_spriteOffsetY = 16.0f;
	setOrigin(16.0f, 16.0f);
	
	m_velocityX = 0.0f;
	m_velocityY = 0.0f;

	//m_state = new cEntityBallIdleState;
}

cEntityBall::~cEntityBall() {
	/*for (std::vector<cParticle*>::const_iterator itr = m_particles.begin(); itr != m_particles.end(); ++itr) {
		cRenderingManager::removeParticle(*itr);
		delete *itr;
	}
	m_particles.clear();*/
}

void cEntityBall::update(cApp *app, float time) {
	if (m_isLocked) {
		return;
	}
	
	//std::cout << m_isInSlope << "\n";

	if (m_isInSlope) {
		
	}

	setAnim(eAnimTag::idle);
	
	m_isFacingLeft = false;
	m_previousX = m_x;
	m_previousY = m_y;
	m_previousLevelX = m_levelX;
	m_previousLevelY = m_levelY;

	m_x += m_velocityX;
	m_y += m_velocityY;
	/*m_levelX += m_velocityX;
	m_levelY += m_velocityY;*/

	if (m_attachedLevel != nullptr) {
		m_levelX = m_startX + (m_x - m_startX) + m_attachedLevel->getX();
		m_levelY = m_startY + (m_y - m_startY) + m_attachedLevel->getY();

		//std::cout << (int)m_levelX << "  " << (int)m_levelY << "  " << m_attachedLevel->getX() << "\n";
	}
	/*if (m_state != nullptr) {
		m_state->update(app, this, time);
	}*/

	// Deceleration when we are on ground
	if (m_velocityY >= 0.0f && m_velocityY <= m_fallAcc && !m_isInSlope) {
		if (m_velocityX > 0.0f) {
			m_velocityX -= m_moveDec;
		}
		if (m_velocityX < 0.0f) {
			m_velocityX += m_moveDec;
		}
	}

	if (m_velocityX >= m_moveVelocity) {
		m_velocityX = m_moveVelocity;
	}
	else if (m_velocityX <= -m_moveVelocity) {
		m_velocityX = -m_moveVelocity;
	}

	if (m_velocityY >= m_fallVelocity) {
		m_velocityY = m_fallVelocity;
	}
	else {
		m_velocityY = m_velocityY + m_fallAcc;
	}

	rotate(m_velocityX*10.0f);
	
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

	/*m_sprite.setPosition(m_x + m_spriteOffsetX+32, m_y + m_spriteOffsetY);
	m_sprite.setTextureRect((int)m_tileOffsetX, (int)m_tileOffsetY, m_width, m_height);*/
}