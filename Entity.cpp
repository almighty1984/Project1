#include "EntityPigan.h"
#include "EntityItem.h"
//#include "InputManager.h"
#include "SoundBufferManager.h"
#include "SoundsManager.h"
#include "RenderingManager.h"

#include "ParticleBrick.h"
#include "ParticleHealth.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream> 

cEntity::cEntity() :	m_isCharging(false), m_isAttacking(false), m_isStunned(false),
						m_nextObject(0), m_number(0), i(0),
						m_startHealth(0.0f), m_slopeOffsetX(0.0f), m_startDelay(0.0f),
						m_soundIdle(""), m_soundAttack(""), 
						m_attachedPlayer(nullptr)/*m_distanceX(0.0f), m_distanceY(0.0f),*/						
{
}
	
cEntity::~cEntity() {
	m_attachedLevel = nullptr;
	m_belowObject = nullptr;
	/*for (auto it = m_particles.begin(); it != m_particles.end(); ++it) {
		cRenderingManager::removeParticle(*it);
		if (*it != nullptr) {
			delete* it;
			*it = nullptr;
		}
	}
	m_particles.clear();*/
	//m_connectedObject = nullptr;
	m_connectedObjects.clear();
	
	m_pathNumbers.clear();
	m_imagePath.clear();
}

int cEntity::getNumPathNumbers() {
	int num = (int)m_pathNumbers.size();
	return num;
}

unsigned short cEntity::getPathNumber(unsigned short i) {
	if (m_pathNumbers.empty()) {
		return 0; }
	else {
		return m_pathNumbers.at(i);
	}
}

//void cEntity::stun(unsigned short duration) {	
//	//m_velocityX = 0.0f;
//	m_particles.push_back(new cParticle);
//	level->getParticleLast()->loadConfig("Data\\Particles\\p_stun.cfg");
//	level->getParticleLast()->attachParent(this);
//	level->getParticleLast()->setX(getMiddleX() + level->getParticleLast()->getOffsetX());
//	level->getParticleLast()->setY(getMiddleY() + level->getParticleLast()->getOffsetY());
//	level->getParticleLast()->setTimeToBeAlive(duration);
//	//cRenderingManager::addParticle(l->getParticleLast());
//}
void cEntity::die(cBaseObject *killer) {
	//m_isDead = true;
	setVelocityY(0.0f);
	if (m_attachedLevel == nullptr) {
		return;
	}

	float posX = getLevelX() + getWidth() / 2 - 8;
	float posY = getLevelY() + getHeight() / 2 - 8;

	float velX = 0.0f;

	cLevel *level = m_attachedLevel;
	level->addParticle(new cParticleBrick);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_brick.cfg");
	level->getParticleLast()->attachLevel(level);
	level->getParticleLast()->setX(getMiddleX() - 8);
	level->getParticleLast()->setY(getMiddleY() - 8);
	level->getParticleLast()->setStartX(posX);
	level->getParticleLast()->setStartY(posY);
	level->getParticleLast()->setLevelX(posX);
	level->getParticleLast()->setLevelY(posY);
	level->getParticleLast()->setVelocityX(-0.71f * 2.0f + m_velocityX * 0.25f + velX);
	level->getParticleLast()->setVelocityY(-0.71f * 2.0f - 2.0f);
	level->getParticleLast()->update(0.0f);

	level->addParticle(new cParticleBrick);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_brick.cfg");
	level->getParticleLast()->attachLevel(level);
	level->getParticleLast()->setX(getMiddleX() - 8);
	level->getParticleLast()->setY(getMiddleY() - 8);
	level->getParticleLast()->setStartX(posX);
	level->getParticleLast()->setStartY(posY);
	level->getParticleLast()->setLevelX(posX);
	level->getParticleLast()->setLevelY(posY);
	level->getParticleLast()->setVelocityX(-0.71f * 2.0f + m_velocityX * 0.25f + velX);
	level->getParticleLast()->setVelocityY(0.71f * 2.0f - 2.0f);
	level->getParticleLast()->update(0.0f);

	level->addParticle(new cParticleBrick);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_brick.cfg");
	level->getParticleLast()->attachLevel(level);
	level->getParticleLast()->setX(getMiddleX() - 8);
	level->getParticleLast()->setY(getMiddleY() - 8);
	level->getParticleLast()->setStartX(posX);
	level->getParticleLast()->setStartY(posY);
	level->getParticleLast()->setLevelX(posX);
	level->getParticleLast()->setLevelY(posY);
	level->getParticleLast()->setVelocityX(0.71f * 2.0f + m_velocityX * 0.25f + velX);
	level->getParticleLast()->setVelocityY(-0.71f * 2.0f - 2.0f);
	level->getParticleLast()->update(0.0f);

	level->addParticle(new cParticleBrick);
	level->getParticleLast()->loadConfig("Data\\Particles\\p_brick.cfg");
	level->getParticleLast()->attachLevel(level);
	level->getParticleLast()->setX(getMiddleX() - 8);
	level->getParticleLast()->setY(getMiddleY() - 8);
	level->getParticleLast()->setStartX(posX);
	level->getParticleLast()->setStartY(posY);
	level->getParticleLast()->setLevelX(posX);
	level->getParticleLast()->setLevelY(posY);
	level->getParticleLast()->setVelocityX(0.71f * 2.0f + m_velocityX * 0.25f + velX);
	level->getParticleLast()->setVelocityY(0.71f * 2.0f - 2.0f);
	level->getParticleLast()->update(0.0f);

	for (int i = 0; i < 1; ++i) {
		level->addParticle(new cParticleHealth);
		level->getParticleLast()->loadConfig("Data\\Particles\\p_health.cfg");
		level->getParticleLast()->attachLevel(level);
		level->getParticleLast()->attachParent(this);
		level->getParticleLast()->setIsDead(false);
		level->getParticleLast()->setX(getX() + getWidth() / 2 - 8.0f);
		level->getParticleLast()->setY(getY() + getHeight() / 2 + 8.0f);
		level->getParticleLast()->setStartX(posX);
		level->getParticleLast()->setStartY(posY);
		level->getParticleLast()->setLevelX(posX);
		level->getParticleLast()->setLevelY(posY);
	}
}

