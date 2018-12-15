#include<SFML/Graphics.hpp>
#include<iostream>
#include<vector>
#include<string>
#include<thread>

constexpr int width = 1024;
constexpr int height = 512 + 32;

int main()
{
	std::string fileName;
	std::cout << "this program sorts a given image by its pixel's colour\ntop left is \"smallest\" (white) pixel and bottom right is \"largest\" (black)\n";
	std::cout << "you can put your images in the \"Images\" folder, please note that this program works best with images 512x512 or smaller\n\n";
	std::cout << "type \"example\" to use the example image\n";
	std::cout << "file name: (extension required)\n";
	std::getline(std::cin, fileName);

	if(fileName == "example")
		fileName = "greyscale.png";

	sf::Image before;
	sf::Image after;

	sf::Texture tBefore;
	sf::Texture tAfter;

	if(!before.loadFromFile("Images/" + fileName))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(2000));
		return EXIT_FAILURE;
	}
	auto size = before.getSize();
	auto index = [&](int x, int y) {return x + y * size.x; };

	std::vector<sf::Uint32> colorValues;
	colorValues.reserve(size.x * size.y);

	after.create(size.x, size.y, sf::Color::Black);

	for(int y = 0; y < size.y; y++)
	for(int x = 0; x < size.x; x++)
		colorValues.push_back(before.getPixel(x, y).toInteger());

	std::sort(colorValues.rbegin(), colorValues.rend());

	for(int y = 0; y < size.y; y++)
	for(int x = 0; x < size.x; x++)
	{
		auto color = colorValues[index(x, y)];
		after.setPixel(x, y, sf::Color(color));
	}

	tBefore.loadFromImage(before);
	tAfter.loadFromImage(after);

	sf::RectangleShape quadBefore({width / 2, static_cast<float>(height) - 32});
	quadBefore.setPosition(0, 32);
	quadBefore.setTexture(&tBefore);

	sf::RectangleShape quadAfter({width / 2, static_cast<float>(height) - 32});
	quadAfter.setPosition(width / 2, 32);
	quadAfter.setTexture(&tAfter);
			
	sf::Font font;
	font.loadFromFile("Images/pixel.ttf");

	sf::Text beforeText, afterText;

	beforeText.setFont(font);

	beforeText.setFillColor(sf::Color::Red);

	beforeText.setCharacterSize(24);
	beforeText.setString("Before:");
	beforeText.setPosition(4, 0);

	afterText.setFont(font);

	afterText.setFillColor(sf::Color::Green);

	afterText.setCharacterSize(24);
	afterText.setString("After:");
	afterText.setPosition((width / 2) + 4, 0);

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

		window.draw(quadBefore);
		window.draw(quadAfter);

		window.draw(beforeText);
		window.draw(afterText);

		window.display();
	}

	std::cout << "Press any key to continue...\n";
	std::cin.get();
	return EXIT_SUCCESS;
}