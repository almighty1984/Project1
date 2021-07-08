#include "PlayerSwingState.h"
#include "PlayerGrassState.h"
#include "SoundsManager.h"
#include "InputManager.h"

cPlayerSwingState::cPlayerSwingState() {
	m_secondCall = false;
}

//cPlayerSwingState::~cPlayerSwingState() {
//}

void cPlayerSwingState::update(cApp* app, cPlayer* p, float time) {
	if (p == nullptr) {
		return;
	}

	if (!m_secondCall) {
		m_secondCall = true;

		if (!cSoundsManager::isPlaying(eSoundTag::swingAttach)) {
			cSoundsManager::play(eSoundTag::swingAttach);
		}

	/*	m_swingX = p->getMorphObject()->getStartX();
		m_swingY = p->getMorphObject()->getStartY();*/

		//app->setUseEventInput(false);
		std::cout << "In swing" << "\n";
		p->setBelowObject(nullptr);
		p->setMovedVelocityX(0.0f);
		p->setMovedVelocityY(0.0f);
		//p->setIsCameraLockedX(false);
		p->setIsInSwing(true);
		//p->setIsHidden(true);
		p->setIsLockedMove(false);
		p->setY(p->getMorphObject()->getY() - 0);
		p->setVelocityY(0.0f);
		//p->m_morphObject->setIsHidden(false);


		std::string pathSwing;

		pathSwing = p->getImagePath().substr(0, p->getImagePath().size() - 4);
		pathSwing.append("_swing.png");

		p->getMorphObject()->setImagePath(pathSwing);
		p->getMorphObject()->setWidth(128);
		p->getMorphObject()->setHeight(128);
		p->getMorphObject()->setOrigin(64, 48);
		p->getMorphObject()->setIsHidden(false);
		p->getMorphObject()->setIsFacingLeft(p->getIsFacingLeft());


		p->getMorphObject()->update(0.0f);
		//app->sleep(100);
	}

	p->setIsHidden(!cRenderingManager::getShowLevelNodeGrid());

	//// Sprint release
	//if (p->keysHeld[cInputManager::get().getSprintKey()])
	//	p->keysHeld[cInputManager::get().getSprintKey()] = false;
	
	// Move left
	if (p->getIsPressingLeft()) {
		p->setIsFacingLeft(true);
		p->getMorphObject()->setIsFacingLeft(true);
		//p->m_isIdle = false;

		if (p->getY() + 64 > p->getMorphObject()->getY() + 8) {
			if (p->getVelocityX() > -4.5f)
				p->setVelocityX(p->getVelocityX() - 0.5f);
		} else {
			if (p->getVelocityX() < 4.5f)
				p->setVelocityX(p->getVelocityX() + 0.5f);
		}
	}
	// Move right
	if (p->getIsPressingRight()) {
		p->setIsFacingLeft(false);
		p->getMorphObject()->setIsFacingLeft(false);

		//p->m_isIdle = false;		

		if (p->getY() + 64 > p->getMorphObject()->getY() + 8) {
			if (p->getVelocityX() < 4.5f) {
				p->setVelocityX(p->getVelocityX() + 0.5f);
			} else {
				if (p->getVelocityX() > -4.5f) {
					p->setVelocityX(p->getVelocityX() - 0.5f);
				}
			}
		}
	}

	float posDiffX = 0.0f;

	if (!p->getIsFacingLeft()) {
		p->getMorphObject()->setSpriteOffsetX(0.0f);
		posDiffX = p->getX() + p->getWidth() / 2 - p->getMorphObject()->getX() + 8 - 16.0f;
		std::cout << posDiffX << "\n";
		if (posDiffX >= -100.0f && posDiffX <= -35.0f)
			p->getMorphObject()->setTileOffsetX(0.0f);
		else if (posDiffX >= -35.0f && posDiffX <= -25.0f)
			p->getMorphObject()->setTileOffsetX(128.0f);
		else if (posDiffX >= -25.0f && posDiffX <= -15.0f)
			p->getMorphObject()->setTileOffsetX(256.0f);
		else if (posDiffX >= -15.0f && posDiffX <= -5.0f)
			p->getMorphObject()->setTileOffsetX(384.0f);
		else if (posDiffX >= -5.0f && posDiffX <= 5.0f)
			p->getMorphObject()->setTileOffsetX(512.0f);

		else if (posDiffX >= 5.0f && posDiffX <= 15.0f)
			p->getMorphObject()->setTileOffsetX(640.0f);
		else if (posDiffX >= 15.0f && posDiffX <= 25.0f)
			p->getMorphObject()->setTileOffsetX(768.0f);
		else if (posDiffX >= 25.0f && posDiffX <= 35.0f)
			p->getMorphObject()->setTileOffsetX(896.0f);
		else if (posDiffX >= 35.0f && posDiffX <= 100.0f)
			p->getMorphObject()->setTileOffsetX(1024.0f);
	} else {
		p->getMorphObject()->setSpriteOffsetX(-128.0f);
		posDiffX = p->getX() + p->getWidth() / 2 - p->getMorphObject()->getX() + 8 - 16.0f;
		std::cout << posDiffX << "\n";
		if (posDiffX >= -100.0f && posDiffX <= -35.0f)
			p->getMorphObject()->setTileOffsetX(1024.0f);
		else if (posDiffX >= -30.0f && posDiffX <= -25.0f)
			p->getMorphObject()->setTileOffsetX(896.0f);
		else if (posDiffX >= -25.0f && posDiffX <= -15.0f)
			p->getMorphObject()->setTileOffsetX(768.0f);
		else if (posDiffX >= -15.0f && posDiffX <= -5.0f)
			p->getMorphObject()->setTileOffsetX(640.0f);

		else if (posDiffX >= -5.0f && posDiffX <= 5.0f)
			p->getMorphObject()->setTileOffsetX(512.0f);
		else if (posDiffX >= 5.0f && posDiffX <= 15.0f)
			p->getMorphObject()->setTileOffsetX(384.0f);
		else if (posDiffX >= 15.0f && posDiffX <= 25.0f)
			p->getMorphObject()->setTileOffsetX(256.0f);
		else if (posDiffX >= 25.0f && posDiffX <= 35.0f)
			p->getMorphObject()->setTileOffsetX(128.0f);
		else if (posDiffX >= 35.0f && posDiffX <= 100.0f)
			p->getMorphObject()->setTileOffsetX(0.0f);
	}

	if (p->getMiddleX() < p->getMorphObject()->getX() + 8) {
		//p->m_animateBackwards = false;
		if (p->getVelocityX() < 4.0f) {
			p->setVelocityX(p->getVelocityX() + 0.3f);
		}

		if (p->getIsFacingLeft() == true) {
			p->setTileOffsetX(0.0f);
		} else {
			p->setTileOffsetX((float)(p->getWidth() * p->getNumAnimFrames() - p->getWidth()));
		}
		//p->getMorphObject()->setTileOffsetX(0.0f);

		//offsetX = (p->getMorphObject()->getX()+8) - (p->getX()+32);
		////p->setY(p->getMorphObject()->getY() - offsetX);
		////p->setVelocityY( p->getVelocityX() );
		//p->m_velocityY = offsetX*0.75f*(p->m_velocityX*0.05f);
	} else if (p->getMiddleX() > p->getMorphObject()->getX() + 8) {
		//p->m_animateBackwards = true;
		if (p->getVelocityX() > -4.0f) {
			p->setVelocityX(p->getVelocityX() - 0.3f);
		}

		if (p->getIsFacingLeft() == true) {
			p->setTileOffsetX((float)(p->getWidth() * p->getNumAnimFrames() - p->getWidth()));
		} else {
			p->setTileOffsetX(0.0f);
		}

		//p->getMorphObject()->setTileOffsetX(512.0f);

		/*offsetX = (p->getX()+32) - (p->getMorphObject()->getX()+8);
		p->m_velocityY = offsetX*0.75f*(-p->m_velocityX*0.05f);*/
	}
	if (p->getIsPressingJump() ||
		(p->getIsFacingLeft() == false && posDiffX >= 50.0f && posDiffX <= 100.0f) ||
		(p->getIsFacingLeft() == true && posDiffX >= -100.0f && posDiffX <= -50.0f)) {
		p->setIsInSwing(false);
	}

	if (!p->getIsInSwing()) {

		
		std::cout << "Dropped swing\n";



		if (/*posDiffX >= -60.0f && */posDiffX <= -50.0f) {
			p->setVelocityY(-4.75f);
		} else if (posDiffX >= -50.0f && posDiffX <= -40.0f) {
			p->setVelocityY(-4.8f);
		} else if (posDiffX >= -40.0f && posDiffX <= -30.0f) {
			p->setVelocityY(-4.85f);
		} else if (posDiffX >= -30.0f && posDiffX <= -20.0f) {
			p->setVelocityY(-4.9f);
		} else if (posDiffX >= -20.0f && posDiffX <= -10.0f) {
			p->setVelocityY(-4.95f);
		} else if (posDiffX >= -10.0f && posDiffX <= -5.0f) {
			p->setVelocityY(-5.0f);
		}

		else if (posDiffX >= -5.0f && posDiffX <= 5.0f) {
			p->setVelocityY(-5.0f);
		}

		else if (posDiffX >= 5.0f && posDiffX <= 10.0f) {
			p->setVelocityY(-5.0f);
		} else if (posDiffX >= 10.0f && posDiffX <= 20.0f) {
			p->setVelocityY(-4.95f);
		} else if (posDiffX >= 20.0f && posDiffX <= 30.0f) {
			p->setVelocityY(-4.9f);
		} else if (posDiffX >= 30.0f && posDiffX <= 40.0f) {
			p->setVelocityY(-4.85f);
		} else if (posDiffX >= 40.0f && posDiffX <= 50.0f) {
			p->setVelocityY(-4.8f);
		} else if (posDiffX >= 50.0f /*&& posDiffX <= 60.0f*/) {
			p->setVelocityY(-4.75f);
		}

		if (!p->getIsPressingLeft() && !p->getIsPressingRight()) {
			p->setVelocityY(p->getVelocityY() * 1.25f);
		} else {
			p->setVelocityX(p->getVelocityX() * 1.25f);
		}

		std::cout << p->getVelocityY() << "\n";
		cSoundsManager::play(eSoundTag::swingDetach);
		cSoundsManager::play(eSoundTag::jump);

		p->setIsHidden(false);
		p->setNumJumps(0);
		p->setIsInSwing(false);

		p->getMorphObject()->setIsHidden(true);
		p->getMorphObject()->setIsFacingLeft(false);

		p->getMorphObject()->loadConfig("Data\\Objects\\swing.cfg");
		p->getMorphObject()->setOrigin(0.0f, 0.0f);		
		p->getMorphObject()->update(0.0f);

		p->setState(new cPlayerGrassState);
		
	}
}