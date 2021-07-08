#include "ParticleHealth.h"
#include "ParticleFluganAttack.h"
#include "RenderingManager.h"
#include "SoundsManager.h"
#include "Player.h"
#include "EntityItem.h"
#include "EntityFlylingDeathState.h"
void cParticleFluganAttack::collisionReactionX(cBaseObject *object) {
	//std::cout << "cParticleFlugan::collisionReactionX " << object->getType() << "\n";
	if (object->getType() == "cam_lock") {
	} else if (object->getType() == "cam_unlock") {
	} else if (object->getType() == "cam_lock_ws") {
	} else if (object->getType() == "cam_unlock_ws") {
	} else if (object->getType() == "clip") {
	} else if (object->getType() == "clip_top") {
	} else if (object->getType() == "clip_bot") {
	} else if (object->getType() == "door_0") {
	} else if (object->getType() == "door_exit") {
	} else if (object->getType() == "view_lock") {
	} else if (object->getType() == "view_unlock") {
	} else if (object->getType().substr(0, 7) == "p_sense") {
	} else if (object->getType() == "player") {
		if (object->getIsRiding() || object->getIsOnLedge()) {
			return;
		}

		if (!object->getIsNearWallLeft() && !object->getIsNearWallRight()) {
			object->setVelocityX(object->getVelocityX() + m_velocityX);			
		}
		object->setVelocityY(-2.0f);

		if (object->getIsHurting() || object->getNumHealth() <= 0.0f) {
			return;
		}

		cPlayer *player;
		player = static_cast<cPlayer*>(object);

		player->hurt(this, 20.0f);
		player->setIsHurting(true);
		player->setHurtSleepDelay(m_hurtSleepDelay);
		player->setHurtAgainDelayValue(player->getHurtAgainDelay());

		cSoundsManager::stop(eSoundTag::hit);
		cSoundsManager::play(eSoundTag::hit);
		
		m_attachedLevel = object->getAttachedLevel();
		if (m_attachedLevel == nullptr) {
			return;
		}
		cLevel *level = m_attachedLevel;
		level->addParticle(new cParticle);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_hit.cfg");
		//l->getParticleLast()->setIsHidden(true);

		if (m_x < object->getMiddleX()) {
			level->getParticleLast()->setX(object->getMiddleX() - 16);
		} else {
			level->getParticleLast()->setX(object->getMiddleX() - 8);
		}

		level->getParticleLast()->setY(m_y - 8);
		unsigned char randNum = (rand() % 7) * 32;
		std::cout << "randNum: " << randNum << "\n";
		level->getParticleLast()->setTileOffsetX((float)randNum);
		level->getParticleLast()->setTileOffsetY(0.0f);
		level->getParticleLast()->setIsHidden(false);
		level->getParticleLast()->update(0.0f);
	}
	else if (object->getType() == "trigger") {
		m_isDead = true;
		std::cout << m_type << "\n";
	}
	else if (object->getType().substr(0, 7) == "target_") {
		//m_isDead = true;
		if (object->getTileOffsetY() == object->getAnim(eAnimTag::idle).y) {
			m_isDead = true;
		}
		/*if (!object->getIsDead()) {
			m_isDead = true;
		}*/
	}
	else if (object->getType().substr(0, 7) == "e_brick") {
		object->die(this);
		m_parent->hurt(object, 1.0f);
	}
	else if (object->getType() == "e_flugan") {
		return;
		if (object->getNumHealth() <= 0) { return; }
		if (object->getIsDead()) { return; }
		m_isDead = true;
		cEntity *entity;
		entity = static_cast<cEntity*>(object);
		entity->hurt(this, 100.0f);
	}
	else if (object->getType() == "e_grodorr") {
		object->die(this);
		/*return;
		if (object->getNumHealth() <= 0) { return; }
		if (object->getIsDead()) { return; }
		m_isDead = true;
		cEntity *entity;
		entity = static_cast<cEntity*>(object);
		entity->hurt(this, 100.0f);*/
	}
	else if (object->getType() == "e_flyling") {
		
	}
	else {
		//m_isDead = true;
	}
}

void cParticleFluganAttack::collisionReactionY(cBaseObject *object) {

}