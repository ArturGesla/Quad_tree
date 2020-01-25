#include "QuadTree.hpp"
#include "AbsImplicitGeometry.hpp"
#include "Circle.hpp"
#include "Rectangle.hpp"
#include "AbsOperation.hpp"
#include "Union.hpp"
#include "Difference.hpp"
#include "Intersection.hpp"

#include <iostream>




namespace implicit
{
	using ImplicitGeometryPtr = std::shared_ptr<implicit::AbsImplicitGeometry>;
	void sample(AbsImplicitGeometry& geometry) //prints ONE geometry object
	{
		double bound = 1.58;
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

int main()
{
	//implicit::ImplicitGeometryPtr circle1( new implicit::Circle( 0.0, 0.0, 1.06 ) );
	//sample(*circle1);
	auto circle1 = std::make_shared<implicit::Circle>(0.0, 0.0, 1.06);
	auto rectangle1 = std::make_shared<implicit::Rectangle>(-1.0, -1.0, 1.0, 1.0);
	auto intersection = std::make_shared<implicit::Intersection>(circle1, rectangle1);
	auto rectangle2 = std::make_shared<implicit::Rectangle>(-0.1, -1.5, 0.1, 1.5);
	auto union1 = std::make_shared<implicit::Union>(intersection, rectangle2);
	auto circle2 = std::make_shared<implicit::Circle>(0.0, 0.0, 0.65);
	auto root = std::make_shared<implicit::Difference>(union1, circle2);
	//implicit::Difference root( union1, circle2 );
	//sample(root);

	implicit::Rectangle rect(0.1,0.1,1.1,1.1);
	sample(rect);
	implicit::ImplicitGeometryPtr rect_ptr(new implicit::Rectangle(0.1, 0.1, 1.1, 1.1));
	/*
	std::cout << "Point (0, 0): " << root.inside( 0.0, 0.0 ) << std::endl;
	std::cout << "Point (1, 0): " << root.inside( 0.0, 1.0 ) << std::endl;
	std::cout << "Point (1, 0): " << root.inside( 1.1, 0.0 ) << std::endl;
	// ...
	// (to be used in the quad tree example)
	*/
	implicit::CellType cell{ implicit::Bounds{-1.58, 1.58 },implicit::Bounds{-1.58,1.58} };
	implicit::generateQuadTree(*root, cell, 10, "quad_tree.vtk");
    return 0;
}
