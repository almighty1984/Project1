#include "BaseObject.h" 
#include "TextureManager.h"
#include "RenderingManager.h"
#include "SoundsManager.h"
#include "Level.h"

cBaseObject::cBaseObject() :
	m_attachedLevel(nullptr),
	m_parent(nullptr),
	m_aboveObject(nullptr),
	m_belowObject(nullptr),
	m_leftObject(nullptr),
	m_rightObject(nullptr),
	m_carriedObject(nullptr),
	m_thrownObject(nullptr),
	m_carrier(nullptr),
	m_senseCollidedLeft(false), m_senseCollidedRight(false), m_senseCollidedAbove(false), m_senseCollidedBelow(false),
	m_timerSense(0.0f), m_timerSenseClear(0.0),
	m_damage(0.0f),
	m_delayCollisionLevel(0.0f), m_delayCollisionEntity(0.0f),
	m_direction(0.0f),
	m_doRemove(false), m_doRotate(false), m_doSpawnSenses(false), m_dontFlipSprite(false),
	m_hurtAgainDelay(0), m_hurtAgainDelayValue(0),
	m_rotation(0.0f),
	m_offsetX(0),
	m_offsetY(0),
	m_spriteOffsetX(0.0f), m_spriteOffsetY(0.0f),
	m_x(0.0f), m_y(0.0f), m_previousX(0.0f), m_previousY(0.0f), m_velocityX(0.0f), m_velocityY(0.0f),
	m_fallVelocity(0.0f), m_fallAcc(0.0f),
	m_moveVelocity(0.0f), m_moveAcc(0.0f), m_moveDec(0.0f),
	m_movedVelocityX(0.0f), m_movedVelocityY(0.0f),
	m_slopeOffsetX(0.0f),
	m_tileOffsetX(0.0f), m_tileOffsetY(0.0f), m_previousTileOffsetX(0.0f), m_previousTileOffsetY(0.0f),
	m_levelX(0.0f), m_levelY(0.0f), m_previousLevelX(0.0f), m_previousLevelY(0.0f), 
	m_width(16), m_height(16), m_tile(0),
	m_layer(0),
	m_radius(0),
	m_startVelocityX(0.0f), m_startVelocityY(0.0f),
	m_startX(0.0f), m_startY(0.0f), m_oldStartX(0.0f), m_oldStartY(0.0f),
	m_startFallVelocity(0.0f), m_startMoveAcc(0.0f), m_startMoveDec(0.0f), m_startMoveVelocity(0.0f),
	m_timerState(0.0f),
	m_timerThrow(0.0f), m_timeLimitThrow(0.0f),
	m_subtractUp(0), m_subtractDown(0),
	m_subtractLeft(0), m_subtractRight(0),
	m_startSubtractUp(0), m_startSubtractDown(0),
	m_startSubtractLeft(0), m_startSubtractRight(0),
	m_isAnim(false), m_isCarried(false), m_isCarrying(false), m_isCircle(false), m_isDead(false), m_isEntity(false), m_isFacingLeft(false), m_isHidden(false), m_isHurting(false), m_isIdle(false), m_isInSlope(false), m_isSlopeSliding(false), m_isLight(false), m_isLocked(false), m_isNearWallLeft(false), m_isNearWallRight(false), m_isOnBack(false), m_isOnGround(false), m_isOnLedge(false), 
	m_isRideable(false), m_isRiding(false),
	m_isSlope(false), m_isStatic(false), m_isThrown(false), m_isThrowing(false), m_isUpsideDown(false), m_isUsingFloatPosition(false), m_isUpdatedEveryFrame(false),
	m_isInWater(false), m_isInWaterJump(false),
	m_isSolidEntityX(false), m_isSolidEntityY(false), m_isSolidPlayerX(false), m_isSolidPlayerY(false), m_isSolidLevelX(false), m_isSolidLevelY(false),
	/*m_startIsSolidX(false), m_startIsSolidY(false),
	m_dontChangeSolid(false),*/	
	m_type(""),	m_imagePath(""),
	/*m_animTag(eAnimTag::idle),*/
	m_animTime(0.0f), m_animSpeed(0.0f),
	m_numAnimFrames(0), m_currentLoops(0), m_numAnimLoops(0),
	m_hurtSleepDelay(0.0f),
	m_timeToBeAlive(0.0f), m_timeBeingAlive(0.0f),
	m_timeBeingDead(0.0f), m_timeToBeDead(0.0f),
	m_timeBeingIdle(0.0f), m_timeToBeIdle(0.0f),
	m_numHealth(0.0f) {

	/*m_animIdle.loop = 0;
	m_animIdle.y = 0;
	m_animIdle.speed = 0;
	m_animDeath.loop = 0;
	m_animDeath.y = 0;
	m_animDeath.speed = 0;*/
	m_anims.clear();
}

