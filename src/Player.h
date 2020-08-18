#pragma once

#include "Common.h"
#include "Controls.h"
#include <Sprite.hpp>
namespace godot {
	///<summary>
	///The main player object
	///</summary>
	class Player : public Sprite
	{
		GODOT_CLASS(Player, Sprite)

	public:
		static void _register_methods();

		void _init();

		void _process(float delta);

		unique_ptr<Vector2> Velocity;

		float speed;
	};
}

