#include <iostream>
#include "AbsImplicitGeometry.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
using ImplicitGeometryPtr = std::shared_ptr<implicit::AbsImplicitGeometry>;
#include "AbsOperation.hpp"
#include "Union.hpp"
#include "Difference.hpp"
#include "Intersection.hpp"

namespace implicit
{
	using ImplicitGeometryPtr = std::shared_ptr<implicit::AbsImplicitGeometry>;
	void sample(AbsImplicitGeometry& geometry) //prints ONE geometry object
	{
		double bound = 2;
		double xmin = -bound;
		double xmax = bound;
		double ymin = -bound;
		double ymax = bound;
		double res = 0.05;

		int nx = 2 * int(bound/res);
		int ny = 2 * int(bound/res);

		for (int j = ny; j > 0; --j)
		{
			for (int i = 0; i < nx; ++i)
			{
				double x = xmin + (i / (nx - 1.0)) * (xmax - xmin);
				double y = ymin + (j / (ny - 1.0)) * (ymax - ymin);

				if (geometry.inside(x, y))
				{
					std::cout <<"x ";
				}
				else
				{
					std::cout << "  ";
				}
			}

			std::cout << std::endl;
		}
	}

}
int main( )
{
    implicit::ImplicitGeometryPtr circle1( new implicit::Circle( 0.0, 0.0, 1.06 ) );
	//sample(*circle1);
    implicit::ImplicitGeometryPtr rectangle1( new implicit::Rectangle( -1.0, -1.0, 1.0, 1.0 ) );
	//sample(*rectangle1);
    implicit::ImplicitGeometryPtr intersection( new implicit::Intersection( circle1, rectangle1 ) );
	//sample(*intersection);
    implicit::ImplicitGeometryPtr rectangle2( new implicit::Rectangle( -0.1, -1.5, 0.1, 1.5 ) );
	//sample(*rectangle2);
    implicit::ImplicitGeometryPtr union1( new implicit::Union( intersection, rectangle2 ) );
	//sample(*union1);
    implicit::ImplicitGeometryPtr circle2( new implicit::Circle( 0.0, 0.0, 0.65 ) );
	//sample(*circle2);
    implicit::Difference root( union1, circle2 );
	sample(root);
	/*
    std::cout << "Point (0, 0): " << root.inside( 0.0, 0.0 ) << std::endl;
    std::cout << "Point (1, 0): " << root.inside( 0.0, 1.0 ) << std::endl;
    std::cout << "Point (1, 0): " << root.inside( 1.1, 0.0 ) << std::endl;
    // ... 
    // (to be used in the quad tree example)
	*/
    return 0;
}
