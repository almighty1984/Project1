#include "Player.h"

void cPlayer::collisionReactionSlopeY(cBaseObject* object) {
	/*if (!getIsPressingLeft() && !getIsPressingRight()) {
		m_velocityX *= m_moveDec;
		
	}*/
	m_isInSlope = true;
	
	m_isHovering = false;
	//m_lockHover = true;
	//m_lockJump = false;
	m_isPressingDownThrust = false;
	//m_isDownThrusting = false;
	m_movedVelocityX = 0.0f;
	m_movedVelocityY = 0.0f;

	if (object->getType().substr(0, 8) == "slope_L_") {
		if (m_velocityY < 0.0f) { return; };
		if (object->getType() == "slope_L_seam") {
			m_y = object->getY() + 16 - m_slopeOffsetX - m_height + m_subtractDown - 8 - 1;
			
			if (m_isFacingLeft && m_isSlopeSliding && !m_isDownThrusting) {
				m_velocityY = m_fallVelocity * 1.5f;
				m_downThrustCooldownValue = 0;
				setVelocityFromSlope(16.0f, 16.0f);
				return;
			}
			
			if (m_isInWater) {
				m_velocityX = -m_moveVelocity * 0.71f;
				m_velocityY = -m_velocityX;
				//setVelocityFromSlope(16.0f, 16.0f);
				//return;
			}
			hitGround(object);
			m_velocityY = 0.0f;
			m_isOnGround = true;
			if (getIsPressingSprint()) {
				if (m_velocityX > m_moveVelocity * 0.3f * m_sprintValue) {
					m_velocityX = m_moveVelocity * 0.3f * m_sprintValue;					
				}
			} else {
				if (m_velocityX > m_moveVelocity * 0.3f) {
					m_velocityX = m_moveVelocity * 0.3f;					
				}
			}
		} else if (object->getType() == "slope_L_1x1") {
			m_y = object->getY() + 16 - m_slopeOffsetX - m_height + m_subtractDown - 1;
			
			if (m_isFacingLeft && m_isSlopeSliding && !m_isDownThrusting) {
				m_velocityY = m_fallVelocity * 1.5f;
				m_downThrustCooldownValue = 0;
				setVelocityFromSlope(16.0f, 16.0f);
				return;
			}
			
			if (m_isInWater) {
				m_velocityX = -m_moveVelocity * 0.71f;
				m_velocityY = -m_velocityX;
				//setVelocityFromSlope(16.0f, 16.0f);
				return;
			}
			hitGround(object);
			m_velocityY = 0.0f;
			m_isOnGround = true;
			if (getIsPressingSprint()) {
				if (m_velocityX > m_moveVelocity * 0.3f * m_sprintValue) {
					m_velocityX = m_moveVelocity * 0.3f * m_sprintValue;
					//m_hasJumped = true;
				}
			} else {
				if (m_velocityX > m_moveVelocity * 0.3f) {
					m_velocityX = m_moveVelocity * 0.3f;
					//m_hasJumped = true;
				}
			}
		} else if (object->getType() == "slope_L_2x1_0") {
			m_y = object->getY() + 16 - m_slopeOffsetX * 0.5f - m_height + m_subtractDown - 1;

			if (m_isFacingLeft && m_isSlopeSliding && !m_isDownThrusting) {
				m_velocityY = m_fallVelocity * 1.0f;

				m_downThrustCooldownValue = 0;
				setVelocityFromSlope(32.0f, 16.0f);
				m_isSlopeSliding = true;
				return;
			}

			if (m_isInWater) {
				m_velocityY = m_velocityX * 0.5f;
				m_velocityX = m_moveVelocity;
				//setVelocityFromSlope(-32.0f, 16.0f);
				return;
			}

			hitGround(object);
			m_velocityY = 0.0f;
			m_isOnGround = true;

			float moveVelocity = m_moveVelocity;
			float sprintValue = 1.0f;
			if (getIsPressingSprint()) {
				sprintValue = m_sprintValue;
			}
			if (m_velocityX > 0.0f) {			// Running against the slope
				moveVelocity *= 0.6f;
				if (m_velocityX > moveVelocity * sprintValue) {
					m_velocityX = moveVelocity * sprintValue;
				}
			} else {
				if (m_velocityX < -moveVelocity * sprintValue) {
					m_velocityX = -moveVelocity * sprintValue;
				}
			}
			if (getIsPressingLeft() || getIsPressingRight()) {
				if (m_velocityX < 0.0f) {
					m_velocityY = -m_velocityX * 0.5f * sprintValue;
				}
			} else {
				if (m_velocityX < 0.0f) {
					m_velocityX += m_moveDec;
				} else if (m_velocityX > 0.0f) {
					m_velocityX -= m_moveDec;
				}
			}



		} else if (object->getType() == "slope_L_2x1_1") {
			m_y = object->getY() + 8 - m_slopeOffsetX * 0.5f - m_height + m_subtractDown - 1;

			if (m_isFacingLeft && m_isSlopeSliding && !m_isDownThrusting) {
				m_velocityY = m_fallVelocity * 1.0f;

				m_downThrustCooldownValue = 0;
				setVelocityFromSlope(32.0f, 16.0f);
				m_isSlopeSliding = true;
				return;
			}
			if (m_isInWater) {
				m_velocityY = m_velocityX * 0.5f;
				m_velocityX = m_moveVelocity;
				//setVelocityFromSlope(-32.0f, 16.0f);
				return;
			}

			hitGround(object);
			m_velocityY = 0.0f;
			m_isOnGround = true;

			float moveVelocity = m_moveVelocity;
			float sprintValue = 1.0f;
			if (getIsPressingSprint()) {
				sprintValue = m_sprintValue;
			}
			if (m_velocityX > 0.0f) {			// Running against the slope
				moveVelocity *= 0.6f;
				if (m_velocityX > moveVelocity * sprintValue) {
					m_velocityX = moveVelocity * sprintValue;
				}
			} else {
				if (m_velocityX < -moveVelocity * sprintValue) {
					m_velocityX = -moveVelocity * sprintValue;
				}
			}
			if (getIsPressingLeft() || getIsPressingRight()) {
				if (m_velocityX < 0.0f) {
					m_velocityY = -m_velocityX * 0.5f * sprintValue;
				}
			} else {
				if (m_velocityX < 0.0f) {
					m_velocityX += m_moveDec;
				} else if (m_velocityX > 0.0f) {
					m_velocityX -= m_moveDec;
				}
			}
		}
	} else if (object->getType().substr(0, 8) == "slope_R_") {
		if (m_velocityY < 0.0f) { return; };
		if (object->getType() == "slope_R_seam") {
			m_y = object->getY() - m_height + m_slopeOffsetX + m_subtractDown - 8 - 1;
			/*if (!m_isSlopeSliding) {
				m_velocityY = 0.0f;
			}*/
			if (!m_isFacingLeft && m_isSlopeSliding && !m_isDownThrusting) {
				//m_isFacingLeft = false;
				//m_y -= 1.0f;				
				m_downThrustCooldownValue = 0.0f;
				//m_velocityY = m_velocityX;
				setVelocityFromSlope(-16.0f, 16.0f);
				m_isSlopeSliding = true;
				return;
			}
			
			if (m_isInWater) {
				//m_velocityY = m_velocityX;
				m_velocityX = m_moveVelocity * 0.71f;
				m_velocityY = m_velocityX;
				//setVelocityFromSlope(-16.0f, 16.0f);
				return;
			}
			
			hitGround(object);
			m_velocityY = 0.0f;
			m_isOnGround = true;

			float moveVelocity = m_moveVelocity;
			float sprintValue = 1.0f;
			if (getIsPressingSprint()) {
				sprintValue = m_sprintValue;
			}
			if (m_velocityX < 0.0f) {			// Running against the slope
				moveVelocity *= 0.3f;
				if (m_velocityX < -moveVelocity * sprintValue) {
					m_velocityX = -moveVelocity * sprintValue;
				}
			} else {
				if (m_velocityX > moveVelocity * sprintValue) {
					m_velocityX = moveVelocity * sprintValue;
				}
			}
			if (getIsPressingLeft() || getIsPressingRight()) {
				if (m_velocityX > 0.0f) {
					m_velocityY = m_velocityX * 0.5f * sprintValue;
				}
			} else {
				if (m_velocityX < 0.0f) {
					m_velocityX += m_moveDec;
				} else if (m_velocityX > 0.0f) {
					m_velocityX -= m_moveDec;
				}
			}
		} else if (object->getType() == "slope_R_1x1") {
			m_y = object->getY() + m_slopeOffsetX - m_height + m_subtractDown - 1;
			
			if (!m_isFacingLeft && m_isSlopeSliding && !m_isDownThrusting) {				
				//m_velocityY = m_fallVelocity * 3.0f;
				m_downThrustCooldownValue = 0;
				setVelocityFromSlope(-16.0f, 16.0f);
				return;
			}
			if (m_isInWater) {
				//m_velocityY = m_velocityX;
				m_velocityX = m_moveVelocity*0.71f;
				m_velocityY = m_velocityX;	
				//setVelocityFromSlope(-16.0f, 16.0f);
				return;
			}
			
			hitGround(object);
			m_velocityY = 0.0f;
			m_isOnGround = true;

			float moveVelocity = m_moveVelocity;
			float sprintValue = 1.0f;
			if (getIsPressingSprint()) {
				sprintValue = m_sprintValue;
			}
			if (m_velocityX < 0.0f) {	// Running against the slope
				moveVelocity *= 0.3f;
				if (m_velocityX < -moveVelocity * sprintValue) {
					m_velocityX = -moveVelocity * sprintValue;
				}
			} else {
				if (m_velocityX > moveVelocity * sprintValue) {
					m_velocityX = moveVelocity * sprintValue;
				}
			}
			if (getIsPressingLeft() || getIsPressingRight()) {
				if (m_velocityX > 0.0f) {
					m_velocityY = m_velocityX * 0.5f * sprintValue;
				}
			} else {
				if (m_velocityX < 0.0f) {
					m_velocityX += m_moveDec;
				} else if (m_velocityX > 0.0f) {
					m_velocityX -= m_moveDec;
				}
			}
		} else if (object->getType() == "slope_R_2x1_0") {
			m_y = object->getY() + m_slopeOffsetX * 0.5f - m_height + m_subtractDown - 0;
			
			if (!m_isFacingLeft && m_isSlopeSliding && !m_isDownThrusting) {
				//m_velocityY = m_fallVelocity * 2.0f;
				
				m_downThrustCooldownValue = 0;
				setVelocityFromSlope(-32.0f, 16.0f);
				m_isSlopeSliding = true;
				return;
			}
			if (m_isInWater) {
				m_velocityY = m_velocityX * 0.5f;
				m_velocityX = m_moveVelocity;
				//setVelocityFromSlope(-32.0f, 16.0f);
				return;
			}

			hitGround(object);
			m_velocityY = 0.0f;
			m_isOnGround = true;

			float moveVelocity = m_moveVelocity;
			float sprintValue = 1.0f;
			if (getIsPressingSprint()) {
				sprintValue = m_sprintValue;
			}
			if (m_velocityX < 0.0f) {	// Running against the slope
				moveVelocity *= 0.6f;
				if (m_velocityX < -moveVelocity * sprintValue) {
					m_velocityX = -moveVelocity * sprintValue;
				}
			} else {					// Running with the slope
				if (m_velocityX > moveVelocity * sprintValue) {
					m_velocityX = moveVelocity * sprintValue;
				}
			}
			if (getIsPressingLeft() || getIsPressingRight()) {
				if (m_velocityX > 0.0f) {
					m_velocityY = m_velocityX * 0.5f * sprintValue;
				}
			} else {
				if (m_velocityX < 0.0f) {
					m_velocityX += m_moveDec;
				} else if (m_velocityX > 0.0f) {
					m_velocityX -= m_moveDec;
				}
			}
		} else if (object->getType() == "slope_R_2x1_1") {
			m_y = object->getY() + 8 + m_slopeOffsetX * 0.5f - m_height + m_subtractDown - 0;
			
			if (!m_isFacingLeft && m_isSlopeSliding && !m_isDownThrusting) {
				//m_velocityY = m_fallVelocity * 2.0f;
				
				m_downThrustCooldownValue = 0;
				setVelocityFromSlope(-32.0f, 16.0f);
				m_isSlopeSliding = true;
				return;
			}
			
			if (m_isInWater) {
				m_velocityY = m_velocityX * 0.5f;
				m_velocityX = m_moveVelocity;
				//setVelocityFromSlope(-32.0f, 16.0f);
				return;
			}

			hitGround(object);
			m_velocityY = 0.0f;
			m_isOnGround = true;

			float moveVelocity = m_moveVelocity;
			float sprintValue = 1.0f;
			if (getIsPressingSprint()) {
				sprintValue = m_sprintValue;
			}
			if (m_velocityX < 0.0f) {	// Running against the slope
				moveVelocity *= 0.6f;
				if (m_velocityX < -moveVelocity * sprintValue) {
					m_velocityX = -moveVelocity * sprintValue;
				}
			} else {					// Running with the slope
				if (m_velocityX > moveVelocity * sprintValue) {
					m_velocityX = moveVelocity * sprintValue;
				}
			}
			if (getIsPressingLeft() || getIsPressingRight()) {
				if (m_velocityX > 0.0f) {
					m_velocityY = m_velocityX * 0.5f * sprintValue;
				}
			} else {
				if (m_velocityX < 0.0f) {
					m_velocityX += m_moveDec;
				} else if (m_velocityX > 0.0f) {
					m_velocityX -= m_moveDec;
				}
			}
		}
	} else if (object->getType() == "slope_LU_1x1") {
		if (m_velocityY > 0.0f) { return; };
		m_y = object->getY() + m_slopeOffsetX - m_subtractUp + 1;
		if (m_velocityX > 0.0f) {
			m_velocityY *= -1.0f;
		} else {
			m_velocityX = -abs(m_velocityY);
		}
	} else if (object->getType() == "slope_RU_1x1") {
		if (m_velocityY > 0.0f) { return; };
		m_y = object->getY() + 16 - m_slopeOffsetX - m_subtractUp + 1;
		if (m_velocityX < 0.0f) {
			m_velocityY *= -1.0f;
		} else {
			m_velocityX = abs(m_velocityY);
		}	
	} else if (object->getType() == "slope_LU_2x1_0") {
		if (m_velocityY > 0.0f) { return; };
		if (m_velocityX > 0.0f) {
			m_velocityY *= -1.0f;
		} else {
			m_velocityX = -abs(m_velocityY) * 1.0f;
		}
		//m_x = object->getLeft() + m_slopeOffsetX - m_width + m_subtractRight + 8;
		m_y = object->getY() + m_slopeOffsetX * 0.5f - m_subtractUp + 1;
	} else if (object->getType() == "slope_LU_2x1_1") {
		if (m_velocityY > 0.0f) { return; };
		if (m_velocityX > 0.0f) {
			m_velocityY *= -1.0f;
		} else {
			m_velocityX = -abs(m_velocityY) * 1.0f;
		}
		//m_x = object->getLeft() + m_slopeOffsetX - m_width + m_subtractRight + 8;
		m_y = object->getY() + 8 + m_slopeOffsetX * 0.5f - m_subtractUp + 1;
	} else if (object->getType() == "slope_RU_2x1_0") {
		if (m_velocityY > 0.0f) { return; };
		if (m_velocityX < 0.0f) {
			m_velocityY *= -1.0f;
		} else {
			m_velocityX = abs(m_velocityY) *1.0f;
		}
		//m_x = object->getRight() - m_slopeOffsetX - m_subtractLeft - 8;
		m_y = object->getBottom() - m_slopeOffsetX * 0.5f - m_subtractUp + 1;
	} else if (object->getType() == "slope_RU_2x1_1") {
		if (m_velocityY > 0.0f) { return; };
		if (m_velocityX < 0.0f) {
			m_velocityY *= -1.0f;
		} else {
			m_velocityX = -m_velocityY * 1.0f;
		}
		//m_x = object->getRight() - m_slopeOffsetX - m_subtractLeft - 8;
		m_y = object->getBottom() - 8 - m_slopeOffsetX * 0.5f - m_subtractUp + 1;
	}
	/*else if (object->getType() == "slope_top") {
		if(m_velocityY > 0.0f) {
			m_y = object->getY()-m_height+m_subtractDown;
		}
		else {
			m_y = m_previousY;
		}

		m_velocityY = 0.0f;
	}*/

	m_isOnGround = true;

	m_hasJumped = false;
}