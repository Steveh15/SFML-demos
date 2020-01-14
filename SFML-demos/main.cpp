
#include <SFML/Graphics.hpp>

#include <iostream>
//#include <deque>
//#include <iterator>
//#include <algorithm>
//#include <iostream>
//#include <vector>
//#include <utility>
//#include <stdlib.h>
//#include <ctime>
#include "CompGeom.hpp"
#include "NBody.hpp"

//
//#include "boost/graph/adjacency_list.hpp"
//#include "boost/graph/topological_sort.hpp"

#include "Point.h"
#include "Vector2.h"




int main()
{

	
	std::unique_ptr<sf::RenderWindow> window(new sf::RenderWindow(sf::VideoMode(950, 950), "SFML works!"));



	//CompGeom::doDemo(*window);
	NBody::doDemo(*window);



	//Vector2 v1(1, 2);
	//Vector2 v2(3, 2);

	//std::cout << v1 << "\n";
	//std::cout << v2 << "\n";
	//std::cout << v2*v1 << "\n";
	//std::cout << 5*v1 << "\n";
	//std::cout << v1*5 << "\n";
	//std::cout << v1.norm() << "\n";
	//std::cout << v1.normalise() << "\n";
	//Vector2 normed = v2.normalise();

	//std::cout << normed << "\n";
	//std::cout << normed.norm() << "\n";

	



	return 0;
} 