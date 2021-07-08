#include "EntityTrain.h"
#include "EntityTrainIdleState.h"
#include "RenderingManager.h"

cEntityTrain::cEntityTrain() : m_secondCall(false) {
	m_type = "e_train";

	m_width = 64;
	m_height = 64;

	m_velocityX = 0.0f;
	m_velocityY = 0.0f;

	i = 0;
	m_nextObject = 0;

	m_state = new cEntityTrainIdleState;

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

cEntityTrain::~cEntityTrain() {
	delete m_state;
	m_state = nullptr;
	//m_isDead = true;
}


void cEntityTrain::update(cApp *app, float time) {
	if (!m_secondCall) {
		m_secondCall = true;
		i = 0;
		m_nextObject = getPathNumber(0);
		/*for (int i = 0; i < app->m_trainNumbers[m_number].size(); ++i) {
			addPathNumber(app->m_trainNumbers[m_number].at(i));
		}*/
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
	m_meterHealthBackground.setX(m_x + m_width / 2 - m_meterHealthBackground.getWidth() / 2);
	m_meterHealthBackground.setY(m_y + 16);
	m_meterHealthBackground.setWidth((int)m_startHealth);
	m_meterHealthBackground.update(time);

	m_meterHealth.setX(m_x + m_width / 2 - m_meterHealthBackground.getWidth() / 2);
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
		//std::cout << (int)m_levelX << "  " << (int)m_levelY << "  " << m_attachedLevel->getX() << "\n";
	}


	/*if (m_velocityX > 0.0f) {
		m_isFacingLeft = false;
	} else if (m_velocityX < 0.0f) {
		m_isFacingLeft = true;
	}
*/
	if (m_isLocked) {
		m_velocityX = 0.0f;
		m_velocityY = 0.0f;
	}
	else {
		if (m_state != nullptr) {
			m_state->update(app, this, time);
		}
	}
}