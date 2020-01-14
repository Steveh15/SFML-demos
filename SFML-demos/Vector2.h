#pragma once

#include <iostream>

class Vector2
{

private:

	double x;
	double y;

public:


	Vector2() : x(0), y(0) {};
	Vector2(const double& _x, const double& _y) : x(_x), y(_y) {};

	void setX(const double & _x) { x = _x; }
	void setY(const double & _y) { y = _y; }

	double getX() const { return x; }
	double getY() const { return y; }


	double norm() const;
	Vector2 normalise() const;


	friend double operator*(const Vector2& lhs, const Vector2& rhs);

	friend Vector2 operator*(const Vector2& vec, const double scalar);

	friend Vector2 operator*(const double scalar, const Vector2& vec);

	friend Vector2 operator/(const Vector2& vec, const double scalar);
	
	friend Vector2 operator+(const Vector2& lhs, const Vector2& rhs);

	friend Vector2 operator-(const Vector2& lhs, const Vector2& rhs);




	friend std::ostream& operator<<(std::ostream& out, Vector2 c);
};
