#include "implicitgeometry.hpp"
implicit::Union::Union(ImplicitGeometryPtr operand1, ImplicitGeometryPtr operand2) :
	AbsOperation(operand1,operand2)
{}
bool implicit::Union::inside(double x, double y) const
{
	return (operand1_->inside(x, y) + operand2_->inside(x, y)) ;
}