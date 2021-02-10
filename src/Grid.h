#pragma once

#include "Common.h"
#include <map>
#include "GridNode.h"

namespace godot {

	class Grid 
	{

	public:

		Grid();

		Grid(int rowCount, int collumnCount);

		GridNode* GetNode(int row, int collumn);

		int CollumnCount;

		int RowCount;

	private:

		map<String, unique_ptr<GridNode>> indicies;

	};
};

