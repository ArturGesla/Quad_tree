#pragma once
#include "AbsImplicitGeometry.hpp"
namespace implicit
{
	class Circle : public AbsImplicitGeometry
	{
	public:
		Circle(double x, double y, double r);
		bool inside(double x, double y) const;
	private:
		double x_, y_;
		double radius_;
	};
}

