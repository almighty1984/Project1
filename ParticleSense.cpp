#include "Object.h"
#include "Entity.h"
#include "EntityGrodorrAttackState.h"
#include "InputManager.h"
#include "SoundsManager.h"
#include "ParticleSense.h"
#include "Player.h"


void cParticleSense::collisionReactionX(cBaseObject *object) {
	/*if (object->getIsDead()) {
		return;
	}*/
	//std::cout << "cParticleSense::collisionReactionX " << object->getType() << "\n";
	
	if (object->getType().substr(0, 3) == "cam" ||
		object->getType() == "clip_top" ||
		object->getType() == "door_0" || object->getType() == "door_exit" ||
		object->getType().substr(0, 11) == "e_item" ||
		object->getType().substr(0, 5) == "level" ||
		object->getType().substr(0, 4) == "view" ||
		object->getType() == "p_open" ||
		object->getType().substr(0, 4) == "path" ||
		object->getType() == "player" ||
		object->getType().substr(0, 5) == "slope" ||
		object->getType().substr(0, 5) == "wall_" ||
		object->getType().substr(0, 5) == "water") {
		return;
	} else if (object->getType() == "clip_ledge_L") {
		if (m_parent == nullptr) { return; }
		if (m_velocityX > 0.0f) {
			m_parent->senseCollidedRight(object);
		}		
	} else if (object->getType() == "clip_ledge_R") {
		if (m_parent == nullptr) { return; }
		if (m_velocityX < 0.0f) {
			m_parent->senseCollidedLeft(object);
		}
	} else if (object->getType() == "clip" || object->getType() == "clip_left" || object->getType() == "clip_right" || object->getType() == "e_brick") {
		if (m_parent == nullptr) { return; }
		//m_doRemove = true;
		/*if (object->getMiddleX() < m_parent->getMiddleX()) {
			m_parent->setLeftObject(object);
		}
		else if (object->getMiddleX() > m_parent->getMiddleX()) {
			m_parent->setRightObject(object);
		}*/
		//m_parent->senseCollided(object);
		if (m_velocityX < 0.0f) {
			m_parent->senseCollidedLeft(object);
		} else if (m_velocityX > 0.0f) {
			m_parent->senseCollidedRight(object);
		}
	} else if (object->getType() == "p_health") {
		std::cout << "hello" << "\n";
	}
	else if (object->getType().substr(0, 5) == "sign_"/* && object->getType().size() == 6*/) {
		cPlayer* player;
		player = static_cast<cPlayer*>(m_parent);
		int num = atoi(object->getType().substr(5, 1).c_str());
		player->setIsInSign(num, true);
		player->setIsNearSign(true);
	} else if (object->getType() == "shop_in") {
		cPlayer* player;
		player = static_cast<cPlayer*>(m_parent);
		player->setIsNearShop(true);
	} else if (object->getType().substr(0, 8) == "trigger_") {
		return;
	} else if (object->getType().substr(0, 7) == "target_") {
		if (object->getAnimTag() == eAnimTag::death) {
			return;
		}
		/*if (object->getIsDead()) {
			return;
		}*/
		//std::cout << "cParticleSense::collisionReactionX " << object->getAnim().y << "\n";
		//m_doRemove = true;
		if (m_parent != nullptr) {
			//cPlayer *player;
			//player = static_cast<cPlayer*>(m_parent);

			//if (player->keysHeld[cInputManager::getLeftKey()] || player->keysHeld[cInputManager::getRightKey()]) {
				//m_doRemove = true;
				//m_parent->clearSense();
				//m_parent->senseCollided(object);
				if (m_velocityX < 0.0f) {
					m_parent->senseCollidedLeft(object);
				} else if (m_velocityX > 0.0f) {
					m_parent->senseCollidedRight(object);
				}
			//}

		}
		return;
	} else if (object->getType() == "e_flyling") {
		return;
	} else if (object->getType() == "e_grass") {
		//std::cout << "sensed grass" << "\n";
		if (m_parent == nullptr) { return; };
		//if (m_timeBeingAlive > 1.0f) { return; }
		object->setIsIdle(false);
		int num = 0;
		if (m_parent->getMiddleX() < object->getMiddleX()) {
			object->setIsFacingLeft(false);
			num = (int)abs(object->getMiddleX() - m_parent->getMiddleX());
			//std::cout << num << " " << num / 2 << "\n";
		} else {
			object->setIsFacingLeft(true);
			num = (int)abs(object->getMiddleX() - m_parent->getMiddleX());
			//std::cout << num << " " << num / 2 << "\n";
		}
		float tileX = 32.0f * 7.0f - ((num / 4) * 32.0f);
		if (tileX <= 0.0f) {
			tileX = 0.0f;
		} else if (tileX > 0.0f && tileX <= 48.0f) {
			tileX = 32.0f;
		} else if (tileX > 48.0f && tileX < 80.0f) {
			tileX = 64.0f;
		} else if (tileX > 80.0f && tileX < 128.0f) {
			tileX = 96.0f;
		}
		object->setTileOffsetX(tileX);
	} else {
		return;
	}
}

void cParticleSense::collisionReactionY(cBaseObject* object) {
	if (object->getIsCarried()) {
		return;
	}
	if (m_parent != nullptr && m_parent->getTimerThrow() > 0.0f) {
		return;
	}
	if (object->getType() == "clip" || object->getType() == "e_brick") {
		return;
	} else if (object->getType() == "player") {
		return;
	} else if (object->getType() == "shop_in")	{
		collisionReactionX(object);
	} else if (object->getType().substr(0, 5) == "sign_") {
		collisionReactionX(object);
	} else {
		return;
	}
}