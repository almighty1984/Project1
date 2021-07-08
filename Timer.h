#ifndef INCLUDED_TIMER
#define INCLUDED_TIMER

#include <SFML/System.hpp>

class cTimer
{
public:
	//cTimer();
	unsigned int getStartTime();
	unsigned int getTime() const;
	void reset();
	float getElapsedTime();

private:
	sf::Clock m_clock;
	unsigned long int m_timeOfBirth;
};
#endif
