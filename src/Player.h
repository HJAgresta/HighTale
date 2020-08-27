#pragma once

#include "Common.h"
#include "Controls.h"
#include <KinematicCollision2D.hpp>
#include <KinematicBody2D.hpp>
#include <StaticBody2D.hpp>
#include <Ref.hpp>

namespace godot {
	///<summary>
	///The main player object
	///</summary>
	class Player : public KinematicBody2D
	{
		GODOT_CLASS(Player, KinematicBody2D)

	public:
		static void _register_methods();

		void _init();

		void _physics_process(float delta);

		unique_ptr<Vector2> Velocity;

		float speed;
	};
}

