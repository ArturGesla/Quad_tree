#include "AbsOperation.hpp"
namespace implicit
{
	class Union : public AbsOperation
	{
	public:
		Union(ImplicitGeometryPtr operand1, ImplicitGeometryPtr operand2);
		bool inside(double x, double y) const;
	};
}