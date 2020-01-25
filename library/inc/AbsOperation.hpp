#pragma once
#include "AbsImplicitGeometry.hpp"
namespace implicit
{
	class AbsOperation : public AbsImplicitGeometry
	{
	public:
		AbsOperation(ImplicitGeometryPtr operand1, ImplicitGeometryPtr operand2);
		~AbsOperation();
	protected:
		ImplicitGeometryPtr operand1_;
		ImplicitGeometryPtr operand2_;
	};
}