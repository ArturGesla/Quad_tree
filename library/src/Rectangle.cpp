#include "implicitgeometry.hpp"

implicit::Rectangle::Rectangle(double x1, double y1, double x2, double y2) :
	x1_(x1), y1_(y1), x2_(x2), y2_(y2)
{ }

bool implicit::Rectangle::inside(double x, double y) const
{
	double x1, x2, y1, y2;
	if (x1_ < x2_)
	{
		x1 = x1_;
		x2 = x2_;
	}
	else
	{
		x1 = x2_;
		x2 = x1_;
	}
	if (y1_ < y2_)
	{
		y1 = y1_;
		y2 = y2_;
	}
	else
	{
		y1 = y2_;
		y2 = y1_;
	}
	bool x_cond = (x < x2) * (x > x1);
	bool y_cond = (y < y2) * (y > y1);
	return x_cond * y_cond;
}