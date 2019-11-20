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

double closetPointBruteForce(std::vector<Point*>::iterator begin_it, std::vector<Point*>::iterator end_it, Point*& p1, Point*& p2) {
	double min_distance = INFINITY;

	for (auto i = begin_it; i != end_it; ++i) {
		for (auto j = i + 1; j != end_it; ++j) {
			if (distance(**i, **j) < min_distance) {
				min_distance = distance(**i, **j);
				p1 = *i;
				p2 = *j;
			}
		}
	}
	return min_distance;
}

double closestStrip(std::vector<Point*>::iterator it1, std::vector<Point*>::iterator it2, Point*& p1, Point*& p2, double d) {

	double min = d;

	std::sort(it1, it2, [](Point* a, Point* b) {
		return a->getPosition().y > b->getPosition().y;
	});

	for (auto i = it1; i != it2; ++i) {
		for (auto j = i + 1; j != it2; ++j) {
			if (abs((*j)->getPosition().y - (*i)->getPosition().y) < min) {

				if (distance(**i, **j) < min) {
					min = distance(**i, **j);
					p1 = *i;
					p2 = *j;
				}
			}
		}
	}
	return min;
}


double closetPointSmart(std::vector<Point*>::iterator it1, std::vector<Point*>::iterator it2, Point*& p1, Point*& p2) {
	// it1 = first point
	// it2 = memory space after last point
	// ithalf = half way point (middle if odd, upper middle if even)

	// Sort by x
	std::sort(it1, it2, [](Point * a, Point * b) {
		return a->getPosition().x < b->getPosition().x;
	});

	int size = it2 - it1;
	auto ithalf = it1 + size / 2;
	double min = INFINITY;

	Point* lp1 = nullptr;
	Point* lp2 = nullptr;
	Point* rp1 = nullptr;
	Point* rp2 = nullptr;

	if (size < 4)
		return closetPointBruteForce(it1, it2, p1, p2);

	// divide into two parts
	// part 1 : All points up to but not including halfway point
	// part 2 :  All points from halway point (including) to last point
	double lmin = closetPointSmart(it1, it1 + size / 2, lp1, lp2);
	double rmin = closetPointSmart(it1 + size / 2, it2, rp1, rp2);

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


	// Build strip which contains all the points points within distance d of the halway point where d = min
	double l_band = (**ithalf).getPosition().x - min;
	double r_band = (**ithalf).getPosition().x + min;

	// Find first point where x is >= lband
	// Find first point where x >= rband
	auto first = std::find_if(it1, it2, [l_band](Point* a) {
		return a->getPosition().x > l_band;
	});

	auto last = std::find_if(it1, it2, [r_band](Point* a) {
		return a->getPosition().x > r_band;
	});

	// Possibilities
	// 0 points in strip (skip search): first = last
	// 1 point in strip (skip search) : first + 1 = last 
	// 2 or more points in strip

	if (first == last || ((first + 1) == last)) {
		//std::cout << "Cond1\n";
		return min;
	}
	else {
		//std::cout << "Cond2\n";
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

//prouces a random double between 0 and 1
double dRand() {
	// rand() produces a random integer between 0 and RAND_MAX
	return (double)rand() / RAND_MAX;
}



int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");

	//srand(time(NULL));
	srand(9);

	int n_point = 10000;
	//int n_point = 5000; // Produces bug
	//int n_point = 1000;

	std::vector<Point> point_vector(n_point);
	std::vector<Point*> pointer_vector(n_point);



	for (int i = 0; i < n_point; i++) {
		point_vector[i].setRadius(2.5);
		//point_vector[i].setFillColor(sf::Color::Black);
		point_vector[i].setFillColor(sf::Color(204, 230, 255));
		point_vector[i].setPosition(dRand() * 750 + 25, dRand() * 750 + 25);
		//point_vector[i].setPosition(round(dRand() * 750 + 25), round(dRand() * 750 + 25));

		pointer_vector[i] = &point_vector[i];
	}


	std::sort(pointer_vector.begin(), pointer_vector.end(), [](Point* a, Point* b) {
		return a->getPosition().x < b->getPosition().x;
	});

	Point* p1 = nullptr;
	Point* p2 = nullptr;

	double d1 = closetPointBruteForce(pointer_vector.begin(), pointer_vector.end(), p1, p2);

	std::cout << "Brute force:\n";
	std::cout << "p1 : " << *p1 << "\n";
	std::cout << "p2 : " << *p2 << "\n";
	std::cout << "distance : " << d1 << "\n";

	p1->setFillColor(sf::Color::Yellow);
	p2->setFillColor(sf::Color::Yellow);


	Point* pd1 = nullptr;
	Point* pd2 = nullptr;

	double d2 = closetPointSmart(pointer_vector.begin(), pointer_vector.end(), pd1, pd2);
	std::cout << "Divide and Conquer force:\n";
	std::cout << "p1 : " << *pd1 << "\n";
	std::cout << "p2 : " << *pd2 << "\n";
	std::cout << "distance : " << d2 << "\n";


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

		for (auto p : point_vector) {
			window.draw(p);
		}


		window.draw(*p1);
		window.draw(*p2);
		window.draw(*pd1);
		window.draw(*pd2);

		window.display();
	}
	return 0;
} 