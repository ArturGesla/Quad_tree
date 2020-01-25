#pragma once
#include <iostream>
namespace implicit
{
	class AbsImplicitGeometry
	{
	public:
		virtual bool inside(double x, double y) const;
		virtual ~AbsImplicitGeometry();
	};
	using ImplicitGeometryPtr = std::shared_ptr<implicit::AbsImplicitGeometry>;
}