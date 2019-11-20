#include "Point.h"
#include <iostream>


std::ostream& operator<<(std::ostream& out, const Point& p) {
	return out <<  "(" << p.getPosition().x << ", " << p.getPosition().y << ")";
}

double Point::distance(const Point& p1, const Point& p2)
{
	double x1 = p1.getPosition().x;
	double x2 = p2.getPosition().x;
	double y1 = p1.getPosition().y;
	double y2 = p2.getPosition().y;
	return sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

double Point::closetPointBruteForce(std::vector<Point*>::iterator begin_it, std::vector<Point*>::iterator end_it, Point*& p1, Point*& p2)
{
	double min_distance = INFINITY;

	for (auto i = begin_it; i != end_it; ++i) {
		for (auto j = i + 1; j != end_it; ++j) {
			if (Point::distance(**i, **j) < min_distance) {
				min_distance = Point::distance(**i, **j);
				p1 = *i;
				p2 = *j;
			}
		}
	}
	return min_distance;
}

double Point::closestStrip(std::vector<Point*>::iterator it1, std::vector<Point*>::iterator it2, Point*& p1, Point*& p2, double d)
{
	double min = d;

	std::sort(it1, it2, [](Point* a, Point* b) {
		return a->getPosition().y > b->getPosition().y;
	});

	for (auto i = it1; i != it2; ++i) {
		for (auto j = i + 1; j != it2; ++j) {
			if (abs((*j)->getPosition().y - (*i)->getPosition().y) < min) {

				if (Point::distance(**i, **j) < min) {
					min = Point::distance(**i, **j);
					p1 = *i;
					p2 = *j;
				}
			}
		}
	}
	return min;
}

double Point::closetPointSmart(std::vector<Point*>::iterator it1, std::vector<Point*>::iterator it2, Point*& p1, Point*& p2)
{
	// it1 = first point
		// it2 = memory space after last point
		// ithalf = half way point (middle if odd, upper middle if even)

		// Sort by x
	std::sort(it1, it2, [](Point* a, Point* b) {
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
	// part 2 :  All points from halfway point (including) to last point
	double lmin = closetPointSmart(it1, ithalf, lp1, lp2);
	double rmin = closetPointSmart(ithalf, it2, rp1, rp2);

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


