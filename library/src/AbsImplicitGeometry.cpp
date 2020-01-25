#include "implicitgeometry.hpp"
bool implicit::AbsImplicitGeometry::inside(double x, double y) const
{
	return 0;
}
implicit::AbsImplicitGeometry::~AbsImplicitGeometry()
{
	//std::cout << "Destruction" << std::endl;
}