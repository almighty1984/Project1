//#include "EntityBall.h"
//
//bool cEntityBall::collisionCheckX(cBaseObject *object) {
//	// Don't do collision testing on these tiles
//	if (!object->getIsSolidX() || object->getIsDead() == true) {
//		return false;
//	}
//
//	char slopeFix = 0;
//
//	float upSide = m_y + m_subtractUp;
//	float downSide = m_y + m_height - m_subtractDown;
//	float leftSide = 0.0f;
//	float rightSide = 0.0f;
//	float middleX = m_x + m_width / 2;
//	float objectUpSide = object->getY() + object->getSubtractUp();
//	float objectDownSide = object->getY() + object->getHeight() - object->getSubtractDown();
//	float objectLeftSide = object->getX() + object->getSubtractLeft();
//	float objectRightSide = object->getX() + object->getWidth() - object->getSubtractRight();
//	float objectMiddleX = object->getX() + object->getWidth() / 2;
//
//	if (object->getIsSlope()) {
//		//slopeOffsetX = m_slopeOffsetX;
//		//std::cout << m_slopeOffsetX << "\n";
//		slopeFix = 16;
//		m_slopeOffsetX = object->getX() + object->getWidth() - (m_x + m_width / 2);
//		leftSide = m_x + m_width / 2;
//		rightSide = m_x + m_width / 2;
//	}
//	else {
//		slopeFix = 0;
//		m_slopeOffsetX = 0.0f;
//		leftSide = m_x + m_subtractLeft;
//		rightSide = m_x + m_width - m_subtractRight;
//	}
//
//	if (m_velocityX < 0.0f) {  // Moving left
//		// Within bounding box X?
//		if (middleX > objectMiddleX && leftSide < objectRightSide) {
//			// Within bounding box Y?
//			if (downSide - 0 > objectUpSide + slopeFix - m_slopeOffsetX &&
//				upSide < objectDownSide) {
//				//m_x = object->getX()+16-10;
//				
//				//collisionReactionX(object);
//				return true;
//
//				//object->collisionReactionX(this);
//			}
//		}
//	}
//	else if (m_velocityX > 0.0f) {  // Moving right
//		// Within bounding box X?
//		if (middleX < objectMiddleX && rightSide > objectLeftSide) {
//			// Within bounding box Y?
//			if (downSide - 0 > objectUpSide + m_slopeOffsetX && upSide < objectDownSide) {
//				//collisionReactionX(object);
//				return true;
//				//object->collisionReactionX(this);
//			}
//		}
//	}
//	return false;
//}
//
//bool cEntityBall::collisionCheckY(cBaseObject *object) {
//	if (object == nullptr) {
//		return false;
//	}
//
//	if (object->getIsDead() || !object->getIsSolidX() || m_isDead) {
//		return false;
//	}
//	/*if (object->getIsSlope()) {
//		collisionCheckSlope(object);
//		return;
//	}*/
//	/*if (m_isInWater && object->getIsSlope()) {
//		collisionCheckSlope(object);
//		return;
//	}*/
//	//// AABB
//	//if((m_x+m_width < object->getX() || object->getX()+object->getWidth() < m_x ||
//	//	m_y+m_height+8 < object->getY() || object->getY()+object->getHeight() < m_y)
//	//	
//	//	// Prevent falling down slopes
//	//	&& m_isInSlope == false) {
//	//		return;
//	//}
//
//	char slopeFix = 0;
//	if ((!m_isInWater && m_velocityY <= m_fallAcc) || (m_isInWater && m_velocityY <= m_fallAcc)) {
//		slopeFix = 16;
//	}
//	char waterOffset = 0;
//
//	float upSide = m_y + m_subtractUp;
//	float downSide = m_y + m_height - m_subtractDown;
//	float leftSide = m_x + m_subtractLeft;
//	float rightSide = m_x + m_width - m_subtractRight;
//	float middleX = m_x + m_width / 2;
//	float objectUpSide = object->getY() + object->getSubtractUp();
//	float objectDownSide = object->getY() + object->getHeight() - object->getSubtractDown();
//	float objectLeftSide = object->getX() + object->getSubtractLeft();
//	float objectRightSide = object->getX() + object->getWidth() - object->getSubtractRight();
//	float objectMiddleX = object->getX() + object->getWidth() / 2;
//
//	//slopeFix = 8;
//		// Moving down
//	if (m_velocityY >= 0.0f) {
//		if (object->getIsSlope()) {
//			m_slopeOffsetX = object->getX() + object->getWidth() - (m_x + m_width / 2);
//
//			//if (m_isInWater) {
//			//	waterOffset = 4;
//			//}
//			/*if (m_isInWater) {
//				collisionCheckSlope(object);
//				return;
//			}*/
//			/*if (object->getType() == "slope_seam_L") {
//				m_slopeOffsetX = object->getX() + object->getWidth() - (m_x + m_width / 2);
//			}
//			else */
//			if (object->getType() == "slope_seam_L") {
//				if ((downSide + slopeFix) >= (object->getY() + m_slopeOffsetX) && downSide - 4 <= objectDownSide) {
//					if (middleX >= objectLeftSide && middleX <= objectRightSide) {
//						//collisionReactionY(object);
//						return true;
//					}
//				}
//			}
//			else if (object->getType() == "slope_seam_R") {
//				if ((downSide + slopeFix) >= (object->getY() + 16 - m_slopeOffsetX) && downSide - 4 <= objectDownSide) {
//					if (middleX >= objectLeftSide && middleX <= objectRightSide) {
//						//collisionReactionY(object);
//						return true;
//						/*if (m_velocityX < -(m_moveVelocity*m_sprintValue*0.7f)) {
//							m_velocityX = -m_moveVelocity*m_sprintValue*0.7f;
//						}*/
//					}
//				}
//			}
//			else if (object->getType() == "slope_L_1x1") {
//				if (downSide + slopeFix + waterOffset >= objectUpSide + m_slopeOffsetX && downSide - 4 <= objectDownSide) {
//					if (middleX >= objectLeftSide && middleX <= objectRightSide) {
//						//collisionReactionY(object);
//						return true;
//						/*if (m_velocityX > m_moveVelocity*m_sprintValue*0.7f) {
//							m_velocityX = m_moveVelocity*m_sprintValue*0.7f;
//						}*/
//					}
//				}
//			}
//			else if (object->getType() == "slope_R_1x1") {
//				if (!m_isInWater && m_velocityY < m_fallAcc) { return false; };
//
//				if (downSide + slopeFix + waterOffset >= objectUpSide + 16 - m_slopeOffsetX && downSide - 4 <= objectDownSide) {
//					if (middleX >= object->getX() && middleX <= objectRightSide) {
//						//collisionReactionY(object);
//						return true;
//						/*if (m_velocityX < -(m_moveVelocity*m_sprintValue*0.7f)) {
//							m_velocityX = -m_moveVelocity*m_sprintValue*0.7f;
//						}*/
//					}
//				}
//			}
//			else if (object->getType() == "slope_LU_1x1") {
//				if (upSide <= (objectUpSide + 16 - m_slopeOffsetX) && upSide >= objectUpSide + 16 - m_slopeOffsetX - 4) {
//					if (middleX >= object->getX() && middleX <= objectRightSide) {
//						//collisionReactionY(object);
//						return true;
//					}
//				}
//			}
//			else if (object->getType() == "slope_RU_1x1") {
//				if (upSide <= (objectUpSide + m_slopeOffsetX) && upSide >= objectUpSide + m_slopeOffsetX - 4) {
//					if (middleX >= object->getX() && middleX <= objectRightSide) {
//						//collisionReactionY(object);
//						return true;
//					}
//				}
//			}
//			else if (object->getType() == "slope_L_2x1_0") {
//				if ((downSide + slopeFix) >= (objectUpSide + 8 + m_slopeOffsetX / 2) && downSide - 16 - 4 + 8 + m_slopeOffsetX / 2 <= objectDownSide) {
//					if (middleX >= objectLeftSide && middleX <= objectRightSide) {
//						//collisionReactionY(object);
//						return true;
//						/*if (m_velocityX > m_moveVelocity*m_sprintValue*0.9f) {
//							m_velocityX = m_moveVelocity*m_sprintValue*0.9f;
//						}*/
//					}
//				}
//			}
//			else if (object->getType() == "slope_L_2x1_1") {
//				if ((downSide + slopeFix) >= (objectUpSide + m_slopeOffsetX / 2) && downSide - 16 - 4 + m_slopeOffsetX / 2 <= objectDownSide) {
//					if (middleX >= objectLeftSide && middleX <= objectRightSide) {
//						//collisionReactionY(object);
//						return true;
//						/*if (m_velocityX > m_moveVelocity*m_sprintValue*0.9f) {
//							m_velocityX = m_moveVelocity*m_sprintValue*0.9f;
//						}*/
//					}
//				}
//			}
//			else if (object->getType() == "slope_R_2x1_0") {
//				if ((downSide + slopeFix) >= (objectUpSide + 16 - 8 - m_slopeOffsetX / 2) && downSide - 4 - 8 - m_slopeOffsetX / 2 <= objectDownSide) {
//					if (middleX >= objectLeftSide && middleX <= objectRightSide) {
//						//collisionReactionY(object);
//						return true;
//						/*if (m_velocityX < -(m_moveVelocity*m_sprintValue*0.9f)) {
//							m_velocityX = -m_moveVelocity*m_sprintValue*0.9f;
//						}*/
//					}
//				}
//			}
//			else if (object->getType() == "slope_R_2x1_1") {
//				if ((downSide + slopeFix) >= (objectUpSide + 16 - m_slopeOffsetX / 2) && downSide - 4 - m_slopeOffsetX / 2 <= objectDownSide) {
//					if (middleX >= objectLeftSide && middleX <= objectRightSide) {
//						//collisionReactionY(object);
//						return true;
//						/*if (m_velocityX < -(m_moveVelocity*m_sprintValue*0.9f)) {
//							m_velocityX = -m_moveVelocity*m_sprintValue*0.9f;
//						}*/
//					}
//				}
//			}
//		}
//		else {
//			if (m_y + m_height - 6 <= objectUpSide &&
//				downSide + 2 >= objectUpSide) {
//				// If player is between the tile in X
//				if (rightSide - 7 >= objectLeftSide &&
//					leftSide + 7 <= objectRightSide) {
//					//collisionReactionY(object);
//					return true;
//				}
//			}
//		}
//	}
//	else if (m_velocityY < 0.0f) {  // Moving up
//	 //m_belowObject = nullptr;
//	 //m_isRiding = false;
//	 //if( /*object->getType() == "clip" || */
//	 //	object->getType() == "clip_top" || 
//	 //	object->getType() == "wall_in_left" || 
//	 //	object->getType() == "wall_in_left_top" || 
//	 //	object->getType() == "wall_in_left_bottom" ||
//	 //	object->getType() == "wall_in_right" ||
//	 //	object->getType() == "wall_in_right_top" ||
//	 //	object->getType() == "wall_in_right_bottom" ||
//	 //	object->getType() == "wall_out_left" || 
//	 //	object->getType() == "wall_out_right" || 
//	 //	object->getType() == "wall_out_top" ||
//	 //	object->getType() == "wall_out_bottom") {
//	 //	return;
//	 //}
//
//		if (rightSide - 4 >= objectLeftSide && leftSide + 4 <= objectRightSide) {
//			if (upSide - 4 > objectUpSide && upSide - 4 < objectDownSide) {
//				/*if (object->getType() == "slope_L_1x1") {
//					if (m_velocityX > m_moveVelocity*m_sprintValue*0.7f)
//						m_velocityX = m_moveVelocity*m_sprintValue*0.7f;
//				} else if (object->getType() == "slope_R_1x1") {
//					if (m_velocityX < -(m_moveVelocity*m_sprintValue*0.7f))
//						m_velocityX = -m_moveVelocity*m_sprintValue*0.7f;
//				} else if (object->getType() == "slope_L_2x1_0" || object->getType() == "slope_L_2x1_1") {
//					if (m_velocityX > m_moveVelocity*m_sprintValue*0.9f) {
//						m_velocityX = m_moveVelocity*m_sprintValue*0.9f;
//					}
//				} else if (object->getType() == "slope_R_2x1_0" || object->getType() == "slope_R_2x1_1") {
//					if (m_velocityX < -(m_moveVelocity*m_sprintValue*0.9f)) {
//						m_velocityX = -m_moveVelocity*m_sprintValue*0.9f;
//					}
//				} else {*/
//				//collisionReactionY(object);
//				return true;
//				//object->collisionReactionY(this);
//				//}			
//			}
//		}
//	}
//	return false;
//}