cBaseObject::cBaseObject(const cBaseObject& other) :
	m_attachedLevel(other.m_attachedLevel),
	m_parent(other.m_parent),
	m_carrier(other.m_carrier),
	m_aboveObject(other.m_aboveObject),
	m_belowObject(other.m_belowObject),
	m_leftObject(other.m_leftObject),
	m_rightObject(other.m_rightObject),
	m_carriedObject(other.m_carriedObject),
	m_thrownObject(other.m_thrownObject),
	m_sensedObject(other.m_sensedObject), m_senseCollidedLeft(other.m_senseCollidedLeft), m_senseCollidedRight(other.m_senseCollidedRight), m_senseCollidedAbove(other.m_senseCollidedAbove), m_senseCollidedBelow(other.m_senseCollidedBelow),
	m_timerSense(other.m_timerSense), m_timerSenseClear(other.m_timerSenseClear),
	m_damage(other.m_damage),
	m_delayCollisionLevel(other.m_delayCollisionLevel), m_delayCollisionEntity(other.m_delayCollisionEntity),
	m_direction(other.m_direction),
	m_doRemove(other.m_doRemove), m_doRotate(other.m_doRotate), m_doSpawnSenses(other.m_doSpawnSenses), m_dontFlipSprite(other.m_dontFlipSprite),
	m_rotation(other.m_rotation),
	m_offsetX(other.m_offsetX),
	m_offsetY(other.m_offsetY),
	m_spriteOffsetX(other.m_spriteOffsetX), m_spriteOffsetY(other.m_spriteOffsetY),
	m_x(other.m_x), m_y(other.m_y),
	m_velocityX(other.m_velocityX), m_velocityY(other.m_velocityY),
	m_fallVelocity(other.m_fallVelocity), m_fallAcc(other.m_fallAcc),
	m_moveVelocity(other.m_moveVelocity), m_moveAcc(other.m_moveAcc), m_moveDec(other.m_moveDec),
	m_movedVelocityX(other.m_movedVelocityX), m_movedVelocityY(other.m_movedVelocityY),
	m_previousX(other.m_previousX), m_previousY(other.m_previousY),	
	m_startVelocityX(other.m_startVelocityX), m_startVelocityY(other.m_startVelocityY),
	m_startX(other.m_startX), m_startY(other.m_startY),	m_oldStartX(other.m_oldStartX), m_oldStartY(other.m_oldStartY),
	m_startFallVelocity(other.m_startFallVelocity), m_startMoveAcc(other.m_startMoveAcc), m_startMoveDec(other.m_startMoveDec), m_startMoveVelocity(other.m_startMoveVelocity),
	m_timerState(other.m_timerState),
	m_timerThrow(other.m_timerThrow), m_timeLimitThrow(other.m_timeLimitThrow),
	m_tile(other.m_tile),
	m_layer(other.m_layer),
	m_width(other.m_width), m_height(other.m_height),
	m_slopeOffsetX(other.m_slopeOffsetX),
	m_tileOffsetX(other.m_tileOffsetX), m_tileOffsetY(other.m_tileOffsetY), m_previousTileOffsetX(other.m_previousTileOffsetX), m_previousTileOffsetY(other.m_previousTileOffsetY),
	m_levelX(other.m_levelX), m_levelY(other.m_levelY),
	m_previousLevelX(other.m_previousLevelX), m_previousLevelY(other.m_previousLevelY),	
	m_isSolidEntityX(other.m_isSolidEntityX), m_isSolidEntityY(other.m_isSolidEntityY), m_isSolidPlayerX(other.m_isSolidPlayerX), m_isSolidPlayerY(other.m_isSolidPlayerY), m_isSolidLevelX(other.m_isSolidLevelX), m_isSolidLevelY(other.m_isSolidLevelY),
	m_isAnim(other.m_isAnim), m_isCarried(other.m_isCarried), m_isCarrying(other.m_isCarrying), m_isCircle(other.m_isCircle), m_isDead(other.m_isDead), m_isEntity(other.m_isEntity), m_isFacingLeft(other.m_isFacingLeft), m_isHidden(other.m_isHidden), m_isHurting(other.m_isHurting), m_isIdle(other.m_isIdle), m_isInSlope(other.m_isInSlope), m_isSlopeSliding(other.m_isSlopeSliding), m_isLight(other.m_isLight), m_isLocked(other.m_isLocked), m_isNearWallLeft(other.m_isNearWallLeft), m_isNearWallRight(other.m_isNearWallRight), m_isOnBack(other.m_isOnBack), m_isOnGround(other.m_isOnGround), m_isOnLedge(other.m_isOnLedge), m_isRideable(other.m_isRideable), m_isRiding(other.m_isRiding), m_isSlope(other.m_isSlope), m_isStatic(other.m_isStatic), m_isThrown(other.m_isThrown), m_isThrowing(other.m_isThrowing), m_isUpsideDown(other.m_isUpsideDown), m_isUsingFloatPosition(other.m_isUsingFloatPosition), m_isUpdatedEveryFrame(other.m_isUpdatedEveryFrame),
	m_isInWater(other.m_isInWater), m_isInWaterJump(other.m_isInWaterJump), 
	m_type(other.m_type), m_imagePath(other.m_imagePath),
	m_animTag(other.m_animTag),
	m_animTime(other.m_animTime), m_animSpeed(other.m_animSpeed),
	m_radius(other.m_radius),
	m_subtractUp(other.m_subtractUp), m_subtractDown(other.m_subtractDown),
	m_subtractLeft(other.m_subtractLeft),	m_subtractRight(other.m_subtractRight),
	m_startSubtractUp(other.m_startSubtractUp), m_startSubtractDown(other.m_startSubtractDown),
	m_startSubtractLeft(other.m_startSubtractLeft), m_startSubtractRight(other.m_startSubtractRight),
	m_numAnimFrames(other.m_numAnimFrames),
	m_currentLoops(other.m_currentLoops),
	m_numAnimLoops(other.m_numAnimLoops),
	m_hurtSleepDelay(other.m_hurtSleepDelay),
	m_timeBeingDead(other.m_timeBeingDead), m_timeToBeDead(other.m_timeToBeDead),
	m_timeBeingIdle(other.m_timeBeingIdle), m_timeToBeIdle(other.m_timeToBeIdle),	
	m_hurtAgainDelay(other.m_hurtAgainDelay), m_hurtAgainDelayValue(other.m_hurtAgainDelayValue),	
	m_numHealth(other.m_numHealth) {
}

