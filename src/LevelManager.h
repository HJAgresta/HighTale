#pragma once

#include "Common.h"
#include "Grid.h"
#include "GridNode.h"
#include <Node2D.hpp>
#include <Dictionary.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>


namespace godot {

	class LevelManager : public Node
	{
		GODOT_CLASS(LevelManager, Node)

	public:
		static void _register_methods();

		virtual void _init();

		virtual void _ready();

		godot::Grid grid;

		Dictionary EnemyTypes;

		Dictionary StaticObjectTypes;

	};
};

