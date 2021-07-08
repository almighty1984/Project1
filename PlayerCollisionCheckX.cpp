#include "Player.h"

bool cPlayer::collisionCheckX(cBaseObject* object) {
	if (object == nullptr || m_isDead) {
		return false;
	}
	if (object->getIsSlope()) {
		return collisionCheckSlopeX(object);
	}

	char offsetY = 0;
	char waterOffset = 0;

	if (m_isInWater) {
		waterOffset = 4;
	}

	m_slopeOffsetX = 0.0f;
	float left = getLeft() /*- waterOffset*/;
	float right = getRight() /* + waterOffset*/;
	float bottom = getBottom() - 4 + waterOffset;
	float top = getTop() + 4 + waterOffset;

	if (m_isCrawling) {
		top += 2;
	}

	if (m_velocityX + m_movedVelocityX < 0.0f/* && !m_isRiding*//* || (m_isRiding && m_belowObject != nullptr && m_belowObject->getVelocityX() < 0.0f)*/) {
		if (left < object->getRight() && /*left + 4*/getMiddleX() > object->getRight()) {
			if (top < object->getBottom() && bottom > object->getTop()) {
				return true;
			}
		}
	} else if (m_velocityX + m_movedVelocityX > 0.0f/* && !m_isRiding*//* || (m_isRiding && m_belowObject != nullptr && m_belowObject->getVelocityX() > 0.0f)*/) {
		if (right > object->getLeft() && /*right - 4*/getMiddleX() < object->getLeft()) {
			if (top < object->getBottom() && bottom > object->getTop()) {
				return true;
			}
		}
	}
	return false;
}