cBaseObject& cBaseObject::operator =(const cBaseObject& other) {
	m_attachedLevel = other.m_attachedLevel;
	m_parent = other.m_parent;
	m_carrier = other.m_carrier;
	m_aboveObject = other.m_aboveObject;
	m_belowObject = other.m_belowObject;
	m_leftObject = other.m_leftObject;
	m_rightObject = other.m_rightObject;
	m_carriedObject = other.m_carriedObject;
	m_thrownObject = other.m_thrownObject,
	m_sensedObject = other.m_sensedObject; m_senseCollidedLeft = other.m_senseCollidedLeft; m_senseCollidedRight = other.m_senseCollidedRight; m_senseCollidedAbove = other.m_senseCollidedAbove; m_senseCollidedBelow = other.m_senseCollidedBelow;
	m_timerSense = other.m_timerSense; m_timerSenseClear = other.m_timerSenseClear;
	m_damage = other.m_damage;
	m_delayCollisionLevel = other.m_delayCollisionLevel; m_delayCollisionEntity = other.m_delayCollisionEntity;
	m_direction = other.m_direction;
	m_doRemove = other.m_doRemove; m_doRotate = other.m_doRotate; m_doSpawnSenses = other.m_doSpawnSenses; m_dontFlipSprite = other.m_dontFlipSprite;
	m_rotation = other.m_rotation;
	m_offsetX = other.m_offsetX;
	m_offsetY = other.m_offsetY;
	m_spriteOffsetX = other.m_spriteOffsetX;
	m_spriteOffsetY = other.m_spriteOffsetY;
	m_x = other.m_x;m_y = other.m_y;
	m_velocityX = other.m_velocityX; m_velocityY = other.m_velocityY;
	m_fallVelocity = other.m_fallVelocity; m_fallAcc = other.m_fallAcc;
	m_moveVelocity = other.m_moveVelocity; m_moveAcc = other.m_moveAcc; m_moveDec = other.m_moveDec;
	m_movedVelocityX = other.m_movedVelocityX; m_movedVelocityY = other.m_movedVelocityY;
	m_previousX = other.m_previousX; m_previousY = other.m_previousY;	
	m_startVelocityX = other.m_startVelocityX;
	m_startVelocityY = other.m_startVelocityY;
	m_timerState = other.m_timerState;
	m_tile = other.m_tile;
	m_layer = other.m_layer;
	m_width = other.m_width;
	m_height = other.m_height;
	m_startX = other.m_startX; m_oldStartX = other.m_oldStartX;
	m_startY = other.m_startY; m_oldStartY = other.m_oldStartY;
	m_startFallVelocity = other.m_startFallVelocity; m_startMoveAcc = other.m_startMoveAcc; m_startMoveDec = other.m_startMoveDec; m_startMoveVelocity = other.m_startMoveVelocity;
	m_slopeOffsetX = other.m_slopeOffsetX;
	m_tileOffsetX = other.m_tileOffsetX; m_tileOffsetY = other.m_tileOffsetY; m_previousTileOffsetX = other.m_previousTileOffsetX; m_previousTileOffsetY = other.m_previousTileOffsetY;
	m_levelX = other.m_levelX; m_levelY = other.m_levelY;
	m_previousLevelX = other.m_previousLevelX; m_previousLevelY = other.m_previousLevelY;
	m_type = other.m_type;
	m_imagePath = other.m_imagePath;	
	m_isSolidEntityX = other.m_isSolidEntityX; m_isSolidEntityY = other.m_isSolidEntityY; m_isSolidPlayerX = other.m_isSolidPlayerX; m_isSolidPlayerY = other.m_isSolidPlayerY; m_isSolidLevelX = other.m_isSolidLevelX; m_isSolidLevelY = other.m_isSolidLevelY;
	m_animTag = other.m_animTag;
	m_isAnim = other.m_isAnim; m_isCarried = other.m_isCarried; m_isCarrying = other.m_isCarrying; m_isCircle = other.m_isCircle; m_isDead = other.m_isDead; m_isEntity = other.m_isEntity; m_isFacingLeft = other.m_isFacingLeft; m_isHidden = other.m_isHidden; m_isHurting = other.m_isHurting; m_isIdle = other.m_isIdle; m_isInSlope = other.m_isInSlope; m_isSlopeSliding = other.m_isSlopeSliding; m_isLight = other.m_isLight; m_isLocked = other.m_isLocked; m_isNearWallLeft = other.m_isNearWallLeft; m_isNearWallRight = other.m_isNearWallRight; m_isOnBack = other.m_isOnBack; m_isOnGround = other.m_isOnGround; m_isOnLedge = other.m_isOnLedge; m_isRideable = other.m_isRideable; m_isRiding = other.m_isRiding; m_isSlope = other.m_isSlope; m_isStatic = other.m_isStatic; m_isThrown = other.m_isThrown; m_isThrowing = other.m_isThrowing; m_isUpsideDown = other.m_isUpsideDown; m_isUpdatedEveryFrame = other.m_isUpdatedEveryFrame; m_isUsingFloatPosition = other.m_isUsingFloatPosition;
	m_isInWater = other.m_isInWater; m_isInWaterJump = other.m_isInWaterJump;
	m_radius = other.m_radius;
	m_subtractUp = other.m_subtractUp;
	m_subtractDown = other.m_subtractDown;
	m_subtractLeft = other.m_subtractLeft;
	m_subtractRight = other.m_subtractRight;
	m_startSubtractUp = other.m_startSubtractUp;
	m_startSubtractDown = other.m_startSubtractDown;
	m_startSubtractLeft = other.m_startSubtractLeft;
	m_startSubtractRight = other.m_startSubtractRight;
	m_animTime = other.m_animTime;
	m_animSpeed = other.m_animSpeed;
	m_numAnimFrames = other.m_numAnimFrames;
	m_currentLoops = other.m_currentLoops;
	m_numAnimLoops = other.m_numAnimLoops;
	m_hurtSleepDelay = other.m_hurtSleepDelay;	
	m_timeBeingDead = other.m_timeBeingDead;
	m_timeToBeDead = other.m_timeToBeDead;
	m_timeBeingIdle = other.m_timeBeingIdle;
	m_timeToBeIdle = other.m_timeToBeIdle;
	m_timerState = other.m_timerState;
	m_timerThrow = other.m_timerThrow; m_timeLimitThrow = other.m_timeLimitThrow;	
	m_hurtAgainDelay = other.m_hurtAgainDelay;
	m_hurtAgainDelayValue = other.m_hurtAgainDelayValue;
    return *this;
}

