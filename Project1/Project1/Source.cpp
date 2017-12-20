#include <SFML\Window.hpp>
#include <SFML\Graphics.hpp>
#include "SimpleAudioManager.h"

int main()
{
	sf::Window window(sf::VideoMode(320, 240), "AudioPlayback");
	sf::Clock clock;

	//initialization
	SimpleAudioManager audio;
	audio.Load("explosion.wav");

	//start game loop
	//fake game engine
	while (window.isOpen())
	{
		//run at 60fps
		float elapsed = clock.getElapsedTime().asSeconds();

		if (elapsed < 1.0f / 60.0f)
			continue;
		clock.restart();

		sf::Event event;

		while (window.pollEvent(event))
		{
			//handle window events
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
				audio.Play("explosion.wav");
		}

		audio.Update(elapsed);
	}

	return 0;
}