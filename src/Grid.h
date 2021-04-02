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

		Grid(int xCount, int yCount);

		int XCount;

		int YCount;

		bool AssignNode(int x, int y, GridObject* callObject);

		GridNode*** Indicies;
		
	};
};

