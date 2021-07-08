#include "Anim.h"

sAnim::sAnim()
: loop(0), speed(0.0f), y(0) {
}

sAnim::sAnim(const sAnim& other)	:	loop(other.loop),
													speed(other.speed),
													y(other.y) {
}

sAnim& sAnim::operator =(const sAnim& other) {
	loop = other.loop;
	speed = other.speed;
	y = other.y;
    return *this;
}

bool sAnim::operator ==(const sAnim& other) {
	return (loop == other.loop && speed == other.speed && other.y == y);
}

bool sAnim::operator !=(const sAnim& other) {
	return (loop != other.loop || speed != other.speed || other.y != y);
}