#pragma once

#include "Particle.h"

#include <windows.h>



namespace NBody {

	//prouces a random double between 0 and 1
	double dRand() {
		// rand() produces a random integer between 0 and RAND_MAX
		return (double)rand() / RAND_MAX;
	}


	std::vector<Point*> makePoints() {
		//srand(time(NULL));
		//srand(16);
		std::vector<Point*> v(1);

		for (auto& p : v) {
			p = new Point();
			p->setRadius(2.5);
			p->setFillColor(sf::Color::Black);
			p->setPosition(sf::Vector2f(400, 400));
			p->setOrigin(sf::Vector2f(2.5, 2.5));
		}

		return v;
	}

	void makePoint(std::vector<Particle*> & particle_vector, double _mass, double _x, double _y, double _vx, double _vy) {

		double size = 1.5;
		Particle* new_particle = new Particle(_mass, Vector2(_x,_y), Vector2(_vx, _vy));
		new_particle->setRadius(size);
		new_particle->setFillColor(sf::Color::Black);
		new_particle->setOrigin(sf::Vector2f(size, size));
		particle_vector.push_back(new_particle);
	}


	void doDemo(sf::RenderWindow& window) {


		double dt = 1.f/5000.f;
		std::vector<Particle*> particle_vector;
		//makePoint(particle_vector, 10, 0, 0, 0, 0);


		double mass_sun = 10;
		double mass_earth = mass_sun * 0.000003;
		double mass_moon = mass_earth * 0.02;


		double sun_earth_distance = 2;
		double moon_earth_distance = sun_earth_distance * 0.3843 / 147.14;

		double earth_velocity = sqrt((mass_sun + mass_earth) / sun_earth_distance);
		double moon_velocity = sqrt((mass_earth + mass_moon) / moon_earth_distance);

		//makePoint(particle_vector, mass_sun, 0, 0, 0, 0);
		//makePoint(particle_vector, mass_earth, sun_earth_distance, 0, 0, earth_velocity);


		makePoint(particle_vector, mass_sun, 0, 0, 0, 0);
		makePoint(particle_vector, mass_earth, sun_earth_distance, 0, 0, earth_velocity);
		makePoint(particle_vector, mass_moon, sun_earth_distance + moon_earth_distance, 0, 0, moon_velocity+ earth_velocity);



		//makePoint(particle_vector, 0.001, 2, 0, 0, 0.4);
		//makePoint(particle_vector, mass_moon, 1.002, 0, 0, 1.000007);


		//particle_vector[1]->updateVelocityGravity(dt/2, *particle_vector[0]);
		//particle_vector[0]->updateVelocityGravity(dt/2, *particle_vector[1]);

		for (std::vector<Particle*>::iterator it1 = particle_vector.begin(); it1 != particle_vector.end(); it1++) {
			for (std::vector<Particle*>::iterator it2 = it1+1; it2 != particle_vector.end(); it2++) {
				(*it1)->updateVelocityGravity(dt / 2, **it2);
				(*it2)->updateVelocityGravity(dt / 2, **it1);
			}
		}



			while (window.isOpen())
			{
				//Sleep(1);

				//std::cout << particle_vector[0]->getPosition() << "\n";

				sf::Event event;
				while (window.pollEvent(event))
				{
					if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
						window.close();
				}

				window.clear(sf::Color(204, 230, 255));


				for (auto p : particle_vector) {
					p->updatePosition(dt);
				}




				for (auto p : particle_vector) {
					window.draw(*p);
				}




				//particle_vector[1]->updateVelocityGravity(dt, *particle_vector[0]);
				//particle_vector[0]->updateVelocityGravity(dt, *particle_vector[1]);

				for (std::vector<Particle*>::iterator it1 = particle_vector.begin(); it1 != particle_vector.end(); it1++) {
					for (std::vector<Particle*>::iterator it2 = it1+1; it2 != particle_vector.end(); it2++) {
						(*it1)->updateVelocityGravity(dt, **it2);
						(*it2)->updateVelocityGravity(dt, **it1);
					}
				}

				window.display();
			}

		// Clear memory;
		for (auto p : particle_vector) {
			delete p;
		}
		particle_vector.clear();

	}




};