#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


const int floor_height = 90, elevator_height = floor_height, floor_width = 100, elevator_width = floor_width;

const int elevator_speed = 200;    // piksele na sekundy
const int number_of_floors = 7;           
const int passenger_mass = 70;   // waga w kg
const int max_passengers = 8;    


sf::RectangleShape createFloor(int height);
sf::RectangleShape createElevator();
sf::Text print_text(const std::string& content, const sf::Font& font, unsigned int size, const sf::Color& color, float x, float y);


int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Winda");

	sf::Texture backgroundImage;
	if (!backgroundImage.loadFromFile("szary.jpg"))
	{
		std::cerr << "Nie można załadować obrazu tła." << std::endl;
		return 1;
	}

	sf::Sprite backgroundSprite(backgroundImage);

	sf::RectangleShape elevator = createElevator();

	std::vector<sf::RectangleShape> floors_to_draw;
	for (int i = number_of_floors; i >= 0; --i)
	{
		sf::RectangleShape floor = createFloor(i * floor_height);
		floors_to_draw.push_back(floor);
	}

	sf::Font font;
	if (!font.loadFromFile("ARIAL.TTF"))
	{
		return -1;
	}
	sf::Text weightText = print_text("Total Weight: 0 kg", font, 30, sf::Color::Black, 300, 10);

	sf::Text passenger_counter("", font, 55); // Tekst do wyświetlania aktualnej liczby pasażerów
	passenger_counter.setFillColor(sf::Color::White);
	passenger_counter.setPosition(elevator_width/ 2 - 15, elevator_height / 2 - 20);
	passenger_counter.setOrigin(passenger_counter.getLocalBounds().width / 2, passenger_counter.getLocalBounds().height / 2); //Ustawienie współrzędnych punktu odniesienia tekstu na jego środek 

    int total_weight = 0
	sf::Text instruction_text = print_text("INSTRUCTIONS\n\n"
		"1. Press 'Add passenger' button \n"
		"2. Select the floor\n"
		"3. Select the destination\n"
		"4. After selecting all passengers, press ENTER\n"
		"5. Enjoy the simulation", font, 20, sf::Color::White, 700, 10);
	instruction_text.setOutlineThickness(2); // Ustaw grubość konturu tekstu na 2 piksele
	instruction_text.setOutlineColor(sf::Color::Black);

	sf::Clock clock;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{


			if (event.type == sf::Event::Closed)
				window.close();


			// tworzenie tekstu liczby pasazerow i ich masy
			weightText.setString("Total Weight: " + std::to_string(int(total_weight)) + " kg");
			passenger_counter.setString(std::to_string(int(total_weight / 70)));
		}
		
		window.clear(sf::Color::White);
		
		window.draw(backgroundSprite); //wazne, aby narysowac tlo na samym poczatku
		// rysowanie kazdego pietra
		for (const auto& floor : floors_to_draw)
		{
			window.draw(floor);
		}
		window.draw(elevator); //winda
		window.draw(weightText); // masa pasazerow
		window.draw(passenger_counter); // liczba pasazerow
		window.draw(instruction_text);
		

		
		window.display();
	}

	return 0;
}

sf::RectangleShape createFloor(int height)
{
	sf::RectangleShape floor(sf::Vector2f(floor_width, floor_height));
	floor.setPosition(0, height);
	floor.setFillColor(sf::Color::White);
	floor.setOutlineThickness(2);
	floor.setOutlineColor(sf::Color::Black);
	return floor;
}

sf::RectangleShape createElevator()
{
	sf::RectangleShape elevator(sf::Vector2f(elevator_width, elevator_height));
	elevator.setFillColor(sf::Color::Red);
	elevator.setOutlineThickness(4);
	elevator.setOutlineColor(sf::Color::Black);
	return elevator;
}

sf::Text print_text(const std::string& content, const sf::Font& font, unsigned int size, const sf::Color& color, float x, float y)
{
	sf::Text text(content, font, size);
	text.setFillColor(color);
	text.setPosition(x, y);
	return text;
}