cBaseObject::~cBaseObject() {
	m_aboveObject = nullptr;
	m_belowObject = nullptr;
	m_leftObject = nullptr;
	m_rightObject = nullptr;

	m_attachedLevel = nullptr;
	m_imagePath.clear();
}

void cBaseObject::setVelocityFromSlope(float vectorX, float vectorY) {
	float projMultiplier = 0.0f;
	float projX = 0.0f;
	float projY = 0.0f;
	projMultiplier = (m_velocityX * vectorX + m_velocityY * vectorY) / (vectorX * vectorX + vectorY * vectorY);
	projX = projMultiplier * vectorX;
	projY = projMultiplier * vectorY;
	m_velocityX = m_velocityX - projX;
	m_velocityY = m_velocityY - projY;
}

void cBaseObject::senseCollidedAbove(cBaseObject* object) {
	m_senseCollidedAbove = true;
	m_aboveObject = object;
}

void cBaseObject::senseCollidedBelow(cBaseObject* object) {
	m_senseCollidedBelow = true;
	m_belowObject = object;
}

void cBaseObject::senseCollidedLeft(cBaseObject* object) {
	m_isNearWallLeft = true;
	m_senseCollidedLeft = true;
	m_leftObject = object;
}

void cBaseObject::senseCollidedRight(cBaseObject* object) {
	m_isNearWallRight = true;
	m_senseCollidedRight = true;
	m_rightObject = object;
}

void cBaseObject::clearSenses() {
	m_timerSense = 0.0f;
	m_sensedObject = nullptr;	
	clearSenseAbove();
	clearSenseBelow();
	clearSenseLeft();
	clearSenseRight();
}

void cBaseObject::clearSenseAbove() {	
	m_senseCollidedAbove = false;
	m_aboveObject = nullptr;
}

void cBaseObject::clearSenseBelow() {
	m_senseCollidedBelow = false;
	m_belowObject = nullptr;
}

void cBaseObject::clearSenseLeft() {
	m_isNearWallLeft = false;
	m_senseCollidedLeft = false;
	m_leftObject = nullptr;
}

void cBaseObject::clearSenseRight() {
	m_isNearWallRight = false;
	m_senseCollidedRight = false;
	m_rightObject = nullptr;
}

void cBaseObject::loadConfig(std::string fileName) {
}

void cBaseObject::setImagePath(std::string imagePath) {
	m_imagePath = imagePath;	
	m_sprite.setTexture(imagePath);
	m_sprite.setTextureRect( (int)m_tileOffsetX, (int)m_tileOffsetY, (int)m_width, (int)m_height );
}

void cBaseObject::setSpritePosition(float spritePositionX, float spritePositionY) {
	m_sprite.setPosition(spritePositionX, spritePositionY);
}

void cBaseObject::setSpriteRect(unsigned short x, unsigned short y, unsigned short width, unsigned short height) {
	m_sprite.setTextureRect(x, y, width, height);
}

void cBaseObject::setSpriteScale(float spriteScaleX, float spriteScaleY) {
	m_sprite.setScale(spriteScaleX, spriteScaleY);
}

void cBaseObject::setRotation(float angle) {
	m_rotation = angle;
	m_sprite.setRotation(angle);
}

void cBaseObject::rotate(float angle) {
	m_sprite.rotate(angle);
	m_rotation = angle;
}

void cBaseObject::setOrigin(float x, float y) {
	m_sprite.setOrigin(x, y);
}

void cBaseObject::setColor(unsigned char red, unsigned char green, unsigned char blue) {
	if (!m_isLight) {
		m_sprite.setColor(red, green, blue);
	}
}

unsigned char cBaseObject::getColor(char element) const {
	return m_sprite.getColor(element);
}

void cBaseObject::resetCollisionBox() {
	m_subtractUp = m_startSubtractUp;
	m_subtractDown = m_startSubtractDown;
	m_subtractLeft = m_startSubtractLeft;
	m_subtractRight = m_startSubtractRight;
}

void cBaseObject::update(float time) {
}

