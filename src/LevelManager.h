#pragma once

#include "Common.h"
#include "Grid.h"
#include "GridNode.h"
#include <Node2D.hpp>

namespace godot {

	class LevelManager : public Object
	{
		GODOT_CLASS(LevelManager, Object)

	public:
		static void _register_methods();

		virtual void _init();

		Grid grid;



	};
};

