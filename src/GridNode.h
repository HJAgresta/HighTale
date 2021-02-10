#pragma once

#include "Common.h"
#include <Node2D.hpp>

namespace godot {

	struct GridNode 
	{

	public:

		GridNode(int row, int collumn);

		int Row;

		int Collumn;

		Vector2 Center;

		Node2D* Occupant;

	};
};

