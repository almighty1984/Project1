 #include "Object.h"
#include "Particle.h"
//#include "InputManager.h"
#include "RenderingManager.h"
#include "SoundsManager.h"
#include "SavesManager.h"
#include "SoundBufferManager.h"
#include "TextureManager.h"


#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

cParticle::cParticle() :	m_delay(0),	/*m_offsetX(0), m_offsetY(0),	*//*m_oldOffsetX(0), m_oldOffsetY(0),*/
							m_doGravitate(false), m_doSpawnNewParticle(false), m_isBaggenHiding(false) {
	
	//std::cout << "cParticle()\n";
	//m_type = "p_melee";
}

//cParticle::~cParticle() {
//}

void cParticle::die(cBaseObject *killer) {
	if (killer == nullptr) {
		return;
	}
	m_isDead = true;
}


void cParticle::hitGround(cBaseObject* object) {
	if (object == nullptr || m_isOnGround || m_doRemove || m_isDead) {
		return;
	}
	//std::cout << "cParticle::hitGround" << object->getType() << "\n";
	m_isOnGround = true;
	m_doGravitate = false;
	m_isIdle = false;
	m_isDead = true;
	m_velocityX = 0.0f;
	m_velocityY = 0.0f;
	m_fallVelocity = 0.0f;
	m_fallAcc = 0.0f;

	//m_doRemove = true;

	//m_timeBeingAlive = 0.0f;
	//m_timeToBeAlive = 10.0f;
	//loadConfig("Data\\Particles\\p_dust_grass.cfg");
	float offsetY = -3.0f;
	if (object->getType().substr(0, 11) == "slope_L_2x1") {
		setOrigin(8.0f, 8.0f);
		setRotation(-26.565f);
		setX(m_x + m_width / 2 - 8);
		if (object->getType().substr(11, 2) == "_0") {
			setY(offsetY - 2 + object->getBottom() - m_slopeOffsetX * 0.5f);
		} else if (object->getType().substr(11, 2) == "_1") {
			setY(offsetY - 2 + object->getBottom() - m_slopeOffsetX * 0.5f - 8);
		}
	} else if (object->getType().substr(0, 11) == "slope_R_2x1") {
		setOrigin(8.0f, 8.0f);
		setRotation(26.565f);
		setX(m_x + m_width / 2 + 8);
		if (object->getType().substr(11, 2) == "_0") {
			setY(offsetY + object->getTop() + m_slopeOffsetX * 0.5f);
		} else if (object->getType().substr(11, 2) == "_1") {
			setY(offsetY + object->getTop() + m_slopeOffsetX * 0.5f + 8);
		}
	} else if (object->getType() == "slope_L_1x1") {
		setOrigin(8.0f, 8.0f);
		setRotation(-45.0f);
		setX(m_x + m_width / 2 - 8);
		setY(offsetY + object->getBottom() - m_slopeOffsetX);
	} else if (object->getType() == "slope_R_1x1") {
		setOrigin(8.0f, 8.0f);
		setRotation(45.0f);
		setX(m_x + m_width / 2 + 8);
		setY(offsetY + object->getTop() + m_slopeOffsetX);
	} else {
		//setIsHidden(true);
		//setX(m_x + m_width / 2);
		setY(object->getTop() - m_height);
	}
	//update(0.0f);


	m_tileOffsetX = 0.0f;
}

