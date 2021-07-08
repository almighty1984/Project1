#include "Entity.h"

bool cEntity::collisionCheckX(cBaseObject* object) {
	if (object == nullptr || object->getIsDead() || m_isDead) {
		return false;
	}
	if (object->getIsSlope()) {
		return collisionCheckSlopeX(object);
	}

	char offsetY = 0;
	float left = getLeft();
	float right = getRight();
	float bottom = getBottom() - 4;
	float top = getTop() + 4;

	if (m_velocityX + m_movedVelocityX < 0.0f/* && !m_isRiding*//* || (m_isRiding && m_belowObject != nullptr && m_belowObject->getVelocityX() < 0.0f)*/) {
		if (left < object->getRight() && getMiddleX() > object->getRight()) {
			if (top < object->getBottom() && bottom > object->getTop()) {
				return true;
			}
		}
	} else if (m_velocityX + m_movedVelocityX > 0.0f/* && !m_isRiding*//* || (m_isRiding && m_belowObject != nullptr && m_belowObject->getVelocityX() > 0.0f)*/) {
		if (right > object->getLeft() && getMiddleX() < object->getLeft()) {
			if (top < object->getBottom() && bottom > object->getTop()) {
				return true;
			}
		}
	}
	return false;
}


