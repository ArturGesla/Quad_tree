#include "implicitgeometry.hpp"
implicit::Difference::Difference(ImplicitGeometryPtr operand1, ImplicitGeometryPtr operand2) :
	AbsOperation(operand1, operand2)
{}
bool implicit::Difference::inside(double x, double y) const
{
	bool decision = 0;
	if (operand1_->inside(x, y) == 1 && operand2_->inside(x, y) == 0)
	{
		decision = 1;
	}
	else
	{
		decision = 0;
	}
	return decision;
}