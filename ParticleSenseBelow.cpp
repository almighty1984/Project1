#include "Object.h"
#include "Entity.h"
#include "EntityGrodorrAttackState.h"
#include "InputManager.h"
#include "SoundsManager.h"
#include "ParticleSenseBelow.h"
#include "Player.h"


void cParticleSenseBelow::collisionReactionY(cBaseObject* object) {
	if (object->getIsSlope()) {
		collisionReactionSlopeY(object);
	}
	/*if (object->getIsDead()) {
		return;
	}*/

	//if (m_parent != nullptr) {
	//	m_parent->senseCollidedBelow(object);
	//	//m_doRemove = true;
	//	std::cout << object->getType() << "\n";
	//}
	//return;

	/*if (object->getIsAnim() && object->getAnimTag() == eAnimTag::death) {
		return;
	}*/
	if (object->getType().substr(0, 3) == "cam" ||
		object->getType() == "door_0" || object->getType() == "door_exit" ||
		object->getType() == "e_brick" ||
		object->getType().substr(0, 11) == "e_item" ||
		object->getType().substr(0, 5) == "level" ||
		object->getType().substr(0, 4) == "view" ||
		object->getType().substr(0, 4) == "path" ||
		object->getType().substr(0, 4) == "sign" ||
		object->getType().substr(0, 5) == "wall_" ||
		object->getType().substr(0, 5) == "water") {
		return;
	} else if (object->getType().substr(0, 4) == "clip" || object->getType().substr(0, 5) == "slope") {
		if (m_parent != nullptr) {
			m_parent->senseCollidedBelow(object);
			std::cout << object->getType() << "\n";
		}
		return;
	} else if (object->getType() == "player") {
		return;
	} else if (object->getType().substr(0, 8) == "trigger_") {
		return;
	} else if (object->getType().substr(0, 7) == "target_") {
		return;
	} else if (object->getType() == "e_flyling") {
		return;
	} else {
		return;
	}
}

void cParticleSenseBelow::collisionReactionX(cBaseObject* object) {
	return;
}