void cBaseObject::createAnim(std::string id, unsigned short y, float speed, unsigned short loop) {
	eAnimTag animationTag;
	if (id == "attack") {
		animationTag = eAnimTag::attack;
	} else if (id == "bounce") {
		animationTag = eAnimTag::bounce;
	} else if (id == "climb") {
		animationTag = eAnimTag::climb;
	} else if (id == "crawl") {
		animationTag = eAnimTag::crawl;
	} else if (id == "death") {
		animationTag = eAnimTag::death;
	} else if (id == "dig") {
		animationTag = eAnimTag::dig;
	} else if (id == "downThrust") {
		animationTag = eAnimTag::downThrust;
	} else if (id == "duck") {
		animationTag = eAnimTag::duck;
	} else if (id == "duckAttack") {
		animationTag = eAnimTag::duckAttack;
	} else if (id == "fall") {
		animationTag = eAnimTag::fall;
	} else if (id == "flipped") {
		animationTag = eAnimTag::flipped;
	} else if (id == "hide") {
		animationTag = eAnimTag::hide;
	} else if (id == "hover") {
		animationTag = eAnimTag::hover;
	} else if (id == "hurt") {
		animationTag = eAnimTag::hurt;
	} else if (id == "idle") {
		animationTag = eAnimTag::idle;
	} else if (id == "jump") {
		animationTag = eAnimTag::jump;
	} else if (id == "jumpHigh") {
		animationTag = eAnimTag::jumpHigh;
	} else if (id == "ledge") {
		animationTag = eAnimTag::ledge;
	} else if (id == "open") {
		animationTag = eAnimTag::open;
	} else if (id == "run") {
		animationTag = eAnimTag::run;
	} else if (id == "slide") {
		animationTag = eAnimTag::slide;
	} else if (id == "stunned") {
		animationTag = eAnimTag::stunned;
	} else if (id == "turn") {
		animationTag = eAnimTag::turn;
	} else if (id == "toss") {
		animationTag = eAnimTag::toss;
	} else if (id == "up") {
		animationTag = eAnimTag::up;
	} else if (id == "walk") {
		animationTag = eAnimTag::walk;
	} else if (id == "wall") {
		animationTag = eAnimTag::wall;
	}
	if ((m_anims[animationTag].y == y && m_anims[animationTag].speed == speed && m_anims[animationTag].loop == loop)) {
		return;
	}
	m_anims[animationTag].y = y;
	m_anims[animationTag].speed = speed;
	m_anims[animationTag].loop = loop;
	//std::cout << "Created animation: " << m_type << " " << id << " " << y << " " << speed << " " << loop << "\n";
}

//sAnim cBaseObject::getAnim() {
//	return m_animCurrent;
//}

sAnim cBaseObject::getAnim(eAnimTag animationTag) {
	return m_anims[animationTag];
}

void cBaseObject::setAnim(eAnimTag animTag) {
	//if (getAnimTag() == animTag) { return; }

	//m_tileOffsetX = 0.0f;

	m_tileOffsetY = getAnim(animTag).y;
	m_animSpeed = getAnim(animTag).speed;
	m_numAnimLoops = getAnim(animTag).loop;

	m_animTag = animTag;
}

bool cBaseObject::collisionCheckX(cBaseObject* object) {
	if (object == this || object == nullptr || object == m_parent) {
		return false;
	}
	if (!getIsSolidX() || !object->getIsSolidX() /*|| object->getIsDead()*/ || m_isDead || m_levelY < 0.0f) {
		return false;
	}
	if (object->getIsSlope()) {
		return collisionCheckSlopeX(object);
	}
	float left = getLeft();
	float right = getRight();
	float bottom = getBottom();
	float top = getTop();
	if (m_velocityX + m_movedVelocityX > 0.0f) {
		if (right > object->getLeft() && getMiddleX() < object->getRight()) {
			if (bottom > object->getTop() && top < object->getBottom()) {
				return true;
			}
		}
	} else if (m_velocityX + m_movedVelocityX < 0.0f) {
		if (left < object->getRight() && getMiddleX() > object->getLeft()) {
			if (bottom > object->getTop() && top < object->getBottom()) {
				return true;
			}
		}
	}
	return false;
}

bool cBaseObject::collisionCheckY(cBaseObject* object) {
	if (object == this || object == nullptr || object == m_parent) {
		return false;
	}
	if (!getIsSolidY() || !object->getIsSolidY() /*|| object->getIsDead() */|| m_isDead || m_levelY < 0.0f) {
		return false;
	}
	if (object->getIsSlope()) {
		return collisionCheckSlopeY(object);
	}
	float left = getLeft();
	float right = getRight();
	float bottom = getBottom()+2;
	float top = getTop();
	if (m_velocityY + m_movedVelocityY < 0.0f) {
		if (top < object->getBottom() && getMiddleY() > object->getTop()) {
			if (left < object->getRight() && right > object->getLeft()) {
				return true;
			}
		}
	} else if (m_velocityY + m_movedVelocityY > 0.0f) {
		if (bottom > object->getTop() && getMiddleY() < object->getBottom()) {
			if (left < object->getRight() && right > object->getLeft()) {
				return true;
			}
		}
	}
	return false;
}

