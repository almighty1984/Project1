#include "ParticleHealth.h"
#include "ParticleGrevertAttack.h"
#include "RenderingManager.h"
#include "SoundsManager.h"
#include "Player.h"
#include "EntityItem.h"
#include "EntityFlylingDeathState.h"
void cParticleGrevertAttack::collisionReactionX(cBaseObject* object) {
	//std::cout << "cParticleGrodorr::collisionReactionX " << object->getType() << "\n";
	if (object->getType() == "cam_lock" || object->getType() == "cam_unlock" ||
		object->getType() == "cam_lock_ws" || object->getType() == "cam_unlock_ws" ||
		object->getType() == "clip" ||
		object->getType() == "clip_top" ||
		object->getType() == "clip_bot" ||
		object->getType() == "door_0" || object->getType() == "door_exit" ||
		object->getType() == "view_lock" || object->getType() == "view_unlock" ||		
		object->getType() == "p_sense") {
		return;
	} else if (object->getType() == "player") {
		if (object->getIsOnLedge()) {
			return;
		}
		if (object->getIsHurting() || object->getNumHealth() <= 0.0f) {
			return;
		}
		object->setVelocityX(object->getVelocityX() + m_velocityX);
		m_attachedLevel = object->getAttachedLevel();

		cPlayer* player;
		player = static_cast<cPlayer*>(object);

		player->hurt(this, 20.0f);
		player->setIsHurting(true);
		player->setHurtSleepDelay(m_hurtSleepDelay);
		player->setHurtAgainDelayValue(player->getHurtAgainDelay());

		cSoundsManager::stop(eSoundTag::hit);
		cSoundsManager::play(eSoundTag::hit);

		if (m_attachedLevel == nullptr) {
			return;
		}
		cLevel* level = m_attachedLevel;
		level->addParticle(new cParticle);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_hit.cfg");

		if (m_x < object->getX() + object->getWidth() / 2) {
			level->getParticleLast()->setX(player->getX() + player->getWidth() / 2 - 16);
		} else {
			level->getParticleLast()->setX(player->getX() + player->getWidth() / 2 - 8);
		}

		level->getParticleLast()->setY(m_y - 8);
		unsigned char randNum = (rand() % 7) * 32;
		std::cout << "randNum: " << randNum << "\n";
		level->getParticleLast()->setTileOffsetX((float)randNum);
		level->getParticleLast()->setTileOffsetY(0.0f);
		level->getParticleLast()->setIsHidden(false);
		level->getParticleLast()->update(0.0f);
	} else if (object->getType() == "trigger") {
		m_isDead = true;
		std::cout << m_type << "\n";
	} else if (object->getType().substr(0, 7) == "target_") {
		//m_isDead = true;
		if (object->getTileOffsetY() == object->getAnim(eAnimTag::idle).y) {
			m_isDead = true;
		}
		/*if (!object->getIsDead()) {
			m_isDead = true;
		}*/
	} else if (object->getType() == "e_flugan") {
		if (object->getNumHealth() <= 0) { return; }
		if (object->getIsDead()) { return; }
		m_isDead = true;
		cEntity* entity;
		entity = static_cast<cEntity*>(object);
		entity->hurt(this, 100.0f);
	} else if (object->getType() == "e_grodorr") {		
		if (object->getNumHealth() <= 0) { return; }
		if (object->getIsDead()) { return; }
		m_isDead = true;
		cEntity* entity;
		entity = static_cast<cEntity*>(object);
		entity->hurt(this, 100.0f);
	} else if (object->getType() == "e_flyling") {

	} else {
		//m_isDead = true;
	}
}

void cParticleGrevertAttack::collisionReactionY(cBaseObject* object) {
	collisionReactionX(object);
}