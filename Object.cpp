#include "Object.h"

//#include "ObjectIdleState.h"

#include "InputManager.h"
#include "SoundBufferManager.h"
#include "RenderingManager.h"
#include "SoundsManager.h"
#include "TextureManager.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream> 

cObject::cObject() :	m_joyMovedX(0.0f), m_joyMovedY(0.0f),
						m_joyMovedCooldownX(0.0f), m_joyMovedCooldownY(0.0f),										
						/*m_particleOffsetX(0), m_particleOffsetY(0),
						m_particleVelocityX(0.0f),*/
						m_dontChangeAnimation(false),						
						m_hasMoved(false),
						m_doUseShader(false),
						m_doUseGravity(false),
						m_isLockedMove(false), m_isLockedOpen(false),
						/*m_isCoin(false),*/
						m_pathShader("") {
	for (unsigned short i = 0; i < 323; ++i) {
		keysHeld[i] = false;
		joyButtonsHeld[i] = false;
		mouseButtonsHeld[i] = false;
	}

	m_tileOffsetX = 0.0f;
	m_tileOffsetY = 0.0f;
	m_spriteOffsetX = 0.0f;
	m_spriteOffsetY = 0.0f;
	m_animSpeed = 0;
	m_numAnimLoops = 0;	
}

cObject::cObject(const cObject& other)	:	cBaseObject(other),											
											m_joyMovedX(other.m_joyMovedX),
											m_joyMovedY(other.m_joyMovedY),
											m_joyMovedCooldownX(other.m_joyMovedCooldownX),
											m_joyMovedCooldownY(other.m_joyMovedCooldownY),
											/*m_particleOffsetX(other.m_particleOffsetX),
											m_particleOffsetY(other.m_particleOffsetY),
											m_particleVelocityX(other.m_particleVelocityX),*/
											m_dontChangeAnimation(other.m_dontChangeAnimation),											
											m_hasMoved(other.m_hasMoved),
											m_doUseShader(other.m_doUseShader),
											m_doUseGravity(other.m_doUseGravity),
											m_isLockedMove(other.m_isLockedMove), m_isLockedOpen(other.m_isLockedOpen),
											/*m_isCoin(other.m_isCoin),*/
											m_pathShader(other.m_pathShader) {

}

cObject& cObject::operator =(const cObject& other) {
	cBaseObject::operator =(other);	
	m_joyMovedX = other.m_joyMovedX;
	m_joyMovedY = other.m_joyMovedY;
	m_joyMovedCooldownX = other.m_joyMovedCooldownX;
	m_joyMovedCooldownY = other.m_joyMovedCooldownY;
	/*m_particleOffsetX = other.m_particleOffsetX;
	m_particleOffsetY = other.m_particleOffsetY;
	m_particleVelocityX = other.m_particleVelocityX;*/
	m_dontChangeAnimation = other.m_dontChangeAnimation;	
	m_hasMoved = other.m_hasMoved;
	m_doUseShader = other.m_doUseShader;
	m_doUseGravity = other.m_doUseGravity,	
	m_isLockedMove = other.m_isLockedMove;
	m_isLockedOpen = other.m_isLockedOpen;
	/*m_isCoin = other.m_isCoin,	*/
	m_pathShader = other.m_pathShader;
	/*m_isMorphable = other.m_isMorphable;*/	
	m_isInSlope = other.m_isInSlope;
	m_numHealth = other.m_numHealth;
	
    return *this;
}

cObject::~cObject() {	
	m_connectedObjects.clear();
	//m_imagePath.clear();
	//m_attachedLevel = nullptr;
}


void cObject::setIsLocked(bool isLocked) {
	m_isLocked = isLocked;
}

