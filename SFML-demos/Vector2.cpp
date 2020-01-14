#include "Vector2.h"
#include <cmath>

double operator*(const Vector2& lhs, const Vector2& rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

Vector2 operator*(const Vector2& vec, const double scalar)
{
	return Vector2(vec.x * scalar, vec.y * scalar);
}

Vector2 operator*(const double scalar, const Vector2& vec)
{
	return Vector2(vec.x * scalar, vec.y * scalar);
}

Vector2 operator/(const Vector2& vec, const double scalar)
{
	return Vector2(vec.x / scalar, vec.y / scalar);
}

Vector2 operator+(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x+ rhs.x, lhs.y + rhs.y);
}

Vector2 operator-(const Vector2& lhs, const Vector2& rhs)
{
	return Vector2(lhs.x - rhs.x, lhs.y - rhs.y);
}

std::ostream& operator<<(std::ostream& out, Vector2 c)
{
	out << "{" << c.x << ", " << c.y << "}";
	return out;
}
 
double Vector2::norm() const
{
	return sqrt(x*x + y*y);
}

Vector2 Vector2::normalise() const
{
	return Vector2(x,y)*(1/this->norm());
}


