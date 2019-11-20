
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
	srand(14);
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


double polarAngle(const Point* p1, const Point* p2) {
	
	return 0;
}

double orientation(const Point* p0, const Point* p1, const Point* p2) {
	// Cross product of the vectors from p0 to p1/p2.
	// If positive, then counter clockwise turn
	// If negative, then clockwise turn
	// If zero then no turn
	int val = (p1->getPosition().x - p0->getPosition().x) * (p2->getPosition().y - p0->getPosition().y) - (p2->getPosition().x - p0->getPosition().x) * (p1->getPosition().y - p0->getPosition().y);
	if (val == 0) return 0;
	return (val > 0) ? -1 : 1;
}

std::vector<Point*> convexHull(std::vector<Point*>::iterator begin_it, std::vector<Point*>::iterator end_it) {

	Point* p0 = *std::min_element(begin_it, end_it, [](Point* a, Point* b) {
		return a->getPosition().y > b->getPosition().y;
	});

	std::sort(begin_it+1,  end_it, [p0](Point *a, Point *b) {
		double a1 = atan2((p0->getPosition().y - a->getPosition().y), (a->getPosition().x - p0->getPosition().x));
		double a2 = atan2((p0->getPosition().y - b->getPosition().y), (b->getPosition().x - p0->getPosition().x));
		if (a1 < a2) return true;
		else if (a1 == a2) {
			return Point::distance(*p0, *a) < Point::distance(*p0, *b);
		}
		else return false;
	});

	std::vector<Point*> v;
	
	v.push_back(*begin_it);
	v.push_back(*(begin_it+1));
	v.push_back(*(begin_it+2));

	for (auto it = begin_it + 3; it != end_it; it++) {
		while (orientation(v[v.size() - 2], v[v.size() - 1], *it) != 1)
			v.pop_back();
		v.push_back(*it);
	}

	return v;
}



int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
	
	std::vector<Point*> pointer_vector = makePoints(200);


	std::vector<Point*> ch = convexHull(pointer_vector.begin(), pointer_vector.end());

	for (auto p : ch) {
		p->setFillColor(sf::Color::Red);
	}


	Point* pd1 = nullptr;
	Point* pd2 = nullptr;
	double d2 = Point::closetPointSmart(pointer_vector.begin(), pointer_vector.end(), pd1, pd2);
	pd1->setFillColor(sf::Color::Yellow);
	pd2->setFillColor(sf::Color::Yellow);


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


	// Clear memory;
	for (auto p : pointer_vector) {
		delete p;
	}
	pointer_vector.clear();


	return 0;
} 