void cEntity::hurt(cBaseObject *hurter, float amount) {
	m_tileOffsetX = 0.0f;	

	unsigned char randNum;
	randNum = (rand() % 3);
	if (randNum == 0) {
		cSoundsManager::stop(eSoundTag::fluganHurt0);
		cSoundsManager::play(eSoundTag::fluganHurt0);
	}
	else if (randNum == 1) {
		cSoundsManager::stop(eSoundTag::fluganHurt1);
		cSoundsManager::play(eSoundTag::fluganHurt1);
	}
	else if (randNum == 2) {
		cSoundsManager::stop(eSoundTag::fluganHurt2);
		cSoundsManager::play(eSoundTag::fluganHurt2);
	}

	m_numHealth = m_numHealth - amount * m_attachedPlayer->getVitality();

	std::cout << getNumHealth() << "\n" << getNumHealth() << "\n" << "\n" << "\n" << "\n";

	//hit(basicObject->getX(), basicObject->getY());
	m_hurtAgainDelayValue = m_hurtAgainDelay;
	if (getNumHealth() <= 0.0f) {
		die(hurter);
	}
}

void cEntity::setX(float positionX) {
	m_x = positionX;
}

void cEntity::setY(float positionY) {
	m_y = positionY;
}

void cEntity::setColor(unsigned char r, unsigned char g, unsigned char b) {
	if (!m_isLight) {
		m_sprite.setColor(r, g, b);
		m_meterHealth.setColor(r, g, b);
		m_meterHealthBackground.setColor(r, g, b);
	}
}

void cEntity::setState(cEntityState* state) {		
	//if(m_state != nullptr) {
	//	//m_state->exit(this);
	//	delete m_state;
	//	m_state = nullptr;
	//}

	//cPlayerState* previousState = m_state;
	//m_state->enter(this, previousState);

	m_timerState = 0.0f;

	if (m_state == state) {
		return;
	} else {
		std::cout << "delete m_state\n";
		delete m_state;
		m_state = state;
	}
}

void cEntity::addPathNumber(unsigned short pathNumber) {
	m_pathNumbers.push_back(pathNumber);
}

