#pragma once
#include "AbsImplicitGeometry.hpp"

#include <array>
#include <vector>

namespace implicit
{

	using Bounds = std::array<double, 2>;
	using CellType = std::array<Bounds, 2>;

	void generateQuadTree(const AbsImplicitGeometry& geometry,
		CellType cell,
		int treeDepth,
		std::string filename);

	using CellsAndLevels = std::pair<std::vector<CellType>,
		std::vector<unsigned int>>;

	class QuadTreeNode
	{
	public:
		QuadTreeNode(CellType cell,int level);
		~QuadTreeNode();

		void partition(const AbsImplicitGeometry& geometry, int maxLevel);

		CellsAndLevels getLeafCells() const;
	private:
		void getLeafCellsRecursive(CellsAndLevels& data) const;

		std::vector<QuadTreeNode> children_;
		CellType cell_;
		int level_;
	};

	namespace detail
	{
		bool isCutByBoundary(CellType cell, const AbsImplicitGeometry& geometry,
			int numberOfSeedPoint);
		std::array<CellType, 4> divideCell(CellType cell);
		void writeCellsToVtkFile(const CellsAndLevels& data, std::string filename);
	}
	
}