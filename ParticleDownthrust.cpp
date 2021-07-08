#include "ParticleHealth.h"
#include "ParticleDownthrust.h"
#include "RenderingManager.h"
#include "InputManager.h"
#include "SoundsManager.h"
#include "SavesManager.h"
#include "PlayerSwingState.h"
#include "EntityPigan.h"
#include "EntityPiganHurtState.h"
#include "EntityItem.h"

#include "EntityFlylingHitState.h"
#include "EntityFlylingDeathState.h"

#include "EntityFluganStunnedState.h"

#include "EntityGrodorrStunnedState.h"

void cParticleDownthrust::collisionReactionX(cBaseObject* object) {
	if (object->getType() == "breakable_0" || object->getType() == "breakable_1") {
		object->setIsDead(true);
		m_isDead = true;
		object->setIsAnim(true);
		object->setTileOffsetX(0.0f);
		object->setTileOffsetY(32.0f);
		object->setAnimTime(5);
		object->update(0.0f);

		std::cout << "cParticleDownthrust::collisionReactionX" << object->getType() << "\n";

		if (cSoundsManager::isPlaying(eSoundTag::breakPot)) {
			cSoundsManager::stop(eSoundTag::breakPot);
		}

		cSoundsManager::play(eSoundTag::breakPot);
		/*if (object->m_particles.size() == 0) {
			object->m_particles.push_back(new cParticle);
			object->m_particles.at( 0 )->loadConfig("Data\\Particles\\p_hit.cfg");
			object->m_particles.at( 0 )->setX( object->getX()+object->getWidth()/2-16 );
			object->m_particles.at( 0 )->setY( object->getY()+object->getHeight()/2 );
			int randNum = (rand() % 7) * 32;
			object->m_particles.at( 0 )->setTileOffsetX(randNum);
			object->m_particles.at( 0 )->setTileOffsetY(0.0f);

			object->m_particles.at( 0 )->setIsHidden(false);
			object->m_particles.at( 0 )->setIsDead(false);
			object->m_particles.at( 0 )->setTimeToBeAliveValue(0);
			object->m_particles.at( 0 )->update(0.0f);

			cRenderingManager::addParticle(object->m_particles.at( 0 ));
		}	*/
	} else if (object->getType().substr(0, 6) == "chest_") {
		return;
	} else if (object->getType().substr(0, 4) == "clip") {
		return;
	} else if (object->getType().substr(0, 8) == "trigger_") {
		return;
	} else if (object->getType().substr(0, 10) == "target_") {
		return;
	} else if (object->getType() == "swing") {
		return;
	} else if (object->getType() == "e_brick") {
		return;
	} else if (object->getType() == "e_ball") {
		object->setVelocityX(m_velocityX);
		m_isDead = true;
		cSoundsManager::stop(eSoundTag::hit);
		cSoundsManager::play(eSoundTag::hit);
	} else if (object->getType() == "e_flyling") {
		cSoundsManager::stop(eSoundTag::hit);
		cSoundsManager::play(eSoundTag::hit);

		if (object->getIsDead() == false) {
			if (!object->getIsHurting()) {
				object->hit(object->getX(), object->getY());

				cPlayer* player;
				player = static_cast<cPlayer*>(m_parent);
				object->setNumHealth(object->getNumHealth() - 20.0f * player->getVitality());

				if (player->getIsPressingUp()) {
					std::cout << "THIS HAPPENED" << "\n" << "\n" << "\n" << "\n";
					object->setVelocityX(m_velocityX * 0.71f * 1.5f);
					object->setVelocityY(-abs(m_velocityX) * 0.71f * 0.5f);
				} else if (player->getIsPressingDown()) {
					object->setVelocityX(m_velocityX * 0.71f * 1.5f);
					object->setVelocityY(abs(m_velocityX) * 0.71f * 0.5f);
				} else {
					object->setVelocityX(m_velocityX);
					object->setVelocityY(0.0f);
				}

				/*object->setVelocityX(player->getVelocityX() + m_velocityX * 1.0f);
				object->setVelocityY(player->getVelocityY() + m_velocityY * 1.0f);*/

				cEntityFlyling* entityFlyling;
				entityFlyling = static_cast<cEntityFlyling*>(object);

				if (entityFlyling->getNumHealth() <= 0) {
					//entity->setIsDead(true);
					entityFlyling->setIsAttacking(false);
					entityFlyling->setIsCharging(false);
					entityFlyling->setState(new cEntityFlylingDeathState);
					return;
				} else {
					std::cout << "p_melee collided with entity_flyling" << "\n";
					entityFlyling->setIsHurting(true);
					entityFlyling->setHurtAgainDelayValue(entityFlyling->getHurtAgainDelay());
					entityFlyling->setState(new cEntityFlylingHitState);
				}
			}
			//m_isDead = true;
		}
	} else if (object->getType() == "e_flugan") {
		if (object->getNumHealth() <= 0) { return; }
		m_isDead = true;
		//if (m_isFacingLeft != object->getIsFacingLeft()) {
		//	cSoundsManager::stop(eSoundTag::block);
		//	cSoundsManager::play(eSoundTag::block);
		//	//m_isDead = true;
		//	return;
		//}		
		if (!object->getIsDead()) {

			if (object->getMiddleX() < getMiddleX()) {
				object->setVelocityX(-1.0f);
			} else {
				object->setVelocityX(1.0f);
			}
			object->setVelocityY(-2.0f);

			cEntity* entity;
			entity = static_cast<cEntity*>(object);
			/*if (m_isFacingLeft) {
				entity->hit(getX() + getWidth() / 2 - 32, entity->getY() + entity->getHeight() / 2);
			}
			else {*/
			entity->hit(getX() + getWidth() / 2, entity->getY() + entity->getHeight() / 2);
			//}
			//entity->setVelocityX(0.0f);
			//entity->setVelocityY(-2.5f);
			entity->setState(new cEntityFluganStunnedState);

			entity->hurt(this, 10.0f);
		}
	} else if (object->getType() == "e_grevert") {
		if (object->getNumHealth() <= 0 || object->getIsIdle()) { return; }
		m_isDead = true;
		if (!object->getIsDead()) {
			/*if (m_isFacingLeft) {
				object->hit(getX() + getWidth() / 2-0, object->getY() + object->getHeight() / 2);
			} else {
				object->hit(getX() + getWidth() / 2+32, object->getY() + object->getHeight() / 2);
			}*/
			object->hit(getMiddleX(), object->getBottom() - m_height / 2);
			object->setVelocityX(getVelocityX() * 0.25f);
			object->setVelocityY(m_parent->getVelocityY() / 2 - 0.0f);
			object->hurt(this, 20.0f);
		}
	} else if (object->getType() == "e_grodorr") {
		if (object->getNumHealth() <= 0) {
			object->die(this);
			return;
		}
		m_isDead = true;
		if (!object->getIsDead()) {
			object->hit(getMiddleX(), getMiddleY());
			object->setVelocityX(getVelocityX() * 0.25f);
			object->setVelocityY(-0.5f);
			object->hurt(this, 10.0f);
		}
	} else if (object->getType() == "e_pigan") {
		m_isDead = true;
		bool isFacingLeft = object->getIsFacingLeft();
		if (object->getIsOnBack()) {
			isFacingLeft = !object->getIsFacingLeft();
		}
		cSoundsManager::play(eSoundTag::hit);
		object->setIsFacingLeft(!m_parent->getIsFacingLeft());
		object->hurt(this, 1.0f);
		object->setVelocityX(0.0f);
	} else if (object->getType() == "wood") {
		setIsDead(true);
		object->setIsDead(true);
	} else if (object->getType() == "player") {
		return;
	} else if (object->getType().substr(0, 4) == "pot_") {
		if (object->getIsDead() == true) {
			return;
		}

		std::cout << "cParticleDownthrust::collisionReactionX" << object->getType() << "\n";
		object->setIsDead(true);
		m_isDead = true;
		object->setIsAnim(true);
		object->setTileOffsetX(0.0f);
		object->setTileOffsetY(32.0f);

		cSoundsManager::stop(eSoundTag::breakPot);
		cSoundsManager::play(eSoundTag::breakPot);

		cLevel* level;
		level = object->getAttachedLevel();

		level->addParticle(new cParticle);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_hit.cfg");
		level->getParticleLast()->setX(object->getMiddleX() - level->getParticleLast()->getWidth() / 2);
		level->getParticleLast()->setY(object->getMiddleY());
		unsigned char randNum = (rand() % 7) * 32;
		std::cout << "randNum: " << randNum << "\n";
		level->getParticleLast()->setTileOffsetX((float)randNum);
		level->getParticleLast()->setTileOffsetY(0.0f);
		level->getParticleLast()->setIsHidden(false);
		level->getParticleLast()->update(0.0f);

		randNum = (rand() % 7) * 32;
		std::cout << "randNum: " << randNum << "\n";
		level->getParticleLast()->setTileOffsetX((float)randNum);
		level->getParticleLast()->update(0.0f);

		level->getParticleLast()->setIsHidden(false);

		level->addParticle(new cParticleHealth);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_health.cfg");
		level->getParticleLast()->setX(object->getX() + level->getParticleLast()->getOffsetX());
		level->getParticleLast()->setY(object->getY() + level->getParticleLast()->getOffsetY());
	}

}

void cParticleDownthrust::collisionReactionY(cBaseObject* object) {
	if (object->getType().substr(0, 4) == "clip") {
		return;
	} else if (object->getType() == "e_pigan") {
		m_isDead = true;
		if (!object->getIsDead()) {
			std::cout << "m_isDead = true" << "\n";
			object->setIsDead(true);
			object->setTileOffsetX(0.0f);
		}
	} else if (object->getType() == "wood") {
		setIsDead(true);
		object->setIsDead(true);
	} else if (object->getType() == "swing") {
		return;
	} else {
		return;
	}
}