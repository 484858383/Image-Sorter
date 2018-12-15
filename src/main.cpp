#include<SFML/Graphics.hpp>
#include<iostream>

constexpr int width = 512;
constexpr int height = 512;

int main()
{
	std::cout << "g\n";


	sf::RenderWindow window(sf::VideoMode(width, height), "Image Sorter", sf::Style::Close);


	while(window.isOpen())
	{
		sf::Event e;
		while(window.pollEvent(e))
		{
			if(e.type == sf::Event::Closed)
				window.close();
			if(e.type == sf::Event::KeyReleased)
				if(e.key.code == sf::Keyboard::Escape)
					window.close();
		}

		window.clear();


		window.display();
	}

	std::cin.get();
	return 0;
}