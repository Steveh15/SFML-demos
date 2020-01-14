#pragma once
#include "Point.h"

#include <SFML/Graphics.hpp>
#include <string>
#include "Vector2.h"

class Particle :
	public Point
{

private:
	double mass;
	std::string label;
	Vector2 position;
	Vector2 velocity;



public:


	Particle(double _mass) : mass(_mass) {
		this->setPosition(position.getX(), position.getY());
	}

	Particle(double _mass, Vector2 _position, Vector2 _velocity) : mass(_mass) , position(_position), velocity(_velocity)  {
		this->setPosition(position.getX(), position.getY());
	}


	double getMass() const { return mass; }
	double getKineticEnergy() const {
		return 0.5 * mass * velocity * velocity;
	}

	Vector2 getPosition() const {
		return position;
	}

	void updateVelocity(double dt, Vector2 force) {
		velocity = velocity + (force * dt) / mass;
	}

	void updatePosition(double dt) {
		position = position + velocity * dt;
		double screen_width = 950;
		double distance_1 = 200;
		this->setPosition(screen_width /2 + distance_1 *position.getX(), screen_width/2 - distance_1 *position.getY());
	}

	void updatePoint() {
		this->setPosition(400+position.getX(), 400-position.getY());
	}

	void updateVelocityGravity(double dt, const Particle& p) {

		Vector2 r = position - p.getPosition();

		Vector2 force = -this->getMass()* p.getMass()* r.normalise() / pow(r.norm(), 2);
		velocity = velocity + (force * dt) / mass;
	}

};

