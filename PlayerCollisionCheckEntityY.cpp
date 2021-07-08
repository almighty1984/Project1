#include "Player.h"
#include "Entity.h"

bool cPlayer::collisionCheckEntityY(cEntity* entity) {
	if (entity == nullptr) {
		return false;
	}
	if (entity->getIsDead() || m_isDead) {
		return false;
	}

	/*if (m_isCarrying && entity->getCarrier() != nullptr && this == entity->getCarrier()) {
		return;
	}*/

	if (m_isThrowing && m_thrownObject == entity) {
		return false;
	}

	/*if (getTop() + 10 < entity->getBottom() && getBottom() + 1 > entity->getTop()) {
		if (getLeft() + 4 <= entity->getRight() && getRight() - 4 >= entity->getLeft()) {
			collisionReactionEntityY(entity);
		}
	}*/

	if (/*getLeft() > entity->getLeft() + 2 && getLeft() < entity->getRight() - 2
		||
		getRight() > entity->getLeft() + 2 && getRight() < entity->getRight() - 2
		||*/
		getMiddleX() + 4 > entity->getLeft() + 0 && getMiddleX() - 4 < entity->getRight() - 0) {
		// Moving up or entity moving down
		if (m_velocityY + m_movedVelocityY < 0.0f || entity->getVelocityY() + entity->getMovedVelocityY() > 0.0f) {
			if (getTop() < entity->getBottom() && getBottom() > entity->getTop()) {				
				return true;
			}
		}
		// Moving down or entity moving up
		if (m_velocityY + m_movedVelocityY > 0.0f || entity->getVelocityY() + entity->getMovedVelocityY() < 0.0f) {
			if (getBottom() + 1 > entity->getTop() && getTop() < entity->getBottom()) {				
				return true;
			}
		}
	}
	//if (getLeft() > entity->getLeft()+2 && getLeft() < entity->getRight()-2
	//	||
	//	getRight() > entity->getLeft()+2 && getRight() < entity->getRight()-2
	//	||
	//	getMiddleX() > entity->getLeft()+2 && getMiddleX() < entity->getRight()-2) {

	//	if (getTop()+0 < entity->getBottom() && getBottom() > entity->getTop()) {
	//		//std::cout << "collisionReactionEntityY above\n";
	//		collisionReactionEntityY(entity);
	//		entity->collisionReactionY(this);
	//	}
	//	//// Is the object below?
	//	//if (getTop() < entity->getTop() && getTop() < entity->getBottom()/* && m_velocityY >= 0.0f*/) {
	//	//		//if ((!m_hasJumped || m_isHovering)/* && m_velocityY > m_fallAcc*/) {
	//	//		//std::cout << "collisionReactionEntityY below\n";
	//	//			collisionReactionEntityY(entity);
	//	//			entity->collisionReactionY(this);
	//	//		//}
	//	//	}
	//	//}
	//}
	return false;
}