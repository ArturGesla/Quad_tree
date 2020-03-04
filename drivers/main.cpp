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
		double xmin = 0; //-bound;
		double xmax = 12; //bound;
		double ymin = 0;// -bound;
		double ymax = 6;// bound;
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
/*
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
	*//*
	std::cout << "Point (0, 0): " << root.inside( 0.0, 0.0 ) << std::endl;
	std::cout << "Point (1, 0): " << root.inside( 0.0, 1.0 ) << std::endl;
	std::cout << "Point (1, 0): " << root.inside( 1.1, 0.0 ) << std::endl;
	// ...
	// (to be used in the quad tree example)
	*/
	auto rectangle1 = std::make_shared<implicit::Rectangle>(1.0,4.0,4.0,5.0);
	auto rectangle2 = std::make_shared<implicit::Rectangle>(2.0,1.0,3.0,5.0);
	auto rectangle3 = std::make_shared<implicit::Rectangle>(4.0,1.0,5.0,5.0);
	auto rectangle4 = std::make_shared<implicit::Rectangle>(4.0,1.0,7.0,2.0);
	auto rectangle5 = std::make_shared<implicit::Rectangle>(6.0,1.0,7.0,5.0);
	auto rectangle6 = std::make_shared<implicit::Rectangle>(6.0,4.0,11.0,5.0);
	auto rectangle7 = std::make_shared<implicit::Rectangle>(8.0,1.0,9.0,5.0);
	auto rectangle8 = std::make_shared<implicit::Rectangle>(10.0,1.0,11.0,5.0);

	auto union1 = std::make_shared<implicit::Union>(rectangle1, rectangle2);
	auto union2 = std::make_shared<implicit::Union>(union1, rectangle3);
	auto union3 = std::make_shared<implicit::Union>(union2, rectangle4);
	auto union4 = std::make_shared<implicit::Union>(union3, rectangle5);
	auto union5 = std::make_shared<implicit::Union>(union4, rectangle6);
	auto union6 = std::make_shared<implicit::Union>(union5, rectangle7);
	auto union7 = std::make_shared<implicit::Union>(union6, rectangle8);

	sample(*union7);

	implicit::CellType cell{ implicit::Bounds{0.0,12.0},implicit::Bounds{0.0,6.0} };
	implicit::generateQuadTree(*union7, cell, 10, "quad_tree_tum.vtk");

    return 0;
}
