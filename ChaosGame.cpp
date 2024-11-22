// Include important C++ libraries here
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <sstream>
#include <vector>
#include <random>

//Make the code easier to type with "using namespace"
using namespace sf;
using namespace std;

int main()
{
	// Create a video mode object
	VideoMode vm(1920, 1080);
	// Create and open a window for the game
	RenderWindow window(vm, "Chaos Game!!", Style::Default);

	vector<Vector2f> vertices;
	vector<Vector2f> points;

	//FROM ME: choosing font
	Font font;
	font.loadFromFile("Arial.ttf");

	//FROM ME: customising text style and setting the message
	Text welcome;
	welcome.setFont(font);
	welcome.setFillColor(sf::Color::Green);
	welcome.setString("Please click in any 3 spots to make a triangle and then click again start the program");

	//FROM ME: RNG
	int min = 0;
	int max = 2;
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<> distrib(min, max);
	int randVal;

	//FROM ME: float 2
	float two = 2;

	while (window.isOpen())
	{
		

		/*
		****************************************
		Handle the players input
		****************************************
		*/
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				// Quit the game when the window is closed
				window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					std::cout << "the left button was pressed" << std::endl;
					std::cout << "mouse x: " << event.mouseButton.x << std::endl;
					std::cout << "mouse y: " << event.mouseButton.y << std::endl;

					if (vertices.size() < 3)
					{
						vertices.push_back(Vector2f(event.mouseButton.x, event.mouseButton.y));
					}
					else if (points.size() == 0)
					{
						///fourth click
						///push back to points vector
						/// FROM ME: first point to use in algorithm
						Vector2f coord(event.mouseButton.x, event.mouseButton.y);
						points.push_back(coord);

					}
				}
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		/*
		****************************************
		Update
		****************************************
		*/

		if (points.size() > 0)
		{
			///generate more point(s)
			///select random vertex
			///calculate midpoint between random vertex and the last point in the vector
			///push back the newly generated coord.
			
			randVal = distrib(gen);

			Vector2f newCoord(((vertices[randVal].x + points.back().x) / two), ((vertices[randVal].y + points.back().y) / two));
			
			points.push_back(newCoord);

		}

		/*
		****************************************
		Draw
		****************************************
		*/
		window.clear();
		//FROM ME: draw the welcome message in the window
		window.draw(welcome);
		for (int i = 0; i < vertices.size(); i++)
		{
			RectangleShape rect(Vector2f(5, 5));
			rect.setPosition(Vector2f(vertices[i].x, vertices[i].y));
			rect.setFillColor(Color::Blue);
			window.draw(rect);
		}

		//FROM ME: draw new points
		for (int i = 0; i < points.size(); i++)
		{
			RectangleShape rect(Vector2f(5, 5));
			rect.setPosition(Vector2f(points[i].x, points[i].y));
			rect.setFillColor(Color::Green);
			window.draw(rect);
		}
		window.display();
	}
}