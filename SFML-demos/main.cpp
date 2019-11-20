#include <SFML/Graphics.hpp>

#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <ctime>

#include "Point.h"


//prouces a random double between 0 and 1
double dRand() {
	// rand() produces a random integer between 0 and RAND_MAX
	return (double)rand() / RAND_MAX;
}

std::vector<Point*> makePoints(const int & n_points) {
	//srand(time(NULL));
	srand(9);
	std::vector<Point*> v(n_points);
	for (auto& p : v){
		p = new Point();
		p->setRadius(2.5);
		p->setFillColor(sf::Color::Black);
		//p->setFillColor(sf::Color(204, 230, 255));
		p->setPosition(dRand() * 750 + 25, dRand() * 750 + 25);
		//point_vector[i].setPosition(round(dRand() * 750 + 25), round(dRand() * 750 + 25));
	}
	std::sort(v.begin(), v.end(), [](Point* a, Point* b) {
		return a->getPosition().x < b->getPosition().x;
	});
	return v;
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
	
	std::vector<Point*> pointer_vector = makePoints(250);

	Point* pd1 = nullptr;
	Point* pd2 = nullptr;
	double d2 = Point::closetPointSmart(pointer_vector.begin(), pointer_vector.end(), pd1, pd2);
	pd1->setFillColor(sf::Color::Red);
	pd2->setFillColor(sf::Color::Red);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
				window.close();
		}

		window.clear(sf::Color(204, 230, 255));

		for (auto p : pointer_vector) {
			window.draw(*p);
		}

		window.display();
	}
	return 0;
} 