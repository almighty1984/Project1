#include "PlayerWaterState.h"
#include "SoundsManager.h"
#include "InputManager.h"

#include <iostream>

cPlayerWaterState::cPlayerWaterState() {
	m_secondCall = false;
}

cPlayerWaterState::~cPlayerWaterState() {

}


//void cPlayerGrassState::loadConfig(char *fileName)
//{
//
//}

//cPlayerWaterState::cPlayerWaterState()
//{	
//	std::cout << "PlayerWaterState\n";
//}
//
//cPlayerWaterState::~cPlayerWaterState()
//{
//	std::cout << "~PlayerWaterState\n";
//}

//void cPlayerWaterState::enter(cPlayer *player, cPlayerState* previousState)
//{
//
//}

void cPlayerWaterState::update(cApp *app, cPlayer *p, float time) {
	if (p == nullptr || app == nullptr || p->getIsInShop()) {
		return;
	}
	
	if (m_secondCall == false) {
		m_secondCall = true;
		p->setTimerState(0.0f);
		//p->setDoPlayMusic1(true);
		//p->setDoPlayMusic0(false);

		p->setIsInWaterJump(false);
		p->setIsInWater(true);
		p->setSubtractUp(36);
		p->setSubtractDown(8);

		
		p->setTimeBeingIdle(0.0f);
		std::cout << "cPlayerWaterState" << "\n";
		p->setImagePath("Data\\Players\\Images\\player_roten_swim.png");
		

		p->setAnim(eAnimTag::idle);
		p->setIsUpsideDown(false);
		p->setSpriteOffsetY(8);
		p->setTileOffsetY(576.0f);

		m_targetX = 0.0f;
		m_targetY = 0.0f;
		
		//app->setUseEventInput(false);
		std::cout << "In water" << "\n";

		//p->setRotation(15.0f);
		//p->setOrigin(p->getWidth()/2, p->getHeight()/2);
		if (cSoundsManager::isPlaying(eSoundTag::hover)) {
			cSoundsManager::stop(eSoundTag::hover);
		}
		if (!cSoundsManager::isPlaying(eSoundTag::splash) && p->getTimeBeingAlive() > 20.0f) {
			cSoundsManager::play(eSoundTag::splash);
		}

	}
	//std::cout << "cPlayerWaterState " << p->getTimerState() << "\n";
	p->setTimerState(p->getTimerState() + time);
	//std::cout << "cPlayerWaterState::update " << p->getSubtractUp() << " " << p->getStartSubtractUp() << "\n";
	/*std::cout << p->m_timerState << "\n";
	p->m_timerState += time;*/

	//std::cout << p->m_velocityX << " " << p->m_velocityY << "\n";


	p->setIsInSwing(false);
	p->setIsInWater(true);
	p->setIsInWaterJump(false);
	p->setIsPressingDownThrust(false);
	p->setIsDownThrusting(false);




	

	/*if (!p->keysHeld[cInputManager::getUpKey()] && !p->keysHeld[cInputManager::getDownKey()] &&
		!p->keysHeld[cInputManager::getLeftKey()] && !p->keysHeld[cInputManager::getRightKey()]) {
		p->setIsIdle(true);
	}*/

	/*p->m_soundWalk.Pause();
	p->m_soundRun.Pause();*/

	//bool moved = false;
	bool movingUp = false;
	bool movingDown = false;
	bool movingLeft = false;
	bool movingRight = false;
	/*bool movingLeft = false;
	bool movingRight = false;*/

	if (p->getIsPressingUp()) {
		//p->keysHeld[cInputManager::getUpKey()] = false;
		m_targetY = p->getY();
		//moved = true;
		/*movingUp = true;
		movingDown = false;*/


	}
	if (p->getIsPressingDown()) {
		//p->keysHeld[cInputManager::getDownKey()] = false;
		m_targetY = p->getY() + p->getHeight();
		//moved = true;
		/*movingUp = false;
		movingDown = true;*/

	}

	float thresholdY = 1.0f;
	float thresholdX = 1.0f;

	if (p->getVelocityY() >= thresholdY) {
		movingUp = false;
		movingDown = true;
	} else if (p->getVelocityY() <= -thresholdY) {
		movingUp = true;
		movingDown = false;
	}
	if (p->getVelocityY() < 1.0f && p->getVelocityY() > -thresholdY) {
		movingUp = false;
		movingDown = false;
	}	

	if (p->getVelocityX() <= -thresholdX) {
		movingLeft = true;
		movingRight = false;
	} else if (p->getVelocityX() >= thresholdX) {
		movingLeft = false;
		movingRight = true;
	}
	if (p->getVelocityX() < thresholdX && p->getVelocityX() > -thresholdX) {
		movingLeft = false;
		movingRight = false;
	}

	if (p->getIsPressingLeft()) {
		//p->keysHeld[cInputManager::getLeftKey()] = false;
		m_targetX = p->getX();
		//p->setIsFacingLeft(true);
		//moved = true;
	}
	if (p->getIsPressingRight()) {
		//p->keysHeld[cInputManager::getRightKey()] = false;
		m_targetX = p->getX() + p->getWidth();
		//p->setIsFacingLeft(false);
		//moved = true;
	}
	//std::cout << m_targetX << " " << m_targetY << "\n";
	double direction = atan2(m_targetY - (p->getY() + p->getHeight() / 2), m_targetX - (p->getX() + p->getWidth() / 2)) * 180 / 3.141592f;
	p->setDirection(direction);

	
	float speed = 0.0f;
	bool isMovingDiagonally = false;


	// Move slower diagonally
	if ((p->getVelocityY() < -1.5f || p->getVelocityY() > 1.5f) &&
		(p->getVelocityX() > 1.5f || p->getVelocityX() < -1.5f)) {
		/*if ((p->keysHeld[cInputManager::getLeftKey()] || p->keysHeld[cInputManager::getRightKey()] || p->m_joyMovedX > cInputManager::getJoyDeadzone() || p->m_joyMovedX < -cInputManager::getJoyDeadzone())
			&&
			(p->keysHeld[cInputManager::getUpKey()] || p->keysHeld[cInputManager::getDownKey()] || p->m_joyMovedY > cInputManager::getJoyDeadzone() || p->m_joyMovedY < -cInputManager::getJoyDeadzone())) {
			std::cout << "Moving diagonally" << "\n";*/
		isMovingDiagonally = true;
	} else {
		isMovingDiagonally = false;
	}
	//std::cout << isMovingDiagonally << "\n";
	if (/*moved == true &&*/
		p->getHasSprint() && p->getIsPressingSprint() &&
		p->getStaminaMeterValue() >= (int)(2.0f / p->getStamina()) * time) {
		p->setStaminaCounter(p->getStaminaCounter() - (2.0f / p->getStamina()) * time);

		if (isMovingDiagonally) {
			speed = 1.0f * 0.71f;
		} else {
			speed = 1.0f;
		}


		/*if ((p->keysHeld[cInputManager::getUpKey()] || p->keysHeld[cInputManager::getUpKey()]) && (p->keysHeld[cInputManager::getLeftKey()] || p->keysHeld[cInputManager::getRightKey()])) {
			speed = 0.75f*0.71f;
		}*/
	} else {
		// Move slower diagonally
		if (isMovingDiagonally) {
			speed = 0.75f * 0.71f;
		} else {
			speed = 0.75f;
		}
		/*if ((p->keysHeld[cInputManager::getUpKey()] || p->keysHeld[cInputManager::getUpKey()]) && (p->keysHeld[cInputManager::getLeftKey()] || p->keysHeld[cInputManager::getRightKey()])) {
			speed = 0.5f * 0.71f;
		}*/
	}

	//std::cout << speed << " " << p->getVelocityX() << " " << p->getVelocityY() << "\n";

	if (p->getIsPressingLeft() || p->getIsPressingRight()) {
		p->setVelocityX(p->getVelocityX() + (float)cos(p->getDirection() * 3.141592f / 180) * 0.5f);
	}
	if (p->getIsPressingUp() || p->getIsPressingDown()) {
		p->setVelocityY(p->getVelocityY() + (float)sin(p->getDirection() * 3.141592f / 180) * 0.5f);
	}
	if (p->getVelocityX() > p->getMoveVelocity() * speed) {
		p->setVelocityX(p->getMoveVelocity() * speed);
	}
	if (p->getVelocityX() < -p->getMoveVelocity() * speed) {
		p->setVelocityX(-p->getMoveVelocity() * speed);
	}
	if (p->getVelocityY() > p->getMoveVelocity() * speed) {
		p->setVelocityY(p->getMoveVelocity() * speed);
	}
	if (p->getVelocityY() < -p->getMoveVelocity() * speed) {
		p->setVelocityY(-p->getMoveVelocity() * speed);
	}

	float moveDec = p->getStartMoveDec() * 0.05f;
	// Decelerate when we've stopped moving
	if (p->getVelocityY() < -moveDec && !p->getIsPressingUp()) {
		p->setVelocityY(p->getVelocityY() + moveDec);
	}
	if (p->getVelocityY() > moveDec && !p->getIsPressingDown()) {
		p->setVelocityY(p->getVelocityY() - moveDec);
	}
	if (p->getVelocityX() < -moveDec && !p->getIsPressingLeft()) {
		p->setVelocityX(p->getVelocityX() + moveDec);
	}
	if (p->getVelocityX() > moveDec && !p->getIsPressingRight()) {
		p->setVelocityX(p->getVelocityX() - moveDec);
	}

	if (!p->getIsPressingLeft() && !p->getIsPressingRight() && !p->getIsPressingUp() && !p->getIsPressingDown()) {
		p->setIsIdle(true);
		p->setTimeBeingIdle(p->getTimeBeingIdle() + time);
	}
	
	if (movingUp || movingDown || movingLeft || movingRight) {
		p->setIsIdle(false);
		p->setTimeBeingIdle(0.0f);
	}
	
	if (p->getTimeBeingIdle() > 20.0f) {		
		p->setAnim(eAnimTag::idle);
		p->setIsUpsideDown(false);
		p->setSpriteOffsetY(8);
	} else {
		float radians = atan2(p->getVelocityY(), p->getVelocityX());

		if (radians < 0.0f) {
			radians += 3.14159265f * 2;
		}

		float degrees = radians * 180 / 3.14159265f;
		float stepDegrees = 22.5f;
		//std::cout << "cPlayerWaterState " << radians << " " << degrees << "\n";

		// Straight down
		if (degrees > 78.75f && degrees <= 101.25f) {
			// Only go if already almost straight down
			if (p->getTileOffsetY() == 512.0f && p->getVelocityY() > 2.0f) {
				p->setTileOffsetY(576.0f);
			}
		} else if (degrees > 101.25f && degrees <= 123.75f) {
			p->setIsFacingLeft(true);
			p->setTileOffsetY(512.0f);
		} else if (degrees > 123.75f && degrees <= 146.25f) {
			p->setIsFacingLeft(true);
			p->setTileOffsetY(448.0f);
		} else if (degrees > 146.25f && degrees <= 168.75f) {
			p->setIsFacingLeft(true);
			p->setTileOffsetY(384.0f);
		} 
		// Straight left
		else if (degrees > 168.75f && degrees <= 191.25f) {
			p->setIsFacingLeft(true);
			p->setTileOffsetY(64.0f);
		} else if (degrees > 191.25f && degrees <= 213.75f) {
			p->setIsFacingLeft(true);
			p->setTileOffsetY(128.0f);
		} else if (degrees > 213.75f && degrees <= 236.25f) {
			p->setIsFacingLeft(true);
			p->setTileOffsetY(192.0f);
		} else if (degrees > 236.25f && degrees <= 258.75f) {
			p->setIsFacingLeft(true);
			p->setTileOffsetY(256.0f);
		}
		// Straight up
		else if (degrees > 258.75f && degrees <= 281.25f) {
			// Only go if already almost straight up
			if (p->getTileOffsetY() == 256.0f && p->getVelocityY() < -2.0f) {
				p->setTileOffsetY(320.0f);
			}			
		} else if (degrees > 281.25f && degrees <= 303.75f) {
			p->setTileOffsetY(256.0f);
		} else if (degrees > 303.75f && degrees <= 326.25f) {
			p->setTileOffsetY(192.0f);
		} else if (degrees > 326.25f && degrees <= 348.75f) {
			p->setTileOffsetY(128.0f);
		}
		// Straight right
		else if (degrees > 348.75f && degrees <= 11.25f) {
			p->setIsFacingLeft(false);
			p->setTileOffsetY(64.0f);
		} 
		else if (degrees > 11.25f && degrees <= 33.75f) {
			p->setIsFacingLeft(false);
			p->setTileOffsetY(384.0f);
		} else if (degrees > 33.75f && degrees <= 56.25f) {
			p->setIsFacingLeft(false);
			p->setTileOffsetY(448.0f);
		} else if (degrees > 56.25f && degrees <= 78.75f) {
			p->setIsFacingLeft(false);
			p->setTileOffsetY(512.0f);
		}

	}

	// If not moving much up/down and pressing left/right, set to straight left/right animation
	if (abs(p->getVelocityY()) < 1.2f) {
		if (p->getIsPressingLeft() && p->getVelocityX() < 0.0f) {
			p->setIsFacingLeft(true);
			p->setTileOffsetY(64.0f);
		}
		if (p->getIsPressingRight() && p->getVelocityX() > 0.0f) {
			p->setIsFacingLeft(false);
			p->setTileOffsetY(64.0f);
		}
	}
	// If not moving much sideways and pressing up/down, set to straight up/down animation
	if (abs(p->getVelocityX()) < 1.2f) {
		if (p->getIsPressingUp() && p->getVelocityY() < 0.0f) {
			p->setTileOffsetY(320.0f);
		}
		if (p->getIsPressingDown() && p->getVelocityY() > 0.0f) {
			p->setTileOffsetY(576.0f);
		}
	}
	//std::cout << "cPlayerWaterState " << p->getVelocityY() << "\n";

	if (p->getVelocityX() < 0.0f) {
		p->setIsFacingLeft(true);
	}
	if (p->getVelocityX() > 0.0f) {
		p->setIsFacingLeft(false);
	}

	if (!p->getIsIdle()) {		
		p->setAnimSpeed(sqrt(p->getVelocityX()* p->getVelocityX() + p->getVelocityY() * p->getVelocityY())*2.0f);
		//std::cout << "cPlayerWaterState " << p->getAnimSpeed() << "\n";
	}
	


	/*if (!movingDown) {
		p->setIsUpsideDown(false);
		p->setSpriteOffsetY(0);
	}*/
}