void cObject::loadConfig(std::string fileName) {
	std::ifstream dataFile( fileName.c_str() );

	  // Verify the data file was opened; exit if not.
	if (!dataFile) {
		std::cout << "Error:  Cannot open file " << fileName << "\n";
		std::cout << m_x/16 << " " << m_y/16 << "\n";
		//exit( 1 );
		fileName = "Data\\Objects\\clip.cfg";
		dataFile.open(fileName.c_str());
	} 

	std::istringstream iStr(std::ios_base::out);
	char buf[ 80 ] = {0};
	std::string firstField;
	std::string secondField;
	std::string data;
	std::string data2;
	std::string data3;

	while (!dataFile.eof() ) {	
		dataFile.getline( buf, sizeof( buf ) );

		iStr.str(std::string(buf));
		iStr >> firstField >> secondField;
		iStr.clear();
		iStr.str("");

		if (firstField == "Config") {
			while (dataFile.peek() != '}' ) {
				dataFile.getline( buf, sizeof( buf ) );

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data;
				iStr.clear();
				iStr.str("");

				if (firstField == "type") {
					m_type = data;
				} else if (firstField == "isUpdatedEveryFrame") {
					if (data == "true" || data == "True" || data == "TRUE") {
						m_isUpdatedEveryFrame = true;
					} else {
						m_isUpdatedEveryFrame = false;
					}
				} else if (firstField == "health") {
					m_numHealth = (float)atof(data.c_str());
				} else if (firstField == "isDead") {
					if (data == "true" || data == "True" || data == "TRUE") {
						m_isDead = true;
					} else {
						m_isDead = false;
					}
				} else if (firstField == "isHidden") {
					if (data == "true" || data == "True" || data == "TRUE") {
						m_isHidden = true;
					} else {
						m_isHidden = false;
					}
				} else if (firstField == "isLight") {
					if (data == "true" || data == "True" || data == "TRUE") {
						m_isLight = true;
					} else {
						m_isLight = false;
					}
				} else if (firstField == "isSlope") {
					if (data == "true" || data == "True" || data == "TRUE") {
						m_isSlope = true;
					} else {
						m_isSlope = false;
					}
				} else if (firstField == "isFacingLeft") {
					if (data == "true" || data == "True" || data == "TRUE") {
						m_isFacingLeft = true;
					} else {
						m_isFacingLeft = false;
					}
				} else if (firstField == "isAnim" || firstField == "isAnimation") {
					if (data == "true" || data == "True" || data == "TRUE") {
						m_isAnim = true;
					} else {
						m_isAnim = false;
					}
				} else if (firstField == "isRideable") {
					if (data == "true" || data == "True" || data == "TRUE") {
						m_isRideable = true;
					} else {
						m_isRideable = false;
					}
				} /*else if (firstField == "isMorphable") {
					if (data == "true" || data == "True" || data == "TRUE")
						m_isMorphable = true;
					else {
						m_isMorphable = false;
					}
				} */else if (firstField == "isUsingFloatPosition") {
					if (data == "true" || data == "True" || data == "TRUE") {
						m_isUsingFloatPosition = true;
					} else {
						m_isUsingFloatPosition = false;
					}
				} else if (firstField == "hurtAgainDelay") {
					m_hurtAgainDelay = (float)atof(data.c_str());
					m_hurtAgainDelayValue = 0.0f;
				} else if (firstField == "tileOffsetX") {
					m_tileOffsetX = (float)atof( data.c_str() );
				} else if (firstField == "tileOffsetY") {
					m_tileOffsetY = (float)atof( data.c_str() );
				} else if (firstField == "timeToBeDead") {
					m_timeToBeDead = (float)atof( data.c_str() );
				} else if (firstField == "timeToBeIdle") {
					m_timeToBeIdle = (float)atof(data.c_str());
				} else if (firstField == "doUseGravity") {
					if(data == "true") {
						m_doUseGravity = true;
					} else if(data == "false") {
						m_doUseGravity = false;
					} else {
						std::cout << "doUseGravity illegal value " << data << "\n";					
					}
				} else if (firstField == "offsetX") {
					if (data.at(0) == '-') {
						data.erase(data.begin(), data.begin() + 1);
						m_offsetX = -atoi(data.c_str());
					} else {
						m_offsetX = atoi(data.c_str());
					}
				} else if (firstField == "offsetY") {
					if (data.at(0) == '-') {
						data.erase(data.begin(), data.begin()+1);
						m_offsetY = -atoi( data.c_str() );						
					} else {
						m_offsetY = atoi( data.c_str() );
					}
				}
			}
		} else if (firstField == "Image") {
			while (dataFile.peek() != '}' ) {
				dataFile.getline( buf, sizeof( buf ) );

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data;
				iStr.clear();
				iStr.str("");

				if (firstField == "path") {
					setImagePath( data );
				} else if (firstField == "width") {
					m_width = atoi( data.c_str() );
				} else if (firstField == "height") {
					m_height = atoi( data.c_str() );
				}
			}
		} else if (firstField == "Collision") {
			while (dataFile.peek() != '}' ) {
				dataFile.getline( buf, sizeof( buf ) );

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data;
				iStr.clear();
				iStr.str("");
				bool isTrue = false;
				if (data == "true" || data == "True" || data == "TRUE") {
					isTrue = true;
				}

				if (firstField == "isSolid") {
					if (isTrue) {
						m_isSolidEntityX = m_isSolidEntityY = true;
						m_isSolidPlayerX = m_isSolidPlayerY = true;
						m_isSolidLevelX = m_isSolidLevelY = true;
					} else {
						m_isSolidEntityX = m_isSolidEntityY = false;
						m_isSolidPlayerX = m_isSolidPlayerY = false;
						m_isSolidLevelX = m_isSolidLevelY = false;
					}
				} else if (firstField == "isSolidX") {
					if (isTrue) {
						m_isSolidEntityX = m_isSolidPlayerX = m_isSolidLevelX = true;
					} else {
						m_isSolidEntityX = m_isSolidPlayerX = m_isSolidLevelX = false;
					}
				} else if (firstField == "isSolidY") {
					if (isTrue) {
						m_isSolidEntityY = m_isSolidPlayerY = m_isSolidLevelY = true;
					} else {
						m_isSolidEntityY = m_isSolidPlayerY = m_isSolidLevelY = false;
					}
				} else if (firstField == "isSolidEntity") {
					if (isTrue) {
						m_isSolidEntityX = m_isSolidEntityY = true;
					} else {
						m_isSolidEntityX = m_isSolidEntityY = false;
					}
				} else if (firstField == "isSolidEntityX") {
					if (isTrue) {
						m_isSolidEntityX = true;
					} else {
						m_isSolidEntityX = false;
					}
				} else if (firstField == "isSolidEntityY") {
					if (isTrue) {
						m_isSolidEntityY = true;
					} else {
						m_isSolidEntityY = false;
					}
				} else if (firstField == "isSolidPlayer") {
					if (isTrue) {
						m_isSolidPlayerX = m_isSolidPlayerY = true;
					} else {
						m_isSolidPlayerX = m_isSolidPlayerY = false;
					}
				} else if (firstField == "isSolidPlayerX") {
					if (isTrue) {
						m_isSolidPlayerX = true;
					} else {
						m_isSolidPlayerX = false;
					}
				} else if (firstField == "isSolidPlayerY") {
					if (isTrue) {
						m_isSolidPlayerY = true;
					} else {
						m_isSolidPlayerY = false;
					}
				} else if (firstField == "isSolidLevel") {
					if (isTrue) {
						m_isSolidLevelX = m_isSolidLevelY = true;
					} else {
						m_isSolidLevelX = m_isSolidLevelY = false;
					}
				} else if (firstField == "isSolidLevelX") {
					if (isTrue) {
						m_isSolidLevelX = true;
					} else {
						m_isSolidLevelX = false;
					}
				} else if (firstField == "isSolidLevelY") {
					if (isTrue) {
						m_isSolidLevelY = true;
					} else {
						m_isSolidLevelY = false;
					}
				} else if (firstField == "subtractLeft") {
					if (data.at(0) == '-') {
						data.erase(data.begin(), data.begin() + 1);
						m_subtractLeft = -atoi(data.c_str());
					} else {
						m_subtractLeft = atoi(data.c_str());
					}
					m_startSubtractLeft = m_subtractLeft;
				} else if (firstField == "subtractRight") {
					if (data.at(0) == '-') {
						data.erase(data.begin(), data.begin() + 1);
						m_subtractRight = -atoi(data.c_str());
					} else {
						m_subtractRight = atoi(data.c_str());
					}
					m_startSubtractRight = m_subtractRight;
				} else if (firstField == "subtractUp") {
					if (data.at(0) == '-') {
						data.erase(data.begin(), data.begin() + 1);
						m_subtractUp = -atoi(data.c_str());
					} else {
						m_subtractUp = atoi(data.c_str());
					}
					m_startSubtractUp = m_subtractUp;
				} else if (firstField == "subtractDown") {
					if (data.at(0) == '-') {
						data.erase(data.begin(), data.begin() + 1);
						m_subtractDown = -atoi(data.c_str());
					} else {
						m_subtractDown = atoi(data.c_str());
					}
					m_startSubtractDown = m_subtractDown;
				}
			}
		} else if (firstField == "Animation" || firstField == "Anim") {
			//m_isAnim = true;
			//m_tileOffsetX = 0.0f;
			//m_tileOffsetY = 0.0f;
			while (dataFile.peek() != '}' ) {
				dataFile.getline( buf, sizeof( buf ) );

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data >> data2 >> data3;
				iStr.clear();
				iStr.str("");

				if (firstField == "numFrames") {
					m_numAnimFrames = atoi(data.c_str());
				}
				if (firstField != "numFrames") {
					createAnim(firstField, atoi(data.c_str()), (float)atof(data2.c_str()), atoi(data3.c_str()));
				}
				setAnim(eAnimTag::idle);
				m_currentLoops = 1;
			}
		} else if (firstField == "Shader") {
			//m_doUseShader = true;			
			while (dataFile.peek() != '}' ) {
				dataFile.getline( buf, sizeof( buf ) );

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data >> data2 >> data3;
				iStr.clear();
				iStr.str("");

				if (firstField == "path") {
					m_pathShader = data;
					m_shader.load(data, "Fragment");
					//m_sfShader.loadFromFile(m_pathShader, sf::Shader::Type::Fragment);
				}
			}
		}
	} 

	dataFile.close();		
}

