#pragma once

#include "Common.h"
#include "Grid.h"
#include "GridNode.h"
#include "Player.h"
#include <Node2D.hpp>
#include <Dictionary.hpp>
#include <PackedScene.hpp>
#include <ResourceLoader.hpp>
#include <string>


namespace godot {

	class LevelManager : public Node2D
	{
		GODOT_CLASS(LevelManager, Node2D)

	public:
		static void _register_methods();

		virtual void _init();

		virtual void _ready();

		Grid* grid;

		~LevelManager();

		Player* player;

		Dictionary ObjectTypes;

	};
};

