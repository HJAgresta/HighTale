#pragma once

#include "Common.h"
#include <map>
#include "GridNode.h"

namespace godot {

	class Grid : public Object
	{
		GODOT_CLASS(Grid, Object)

	public:
		static void _register_methods();

		virtual void _init();

		Grid();

		Grid(int collumnCount, int rowCount);

		map<String, unique_ptr<GridNode>> indicies;

		int CollumnCount;

		int RowCount;

	};
};