void cEntity::loadConfig(std::string fileName) {
	std::ifstream dataFile( fileName.c_str() );

	if (!dataFile) {
		std::cout << "Error:  Cannot open file " << fileName << "\n";
		//exit( 1 );
	} 

	std::istringstream iStr(std::ios_base::out);
	char buf[ 80 ] = {0};
	std::string firstField;
	std::string secondField;
	std::string data, data2, data3;

	while (!dataFile.eof()) {	
		dataFile.getline( buf, sizeof( buf ) );

		iStr.str(std::string(buf));
		iStr >> firstField;
		iStr.clear();
		iStr.str("");

		if (firstField == "Config") {
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

				if (firstField == "type") {
					m_type = data;
				} else if (firstField == "isHidden") {
					if (isTrue) {
						m_isHidden = true;
					} else {
						m_isHidden = false;
					}
				} else if (firstField == "isStatic") {
					if (isTrue) {
						m_isStatic = true;
					} else {
						m_isStatic = false;
					}
				} else if (firstField == "isFacingLeft") {
					if (isTrue) {
						m_isFacingLeft = true;
					} else {
						m_isFacingLeft = false;
					}
				} /*else if(firstField == "animateOnDeath") {
					if(data == "true" || data == "True" || data == "TRUE") {
						m_animateOnDeath = true;
					} else {
						m_animateOnDeath = false;
					}
				} */else if (firstField == "isRideable") {
					if (isTrue) {
						m_isRideable = true;
					} else {
						m_isRideable = false;
					}
				} else if (firstField == "doRotate") {
					if (isTrue) {
						m_doRotate = true;
					} else {
						m_doRotate = false;
					}
				} else if (firstField == "dontFlipSprite") {
					if (isTrue) {
						m_dontFlipSprite = true;
					} else {
						m_dontFlipSprite = false;
					}
				} else if (firstField == "damage") {
					m_damage = (float)atof(data.c_str());
				} else if (firstField == "animationLoop") {
					m_numAnimLoops = (int)atoi( data.c_str() );
				} else if (firstField == "hurtAgainDelay") {
					m_hurtAgainDelay = (float)atof(data.c_str());
				} else if (firstField == "hurtSleepDelay") {
					m_hurtSleepDelay = (float)atof(data.c_str());
				} else if (firstField == "health") {
					m_numHealth = (float)atof(data.c_str());
					m_startHealth = m_numHealth;
				} else if (firstField == "offsetX") {
					if (data.at(0) == '-') {
						data.erase(data.begin(), data.begin() + 1);
						m_offsetX = -atoi(data.c_str());
					} else {
						m_offsetX = atoi(data.c_str());
					}
				} else if (firstField == "offsetY" && m_offsetY == 0.0f) {
					if (data.at(0) == '-') {
						data.erase(data.begin(), data.begin() + 1);
						m_offsetY = -atoi(data.c_str());
					} else {
						m_offsetY = atoi(data.c_str());
					}
					//std::cout << m_type << " offsetY: " << m_offsetY << "\n";
				} else if (firstField == "startDelay") {
					m_startDelay = (float)atof(data.c_str());
				} else if (firstField == "timeToBeDead") {
					m_timeToBeDead = (float)atof(data.c_str());
				} else if (firstField == "timeToBeIdle") {
					m_timeToBeIdle = (float)atof(data.c_str());
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
				} else if(firstField == "height") {
					m_height = atoi( data.c_str() );				
				} else if (firstField == "shader") {
					m_pathShader = data;
				}
			}
		} else if (firstField == "Movement") {			
			while (dataFile.peek() != '}' ) {
				dataFile.getline( buf, sizeof( buf ) );

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data;
				iStr.clear();
				iStr.str("");

				if (firstField == "fallVelocity") {
					m_fallVelocity = (float)atof(data.c_str());
				} else if (firstField == "fallAcc") {
					m_fallAcc = (float)atof(data.c_str());
				} else if (firstField == "jumpForce") {
					m_jumpForce = (float)atof(data.c_str());
				} else if (firstField == "moveVelocity") {
					m_moveVelocity = (float)atof(data.c_str());
					m_startMoveVelocity = m_moveVelocity;
					//m_velocityX = m_moveVelocity;
				} else if (firstField == "moveAcc") {
					m_moveAcc = (float)atof(data.c_str());
					m_startMoveAcc = m_moveAcc;
				} else if (firstField == "moveDec") {
					m_moveDec = (float)atof(data.c_str());
					m_startMoveDec = m_moveDec;
				}
			}
		} else if (firstField == "Animation" || firstField == "Anim") {
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
				} else if (firstField == "isCircle") {
					if (isTrue) {
						m_isCircle = true;
					} else {
						m_isCircle = false;
					}
				} else if (firstField == "radius") {
					m_radius = atoi(data.c_str());
				} else if (firstField == "subtractLeft") {
					m_subtractLeft = atoi( data.c_str() );
				} else if (firstField == "subtractRight") {
					m_subtractRight = atoi( data.c_str() );
				} else if (firstField == "subtractUp") {
					m_subtractUp = atoi( data.c_str() );
				} else if (firstField == "subtractDown") {
					m_subtractDown = atoi( data.c_str() );
				}
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
		else if (firstField == "Sound") {
			while (dataFile.peek() != '}') {
				dataFile.getline(buf, sizeof(buf));

				iStr.str(std::string(buf));
				iStr >> firstField >> secondField >> data >> data2 >> data3;
				iStr.clear();
				iStr.str("");

				if (firstField == "idle") {
					m_soundIdle = data;
				}
			}
		}
	} 


	m_tileOffsetX = (float)(rand() % (m_numAnimFrames-1) * m_width);


	dataFile.close();

	/*if (m_doUseShader == true) {
		m_sfShader.loadFromFile(m_pathShader, sf::Shader::Type::Fragment);
	}*/

	m_belowObject = nullptr;
}

