//#include "ObjectBox.h"
//#include "RenderingManager.h"
//
//cObjectBox::cObjectBox()
//:	m_offsetX(0),
//	m_offsetY(0) {
//
//}
//
//cObjectBox::~cObjectBox() {
//
//}
//
//void cObjectBox::update(float time) {
//	for (unsigned short i=0; i<m_projectiles.size(); ++i) {
//		m_projectiles.at(i)->update(time);
//
//		if (m_projectiles.at(i)->getIsDead() == true) {
//			cRenderingManager::get().removeProjectile(m_projectiles.at(i));
//			m_projectiles.erase(m_projectiles.begin()+i, m_projectiles.begin()+i+1);
//		}
//	}
//
//	if (m_useGravity == true) {
//		if (m_velocityY >= 5.0f) {
//			m_velocityY = 5.0f;
//		} else {
//			m_velocityY += 0.2f;
//		}
//	}
//
//
//	m_previousX = m_positionX;
//	m_previousY = m_positionY;
//	m_previousLevelPositionX = m_levelPositionX;
//	m_previousLevelPositionY = m_levelPositionY;
//
//	m_positionX += m_velocityX;
//	m_positionY += m_velocityY;
//	m_levelPositionX += m_velocityX;
//	m_levelPositionY += m_velocityY;
//
//	m_offsetX = (int)m_levelPositionX - m_startX;
//
//	/*if(m_positionX == m_previousX && m_positionY == m_previousY)
//		m_hasMoved = false;
//	else
//		m_hasMoved = true;*/
//	if (m_velocityX == 0.0f && m_velocityY == 0.0f) {
//		m_hasMoved = false;
//	} else {
//		m_hasMoved = true;
//	}
//
//	if (m_isAnimation == true) {	
//		//if(m_currentLoops <= m_animationLoops || m_animationLoops == 0) {
//			if (m_isDead == true) {
//				m_tileOffsetY = m_animDeath.y;
//				m_animationSpeed = m_animDeath.speed;
//				m_animationLoops = m_animDeath.loop;
//
//				if (m_deathTimeLimit != 0) {
//					m_deathTimer++;
//					if(m_deathTimer > m_deathTimeLimit) {
//						std::cout << "NOT DEAD ANYMORE!!!\n";
//						m_isDead = false;
//						m_deathTimer = 0;
//					}
//				}	
//			} else {
//				m_tileOffsetY = m_animIdle.y;
//				m_animationSpeed = m_animIdle.speed;
//				m_animationLoops = m_animIdle.loop;
//			}
//			// Update animation
//			if (m_animationTime > 1.0f) {				
//				m_tileOffsetX += m_width;
//				m_animationTime = 0.0f;
//
//				if (m_tileOffsetX >= (m_width*m_numFrames) && (m_currentLoops < m_animationLoops || m_animationLoops == 0) ) {
//					m_tileOffsetX = 0;
//					++m_currentLoops;
//				}
//			} else {
//				m_animationTime += m_animationSpeed;
//			}
//		
//	}
//
//	//if(m_isMorphable == true) {
//	//	if(m_facingLeft) {
//	//		m_sfSprite.setScale(-1.0f, 1.0f);
//	//		m_sfSprite.setPosition((int)(m_positionX-64+8+m_width), (int)(m_positionY-64+8));
//	//	}
//	//	else {
//	//		m_sfSprite.setScale(1.0f, 1.0f);
//	//		m_sfSprite.setPosition((int)(m_positionX-64+8), (int)(m_positionY-64+8));			
//	//	}
//	//}
//	//else {
//	//	if(m_useFloatPosition)
//	//		m_sfSprite.setPosition(m_positionX, m_positionY);
//	//	else
//	//		m_sfSprite.setPosition((int)m_positionX, (int)(m_positionY));
//	//}
//
//	////m_sfSprite.setColor(sf::Color(time*0.05,63,255) );
//	//m_sfSprite.setTextureRect(sf::IntRect((int)m_tileOffsetX, (int)m_tileOffsetY, m_width, m_height));
//
//	
//
//	// Deceleration when we are on ground
//	//if (m_isIdle == true) {
//		if (m_velocityY >= 0.0f && m_velocityY <= 0.2f) {		
//			// Deceleration when you have stopped running to the right
//			if (m_velocityX > 0.0f) {
//				m_velocityX -= 0.2f;
//			}
//			// Deceleration when you have stopped running to the left
//			if (m_velocityX < 0.0f) {
//				m_velocityX += 0.2f;
//			}
//		}
//	//}
//
//	// Stop at very small velocity
//	//if (m_isIdle == true) {
//		if(m_velocityX > -0.2f && m_velocityX < 0.2f) {
//			m_velocityX = 0.0f;
//		}
//	//}
//
//	m_sprite.setPosition(m_positionX, m_positionY);
//	m_sprite.setTextureRect((int)m_tileOffsetX, (int)m_tileOffsetY, m_width, m_height);
//
//	m_isIdle = true;
//}