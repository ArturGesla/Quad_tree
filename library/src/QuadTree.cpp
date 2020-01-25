#include "QuadTree.hpp"

#include <iostream>
#include <fstream>

namespace implicit
{
	namespace detail
	{
		bool isCutByBoundary(CellType cell, const AbsImplicitGeometry& geometry,
			int numberOfSeedPoint)
		{
			double dx = (cell[0][1] - cell[0][0]) / (numberOfSeedPoint - 1.0);
			double dy = (cell[1][1] - cell[1][0]) / (numberOfSeedPoint - 1.0);

			int count = 0;

			for (int i = 0; i < numberOfSeedPoint; ++i)
			{
				for (int j = 0; j < numberOfSeedPoint; ++j)
				{
					double x = cell[0][0] + i * dx;
					double y = cell[1][0] + j * dy;

					bool isInside = geometry.inside(x, y);

					if (isInside)
					{
						count++;
					}
				}
			}

			return count != 0 && count != numberOfSeedPoint * numberOfSeedPoint;
		}

		std::array<CellType, 4> divideCell(CellType cell)
		{
			double x[] = { cell[0][0], (cell[0][1] + cell[0][0]) / 2.0, cell[0][1] };
			double y[] = { cell[1][0], (cell[1][1] + cell[1][0]) / 2.0, cell[1][1] };

			CellType cell0{ Bounds { x[0], x[1] }, Bounds{ y[1], y[2] } };
			CellType cell1{ Bounds { x[1], x[2] }, Bounds{ y[1], y[2] } };
			CellType cell2{ Bounds { x[0], x[1] }, Bounds{ y[0], y[1] } };
			CellType cell3{ Bounds { x[1], x[2] }, Bounds{ y[0], y[1] } };

			return { cell0, cell1, cell2, cell3 };
		}
		void writeCellsToVtkFile(const CellsAndLevels& data, std::string filename)
		{
			// For convenience. Use const& to prevent creating copies
			const std::vector<CellType>& cells = data.first;
			const std::vector<unsigned int>& levels = data.second;

			unsigned int numberOfCells = cells.size();

			std::ofstream outfile;

			outfile.open(filename);

			outfile << "# vtk DataFile Version 4.2" << std::endl;
			outfile << "Test Data                 " << std::endl;
			outfile << "ASCII                     " << std::endl;
			outfile << "DATASET UNSTRUCTURED_GRID " << std::endl;

			outfile << "POINTS " << 4 * numberOfCells << " " << "double " << std::endl;

			for (unsigned int i = 0; i < numberOfCells; ++i)
			{
				outfile << cells[i][0][0] << "\t" << cells[i][1][0] << "\t" << "0" << std::endl;
				outfile << cells[i][0][1] << "\t" << cells[i][1][0] << "\t" << "0" << std::endl;
				outfile << cells[i][0][1] << "\t" << cells[i][1][1] << "\t" << "0" << std::endl;
				outfile << cells[i][0][0] << "\t" << cells[i][1][1] << "\t" << "0" << std::endl;
			}

			outfile << "CELLS " << numberOfCells << " " << 5 * numberOfCells << std::endl;

			for (unsigned int i = 0; i < numberOfCells * 4; i += 4)
			{
				outfile << "4\t" << i << "\t" << i + 1 << "\t" << i + 2 << "\t" << i + 3 << std::endl;
			}

			outfile << "CELL_TYPES " << numberOfCells << std::endl;

			for (unsigned int i = 0; i < numberOfCells; i++)
			{
				outfile << "9" << std::endl;
			}

			outfile << "CELL_DATA " << numberOfCells << std::endl;
			outfile << "SCALARS depth double" << std::endl;
			outfile << "LOOKUP_TABLE default" << std::endl;

			for (unsigned int i = 0; i < numberOfCells; i++)
			{
				outfile << levels[i] << std::endl;
			}

			outfile.close();
		}
	}
	void generateQuadTree(const AbsImplicitGeometry& geometry,
		CellType cell,
		int treeDepth,
		std::string filename)
	{
		QuadTreeNode node(cell, 0);
		std::cout << "Partitioning..." << std::endl;
		node.partition(geometry, treeDepth);
		std::cout << "Extracting leaf data..." << std::endl;
		CellsAndLevels data= node.getLeafCells();
		std::cout << "Writing leaf cells..." << std::endl;
		detail::writeCellsToVtkFile(data, filename);
		std::cout << "Done!" << std::endl;

	}
	QuadTreeNode::QuadTreeNode(CellType cell, int level) :
		level_(level), cell_(cell)
	{
	}
	QuadTreeNode::~QuadTreeNode()
	{
	}
	void QuadTreeNode::partition(const AbsImplicitGeometry& geometry, int maxLevel)
	{
		if (level_ < maxLevel)
		{
			bool isCut = detail::isCutByBoundary(cell_, geometry, 7);

			if (isCut)
			{
				auto childCells = detail::divideCell(cell_);

				for (int i = 0; i < 4; i++)
				{
					QuadTreeNode childNode(childCells[i], level_ + 1);
					children_.push_back(childNode);
					children_[i].partition(geometry, maxLevel);
				}
			}
		}
	}
	CellsAndLevels QuadTreeNode::getLeafCells() const
	{
		CellsAndLevels data;
		getLeafCellsRecursive(data);
		return data;
	}
	void QuadTreeNode::getLeafCellsRecursive(CellsAndLevels& data) const
	{
		if (children_.empty())
		{
			data.first.push_back(cell_);
			data.second.push_back(level_);
			/*std::cout << "Cell on the level " << level_ << ", x in (" 
				<< cell_[0][0] << ","<< cell_[0][1] << "), y in (" 
				<< cell_[1][0] << "," << cell_[1][1] << ")"<<std::endl;
		*/}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				children_[i].getLeafCellsRecursive(data);
			}
		}
	}
}