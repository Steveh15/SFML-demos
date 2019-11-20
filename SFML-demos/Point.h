#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Point : public sf::CircleShape
{

public:
	using sf::CircleShape::CircleShape;



	static double distance(const Point& p1, const Point& p2);
	static double closetPointBruteForce(std::vector<Point*>::iterator begin_it, std::vector<Point*>::iterator end_it, Point*& p1, Point*& p2);
	static double closestStrip(std::vector<Point*>::iterator it1, std::vector<Point*>::iterator it2, Point*& p1, Point*& p2, double d);
	static double closetPointSmart(std::vector<Point*>::iterator it1, std::vector<Point*>::iterator it2, Point*& p1, Point*& p2);

	friend std::ostream& operator<<(std::ostream& out, const Point& p);



};
