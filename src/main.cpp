#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<string>

constexpr int width = 1024;
constexpr int height = 512;

int main()
{
	std::string fileName = "greyscale.png";
	sf::RenderWindow window(sf::VideoMode(width, height), "Image Sorter", sf::Style::Close);

	sf::Image before;
	sf::Image after;

	sf::Texture tBefore;
	sf::Texture tAfter;

	before.loadFromFile(fileName);
	auto size = before.getSize();
	auto index = [&](int x, int y) {return x + y * size.x; };

	std::vector<sf::Uint32> colorValues;
	colorValues.reserve(size.x * size.y);

	after.create(size.x, size.y, sf::Color::Black);

	for(int y = 0; y < size.y; y++)
	for(int x = 0; x < size.x; x++)
		colorValues.push_back(before.getPixel(x, y).toInteger());

	std::sort(colorValues.rbegin(), colorValues.rend());
	//for(auto& i : colorValues)
	//	std::cout << i << std::endl;

	for(int y = 0; y < size.y; y++)
	for(int x = 0; x < size.x; x++)
	{
		auto color = colorValues[index(x, y)];
		after.setPixel(x, y, sf::Color(color));
	}

	tBefore.loadFromImage(before);
	tAfter.loadFromImage(after);

	sf::RectangleShape quadBefore({width / 2, static_cast<float>(height)});
	quadBefore.setTexture(&tBefore);

	sf::RectangleShape quadAfter({width / 2, static_cast<float>(height)});
	quadAfter.setPosition(width / 2, 0);
	quadAfter.setTexture(&tAfter);
			

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

		window.draw(quadBefore);
		window.draw(quadAfter);

		window.display();
	}

	std::cout << "Press any key to continue...\n";
	std::cin.get();
	return 0;
}