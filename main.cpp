//#include <SFML/System.hpp>
#include "App.h"
#include <iostream>

int main()
{
    //sf::Clock Clock;
    //while (Clock.GetElapsedTime() < 5.f)

	cApp *app;
	app = new cApp;

	app->init(app);
	app->run(app);

	delete app;	

    return EXIT_SUCCESS;
}