void cEntity::update(cApp *app, float time) {
	m_previousX = m_x;
	m_previousY = m_y;
	m_previousLevelX = m_levelX;
	m_previousLevelY = m_levelY;

	m_x += (m_velocityX + m_movedVelocityX);
	m_y += (m_velocityY + m_movedVelocityY);

	if (m_attachedLevel != nullptr) {
		m_levelX = m_startX + (m_x - m_startX) + m_attachedLevel->getX();
		m_levelY = m_startY + (m_y - m_startY) + m_attachedLevel->getY();
	}
	/*for (unsigned short i = 0; i < m_particles.size(); ++i) {
		m_particles.at(i)->update(time);

		if (m_particles.at(i)->getIsDead() == true) {
			cRenderingManager::removeParticle(m_particles.at(i));
			m_particles.erase(m_particles.begin() + i, m_particles.begin() + i + 1);
		}
	}*/
	// Death animation
	//if (m_isDead) {
	//	setAnim(eAnimTag::death);
	//} else {
	//	setAnim(eAnimTag::idle);
	//}
	// Update animation		
	if (m_animTime > 10.0f) {
		m_tileOffsetX += m_width;
		if (m_tileOffsetX > (m_width * m_numAnimFrames - m_width)) {

			m_currentLoops += 1;
			// Go through number of loops set
			if (m_currentLoops < m_numAnimLoops) {				
				m_tileOffsetX = 0.0f;
				std::cout << "Entity::update " << m_currentLoops << "\n";
			} else { // then rest at last frame
				m_tileOffsetX = (float)(m_width * m_numAnimFrames - m_width);
			}
			// Unless 0, then loop forever
			if (m_numAnimLoops == 0) {
				m_tileOffsetX = 0.0f;
				m_currentLoops = 0;
			}			
		}
		m_animTime = 0.0f;
	}
	else {
		m_animTime += m_animSpeed ;
	}

	/*if (m_tileOffsetX > (m_width * m_numAnimFrames) - m_width) {
		m_tileOffsetX = (float)(m_width * m_numAnimFrames - m_width);
	}*/

	if (m_isDead /*&& m_timeToBeDead != 0.0f*/) {
		m_timeBeingDead += time;
		setAnim(eAnimTag::death);		
		if (m_timeBeingDead > m_timeToBeDead) {
			std::cout << "NOT DEAD ANYMORE!!!\n";
			m_isDead = false;
			m_timeBeingDead = 0.0f;
			setAnim(eAnimTag::idle);
			m_currentLoops = 0;
		}
	}

	m_sprite.setPosition(m_x + m_spriteOffsetX, m_y + m_spriteOffsetY);
	m_sprite.setTextureRect((int)m_tileOffsetX, (int)m_tileOffsetY, m_width, m_height);
}