bool cBaseObject::collisionCheckSlopeX(cBaseObject* object) {
	float left = getLeft();
	float right = getRight();
	float bottom = getBottom() - 0;
	float top = getTop() + 0;

	left = getMiddleX() - 0;
	right = getMiddleX() + 0;
	m_slopeOffsetX = 0.0f;

	if (m_velocityX < 0.0f) {
		if (left < object->getRight() && right > object->getLeft()) {
			m_slopeOffsetX = 16 - abs(getMiddleX() - object->getRight());
			if (object->getType().substr(0, 7) == "slope_L") {
				return false;
			} else if (object->getType() == "slope_R_1x1") {
				if (bottom > object->getTop() + m_slopeOffsetX && top < object->getBottom() + m_slopeOffsetX) {
					return true;
				}
			} else if (object->getType() == "slope_R_2x1_0") {
				if (bottom > object->getTop() + m_slopeOffsetX * 0.5f && top < object->getBottom() + m_slopeOffsetX * 0.5f) {
					return true;
				}
			} else if (object->getType() == "slope_R_2x1_1") {
				if (bottom > object->getTop() + 8 + m_slopeOffsetX * 0.5f && top < object->getBottom() + 8 + m_slopeOffsetX * 0.5f) {
					return true;
				}
			} else if (object->getType() == "slope_RU_2x1_0") {
				if (bottom > object->getTop() + 16 - m_slopeOffsetX * 0.5f && top < object->getBottom() + 16 - m_slopeOffsetX * 0.5f) {
					return true;
				}
			} else if (object->getType() == "slope_RU_2x1_1") {
				if (bottom > object->getTop() + 16 - 8 - m_slopeOffsetX * 0.5f && top < object->getBottom() + 16 - 8 - m_slopeOffsetX * 0.5f) {
					return true;
				}
			} else if (object->getType() == "slope_RU_1x1") {
				if (bottom > object->getTop() + 16 - m_slopeOffsetX && top < object->getBottom() + 16 - m_slopeOffsetX) {
					return true;
				}
			}
		}
	} else if (m_velocityX > 0.0f) {
		if (right > object->getLeft() && left + 0 < object->getRight()) {
			m_slopeOffsetX = 16 - abs(getMiddleX() - object->getRight());
			if (object->getType().substr(0, 7) == "slope_R") {
				return false;
			} else if (object->getType() == "slope_L_1x1") {
				if (bottom > object->getTop() + 16 - m_slopeOffsetX && top < object->getBottom() + 16 - m_slopeOffsetX) {
					return true;
				}
			} else if (object->getType() == "slope_L_2x1_0") {
				if (bottom > object->getTop() + 16 - m_slopeOffsetX * 0.5f && top < object->getBottom() + 16 - m_slopeOffsetX * 0.5f) {
					return true;
				}
			} else if (object->getType() == "slope_L_2x1_1") {
				if (bottom > object->getTop() + 16 - 8 - m_slopeOffsetX * 0.5f && top < object->getBottom() + 16 - 8 - m_slopeOffsetX * 0.5f) {
					return true;
				}
			} else if (object->getType() == "slope_LU_2x1_0") {
				if (bottom > object->getTop() + m_slopeOffsetX * 0.5f && top < object->getBottom() + m_slopeOffsetX * 0.5f) {
					return true;
				}
			} else if (object->getType() == "slope_LU_2x1_1") {
				if (bottom > object->getTop() + 8 + m_slopeOffsetX * 0.5f && top < object->getBottom() + 8 + m_slopeOffsetX * 0.5f) {
					return true;
				}
			} else if (object->getType() == "slope_LU_1x1") {
				if (bottom > object->getTop() + m_slopeOffsetX && top < object->getBottom() + m_slopeOffsetX) {
					return true;
				}
			}
		}
	}
	return false;
}

