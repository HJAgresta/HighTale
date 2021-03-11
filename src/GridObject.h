#pragma once

#include "Common.h"
#include "GridNode.h"
#include <KinematicBody2D.hpp>

namespace godot {
	///<summary>
	///The main player object
	///</summary>
	class GridObject : public KinematicBody2D
	{
		GODOT_CLASS(GridObject, KinematicBody2D)

	public:

		GridNode* AssignedNode;

	};
}