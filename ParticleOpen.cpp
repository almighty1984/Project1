#include "ParticleOpen.h"

#include "EntityItem.h"
#include "ParticleHealth.h"
#include "RenderingManager.h"
#include "SavesManager.h"
#include "SoundsManager.h"
#include "Object.h"
#include "Level.h"

#include "EntityBrickThrownState.h"

void cParticleOpen::collisionReactionX(cBaseObject* object) {
	collisionReactionY(object);
}

void cParticleOpen::collisionReactionY(cBaseObject* object) {
	//std::cout << "cParticleOpen::collisionReactionY " << object->getType() << "\n";
	if (object->getType() == "player") {
		return;
	} else if (object->getType() == "e_brick") {
		if (m_parent == nullptr || (m_parent != nullptr && m_parent->getIsThrowing())) {
			return;
		}
		if (!m_parent->getIsCarrying()) {
			m_parent->setIsCarrying(true);
			m_parent->clearSenseLeft();
			m_parent->clearSenseRight();
			/*if (object->getAboveObject() != nullptr) {
				m_parent->setCarriedObject(object->getAboveObject());
				object->getAboveObject()->setIsCarried(true);
				object->getAboveObject()->setCarrier(m_parent);
			} else {*/
			m_parent->setCarriedObject(object);
			object->setIsCarried(true);
			object->setCarrier(m_parent);
			//}

		}
		m_doRemove = true;
	} else if (object->getType() == "e_pigan") {
		if (m_parent == nullptr || !object->getIsOnBack() || (m_parent != nullptr && m_parent->getIsThrowing())) {
			return;
		}
		if (!m_parent->getIsCarrying()) {
			m_parent->setIsCarrying(true);
			m_parent->clearSenseLeft();
			m_parent->clearSenseRight();
			/*if (object->getAboveObject() != nullptr) {
				m_parent->setCarriedObject(object->getAboveObject());
				object->getAboveObject()->setIsCarried(true);
				object->getAboveObject()->setCarrier(m_parent);
			} else {*/
			m_parent->setCarriedObject(object);
			object->setIsCarried(true);
			object->setCarrier(m_parent);
			//}

		}
		m_doRemove = true;
	} else if (object->getType().substr(0, 6) == "chest_") {
		if (m_parent != nullptr && (m_parent->getIsThrowing() || m_parent->getIsCarrying() || !m_parent->getIsOnGround())) {
			return;
		}
		m_parent->setVelocityX(0.0f);
		//object->setState(new cObjectDeathState);

		object->hit(m_x, m_y);
		//std::cout << "cParticleMelee::collisionReactionx " << object->getType() << "\n";
		object->setIsDead(true);
		object->setAnim(eAnimTag::death);
		m_isDead = true;
		object->setIsAnim(true);
		object->setTileOffsetX(0.0f);

		cSoundsManager::stop(eSoundTag::chestOpen);
		cSoundsManager::play(eSoundTag::chestOpen);

		cLevel* level;
		level = object->getAttachedLevel();

		if (level == nullptr) {
			return;
		}
		level->addEntity(new cEntityItem);
		level->getEntityLast()->loadConfig("Data\\Entities\\e_item_coin.cfg");
		level->getEntityLast()->setIsDead(false);
		level->getEntityLast()->setIsAnim(false);
		level->getEntityLast()->setX(object->getX() + 8);
		level->getEntityLast()->setY(object->getY() + 4);
		level->getEntityLast()->setStartX(object->getX());
		level->getEntityLast()->setStartY(object->getY());
		level->getEntityLast()->setLevelX(object->getLevelX());
		level->getEntityLast()->setLevelY(object->getLevelY());
		level->getEntityLast()->attachLevel(level);

		cPlayer* player;
		player = static_cast<cPlayer*>(m_parent);
		level->getEntityLast()->attachPlayer(player);
	} else if (object->getType().substr(0, 8) == "trigger_") {
		if (object->getIsHurting()/* || cSoundsManager::isPlaying(eSoundTag::chestOpen)*/) {
			return;
		}
		if (m_parent != nullptr && m_parent->getIsThrowing() || m_parent->getIsCarrying()) {
			return;
		}
		m_parent->setVelocityX(0.0f);
		//m_isDead = true;
		cSoundsManager::play(eSoundTag::chestOpen);
		object->setHurtAgainDelayValue(object->getHurtAgainDelay());

		int tmpInt = 0;
		if (object->getType().size() == 9) {
			std::istringstream(object->getType().substr(8, 1)) >> tmpInt;
		} else if (object->getType().size() == 10) {
			std::istringstream(object->getType().substr(8, 2)) >> tmpInt;
		}
		std::cout << m_parent->getAttachedLevel()->getPath() << " " << tmpInt << "\n";

		eAnimTag oldAnimTag = object->getAnimTag();

		if (cSavesManager::hasTargetedObject(m_parent->getAttachedLevel()->getPath(), tmpInt)) {
			cSavesManager::removeTargetObject(m_parent->getAttachedLevel()->getPath(), tmpInt);
			object->live();
		} else {
			cSavesManager::addTargetObject(m_parent->getAttachedLevel()->getPath(), tmpInt);
			object->die(this);
		}

		if (oldAnimTag == eAnimTag::idle) {
			object->setAnim(eAnimTag::death);
			m_parent->setIsFacingLeft(true);
			//object->setTileOffsetY(32.0f);
			//cSavesManager::addTargetObject(m_parent->getAttachedLevel()->getPath(), tmpInt);
			//object->die(this);
			//object->setAnim(eAnimTag::death);
		} else if (oldAnimTag == eAnimTag::death) {
			object->setAnim(eAnimTag::idle);
			m_parent->setIsFacingLeft(false);
			//object->setTileOffsetY(0.0f);
			//cSavesManager::removeTargetObject(m_parent->getAttachedLevel()->getPath(), tmpInt);
			//object->live();
			//object->setAnim(eAnimTag::idle);
		}
		//object->setIsDead(false);		
		object->update(0.0f);

		m_parent->setTileOffsetX(0.0f);
		m_parent->setAnim(eAnimTag::open);
	}
}