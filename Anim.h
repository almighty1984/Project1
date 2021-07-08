#pragma once

enum class eAnimTag {
	attack = 0,
	bounce,
	climb,
	crawl,
	death, dig, downThrust, duck, duckAttack,
	fall, flipped,
	hide, hover, hurt,
	idle,
	jump, jumpHigh,
	ledge,
	open,
	run,
	slide, stunned,
	turn,
	toss,
	up,
	walk, wall
};

struct sAnim {
	sAnim();
	sAnim(const sAnim& other);
	sAnim& operator=(const sAnim& other);
	bool operator==(const sAnim& other);
	bool operator!=(const sAnim& other);

	void clear() { y = 0; speed = 0.0f; loop = 0; };

	unsigned short y;
	float speed;
	unsigned short loop;
};