bool cBaseObject::collisionCheckSlopeY(cBaseObject* object) {
	char offsetY = 0;

	float bottom = getBottom() + offsetY + 0;

	float top = getTop() + 0;
	m_slopeOffsetX = 0.0f;
	// Moving up
	if (m_velocityY < 0.0f) {
		m_slopeOffsetX = 16 - abs(getMiddleX() - object->getRight());
		if (object->getType() == "slope_LU_1x1") {
			if (top <= object->getTop() + m_slopeOffsetX && bottom >= object->getTop()) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_RU_1x1") {
			if (top <= object->getBottom() - m_slopeOffsetX && bottom >= object->getTop()) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_LU_2x1_0") {
			if (top <= object->getTop() + m_slopeOffsetX * 0.5f && bottom >= object->getTop()) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_LU_2x1_1") {
			if (top <= object->getTop() + 8 + m_slopeOffsetX * 0.5f && bottom >= object->getTop()) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_RU_2x1_0") {
			if (top <= object->getBottom() - m_slopeOffsetX * 0.5f && bottom >= object->getTop()) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_RU_2x1_1") {
			if (top <= object->getBottom() - 8 - m_slopeOffsetX * 0.5f && bottom >= object->getTop()) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else {
			return false;
		}
	} else if (m_velocityY >= 0.0f) {
		m_slopeOffsetX = 16 - abs(getMiddleX() - object->getRight());
		if (object->getType().substr(0, 8) == "slope_LU" || object->getType().substr(0, 8) == "slope_RU") {
			return false;
		} else if (object->getType() == "slope_L_seam") {
			if (bottom >= (object->getBottom() - m_slopeOffsetX) && top <= object->getBottom() - m_slopeOffsetX + 0) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_R_seam") {
			if (bottom >= (object->getTop() + m_slopeOffsetX) && top <= object->getBottom() + m_slopeOffsetX + 0) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_L_1x1") {
			if (bottom >= object->getBottom() - m_slopeOffsetX && top <= object->getBottom() - m_slopeOffsetX + 0) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_R_1x1") {
			if (bottom >= object->getTop() + m_slopeOffsetX && top <= object->getTop() + m_slopeOffsetX + 0) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_L_2x1_0") {
			if (bottom >= (object->getBottom() - m_slopeOffsetX * 0.5f) && top <= object->getBottom() - m_slopeOffsetX * 0.5f + 0) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_L_2x1_1") {
			if (bottom >= (object->getBottom() - m_slopeOffsetX * 0.5f - 8) && top <= object->getBottom() - m_slopeOffsetX * 0.5f - 8 + 0) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_R_2x1_0") {
			if (bottom >= (object->getTop() + m_slopeOffsetX * 0.5f) && top <= object->getTop() + m_slopeOffsetX * 0.5f + 0) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		} else if (object->getType() == "slope_R_2x1_1") {
			if (bottom >= (object->getTop() + m_slopeOffsetX * 0.5f + 8) && top <= object->getTop() + m_slopeOffsetX * 0.5f + 8 + 0) {
				if (getMiddleX() >= object->getLeft() && getMiddleX() <= object->getRight()) {
					return true;
				}
			}
		}
	}
	return false;
}

void cBaseObject::collisionReactionSlopeX(cBaseObject* object) {
	if (object->getType() == "slope_L_1x1" || object->getType() == "slope_L_seam") {
		m_y = object->getY() + 16 - m_slopeOffsetX - m_height + m_subtractDown - 1;
		if (m_isSlopeSliding) {
			setVelocityFromSlope(16.0f, 16.0f);
			return;
		}
		/*if (m_velocityX > m_moveVelocity * 0.3f) {
			m_velocityX = m_moveVelocity * 0.3f;
		}*/
		m_velocityY = -m_velocityX;
	} else if (object->getType() == "slope_R_1x1" || object->getType() == "slope_R_seam") {
		m_y = object->getY() + m_slopeOffsetX - m_height + m_subtractDown - 1;
		if (m_isSlopeSliding) {
			setVelocityFromSlope(-16.0f, 16.0f);
			return;
		}
		/*if (m_velocityX < -m_moveVelocity * 0.3f) {
			m_velocityX = -m_moveVelocity * 0.3f;
		}*/
		m_velocityY = m_velocityX;
	} else if (object->getType() == "slope_L_2x1_0") {
		m_y = object->getY() + 16 - m_slopeOffsetX * 0.5f - m_height + m_subtractDown - 1;
		if (m_isSlopeSliding) {
			setVelocityFromSlope(32.0f, 16.0f);
			return;
		}
		/*if (m_velocityX > m_moveVelocity * 0.6f) {
			m_velocityX = m_moveVelocity * 0.6f;
		}*/
		m_velocityY = -m_velocityX * 0.5f;
	} else if (object->getType() == "slope_L_2x1_1") {
		m_y = object->getY() + 8 - m_slopeOffsetX * 0.5f - m_height + m_subtractDown - 1;
		if (m_isSlopeSliding) {
			setVelocityFromSlope(32.0f, 16.0f);
			return;
		}
		/*if (m_velocityX > m_moveVelocity * 0.6f) {
			m_velocityX = m_moveVelocity * 0.6f;
		}*/
		m_velocityY = -m_velocityX * 0.5f;
	} else if (object->getType() == "slope_R_2x1_0") {
		m_y = object->getY() + m_slopeOffsetX * 0.5f - m_height + m_subtractDown - 1;
		if (m_isSlopeSliding) {
			setVelocityFromSlope(-32.0f, 16.0f);
			return;
		}
		/*if (m_velocityX < -m_moveVelocity * 0.6f) {
			m_velocityX = -m_moveVelocity * 0.6f;
		}*/
		m_velocityY = m_velocityX * 0.5f;
		//std::cout << m_velocityY << "\n";
	} else if (object->getType() == "slope_R_2x1_1") {
		m_y = object->getY() + 8 + m_slopeOffsetX * 0.5f - m_height + m_subtractDown - 1;
		if (m_isSlopeSliding) {
			setVelocityFromSlope(-32.0f, 16.0f);
			return;
		}
		/*if (m_velocityX < -m_moveVelocity * 0.6f) {
			m_velocityX = -m_moveVelocity * 0.6f;
		}*/
		m_velocityY = m_velocityX * 0.5f;
		//std::cout << m_velocityY << "\n";
	} else if (object->getType() == "slope_LU_1x1") {
		m_y = object->getY() + m_slopeOffsetX - m_subtractUp;
		m_velocityY = abs(m_velocityX);
	} else if (object->getType() == "slope_RU_1x1") {
		m_y = object->getY() + 16 - m_slopeOffsetX - m_subtractUp;
		m_velocityY = abs(m_velocityX);
	} else if (object->getType() == "slope_LU_2x1_0") {
		m_y = object->getY() + m_slopeOffsetX * 0.5f - m_subtractUp;
		m_velocityY = abs(m_velocityX) * 0.5f;
	} else if (object->getType() == "slope_LU_2x1_1") {
		m_y = object->getY() + 8 + m_slopeOffsetX * 0.5f - m_subtractUp;
		m_velocityY = abs(m_velocityX) * 0.5f;
	} else if (object->getType() == "slope_RU_2x1_0") {
		m_velocityY = abs(m_velocityX) * 0.5f;
		m_y = object->getBottom() - m_slopeOffsetX * 0.5f - m_subtractUp + 2;
	} else if (object->getType() == "slope_RU_2x1_1") {
		m_velocityY = abs(m_velocityX) * 0.5f;
		m_y = object->getBottom() - 8 - m_slopeOffsetX * 0.5f - m_subtractUp + 2;
	}
}

void cBaseObject::collisionReactionSlopeY(cBaseObject* object) {
	if (object->getType().substr(0, 8) == "slope_L_") {
		//if (m_velocityY < 0.0f) { return; };
		//m_movedVelocityX = 0.0f;
		//m_movedVelocityY = 0.0f;		
		m_isInSlope = true;
		m_isOnGround = true;
		//m_isDownThrusting = false;
		
		if (object->getType() == "slope_L_seam") {
			m_y = object->getY() + 16 - m_slopeOffsetX - m_height + m_subtractDown - 8 - 1;
			if (m_isSlopeSliding) {
				setVelocityFromSlope(16.0f, 16.0f);
				return;
			}			
			hitGround(object);
			/*if (m_velocityX > m_moveVelocity * 0.3f) {
				m_velocityX = m_moveVelocity * 0.3f;
			}*/
			m_velocityY = -m_velocityX;
		} else if (object->getType() == "slope_L_1x1") {
			m_y = object->getY() + 16 - m_slopeOffsetX - m_height + m_subtractDown - 1;
			if (m_isSlopeSliding) {
				setVelocityFromSlope(16.0f, 16.0f);
				return;
			}			
			hitGround(object);
			//if (m_velocityX > m_moveVelocity * 0.3f) {
			//	m_velocityX = m_moveVelocity * 0.3f;
			//	//m_hasJumped = true;
			//}
			m_velocityY = -m_velocityX;
		} else if (object->getType() == "slope_L_2x1_0") {			
			m_y = object->getY() + 16 - m_slopeOffsetX * 0.5f - m_height + m_subtractDown - 1;
			if (m_isSlopeSliding) {
				setVelocityFromSlope(32.0f, 16.0f);
				return;
			}			
			hitGround(object);
			/*if (m_velocityX > m_moveVelocity * 0.6f) {
				m_velocityX = m_moveVelocity * 0.6f;
			}	*/		
			m_velocityY = -m_velocityX * 0.5f;
		} else if (object->getType() == "slope_L_2x1_1") {
			m_y = object->getY() + 8 - m_slopeOffsetX * 0.5f - m_height + m_subtractDown - 1;
			if (m_isSlopeSliding) {
				setVelocityFromSlope(32.0f, 16.0f);
				return;
			}			
			hitGround(object);
			//if (m_velocityX > m_moveVelocity * 0.6f) {
			//	m_velocityX = m_moveVelocity * 0.6f;
			//	//m_hasJumped = true;
			//}
			m_velocityY = -m_velocityX * 0.5f;
		}
	} else if (object->getType().substr(0, 8) == "slope_R_") {
		//if (m_velocityY < 0.0f) { return; };
		//m_movedVelocityX = 0.0f;
		//m_movedVelocityY = 0.0f;
		m_isInSlope = true;
		m_isOnGround = true;

		if (object->getType() == "slope_R_seam") {
			m_y = object->getY() - m_height + m_slopeOffsetX + m_subtractDown - 8 - 1;			
			hitGround(object);
			/*if (m_velocityX < -m_moveVelocity * 0.3f) {
				m_velocityX = -m_moveVelocity * 0.3f;
			}*/
			m_velocityY = m_velocityX;
		} else if (object->getType() == "slope_R_1x1") {
			m_y = object->getY() + m_slopeOffsetX - m_height + m_subtractDown - 1;		
			hitGround(object);
			//if (m_velocityX < -m_moveVelocity * 0.3f) {
			//	m_velocityX = -m_moveVelocity * 0.3f;
			//	//m_hasJumped = true;
			//}
			m_velocityY = m_velocityX;
		} else if (object->getType() == "slope_R_2x1_0") {
			m_y = object->getY() + m_slopeOffsetX * 0.5f - m_height + m_subtractDown - 1;			
			hitGround(object);
			//if (m_velocityX < -m_moveVelocity * 0.6f) {
			//	m_velocityX = -m_moveVelocity * 0.6f;
			//	//m_hasJumped = true;
			//}
			m_velocityY = m_velocityX * 0.5f;
		} else if (object->getType() == "slope_R_2x1_1") {
			m_y = object->getY() + 8 + m_slopeOffsetX * 0.5f - m_height + m_subtractDown - 1;			
			hitGround(object);
			/*if (m_velocityX < -m_moveVelocity * 0.6f) {
				m_velocityX = -m_moveVelocity * 0.6f;
			}*/
			m_velocityY = m_velocityX * 0.5f;
		}
	} else if (object->getType() == "slope_LU_1x1") {
		if (m_velocityY > 0.0f) { return; };
		m_y = object->getY() + m_slopeOffsetX - m_subtractUp + 1;
		if (m_velocityX > 0.0f) {
			m_velocityY *= -1.0f;
		} else {
			m_velocityX = -abs(m_velocityY);
		}
	} else if (object->getType() == "slope_RU_1x1") {
		if (m_velocityY > 0.0f) { return; };
		m_y = object->getY() + 16 - m_slopeOffsetX - m_subtractUp + 1;
		if (m_velocityX < 0.0f) {
			m_velocityY *= -1.0f;
		} else {
			m_velocityX = abs(m_velocityY);
		}
	} else if (object->getType() == "slope_LU_2x1_0") {
		if (m_velocityY > 0.0f) { return; };
		if (m_velocityX > 0.0f) {
			m_velocityY *= -1.0f;
		} else {
			m_velocityX = -abs(m_velocityY) * 1.0f;
		}
		//m_x = object->getLeft() + m_slopeOffsetX - m_width + m_subtractRight + 8;
		m_y = object->getY() + m_slopeOffsetX * 0.5f - m_subtractUp + 1;
	} else if (object->getType() == "slope_LU_2x1_1") {
		if (m_velocityY > 0.0f) { return; };
		if (m_velocityX > 0.0f) {
			m_velocityY *= -1.0f;
		} else {
			m_velocityX = -abs(m_velocityY) * 1.0f;
		}
		//m_x = object->getLeft() + m_slopeOffsetX - m_width + m_subtractRight + 8;
		m_y = object->getY() + 8 + m_slopeOffsetX * 0.5f - m_subtractUp + 1;
	} else if (object->getType() == "slope_RU_2x1_0") {
		if (m_velocityY > 0.0f) { return; };
		if (m_velocityX < 0.0f) {
			m_velocityY *= -1.0f;
		} else {
			m_velocityX = abs(m_velocityY) * 1.0f;
		}
		//m_x = object->getRight() - m_slopeOffsetX - m_subtractLeft - 8;
		m_y = object->getBottom() - m_slopeOffsetX * 0.5f - m_subtractUp + 1;
	} else if (object->getType() == "slope_RU_2x1_1") {
		if (m_velocityY > 0.0f) { return; };
		if (m_velocityX < 0.0f) {
			m_velocityY *= -1.0f;
		} else {
			m_velocityX = -m_velocityY * 1.0f;
		}
		//m_x = object->getRight() - m_slopeOffsetX - m_subtractLeft - 8;
		m_y = object->getBottom() - 8 - m_slopeOffsetX * 0.5f - m_subtractUp + 1;
	}
	/*else if (object->getType() == "slope_top") {
		if(m_velocityY > 0.0f) {
			m_y = object->getY()-m_height+m_subtractDown;
		}
		else {
			m_y = m_previousY;
		}

		m_velocityY = 0.0f;
	}*/
}