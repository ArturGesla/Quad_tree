#include "implicitgeometry.hpp"
implicit::Circle::Circle(double x, double y, double r) :
	x_(x), y_(y), radius_(r)
{ }
bool implicit::Circle::inside(double x, double y) const
{
	double dx = x - x_;
	double dy = y - y_;
	return dx * dx + dy * dy <= radius_ * radius_;
}

