#include <SFML/Graphics.hpp>
#include "Group.h"
#include "Constants.h"

int main()
{
	printf("Controls:\n");
	printf("	Mouse - Move Particals\n\n");
	printf("	Arrows - Move\n\n");
	printf("	W - Zoom In\n");
	printf("	S - Zoom Out\n\n\n");

	printf("Particals: %i\n", amount);
	printf("Square Width/Height: %i\n", sqrtAmount);

	sf::ContextSettings set;
	set.antialiasingLevel = 16;

	sf::RenderWindow window(sf::VideoMode(width, height), "Particals", sf::Style::Close, set);
	Group par = Group();

	sf::Clock clock;
	float lastTime = 0;
	float currentTime = clock.restart().asSeconds();
	float fps = 1.f / currentTime;
	while (window.isOpen())
	{
		sf::Event evnt;
		while (window.pollEvent(evnt))
            switch (evnt.type){ case sf::Event::Closed: window.close();	break; }

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			par.updateMouse(sf::Mouse::getPosition(window), false);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
			par.updateMouse(sf::Mouse::getPosition(window), true);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			par.cam.offSet.y += speed / fps;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			par.cam.offSet.y -= speed / fps;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			par.cam.offSet.x += speed / fps;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			par.cam.offSet.x -= speed / fps;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			par.cam.zoom *= 1.f + (zSpeed / fps);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			if (par.cam.zoom > maxZoom)
				par.cam.zoom /= 1.f + (zSpeed / fps);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			par.reset();

		window.clear(sf::Color(16, 16, 16));
		par.drawUpdate(window, fps);
		window.display();

		currentTime = clock.restart().asSeconds();
		fps = 1.f / currentTime;
	}

	return 0;
}
