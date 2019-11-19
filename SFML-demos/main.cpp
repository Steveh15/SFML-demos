#include <SFML/Graphics.hpp>

#include <algorithm>
#include <iostream>
#include <vector>
#include <utility>
#include <stdlib.h>
#include <ctime>

#include "Point.h"

double distance(const Point& p1, const Point& p2) {
	double x1 = p1.getPosition().x;
	double x2 = p2.getPosition().x;
	double y1 = p1.getPosition().y;
	double y2 = p2.getPosition().y;
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double closetPointBruteForce(std::vector<Point>::iterator begin_it, std::vector<Point>::iterator end_it, Point*& p1, Point*& p2) {
	double min_distance = 100000;

	for (auto i = begin_it; i != end_it; ++i) {
		for (auto j = i + 1; j != end_it; ++j) {
			if (distance(*i, *j) < min_distance) {
				min_distance = distance(*i, *j);
				p1 = &*begin_it + (i - begin_it);
				p2 = &*begin_it + (j - begin_it);
			}
		}
	}
	return min_distance;
}


double closestStrip(std::vector<Point>::iterator it1, std::vector<Point>::iterator it2, Point*& p1, Point*& p2, double d) {

	double min = d;

	std::sort(it1, it2, [](Point a, Point b) {
		return a.getPosition().y > b.getPosition().y;
	});

	for (auto i = it1; i != it2; ++i) {

		for (auto j = i + 1; j != it2; ++j) {
			if (abs(j->getPosition().y - i->getPosition().y) < min) {

				if (distance(*i, *j) < min) {
					min = distance(*i, *j);
					p1 = &*it1 + (i - it1);
					p2 = &*it1 + (j - it1);
				}
			}
		}
	}

	return min;
}


double closetPointSmart(std::vector<Point>::iterator it1, std::vector<Point>::iterator it2, Point*& p1, Point*& p2) {


	std::sort(it1, it2, [](Point a, Point b) {
		return a.getPosition().x < b.getPosition().x;
	});

	int size = it2 - it1;
	Point* lp1 = nullptr;
	Point* lp2 = nullptr;
	Point* rp1 = nullptr;
	Point* rp2 = nullptr;

	if (size < 4)
		return closetPointBruteForce(it1, it2, p1, p2);

	double lmin = closetPointSmart(it1, it1 + size / 2, lp1, lp2);
	double rmin = closetPointSmart(it1 + size / 2, it2, rp1, rp2);

	double min;
	if (lmin < rmin) {
		min = lmin;
		p1 = lp1;
		p2 = lp2;
	}
	else {
		min = rmin;
		p1 = rp1;
		p2 = rp2;
	}

	auto first = std::find_if(it1, it2, [it1, size, min](Point a) {
		return a.getPosition().x >= ((it1 + size / 2)->getPosition().x - min);
	});
	auto last = std::find_if(it1, it2, [it1, size, min](Point a) {
		return a.getPosition().x > ((it1 + size / 2)->getPosition().x + min);
	});


	if (first == last) {
		return min;
	}
	else {
		Point* strip_p1 = nullptr;
		Point* strip_p2 = nullptr;
		double min_strip = closestStrip(first, last, strip_p1, strip_p2, min);

		if (min_strip < min) {
			min = min_strip;
			p1 = strip_p1;
			p2 = strip_p2;
		}

	}

	return min;
}


int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

	//srand(time(NULL));
	srand(9);

	std::vector<Point> point_vector(10000);
	//std::vector<Point> point_vector(5000); 
	//std::vector<Point> point_vector(1000);

	for (auto& p : point_vector) {
		p.setRadius(2.5);
		//p.setFillColor(sf::Color::Black);
		p.setFillColor(sf::Color(204, 230, 255));
		p.setPosition(rand() % 751 + 25, rand() % 751 + 25);
	}

	std::sort(point_vector.begin(), point_vector.end(), [](Point a, Point b) {
		return a.getPosition().x < b.getPosition().x;
	}); 

	Point* p1 = nullptr;
	Point* p2 = nullptr;
	Point* pd1 = nullptr;
	Point* pd2 = nullptr;




	//double brute = closetPointBruteForce(point_vector.begin(), point_vector.end(), p1, p2);


	//p1->setFillColor(sf::Color::Red);
	//p2->setFillColor(sf::Color::Red);
	//window.draw(*p1);
	//window.draw(*p2);
	//std::cout << "(" << p1->getPosition().x << ", " << p1->getPosition().y << ") -> (" << p2->getPosition().x << ", " << p2->getPosition().y << ")\n";


	double divide = closetPointSmart(point_vector.begin(), point_vector.end(), pd1, pd2);

	pd1->setFillColor(sf::Color::Yellow);
	pd2->setFillColor(sf::Color::Yellow);
	window.draw(*pd1);
	window.draw(*pd2);

	std::cout << "(" << pd1->getPosition().x << ", " << pd1->getPosition().y << ") -> (" << pd2->getPosition().x << ", " << pd2->getPosition().y << ")\n";

	//std::cout << "Brute force : " << brute << "\n";
	std::cout << "DaC force : " << divide << "\n";

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
				window.close();
		}

	/*	for (auto p : point_vector) {
			window.draw(p);
		}*/

		//window.clear(sf::Color(204, 230, 255)); 

		//p1->setFillColor(sf::Color::Red);
		//p2->setFillColor(sf::Color::Red);
		//window.draw(*p1);
		//window.draw(*p2);



		window.display();
	}
	return 0;
}