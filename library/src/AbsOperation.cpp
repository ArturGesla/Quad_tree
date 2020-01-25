#include "implicitgeometry.hpp"
implicit::AbsOperation::AbsOperation(ImplicitGeometryPtr operand1, ImplicitGeometryPtr operand2) :
	operand1_(operand1), operand2_(operand2)
{}
implicit::AbsOperation::~AbsOperation()
{
	//std::cout << "Destruction" << std::endl;
}