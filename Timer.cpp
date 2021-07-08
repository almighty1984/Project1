#include "Timer.h"

//cTimer::cTimer()
//{
//	reset();
//}

float cTimer::getElapsedTime()
{
	sf::Time time;
	time = m_clock.getElapsedTime();

	return time.asSeconds();
}

unsigned int cTimer::getStartTime()
{
	sf::Time time;
	time = m_clock.getElapsedTime();

	return time.asMilliseconds();
}
unsigned int cTimer::getTime() const
{
	/*if ((SDL_GetTicks() - m_timeOfBirth) > 13)
		return 13;
	else*/

	sf::Time time;
	time = m_clock.getElapsedTime();

	return time.asSeconds() - m_timeOfBirth;
	//return (int)(m_clock.getElapsedTime()*1000.0f) - m_timeOfBirth; 
	//return SDL_GetTicks() - m_timeOfBirth;
}

void cTimer::reset()
{
	sf::Time time;

	time = m_clock.getElapsedTime();

	m_timeOfBirth = time.asSeconds();
	//m_timeOfBirth = (int)(m_clock.getElapsedTime()*1000.0f);
}
