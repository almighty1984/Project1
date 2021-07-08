#include "ParticleHealth.h"
#include "ParticleMelee.h"
#include "ParticleShot.h"
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

void cParticleMelee::collisionReactionX(cBaseObject* object) {
	//std::cout << "cParticleMelee::collisionReactionX " << object->getType() << "\n";
	if (object->getType() == "breakable_0" || object->getType() == "breakable_1") {
		object->setIsDead(true);
		m_isDead = true;
		object->setIsAnim(true);
		object->setTileOffsetX(0.0f);
		object->setTileOffsetY(32.0f);
		object->setAnimTime(5);
		object->update(0.0f);

		std::cout << "cParticleMelee::collisionReactionX " << object->getType() << "\n";

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
	} else if (object->getType().substr(0, 14) == "p_sense") {		
	} else if (object->getType().substr(0, 4) == "pot_") {
		if (object->getIsDead()) {
			return;
		}
		//std::cout << "cParticleMelee::collisionReactionX " << object->getType() << "\n";
		object->setIsDead(true);
		m_isDead = true;
		object->setIsAnim(true);
		object->setTileOffsetX(0.0f);
		object->setTileOffsetY(32.0f);

		cSoundsManager::stop(eSoundTag::breakPot);
		cSoundsManager::play(eSoundTag::breakPot);


		cLevel* level = object->getAttachedLevel();
		level->addParticle(new cParticle);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_hit.cfg");
		level->getParticleLast()->setX(object->getX() + object->getWidth() / 2 - level->getParticleLast()->getWidth() / 2);
		level->getParticleLast()->setY(object->getY() + object->getHeight() / 2);
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

		/*object->m_particles.back()->setVelocityX(-1.0f);
		object->m_particles.back()->setVelocityY(-1.0f);*/
		//object->setParticleVelocityX(-1.0f);
		//object->m_particles.back()->update(0.0f);		
	} else if (object->getType().substr(0, 8) == "trigger_") {
	} else if (object->getType().substr(0, 7) == "target_") {
		/*if (!object->getIsDead()) {
			m_isDead = true;
		}*/
		if (object->getTileOffsetY() == 0.0f) {
			std::cout << "ParticleMelee::collisionReactionX " << object->getType() << " closed" << "\n";
			m_isDead = true;
		}
	} else if (object->getType().substr(0, 7) == "e_brick") {
		//if (m_isDead || object->getIsDead() || object->getNumHealth() <= 0.0f || object->getHurtAgainDelayValue() > 0.0f) {
		//	return;
		//}
		///*m_velocityX *= 0.125f;
		//m_velocityY *= 0.125f;*/
		m_doRemove = true;
		object->die(this);
	} else if (object->getType() == "e_ball") {
		object->setVelocityX(m_velocityX);
		m_isDead = true;
		cSoundsManager::stop(eSoundTag::hit);
		cSoundsManager::play(eSoundTag::hit);
	} else if (object->getType() == "e_flyling") {
		if (!object->getIsDead() && !object->getIsHurting()) {
			cSoundsManager::stop(eSoundTag::hit);
			cSoundsManager::play(eSoundTag::hit);
			object->hit(object->getMiddleX(), object->getMiddleY());
			object->setIsHurting(true);
			cPlayer* player;
			player = static_cast<cPlayer*>(m_parent);
			object->setNumHealth(object->getNumHealth() - 20.0f * player->getVitality());

			/*if (player->keysHeld[cInputManager::getUpKey()]) {
				std::cout << "THIS HAPPENED" << "\n" << "\n" << "\n" << "\n";
				object->setVelocityX(m_velocityX * 0.71f*1.5f);
				object->setVelocityY(-abs(m_velocityX) * 0.71f*0.5f);
			}
			else if (player->keysHeld[cInputManager::getDownKey()]) {
				object->setVelocityX(m_velocityX * 0.71f*1.5f);
				object->setVelocityY(abs(m_velocityX) * 0.71f*0.5f);
			}
			else {
				object->setVelocityX(m_velocityX);
				object->setVelocityY(0.0f);
			}*/

			/*object->setVelocityX(player->getVelocityX() + m_velocityX * 1.0f);
			object->setVelocityY(player->getVelocityY() + m_velocityY * 1.0f);*/

			/*if (object->getIsDead() == false) {
				cEntityFlyling* entityFlyling;
				entityFlyling = static_cast<cEntityFlyling*>(object);
				std::cout << "p_melee collided with entity_flyling" << "\n";
				if (m_velocityX < 0.0f) {
					entityFlyling->setIsFacingLeft(false);
				} else {
					entityFlyling->setIsFacingLeft(true);
				}
				entityFlyling->setIsHurting(true);
				entityFlyling->setNumHealth(entityFlyling->getNumHealth() - 50);
				entityFlyling->setHurtAgainDelayValue(0);
				entityFlyling->setVelocityX(m_velocityX * 2.0f);
				m_isDead = true;
			}*/

			cEntity* entityFlyling;
			entityFlyling = static_cast<cEntityFlyling*>(object);
			std::cout << "p_melee collided with entity_flyling" << "\n";
			entityFlyling->setVelocityX(m_velocityX * 1.5f);
			entityFlyling->setIsHurting(true);
			entityFlyling->setHurtAgainDelayValue(entityFlyling->getHurtAgainDelay());
			entityFlyling->setState(new cEntityFlylingHitState(m_parent->getVelocityX(), m_parent->getVelocityY()));
		}
	} else if (object->getType() == "e_flugan") {
		if (object->getNumHealth() <= 0 || m_isDead) { return; }
		m_isDead = true;
		//if (m_isFacingLeft != object->getIsFacingLeft()) {
		//	cSoundsManager::stop(eSoundTag::block);
		//	cSoundsManager::play(eSoundTag::block);
		//	//m_isDead = true;
		//	return;
		//}		
		if (!object->getIsDead()) {
			cEntity* entity;
			entity = static_cast<cEntity*>(object);
			if (m_isFacingLeft) {
				entity->hit(getX() + getWidth() / 2 - 32, entity->getMiddleY());
			} else {
				entity->hit(getX() + getWidth() / 2, entity->getMiddleY());
			}
			//entity->setVelocityX(m_velocityX);
			//entity->setVelocityY(m_parent->getVelocityY()/2);
			
			object->setVelocityY(m_velocityY + object->getVelocityY() - 1.0f);

			entity->hurt(this, 10.0f);


		}
	} else if (object->getType() == "e_grevert") {
		if (object->getNumHealth() <= 0 || object->getIsIdle()) { return; }
		m_isDead = true;
		if (!object->getIsDead()) {
			cSoundsManager::stop(eSoundTag::hit);
			cSoundsManager::play(eSoundTag::hit);
			cEntity* entity;
			entity = static_cast<cEntity*>(object);
			/*if (m_isFacingLeft) {
				entity->hit(getX() + getWidth() / 2-0, entity->getY() + entity->getHeight() / 2);
			} else {
				entity->hit(getX() + getWidth() / 2+32, entity->getY() + entity->getHeight() / 2);
			}*/
			entity->hit(getMiddleX(), entity->getBottom() - m_height / 2);
			entity->setVelocityX(getVelocityX() * 0.25f);
			entity->setVelocityY(m_parent->getVelocityY() / 2 - 0.0f);
			entity->hurt(this, 100.0f);
		}
	} else if (object->getType() == "e_grodorr") {
		if (object->getNumHealth() <= 0 || m_parent == nullptr) {
			return;
		}
		//object->die(this);
		m_isDead = true;
		if (!object->getIsDead()) {
			cSoundsManager::stop(eSoundTag::hit);
			cSoundsManager::play(eSoundTag::hit);
			/*if (m_isFacingLeft) {
				entity->hit(getX() + getWidth() / 2-0, entity->getY() + entity->getHeight() / 2);
			} else {
				entity->hit(getX() + getWidth() / 2+32, entity->getY() + entity->getHeight() / 2);
			}*/
			object->hit(getMiddleX(), object->getBottom()-m_height/2);
			object->setVelocityX(getVelocityX()*0.25f);
			//object->setVelocityY(m_parent->getVelocityY() - 4.0f);
			object->setVelocityY(m_parent->getVelocityY()/2 - 4.0f);
			object->hurt(this, 10.0f);
			
		}
	} else if (object->getType() == "e_pigan") {
		m_isDead = true;
		/*bool isFacingLeft = object->getIsFacingLeft();
		if (object->getIsOnBack()) {
			isFacingLeft = !object->getIsFacingLeft();
		}*/
		cSoundsManager::play(eSoundTag::hit);
		object->setIsFacingLeft(!object->getIsFacingLeft());
		object->hurt(this, 10.0f);
		object->setVelocityX(0.0f);		
	} else if (object->getType() == "e_swing") {
		std::cout << "p_melee collided with swing" << "\n";
		if (m_parent == nullptr) {
			return;
		}
		cPlayer* player;
		player = static_cast<cPlayer*>(m_parent);

		if (player->getIsInSwing()) {
			return;
		}
		player->setMorphObject(object);
		player->setState(new cPlayerSwingState);
	} else if (object->getType() == "wood") {
		setIsDead(true);
		object->setIsDead(true);
	} else if (object->getType() == "player") {
		/*m_isDead = true;
		object->setVelocityX(object->getVelocityX()+m_velocityX);
		std::cout << "HELLLLOOOOOO" << "\n";*/
		return;
	}

}

