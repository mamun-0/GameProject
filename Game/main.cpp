//Liberies
#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>
int main(){
	
	//Creating window
	sf::RenderWindow window(sf::VideoMode(800, 600), "AI");
	window.setFramerateLimit(60);
	bool play = true;
	sf::Event event;

	//State
	bool up = false, down = false;
	
	//Variables

	int velocityPad1 = 0;
	int miniballXVelocity = -3;
	int miniballYVelocity = -3;
	int velocityPad2 = 0;
	//========LoadFiles====
	sf::Texture pad;
	if (pad.loadFromFile("MyFile/bar.png") == false) return -1;
	sf::Texture pad1;
	if (pad1.loadFromFile("MyFile/bar1.png") == false) return -1;
	sf::Texture ball;
	if (ball.loadFromFile("MyFile/ball.png") == false) return -1;
	sf::Texture background;
	if (background.loadFromFile("MyFile/background.jpg") == false) return -1;
	
	//=======Create shapes====
	
	//background
	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(800, 600));
	rectangle.setPosition(0, 0);
	rectangle.setTexture(&background);

	//FirstPad

	sf::RectangleShape shape1;
	shape1.setSize(sf::Vector2f(40, 150));
	shape1.setPosition(15,200);
	shape1.setTexture(&pad);

	//Second Pad
	sf::RectangleShape shape2;
	shape2.setSize(sf::Vector2f(40, 150));
	shape2.setPosition(750, 300);
	shape2.setTexture(&pad1);

	//Ball

	sf::RectangleShape miniball;
	miniball.setSize(sf::Vector2f(50, 50));
	miniball.setPosition(400, 500);
	miniball.setTexture(&ball);
	
	while (play == true)
	{

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) play = false;
			//Key Pressed section
			if (event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Up) {
				up = true;
			}
			if (event.type == sf::Event::KeyPressed &&
				event.key.code == sf::Keyboard::Down) {
				down = true;
			}
			//============Key Released section
			if (event.type == sf::Event::KeyReleased &&
				event.key.code == sf::Keyboard::Up) {
				up = false;
			}
			if (event.type == sf::Event::KeyReleased &&
				event.key.code == sf::Keyboard::Down) {
				down = false;
			}
		}

		//Logic
		if (up == true) {
			velocityPad1 = -5;
		}
		if (down == true) {
			velocityPad1 = 5;
		}
		if (up == true && down == true) {
			velocityPad1 = 0;
		}
		if (up == false && down == false) {
			velocityPad1 = 0;
		}


		shape1.move(0, velocityPad1);
		miniball.move(miniballXVelocity, miniballYVelocity);
		//Check pad out of bound
		if (shape1.getPosition().y < 0)
			shape1.setPosition(15, 0);

		if (shape1.getPosition().y > 450)
			shape1.setPosition(15, 450);
		if (miniball.getPosition().y < 0)
			miniballYVelocity = -miniballYVelocity;
		if (miniball.getPosition().y > 550)
			miniballYVelocity = -miniballYVelocity;
		//Pad2 AI
		if (miniball.getPosition().y < shape2.getPosition().y){
			velocityPad2 = -3;
		}
		if (miniball.getPosition().y > shape2.getPosition().y)
			velocityPad2 = 3;
		shape2.move(0, velocityPad2);
		//Collision for Pad 1
		if (miniball.getGlobalBounds().intersects(shape1.getGlobalBounds()) == true)
			miniballXVelocity = -miniballXVelocity;
		//Collision for Pad 2
		if (miniball.getGlobalBounds().intersects(shape2.getGlobalBounds()) == true)
			miniballXVelocity = -miniballXVelocity;
		std::cout << miniball.getPosition().x<<"\t"<<miniball.getPosition().y<<"\n";
		//Rendering part
		window.clear();
		//Drawing
		window.draw(rectangle);
		window.draw(shape1);
		window.draw(shape2);
		window.draw(miniball);
		window.display();
	}
	
	window.close();
	return 0;
}