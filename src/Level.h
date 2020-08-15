#pragma once

#include "Common.h"
#include <Sprite.hpp>

namespace godot {

	class Level : public Sprite
	{
		GODOT_CLASS(Level, Sprite);

	private:
		float time_passed;
		float time_emit;
		float amplitude;
		float speed;

	public:
		static void _register_methods();

		Level();
		~Level();

		void _init(); // our initializer called by Godot

		void _process(float delta);
		void set_speed(float p_speed);
		float get_speed();

	};
}