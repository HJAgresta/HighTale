#pragma once

#include "Common.h"
#include "GridNode.h"
#include "GridObject.h"

namespace godot {

	class Grid 
	{

	public:

		Grid();

		~Grid();

		Grid(int rowCount, int collumnCount);

		int CollumnCount;

		int RowCount;

		bool AssignNode(int row, int collumn, GridObject* callObject);

		GridNode*** Indicies;




	};
};

