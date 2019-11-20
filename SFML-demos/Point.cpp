#include "Point.h"
#include <iostream>


std::ostream& operator<<(std::ostream& out, const Point& p) {
	return out <<  "(" << p.getPosition().x << ", " << p.getPosition().y << ")";
}