void cObject::setX(float positionX) {	
	m_previousX = m_x;
	m_x = positionX;	
}

void cObject::setY(float positionY) {	
	m_previousY = m_y;
	m_y = positionY;	
}

void cObject::live() {
	setAnim(eAnimTag::idle);
	m_isDead = false;
	m_isAnim = true;
	
	for (auto it = m_connectedObjects.begin(); it != m_connectedObjects.end(); ++it) {
		if ((*it) != nullptr && !m_connectedObjects.empty() && (*it) != this) {
			//if ((*it)->getAnim() == (*it)->getAnim(eAnimTag::death)) {
				(*it)->live();
			//}
		}
	}
	m_tileOffsetX = 0.0f;
}

void cObject::die(cBaseObject *killer) {	
	setAnim(eAnimTag::death);
	m_isDead = true;
	m_isAnim = true;
	
	for (auto it = m_connectedObjects.begin(); it != m_connectedObjects.end(); ++it) {
		if ((*it) != nullptr && !m_connectedObjects.empty() && (*it) != this) {
			//if ((*it)->getAnimTag() == eAnimTag::idle) {
				(*it)->die(killer);
			//}
		}
	}
	m_tileOffsetX = 0.0f;
}

void cObject::hit(float positionX, float positionY) {
	if (m_isHurting) {
		return;
	}
	cSoundsManager::stop(eSoundTag::hit);
	cSoundsManager::play(eSoundTag::hit);

	cLevel *level = m_attachedLevel;
	if (level == nullptr) { return; }

	level->addParticle(new cParticle);
	
	level->getParticleLast()->loadConfig("Data\\Particles\\p_hit.cfg");
	level->getParticleLast()->attachParent(this);
	level->getParticleLast()->setX(positionX - level->getParticleLast()->getWidth() / 2);
	level->getParticleLast()->setY(positionY - level->getParticleLast()->getHeight() / 2);
	/*if (getX() + getWidth() / 2 < object->getX() + object->getWidth() / 2) {
		level->getParticleLast()->setX(getX() + getWidth() / 2 + level->getParticleLast()->getOffsetX());
	}
	else {
		level->getParticleLast()->setX(getX() + getWidth() / 2 + level->getParticleLast()->getOffsetX() - 32);
	}
	level->getParticleLast()->setY(getY() + getHeight() / 2 + level->getParticleLast()->getOffsetY());*/
	int randNum = (rand() % 7) * 32;
	//std::cout << "randNum: " << randNum << "\n";
	level->getParticleLast()->setTileOffsetX((float)randNum);
	level->getParticleLast()->setTileOffsetY(0.0f);
	level->getParticleLast()->setIsHidden(false);
	level->getParticleLast()->update(0.0f);
}