void cParticle::loadConfig(std::string fileName) {
	std::ifstream dataFile( fileName.c_str() );

	  // Verify the data file was opened; exit if not.
	if ( !dataFile ) {
		std::cout << "Error:  Cannot open file " << fileName << "\n";
		//exit( 1 );
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
				if (firstField == "velocityX") {
					m_velocityX = (float)atof( data.c_str() );
					m_startVelocityX = m_velocityX;
				} else if (firstField == "velocityY") {
					if (data.at(0) == '-') {
						data.erase(data.begin(), data.begin()+1);
						m_velocityY = -(float)atof( data.c_str() );						
					} else {
						m_velocityY = (float)atof( data.c_str() );
					}
					m_startVelocityY = m_velocityY;
				} else if (firstField == "fallVelocity") {
					m_fallVelocity = (float)atof( data.c_str() );
				} else if (firstField == "fallAcc") {
					m_fallAcc = (float)atof( data.c_str() );
				} else if (firstField == "delay") {
					m_delay = atoi( data.c_str() );
				} else if (firstField == "timeToBeAlive") {
					m_timeToBeAlive = (float)atof( data.c_str() );
				} else if (firstField == "timeToBeDead") {
					m_timeToBeDead = (float)atof(data.c_str());
				} else if (firstField == "offsetX" && m_offsetX == 0.0f) {
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
				} else if (firstField == "type") {
					m_type = data;
				} else if (firstField == "isAnim" || firstField == "isAnimation") {
					if (data == "true") {
						m_isAnim = true;
					} else {
						m_isAnim = false;
					}
				} else if (firstField == "isHidden") {
					if (data == "true") {
						m_isHidden = true;
					} else {
						m_isHidden = false;
					}
				} else if (firstField == "type") {
					m_type = data;
				} else if (firstField == "doGravitate") {
					if (data == "true") {
						m_doGravitate = true;
					} else {
						m_doGravitate = false;
					}
				} else if (firstField == "hurtSleepDelay") {
					m_hurtSleepDelay = (float)atof(data.c_str());
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
					m_subtractLeft = atoi( data.c_str() );
				} else if (firstField == "subtractRight") {
					m_subtractRight = atoi( data.c_str() );
				} else if (firstField == "subtractUp") {
					m_subtractUp = atoi( data.c_str() );
				} else if (firstField == "subtractDown") {
					m_subtractDown = atoi( data.c_str() );
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
		} else if (firstField == "Animation" || firstField == "Anim") {
			m_tileOffsetX = 0.0f;
			m_tileOffsetY = 0.0f;
			m_isAnim = true;
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
			}
		}
	}
	dataFile.close();
}

void cParticle::update(float time) {
	if (m_isLocked) {
		m_velocityX = 0.0f;
		m_velocityY = 0.0f;
		return;
	}

	if (m_isDead) {
		//setIsSolid(false);
		m_velocityY = 0.0f;
		m_velocityX = 0.0f;
		m_timeBeingDead += time;
		if (m_timeBeingDead > m_timeToBeDead) {
			m_isDead = false;
			m_doRemove = true;
		}
	} else {
		//if (m_timeToBeAlive != 0.0f) {
			m_timeBeingAlive += time;
			if (m_timeBeingAlive > m_timeToBeAlive) {
				m_isDead = true;
			}
		//}
	}

	if (m_doGravitate) {
		if (m_velocityY >= m_fallVelocity) {
			m_velocityY = m_fallVelocity;
		} else {
			m_velocityY += m_fallAcc;
		}
	}


	m_previousX = m_x;
	m_previousY = m_y;
	m_previousLevelX = m_levelX;
	m_previousLevelY = m_levelY;


	//std::cout << m_offsetX << "\n";
	m_x = m_x/*+m_offsetX*/+m_velocityX+m_movedVelocityX;
	m_y = m_y/*+m_offsetY*/ + m_velocityY+m_movedVelocityY;
	

	if (m_attachedLevel != nullptr) {
		m_levelX = m_startX + (m_x - m_startX) + m_attachedLevel->getX();
		m_levelY = m_startY + (m_y - m_startY) + m_attachedLevel->getY();

		if (m_levelY >= m_attachedLevel->getNumRows()*16) {
			m_doRemove = true;
		}
	}
	
	//std::cout << "cParticle::update " << m_levelX << "\n";
	if (m_isAnim) {
		if (m_isDead) {
			setAnim(eAnimTag::death);
		} else {
			setAnim(eAnimTag::idle);
		}
		if (m_animTime >= 10.0f) {
			m_tileOffsetX += m_width;
			if (m_tileOffsetX >= (m_width * m_numAnimFrames - m_width)) {
				if (m_currentLoops < m_numAnimLoops && m_numAnimLoops != 0) {
					m_tileOffsetX = (float)(m_width * m_numAnimFrames - m_width);
					m_currentLoops += 1;
				} else if (m_numAnimLoops == 0) {
					m_tileOffsetX = 0.0f;
					m_currentLoops = 0;
				}
			}
			m_animTime = 0.0f;
		} else {
			m_animTime += m_animSpeed;
		}

		if (m_tileOffsetX >= (m_width * m_numAnimFrames) - m_width) {
			m_tileOffsetX = (float)(m_width * m_numAnimFrames - m_width);
		}
		if (m_tileOffsetX <= 0.0f) {
			m_tileOffsetX = 0.0f;
		}
	}
	
	m_sprite.setPosition(m_x, m_y);
	m_sprite.setTextureRect((int)m_tileOffsetX, (int)m_tileOffsetY, m_width, m_height);	
}