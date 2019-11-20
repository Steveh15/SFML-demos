#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Point : public sf::CircleShape
{

	using sf::CircleShape::CircleShape;


	friend std::ostream& operator<<(std::ostream& out, const Point& p);

};