void cParticleMelee::collisionReactionY(cBaseObject* object) {
	if (object->getType() == "e_pigan") {
		m_isDead = true;
		//m_collidedBaggen = true;
		if (object->getIsDead() == false) {
			std::cout << "cParticleMelee::collisionReactionY " << "m_isDead = true" << "\n";
			object->setIsDead(true);
			object->setTileOffsetX(0.0f);
		}
	} else if (object->getType() == "wood") {
		setIsDead(true);
		object->setIsDead(true);
	} else if (object->getType().substr(0, 14) == "p_sense") {
		return;
	} else if (object->getType() == "swing") {
		////setCollidedSwing(false);
		//object->setIsHidden(true);
		//if (cSoundsManager::m_soundSwingAttach.getStatus() != sf::SoundSource::Playing)
		//	cSoundsManager::m_soundSwingAttach.play();

		//std::cout << "p_melee collided with swing" << "\n";
		////m_collidedSwing = true;
		//m_parent->setIsInSwing(true);
		//m_parent->setIsHidden(true);
		//cPlayer *player;
		//player = static_cast<cPlayer*>(m_parent);
		//player->setState(new cPlayerSwingState);

		//object->setIsFacingLeft(m_parent->getIsFacingLeft());
		//m_parent->attachMorphObject(object);
		//object->setWidth(128);
		//object->setHeight(128);
		//std::cout << (object->getY()) << "\n";
	} else {
		return;
		//std::cout << "particle is dead\n";
		//m_isDead = true;
	}
	//m_velocityY = 0.0f;	
}