void cObject::hurt(cBaseObject *hurter, float amount) {
	
}

//void cObject::collisionReactionX(cBaseObject *object) {
//	
//}
//
//void cObject::collisionReactionY(cBaseObject *object) {
//	
//}

void cObject::update(float time) {
	if (m_hurtAgainDelayValue > 0.0f) {
		std::cout << "cObject::update " << m_type << " is hurting " << m_hurtAgainDelayValue << "\n";
		m_isHurting = true;
		m_hurtAgainDelayValue -= time;
		m_doUseShader = true;
	} else {
		m_isHurting = false;
		m_hurtAgainDelayValue = 0.0f;
		m_doUseShader = false;
		//std::cout << m_hurtAgainDelayValue << "\n";
	}

	if (m_isDead && m_timeToBeDead != 0.0f) {
		setAnim(eAnimTag::death);
		m_timeBeingDead += time;
		if (m_timeBeingDead > m_timeToBeDead) {
			setAnim(eAnimTag::idle);
			//std::cout << "NOT DEAD ANYMORE!!!\n";
			m_isDead = false;
			m_timeBeingDead = 0.0f;
			m_isHidden = false;
			m_tileOffsetX = 0.0f;
			m_currentLoops = 0;
			m_animTime = 0.0f;
			m_isAnim = true;
		}
	}
	if (m_isAnim) {		
		// Change animation frame
		if (m_animTime >= 10.0f) {
			m_tileOffsetX += m_width;
			m_animTime = 0.0f;

			// Go back to first frame
			if (m_tileOffsetX >= m_width*m_numAnimFrames) {
				if (m_currentLoops < m_numAnimLoops || m_numAnimLoops == 0) {
					m_tileOffsetX = 0.0f;
					++m_currentLoops;
				} else {
					m_isAnim = false;
					m_tileOffsetX = (float)(m_width*m_numAnimFrames - m_width);
				}
			}
		} else {
			m_animTime += m_animSpeed;
		}
	}
	
	if (m_doUseGravity) {
		if (m_velocityY >= 5.0f) {
			m_velocityY = 5.0f;
		} else {
			m_velocityY += 0.2f;
		}
	}

	m_previousX = m_x;
	m_previousY = m_y;
	/*m_previousLevelX = m_levelX;
	m_previousLevelY = m_levelY;*/

	m_x += m_velocityX;
	m_y += m_velocityY;
	if (m_attachedLevel != nullptr) {
		m_levelX = m_startX + (m_x - m_startX) + m_attachedLevel->getX();
		m_levelY = m_startY + (m_y - m_startY) + m_attachedLevel->getY();
	}

	//m_offsetX = (int)m_levelX - m_startX;
	//m_offsetY = (int)m_levelY - m_startY + 16 - m_height;

	/*if(m_x == m_previousX && m_y == m_previousY)
		m_hasMoved = false;
	else
		m_hasMoved = true;*/
	if (m_velocityX == 0.0f && m_velocityY == 0.0f) {
		m_hasMoved = false;
	} else {
		m_hasMoved = true;
	}

	m_sprite.setPosition(m_x+m_spriteOffsetX, m_y+m_spriteOffsetY);
	m_sprite.setTextureRect((int)m_tileOffsetX, (int)m_tileOffsetY, m_width, m_height);

	//m_isIdle = true;	

	// Deceleration when we are on ground
	//if (m_isIdle == true) {
		if (m_velocityY >= 0.0f && m_velocityY <= 0.2f) {		
			// Deceleration when you have stopped running to the right
			if (m_velocityX > 0.0f) {
				m_velocityX -= 0.2f;
			}
			// Deceleration when you have stopped running to the left
			if (m_velocityX < 0.0f) {
				m_velocityX += 0.2f;
			}
		}
	//}

	// Stop at very small velocity
	//if (m_isIdle == true) {
		if (m_velocityX > -0.2f && m_velocityX < 0.2f) {
			m_velocityX = 0.0f;
		}
	//}
	
}

void cObject::setDontChangeAnimation(bool dontChangeAnimation) {
	m_dontChangeAnimation = dontChangeAnimation;

	for (auto it = m_connectedObjects.begin(); it != m_connectedObjects.end(); ++it) {
		(*it)->setDontChangeAnimation(dontChangeAnimation);
	}
}