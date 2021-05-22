#pragma once

#include "Common.h"
#include <Node2D.hpp>

namespace godot {

	struct GridNode
	{

	public:

		GridNode();

		GridNode(int xCount, int yCount);

		int XCount;

		int YCount;

		Vector2 Center;

		Node2D* Occupant;

	};
};

